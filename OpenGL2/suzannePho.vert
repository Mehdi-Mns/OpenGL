#version 430

in vec4 v_coord;
in vec3 v_normal;
in vec2 v_texcoord;


uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 NM;	//normal matrix
uniform vec3 lpos;
uniform vec4 Ka;
uniform vec4 Kp;
uniform vec4 Ks;
uniform vec3 ads;
uniform int shininess;
uniform vec4 lightColor;
uniform sampler2D tex;		//the currently bound texture

out vec4 vcoord;
out vec3 vnormal;
//out vec4 color;
//out vec2 texcoord;

void main()
{
	// pass texcoord to fragment shader(not used for the moment)
	//texcoord = v_texcoord;
	vcoord = v_coord;
	vnormal=v_normal;
	
	//color =  (ambient+diffuse+spec);//*vec4(abs(N), 1.0f);
	gl_Position = MVP * v_coord;
}