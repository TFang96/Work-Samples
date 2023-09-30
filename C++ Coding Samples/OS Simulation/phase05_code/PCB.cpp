#include "PCB.h"

PCB::PCB()
{
	processState = 0;
}

PCB::PCB(int state)
{
	processState = state;
}

int PCB::GetProcessState()
{
	return processState;
}

void PCB::SetProcessState(int p)
{
	processState = p;
}
