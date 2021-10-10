#include <stdio.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h> 
#include "GL/freeglut.h"
#include <vector>
#include <string>
#include "GraphicObject.h"
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>

// переменные, необходимые для счета времени между кадрами
LARGE_INTEGER newValueOfCounter, oldValueOfCounter, Frequency;

// функция, которая возвращает время между кадрами
float GetSimulationTime() {
	oldValueOfCounter = newValueOfCounter;
	QueryPerformanceCounter(&newValueOfCounter);
	return 
		float(newValueOfCounter.QuadPart - oldValueOfCounter.QuadPart) / Frequency.QuadPart;
}

// объект камеры
Camera camera;

// позиции
glm::vec3 firstPosition = { 4.0, 0, 0, };
glm::vec3 secondPosition = { -4.0, 0, 0, };
glm::vec3 thirthPosition = { 0, 0, 4.0, };
glm::vec3 fourthPosition = { 0, 0, -4.0, };

// объекты чайников
GraphicObject firstObject;
GraphicObject secondObject;
GraphicObject thirthObject;
GraphicObject fourthObject;

// массив объектов для вывода
const int graphicObjectCount = 4;
GraphicObject graphicObjects[graphicObjectCount] = { firstObject, secondObject, thirthObject, fourthObject };

// название окна
std::string windowName = "lab3 FPS: ";

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
	double r;
	double g;
	double b;
	double a;
};

// цвета
RGBA_Color white = { 1.0, 1.0, 1.0, 1.0 };
RGBA_Color black = { 0, 0, 0, 1.0 };
RGBA_Color blue = { 0, 0, 1.0, 1.0 };
RGBA_Color red = { 1.0, 0, 0, 1.0 };
RGBA_Color green = { 0.22, 0.88, 0.11, 1.0 };

// массив цветов
std::vector<RGBA_Color> arrayOfColors = { white, black, blue, red };

// индекс текущего цвета в массиве
int indexOfCurrentColor = 0;

//int counter1sec = 0;

// функция вызывается как можно чаще
void Simulation()
{
	// ОПРЕДЕЛЕНИЕ ВРЕМЕНИ ПРОШЕДШЕГО С МОМЕНТА ПОСЛЕДНЕЙ СИМУЛЯЦИИ В СЕКУНДАХ
	float simulationTimePassed = GetSimulationTime();
	// вывод FPS в заголовок окна
	glutSetWindowTitle((windowName + std::to_string(1/simulationTimePassed)).c_str());
	// ПЕРЕМЕЩЕНИЕ КАМЕРЫ
	bool CameraLeft = GetAsyncKeyState(VK_LEFT);
	bool CameraRight = GetAsyncKeyState(VK_RIGHT);
	bool CameraUp = GetAsyncKeyState(VK_UP);
	bool CameraDown = GetAsyncKeyState(VK_DOWN);
	bool CameraForward = GetAsyncKeyState(VK_ADD);
	bool CameraBackward = GetAsyncKeyState(VK_SUBTRACT);
	camera.setKey(CameraLeft, CameraRight,
		CameraUp, CameraDown,
		CameraForward, CameraBackward);

	camera.simulate(simulationTimePassed);

	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
};

// функция, вызываемая при изменении размеров окна
void Reshape(int w, int h) {
	// установить новую область просмотра, равную всей области окна
	glViewport(xZero, yZero, (GLsizei)w, (GLsizei)h);
	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(yFov, (float)w / h, zNear, zFar);
	indexOfCurrentColor++;
	if (indexOfCurrentColor == arrayOfColors.size())
		indexOfCurrentColor = 0;
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void Display(void) {
	// отчищаем буфер цвета
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// устанавливаем камеру
	camera.apply();
	// выводим объекты
	for (int i = 0; i < graphicObjectCount; i++) {
		graphicObjects[i].draw();
	};
	// смена переднего и заднего буферов
	glutSwapBuffers();
};

void KeyboardFunc(unsigned char key, int x, int y) {
	printf("Key code is %i\n", (unsigned int)key);
	indexOfCurrentColor++;
	if (indexOfCurrentColor == arrayOfColors.size())
		indexOfCurrentColor = 0;
};

int main(int argc, char* argv[]) {

	// установка цветов чайников
	graphicObjects[0].setColor(white.r, white.g, white.b);
	graphicObjects[1].setColor(red.r, red.g, red.b);
	graphicObjects[2].setColor(blue.r, blue.g, blue.b);
	graphicObjects[3].setColor(green.r, green.g, green.b);

	// установка позиций чайников
	graphicObjects[0].setPosition(firstPosition);
	graphicObjects[1].setPosition(secondPosition);
	graphicObjects[2].setPosition(thirthPosition);
	graphicObjects[3].setPosition(fourthPosition);

	// установка углов поворота чайников
	graphicObjects[0].setAngle(glm::radians(180.0f));
	graphicObjects[1].setAngle(glm::radians(0.0f));
	graphicObjects[2].setAngle(glm::radians(90.0f));
	graphicObjects[3].setAngle(glm::radians(-90.0f));


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
	glutCreateWindow((windowName).c_str());

	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(Display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(Reshape);
	// устанавливаем функцию которая будет вызвана через 20 мс
	glutIdleFunc(Simulation);
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(KeyboardFunc);

	QueryPerformanceCounter(&newValueOfCounter);
	QueryPerformanceFrequency(&Frequency);

	// основной цикл обработки сообщений ОС
	glutMainLoop();
}
