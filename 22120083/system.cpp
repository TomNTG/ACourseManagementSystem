#include "header.h"

date SttoDate(string st) {
	date val;
	val.d = stoi(st.substr(0, st.find('/')));
	st.erase(0, st.find('/') + 1);
	val.m = stoi(st.substr(0, st.find('/')));
	st.erase(0, st.find('/') + 1);
	val.y = stoi(st.substr(0, st.find('/')));
	st.erase(0, st.find('/') + 1);
	return val;
}
string DatetoSt(date dt) {
	string st = "";
	if (dt.d < 10) st += "0";
	st += to_string(dt.d) + "/";
	if (dt.m < 10) st += "0";
	st += to_string(dt.m) + "/";
	st += to_string(dt.y);
	return st;
}

void initList(listUser& l) {
	l.head = l.tail = NULL;
}

void initList(listStudent& l) {
	l.head = l.tail = NULL;
}

void initList(listClass& l) {
	l.head = l.tail = NULL;
}

void initList(listCourse& l) {
	l.head = l.tail = NULL;
}

void initList(listStuCourse& l) {
	l.head = l.tail = NULL;
}

nodeUser* createNodeUser(User val) {
	nodeUser* tmp = new nodeUser;
	tmp->data = val;
	tmp->next = tmp->prev = NULL;
	return tmp;
}

nodeStudent* createNodeStudent(Student val) {
	nodeStudent* tmp = new nodeStudent;
	tmp->data = val;
	tmp->next = tmp->prev = NULL;
	return tmp;
}

nodeClass* createNodeClass(Class val) {
	nodeClass* tmp = new nodeClass;
	tmp->data = val;
	tmp->next = tmp->prev = NULL;
	return tmp;
}

nodeCourse* createNodeCourse(Course val) {
	nodeCourse* tmp = new nodeCourse;
	tmp->data = val;
	tmp->next = tmp->prev = NULL;
	return tmp;
}

nodeStuCourse* createNodeStuCourse(StuCourse val) {
	nodeStuCourse* tmp = new nodeStuCourse;
	tmp->data = val;
	tmp->next = tmp->prev = NULL;
	return tmp;
}

void addUser(listUser& l, nodeUser* user) {
	if (user == NULL) return;
	if (l.head == NULL) {
		l.head = l.tail = user;
	}
	else {
		l.tail->next = user;
		user->prev = l.tail;
		l.tail = user;
	}
}

void addStudent(listStudent& l, nodeStudent* Stu) {
	if (Stu == NULL) return;
	if (l.head == NULL) {
		l.head = l.tail = Stu;
	}
	else {
		l.tail->next = Stu;
		Stu->prev = l.tail;
		l.tail = Stu;
	}
}

void addClass(listClass& l, nodeClass* cla) {
	if (cla == NULL) return;
	if (l.head == NULL) {
		l.head = l.tail = cla;
	}
	else {
		l.tail->next = cla;
		cla->prev = l.tail;
		l.tail = cla;
	}
}

void addCourse(listCourse& l, nodeCourse* Cour) {
	if (Cour == NULL) return;
	if (l.head == NULL) {
		l.head = l.tail = Cour;
	}
	else {
		l.tail->next = Cour;
		Cour->prev = l.tail;
		l.tail = Cour;
	}
}

void addStuCourse(listStuCourse& l, nodeStuCourse* val) {
	if (val == NULL) return;
	if (l.head == NULL) {
		l.head = l.tail = val;
	}
	else {
		l.tail->next = val;
		val->prev = l.tail;
		l.tail = val;
	}
}

void removeStuCourse(listStuCourse& l, nodeStuCourse* key) {
	if (key == NULL) return;
	if (l.head == NULL) return;
	if (key->prev == NULL) {
		l.head = l.head->next;
		if (l.head == NULL)	l.tail = NULL;
		else l.head->prev = NULL;
		key->next = NULL;
		delete key;
		return;
	}
	if (key->next == NULL) {
		l.tail = l.tail->prev;
		if (l.tail == NULL) l.head = NULL;
		else l.tail->next = NULL;
		key->prev = NULL;
		delete key;
		return;
	}
	key->prev->next = key->next;
	key->next->prev = key->prev;
	key->next = key->prev = NULL;
	delete key;
}

void removeCourse(listCourse& l, nodeCourse* key) {
	if (key == NULL) return;
	if (key->prev == NULL) {
		l.head = l.head->next;
		if (l.head == NULL) l.tail = NULL;
		else l.head->prev = NULL;
		key->next = NULL;
		delete key;
		return;
	}
	if (key->next == NULL) {
		l.tail = l.tail->prev;
		if (l.tail == NULL) l.head = NULL;
		else l.tail->next = NULL;
		key->prev = NULL;
		delete key;
		return;
	}
	key->prev->next = key->next;
	key->next->prev = key->prev;
	key->next = key->prev = NULL;
	delete key;
}

nodeStuCourse* Find(listStuCourse& l, string key) {
	nodeStuCourse* tmp = l.head;
	while (tmp != NULL) {
		if (tmp->data.id == key) return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

nodeStudent* Find(listStudent& l, string key) {
	nodeStudent* tmp = l.head;
	while (tmp != NULL) {
		if (tmp->data.id == key) return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

nodeUser* inputUser(fstream& f) {
	User val;
	getline(f, val.id, ',');
	if (val.id == "") return NULL;
	getline(f, val.pass, ',');
	getline(f, val.firstname, ',');
	getline(f, val.lastname, ',');
	getline(f, val.gender, ',');
	string tmp;
	getline(f, tmp, ',');
	val.birthday = SttoDate(tmp);
	getline(f, val.SocialID, ',');
	getline(f, tmp, ',');
	val.academic = stoi(tmp);
	getline(f, val.className, ',');
	getline(f, tmp, '\n');
	if (tmp == "TRUE") val.isStaff = true;
	else val.isStaff = false;
	return createNodeUser(val);
}

nodeStudent* inputStudent(fstream& f, int aca, string cla_name) {
	Student val;
	string tmp;
	getline(f, tmp, ',');
	if (tmp == "") return NULL;
	getline(f, val.id, ',');
	getline(f, val.firstname, ',');
	getline(f, val.lastname, ',');
	getline(f, val.gender, ',');
	getline(f, tmp, ',');
	val.birthday = SttoDate(tmp);
	getline(f, val.SocialID, '\n');
	val.academic = aca;
	val.className = cla_name;
	return createNodeStudent(val);
}

nodeClass* inputClass(fstream& f) {
	Class val;
	getline(f, val.ClassName, ',');
	if (val.ClassName == "") return NULL;
	getline(f, val.ClassPath, ',');
	string tmp;
	getline(f, tmp, '\n');
	val.academic = stoi(tmp);
	if (val.academic < CurSchoolyear.Sta_year - 3) return NULL;
	getListStudent(val.List_st, val.ClassPath, val.academic, val.ClassName);
	return createNodeClass(val);
}

nodeStuCourse* inputStuCourse(fstream& f) {
	StuCourse val;
	string tmp;
	getline(f, tmp, ',');
	if (tmp == "") return NULL;
	getline(f, val.id, ',');
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
	return createNodeStuCourse(val);
}

nodeCourse* inputCourse(fstream& f, string Path) {
	Course val;
	getline(f, val.id, ',');
	if (val.id == "") return NULL;
	getline(f, val.CourseName, ',');
	getline(f, val.ClassName, ',');
	getline(f, val.TeacherName, ',');
	string tmp;
	getline(f, tmp, ',');
	val.Credits = stoi(tmp);
	getline(f, tmp, ',');
	val.maxStudents = stoi(tmp);
	getline(f, val.wDay, ',');
	getline(f, val.Session, '\n');
	getListStuCourse(val.List_st, Path + "\\" + val.id + ".csv");
	return createNodeCourse(val);
}

void getListUsers(listUser& l) {
	fstream f;
	f.open("DATA/users.csv", ios::in);
	initList(l);
	if (!f.is_open()) return;
	string s = "";
	getline(f, s);
	while (!f.eof())
		addUser(l, inputUser(f));
	f.close();
}

void getListStudent(listStudent& l, string Path, int aca, string cla_name) {
	fstream f;
	f.open(Path, ios::in);
	initList(l);
	if (!f.is_open()) return;
	string s = "";
	getline(f, s);
	while (!f.eof())
		addStudent(l, inputStudent(f, aca, cla_name));
	f.close();
}

void getListClass(listClass& l, string PathSchoolyear) {
	fstream f;
	f.open(PathSchoolyear + "/INFOR.txt", ios::in);
	initList(l);
	if (!f.is_open()) return;
	while (!f.eof())
		addClass(l, inputClass(f));
	f.close();
}

void getListStuCourse(listStuCourse& l, string Path) {
	fstream f;
	f.open(Path, ios::in);
	initList(l);
	if (!f.is_open()) return;
	string s = "";
	getline(f, s);
	while (!f.eof())
		addStuCourse(l, inputStuCourse(f));
	f.close();
}

void getListCourse(listCourse& l, string Path) {
	fstream f;
	f.open(Path + "\\Course.csv", ios::in);
	initList(l);
	if (!f.is_open()) return;
	string s = "";
	getline(f, s);
	while (!f.eof())
		addCourse(l, inputCourse(f, Path));
	f.close();
}

void getListAllStudent(listStudent& l, listClass& lClass) {
	initList(l);
	nodeClass* tmp = lClass.head;
	while (tmp != NULL) {
		MergeList(l, tmp->data.List_st);
		tmp = tmp->next;
	}
}

void AddListUsers(listUser& l_Us, listStudent l_St) {
	nodeStudent* t_st = l_St.head;
	while (t_st != NULL) {
		User t_us;
		t_us.id = t_st->data.id;
		t_us.pass = "123456";
		t_us.firstname = t_st->data.firstname;
		t_us.lastname = t_st->data.lastname;
		t_us.gender = t_st->data.gender;
		t_us.SocialID = t_st->data.SocialID;
		t_us.className = t_st->data.className;
		t_us.birthday = t_st->data.birthday;
		t_us.academic = t_st->data.academic;
		t_us.isStaff = false;
		addUser(l_Us, createNodeUser(t_us));
		t_st = t_st->next;
	}
}

void UpdateListUsers(listUser l) {
	fstream f;
	f.open("DATA/users.csv", ios::out);
	f << "ID,Password,First name,Last name,Gender,Date of Birth,Social ID,Academic,Class,Staff" << '\n';
	nodeUser* t = l.head;
	while (t != NULL) {
		f << t->data.id << ','
			<< t->data.pass << ','
			<< t->data.firstname << ','
			<< t->data.lastname << ','
			<< t->data.gender << ','
			<< t->data.birthday.d << '/' << t->data.birthday.m << '/' << t->data.birthday.y << ','
			<< t->data.SocialID << ','
			<< t->data.academic << ','
			<< t->data.className << ',';
		if (t->data.isStaff) f << "TRUE";
		else f << "FALSE";
		t = t->next;
		if (t != NULL) f << '\n';
	}
	f.close();
}

void UpdateListStudent(string PathClass, listStudent l) {
	fstream f;
	f.open(PathClass, ios::out);
	f << "No,ID,First name,Last name,Gender,Date of Birth,Social ID" << '\n';
	nodeStudent* t = l.head;
	int i = 0;
	while (t != NULL) {
		i++;
		f << i << ','
			<< t->data.id << ','
			<< t->data.firstname << ','
			<< t->data.lastname << ','
			<< t->data.gender << ','
			<< t->data.birthday.d << '/' << t->data.birthday.m << '/' << t->data.birthday.y << ','
			<< t->data.SocialID << ',';
		t = t->next;
		if (t != NULL) f << '\n';
	}
	f.close();
}

void UpdateListClass(string PathSchoolyear, listClass l) {
	fstream f;
	f.open(PathSchoolyear + "\\INFOR.txt", ios::out);
	nodeClass* t = l.head;
	while (t != NULL) {
		t->data.ClassPath = PathSchoolyear + '\\' + t->data.ClassName + ".csv";
		f << t->data.ClassName << ','
			<< t->data.ClassPath << ','
			<< t->data.academic;
		UpdateListStudent(t->data.ClassPath, t->data.List_st);
		t = t->next;
		if (t != NULL) f << '\n';
	}
	f.close();
}

void UpdateListStuCourse(string PathCourse, listStuCourse l) {
	fstream f;
	f.open(PathCourse, ios::out);
	f<< "No,ID,Total Mark,Final Mark,Midterm Mark,Other Mark" << '\n';
	nodeStuCourse* t = l.head;
	int i = 0;
	while (t != NULL) {
		i++;
		f << i << ','
			<< t->data.id << ','
			<< t->data.Mark.TotalMark << ','
			<< t->data.Mark.FinalMark << ','
			<< t->data.Mark.MidtermMark << ','
			<< t->data.Mark.OtherMark;
		t = t->next;
		if (t != NULL) f << '\n';
	}
	f.close();
}

void UpdateListCourse(string PathSemester, listCourse l) {
	fstream f;
	f.open(PathSemester+"\\Course.csv", ios::out);
	f << "ID,Course name,Class name,Teacher name,Credits,Max students,Day of the week,Session" << '\n';
	nodeCourse* t = l.head;
	while (t != NULL) {
		f << t->data.id << ','
			<< t->data.CourseName << ','
			<< t->data.ClassName << ','
			<< t->data.TeacherName << ','
			<< t->data.Credits << ','
			<< t->data.maxStudents << ','
			<< t->data.wDay << ','
			<< t->data.Session;
		UpdateListStuCourse(PathSemester + "\\" + t->data.id + ".csv", t->data.List_st);
		t = t->next;
		if (t != NULL) f << '\n';
	}
	f.close();
}

void MergeList(listStudent& x, listStudent& y) {
	if (x.head == NULL) {
		x = y;
		return;
	}
	if (y.head == NULL) return;
	x.tail->next = y.head;
	y.head->prev = x.tail;
	x.tail = y.tail;
}

void MergeList(listClass& x, listClass& y) {
	if (x.head == NULL) {
		x = y;
		return;
	}
	if (y.head == NULL) return;
	x.tail->next = y.head;
	y.head->prev = x.tail;
	x.tail = y.tail;
}
