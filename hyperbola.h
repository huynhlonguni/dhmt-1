#pragma once

#include <math.h>
#include "shape.h"
#include "vector.h"

class SHyperbola : public Shape {
public:
	enum DrawMode {
		HYPERBOLA_DRAW_MIDPOINT = 0,
		HYPERBOLA_DRAW_NUM,
	};

	constexpr static const char *names[HYPERBOLA_DRAW_NUM] = {
		"Midpoint",
	};

private:
	Vector2 center;
	float major;
	float minor;
	DrawMode mode = HYPERBOLA_DRAW_MIDPOINT;
	static const int yEnd = 500;

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

		int x = a;
		int y = 0;
		int xe = yEnd;

		float p = -a2 + a * b2 + b2 * 0.25;
		while (y <= b2 * x / a2) {
			drawMidpointReflected(x, y, xc, yc);
			if (p < 0) {
				p += b2 * (2 * x + 2) - a2 * (2 * y + 3);
				x++;
			}
			else {
				p += - a2 * (2 * y + 3);
			}
			y++;
		}

		while (x <= xe) {
			drawMidpointReflected(x, y, xc, yc);
			if (p < 0) {
				p += b2 * (2 * x + 3);
			}
			else {
				p += b2 * (2 * x + 3) - a2 * (2 * y + 2);
				y++;
			}
			x++;
		}

	}

public:
	SHyperbola(Vector2 center, float major, float minor)
		: center(center)
		, major(major)
		, minor(minor) {}

	SHyperbola(Vector2 center, float major, float minor, int mode)
		: center(center)
		, major(major)
		, minor(minor)
		, mode((DrawMode)mode) {}

	void draw() {
		beginDraw();
		switch (mode) {
			case HYPERBOLA_DRAW_MIDPOINT:
				drawMidpoint();
				break;
		}
		endDraw();
	}

	void log() {
		cout << "Drawing: Hyperbola("
			<< center.x << ", "
			<< center.y << ", "
			<< major << ", "
			<< minor << ")\n";
		cout << "Algorithm: " << names[mode] << endl;
		cout << "Time taken: " << drawTime << "ms\n";
		cout << endl;
	}
};