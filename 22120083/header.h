#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <windows.h>
#include <time.h>
#include <sstream>
#include <fstream>
#include <filesystem>

using namespace std;

struct date {
	int d, m, y;
};

struct Schoolyear
{
	int Sta_year, End_year;
};

struct Semester {
	int InforSemester;
	date Star, End;
	Schoolyear Sch_year;
};

struct User {
	bool isStaff;
	int  academic;
	string id;
	string pass; //123456
	string firstname;
	string lastname;
	string gender;
	string SocialID;
	string className;
	date birthday;
	
};

struct nodeUser{
	User data;
	nodeUser* prev;
	nodeUser* next;
};

struct listUser {
	nodeUser* head;
	nodeUser* tail;
};

struct CourseMark {
	float TotalMark;
	float FinalMark;
	float MidtermMark;
	float OtherMark;
};

struct StuCourse {
	string id;
	CourseMark Mark;
};

struct nodeStuCourse {
	StuCourse data;
	nodeStuCourse* next;
	nodeStuCourse* prev;
};

struct listStuCourse {
	nodeStuCourse* head;
	nodeStuCourse* tail;
};

struct Course {
	int Credits;
	int maxStudents = 50;
	string id;
	string CourseName;
	string ClassName;
	string TeacherName;
	string wDay;
	string Session;
	listStuCourse List_st;
	//int numberRegistered = 0;
	//int academicYear;
};

struct nodeCourse {
	Course data;
	nodeCourse* next;
	nodeCourse* prev;
};

struct listCourse {
	nodeCourse* head;
	nodeCourse* tail;
};

struct Student {
	int  academic;
	string id;
	string firstname;
	string lastname;
	string gender;
	string SocialID;
	string className;
	date birthday;
	listCourse LStu_Courses;
	//CourseMark courseMark;
	//SemesterMark semesterMark;
};

struct nodeStudent {
	Student data;
	nodeStudent* next;
	nodeStudent* prev;
};

struct listStudent {
	nodeStudent* head;
	nodeStudent* tail;
};

struct Class {
	string ClassName;
	string ClassPath;
	listStudent List_st;
	int  academic;
};

struct nodeClass {
	Class data;
	nodeClass* next;
	nodeClass* prev;
};

struct listClass {
	nodeClass* head;
	nodeClass* tail;
};

extern nodeUser* userLogin;
extern listUser l_User;
extern Schoolyear CurSchoolyear;
extern Semester CurSemester;
extern listClass l_Class;
extern listCourse l_Course;
extern listStudent l_AllStudent;
extern string PathSchoolyear;
extern string PathSemester;

//UI
void gotoXY(int x, int y);
void drawBox(int width, int height, int left, int top);
void textAlignCenter(string s, int left, int width, int y);
void notifyBox(string msg);

//Log
nodeUser* findUser(string id, string pass);
void loginUI(string& id, string& pass);
void solveLogin();

//System
date SttoDate(string st);
string DatetoSt(date dt);
void initList(listUser& l);
void initList(listStudent& l);
void initList(listClass& l);
void initList(listCourse& l);
void initList(listStuCourse& l);
nodeUser* createNodeUser(User val);
nodeStudent* createNodeStudent(Student val);
nodeClass* createNodeClass(Class val);
nodeCourse* createNodeCourse(Course val);
nodeStuCourse* createNodeStuCourse(StuCourse val);
void addUser(listUser& l, nodeUser* user);
void addStudent(listStudent& l, nodeStudent* Stu);
void addClass(listClass& l, nodeClass* cla);
void addCourse(listCourse& l, nodeCourse* Cour);
void addStuCourse(listStuCourse& l, nodeStuCourse* val);
void removeStuCourse(listStuCourse& l, nodeStuCourse* key);
void removeCourse(listCourse& l, nodeCourse* key);
nodeStuCourse* Find(listStuCourse& l, string key);
nodeStudent* Find(listStudent& l, string key);
nodeUser* inputUser(fstream& f);
nodeStudent* inputStudent(fstream& f, int aca, string cla_name);
nodeClass* inputClass(fstream& f);
nodeStuCourse* inputStuCourse(fstream& f);
nodeCourse* inputCourse(fstream& f, string Path);
void getListUsers(listUser& l);
void getListStudent(listStudent& l, string Path, int aca, string cla_name);
void getListClass(listClass& l, string PathSchoolyear);
void getListStuCourse(listStuCourse& l, string Path);
void getListCourse(listCourse& l, string Path);
void getListAllStudent(listStudent& l, listClass& lClass);
void UpdateListUsers(listUser l);
void UpdateListStudent(string PathClass, listStudent l);
void UpdateListClass(string PathSchoolyear, listClass l);
void UpdateListStuCourse(string PathCourse, listStuCourse l);
void UpdateListCourse(string PathSemester, listCourse l);
void MergeList(listStudent& x, listStudent& y);
void MergeList(listClass& x, listClass& y);
void AddListUsers(listUser& l_Us, listStudent l_St);

//Staff
void staffMenu();
void LoadStaffMenu();
void ProfileStaff();
void changePassword();
void logout();
void CreateSchoolYear();
void SchoolYearMenu();
void LoadSchoolYear();
void CreateNewClass();
void NewStudentMenu(string st);
void LoadNewStudent();
void ANewStudent(nodeClass*& toClass);
void CSVStudent(nodeClass*& toClass);

void CreateSemester();
void SemesterMenu();
void LoadSemester();
void ANewCourse();

void CourseMenu();
void LoadCourseMenu();
void Student_CourseMenu(string st);
void LoadStudent_Course();
void AddStudentCourse(nodeCourse* toCourse);
void RemoveStudentCourse(nodeCourse* toCourse);
void CSVStudentCourse(nodeCourse*& toCourse);
void DeleteCourse();
void UpdateCourseMenu(Course val);
void LoadUpdateCourse();
string UpdateCourse(string st);
void ViewCourse();
void ViewMenu();
void LoadViewMenu();
void ViewClass();
void LoadViewStudentClass();
void ViewStudentClass(listStudent l, string st);
void LoadViewStudentCourse();
void ViewStudentCourse(listStuCourse l, string st);
void LoadViewClassMark();
void ViewClassMark(listStudent l, string st);
void LoadExportCourse();
void ExportCourse(listStuCourse l, string st);
void LoadImportCourse();
void ImportCourse(listStuCourse& l, string st);
void UpdateMarkMenu(CourseMark& val);
void LoadUpdateMark_1();
void LoadUpdateMark_2(nodeCourse*& toCourse);
float UpdateMark(string st);

void studentMenu();
void LoadStudentMenu();
void ProfileStudent();
void ViewCourseStudent();
void View_scoreboard();
