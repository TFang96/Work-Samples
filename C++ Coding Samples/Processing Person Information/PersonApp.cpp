#include "Person.h"
#include <vector>
#include <fstream>
#include <time.h>
/**
default constructor. does not return anything.
*/
Person::Person()
{
	firstName = " ";
	lastName = " ";
	sex = " ";
	birthYear = 0;
	birthMonth = 0;
	birthDay = 0;
}

/** 
constructor. does not return anything.
*/
Person::Person(string fname, string lname, string s, int byear,
	int bmth, int bday)
{
	firstName = fname;
	lastName = lname;
	sex = s;
	birthYear = byear;
	birthMonth = bmth;
	birthDay = bday;
}

/**
mutator for first & last name.
does not return anything.
*/
void Person::setName(string fname, string lname)
{
	firstName = fname; 
	lastName = lname;
}

/**
mutator for gender.
does not return anything.
*/
void Person::setGender(string gen)
{
	sex = gen;
}

/** 
mutator for birth info. 
does not return anything.
*/
void Person::setBirth(int year, int month, int day)
{
	birthYear = year;
	birthMonth = month;
	birthDay = day;
}

/**
returns the first name.
*/
string Person::getFname()
{
	return firstName;
}

/**
returns the last name.
*/
string Person::getLname()
{
	return lastName;
}

/**
returns the gender.
*/
string Person::getGender()
{
	return sex;
}

/**
returns the birth year
*/
int Person::getYear()
{
	return birthYear;
}

/** 
returns the birth month
*/
int Person::getMonth()
{
	return birthMonth;
}

/**
returns the birth day.
*/ 
int Person::getDay()
{
	return birthDay;
}

// prototypes for functions.
void ReadFile(vector<Person>& List, string file);
void PrintInfo(vector<Person> List);
void printMeFirst(string name, string courseInfo);
bool findLastName(string name, vector<Person> List);

/**
Main function. 
return 0.
*/
int main(int argc, char * argv[])
{
	// Print programmer information.
	printMeFirst("Ziheng (Tony) Fang", "Lab 4: CS 116 Thursday");
	// Vector to hold list.
	vector<Person> personList;
	// Read file & store info.
	ReadFile(personList, argv[1]);
	// Variable to hold user's choice.
	int choice;
	// Print instructions.
	cout << "Please make a selection: " << endl;
	cout << "\t" << "1- Find person by last name. " << endl;
	cout << "\t" << "2- Print all information. " << endl;
	cout << "\t" << "3- Exit. " << endl;
	cin >> choice; // input user choice.
	// if invalid input has been entered.
	while (cin.fail())
	{
		cin.clear();
		cin.ignore();
		cout << "Invalid input, enter a numeric value. ";
		cout << endl;
	}
	// If user enters a 3, program will quit.
	while (choice !=3)
	{
		//temp last name user enter's
		string temp_name;
		//switch between choices user makes.
		switch(choice)
		{
			// if user enter's 1, we search for info.
			case 1:
				cout << "Please enter the name you wish to find. " << endl;
				cin >> temp_name;
				if(findLastName(temp_name, personList))
					cout << "Person found! " << endl;
				else
					cout << "Name not found. " << endl;
				cout << "What would you like to do next? " << endl;
				cout << "\t" << "1- Search for a last name. " << endl;
				cout << "\t" << "2- Print all information. " << endl;
				cout << "\t" << "3 - Exit. " << endl;
				cin >> choice;
				while(cin.fail())
				{
					cin.clear();
					cin.ignore();
					cout << "Invalid input, enter a numeric value. " << endl;
					cin >> choice;
				}
				break;
			// if user enter's 2, we print all info.
			case 2:
				PrintInfo(personList);
				cout << "What would you like to do next? " << endl;
				cout << "\t" << "1- Search for a last name. " << endl;
				cout << "\t" << "2- Print all information. " << endl;
				cout << "\t" << "3 - Exit. " << endl;
				cin >> choice;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore();
					cout << "Invalid input, enter a numeric value. " << endl;
					cin >> choice;
				}
				break;
			// if user enter's a numeric value other than 1, 2, or 3.
			default:
				cout << "Invalid input, try again. " << endl;
				cout << "What would you like to do next? " << endl;
				cout << "\t" << "1- Search for a last name. " << endl;
				cout << "\t" << "2- Print all information. " << endl;
				cout << "\t" << "3 - Exit. " << endl;
				cin >> choice;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore();
					cout << "Invalid input, enter a numeric value. " << endl;
					cin >> choice;
				}
				break;
		}
	}
	if (choice == 3) // user wants to quit
		cout << "Have a great day, goodbye. " << endl;
	return 0;
}

/**
Read info from the file and print out information.
Does not return anything.
*/
void ReadFile(vector<Person> & List, string file)
{
	// temp variables to hold info
	string temp_first;
	string temp_last;
	string temp_gen;
	int tempYear;
	int tempMonth;
	int tempDay;
	// open input file
	ifstream input;
	input.open(file.c_str());
	while(!input.eof())
	{
		input >> temp_first;
		input >> temp_last;
		input >> temp_gen;
		input >> tempYear;
		input >> tempMonth;
		input >> tempDay;
		Person temp = Person(temp_first, temp_last, temp_gen, tempYear, tempMonth, tempDay);
		List.push_back(temp);
	}
	input.close();
}

/**
Prints everyone's information.
Does not return anything.
*/
void PrintInfo(vector<Person> List)
{
	for (int i = 0; i < List.size()-1; i++)
	{
		cout << "First Name: " << List[i].getFname() << endl;
		cout << "Last Name: " << List[i].getLname() << endl;
		cout << "Gender: " << List[i].getGender() << endl;
		cout << "Birth Year: " << List[i].getYear() << endl;
		cout << "Birth Month: " << List[i].getMonth() << endl;
		cout << "Birth Day: " << List[i].getDay() << endl;
		cout << endl;
	}
}

/**
Checks to see if last name exists in list.
returns true if it exists and false if it does not.
*/
bool findLastName(string name, vector<Person> List)	
{
	bool found = false;
	for (int i = 0; i < List.size(); i++)
	{
		if(List[i].getLname() == name)
			found = true;
	}
	if (found)
		return true;
	return false;
}

/**
Print programmer's info.
Does not return anything. 
*/
void printMeFirst(string name, string courseInfo)
{
	cout << "Program written by: " << name << endl;
	cout << "Course info: " << courseInfo << endl;
	time_t now = time(0);
	char * dt = ctime (&now);
	cout << "Date: " << dt << endl;
}
