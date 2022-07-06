#include<iostream>
#include"SystemManage.h"


int main() {

	SystemManage sm;
	// sm.initSystem();
	
	while (1)
	{
		sm.Menu();
		

		string in;
		cin >> in;
		cout << endl;
		// 这里转整数 限制了输入只能是整型
		int choice = atoi(in.c_str());
		
		switch (choice)
		{
		case 0:
			sm.changeBlurFlag();
			break;
		case 1:			// 从文件中加载课程成绩
			sm.loadScoreTxt();
			break;
		case 2:			// 根据姓名删除学生
			sm.deleteStudent();
			break;
		case 3:			// 修改成绩
			sm.updateScore();
			break;
		case 4:			// 添加课程成绩
			sm.addCourseforStudent();
			break;
		case 5:			// 根据姓名查找学生的所有成绩
			sm.searchStudentScore();
			break;
		case 6:			// 根据班级查找所有学生的所有成绩
			sm.searchStuScoreFromClass();
			break; 
		case 7:			// 根据课程名查找所有学生的所有成绩
			sm.searchStuScorefromCourse();
			break;
		case 8:			// 查找所有学生成绩
			sm.showAllStudentsCourse();
			break;
		case 9:			// 班级单科成绩统计
			sm.concluClassScore();
			break;
		case 10:			// 展示文件信息
			sm.showFile();
			break;
		case -1:
			cout << "系统已退出，感谢您的使用！" << endl;
			return 0;
		default:
			printf("输入有误，没有该功能！\n\n");
			system("pause");  //暂停
			system("cls");    //清屏
			break;
		}

		cout << endl;
	}

	
	
	
	return 0;
}