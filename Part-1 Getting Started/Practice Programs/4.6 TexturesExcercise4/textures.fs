#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

// uniform value to set the transperancy of the textures
uniform float mixvalue;

void main()
{
    // linearly interpolate between both textures (80% texture1, 20% texture2)
    FragColor = mix(texture(texture1, TexCoord),
                    texture(texture2, TexCoord), mixvalue);
}

