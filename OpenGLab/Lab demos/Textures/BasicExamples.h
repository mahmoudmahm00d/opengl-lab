#pragma once
typedef unsigned int GLuint;
typedef float GLfloat;
class GLUquadric;


extern GLfloat xrot; // X Rotation
extern GLfloat yrot; // Y Rotation
extern GLfloat zrot; // Z Rotation

struct BasicExamples
{

	static void DrawSquareNoTexture();
	static void DrawSquareWithTexture(); // change loadNeheTexture to true
	static void DrawSquareUpsideDown(); // change loadNeheTexture to true
	static void SquareWithTexture(GLuint textureId); // change load4Textures to true
	static void ThreeSquaresWithTexutres(GLuint* texturesIds); // change load4Textures to true


	static void CubeExample(GLuint textureId); // change load4Textures to true
	static void EarthExample(GLUquadric* quadric, GLuint textureId); // change loadEarthTexture to true
};
