#pragma once
#include <iostream>

#include <Core/Engine.h>

using namespace std;

class Platforma {
public:
	Platforma();
	Platforma(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, int indexColor);
	~Platforma();
	glm::vec3 pos;
	float posX;
	float posY;
	float posZ;
	float scaleX;
	float scaleY;
	float scaleZ;

	int indexColor;
};
