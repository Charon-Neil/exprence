#include "SystemManage.h"


SystemManage::SystemManage() {
	blurFlag = false;
	loadStudentTxT(); // 初始化学生信息（教务系统录入学生学籍）
	loadModuleTxT();  // 初始化课程信息（教务系统上架课程）	
}




void SystemManage::Menu() {
	printf("*************************************************\n");
	printf("   欢迎使用学生成绩管理系统@崔继凡（感谢csdn）\n");
	printf("*************************************************\n");
	printf("*\t\t 1.录入学生成绩\t\t\t*\n");
	printf("*\t\t 2.删除学生信息\t\t\t*\n");
	printf("*\t\t 3.课程成绩修改\t\t\t*\n");
	printf("*\t\t 4.添加课程成绩\t\t\t*\n");
	printf("*\t\t 5.查询学生成绩\t\t\t*\n");
	printf("*\t\t 6.按班级查询学生成绩\t\t*\n");
	printf("*\t\t 7.按课程查询学生成绩\t\t*\n");
	printf("*\t\t 8.查询所有学生成绩\t\t*\n");
	printf("*\t\t 9.班级单科成绩统计\t\t*\n");
	printf("*\t\t 10.打开文件显示内容\t\t*\n");
	printf("*\t\t 0.模糊查询:%s\t\t\t*\n", (blurFlag? "开" :"关"));
	printf("*\t\t-1.退出查询系统\t\t\t*\n");
	printf("*************************************************\n");
	printf("->请选择功能(输入数字):");
}


void SystemManage::loadStudentTxT()
{
	ifstream in("./student.txt");
	string filename;
	string line;

	if (in) // 有该文件
	{
		getline(in, line); //先读掉第一行无用信息
		while (getline(in, line)) // line中不包括每行的换行符
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
			if (initStu == nullptr) {	//表示原先没有该学生，可以添加
				allStudents.push_back(s);
			}
			else {
				if (initStu->id == s.id) {	// 名称相同，学号相同，是同一个人，不进行新增

				}
				else	//// 名称相同，学号不同同，不是同一个人，进行新增
				{
					allStudents.push_back(s);
				}
			}

			
		}
		sort(allStudents.begin(), allStudents.end());
	
	}
	else // 没有该文件
	{
		cout << "no student.txt file" << endl;
	}
}

void SystemManage::loadModuleTxT()
{
	ifstream in("./module.txt");
	string filename;
	string line;

	if (in) // 有该文件
	{
		getline(in, line); //先读掉第一行无用信息
		while (getline(in, line)) // line中不包括每行的换行符
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
	else // 没有该文件
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
	printf("-------------->2.录入学生成绩<---------------\n\n");

	cout << "是否使用默认成绩文件（默认使用score.txt）y/n:" << endl;;
	string sc;
	cin >> sc;
	string path = "./score.txt";
	if (sc == "n") {
		cout << "请输入需要录入成绩的文件：";
		cin >> path;
	}
	

	ifstream in(path);
	string filename;
	string line;

	if (in) // 有该文件
	{
		cout << "开始录入成绩，是否需要打印录入结果?y/n" << endl;
		cin >> sc;
		getline(in, line); //先读掉第一行无用信息
		while (getline(in, line)) // line中不包括每行的换行符
		{
			if((sc == "y")||(sc=="Y"))
				cout << line << endl;
			if (line.find('#') == 0)  //末行退出
				break;
			
			vector<string> v1 = splitWithStl(line, "\t");
			// 找到对应课程
			course c = findCourse(v1[2]);
			c.score = atoi(v1[3].c_str());
			// 根据名称找到对应学生
			pair<student*, int> pa = findStudent(v1[1]);
			student* st = pa.first;
			int pos = pa.second;
			if (st == nullptr) {
				cout << "系统中无此学生：" << v1[1] << endl;
				continue;
			}
			else
			{
				//判断该同学是否已有该门课程，没有则添加，有则更新成绩
				pair<course*, int> coursePair = findCourse(*st, c.name);
				if (coursePair.second == -1) {
					allStudents[pos].allCourses.push_back(c);
					if (c.score >= 60) {  // 该科目通过则获得学分
						allStudents[pos].alreadyPoint += c.point;
					}
					else {	//否则不及格课程数+1
						allStudents[pos].failCourseNum += 1;
					}
				}
				else   //有则更新
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
					coursePair.first->score = c.score;  // 最后进行更新
				}
				
			}
			
		}
		
		cout << "----------------成绩录入成功---------------" << endl;
	}
	else // 没有该文件
	{
		cout << "no " << path << " file" << endl;
	}
}

void SystemManage::changeBlurFlag()
{
	this->blurFlag = !this->blurFlag;
	if (blurFlag)
	{
		cout << "**************现在可以使用模糊查询**************" << endl;
	}
	else {
		cout << "***************模糊查询已经关闭*****************" << endl;
	}

}

course SystemManage::findCourse(string courseName)
{
	for (int i = 0; i < mustCourses.size(); i++) {
		if (courseName == mustCourses[i].name)
			return mustCourses[i];
	}
	// 如果在必修课表找不到，则说明不存在，课程编号为-1
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
	printf("---------------->1.删除学生信息<-----------------\n\n");
	student* st = nullptr;
	int pos = -1;
	while(1) {
		cout.setf(ios_base::boolalpha);     // 设置打印bool变量
		cout << "请输入需要删除的学生姓名(是否支持模糊查询：" << (bool)blurFlag << ")" << endl;
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
				cout << "查无此人" << endl;
				break;
			}

			pos = st->tmpCompare;
		}

		if (st == nullptr) {
			cout << "查无此人" << endl;
			break;
		}
		else {
			cout << "学号\t\t班级\t姓名\t\n";
			cout << st->id << "\t" << st->classNum << "\t" << st->name << endl;
			cout << "查询到了如上信息，请确认是否删除(y/n)" << endl;
			string re;
			cin >> re;
			if (re == "y") {
				// remove(allStudents.begin(), allStudents.end(), *st);
				allStudents.erase(allStudents.begin() + pos);
				cout << "删除成功" << endl;
			}
			else {
				cout << "不删除" << endl;
			}
			break;
		}
	}
}

void SystemManage::updateScore()
{
	printf("---------------->3.课程成绩修改<-----------------\n\n");
	cout.setf(ios_base::boolalpha);     // 设置打印bool变量
	cout << "请输入需要修改的学生姓名(是否支持模糊查询：" << (bool)blurFlag << ")" << endl;
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
		cout << "查无此人" << endl;
	}
	else {
		if (st->allCourses.size() == 0) {
			cout << "暂时无法查到该学生成绩,可能是系统还未录入" << endl;
			return;
		}
		string co;
		string score;
		while (1)
		{
			showStudentAllCourses(*st);
			cout << "请输入需要修改的科目名称" << endl;
			cin >> co;
			pair <course*, int> paCourse = findCourse(*st, co); // 注意这里需要用到原数据，因此函数上是用的引用
			int pos = paCourse.second;
			if (pos == -1) {
				cout << "没有查到: " << co << ",请重新输入课程名称" << endl;
				continue;
			}
			else
			{
				cout << "请输入需要修改的分数" << endl;
				cin >> score;
				course* updataCourse = paCourse.first;
				int initScore = updataCourse->score;     // 记录初始分数
				updataCourse->score = atoi(score.c_str());
				if (initScore >= 60 && updataCourse->score < 60) {     //原先过了，修改后没过，学分减少，不及格课程+1
					st->alreadyPoint -= updataCourse->point;
					st->failCourseNum += 1;
				}
				else if(initScore < 60 && updataCourse->score >= 60)     // 原先没过，修改后过了，学分增加,不及格课程-1
				{
					st->alreadyPoint += updataCourse->point;
					st->failCourseNum -= 1;
				}
				cout << name << "的<<" << co << ">>修改成功，现在是：" << score << "分" << endl;
				//saveSingleMsg(*st, *updataCourse);  // 询问是否保存至文件
				saveStuMsg(allStudents);
				break;
			}
				
		}
	}
	
}

void SystemManage::addCourseforStudent()
{
	while (1) {
		printf("---------------->4.添加课程成绩<-----------------\n\n");
		cout.setf(ios_base::boolalpha);     // 设置打印bool变量
		cout << "请输入需要添加成绩的学生姓名(是否支持模糊查询：" << (bool)blurFlag << ")" << endl;
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
			cout << "查无此人" << endl;
			return;
		}
		else {
			string co;
			string score;
			while (1)
			{
				showStudentAllCourses(*st);
				cout << "请输入需要添加的科目名称" << endl;
				cin >> co;

				course sysCourse = findCourse(co);  // 先在教务系统查询是否录入了该门课程
				if (sysCourse.number == -1) {
					cout << "教务系统查询未录入该门课程，添加失败" << endl;
					return;
				}

				pair <course*, int> paCourse = findCourse(*st, co); // 再在学生已选课程里查询是否存在
				int pos = paCourse.second;
				if (pos == -1) {  // 表示没有该课程。可以添加
					cout << "请输入该门课程的分数：" << endl;
					cin >> score;
					sysCourse.score = atoi(score.c_str());   //设置分数
					if (sysCourse.score >= 60) {      // 过了则获得学分
						st->alreadyPoint += sysCourse.point;
					}
					else {
						st->failCourseNum += 1;
					}
					st->allCourses.push_back(sysCourse);
					cout << " 添加课程:\t" << sysCourse.name
						<< "\t分数是: " << sysCourse.score
						<<  endl;
					saveSingleMsg(*st, sysCourse);  // 询问是否保存至文件
					showStudentAllCourses(*st);
					return;
				}
				else
				{
					cout << "已存在该门课程，请勿重复添加" << endl;
					return;
				}
			}

		}
	}

}

void SystemManage::searchStudentScore()
{
	printf("-------------->5.查询学生成绩<---------------\n\n");
	cout.setf(ios_base::boolalpha);     // 打印bool
	cout << "请输入查询学生姓名(是否支持模糊查询：" << (bool)blurFlag << ")" << endl;
	student* st = nullptr;
	string name;
	cin >> name;

	// 非模糊查询
	if (!blurFlag) {
		pair<student*, int> stuPair = findStudent(name);
		st = stuPair.first;
	}
	else // 模糊查询
	{
		st = blurFindStudent(name, allStudents);
		
	}

	if (st == nullptr) {
		cout << "查无此人" << endl;
		return;
	}
	// 展示学生的所有课程信息
	showStudentAllCourses(*st);
	


}

void SystemManage::searchStuScoreFromClass()
{
	printf("-------------->6.查询班级所有学生成绩<-------------\n\n");
	cout << "请输入查询的班号：" << endl;
	string cls;
	cin >> cls;

	vector<student> rec = searchClass(cls);
	if (rec.size() == 0) {
		cout << "系统不存在此班级，请检查是否输入正确" << endl;
	}
	sort(rec.begin(), rec.end(), pointCompare);
	for (student stu : rec) {
		showStudentAllCourses(stu);
	}

	// 选择是否保存至文件中
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
	printf("------------->7.查询课程所有学生成绩<-------------\n\n");
	cout << "请输入查询的课程名称：" << endl;
	string courseName;
	cin >> courseName;

	// 判断教务系统中是否有该门课程
	course cou = findCourse(courseName);
	if (cou.number == -1) {
		cout << "系统不存在此课程，请检查是否输入正确" << endl;
		return;
	}

	// 查找选课学生，然后遍历
	vector<student> stuVec = searchCourse(courseName, allStudents);
	if (stuVec.size() == 0) {
		cout << "暂时没有人选择您的课程呢，请您稍后再查询" << endl;
	}
	sort(stuVec.begin(), stuVec.end(), scoreCompare);
	cout << endl << "学号\t\t" << " 班级\t" << " 姓名\t" << " 成绩\t" << endl;
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
			if (cou.name == courseNumber) {  // 如果该学生的所有已选课程中包含这门课，则加入，然后跳出，判断下一个学生
				stu.tmpCompare = cou.score;   // 记录待统计的当前课程的成绩
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
		cout << "暂时查询不到 " << st.name << " 的成绩，可能是系统还未录入" << endl;
		return;
	}

	cout << endl  << "学号：" <<	st.id 
				  << " 班级：" << st.classNum
				  << " 姓名：" << st.name   
				  << " 已修学分：" << st.alreadyPoint 
				  << " 成绩如下：" << endl;
	cout << "课程编号\t课程名称\t\t课程学分\t\t课程成绩" << endl;
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
	printf("--------------->8.查询所有学生成绩<---------------\n\n");
	sort(allStudents.begin(), allStudents.end(), pointCompare); //按照学分进行排序
	for (int i = 0; i < allStudents.size(); i++) {
		showStudentAllCourses(allStudents[i]);
		cout << endl;
	}

	// 选择是否保存至文件中
	saveStuMsg(allStudents);
	//
	concluStudentMsg(allStudents);
}

void SystemManage::concluClassScore()
{
	printf("---------------->9.班级单科统计<-------------------\n\n");
	cout << "请输入待统计的班级：" << endl;
	string className;
	cin >> className;
	vector<student> rec = searchClass(className);
	// 判断有无该班级
	if (rec.size() == 0) {
		cout << "系统不存在此班级，请检查是否输入正确" << endl;
		return;
	}

	cout << "请输入统计的单科课程名称：" << endl;
	string courseName;
	cin >> courseName;
	// 判断教务系统中是否有该门课程
	course cou = findCourse(courseName);
	if (cou.number == -1) {
		cout << "系统不存在此课程，请检查是否输入正确" << endl;
		return;
	}

	// 统计该班级选择该门课程的人数
	vector<student> stuSelectCourse = searchCourse(courseName, rec);
	// 如果没人选则返回
	if (stuSelectCourse.size() == 0) {
		cout << className << "还没有人选择" << courseName << "这门课呢，快去选课吧" << endl;
		return;
	}


	double allScores = 0;
	// 记录不及格学生
	vector<student> failStu;
	cout << endl << "查询到 " << className << " 有以下同学选择了 " << courseName << " 成绩如下:" << endl;
	cout << "学号\t\t姓名\t分数" << endl;
	sort(stuSelectCourse.begin(), stuSelectCourse.end(), scoreCompare);
	for (student stu : stuSelectCourse) {
		cout << stu.id << "\t" << stu.name << "\t" << stu.tmpCompare << endl;
		allScores += stu.tmpCompare;
		if (stu.tmpCompare < 60) {
			failStu.push_back(stu);
		}
	}
	// 计算平均分
	int num = stuSelectCourse.size();
	double averScores = allScores / num;

	// 计算标准差
	double stdEro = 0;
	for (student stu : stuSelectCourse) {
		stdEro += pow(stu.tmpCompare - averScores, 2);
	}
	stdEro = sqrt(stdEro / num);

	// 计算合格率 要强转为double 否则可能会出现0
	double accessRate = (num - failStu.size()) / (double)num;
	//
	cout << endl;
	cout << "平均成绩为： " << averScores << endl;
	cout << "标准差为： " << stdEro << endl;
	cout << "合格率为： " << accessRate << endl;

	if (failStu.size() > 0) {
		cout << "不及格学生有: " << endl;
		cout << "学号\t\t姓名\t分数" << endl;
		for (student stu : failStu) {
			cout << stu.id << "\t" << stu.name << "\t" << stu.tmpCompare << endl;
		}
	}
	else
	{
		cout << "没有不及格学生，大家都很棒~~" << endl;
	}

	// 统计学生的总学分、不及格课程数、未修学分
	concluStudentMsg(rec);
	

}

void SystemManage::concluStudentMsg(vector<student>& stuVec)
{
	cout << endl;
	cout << "是否统计学生已修学分信息？y/n" << endl;
	string sc;
	cin >> sc;
	if ((sc == "y") || (sc == "Y")) {
		if (stuVec.size() == 0) {
			cout << "好像没有学生让您统计呢~~，先录入学生信息吧" << endl;
			return;
		}
		sort(stuVec.begin(), stuVec.end(), pointCompare);
		cout << "学号\t\t姓名\t已修总学分\t不及格课程数\t未修学分(不足50视为未修满)" << endl;
		for (student stu : stuVec) {
			cout << stu.id << "\t" << stu.name << "\t"
				<< stu.alreadyPoint << "\t\t" << stu.failCourseNum << "\t\t"
				<< (((50 - stu.alreadyPoint) > 0) ? (50 - stu.alreadyPoint) : 0) << endl;
		}
	}
	else
	{
		cout << "这次没有统计学分信息哦" << endl;
	}
	
}

void SystemManage::saveStuMsg(vector<student> stuVec, course* co)//保存函数
{
	if (stuVec.size() == 0) {
		return;
	}
	cout << endl;
	cout << "是否保存学生成绩信息至文件中？y/n" << endl;
	string sc;
	cin >> sc;
	if ((sc == "y") || (sc == "Y"))
	{
		ofstream outfile;    //定义输出流对象
		while (1)
		{
			//cout << "请输入需要保存的文件名称(按n退出)：" << endl;
			//cin >> sc;
			//if (sc == "n") {
			//	break;
			//}
			outfile.open("C:\student.txt");    //打开文件
			if (!outfile)
			{
				cout << "打开 " << sc << " 文件失败" << endl;
			}
			else
			{
				break;
			}
		}

		// 保存信息至文件当中
		outfile << "学号\t姓名\t课程名称\t成绩" << endl;
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
		
		cout << "信息成功保存至："<< sc << endl;

	
	}
	else {
		cout << "未保存至文件" << endl;
	}
}

void SystemManage::saveSingleMsg(student stu, course cou)
{
	cout << endl;
	cout << "是否保存新增（修改）学生成绩信息至文件中(追加保存)？y/n" << endl;
	string sc;
	cin >> sc;
	if ((sc == "y") || (sc == "Y"))
	{
		ofstream outfile;    //定义输出流对象
		while (1)
		{
			cout << "请输入需要保存的文件名称(按n退出)：" << endl;
			cin >> sc;
			if (sc == "n") {
				break;
			}
			outfile.open(sc, ios::app);    //打开文件
			if (!outfile)
			{
				cout << "打开 " << sc << " 文件失败" << endl;
			}
			else
			{
				break;
			}
		}

		// 保存信息至文件当中
		
		outfile << stu.id << "\t" << stu.name << "\t"
				<< cou.name << "\t" << cou.score << "\t"
					<< endl;
		cout << "信息成功保存至：" << sc << "内容如下：" << endl;
		cout << stu.id << "\t" << stu.name << "\t"
			<< cou.name << "\t" << cou.score << "\t"
			<< endl;
	}
	else {
		cout << "未保存至文件" << endl;
	}
}

void SystemManage::showFile()
{
	printf("-------------->10.打开文件显示内容<------------------\n\n");
	string path;
	cout << "请输入需要读取的txt" << endl;
	cin >> path;
	ifstream in(path);
	string line;

	if (in) // 有该文件
	{
		getline(in, line); //先读掉第一行无用信息
		cout << line << endl;
		while (getline(in, line)) // line中不包括每行的换行符
		{
			cout << line << endl;
			if (line.find('#') == 0)
				break;
		}

	}
	else // 没有该文件
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
			stuVec[i].tmpCompare = i;		// 记录处于容器中的位置，删除时使用
		}
	}
	// 如果查询不到返回nullptr
	if (re.size() == 0) {
		return nullptr;
	}

	//将这几个人按照学号进行排序
	sort(re.begin(), re.end()); //降序sort(begin, end, cmp)

	
	cout << "*********************************************" << endl;
	cout << "序号\t学号\t\t班级\t姓名\t" << endl;
	for (int i = 0; i < re.size(); i++) {
		cout << i + 1 << ".\t" << re[i]->id << "\t"
			<< re[i]->classNum << "\t" << re[i]->name << endl;
	}
	cout << "*********************************************" << endl;
	cout << "查询到了以上相关学生信息，请继续选择(退出按n):" << endl;
	
	while (true)
	{
		string sc;
		cin >> sc;

		if ((sc == "n")||(sc=="N")) {
			return nullptr;
		}
		int choice = atoi(sc.c_str());
		// 如果输入其他不在范围内的数字，则重新输入
		if (choice > re.size() || choice <= 0) {
			cout << "输入错误，请检查您的选择，并重新输入" << endl;
			continue;
		}

		return re[choice - 1];
	}  
	

}



// 分割字符串
vector<string> SystemManage::splitWithStl(const std::string& str, const std::string& pattern){//csdn https://blog.csdn.net/qq_44894692/article/details/104200627
	std::vector<std::string> resVec;

	if ("" == str)
	{
		return resVec;
	}
	//方便截取最后一段数据
	std::string strs = str + pattern;

	size_t pos = strs.find(pattern);
	size_t size = strs.size();

	while (pos != std::string::npos)
	{
		std::string x = strs.substr(0, pos);//substr函数，获得子字符串
		
		//擦除首尾空格
		x.erase(0, x.find_first_not_of(" "));//擦除函数
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
