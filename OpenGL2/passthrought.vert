// File: "passthrought.vert"
// Caution: Use UNIX EOL-format

#version 430

in vec4 vPosition;
in vec4 vColor;
uniform mat4 MVP;   //Projection * View * Model
out vec4 color;		//final color

void main()
{
	color = vColor;
	gl_Position = MVP * vPosition;
}