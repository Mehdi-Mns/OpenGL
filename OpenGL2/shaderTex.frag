#version 430

in vec2 UV;

out vec4 fColor;

uniform float time; // current time in s or ms

void main() {
	// compute a nice color for this pixel
	// depending on UV.x, UV.y and time
	float Cosinus = cos(UV.x + UV.y + time/1000);
	float Sinus = sin(UV.x + UV.y + time/1000);
	fColor = vec4(Sinus, Cosinus, Sinus+Cosinus, 1);
}