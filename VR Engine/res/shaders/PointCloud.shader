#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colour;

uniform mat4 u_transformationMatrix;
uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform float u_usingVR;
uniform mat4 u_VRMatrix;

out vec3 out_colour;

void main()
{

	vec4 worldPosition = u_transformationMatrix * vec4(position, 1.0);
	vec4 positionRelativeToCam = u_viewMatrix * worldPosition;

	if (u_usingVR > 0.5)
	{
		gl_Position = u_VRMatrix * positionRelativeToCam;;
	}
	else
	{
		gl_Position = u_projectionMatrix * positionRelativeToCam;
	}

	out_colour = colour;
};


#shader fragment
#version 330 core

in vec3 out_colour;

out vec4 color;

void main()
{	
	color = vec4(out_colour, 1.0);
};