#include "course.h"

course::course()
{
	//this->number = 0;
	//this->name = "";
	//this->point = 0;
	//this->score = 0;
}

course::course(int number, string name, double point)
{
	this->number = number;
	this->name = name;
	this->point = point;
	this->score = 0;
}
