#shader vertex
#version 400 core

layout(location = 0) in vec2 position;

out vec4 clipSpace;
out vec2 textureCoords;
out vec3 toCameraVector;
out vec3  fromLightVector;

uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform vec3 u_cameraPosition;
uniform vec3 u_lightPosition;

const float tiling = 15.0;

void main()
{
	vec4 worldPosition = u_transformationMatrix * vec4(position.x, 0.0, position.y, 1.0);
	clipSpace = u_projectionMatrix * u_viewMatrix * worldPosition;
	gl_Position = clipSpace;
	textureCoords = vec2(position.x / 2.0 + 0.5, position.y / 2.0 + 0.5) * tiling;
	toCameraVector = u_cameraPosition - worldPosition.xyz;
	fromLightVector = worldPosition.xyz - u_lightPosition;
};


#shader fragment
#version 400 core

in vec4 clipSpace;
in vec2 textureCoords;
in vec3 toCameraVector;
in vec3 fromLightVector;

out vec4 color;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudvMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;

uniform float u_moveFactor;
uniform vec3 u_lightColour;

const float waveStrength = 0.02;
const float refractivePower = 10;
const float shineDamper = 20.0;
const float reflectivity = 0.6;

void main()
{
	vec2 ndc = (clipSpace.xy / clipSpace.w)/2.0 + 0.5;
	vec2 refractTexCoords = vec2(ndc.x, ndc.y);
	vec2 reflectTexCoords = vec2((ndc.x), (1 - ndc.y)); 

	float near = 0.1f;
	float far = 1000.0f;
	float depth = texture(depthMap, refractTexCoords).r;
	float floorDistance = 2.0 *near * far / (far + near - (2.0 * depth - 1.0)*(far - near));

	depth = gl_FragCoord.z;
	float waterDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
	float waterDepth = floorDistance - waterDistance;

	vec2 distortedTexCoords = texture(dudvMap, vec2(textureCoords.x + u_moveFactor, textureCoords.y)).rg*0.1;
	distortedTexCoords = textureCoords + vec2(distortedTexCoords.x, distortedTexCoords.y/* + u_moveFactor*/);
	vec2 totalDistortion = (texture(dudvMap, distortedTexCoords).rg * 2.0 - 1.0) * waveStrength * clamp(waterDepth / 5.0, 0.0, 1.0); //5 max depth for alfa == 1;
	
	refractTexCoords += totalDistortion;
	reflectTexCoords += totalDistortion;

	refractTexCoords = clamp(refractTexCoords, 0.001, 0.999);
	reflectTexCoords = clamp(reflectTexCoords, 0.001, 0.999);

	vec4 reflectColour = texture(reflectionTexture, reflectTexCoords);
	vec4 refractColour = texture(refractionTexture, refractTexCoords);

	vec3 viewVector = normalize(toCameraVector);
	float fractiveFactor = dot(viewVector, vec3(0.0, 1.0, 0.0));
	fractiveFactor = pow(fractiveFactor, refractivePower);

	vec4 normalMapColour = texture(normalMap, distortedTexCoords);
	vec3 normal = vec3(normalMapColour.r * 2.0 - 1.0, normalMapColour.b, normalMapColour.g * 2.0 - 1.0);
	normal = normalize(normal);

	vec3 reflectedLight = reflect(normalize(fromLightVector), normal);
	float specular = max(dot(reflectedLight, viewVector), 0.0);
	specular = pow(specular, shineDamper);
	vec3 specularHighlights = u_lightColour * specular * reflectivity * clamp(waterDepth / 5.0, 0.0, 1.0); //5 max depth for alfa == 1;

	

	color = mix(reflectColour, refractColour, fractiveFactor);
	color = mix(color, vec4(0.0, 0.3, 0.5, 1.0), 0.2) + vec4(specularHighlights, 0.0);
	color.a = clamp(waterDepth/5.0, 0.0, 1.0); //5 max depth for alfa == 1
};