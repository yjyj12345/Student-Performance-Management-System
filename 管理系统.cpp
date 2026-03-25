#include"管理系统.h"

//绘制注册登录界面
void draw(){
    initgraph(width, height);
	setbkcolor(WHITE);// 设置背景为白色
	cleardevice();
	settextcolor(BLACK); //设置字为黑色
	settextstyle(40, 0, _T("黑体"));
	outtextxy(width / 2 - 150, 50, _T("注册/登录"));// 标题
	rectangle(width / 2 - 150, 150, width / 2 + 150, 200);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(width / 2 - 140, 160, _T("用户名:"));// 用户名输入
	rectangle(width / 2 - 150, 250, width / 2 + 150, 300);
	settextstyle(20, 0, _T("黑体"));
	setbkmode(TRANSPARENT);
	outtextxy(width / 2 - 140, 260, _T("密码:"));// 密码输入
	setfillcolor(LIGHTGRAY);
	fillrectangle(width / 2 - 150, 350, width / 2 - 50, 400);
	settextstyle(20, 0, _T("黑体"));
	setbkmode(TRANSPARENT);
	outtextxy(width / 2 - 120, 365, _T("注册")); // 注册按钮
	fillrectangle(width / 2 + 50, 350, width / 2 + 150, 400);
	settextstyle(20, 0, _T("黑体"));
	setbkmode(TRANSPARENT);
	outtextxy(width / 2 + 80, 365, _T("登录")); // 绘制登录按钮
}

//用户名和密码输入
void getuserdata() {
	char ch;
	int x = width / 2 - 10;
	int y = 165;//调整坐标位置
	// 获取用户名输入
	outtextxy(x, y, _T(""));
	while ((ch = _getch()) != '\r')//获取用户输入的字符赋值给ch
	{//字符不等于回车键\r
		if (ch == '\b' && x > width / 2 - 10)
		{//字符是退格键\b
			x = x - 15;//调整横坐标位置
			setfillcolor(WHITE);
			fillrectangle(x, y, x+15, y+20);
			outtextxy(x, y, _T(" "));
			username.pop_back(); //删除字符串username的最后一个字符
		}
		else if (ch != '\b')
		{//字符不是退格键\b
			username = username + ch;
            //将当前输入的字符ch添加到字符串username中
			outtextxy(x, y, ch);
			x = x + 15;
		}
	}
	x = width / 2 - 10;
	y = 265;
	// 获取密码输入
	outtextxy(x, y, _T(""));
	while ((ch = _getch()) != '\r')
	{
		if (ch == '\b' && x > width / 2 - 10)
		{
			x = x - 15;
			setfillcolor(WHITE);
			fillrectangle(x, y, x + 15, y + 20);
			outtextxy(x, y, _T(" "));
			password.pop_back();
		}
		else if (ch != '\b')
		{
			password = password + ch;
			outtextxy(x, y, ch);
			x = x + 15;
		}
	}
}

//将用户信息保存到文件
void saveuserdata() {
	//创建一个ofstream对象file向文件写入数据
	ofstream file(userfilename, ios::app);
	if (file.is_open())
	{//文件打开成功则将用户名密码依次写入文件
		file << username << " " << password << endl;
		file.close();
		outtextxy(width / 2 - 140, 460, _T("注册成功！"));
		Sleep(500); 
	}
	else
	{//文件无法打开时，退出整个程序
		outtextxy(width / 2 - 140, 460, _T("无法保存用户信息 请稍后重试"));
		Sleep(500); 
		exit(0);
	}
}

//从文件中读取用户信息并验证
int verifyuserdata() {
	ifstream file(userfilename);
	if (file.is_open()) {
		string line;
		while (getline(file, line))//从file文件流读取一行字符并存储到line字符串中
		{
			istringstream iss(line); //istringstream类用于从字符串中读取数据
			string storedusername;
			string storedpassword;
			iss >> storedusername >> storedpassword;//从istringstream对象读取用户名和密码
			if (username == storedusername && password == storedpassword)
			{
				file.close();
				return 1;//用户名密码对比成功返回1
			}
		}
		file.close();
	}
	return 0;//对比验证失败返回0
}

// 判断鼠标位置是否点击按钮
void buttonclick(){
	MOUSEMSG msg;
	int loginclick = 0;
	while (!loginclick)
	{
		msg = GetMouseMsg();//获取鼠标消息
		if (msg.uMsg == WM_LBUTTONDOWN) // 判断是否点击注册按钮
		{
			if (msg.x >= width / 2 - 150 && msg.x <= width / 2 - 50 && msg.y >= 350 && msg.y <= 400)
			{//鼠标左键点击注册按钮
				saveuserdata();
				loginclick = 1;
			}
			else if (msg.x >= width / 2 + 50 && msg.x <= width / 2 + 150 && msg.y >= 350 && msg.y <= 400)// 判断是否点击登录按钮
			{//鼠标左键点击登录按钮
				if (verifyuserdata()) {
					outtextxy(width / 2 - 140, 460, _T("登录成功！"));
					loginclick = 1;
					Sleep(500);
				}
				else {
					outtextxy(width / 2 - 140, 460, _T("登录失败！请检查用户名和密码")); 
					Sleep(500);
				}
			}
		}
	}
}

//添加学生
void management::addstudent() {
	int choice;
	cout << "请选择所添加学生的年级：" << endl << "1.小学" << endl << "2.中学" << endl << "3.大学" << endl;
	cin >> choice;
	student* newstudent;//指向student基类的指针
	switch (choice) {
	case 1://new关键字动态分配内存来创建一个primarystudent对象
		newstudent = new primarystudent(" "," "," ",0," ",0,0,0);
		break;
	case 2:
		newstudent = new middlestudent(" ", " ", " ", 0, " ", 0, 0);
		break;
	case 3:
		newstudent = new collegestudent(" ", " ", " ", 0, " ",0, 0, 0, 0);
		break;
	default:cout << "输入有误！\n";  return;
	}
	newstudent->input();//调用新创建的学生对象的input函数进行学生信息的输入
	for (const auto& student : students) {
		//for循环遍历容器中的每一个学生对象,const auto&以只读方式遍历容器中的元素
		if (student->getid() == newstudent->getid()) {
			cout << "添加重复!" << endl;
			delete newstudent;//添加重复则释放动态分配的内存
			return;
		}
	}
	students.push_back(newstudent);//将新创建的学生对象添加到students容器中
	cout << "添加成功！" << endl<<endl;
}

//查询学生
void management::searchstudent() {
	string query;
	cout << "请输入所查询学生的姓名或学号：";
	cin >> query;
	int found = 0;
	for (const auto& student : students) {//for循环遍历students容器中的学生对象
		if (student->getname() == query || student->getid() == query) {
			student->show();
			found = 1;
		}
	}
	if (found==0) {
		cout << "未找到相应记录!" << endl;
	}
}

//显示所有学生
void management::showall() { 
	for (const auto& student : students) {//for循环遍历students容器中的学生对象
		student->show();
	}
}

//编辑学生
void management::editstudent() {
	string query;
	cout << "请输入要编辑的学生的姓名或学号：";
	cin >> query;
	for (auto& student : students) {
		if (student->getname() == query || student->getid() == query) {
			student->input();
			cout << "编辑成功!" << endl;
			return;
		}
	}
	cout << "未找到相应记录!" << endl;
}

//删除学生
void management::deletestudent() {
	if (students.empty()) {//检验是否为空，空返回1
		cout << "记录为空！" << endl;
		return;
	}
	string query;
	cout << "输入要删除的学生的姓名或学号：";
	cin >> query;
	auto t = students.begin();//获取指向容器中第一个元素的迭代器
	while (t != students.end()) {//遍历容器中的每个元素
		if ((*t)->getname() == query || (*t)->getid() == query) {
			delete* t;//找到时delete删除当前迭代器t所指向的学生对象
			t = students.erase(t);//删除容器中元素
			cout << "删除成功!" << endl;
			return;
		}
		else {
			++t;//t自增使其指向下一个元素
		}
	}
	cout << "未找到相应记录!" << endl;
}

//统计学生人数
void management::countstudents() {
	int countp = 0;
	int countm = 0;
	int countc = 0;
	for (const auto& student : students) {//for循环遍历students容器中的每个学生对象
		//const表示这个变量是常量，不能通过这个变量修改所引用的对象
		//auto 自动类型推导关键字，让编译器根据初始化的值自动推断变量的类型。根据students容器中存储的元素类型确定student的类型
	    if (dynamic_cast<primarystudent*>(student)) { countp++; }
		//dynamic_cast动态类型转,如果转换成功，说明当前遍历到的学生对象是primarystudent类型的，则countp加 1
	    else if (dynamic_cast<middlestudent*>(student)) { countm++; }
		else if (dynamic_cast<collegestudent*>(student)) { countc++; }
	}
	cout << "小学生共 " << countp << " 人" << endl
		<< "中学生共 " << countm << " 人" << endl
		<< "大学生共 " << countc << " 人" << endl;
}
/*int management::totalscore() {// 计算总分
	int sum = 0;
	for (const auto& student : students) {
		sum = sum + student->totalscore();
	}
	return sum;
	
	}*/
	
//计算中学生单科平均分
double management::middleaveragescore(const string& subject) {
	int count = 0;
	int sum = 0;
	for (const auto& student : students) {
        if (dynamic_cast<middlestudent*>(student)) {
			if (subject == "geography") 
				sum =sum+ dynamic_cast<middlestudent*>(student)->getgeography();
			else if (subject == "history")
				sum =sum+ dynamic_cast<middlestudent*>(student)->gethistory();
			count++;
		}
	}
	if (count > 0) {
		return (double)sum / count;
	}
	else return 0;
}

//计算大学生单科平均分
double management::collegeaveragescore(const string& subject) { 
	int count = 0;
	int sum = 0;
	for (const auto& student : students) {
        if (dynamic_cast<collegestudent*>(student)) {
			if (subject == "professional")
				sum = sum+ dynamic_cast<collegestudent*>(student)->getprofessional();
			else if (subject == "collegeenglish") 
				sum= sum+ dynamic_cast<collegestudent*>(student)->getcollegeenglish();
			else if (subject == "design")
				sum =sum+ dynamic_cast<collegestudent*>(student)->getdesign();
			else if (subject == "highermath")
				sum =sum+ dynamic_cast<collegestudent*>(student)->gethighermath();
			count++;
		}
	}
	if (count > 0) {
		return (double)sum / count;
	}
	else return 0;
}

//计算小学生单科平均分
double management::primaryaveragescore(const string& subject) {
	int count = 0;
	int sum = 0;
	for (const auto& student : students) {
//const表示这个变量是常量，不能通过这个变量修改所引用的对象
//auto 自动类型推导关键字，让编译器根据初始化的值自动推断变量的类型。根据students容器中存储的元素类型确定student的类型
		if (dynamic_cast<primarystudent*>(student)) {
//dynamic_cast类型转换操作符，用于在继承层次结构中进行安全的向下转型（将基类指针或引用转换为派生类指针或引用）
			if (subject == "english") 
				sum =sum+ dynamic_cast<primarystudent*>(student)->getenglish();
			else if (subject == "math") 
				sum =sum+ dynamic_cast<primarystudent*>(student)->getmath();
			else if (subject == "chinese") 
				sum =sum+ dynamic_cast<primarystudent*>(student)->getchinese();
			count++;
		}
	}
	if (count > 0) {
		return (double)sum / count;
	}
	else return 0;
	//return count > 0 ? static_cast<double>(sum) / count : 0;
}

// 保存学生记录到文件
void management::savetofile() {
	ofstream outfile(filename); //创建一个输出文件流对象outfile，打开名为filename的文件
	if (outfile.is_open()) {//文件成功打开，is_open()返回true
		for (const auto& student : students) {//遍历容器students中的每个元素,const确保在循环体内不能修改学生对象
			outfile << student->getid() << "  " << student->getname() << "  " << student->getgender() << "  " << student->getage() << "  " << student->getclassname() << "  ";//将学生对象的属性写入到输出文件流中
//如果当前学生对象是primarystudent小学生类型，就将小学生的英语数学语文成绩写入文件流
			if (dynamic_cast<primarystudent*>(student)) {
				outfile << dynamic_cast<primarystudent*>(student)->getenglish() << "  "
					<< dynamic_cast<primarystudent*>(student)->getmath() << "  "
					<< dynamic_cast<primarystudent*>(student)->getchinese()<< endl;
			}
//如果是middlestudent中学生类型，就写入地理和历史成绩
			else if (dynamic_cast<middlestudent*>(student)) {
				outfile << dynamic_cast<middlestudent*>(student)->getgeography() << "  "
					<< dynamic_cast<middlestudent*>(student)->gethistory() << endl;
			}
			else if (dynamic_cast<collegestudent*>(student)) {
				outfile <<dynamic_cast<collegestudent*>(student)->getprofessional() << "  "
					<< dynamic_cast<collegestudent*>(student)->getcollegeenglish() << "  "
					<< dynamic_cast<collegestudent*>(student)->getdesign() << "  "
					<< dynamic_cast<collegestudent*>(student)->gethighermath() << endl;
			}
		}
		outfile.close();//完成所有学生信息的写入后
		cout << "保存成功！" << endl;
	}
	else {
		cout << "无法打开文件进行保存！" << endl;
	}
}
/*// 按总分排序
void management::sortbytotalscore() {
	sort(students.begin(), students.end(), [](student* a, student* b) {
//students.begin()和students.end()分别表示students容器中元素范围的起始和结束迭代器
		return a->totalscore() > b->totalscore();
//如果a的总成绩大于b的总成绩，就返回true，表示a应排在b的前面,否则返回false
		});
}*/

// 按总分排序
void management::sortbytotalscore(){
int n = students.size();
vector<student*> sortedstudents = students;//创建一个临时容器用于存储排序后的结果
for (int i = 0; i < n - 1; ++i) {//冒泡排序
	for (int j = 0; j < n - i - 1; ++j) {
		if (sortedstudents[j]->totalscore() < sortedstudents[j + 1]->totalscore()) {//交换元素位置
			student* temp = sortedstudents[j];
			sortedstudents[j] = sortedstudents[j + 1];
			sortedstudents[j + 1] = temp;
		}
	}
}
for (const auto& student : sortedstudents) {// 输出排序后的结果（仅在本次函数调用中按排序后顺序输出，不改变原容器顺序）
	student->show();}
}

//从文件读取学生记录
void management::readfromfile() {
	ifstream infile(filename); //创建一个输入文件流对象inFile，并打开名为filename的文件
	if (infile.is_open()) {//检查文件是否成功打开
		students.clear(); //在开始读取新的文件内容之前，清空存储学生对象的容器students，确保没有残留的旧数据。
		string id;
		string name;
		string gender;
		string classname;
		int age;
		while (infile >> id >> name >> gender >> age >> classname) {//能够从文件中读取到有效的数据并存储到这些变量中，while 循环就继续执行
			student* newstudent = NULL; //声明一个student基类指针newstudent并初始化为NULL
			if (id[0] == 'p') {//通过判断读取到的学生id学号首字符判断学生类型
				int englishscore, mathscore, chinesescore;//声明三个整数变量，分别用于存储小学生的英语数学语文成绩
				infile >> englishscore >> mathscore >> chinesescore;
				newstudent = new primarystudent(englishscore, mathscore, chinesescore);
			}
			else if (id[0] == 'm') {
				int geographyscore, historyscore;
				infile >> geographyscore >> historyscore;
				newstudent = new middlestudent(geographyscore, historyscore);
			}
			else if (id[0] == 'c') {
				int professionalscore, collegeenglishscore, designscore, highermathscore;
				infile >> professionalscore >> collegeenglishscore >>designscore >> highermathscore;
				newstudent = new collegestudent(professionalscore, collegeenglishscore, designscore, highermathscore);
			}
			newstudent->setid(id);
			newstudent->setname(name);
			newstudent->setgender(gender);
			newstudent->setage(age);
			newstudent->setclassname(classname);
			students.push_back(newstudent);//新创建的学生对象添加到students容器中
		}
		infile.close();
		cout << "读取成功!" << endl;
	}
	else {
		cout << "无法打开文件进行读取!" << endl;
	}
}

// 按单科成绩排序
void management::sortbysubjectscore(string& subject) {
	sort(students.begin(), students.end(), [subject](student* a, student* b) {
		if (dynamic_cast<primarystudent*>(a) && dynamic_cast<primarystudent*>(b)) {//检查指针a和b是否可以安全地转换为PrimaryStudent小学生类型指针
			if (subject == "english") return dynamic_cast<primarystudent*>(a)->getenglish() > dynamic_cast<primarystudent*>(b)->getenglish();
			//如果subject为english就比较两个小学生对象的英语成绩并返回成绩高的学生排在前面的结果
			else if (subject == "math") return dynamic_cast<primarystudent*>(a)->getmath() > dynamic_cast<primarystudent*>(b)->getmath();
			else if (subject == "chinese") return dynamic_cast<primarystudent*>(a)->getchinese() > dynamic_cast<primarystudent*>(b)->getchinese();
		}
		else if (dynamic_cast<middlestudent*>(a) && dynamic_cast<middlestudent*>(b)) {
			if (subject == "geography") return dynamic_cast<middlestudent*>(a)->getgeography() > dynamic_cast<middlestudent*>(b)->getgeography();
			else if (subject == "history") return dynamic_cast<middlestudent*>(a)->gethistory() > dynamic_cast<middlestudent*>(b)->gethistory();
		}
		else if (dynamic_cast<collegestudent*>(a) && dynamic_cast<collegestudent*>(b)) {
			if (subject == "professional")
				return dynamic_cast<collegestudent*>(a)->getprofessional() > dynamic_cast<collegestudent*>(b)->getprofessional();
			else if (subject == "collegeenglish") return dynamic_cast<collegestudent*>(a)->getcollegeenglish() > dynamic_cast<collegestudent*>(b)->getcollegeenglish();
			else if (subject == "design") return dynamic_cast<collegestudent*>(a)->getdesign() > dynamic_cast<collegestudent*>(b)->getdesign();
			else if (subject == "highermath") return dynamic_cast<collegestudent*>(a)->gethighermath() > dynamic_cast<collegestudent*>(b)->gethighermath();
		}
		return false;
		});
	printsortedbysubject(students, subject);
}

// 输出排序后的学生信息
void management::printsortedbysubject(vector<student*>& students, string& subject) {
//vector<student*>& students是引用类型的参数，存储学生对象指针的向量容器
//string& subject是引用类型的字符串参数，要进行排序和输出的学科名称。
	cout << "学生信息（按" << subject << "成绩从高到低）：" << endl;
	for (auto student : students) {//自动遍历容器中的所有元素，从第一个元素开始，依次将每个元素赋值给student，然后执行循环体中的代码，直至遍历完整个容器
		if (primarystudent* p = dynamic_cast<primarystudent*>(student)){//尝试将当前遍历到的学生对象指针student转换为primarystudent小学生类型指针并将结果赋值给p
			if (subject == "english") { 
				cout << "姓名：" << student->getname() << " 英语成绩：" << p->getenglish() << endl;}
			else if (subject == "math") {
				cout << "姓名：" << student->getname() << " 数学成绩：" << p->getmath() << endl;}
			else if (subject == "chinese") { 
				cout << "姓名：" << student->getname() << " 语文成绩：" << p->getchinese() << endl;}
			//else { cout << "学科输入有误！"<<endl; break; }
		}
		else if (middlestudent* m = dynamic_cast<middlestudent*>(student)) {
			if (subject == "geography") {
				cout << "姓名：" << student->getname() << ", 地理成绩：" << m->getgeography() << endl;}
			else if (subject == "history") {
				cout << "姓名：" << student->getname() << ", 历史成绩：" << m->gethistory() << endl;}
			//else { cout << "学科输入有误！"<<endl; break; }
		}
		else if (collegestudent* c = dynamic_cast<collegestudent*>(student)) {
			if (subject == "professional") cout << "姓名：" << student->getname() << ", 专业课程成绩：" << c->getprofessional() << endl;
			else if (subject == "collegeenglish") cout << "姓名：" << student->getname() << ", 英语成绩：" << c->getcollegeenglish() << endl;
			else if (subject == "design") cout << "姓名：" << student->getname() << ", 编程成绩：" << c->getdesign() << endl;
			else if (subject == "highermath") cout << "姓名：" << student->getname() << ", 高等数学成绩：" << c->gethighermath()<< endl;
			//else { cout << "学科输入有误！"<<endl; break; }
		}
        
	}
}

//注册登录
void login(){
	draw();
	getuserdata();
	buttonclick();
}

//主函数
int main() {
	int islogin = 0;
	while (!islogin) {
		login();
		if (verifyuserdata()) {
			islogin = 1;
			closegraph();
		}
	}
	management s("students.txt");
    s.readfromfile();
	int choice;
	do {
		cout << "*************************************************************************" << endl
		    <<"1.添加学生成绩" <<endl
			<<"2.查询学生成绩" << endl
			<<"3.显示所有学生成绩" << endl
			<<"4.编辑学生成绩" << endl
			<<"5.删除学生" << endl
			<<"6.统计(学生总数 总分 各科平均分)" << endl
			<<"7.保存到文件" << endl
			<<"8.按总成绩排序" << endl
			<<"9.按单科成绩排序" << endl
			<<"0.退出系统" << endl;
	    cout << "请选择功能（输入对应序号）" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
		{
			s.addstudent();
			break;
		}
		case 2:
			s.searchstudent();
			break;
		case 3:
			s.showall();
			break;
		case 4:
			s.editstudent();
			break;
		case 5:
			s.deletestudent();
			break;
		case 6:
			s.countstudents();
			//cout << "总分：" << s.totalscore() << endl;
			cout << "语文平均分：" << s.primaryaveragescore("chinese") << endl;
			cout << "数学平均分：" << s.primaryaveragescore("math") << endl;
			cout << "英语平均分：" << s.primaryaveragescore("english") << endl;
			cout << "地理平均分：" << s.middleaveragescore("geography") << endl;
			cout << "历史平均分：" << s.middleaveragescore("history") << endl;
			cout << "专业课平均分：" << s.collegeaveragescore("professional") << endl;
			cout << "大学英语课平均分：" << s.collegeaveragescore("collegeenglish") << endl;
			cout << "程序设计平均分：" << s.collegeaveragescore("design") << endl;
			cout << "高等数学平均分：" << s.collegeaveragescore("highermath") << endl;
			break;
		case 7:
			s.savetofile();
			break;
		case 8:
			s.sortbytotalscore();
			cout << "按总分排序完成。" << endl;
			break;
		case 9:
		{
			string subject;
			cout << "输入单科名称（如 english、math 等）：";
			cin >> subject;
			s.sortbysubjectscore(subject);
			cout << "按" << subject << "排序完成。" << endl;
			break;
		}
		case 0:
			cout << "退出系统" << endl;
			break;
		default:
			cout << "无效!" << endl;
		}
	} while (choice != 0);

	for (const auto& student : s.get()) {
		delete student;// 释放学生对象占用的内存
	}
	return 0;
}



