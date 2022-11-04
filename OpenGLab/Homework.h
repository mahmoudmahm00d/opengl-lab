#pragma once
#include "Point.h"

/*
 * All of the drawings in this class will be in X,Y plane
 */
class Homework
{
public:
	static void DrawLine(Point startPoint, Point endPoint);
	static void DrawTriangle(Point pRight, Point pLeft, Point pTop);
	static void DrawRectangle(Point pUpperRight, Point pUpperLeft,
	                          Point pLowerLeft, Point pLowerRight);
	/*
	 * Filled circle, using GL_TRIANGLES mode
	 */
	static void DrawSolidCircle(Point center, float radius);
	static void DrawCircle(Point center, float radius);
	static void DrawArc(Point startPoint, Point endPoint, float radius);
	static void DrawArc(Point center, float radius,
	                    float startAngle, float endAngle);
	static void DrawSineWave(float xStart, float xEnd);
	static void DrawCosineWave(float xStart, float xEnd);
	static void DrawCharacter(Point nose, float bodyLength,
	                          float headRadius, float handLength,
	                          float legLength);
	static void DrawBicycle(Point seatCenterPoint, float wheelRadius,
	                          float distanceBetweenWheels);

};
