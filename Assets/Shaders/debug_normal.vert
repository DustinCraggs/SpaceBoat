
// Per-fragment Phong lighting.
// The vertex shader converts vertex position and normal in eye space.
// Passes these to the fragment shader for per-fragment Phong calculation.

#version 330

uniform mat4 projection_matrix;
uniform mat4 modelview_matrix;

layout (location = 0) in vec3 vertex_in;
layout (location = 1) in vec3 normal_in;

out vec3 normal; // the eye space normal

void main(void){
	normal = normalize(normal_in);
	
	gl_Position = projection_matrix * modelview_matrix * vec4(vertex_in, 1.0);
}
