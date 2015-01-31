========================================================================
    CSE332 : lab0 
========================================================================

===================================
    Lab 0 Info
===================================
(1) Student 
Name: Jing Lu
Email: jinglu@wustl.edu

(2) Files submitted 
Info.h: defines different error code
Card.h: defines struct for a playing card
lab0.cpp: programs that parse card definition strings, construct cards and print cards
README.txt: readme file

(3) Usage:
Type lab0 <filename>
Note that if run on Linux, comment out #include "stdafx.h"

(4) Compile and execute
No known warnings or errors generated

===================================
    Testing
===================================
(1) Using provided card_file.txt: 

H:\My Documents\Visual Studio 2013\Projects\lab0\Debug>lab0 card_file.
------- Cards information: --------
Two of Clubs
Three of Clubs
Four of Clubs
Five of Clubs
Six of Clubs
Seven of Clubs
Eight of Clubs
Nine of Clubs
Ten of Clubs
Jack of Clubs
Queen of Clubs
King of Clubs
Ace of Clubs
Ace of Diamonds
King of Diamonds
Queen of Diamonds
Jack of Diamonds
Ten of Diamonds
Nine of Diamonds
Eight of Diamonds
Seven of Diamonds
Six of Diamonds
Five of Diamonds
Four of Diamonds
Three of Diamonds
Two of Diamonds
Two of Hearts
Three of Hearts
Four of Hearts
Five of Hearts
Six of Hearts
Seven of Hearts
Eight of Hearts
Nine of Hearts
Ten of Hearts
Jack of Hearts
Queen of Hearts
King of Hearts
Ace of Hearts
Ace of Spades
King of Spades
Queen of Spades
Jack of Spades
Ten of Spades
Nine of Spades
Eight of Spades
Seven of Spades
Six of Spades
Five of Spades
Four of Spades
Three of Spades
Two of Spades

(2) Using own test file:

H:\My Documents\Visual Studio 2013\Projects\lab0\Debug>cat test.txt
//test invalid string length

i am a long string
please do not include me

//test invalid suit information
Ai 2w 3~ 4:          5M     6*   8q   9b
10f   jzz    q12  k3

//test invalid rank information
1D    0s     11c    12H    13d
29D      34C

//test special rank case(still invalid)
01C   02d   09S

//test invalid suit and rank information
01f  00m  0a   29G    11e  13R


//test valid string
Ac 2c 3c 4c 5C 6C     7C 8C    9C 10c       Jc  qc  kc
ah 2h 3h 4h 5h 6h     7H 8H    9H 10H       Jh  qh  kH
ad 2d 3d 4d 5d 6d     7D 8D    9D 10D       Jd  qd  kD
As 2s 3s 4s 5s 6s     7S 8S    9S 10S       Js  qs  kS


H:\My Documents\Visual Studio 2013\Projects\lab0\Debug>lab0 test.txt
------- Cards information: --------
Ace of Clubs
Two of Clubs
Three of Clubs
Four of Clubs
Five of Clubs
Six of Clubs
Seven of Clubs
Eight of Clubs
Nine of Clubs
Ten of Clubs
Jack of Clubs
Queen of Clubs
King of Clubs
Ace of Hearts
Two of Hearts
Three of Hearts
Four of Hearts
Five of Hearts
Six of Hearts
Seven of Hearts
Eight of Hearts
Nine of Hearts
Ten of Hearts
Jack of Hearts
Queen of Hearts
King of Hearts
Ace of Diamonds
Two of Diamonds
Three of Diamonds
Four of Diamonds
Five of Diamonds
Six of Diamonds
Seven of Diamonds
Eight of Diamonds
Nine of Diamonds
Ten of Diamonds
Jack of Diamonds
Queen of Diamonds
King of Diamonds
Ace of Spades
Two of Spades
Three of Spades
Four of Spades
Five of Spades
Six of Spades
Seven of Spades
Eight of Spades
Nine of Spades
Ten of Spades
Jack of Spades
Queen of Spades
King of Spades


===================================
    Error Code
===================================
(1) defined error codes
code 0: successful execution
code 1: fail to satisfy argument requirements
code 2: fail to open file
code 3: no valid cards

(2) test error codes(omit program output in the following cases)

H:\My Documents\Visual Studio 2013\Projects\lab0\Debug>lab0 card_file.txt
....
H:\My Documents\Visual Studio 2013\Projects\lab0\Debug>echo %errorlevel%
0

H:\My Documents\Visual Studio 2013\Projects\lab0\Debug>lab0 
....
H:\My Documents\Visual Studio 2013\Projects\lab0\Debug>echo %errorlevel%
1

H:\My Documents\Visual Studio 2013\Projects\lab0\Debug>lab0 file_not_exist.txt
....
H:\My Documents\Visual Studio 2013\Projects\lab0\Debug>echo %errorlevel%
2

H:\My Documents\Visual Studio 2013\Projects\lab0\Debug>lab0 empty.txt
....
H:\My Documents\Visual Studio 2013\Projects\lab0\Debug>echo %errorlevel%
3


===================================
    Extra Credit
===================================
(1) Login shell
Note that I use shell on my Mac, here is the command:

Last login: Mon Jan 26 19:20:08 on ttys000
Jings-MacBook-Pro:~ jinglu$ ssh shell.cec.wustl.edu
This system is now WUSTL Key enabled.
jinglu@shell.cec.wustl.edu's password: 
Last login: Mon Jan 26 19:20:23 2015 from pat-vl2101-wustl-guest.nts.wustl.edu
[jinglu@shell ~]$ pwd
/home/warehouse/jinglu
[jinglu@shell ~]$ ls
artifacts.xml  Desktop                math449       Public       winprofile
cse332         Documents              Music         public_html
cse361         Downloads              My Documents  Templates
cse417         eclipse.configuration  p2            Videos
cse473         exp                    Pictures      WINDOWS


(2) Fix warnings and errors
(2-A) lab0.cpp:32:68: error: ‘strcmp’ was not declared in this scope
     if (argc != minimum_arguments || strcmp(argv[file_index], "--help") == 0){

Solution: include <cstring>

(2-B)lab0.cpp:191:45: error: ‘const class std::vector<Card>’ has no member named ‘cend’
  for (auto it = cards.cbegin(); it != cards.cend(); ++it){

Solution: use indices to traverse the vector instead of using iterator

(2-C) lab0.cpp:79:6: warning: unused variable ‘rank’ [-Wunused-variable]
  int rank = 0;

Solution: remove the line


(3) Output
[jinglu@shell lab0]$ ./lab0 card_file.txt
------- Cards information: --------
Two of Clubs
Three of Clubs
Four of Clubs
Five of Clubs
Six of Clubs
Seven of Clubs
Eight of Clubs
Nine of Clubs
Ten of Clubs
Jack of Clubs
Queen of Clubs
King of Clubs
Ace of Clubs
Ace of Diamonds
King of Diamonds
Queen of Diamonds
Jack of Diamonds
Ten of Diamonds
Nine of Diamonds
Eight of Diamonds
Seven of Diamonds
Six of Diamonds
Five of Diamonds
Four of Diamonds
Three of Diamonds
Two of Diamonds
Two of Hearts
Three of Hearts
Four of Hearts
Five of Hearts
Six of Hearts
Seven of Hearts
Eight of Hearts
Nine of Hearts
Ten of Hearts
Jack of Hearts
Queen of Hearts
King of Hearts
Ace of Hearts
Ace of Spades
King of Spades
Queen of Spades