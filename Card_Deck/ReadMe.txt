========================================================================
                   CSE 332: Lab1
========================================================================

/////////////////////////////////////////////////////////////////////////////
   Lab2 Info
/////////////////////////////////////////////////////////////////////////////
(1) Name: Jing Lu
    Email: jinglu@wustl.edu

(2) Files submitted
    Card.h and Card.cpp: card class header and implementation
	Hand.h and Hand.cpp: hand class header and implementation
	Deck.h and Deck.cpp: deck class header and implementation
	Error.h: define different error level
	lab2.cpp: main function

(3) Usage
    Type lab2 <filename> or lab2 <filename> -shuffle or lab2 -shuffle <filename>
	Note that if run on Linux, comment out #include "stdax.h"

(4) Complie and Execution
    No errors found


/////////////////////////////////////////////////////////////////////////////
     Modification
/////////////////////////////////////////////////////////////////////////////
Lab1 is reused and modified for Lab1. 
Some notes:
(1) Use original card class from previous lab
(2) Modify previous hand class in lab1 by rules in the lab instruction
(3) Create new class for deck according to lab instruction
(4) Create Error.h to define error level
   

/////////////////////////////////////////////////////////////////////////////
     Testing
/////////////////////////////////////////////////////////////////////////////
(1) Test 45 cards without shuffling
2C 3C 4C 5C 6C
7C 8C 9C 10C JC 
QC KC AC aD kD 
qD jD 10D 9D 8D 
7D 6D 5D 4D 3D 
2D 2h 3h 4h 5h 
6h 7h 8h 9h 10h 
Jh Qh Kh Ah as 
ks qs js 10s 9s


---------
H:\My Documents\Visual Studio 2013\Projects\lab2\Debug>lab2 card_file.txt
Finish constructing the deck

Finish constructing hands

Finish drawing cards into hands

Print remaining cards in deck:
Print hands before sorting:
2H 9S 10C 10D JH
2D 9C 10H 10S JD
3D 8C 9H JS QD
4D 7C 8H QS KD
5D 6C 7H KS AD
5C 6D 6H AC AS
4C 5H 7D KC AH
3C 4H 8D QC KH
2C 3H 9D JC QH
Sort hands according to less than operator:
2C 3H 9D JC QH
2D 9C 10H 10S JD
2H 9S 10C 10D JH
3C 4H 8D QC KH
3D 8C 9H JS QD
4C 5H 7D KC AH
4D 7C 8H QS KD
5C 6D 6H AC AS
5D 6C 7H KS AD
Sort hands according to poker_rank function:
5C 6D 6H AC AS (two_pairs)
2D 9C 10H 10S JD (one_pair)
2H 9S 10C 10D JH (one_pair)
4C 5H 7D KC AH (no_rank)
5D 6C 7H KS AD (no_rank)
3C 4H 8D QC KH (no_rank)
4D 7C 8H QS KD (no_rank)
2C 3H 9D JC QH (no_rank)
3D 8C 9H JS QD (no_rank)



(2) Test more than 45 cards without shuffling
2C 3C 4C 5C 6C
7C 8C 9C 10C JC 
QC KC AC aD kD 
qD jD 10D 9D 8D 
7D 6D 5D 4D 3D 
2D 2h 3h 4h 5h 
6h 7h 8h 9h 10h 
Jh Qh Kh Ah as 
ks qs js 10s 9s
qD jD 10D 9D 8D 
7D 6D 5D 4D 3D 
2D 2h 3h 4h 5h 


-----------
H:\My Documents\Visual Studio 2013\Projects\lab2\Debug>lab2 card_file.txt
Finish constructing the deck

Finish constructing hands

Finish drawing cards into hands

Print remaining cards in deck:
2C
3C
4C
5C
6C
7C
8C
9C
10C
JC
QC
KC
AC
AD
KD
Print hands before sorting:
4D 5H 7D 8H QS
4H 5D 7H 8D KS
3H 6D 6H 9D AS
2H 5H 7D 10D AH
2D 4H 8D JD KH
3D 3H 9D QD QH
2H 4D 9S 10D JH
2D 5D 10H 10S JD
3D 6D 9H JS QD
Sort hands according to less than operator:
2D 4H 8D JD KH
2D 5D 10H 10S JD
2H 4D 9S 10D JH
2H 5H 7D 10D AH
3D 3H 9D QD QH
3D 6D 9H JS QD
3H 6D 6H 9D AS
4D 5H 7D 8H QS
4H 5D 7H 8D KS
Sort hands according to poker_rank function:
3D 3H 9D QD QH (two_pairs)
2D 5D 10H 10S JD (one_pair)
3H 6D 6H 9D AS (one_pair)
2H 5H 7D 10D AH (no_rank)
4H 5D 7H 8D KS (no_rank)
2D 4H 8D JD KH (no_rank)
4D 5H 7D 8H QS (no_rank)
3D 6D 9H JS QD (no_rank)
2H 4D 9S 10D JH (no_rank)


(3) Test 45 cards with shuffling
2C 3C 4C 5C 6C
7C 8C 9C 10C JC 
QC KC AC aD kD 
qD jD 10D 9D 8D 
7D 6D 5D 4D 3D 
2D 2h 3h 4h 5h 
6h 7h 8h 9h 10h 
Jh Qh Kh Ah as 
ks qs js 10s 9s

------
H:\My Documents\Visual Studio 2013\Projects\lab2\Debug>lab2 card_file.txt -shuff
le
Finish constructing the deck

Deck Shuffled

Finish constructing hands

Finish drawing cards into hands

Print remaining cards in deck:
Print hands before sorting:
3C 5D QC QS AD
2H 4C JS QH KH
2D 5H 6D KD AH
3D 7D 10H JC AC
4H 7C 8D 9D 10S
3H 4D 8C 10C JH
2C 6H 9S JD KS
5C 7H 8H 10D QD
6C 9C 9H KC AS
Sort hands according to less than operator:
2C 6H 9S JD KS
2D 5H 6D KD AH
2H 4C JS QH KH
3C 5D QC QS AD
3D 7D 10H JC AC
3H 4D 8C 10C JH
4H 7C 8D 9D 10S
5C 7H 8H 10D QD
6C 9C 9H KC AS
Sort hands according to poker_rank function:
3C 5D QC QS AD (one_pair)
6C 9C 9H KC AS (one_pair)
2D 5H 6D KD AH (no_rank)
3D 7D 10H JC AC (no_rank)
2C 6H 9S JD KS (no_rank)
2H 4C JS QH KH (no_rank)
5C 7H 8H 10D QD (no_rank)
3H 4D 8C 10C JH (no_rank)
4H 7C 8D 9D 10S (no_rank)

-----

H:\My Documents\Visual Studio 2013\Projects\lab2\Debug>lab2 card_file.txt -shuff
le
Finish constructing the deck

Deck Shuffled

Finish constructing hands

Finish drawing cards into hands

Print remaining cards in deck:
Print hands before sorting:
3D 8H 10S JD JH
10C JS QD QS KH
6C 9S 10H QC AH
4D 4H 5C 5D QH
2D 8D KS AD AS
2C 6H 7C 7H 9D
4C 6D 9H JC KC
3H 8C 9C KD AC
2H 3C 5H 7D 10D
Sort hands according to less than operator:
2C 6H 7C 7H 9D
2D 8D KS AD AS
2H 3C 5H 7D 10D
3D 8H 10S JD JH
3H 8C 9C KD AC
4C 6D 9H JC KC
4D 4H 5C 5D QH
6C 9S 10H QC AH
10C JS QD QS KH
Sort hands according to poker_rank function:
4D 4H 5C 5D QH (two_pairs)
2D 8D KS AD AS (one_pair)
10C JS QD QS KH (one_pair)
3D 8H 10S JD JH (one_pair)
2C 6H 7C 7H 9D (one_pair)
6C 9S 10H QC AH (no_rank)
3H 8C 9C KD AC (no_rank)
4C 6D 9H JC KC (no_rank)
2H 3C 5H 7D 10D (no_rank)


(4) Test erro level
H:\My Documents\Visual Studio 2013\Projects\lab2\Debug>lab2
Error: no argument
Correct usage: lab2 <filename> (-shuffle) or lab2 (-shuffle) <filename>

H:\My Documents\Visual Studio 2013\Projects\lab2\Debug>echo %errorlevel%
3

H:\My Documents\Visual Studio 2013\Projects\lab2\Debug>lab2 -shuffle
Error: argument only contains -shuffle
Correct usage: lab2 <filename> (-shuffle) or lab2 (-shuffle) <filename>

H:\My Documents\Visual Studio 2013\Projects\lab2\Debug>echo %errorlevel%
1

H:\My Documents\Visual Studio 2013\Projects\lab2\Debug>lab2 test haha
Error: neither arguments contain -shuffle
Correct usage: lab2 <filename> (-shuffle) or lab2 (-shuffle) <filename>

H:\My Documents\Visual Studio 2013\Projects\lab2\Debug>echo %errorlevel%
2

H:\My Documents\Visual Studio 2013\Projects\lab2\Debug>lab2 one two three
Error: too many arguments
Correct usage: lab2 <filename> (-shuffle) or lab2 (-shuffle) <filename>

H:\My Documents\Visual Studio 2013\Projects\lab2\Debug>echo %errorlevel%
4


/////////////////////////////////////////////////////////////////////////////
     Extra Credit
/////////////////////////////////////////////////////////////////////////////
(1)A8 and A9
A8 is applied. When the constructor of Deck class uses load() method with the given filename,
if the given file cannot be opened, load() will throw an exception and constructor will catch it.
Then construct throws an exception and it propates up to the main function where the constructor is used.
Then the main function will return an appropriate non-zero code to indicate the program failure.

A9 is applied. In my program, no exception is used to control program execution under normal condition.
It is used under abnormal conditions.

(2)A12-A15
A12 is applied. Deference 'this' is used but it is not zero, so there will be no access violation.

A13 and A14 are applied. Array index is within the bound and is checked before using it to access the array.

A15 is applied. I use vector but with no fixed size because number of elements to insert can vary.

(3)A16
When debugging, I try to check the program part by part until a part is not working correctly. Then I check
the related function calls and print useful information to monitor the state of the program. In this process,
I will design specific cases to test the output and compare it with expected results.


(4)B10-B12

B10 is applied. They are in the same order.
B11 is applied. No initialization in constructor body in my program.
B12 is applied. The constructor of Deck will catch exception from load() function.


(5)B18
B18 is applied. We allow assignment opearator in Hand class and therefore it is not declared as private.

(6)B31 first part
B31 is applied. I use inclusion guard in all  header files.