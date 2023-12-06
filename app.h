#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "shape.h"
#include "line.h"
#include "circle.h"
#include "ellipse.h"
#include "parabola.h"
#include "hyperbola.h"
using namespace std;

class App {
private:
	vector<Shape*> shapes;
public:
	App() {
		srand(time(NULL));
	}

	void run() {
		cout << "\n-----Frame-----\n";
		for (int i = 0; i < shapes.size(); i++) {
			shapes[i]->draw();
			shapes[i]->log();
		}
	}

	void loadShapesFromFile(const char *name) {
		ifstream input(name);

		string line;
		while (getline(input, line)) {
			istringstream iss(line);
			int id;
			if (iss >> id) {
				switch (id) {
					case 0: {
						int x1, y1, x2, y2;
						iss >> x1 >> y1 >> x2 >> y2;
						shapes.push_back(new SLine(Vector2(x1, y1), Vector2(x2, y2), SLine::LINE_DRAW_DDA));
						break;
					}
					case 1: {
						int x1, y1, x2, y2;
						iss >> x1 >> y1 >> x2 >> y2;
						shapes.push_back(new SLine(Vector2(x1, y1), Vector2(x2, y2), SLine::LINE_DRAW_BRESENHAM));
						break;
					}
					case 2: {
						int xt, yt, r;
						iss >> xt >> yt >> r;
						shapes.push_back(new SCircle(Vector2(xt, yt), r, SCircle::CIRCLE_DRAW_MIDPOINT));
						break;
					}
					case 3: {
						int xt, yt, a, b;
						iss >> xt >> yt >> a >> b;
						shapes.push_back(new SEllipse(Vector2(xt, yt), a, b, SEllipse::ELLIPSE_DRAW_MIDPOINT));
						break;
					}
					case 4: {
						int xt, yt, p;
						iss >> xt >> yt >> p;
						shapes.push_back(new SParabola(Vector2(xt, yt), p, SParabola::PARABOLA_DRAW_MIDPOINT));
						break;
					}
					case 5: {
						int xt, yt, a, b;
						iss >> xt >> yt >> a >> b;
						shapes.push_back(new SHyperbola(Vector2(xt, yt), a, b, SHyperbola::HYPERBOLA_DRAW_MIDPOINT));
						break;
					}
					case 6: {
						int x1, y1, x2, y2;
						iss >> x1 >> y1 >> x2 >> y2;
						shapes.push_back(new SLine(Vector2(x1, y1), Vector2(x2, y2), SLine::LINE_DRAW_OPENGL));
						break;
					}
					case 7: {
						int xt, yt, r;
						iss >> xt >> yt >> r;
						shapes.push_back(new SCircle(Vector2(xt, yt), r, SCircle::CIRCLE_DRAW_OPENGL));
						break;
					}
				}
			}
		}
	}

	~App() {
		for (int i = 0; i < shapes.size(); i++)
			delete shapes[i];
	}
};