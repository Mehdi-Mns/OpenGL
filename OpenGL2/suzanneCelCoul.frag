#version 430

in vec4 color;
//in vec2 texcoord;

uniform sampler2D tex;		//the currently bound texture

out vec4 fColor;			// final fragment color

void main()
{
	fColor = max(step(0.1,color)*0.1,max(step(0.4,color)*0.4,max(step(0.5,color)*0.5,step(0.9,color)*0.9)));//*texture(tex, texcoord) ;
}