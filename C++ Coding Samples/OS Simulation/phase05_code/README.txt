To compile do: 'make sim05.o'
To run do: './sim05.o [config]'
*******************************
Program built on top of the 4th phase.
Changes made include a function implemented on line 80
on Process.cpp to create a vector of current tasks that
will be executed in one round of Round Robin. A function 'IsFinished'
is implemented on line 125 of Process.cpp to check whether or not the process
is finished. On line 1183 of sim05.cpp a new function 'ExecuteProessesRR' is implemented
for the Round R scheduling algorithm. Everything else remains the same. To the best of my knowledge
SJF and STR are the same thing so if the scheduling algorithm is STR, it will be handled the same way as if it was SJF. 
