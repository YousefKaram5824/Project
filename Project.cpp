#include <iostream>
#include <fstream>
#include <string>

using namespace std;
\\help!

struct DATE
{
	int day, month, year;
};
struct SUBSCRIBTION
{
	string type;
	DATE START_date, END_date;
	int rides;
};


struct USER
{
	string type, name, password;
	int id;
	float balance;
	SUBSCRIBTION SUB;
}users[10];



void login();
void not_login();
void registration();
void forgot();

int main()
{
	int choice;

	cout << "\t\t\t\tWelcome to Metro Mate Project\n";
	cout << "\t\t\t\t*****************************\n";
	cout << "Press [1] to LOGIN\n";
	cout << "Press [2] to REGISTER\n";
	cout << "Press [3] to EXIT\n\n\n";
	cout << "Please enter your choice : ";
	cin >> choice;

	switch (choice) 
	{
		case 1 :
			login();
			break;
		case 2 :
			registration();
			break;
		case 3 :
			cout << "Thank you!\n";
			break;
		default :
			system("cls");
			cout << "Please select from the options given above\n";
			main();
	}

	return 0;
}

void login() {
	int count = 0;
	string username, password, user, pass;
	system("cls");
	cout << "Please enter the username and password\n";
	cout << "USERNAME : ";
	getline(cin, username);
	cout << "PASSWORD : ";
	cin >> password;

	ifstream input("records.txt");

	while (input >> user >> pass) 
	{
		if (user == username && pass == password) 
		{
			count = 1;
			system("cls");
		}
	}

	input.close();

	if (count == 1) 
	{
		cout << "\n Your LOGIN is successfull !\n\n";
		main();
	}
	else 
	{
		not_login();
	}
}

void not_login() {
	int choice;
	system("cls");
	cout << "LOGIN ERROR!\n\n";
	cout << "Press [1] to login again\n";
	cout << "Press [2] to if you forgot your PASSWORD\n";
	cout << "Press [3] to get the main menu\n\n\n";
	cout << "Please enter your choice : ";
	cin >> choice;
	switch (choice) {
	case 1:
		login();
		break;
	case 2:
		forgot();
		break;
	case 3:
		system("cls");
		main();
		break;
	default:
		system("cls");
		cout << "Please select from the options given above\n";
		not_login();
	}
}

void registration() {
	string new_username;
	int new_password;
	system("cls");
	cout << "Enter the username : ";
	getline(cin, new_username);
	cout << "Enter the password : ";
	cin >> new_password;
	ofstream f1("records.txt", ios::app);
	f1 << new_username << ' ' << new_password << endl;
	system("cls");
	cout << "Registration is successfull!\n";
	main();
}

void forgot() {
	int option;
	system("cls");
	cout << "You forgot the password? Don't worry\n";
	cout << "Press [1] to search your id by username\n";
	cout << "Press [2] to go back to the main menu\n";
	cout << "Enter your choice : \n";
	cin >> option;
	switch (option)
	{
		case 1 :
		{
			int count = 0;
			string suserid, sid, spass;
			cout << "Enter your username : ";
			getline(cin, suserid);
			ifstream f2("records.txt");
			while (f2 >> sid >> spass) 
			{
				if (sid == suserid) {
					count = 1;
				}
			}
			f2.close();
			if (count == 1) 
			{
			cout << "Your count is found!\n";
			cout << "Your password is : " << spass;
			main();
			}
			else {
				cout << "Sorry! Your account is not found.\n";
				main();
			}
			break;
		}

		case 2 :
		{
			main();
		}
		default :
			cout << "Wrong choice! Please try again\n";
			forgot();
	}
}
