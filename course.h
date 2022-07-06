#pragma once
#include<string>

using namespace std;

class course
{
public:
	course();
	course(int number, string name, double point);


	int number;		//课程代码
	string name;
	double point;  //学分
	int score;		//成绩


};

