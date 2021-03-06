
#version 330

in vec3 texCoord; 

// The final colour we will see at this location on screen
out vec4 fragColour;

uniform samplerCube skybox;

void main(void)
{
    // Texture lookup, just as for 2D texture mapping
    fragColour = texture(skybox, texCoord);
    // fragColour = vec4(1.0, 0.2, 1.0, 1.0);
}
