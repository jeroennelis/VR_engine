#shader vertex
#version 330 core

layout(location = 0) in vec3 position;


void main()
{
	gl_Position = vec4(position, 1.0);
};

#shader geometry
#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices = 24) out;

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;

const float size = 0.1;

void createVertex(vec3 offset)
{
	vec4 actualOffset = vec4(offset * size, 0.0);
	vec4 worldPosition = gl_in[0].gl_Position + actualOffset;
	vec4 positionRelativeToCam = u_viewMatrix * worldPosition;
	gl_Position = u_projectionMatrix * positionRelativeToCam;
	EmitVertex();
}

void main()
{
	createVertex(vec3(-1.0, 1.0, 1.0));
	createVertex(vec3(-1.0, -1.0, 1.0));
	createVertex(vec3(1.0, 1.0, 1.0));
	createVertex(vec3(1.0, -1.0, 1.0));

	EndPrimitive();

	createVertex(vec3(1.0, 1.0, 1.0));
	createVertex(vec3(1.0, -1.0, 1.0));
	createVertex(vec3(1.0, 1.0, -1.0));
	createVertex(vec3(1.0, -1.0, -1.0));

	EndPrimitive(); 
	
	createVertex(vec3(1.0, 1.0, -1.0));
	createVertex(vec3(1.0, -1.0, -1.0));
	createVertex(vec3(-1.0, 1.0, -1.0));
	createVertex(vec3(-1.0, -1.0, -1.0));

	EndPrimitive(); 
	
	createVertex(vec3(-1.0, 1.0, -1.0));
	createVertex(vec3(-1.0, -1.0, -1.0));
	createVertex(vec3(-1.0, 1.0, 1.0));
	createVertex(vec3(-1.0, -1.0, 1.0));

	EndPrimitive(); 
	
	createVertex(vec3(1.0, 1.0, 1.0));
	createVertex(vec3(1.0, 1.0, -1.0));
	createVertex(vec3(-1.0, 1.0, 1.0));
	createVertex(vec3(-1.0, 1.0, -1.0));

	EndPrimitive(); 
	
	createVertex(vec3(-1.0, -1.0, 1.0));
	createVertex(vec3(-1.0, -1.0, -1.0));
	createVertex(vec3(1.0, -1.0, 1.0));
	createVertex(vec3(1.0, -1.0, -1.0));

	EndPrimitive();
};

#shader fragment
#version 330 core

out vec4 color;

void main()
{	
	color = vec4(1.0, 0.0, 0.0, 1.0);
};