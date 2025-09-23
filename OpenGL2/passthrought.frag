// File: "passthrought.frag"
// Caution: Use UNIX EOL-format

#version 430

in vec4 color;
out vec4 fColor; //final color

void main()
{
	fColor = color;
}