/* Assignment : Project 1
File : lastnameP1.cpp
Author : Ziheng (Tony) Fang
Description : The program will first
read a set of number store in a file
then it will print the numbers, info
about them and will sort the numbers. */

// Include 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>
// Use the standard namespace.
using namespace std;

// Allocate 1000 spaces.
int const MAXNUMBERS = 1000;

// Define prototypes.
int GetNumbers (int N []);
void PrintNumbers (int N [], int C);
int GetLargest (int N[], int C);
void PrintSmallest (int N [], int C, int largest);
void PrintLargest (int largest);
void LeastDifference (int N [], int C, int largest_number);
void GreatestDifference (int N [], int C);
void AscendingSequence (int N [], int C);
void DescendingSequence (int N [], int C);
void Sort (int N [], int C);
void Swap (int & a, int & b);

int main ()
{
	// Define the array 'N'.
	int N [MAXNUMBERS];
	// Store the value from GetNumbers in
	// 'count'.
	int count = GetNumbers(N);
	// Print the numbers.
	PrintNumbers (N, count);
	// Store the value of the largest number in
	// 'largest number'.
	int largest_number = GetLargest(N, count);
	// Print the smallest number.
	PrintSmallest (N, count, largest_number);
	// Print the largest number.	
	PrintLargest (largest_number);
	// Print the numbers with the least difference.
	LeastDifference (N, count, largest_number);
	// Print the numbers with the greatest difference.
	GreatestDifference (N, count);
	// Print ascending sequence.
	AscendingSequence (N, count);
	// Print the descending sequence.
	DescendingSequence (N, count);
	// Print sorted numbers
	Sort (N, count);
	return 0;
}

// This function reads the file and gets the numbers.
int GetNumbers (int N [])
{
	ifstream input;
	// Opens "numbers.txt".
	input.open ("numbers.txt");
	// Define numbs
	int numbs;
	// Initialize count.
	int count = 0;
	// While loop runs until nothing can be put from 
	// int to numbs.
	while (input >> numbs)
	{
		/* Input the values in 
		 numbs into the array
		 N. */
		N [count] = numbs;
		/* Increment count by
  		one. */		
		count++;
	}
	// Returns the number of numbers there are.
	return count;
			
}

// This function prints all the numbers.
void PrintNumbers (int N [], int C)
{
	/* Print the line "The Numbers:" */
	cout << "The Numbers:" << endl;
	// Initialize a counter 'i'.
	int i = 0;
	while (i < C)
	{
		// Prints out each line making 8 columns.	
		for (int counter = 0; counter < 8 && i < C; counter++)
		{	
			cout << setw (10) << right <<  N[i]; 
			i++;
		}
		// Start a new line after each row.
		cout << endl;
	} 
	
}
/* This function gets and returns
 * the largest number from the set. */
int GetLargest(int N [], int C)
{
	// We start with the zero as the 
	// "largest number".
	int largest = 0;
	/* The for loop iterates until while
 * 	i is less then c, we increment i by 1
 * 	each time. */
	for (int i = 0; i < C; i++)
	{
		// Whenver we encounter a number
		// that is greater than
		// the one stored in 'largest'
		// we replace largest with the larger
		// number. In the end we would end up with
		// the largest number.
		if (N[i] > largest)
		{
			largest = N[i];
		}
	}
	// Returns the variable "largest".
	return largest;
}

// Function prints the smallest number from the file
void PrintSmallest (int N [], int C, int largest)
{
	/* We start of with the smallest number as 
 * 	the largest. */
	int smallest = largest;
	// Set i equal to 0.
	int i = 0;
	// While loop to keep iterating while i is
	// less than C.
	while (i < C)
	{
		/* Update 'smallest' to be N[i] each time
 * 		N[i] is smaller than the value stored in
 * 		smallest. */
		if (N[i] < smallest)
		{
			smallest = N[i];
		}
		// Increment i by 1.
		i++;
	}
	// Print the smallest number and start a new line.
	cout << "Smallest Number: " << smallest << endl;
}

// This function prints the largest number.
void PrintLargest (int largest)
{
	// Print largest number and start a new line.
	cout << "Largest Number: " << largest << endl;
	/* The largest number was obtained by a previous
 * 	function. */
}

void LeastDifference (int N [], int C, int largest)
{
	// Define variables LeastDiff1
	// and LeastDiff2.
	int LeastDiff1;
	int LeastDiff2;
	int i = 0;
	int diff = largest * 2;
	// While loop keeps on going until i is
	// greater than or equal to C.
	while (i < C)
	{	
		// If the difference of N[i+1]
		// and N[i] is less than the value 
		// stored in 'LeastDiff1' and 'LeastDiff2'
		// we update the variables with N[i+1] 
		// and N[i].
		if (abs(N[i+1]-N[i]) < diff)
		{
			diff = abs(N[i+1] - N[i]);
			LeastDiff1 = N[i+1];
			LeastDiff2 = N[i];
		}
	// Increment i by 1.
	i++;
	}
	// Prints the values producing the least difference.
	cout << "Least Difference: " << LeastDiff2 << " " 
		<< LeastDiff1 << endl;
}

/* This function finds the greatest 
 * difference. */
void GreatestDifference (int N [], int C)
{
	/* Variable to hold
 * 	one of the numbers. */
	int GreatestDiff1; 
	// Variable to hold the
	// adjacent number.
	int GreatestDiff2;
	// Calculate the difference
	// to start with.
	int diff = 0;
	// Use i as a counter.
	int i = 0;
	while (i < C)
	{	
		// If statement basically 
		// says that if the difference
		// of 2 adjacent numbers 
		// were greater than 'diff',
		// these two adjacent numbers
		// would be the numbers with the 
		// greatest difference.
		if (abs(N[i+1]-N[i]) > diff)
		{
			diff = abs(N[i+1] - N[i]);
			GreatestDiff1 = N[i+1];
			GreatestDiff2 = N[i];
		}
	// Increment i by 1.
	i++;
	}
	// Print the values with the greatest difference.
	cout << "Greatest Difference: " << GreatestDiff2 << " " 
		<< GreatestDiff1 << endl;		
}

/* Function prints the longest ascending
 * sequence of numbers. */
void AscendingSequence (int N [], int C)
{
	// Initialize counter.
	int i = 0;
	/* Initialize and define
 * 	temporary holders of the
 * 	start and end indexes. */
	int sequence_length_one = 0;
	int sequence_length_two = 0;
	/* Initialize and define the final
 * 	start and end index. */
	int sequence_length_begin = 0;
	int sequence_length_end = 0;
	while (i < C)
	{
		while (N[i] > N[i+1] && i < C)
		{
			i++;
		}
		sequence_length_one = i;
		while (N[i] < N[i+1] && i < C)
		{
			i++;
		}
		sequence_length_two = i+1;
		/* Only if the sequence is the longest yet, 
 * 		store the indexes of the sequence in 'sequence_length_begin'
 * 		and 'sequence_length_end'. */
		if (sequence_length_two - sequence_length_one > 
			sequence_length_end - sequence_length_begin)
			{
				sequence_length_begin = sequence_length_one;
				sequence_length_end = sequence_length_two;
			}
	}
	// Print 'Ascending Sequence: ' and 
	// start a new line.
	cout << "Ascending Sequence: " << endl;
	// Print the ascending sequence.
	for (int a = sequence_length_begin; a < sequence_length_end;
		a++)
		{	
			cout << setw (10) << right << N[a];
		}
	// Start a new line.
	cout << endl;
}

// Function prints the descending sequence.
void DescendingSequence (int N [], int C)
{
	// Declare & initalize i as a
	// counter.
	int i = 0;
	// Delcare and initialize variables
	// to hold temporary start and end
	// indexes of longest descending 
	// sequence.
	int sequence_length_one = 0;
	int sequence_length_two = 0;
	// Declare and initialize variables
	// to hold the actual indexes for the
	// start and end of the longest
	// descending sequence.
	int sequence_length_begin = 0;
	int sequence_length_end =0;
	while (i < C)
	{
		
		while (N[i] < N[i+1] && i < C)
		{
			i++;
		}
		sequence_length_one = i;
		while (N[i] > N[i+1] && i < C)
		{
			i++;
		}
		sequence_length_two = i+1;
		// Find whether or not the sequence is the "longest"
		// by finding the difference.
		if (sequence_length_two - sequence_length_one > 
			sequence_length_end - sequence_length_begin)
			{
				sequence_length_begin = sequence_length_one;
				sequence_length_end = sequence_length_two;
			}
	}
	// Print "Descending Sequence: " 
	cout << "Descending Sequence: " << endl;
	// Prints the descending sequence.
	for (int a = sequence_length_begin; a < sequence_length_end;
		a++)
		{
			cout << setw (10) << right << N[a];
		}
	// Print a new line.
	cout << endl;
				
}

/* This function sorts all the numbers
 * in order. */
void Sort (int N [], int C)
{
	// Prints "Sorted Numbers" and starts
	// a new line.
	cout << "Sorted Numbers:" << endl;
	// Loop through the entire list of numbers.
	for (int i = 0; i < C; i++)
	{
		int j = i;
		/* If any number is greater then the number
 * 		after it, we swap until it is less than the 
 * 		number after it. */
		while (j > 0 && N[j] < N[j-1])
		{
			Swap (N[j], N[j-1]);
			j--;					
		}
	}
	// Declare a counter.
	int i = 0;	
	while (i < C)
	{
		// Prints out each line making 8 columns.	
		for (int counter = 0; counter < 8 && i < C; counter++)
		{	
			cout << setw (10) << right <<  N[i];
			// Increment i by 1. 
			i++;
		}
		// Start a new line after each row.
		cout << endl;
	} 
}

/* This function swaps two values
 * when called. */
void Swap (int & a, int & b)
{
	// Store the value of a in temp.
	int temp = a;
	// Assign the value of a to temp.
	a = b;
	/* Assign the original value of 'a'
 * 	(which is currently in 'temp') to 'b'. */
	b = temp;
}
