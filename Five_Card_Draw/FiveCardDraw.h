
#ifndef FiveCardDraw_H
#define FiveCardDraw_H

#include <algorithm>
#include "Game.h"

using namespace std;

//public inheritance from Game base class
class FiveCardDraw: public Game{

protected:
	size_t dealer_position;    //current dealer position, rotating during the game
	Deck discard_deck = Deck();         //deck to store discarded cards
public: 
	FiveCardDraw();            //default constructor

	//player's turn
	virtual int before_turn(Player &player);    
	virtual int turn(Player &player);
	virtual int after_turn(Player &player);

	//game's round
	virtual int before_round();
	virtual int round();
	virtual int after_round();

//helper methods for after_round()
protected:
	void print_sorted_player();
	void reset();
//-------------------------------------------------------------------------------------
//Helper Function for extra credit
vector<int> auto_valid_positions(Player &player);
void highest_automated_leave(string automated_name);
void lowest_automated_leave(string automated_name);
void other_automated_leave(string automated_name);
void terminate();


};







#endif