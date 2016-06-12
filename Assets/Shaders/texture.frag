
// Calculates Blinn Phong colour at each fragment

#version 330

in vec2 texcoord;

out vec4 fragColour;

uniform mat4 view_matrix;

uniform sampler2D diffmap;

void main(void){
    fragColour = vec4(texture(diffmap, texcoord));
    // fragColour = vec4(1.0);
    
}
