#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <vector>
#include "Task.h"

using namespace std;

class Process
{
	public:
		Process();
		Process(int pNum);
		int GetNum();
		void SetNum(int n);
		void AddTask(Task t);
		void CalcTime();
		int GetTime();
		void CalcIO();
		int GetIO();
		int TotalTasks();
		void CreateCurrentTasks(int q);
		bool IsFinished();
		vector<Task> GetTasks();
		vector<Task> GetCurrentTasks();
	private:
		int processNum;
		vector<Task> remainingTasks;
		vector<Task> currentTasks;
		bool finished;
		int totalTime;
		int IOCount;
};

#endif
