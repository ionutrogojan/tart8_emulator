#version 330

// Input from vertex shader
in vec2 TexCoords;
// Texture sampler
uniform sampler2D textureSampler;
uniform vec4 replaceColor;
uniform vec4 newColor;
// Output to the framebuffer
out vec4 FragColor;

void main() {
    // Sample the texture at the current texture coordinate
    vec4 originalColor = texture(textureSampler, TexCoords);
	// vec4 replaceColor = vec4(0.0, 0.0, 0.0, 1.0);

	// if (originalColor == replaceColor) {
	if (distance(originalColor, replaceColor) < 0.1) {
    	// Replace the color with a new color
    	FragColor = newColor;
	} else {
    	// Output the new color to the framebuffer
    	// FragColor = originalColor;
		FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
}