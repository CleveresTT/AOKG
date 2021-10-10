#include <windows.h>
#include "GL/freeglut.h"
#include "math.h"
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//  КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ОДНОГО ГРАФИЧЕСКОГО ОБЪЕКТА
class GraphicObject
{
private:
	// Угол поворота для объекта 
	float angle;
	// Матрица модели (расположение объекта) ‐ чтоб не вычислять каждый раз
	glm::mat4 modelMatrix;
	// Цвет модели
	double color[3];
public:
	// Задать позицию объекта
	void setPosition(glm::vec3 position);
	// Задать угол поворота в градусах относительно оси OY
	void setAngle(float a);
	// Задать цвет модели
	void setColor(double r, double g, double b);
	// Вывести объект
	void draw(void);
};

class Camera
{
private:
	// необходимые свойства
	float radius;
	bool left,
		right,
		up,
		down,
		forward,
		backward,
		w,
		a,
		s,
		d,
		q,
		e;
	float time, 
		x=0, 
		y=0, 
		z=0,
		EyeX=10,
		EyeY=10,
		EyeZ=10,
		fi = 45, 
		om = 45;
public:
	// конструктор по умолчанию
	Camera();
	// деструктор ‐ сохранение новых параметров камеры
	~Camera();
	// установка признаков нажатых клавиш
	void setKey(bool left, bool right, bool up, bool down, bool forward, bool backward, bool w, bool a, bool s, bool d, bool q, bool e);
	// движение камеры в ранее выбранном направлении
	// параметр ‐ количество секунд прошедших с момента последнего вызова
	void simulate(float sec);
	// функция для установки матрицы камеры
	void apply();
};