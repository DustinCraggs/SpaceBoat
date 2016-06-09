
// Per-fragment Phong lighting.
// The vertex shader converts vertex position and normal in eye space.
// Passes these to the fragment shader for per-fragment Phong calculation.

#version 330

layout (location = 0) in vec3 vertex_in;
layout (location = 1) in vec3 colour_in;

out vec3 particle_colour;

void main(void){
	gl_Position = vec4(vertex_in, 1.0);
	gl_PointSize = 2.0;
	particle_colour = colour_in;
}
