#include "SystemManage.h"


SystemManage::SystemManage() {
	blurFlag = false;
	loadStudentTxT(); // ��ʼ��ѧ����Ϣ������ϵͳ¼��ѧ��ѧ����
	loadModuleTxT();  // ��ʼ���γ���Ϣ������ϵͳ�ϼܿγ̣�	
}




void SystemManage::Menu() {
	printf("*************************************************\n");
	printf("   ��ӭʹ��ѧ���ɼ�����ϵͳ@�޼̷�����лcsdn��\n");
	printf("*************************************************\n");
	printf("*\t\t 1.¼��ѧ���ɼ�\t\t\t*\n");
	printf("*\t\t 2.ɾ��ѧ����Ϣ\t\t\t*\n");
	printf("*\t\t 3.�γ̳ɼ��޸�\t\t\t*\n");
	printf("*\t\t 4.��ӿγ̳ɼ�\t\t\t*\n");
	printf("*\t\t 5.��ѯѧ���ɼ�\t\t\t*\n");
	printf("*\t\t 6.���༶��ѯѧ���ɼ�\t\t*\n");
	printf("*\t\t 7.���γ̲�ѯѧ���ɼ�\t\t*\n");
	printf("*\t\t 8.��ѯ����ѧ���ɼ�\t\t*\n");
	printf("*\t\t 9.�༶���Ƴɼ�ͳ��\t\t*\n");
	printf("*\t\t 10.���ļ���ʾ����\t\t*\n");
	printf("*\t\t 0.ģ����ѯ:%s\t\t\t*\n", (blurFlag? "��" :"��"));
	printf("*\t\t-1.�˳���ѯϵͳ\t\t\t*\n");
	printf("*************************************************\n");
	printf("->��ѡ����(��������):");
}


void SystemManage::loadStudentTxT()
{
	ifstream in("./student.txt");
	string filename;
	string line;

	if (in) // �и��ļ�
	{
		getline(in, line); //�ȶ�����һ��������Ϣ
		while (getline(in, line)) // line�в�����ÿ�еĻ��з�
		{
			// cout << line << endl;
			if (line.find('#') == 0)
				break;
			student s;
			vector<string> v1 = splitWithStl(line, "\t");
			s.id = v1[0];
			s.name = v1[1];
			s.classNum = v1[2];

			pair<student*, int> studentPair = findStudent(s.name);
			student* initStu = studentPair.first;
			if (initStu == nullptr) {	//��ʾԭ��û�и�ѧ�����������
				allStudents.push_back(s);
			}
			else {
				if (initStu->id == s.id) {	// ������ͬ��ѧ����ͬ����ͬһ���ˣ�����������

				}
				else	//// ������ͬ��ѧ�Ų�ͬͬ������ͬһ���ˣ���������
				{
					allStudents.push_back(s);
				}
			}

			
		}
		sort(allStudents.begin(), allStudents.end());
	
	}
	else // û�и��ļ�
	{
		cout << "no student.txt file" << endl;
	}
}

void SystemManage::loadModuleTxT()
{
	ifstream in("./module.txt");
	string filename;
	string line;

	if (in) // �и��ļ�
	{
		getline(in, line); //�ȶ�����һ��������Ϣ
		while (getline(in, line)) // line�в�����ÿ�еĻ��з�
		{
			// cout << line << endl;
			if (line.find('#') == 0)
				break;

			vector<string> v1 = splitWithStl(line, "\t");
			int number = atoi(v1[0].c_str());
			double point = atof(v1[2].c_str());
			course c(number, v1[1], point);
			mustCourses.push_back(c);
		}
	}
	else // û�и��ļ�
	{
		cout << "no module.txt file" << endl;
	}

	/*double allScore = 0;
	for( course c : mustCourses)
	{
		cout << c.name << "\t" << c.point << endl;
		allScore += c.point;
	}
	cout << "allScore: " << allScore << endl;*/
}

void SystemManage::loadScoreTxt()
{
	printf("-------------->2.¼��ѧ���ɼ�<---------------\n\n");

	cout << "�Ƿ�ʹ��Ĭ�ϳɼ��ļ���Ĭ��ʹ��score.txt��y/n:" << endl;;
	string sc;
	cin >> sc;
	string path = "./score.txt";
	if (sc == "n") {
		cout << "��������Ҫ¼��ɼ����ļ���";
		cin >> path;
	}
	

	ifstream in(path);
	string filename;
	string line;

	if (in) // �и��ļ�
	{
		cout << "��ʼ¼��ɼ����Ƿ���Ҫ��ӡ¼����?y/n" << endl;
		cin >> sc;
		getline(in, line); //�ȶ�����һ��������Ϣ
		while (getline(in, line)) // line�в�����ÿ�еĻ��з�
		{
			if((sc == "y")||(sc=="Y"))
				cout << line << endl;
			if (line.find('#') == 0)  //ĩ���˳�
				break;
			
			vector<string> v1 = splitWithStl(line, "\t");
			// �ҵ���Ӧ�γ�
			course c = findCourse(v1[2]);
			c.score = atoi(v1[3].c_str());
			// ���������ҵ���Ӧѧ��
			pair<student*, int> pa = findStudent(v1[1]);
			student* st = pa.first;
			int pos = pa.second;
			if (st == nullptr) {
				cout << "ϵͳ���޴�ѧ����" << v1[1] << endl;
				continue;
			}
			else
			{
				//�жϸ�ͬѧ�Ƿ����и��ſγ̣�û������ӣ�������³ɼ�
				pair<course*, int> coursePair = findCourse(*st, c.name);
				if (coursePair.second == -1) {
					allStudents[pos].allCourses.push_back(c);
					if (c.score >= 60) {  // �ÿ�Ŀͨ������ѧ��
						allStudents[pos].alreadyPoint += c.point;
					}
					else {	//���򲻼���γ���+1
						allStudents[pos].failCourseNum += 1;
					}
				}
				else   //�������
				{
					int initScore = coursePair.first->score;
					if (initScore < 60 && c.score >= 60) {
						allStudents[pos].alreadyPoint += c.point;
						allStudents[pos].failCourseNum -= 1;
					}
					else if (initScore >= 60 && c.score < 60) {
						allStudents[pos].alreadyPoint -= c.point;
						allStudents[pos].failCourseNum += 1;
					}
					coursePair.first->score = c.score;  // �����и���
				}
				
			}
			
		}
		
		cout << "----------------�ɼ�¼��ɹ�---------------" << endl;
	}
	else // û�и��ļ�
	{
		cout << "no " << path << " file" << endl;
	}
}

void SystemManage::changeBlurFlag()
{
	this->blurFlag = !this->blurFlag;
	if (blurFlag)
	{
		cout << "**************���ڿ���ʹ��ģ����ѯ**************" << endl;
	}
	else {
		cout << "***************ģ����ѯ�Ѿ��ر�*****************" << endl;
	}

}

course SystemManage::findCourse(string courseName)
{
	for (int i = 0; i < mustCourses.size(); i++) {
		if (courseName == mustCourses[i].name)
			return mustCourses[i];
	}
	// ����ڱ��޿α��Ҳ�������˵�������ڣ��γ̱��Ϊ-1
	course co;
	co.number = -1;
	return co;
}

pair<course*, int> SystemManage::findCourse(student& st, string courseName)
{
	for (int i = 0; i < st.allCourses.size(); i++) {
		if (courseName == st.allCourses[i].name)
			return pair<course*, int>(&(st.allCourses[i]), i);
	}
	return pair<course*, int>(nullptr, -1);
}

pair<student*, int> SystemManage::findStudent(string name)
{
	for (int i = 0; i < allStudents.size(); i++) {
		if (allStudents[i].name == name)
			return pair<student*, int>(&allStudents[i], i);
	}
	return pair<student*, int>(nullptr, -1);
}

void SystemManage::deleteStudent()
{
	printf("---------------->1.ɾ��ѧ����Ϣ<-----------------\n\n");
	student* st = nullptr;
	int pos = -1;
	while(1) {
		cout.setf(ios_base::boolalpha);     // ���ô�ӡbool����
		cout << "��������Ҫɾ����ѧ������(�Ƿ�֧��ģ����ѯ��" << (bool)blurFlag << ")" << endl;
		string name;
		cin >> name;

		if (!blurFlag) {
			pair<student*, int> pa = findStudent(name);
			st = pa.first;
			pos = pa.second;
		}
		else {
			st = blurFindStudent(name, allStudents);
			if (st == nullptr) {
				cout << "���޴���" << endl;
				break;
			}

			pos = st->tmpCompare;
		}

		if (st == nullptr) {
			cout << "���޴���" << endl;
			break;
		}
		else {
			cout << "ѧ��\t\t�༶\t����\t\n";
			cout << st->id << "\t" << st->classNum << "\t" << st->name << endl;
			cout << "��ѯ����������Ϣ����ȷ���Ƿ�ɾ��(y/n)" << endl;
			string re;
			cin >> re;
			if (re == "y") {
				// remove(allStudents.begin(), allStudents.end(), *st);
				allStudents.erase(allStudents.begin() + pos);
				cout << "ɾ���ɹ�" << endl;
			}
			else {
				cout << "��ɾ��" << endl;
			}
			break;
		}
	}
}

void SystemManage::updateScore()
{
	printf("---------------->3.�γ̳ɼ��޸�<-----------------\n\n");
	cout.setf(ios_base::boolalpha);     // ���ô�ӡbool����
	cout << "��������Ҫ�޸ĵ�ѧ������(�Ƿ�֧��ģ����ѯ��" << (bool)blurFlag << ")" << endl;
	string name;
	cin >> name;

	student* st = nullptr;
	if (!blurFlag) {
		pair<student*, int> pa = findStudent(name);
		st = pa.first;
	}
	else
	{
		st = blurFindStudent(name, allStudents);
	}
	

	if (st == nullptr) {
		cout << "���޴���" << endl;
	}
	else {
		if (st->allCourses.size() == 0) {
			cout << "��ʱ�޷��鵽��ѧ���ɼ�,������ϵͳ��δ¼��" << endl;
			return;
		}
		string co;
		string score;
		while (1)
		{
			showStudentAllCourses(*st);
			cout << "��������Ҫ�޸ĵĿ�Ŀ����" << endl;
			cin >> co;
			pair <course*, int> paCourse = findCourse(*st, co); // ע��������Ҫ�õ�ԭ���ݣ���˺��������õ�����
			int pos = paCourse.second;
			if (pos == -1) {
				cout << "û�в鵽: " << co << ",����������γ�����" << endl;
				continue;
			}
			else
			{
				cout << "��������Ҫ�޸ĵķ���" << endl;
				cin >> score;
				course* updataCourse = paCourse.first;
				int initScore = updataCourse->score;     // ��¼��ʼ����
				updataCourse->score = atoi(score.c_str());
				if (initScore >= 60 && updataCourse->score < 60) {     //ԭ�ȹ��ˣ��޸ĺ�û����ѧ�ּ��٣�������γ�+1
					st->alreadyPoint -= updataCourse->point;
					st->failCourseNum += 1;
				}
				else if(initScore < 60 && updataCourse->score >= 60)     // ԭ��û�����޸ĺ���ˣ�ѧ������,������γ�-1
				{
					st->alreadyPoint += updataCourse->point;
					st->failCourseNum -= 1;
				}
				cout << name << "��<<" << co << ">>�޸ĳɹ��������ǣ�" << score << "��" << endl;
				//saveSingleMsg(*st, *updataCourse);  // ѯ���Ƿ񱣴����ļ�
				saveStuMsg(allStudents);
				break;
			}
				
		}
	}
	
}

void SystemManage::addCourseforStudent()
{
	while (1) {
		printf("---------------->4.��ӿγ̳ɼ�<-----------------\n\n");
		cout.setf(ios_base::boolalpha);     // ���ô�ӡbool����
		cout << "��������Ҫ��ӳɼ���ѧ������(�Ƿ�֧��ģ����ѯ��" << (bool)blurFlag << ")" << endl;
		string name;
		cin >> name;

		student* st = nullptr;

		if (!blurFlag) {
			pair<student*, int> pa = findStudent(name);
			st = pa.first;
		}
		else {
			st = blurFindStudent(name, allStudents);
		}

		if (st == nullptr) {
			cout << "���޴���" << endl;
			return;
		}
		else {
			string co;
			string score;
			while (1)
			{
				showStudentAllCourses(*st);
				cout << "��������Ҫ��ӵĿ�Ŀ����" << endl;
				cin >> co;

				course sysCourse = findCourse(co);  // ���ڽ���ϵͳ��ѯ�Ƿ�¼���˸��ſγ�
				if (sysCourse.number == -1) {
					cout << "����ϵͳ��ѯδ¼����ſγ̣����ʧ��" << endl;
					return;
				}

				pair <course*, int> paCourse = findCourse(*st, co); // ����ѧ����ѡ�γ����ѯ�Ƿ����
				int pos = paCourse.second;
				if (pos == -1) {  // ��ʾû�иÿγ̡��������
					cout << "��������ſγ̵ķ�����" << endl;
					cin >> score;
					sysCourse.score = atoi(score.c_str());   //���÷���
					if (sysCourse.score >= 60) {      // ��������ѧ��
						st->alreadyPoint += sysCourse.point;
					}
					else {
						st->failCourseNum += 1;
					}
					st->allCourses.push_back(sysCourse);
					cout << " ��ӿγ�:\t" << sysCourse.name
						<< "\t������: " << sysCourse.score
						<<  endl;
					saveSingleMsg(*st, sysCourse);  // ѯ���Ƿ񱣴����ļ�
					showStudentAllCourses(*st);
					return;
				}
				else
				{
					cout << "�Ѵ��ڸ��ſγ̣������ظ����" << endl;
					return;
				}
			}

		}
	}

}

void SystemManage::searchStudentScore()
{
	printf("-------------->5.��ѯѧ���ɼ�<---------------\n\n");
	cout.setf(ios_base::boolalpha);     // ��ӡbool
	cout << "�������ѯѧ������(�Ƿ�֧��ģ����ѯ��" << (bool)blurFlag << ")" << endl;
	student* st = nullptr;
	string name;
	cin >> name;

	// ��ģ����ѯ
	if (!blurFlag) {
		pair<student*, int> stuPair = findStudent(name);
		st = stuPair.first;
	}
	else // ģ����ѯ
	{
		st = blurFindStudent(name, allStudents);
		
	}

	if (st == nullptr) {
		cout << "���޴���" << endl;
		return;
	}
	// չʾѧ�������пγ���Ϣ
	showStudentAllCourses(*st);
	


}

void SystemManage::searchStuScoreFromClass()
{
	printf("-------------->6.��ѯ�༶����ѧ���ɼ�<-------------\n\n");
	cout << "�������ѯ�İ�ţ�" << endl;
	string cls;
	cin >> cls;

	vector<student> rec = searchClass(cls);
	if (rec.size() == 0) {
		cout << "ϵͳ�����ڴ˰༶�������Ƿ�������ȷ" << endl;
	}
	sort(rec.begin(), rec.end(), pointCompare);
	for (student stu : rec) {
		showStudentAllCourses(stu);
	}

	// ѡ���Ƿ񱣴����ļ���
	saveStuMsg(rec);
	
}

vector<student> SystemManage::searchClass(string classNumber)
{
	vector<student> rec;
	for (student st : allStudents) {
		if (st.classNum == classNumber)
			rec.push_back(st);
	}
	return rec;
}

 void SystemManage::searchStuScorefromCourse()
{
	printf("------------->7.��ѯ�γ�����ѧ���ɼ�<-------------\n\n");
	cout << "�������ѯ�Ŀγ����ƣ�" << endl;
	string courseName;
	cin >> courseName;

	// �жϽ���ϵͳ���Ƿ��и��ſγ�
	course cou = findCourse(courseName);
	if (cou.number == -1) {
		cout << "ϵͳ�����ڴ˿γ̣������Ƿ�������ȷ" << endl;
		return;
	}

	// ����ѡ��ѧ����Ȼ�����
	vector<student> stuVec = searchCourse(courseName, allStudents);
	if (stuVec.size() == 0) {
		cout << "��ʱû����ѡ�����Ŀγ��أ������Ժ��ٲ�ѯ" << endl;
	}
	sort(stuVec.begin(), stuVec.end(), scoreCompare);
	cout << endl << "ѧ��\t\t" << " �༶\t" << " ����\t" << " �ɼ�\t" << endl;
	for (student stu : stuVec) {		
		cout << stu.id << "\t"
			 << stu.classNum << "\t"
			 << stu.name << "\t"
			 << stu.tmpCompare << endl;
			 
	}

	saveStuMsg(stuVec, &cou);
	return;
	
}

vector<student> SystemManage::searchCourse(string courseNumber, vector<student> stuVec)
{
	vector<student> rec;
	for (student stu : stuVec) {
		for (course cou : stu.allCourses) {
			if (cou.name == courseNumber) {  // �����ѧ����������ѡ�γ��а������ſΣ�����룬Ȼ���������ж���һ��ѧ��
				stu.tmpCompare = cou.score;   // ��¼��ͳ�Ƶĵ�ǰ�γ̵ĳɼ�
				rec.push_back(stu);
				break;
			}
		}
	}
	return rec;
}

void SystemManage::showStudentAllCourses(student& st)
{
	if (st.allCourses.size() == 0) {
		cout << "��ʱ��ѯ���� " << st.name << " �ĳɼ���������ϵͳ��δ¼��" << endl;
		return;
	}

	cout << endl  << "ѧ�ţ�" <<	st.id 
				  << " �༶��" << st.classNum
				  << " ������" << st.name   
				  << " ����ѧ�֣�" << st.alreadyPoint 
				  << " �ɼ����£�" << endl;
	cout << "�γ̱��\t�γ�����\t\t�γ�ѧ��\t\t�γ̳ɼ�" << endl;
	for (int i = 0; i < st.allCourses.size(); i++) {
		cout << st.allCourses[i].number << "\t"
			 << st.allCourses[i].name << "\t\t"
			<< st.allCourses[i].point << "\t\t\t"
			 << st.allCourses[i].score << "\t"
			 << endl;
	}
	cout << "**********************************************************" << endl;
}

void SystemManage::showAllStudentsCourse()
{
	printf("--------------->8.��ѯ����ѧ���ɼ�<---------------\n\n");
	sort(allStudents.begin(), allStudents.end(), pointCompare); //����ѧ�ֽ�������
	for (int i = 0; i < allStudents.size(); i++) {
		showStudentAllCourses(allStudents[i]);
		cout << endl;
	}

	// ѡ���Ƿ񱣴����ļ���
	saveStuMsg(allStudents);
	//
	concluStudentMsg(allStudents);
}

void SystemManage::concluClassScore()
{
	printf("---------------->9.�༶����ͳ��<-------------------\n\n");
	cout << "�������ͳ�Ƶİ༶��" << endl;
	string className;
	cin >> className;
	vector<student> rec = searchClass(className);
	// �ж����޸ð༶
	if (rec.size() == 0) {
		cout << "ϵͳ�����ڴ˰༶�������Ƿ�������ȷ" << endl;
		return;
	}

	cout << "������ͳ�Ƶĵ��ƿγ����ƣ�" << endl;
	string courseName;
	cin >> courseName;
	// �жϽ���ϵͳ���Ƿ��и��ſγ�
	course cou = findCourse(courseName);
	if (cou.number == -1) {
		cout << "ϵͳ�����ڴ˿γ̣������Ƿ�������ȷ" << endl;
		return;
	}

	// ͳ�Ƹð༶ѡ����ſγ̵�����
	vector<student> stuSelectCourse = searchCourse(courseName, rec);
	// ���û��ѡ�򷵻�
	if (stuSelectCourse.size() == 0) {
		cout << className << "��û����ѡ��" << courseName << "���ſ��أ���ȥѡ�ΰ�" << endl;
		return;
	}


	double allScores = 0;
	// ��¼������ѧ��
	vector<student> failStu;
	cout << endl << "��ѯ�� " << className << " ������ͬѧѡ���� " << courseName << " �ɼ�����:" << endl;
	cout << "ѧ��\t\t����\t����" << endl;
	sort(stuSelectCourse.begin(), stuSelectCourse.end(), scoreCompare);
	for (student stu : stuSelectCourse) {
		cout << stu.id << "\t" << stu.name << "\t" << stu.tmpCompare << endl;
		allScores += stu.tmpCompare;
		if (stu.tmpCompare < 60) {
			failStu.push_back(stu);
		}
	}
	// ����ƽ����
	int num = stuSelectCourse.size();
	double averScores = allScores / num;

	// �����׼��
	double stdEro = 0;
	for (student stu : stuSelectCourse) {
		stdEro += pow(stu.tmpCompare - averScores, 2);
	}
	stdEro = sqrt(stdEro / num);

	// ����ϸ��� ҪǿתΪdouble ������ܻ����0
	double accessRate = (num - failStu.size()) / (double)num;
	//
	cout << endl;
	cout << "ƽ���ɼ�Ϊ�� " << averScores << endl;
	cout << "��׼��Ϊ�� " << stdEro << endl;
	cout << "�ϸ���Ϊ�� " << accessRate << endl;

	if (failStu.size() > 0) {
		cout << "������ѧ����: " << endl;
		cout << "ѧ��\t\t����\t����" << endl;
		for (student stu : failStu) {
			cout << stu.id << "\t" << stu.name << "\t" << stu.tmpCompare << endl;
		}
	}
	else
	{
		cout << "û�в�����ѧ������Ҷ��ܰ�~~" << endl;
	}

	// ͳ��ѧ������ѧ�֡�������γ�����δ��ѧ��
	concluStudentMsg(rec);
	

}

void SystemManage::concluStudentMsg(vector<student>& stuVec)
{
	cout << endl;
	cout << "�Ƿ�ͳ��ѧ������ѧ����Ϣ��y/n" << endl;
	string sc;
	cin >> sc;
	if ((sc == "y") || (sc == "Y")) {
		if (stuVec.size() == 0) {
			cout << "����û��ѧ������ͳ����~~����¼��ѧ����Ϣ��" << endl;
			return;
		}
		sort(stuVec.begin(), stuVec.end(), pointCompare);
		cout << "ѧ��\t\t����\t������ѧ��\t������γ���\tδ��ѧ��(����50��Ϊδ����)" << endl;
		for (student stu : stuVec) {
			cout << stu.id << "\t" << stu.name << "\t"
				<< stu.alreadyPoint << "\t\t" << stu.failCourseNum << "\t\t"
				<< (((50 - stu.alreadyPoint) > 0) ? (50 - stu.alreadyPoint) : 0) << endl;
		}
	}
	else
	{
		cout << "���û��ͳ��ѧ����ϢŶ" << endl;
	}
	
}

void SystemManage::saveStuMsg(vector<student> stuVec, course* co)//���溯��
{
	if (stuVec.size() == 0) {
		return;
	}
	cout << endl;
	cout << "�Ƿ񱣴�ѧ���ɼ���Ϣ���ļ��У�y/n" << endl;
	string sc;
	cin >> sc;
	if ((sc == "y") || (sc == "Y"))
	{
		ofstream outfile;    //�������������
		while (1)
		{
			//cout << "��������Ҫ������ļ�����(��n�˳�)��" << endl;
			//cin >> sc;
			//if (sc == "n") {
			//	break;
			//}
			outfile.open("C:\student.txt");    //���ļ�
			if (!outfile)
			{
				cout << "�� " << sc << " �ļ�ʧ��" << endl;
			}
			else
			{
				break;
			}
		}

		// ������Ϣ���ļ�����
		outfile << "ѧ��\t����\t�γ�����\t�ɼ�" << endl;
		if (co == nullptr) {
			for (student stu : stuVec) {
				for (course cou : stu.allCourses) {
					outfile << stu.id << "\t" << stu.name << "\t"
						<< cou.name << "\t" << cou.score << "\t"
						<< endl;
					/*cout << stu.id << "\t" << stu.name << "\t"
						<< cou.name << "\t" << cou.score << "\t"
						<< endl;*/
				}
			}
		}
		else
		{
			for (student stu : stuVec) {
				outfile << stu.id << "\t" << stu.name << "\t"
					<< co->name << "\t" << stu.tmpCompare << "\t"
					<< endl;
			}
		}
		outfile << "#END";
		
		cout << "��Ϣ�ɹ���������"<< sc << endl;

	
	}
	else {
		cout << "δ�������ļ�" << endl;
	}
}

void SystemManage::saveSingleMsg(student stu, course cou)
{
	cout << endl;
	cout << "�Ƿ񱣴��������޸ģ�ѧ���ɼ���Ϣ���ļ���(׷�ӱ���)��y/n" << endl;
	string sc;
	cin >> sc;
	if ((sc == "y") || (sc == "Y"))
	{
		ofstream outfile;    //�������������
		while (1)
		{
			cout << "��������Ҫ������ļ�����(��n�˳�)��" << endl;
			cin >> sc;
			if (sc == "n") {
				break;
			}
			outfile.open(sc, ios::app);    //���ļ�
			if (!outfile)
			{
				cout << "�� " << sc << " �ļ�ʧ��" << endl;
			}
			else
			{
				break;
			}
		}

		// ������Ϣ���ļ�����
		
		outfile << stu.id << "\t" << stu.name << "\t"
				<< cou.name << "\t" << cou.score << "\t"
					<< endl;
		cout << "��Ϣ�ɹ���������" << sc << "�������£�" << endl;
		cout << stu.id << "\t" << stu.name << "\t"
			<< cou.name << "\t" << cou.score << "\t"
			<< endl;
	}
	else {
		cout << "δ�������ļ�" << endl;
	}
}

void SystemManage::showFile()
{
	printf("-------------->10.���ļ���ʾ����<------------------\n\n");
	string path;
	cout << "��������Ҫ��ȡ��txt" << endl;
	cin >> path;
	ifstream in(path);
	string line;

	if (in) // �и��ļ�
	{
		getline(in, line); //�ȶ�����һ��������Ϣ
		cout << line << endl;
		while (getline(in, line)) // line�в�����ÿ�еĻ��з�
		{
			cout << line << endl;
			if (line.find('#') == 0)
				break;
		}

	}
	else // û�и��ļ�
	{
		cout << "no " << path << " file" << endl;
	}
}

student* SystemManage::blurFindStudent(string partName, vector<student>& stuVec)
{
	vector<student*> re;
	int pos = -1;
	for (int i = 0; i < stuVec.size(); i++) {
		pos = stuVec[i].name.find(partName);
		if (pos != -1) {
			re.push_back(&stuVec[i]);
			stuVec[i].tmpCompare = i;		// ��¼���������е�λ�ã�ɾ��ʱʹ��
		}
	}
	// �����ѯ��������nullptr
	if (re.size() == 0) {
		return nullptr;
	}

	//���⼸���˰���ѧ�Ž�������
	sort(re.begin(), re.end()); //����sort(begin, end, cmp)

	
	cout << "*********************************************" << endl;
	cout << "���\tѧ��\t\t�༶\t����\t" << endl;
	for (int i = 0; i < re.size(); i++) {
		cout << i + 1 << ".\t" << re[i]->id << "\t"
			<< re[i]->classNum << "\t" << re[i]->name << endl;
	}
	cout << "*********************************************" << endl;
	cout << "��ѯ�����������ѧ����Ϣ�������ѡ��(�˳���n):" << endl;
	
	while (true)
	{
		string sc;
		cin >> sc;

		if ((sc == "n")||(sc=="N")) {
			return nullptr;
		}
		int choice = atoi(sc.c_str());
		// ��������������ڷ�Χ�ڵ����֣�����������
		if (choice > re.size() || choice <= 0) {
			cout << "���������������ѡ�񣬲���������" << endl;
			continue;
		}

		return re[choice - 1];
	}  
	

}



// �ָ��ַ���
vector<string> SystemManage::splitWithStl(const std::string& str, const std::string& pattern){//csdn https://blog.csdn.net/qq_44894692/article/details/104200627
	std::vector<std::string> resVec;

	if ("" == str)
	{
		return resVec;
	}
	//�����ȡ���һ������
	std::string strs = str + pattern;

	size_t pos = strs.find(pattern);
	size_t size = strs.size();

	while (pos != std::string::npos)
	{
		std::string x = strs.substr(0, pos);//substr������������ַ���
		
		//������β�ո�
		x.erase(0, x.find_first_not_of(" "));//��������
		x.erase(x.find_last_not_of(" ") + 1);

		resVec.push_back(x);
		strs = strs.substr(pos + pattern.size(), size);
		pos = strs.find(pattern);
	}

	return resVec;
}

bool pointCompare(const student& st1, const student& st2)
{
	return st1.alreadyPoint > st2.alreadyPoint;
}

bool scoreCompare(const student& st1, const student& st2)
{
	return st1.tmpCompare > st2.tmpCompare;
}
