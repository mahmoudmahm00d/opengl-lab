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

void Homework::DrawSolidCircle(Point center, float radius)
{
	int steps = 360;
	float theta = 0;
	glBegin(GL_TRIANGLES);
	for (int step = 0; step <= steps; step++)
	{
		float x = center.x + radius * cos(theta);
		float y = center.y + radius * sin(theta);
		glVertex2f(x, y);
		theta = theta + .5;
		x = center.x + radius * cos(theta);
		y = center.y + radius * sin(theta);
		glVertex2f(x, y);
		glVertex2f(center.x, center.y);
		theta = theta + .5;
	}
	glEnd();
}

void Homework::DrawCircle(Point center, float radius)
{
	int steps = 360;
	float theta = 0;
	glBegin(GL_POINTS);
	for (int step = 0; step <= steps; step++)
	{
		float x = center.x + radius * cos(theta);
		float y = center.y + radius * sin(theta);
		glVertex2f(x, y);
		theta = theta + .5;
		x = center.x + radius * cos(theta);
		y = center.y + radius * sin(theta);
		glVertex2f(x, y);
		theta = theta + .5;
	}
	glEnd();
}

void Homework::DrawArc(Point center, float radius, float startAngle, float endAngle)
{
	if (startAngle > endAngle)
	{
		float temp = startAngle;
		startAngle = endAngle;
		endAngle = temp;
	}
	float theta = startAngle;
	glBegin(GL_POINTS);
	for (; theta <= endAngle; theta = theta + .5)
	{
		float x = center.x + radius * cos(theta * 3.14 / 180);
		float y = center.y + radius * sin(theta * 3.14 / 180);
		glVertex2f(x, y);
	}
	glEnd();
}

float M_PI = 3.14f;
int ARC_VERTEX_COUNT = 100;

float NormalizeAngleToSmallestPositive(float angle)
{
	while (angle < 0.0) { angle += M_PI * 2; }
	while (angle >= M_PI * 2) { angle -= M_PI * 2; }
	return angle;
}

void DrawArc_(float angle1, float angle2, float radius,
              float x, float y)
{
	// Prepare angles
	angle1 = NormalizeAngleToSmallestPositive(angle1);
	angle2 = NormalizeAngleToSmallestPositive(angle2);
	if (angle1 > angle2)
	{
		float buffer = angle1;
		angle1 = angle2;
		angle2 = buffer;
	}
	if (0 != angle2 - angle1 > M_PI)
	{
		angle1 += M_PI * 2;
	}

	// Create opengl geometry
	glBegin(GL_POINTS);
	for (int i = 0; i < ARC_VERTEX_COUNT; i++)
	{
		float xx = sin((float)i / (ARC_VERTEX_COUNT - 1) * (angle2 - angle1) + angle1) * radius + x;
		float yy = cos((float)i / (ARC_VERTEX_COUNT - 1) * (angle2 - angle1) + angle1) * radius + y;
		glVertex2f(xx, yy);
	}
	glEnd();
}

void Homework::DrawArc(Point startPoint, Point endPoint, float radius)
{
	float x1 = startPoint.x;
	float y1 = startPoint.y;
	float x2 = endPoint.x;
	float y2 = endPoint.y;
	// distance between points
	float distance = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	// halfway point
	float xAverage = (x1 + x2) / 2.0;
	float yAverage = (y1 + y2) / 2.0;
	// circle center
	float xCenter = sqrt(radius * radius - distance * distance / 4.0) * (y1 - y2) / distance;
	float yCenter = sqrt(radius * radius - distance * distance / 4.0) * (x2 - x1) / distance;
	xCenter = xAverage - xCenter;
	yCenter = yAverage - yCenter;
	// angles
	float angle1 = atan2(x1 - xCenter, y1 - yCenter);
	float angle2 = atan2(x2 - xCenter, y2 - yCenter);
	// create the arc
	DrawArc_(angle1, angle2, radius, xCenter, yCenter);
}


void Homework::DrawSineWave(float xStart, float xEnd)
{
	glBegin(GL_POINTS);
	const float precision = 0.1f;
	float x = xStart;
	while (x < xEnd)
	{
		glVertex2f(x, sin(x));
		x = x + precision;
	}
	glEnd();
}

void Homework::DrawCosineWave(float xStart, float xEnd)
{
	glBegin(GL_POINTS);
	const float precision = 0.1f;
	float x = xStart;
	while (x < xEnd)
	{
		glVertex2f(x, cos(x));
		x = x + precision;
	}
	glEnd();
}

void Homework::DrawCharacter(Point nose, float bodyLength, float headRadius, float handLength, float legLength)
{
	glColor3f(0, 0, 1);
	// Draw nose
	DrawCircle(nose, .2f);

	// Draw mouth
	Point mouth{nose};
	mouth.y -= 1;
	DrawArc(mouth, .5f, 200, 330);

	// Draw left eye + eyebrow
	Point leftEye{nose.x - 1, nose.y + 1};
	DrawCircle(leftEye, .2f);
	leftEye.y += 0.5f;
	DrawArc(leftEye, .3f, 60, 120);

	// Draw right eye
	Point rightEye{nose.x + 1, nose.y + 1};
	DrawCircle(rightEye, .2f);
	rightEye.y += 0.4f;
	DrawArc(rightEye, .3f, 60, 120);
	// Draw head
	DrawCircle(nose, headRadius);

	// Draw body
	Point bodyStart{nose.x, nose.y - headRadius};
	Point bodyEnd{nose.x, nose.y - headRadius - bodyLength};
	DrawLine(bodyStart, bodyEnd);

	// Draw hands
	Point handsStart{bodyStart.x, bodyStart.y - 1};
	Point rightHandEnd{handsStart.x + handLength, handsStart.y - handLength,};
	Point leftHandEnd{handsStart.x - handLength, handsStart.y - handLength,};
	DrawLine(handsStart, rightHandEnd);
	DrawLine(handsStart, leftHandEnd);

	// Draw legs
	Point legsStart{bodyEnd.x, bodyEnd.y};
	Point rightLegEnd{legsStart.x + legLength, legsStart.y - legLength,};
	Point leftLegEnd{legsStart.x - legLength, legsStart.y - legLength,};
	DrawLine(legsStart, rightLegEnd);
	DrawLine(legsStart, leftLegEnd);
}

void Homework::DrawBicycle(Point seatCenterPoint, float wheelRadius, float distanceBetweenWheels)
{
	// Seat
	float seatDim = 0.5f;
	Point seatP1{seatCenterPoint.x - seatDim, seatCenterPoint.y - seatDim};
	Point seatP2{seatCenterPoint.x - seatDim, seatCenterPoint.y + seatDim};
	Point seatP3{seatCenterPoint.x + seatDim + 0.5f, seatCenterPoint.y};
	DrawTriangle(seatP1, seatP2, seatP3);
	Point bottomPointUnderTheSeat{seatCenterPoint.x, seatCenterPoint.y - seatDim - 0.5f};
	DrawLine(seatCenterPoint, bottomPointUnderTheSeat);

	// Horizontal line under the seat
	Point sp{bottomPointUnderTheSeat.x - distanceBetweenWheels, bottomPointUnderTheSeat.y};
	Point ep{bottomPointUnderTheSeat.x + distanceBetweenWheels, bottomPointUnderTheSeat.y};
	DrawLine(sp, ep);

	// Back Wheel
	DrawSolidCircle(Point{sp.x, sp.y - wheelRadius},
	                wheelRadius);
	// Front Wheel
	DrawSolidCircle(Point{ep.x, ep.y - wheelRadius},
	                wheelRadius);

	// Steering Wheel
	Point topP{ ep.x, ep.y + 1 };
	DrawLine(ep, topP);
	DrawLine(topP, Point{topP.x - 0.5f,topP.y - 0.5f, topP.z + 0.5f});
	DrawLine(topP, Point{topP.x - 0.5f,topP.y + 0.5f, topP.z - 0.5f});
}
