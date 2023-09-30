Name of Game: ASCII Farkle
Author: Ziheng (Tony) Fang

Goal: Score higher & reach 10k points before your opponent.

Game play techniques: 
1) Roll dice
2) Select dice you want and save it. 
3) Score is calculated.
4) Game ends when any player reaches 10k points.
5) Player with the greater amount of points when game
ends wins.

Scoring Algorithm: 
Number of Ones:
1 - 100 Points
2 - 200 Points
3 - 1000 Points
4 - 2000 Points 
5 - 4000 Points
6 - 8000 Points
Number of Twos:
1 or 2 - No points
3 - 200 Points
4 - 400 Points
5 - 800 Points 
6 - 1600 Points
Number of Threes:
1 or 2 - No Points
3 - 300 Points
4 - 600 Points
5 - 1200 Points
6 - 2400 Points
Number of Fours: 
1 or 2 - No points
3 - 400 Points
4 - 800 Points
5 - 1600 Points
6 - 3200 Points
Number of Fives:
1 - 50 Points
2 - 100 Points
3 - 500 Points
4 - 1000 Points
5 - 2000 Points
6 - 4000 Points
Number of Sixes:
1 or 2 - No points (0)
3 - 600 Points
4 - 1200 Points
5 - 2400 Points
6 - 4800 Points
Three Pair : 500 Points
Straight Six : 1000 Points

Removal and replacement techniques:
N/A

AIA Player:
After each roll, the AIA player will always take 1's, 2's, 3's, 4's, and 6's if they yield points.
It will only take 5's if there are more than 3 of them or all if there are more than 3 remaining 
dice to roll.

End game condition:
If any player reaches 10k points.

What works:
Currently allows human to play and have score calculated. 
Bell rings after each roll.
Selected dice printed in green. Others printed in red.
Human & AIA player can play, score is calculated.
Able to determine the winner, loser, quitter, and ties.

What doesn't work:
The AIA does in fact work, however I do not know how I can get it to show the actual dice it rolls.
Also when you get a farkle, it automatically skips to the other player without letting you see what
you rolled.
