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

uniform float u_useFakeLighting;

uniform float u_numberOfRows;
uniform vec2 u_offset;

uniform vec4 u_clipPlane;

const float density = 0.0007;		//TODO make uniform
const float gradient = 1.5;			//TODO make uniform


void main()
{
	vec4 worldPosition = u_transformationMatrix * vec4(position,1.0);
	
	gl_ClipDistance[0] = dot(worldPosition, u_clipPlane);

	vec4 positionRelativeToCam = u_viewMatrix * worldPosition;

	if (u_usingVR > 0.5)
	{
		gl_Position = u_VRMatrix * positionRelativeToCam;
	}
	else
	{
		gl_Position = u_projectionMatrix * positionRelativeToCam;
	}
	
	pass_textureCoords = (textureCoords/ u_numberOfRows) + u_offset;

	vec3 actualNormal = normal;
	if (u_useFakeLighting > 0.5)
	{
		actualNormal = vec3(0.0, 1.0, 0.0);
	}


	surfaceNormal = (u_transformationMatrix *vec4(actualNormal, 0.0)).xyz;
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

uniform sampler2D textureSampler;
uniform vec3 u_lightColour;
uniform float u_shineDamper;
uniform float u_reflectivity;
uniform vec3 u_skyColour;

void main()
{
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

	vec4 textureColour = texture(textureSampler, pass_textureCoords);
	if (textureColour.a < 0.5)
	{
		discard;
	}

	color = vec4(diffuse, 1.0) * textureColour + vec4(finalSpecular, 1.0);

	color = mix(vec4(u_skyColour, 1.0), color, visibility);
};