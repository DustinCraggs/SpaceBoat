
// Calculates Blinn Phong colour at each fragment

#version 330

out vec4 fragColour;

in vec3 particle_colour;

void main(void){
	// vec3 t = particle_colour;
	// fragColour = vec4(0.5);
    fragColour = vec4(particle_colour, 1.0);
}
