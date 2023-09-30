// Assignment : Project 01
// Name: Ziheng (Tony) Fang
// Lab : Monday Afternoon
// Description: This is the farkle game. A score is calculated
// after each "roll". Each roll utilizes 6 dice. A score of zero
// would result in a farkle. A straight six would result in 1000 points
// and a three pair would result in 500 points. A pair would be a set
// of two same numbers. Three pairs would be three of such sets. One roll
// of a one would yield 100 points, two rolls would yeild 200, three rolls
// would yeild 1000, four rolls would yield 2000, five rolls would yield 4000,
// and six rolls would yield 8000. Rolling two or one 2's would yield zero points.
// A roll of three twos would yield 200 points, a roll of four would yield 400, a 
// roll of 5 would be 800 points, and a roll of 6 two's would be 1600 points. A roll of 
// one or two three's would yield zero points. Three 3's would yield 300 points, 4 would 
// yield 600, 5 would yield 1200, and six would yield 2400. Rolling two or one fours would
// yield 0 points. Rolling three 4's would yield 400 points, 4 four's would yield 800 points
// 5 fours would yield 1600 points, and 6 would yield 3200 points. A roll of one five would be
// 50 points, two 5's would be 100 points, three 5's would yield 500 points, four 5's would yield
// 1000 points, five 5's would yield 2000 points, and 6 fives would yield 4000 points. A roll
// of one or two sixes would not give us any points. A roll of three 6's would be 600 points,
// a roll of three 6's would give us 600 points, a roll of 4 six's would be 1200, a role of 5
// six's would be 2400 points, and a roll of 6 six's would be 4800 points. 

// allow the use of cin & cout
#include <iostream>
// used to read in the text file
#include <fstream>

// use the standard namespace 
using namespace std;
// Prototypes to use function
// Documentation will appear at the function implementation
void collect_data(int data_set[]);
void print_score(int ones, int twos, int threes, int fours, int fives, int sixes, int data_set[]);
bool three_pairs(int ones, int twos, int threes, int fours, int fives, int sixes);
bool straight_six(int ones, int twos, int threes, int fours, int fives, int sixes);

// Main function
int main()
{
	// Name variable to store open file.
	ifstream file;
	// Open the file
	file.open("dice.txt");
	// Variable to hold the number of roles.
	int num_of_roles = 0;	
	// Variable to hold the role number. 
	int role_number = 0;
	// Read the number of roles into variable num_of_roles
	while (file >> num_of_roles)
	{
		// This means we have hit the end of the file!
		if (num_of_roles == 0)
			// We have to exit.
			break;
		// This is a counter for the while loop
		// to make sure we don't accidently 
		// read a "number of roles" as a number
		// shown on the dice.
		int count = 0;
		// Array to hold the numbers ending up on dice.
		int data_set[6];
		// Int to hold the number resulting on the rolled dice.
		int dice_number;
		// Read in numbers that are the results of the rolled dice.
		while (count < num_of_roles)
		{
			// Input operator takes input from our file and puts 
			// them in "dice_number"
			file >> dice_number;
			// Places the dice results into our array.
			data_set[count] = dice_number; 
			// Increment the count number. 
			count++;
		}
		// Increment the role number.
		role_number++;
		// Prints "Roll :"
		cout << "Roll " << role_number << ":";
		// Passes the vector to function "collect data" to process
		// the results on dice.
		collect_data(data_set);
		// Clears the array for the next round.
		for (int i = 0; i < 6; i++)
			data_set[i] = 0;
	}
	return 0;
}

// This function basically counts the results
// to see how many one's, two's, three's, four's,
// five's, and six's we get in each role. 
// It does NOT calculate the final score. 
void collect_data(int data_set[])
{
	// Counter to for the while loop.
	int count = 0;
	// Holds the number of ones during the role.
	int num_of_ones = 0;
	// Holds the number of twos during the role.
	int num_of_twos = 0;
	// Holds the number of threes during the role.
	int num_of_threes = 0;
	// Holds the number of fours during the role.
	int num_of_fours = 0;
	// Holds the number of fives during the role.
	int num_of_fives = 0;
	// Holds the number of sixes during the role.
	int num_of_sixes = 0;
	// While loop to update the number of one's,
	// two's, three's, four's, five's, and six's
	// so they are accurate.
	while (count < 6)
	{
		// The following if/else-if statements would
		// update the number of one's, two's, three's, four's
		// five's, and six's so they are accurate
		if (data_set[count] == 1)
			num_of_ones++;
		else if (data_set[count] == 2)
			num_of_twos++;
		else if (data_set[count] == 3)
			num_of_threes++;
		else if (data_set[count] == 4)
			num_of_fours++;
		else if (data_set[count] == 5)
			num_of_fives++;
		else if (data_set[count] == 6)
			num_of_sixes++;
		// Increment counter. We don't want 
		// to be in an infinite loop.
		count++;
	} 
	// Sends data to print_score to calculate
	// score and print it on the screen.
	print_score(num_of_ones, num_of_twos, num_of_threes, 
		num_of_fours, num_of_fives, num_of_sixes, data_set);
}

// Function to calculate & print actual score. 
void print_score(int ones, int twos, int threes, int fours, int fives, int sixes, int data_set[])
{
	// Score starts out with 0.
	int score = 0;
	// Checks for three pairs.
	if (three_pairs(ones, twos, threes, fours, fives, sixes))
	{
		// Increment score for a three pair.
		score = 500;
		// Prints the results (not score).
		for (int i = 0; i < 6; i++)
			cout << " -" << data_set[i] << "-";
	}
	// Checks for a straight of 6. Overrides
	// previous score since each dice can only be used once.
	else if (straight_six(ones, twos, threes, fours, fives, sixes))
	{
		score = 1000;
		// Prints the results (not score).
		for (int i = 0; i < 6; i++)
			cout << " -" << data_set[i] << "-";
	}
	// Checks all the other rules... only if there are no three pairs.
	// Since three pairs (2 x 3 = 6) would use up all six dice and 
	// each dice can only be used once, there would be no reason to test
	// any of the other rules.
	else
	{
		if (ones == 0)
			score += 0;
		else if (ones == 1)
			score += 100;
		else if (ones == 2)
			score += 200;
		else if (ones == 3)
			score += 1000;
		else if (ones == 4)
			score += 2000;
		else if (ones == 5)
			score += 4000;
		else if (ones == 6)
			score += 8000;
		if (twos == 0)
			score += 0;
		else if (twos == 1)
			score += 0;
		else if (twos == 2)
			score += 0;
		else if (twos == 3)
			score += 200;
		else if (twos == 4)
			score += 400;
		else if (twos == 5)
			score += 800;
		else if (twos == 6)
			score += 1600;
		if (threes == 0)
			score += 0;
		else if (threes == 1)
			score += 0;
		else if (threes == 2)
			score += 0;
		else if (threes == 3)
			score += 300;
		else if (threes == 4)
			score += 600;
		else if (threes == 5)
			score += 1200;
		else if (threes == 6)
			score += 2400;
		if (fours == 0)
			score += 0;
		else if (fours == 1)
			score += 0;
		else if (fours == 2)
			score += 0;
		else if (fours == 3)
			score += 400;
		else if (fours == 4)
			score += 800;
		else if (fours == 5)
			score += 1600;
		else if (fours == 6)
			score += 3200;
		if (fives == 0)
			score += 0;
		else if (fives == 1)
			score += 50;
		else if (fives == 2)
			score += 100;
		else if (fives == 3)
			score += 500;
		else if (fives == 4)
			score += 1000;
		else if (fives == 5)
			score += 2000;
		else if (fives == 6)
			score += 4000;
		if (sixes == 0)
			score += 0;
		else if (sixes == 1)
			score += 0;
		else if (sixes == 2)
			score += 0;
		else if (sixes == 3)
			score += 600;
		else if (sixes == 4)
			score += 1200;
		else if (sixes == 5)
			score += 2400;
		else if (sixes == 6)
			score += 4800;
	}
	// How to print data if we don't have three pairs or straight six
	if (three_pairs(ones, twos, threes, fours, fives, sixes) == false
		&& straight_six(ones, twos, threes, fours, fives, sixes)== false)
	{
		// Checks each roll. We only want to print the dashes
		// (-) if the roll was calculated in our score.
		for (int i = 0; i < 6; i++)
		{
			if (data_set[i] == 1)
				cout << " -" << data_set[i] << "-";
			if (data_set[i] == 2)
			{
				if (twos >= 3)
					cout << " -" << data_set[i] << "-";
				else
					cout << " " << data_set[i];
			}
			if (data_set[i] == 3)
			{ 
				if (threes >= 3)
					cout << " -" << data_set[i] << "-";
				else
					cout << " " << data_set[i];
			}
			if (data_set[i] ==4)
			{
				if (fours >= 3)
					cout << " -" << data_set[i] << "-";
				else
					cout << " " << data_set[i];
			}
			if (data_set[i] == 5)
				cout << " -" << data_set[i] << "-";
			if (data_set[i] == 6)
			{
				if (sixes >= 3)
					cout << " -" << data_set[i]<< "-";
				else
					cout << " " << data_set[i];
			}
		}
	} 
	// It's a farkle if you have 0 points.
	if (score == 0)
		cout << " ==> " << "Farkle!" << endl;
	// Print out points if you don't have a farkle.
	else
		cout << " ==> " << score << endl;
	
}

// Function would check for any 3-pairs. 
bool three_pairs(int ones, int twos, int threes, int fours, int fives, int sixes)
{
	// Variable to store the number of pairs
	int pairs = 0;
	// If there are two or or more, there obviously is a pair.
	if (ones == 2)
		pairs++;
	if (twos == 2)
		pairs++;
	if (threes == 2)
		pairs++;
	if (fours == 2)
		pairs++;
	if (fives == 2)
		pairs++;
	if (sixes == 2)
		pairs++;
	// Will return true if we have three or more pairs. 
	if (pairs == 3)
		return true;
	else
		return false;
}

// This function is to test whether or not
// we have a straight six.
bool straight_six(int ones, int twos, int threes, int fours, int fives, int sixes)
{
	// A straight six if basically if we have one of each.
	if (ones == 1 && twos == 1 && threes == 1
		&& fours == 1 && fives == 1 && sixes == 1)
		return true;
	// If that is not the case then we don't have a straight six.
	else
		return false;
}

