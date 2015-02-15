========================================================================
                   CSE 332: Lab1
========================================================================

/////////////////////////////////////////////////////////////////////////////
   Lab1 Info
/////////////////////////////////////////////////////////////////////////////
(1) Name: Jing Lu
    Email: jinglu@wustl.edu

(2) Files submitted
        Info.h: defines different error code
	Card.h: defines struct for a playing card
	Hand.h: defines struct for a hand
	lab1.cpp: program that read a hand of cards at one time and print the poker hand rank
	          and in the end, print all cards in sorted order
	README.txt: readme file
	hands.txt: provided test file
	extra.txt: my own test file for extra credit portion

(3) Usage
    Type lab1 <filename>
	Note that if run on Linux, comment out #include "stdax.h"

	To run extra credit, refer to the usage described in the extra credit
	section in README.txt

(4) Complie and Execution
    No errors found


/////////////////////////////////////////////////////////////////////////////
     Modification
/////////////////////////////////////////////////////////////////////////////
Lab0 is reused and modified for Lab1. 
Some modifications are:
(1) define operator< in card struct
(2) modify the parseInput method so that it reads line by line and construct
    hands of valid card
(3) modify printCards method so that it prints all cards in sorted order
(4) create a new method printHandRank that takes vector card and print poker
    hand rank for each hand of cards
(5) modify the main function to fulfill lab requirement
   

/////////////////////////////////////////////////////////////////////////////
     Testing
/////////////////////////////////////////////////////////////////////////////
(1) Using provided hands.txt

H:\My Documents\Visual Studio 2013\Projects\lab1\Debug>lab1 hands.txt
Warning: Not a hand
Warning: Not a hand
------- Poker Hand Ranks: --------
Valid Hand No.0: no rank
Cards in hand:
Three of Clubs
Five of Spades
Six of Spades
Jack of Diamonds
King of Diamonds
Valid Hand No.1: full house
Cards in hand:
Jack of Clubs
Jack of Hearts
Queen of Clubs
Queen of Hearts
Queen of Spades
Valid Hand No.2: straight
Cards in hand:
Six of Clubs
Seven of Hearts
Eight of Spades
Nine of Hearts
Ten of Spades
Valid Hand No.3: three of a kind
Cards in hand:
Jack of Spades
King of Spades
Ace of Clubs
Ace of Diamonds
Ace of Hearts
Valid Hand No.4: straight flush
Cards in hand:
Five of Diamonds
Six of Diamonds
Seven of Diamonds
Eight of Diamonds
Nine of Diamonds
Valid Hand No.5: one pair
Cards in hand:
Two of Clubs
Two of Spades
Five of Hearts
Seven of Spades
Eight of Clubs
Valid Hand No.6: four of a kind
Cards in hand:
Four of Clubs
Four of Diamonds
Four of Hearts
Four of Spades
Ace of Spades
Valid Hand No.7: flush
Cards in hand:
Two of Hearts
Three of Hearts
Eight of Hearts
Ten of Hearts
King of Hearts
Valid Hand No.8: two pairs
Cards in hand:
Nine of Clubs
Nine of Spades
Ten of Clubs
Ten of Diamonds
Queen of Diamonds
------- All Cards -------
Two of Clubs
Two of Hearts
Two of Spades
Three of Clubs
Three of Hearts
Four of Clubs
Four of Diamonds
Four of Hearts
Four of Spades
Five of Diamonds
Five of Hearts
Five of Spades
Six of Clubs
Six of Diamonds
Six of Spades
Seven of Diamonds
Seven of Hearts
Seven of Spades
Eight of Clubs
Eight of Diamonds
Eight of Hearts
Eight of Spades
Nine of Clubs
Nine of Diamonds
Nine of Hearts
Nine of Spades
Ten of Clubs
Ten of Diamonds
Ten of Hearts
Ten of Spades
Jack of Clubs
Jack of Diamonds
Jack of Hearts
Jack of Spades
Queen of Clubs
Queen of Diamonds
Queen of Hearts
Queen of Spades
King of Diamonds
King of Hearts
King of Spades
Ace of Clubs
Ace of Diamonds
Ace of Hearts
Ace of Spades


(2) Own Test File

-- Empty file

H:\My Documents\Visual Studio 2013\Projects\lab1\Debug>lab1 hands.txt
Warning: Empty card deck
Error when printing poker hand rank

-- Test file

please skip this line // not a hand (invalid definition strings)

6H // not a hand (too few)

9D  6D 5D 8p 7D // not a hand (suit of one string is not valid)

9D  6D 5D 11D 7D // not a hand (rank of one string is not valid)

Kc 3s 3D 2D 7c 5c  // not a hand (too many)


H:\My Documents\Visual Studio 2013\Projects\lab1\Debug>lab1 hands.txt
Warning: Invalid length of card definition string
Warning: Invalid length of card definition string
Warning: Invalid length of card definition string
Warning: Invalid length of card definition string
Warning: Not a hand
Warning: Not a hand
Warning: Invalid suit information in card definition string
Warning: Not a hand
Warning: Invalid rank information in card definition string
Warning: Not a hand
Warning: Not a hand
Warning: Empty card deck
Error when printing poker hand rank


/////////////////////////////////////////////////////////////////////////////
    Error Code
/////////////////////////////////////////////////////////////////////////////
(1) defined error codes
code 0: successful execution
code 1: fail to satisfy argument requirements
code 2: fail to open file
code 3: no valid cards

(2) test error codes(omit program output in the following cases)

H:\My Documents\Visual Studio 2013\Projects\lab1\Debug>lab1 hands.txt
....
H:\My Documents\Visual Studio 2013\Projects\lab1\Debug>echo %errorlevel%
0

H:\My Documents\Visual Studio 2013\Projects\lab1\Debug>lab1
....
H:\My Documents\Visual Studio 2013\Projects\lab1\Debug>echo %errorlevel%
1

H:\My Documents\Visual Studio 2013\Projects\lab1\Debug>lab1 file_not_exist.txt
....
H:\My Documents\Visual Studio 2013\Projects\lab1\Debug>echo %errorlevel%
2

H:\My Documents\Visual Studio 2013\Projects\lab1\Debug>lab1 empty.txt
....
H:\My Documents\Visual Studio 2013\Projects\lab1\Debug>echo %errorlevel%
3



/////////////////////////////////////////////////////////////////////////////
    Extra credit
/////////////////////////////////////////////////////////////////////////////
(1) Note
    To run extra credit portion, comment the line status = printHandRank(cards)
	and comment out status = extraCredit(cards);
	Then rebuild the solution and run the command "lab1 hands.txt" or "lab1 extra.txt" 

(2) Implementation:
 -- I create a new header file called Hand.h that represents a hand struct that has rank and a vector of five cards in hand
 -- In lab1.cpp, I write some new methods
    -- create a new operator< for hand that compares two hands according to the rules in lab instruction
	-- create two helper functions to get information when two hands are both two pairs or one pair
	-- create a method that specifically deal with extra credit portion

(3) Testing
****** Using the provided hands.txt
   
H:\My Documents\Visual Studio 2013\Projects\lab1\Debug>lab1 hands.txt
Warning: Not a hand
Warning: Not a hand
------- Extra credit: --------
Valid Hand No.0 : straight flush
Cards in hand:
Five of Diamonds
Six of Diamonds
Seven of Diamonds
Eight of Diamonds
Nine of Diamonds
Valid Hand No.1 : four of a kind
Cards in hand:
Four of Clubs
Four of Diamonds
Four of Hearts
Four of Spades
Ace of Spades
Valid Hand No.2 : full house
Cards in hand:
Jack of Clubs
Jack of Hearts
Queen of Clubs
Queen of Hearts
Queen of Spades
Valid Hand No.3 : flush
Cards in hand:
Two of Hearts
Three of Hearts
Eight of Hearts
Ten of Hearts
King of Hearts
Valid Hand No.4 : straight
Cards in hand:
Six of Clubs
Seven of Hearts
Eight of Spades
Nine of Hearts
Ten of Spades
Valid Hand No.5 : three of a kind
Cards in hand:
Jack of Spades
King of Spades
Ace of Clubs
Ace of Diamonds
Ace of Hearts
Valid Hand No.6 : two pairs
Cards in hand:
Nine of Clubs
Nine of Spades
Ten of Clubs
Ten of Diamonds
Queen of Diamonds
Valid Hand No.7 : one pair
Cards in hand:
Two of Clubs
Two of Spades
Five of Hearts
Seven of Spades
Eight of Clubs
Valid Hand No.8 : no rank
Cards in hand:
Three of Clubs
Five of Spades
Six of Spades
Jack of Diamonds
King of Diamonds
------- All Cards -------
Two of Clubs
Two of Hearts
Two of Spades
Three of Clubs
Three of Hearts
Four of Clubs
Four of Diamonds
Four of Hearts
Four of Spades
Five of Diamonds
Five of Hearts
Five of Spades
Six of Clubs
Six of Diamonds
Six of Spades
Seven of Diamonds
Seven of Hearts
Seven of Spades
Eight of Clubs
Eight of Diamonds
Eight of Hearts
Eight of Spades
Nine of Clubs
Nine of Diamonds
Nine of Hearts
Nine of Spades
Ten of Clubs
Ten of Diamonds
Ten of Hearts
Ten of Spades
Jack of Clubs
Jack of Diamonds
Jack of Hearts
Jack of Spades
Queen of Clubs
Queen of Diamonds
Queen of Hearts
Queen of Spades
King of Diamonds
King of Hearts
King of Spades
Ace of Clubs
Ace of Diamonds
Ace of Hearts
Ace of Spades


****** Using own test file (named extra.txt)

9D  6D 5D 8D 7D // straight flush 

KD  JD qD aD 10D // straight flush (rank higher)


4s 4H  4D As 4c  // four of a kind

Js JH  7D JD jc  // four of a kind (rank higher)


Qs QH	 JH Qc Jc // full house  (rank higher)

5s 5H	 8s 8d 8c // full house


KH   10H 3H 2H 8H // flush  (rank higher)

8s   4s 3s 6s 8s // flush


6c 10c 9H  8s  7H // straight

6c 10s 9H  8s  7H // straight  (rank higher)


AH Ks Js AD Ac // three of a kind  (rank higher)

5H Ks Js 5D 5c // three of a kind


9c QD 10c 10D 9s // two pairs  (rank higher)

5c QD 10c 10D 5s // two pairs


7s 8c 2s 5H 2c // one pair

7s 10c 2s 5H 2c // one pair  (rank higher)


KD JD 6s 5s 3c // no rank (rank higher)

10D JD 6s 5s 3c // no rank


H:\My Documents\Visual Studio 2013\Projects\lab1\Debug>lab1 extra.txt
------- Extra credit: --------
Valid Hand No.0 : straight flush
Cards in hand:
Ten of Diamonds
Jack of Diamonds
Queen of Diamonds
King of Diamonds
Ace of Diamonds
Valid Hand No.1 : straight flush
Cards in hand:
Five of Diamonds
Six of Diamonds
Seven of Diamonds
Eight of Diamonds
Nine of Diamonds
Valid Hand No.2 : four of a kind
Cards in hand:
Seven of Diamonds
Jack of Clubs
Jack of Diamonds
Jack of Hearts
Jack of Spades
Valid Hand No.3 : four of a kind
Cards in hand:
Four of Clubs
Four of Diamonds
Four of Hearts
Four of Spades
Ace of Spades
Valid Hand No.4 : full house
Cards in hand:
Jack of Clubs
Jack of Hearts
Queen of Clubs
Queen of Hearts
Queen of Spades
Valid Hand No.5 : full house
Cards in hand:
Five of Hearts
Five of Spades
Eight of Clubs
Eight of Diamonds
Eight of Spades
Valid Hand No.6 : flush
Cards in hand:
Two of Hearts
Three of Hearts
Eight of Hearts
Ten of Hearts
King of Hearts
Valid Hand No.7 : flush
Cards in hand:
Three of Spades
Four of Spades
Six of Spades
Eight of Spades
Eight of Spades
Valid Hand No.8 : straight
Cards in hand:
Six of Clubs
Seven of Hearts
Eight of Spades
Nine of Hearts
Ten of Spades
Valid Hand No.9 : straight
Cards in hand:
Six of Clubs
Seven of Hearts
Eight of Spades
Nine of Hearts
Ten of Clubs
Valid Hand No.10 : three of a kind
Cards in hand:
Jack of Spades
King of Spades
Ace of Clubs
Ace of Diamonds
Ace of Hearts
Valid Hand No.11 : three of a kind
Cards in hand:
Five of Clubs
Five of Diamonds
Five of Hearts
Jack of Spades
King of Spades
Valid Hand No.12 : two pairs
Cards in hand:
Nine of Clubs
Nine of Spades
Ten of Clubs
Ten of Diamonds
Queen of Diamonds
Valid Hand No.13 : two pairs
Cards in hand:
Five of Clubs
Five of Spades
Ten of Clubs
Ten of Diamonds
Queen of Diamonds
Valid Hand No.14 : one pair
Cards in hand:
Two of Clubs
Two of Spades
Five of Hearts
Seven of Spades
Ten of Clubs
Valid Hand No.15 : one pair
Cards in hand:
Two of Clubs
Two of Spades
Five of Hearts
Seven of Spades
Eight of Clubs
Valid Hand No.16 : no rank
Cards in hand:
Three of Clubs
Five of Spades
Six of Spades
Jack of Diamonds
King of Diamonds
Valid Hand No.17 : no rank
Cards in hand:
Three of Clubs
Five of Spades
Six of Spades
Ten of Diamonds
Jack of Diamonds
------- All Cards -------
Two of Clubs
Two of Clubs
Two of Hearts
Two of Spades
Two of Spades
Three of Clubs
Three of Clubs
Three of Hearts
Three of Spades
Four of Clubs
Four of Diamonds
Four of Hearts
Four of Spades
Four of Spades
Five of Clubs
Five of Clubs
Five of Diamonds
Five of Diamonds
Five of Hearts
Five of Hearts
Five of Hearts
Five of Hearts
Five of Spades
Five of Spades
Five of Spades
Five of Spades
Six of Clubs
Six of Clubs
Six of Diamonds
Six of Spades
Six of Spades
Six of Spades
Seven of Diamonds
Seven of Diamonds
Seven of Hearts
Seven of Hearts
Seven of Spades
Seven of Spades
Eight of Clubs
Eight of Clubs
Eight of Diamonds
Eight of Diamonds
Eight of Hearts
Eight of Spades
Eight of Spades
Eight of Spades
Eight of Spades
Eight of Spades
Nine of Clubs
Nine of Diamonds
Nine of Hearts
Nine of Hearts
Nine of Spades
Ten of Clubs
Ten of Clubs
Ten of Clubs
Ten of Clubs
Ten of Diamonds
Ten of Diamonds
Ten of Diamonds
Ten of Diamonds
Ten of Hearts
Ten of Spades
Jack of Clubs
Jack of Clubs
Jack of Diamonds
Jack of Diamonds
Jack of Diamonds
Jack of Diamonds
Jack of Hearts
Jack of Hearts
Jack of Spades
Jack of Spades
Jack of Spades
Queen of Clubs
Queen of Diamonds
Queen of Diamonds
Queen of Diamonds
Queen of Hearts
Queen of Spades
King of Diamonds
King of Diamonds
King of Hearts
King of Spades
King of Spades
Ace of Clubs
Ace of Diamonds
Ace of Diamonds
Ace of Hearts
Ace of Spades