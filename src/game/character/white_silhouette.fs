#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform float flashAmount; // 0.0 = normal, 1.0 = full white

out vec4 finalColor;

void main()
{
    vec4 texColor = texture(texture0, fragTexCoord) * fragColor;
    vec4 whiteColor = vec4(1.0, 1.0, 1.0, texColor.a);
    finalColor = mix(texColor, whiteColor, flashAmount);
}