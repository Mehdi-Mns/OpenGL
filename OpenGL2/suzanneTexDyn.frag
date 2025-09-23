#version 430

in vec4 color;
in vec2 texcoord;

uniform sampler2D renderedTexture;		//the currently bound texture

out vec4 fColor;			// final fragment color

void main()
{
	fColor =  texture(renderedTexture, texcoord) ;
}