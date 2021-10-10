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

void Camera::setKey(bool left, bool right, bool up, bool down, bool forward, bool backward) {
	Camera::left = left;
	Camera::right = right;
	Camera::up = up;
	Camera::down = down;
	Camera::forward = forward;
	Camera::backward = backward;

	if (left) 
		fi += 90 * time;

	if (right) 
		fi += -90 * time;

	if (up && om < 90) 
		om += 90 * time;

	if (down && om > -90) 
		om += -90 * time;

	if (forward && radius > 10) 
		radius += -30 * time;

	if (backward && radius < 40) 
		radius += 30 * time;
}

void Camera::apply() {
	float fiRad = fi * 0.017;
	float omRad = om * 0.017;
	x = radius * cos(fiRad) * cos(omRad);
	z = radius * sin(fiRad) * cos(omRad);
	y = radius * sin(omRad);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
}