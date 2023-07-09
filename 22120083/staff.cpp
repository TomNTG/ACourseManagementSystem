#include "header.h"

Schoolyear CurSchoolyear;
Semester CurSemester;
listClass l_Class;
listCourse l_Course;
string PathSchoolyear = "";
string PathSemester = "";
listClass l_NewClass;
listStudent l_AllStudent;

void staffMenu() {
	/*
	1. View profile info
	2. Change the password
	3. Create a school year
	4. Create a semester
	5. Course
	6. View
	7. Log out
	0. EXIT
	*/
	const int width = 40;
	const int height = 12;
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
	cout << "3. Create a school year\n";
	yPos++;
	gotoXY(50, yPos);
	cout << "4. Create a semester\n";
	yPos++;
	gotoXY(50, yPos);
	cout << "5. Course\n";
	yPos++;
	gotoXY(50, yPos);
	cout << "6. View\n";
	yPos++;
	gotoXY(50, yPos);
	cout << "7. Log out\n";
	yPos += 2;
	gotoXY(50, yPos);
	cout << "0. EXIT\n";
}

void LoadStaffMenu() {
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
	do {
		staffMenu();
		gotoXY(40, 21);
		int cur = -1;
		cout << "Enter your choice (0-7): ";
		cin >> cur;
		switch (cur) {
		case 1: //View profile info
		{
			ProfileStaff();
			break;
		}
		case 2: //Change the password
		{
			changePassword();
			break;
		}
		case 3: //Create a school year
		{
			CreateSchoolYear();
			break;
		}
		case 4: //Create a semester
		{
			CreateSemester();
			break;
		}
		case 5: //Course
		{
			LoadCourseMenu();
			break;
		}
		case 6: //View
		{
			LoadViewMenu();
			break;
		}
		case 7: //Log out
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
			gotoXY(40, 22);
			cout << "Error!";
			gotoXY(40, 23);
			system("pause");
			break;
		}
		}
	} while (1);
}

//Profile
void ProfileStaff() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int yPos = 10;
	system("cls");
	textAlignCenter("PROFILE", left, width, yPos-3);
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
	cout << "Staff ID: " << userLogin->data.id;
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

//Change Password
void changePassword() {
	const int width = 40;
	const int height = 7;
	const int left = 40;
	const int top = 8;
	string OldPass;
	do {
		system("cls");
		textAlignCenter("Change Password", left, width, 7);
		drawBox(width, height, left, top);
		gotoXY(45, 10); 
		cout << "Old password: ";
		cin >> OldPass;
		if (OldPass == userLogin->data.pass) {
			gotoXY(45, 12); cout << "New password: ";
			cin >> userLogin->data.pass;
			notifyBox("Successful");
			UpdateListUsers(l_User);
			return;
		}
		else {
			do{
				system("cls");
				drawBox(width, height, left, top);
				textAlignCenter("Wrong password!", left, width, 10);
				gotoXY(50, 12);
				cout << "0. Try again";
				gotoXY(50, 13);
				cout << "1. Back";
				gotoXY(45, 16);
				int key = -1;
				cout << "Enter your choice (0-1): ";
				cin >> key;
				if (key == 0) break;
				else if (key == 1) return;
				else {
					gotoXY(45, 17);
					cout << "Error!";
					gotoXY(45, 18);
					system("pause");
				}
			} while (1);
		}
	} while (1);
}

//Log out
void logout() {
	userLogin = NULL;
	solveLogin();
}

//Create a school year
void CreateSchoolYear() {
	system("cls");
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 10;
	int yPos = 13;

	drawBox(40, 8, 40, 10);
	gotoXY(48, yPos);
	cout << "Start year:";
	gotoXY(48, yPos + 2);
	cout << "End year:";
	gotoXY(62, yPos);
	cin >> CurSchoolyear.Sta_year;
	gotoXY(62, yPos + 2);
	cin >> CurSchoolyear.End_year;
	PathSchoolyear = "DATA\\" + to_string(CurSchoolyear.Sta_year) 
		+ '-' + to_string(CurSchoolyear.End_year);
	string PathOldSchoolyear = "DATA\\" + to_string(CurSchoolyear.Sta_year - 1) + '-' + to_string(CurSchoolyear.End_year - 1);
	if (filesystem::exists(PathOldSchoolyear))
		getListClass(l_Class, PathOldSchoolyear);
	filesystem::create_directories(PathSchoolyear);
	LoadSchoolYear();
	nodeClass* t = l_NewClass.head;
	while (t != NULL) {
		AddListUsers(l_User, t->data.List_st);
		t = t->next;
	}
	UpdateListUsers(l_User);
	MergeList(l_Class, l_NewClass);
	UpdateListClass(PathSchoolyear, l_Class);
	fstream f;
	f.open("DATA/INFOR.txt", ios::out);
	f << CurSchoolyear.Sta_year << '\n' << CurSchoolyear.End_year;
	f.close();
	CurSemester.InforSemester = 0;
	notifyBox("Successful");
}

void SchoolYearMenu() {
	/*
	1. Create a new class
	2. Add new students
	0. Save
	*/
	const int width = 50;
	const int height = 7;
	const int left = 35;
	const int top = 8;

	int yPos = 10;
	system("cls");
	drawBox(30, height, 55, 8);
	nodeClass* tmp = l_NewClass.head;
	int cnt = 0;
	while (tmp != NULL) {
		gotoXY(39, yPos);
		cnt++;
		cout << cnt << ". " << tmp->data.ClassName;
		tmp = tmp->next;
		yPos++;
	}
	drawBox(15, cnt < 5 ? height : cnt + 3, 35, 8);
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), 35, 50, 6);
	gotoXY(60, 10);
	cout << "1. Create a new class\n";
	gotoXY(60, 11);
	cout << "2. Add new students\n";
	gotoXY(60, 13);
	cout << "0. Save\n";
}

void LoadSchoolYear() {
	initList(l_NewClass);
	do {
		SchoolYearMenu();
		gotoXY(55, 16);
		int cur = -1;
		cout << "Enter your choice (0-2): ";
		cin >> cur;
		switch (cur) {
		case 1: //Create a new class
		{
			CreateNewClass();
			break;
		}
		case 2: //Add new students
		{
			LoadNewStudent();
			break;
		}
		case 0: //Save
		{
			return;
			break;
		}
		default: {
			gotoXY(55, 17);
			cout << "Error!";
			gotoXY(55, 18);
			system("pause");
			break;
		}
		}
	} while (1);
}

void CreateNewClass() {
	system("cls");
	int width = 30;
	int height = 4;
	int left = 45;
	int top = 8;
	drawBox(width, height, left, top);
	Class NewClass;
	gotoXY(50, 10);
	cout << "Class name:";
	gotoXY(62, 10);
	cin >> NewClass.ClassName;
	NewClass.ClassPath = PathSchoolyear + '\\' + NewClass.ClassName + ".csv";
	initList(NewClass.List_st);
	NewClass.academic = CurSchoolyear.Sta_year;
	addClass(l_NewClass, createNodeClass(NewClass));
}

void NewStudentMenu(string st) {
	/*
	1. Add a new student
	2. Import a CSV file
	0. Back
	*/
	const int width = 40;
	const int height = 7;
	const int left = 40;
	const int top = 8;

	int yPos = 10;
	system("cls");
	drawBox(width, height, left, top);
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), left, width, 5);
	textAlignCenter(st, left, width, 6);
	gotoXY(50, 10);
	cout << "1. Add a new student\n";
	gotoXY(50, 11);
	cout << "2. Import a CSV file\n";
	gotoXY(50, 13);
	cout << "0. Back\n";
}

void LoadNewStudent() {
	nodeClass* toClass = NULL;
	while (1) {
		const int width = 50;
		const int height = 7;
		const int left = 35;
		const int top = 8;
		int yPos = 10;
		system("cls");
		drawBox(45, height, 55, 8);
		nodeClass* tmp = l_NewClass.head;
		int cnt = 0;
		while (tmp != NULL) {
			gotoXY(39, yPos);
			cnt++;
			cout << cnt << ". " << tmp->data.ClassName;
			tmp = tmp->next;
			yPos++;
		}
		drawBox(15, cnt < 5 ? height : cnt + 3, 35, 8);
		textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), 35, 50, 6);
		if (cnt == 0) {
			notifyBox("Empty!");
			return;
		}
		int key = -1;
		gotoXY(57, 11);
		cout << "Enter the class of your choice (1-" << cnt << "): ";
		cin >> key;
		if (key > 0 && key <= cnt) {
			toClass = l_NewClass.head;
			for (int i = 1; i < key; i++)
				toClass = toClass->next;
			break;
		}
		else {
			gotoXY(57, 12);
			cout << "Error!";
			gotoXY(57, 13);
			system("pause");
		}
	}
	do {
		NewStudentMenu(toClass->data.ClassName);
		gotoXY(40, 16);
		int cur = -1;
		cout << "Enter your choice (0-2): ";
		cin >> cur;
		switch (cur) {
		case 1: //Add a new student
		{
			ANewStudent(toClass);
			break;
		}
		case 2: //Import a CSV file
		{
			CSVStudent(toClass);
			break;
		}
		case 0: //Back
		{
			return;
			break;
		}
		default: {
			gotoXY(40, 17);
			cout << "Error!";
			gotoXY(40, 18);
			system("pause");
			break;
		}
		}
	} while (1);
}

void ANewStudent(nodeClass*& toClass) {
	/*
	Student ID
	Frist name 
	Last name
	Gender
	Date of Birth
	Social ID
	*/
	
	const int width = 50;
	const int height = 10;
	const int left = 35;
	const int top = 8;

	int yPos = 10;
	system("cls");
	drawBox(width, height, left, top);
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), left, width, 5);
	textAlignCenter(toClass->data.ClassName, left, width, 6);
	Student NewStudent;
	cin.ignore();
	gotoXY(40, yPos);
	cout << "Student ID: ";
	getline(cin, NewStudent.id);
	yPos++;
	gotoXY(40, yPos);
	cout << "Frist name: "; 
	getline(cin, NewStudent.firstname);
	yPos++;
	gotoXY(40, yPos);
	cout << "Last name: ";
	getline(cin, NewStudent.lastname);
	yPos++;
	gotoXY(40, yPos);
	cout << "Gender (Male/Female): ";
	getline(cin, NewStudent.gender);
	yPos++;
	gotoXY(40, yPos);
	cout << "Date of Birth (dd/mm/yyyy): ";
	string tmp;
	getline(cin, tmp);
	NewStudent.birthday = SttoDate(tmp);
	yPos ++;
	gotoXY(40, yPos);
	cout << "Social ID: ";
	getline(cin, NewStudent.SocialID);
	NewStudent.className = toClass->data.ClassName;
	NewStudent.academic = toClass->data.academic;
	addStudent(toClass->data.List_st, createNodeStudent(NewStudent));
	notifyBox("Successful");
}

void CSVStudent(nodeClass*& toClass) {
	const int width = 60;
	const int height = 5;
	const int left = 30;
	const int top = 8;

	system("cls");
	drawBox(width, height, left, top);
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), left, width, 5);
	textAlignCenter(toClass->data.ClassName, left, width, 6);
	textAlignCenter("Path of the CSV file:", left, width, 10);
	string PathCSV;
	gotoXY(32, 11);
	cout << "-> ";
	cin.ignore();
	getline(cin, PathCSV);
	fstream f;
	f.open(PathCSV, ios::in);
	if (!f) {
		notifyBox("FILE NOT EXISTS");
		return;
	}
	string s = "";
	getline(f, s);
	while (!f.eof())
		addStudent(toClass->data.List_st, inputStudent(f, toClass->data.academic, toClass->data.ClassName));
	f.close();
	notifyBox("Successful");
}


//Create a semester
void CreateSemester() {
	system("cls");
	const int width = 45;
	const int height = 7;
	const int left = 37;
	const int top = 10;
	int yPos = 12;

	drawBox(width, height, left, top);
	textAlignCenter("Semester", left, width, 8);
	gotoXY(40, yPos);
	cout << "Semester (1-3):";
	yPos++;
	gotoXY(40, yPos);
	cout << "School year:";
	yPos++;
	gotoXY(40, yPos);
	cout << "Start date (dd/mm/yyyy):";
	yPos++;
	gotoXY(40, yPos);
	cout << "End date (dd/mm/yyyy):";

	yPos = 12;
	string tmp="Semester (1-3):";
	gotoXY(42 + (int)tmp.size(), yPos);
	cin >> CurSemester.InforSemester;
	yPos++;
	tmp = "School year:";
	gotoXY(42 + (int)tmp.size(), yPos);
	string st;
	cin.ignore();
	getline(cin, st);
	CurSemester.Sch_year.Sta_year = stoi(st.substr(0, st.find('-')));
	st.erase(0, (int)st.find('-') + 1);
	CurSemester.Sch_year.End_year = stoi(st.substr(0, st.find('-')));
	yPos++;
	tmp = "Start date (dd/mm/yyyy):";
	gotoXY(42 + (int)tmp.size(), yPos);
	getline(cin, st);
	CurSemester.Star = SttoDate(st);
	yPos++;
	tmp = "End date (dd/mm/yyyy):";
	gotoXY(42 + (int)tmp.size(), yPos);
	getline(cin, st);
	CurSemester.End = SttoDate(st);

	CurSchoolyear = CurSemester.Sch_year;
	PathSchoolyear = "DATA\\" + to_string(CurSchoolyear.Sta_year)
		+ '-' + to_string(CurSchoolyear.End_year);
	PathSemester = PathSchoolyear + "\\Semester" + to_string(CurSemester.InforSemester);
	filesystem::create_directories(PathSemester);
	LoadSemester();
	UpdateListCourse(PathSemester, l_Course);
	fstream f;
	f.open(PathSchoolyear + "\\Semester.txt", ios::out);
	f << CurSemester.InforSemester << ','
		<< CurSemester.Star.d << '/' << CurSemester.Star.m << '/' << CurSemester.Star.y << ','
		<< CurSemester.End.d << '/' << CurSemester.End.m << '/' << CurSemester.End.y;
	f.close();
	notifyBox("Successful");
}

void SemesterMenu() {
	/*
	1. Add a course 
	0. Save
	*/
	const int width = 50;
	const int height = 6;
	const int left = 35;
	const int top = 8;

	int yPos = 10;
	system("cls");
	drawBox(30, height, 55, 8);
	nodeCourse* tmp = l_Course.head;
	int cnt = 0;
	while (tmp != NULL) {
		gotoXY(39, yPos);
		cnt++;
		cout << cnt << ". " << tmp->data.id;
		tmp = tmp->next;
		yPos++;
	}
	drawBox(15, cnt < 4 ? height : cnt + 3, 35, 8);
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), 35, 50, 6);
	gotoXY(60, 10);
	cout << "1. Add a course\n";
	gotoXY(60, 12);
	cout << "0. Save\n";
}

void LoadSemester() {
	initList(l_Course);
	do {
		SemesterMenu();
		gotoXY(55, 16);
		int cur = -1;
		cout << "Enter your choice (0-1): ";
		cin >> cur;
		switch (cur) {
		case 1: //Add a course
		{
			ANewCourse();
			break;
		}
		case 0: //Save
		{
			return;
			break;
		}
		default: {
			gotoXY(55, 17);
			cout << "Error!";
			gotoXY(55, 18);
			system("pause");
			break;
		}
		}
	} while (1);
}

void ANewCourse() {
	/*
	Course ID
	Course name
	Class name
	Teacher name
	Credits
	Max students: 50
	Day of the week
	Session
	*/

	const int width = 55;
	const int height = 12;
	const int left = 30;
	const int top = 8;

	int yPos = 10;
	system("cls");
	drawBox(width, height, left, top);
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), left, width, 5);
	textAlignCenter("Semester " + to_string(CurSemester.InforSemester), left, width, 6);
	Course NewCourse;
	gotoXY(35, yPos);
	cout << "Course ID:";
	yPos++;
	gotoXY(35, yPos);
	cout << "Course name:";
	yPos++;
	gotoXY(35, yPos);
	cout << "Class name:";
	yPos++;
	gotoXY(35, yPos);
	cout << "Teacher name:";
	yPos++;
	gotoXY(35, yPos);
	cout << "Credits:";
	yPos++;
	gotoXY(35, yPos);
	cout << "Max students: 50";
	yPos++;
	gotoXY(35, yPos);
	cout << "Day of the week (MON/TUE/WED/THU/FRI/SAT):";
	yPos++;
	gotoXY(35, yPos);
	cout << "Session (S1/S2/S3/S4):";
	yPos++;
	gotoXY(35, yPos);
	cout << "S1(07:30), S2(09:30), S3(13:30), S4(15:30)";

	yPos = 10;
	cin.ignore();
	string tmp = "Course ID:";
	gotoXY(37 + (int)tmp.size(),yPos);
	getline(cin, NewCourse.id);
	yPos++;
	tmp = "Course name:";
	gotoXY(37 + (int)tmp.size(), yPos);
	getline(cin, NewCourse.CourseName);
	yPos++;
	tmp = "Class name:";
	gotoXY(37 + (int)tmp.size(), yPos);
	getline(cin, NewCourse.ClassName);
	yPos++;
	tmp = "Teacher name:";
	gotoXY(37 + (int)tmp.size(), yPos);
	getline(cin, NewCourse.TeacherName);
	yPos++;
	tmp = "Credits:";
	gotoXY(37 + (int)tmp.size(), yPos);
	cin >> NewCourse.Credits;
	cin.ignore();
	yPos+=2;
	tmp = "Day of the week (MON/TUE/WED/THU/FRI/SAT):";
	gotoXY(37 + (int)tmp.size(), yPos);
	getline(cin, NewCourse.wDay);
	yPos++;
	tmp = "Session (S1/S2/S3/S4):";
	gotoXY(37 + (int)tmp.size(), yPos);
	getline(cin, NewCourse.Session);
	initList(NewCourse.List_st);
	addCourse(l_Course, createNodeCourse(NewCourse));
	notifyBox("Successful");
}


//Course
void CourseMenu() {
	/*
	1. View
	2. Update students
	3. Update course information
	4. Delete course
	5. Export CSV file
	6. Import CSV file
	7. Update a student's result
	0. BACK
	*/
	const int width = 40;
	const int height = 12;
	const int left = 40;
	const int top = 8;

	int yPos = 10;
	system("cls");
	drawBox(width, height, left, top);
	textAlignCenter("Course", left, width, 6);
	gotoXY(50, yPos);
	cout << "1. View\n";
	yPos++;
	gotoXY(50, yPos);
	cout << "2. Update students\n";
	yPos++;
	gotoXY(50, yPos);
	cout << "3. Update course information\n";
	yPos++;
	gotoXY(50, yPos);
	cout << "4. Delete course\n";
	yPos++;
	gotoXY(50, yPos);
	cout << "5. Export CSV file\n";
	yPos++;
	gotoXY(50, yPos);
	cout << "6. Import CSV file\n";
	yPos++;
	gotoXY(50, yPos);
	cout << "7. Update a student's result\n";
	yPos += 2;
	gotoXY(50, yPos);
	cout << "0. BACK\n";
}

void LoadCourseMenu() {
	PathSemester = PathSchoolyear + "\\Semester" + to_string(CurSemester.InforSemester);
	getListCourse(l_Course, PathSemester);
	getListClass(l_Class, PathSchoolyear);
	getListAllStudent(l_AllStudent, l_Class);
	do {
		CourseMenu();
		gotoXY(40, 21);
		int cur = -1;
		cout << "Enter your choice (0-7): ";
		cin >> cur;
		switch (cur) {
		case 1: //View
		{
			ViewCourse();
			break;
		}
		case 2: //Update students
		{
			LoadStudent_Course();
			UpdateListCourse(PathSemester, l_Course);
			break;
		}
		case 3: //Update course information
		{
			LoadUpdateCourse();
			UpdateListCourse(PathSemester, l_Course);
			break;
		}
		case 4: //Delete course
		{
			DeleteCourse();
			UpdateListCourse(PathSemester, l_Course);
			break;
		}
		case 5:
		{
			LoadExportCourse();
			break;
		}
		case 6:
		{
			LoadImportCourse();
			UpdateListCourse(PathSemester, l_Course);
			break;
		}
		case 7:
		{
			LoadUpdateMark_1();
			UpdateListCourse(PathSemester, l_Course);
			break;
		}
		case 0: //BACK
		{
			return;
			break;
		}
		default: {
			gotoXY(40, 22);
			cout << "Error!";
			gotoXY(40, 23);
			system("pause");
			break;
		}
		}
	} while (1);
}

void Student_CourseMenu(string st) {
	/*
	1. Add a student
	2. Remove a student
	3. Upload a CSV file
	0. Save
	*/
	const int width = 40;
	const int height = 8;
	const int left = 40;
	const int top = 8;

	int yPos = 10;
	system("cls");
	drawBox(width, height, left, top);
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), left, width, 5);
	textAlignCenter(st, left, width, 6);
	gotoXY(50, 10);
	cout << "1. Add a student\n";
	gotoXY(50, 11);
	cout << "2. Remove a student\n";
	gotoXY(50, 12);
	cout << "3. Upload a CSV file\n";
	gotoXY(50, 14);
	cout << "0. Save\n";
}

void LoadStudent_Course() {
	nodeCourse* toCourse = NULL;
	while (1) {
		const int width = 50;
		const int height = 8;
		const int left = 35;
		const int top = 8;

		int yPos = 10;
		system("cls");
		drawBox(35, height, 55, 8);
		nodeCourse* tmp = l_Course.head;
		int cnt = 0;
		while (tmp != NULL) {
			gotoXY(39, yPos);
			cnt++;
			cout << cnt << ". " << tmp->data.id;
			tmp = tmp->next;
			yPos++;
		}
		drawBox(15, cnt < 4 ? height : cnt + 3, 35, 8);
		textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), 35, 50, 6);
		if (cnt == 0) {
			notifyBox("Empty!");
			return;
		}
		int key = -1;
		gotoXY(57, 12);
		cout << "Enter the course (1-" << cnt << "): ";
		cin >> key;
		if (key > 0 && key <= cnt) {
			toCourse = l_Course.head;
			for (int i = 1; i < key; i++)
				toCourse = toCourse->next;
			break;
		}
		else {
			gotoXY(57, 13);
			cout << "Error!";
			gotoXY(57, 14);
			system("pause");
		}
	}
	do {
		Student_CourseMenu(toCourse->data.id);
		gotoXY(40, 17);
		int cur = -1;
		cout << "Enter your choice (0-3): ";
		cin >> cur;
		switch (cur) {
		case 1: //Add a student
		{
			AddStudentCourse(toCourse);
			break;
		}
		case 2: //Remove a student
		{
			RemoveStudentCourse(toCourse);
			break;
		}
		case 3: //Upload a CSV file
		{
			CSVStudentCourse(toCourse);
			break;
		}
		case 0: //Save
		{
			return;
			break;
		}
		default: {
			gotoXY(40, 18);
			cout << "Error!";
			gotoXY(40, 19);
			system("pause");
			break;
		}
		}
	} while (1);
}

void AddStudentCourse(nodeCourse* toCourse) {
	/*
	Student ID
	*/
	const int width = 50;
	const int height = 4;
	const int left = 35;
	const int top = 8;

	int yPos = 10;
	system("cls");
	drawBox(width, height, left, top);
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), left, width, 5);
	textAlignCenter(toCourse->data.id, left, width, 6);
	StuCourse NewStudent;
	cin.ignore();
	gotoXY(40, yPos);
	cout << "Student ID: ";
	getline(cin, NewStudent.id);
	addStuCourse(toCourse->data.List_st, createNodeStuCourse(NewStudent));
	notifyBox("Successful");
}

void RemoveStudentCourse(nodeCourse* toCourse) {
	/*
	Student ID
	*/
	const int width = 50;
	const int height = 4;
	const int left = 35;
	const int top = 8;

	int yPos = 10;
	system("cls");
	drawBox(width, height, left, top);
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), left, width, 5);
	textAlignCenter(toCourse->data.id, left, width, 6);
	string IDStudent;
	cin.ignore();
	gotoXY(40, yPos);
	cout << "Student ID: ";
	getline(cin, IDStudent);
	removeStuCourse(toCourse->data.List_st, Find(toCourse->data.List_st, IDStudent));
	notifyBox("Successful");
}

void CSVStudentCourse(nodeCourse*& toCourse) {
	const int width = 60;
	const int height = 5;
	const int left = 30;
	const int top = 8;

	system("cls");
	drawBox(width, height, left, top);
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), left, width, 5);
	textAlignCenter(toCourse->data.id, left, width, 6);
	textAlignCenter("Path of the CSV file:", left, width, 10);
	string PathCSV;
	gotoXY(32, 11);
	cout << "-> ";
	cin.ignore();
	getline(cin, PathCSV);
	fstream f;
	f.open(PathCSV, ios::in);
	if (!f) {
		notifyBox("FILE NOT EXISTS");
		return;
	}
	string s = "";
	getline(f, s);
	while (!f.eof()) {
		StuCourse NewStudent;
		getline(f, NewStudent.id,'\n');
		if (NewStudent.id != "")
			addStuCourse(toCourse->data.List_st, createNodeStuCourse(NewStudent));
	}
	f.close();
	notifyBox("Successful");
}

void DeleteCourse() {
	nodeCourse* toCourse = NULL;
	while (1) {
		const int width = 50;
		const int height = 8;
		const int left = 35;
		const int top = 8;

		int yPos = 10;
		system("cls");
		drawBox(35, height, 55, 8);
		nodeCourse* tmp = l_Course.head;
		int cnt = 0;
		while (tmp != NULL) {
			gotoXY(39, yPos);
			cnt++;
			cout << cnt << ". " << tmp->data.id;
			tmp = tmp->next;
			yPos++;
		}
		drawBox(15, cnt < 4 ? height : cnt + 3, 35, 8);
		textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), 35, 50, 6);
		if (cnt == 0) {
			notifyBox("Empty!");
			return;
		}
		int key = -1;
		gotoXY(57, 12);
		cout << "Enter the course (1-" << cnt << "): ";
		cin >> key;
		if (key > 0 && key <= cnt) {
			toCourse = l_Course.head;
			for (int i = 1; i < key; i++)
				toCourse = toCourse->next;
			break;
		}
		else {
			gotoXY(57, 13);
			cout << "Error!";
			gotoXY(57, 14);
			system("pause");
		}
	}
	removeCourse(l_Course, toCourse);
	notifyBox("Successful");
}

void UpdateCourseMenu(Course val) {
	/*
	1. Course ID
	2. Course name
	3. Class name
	4. Teacher name
	5. Credits
	6. Max students: 50
	7. Day of the week
	8. Session
	0. Save
	*/
	const int width = 55;
	const int height = 14;
	const int left = 30;
	const int top = 8;

	int yPos = 10;
	system("cls");
	drawBox(width, height, left, top);
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), left, width, 5);
	textAlignCenter(val.id, left, width, 6);
	gotoXY(32, yPos);
	cout << "1. Course ID: " << val.id;
	yPos++;
	gotoXY(32, yPos);
	cout << "2. Course name: " << val.CourseName;
	yPos++;
	gotoXY(32, yPos);
	cout << "3. Class name: " << val.ClassName;
	yPos++;
	gotoXY(32, yPos);
	cout << "4. Teacher name: " << val.TeacherName;
	yPos++;
	gotoXY(32, yPos);
	cout << "5. Credits: " << val.Credits;
	yPos++;
	gotoXY(32, yPos);
	cout << "6. Max students: " << val.maxStudents;
	yPos++;
	gotoXY(32, yPos);
	cout << "7. Day of the week (MON/TUE/WED/THU/FRI/SAT): " << val.wDay;
	yPos++;
	gotoXY(32, yPos);
	cout << "8. Session (S1/S2/S3/S4): " << val.Session;
	yPos++;
	gotoXY(32, yPos);
	cout << "S1(07:30), S2(09:30), S3(13:30), S4(15:30)";
	gotoXY(32, 20);
	cout << "0. Save\n";
}

void LoadUpdateCourse() {
	nodeCourse* toCourse = NULL;
	while (1) {
		const int width = 50;
		const int height = 8;
		const int left = 35;
		const int top = 8;

		int yPos = 10;
		system("cls");
		drawBox(35, height, 55, 8);
		nodeCourse* tmp = l_Course.head;
		int cnt = 0;
		while (tmp != NULL) {
			gotoXY(39, yPos);
			cnt++;
			cout << cnt << ". " << tmp->data.id;
			tmp = tmp->next;
			yPos++;
		}
		drawBox(15, cnt < 4 ? height : cnt + 3, 35, 8);
		textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), 35, 50, 6);
		if (cnt == 0) {
			notifyBox("Empty!");
			return;
		}
		int key = -1;
		gotoXY(57, 12);
		cout << "Enter the course (1-" << cnt << "): ";
		cin >> key;
		if (key > 0 && key <= cnt) {
			toCourse = l_Course.head;
			for (int i = 1; i < key; i++)
				toCourse = toCourse->next;
			break;
		}
		else {
			gotoXY(57, 13);
			cout << "Error!";
			gotoXY(57, 14);
			system("pause");
		}
	}
	do {
		UpdateCourseMenu(toCourse->data);
		gotoXY(30, 23);
		int cur = -1;
		cout << "Enter your choice (0-8): ";
		cin >> cur;
		switch (cur) {
		case 1:
		{
			toCourse->data.id = UpdateCourse("Course ID");
			break;
		}
		case 2:
		{
			toCourse->data.CourseName = UpdateCourse("Course name");
			break;
		}
		case 3:
		{
			toCourse->data.ClassName = UpdateCourse("Class name");
			break;
		}
		case 4:
		{
			toCourse->data.TeacherName = UpdateCourse("Teacher name");
			break;
		}
		case 5:
		{
			toCourse->data.Credits = stoi(UpdateCourse("Credits"));
			break;
		}
		case 6:
		{
			toCourse->data.maxStudents = stoi(UpdateCourse("Max students"));
			break;
		}
		case 7:
		{
			toCourse->data.wDay = UpdateCourse("Day of the week (MON/TUE/WED/THU/FRI/SAT)");
			break;
		}
		case 8:
		{
			toCourse->data.Session = UpdateCourse("Session (S1/S2/S3/S4)");
			break;
		}
		case 0: //Save
		{
			return;
			break;
		}
		default: {
			gotoXY(30, 24);
			cout << "Error!";
			gotoXY(30, 25);
			system("pause");
			break;
		}
		}
	} while (1);
}

string UpdateCourse(string st) {
	/*
	Course ID
	Course name
	Class name
	Teacher name
	Credits
	Max students: 50
	Day of the week
	Session
	*/

	/*
	Student ID
	*/
	const int width = 50;
	const int height = 4;
	const int left = 35;
	const int top = 8;

	int yPos = 10;
	system("cls");
	drawBox(width, height, left, top);
	string ans;
	cin.ignore();
	gotoXY(40, yPos);
	cout << st << ": ";
	getline(cin, ans);
	notifyBox("Successful");
	return ans;
}

void ViewCourse() {
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
	nodeCourse* tmp = l_Course.head;
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

//View
void ViewMenu() {
	/*
	1. Classes
	2. Students in a class
	3. Students in a course
	4. The scoreboard of a class
	0. BACK
	*/
	const int width = 40;
	const int height = 9;
	const int left = 40;
	const int top = 8;

	int yPos = 10;
	system("cls");
	drawBox(width, height, left, top);
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), left, width, 6);
	gotoXY(50, yPos);
	cout << "1. Classes\n";
	yPos++;
	gotoXY(50, yPos);
	cout << "2. Students in a class\n";
	yPos++;
	gotoXY(50, yPos);
	cout << "3. Students in a course\n";
	yPos++;
	gotoXY(50, yPos);
	cout << "4. The scoreboard of a class\n";
	yPos += 2;
	gotoXY(50, yPos);
	cout << "0. BACK\n";
}

void LoadViewMenu() {
	PathSemester = PathSchoolyear + "\\Semester" + to_string(CurSemester.InforSemester);
	getListCourse(l_Course, PathSemester);
	getListClass(l_Class, PathSchoolyear);
	getListAllStudent(l_AllStudent, l_Class);
	do {
		ViewMenu();
		gotoXY(40, 18);
		int cur = -1;
		cout << "Enter your choice (0-4): ";
		cin >> cur;
		switch (cur) {
		case 1: //Classes
		{
			ViewClass();
			break;
		}
		case 2: //Students in a class
		{
			LoadViewStudentClass();
			break;
		}
		case 3: //Students in a course
		{
			LoadViewStudentCourse();
			break;
		}
		case 4: //The scoreboard of a class
		{
			LoadViewClassMark();
			break;
		}
		case 0: //BACK
		{
			return;
			break;
		}
		default: {
			gotoXY(40, 19);
			cout << "Error!";
			gotoXY(40, 20);
			system("pause");
			break;
		}
		}
	} while (1);
}

void ViewClass() {
	const int width = 26;
	int height = 3;
	const int left = 45;
	const int top = 9;

	int yPos = 10;
	system("cls");
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), 35, 50, 6);
	gotoXY(47, yPos);
	cout << "No";
	gotoXY(50, yPos);
	cout << "|Class name";
	gotoXY(62, yPos);
	cout << "|Academic";
	string st = string(26, '-');
	yPos++;
	gotoXY(46, yPos);
	cout << st;
	nodeClass* tmp = l_Class.head;
	yPos++;
	int cnt = 0;
	while (tmp != NULL) {
		cnt++;
		gotoXY(47, yPos);
		cout << cnt;
		gotoXY(50, yPos);
		cout << "|  " << tmp->data.ClassName;
		gotoXY(62, yPos);
		cout << "|  " << tmp->data.academic;
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

void LoadViewStudentClass() {
	nodeClass* toClass = NULL;
	while (1) {
		const int width = 50;
		const int height = 7;
		const int left = 35;
		const int top = 8;
		int yPos = 10;
		system("cls");
		drawBox(45, height, 55, 8);
		nodeClass* tmp = l_Class.head;
		int cnt = 0;
		while (tmp != NULL) {
			gotoXY(39, yPos);
			cnt++;
			cout << cnt << ". " << tmp->data.ClassName;
			tmp = tmp->next;
			yPos++;
		}
		drawBox(15, cnt < 5 ? height : cnt + 3, 35, 8);
		textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), 35, 50, 6);
		if (cnt == 0) {
			notifyBox("Empty!");
			return;
		}
		int key = -1;
		gotoXY(57, 11);
		cout << "Enter the class of your choice (1-" << cnt << "): ";
		cin >> key;
		if (key > 0 && key <= cnt) {
			toClass = l_Class.head;
			for (int i = 1; i < key; i++)
				toClass = toClass->next;
			break;
		}
		else {
			gotoXY(57, 12);
			cout << "Error!";
			gotoXY(57, 13);
			system("pause");
		}
	}
	ViewStudentClass(toClass->data.List_st, toClass->data.ClassName);
}

void ViewStudentClass(listStudent l, string st) {
	const int width = 87;
	int height = 3;
	const int left = 20;
	const int top = 9;

	int yPos = 10;
	system("cls");
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), left, width, 6);
	textAlignCenter(st, left, width, 7);
	gotoXY(22, yPos);
	cout << "No";
	gotoXY(24, yPos);
	cout << "|ID";
	gotoXY(36, yPos);
	cout << "|First name";
	gotoXY(48, yPos);
	cout << "|      Last name";
	gotoXY(70, yPos);
	cout << "|Gender";
	gotoXY(79, yPos);
	cout << "|Day of Birth";
	gotoXY(93, yPos);
	cout << "|  Social ID";
	string t = string(87, '-');
	yPos++;
	gotoXY(21, yPos);
	cout << t;
	nodeStudent* tmp = l.head;
	yPos++;
	int cnt = 0;
	while (tmp != NULL) {
		cnt++;
		gotoXY(22, yPos);
		cout << cnt;
		gotoXY(24, yPos);
		cout << '|' << tmp->data.id;
		gotoXY(36, yPos);
		cout << '|' << tmp->data.firstname;
		gotoXY(48, yPos);
		cout << '|' << tmp->data.lastname;
		gotoXY(70, yPos);
		cout << '|' << tmp->data.gender;
		gotoXY(79, yPos);
		cout << '|' << tmp->data.birthday.d << '/'
			<< tmp->data.birthday.m << '/'
			<< tmp->data.birthday.y;
		gotoXY(93, yPos);
		cout << '|' << tmp->data.SocialID;
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

void LoadViewStudentCourse() {
	getListAllStudent(l_AllStudent, l_Class);
	nodeCourse* toCourse = NULL;
	while (1) {
		const int width = 50;
		const int height = 7;
		const int left = 35;
		const int top = 8;

		int yPos = 10;
		system("cls");
		drawBox(35, height, 55, 8);
		nodeCourse* tmp = l_Course.head;
		int cnt = 0;
		while (tmp != NULL) {
			gotoXY(39, yPos);
			cnt++;
			cout << cnt << ". " << tmp->data.id;
			tmp = tmp->next;
			yPos++;
		}
		drawBox(15, cnt < 4 ? height : cnt + 3, 35, 8);
		textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), 35, 50, 6);
		if (cnt == 0) {
			notifyBox("Empty!");
			return;
		}
		int key = -1;
		gotoXY(57, 11);
		cout << "Enter the course (1-" << cnt << "): ";
		cin >> key;
		if (key > 0 && key <= cnt) {
			toCourse = l_Course.head;
			for (int i = 1; i < key; i++)
				toCourse = toCourse->next;
			break;
		}
		else {
			gotoXY(57, 13);
			cout << "Error!";
			gotoXY(57, 14);
			system("pause");
		}
	}
	ViewStudentCourse(toCourse->data.List_st, toCourse->data.id);
}

void ViewStudentCourse(listStuCourse l, string st) {
	const int width = 100;
	int height = 3;
	const int left = 10;
	const int top = 9;

	int yPos = 10;
	system("cls");
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), left, width, 6);
	textAlignCenter(st, left, width, 7);
	gotoXY(12, yPos);
	cout << "No";
	gotoXY(14, yPos);
	cout << "|    ID";
	gotoXY(26, yPos);
	cout << "|First name";
	gotoXY(38, yPos);
	cout << "|      Last name";
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
	nodeStuCourse* tmp = l.head;
	yPos++;
	int cnt = 0;
	while (tmp != NULL) {
		cnt++;
		gotoXY(12, yPos);
		cout << cnt;
		gotoXY(14, yPos);
		cout << '|' << tmp->data.id;
		gotoXY(26, yPos);
		nodeStudent* k = Find(l_AllStudent, tmp->data.id);
		cout << '|' << k->data.firstname;
		gotoXY(38, yPos);
		cout << '|' << k->data.lastname;
		gotoXY(60, yPos);
		cout << '|' << tmp->data.Mark.TotalMark;
		gotoXY(72, yPos);
		cout << '|' << tmp->data.Mark.FinalMark;
		gotoXY(84, yPos);
		cout << '|' << tmp->data.Mark.MidtermMark;
		gotoXY(98, yPos);
		cout << '|' << tmp->data.Mark.OtherMark;
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

void LoadViewClassMark() {
	nodeStudent* tmpStu = l_AllStudent.head;
	while (tmpStu != NULL) {
		initList(tmpStu->data.LStu_Courses);
		tmpStu = tmpStu->next;
	}
	nodeCourse* tmp = l_Course.head;
	while (tmp !=NULL) {
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
	nodeClass* toClass = NULL;
	while (1) {
		const int width = 50;
		const int height = 7;
		const int left = 35;
		const int top = 8;
		int yPos = 10;
		system("cls");
		drawBox(45, height, 55, 8);
		nodeClass* tmp = l_Class.head;
		int cnt = 0;
		while (tmp != NULL) {
			gotoXY(39, yPos);
			cnt++;
			cout << cnt << ". " << tmp->data.ClassName;
			tmp = tmp->next;
			yPos++;
		}
		drawBox(15, cnt < 5 ? height : cnt + 3, 35, 8);
		textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), 35, 50, 6);
		if (cnt == 0) {
			notifyBox("Empty!");
			return;
		}
		int key = -1;
		gotoXY(57, 11);
		cout << "Enter the class of your choice (1-" << cnt << "): ";
		cin >> key;
		if (key > 0 && key <= cnt) {
			toClass = l_Class.head;
			for (int i = 1; i < key; i++)
				toClass = toClass->next;
			break;
		}
		else {
			gotoXY(57, 12);
			cout << "Error!";
			gotoXY(57, 13);
			system("pause");
		}
	}
	ViewClassMark(toClass->data.List_st, toClass->data.ClassName);
}

void ViewClassMark(listStudent l, string st) {
	const int width = 73;
	int height = 3;
	const int left = 20;
	const int top = 9;

	int yPos = 10;
	system("cls");
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), left, width, 6);
	textAlignCenter(st, left, width, 7);
	gotoXY(22, yPos);
	cout << "No";
	gotoXY(24, yPos);
	cout << "|ID";
	gotoXY(36, yPos);
	cout << "|First name";
	gotoXY(48, yPos);
	cout << "|      Last name";
	gotoXY(70, yPos);
	cout << "|Gender";
	gotoXY(79, yPos);
	cout << "|GPA semester";
	string t = string(73, '-');
	yPos++;
	gotoXY(21, yPos);
	cout << t;
	nodeStudent* tmp = l.head;
	yPos++;
	int cnt = 0;
	while (tmp != NULL) {
		cnt++;
		gotoXY(22, yPos);
		cout << cnt;
		gotoXY(24, yPos);
		cout << '|' << tmp->data.id;
		gotoXY(36, yPos);
		cout << '|' << tmp->data.firstname;
		gotoXY(48, yPos);
		cout << '|' << tmp->data.lastname;
		gotoXY(70, yPos);
		cout << '|' << tmp->data.gender;
		gotoXY(79, yPos);
		nodeCourse* k = tmp->data.LStu_Courses.head;
		float res = 0;
		int sum = 0;
		while (k != NULL) {
			nodeStuCourse* s = Find(k->data.List_st, tmp->data.id);
			if (s != NULL) {
				res += (float)s->data.Mark.TotalMark * (k->data.Credits);
				sum += k->data.Credits;
			}
			k = k->next;
		}
		if (sum == 0) cout << "|   " << 0;
		else cout << "|   " << (float)res / sum;
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


//Import
void LoadExportCourse() {
	getListAllStudent(l_AllStudent, l_Class);
	nodeCourse* toCourse = NULL;
	while (1) {
		const int width = 50;
		const int height = 7;
		const int left = 35;
		const int top = 8;

		int yPos = 10;
		system("cls");
		drawBox(35, height, 55, 8);
		nodeCourse* tmp = l_Course.head;
		int cnt = 0;
		while (tmp != NULL) {
			gotoXY(39, yPos);
			cnt++;
			cout << cnt << ". " << tmp->data.id;
			tmp = tmp->next;
			yPos++;
		}
		drawBox(15, cnt < 4 ? height : cnt + 3, 35, 8);
		textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), 35, 50, 6);
		if (cnt == 0) {
			notifyBox("Empty!");
			return;
		}
		int key = -1;
		gotoXY(57, 11);
		cout << "Enter the course (1-" << cnt << "): ";
		cin >> key;
		if (key > 0 && key <= cnt) {
			toCourse = l_Course.head;
			for (int i = 1; i < key; i++)
				toCourse = toCourse->next;
			break;
		}
		else {
			gotoXY(57, 13);
			cout << "Error!";
			gotoXY(57, 14);
			system("pause");
		}
	}
	ExportCourse(toCourse->data.List_st, toCourse->data.id);
}

void ExportCourse(listStuCourse l, string st) {
	const int width = 80;
	const int height = 5;
	const int left = 20;
	const int top = 8;

	system("cls");
	drawBox(width, height, left, top);
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), left, width, 5);
	textAlignCenter(st, left, width, 6);
	string PathCSV = "";
	gotoXY(22, 11);
	cout << "Destination Path -> ";
	cin.ignore();
	getline(cin, PathCSV);
	if (PathCSV.substr((int)PathCSV.length() - 4, 3) != ".csv")
		PathCSV = PathCSV + "\\" + st + ".csv";
	ofstream f;
	f.open(PathCSV, ios::out);
	if (!f.is_open()) {
		notifyBox("FILE NOT EXISTS");
		return;
	}

	f << "No,ID,First name,Last name,Total Mark,Final Mark,Midterm Mark,Other Mark" << '\n';
	nodeStuCourse* tmp = l.head;
	int cnt = 0;
	while (tmp != NULL) {
		cnt++;
		nodeStudent* k = Find(l_AllStudent, tmp->data.id);
		f << cnt << ','
			<< tmp->data.id << ','
			<< k->data.firstname << ','
			<< k->data.lastname << ','
			<< tmp->data.Mark.TotalMark << ','
			<< tmp->data.Mark.FinalMark << ','
			<< tmp->data.Mark.MidtermMark << ','
			<< tmp->data.Mark.OtherMark;
		tmp = tmp->next;
		if (tmp != NULL) f << '\n';
	}
	f.close();
	notifyBox("Successful");
}

void LoadImportCourse() {
	getListAllStudent(l_AllStudent, l_Class);
	nodeCourse* toCourse = NULL;
	while (1) {
		const int width = 50;
		const int height = 7;
		const int left = 35;
		const int top = 8;

		int yPos = 10;
		system("cls");
		drawBox(35, height, 55, 8);
		nodeCourse* tmp = l_Course.head;
		int cnt = 0;
		while (tmp != NULL) {
			gotoXY(39, yPos);
			cnt++;
			cout << cnt << ". " << tmp->data.id;
			tmp = tmp->next;
			yPos++;
		}
		drawBox(15, cnt < 4 ? height : cnt + 3, 35, 8);
		textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), 35, 50, 6);
		if (cnt == 0) {
			notifyBox("Empty!");
			return;
		}
		int key = -1;
		gotoXY(57, 11);
		cout << "Enter the course (1-" << cnt << "): ";
		cin >> key;
		if (key > 0 && key <= cnt) {
			toCourse = l_Course.head;
			for (int i = 1; i < key; i++)
				toCourse = toCourse->next;
			break;
		}
		else {
			gotoXY(57, 13);
			cout << "Error!";
			gotoXY(57, 14);
			system("pause");
		}
	}
	ImportCourse(toCourse->data.List_st, toCourse->data.id);
}

void ImportCourse(listStuCourse& l, string st) {
	const int width = 80;
	const int height = 5;
	const int left = 20;
	const int top = 8;

	system("cls");
	drawBox(width, height, left, top);
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), left, width, 5);
	textAlignCenter(st, left, width, 6);
	string PathCSV = "";
	gotoXY(22, 11);
	cout << "Source Path -> ";
	cin.ignore();
	getline(cin, PathCSV);
	fstream f;
	f.open(PathCSV, ios::in);
	if (!f.is_open()) {
		notifyBox("FILE NOT EXISTS");
		return;
	}
	string s = "";
	getline(f, s);
	initList(l);
	while (!f.eof()) {
		StuCourse val;
		string tmp;
		getline(f, tmp, ',');
		if (tmp == "") continue;
		getline(f, val.id, ',');
		getline(f, tmp, ',');
		getline(f, tmp, ',');
		getline(f, tmp, ',');
		if (tmp == "") tmp = '0';
		val.Mark.TotalMark = stof(tmp);
		getline(f, tmp, ',');
		if (tmp == "") tmp = '0';
		val.Mark.FinalMark = stof(tmp);
		getline(f, tmp, ',');
		if (tmp == "") tmp = '0';
		val.Mark.MidtermMark = stof(tmp);
		getline(f, tmp, '\n');
		if (tmp == "") tmp = '0';
		val.Mark.OtherMark = stof(tmp);
		addStuCourse(l, createNodeStuCourse(val));
	}
	f.close();
	notifyBox("Successful");
}

//UpdateMark
void UpdateMarkMenu(CourseMark& val) {
	/*
	1. Total Mark
	2. Final Mark
	3. Midterm Mark
	4. OtherMark
	0. Save
	*/
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int yPos = 10;
	system("cls");
	drawBox(width, height, left, top);
	gotoXY(45, yPos);
	cout << "1. Total Mark " << val.TotalMark;
	yPos++;
	gotoXY(45, yPos);
	cout << "2. Final Mark " << val.FinalMark;
	yPos++;
	gotoXY(45, yPos);
	cout << "3. Midterm Mark " << val.MidtermMark;
	yPos++;
	gotoXY(45, yPos);
	cout << "4. Other Mark " << val.OtherMark;
	yPos += 2;
	gotoXY(45, 16);
	cout << "0. Save\n";
}

void LoadUpdateMark_1() {
	nodeCourse* toCourse = NULL;
	while (1) {
		const int width = 50;
		const int height = 7;
		const int left = 35;
		const int top = 8;

		int yPos = 10;
		system("cls");
		drawBox(35, height, 55, 8);
		nodeCourse* tmp = l_Course.head;
		int cnt = 0;
		while (tmp != NULL) {
			gotoXY(39, yPos);
			cnt++;
			cout << cnt << ". " << tmp->data.id;
			tmp = tmp->next;
			yPos++;
		}
		drawBox(15, cnt < 4 ? height : cnt + 3, 35, 8);
		textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), 35, 50, 6);
		if (cnt == 0) {
			notifyBox("Empty!");
			return;
		}
		int key = -1;
		gotoXY(57, 12);
		cout << "Enter the course (1-" << cnt << "): ";
		cin >> key;
		if (key > 0 && key <= cnt) {
			toCourse = l_Course.head;
			for (int i = 1; i < key; i++)
				toCourse = toCourse->next;
			break;
		}
		else {
			gotoXY(57, 13);
			cout << "Error!";
			gotoXY(57, 14);
			system("pause");
		}
	}
	LoadUpdateMark_2(toCourse);
}

void LoadUpdateMark_2(nodeCourse*& toCourse) {
	nodeStuCourse* toStuCourse = NULL;
	const int width = 50;
	const int height = 4;		
	const int left = 35;
	const int top = 8;
	int yPos = 10;
	system("cls");
	drawBox(width, height, left, top);
	textAlignCenter(to_string(CurSchoolyear.Sta_year) + '-' + to_string(CurSchoolyear.End_year), left, width, 5);
	textAlignCenter(toCourse->data.id, left, width, 6);
	string IDStudent;
	cin.ignore();
	gotoXY(40, yPos);
	cout << "Student ID: ";
	getline(cin, IDStudent);
	toStuCourse = Find(toCourse->data.List_st, IDStudent);
	if (toStuCourse == NULL) {
		notifyBox("Fail!");
		return;
	}
	do {
		UpdateMarkMenu(toStuCourse->data.Mark);
		gotoXY(45, 19);
		int cur = -1;
		cout << "Enter your choice (0-4): ";
		cin >> cur;
		switch (cur) {
		case 1:
		{
			toStuCourse->data.Mark.TotalMark = UpdateMark("Total Mark");
			break;
		}
		case 2:
		{
			toStuCourse->data.Mark.FinalMark = UpdateMark("Final Mark");
			break;
		}
		case 3:
		{
			toStuCourse->data.Mark.MidtermMark = UpdateMark("Midterm Mark");
			break;
		}
		case 4:
		{
			toStuCourse->data.Mark.OtherMark = UpdateMark("Other Mark");
			break;
		}
		case 0: //Save
		{
			return;
			break;
		}
		default: {
			gotoXY(45, 20);
			cout << "Error!";
			gotoXY(45, 21);
			system("pause");
			break;
		}
		}
	} while (1);
}

float UpdateMark(string st) {
	/*
	1. Total Mark
	2. Final Mark
	3. Midterm Mark
	4. OtherMark
	0. Save
	*/
	
	const int width = 50;
	const int height = 4;
	const int left = 35;
	const int top = 8;

	int yPos = 10;
	system("cls");
	drawBox(width, height, left, top);
	float ans;
	cin.ignore();
	gotoXY(40, yPos);
	cout << st << ": ";
	cin >> ans;
	notifyBox("Successful");
	return ans;
}
