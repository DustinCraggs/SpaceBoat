
// Per-fragment Phong lighting.
// The vertex shader converts vertex position and normal in eye space.
// Passes these to the fragment shader for per-fragment Phong calculation.

#version 330

uniform mat4 projection_matrix;
uniform mat4 modelview_matrix;
// uniform mat3 normal_matrix;

layout (location = 0) in vec3 vertex_in;
layout (location = 1) in vec3 normal_in;
layout (location = 2) in vec2 texcoord_in;

out vec2 texcoord;

void main(void){
    texcoord = vec2(texcoord_in.x, 1 - texcoord_in.y);
	gl_Position = projection_matrix *  modelview_matrix * vec4(vertex_in, 1.0);
}
