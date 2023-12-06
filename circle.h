#pragma once

#include <math.h>
#include "shape.h"
#include "vector.h"

class SCircle : public Shape {
public:
	enum DrawMode {
		CIRCLE_DRAW_MIDPOINT = 0,
		CIRCLE_DRAW_OPENGL,
		CIRCLE_DRAW_NUM,
	};

	constexpr static const char *names[CIRCLE_DRAW_NUM] = {
		"Midpoint",
		"OpenGL",
	};

private:
	Vector2 center;
	float radius;
	DrawMode mode = CIRCLE_DRAW_MIDPOINT;
	static const int segment = 360 * 1;

private:
	void drawMidpointReflected(int x, int y, int xc, int yc) {
		Vector2::draw(x + xc, y + yc);
		Vector2::draw(-x + xc, y + yc);
		Vector2::draw(x + xc, -y + yc);
		Vector2::draw(-x + xc, -y + yc);

		Vector2::draw(y + xc, x + yc);
		Vector2::draw(-y + xc, x + yc);
		Vector2::draw(y + xc, -x + yc);
		Vector2::draw(-y + xc, -x + yc);
	}

	void drawMidpoint() {
		int xc = center.x;
		int yc = center.y;
		int r = radius;

		int x = 0;
		int y = r;

		int p = 1 - r;
		while (x <= y) {
			drawMidpointReflected(x, y, xc, yc);
			x++;
			if (p < 0)
				p += 2 * x + 3;
			else {
				y--;
				p += 2 * x - 2 * y + 1;
			}
		}
	}

	void drawGL() {
		int xc = center.x;
		int yc = center.y;
		int r = radius;

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < segment; i++) {
			float th = i * 2.0 * M_PI / (float)segment;
			float x = xc + r * cos(th);
			float y = yc + r * sin(th);
			Vector2::draw(x, y);
		}
		glEnd();
	}


public:
	SCircle(Vector2 center, float radius) : center(center), radius(radius) {}

	SCircle(Vector2 center, float radius, int mode) : center(center), radius(radius), mode((DrawMode)mode) {}

	void draw() {
		beginDraw();
		switch (mode) {
			case CIRCLE_DRAW_MIDPOINT:
				drawMidpoint();
				break;

			case CIRCLE_DRAW_OPENGL:
				drawGL();
				break;
		}
		endDraw();
	}

	void log() {
		cout << "Drawing: Circle("
			<< center.x << ", "
			<< center.y << ", "
			<< radius << ")\n";
		cout << "Algorithm: " << names[mode] << endl;
		cout << "Time taken: " << drawTime << "ms\n";
		cout << endl;
	}
};