// Shader fragment - đổi texture sang đỏ nhấp nháy
#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform float time;

out vec4 finalColor;

void main() {
    vec4 texColor = texture(texture0, fragTexCoord);
    float flash = abs(sin(time * 3.0));  // nhấp nháy nhanh (10Hz)
    vec3 redTint = mix(texColor.rgb, vec3(1.0, 0.0, 0.0), flash * 0.25);
    finalColor = vec4(redTint, texColor.a) * fragColor;
}
