#ifndef PLAYER_H

#define PLAYER_H

#include <string>
#include <fstream>
#include <ostream>
#include <sstream>
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory>

#include "Hand.h"
#include "Error.h"

//number of input file arguments
#define NUM_ARGS_INPUT_FILE 3



struct Player{
	friend class FiveCardDraw;
private:
	std::string player_name;    //player's name
	Hand player_hand;           //a hand for player's cards
	unsigned int hands_won;     //number of winning
	unsigned int hands_lost;    //number of losing
public:
	
	Player(const char *);      //constructor
	std::string get_player_name() const;   //get player's name
	Hand getPlayerHand() const;    //get player's hand

	friend std::ostream& operator<< (std::ostream &, const Player &);    //non-member insertion operator

};


#endif