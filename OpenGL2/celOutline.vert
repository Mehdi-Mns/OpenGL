#version 430

in vec4 v_coord;
in vec2 v_texcoord;
in vec3 v_normal;

uniform mat4 MVP;
uniform mat4 MV;
uniform vec3 lpos;
uniform mat3 NM;	//normal matrix

out vec4 color;

void main()
{
	vec3 N = normalize (NM * v_normal);
	vec4 v_coordGonfl = v_coord + vec4(0.1*N, 0);
	// display normals

	vec3 P = mat3(MV) * vec3(v_coord);
	vec3 L = normalize (lpos - P);
	vec3 R = reflect(L,N);
	vec3 V = -normalize(P);
	
	color = vec4(0,0,0,1);
	gl_Position = MVP * v_coordGonfl;
}