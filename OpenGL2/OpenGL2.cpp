// OpenGL2.cpp : Main OpenGL2 program with shaders, 3D objects and textures.
// This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include<string>
#include <vector>
#include<fstream>
#include<sstream>

using namespace glm;
using namespace std;

// Window parameters
#define TITLE "OpenGL2"
#define BUFFER_OFFSET(offset) ((GLvoid*)(offset))
int SCREEN_X = 1024;
int SCREEN_Y = 768;
int mode = 2;
int cube = 0;
int TIME;
bool text = 0;
bool frame = false;

// Mouse parameters
int X = 0;
int Y = 0;
float zoom = 2.0f;
GLint shininess = 10;

// Lighting parameters
vec3 ads = { 1,1,1 };
vec3 lpos = { 0,0,2 };
vec4 Ka = { 1,0,0,1 };
vec4 Kp = { 0,1,0,1 };
vec4 Ks = { 0,0,1,1 };
vec4 lightColor = { 1,1,1,1 };


// -------------------- OpenGL object handles --------------------

GLuint vaoCube;
GLuint vboCube;
GLuint vaoCube2;
GLuint vboCube2;
GLuint vaoOct;
GLuint vboOct;
GLuint vPosition;
GLuint vColor;
int sp;

GLuint vaoSuzanne;
GLuint vbo_mesh_data;
GLuint vaoSuzanne2;
GLuint vbo_mesh_data2;
GLuint attribute;
vector<GLfloat> suzanne_mesh_data;
vector<GLfloat> suzanne_mesh_data2;

GLuint program;
GLuint programCube;
GLuint programSuz;
GLuint programTex;
GLuint programTexDyn;
GLuint programGou;
GLuint programPho;
GLuint programCel;
GLuint programCelCoul;
GLuint shaderTex;
GLuint shaderPost;
vector<vec4> vPositions;
vector<vec4> vColors;
vector<vec4> vPositions2;
vector<vec4> vColors2;
vector<vec4> vPositionsO;
vector<vec4> vColorsO;

GLuint vaoquad, vboquad;
GLuint framebuffer, renderedTexture, depthrenderbuffer;


// -------------------- Geometry --------------------

vec4 vertices[8] = {
	{-0.5, -0.5, 0.5, 1.0},
	{-0.5, 0.5, 0.5, 1.0},
	{0.5, 0.5, 0.5, 1.0},
	{0.5, -0.5, 0.5, 1.0},
	{-0.5, -0.5, -0.5, 1.0},
	{-0.5, 0.5, -0.5, 1.0},
	{0.5, 0.5, -0.5, 1.0},
	{0.5, -0.5, -0.5, 1.0}
};


vec4 verticesOcta[6] = {
	{0.0, 1.0, 0.0, 1.0},
	{-0.5, 0.0, 0.5, 1.0},
	{0.5, 0.0, 0.5, 1.0},
	{0.5, 0.0, -0.5, 1.0},
	{-0.5, 0.0, -0.5, 1.0},
	{0.0, -1.0, 0.0, 1.0},
};


vec4 colors[8] = {
	{1.0, 0.0, 0.0, 1.0}, //red
	{1.0, 1.0, 0.0, 1.0}, //yellow
	{0.0, 1.0, 0.0, 1.0}, //green
	{0.0, 0.0, 1.0, 1.0}, //blue
	{1.0, 0.0, 1.0, 1.0}, //magenta
	{0.0, 1.0, 1.0, 1.0}, //cyan
	{0.0, 0.0, 0.0, 1.0}, //black
	{1.0, 1.0, 1.0, 1.0}  //white
};


// -------------------- Basic Utilities --------------------

/**
 * @brief Assigns the same color to a cube vertex.
 * @param i Vertex index.
 */
void sameColor(int i) {
	vPositions.push_back(vertices[i]);
	vColors.push_back(colors[i]);
}

/**
 * @brief Assigns a color to a cube face vertex.
 * @param i Vertex index.
 * @param j Color index.
 */
void faceColor(int i, int j) {
	vPositions2.push_back(vertices[i]);
	vColors2.push_back(colors[j]);
}

/**
 * @brief Assigns a color to an octahedron vertex.
 * @param i Vertex index.
 * @param j Color index.
 */
void OctaColor(int i, int j) {
	vPositionsO.push_back(verticesOcta[i]);
	vColorsO.push_back(colors[j]);
}

/**
 * @brief Fills cube buffers with per-vertex color.
 */
void colorCube() {
	sameColor(0);//
	sameColor(1);
	sameColor(2);
	sameColor(0);//
	sameColor(2);
	sameColor(3);
	sameColor(1);//
	sameColor(5);
	sameColor(6);
	sameColor(1);//
	sameColor(6);
	sameColor(2);
	sameColor(0);//
	sameColor(4);
	sameColor(7);
	sameColor(0);//
	sameColor(7);
	sameColor(3);
	sameColor(4);//
	sameColor(5);
	sameColor(1);
	sameColor(4);//
	sameColor(1);
	sameColor(0);
	sameColor(3);//
	sameColor(2);
	sameColor(6);
	sameColor(3);//
	sameColor(6);
	sameColor(7);
	sameColor(4);//
	sameColor(5);
	sameColor(6);
	sameColor(4);//
	sameColor(6);
	sameColor(7);
}

/**
 * @brief Fills cube buffers with per-face color.
 */
void colorCubeFace() {
	faceColor(0, 0);//
	faceColor(1, 0);
	faceColor(2, 0);
	faceColor(0, 0);//
	faceColor(2, 0);
	faceColor(3, 0);
	faceColor(1, 1);//
	faceColor(5, 1);
	faceColor(6, 1);
	faceColor(1, 1);//
	faceColor(6, 1);
	faceColor(2, 1);
	faceColor(0, 2);//
	faceColor(4, 2);
	faceColor(7, 2);
	faceColor(0, 2);//
	faceColor(7, 2);
	faceColor(3, 2);
	faceColor(4, 3);//
	faceColor(5, 3);
	faceColor(1, 3);
	faceColor(4, 3);//
	faceColor(1, 3);
	faceColor(0, 3);
	faceColor(3, 4);//
	faceColor(2, 4);
	faceColor(6, 4);
	faceColor(3, 4);//
	faceColor(6, 4);
	faceColor(7, 4);
	faceColor(4, 5);//
	faceColor(5, 5);
	faceColor(6, 5);
	faceColor(4, 5);//
	faceColor(6, 5);
	faceColor(7, 5);
}

/**
 * @brief Fills octahedron buffers with per-face color.
 */
void colorOcta() {
	OctaColor(0, 0);//
	OctaColor(1, 0);
	OctaColor(2, 0);
	OctaColor(0, 1);//
	OctaColor(2, 1);
	OctaColor(3, 1);
	OctaColor(0, 2);//
	OctaColor(3, 2);
	OctaColor(4, 2);
	OctaColor(0, 3);//
	OctaColor(4, 3);
	OctaColor(1, 3);
	OctaColor(5, 4);//
	OctaColor(1, 4);
	OctaColor(2, 4);
	OctaColor(5, 5);//
	OctaColor(2, 5);
	OctaColor(3, 5);
	OctaColor(5, 6);//
	OctaColor(3, 6);
	OctaColor(4, 6);
	OctaColor(5, 7);//
	OctaColor(4, 7);
	OctaColor(1, 7);
}

/**
 * @brief Reads a shader file and returns its content as a string.
 * @param shaderFile Path to the shader file.
 * @return Shader source string or NULL on failure.
 */
GLchar* readShaderSource(const char * shaderFile)
{
	FILE* fp;
	fopen_s(&fp, shaderFile, "r");
	GLchar* buf;
	long size;
	if (fp == NULL) return NULL;
	fseek(fp, 0L, SEEK_END);			//go to end
	size = ftell(fp);					//getsize
	fseek(fp, 0L, SEEK_SET);			//go to beginning
	buf = (GLchar*)malloc((size + 1) * sizeof(GLchar));
	fread(buf, 1, size, fp);
	buf[size] = 0;
	fclose(fp);
	return buf;
}

/**
 * @brief Compiles and links a GLSL program from vertex and fragment shader files.
 * @param vShaderFile Vertex shader file path.
 * @param fShaderFile Fragment shader file path.
 * @return GLuint program ID.
 */
GLuint initShaders(const char* vShaderFile, const char* fShaderFile)
{
	struct Shader {
		const char* filename;
		GLenum type;
		GLchar* source;
	}

	shaders[2] = {
		{ vShaderFile, GL_VERTEX_SHADER, NULL },
		{ fShaderFile, GL_FRAGMENT_SHADER, NULL }
	};

	GLuint program = glCreateProgram();

	for (int i = 0; i < 2; ++i) {
		Shader& s = shaders[i];
		s.source = readShaderSource(s.filename);

		if (shaders[i].source == NULL) {
			printf("Failed to read %s\n", s.filename);
			exit(EXIT_FAILURE);
		}

		GLuint shader = glCreateShader(s.type);
		glShaderSource(shader, 1, (const GLchar**)&s.source, NULL);
		glCompileShader(shader);
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (!compiled) {
			printf("%s failed to compile:\n", s.filename);
			GLint logSize;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetShaderInfoLog(shader, logSize, NULL, logMsg);
			printf("%s\n", logMsg);
			delete[] logMsg;
			exit(EXIT_FAILURE);
		}

		delete[] s.source;
		glAttachShader(program, shader);
	}

	/* linkand errorcheck */
	glLinkProgram(program);
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked) {
		printf("Shaderprogram failed to link:\n");
		GLint logSize;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
		char* logMsg = new char[logSize];
		glGetProgramInfoLog(program, logSize, NULL, logMsg);
		printf("%s\n", logMsg);
		delete[] logMsg;
		exit(EXIT_FAILURE);
	}
	/* use program object*/
	glUseProgram(program);
	return program;
}

/**
 * @brief Splits a string of format "a/b/c" into indices.
 * @param str Input string.
 * @return Vector of three GLushort indices.
 */
vector<GLushort> splitf(string str) {
	stringstream tosplit(str);
	string segment;
	vector<GLushort> seglist;
	while (getline(tosplit, segment, '/'))
		seglist.push_back(stoi(segment));
	seglist[0]--;
	seglist[1]--;
	seglist[2]--;
	return seglist;
}

/**
 * @brief Loads an OBJ model from file into mesh data.
 * @param filename OBJ file path.
 * @param mesh_data Vector to store vertex/texcoord/normal data.
 * @param mode Normal computation mode (2=per-vertex normals, 3=average).
 */
void load_obj(const char* filename, vector<GLfloat> &mesh_data, int mode) {
	vector<vec4> v;
	vector<vec2> vt;
	vector<vec3> vn;
	vector<vector<GLushort>> f; // [[ , , ], [ , , ], [ , , ], ...]  1face = a/b/c d/e/f g/h/i index des v/vt/vn = 1vertex

	// 1) readfile data into v, vt, vn
	ifstream in(filename, ios::in);
	if (!in) { cerr << "Cannot open " << filename << endl; exit(1); }
	string line;

	while (getline(in, line)) {
		if (line.substr(0, 2) == "v ") { // vertex data
			istringstream s(line.substr(2));
			vec4 v4; s >> v4.x; s >> v4.y; s >> v4.z; v4.w = 1.0f;
			v.push_back(v4);
		}
		else if (line.substr(0, 3) == "vt ") { // texture data
			istringstream s(line.substr(3));
			vec2 v2; s >> v2.x; s >> v2.y;
			vt.push_back(v2);
		}
		else if (line.substr(0, 3) == "vn ") { // normal data
			istringstream s(line.substr(3));
			vec3 v3; s >> v3.x; s >> v3.y; s >> v3.z;
			vn.push_back(v3);
		}
		else if (line.substr(0, 2) == "f ") { // index data
			istringstream s(line.substr(2));
			string str1, str2, str3;
			s >> str1; s >> str2; s >> str3;
			f.push_back(splitf(str1));
			f.push_back(splitf(str2));
			f.push_back(splitf(str3));
		}
	}
	// 2) for each face f, store into mesh_data three consecutive vertices in the form:
	// v.x, v.y, v.z, v.w, vt.u, vt.v,vn.x, vn.y, vn.z
	// Caution: obj lists are indexed starting with 1, your vectors with 0 !


	vector<vector<vec3>> tab;

	if (mode == 3) {
		for (int i = 0; i < v.size(); i++)
			tab.push_back({ vec3(0) });

		//On liste tout les vecteurs normaux en les comptant
		for (int i = 0; i < f.size(); i++) {
			int I = f[i][0];                 //index I de v recupérer dans f
			tab[I].push_back(vn[f[i][2]]);
			tab[I][0].x++;

		}

		//on calcule la moyenne des vecteurs normaux pour chaque vertex
		for (int i = 0; i < tab.size(); i++) {
			vec3 s;
			for (int j = 1; j < tab[i].size(); j++) {
				s += tab[i][j];
			}
			s = s / tab[i][0][0];
			tab[i][0] = s;
		}
	}


	for (int i = 0; i < f.size(); i++) {

		mesh_data.push_back(v[f[i][0]].x);
		mesh_data.push_back(v[f[i][0]].y);
		mesh_data.push_back(v[f[i][0]].z);
		mesh_data.push_back(v[f[i][0]].w);
		mesh_data.push_back(vt[f[i][1]].x);
		mesh_data.push_back(vt[f[i][1]].y);
		if (mode == 2) {
			mesh_data.push_back(vn[f[i][2]].x);
			mesh_data.push_back(vn[f[i][2]].y);
			mesh_data.push_back(vn[f[i][2]].z);
		}
		else if (mode == 3) {
			mesh_data.push_back(tab[f[i][0]][0][0]);
			mesh_data.push_back(tab[f[i][0]][0][1]);
			mesh_data.push_back(tab[f[i][0]][0][2]);
		}

	}


}
 
/**
 * @brief Sets up vertex attributes for cube shader.
 * @param program Shader program ID.
 */
void plumShaderCube(GLuint program) {

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	sp = vPositions.size() * sizeof(glm::vec4);
	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sp));
}

/**
 * @brief Sets up vertex attributes for Suzanne shader.
 * @param program Shader program ID.
 */
void plumShaderSuzanne(GLuint program) {

	attribute = glGetAttribLocation(program, "v_coord"); glEnableVertexAttribArray(attribute);
	glVertexAttribPointer(attribute, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	attribute = glGetAttribLocation(program, "v_texcoord"); glEnableVertexAttribArray(attribute);
	glVertexAttribPointer(attribute, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
	attribute = glGetAttribLocation(program, "v_normal"); glEnableVertexAttribArray(attribute);
	glVertexAttribPointer(attribute, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
}

/**
 * @brief Initializes cube and octahedron geometry and shaders.
 */
void initCubeData() {

	colorCube();
	colorCubeFace();
	colorOcta();
	int sp = vPositions.size() * sizeof(vec4);
	int sc = vColors.size() * sizeof(vec4);
	int spo = vPositionsO.size() * sizeof(vec4);
	int sco = vColorsO.size() * sizeof(vec4);

	programCube = initShaders("passthrought.vert", "passthrought.frag");

	glGenVertexArrays(1, &vaoCube);
	glBindVertexArray(vaoCube);

	glGenBuffers(1, &vboCube);
	glBindBuffer(GL_ARRAY_BUFFER, vboCube);

	glBufferData(GL_ARRAY_BUFFER, sp + sc, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sp, &vPositions[0]);  //load
	glBufferSubData(GL_ARRAY_BUFFER, sp, sc, &vColors[0]);  //load

	plumShaderCube(programCube);

	glGenVertexArrays(1, &vaoCube2);
	glBindVertexArray(vaoCube2);

	glGenBuffers(1, &vboCube2);
	glBindBuffer(GL_ARRAY_BUFFER, vboCube2);

	glBufferData(GL_ARRAY_BUFFER, sp + sc, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sp, &vPositions2[0]);  //load
	glBufferSubData(GL_ARRAY_BUFFER, sp, sc, &vColors2[0]);  //load

	plumShaderCube(programCube);

	glGenVertexArrays(1, &vaoOct);
	glBindVertexArray(vaoOct);

	glGenBuffers(1, &vboOct);
	glBindBuffer(GL_ARRAY_BUFFER, vboOct);

	glBufferData(GL_ARRAY_BUFFER, spo + sco, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, spo, &vPositionsO[0]);  //load
	glBufferSubData(GL_ARRAY_BUFFER, spo, sco, &vColorsO[0]);  //load

	plumShaderCube(programCube);

}

/**
 * @brief Initializes Suzanne mesh data and associated shaders (mode 2).
 */
void initSingeData() {

	// Load OBJ with mode 2 (per-vertex normals)
	load_obj("objet/suzanne.obj", suzanne_mesh_data, 2);

	// Generate VAO for Suzanne
	glGenVertexArrays(1, &vaoSuzanne);
	glBindVertexArray(vaoSuzanne);

	// Generate VBO for mesh data
	glGenBuffers(1, &vbo_mesh_data);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_mesh_data);

	// Upload mesh data
	glBufferData(GL_ARRAY_BUFFER, suzanne_mesh_data.size() * sizeof(GLfloat), &suzanne_mesh_data[0], GL_STATIC_DRAW);

	// Initialize basic Phong shader
	programSuz = initShaders("suzanne.vert", "suzanne.frag");
	//plumShaderSuzanne(programSuz);

	// Initialize basic Gouraud shader
	programGou = initShaders("suzanneGou.vert", "suzanneGou.frag");
	plumShaderSuzanne(programGou);

	// Initialize Phong shader
	programPho = initShaders("suzannePho.vert", "suzannePho.frag");
	//plumShaderSuzanne(programPho);

	// Textured shader
	programTex = initShaders("suzanneTex.vert", "suzanneTex.frag");
	plumShaderSuzanne(programTex);

	// Shader for procedural/dynamic 
	shaderTex = initShaders("shaderTex.vert", "shaderTex.frag");
	plumShaderSuzanne(shaderTex);

	// Dynamic texture shader
	programTexDyn = initShaders("suzanneTexDyn.vert", "suzanneTexDyn.frag");
	plumShaderSuzanne(programTexDyn);

	//shaderPost = initShaders("shaderPost.vert", "shaderPost.frag");
	//plumShaderSuzanne(shaderPost);

}

/**
 * @brief Initializes Suzanne mesh data and shaders (mode 3, averaged normals).
 */
void initSingeData2() {

	// Load OBJ with mode 3 (averaged normals)
	load_obj("objet/suzanne.obj", suzanne_mesh_data2, 3);

	glGenVertexArrays(1, &vaoSuzanne2);
	glBindVertexArray(vaoSuzanne2);

	glGenBuffers(1, &vbo_mesh_data2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_mesh_data2);

	glBufferData(GL_ARRAY_BUFFER, suzanne_mesh_data2.size() * sizeof(GLfloat), &suzanne_mesh_data2[0], GL_STATIC_DRAW);

	// Setup attributes for all shaders
	plumShaderSuzanne(programSuz);
	plumShaderSuzanne(programGou);
	plumShaderSuzanne(programPho);
	plumShaderSuzanne(programTex);

	// Cel-outline shader
	programCel = initShaders("celOutline.vert", "celOutline.frag");
	plumShaderSuzanne(programCel);

	// Cel-color shader
	programCelCoul = initShaders("SuzanneCelCoul.vert", "SuzanneCelCoul.frag");
	plumShaderSuzanne(programCelCoul);
}

/**
 * @brief Basic OpenGL initialization (clear color, projection, depth test).
 */
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glViewport(0, 0, SCREEN_X, SCREEN_Y);
	glEnable(GL_DEPTH_TEST);
}

/**
 * @brief Initializes a fullscreen quad for post-processing or texture display.
 */
void initQuad()
{
	// Generate VAO
	glGenVertexArrays(1, &vaoquad);
	glBindVertexArray(vaoquad);

	// 2D quad vertices
	const GLfloat vertices[] =
	{ -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f };

	// Generate VBO
	glGenBuffers(1, &vboquad);
	glBindBuffer(GL_ARRAY_BUFFER, vboquad);

	// Upload vertices
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
		GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);
}

/**
 * @brief Creates a framebuffer object with color texture and depth buffer.
 * @param X Width.
 * @param Y Height.
 */
void createFrameBuffer(int X, int Y) {

	// creates a framebuffer of size (X,Y) with one color attachment (texture) and a depth buffer
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glGenTextures(1, &renderedTexture);
	glBindTexture(GL_TEXTURE_2D, renderedTexture);
	
	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, X, Y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	// Set "renderedTexture" as our color attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
	
	// The depth buffer
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, X, Y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
	
	// check that framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		fprintf(stderr, "Error creating Framebuffer\n"); exit(EXIT_FAILURE);
	}
}

/**
 * @brief Creates a checkerboard texture.
 * @return Texture ID.
 */
GLuint createTexureChecker() {
	const int CHECKERSIZE = 256;
	float *checkerImage = new float[CHECKERSIZE*CHECKERSIZE * 4]; // RGBA array
	int i, j; float c;

	for (i = 0; i < CHECKERSIZE; i++)
		for (j = 0; j < CHECKERSIZE; j++) {
			c = (((i & 0x8) == 0) ^ ((j & 0x8)) == 0);					// one square = 8 pixels
			checkerImage[4 * (i*CHECKERSIZE + j)] = (GLfloat)c;
			checkerImage[4 * (i*CHECKERSIZE + j) + 1] = (GLfloat)c;
			checkerImage[4 * (i*CHECKERSIZE + j) + 2] = (GLfloat)c;
			checkerImage[4 * (i*CHECKERSIZE + j) + 3] = (GLfloat)1.0f;
		}

	
	GLuint texture;
	glGenTextures(1, &texture); // Generate texture
	glBindTexture(GL_TEXTURE_2D, texture); 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrap mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERSIZE, CHECKERSIZE, 0, GL_RGBA, GL_FLOAT, checkerImage);// Upload image
	glGenerateMipmap(GL_TEXTURE_2D);
	delete[] checkerImage;
	return texture;
}

/**
 * @brief Loads a BMP texture from file.
 * @param filename BMP file path.
 * @param width Width of the image.
 * @param height Height of the image.
 * @return Texture ID.
 */
GLuint loadTextureFromBMP(const char * filename, int width, int height) {
	GLuint texture = 0; unsigned char * data;
	FILE * file; errno_t err;
	if ((err = fopen_s(&file, filename, "rb")) != 0) printf("Error: Texture was not opened.\n");
	else {
		data = (unsigned char *)malloc(width* height * 3);
		fread(data, width* height * 3, 1, file);
		fclose(file);
		for (int i = 0; i < width* height; ++i) { // bmp files are encoded BGR and not RGB
			int index = i * 3; unsigned char B, R;
			B = data[index]; R = data[index + 2];
			data[index] = R; data[index + 2] = B;
		}
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
		free(data);
	}
	return texture;
}


/**
 * @brief Updates model, view, projection, and normal matrices for a given shader program.
 * @param program Shader program ID.
 */
void updateMVP(GLuint program) {
	mat4 Projection = perspective(45.0f, (float)SCREEN_X / (float)SCREEN_Y, 0.1f, 100.0f);
	mat4 View = lookAt(vec3(zoom, 0, zoom),             //où je suis
		vec3(0, 0, 0),            //où je regarde
		vec3(0, 1, 0));			//up et down
	mat4 Model = rotate(rotate(mat4(1.0f), (float)Y / 50, vec3(1, 0, 0)), (float)X / 50, vec3(0, 1, 0));				// translate, rotate, scale
	mat4 MV = View * Model;
	mat4 MVP = Projection * MV;
	mat3 NM = transpose(inverse(mat3(MV)));
	glUniformMatrix4fv(glGetUniformLocation(program, "MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "MV"), 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix3fv(glGetUniformLocation(program, "NM"), 1, GL_FALSE, &NM[0][0]);

	// Upload material and light parameters
	glUniform4fv(glGetUniformLocation(program, "Ka"), 1, &Ka[0]);
	glUniform4fv(glGetUniformLocation(program, "Kp"), 1, &Kp[0]);
	glUniform4fv(glGetUniformLocation(program, "Ks"), 1, &Ks[0]);
	glUniform4fv(glGetUniformLocation(program, "lightColor"), 1, &lightColor[0]);
	glUniform1i(glGetUniformLocation(program, "shininess"), shininess);
	glUniform3fv(glGetUniformLocation(program, "lpos"), 1, &lpos[0]);
	glUniform3fv(glGetUniformLocation(program, "ads"), 1, &ads[0]);

}

// -------------------- Display Functions --------------------

/**
 * @brief Displays cube using current cube shader.
 */
void displayCube()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vaoCube);
	glUseProgram(programCube);
	updateMVP(programCube);

	glDrawArrays(GL_TRIANGLES, 0, vPositions.size());
	glutSwapBuffers();
}

/**
 * @brief Displays second cube variant with per-face color.
 */
void displayCube2()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vaoCube2);
	glUseProgram(programCube);
	updateMVP(programCube);

	glDrawArrays(GL_TRIANGLES, 0, vPositions2.size());
	glutSwapBuffers();
}

/**
 * @brief Displays octahedron with colors.
 */
void displayOcta()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vaoOct);
	glUseProgram(programCube);
	updateMVP(programCube);

	glDrawArrays(GL_TRIANGLES, 0, vPositionsO.size());
	glutSwapBuffers();
}


/**
 * @brief Displays Suzanne mesh with basic shader.
 */
void displaySinge()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programSuz);
	glBindVertexArray(vaoSuzanne);
	updateMVP(programSuz);

	glDrawArrays(GL_TRIANGLES, 0, suzanne_mesh_data.size()/9);
	glutSwapBuffers();
}

/**
 * @brief Displays Suzanne mesh 2 with basic shader.
 */
void displaySinge2()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programSuz);
	glBindVertexArray(vaoSuzanne2);
	updateMVP(programSuz);

	glDrawArrays(GL_TRIANGLES, 0, suzanne_mesh_data2.size() / 9);
	glutSwapBuffers();
}

/**
 * @brief Displays Suzanne mesh with Gouraud shading.
 */
void displaySingeL()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programGou);
	glBindVertexArray(vaoSuzanne);
	updateMVP(programGou);

	glDrawArrays(GL_TRIANGLES, 0, suzanne_mesh_data2.size() / 9);
	glutSwapBuffers();
}

/**
 * @brief Displays Suzanne 2 with Gouraud shading.
 */
void displaySinge2L()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programGou);
	glBindVertexArray(vaoSuzanne2);
	updateMVP(programGou);

	glDrawArrays(GL_TRIANGLES, 0, suzanne_mesh_data2.size() / 9);
	glutSwapBuffers();
}

/**
 * @brief Displays Suzanne 2 with Phong shading.
 */
void displaySinge2LP()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programPho);
	glBindVertexArray(vaoSuzanne2);
	updateMVP(programPho);

	glDrawArrays(GL_TRIANGLES, 0, suzanne_mesh_data2.size() / 9);
	glutSwapBuffers();
}

/**
 * @brief Displays Suzanne with texture.
 */
void displaySingeT()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programTex);
	glBindVertexArray(vaoSuzanne);
	updateMVP(programTex);

	glDrawArrays(GL_TRIANGLES, 0, suzanne_mesh_data2.size() / 9);
	glutSwapBuffers();
}

/**
 * @brief Displays Suzanne with cel shading outline and color fill.
 */
void displaySingeC()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);

	glUseProgram(programCel);
	glBindVertexArray(vaoSuzanne2);
	updateMVP(programCel);
	glDrawArrays(GL_TRIANGLES, 0, suzanne_mesh_data2.size() / 9);

	glEnable(GL_DEPTH_TEST);

	glUseProgram(programCelCoul);
	glBindVertexArray(vaoSuzanne2);
	updateMVP(programCelCoul);
	glDrawArrays(GL_TRIANGLES, 0, suzanne_mesh_data2.size() / 9);

	glutSwapBuffers();
}

/**
 * @brief Displays dynamic texture on quad.
 */
void displayTexture() {
	glViewport(0, 0, SCREEN_X, SCREEN_Y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderTex = initShaders("shaderTex.vert", "shaderTex.frag");
	glUseProgram(shaderTex);

	TIME = glutGet(GLUT_ELAPSED_TIME);
	//cout << TIME << "\n";
	glUniform1f(glGetUniformLocation(shaderTex, "time"), TIME);
	glBindVertexArray(vaoquad);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glutSwapBuffers();

}

/**
 * @brief Displays Suzanne mesh with dynamically updated texture.
 */
void displaySuzanneDyn() {
	if (frame == false) {
		createFrameBuffer(SCREEN_X, SCREEN_Y);
		frame = true;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glViewport(0, 0, SCREEN_X, SCREEN_Y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderTex);
	glBindVertexArray(vaoquad);
	TIME = glutGet(GLUT_ELAPSED_TIME);
	glUniform1f(glGetUniformLocation(shaderTex, "time"), TIME);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// use texture, render to screen
	glViewport(0, 0, SCREEN_X, SCREEN_Y);
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // 0 = screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(programTex);
	glBindVertexArray(vaoSuzanne);
	updateMVP(programTex);
	glBindTexture(GL_TEXTURE_2D, renderedTexture);
	glDrawArrays(GL_TRIANGLES, 0, suzanne_mesh_data2.size() / 9);
	glutSwapBuffers();

}

/**
 * @brief Post-processing display using framebuffer texture.
 */
void displayPost() {
	if (frame == false) {
		createFrameBuffer(SCREEN_X, SCREEN_Y);
		frame = true;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glViewport(0, 0, SCREEN_X, SCREEN_Y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programTex);
	glBindVertexArray(vaoSuzanne);
	updateMVP(programTex);
	glDrawArrays(GL_TRIANGLES, 0, suzanne_mesh_data2.size() / 9);

	// Render framebuffer texture to screen with post-processing shader
	glViewport(0, 0, SCREEN_X, SCREEN_Y);
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // 0 = screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, renderedTexture);
	glUseProgram(shaderPost);
	glBindVertexArray(vaoquad);
	TIME = glutGet(GLUT_ELAPSED_TIME);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glutSwapBuffers();

}


// -------------------- Input Handling --------------------

/**
 * @brief Moves light position with mouse.
 * @param button Mouse button pressed.
 * @param state Button state.
 * @param x Mouse X.
 * @param y Mouse Y.
 */
void moveLight(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
	{
		lpos.x = (((double)x / (double)SCREEN_X) - 0.5)*(SCREEN_X / (float)SCREEN_Y) * 4;
		lpos.y = ((-1)*(((double)y / (double)SCREEN_Y) - 0.5)) * 4;
		updateMVP(program);
	}

}

/**
 * @brief Keyboard event handler for switching modes, adjusting light/material.
 */
void keyboard(unsigned char key, int x, int y)
{
	GLuint attribute;

	switch (key) {
		case 'q': case 27: case 'Q':			// Exit and free all OpenGL resources
			glDeleteBuffers(1, &vboCube);
			glDeleteVertexArrays(1, &vaoCube);
			glDeleteBuffers(1, &vboCube2);
			glDeleteVertexArrays(1, &vaoCube2);
			glDeleteBuffers(1, &vboOct);
			glDeleteVertexArrays(1, &vaoOct);
			glDeleteBuffers(1, &vbo_mesh_data);
			glDeleteVertexArrays(1, &vaoSuzanne);
			glDeleteBuffers(1, &vbo_mesh_data2);
			glDeleteVertexArrays(1, &vaoSuzanne2);
			glDeleteBuffers(1, &vboquad);
			glDeleteVertexArrays(1, &vaoquad);

			glDeleteTextures(1, &renderedTexture);
			glDeleteRenderbuffers(1, &depthrenderbuffer);
			glDeleteFramebuffers(1, &framebuffer);
			exit(0);
			break;

		case '0':								// Switch to dynamic texture display
			mode = 0;
			glutDisplayFunc(displayTexture);
			break;

		case '1':								// Switch between cube variants and octahedron
			mode = 1;
			cube = (cube + 1) % 3;
			if(cube==0)
				glutDisplayFunc(displayCube);
			else if(cube==1)
				glutDisplayFunc(displayCube2);
			else if(cube==2)
				glutDisplayFunc(displayOcta);
			break;

		case '2':								// Basic Suzanne display
			mode = 2;
			glutDisplayFunc(displaySinge);
			break;

		case '3':								// Suzanne with averaged normals
			mode = 3;
			glutDisplayFunc(displaySinge2);
			break;

		case 't':								// Toggle checker texture or BMP texture
			text = !text;
			if(text)
				createTexureChecker();
			else
				loadTextureFromBMP("metal.bmp", 1400, 980);
			ads = { 1,1,1 };
			glutDisplayFunc(displaySingeT);
			break;

		case 'k':								// Switch between Gouraud / Phong shading for Suzanne
			ads = { 1,1,1 };
			glutDisplayFunc(displaySingeL);
			break;

		case 'l':								// Switch between Gouraud / Phong shading for Suzanne
			ads = { 1,1,1 };
			glutDisplayFunc(displaySinge2L);
			break;

		case 'm':								// Switch between Gouraud / Phong shading for Suzanne
			ads = { 1,1,1 };
			glutDisplayFunc(displaySinge2LP);
			break;

		case 'i':								// Update ADS light vector
			ads = { 1,0,0 };
			updateMVP(program);
			break;
		case 'o':								// Update ADS light vector
			ads = { 0,1,0 };
			updateMVP(program);
			break;
		case 'p':								// Update ADS light vector
			ads = { 0,0,1 };
			updateMVP(program);
			break;
		case 'z':								// Adjust ambient, diffuse, specular coefficients
			Ka.x=Ka.x-0.1;
			updateMVP(program);
			break;
		case 'e':								// Adjust ambient, diffuse, specular coefficients
			Ka.x = Ka.x + 0.1;
			updateMVP(program);
			break;
		case 's':								// Adjust ambient, diffuse, specular coefficients
			Kp.y = Kp.y - 0.1;
			updateMVP(program);
			break;
		case 'd':								// Adjust ambient, diffuse, specular coefficients
			Kp.y = Kp.y + 0.1;
			updateMVP(program);
			break;
		case 'x':								// Adjust ambient, diffuse, specular coefficients
			Ks.z = Ks.z - 0.1;
			updateMVP(program);
			break;
		case 'c':								// Adjust ambient, diffuse, specular coefficients
			Ks.z = Ks.z + 0.1;
			updateMVP(program);
			break;
		case '7':								// Adjust shininess -
			shininess = shininess - 1;
			updateMVP(program);
			break;
		case '9':								// Adjust shininess +
			shininess = shininess + 1;
			updateMVP(program);
			break;
		case 'a':								// Zoom in
			zoom = zoom + 0.1;
			cout << zoom << '\n';
			updateMVP(program);
			break;
		case 'w':								// Zoom out
			zoom = zoom - 0.1;
			cout << zoom << '\n';
			updateMVP(program);
			break;
		case '4':								// Cel shading display
			mode = 4;
			glutDisplayFunc(displaySingeC);
			break;

		case '5':								// Suzanne with dynamic texture
			mode = 5;
			glutDisplayFunc(displaySuzanneDyn);
			break;
		case '8':								// Post-processing (currently commented)
			mode = 8;
			//glutDisplayFunc(displayPost);
			break;
	}
}

/**
 * @brief Updates rotation angles based on mouse motion.
 * @param x Mouse X.
 * @param y Mouse Y.
 */
void rotate(int x, int y)
{
	X = x;
	Y = y;
	updateMVP(program);
}

/**
 * @brief GLUT idle function for continuous updates.
 */
void idlefunc() { glutPostRedisplay(); }

/**
 * @brief Main entry point.
 */
int main(int argc, char** argv)
{

	//Initialisation de glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(SCREEN_X, SCREEN_Y);
	glutCreateWindow(TITLE);
	init();


	//Initialisation de glew
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* glewInit failed*/
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Using GLEW %s\n",glewGetString(GLEW_VERSION));
	
	//createFrameBuffer(SCREEN_X, SCREEN_Y);
	initQuad();
	initSingeData();
	initSingeData2();

	initCubeData();
	updateMVP(programCube);
	
	
	glutDisplayFunc(displayCube);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(moveLight);
	glutMotionFunc(rotate);
	glutIdleFunc(idlefunc);
	glutMainLoop();
}

