#include "Task.h"

/* default constructor. */
Task::Task()
{
	type = "N";
	count = 0;
	time = 0;
}

/* parameterized constructor. */
Task::Task(string t, int c)
{
	type = t;
	count = c;
	time = 0;
}

/* parameterized constructor. */
Task::Task(string t, int c, int ti)
{
	type = t;
	count = c;
	time = ti;
}

/* obtains the type of the task. */
string Task::GetType()
{
	return type;
}

/* sets the type of the task. */
void Task::SetType(string t)
{
	type = t;
}

/* obtains the number of times task is to run. */
int Task::GetCount()
{
	return count;
}

/* sets the number of times task is to run. */
void Task::SetCount(int c)
{
	count = c;
}

/* obtains the time of each task. and determines whether IO is involved. */
void Task::CalcTime(System s)
{
	if(type == "Processor")
	{
		IO = false;
		time = count * s.getCPU();
	}
	else if(type == "Keyboard")
	{
		IO = true;
		time = count * s.getKey();
	}
	else if(type == "Monitor")
	{
		IO = true;
		time = count * s.getMonitor();
	}
	else if(type == "Hard Drive input")
	{
		IO = true;	
		time = count * s.getHard();
	}
	else if(type == "Hard Drive output")
	{
		IO = true;	
		time = count * s.getHard();
	}
	else if(type == "Projector")
	{
		IO = true;
		time = count * s.getProj();
	}
	else if(type == "Memory Allocate")
	{
		IO = false;
		time = count * s.getMem();
	}
	else if(type == "Memory Block")
	{
		IO = false;
		time = count * s.getMem();
	}
	else if(type == "Scanner")
	{
		IO = true;
		time = count *s.getScan();
	}
}

/* obtains the time of the task. */
int Task::GetTime()
{
	return time;
}

/* reflect completed portions. */
void Task::DecrementTime(int q)
{
	time-=q;
} 

/* determines if the task is an IO task. */
bool Task::IsIO()
{
	return IO;
}
