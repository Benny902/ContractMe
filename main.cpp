#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h> 
#include <conio.h>
#include <dos.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>

using namespace std;

const int HR_TYPE = 1;
const int EMPLOYEER_TYPE = 2;
const int CONTRACTOR_TYPE = 3;

int ContractorCount = 0; // Contractor user count.
int ContractorHired = 0;
int EmployerCount = 0;  // Employer user count.


typedef struct User {
	string fullName;
	string username;
	string password;
	int UserType = 0;  //  1 = HR  ,  2 = Employeer  ,  3 = Contractor
} User;

typedef struct WorkDay {
	int day;
	int month;
	int year;
	int startTime;
	int endTime;
}WorkDay;

typedef struct Contractor {
	User details;
	int salary;
	string place;
	int numskills;
	string* skill = NULL;
	int numOfWorkDays = 0;
	WorkDay* workDay = NULL;
}Contractor;


void textColor(int textcolor);
void ourLogo();
void printBye();
void mainmenu();
WorkDay calendar(string);
void writeHRtoFile();
void login();
void signUp();
void writeUserToFile(User);
void tech();
bool checkUserExists(ifstream&, string);
void ChooseMenu(int , string );
void lowercase(string&);
int calculateHours(int , int );

void hrMenu(string );
void statisticAnalysis();
void addNewWorker();
void monitorHiring();
void workersFeed();

void employeerMenu(string );
void hiringHistory(string);
void searchContractor(string);
bool checkSkills(string* , int , string );
void bookContractor(string , string , WorkDay );
bool checkDate(WorkDay , string );

void contractorMenu(string );
void editprofile(string);
void addworkday(Contractor&);
void updateWorkHistory(Contractor&);
void addvacation(Contractor&);
void buildContractor(Contractor&, string);


int main()
{
	ourLogo(); // function to print our logo

	textColor(15);
	cout << endl << endl
		<< "+++++++++++++++++++++++++++++++++++++++++++" << endl
		<< "+++  HELLO! :), welcome to ContractMe!  +++  (for technical support press '0' at anytime)" << endl
		<< "+++++++++++++++++++++++++++++++++++++++++++" << endl;

	textColor(15); // changing back to white text
	mainmenu();

	printBye();
	getchar();
	getchar();
	return 0;
}

void textColor(int textcolor)  // function to switch text colors
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, textcolor);
}

void ourLogo() // func to print our logo
{
	system("CLS");
	textColor(48);
	cout << "                                                                                  " << endl;
	textColor(48); cout << "  "; textColor(1); cout << " CCCCCCC                                                   M     M            "; textColor(48); cout << "  " << endl;
	textColor(48); cout << "  "; textColor(1); cout << " CCC           n      t                         t         MMM   MMM     eeeee "; textColor(48); cout << "  " << endl;
	textColor(48); cout << "  "; textColor(1); cout << " CC       ooo  nnnn  ttt   r rrrr aaaaa  ccccc ttt       M   M M   M    e     "; textColor(48); cout << "  " << endl;
	textColor(48); cout << "  "; textColor(1); cout << " CC      o   o n   n  t     r     a   a  c      t       M     M     M   eeee  "; textColor(48); cout << "  " << endl;
	textColor(48); cout << "  "; textColor(1); cout << " CCC     o   o n   n  t     r     a   a  c      t      M             M  e     "; textColor(48); cout << "  " << endl;
	textColor(48); cout << "  "; textColor(1); cout << " CCCCCCC  ooo  n   n  tttt  r     aaaaaa ccccc  tttt  M               M eeeee "; textColor(48); cout << "  " << endl;
	textColor(48);
	cout << "                                                                                  " << endl;
	textColor(15); // returning to white text
}

void printBye()
{
	system("CLS");
	cout << " " << endl
		<< "                        .-''''-.     " << endl
		<< "                       / .===. \\  " << endl
		<< "                       \\/ 6 6 \\/  " << endl
		<< "                       ( \\___/ )  " << endl
		<< "  _________________ooo__\\_____/_____________________ " << endl
		<< " /                                                  \\ " << endl
		<< " |  Good bye & and thank you for using ContractMe!   | " << endl
		<< " \\______________________________ooo_________________/ " << endl
		<< "                        |  |  | " << endl
		<< "                        |_ | _| " << endl
		<< "                        |  |  | " << endl
		<< "                        |__|__| " << endl
		<< "                        /-'Y'-\\ " << endl
		<< "                       (__/ \\__)  " << endl;
}

void mainmenu()
{
	int choice;
	do {
		cout << "\n\tLOGIN & Sign up page\n\tEnter your choice:\n\n1. Login \n2. Sign up \n3. Exit\n" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0: // technical support
			tech();
			break;
		case 1: // login
			login();
			break;
		case 2: // sign up
			signUp();
			break;
		case 3: // exit
			break;
		default:
			cout << "\nError, please try again:\n" << endl;
		}
	} while (choice != 3);
}

void login()
{
	ourLogo();
	string userInput;
	string pass;
	cout << endl << endl;
	cout << "Username: ";
	cin >> userInput;
	cout << "Password: ";
	cin >> pass;

	lowercase(userInput); //Change to lowercase before checking if exists.

	ifstream inFile;
	inFile.open("database.txt");
	if (inFile.fail()) {
		cerr << "error opening file" << endl;
		exit(1);
	}
	string checkpass;
	int checktype;
	string temp;
	if (checkUserExists(inFile, userInput)) {
		inFile >> checkpass;
		if (checkpass == pass)
		{
			inFile >> temp; // skipping the name 
			inFile >> checktype;
			inFile.close();
			ChooseMenu(checktype, userInput);
			return;
		}
		else cout << "Wrong pass.\n";
		return;
	}
	cout << "User does not exsist in the database, try again";
	inFile.close();
	return;
}

void signUp() // only Employer can signup
{
	ourLogo();
	User u1;
	string name, username, password;

	cout << ("\nHello, enter your name, username and password:\n");
	cout << "name: " << endl;
	cin >> name;
	cout << "username: " << endl;
	cin >> username;
	cout << "password: " << endl;
	cin >> password;

	lowercase(username); //Account usernames will be stored in lowercase on the DataBase.

	// Username in database must be unique.
	ifstream inFile;
	inFile.open("database.txt", ios::app);
	if (inFile.fail()) {
		cerr << "error opening file" << endl;
		exit(1);
	}
	while (checkUserExists(inFile, username)) {
		cout << "Username taken." << endl << "Enter another username: ";
		cin >> username;
	}
	u1.fullName = name;
	u1.username = username;
	u1.password = password;
	u1.UserType = EMPLOYEER_TYPE;  // employer 
	writeUserToFile(u1);

	EmployerCount++; // Counting the number of employers in the system - for "Statistic Analysis"
	employeerMenu(username);
}

void writeUserToFile(User newUser)
{
	ofstream inFile;
	inFile.open("database.txt", ios::app);
	if (inFile.fail()) {
		cout << "error opening file" << endl;
		exit(1);
	}
	inFile << newUser.username << " ";
	inFile << newUser.password << " ";
	inFile << newUser.fullName << " ";
	inFile << newUser.UserType << endl;
	inFile.close();
	inFile.open("HiringHistory.txt", ios::app);
	if (inFile.fail()) {
		cout << "error opening file" << endl;
		exit(1);
	}
	inFile << "UserName:" << endl << newUser.username << endl;
	inFile << "HiringHistory:" << endl;
	inFile.close();
}

void ChooseMenu(int type, string userInput)
{
	if (type == 1)
		hrMenu(userInput);
	else if (type == 2)
		employeerMenu(userInput);
	else // type 3
		contractorMenu(userInput);
}

void tech()
{
	ourLogo();
	string problem;
	cout << "\nHello, welcome to tech support.\n please describe your problem: " << endl;
	cin >> problem;
	cout << "\nThank you for your message, we will return to you with a solution asap " << endl;

}


void buildContractor(Contractor& worker, string userInput)
{
	fstream inFile; //getting workHours and payPerHour from the database
	inFile.open("database.txt");
	if (inFile.fail()) {
		cout << "error opening file" << endl;
		exit(1);
	}
	string temp;
	string checkInput;
	while (!inFile.eof())
	{
		inFile >> checkInput; // Getting the UserName field from the file.
		if (checkInput == userInput) // we are now in the correct user
		{
			worker.details.username = checkInput;
			inFile >> worker.details.password; //pass
			inFile >> worker.details.fullName;//name
			inFile >> worker.details.UserType; //type
			inFile >> worker.salary; //salary
			inFile >> worker.numskills;
			worker.skill = new string[worker.numskills];
			for (int i = 0; i < worker.numskills; ++i)
			{
				inFile >> worker.skill[i];
			}
			getline(inFile, worker.place);
			break;
		}
		getline(inFile, temp);
	}
	inFile.close();
	//cout << "Hello '" << name << "', " << endl;
	//int totalHours = 0;
	inFile.open("workHistory.txt");
	while (!inFile.eof())
	{
		inFile >> checkInput; // Getting the UserName field from the file.
		if (checkInput == userInput) // we are now in the correct user
		{
			inFile >> worker.numOfWorkDays;
			worker.workDay = new WorkDay[worker.numOfWorkDays];
			for (int i = 0; i < worker.numOfWorkDays; i++)
			{
				inFile >> worker.workDay[i].day; // ignoring day date
				inFile >> worker.workDay[i].month; // ignoring mpnth date
				inFile >> worker.workDay[i].year; // ignoring year date
				inFile >> worker.workDay[i].startTime; // getting start Time
				inFile >> worker.workDay[i].endTime; // getting End time
			}
			break;
		}
	}
	inFile.close();
}

void contractorMenu(string userInput)
{
	//// name username password type workHours payPerHour NotAvailable(DayOfMonth)
		// welcome to the contractor menu, and print his work hours and salary
	Contractor worker;
	buildContractor(worker, userInput);
	int totalHours = 0;
	// entering to the contractor menu options
	int choice = 0;
	while (choice != 4)
	{
		ourLogo();
		cout << "Hello " << worker.details.fullName << endl;
		for (int i = 0; i < worker.numOfWorkDays; i++)
		{
			if ((worker.workDay[i].startTime != 0 && worker.workDay[i].endTime != 0) && (worker.workDay[i].startTime != -1 && worker.workDay[i].endTime != -1))
			{
				cout << worker.workDay[i].day << "/" << worker.workDay[i].month << "/" << worker.workDay[i].year << "\t" << worker.workDay[i].startTime << ":00 - " << worker.workDay[i].endTime << ":00" << endl;
				totalHours += calculateHours(worker.workDay[i].startTime, worker.workDay[i].endTime);
			}
		}
		cout << "And your total salary is:" << totalHours * worker.salary << endl;
		cout << "Welcome to the Contractor Menu" << endl;
		cout << "\nWhat do you want to do next? " << endl
			<< "1.Report work hours" << endl
			<< "2.Report vacation" << endl
			<< "3.Edit profile" << endl
			<< "4.Sign out" << endl;
		cin >> choice;
		switch (choice) {
		case 0: // technical support
			tech();
			break;
		case 1: //report work hours
			addworkday(worker);
			updateWorkHistory(worker);
			break;
		case 2: //Report vacation
			addvacation(worker);
			updateWorkHistory(worker);
			break;
		case 3:
			// edit
			editprofile(userInput);
			break;
		case 4:
			delete[] worker.skill;
			delete[]worker.workDay;
			cout << "Signed out of the system." << endl;
			break;
		default:
			cout << "Please enter choice between 1-4 only, 4 to sign out." << endl;
		}
	}
}

void editprofile(string username)
{
	ourLogo();
	ifstream original("database.txt");
	ofstream replica("database1.txt");
	string tmp, checkUser, salary, location, pass, fullname;
	string* skills = NULL;
	int numofskills=0;
	do
	{
		original >> tmp; //get username
		if (tmp == username)
		{
			original >> pass; 
			original >> fullname;
			original >> tmp; //skip type
			original >> salary;
			original >> numofskills;
			skills = new string[numofskills];
			for (int i = 0; i < numofskills; ++i)
				original >> skills[i];
			getline(original, location);
		}
		else
		{
			replica << tmp;
			getline(original, tmp);
			replica << tmp << endl;
		}
	} while (!original.eof());
	original.close();
	replica.close();
	remove("database.txt");
	rename("database1.txt", "database.txt");
	int choise = 0;
	ofstream inFile("database.txt", ios::app);
	string* temp;
	while (choise != 4)
	{
		cout << "What you want to edit:" << endl << "1 - Wage" << endl << "2 - Location" << endl << "3 - Add skill" << endl << "4 - Save" << endl;
		cin >> choise;
		switch (choise)
		{
		case 0:
			tech();
			break;
		case 1:
			cout << "Enter new wage: ";
			cin >> salary;
			break;
		case 2:
			cout << "Enter new location: ";
			cin.ignore();
			getline(cin, location);
			location = " " + location;
			break;
		case 3:
			temp = new string[numofskills + 1];
			for (int i = 0; i < numofskills; ++i)
				temp[i] = skills[i];
			skills = temp;
			cout << "Enter new skill: ";
			cin >> temp[numofskills];
			numofskills++;
			break;
		case 4:
			inFile << username << " " << pass << " " << fullname << " " << CONTRACTOR_TYPE << " " << salary << " " << numofskills;
			for (int i = 0; i < numofskills; ++i)
				inFile << " " << skills[i];
			inFile << location<< endl;
			break;
		default:
			cout << "Incorrect input" << endl;
			break;
		}
	}
	inFile.close();
}

void addvacation(Contractor& worker)
{
	int starthour = 0, endhour = 0;
	cout << "enter the date you start the vacation" << endl;
	WorkDay startVacation = calendar(worker.details.username);
	cout << "enter the date you end the vacation" << endl;
	WorkDay endVacation = calendar(worker.details.username);
	for (int i = 0; i < worker.numOfWorkDays; ++i)
	{
		if (startVacation.year <= worker.workDay[i].year && endVacation.year >= worker.workDay[i].year)
			if (startVacation.month <= worker.workDay[i].month && endVacation.month >= worker.workDay[i].month)
				if (startVacation.day <= worker.workDay[i].day && endVacation.day >= worker.workDay[i].day)
				{
					cout << "You can't report a vacation on this day, you already reported a workday on this day" << endl;
					return;
				}
	}
	while (!(startVacation.day == endVacation.day + 1 && startVacation.month == endVacation.month && startVacation.year == endVacation.year))
	{
		if (startVacation.day == 32)
		{
			startVacation.day = 1;
			startVacation.month++;
			if (startVacation.month == 13)
			{
				startVacation.month = 1;
				startVacation.year++;
			}
		}
		worker.numOfWorkDays++;
		WorkDay* temp = new WorkDay[worker.numOfWorkDays];
		temp[0].day = startVacation.day;
		temp[0].month = startVacation.month;
		temp[0].year = startVacation.year;
		temp[0].startTime = starthour;
		temp[0].endTime = endhour;
		for (int i = 1; i < worker.numOfWorkDays; ++i)
		{
			temp[i].day = worker.workDay[i - 1].day;
			temp[i].month = worker.workDay[i - 1].month;
			temp[i].year = worker.workDay[i - 1].year;
			temp[i].startTime = worker.workDay[i - 1].startTime;
			temp[i].endTime = worker.workDay[i - 1].endTime;
		}
		delete[] worker.workDay;
		worker.workDay = temp;
		startVacation.day++;
	}
}

void addworkday(Contractor& worker)
{
	WorkDay date = calendar(worker.details.username);
	cout << "Enter the hour u Started to work: " << endl;
	cin >> date.startTime;
	cout << "Enter the hour u Finished to work: " << endl;
	cin >> date.endTime;
	for (int i = 0; i < worker.numOfWorkDays; ++i)
	{
		if (date.day == worker.workDay[i].day)
			if (date.month == worker.workDay[i].month)
				if (date.year == worker.workDay[i].year)
				{
					worker.workDay[i].startTime = date.startTime;
					worker.workDay[i].endTime = date.endTime;
					return;
				}
	}
	worker.numOfWorkDays++;
	WorkDay* temp = new WorkDay[worker.numOfWorkDays];
	temp[0].day = date.day;
	temp[0].month = date.month;
	temp[0].year = date.year;
	temp[0].startTime = date.startTime;
	temp[0].endTime = date.endTime;
	for (int i = 1; i < worker.numOfWorkDays; ++i)
	{
		temp[i].day = worker.workDay[i - 1].day;
		temp[i].month = worker.workDay[i - 1].month;
		temp[i].year = worker.workDay[i - 1].year;
		temp[i].startTime = worker.workDay[i - 1].startTime;
		temp[i].endTime = worker.workDay[i - 1].endTime;
	}
	delete[] worker.workDay;
	worker.workDay = temp;
}

void updateWorkHistory(Contractor& worker)
{
	string checkInput;
	ifstream original;
	original.open("workHistory.txt");
	ofstream replica;
	replica.open("workHistory2.txt");
	while (!original.eof())
	{
		getline(original, checkInput);
		if (checkInput == worker.details.username)
			break;
		replica << checkInput << endl;
	}
	string temp;
	int num;
	original >> num;
	for (int i = 0; i < num + 1; ++i)
	{
		getline(original, temp);
	}
	while (!original.eof())
	{
		getline(original, temp);
		replica << temp;
		if (!original.eof())
			replica << endl;
	}
	replica << worker.details.username << endl;
	replica << worker.numOfWorkDays << endl;
	for (int i = 0; i < worker.numOfWorkDays; ++i)
	{
		replica << worker.workDay[i].day << " ";
		replica << worker.workDay[i].month << " ";
		replica << worker.workDay[i].year << " ";
		replica << worker.workDay[i].startTime << " ";
		replica << worker.workDay[i].endTime << endl;
	}
	original.close();
	replica.close();
	remove("workHistory.txt");
	rename("workHistory2.txt", "workHistory.txt");
}

int calculateHours(int start, int finish) // example:: start = 8, finish = 17 ... => = 9 hours
{
	int hours = 0;
	for (int i = start; i < finish; i++)
		hours++;
	return hours;
}

void lowercase(string& data)
{
	transform(data.begin(), data.end(), data.begin(),
		[](unsigned char c) { return tolower(c); });
}

bool checkUserExists(ifstream& inFile, string userName)
{
	string checkUser;
	string skipLine;
	while (!inFile.eof()) {
		inFile >> checkUser; // Getting the UserName field from the file.
		if (checkUser == userName)
			return true;
		getline(inFile, skipLine); // Skiping line
	}
	return false; // If no matching user was found.
}

void statisticAnalysis()
{
	ourLogo();
	cout << "Company�s Statistic Analysis:" << endl;
	cout << "Contractor numbers: " << ContractorCount << endl;
	cout << "Contractor Hired: " << ContractorHired << endl;
	cout << "Employer Numbers: " << EmployerCount << endl;
	cout << "Return to menu - press Enter";
	getchar();
	getchar();
}

void hrMenu(string userInput)
{
	int choice = 0;
	while (choice != 5)
	{
		ourLogo();
		cout << "Hello, welcome to the HR Menu, what do you want to do next? " << endl
			<< "1.Statistic Analysis" << endl
			<< "2.Monitor Hiring" << endl
			<< "3.Add New Worker" << endl
			<< "4.Workers Feed" << endl
			<< "5.Sign out" << endl;
		cin >> choice;
		switch (choice) {
		case 0: // technical support
			tech();
			break;
		case 1:
			statisticAnalysis();
			break;
		case 2:
			monitorHiring();
			break;
		case 3:
			addNewWorker();
			break;
		case 4:
			workersFeed();
			break;
		case 5:
			cout << "Signed out of the system." << endl;
			break;
		default:
			cout << "Please enter choice between 1-5 only, 5 to sign out." << endl;
		}
	}
}

void addNewWorker()
{
	ourLogo();
	string username, fullName, place, pass;
	int wage, numberSkills;
	cout << "Hello, welcome to add a new worker " << endl;
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> pass;
	cout << "Enter full name: ";
	cin >> fullName;
	cout << "Enter wage: ";
	cin >> wage;
	cout << "Enter how much skills contractor has: ";
	cin >> numberSkills;
	string* skills = new string[numberSkills];
	if (skills == NULL)
	{
		cout << "cannot allocate memory" << endl;
		return;
	}
	for (int i = 0; i < numberSkills; ++i)
	{
		cout << "Enter " << i + 1 << " skill: ";
		cin >> skills[i];
	}
	cout << "Enter city: ";
	cin.ignore();
	getline(cin, place);
	fstream inFile;
	inFile.open("database.txt", ios::app);
	if (inFile.fail()) {
		cout << "error opening file" << endl;
		exit(1);
	}
	lowercase(username);
	inFile << username << " ";
	inFile << pass << " ";
	inFile << fullName << " ";
	inFile << CONTRACTOR_TYPE << " ";
	inFile << wage << " ";
	inFile << numberSkills << " ";
	for (int i = 0; i < numberSkills; ++i)
	{
		inFile << skills[i] << " ";
	}
	inFile << place << endl;
	inFile.close();
	inFile.open("workHistory.txt", ios::app);
	if (inFile.fail()) {
		cout << "error opening file" << endl;
		exit(1);
	}
	inFile << username << endl;
	inFile << "0" << endl;
	delete[] skills;
	inFile.close();
	cout << "New worker added succesfully. Return to menu - press Enter";
	getchar();
	getchar();
	++ContractorCount;
}

void monitorHiring() 
{
	ourLogo();
	fstream inFile;
	inFile.open("HiringHistory.txt");
	if (inFile.fail()) {
		cout << "error opening file" << endl;
		exit(1);
	}
	string getLine;
	while (!inFile.eof()) {
		getline(inFile, getLine); // Skiping line
		cout << getLine<<endl;
		//cout << endl;
	}
	cout << "Return to menu - press Enter";
	getchar();
	getchar();
	inFile.close();
}

void workersFeed()
{
	ourLogo();
	ifstream inFile;
	inFile.open("database.txt");
	if (inFile.fail()) {
		cout << "error opening file" << endl;
		exit(1);
	}
	string userName;
	string temp;
	Contractor user;
	cout << "Hello, Please enter the username: " << endl;
	cin >> userName;
	if (checkUserExists(inFile, userName))
	{
		buildContractor(user, userName);
		cout << "Contractor details: " << endl;
		cout << "Name: " << user.details.fullName << endl;
		cout << "Wage: " << user.salary << endl;
		cout << "Skills:" << endl;
		for (int i = 1; i <= user.numskills; ++i)
		{
			cout << "\t" << i << ": " << user.skill[i - 1] << endl;
		}
		cout << "City: " << user.place << endl;
		cout << "Workhistory:" << endl;
		for (int i = 0; i < user.numOfWorkDays; ++i)
		{
			if ((user.workDay[i].startTime != 0 && user.workDay[i].endTime != 0) && (user.workDay[i].startTime != -1 && user.workDay[i].endTime != -1))
				cout << "\t" << user.workDay[i].day << "/" << user.workDay[i].month << "/" << user.workDay[i].year << "\t" << user.workDay[i].startTime << ":00 - " << user.workDay[i].endTime << ":00" << endl;
			else if(user.workDay[i].startTime == 0 && user.workDay[i].endTime == 0)
				cout << "\t" << user.workDay[i].day << "/" << user.workDay[i].month << "/" << user.workDay[i].year << " - Vacation"<< endl;
		}
		inFile.close();
		cout << "Return to menu - press Enter" << endl;
		getchar();
	}
	else cout << "User does not exist. Return to menu - press Enter" << endl;
	getchar();
	inFile.close();
}

void employeerMenu(string userInput)
{
	int choice = 0;
	while (choice != 3)
	{
		ourLogo();
		cout << "Hello, welcome to the Employeer Menu, what do you want to do next? " << endl
			<< "1.Hiring History" << endl
			<< "2.Search Contractor" << endl
			<< "3.Sign out" << endl;
		cin >> choice;
		switch (choice) {
		case 0: // technical support
			tech();
			break;
		case 1:
			hiringHistory(userInput);
			break;
		case 2:
			searchContractor(userInput);
			break;
		case 3:
			cout << "Signed out of the system." << endl;
			break;
		default:
			cout << "Please enter choice between 1-3 only, 3 to sign out." << endl;
		}
	}
}

void hiringHistory(string currentUser)
{
	ourLogo();
	ifstream inFile;
	string temp;
	inFile.open("HiringHistory.txt");
	while (!inFile.eof()) 
	{
		getline(inFile, temp);
		if (temp == "UserName:")
		{
			getline(inFile, temp);
			if (temp == currentUser)
			{
				getline(inFile, temp);
				getline(inFile, temp);
				if (temp != "UserName:")
				{
					do
					{
						cout << temp<<endl;
						getline(inFile, temp);
					} while ((temp != "UserName:") && (!inFile.eof()));
					inFile.close();
					cout << "Return to menu - press Enter";
					getchar();
					getchar();
					return;
				}
			}
		}
	}
	inFile.close();
	cout << "Return to menu - press Enter";
	getchar();
	getchar();
}

void searchContractor(string currentUser)
{
	ourLogo();
	string location, skill, temp;
	int minWage, maxWage;
	WorkDay date;
	cout << "Enter location ( 0 if not needed)" << endl;
	cin.ignore();
	getline(cin, location);
	location = " " + location;
	cout << "Enter Skill ( 0 if not needed)" << endl;
	cin >> skill;
	cout << "Enter minimum wage ( 0 if not needed)" << endl;
	cin >> minWage;
	cout << "Enter maxWage ( 0 if not needed)" << endl;
	cin >> maxWage;
	cout << "Enter date ( 0 if not needed)" << endl;
	date = calendar(currentUser);
	fstream inFile;
	inFile.open("database.txt");
	if (inFile.fail()) {
		cout << "error opening file" << endl;
		exit(1);
	}
	int checkType, userNumSkills, userSalary, flag = 0;
	string UserName, userPass, userUsername, userPlace;
	cout << "searching workers for: " << skill << "\t" << date.day << "/" << date.month << "/" << date.year << endl;
	while (!inFile.eof()) {
		inFile >> userUsername;
		inFile >> userPass;
		inFile >> UserName;
		inFile >> checkType;
		if (checkType == CONTRACTOR_TYPE)//if the user is contractor 
		{
			inFile >> userSalary;
			inFile >> userNumSkills;
			string* userSkills = new string[userNumSkills];
			if (userSkills == NULL)
			{
				cout << "cannot allocate memory" << endl;
				return;
			}
			for (int i = 0; i < userNumSkills; ++i) {

				inFile >> userSkills[i];
			}
			getline(inFile, userPlace);
			if (userPlace == location || location == " 0")
			{
				if (checkSkills(userSkills, userNumSkills, skill) || skill == "0")
				{
					if ((userSalary > minWage && userSalary < maxWage) || (minWage < userSalary && maxWage == 0))
					{
						if (checkDate(date, userUsername))//check if the contractor is available
						{
							++flag;
							cout <<"Username: " << userUsername << endl<<"Wage: " << userSalary <<endl<<"Skills: "<<endl;
							for (int i = 0; i < userNumSkills; ++i)
							{
								cout <<"\t" <<userSkills[i]<<endl;
							}
							cout << "===================================================================" << endl;
						}
					}
				}
			}
			delete[] userSkills;
		}
	}
	if (flag == 0)
	{
		cout << "Cannot find contractor that fit to your needs, return to menu - press Enter" << endl;
		inFile.close();
		getchar();
		getchar();
		return;
	}
	getchar();
	cout << "Please enter the name of the contractor you want to book" << endl;
	cin >> UserName;
	bookContractor(UserName, currentUser, date); // contrator, employer , date
	inFile.close();
}

bool checkSkills(string* skills, int length, string skill)
{
	for (int i = 0; i < length; ++i)
		if (skills[i] == skill)
			return true;
	return false;
}

bool checkDate(WorkDay date, string userName)
{
	string tempUser;
	WorkDay temp; //temp date
	fstream inFile;
	inFile.open("workHistory.txt");
	if (inFile.fail()) {
		cout << "error opening file" << endl;
		exit(1);
	}
	while (!inFile.eof())
	{
		inFile >> tempUser;
		if (tempUser == userName)
		{
			int numofdays;
			inFile >> numofdays;
			for (int i = 0; i < numofdays; ++i)
			{
				inFile >> temp.day;
				inFile >> temp.month;
				inFile >> temp.year;
				inFile >> temp.startTime;
				inFile >> temp.endTime;
				if (temp.day == date.day)
					if (temp.month == date.month)
						if (temp.year == date.year)
						{
							inFile.close();
							return false;
						}

			}

		}
	}
	inFile.close();
	return true;
}

void bookContractor(string username, string currentUser, WorkDay date)
{
	Contractor worker;
	buildContractor(worker, username);
	worker.numOfWorkDays++;
	WorkDay* temp = new WorkDay[worker.numOfWorkDays];
	temp[0].day = date.day;
	temp[0].month = date.month;
	temp[0].year = date.year;
	temp[0].startTime = -1; //worker need to report starttime and endtime
	temp[0].endTime = -1;
	for (int i = 1; i < worker.numOfWorkDays; ++i)
	{
		temp[i].day = worker.workDay[i - 1].day;
		temp[i].month = worker.workDay[i - 1].month;
		temp[i].year = worker.workDay[i - 1].year;
		temp[i].startTime = worker.workDay[i - 1].startTime;
		temp[i].endTime = worker.workDay[i - 1].endTime;
	}
	delete[] worker.workDay;
	worker.workDay = temp;
	updateWorkHistory(worker);


	string datestring = username;
	datestring += " ";
	datestring += to_string(date.day);
	datestring += " ";
	datestring += to_string(date.month);
	datestring += " ";
	datestring += to_string(date.year);
	string tmp;
	ifstream original("HiringHistory.txt");
	ofstream replica("HiringHistory2.txt");
	getline(original, tmp);
	while (!original.eof() && tmp!=currentUser)
	{
		replica << tmp<<endl;
		getline(original, tmp);
	}
	while (!original.eof() && tmp != "UserName: ")
	{
		replica << tmp<<endl;
		getline(original, tmp);
	}
	replica << datestring << endl;
	if (!original.eof())
	{
		replica << tmp << endl;
		while (!original.eof())
		{
			getline(original, tmp);
			replica << tmp << endl;
		}
	}
	original.close();
	replica.close();
	remove("HiringHistory.txt");
	rename("HiringHistory2.txt", "HiringHistory.txt");
	++ContractorHired;//increas the number of contractor that hired
}

WorkDay calendar(string currentUser) {
	int month, day, year;
	do {
		cout << "Enter your month (1-12)" << endl
			<< "1 - January " << endl
			<< "2 - February " << endl
			<< "3 - March " << endl
			<< "4 - April " << endl
			<< "5 - May " << endl
			<< "6 - June " << endl
			<< "7 - July " << endl
			<< "8 - August " << endl
			<< "9 - September " << endl
			<< "10 - October " << endl
			<< "11 - November " << endl
			<< "12 - December " << endl;
		cin >> month;
		if (month < 1 || month > 12) {
			cout << "Error, Month must be between 1 and 12 Try again, "
				<< currentUser << endl;
		}
	} while (month < 1 || month > 12);
	do {
		cout << "Enter day" << endl;
		cin >> day;
		if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12)) {
			if ((day < 1) || (day > 31))
				cout << "Error, in Months 1,3,5,7,8,10,12 the Day must be between 1 and 31\nTry again, "
				<< currentUser << endl;
			else break;
		}
		else if ((month == 4) || (month == 6) || (month == 9) || (month == 11)) {
			if ((day < 1) || (day > 31))
				cout << "Error, in Months 4,6,9,11 the Day must be between 1 and 30\nTry again, "
				<< currentUser << endl;
			else break;
		}
		else {
			if ((day < 1) || (day > 28))
				cout << "Error, in Month February the Day must be between 1 and 28\nTry again, "
				<< currentUser << endl;
			else break;
		}
	} while (1);
	cout << "enter year: ";
	cin >> year;
	WorkDay temp;
	temp.day = day;
	temp.month = month;
	temp.year = year;
	return temp;
}