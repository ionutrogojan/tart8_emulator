#version 330

in vec2 fragTexCoord;

uniform sampler2D textureSampler;
// uniform vec4 originColor;
uniform vec4 newColor;

out vec4 finalColor;

void main() {
	vec4 currentColor = texture(textureSampler, fragTexCoord);

	if (currentColor.a == 1.0)
		finalColor = newColor;
	else
		finalColor = currentColor;
}
