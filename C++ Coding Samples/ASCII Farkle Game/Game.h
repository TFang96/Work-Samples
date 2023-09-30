// Add Documentation here

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
using namespace std;

#define MAX_DICE 6
#define POINTS_TO_WIN 5000
#define MIN_FIRST_SCORE 500

enum state_types { GO, HUMANWINS, TIE, AIAWINS, QUITTER };
enum player_type { NONE, HUMAN, AIA };

class Game
{
    public:
	
        Game (const string & T);
	// Game destructor
        ~Game ();
	// Prototype to initialize Game.
	void Init ();
	// Prototype to print instructions.
        void Instructions (ostream & outs);
	// Prototype to start turn.
	void StartTurn ();
	// Output operator for game.
	friend ostream & operator << (ostream & outs, const Game & G);
        bool Enter (char selection, ostream & outs);
	bool TurnDone ();
	// Prototype for AIA function.
	void AIAPlayer (ostream & outs);
	bool Done ();
        void Message (ostream & outs);
	// Struct used to create die which are objects.
	struct Die
	{
		// Default constructor.
		Die ();
		// Output Operator for the dice.
		friend ostream & operator << (ostream & outs, const Die & D);
		// Holds the value on the dice.
		int pips;
		// Indicates whether or not the die is used or selected.
		bool selected;
		bool used;
	};
	// Tests whether or not we have a threepair.
	bool ThreePair (vector <Die> dice);

    private:
	// Rolls the dice.
        void Roll ();
	// Prototype to calculate the score.
	int CalculateScore (vector <Die> & dice);
	// Prototypes to save the selected dice & score.
	void SaveSelected ();
	void SaveScore ();
	// Holds title of game.
	string title;
	// Vectors to hold the rolled, remaining, selected, and saved dice.
        vector <Die> rolledDice;
        vector <Die> remainingDice;
        vector <Die> selectedDice;
        vector <Die> savedDice;
	// Holds the state of the game.
	state_types gameState;
	// Holds whose turn (human or AIA).
	player_type whoseTurn;
	bool turnDone;
	// Holds the number of rolls remaining.
	int numToRoll;
	int rolledScore;
	int subTotal;
	int turnTotal;
	bool humanOnBoard;
	bool aiaOnBoard;
	int humanScore;
	int aiaScore;
	bool lastTurn;
	// Variable to hold whether or not farkle is true.
	bool farkle;
};

#endif
