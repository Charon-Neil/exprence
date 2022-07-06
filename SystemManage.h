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
	vector<student> allStudents;       // 存储所有学生信息
	vector<course> mustCourses;			//存储所有上架的课程

	void Menu();
	void loadStudentTxT();
	void loadModuleTxT();	
	void loadScoreTxt();
	void changeBlurFlag();
	course findCourse(string courseName);     //从必修课程里找课程，用于录入成绩
	pair<course*, int> findCourse(student& st, string courseName);  //查询某个学生的某个课程
	pair<student*, int> findStudent(string name);
	void deleteStudent();			// 删除学生
	void updateScore();				// 修改成绩
	void addCourseforStudent();		//添加课程成绩
	void searchStudentScore();		// 根据姓名查找单个学生成绩
	void searchStuScoreFromClass(); // 从班级查找学生成绩
	vector<student> searchClass(string classNumber);    // 查找某个班级的所有学生，返回到vector容器中

	void searchStuScorefromCourse();        // 从课程查询所有已选课的学生成绩

	vector<student> searchCourse(string courseNumber , vector<student> stuVec);// 根据课程名查询所选的学生，返回到vector容器中
	void showStudentAllCourses(student& st);  //显示某个学生的所有成绩
	void showAllStudentsCourse();      // 显示所有学生所有课程成绩

	void concluClassScore();      // 对班级进行统计分析
	void concluStudentMsg(vector<student>& stuVec);		  // 对学生完成的总学分、不及格课程数以及未修学分进行统计

	void saveStuMsg(vector<student> stuVec, course * co = nullptr);   // 保存指定学生的所有课程信息(注意这个保存是覆盖原文件的内容)
	void saveSingleMsg(student stu, course cou); // 保存单条学生的单门课程信息（这个是在原文件上追加）

	void showFile();   // 从文件展示学生信息

	student* blurFindStudent(string partName, vector<student>& stuVec);
	

	vector<string> splitWithStl(const std::string& str, const std::string& pattern);  // 按指定内容分割字符串

	
};

bool pointCompare(const student& st1, const student& st2);	// 按照已修学分进行比较
bool scoreCompare(const student& st1, const student& st2);	// 按照课程成绩进行比较
bool idCompare(const student& st1, const student& st2);//按照学号排序