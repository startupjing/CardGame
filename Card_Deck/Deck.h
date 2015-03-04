#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"


class Deck{
	friend class Hand;
	friend std::ostream& operator<< (std::ostream &, const Deck &);    //to print cards in the deck
private:
	std::vector<Card> cards;
public:
	Deck(char *);    //construct that loads cards using given file
	virtual ~Deck();    //deconstructor
	int size() const;   //deck size
	std::vector<Card> getCards() const;   //get cards in the stack
	void load(char *);     //load cards from file to deck
	void shuffle();       //shuffle cards
	Card remove();        //remove card from back of deck
};


#endif