// HandRank.h
//
// author: Jing Lu  jinglu@wustl.edu
//
// purpose: define a struct to represent a hand

#ifndef HAND_H

#define HAND_H

using namespace std;
#include <string>
#include <vector>
#include "Card.h"

struct Hand{
	//enumeration for different hand ranks
	enum Rank{
		no_rank,
		one_pair,
		two_pairs,
		three_kind,
		straight,
		flush,
		full_house,
		four_kind,
		straight_flush
	};

	//define less than operator
	bool operator< (const Hand &) const;

	//member variables
	enum Rank rank;
	vector<Card> cardsInHand;
};

#endif