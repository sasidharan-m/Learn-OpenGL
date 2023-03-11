#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// uniform variable that controls the texture blend
uniform float blend;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // linearly interpolate between both textures (((1-blend)*100)% texture1, (blend*100)% texture2)
    FragColor = mix(texture(texture1, TexCoord),
                    texture(texture2, vec2(TexCoord.x, TexCoord.y)), blend);
}

