#shader vertex
#version 330 core

layout(location = 0) in vec2 position;

out vec2 textureCoords;

uniform mat4 u_transformationMatrix;

void main()
{
	gl_Position = u_transformationMatrix * vec4(position, 0.0, 1.0);
	textureCoords = vec2((position.x + 1.0) / 2.0, 1 - (position.y + 1.0) / 2.0);
};


#shader fragment
#version 330 core

in vec2 textureCoords;

layout(location = 0) out vec4 color;

uniform sampler2D guiTexture;


void main()
{
	
	color = texture(guiTexture, textureCoords);
};