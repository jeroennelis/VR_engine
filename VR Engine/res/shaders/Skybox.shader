#shader vertex
#version 400

layout(location = 0) in vec3 position;

out vec3 textureCoords;

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;

void main(void) {

	gl_Position = u_projectionMatrix * u_viewMatrix * vec4(position, 1.0);
	textureCoords = position;
}

#shader fragment
#version 400

in vec3 textureCoords;
out vec4 out_Color;

uniform samplerCube cubeMap;

void main(void) {
	out_Color = texture(cubeMap, textureCoords);
}