#include <iostream>
#include <string>

using namespace std;

class Person
{
	public:
		Person(); // default constructor.
		Person(string fname, string lname, string s, int byear,
			int bmth, int bday); // constructor
		void setName(string fname, string lname); // sets name.
		void setGender(string gen); // sets gender
		void setBirth(int year, int month, int day); //sets birth info.
		string getFname(); // returns first name
		string getLname(); // returns last name
		string getGender(); // returns gender
		int getYear(); // returns birth year
		int getMonth(); // returns birth month
		int getDay(); // returns birth day
	private:
		string firstName; // holds first name
		string lastName; // holds last name
		string sex; // holds gender
		int birthYear; // holds birth year
		int birthMonth; // holds birth month
		int birthDay; // holds birth day.
};
