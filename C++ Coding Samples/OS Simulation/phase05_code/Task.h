#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>
#include "System.h"


using namespace std;

class Task
{
	public:
		Task();
		Task(string t, int c);
		Task(string t, int c, int ti);
		string GetType();
		void SetType (string t);
		int GetCount();
		void SetCount(int c);
		void CalcTime(System s);
		int GetTime();
		void DecrementTime(int q);
		bool IsIO();
	private:
		string type;
		int count;	
		int time;
		bool IO;
};

#endif
