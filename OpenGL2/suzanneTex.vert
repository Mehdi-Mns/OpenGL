#version 430

in vec4 v_coord;
in vec3 v_normal;
in vec2 v_texcoord;

uniform mat4 MVP;
uniform mat4 MV;
uniform vec3 lpos;
uniform mat3 NM;	//normal matrix
uniform vec4 Ka;
uniform vec4 Kp;
uniform vec4 Ks;
//uniform int shininess;
uniform vec4 lightColor;

out vec4 color;
out vec2 texcoord;

void main()
{
	// pass texcoord to fragment shader(not used for the moment)
	texcoord = v_texcoord;
	// display normals
	vec3 N = normalize (NM * v_normal);
	
	color =  vec4(abs(N), 1.0f);
	gl_Position = MVP * v_coord;
}