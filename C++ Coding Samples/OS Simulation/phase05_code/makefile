sim05.o: Driver.o PCB.o Process.o Task.o
	g++ -pthread -std=c++17 -g Driver.o PCB.o Process.o Task.o -o sim05.o 
Driver.o: System.h PCB.h Process.h Task.h sim05.cpp
	g++ -pthread -std=c++17 -g -c sim05.cpp -o Driver.o
PCB.o: PCB.h PCB.cpp
	g++ -std=c++17 -g -c PCB.cpp -o PCB.o
Process.o: Task.h Process.h Process.cpp
	g++ -std=c++17 -g -c Process.cpp -o Process.o
Task.o: Task.h Task.cpp
	g++ -std=c++17 -g -c Task.cpp -o Task.o
clean :
	rm *.o 

