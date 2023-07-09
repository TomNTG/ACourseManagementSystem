#include "header.h"

nodeStudent* stmain=NULL;

void studentMenu() {
	/*
	1. View profile info
	2. Change the password
	3. View course
	4. View scoreboard
	5. Log out
	0. EXIT
	*/
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int yPos = 10;
	system("cls");
	drawBox(width, height, left, top);
	textAlignCenter("WELCOME", left, width, 5);
	textAlignCenter(userLogin->data.lastname + ' ' + userLogin->data.firstname, left, width, 6);
	gotoXY(50, yPos);
	cout << "1. View profile info\n";
	yPos++;
	gotoXY(50, yPos);
	cout << "2. Change the password\n";
	yPos++;
	gotoXY(50, yPos);
	cout << "3. View course\n";
	yPos++;
	gotoXY(50, yPos);
	cout << "4. View scoreboard\n";
	yPos++;
	gotoXY(50, yPos);
	cout << "5. Log out\n";
	yPos += 2;
	gotoXY(50, yPos);
	cout << "0. EXIT\n";
}

void LoadStudentMenu() {
	fstream f;
	f.open("DATA/INFOR.txt", ios::in);
	f >> CurSchoolyear.Sta_year >> CurSchoolyear.End_year;
	f.close();
	PathSchoolyear = "DATA\\" + to_string(CurSchoolyear.Sta_year)
		+ '-' + to_string(CurSchoolyear.End_year);
	f.open(PathSchoolyear + "\\Semester.txt", ios::in);
	if (!f.is_open()) CurSemester.InforSemester = 0;
	else {
		string st;
		getline(f, st, ',');
		CurSemester.InforSemester = stoi(st);
		getline(f, st, ',');
		CurSemester.Star = SttoDate(st);
		getline(f, st, '\n');
		CurSemester.End = SttoDate(st);
		CurSemester.Sch_year = CurSchoolyear;
		PathSemester = PathSchoolyear + "\\Semester" + to_string(CurSemester.InforSemester);
	}
	getListCourse(l_Course, PathSemester);
	getListClass(l_Class, PathSchoolyear);
	getListAllStudent(l_AllStudent, l_Class);
	nodeStudent* tmpStu = l_AllStudent.head;
	while (tmpStu != NULL) {
		initList(tmpStu->data.LStu_Courses);
		tmpStu = tmpStu->next;
	}
	nodeCourse* tmp = l_Course.head;
	while (tmp != NULL) {
		nodeStuCourse* t1 = tmp->data.List_st.head;
		while (t1 != NULL) {
			nodeStudent* tStu = Find(l_AllStudent, t1->data.id);
			if (tStu != NULL) {
				addCourse(tStu->data.LStu_Courses, createNodeCourse(tmp->data));
			}
			t1 = t1->next;
		}
		tmp = tmp->next;
	}
	stmain = Find(l_AllStudent, userLogin->data.id);
	do {
		studentMenu();
		gotoXY(40, 19);
		int cur = -1;
		cout << "Enter your choice (0-5): ";
		cin >> cur;
		switch (cur) {
		case 1: //View profile info
		{
			ProfileStudent();
			break;
		}
		case 2: //Change the password
		{
			changePassword();
			break;
		}
		case 3: //View course
		{
			ViewCourseStudent();
			break;
		}
		case 4: //View scoreboard
		{
			View_scoreboard();
			break;
		}
		case 5: //Log out
		{
			logout();
			break;
		}
		case 0: //EXIT
		{
			gotoXY(0, 20);
			exit(0);
			break;
		}
		default: {
			gotoXY(40, 20);
			cout << "Error!";
			gotoXY(40, 21);
			system("pause");
			break;
		}
		}
	} while (1);
}

//Profile
void ProfileStudent() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int yPos = 10;
	system("cls");
	textAlignCenter("PROFILE", left, width, yPos - 3);
	drawBox(width, height, left, top);
	gotoXY(50, yPos);
	cout << "First name: " << userLogin->data.firstname;
	yPos++;
	gotoXY(50, yPos);
	cout << "Last name: " << userLogin->data.lastname;
	yPos++;
	gotoXY(50, yPos);
	cout << "Gender: " << userLogin->data.gender;
	yPos++;
	gotoXY(50, yPos);
	cout << "Student ID: " << userLogin->data.id;
	yPos++;
	gotoXY(50, yPos);
	cout << "Social ID: " << userLogin->data.SocialID;
	yPos++;
	gotoXY(50, yPos);
	cout << "Date of Birth: "
		<< userLogin->data.birthday.d
		<< '/' << userLogin->data.birthday.m
		<< '/' << userLogin->data.birthday.y;
	yPos += 4;
	gotoXY(46, yPos);
	system("pause");
}

void ViewCourseStudent() {
	const int width = 112;
	int height = 3;
	const int left = 3;
	const int top = 9;

	int yPos = 10;
	system("cls");
	textAlignCenter("Course", left, width, 6);
	gotoXY(5, yPos);
	cout << "No";
	gotoXY(7, yPos);
	cout << "|Course ID";
	gotoXY(18, yPos);
	cout << "|Course name";
	gotoXY(31, yPos);
	cout << "|Class name";
	gotoXY(43, yPos);
	cout << "|      Teacher name";
	gotoXY(67, yPos);
	cout << "|Credits";
	gotoXY(76, yPos);
	cout << "|Max students";
	gotoXY(90, yPos);
	cout << "|Day of the week";
	gotoXY(107, yPos);
	cout << "|Session";
	string st = string(112, '-');
	yPos++;
	gotoXY(4, yPos);
	cout << st;
	nodeCourse* tmp = stmain->data.LStu_Courses.head;
	yPos++;
	int cnt = 0;
	while (tmp != NULL) {
		cnt++;
		gotoXY(5, yPos);
		cout << cnt;
		gotoXY(7, yPos);
		cout << '|' << tmp->data.id;
		gotoXY(18, yPos);
		cout << '|' << tmp->data.CourseName;
		gotoXY(31, yPos);
		cout << '|' << tmp->data.ClassName;
		gotoXY(43, yPos);
		cout << '|' << tmp->data.TeacherName;
		gotoXY(67, yPos);
		cout << "|   " << tmp->data.Credits;
		gotoXY(76, yPos);
		cout << "|     " << tmp->data.maxStudents;
		gotoXY(90, yPos);
		cout << "|      " << tmp->data.wDay;
		gotoXY(107, yPos);
		cout << "|   " << tmp->data.Session;
		tmp = tmp->next;
		yPos++;
	}
	height = cnt + 3;
	drawBox(width, height, left, top);
	if (cnt == 0) {
		notifyBox("Empty!");
		return;
	}
	gotoXY(50, 10 + height + 2);
	system("pause");
}

void View_scoreboard() {
	const int width = 100;
	int height = 3;
	const int left = 10;
	const int top = 9;

	int yPos = 10;
	system("cls");
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), left, width, 6);
	gotoXY(12, yPos);
	cout << "No";
	gotoXY(14, yPos);
	cout << "|Course ID";
	gotoXY(25, yPos);
	cout << "|Class name";
	gotoXY(37, yPos);
	cout << "|Course name";
	gotoXY(60, yPos);
	cout << "|Total Mark";
	gotoXY(72, yPos);
	cout << "|Final Mark";
	gotoXY(84, yPos);
	cout << "|Midterm Mark";
	gotoXY(98, yPos);
	cout << "|Other Mark";
	string t = string(100, '-');
	yPos++;
	gotoXY(11, yPos);
	cout << t;
	nodeCourse* tmp = stmain->data.LStu_Courses.head;
	yPos++;
	int cnt = 0;
	while (tmp != NULL) {
		cnt++;
		gotoXY(12, yPos);
		cout << cnt;
		gotoXY(14, yPos);
		cout << '|' << tmp->data.id;
		gotoXY(25, yPos);
		cout << '|' << tmp->data.ClassName;
		gotoXY(37, yPos);
		cout << '|' << tmp->data.CourseName;
		nodeStuCourse* k = Find(tmp->data.List_st, stmain->data.id);
		gotoXY(60, yPos);
		cout << "|    " << k->data.Mark.TotalMark;
		gotoXY(72, yPos);
		cout << "|    " << k->data.Mark.FinalMark;
		gotoXY(84, yPos);
		cout << "|     " << k->data.Mark.MidtermMark;
		gotoXY(98, yPos);
		cout << "|    " << k->data.Mark.OtherMark;
		tmp = tmp->next;
		yPos++;
	}
	height = cnt + 3;
	drawBox(width, height, left, top);
	if (cnt == 0) {
		notifyBox("Empty!");
		return;
	}
	gotoXY(50, 10 + height + 2);
	system("pause");
}