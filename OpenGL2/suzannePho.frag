#version 430

in vec4 vcoord;
in vec3 vnormal;
//in vec4 color;
//in vec2 texcoord;

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

out vec4 fColor;			// final fragment color

void main()
{
	// display normals
	vec3 N = normalize (NM * vnormal);

	vec3 P = mat3(MV) * vec3(vcoord);
	vec3 L = normalize (lpos - P);
	vec3 R = reflect(L,N);
	vec3 V = -normalize(P);

	//Ambient light
	vec4 ambient = Ka * lightColor;
	//Diffuse Light
	vec4 diffuse = Kp * max(dot(N,L),0) * lightColor;
	//Specular light
	vec4 spec = Ks * pow(max(dot(R, V),0),shininess) * lightColor;

	fColor =   (ambient*ads[0]+diffuse*ads[1]+spec*ads[2]) ;//*texture(tex, texcoord) ;
}