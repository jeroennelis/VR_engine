#shader vertex
#version 330

const int MAX_JOINTS = 50;//max joints allowed in a skeleton
const int MAX_WEIGHTS = 3;//max number of joints that can affect a vertex

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_textureCoords;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in ivec3 in_jointIndices;
layout(location = 4) in vec3 in_weights;

out vec2 pass_textureCoords;
out vec3 pass_normal;
out vec3 toLightVector;

uniform mat4 u_jointTransforms[MAX_JOINTS];
uniform mat4 u_transformationMatrix;
uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;

uniform vec3 u_lightPosition;

void main(void) {

	vec4 totalLocalPos = vec4(0.0);
	vec4 totalNormal = vec4(0.0);

	for (int i = 0; i<MAX_WEIGHTS; i++) 
	{
		mat4 jointTransform = u_jointTransforms[in_jointIndices[i]];
		vec4 posePosition = jointTransform * vec4(in_position, 1.0);
		totalLocalPos += posePosition * in_weights[i];

		vec4 worldNormal = jointTransform * vec4(in_normal, 0.0);
		totalNormal += worldNormal * in_weights[i];
	}
	vec4 worldPosition = u_transformationMatrix * totalLocalPos;

	vec4 positionRelativeToCam = u_viewMatrix * worldPosition;

	gl_Position = u_projectionMatrix * positionRelativeToCam;

	pass_normal = totalNormal.xyz;
	pass_textureCoords = in_textureCoords;

	toLightVector = u_lightPosition - worldPosition.xyz;
}


#shader fragment
#version 330

in vec2 pass_textureCoords;
in vec3 pass_normal;
in vec3 toLightVector;

out vec4 out_colour;

uniform sampler2D textureSampler;
uniform vec3 u_lightColour;

void main(void) {

	vec3 unitNormal = normalize(pass_normal);
	vec3 unitLightVector = normalize(toLightVector);

	float nDot = dot(unitNormal, unitLightVector);
	float brightness = max(nDot, 0.2); // 0.2 ambient lighting, future uniform
	vec3 diffuse = brightness * u_lightColour;

	vec4 textureColour = texture(textureSampler, pass_textureCoords);

	out_colour = vec4(diffuse, 1.0) * textureColour;

}