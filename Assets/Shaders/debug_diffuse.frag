
// Calculates Blinn Phong colour at each fragment

#version 330

uniform vec3 diffuse;

out vec4 fragColour;

void main(void){
    fragColour = vec4(diffuse, 1.0);
}
