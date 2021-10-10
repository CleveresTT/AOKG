#include "GraphicObject.h"
#include <algorithm>

void GraphicObject::setPosition(glm::vec3 position) {
	modelMatrix = glm::translate(glm::mat4(1.0), position);
}

void GraphicObject::setAngle(float a) {
	modelMatrix = glm::rotate(modelMatrix, a, glm::vec3(0, 1, 0));
}

void GraphicObject::setColor(double r, double g, double b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void GraphicObject::draw(void) {
	glPushMatrix();
	glMultMatrixf(value_ptr(modelMatrix));
	glColor3f(color[0], color[1], color[2]);
	glutWireTeapot(1.0);
	glPopMatrix();
}

/////////////////////////////////

Camera::Camera() {
	radius = 30;
}
Camera::~Camera() {
}
void Camera::simulate(float sec) {
	time = sec;
}

void Camera::setKey(bool left, bool right, bool up, bool down, bool forward, bool backward, bool w, bool a, bool s, bool d, bool q, bool e) {
	Camera::left = left;
	Camera::right = right;
	Camera::up = up;
	Camera::down = down;
	Camera::forward = forward;
	Camera::backward = backward;
	Camera::w = w;
	Camera::a = a;
	Camera::s = s;
	Camera::d = d;
	Camera::q = s;
	Camera::e = d;

	if (w)
		y += 10 * time;

	if (s)
		y += -10 * time;

	if (a)
		x += 10 * time;

	if (d)
		x += -10 * time;

	if (q)
		z += 10 * time;

	if (e)
		z += -10 * time;




	if (left) {
		EyeX += 30 * time;
		x += 30 * time;
	}
		//fi += 90 * time;

	if (right) {
		EyeX -= 30 * time;
		x -= 30 * time;
	}
		//fi += -90 * time;

	if (up && om < 90) {
		EyeY += 30 * time;
		y += 30 * time;
	}
		///om += 90 * time;

	if (down && om > -90) {
		EyeY -= 30 * time;
		y -= 30 * time;
	}
		//om += -90 * time;

	if (forward /*&& radius > 10*/) {
		EyeZ += 30 * time;
		z += 30 * time;
	}
		//radius += -30 * time;

	if (backward /*&& radius < 40*/) {
		EyeZ -= 30 * time;
		z -= 30 * time;
	}
		//radius += 30 * time;
}

void Camera::apply() {
	//float fiRad = fi * 0.017;
	//float omRad = om * 0.017;
	//EyeX = radius * cos(fiRad) * cos(omRad);
	//EyeY = radius * sin(fiRad) * cos(omRad);
	//EyeZ = radius * sin(omRad);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(EyeX, EyeY, EyeZ, x, y, z, 0, 1, 0);
}