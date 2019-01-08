#shader vertex
#version 410

uniform mat4 matrix;

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 v2TexCoordsIn;
layout(location = 2) in vec3 v3NormalIn;


out vec2 v2TexCoord;

void main()
{
	v2TexCoord = v2TexCoordsIn;
	gl_Position = matrix * vec4(position.xyz, 1);
}


#shader fragment
#version 410 core

uniform sampler2D diffuse;

in vec2 v2TexCoord;

out vec4 outputColor;

void main()
{
	outputColor = texture(diffuse, v2TexCoord);
}