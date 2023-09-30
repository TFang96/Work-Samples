#include "Process.h"

/* default constructor */
Process::Process()
{
	processNum = 0;
	totalTime = 0;
	IOCount = 0;
	finished = false;
}

/* parameterized constructor */
Process::Process(int pNum)
{
	processNum = pNum;
	totalTime = 0;
	IOCount = 0;
	finished = false;
}

/*obtains the process ID. */
int Process::GetNum()
{
	return processNum;
}

/* sets the process ID. */
void Process::SetNum(int n)
{
	processNum = n;
}

/* adds a task to the process. */
void Process::AddTask(Task t)
{
	remainingTasks.push_back(t);
}

/* obtains the running time of the process. */
void Process::CalcTime()
{
	for(int i = 0; i < remainingTasks.size(); i++)
	{
		if(remainingTasks[i].GetTime() > 0)
		{
			totalTime += remainingTasks[i].GetTime();
		}
	}
}

/* returns the running time of the process. */
int Process::GetTime()
{
	return totalTime;
}

/* calculates the number of IO tasks for the process. */
void Process::CalcIO()
{
	for(int i = 0; i < remainingTasks.size(); i++)
	{
		if(remainingTasks[i].IsIO())
			IOCount++;
	}
}

/* gets the number of IO tasks for the process. */
int Process::GetIO()
{
	return IOCount;
}

/* gets the total number of tasks for the process. */
int Process::TotalTasks()
{
	return remainingTasks.size();
}

/* function to create tasks executed by current rr run. */
void Process::CreateCurrentTasks(int q)
{
	currentTasks.clear(); // clear the vector to begin with. 
	int quantum = q;
	for(int i = 0; i < remainingTasks.size(); i++)
	{
		if(remainingTasks[i].GetTime() > 0)
		{
			if(remainingTasks[i].GetTime() > quantum)
			{
				Task newCurrent = Task(remainingTasks[i].GetType(), remainingTasks[i].GetCount(), quantum);
				currentTasks.push_back(newCurrent);
				remainingTasks[i].DecrementTime(quantum);
				if(remainingTasks[i].GetTime() <= 0)
				{
					remainingTasks.erase(remainingTasks.begin() + i);
				}
				break;
			}
			else if(remainingTasks[i].GetTime() == quantum)
			{
				Task newCurrent = Task(remainingTasks[i].GetType(), remainingTasks[i].GetCount(), quantum);
				currentTasks.push_back(newCurrent);
				remainingTasks[i].DecrementTime(quantum);
				if(remainingTasks[i].GetTime() <= 0)
				{
					remainingTasks.erase(remainingTasks.begin() + i);
				}
				break;
			}
			else // time smaller than quantum
			{
				Task newCurrent = Task(remainingTasks[i].GetType(), remainingTasks[i].GetCount(), remainingTasks[i].GetTime());
				currentTasks.push_back(newCurrent);
				remainingTasks[i].DecrementTime(quantum);
				if(remainingTasks[i].GetTime() <= 0)
				{
					remainingTasks.erase(remainingTasks.begin() + i);
				}
			}
		}
	}
}

/* checks to see if process is complete or interupted. */
bool Process::IsFinished()
{
	return remainingTasks.size() == 0;
}

/* gets all the tasks for the process. */
vector<Task> Process::GetTasks()
{
	return remainingTasks;
}

vector<Task> Process::GetCurrentTasks()
{
	return currentTasks;
}
