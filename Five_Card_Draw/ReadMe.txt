========================================================================
                         CSE332 : Lab3
========================================================================

/////////////////////////////////////////////////////////////////////////////
                             Lab3 Info
/////////////////////////////////////////////////////////////////////////////
(1) Name: 
    Jing Lu, 
	Seed(Peiyun) Zeng

(2) Files submitted:
    Card.h and Card.cpp: Card class header and implementation
	Hand.h and Hand.cpp: Hand class header and implementation
	Deck.h and Deck.cpp: Deck class header and implementation
	Player.h and Player.cpp: Player header and implementation
	Game.h and Game.cpp: Game header and implementation
	FiveCardDraw.h and FiveCardDraw.cpp: FiveCardDraw header and implementation
	Error.h: define different error level
	lab3.cpp: main function

(3) Usage
    Type:  lab3.exe FiveCardDraw <p1's name> <p2's name> ....
	Note that
	    (1) Command line arguments need to contain at least two players to start the game
		(2) Game name should contains "FiveCardDraw"
		(3) If run on Linux, comment out #include "stdax.h" 

(4) Compile and Execution
    No errors or warnings found


/////////////////////////////////////////////////////////////////////////////
                           Modification
/////////////////////////////////////////////////////////////////////////////
Lab1 and Lab2 is reused and modified
Some changes are
(1) Deck class: add default constructor and add_card() method
(2) Hand class: add indexing operator, remove_card() method
(3) Player struct
(4) Game class
(5) FiveCardDraw class
(6) Error.h: add some new error codes


/////////////////////////////////////////////////////////////////////////////
                      Some Notes About Usage
/////////////////////////////////////////////////////////////////////////////
(1) About discarding the card: 

When the program asks if the player wants to discard cards, user can enter multiple positions of card
(position starting from 0, NOT 1). 

If user enters some invalid input(such as invalid position, non-numerical values),
only invalid input will be ignored and other inputs will still be processed.

If user inputs are all invalid, program will prompt the user again

If user does not want to discard any card, just enter "Enter"

(2) About joining and leaving the game:
When the program asks if the player wants to join or leave the game, user can enter multiple player names 
and those names will all be processed.
If no one wants to join or leave the room, type "no"

(3) About exiting the game:
When there is only one player left in the game, the program automatically saves that player's statistics to a file
and end the game

/////////////////////////////////////////////////////////////////////////////
                             Testing
/////////////////////////////////////////////////////////////////////////////

****** TEST 1 :Two Player with Well-formed Input

----------------------------------------------------------------------
                       Program Output
----------------------------------------------------------------------
Y:\jinglu\winprofile\desktop\lab3\Debug>lab3.exe FiveCardDraw seed jing
jing 2H 6H 7D 9C JD
Please give positions of cards you want to discard

seed 4D 4H 5H 7H JH
Please give positions of cards you want to discard

jing 2H 6H 7D 9C JD
seed 4D 4H 5H 7H JH
winner: seed
------------
seed 1 0

4D 4H 5H 7H JH
------------
------------
jing 0 1

2H 6H 7D 9C JD
------------
Anyone wants to leave?
no
Anyone wants to join?
no
seed 6D 10C 10D QD QH
Please give positions of cards you want to discard
0 1 3
jing 6C 6H 8D 9H JH
Please give positions of cards you want to discard
2 4
seed 4C 4D 10D JD QH
jing 5D 6C 6H 7D 9H
winner: jing
------------
jing 1 1

5D 6C 6H 7D 9H
------------
------------
seed 1 1

4C 4D 10D JD QH
------------
Anyone wants to leave?
jing
Anyone wants to leave?
no
Anyone wants to join?
no
----------------------------------------------------------------------
                         Analysis
----------------------------------------------------------------------
(1) In the first round, both players do not discard card. Since seed has a pair of 4
but jing does not have any pair, seed wins.
(2) In the second round, seed replaces his card at position 0, 1, and 3 and jing replaces
his card at position 2 and 4. Since Jing has a pair of 6 but seed has a pair of 4, jing wins.
(3) The statistics is correct because jing has 1 win and 1 lose and seed has 1 win and 1 lose.
(4) After jing leaves the game, game only contains seed(less than two palyer), so game ends.


****** TEST 2:  Two Player with Badly-formed Input

----------------------------------------------------------------------
                       Program Output
----------------------------------------------------------------------
Y:\jinglu\winprofile\desktop\lab3\Debug>lab3.exe FiveCardDraw seed jing
jing 2C 2H 3D 4H 5C
Please give positions of cards you want to discard
invalid_input
Detecting non-numeric position value from user input
Please give positions of cards you want to discard
9999
detecting invliad position from user: 9999
Please give positions of cards you want to discard
0 1 4
seed 7C 7H 9H 10H QH
Please give positions of cards you want to discard
string 0 1
Detecting non-numeric position value from user input
jing 3D 4H 5H 6D QC
seed 9H 10H JD QH KD
winner: seed
------------
seed 1 0

9H 10H JD QH KD
------------
------------
jing 1 2

3D 4H 5H 6D QC
------------
Anyone wants to leave?
no
Anyone wants to join?
no
seed 3D 4C 5D 5H 8H
Please give positions of cards you want to discard
bad_position 999
Detecting non-numeric position value from user input
detecting invliad position from user: 999
Please give positions of cards you want to discard
2
jing 5C 7D 7H 10D KD
Please give positions of cards you want to discard
1
seed 3D 4C 5H 8H 9C
jing 4H 5C 7H 10D KD
winner: jing
------------
jing 2 2

4H 5C 7H 10D KD
------------
------------
seed 1 1

3D 4C 5H 8H 9C
------------
Anyone wants to leave?
jing
Anyone wants to leave?
no
Anyone wants to join?
no

----------------------------------------------------------------------
                         Analysis
----------------------------------------------------------------------
(1) When user enters invalid input(such as string, invalid position), the program prints
corresponding warnings about invalid input.
(2) Game statistics of jing is successfully loaded from file produced by previous game.
(3) The program correctly determines who wins or loses


****** TEST 3:  Multiple Players with Well-formed Input
****** NOTE: for this test, we reset all previous game statistics
----------------------------------------------------------------------
                       Program Output
----------------------------------------------------------------------
Y:\jinglu\winprofile\desktop\lab3\Debug>lab3.exe FiveCardDraw seed jing cse332
jing 2D 6D 9H QH KC
Please give positions of cards you want to discard

cse332 2H 5C 6H 7D 8D
Please give positions of cards you want to discard

seed 3H 4D 6C 8H QC
Please give positions of cards you want to discard

jing 2D 6D 9H QH KC
cse332 2H 5C 6H 7D 8D
seed 3H 4D 6C 8H QC
winner: jing
------------
jing 1 0

2D 6D 9H QH KC
------------
------------
seed 0 1

3H 4D 6C 8H QC
------------
------------
cse332 0 1

2H 5C 6H 7D 8D
------------
Anyone wants to leave?
no
Anyone wants to join?
wustl
Anyone wants to join?
no
cse332 2D 2H 10H JD QD
Please give positions of cards you want to discard

wustl 3H 4D 5D JH QC
Please give positions of cards you want to discard

seed 3C 5C 8D 10D KH
Please give positions of cards you want to discard

jing 2C 6D 8H 10C KC
Please give positions of cards you want to discard

cse332 2D 2H 10H JD QD
wustl 3H 4D 5D JH QC
seed 3C 5C 8D 10D KH
jing 2C 6D 8H 10C KC
winner: cse332
------------
cse332 1 1

2D 2H 10H JD QD
------------
------------
jing 1 1

2C 6D 8H 10C KC
------------
------------
seed 0 2

3C 5C 8D 10D KH
------------
------------
wustl 0 1

3H 4D 5D JH QC
------------
Anyone wants to leave?
no
Anyone wants to join?
no
wustl 2D 3D 7C 10D QH
Please give positions of cards you want to discard
0 1
seed 2H 9H 10C JC QC
Please give positions of cards you want to discard
2 4
jing 4H 5H 6H JD KD
Please give positions of cards you want to discard
1
cse332 3H 4C 7D 9D JH
Please give positions of cards you want to discard
2
wustl 5C 7C 10D QD QH
seed 2H 9H 10H JC KH
jing 4H 6D 6H JD KD
cse332 3H 4C 9C 9D JH
winner: wustl
------------
wustl 1 1

5C 7C 10D QD QH
------------
------------
cse332 1 2

3H 4C 9C 9D JH
------------
------------
jing 1 2

4H 6D 6H JD KD
------------
------------
seed 0 3

2H 9H 10H JC KH
------------
Anyone wants to leave?
wustl
Anyone wants to leave?
no
Anyone wants to join?
no
jing 7H 8D 9C JC KC
Please give positions of cards you want to discard

cse332 2D 7D 10D QC KD
Please give positions of cards you want to discard

seed 3D 5C 10H JH QD
Please give positions of cards you want to discard

jing 7H 8D 9C JC KC
cse332 2D 7D 10D QC KD
seed 3D 5C 10H JH QD
winner: cse332
------------
cse332 2 2

2D 7D 10D QC KD
------------
------------
jing 1 3

7H 8D 9C JC KC
------------
------------
seed 0 4

3D 5C 10H JH QD
------------
Anyone wants to leave?
cse332
Anyone wants to leave?
no
Anyone wants to join?
no
seed 8C 9D QC QD KD
Please give positions of cards you want to discard

jing 2H 3D 3H 5C 6C
Please give positions of cards you want to discard

seed 8C 9D QC QD KD
jing 2H 3D 3H 5C 6C
winner: seed
------------
seed 1 4

8C 9D QC QD KD
------------
------------
jing 1 4

2H 3D 3H 5C 6C
------------
Anyone wants to leave?
jing
Anyone wants to leave?
no
Anyone wants to join?
no

----------------------------------------------------------------------
                         Analysis
----------------------------------------------------------------------
(1) Initially, game starts with three players (seed, jing, and cse332) and
then program correctly determines who wins and loses.
(2) At the beginning of the second round, a new player(wustl) joins the game.
Then program continues and outputs correctly.
(3) In the following rounds, wustl leaves at the end of 2nd round, cse332 leaves
at the end of 3rd round, and jing leaves at the end of 4th round. Then game ends.
(4) Game statistics of wustl, cse332 and jing is produced when they leave the game




****** TEST 4:  Multiple Players with Badly-formed Input

----------------------------------------------------------------------
                       Program Output
----------------------------------------------------------------------

Y:\jinglu\winprofile\desktop\lab3\Debug>lab3.exe FiveCardDraw jing cse332
cse332 5D 6D 7C 9D JH
Please give positions of cards you want to discard

jing 8C 8D 10D JC JD
Please give positions of cards you want to discard
0
cse332 5D 6D 7C 9D JH
jing 8D 9H 10D JC JD
winner: jing
------------
jing 2 4

8D 9H 10D JC JD
------------
------------
cse332 2 3

5D 6D 7C 9D JH
------------
Anyone wants to leave?
no
Anyone wants to join?
wustl
Anyone wants to join?
no
wustl 2C 7C 7D JC JD
Please give positions of cards you want to discard
string
Detecting non-numeric position value from user input
Please give positions of cards you want to discard
99999
detecting invliad position from user: 99999
Please give positions of cards you want to discard
1
jing 2D 8H 10D QH KC
Please give positions of cards you want to discard
invalid_input
Detecting non-numeric position value from user input
Please give positions of cards you want to discard
999 12345
detecting invliad position from user: 999
detecting invliad position from user: 12345
Please give positions of cards you want to discard
1
cse332 4C 8C 10C QD KD
Please give positions of cards you want to discard

wustl 2C 7D 8D JC JD
jing 2D 9H 10D QH KC
cse332 4C 8C 10C QD KD
winner: wustl
------------
wustl 2 1

2C 7D 8D JC JD
------------
------------
jing 2 5

2D 9H 10D QH KC
------------
------------
cse332 2 4

4C 8C 10C QD KD
------------
Anyone wants to leave?
jing
Anyone wants to leave?
cse332
Anyone wants to leave?
no
Anyone wants to join?
no

----------------------------------------------------------------------
                         Analysis
----------------------------------------------------------------------
(1) When user enters invalid input(such as string, invalid position), the program prints
corresponding warnings about invalid input.
(2) Game statistics of jing, wustl and cse332 are successfully loaded from file produced by previous game.
(3) The program correctly determines who wins or loses


/////////////////////////////////////////////////////////////////////////////
                   Extra Credit Implementation
/////////////////////////////////////////////////////////////////////////////

Desgin/Method

To play the game automated. There are two major parts to deal with: automate the before_round and after_round
I. automate before_round

Essentially, at every cin (where user inputs to control the non-automated player), if it is an automated player
we now need to calculate positions to discard the cards according to the situation. We created one helper method to
calcualte the wanted positions according to the hand of the automated player

(1).vector<int>	FiveCardDraw::auto_valid_positions(Player &player)
auto_valid_positions will generate a vector containing valid_positions to discard cards in automated player's hand
according to the given situation as discribed by the documentation

so when we call before_turn on any player, if it is an automated player, we will call auto_valid_positions to generate
the vector of valid_positions. Afterwards we will discard the cards just like dealing with ordianray players

II. automate after_round

We utlized  three extra member functions to implment this

(2)void highest_automated_leave(string automated_name);
(3)void lowest_automated_leave(string automated_name);
(4)void other_automated_leave(string automated_name);

as name suggested, they are responsible to implement the leaving of 3 kinds of automated_player.
Inside void FiveCardDraw::print_sorted_player() ( a helper function to update player info inside after_round)
we detect which situation it is for a automated player and call (2) (3) (4) accordingly
Note: we realize we cannot save a file like long*.txt, so we choose to save the file of automated player
in the format of playerName_automated.txt



/////////////////////////////////////////////////////////////////////////////
                      Extra Credit Test
/////////////////////////////////////////////////////////////////////////////

NOTE: some statisttics are not reset, player might have statistics from previous games


****** TEST 1:  Two automated players

----------------------------------------------------------------------
                       Program Output
----------------------------------------------------------------------
X:\jinglu\winprofile\desktop\lab3\Debug>lab3.exe FiveCardDraw seed* jing*
jing* 3C 6D 8H QC KD
Automated Player: jing* 3C 6D 8H QC KD  is playing
seed* 2C 2D 9D 10C KC
Automated Player: seed* 2C 2D 9D 10C KC  is playing
jing* 4C 8C QC QD KD
seed* 2C 2D 2H 5D 7D
winner: seed*
------------
seed* 1 0

2C 2D 2H 5D 7D
------------
------------
jing* 0 1

4C 8C QC QD KD
------------
Automated player seed* does not leave the game with highest rank with 90%
Automated player jing* leave the game with lowest rank with 90%
Only One player left. Stop the game
Exception caught, stop the game





****** TEST 2:  Multiple automated players
----------------------------------------------------------------------
                       Program Output
----------------------------------------------------------------------

X:\jinglu\winprofile\desktop\lab3\Debug>lab3.exe FiveCardDraw seed* jing* long*
jing* 3C 3H 7D 10C JD
Automated Player: jing* 3C 3H 7D 10C JD  is playing
long* 3D 5C 7C 8C KH
Automated Player: long* 3D 5C 7C 8C KH  is playing
seed* 2D 2H 4H 7H 9D
Automated Player: seed* 2D 2H 4H 7H 9D  is playing
jing* 3C 3H 6D JH QH
long* 6C 8C 9H 10H KH
seed* 2D 2H 4C QC KD
winner: jing*
------------
jing* 1 0

3C 3H 6D JH QH
------------
------------
seed* 0 1

2D 2H 4C QC KD
------------
------------
long* 0 1

6C 8C 9H 10H KH
------------
Automated player jing* does not leave the game with highest rank with 90%
Automated player seed* does not leave the game with other rank with 50%
Automated player long* leave the game with lowest rank with 90%
Anyone wants to leave?
no
Anyone wants to join?
no
seed* 4D 5C 9C QC QH
Automated Player: seed* 4D 5C 9C QC QH  is playing
jing* 3D 3H 4C 5H 6H
Automated Player: jing* 3D 3H 4C 5H 6H  is playing
seed* 3C 7H 8H QC QH
jing* 2D 3D 3H 5D 10D
winner: seed*
------------
seed* 1 1

3C 7H 8H QC QH
------------
------------
jing* 1 1

2D 3D 3H 5D 10D
------------
Automated player seed* leave the game with highest rank with 10%
Only One player left. Stop the game
Exception caught, stop the game






****** TEST 3:  Two automated players + One Human player

----------------------------------------------------------------------
                       Program Output
----------------------------------------------------------------------

X:\jinglu\winprofile\desktop\lab3\Debug>lab3.exe FiveCardDraw seed* jing* human
jing* 2D 3C 4C JC KH
Automated Player: jing* 2D 3C 4C JC KH  is playing
human 4D 5H 8D 9H QD
Please give positions of cards you want to discard
1 3
seed* 2C 6C 8H JH KC
Automated Player: seed* 2C 6C 8H JH KC  is playing
jing* 3D 4H 8C JC KH
human 4D 6D 8D JD QD
seed* 2H 6H JH QC KC
winner: human
------------
human 1 0

4D 6D 8D JD QD
------------
------------
seed* 0 1

2H 6H JH QC KC
------------
------------
jing* 0 1

3D 4H 8C JC KH
------------
Automated player seed* leave the game with other rank with 50%
Anyone wants to leave?
no
Anyone wants to join?
no
jing* 5D 7C 8D 8H JD
Automated Player: jing* 5D 7C 8D 8H JD  is playing
human 8C 9D 10D 10H KD
Please give positions of cards you want to discard
2
jing* 3H 7H 8D 8H 9H
human 2D 8C 9D 10H KD
winner: jing*
------------
jing* 1 1

3H 7H 8D 8H 9H
------------
------------
human 1 1

2D 8C 9D 10H KD
------------
Automated player jing* does not leave the game with highest rank with 90%
Anyone wants to leave?
no
Anyone wants to join?
no
human 5H 7H 8C 8D KH
Please give positions of cards you want to discard
2
jing* 3H 7D 8H 9H 10H
Automated Player: jing* 3H 7D 8H 9H 10H  is playing
human 5H 7H 8D 10D KH
jing* 3D 9C 9H 10C 10H
winner: jing*
------------
jing* 2 1

3D 9C 9H 10C 10H
------------
------------
human 1 2

5H 7H 8D 10D KH
------------
Automated player jing* leave the game with highest rank with 10%
Only One player left. Stop the game
Exception caught, stop the game






****** TEST 4:  Multiple automated players + Multiple Human players

----------------------------------------------------------------------
                       Program Output
----------------------------------------------------------------------


X:\jinglu\winprofile\desktop\lab3\Debug>lab3.exe FiveCardDraw seed* jing* human1
 human2
jing* 3C 6D 7H JD KC
Automated Player: jing* 3C 6D 7H JD KC  is playing
human1 2D 4H 8D JC QC
Please give positions of cards you want to discard
2
human2 5H 8H 9H KD KH
Please give positions of cards you want to discard
1
seed* 3H 5D JH QD QH
Automated Player: seed* 3H 5D JH QD QH  is playing
jing* 3D 9C 9D JD KC
human1 2D 4H 10D JC QC
human2 4D 5H 9H KD KH
seed* 5C 10C 10H QD QH
winner: seed*
------------
seed* 1 0

5C 10C 10H QD QH
------------
------------
human2 0 1

4D 5H 9H KD KH
------------
------------
jing* 0 1

3D 9C 9D JD KC
------------
------------
human1 0 1

2D 4H 10D JC QC
------------
Automated player seed* does not leave the game with highest rank with 90%
Automated player jing* does not leave the game with other rank with 50%
Anyone wants to leave?
no
Anyone wants to join?
no
human1 4C 5D 6D 8D 10H
Please give positions of cards you want to discard
0
human2 2D 6C 9C 10C JC
Please give positions of cards you want to discard
1
seed* 3H 4H 5H 6H 7C
Automated Player: seed* 3H 4H 5H 6H 7C  is playing
jing* 2C 5C 8C 9H JD
Automated Player: jing* 2C 5C 8C 9H JD  is playing
human1 5D 6D 8D 10H QH
human2 2D 9C 10C 10D JC
seed* 3H 4H 5H 6H 7C
jing* 7D 8H 9H JD KC
winner: seed*
------------
seed* 2 0

3H 4H 5H 6H 7C
------------
------------
human2 0 2

2D 9C 10C 10D JC
------------
------------
jing* 0 2

7D 8H 9H JD KC
------------
------------
human1 0 2

5D 6D 8D 10H QH
------------
Automated player seed* does not leave the game with highest rank with 90%
Automated player jing* leave the game with other rank with 50%
Anyone wants to leave?
no
Anyone wants to join?
no
seed* 2H 4H 5D 6H 9D
Automated Player: seed* 2H 4H 5D 6H 9D  is playing
human1 4C 5H 8C QD KH
Please give positions of cards you want to discard
3
human2 2C 5C 7H 10D JH
Please give positions of cards you want to discard
1
seed* 3C 3H 4D 6H 9D
human1 4C 5H 8C 10H KH
human2 2C 3D 7H 10D JH
winner: seed*
------------
seed* 3 0

3C 3H 4D 6H 9D
------------
------------
human1 0 3

4C 5H 8C 10H KH
------------
------------
human2 0 3

2C 3D 7H 10D JH
------------
Automated player seed* does not leave the game with highest rank with 90%
Anyone wants to leave?
no
Anyone wants to join?
no
human1 2C 8D 10C JC KH
Please give positions of cards you want to discard
0 1
human2 8C 10D 10H JH QH
Please give positions of cards you want to discard
2
seed* 3H 4H 5H 6C 7C
Automated Player: seed* 3H 4H 5H 6C 7C  is playing
human1 2D 3D 10C JC KH
human2 4C 8C 10D JH QH
seed* 3H 4H 5H 6C 7C
winner: seed*
------------
seed* 4 0

3H 4H 5H 6C 7C
------------
------------
human1 0 4

2D 3D 10C JC KH
------------
------------
human2 0 4

4C 8C 10D JH QH
------------
Automated player seed* does not leave the game with highest rank with 90%
Anyone wants to leave?
human1
Anyone wants to leave?
no
Anyone wants to join?
no
seed* 3D 6H 7C 9C QH
Automated Player: seed* 3D 6H 7C 9C QH  is playing
human2 2D 5H 6D 9D KH
Please give positions of cards you want to discard
2
seed* 8D 9C 10H QH KD
human2 2D 3C 5H 9D KH
winner: seed*
------------
seed* 5 0

8D 9C 10H QH KD
------------
------------
human2 0 5

2D 3C 5H 9D KH
------------
Automated player seed* does not leave the game with highest rank with 90%
Anyone wants to leave?
no
Anyone wants to join?
no
human2 7C 8D 10C 10H QC
Please give positions of cards you want to discard
0
seed* 3D 4D 5C 5D KD
Automated Player: seed* 3D 4D 5C 5D KD  is playing
human2 2H 8D 10C 10H QC
seed* 2C 5C 5D 7H QH
winner: human2
------------
human2 1 5

2H 8D 10C 10H QC
------------
------------
seed* 5 1

2C 5C 5D 7H QH
------------
Automated player seed* leave the game with lowest rank with 90%
Only One player left. Stop the game
Exception caught, stop the game


