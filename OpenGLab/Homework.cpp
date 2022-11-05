#include "Homework.h"
#include <windows.h>
#include <gl\gl.h>
#include <cmath>

void Homework::DrawLine(Point startPoint, Point endPoint)
{
	glBegin(GL_LINES);
	glVertex2f(startPoint.x, startPoint.y);
	glVertex2f(endPoint.x, endPoint.y);
	glEnd();
}

void Homework::DrawTriangle(Point pRight, Point pLeft, Point pTop)
{
	glBegin(GL_TRIANGLES);
	glVertex3f(pRight.x, pRight.y, pRight.z);
	glVertex3f(pLeft.x, pLeft.y, pLeft.z);
	glVertex3f(pTop.x, pTop.y, pTop.z);
	glEnd();
}

void Homework::DrawRectangle(Point pUpperRight, Point pUpperLeft,
                             Point pLowerLeft, Point pLowerRight)
{
	glBegin(GL_QUADS);
	glVertex3f(pUpperRight.x, pUpperRight.y, pUpperRight.z);
	glVertex3f(pUpperLeft.x, pUpperLeft.y, pUpperLeft.z);
	glVertex3f(pLowerLeft.x, pLowerLeft.y, pLowerLeft.z);
	glVertex3f(pLowerRight.x, pLowerRight.y, pLowerRight.z);
	glEnd();
}

// TODO: IMPLEMENT THE REST OF HOMEWORK.H FUNCTIONS