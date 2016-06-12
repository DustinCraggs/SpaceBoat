#version 330

in vec3 normal;

out vec4 fragColour;

void main(void){
	vec3 normals = normal;
    fragColour = vec4(1.0f, 0.9f, 0.5f, 0.1f);
}
