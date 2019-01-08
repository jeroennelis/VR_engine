#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoords;
layout(location = 2) in vec3 normal;

out vec2 pass_textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCamVector;
out float visibility;

uniform mat4 u_transformationMatrix;
uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform vec3 u_lightPosition;
uniform float u_usingVR;
uniform mat4 u_VRMatrix;

uniform vec4 u_clipPlane;

const float density = 0.0007;		//TODO make uniform
const float gradient = 1.5;			//TODO make uniform

void main()
{
	vec4 worldPosition = u_transformationMatrix * vec4(position, 1.0);
	gl_ClipDistance[0] = dot(worldPosition, u_clipPlane);


	vec4 positionRelativeToCam = u_viewMatrix * worldPosition;

	if (u_usingVR > 0.5)
	{
		gl_Position = u_VRMatrix * worldPosition;
	}
	else
	{
		gl_Position = u_projectionMatrix * positionRelativeToCam;
	}

	pass_textureCoords = textureCoords;

	surfaceNormal = (u_transformationMatrix *vec4(normal, 0.0)).xyz;
	toLightVector = u_lightPosition - worldPosition.xyz;
	toCamVector = (inverse(u_viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;

	float distance = length(positionRelativeToCam.xyz);
	visibility = exp(-pow((distance*density), gradient));
	visibility = clamp(visibility, 0.0, 1.0);
};


#shader fragment
#version 330 core

in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCamVector;
in float visibility;

layout(location = 0) out vec4 color;

uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;

uniform vec3 u_lightColour;
uniform float u_shineDamper;
uniform float u_reflectivity;
uniform vec3 u_skyColour;

void main()
{
	vec4 blendMapColour = texture(blendMap, pass_textureCoords);

	float backTextureAmount = 1 - (blendMapColour.r + blendMapColour.g + blendMapColour.b);
	vec2 tiledCoords = pass_textureCoords * 40.0;
	vec4 backgroundTextureColour = texture(backgroundTexture, tiledCoords) * backTextureAmount;
	vec4 rTextureColour = texture(rTexture, tiledCoords) * blendMapColour.r;
	vec4 gTextureColour = texture(gTexture, tiledCoords) * blendMapColour.g;
	vec4 bTextureColour = texture(bTexture, tiledCoords) * blendMapColour.b;

	vec4 totalColour = backgroundTextureColour + rTextureColour + gTextureColour + bTextureColour;

	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);

	float nDot = dot(unitNormal, unitLightVector);
	float brightness = max(nDot, 0.2); // 0.2 ambient lighting, future uniform
	vec3 diffuse = brightness * u_lightColour;

	vec3 unitVectorToCam = normalize(toCamVector);
	vec3 lightDirection = -unitLightVector;
	vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

	float specularFactor = dot(reflectedLightDirection, unitVectorToCam);
	specularFactor = max(specularFactor, 0.0);
	float dampedFactor = pow(specularFactor, u_shineDamper);
	vec3 finalSpecular = dampedFactor * u_reflectivity * u_lightColour;


	color = vec4(diffuse, 1.0) * totalColour + vec4(finalSpecular, 1.0);
	color = mix(vec4(u_skyColour, 1.0), color, visibility);
};