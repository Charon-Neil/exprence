#pragma once
#include<string>
#include"course.h"
#include<vector>


class student
{
public:
	string name;
	string id;
	string classNum;
	double mustPoint = 50;		// 必修学分
	double alreadyPoint = 0;	// 已修学分
	int failCourseNum = 0;       // 所有不及格课程数
	int tmpCompare;			//用来暂存 比较当们课程的成绩
	vector<course> allCourses;  //该学生所选的所有课程的vector容器

	bool operator==(const student& st);
	bool operator<(const student& st);  


};

