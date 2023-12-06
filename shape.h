#pragma once

#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

class Shape {
protected:
	struct Color {
		float r;
		float g;
		float b;
		float a;
	};

	Color color;

	struct timespec start, end;
	float drawTime = 0;

protected:
	void genColor() {
		color.r = rand() / (float)RAND_MAX;
		color.g = rand() / (float)RAND_MAX;
		color.b = rand() / (float)RAND_MAX;
		color.a = 1.0;
	}

	void beginDraw() {
		glColor4f(color.r, color.g, color.b, color.a);
		clock_gettime(CLOCK_MONOTONIC, &start);
	}

	void endDraw() {
		glFlush();
		clock_gettime(CLOCK_MONOTONIC, &end);
		long long elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
		drawTime = (double)elapsed_ns / 1000000.0;
	}

public:
	Shape() {
		genColor();
	}

	virtual void draw() = 0;

	virtual void log() = 0;
};