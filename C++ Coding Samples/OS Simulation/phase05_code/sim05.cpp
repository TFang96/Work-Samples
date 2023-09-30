/**
Name: Ziheng (Tony) Fang
Class: CS 446 - Spring 2019
Date: 2/13/2019
*/

#include <fstream>
#include <ctime>
#include <pthread.h>
#include <semaphore.h>
#include <vector> 
#include "System.h"
#include "PCB.h"
#include "Process.h"
#include "Task.h"

/* Default constructor for System */
System::System()
{
	monitor = 0;
	cpu = 0;
	scanner = 0;
	hard = 0;
	keyboard = 0;
	memory = 0;
	projector = 0; 
	logInstruction = 0;
	memAmount = 0;
	logFilePath = "NO FILE";
	memBlockSize = 0;
	projQ = 0;
	hardQ = 0;
	quantNo = 0;
	schedCode = 0;
}

/* Parameterized constructor for System. */
System::System(int mon, int c, int scan, int h, int key, int mem, int proj, int logInt, int memA, string logFP, int bSize, int pNo, int hNo, int qtNo, int schdCd)
{
	monitor = mon;
	cpu = c;
	scanner = scan;
	hard = h;
	keyboard = key;
	memory = mem;
	projector = proj;
	logInstruction = logInt;
	memAmount = memA;
	logFilePath = logFP;
	memBlockSize = bSize;
	projQ = pNo;
	hardQ = hNo;
	quantNo = qtNo;
	schedCode = schdCd;
}

/* function to set the monitor information. */
void System::setMonitor(int m)
{
	monitor = m;
}

/* function to return the monitor information. */
int System::getMonitor()
{
	return monitor;
}

/* function to set the cpu/processor information. */
void System::setCPU(int c)
{
	cpu = c;
}

/* function to return the cpu/processor information. */
int System::getCPU()
{
	return cpu;
}

/* function to set the scanner information. */
void System::setScanner(int s)
{
	scanner = s;
}

/* function to return the scanner information. */
int System::getScan()
{
	return scanner;
}

/* function to set the hard drive information. */
void System::setHard(int h)
{
	hard = h;
}

/* function to return the hard drive information. */
int System::getHard()
{
	return hard;
}

/* function to set the keyboard information. */
void System::setKey(int k)
{
	keyboard = k;
}

/* function to return the keyboard information. */
int System::getKey()
{
	return keyboard;
}

/* function to set the memory information. */
void System::setMem(int m)
{
	memory = m;
}

/* function to return the memory information. */
int System::getMem()
{
	return memory;
}

/* function to set the projector information. */
void System::setProj(int p)
{
	projector = p;
}

/* function to return the projector information. */
int System::getProj()
{
	return projector;
}

/* function to set where to log output. */
void System::setInstru(int instr)
{
	logInstruction = instr;
}

/* function to return where to log output. */
int System::getInstru()
{
	return logInstruction;
}

/* function to get the amount of memory on system. */
int System::getMemAmount()
{
	return memAmount;
}

/* function to set the amount of memory on system. */
void System::setMemAmount(int mem)
{
	memAmount = mem;
}

/* function to set the file path. */
void System::setFilePath(string fp)
{
	logFilePath = fp;
}

/* function to return file path. */
string System::getFilePath()
{
	return logFilePath;
}

void System::setBlockSize(int m)
{
	memBlockSize = m;
}

int System::getBlockSize()
{
	return memBlockSize;
}

void System::setProjQ(int p)
{
	projQ = p;
}

int System::getProjQ()
{
	return projQ;
}

void System::setHardQ(int h)
{
	hardQ = h;
}

int System::getHardQ()
{
	return hardQ;
}

void System::setQuantNo(int q)
{
	quantNo = q;
}

int System::getQuantNo()
{
	return quantNo;
}

void System::setSchedCode(int s)
{
	schedCode = s;
}

int System::getSchedCode()
{
	return schedCode;
}

void GetInfo(System s, string inputName, PCB status); // prototype for outputdata function.
double ClockDifference(clock_t time1, clock_t time2); // calculates the difference in msecs.
double ClockToMilliSeconds(clock_t t); // calculates the number of milliseconds from ticks
void * StartRoutineProj(void * t); // function for projector thread
void * StartRoutineHard(void * t); // function for hard thread
void * StartRoutineMonitor(void * t); // function for monitor thread
void * StartRoutineKey(void * t); // function for key thread
void * StartRoutineScan(void * t); // function for scan thread
void SortSJF(vector<Process> &p);
void SortPS(vector<Process> &p);
sem_t sem1; // semaphore for projector
sem_t sem2; // semaphore for hard drive
sem_t sem3; // semaphore for monitor
sem_t sem4; // semaphore for keyboard
sem_t sem5; // semaphore for scanner. 
void ExecuteProcesses(vector<Process> p, System s, ofstream &o, PCB status);
void ExecuteProcessesRR(vector<Process> p, System s, ofstream & o, PCB status);
bool IsAllFinished(vector<Process>p);

/* main function. */
int main(int argc, char * argv[])
{
	ifstream configFile; // declare an ifstream object as 'configFile' for the configuration file.
	configFile.open(argv[1]); //open the configuration file
	/* if there is a problem opening the configuration file. */
	if(!configFile.is_open())
	{
		cout << "Error: The configuration file is not found... " << endl;
		return 1;
	}
	string fileName = argv[1]; // gets the configuration file name.
	size_t dotPos = fileName.find('.'); // gets the position of the dot separating file name and extension.
	string extension = fileName.substr(dotPos + 1, fileName.length()); // get file extension.
	/* exit if invalid file type for configuration file. */
	if(extension != "conf")
	{
		cout << "Error: Invalid configuration file type... exiting... " << endl;
		return 2;
	}
	/* testing for empty file. */
	if(configFile.peek() == std::ifstream::traits_type::eof())
	{
		cout << "Error: The configuration file is empty... exiting... " << endl;
		return 3;
	}
	string tempName; // string to temporarily hold lines read in.
	string titleOfFile; // gets the first line of file.
	string versionName; // stores the version number of the configuration file
	string fileInfo; // store name of file.
	int version = 0; // stores the version of the configuration file
	int projTime = 0; // stores the cycle time of the projector
	int cpuTime = 0; // stores the cycle time of the processor/cpu
	int keyboard = 0; // stores the cycle time of the keyboard.
	int monitor = 0; // stores the display time of the monitor
	int scanner= 0; // stores the scanner cycle time
	int hardDrive = 0; // stores the hard drive cycle time.
	int mem = 0; // stores the memory cycle time. 
	int sysMem; // total amount of memory
	int blckSize; // includes the size of each memory block.
	int projNo; // the number of projectors
	int hardNo; // the number of hard drives. 
	int logStatus; // holds value as to where to output.
	int quantum;
	string schedulingCode;
	int scheduling;
	string logInfo; // gets information on where to output.
	string logFileName; // string to hold the log file name. 
	string dummyData; // string to hold extra new line characters.
	getline(configFile, titleOfFile); // get the title of file
	getline(configFile, versionName, ':'); // get the version/phase 
	configFile >> version; // obtain version number
	getline(configFile, fileInfo, ':'); // obtain file path.
	configFile >> fileInfo; // obtain file path.
	getline(configFile, dummyData); // get rid of the new line character.
	/* Read entire configuration file. */
	while(!configFile.eof())
	{
		/* Read each line of code until ':'.*/
		getline(configFile, tempName, ':'); 
		/* If we are reading the projector cycle time. */
		if(tempName == "Projector cycle time {msec}")
		{
			configFile >> projTime;
			getline(configFile, dummyData); // get rid of the new line character.
		}
		/* If we are reading the processor cycle time. */
		else if(tempName == "Processor cycle time {msec}")
		{
			configFile >> cpuTime;
			getline(configFile, dummyData);
		}
		/* If we are reading the keyboard cycle time. */
		else if(tempName == "Keyboard cycle time {msec}")
		{
			configFile >> keyboard;
			getline(configFile, dummyData);
		}
		/* If we are reading the monitory display time. */
		else if(tempName == "Monitor display time {msec}")
		{
			configFile >> monitor;
			getline(configFile, dummyData);
		}
		/* If we are reading the scanner cycle time. */
		else if(tempName == "Scanner cycle time {msec}")
		{
			configFile >> scanner;
			getline(configFile, dummyData);
		}
		/* If we are reading the hard drive cycle time. */
		else if(tempName == "Hard drive cycle time {msec}")
		{
			configFile >> hardDrive;
			getline(configFile, dummyData);
		}
		/* If we are reading in the memory cycle time. */
		else if(tempName == "Memory cycle time {msec}")
		{
			configFile >> mem;
			getline(configFile, dummyData);
		}
		/* If we are reading in the amount of system memory. */
		else if(tempName == "System memory {kbytes}")
		{
			configFile >> sysMem;
			getline(configFile, dummyData);
		}
		/* If memory indicated in Megabytes. */
		else if(tempName == "System memory {mbytes}")
		{
			configFile >> sysMem;
			sysMem*=1000;
			getline(configFile, dummyData);
		}
		/* If memory indicated in Gigabytes. */
		else if(tempName == "System memory {gbytes}")
		{
			configFile >> sysMem;
			sysMem*=1000000;
			getline(configFile, dummyData);
		}
		/* If reading in the memory block size in kbytes */
		else if (tempName == "Memory block size {kbytes}")
		{
			configFile >> blckSize;
			getline(configFile, dummyData);
		}
		/* If memory indicated in mbytes. */
		else if(tempName == "Memory block size {mbytes}")
		{
			configFile >> blckSize;
			blckSize*=1000;
			getline(configFile, dummyData);
		}
		/* If memory indicated in gbytes. */
		else if(tempName == "Memory block size {gbytes}")
		{
			configFile >> blckSize;
			blckSize*=1000000;
			getline(configFile, dummyData);
		}
		/* If we are reading in the number of projectors. */
		else if (tempName == "Projector quantity")
		{
			configFile >> projNo;
			getline(configFile, dummyData);
		}
		/* If we are reading in the number of hard drives. */
		else if (tempName == "Hard drive quantity")
		{
			configFile >> hardNo;
			getline(configFile, dummyData);
		}
		/* If we are reading in where we are logging to. */
		else if(tempName == "Log")
		{
			getline(configFile, logInfo); // get the log info.
			if(logInfo == " Log to Monitor") // 1 - log only to monitor.
				logStatus = 1;
			if(logInfo == " Log to File") // 2 - log to file.
				logStatus = 2;
			if(logInfo == " Log to Both") // 3- log to both.
				logStatus = 3;
		}
		/* obtain the path to log file to (only applies if 2 or 3 on log status. */
		else if(tempName == "Log File Path")
		{
			configFile >> logFileName;
			getline(configFile, dummyData);
		}
		/* obtain the processor quantum number */
		else if(tempName == "Processor Quantum Number {msec}")
		{
			configFile >> quantum;
			getline(configFile, dummyData);
		}
		/* obtain the scheduling algorithm. */ 
		else if(tempName == "CPU Scheduling Code")
		{
			getline(configFile, schedulingCode);
			if(schedulingCode == " FIFO")
				scheduling = 1;
			else if(schedulingCode == " PS")
				scheduling = 2;
			else if(schedulingCode == " SJF")
				scheduling = 3;
			else if(schedulingCode == " RR")
				scheduling = 4;
			else if(schedulingCode == " STR")
				scheduling = 5;
			else
			{
				cout << "Invalid scheduling algorithm. " << endl;
				return 1;
			}
		}
		/* We know we reached the end. */
		else if(tempName == "End Simulator Configuration File\n")
		{
			break;
		}
		/* If invalid data exists in configuration file, we quit. */
		else
		{
			cout << "Invalid data read... " << tempName << endl;
			break;
		}	
	}
	configFile.close(); // close the input file.
	cout << endl;
	/* create instance of a system with attributes of configuration file. */
	System s1 = System(monitor, cpuTime, scanner, hardDrive, keyboard, mem, projTime, logStatus, sysMem, logFileName, blckSize, projNo, hardNo, quantum, scheduling);
	PCB state;
	GetInfo(s1, fileInfo, state); // output the data for the system. 
	return 0;
}

/* function outputs data in regards to a system's attributes. */
void GetInfo(System s, string inputName, PCB status)
{
	ofstream outputFile; // ofstream object to hold output file.
	outputFile.open(s.getFilePath().c_str()); // open the file in accordance to the log file path.
	ifstream inputFile; // ifstream object to hold input file.
	inputFile.open(inputName.c_str()); // open the input file.
	/* if user enters an invalid file. */
	if(!inputFile.is_open())
	{
		cout << "Input file is not found, program will now exit. " << endl;
		return;
	}
	string input = inputName; // store input name in a string.. 
	size_t dotPos = input.find('.'); // find the position of the dot.
	string extension = input.substr(dotPos+1, input.length()); // get the extension.
	/* testing for invalid file extension. */
	if(extension != "mdf")
	{
		cout << "Invalid input file extension... exiting program... " << endl;
		return;
	}
	/* testing for empty file. */
	if(inputFile.peek() == std::ifstream::traits_type::eof())
	{
		cout << "Error: The input file is empty... exiting... " << endl;
		return;
	}
	srand(time(NULL));
	double milSecsActual; // actual time in milliseconds
	clock_t timeActual; // actual time in ticks.
	int processCount = 1; // to hold process number.
	/* two temporary variables used to obtain time elapsed. */
	int timeRequired;  // holds the amount of time required for a process
	int value; // number to hold numerical value of each line. 
	string txt; // temp string to hold all non-digit characters preceding number. 
	string tempVal; // temp string to hold number.
	size_t offset; // variable to determine where number and non-digit characters separate.
	vector<Process> processes; 
	Process newProcess;
	/* read in file. */
	string dummyData; // to hold any junk data from buffer.
	getline(inputFile, dummyData); // get the first line of text
	string readIn; // holds the info read in from buffer.
	/* read entire input file. */
	while(!inputFile.eof())
	{
		getline(inputFile, readIn, ';'); // obtain each line. 
		/* remove new line character if it is there. */
		if(readIn.at(0) == '\n' || readIn.at(0) == '\r')
		{
			readIn.erase(0, 1);  
			/* if next character is a space. */
			if(readIn.at(0) == ' ')
				readIn.erase(0, 1);
		}
		/* remove extra space if it exists. */
		if(readIn.at(0) == ' ') 
		{
			readIn.erase(0, 1);
			/* if next character is a new line. */
			if(readIn.at(0) == '\n')
				readIn.erase(0, 1);
		}
		offset = readIn.find('}'); // determine where the non-digit characters and the number meets.
		tempVal = readIn.substr(offset + 1); // store number as a string.
		/* check too see if value is missing. */
		if(tempVal == " ")
		{
			cout << "Error: Missing cycle value... Exiting... " << endl;
			return;
		}
		txt = readIn.substr(0, offset); //store the non-digit characters as a substring. 
		value = stoi(tempVal); // convert number to an integer.
		/* Negative values are not valid. */
		if(value < 0)
		{
			cout << "Error: Negative cycle value read in... Program will now exit..." << endl;
			return;
		}
		/* if we are beginning or ending the simulation. */
		if (txt.at(0) == 'S')
		{
			/* if we are beginning the simulation. */
			if(txt == "S{begin")
			{
				timeActual = clock(); //get time.
				milSecsActual = ClockToMilliSeconds(timeActual); // convert to milliseconds.
				status.SetProcessState(1); // set process state.
				/* print per instructions. */
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Simulator program starting" << endl;
				else if(s.getInstru() == 2)
					outputFile << milSecsActual << " - " << "Simulator program starting" << endl;
				else
				{
					cout << milSecsActual << " - " << "Simulator program starting" << endl;
					outputFile << milSecsActual << " - " << "Simulator program starting" << endl;
				}
			}
			/* if we are ending the simulation. */
			else if(txt == "S{finish")
			{
				/* sort via priority scheduling. */
				if(s.getSchedCode() == 2)
				{
					SortPS(processes);
					ExecuteProcesses(processes, s, outputFile, status);
				}
				/* sort via shortest job first. */
				else if(s.getSchedCode() == 3 || s.getSchedCode() == 5)
				{
					SortSJF(processes);
					ExecuteProcesses(processes, s, outputFile, status);
				}
				/* do round robin execution. */
				else if(s.getSchedCode() == 4)
					ExecuteProcessesRR(processes, s, outputFile, status);
				/* ending simulation. */
				timeActual = clock(); // get time
				milSecsActual = ClockToMilliSeconds(timeActual); // convert to milliseconds.
				status.SetProcessState(5); // set process state.
				/* print per instructions. */
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Simulator program ending" << endl;
				else if(s.getInstru() == 2)
					outputFile << milSecsActual << " - " << "Simulator program ending" << endl;
				else
				{
					cout << milSecsActual << " - " << "Simulator program ending" << endl;
					outputFile << milSecsActual << " - " << "Simulator program ending" << endl;
				}
				return;
			}
			else // if invalid data read in we exit.
			{
				cout << "Error: Invalid data read in... Program will now exit... " << endl;
				return;
			}
				
		}
		/* if we begin or end a process. */
		else if(txt.at(0) == 'A')
		{
			/* beginning a process. */
			if(txt == "A{begin")
			{
				status.SetProcessState(1); // set system status.
				milSecsActual = ClockToMilliSeconds(timeActual); // convert to milliseconds. 
				newProcess = Process(processCount); // creates a new process. 
			}
			/* finishing a process. */
			else if(txt == "A{finish")
			{
				status.SetProcessState(5); // set state
				timeActual = clock(); // get time.
				milSecsActual = ClockToMilliSeconds(timeActual); // convert to milliseconds.
				newProcess.CalcTime();
				newProcess.CalcIO();
				processes.push_back(newProcess);
				processCount++; // add on the number of processes.
			}
			else // if invalid data is read in.
			{
				cout << "Error: Invalid data read in... Program will now exit... " << endl;
				return;
			}
		}
		/* if we are reading in a processor aspect. */
		else if(txt == "P{run")
		{
			status.SetProcessState(3); // set system status.
			/* create and add task. */
			Task processTask = Task("Processor", processCount);
			processTask.CalcTime(s);
			newProcess.AddTask(processTask);
		}
		/* if we are reading in a memory allocation aspect. */
		else if(txt == "M{allocate")
		{
			status.SetProcessState(3); // set process state
			/* create and add task. */
			Task memoryTask = Task("Memory Allocate", processCount);
			memoryTask.CalcTime(s);
			newProcess.AddTask(memoryTask);
		}
		/* if we are reading in a memory blocking aspect. */
		else if(txt == "M{block")
		{
			status.SetProcessState(3); // set process status
			/* create and add task. */
			Task memoryTask = Task("Memory Block", processCount);
			memoryTask.CalcTime(s);
			newProcess.AddTask(memoryTask);
		}
		/* if we are reading in a monitor aspect. */
		else if(txt == "O{monitor")
		{
			status.SetProcessState(4); // set system status.
			/* create and add task. */
			Task monitorTask = Task("Monitor", processCount);
			monitorTask.CalcTime(s);
			newProcess.AddTask(monitorTask);
		}
		/* if we are reading in a hard drive aspect. */
		else if(txt == "I{hard drive")
		{
			status.SetProcessState(4); // set system status.
			/* create and add task. */
			Task hardTask = Task("Hard Drive input", processCount);
			hardTask.CalcTime(s);
			newProcess.AddTask(hardTask);
		}
		/* if we are reading in a scanner aspect. */
		else if(txt == "I{scanner")
		{
			status.SetProcessState(4); // set system status
			/* create and add task. */
			Task scanTask = Task("Scanner", processCount);
			scanTask.CalcTime(s);
			newProcess.AddTask(scanTask);
		}
		/* if we are reading in a projector aspect. */
		else if(txt == "O{projector")
		{
			status.SetProcessState(4); // set system status. 
			/* create and add task. */
			Task projTask = Task("Projector", processCount);
			projTask.CalcTime(s);
			newProcess.AddTask(projTask);
		}
		/* if we are reading in a keyboard aspect. */
		else if(txt == "I{keyboard")
		{
			status.SetProcessState(4); // set system status
			/* create and add task. */
			Task keyTask = Task("Keyboard", processCount);
			keyTask.CalcTime(s);
			newProcess.AddTask(keyTask);
		}
		/* if we are reading in a hard drive output aspect.*/
		else if(txt == "O{hard drive")
		{
			status.SetProcessState(4); // set system status
			/* create and add task. */
			Task hardTask = Task("Hard Drive output", processCount);
			hardTask.CalcTime(s);
			newProcess.AddTask(hardTask);
		}
		/* cases of invalid data */
		else
		{
			cout << "Invalid data detected from input file.... " << txt << " program will now exit... " << endl;
			break;
		}
	}
	inputFile.close(); // close input file.
	outputFile.close(); // close output file. 
}

double ClockDifference(clock_t time1, clock_t time2)
{
	double diffTicks = time2 - time1; // difference in ticks
	double diffMSecs = diffTicks/(CLOCKS_PER_SEC/1000); // difference in milliseconds
	return diffMSecs; // return the difference in milliseconds
}

void * StartRoutineProj(void * t)
{
	sem_wait(&sem1);
	int *actualTime = (int *)t;
	clock_t t1 = clock();
	clock_t t2 = clock();
	/* wait out the required time. */
	while(ClockDifference(t1, t2) < *actualTime)
	{
		t2 = clock();
	}
	sem_post(&sem1);
	pthread_exit(NULL);
}

void * StartRoutineHard(void * t)
{
	sem_wait(&sem2);
	int *actualTime = (int *)t;
	clock_t t1 = clock();
	clock_t t2 = clock();
	/* wait out the required time. */
	while(ClockDifference(t1, t2) < *actualTime)
	{
		t2 = clock();
	}
	sem_post(&sem2);
	pthread_exit(NULL);
}

void * StartRoutineMonitor(void * t)
{
	sem_wait(&sem3);
	int *actualTime = (int *)t;
	clock_t t1 = clock();
	clock_t t2 = clock();
	/* wait out the required time. */
	while(ClockDifference(t1, t2) < *actualTime)
	{
		t2 = clock();
	}
	sem_post(&sem3);
	pthread_exit(NULL);
}

void * StartRoutineKey(void * t)
{
	sem_wait(&sem4);
	int *actualTime = (int *)t;
	clock_t t1 = clock();
	clock_t t2 = clock();
	/* wait out the required time. */
	while(ClockDifference(t1, t2) < *actualTime)
	{
		t2 = clock();
	}
	sem_post(&sem4);
	pthread_exit(NULL);
}

void * StartRoutineScan(void * t)
{
	sem_wait(&sem5);
	int *actualTime = (int *)t;
	clock_t t1 = clock();
	clock_t t2 = clock();
	/* wait out the required time. */
	while(ClockDifference(t1, t2) < *actualTime)
	{
		t2 = clock();
	}
	sem_post(&sem5);
	pthread_exit(NULL);
}

double ClockToMilliSeconds(clock_t t)
{
	double MSecs = t/(CLOCKS_PER_SEC/1000); // convert ticks to milliseconds
	return MSecs; // return milliseconds.
}

/* Function to sort processes by job lenth (shorter jobs are ones with lesser tasks will have precedence.). */
void SortSJF(vector<Process> &p)
{
	int minIndex;
	for(int i = 0; i < p.size() - 1; i++)
	{
		minIndex = i;
		for(int j = i+1; j < p.size(); j++)
		{
			if(p[j].TotalTasks() < p[minIndex].TotalTasks())
				minIndex = j;
		}
		swap(p[minIndex], p[i]);
	}
}

/* Function to sort processes by priority (more IO = higher priority). */
void SortPS(vector<Process> &p)
{
	int minIndex;
	for(int i = 0; i < p.size() -1; i++)
	{
		minIndex = i;
		for(int j = i+1; j <p.size(); j++)
		{
			if(p[j].GetIO() > p[minIndex].GetIO())
				minIndex = j;
		}
		swap(p[minIndex], p[i]);
	}
}

/* Function to simulate execution of all processes and tasks within. */
void ExecuteProcesses(vector<Process> p, System s, ofstream &o, PCB status)
{
	double milSecsActual; // actual time in milliseconds
	clock_t timeActual; // actual time in ticks.
	clock_t tempTime;
	clock_t tempTime2;
	pthread_t t;
	int data;
	int *dataPointer;
	int memLocation = 0;; // randomly generate integer memory location.
	int currHard = 0; // holds the current hard drive used
	int currProj = 0; // holds the current projector used.
	sem_init(&sem1, 0, s.getProjQ());
	sem_init(&sem2, 0, s.getHardQ());
	sem_init(&sem3, 0, 1);
	sem_init(&sem4, 0, 1);
	sem_init(&sem5, 0, 1);	
	for(int i = 0; i < p.size(); i++)
	{
		timeActual = clock();
		milSecsActual = ClockToMilliSeconds(timeActual);
		if(s.getInstru() == 1)
			cout << milSecsActual << " - " << "OS: preparing process " << p[i].GetNum() << endl;
		else if(s.getInstru() == 2)
			o << milSecsActual << " - " << "OS: preparing process " << p[i].GetNum() << endl;
		else
		{
			cout << milSecsActual << " - " << "OS: preparing process " << p[i].GetNum() << endl;
			o << milSecsActual << " - " << "OS: preparing process " << p[i].GetNum() << endl;
		}
		if(s.getInstru() == 1)
			cout << milSecsActual << " - " << "OS: starting process " << p[i].GetNum() << endl;
		else if(s.getInstru() == 2)
			o << milSecsActual << " - " << "OS: starting process " << p[i].GetNum() << endl;
		else
		{
			cout << milSecsActual << " - " << "OS: starting process " << p[i].GetNum() << endl;
			o << milSecsActual << " - " << "OS: starting process " << p[i].GetNum() << endl;
		}
			
		/* complete tasks in process. */	
		for(int j = 0; j < p[i].GetTasks().size(); j++)
		{
			if(p[i].GetTasks()[j].GetType() == "Processor")
			{
				status.SetProcessState(3);
				timeActual = clock(); 
				milSecsActual = ClockToMilliSeconds(timeActual);
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start processing action" << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start processing action" << endl;
				else
				{
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start processing action" << endl;
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start processing action" << endl;
				}
				tempTime = clock();
				tempTime2 = clock();
				while(ClockDifference(tempTime, tempTime2) < p[i].GetTasks()[j].GetTime())
				{
					tempTime2 = clock();
				}
				timeActual = clock();
				milSecsActual = ClockToMilliSeconds(timeActual);
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end processing action" << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end processing action" << endl;
				else
				{
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end processing action" << endl;
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end processing action" << endl;
				}
			}
			else if(p[i].GetTasks()[j].GetType() == "Monitor")
			{
				status.SetProcessState(4);
				timeActual = clock();
				milSecsActual = ClockToMilliSeconds(timeActual);
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start monitor output" << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start monitor output" << endl;
				else
				{
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start monitor output" << endl;
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start monitor output" << endl;
				}
				data = p[i].GetTasks()[j].GetTime();
				dataPointer = &data;
				pthread_create(&t, NULL, StartRoutineMonitor, (void*)dataPointer);
				pthread_join(t, NULL);
				timeActual = clock();
				milSecsActual = ClockToMilliSeconds(timeActual);
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end monitor output" << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end monitor output" << endl;
				else
				{
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end monitor output" << endl;
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end monitor output" << endl;
				}
				
			}
			else if(p[i].GetTasks()[j].GetType() == "Hard Drive input")
			{
				status.SetProcessState(4);
				timeActual = clock();
				milSecsActual = ClockToMilliSeconds(timeActual);
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start hard drive input on HDD " << currHard << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start hard drive input on HDD " << currHard << endl;
				else
				{
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start hard drive input on HDD " << currHard << endl;
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start hard drive input on HDD " << currHard << endl;
				}
				data = p[i].GetTasks()[j].GetTime();
				dataPointer = &data;
				pthread_create(&t, NULL, StartRoutineHard, (void*)dataPointer);
				pthread_join(t, NULL);
				timeActual = clock();
				milSecsActual = ClockToMilliSeconds(timeActual);
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end hard drive input" << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end hard drive input" << endl;
				else
				{
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end hard drive input" << endl;
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end hard drive input" << endl;
				}
				currHard++;
				if(currHard >= s.getHardQ())
					currHard = 0;
			}
			else if(p[i].GetTasks()[j].GetType() == "Hard Drive output")
			{
				status.SetProcessState(4);
				timeActual = clock();
				milSecsActual = ClockToMilliSeconds(timeActual);
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start hard drive output on HDD " << currHard << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start hard drive output on HDD " << currHard << endl;
				else
				{
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start hard drive output on HDD " << currHard << endl;
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start hard drive output on HDD " << currHard << endl;
				}
				data = p[i].GetTasks()[j].GetTime();
				dataPointer = &data;
				pthread_create(&t, NULL, StartRoutineHard, (void*)dataPointer);
				pthread_join(t, NULL);
				timeActual = clock();
				milSecsActual = ClockToMilliSeconds(timeActual);
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end hard drive output" << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end hard drive output" << endl;
				else
				{
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end hard drive output" << endl;
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end hard drive output" << endl;
				}
				currHard++;
				if(currHard >= s.getHardQ())
					currHard = 0;
			}
			else if(p[i].GetTasks()[j].GetType() == "Projector")
			{
				status.SetProcessState(4);
				timeActual = clock();
				milSecsActual = ClockToMilliSeconds(timeActual);	
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start projector output on PROJ " << currProj << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start projector output on PROJ " << currProj << endl;
				else
				{
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start projector output on PROJ " << currProj << endl;
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start projector output on PROJ" << currProj << endl;
				}
				data = p[i].GetTasks()[j].GetTime();
				dataPointer = &data;
				pthread_create(&t, NULL, StartRoutineProj, (void*)dataPointer);
				pthread_join(t, NULL);
				timeActual = clock();
				milSecsActual = ClockToMilliSeconds(timeActual);
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end projector output" << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end projector output" << endl;
				else
				{
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end projector output" << endl;
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end projector output" << endl;
				}
				currProj++;
				if(currProj >= s.getProj())
					currProj = 0;
			}
			else if(p[i].GetTasks()[j].GetType() == "Memory Allocate")
			{
				status.SetProcessState(3);
				timeActual = clock();
				milSecsActual = ClockToMilliSeconds(timeActual);
				/* prints per instruction. */
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": allocating memory" << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": allocating memory" << endl;
				else
				{
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": allocating memory" << endl;
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": allocating memory" << endl;
				}
				tempTime = clock();
				tempTime2 = clock();
				while(ClockDifference(tempTime, tempTime2) < p[i].GetTasks()[j].GetTime())
				{
					tempTime2 = clock();
				}
				timeActual = clock();
				milSecsActual = ClockToMilliSeconds(timeActual);
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": memory allocated at 0x" << hex << memLocation << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": memory allocated at 0x" << hex << memLocation << endl;
				else
				{
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": memory allocated at 0x" << hex << memLocation << endl;
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": memory allocated at 0x" << hex << memLocation << endl;
				}
				memLocation+=s.getBlockSize();
				if(memLocation > s.getMemAmount())
					memLocation = 0;
			}
			else if(p[i].GetTasks()[j].GetType() == "Memory Block")
			{
				status.SetProcessState(3);
				timeActual = clock();
				milSecsActual = ClockToMilliSeconds(timeActual);
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start memory blocking" << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start memory blocking" << endl;
				else
				{
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start memory blocking" << endl;
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start memory blocking" << endl;
				}
				tempTime = clock();
				tempTime2 = clock();
				while(ClockDifference(tempTime, tempTime2) < p[i].GetTasks()[j].GetTime())
				{
					tempTime2 = clock();
				}
				timeActual = clock();
				milSecsActual = ClockToMilliSeconds(timeActual);
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end memory blocking" << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end memory blocking" << endl;
				else
				{
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end memory blocking" << endl;
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end memory blocking" << endl;
				}
			}
			else if(p[i].GetTasks()[j].GetType() == "Scanner")
			{
				status.SetProcessState(4);
				timeActual = clock();
				milSecsActual = ClockToMilliSeconds(timeActual);
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start scanner input" << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start scanner input" << endl;
				else
				{
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start scanner input" << endl;
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start scanner input" << endl;
				}
				data = p[i].GetTasks()[j].GetTime();
				dataPointer = &data;
				pthread_create(&t, NULL, StartRoutineScan, (void*)dataPointer);
				pthread_join(t, NULL);
				timeActual = clock();
				milSecsActual = ClockToMilliSeconds(timeActual);
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end scanner input" << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end scanner input" << endl;
				else
				{
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end scanner input" << endl;
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end scanner input" << endl;
				}
			}
			else if(p[i].GetTasks()[j].GetType() == "Keyboard")
			{
				status.SetProcessState(4);
				timeActual = clock();
				milSecsActual = ClockToMilliSeconds(timeActual);
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start keyboard input" << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start keyboard input" << endl;
				else
				{
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start keyboard input" << endl;
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start keyboard input" << endl;
				}
				data = p[i].GetTasks()[j].GetTime();
				dataPointer = &data;
				pthread_create(&t, NULL, StartRoutineKey, (void*)dataPointer);
				pthread_join(t, NULL);
				timeActual = clock();
				milSecsActual = ClockToMilliSeconds(timeActual);
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end keyboard input" << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end keyboard input" << endl;
				else
				{
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end keyboard input" << endl;
					o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end keyboard input" << endl;
				}
			}
		}
	}
}
					
/* function executes processes via round robin. */
void ExecuteProcessesRR(vector<Process> p, System s, ofstream & o, PCB status)
{
	double milSecsActual;
	clock_t timeActual;
	clock_t tempTime;
	clock_t tempTime2;
	pthread_t t;
	int data;
	int *dataPointer;
	int memLocation = 0;
	int currHard = 0;
	int currProj = 0;
	sem_init(&sem1, 0, s.getProjQ());
	sem_init(&sem2, 0, s.getHardQ());
	sem_init(&sem3, 0, 1);
	sem_init(&sem4, 0, 1);
	sem_init(&sem5, 0, 1);
	while(!IsAllFinished(p))
	{
		for(int i = 0; i<p.size(); i++)
		{
			timeActual = clock();
			milSecsActual = ClockToMilliSeconds(timeActual);
			if(s.getInstru() == 1)
				cout << milSecsActual << " - " << "OS: preparing process " << p[i].GetNum() << endl;
			else if(s.getInstru() == 2)
				o << milSecsActual << " - " << "OS: preparing process " << p[i].GetNum() << endl;
			else
			{
				cout << milSecsActual << " - " << "OS: preparing process " << p[i].GetNum() << endl;
				o << milSecsActual << " - " << "OS: preparing process " << p[i].GetNum() << endl;
			}
			if(s.getInstru() == 1)
				cout << milSecsActual << " - " << "OS: starting process " << p[i].GetNum() << endl;
			else if(s.getInstru() == 2)
				o << milSecsActual << " - " << "OS: starting process " << p[i].GetNum() << endl;
			else
			{
				cout << milSecsActual << " - " << "OS: starting process " << p[i].GetNum() << endl;
				o << milSecsActual << " - " << "OS: starting process " << p[i].GetNum() << endl;
			}
			p[i].CreateCurrentTasks(s.getQuantNo());
			for(int j = 0; j<p[i].GetCurrentTasks().size(); j++)
			{
				if(p[i].GetCurrentTasks()[j].GetType() == "Processor")
				{
					status.SetProcessState(3);
					timeActual = clock();
					milSecsActual = ClockToMilliSeconds(timeActual);
					if(s.getInstru() == 1)
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start processing action" << endl;
					else if(s.getInstru() == 2)
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start processing action" << endl;
					else
					{
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start processing action" << endl;
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start processing action" << endl;
					}
					tempTime = clock();
					tempTime2 = clock();
					while(ClockDifference(tempTime, tempTime2) < p[i].GetCurrentTasks()[j].GetTime())
					{
						tempTime2 = clock();
					}
					if(s.getInstru() == 1)
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end processing action" << endl;
					else if(s.getInstru() == 2)
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end processing action" << endl;
					else
					{
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end processing action" << endl;
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end processing action" << endl;
					}
				}
				else if(p[i].GetCurrentTasks()[j].GetType() == "Monitor")
				{
					status.SetProcessState(4);
					timeActual = clock();
					milSecsActual = ClockToMilliSeconds(timeActual);
					if(s.getInstru() == 1)
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start monitor output" << endl;
					else if(s.getInstru() == 2)
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start monitor output" << endl;
					else
					{
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start monitor output" << endl;
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start monitor output" << endl;
					}
					data = p[i].GetCurrentTasks()[j].GetTime();
					dataPointer = &data;
					pthread_create(&t, NULL, StartRoutineMonitor, (void*)dataPointer);
					pthread_join(t, NULL);
					timeActual = clock();
					milSecsActual = ClockToMilliSeconds(timeActual);
					if(s.getInstru() == 1)
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end monitor output" << endl;
					else if(s.getInstru() == 2)
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end monitor output" << endl;
					else
					{
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end monitor output" << endl;
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end monitor output" << endl;
					}
				}
				else if(p[i].GetCurrentTasks()[j].GetType() == "Hard Drive input")
				{
					status.SetProcessState(4);
					timeActual = clock();
					milSecsActual = ClockToMilliSeconds(timeActual);
					if(s.getInstru() == 1)
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start hard drive input on HDD " << currHard << endl;
					else if(s.getInstru() == 2)
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start hard drive input on HDD " << currHard << endl;
					else
					{
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start hard drive input on HDD " << currHard << endl;
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start hard drive input on HDD " << currHard << endl;
					}
					data = p[i].GetCurrentTasks()[j].GetTime();
					dataPointer = &data;
					pthread_create(&t, NULL, StartRoutineHard, (void*)dataPointer);
					pthread_join(t, NULL);
					timeActual = clock();
					milSecsActual = ClockToMilliSeconds(timeActual);
					if(s.getInstru() == 1)
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end hard drive input" << endl;
					else if(s.getInstru() == 2)
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end hard drive input" << endl;
					else
					{
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end hard drive input" << endl;
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end hard drive input" << endl;
					}
					currHard++;
					if(currHard >= s.getHardQ())
						currHard = 0;
				}
				else if(p[i].GetCurrentTasks()[j].GetType() == "Hard Drive output")
				{
					status.SetProcessState(4);
					timeActual = clock();
					milSecsActual = ClockToMilliSeconds(timeActual);
					if(s.getInstru() == 1)
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start hard drive output on HDD " << currHard << endl;
					else if(s.getInstru() == 2)
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start hard drive output on HDD " << currHard << endl;
					else
					{
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start hard drive output on HDD " << currHard << endl;
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start hard drive output on HDD " << currHard << endl;
					}
					data = p[i].GetCurrentTasks()[j].GetTime();
					dataPointer = &data;
					pthread_create(&t, NULL, StartRoutineHard, (void*)dataPointer);
					pthread_join(t, NULL);
					timeActual = clock();
					milSecsActual = ClockToMilliSeconds(timeActual);
					if(s.getInstru() == 1)
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end hard drive output" << endl;
					else if(s.getInstru() == 2)
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end hard drive output" << endl;
					else
					{
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end hard drive output" << endl;
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end hard drive output" << endl;
					}
					currHard++;
					if(currHard >= s.getHardQ())
						currHard = 0;
				}
				else if(p[i].GetCurrentTasks()[j].GetType() == "Projector")
				{
					status.SetProcessState(4);
					timeActual = clock();
					milSecsActual = ClockToMilliSeconds(timeActual);
					if(s.getInstru() == 1)
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start projector output on PROJ " << currProj << endl;
					else if(s.getInstru() == 2)
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start projector output on PROJ " << currProj << endl;
					else
					{
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start projector output on PROJ " << currProj << endl;
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start projector output on PROJ " << currProj << endl;
					}
					data = p[i].GetCurrentTasks()[j].GetTime();
					dataPointer = &data;
					pthread_create(&t, NULL, StartRoutineProj, (void*)dataPointer);
					pthread_join(t, NULL);
					timeActual = clock();
					milSecsActual = ClockToMilliSeconds(timeActual);
					if(s.getInstru() == 1)
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end projector output" << endl;
					else if(s.getInstru() == 2)
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end projector output" << endl;
					else
					{
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end projector output" << endl;
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end projector output" << endl;
					}
					currProj++;
					if(currProj >= s.getProj())
						currProj = 0;
				}
				else if(p[i].GetCurrentTasks()[j].GetType() == "Memory Allocate")
				{
					status.SetProcessState(3);
					timeActual = clock();
					milSecsActual = ClockToMilliSeconds(timeActual);
					if(s.getInstru() == 1)
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": allocating memory" << endl;
					else if(s.getInstru() == 2)
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": allocating memory" << endl;
					else
					{
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": allocating memory" << endl;
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": allocating memory" << endl;
					}
					tempTime = clock();
					tempTime2 = clock();
					while(ClockDifference(tempTime, tempTime2) < p[i].GetCurrentTasks()[j].GetTime())
					{
						tempTime2 = clock();
					}
					timeActual = clock();
					milSecsActual = ClockToMilliSeconds(timeActual);
					if(s.getInstru() == 1)
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": memory allocated at 0x" << hex << memLocation << endl;
					else if(s.getInstru() == 2)
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": memory allocated at 0x" << hex << memLocation << endl;
					else
					{
						cout << milSecsActual << " - " << "Process " <<p[i].GetNum() << ": memory allocated at 0x" << hex << memLocation << endl;
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": memory allocated at 0x" << hex << memLocation << endl;
					}
					memLocation+=s.getBlockSize();
					if(memLocation >= s.getMemAmount())
						memLocation = 0;
				}
				else if(p[i].GetCurrentTasks()[j].GetType() == "Memory Block")
				{
					status.SetProcessState(3);
					timeActual = clock();
					milSecsActual = ClockToMilliSeconds(timeActual);
					if(s.getInstru() == 1)
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start memory blocking" << endl;
					else if(s.getInstru() == 2)
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start memory blocking" << endl;
					else
					{
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start memory blocking" << endl;
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start memory blocking" << endl;
					}
					tempTime = clock();
					tempTime2 = clock();
					while(ClockDifference(tempTime, tempTime2) < p[i].GetCurrentTasks()[j].GetTime())
					{
						tempTime2 = clock();
					}
					timeActual = clock();
					milSecsActual = ClockToMilliSeconds(timeActual);
					if(s.getInstru() == 1)
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end memory blocking" << endl;
					else if(s.getInstru() == 2)
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end memory blocking" << endl;
					else
					{
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end memory blocking" << endl;
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end memory blocking" << endl;
					}
				}
				else if(p[i].GetCurrentTasks()[j].GetType() == "Scanner")
				{
					status.SetProcessState(4);
					timeActual = clock();
					milSecsActual = ClockToMilliSeconds(timeActual);
					if(s.getInstru() == 1)
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start scanner input" <<endl;
					else if(s.getInstru() == 2)
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start scanner input" << endl;
					else
					{
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start scanner input" << endl;
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start scanner input" << endl;
					}
					data = p[i].GetCurrentTasks()[j].GetTime();
					dataPointer = &data;
					pthread_create(&t, NULL, StartRoutineScan, (void*)dataPointer);
					pthread_join(t, NULL);
					timeActual = clock();
					milSecsActual = ClockToMilliSeconds(timeActual);
					if(s.getInstru() == 1)
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end scanner input" << endl;
					else if(s.getInstru() == 2)
						o << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end scanner input" << endl;
					else
					{
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end scanner input" << endl;
						o << milSecsActual << " - Process " << p[i].GetNum() << ": end scanner input" << endl;
					}
				}
				else if(p[i].GetCurrentTasks()[j].GetType() == "Keyboard")
				{
					status.SetProcessState(4);
					timeActual = clock();
					milSecsActual = ClockToMilliSeconds(timeActual);
					if(s.getInstru() == 1)
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start keyboard input" << endl;
					else if(s.getInstru() == 2)
						o << milSecsActual << " - Process " << p[i].GetNum() << ": start keyboard input" << endl;
					else
					{
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": start keyboard input" << endl;
						o << milSecsActual << " - Process " << p[i].GetNum() << ": start keyboard input" << endl;
					}
					data = p[i].GetCurrentTasks()[j].GetTime();
					dataPointer = &data;
					pthread_create(&t, NULL, StartRoutineKey, (void*)dataPointer);
					pthread_join(t, NULL);
					timeActual = clock();
					milSecsActual = ClockToMilliSeconds(timeActual);
					if(s.getInstru() == 1)
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end keyboard input" << endl;
					else if(s.getInstru() == 2)
						o << milSecsActual << " - Process " << p[i].GetNum() << ": end keyboard input" << endl;
					else
					{
						cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": end keyboard input" << endl;
						o << milSecsActual << " - Process " << p[i].GetNum() << ": end keyboard input" << endl;
					}
				}
			}
			if(!p[i].IsFinished())
			{
				if(s.getInstru() == 1)
					cout << milSecsActual << " - " << "Process " << p[i].GetNum() << ": interrupt processing action" << endl;
				else if(s.getInstru() == 2)
					o << milSecsActual << " - Process " << p[i].GetNum() << ": interrupt processing action" << endl;
				else
				{
					cout << milSecsActual << " - " << "Process "<< p[i].GetNum() << ": interrupt processing action" << endl;
					o << milSecsActual << " - Process " << p[i].GetNum() << ": interrupt processing action" << endl;
				}
			}
		}
	}
}

/*check if there are any unfinished processes*/
bool IsAllFinished(vector<Process>p)
{
	for(int i = 0; i < p.size(); i++)
	{
		if(!p[i].IsFinished())
		{
			return false;
		}
	}
	return true;
}
