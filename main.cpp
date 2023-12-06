#include <GL/glut.h>
#include <iostream>
#include <string.h>
#include "app.h"
using namespace std;

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

App app;
 
void init(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2.0);
	glLineWidth(2.0);

	app.run();
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("%s -i <input file>\n", argv[0]);
		exit(1);
	}

	glutInit(&argc, argv);

	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - SCREEN_WIDTH / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2 - SCREEN_HEIGHT / 2);

	glutCreateWindow("Computer Graphics");

	init();

	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-i") == 0) {
			if (i + 1 < argc)
				app.loadShapesFromFile(argv[i + 1]);
		}
	}

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
