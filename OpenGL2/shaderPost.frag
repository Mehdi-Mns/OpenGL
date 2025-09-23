#version 430

in vec2 UV;

out vec4 fColor;

uniform float time; // current time in s or ms

void main() {
	fColor = vec4(texture(renderedTexture, UV).xyz,1.0);
}