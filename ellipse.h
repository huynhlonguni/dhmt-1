#pragma once

#include <math.h>
#include "shape.h"
#include "vector.h"

class SEllipse : public Shape {
public:
	enum DrawMode {
		ELLIPSE_DRAW_MIDPOINT = 0,
		ELLIPSE_DRAW_NUM,
	};

	constexpr static const char *names[ELLIPSE_DRAW_NUM] = {
		"Midpoint",
	};

private:
	Vector2 center;
	float major;
	float minor;
	DrawMode mode = ELLIPSE_DRAW_MIDPOINT;


private:
	void drawMidpointReflected(int x, int y, int xc, int yc) {
		Vector2::draw(x + xc, y + yc);
		Vector2::draw(-x + xc, y + yc);
		Vector2::draw(x + xc, -y + yc);
		Vector2::draw(-x + xc, -y + yc);
	}

	void drawMidpoint() {
		int xc = center.x;
		int yc = center.y;
		int a = major / 2;
		int b = minor / 2;
		int a2 = a * a;
		int b2 = b * b;

		int x = 0;
		int y = b;
		int xe = a2 / sqrt(a2 + b2);

		float p = b2 - a2 * b + a2 * 0.25;

		while (x <= xe) {
			drawMidpointReflected(x, y, xc, yc);
			if (p < 0) {
				p += b2 * (2 * x + 3);
			}
			else {
				p += b2 * (2 * x + 3) - a2 * (2 * y - 2);
				y--;
			}
			x++;
		}
		
		p = b2 * (x + 1 / 2) * (x + 1 / 2) + a2 * (y - 1) * (y - 1) - a2 * b2;

		while (y >= 0) {
			drawMidpointReflected(x, y, xc, yc);
			if (p < 0) {
				p += b2 * (2 * x + 2) - a2 * (2 * y - 3);
				x++;
			}
			else {
				p += - a2 * (2 * y - 3);
			}
			y--;
		}
	}

public:
	SEllipse(Vector2 center, float major, float minor)
		: center(center)
		, major(major * 2)
		, minor(minor * 2) {}

	SEllipse(Vector2 center, float major, float minor, int mode)
		: center(center)
		, major(major * 2)
		, minor(minor * 2)
		, mode((DrawMode)mode) {}

	void draw() {
		beginDraw();
		switch (mode) {
			case ELLIPSE_DRAW_MIDPOINT:
				drawMidpoint();
				break;
		}
		endDraw();
	}

	void log() {
		cout << "Drawing: Ellipse("
			<< center.x << ", "
			<< center.y << ", "
			<< major << ", "
			<< minor << ")\n";
		cout << "Algorithm: " << names[mode] << endl;
		cout << "Time taken: " << drawTime << "ms\n";
		cout << endl;
	}
};