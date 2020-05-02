#define PI 3.141592653589793
#include "MainExercise.h"
#include<iostream>
//#include<GL/glew.h>
#include<GL/glut.h>
#include<glm/glm.hpp>
#include<vector>
#include<algorithm>
#include<random>

#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
/// --- GLOBALS ---
float SW, SH;
glm::mat4 viewMat = glm::lookAt(glm::vec3(5.0, 5.0, 5.0), glm::vec3(0.0), glm::vec3(0.0,1.0,0.0));
glm::mat4 projMat = glm::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 0.5f, -0.5f);
/// ---------------

void MainExercise::init(int windowWidth, int windowHeight) {
	_windowWidth = windowWidth;
	_windowHeight = windowHeight;

	SW = windowWidth;
	SH = windowHeight;
}
void drawFractalRecursively(glm::vec2 A, glm::vec2 B, glm::vec2 C, int depth) {
	glm::vec2 Ap, Bp, Cp;
	
	if (depth > 5) {
		glBegin(GL_LINE_STRIP);

		glVertex2f(A.x, A.y);
		glVertex2f(A.x + (B.x - A.x) / 3.0f, A.y + (B.y - A.y) / 3.0f);
		glVertex2f(C.x, C.y);
		glVertex2f(A.x + 2. * (B.x - A.x) / 3.0f, A.y + 2. * (B.y - A.y) / 3.0f);
		glVertex2f(B.x, B.y);

		glEnd();
		return;
	}

	depth++;

	// ---prvi segment kochine krivulje
	Ap.x = A.x; Ap.y = A.y;
	Bp.x = A.x + (B.x - A.x) / 3.0f;  Bp.y = A.y + (B.y - A.y) / 3.0f;
	Cp.x = A.x + (C.x - A.x) / 3.0f;  Cp.y = A.y + (C.y - A.y) / 3.0f;
	drawFractalRecursively(Ap, Bp, Cp, depth);

	// ---drugi segment kochine krivulje
	Ap.x = Bp.x; Ap.y = Bp.y;
	Bp.x = C.x; Bp.y = C.y;
	Cp.x = A.x + 2.*(C.x-A.x) / 3.;  Cp.y = A.y + 2.*(C.y-A.y) / 3.;
	drawFractalRecursively(Ap, Bp, Cp, depth);

	// ---treci segment kochine krivulje
	Ap.x = Bp.x; Ap.y = Bp.y;
	Bp.x = A.x + 2.*(B.x-A.x) / 3.;  Bp.y = A.y + 2.*(B.y-A.y) / 3.;
	Cp.x = B.x + 2.*(C.x-B.x) / 3.;  Cp.y = B.y + 2.*(C.y-B.y) / 3.;
	drawFractalRecursively(Ap, Bp, Cp, depth);

	// ---cetvrti segment kochine krivulje
	Ap.x = Bp.x; Ap.y = Bp.y;
	Bp.x = B.x; Bp.y = B.y;
	Cp.x = B.x + (C.x-B.x) / 3.;  Cp.y = B.y + (C.y-B.y) / 3.;
	drawFractalRecursively(Ap, Bp, Cp, depth);
}
void drawSnowFlake() {
	//kochina krivulja
	/*glm::vec2 A, B, C;
	A.x = 10.0f; A.y = 200.0f - 10.0f;
	B.x = 320.0f - 10.0f; B.y = 200.0f - 10.0f;
	C.x = (A.x + B.x) / 2.0f; C.y = A.y - sqrt(3) / 2.0f * (B.x - A.x) / 3.0f;*/

	//kochina pahuljica
	glm::vec2 A, B, C;
	double visina, d;

	visina = 200.0 - 20.0f;
	d = sqrt(3.)*visina / 2.0f;

	A.x = 10; A.y = 200 - 10 - visina / 4.;
	B.x = A.x + d; B.y = A.y;
	C.x = (A.x + B.x) / 2.; C.y = A.y + sqrt(3) / 2. * d / 3.;
	drawFractalRecursively(A, B, C, 1);

	B.x = A.x + d / 2.;
	B.y = A.y - d * sqrt(3.) / 2.;
	C.x = (A.x + B.x) / 2. - d / 4.; C.y = (A.y + B.y) / 2. - visina / 4. / 2.;
	drawFractalRecursively(A, B, C, 1);

	A.x = A.x + d;
	C.x = (A.x + B.x) / 2. + d / 4.;
	C.y = (A.y + B.y) / 2. - visina / 4. / 2.;
	drawFractalRecursively(A, B, C, 1);
}
int zaokruzi(double d) {
	if (d >= 0) {
		return (int)(d + 0.5);
	}
	return (int)(d - 0.5);
}
void drawIFSPaprat() {
	// str 297, tablica 13.1
	int limit = 25;
	glPointSize(1);
	glColor3f(0.0f, 0.7f, 0.3f);
	glBegin(GL_POINTS);
	double x0, y0;
	for (int br = 0; br < 200000; br++) {
		x0 = 0; y0 = 0;
		for (int iter = 0; iter < limit; iter++) {
			double x, y; int p = rand() % 100;
			if (p < 1) {
				x = 0; y = 0.16 * y0;
			}
			else if (p < 8) {
				x = 0.2*x0-0.26*y0 + 0;
				y = 0.23 * x0 + 0.22 * y0 + 1.6;
			}
			else if (p < 15) {
				x = -0.15 * x0 + 0.28 * y0 + 0;
				y = 0.26 * x0 + 0.24 * y0 + 0.44;
			}
			else {
				x = 0.85 * x0 + 0.04 * y0 + 0;
				y = -0.04 * x0 + 0.85 * y0 + 1.6;
			}
			x0 = x; y0 = y;
		}
		//std::cout << zaokruzi(x0 * 80 + 300) << " " <<  zaokruzi(y0 * 60) << std::endl;
		glVertex3i(zaokruzi(x0 * 80 + 300), zaokruzi(y0 * 60), 0);
	}
	glEnd();
}
void drawIFSSierpinskiTriangle() {
	// str 298, tablica 13.2
	int limit = 25;
	glPointSize(1);
	glColor3f(0.0f, 0.7f, 0.3f);
	glBegin(GL_POINTS);
	double x0, y0;
	for (int br = 0; br < 200000; br++) {
		x0 = 0; y0 = 0;
		for (int iter = 0; iter < limit; iter++) {
			double x, y; int p = rand() % 100;
			if (p < 33) {
				x = 0.5 * x0;
				y = 0.5 * y0;
			}
			else if (p < 66) {
				x = 0.5 * x0 + 1.28;
				y = 0.5 * y0;
			}
			else {
				x = 0.5 * x0 + 0.64;
				y = 0.5 * y0 + 1.11;
			}
			x0 = x; y0 = y;
		}
		glVertex2i(zaokruzi(x0 * 200 + 50), zaokruzi(y0 * 300));
	}
	glEnd();
}




//std::string rules[] = { "F>F+F--F+F", "NULL" }; //str 302 i 304 general pravilo
//std::string rules[] = { "X>sw[-FX]+FX", "NULL" }; //13.21a
std::string rules[] = { "F>FF-[-F+F+F]+[+F-F-F]", "NULL" }; //13.21b
//std::string rules[] = { "X>sw[-FY]+FX", "Y>FX+FY-FX", "NULL" }; //13.21c
//std::string rules[] = { "F>F[+F]F[-F][F]", "NULL" }; //13.21d
int dubina = 1;
typedef struct {
	double x;
	double y;
	double z;
	double angle;
	double penSize;
	double segmentSize;
} Turtle;
struct CharSequence{
	CharSequence() : data(""), n(0) {}
	CharSequence(std::string Data, int N) :  data(Data), n(N) {}

	std::string data;
	int n;
};

CharSequence* copyOfCharSequence(CharSequence* axiom) {
	CharSequence* copyNew = axiom;
	return copyNew;
}

std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(-1, 1); //doubles from -1 to 1
void moveTurtle(Turtle* turtle, double pomak) {
	turtle->x += pomak*cos(turtle-> angle*PI / 180.0);
	turtle->y += pomak * sin(turtle->angle * PI / 180.0);

	double r = distribution(generator);
	//float r = ((double)rand() / (RAND_MAX));
	turtle->z += r;
	//turtle->z += pomak * cos(turtle->angle * PI / 180.0);
}
std::string pronadiPravilo(char simbol) {
	int i = 0;
	while (true) {
		if (rules[i] == "NULL") {
			return "NULL";
		}
		if (rules[i][0] == simbol)
		{
			return rules[i].substr(2); // get from -> next to the end
		}
		i++;
	}
}
CharSequence lSustav(CharSequence axiom, int dubina) {
	CharSequence niz = axiom;

	for (int i = 0; i < dubina; i++) {
		CharSequence novi; novi.data = " "; novi.n = 0;//(" ", 0); 
		for (int i = 0; i < niz.n; i++) {
			char simbol = niz.data[i];
			std::string pravilo = pronadiPravilo(simbol);
			if (pravilo == "NULL") {
				//charSequenceAdd(novi, simbol);
				novi.data += simbol;
			}
			else {
				//charSequenceAddString(novi, pravilo);
				novi.data += pravilo;
				novi.n = novi.data.size();
			}
		}
		niz = novi;
	}
	return niz;
}
void LinderMayerSystem(){
	double pomak = 500 * pow(1.0 / 3.0, dubina); double angle = 60;
	
	CharSequence axiom; 
	//axiom.data = "F"; // ravno generalno
	axiom.data = "F--F--F"; // pahulja uokvirena
	axiom.n = axiom.data.size();

	CharSequence niz = lSustav(axiom, dubina);

	Turtle turtle; turtle.angle = 0; turtle.x = 50; turtle.y = 150;

	glColor3f(0.0f, 0.1f, 1.0f); glPointSize(1);
	glTranslatef(0.0f, SH / 2.0f, 0.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	for (int i = 0; i < niz.n; i++) {
		
		char simbol = niz.data[i];
		if (simbol == 'F') {
			glBegin(GL_LINES);
			double x0 = turtle.x;
			double y0 = turtle.y;
			moveTurtle(&turtle, pomak);
			double x1 = turtle.x;
			double y1 = turtle.y;
			glVertex2i(zaokruzi(x0), zaokruzi(y0));
			glVertex2i(zaokruzi(x1), zaokruzi(y1));
			glEnd();
		}
		else if (simbol == '+') {
			turtle.angle += angle;
		}
		else if (simbol == '-') {
			turtle.angle -= angle;
		}
		
	}
}

std::vector<glm::vec3> vertices;
glm::vec3 sredisteTijela;
const int BIG_NUM = 100000;
float xmin = BIG_NUM, xmax = -BIG_NUM;
float ymin = BIG_NUM, ymax = -BIG_NUM;
float zmin = BIG_NUM, zmax = -BIG_NUM;
void LinderMayerSystemPrekinuteKrivulje() {
	//double angle = 50; 
	//double angle = 50; // 13.21a
	double angle = 22.5; // 13.21b
	//double angle = 30; // 13.21c
	//double angle = 20; // 13.21d

	CharSequence axiom;
	//axiom.data = "FX"; // 13.21a
	axiom.data = "F";	 // 13.21b
	//axiom.data = "FX";	 // 13.21c
	//axiom.data = "-F";	 // 13.21d
	axiom.n = axiom.data.size();

	CharSequence niz = lSustav(axiom, dubina);

	//double penFactor = 0.7; double segmentFactor = 0.6; // 13.21a
	double penFactor = 0.7; double segmentFactor = 0.6; // 13.21b
	//double penFactor = 0.7; double segmentFactor = 0.65; // 13.21c
	//double penFactor = 0.7; double segmentFactor = 0.65; // 13.21d

	//Turtle turtle; turtle.angle = 0; turtle.x = 300; turtle.y = 10; turtle.penSize = 4; turtle.segmentSize = 40;
	Turtle turtle; turtle.angle = 0; turtle.x = 0; turtle.y = 0; turtle.z = 0; turtle.penSize = 4; turtle.segmentSize = 40;

	glColor3f(0.0f, 0.1f, 1.0f); glPointSize(1);
	//glTranslatef(-SW/2.0f, SH / 2.0f, 0.0f);// 13.21a
	//glTranslatef((-SW / 2.0f) - 75.0f,0.0f, 0.0f);// 13.21a


	//glTranslatef(0.0f, 0.0f, 0.0f);
	//glScalef(0.4f, 0.4f, 0.4f);
	std::vector<Turtle> stackTurtle;
	for (int i = 0; i < niz.n; i++) {
		char simbol = niz.data[i];
		if (simbol == 'F') {
			glLineWidth((float)turtle.penSize);
			glBegin(GL_LINES);
			double x0 = turtle.x;
			double y0 = turtle.y; double z0 = turtle.z;
			moveTurtle(&turtle, turtle.segmentSize);
			double x1 = turtle.x;
			double y1 = turtle.y; double z1 = turtle.z;
			// trebam gurnit u ishodiste
			//glTranslatef(-zaokruzi(x0), -zaokruzi(y0), 0);
			
			glm::vec3 prva = projMat* viewMat* glm::vec4(zaokruzi(x0), zaokruzi(y0), zaokruzi(z0),1.0);
			glm::vec3 druga = projMat * viewMat * glm::vec4(zaokruzi(x1), zaokruzi(y1), zaokruzi(z1), 1.0);
			

			if (dubina == 5) {
				glm::vec3 prva = glm::vec3(zaokruzi(x0), zaokruzi(y0), zaokruzi(z0));
				glm::vec3 druga = glm::vec3(zaokruzi(x1), zaokruzi(y1), zaokruzi(z1));
				vertices.push_back(prva);
				vertices.push_back(druga);
			}
			else {
				glVertex3f(prva.x, prva.y, prva.z);
				glVertex3f(druga.x, druga.y, druga.z);
			}
			//glVertex3i(zaokruzi(x0), zaokruzi(y0), zaokruzi(z0));
			//glVertex3i(zaokruzi(x1), zaokruzi(y1), zaokruzi(z1));
			glEnd();
		}
		else if (simbol == '+') {
			turtle.angle += angle;
		}
		else if (simbol == '-') {
			turtle.angle -= angle;
		}
		else if (simbol == 's') {
			turtle.segmentSize = std::max(1.0, turtle.segmentSize * segmentFactor);
		}
		else if (simbol == 'w') {
			turtle.penSize = std::max(1.0, turtle.penSize * penFactor);
		}
		else if (simbol == '[') {
			stackTurtle.push_back(turtle);
		}
		else if (simbol == ']') {
			turtle = stackTurtle.back();
			stackTurtle.pop_back();
		}
	}
	if (dubina == 5) {
		float sumaX = 0.0f, sumaY = 0.0f, sumaZ = 0.0f;
		for (auto& v : vertices) {
			if (v.x < xmin) xmin = v.x;
			if (v.y < ymin) ymin = v.y;
			if (v.z < zmin) zmin = v.z;

			if (v.x > xmax) xmax = v.x;
			if (v.y > ymax) ymax = v.y;
			if (v.z > zmax) zmax = v.z;

			sumaX += v.x;
			sumaY += v.y;
			sumaZ += v.z;
		}
		float vrojVrhova = float(vertices.size());
		sredisteTijela = glm::vec3(sumaX / vrojVrhova, sumaY / vrojVrhova, sumaZ / vrojVrhova);
		
		float prebaciUIshodiste_data[16] = {
		   1.0f, 0.0f, 0.0f, 0.0f,
		   0.0f, 1.0f, 0.0f, 0.0f,
		   0.0f, 0.0f, 1.0f, 0.0f,
		   -sredisteTijela.x, -sredisteTijela.y, -sredisteTijela.z, 1.0f };
		glm::mat4x4 prebaciUIshodiste = glm::make_mat4x4(prebaciUIshodiste_data);

		int br = 0;
		float x_n, y_n, z_n;
		const float DG = -1.0f; const float GG = 1.0f;
		for (auto& v : vertices) {
			//postaviti u ishodiste
			glm::vec4 transformedVector = glm::transpose(prebaciUIshodiste) * glm::vec4(v.x, v.y, v.z, 1.0f);

			//skaliraj na [-1,1] jer tna taj nacin postizes da mozes prikazat bilo koji .obj
			x_n = (GG - DG) * ((transformedVector.x - xmin) / (xmax - xmin)) + DG;
			y_n = (GG - DG) * ((transformedVector.y - ymin) / (ymax - ymin)) + DG;
			z_n = (GG - DG) * ((transformedVector.z - zmin) / (zmax - zmin)) + DG;

			vertices[br] = glm::vec4(x_n, y_n, z_n, 1.0f);
			br++;
		}
		for (int i = 0; i < vertices.size(); i= i+2) {
			//std::cout << "prva:  " << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << std::endl;
			//std::cout << "druga: " << vertices[i + 1].x<<  " " << vertices[i + 1].y << " " << vertices[i + 1].z << std::endl;
			glBegin(GL_LINES);
			glm::vec3 treca		= projMat * viewMat * glm::vec4(vertices[i],1.0);
			glm::vec3 cetvrta	= projMat * viewMat * glm::vec4(vertices[i+1], 1.0);
			glVertex3f(treca.x, treca.y, treca.z);
			glVertex3f(cetvrta.x, cetvrta.y, cetvrta.z);
			glEnd();
		}
	}
}



struct Complex {
	Complex() {
		this->real = 0.0f; this->imag = 0.0f;
	}
	Complex(float Real, float Imag) : real(Real), imag(Imag) {}
	float real;
	float imag;
};
int limit = 150; // limit je 200 dosta za Slika 13.9
//int limit = 16; // julijev
float umin = 0.0f; float umax = 0.0f;
float vmin = -0.0f; float vmax = 0.0f;

// klascini mandelbrot center(0,0), w=4
float centerX = 0.0f;//-0.7454265f; // centat komplexne ravnine X
float centerY = 0.0f;//0.1130090f; // centat komplexne ravnine Y
float w = 4.0f; // sirina i visina komplexne ravnine
int cnt = 1;
float odmakOdRuba = 30.0f;
int MandelbrotCurveDivergenceTest(Complex c) {

	//Complex c; c.real = 0.13f; c.imag = 0.6;

	// z0 = 0 + 0i
	Complex z_curr; z_curr.real = 0.0f, z_curr.imag = 0.0f;
	
	// sto vise povecam limit to ce manje tocaka biti u mandelbrotovom skupu, odnosno crno
	// tako mogu spojiti dva half islanda
	for (int i = 1; i <= limit; i++) {
		Complex z_next;
		z_next.real = pow(z_curr.real,2) - pow(z_curr.imag,2) + c.real;
		z_next.imag = 2 * z_curr.real * z_curr.imag + c.imag;
		float modulOdZ_next = sqrt(pow(z_next.real, 2) + pow(z_next.imag, 2));
		
		// izvan geomtrijske reprezentacije granice Mandelbrotovog skupa
		if (modulOdZ_next > 2) {
			// utvrdena divergencija, nije unutar skupa, vrati korak u kojem je otkrivena
			return i;
		}
		else {
			z_curr = z_next;
		}
	}

	// svi kompleksni brojevi ispitani do limita su unutar mandelbrotove kruznice
	return -1;
}
void MandelBrotDraw() {
	
	float xmin = 0 + odmakOdRuba; float xmax = SW - odmakOdRuba;
	float ymin = 0 + odmakOdRuba; float ymax = SH - odmakOdRuba;

	umin = centerX - w / 2.0f; 
	umax = centerX + w / 2.0f; // -1,1
	
	vmin = centerY - w / 2.0f;
	vmax = centerY + w / 2.0f; // -1.2,1.2

	glBegin(GL_POINTS);
	for (int i = xmin; i < xmax; i++) {
		for (int j = ymin; j < ymax; j++) {
			Complex c; 
			// c.real je u a ne i, i je piksel u worldu a treba ga preklopiti sa kompleksnom ravninom
			float u = ((i - xmin) / float(xmax - xmin)) * (umax - umin) + umin;
			c.real = u;

			// c.imag je v a ne j, j je piksel u worldu a treba ga preklopiti sa kompleksnom ravninom
			float v = ((j - ymin) / float(ymax - ymin)) * (vmax - vmin) + vmin;
			c.imag = v;
			// ZAKLJUCAK: MandelBrot varira c po pixelima. Vidjet cemo da Julije fiksira c i varira nesto drugo

			// za svaki piksel unutar windowa se ispitiva divergenceTest
			int divStep = MandelbrotCurveDivergenceTest(c);

			if (divStep == -1) {
				glColor3f(1.0f, 1.0f, 0.0f); // pripadaju Mandelbrotovom skupu
			}
			else {
				// divstep je izmedu 0 i 8, limit 8
				glColor3f(	float(divStep) / limit,
							float(divStep) / limit / 2.0f,
							float(divStep) / limit / 3.0f);
			}
			glVertex2i(i, j);
		}
	}
	glEnd();

	// crtaj kompleksnu ravninu [umin->umax, vmin->vmax] crvenom
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glPointSize(3);
		glBegin(GL_LINE_LOOP);
		glm::vec2 V1(umin, vmax/*(vmax - vmin) / 2.0f*/);
		glm::vec2 V2(umin, vmin/*-(vmax - vmin) / 2.0f*/);
		glm::vec2 V3(umax, vmin/*-(vmax - vmin) / 2.0f*/);
		glm::vec2 V4(umax, vmax/*(vmax - vmin) / 2.0f*/);
		// V1.x=u V1.y=v
		float x,y;
		x = ((V1.x - umin) / (umax - umin)) * (xmax - xmin) + xmin;
		y = ((V1.y - vmin) / (vmax - vmin)) * (ymax - ymin) + ymin;
		glVertex2f(x, y);
		x = ((V2.x - umin) / (umax - umin)) * (xmax - xmin) + xmin;
		y = ((V2.y - vmin) / (vmax - vmin)) * (ymax - ymin) + ymin;
		glVertex2f(x, y);
		x = ((V3.x - umin) / (umax - umin)) * (xmax - xmin) + xmin;
		y = ((V3.y - vmin) / (vmax - vmin)) * (ymax - ymin) + ymin;
		glVertex2f(x, y);
		x = ((V4.x - umin) / (umax - umin)) * (xmax - xmin) + xmin;
		y = ((V4.y - vmin) / (vmax - vmin)) * (ymax - ymin) + ymin;
		
		glVertex2f(x, y);
		glEnd();
	}
}




int JulijeCurveDivergenceTest(Complex c, Complex z0) {

	Complex z_curr; 
	z_curr.real = z0.real;
	z_curr.imag = z0.imag;

	for (int i = 1; i <= limit; i++) {
		Complex z_next;
		z_next.real = pow(z_curr.real, 2) - pow(z_curr.imag, 2) + c.real;
		z_next.imag = 2 * z_curr.real * z_curr.imag + c.imag;
		float modulOdZ_next = sqrt(pow(z_next.real, 2) + pow(z_next.imag, 2));

		// izvan geomtrijske reprezentacije granice Julijevog skupa
		if (modulOdZ_next > 2) {
			// utvrdena divergencija, nije unutar skupa, vrati korak u kojem je otkrivena
			return i;
		}
		else {
			z_curr = z_next;
		}
	}

	// svi kompleksni brojevi ispitani do limita su unutar mandelbrotove kruznice
	return -1;
}

int currentJulijeConstantC = 0;
Complex julijeConstants[] =
{
	Complex(0.11, 0.65),
	Complex(-0.67, 0.34),
	Complex(0.179180, 0.58888),
	Complex(0.32, 0.043),
	Complex(-0.807984, -0.145732),
	Complex(-0.500036, -0.520156),
	Complex(0.371588,-0.155767),
	Complex(-0.74543, 0.11301)
};

void JulijeDraw() {
	float xmin = 0 + odmakOdRuba; float xmax = SW - odmakOdRuba;
	float ymin = 0 + odmakOdRuba; float ymax = SH - odmakOdRuba;

	umin = centerX - w / 2.0f;
	umax = centerX + w / 2.0f; // -1,1

	vmin = centerY - w / 2.0f;
	vmax = centerY + w / 2.0f; // -1.2,1.2


	// c je konstantan
	Complex c;
	c = julijeConstants[currentJulijeConstantC];
	//c.real = 0.11; c.imag = 0.65;
	//c.real = -0.67; c.imag = 0.34;
	//c.real = 0.179180; c.imag = 0.58888;
	//c.real = 0.32; c.imag = 0.043;
	//c.real = -0.807984; c.imag = -0.145732;
	//c.real = -0.500036; c.imag = -0.520156;
	//c.real = 0.371588; c.imag = -0.155767;
	//c.real = -0.74543; c.imag = 0.11301;

	glBegin(GL_POINTS);
	for (int i = xmin; i < xmax; i++) {
		for (int j = ymin; j < ymax; j++) {
			
			Complex z0; 
			z0.real = ((i - xmin) / float(xmax - xmin)) * (umax - umin) + umin;
			z0.imag = ((j - ymin) / float(ymax - ymin)) * (vmax - vmin) + vmin;
			// ZAKLJUCAK: Julije fiksira c i varira z0

			// za svaki piksel unutar windowa se ispitiva divergenceTest
			int divStep = JulijeCurveDivergenceTest(c, z0);

			if (divStep == -1) {
				glColor3f(/*(rand() % 100) / 100.0f*/1.0f, 0.9f, 0.1f); // pripadaju Mandelbrotovom skupu
			}
			else {
				// divstep je izmedu 0 i 8, limit 8
				glColor3f(float(divStep) / float(limit),
					float(divStep) / limit / 2.0f,
					float(divStep) / limit / 3.0f);
			}
			glVertex2i(i, j);
		}
	}
	glEnd();

	// crtaj kompleksnu ravninu [umin->umax, vmin->vmax] crvenom
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glPointSize(3);
		glBegin(GL_LINE_LOOP);
		glm::vec2 V1(umin, vmax/*(vmax - vmin) / 2.0f*/);
		glm::vec2 V2(umin, vmin/*-(vmax - vmin) / 2.0f*/);
		glm::vec2 V3(umax, vmin/*-(vmax - vmin) / 2.0f*/);
		glm::vec2 V4(umax, vmax/*(vmax - vmin) / 2.0f*/);
		// V1.x=u V1.y=v
		float x, y;
		x = ((V1.x - umin) / (umax - umin)) * (xmax - xmin) + xmin;
		y = ((V1.y - vmin) / (vmax - vmin)) * (ymax - ymin) + ymin;
		glVertex2f(x, y);
		x = ((V2.x - umin) / (umax - umin)) * (xmax - xmin) + xmin;
		y = ((V2.y - vmin) / (vmax - vmin)) * (ymax - ymin) + ymin;
		glVertex2f(x, y);
		x = ((V3.x - umin) / (umax - umin)) * (xmax - xmin) + xmin;
		y = ((V3.y - vmin) / (vmax - vmin)) * (ymax - ymin) + ymin;
		glVertex2f(x, y);
		x = ((V4.x - umin) / (umax - umin)) * (xmax - xmin) + xmin;
		y = ((V4.y - vmin) / (vmax - vmin)) * (ymax - ymin) + ymin;

		glVertex2f(x, y);
		glEnd();
	}
}
void renderScene() {
	//drawSnowFlake();

	//drawIFSPaprat();
	//drawIFSSierpinskiTriangle();

	//LinderMayerSystem();
	//LinderMayerSystemPrekinuteKrivulje();

	//MandelBrotDraw();
	JulijeDraw();
}


void MainExercise::display() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	renderScene();

	glutSwapBuffers();
}
void MainExercise::reshape(int width, int height) {
	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	

	
	glOrtho(0, GLsizei(width - 1), GLsizei(height - 1), 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}


void MainExercise::OnMouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//empty for now
		dubina++; // LinderMayerovi sustavi
		glutPostRedisplay();
	}
}
const float pomakKamere = 0.05f;
void MainExercise::OnKeyboardClick(unsigned char key, int x, int y) {
	
	if (key == 'd') {
		centerX += pomakKamere/pow(float(cnt),2);
	}
	if (key == 'a') {
		centerX -= pomakKamere/ pow(float(cnt), 2);
	}
	if (key == 'w') {
		centerY -= pomakKamere / pow(float(cnt), 2);
	}
	if (key == 's') {
		centerY += pomakKamere / pow(float(cnt), 2);
	}

	if (key == 'q') {
		// pokusaj da s misem prebacim na intervale [0,screenWidth]->[-1,1] ali lakse se pomicat sa tastaturom
		/*float oldValue = 0.0f + odmakOdRuba;
		float NewMax = 1.0f; float NewMin = -1.0f;
		float OldMax = SW - odmakOdRuba; float OldMin = 0.0f + odmakOdRuba;
		centerX = +((((float(x) - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin);// pribaci sa [0, SW] -> [-1, 1]
		
		OldMax = SH - odmakOdRuba;
		centerY = +((((float(y) - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin);
		std::cout << centerX << " " << centerY << std::endl;*/

		// krivulja n-tog reda u anzivniku, sto je n veci to brze tezi nuli
		// za MandelBrotDraw put like 4, for Julije 1 is perfect...
		w = 1.0 / (pow(float(cnt), 4));
		cnt++;
		std::cout << "w: " << w << std::endl;
	}

	if (key == 'n') {
		currentJulijeConstantC++;
		w = 4.0f;
		cnt = 1;
		if (currentJulijeConstantC == (sizeof(julijeConstants) / sizeof(*julijeConstants))) {
			currentJulijeConstantC = 0;
			/*centerX = 0.0f; centerY = 0.0f;*/
		}
	}
	glutPostRedisplay();
}
void MainExercise::run(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(_windowWidth, _windowHeight);
	glutInitWindowPosition(868, 268);
	glutCreateWindow("Fraktal Geometry");


	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMouseFunc(OnMouseClick);
	glutKeyboardFunc(OnKeyboardClick);

	glutMainLoop();
}