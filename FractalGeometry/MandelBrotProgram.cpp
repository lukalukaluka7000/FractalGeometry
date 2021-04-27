#include "MandelBrotProgram.h"
#include <cmath>

void MandelBrotProgram::init(float w, int SW, int SH, int limit, glm::vec2 center, float odmakOdRuba)
{
	_w = w;
	_SW = SW;
	_SH = SH;
	_limit = limit;
	_center = center;
	_odmakOdRuba = odmakOdRuba;
}
void MandelBrotProgram::prepareOverlapingCoordinatePlanes() 
{
	_uvMin = glm::vec2(_center.x - _w / 2.0f, _center.y - _w / 2.0f);
	_uvMax = glm::vec2(_center.x + _w / 2.0f, _center.y + _w / 2.0f);
}

//struct Complex {
//	Complex() {
//		this->real = 0.0f; this->imag = 0.0f;
//	}
//	Complex(float Real, float Imag) : real(Real), imag(Imag) {}
//	float real;
//	float imag;
//};
//int limit = 150; // limit je 200 dosta za Slika 13.9
////int limit = 16; // julijev
//float umin = 0.0f; float umax = 0.0f;
//float vmin = -0.0f; float vmax = 0.0f;
//
//// klascini mandelbrot center(0,0), w=4
//float centerX = 0.0f;//-0.7454265f; // centat komplexne ravnine X
//float centerY = 0.0f;//0.1130090f; // centat komplexne ravnine Y
//float w = 4.0f; // sirina i visina komplexne ravnine
//int cnt = 1;
//float odmakOdRuba = 30.0f;
//int MandelbrotCurveDivergenceTest(Complex c) {
//
//	//Complex c; c.real = 0.13f; c.imag = 0.6;
//
//	// z0 = 0 + 0i
//	Complex z_curr; z_curr.real = 0.0f, z_curr.imag = 0.0f;
//
//	// sto vise povecam limit to ce manje tocaka biti u mandelbrotovom skupu, odnosno crno
//	// tako mogu spojiti dva half islanda
//	for (int i = 1; i <= limit; i++) {
//		Complex z_next;
//		z_next.real = pow(z_curr.real, 2) - pow(z_curr.imag, 2) + c.real;
//		z_next.imag = 2 * z_curr.real * z_curr.imag + c.imag;
//		float modulOdZ_next = sqrt(pow(z_next.real, 2) + pow(z_next.imag, 2));
//
//		// izvan geomtrijske reprezentacije granice Mandelbrotovog skupa
//		if (modulOdZ_next > 2) {
//			// utvrdena divergencija, nije unutar skupa, vrati korak u kojem je otkrivena
//			return i;
//		}
//		else {
//			z_curr = z_next;
//		}
//	}
//
//	// svi kompleksni brojevi ispitani do limita su unutar mandelbrotove kruznice
//	return -1;
//}
//void MandelBrotDraw() {
//
//	float xmin = 0 + odmakOdRuba; float xmax = SW - odmakOdRuba;
//	float ymin = 0 + odmakOdRuba; float ymax = SH - odmakOdRuba;
//
//	umin = centerX - w / 2.0f;
//	umax = centerX + w / 2.0f; // -1,1
//
//	vmin = centerY - w / 2.0f;
//	vmax = centerY + w / 2.0f; // -1.2,1.2
//
//	glBegin(GL_POINTS);
//	for (int i = xmin; i < xmax; i++) {
//		for (int j = ymin; j < ymax; j++) {
//			Complex c;
//			// c.real je u a ne i, i je piksel u worldu a treba ga preklopiti sa kompleksnom ravninom
//			float u = ((i - xmin) / float(xmax - xmin)) * (umax - umin) + umin;
//			c.real = u;
//
//			// c.imag je v a ne j, j je piksel u worldu a treba ga preklopiti sa kompleksnom ravninom
//			float v = ((j - ymin) / float(ymax - ymin)) * (vmax - vmin) + vmin;
//			c.imag = v;
//			// ZAKLJUCAK: MandelBrot varira c po pixelima. Vidjet cemo da Julije fiksira c i varira nesto drugo
//
//			// za svaki piksel unutar windowa se ispitiva divergenceTest
//			int divStep = MandelbrotCurveDivergenceTest(c);
//
//			if (divStep == -1) {
//				glColor3f(1.0f, 1.0f, 0.0f); // pripadaju Mandelbrotovom skupu
//			}
//			else {
//				// divstep je izmedu 0 i 8, limit 8
//				glColor3f(float(divStep) / limit,
//					float(divStep) / limit / 2.0f,
//					float(divStep) / limit / 3.0f);
//			}
//			glVertex2i(i, j);
//		}
//	}
//	glEnd();
//
//	// crtaj kompleksnu ravninu [umin->umax, vmin->vmax] crvenom
//	{
//		glColor3f(1.0f, 0.0f, 0.0f);
//		glPointSize(3);
//		glBegin(GL_LINE_LOOP);
//		glm::vec2 V1(umin, vmax/*(vmax - vmin) / 2.0f*/);
//		glm::vec2 V2(umin, vmin/*-(vmax - vmin) / 2.0f*/);
//		glm::vec2 V3(umax, vmin/*-(vmax - vmin) / 2.0f*/);
//		glm::vec2 V4(umax, vmax/*(vmax - vmin) / 2.0f*/);
//		// V1.x=u V1.y=v
//		float x, y;
//		x = ((V1.x - umin) / (umax - umin)) * (xmax - xmin) + xmin;
//		y = ((V1.y - vmin) / (vmax - vmin)) * (ymax - ymin) + ymin;
//		glVertex2f(x, y);
//		x = ((V2.x - umin) / (umax - umin)) * (xmax - xmin) + xmin;
//		y = ((V2.y - vmin) / (vmax - vmin)) * (ymax - ymin) + ymin;
//		glVertex2f(x, y);
//		x = ((V3.x - umin) / (umax - umin)) * (xmax - xmin) + xmin;
//		y = ((V3.y - vmin) / (vmax - vmin)) * (ymax - ymin) + ymin;
//		glVertex2f(x, y);
//		x = ((V4.x - umin) / (umax - umin)) * (xmax - xmin) + xmin;
//		y = ((V4.y - vmin) / (vmax - vmin)) * (ymax - ymin) + ymin;
//
//		glVertex2f(x, y);
//		glEnd();
//	}
//}
//
//
//void renderScene() {
//	//drawSnowFlake();
//
//	//drawIFSPaprat();
//	//drawIFSSierpinskiTriangle();
//
//	//LinderMayerSystem();
//	//LinderMayerSystemPrekinuteKrivulje();
//
//	MandelBrotDraw();
//	//JulijeDraw();
//}