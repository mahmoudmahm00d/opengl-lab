#include "BasicExamples.h"
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <glaux.h>

void BasicExamples::DrawSquareNoTexture()
{
	glTranslated(0, 0, -5);
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();
}

void BasicExamples::DrawSquareWithTexture()
{
	glTranslated(0, 0, -3);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glEnd();
}

/**
 * \brief Map each point of the Rect with the opposite point from the texture
 * = move each texture point 2 steps forward.
 */
void BasicExamples::DrawSquareUpsideDown()
{
	glTranslated(0, 0, -3);
	glBegin(GL_QUADS);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glEnd();
}

void BasicExamples::SquareWithTexture(GLuint textureId)
{
	glTranslatef(0.0f, 0.0f, -5.0f);
	glBindTexture(GL_TEXTURE_2D, textureId);
	DrawSquareWithTexture();
}


void BasicExamples::ThreeSquaresWithTexutres(GLuint* texturesIds)
{
	glTranslatef(0.0f, 0.0f, -5.0f);

	glPushMatrix();
	glTranslated(-3, 0, 0);
	glBindTexture(GL_TEXTURE_2D, texturesIds[0]);
	DrawSquareWithTexture();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 0);
	glBindTexture(GL_TEXTURE_2D, texturesIds[1]);
	DrawSquareWithTexture();
	glPopMatrix();

	glPushMatrix();
	glTranslated(3, 0, 0);
	glBindTexture(GL_TEXTURE_2D, texturesIds[2]);
	DrawSquareWithTexture();
	glPopMatrix();
}


void GlassCubeExample()
{
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0f, 0.0f, 1.0f); // normals are used for lightning
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	// Back Face
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	// Top Face
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	// Bottom Face
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	// Right face
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	// Left Face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
}

static GLfloat xrot; // X Rotation
static GLfloat yrot; // Y Rotation
static GLfloat zrot; // Z Rotation

void BasicExamples::CubeExample(GLuint textureId)
{
	glTranslated(0, 0, -5);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, textureId);
	GlassCubeExample();

	xrot += 3;
	yrot += 2;
	zrot += 4;
}

double t = 0;

void BasicExamples::EarthExample(GLUquadric* quadric, GLuint textureId)
{
	gluQuadricTexture(quadric, GL_TRUE);
	glTranslated(0, 0, -15);
	glRotated(-90, 1, 0, 0); // comment out
	glBindTexture(GL_TEXTURE_2D, textureId);
	glRotated(t, 0, 0, 1);
	gluSphere(quadric, 4, 32, 32);
	t += 3;
}
