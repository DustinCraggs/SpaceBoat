#version 330

in vec3 normal;

out vec4 fragColour;

void main(void){

	vec3 normals = normal;
	float multiplier = gl_FragCoord.w;
    fragColour = vec4(0.9, 0.6, 0.2, multiplier*0.5);
}
