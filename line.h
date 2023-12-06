#pragma once

#include <math.h>
#include "shape.h"
#include "vector.h"

class SLine : public Shape {
public:
	enum DrawMode {
		LINE_DRAW_DDA = 0,
		LINE_DRAW_BRESENHAM,
		LINE_DRAW_OPENGL,
		LINE_DRAW_COUNT
	};

	constexpr static const char *names[LINE_DRAW_COUNT] = {
		"DDA",
		"Bresenham",
		"OpenGL"
	};

private:
	Vector2 p1;
	Vector2 p2;
	DrawMode mode = LINE_DRAW_OPENGL;


private:
	void drawDDA() {
		float x1 = p1.x;
		float y1 = p1.y;
		float x2 = p2.x;
		float y2 = p2.y;
		
		float dx = x2 - x1;
		float dy = y2 - y1;

		int step = abs(dy);
		if (abs(dx) > abs(dy))
			step = abs(dx);

		dx /= step;
		dy /= step;

		float x = x1;
		float y = y1;
		for (int i = 0; i <= step; i++) {
			Vector2::draw((int)round(x), (int)round(y));
			x += dx;
			y += dy;
		}
	}

	void drawBresenhamDX(int x1, int y1, int x2, int y2) {
		int dx = x2 - x1;
		int dy = y2 - y1;

		int yi = 1;
		if (dy < 0) {
			yi = -1;
			dy = -dy;
		}

		int p = 2 * dy - dx;
		int y = y1;

		for (int x = x1; x <= x2; x++) {
			Vector2::draw(x, y);
			if (p > 0) {
				y += yi;
				p += 2 * (dy - dx);
			}
			else {
				p += 2 * dy;
			}
		}
	}

	void drawBresenhamDY(int x1, int y1, int x2, int y2) {
		int dx = x2 - x1;
		int dy = y2 - y1;

		int xi = 1;
		if (dx < 0) {
			xi = -1;
			dx = -dx;
		}

		int p = 2 * dx - dy;
		int x = x1;

		for (int y = y1; y <= y2; y++) {
			Vector2::draw(x, y);
			if (p > 0) {
				x += xi;
				p += 2 * (dx - dy);
			}
			else {
				p += 2 * dx;
			}
		}
	}

	//References: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
	void drawBresenham() {
		int x1 = p1.x;
		int y1 = p1.y;
		int x2 = p2.x;
		int y2 = p2.y;
		
		int dx = x2 - x1;
		int dy = y2 - y1;

		if (abs(dx) > abs(dy)) {
			if (x1 > x2)
				drawBresenhamDX(x2, y2, x1, y1);
			else
				drawBresenhamDX(x1, y1, x2, y2);
		}
		else {
			if (y1 > y2)
				drawBresenhamDY(x2, y2, x1, y1);
			else
				drawBresenhamDY(x1, y1, x2, y2);
		}
	}

	void drawGL() {
		glBegin(GL_LINES);
		glVertex2f(p1.x, p1.y);
		glVertex2f(p2.x, p2.y);
		glEnd();
	}


public:
	SLine(Vector2 p1, Vector2 p2) : p1(p1), p2(p2) {}

	SLine(Vector2 p1, Vector2 p2, int mode) : p1(p1), p2(p2), mode((DrawMode)mode) {}

	void draw() {
		beginDraw();
		switch (mode) {
			case LINE_DRAW_DDA:
				drawDDA();
				break;

			case LINE_DRAW_BRESENHAM:
				drawBresenham();
				break;

			case LINE_DRAW_OPENGL:
				drawGL();
				break;
		}
		endDraw();
	}

	void log() {

		cout << "Drawing: Line("
			<< p1.x << ", "
			<< p1.y << ", "
			<< p2.x << ", "
			<< p2.y << ")\n";
		cout << "Algorithm: " << names[mode] << endl;
		cout << "Time taken: " << drawTime << "ms\n";
		cout << endl;
	}
};