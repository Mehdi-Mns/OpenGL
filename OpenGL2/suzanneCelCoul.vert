#version 430

in vec4 v_coord;
in vec3 v_normal;
in vec2 v_texcoord;

uniform mat4 MVP;
uniform mat4 MV;
uniform vec3 lpos;
uniform vec3 ads;
uniform mat3 NM;	//normal matrix
uniform vec4 Ka;
uniform vec4 Kp;
uniform vec4 Ks;
uniform int shininess;
uniform vec4 lightColor;

out vec4 color;
//out vec2 texcoord;

void main()
{
	// pass texcoord to fragment shader(not used for the moment)
	//texcoord = v_texcoord;
	// display normals
	vec3 N = normalize (NM * v_normal);

	vec3 P = mat3(MV) * vec3(v_coord);
	vec3 L = normalize (lpos - P);
	vec3 R = reflect(L,N);
	vec3 V = -normalize(P);

	//Ambient light
	vec4 ambient = Ka * lightColor;
	//Diffuse Light
	vec4 diffuse = Kp * max(dot(N,L),0) * lightColor;
	//Specular light
	vec4 spec = Ks * pow(max(dot(R, V),0),shininess) * lightColor;
	
	color =  (ambient*ads[0]+diffuse*ads[1]+spec*ads[2]);//*vec4(abs(N), 1.0f);
	gl_Position = MVP * v_coord;
}