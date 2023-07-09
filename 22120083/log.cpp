#include "header.h"

nodeUser* userLogin = NULL;
listUser l_User;

nodeUser* findUser(string id, string pass) {
	nodeUser* tmp = l_User.head;
	while (tmp != NULL) {
		if (id == tmp->data.id) {
			if (pass == tmp->data.pass) return tmp;
			else return NULL;
		}
		tmp = tmp->next;
	}
	return NULL;
}

void loginUI(string& id, string& pass) {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 10;
	int yPos = 13;

	drawBox(width, height, left, top);
	textAlignCenter("HCMUS", left, width, 6);
	textAlignCenter("LOGIN", left, width, 7);
	gotoXY(48, yPos);
	cout << "ID:";
	gotoXY(48, yPos + 2);
	cout << "PASSWORD:";
	gotoXY(58, yPos);
	cin >> id;
	gotoXY(58, yPos + 2);
	cin >> pass;
}

void solveLogin() {
	system("cls");
	getListUsers(l_User);
	while (1) {
		string UserID, UserPass;
		loginUI(UserID, UserPass);
		userLogin = findUser(UserID, UserPass);
		if (userLogin == NULL) {
			notifyBox("Login Fail");
		}
		else {
			notifyBox("Login Succesful");
			break;
		}
	}
	cout << userLogin->data.isStaff;
	if (userLogin->data.isStaff) {
		//Staff 
		LoadStaffMenu();
	}
	else {
		//Student
		LoadStudentMenu();
	}
	system("cls");
}