#version 430

in vec4 in_position;

out vec2 UV;

void main() {
	// quad coordinates [-1,1] to tex coordinates [0,1]:
	UV = (1.0f+in_position.xy)/2.0f;

	// no MVP, just orthogonal projection:
	gl_Position = in_position;
}