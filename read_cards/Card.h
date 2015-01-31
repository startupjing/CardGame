// Card.h
//
// author: Jing Lu  jinglu@wustl.edu
//
// purpose: define a struct to represent a playing card

#ifndef CARD_H

#define CARD_H
#include <string>


struct Card{
	//enumeration for different suits
	enum Suit{
		clubs,
		diamonds,
		hearts,
		spades
	};

	//enumeration for different ranks
	enum Rank{
		ace,
		two,
		three,
		four,
		five,
		six,
		seven,
		eight,
		nine,
		ten,
		jack,
		queen,
		king
	};
    
	//member variables
	enum Suit suit;
	enum Rank rank;
};

#endif