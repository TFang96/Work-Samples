#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>

using namespace std;

class System
{
	public:
		System();
		System(int mon, int c, int scan, int h, int key, int mem, int proj, int logInt, int memA, string logFP, int bSize, int pNo, int hNo, int qtNo, int schdCd);
		void setMonitor(int m);
		int getMonitor();
		void setCPU(int c);
		int getCPU();
		void setScanner(int s);
		int getScan();
		void setHard(int h);
		int getHard();
		void setKey(int k);
		int getKey();
		void setMem(int m);
		int getMem();
		void setProj(int p);
		int getProj();
		void setInstru(int instr);
		int getInstru();
		void setFilePath(string fp);
		int getMemAmount();
		void setMemAmount(int mem);
		string getFilePath();
		void setBlockSize(int m);
		int getBlockSize();
		void setProjQ(int p);
		int getProjQ();
		void setHardQ(int h);
		int getHardQ();
		void setQuantNo(int q);
		int getQuantNo();
		void setSchedCode(int s);
		int getSchedCode();
	private:
		int monitor;
		int cpu;
		int scanner;
		int hard;
		int keyboard;
		int memory;
		int projector;
		int logInstruction;
		int memAmount;
		int memBlockSize;
		int projQ;
		int hardQ;
		int quantNo;
		int schedCode;
		string logFilePath;
};

#endif
