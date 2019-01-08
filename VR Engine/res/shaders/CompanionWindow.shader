#shader vertex
#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 v2UVIn;

noperspective out vec2 v2UV;

void main()
{
	v2UV = v2UVIn;
	gl_Position = position;
}


#shader fragment
#version 410 core

uniform sampler2D mytexture;

noperspective in vec2 v2UV;

out vec4 outputColor;

void main()
{
	outputColor = texture(mytexture, v2UV);
}