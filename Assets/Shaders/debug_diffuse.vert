
#version 330

uniform mat4 projection_matrix;
uniform mat4 modelview_matrix;

layout (location = 0) in vec3 vertex_in;

void main(void){
	gl_Position = projection_matrix * modelview_matrix * vec4(vertex_in, 1.0);
}
