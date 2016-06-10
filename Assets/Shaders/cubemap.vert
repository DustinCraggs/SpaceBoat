
#version 330

layout (location = 0) in vec3 a_vertex; 
layout (location = 1) in vec3 a_normal; 

uniform mat4 projection_matrix;
uniform mat4 modelview_matrix;

// Notice 3D tex coords for a cube map
// Tex coord is a direction in 3D
out vec3 texCoord;

void main(void)
{

	texCoord = a_vertex; // use position as texture coord

    gl_Position = projection_matrix * modelview_matrix * vec4(a_vertex, 1.0);
}
