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
		// ����ת���� ����������ֻ��������
		int choice = atoi(in.c_str());
		
		switch (choice)
		{
		case 0:
			sm.changeBlurFlag();
			break;
		case 1:			// ���ļ��м��ؿγ̳ɼ�
			sm.loadScoreTxt();
			break;
		case 2:			// ��������ɾ��ѧ��
			sm.deleteStudent();
			break;
		case 3:			// �޸ĳɼ�
			sm.updateScore();
			break;
		case 4:			// ��ӿγ̳ɼ�
			sm.addCourseforStudent();
			break;
		case 5:			// ������������ѧ�������гɼ�
			sm.searchStudentScore();
			break;
		case 6:			// ���ݰ༶��������ѧ�������гɼ�
			sm.searchStuScoreFromClass();
			break; 
		case 7:			// ���ݿγ�����������ѧ�������гɼ�
			sm.searchStuScorefromCourse();
			break;
		case 8:			// ��������ѧ���ɼ�
			sm.showAllStudentsCourse();
			break;
		case 9:			// �༶���Ƴɼ�ͳ��
			sm.concluClassScore();
			break;
		case 10:			// չʾ�ļ���Ϣ
			sm.showFile();
			break;
		case -1:
			cout << "ϵͳ���˳�����л����ʹ�ã�" << endl;
			return 0;
		default:
			printf("��������û�иù��ܣ�\n\n");
			system("pause");  //��ͣ
			system("cls");    //����
			break;
		}

		cout << endl;
	}

	
	
	
	return 0;
}