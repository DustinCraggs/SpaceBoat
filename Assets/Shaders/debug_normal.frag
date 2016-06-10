
// Calculates Blinn Phong colour at each fragment

#version 330

in vec3 normal;

out vec4 fragColour;

void main(void){
    fragColour = vec4((normal + 1.0)/2.0, 1.0);
}
