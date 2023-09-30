#ifndef PCB_H
#define PCB_h

#include <iostream>

using namespace std;

class PCB
{
	public:
		PCB();
		PCB(int state);
		int GetProcessState();
		void SetProcessState(int p);
	private:
		int processState;
};

#endif
