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
	double mustPoint = 50;		// ����ѧ��
	double alreadyPoint = 0;	// ����ѧ��
	int failCourseNum = 0;       // ���в�����γ���
	int tmpCompare;			//�����ݴ� �Ƚϵ��ǿγ̵ĳɼ�
	vector<course> allCourses;  //��ѧ����ѡ�����пγ̵�vector����

	bool operator==(const student& st);
	bool operator<(const student& st);  


};

