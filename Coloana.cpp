#include "Platforma.h"

Platforma::Platforma() {

}
Platforma::Platforma(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, int indexColor) {
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;
	this->indexColor = indexColor;

}

Platforma::~Platforma() {

}