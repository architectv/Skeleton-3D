#ifndef SERIALISER_H
#define SERIALISER_H

#include <iostream>
#include "./display/scene.h"

class Serialiser
{
public:
	Serialiser() = delete;
	
	Scene LoadData(std::string);
	void SaveData(Scene, std::string);
};

#endif // SERIALISER_H
