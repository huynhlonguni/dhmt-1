#pragma once

class Vector2 {
public:
	float x;
	float y;
public:
	Vector2() : x(0), y(0) {}

	Vector2(float x, float y) : x(x), y(y) {}

	static void draw(float x, float y) {
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
	}

	static void draw(int x, int y) {
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
	}
};