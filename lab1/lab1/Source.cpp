#include <stdio.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h> 
#include "GL/freeglut.h"
#include <vector>

// название окна
char windowName[] = "lab1";

// параметры для функций glutInitWindowPosition и glutInitWindowSize
int windowPositionInt = 200;
int windowSizeInt = 800;

// параметры для функции glutTimerFunc
unsigned int timeBetweenFrames = 20;
int indexOfTimer = 0;

// параметры для функции glViewport
GLint xZero = 0;
GLint yZero = 0;

// параметры для функции gluPerspective
GLdouble yFov = 25.0;
GLdouble zNear = 0.2;
GLdouble zFar = 70.0;

// параметры для функции gluLookAt
GLdouble eyeX = 5;
GLdouble eyeY = 5;
GLdouble eyeZ = 7.5;
GLdouble centerX = 0;
GLdouble centerY = 0;
GLdouble centerZ = 0;
GLdouble upX = 0;
GLdouble upY = 1;
GLdouble upZ = 0;

// размер чайника
GLdouble sizeOfTeapot = 1.0;

// структура, описывающая цвета
struct RGBA_Color {
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
};

// цвета
RGBA_Color white = { 1.0, 1.0, 1.0, 1.0 };
RGBA_Color black = { 0, 0, 0, 1.0 };
RGBA_Color blue = { 0, 0, 1.0, 1.0 };
RGBA_Color red = { 1.0, 0, 0, 1.0 };
RGBA_Color background = { 0.22, 0.88, 0.11, 1.0 };

// массив цветов
std::vector<RGBA_Color> arrayOfColors = { white, black, blue, red };

// индекс текущего цвета в массиве
int indexOfCurrentColor = 0;

//int counter1sec = 0;

// функция вызывается каждые 20 мс
void Simulation(int value) {
	/*
	counter1sec++;
	if (counter1sec == 50) {
		counter1sec = 0;
	 indexOfCurrentColor++;
		if  indexOfCurrentColor == arrayOfColors.size())
		 indexOfCurrentColor = 0;
	}
	*/
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
	// эта же функция будет вызвана еще раз через 20 мс
	glutTimerFunc(timeBetweenFrames, Simulation, indexOfTimer);
}

// функция, вызываемая при изменении размеров окна
void Reshape(int w, int h){
	// установить новую область просмотра, равную всей области окна
	glViewport(xZero, yZero, (GLsizei)w, (GLsizei)h);
	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(yFov, (float)w / h, zNear, zFar);
 indexOfCurrentColor++;
	if  (indexOfCurrentColor == arrayOfColors.size())
	 indexOfCurrentColor = 0;
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void Display(void){
	// отчищаем буфер цвета
	glClearColor(background.r, background.g, background.b, background.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	// выводим объект ‐ красный (1,0,0) чайник
	glColor4f(arrayOfColors [indexOfCurrentColor].r, arrayOfColors [indexOfCurrentColor].g, arrayOfColors [indexOfCurrentColor].b, arrayOfColors [indexOfCurrentColor].a);
	glutWireTeapot(sizeOfTeapot);
	// смена переднего и заднего буферов
	glutSwapBuffers();
};

void KeyboardFunc(unsigned char key, int x, int y) {
	printf("Key code is %i\n", (unsigned int)key);
 indexOfCurrentColor++;
	if  (indexOfCurrentColor == arrayOfColors.size())
	 indexOfCurrentColor = 0;
};

int main(int argc, char* argv[]) {
	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);


	// создание окна:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(windowPositionInt, windowPositionInt);
	// 2. устанавливаем размер окна
	glutInitWindowSize(windowSizeInt, windowSizeInt);
	// 3. создаем окно
	glutCreateWindow(windowName);
	
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(Display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(Reshape);
	// устанавливаем функцию которая будет вызвана через 20 мс
	glutTimerFunc(timeBetweenFrames, Simulation, indexOfTimer);
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(KeyboardFunc);


	// основной цикл обработки сообщений ОС
	glutMainLoop();
}