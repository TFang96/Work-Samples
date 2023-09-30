#include <iostream>
#include <string>

using namespace std;

class System
{
	public:
		System();
		System(float mon, float c, float scan, float h, float key, float mem, float proj, int logInt, string logFP);
		void setMonitor(float m);
		float getMonitor();
		void setCPU(float c);
		float getCPU();
		void setScanner(float s);
		float getScan();
		void setHard(float h);
		float getHard();
		void setKey(float k);
		float getKey();
		void setMem(float m);
		float getMem();
		void setProj(float p);
		float getProj();
		void setInstru(int instr);
		int getInstru();
		void setFilePath(string fp);
		string getFilePath();
	private:
		float monitor;
		float cpu;
		float scanner;
		float hard;
		float keyboard;
		float memory;
		float projector;
		int logInstruction;
		string logFilePath;
};
