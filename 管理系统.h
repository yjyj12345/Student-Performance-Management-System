#pragma once
#include<iostream>//输入输出流的头文件
#include<fstream>
#include<string>
#include<vector>//向量容器的头文件
#include<algorithm>//算法库的头文件
#include<iomanip>
#include <graphics.h>
#include <conio.h>
#include <sstream>
#include<windows.h>
using namespace std;
int width = 800;// 定义窗口大小
int height = 600;
string username;
string password;// 全局变量用于存储输入的用户名和密码
string userfilename = "userdata.txt";// 文件名
void draw();// 绘制注册登录界面
void getuserdata();// 用户名和密码输入
void saveuserdata();// 将用户信息保存到文件
int verifyuserdata();// 从文件中读取用户信息并验证
void buttonclick();// 判断鼠标位置是否点击按钮

//学生类（抽象基类）
class student {
protected:
	string id;
	string name;
	string gender;
	int age;
	string classname;
public:
	student(string ID=" ", string NAME=" ", string G=" ", int AGE=0, string C=" ") :id(ID), name(NAME), gender(G), age(AGE), classname(C) {}
	virtual void show()=0;
	virtual void input()=0;
	virtual int totalscore() = 0;
    string getid() { return id; }
	void setid(string& ID) { id = ID; }
	string getname() { return name; }
	void setname(string& NAME) { name = NAME; }
	string getgender() { return gender; }
	void setgender(string& G) { gender = G; }
	int getage() { return age; }
	void setage(int AGE) { age = AGE; }
	string getclassname() { return classname; }
	void setclassname(string& C) { classname = C; }
	virtual ~student(){}
};

//小学生类
class primarystudent :public virtual student {
protected:
	int english;
	int math;
	int chinese;
public:
	primarystudent(string ID, string NAME, string G, int AGE, string C,int E,int M,int CH):student(ID, NAME, G,AGE,C), english(E),math(M), chinese(CH){}
	primarystudent(int englishscore, int mathscore, int chinesescore) : english(englishscore), math(mathscore), chinese(chinesescore) {}
	void show() { cout << "小学生 学号：" << id << " 姓名：" << name << " 性别：" << gender << " 年龄：" << age << " 班级：" << classname << " 英语成绩：" << english << " 数学成绩：" << math << " 语文成绩：" << chinese << endl; }
	void input() {
		cout << "请输入该小学生的学生信息" << endl;
		cout << "学号（以p开头）："; cin >> id;
		cout << "姓名："; cin >> name;
		cout << "性别："; cin >> gender;
		cout << "年龄："; cin >> age;
		cout << "班级："; cin >> classname;
		cout << "英语成绩："; cin >> english;
		cout << "数学成绩："; cin >> math;
		cout << "语文成绩："; cin >> chinese;
	}
	int totalscore(){return english+math+chinese; }
	int getenglish() { return english; }
	int getmath() { return math; }
	int getchinese() { return chinese; }
};

//中学生类
class middlestudent :public virtual student {
protected:
	int geography;
	int history;
public:
	middlestudent(string ID, string NAME, string G, int AGE, string C, int GEO, int H) :student(ID, NAME, G, AGE, C),geography(GEO),history(H){}
	middlestudent(int geographyscore, int historyscore) : geography(geographyscore), history(historyscore) {}
	void show() { cout << "中学生 学号：" << id << " 姓名：" << name << " 性别：" << gender << " 年龄：" << age << " 班级：" << classname << " 地理成绩：" << geography << " 历史成绩：" << history << endl; }
	void input() {
		cout << "请输入该中学生的学生信息" << endl;
		cout << "学号（以m开头）："; cin >> id;
		cout << "姓名："; cin >> name;
		cout << "性别："; cin >> gender;
		cout << "年龄："; cin >> age;
		cout << "班级："; cin >> classname;
		cout << "地理成绩："; cin >> geography;
		cout << "历史成绩："; cin >> history;
	}
	int totalscore() { return geography + history; }
	int getgeography() { return geography; }
	int gethistory() { return history; }
};

//大学生类
class collegestudent :public virtual student {
protected:
	int professional;
	int collegeenglish;
	int design;
	int highermath;
public:
	collegestudent(string ID, string NAME, string G, int AGE, string C, int PRO, int CE,int D,int HM) :student(ID, NAME, G, AGE, C), professional(PRO), collegeenglish(CE), design(D),highermath(HM){}
	collegestudent(int professionalscore, int collegeenglishscore, int designscore, int highermathscore) :
		professional(professionalscore), collegeenglish(collegeenglishscore),design(designscore), highermath(highermathscore) {}
	void show() { cout << "大学生 学号：" << id << " 姓名：" << name << " 性别：" << gender << " 年龄：" << age << " 班级：" << classname << " 专业课成绩：" << professional << " 大学英语成绩：" << collegeenglish << " 程序设计成绩：" << design << "高等数学成绩" << highermath << endl; }
	void input() {
		cout << "请输入该大学生的学生信息" << endl;
		cout << "学号（以c开头）："; cin >> id;
		cout << "姓名："; cin >> name;
		cout << "性别："; cin >> gender;
		cout << "年龄："; cin >> age;
		cout << "班级："; cin >> classname;
		cout << "专业课成绩："; cin >> professional;
		cout << "大学英语成绩："; cin >> collegeenglish;
		cout << "程序设计成绩："; cin >> design;
		cout << "高等数学成绩："; cin >> highermath;
	}
	int getprofessional() { return professional; }
	int getcollegeenglish () { return collegeenglish; }
	int getdesign() { return design; }
	int gethighermath() { return highermath; }
	int totalscore() { return professional + collegeenglish + design + highermath; }
	//void setprofessional(int score) { professional = score; }
	//void setcollegeenglish(int score) { collegeenglish = score; }
	//void setdesign(int score) { design = score; }
	//void sethighermath(int score) { highermath = score; }
	//void setid(string& ID) { id = ID; }
	//void setname(string& NAME) { name = NAME; }
	//void setgender(string& G) { gender = G; }
	//void setage(int AGE) { age = AGE; }
	//void setclassname(string& C) { classname = C; }
};

//学生信息管理类
class management {
protected:
	vector<student*>students; //student* 表示指向 student 类型对象的指针.vector 容器将用来存放指向 student 类型对象的指针
	string filename;
public:
	management(const string &file):filename(file){}
	vector< student*>& get() { return students; }
	void addstudent();//添加学生
	void searchstudent();//查询学生
	void showall(); // 显示所有学生
	void editstudent();// 编辑学生
	void deletestudent();// 删除学生
	void countstudents();// 统计学生人数
	//int totalscore();// 计算总分
	double primaryaveragescore(const string& subject); // 计算单科平均分
	double middleaveragescore(const string& subject); // 计算单科平均分
	double collegeaveragescore(const string& subject); // 计算单科平均分
	void savetofile();// 保存学生记录到文件
	void readfromfile();// 从文件读取学生记录
	void sortbytotalscore();// 按总分排序
	void sortbysubjectscore(string& subject);//// 按单科成绩排序
	void printsortedbysubject(vector<student*>& students, string& subject);//// 输出按照单科排序后的学生信息
};	
