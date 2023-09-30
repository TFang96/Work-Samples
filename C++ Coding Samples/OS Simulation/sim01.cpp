/**
Name: Ziheng (Tony) Fang
Class: CS 446 - Spring 2019
Date: 2/13/2019
*/

#include <fstream>
#include "System.h"

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
	logFilePath = "NO FILE";
}

/* Parameterized constructor for System. */
System::System(float mon, float c, float scan, float h, float key, float mem, float proj, int logInt, string logFP)
{
	monitor = mon;
	cpu = c;
	scanner = scan;
	hard = h;
	keyboard = key;
	memory = mem;
	projector = proj;
	logInstruction = logInt;
	logFilePath = logFP;
}

/* function to set the monitor information. */
void System::setMonitor(float m)
{
	monitor = m;
}

/* function to return the monitor information. */
float System::getMonitor()
{
	return monitor;
}

/* function to set the cpu/processor information. */
void System::setCPU(float c)
{
	cpu = c;
}

/* function to return the cpu/processor information. */
float System::getCPU()
{
	return cpu;
}

/* function to set the scanner information. */
void System::setScanner(float s)
{
	scanner = s;
}

/* function to return the scanner information. */
float System::getScan()
{
	return scanner;
}

/* function to set the hard drive information. */
void System::setHard(float h)
{
	hard = h;
}

/* function to return the hard drive information. */
float System::getHard()
{
	return hard;
}

/* function to set the keyboard information. */
void System::setKey(float k)
{
	keyboard = k;
}

/* function to return the keyboard information. */
float System::getKey()
{
	return keyboard;
}

/* function to set the memory information. */
void System::setMem(float m)
{
	memory = m;
}

/* function to return the memory information. */
float System::getMem()
{
	return memory;
}

/* function to set the projector information. */
void System::setProj(float p)
{
	projector = p;
}

/* function to return the projector information. */
float System::getProj()
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

void OutputData(System s, string inputName); // prototype for outputdata function.

/* main function. */
int main(int argc, char * argv[])
{
	ifstream configFile; // declare an ifstream object as 'configFile' for the configuration file.
	configFile.open(argv[1]); //open the configuration file
	/* if there is a problem opening the configuration file. */
	if(!configFile.is_open())
	{
		cout << "Error: The configuration file is not found... " << endl;
		return 0;
	}
	string tempName; // string to temporarily hold lines read in.
	string titleOfFile; // gets the first line of file.
	string versionName; // stores the version number of the configuration file
	string fileInfo; // store name of file.
	float version = 0; // stores the version of the configuration file
	float projTime = 0; // stores the cycle time of the projector
	int cpuTime = 0; // stores the cycle time of the processor/cpu
	float keyboard = 0; // stores the cycle time of the keyboard.
	float monitor = 0; // stores the display time of the monitor
	float scanner= 0; // stores the scanner cycle time
	float hardDrive = 0; // stores the hard drive cycle time.
	float mem = 0; // stores the memory cycle time. 
	int logStatus; // holds value as to where to output.
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
		/* We know we reached the end. */
		else if(tempName == "End Simulator Configuration File\n")
		{
			break;
		}
		/* If invalid data exists in configuration file, we quit. */
		else
		{
			cout << "Invalid data read... " << endl;
			break;
		}	
	}
	configFile.close(); // close the input file.
	cout << endl;
	/* create instance of a system with attributes of configuration file. */
	System s1 = System(monitor, cpuTime, scanner, hardDrive, keyboard, mem, projTime, logStatus, logFileName);
	OutputData(s1, fileInfo); // output the data for the system. 
	return 0;
}

/* function outputs data in regards to a system's attributes. */
void OutputData(System s, string inputName)
{
	ofstream outputFile; // ofstream object to hold output file.
	outputFile.open(s.getFilePath().c_str()); // open the file in accordance to the log file path.
	ifstream inputFile; // ifstream object to hold input file.
	inputFile.open(inputName.c_str()); // open the input file.
	/* if user enters an invalid file. */
	if(!inputFile.is_open())
	{
		cout << "File is not found, program will now exit. " << endl;
		return;
	}


	/* if we only log to monitor. */
	if(s.getInstru() == 1)
	{
		cout << "Configuration File Data" << endl;
		cout << "Monitor = " << s.getMonitor() << " ms/cycle" << endl;
		cout << "Processor = " << s.getCPU() << " ms/cycle" << endl;
		cout << "Scanner = " << s.getScan() << " ms/cycle" << endl;
		cout << "Hard Drive = " << s.getHard() << " ms/cycle" << endl;
		cout << "Keyboard = " << s.getKey() << " ms/cycle" << endl;
		cout << "Memory = " << s.getMem() << " ms/cycle" << endl;
		cout << "Projector = " << s.getProj() << " ms/cycle" << endl;
		cout << "Logged to: monitor" << endl;
		cout << endl;
		cout << "Meta-Data Metrics " << endl;
	}
	/* if we only log to output file. */
	else if(s.getInstru() == 2)
	{
		outputFile << "Configuration File Data" << endl;
		outputFile << "Monitor = " << s.getMonitor() << " ms/cycle" << endl;
		outputFile << "Processor = " << s.getCPU() << " ms/cycle" << endl;
		outputFile << "Scanner = " << s.getScan() << " ms/cycle" << endl;
		outputFile << "Hard Drive = " << s.getHard() << " ms/cycle" << endl;
		outputFile << "Keyboard = " << s.getKey() << " ms/cycle" << endl;
		outputFile << "Memory = " << s.getMem() << " ms/cycle" << endl;
		outputFile << "Projector = " << s.getProj() << " ms/cycle" << endl;
		outputFile << "Logged to: " << s.getFilePath() << endl;
		outputFile << endl;
		outputFile << "Meta-Data Metrics " << endl;
	}
	/* if we log to both. */
	else
	{
		cout << "Configuration File Data" << endl;
		cout << "Monitor = " << s.getMonitor() << " ms/cycle" << endl;
		cout << "Processor = " << s.getCPU() << " ms/cycle" << endl;
		cout << "Scanner = " << s.getScan() << " ms/cycle" << endl;
		cout << "Hard Drive = " << s.getHard() << " ms/cycle" << endl;
		cout << "Keyboard = " << s.getKey() << " ms/cycle" << endl;
		cout << "Memory = " << s.getMem() << " ms/cycle" << endl;
		cout << "Projector = " << s.getProj() << " ms/cycle" << endl;
		outputFile << "Configuration File Data" << endl;
		outputFile << "Monitor = " << s.getMonitor() << " ms/cycle" << endl;
		outputFile << "Processor = " << s.getCPU() << " ms/cycle" << endl;
		outputFile << "Scanner = " << s.getScan() << " ms/cycle" << endl;
		outputFile << "Hard Drive = " << s.getHard() << " ms/cycle" << endl;
		outputFile << "Keyboard = " << s.getKey() << " ms/cycle" << endl;
		outputFile << "Memory = " << s.getMem() << " ms/cycle" << endl;
		outputFile << "Projector = " << s.getProj() << " ms/cycle" << endl;
		cout << "Logged to: monitor and " << s.getFilePath() << endl;
		outputFile << "Logged to: monitor and " << s.getFilePath() << endl;
		cout << endl;
		cout << "Meta-Data Metrics " << endl;
		outputFile << endl;
		outputFile << "Meta-Data Metrics " << endl;
	}
	int value; // number to hold numerical value of each line. 
	string txt; // temp string to hold all non-digit characters preceding number. 
	string tempVal; // temp string to hold number.
	size_t offset; // variable to determine where number and non-digit characters separate.
	/* read in file. */
	string dummyData; // to hold any junk data from buffer.
	getline(inputFile, dummyData); // get the first line of text
	string readIn; // holds the info read in from buffer.
	/* read entire input file. */
	while(!inputFile.eof())
	{
		getline(inputFile, readIn, ';'); // obtain each line. 
		/* remove new line character if it is there. */
		if(readIn.at(0) == '\n')
			readIn.erase(0, 1);  
		/* remove extra space if it exists. */
		if(readIn.at(0) == ' ') 
			readIn.erase(0, 1);
		offset = readIn.find('}'); // determine where the non-digit characters and the number meets.
		tempVal = readIn.substr(offset + 1); // store number as a string.
		txt = readIn.substr(0, offset); //store the non-digit characters as a substring. 
		value = stoi(tempVal); // convert number to an integer.
		/* if we are reading in a processor aspect. */
		if(txt.at(0) == 'P')
		{
			/* if statements determine where to output information. */
			if(s.getInstru() == 1)
			{
				cout << readIn << " - " << s.getCPU() * value << " ms" << endl;
			}
			else if(s.getInstru() == 2)
			{
				outputFile << readIn << " - " << s.getCPU() * value << " ms" << endl;
			}
			else
			{
				cout << readIn << " - " << s.getCPU() * value << " ms" << endl;
				outputFile << readIn << " - " << s.getCPU() * value << " ms" << endl;
			}
		}
		/* if we are reading in a memory aspect. */
		else if(txt.at(0) == 'M')
		{
			/* if statements determine where to output information. */
			if(s.getInstru() == 1)
			{
				cout << readIn << " - " << s.getMem() * value << " ms" << endl;
			}
			else if(s.getInstru() == 2)
			{
				outputFile << readIn << " - " << s.getMem() * value << " ms" << endl;
			}
			else
			{
				cout << readIn << " - " << s.getMem() * value << " ms" << endl;
				outputFile << readIn << " - " << s.getMem() * value << " ms" << endl;
			}
		}
		/* if we are reading in a monitor aspect. */
		else if(txt == "O{monitor")
		{
			/* if statements determine where to output information. */
			if(s.getInstru() == 1)
			{
				cout << readIn << " - " << s.getMonitor() * value << " ms" << endl;
			}
			else if(s.getInstru() == 2)
			{
				outputFile << readIn << " - " << s.getMonitor() * value << " ms" << endl;
			}
			else
			{
				cout << readIn << " - " << s.getMonitor() * value << " ms" << endl;
				outputFile << readIn << " - " << s.getMonitor() * value << " ms" << endl;
			}
		}
		/* if we are reading in a hard drive aspect. */
		else if(txt == "I{hard drive")
		{
			/* if statements determine where to output information. */
			if(s.getInstru() == 1)
			{
				cout << readIn << " - " << s.getHard() * value << " ms" << endl;
			}
			else if(s.getInstru() == 2)
			{
				outputFile << readIn << " - " << s.getHard() * value << " ms" << endl;
			}
			else
			{
				cout << readIn << " - " << s.getHard() * value << " ms" << endl;
				outputFile << readIn << " - " << s.getHard() * value << " ms" << endl;
			}
		}
		/* if we are reading in a scanner aspect. */
		else if(txt == "I{scanner")
		{
			/* if statements determine where to output information. */
			if(s.getInstru() == 1)
			{
				cout << readIn << " - " << s.getScan() * value << " ms" << endl;
			}
			else if(s.getInstru() == 2)
			{
				outputFile << readIn << " - " << s.getScan() * value << " ms" << endl;
			}
			else
			{
				cout << readIn << " - " << s.getScan() * value << " ms" << endl;
				outputFile << readIn << " - " << s.getScan() * value << " ms" << endl;
			}
		}
		/* if we are reading in a projector aspect. */
		else if(txt == "O{projector")
		{
			/* if statements determine where to output information. */
			if(s.getInstru() == 1)
			{
				cout << readIn << " - " << s.getProj() * value << " ms" << endl;
			}
			else if(s.getInstru() == 2)
			{
				outputFile << readIn << " - " << s.getProj() * value << " ms" << endl;
			}
			else
			{
				cout << readIn << " - " << s.getProj() * value << " ms" << endl;
				outputFile << readIn << " - " << s.getProj() * value << " ms" << endl;
			}
		}
		/* if we are reading in a keyboard aspect. */
		else if(txt == "I{keyboard")
		{
			/* if statements determine where to output information. */
			if(s.getInstru() == 1)
			{
				cout << readIn << " - " << s.getKey() * value << " ms" << endl;
			}
			else if(s.getInstru() == 2)
			{
				outputFile << readIn << " - " << s.getKey() * value << " ms" << endl;
			}
			else
			{
				cout << readIn << " - " << s.getKey() * value << " ms" << endl;
				outputFile << readIn << " - " << s.getKey() * value << " ms" << endl;
			}
		}
		/* if we are reading in a hard drive aspect.*/
		else if(txt == "O{hard drive")
		{
			/* if statements determine where to output information. */
			if(s.getInstru() == 1)
			{
				cout << readIn << " - " << s.getHard() * value << " ms" << endl;
			}
			else if(s.getInstru() == 2)
			{
				outputFile << readIn << " - " << s.getHard() * value << " ms" << endl;
			}
			else
			{
				cout << readIn << " - " << s.getHard() * value << " ms" << endl;
				outputFile << readIn << " - " << s.getHard() * value << " ms" << endl;
			}
		}
		/* all other cases. */
		else
		{
			/* determine if something invalid was read in. */
			if(txt.at(0) != 'S' && txt.at(0) != 'A')
			{
				cout << "Invalid data detected from input file.... program will now exit... " << endl;
				break;
			}
		}
	}
	inputFile.close(); // close input file.
	outputFile.close(); // close output file. 
}
