#pragma once

#include <math.h>
#include "shape.h"
#include "vector.h"

class SParabola : public Shape {
public:
	enum DrawMode {
		PARABOLA_DRAW_MIDPOINT = 0,
		PARABOLA_DRAW_NUM,
	};

	constexpr static const char *names[PARABOLA_DRAW_NUM] = {
		"Midpoint",
	};

private:
	Vector2 vert;
	float dist;
	DrawMode mode = PARABOLA_DRAW_MIDPOINT;
	static const int yEnd = 500;

private:
	void drawMidpointReflected(int x, int y, int xc, int yc, int flip) {
		if (flip) y = -y;
		Vector2::draw(x + xc, y + yc);
		Vector2::draw(-x + xc, y + yc);
	}

	void drawMidpoint() {
		int xc = vert.x;
		int yc = vert.y;
		int d = dist;
		int flip = 0;
		if (d < 0) {
			d = -d;
			flip = 1;
		}

		int x = 0;
		int y = 0;
		int xe = 2 * d;
		int ye = yEnd;

		float p = 1 - 2 * d;
		while (x <= xe) {
			drawMidpointReflected(x, y, xc, yc, flip);
			if (p < 0) {
				p += 2 * x + 3;
			}
			else {
				p += - 4 * d + 2 * x + 3;
				y++;
			}
			x++;
		}

		p = 0.25 - 2 * d;
		while (y <= ye) {
			drawMidpointReflected(x, y, xc, yc, flip);
			if (p < 0) {
				p += 2 * x + 2 - 4 * d;
				x++;
			}
			else {
				p += -4 * d;
			}
			y++;
		}
	} 

public:
	SParabola(Vector2 vert, float dist) : vert(vert), dist(dist) {}

	SParabola(Vector2 vert, float dist, int mode) : vert(vert), dist(dist), mode((DrawMode)mode) {}

	void draw() {
		beginDraw();
		switch (mode) {
			case PARABOLA_DRAW_MIDPOINT:
				drawMidpoint();
				break;
		}
		endDraw();
	}

	void log() {
		cout << "Drawing: Parabola("
			<< vert.x << ", "
			<< vert.y << ", "
			<< dist << ")\n";
		cout << "Algorithm: " << names[mode] << endl;
		cout << "Time taken: " << drawTime << "ms\n";
		cout << endl;
	}
};