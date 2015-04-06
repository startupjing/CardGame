#include "stdafx.h"
#include "Card.h"

static const std::string suits[] = { "C", "D", "H", "S" };
static const std::string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

bool Card::operator< (const Card &card) const{
	//first compare rank and then suit
	return (rank < card.rank) || ((rank == card.rank) && (suit < card.suit));
}

bool Card::operator== (const Card &card) const{
	return rank == card.rank && suit == card.suit;
}


std::string Card::asString() const{
	std::string cardStr = ranks[rank] + suits[suit];
	return cardStr;
}