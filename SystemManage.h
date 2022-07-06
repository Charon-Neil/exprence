#pragma once
#include"student.h"
#include<fstream>
#include<iostream>
#include"course.h"
#include<algorithm>



class SystemManage
{
public:
	SystemManage();

	bool blurFlag;
	vector<student> allStudents;       // �洢����ѧ����Ϣ
	vector<course> mustCourses;			//�洢�����ϼܵĿγ�

	void Menu();
	void loadStudentTxT();
	void loadModuleTxT();	
	void loadScoreTxt();
	void changeBlurFlag();
	course findCourse(string courseName);     //�ӱ��޿γ����ҿγ̣�����¼��ɼ�
	pair<course*, int> findCourse(student& st, string courseName);  //��ѯĳ��ѧ����ĳ���γ�
	pair<student*, int> findStudent(string name);
	void deleteStudent();			// ɾ��ѧ��
	void updateScore();				// �޸ĳɼ�
	void addCourseforStudent();		//��ӿγ̳ɼ�
	void searchStudentScore();		// �����������ҵ���ѧ���ɼ�
	void searchStuScoreFromClass(); // �Ӱ༶����ѧ���ɼ�
	vector<student> searchClass(string classNumber);    // ����ĳ���༶������ѧ�������ص�vector������

	void searchStuScorefromCourse();        // �ӿγ̲�ѯ������ѡ�ε�ѧ���ɼ�

	vector<student> searchCourse(string courseNumber , vector<student> stuVec);// ���ݿγ�����ѯ��ѡ��ѧ�������ص�vector������
	void showStudentAllCourses(student& st);  //��ʾĳ��ѧ�������гɼ�
	void showAllStudentsCourse();      // ��ʾ����ѧ�����пγ̳ɼ�

	void concluClassScore();      // �԰༶����ͳ�Ʒ���
	void concluStudentMsg(vector<student>& stuVec);		  // ��ѧ����ɵ���ѧ�֡�������γ����Լ�δ��ѧ�ֽ���ͳ��

	void saveStuMsg(vector<student> stuVec, course * co = nullptr);   // ����ָ��ѧ�������пγ���Ϣ(ע����������Ǹ���ԭ�ļ�������)
	void saveSingleMsg(student stu, course cou); // ���浥��ѧ���ĵ��ſγ���Ϣ���������ԭ�ļ���׷�ӣ�

	void showFile();   // ���ļ�չʾѧ����Ϣ

	student* blurFindStudent(string partName, vector<student>& stuVec);
	

	vector<string> splitWithStl(const std::string& str, const std::string& pattern);  // ��ָ�����ݷָ��ַ���

	
};

bool pointCompare(const student& st1, const student& st2);	// ��������ѧ�ֽ��бȽ�
bool scoreCompare(const student& st1, const student& st2);	// ���տγ̳ɼ����бȽ�
bool idCompare(const student& st1, const student& st2);//����ѧ������