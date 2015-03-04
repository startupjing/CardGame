// lab2.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Card.h"
#include "Hand.h"
#include "Deck.h"
#include "Error.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;
std::vector<int> getTwoPairsInfo(const std::vector<Card> &);
std::vector<int> getOnePairInfo(const std::vector<Card> &);
bool poker_rank(const Hand &hand1, const Hand &hand2);

static const std::string handRanks[] = { "no_rank", "one_pair", "two_pairs", "three_kind", "straight", "flush", "full_house", "four_kind", "straight_flush" };


int main(int argc, char* argv[]){
    //no command line arguments
	if (argc == 1){
		std::cout << "Error: no argument" << std::endl;
		std::cout << "Correct usage: lab2 <filename> (-shuffle) or lab2 (-shuffle) <filename>" << std::endl;
		return Error::no_arg;
	}
	//only one arguments but it contains shuffle
	else if (argc == 2 && strcmp(argv[1], "-shuffle")==0){
		std::cout << "Error: argument only contains -shuffle" << std::endl;
		std::cout << "Correct usage: lab2 <filename> (-shuffle) or lab2 (-shuffle) <filename>" << std::endl;
		return Error::only_shuffle;
	}
	//two arguments but neither one contains shuffle
	else if (argc == 3 && strcmp(argv[1], "-shuffle") != 0 && strcmp(argv[2], "-shuffle") != 0){
		std::cout << "Error: neither arguments contain -shuffle" << std::endl;
		std::cout << "Correct usage: lab2 <filename> (-shuffle) or lab2 (-shuffle) <filename>" << std::endl;
		return Error::neither_shuffle;
	}
	//more than 2 arguments
	else if (argc > 3){
		std::cout << "Error: too many arguments" << std::endl;
		std::cout << "Correct usage: lab2 <filename> (-shuffle) or lab2 (-shuffle) <filename>" << std::endl;
		return Error::too_many_arg;
	}
	else{
		//determine the index of filename
		char *filename = argv[1];
		if (argc == 3 && strcmp(argv[1], "-shuffle")==0){
			filename = argv[2];
		}

		try{
			Deck deck(filename);

			//not enough cards
			if (deck.size() < 45){
				std::cout << "Error: not enough cards in the deck" << std::endl;
				return Error::not_enough_cards;
			}
			std::cout << "Finish constructing the deck\n" << std::endl;

			//shuffle cards
			if (argc == 3){
				deck.shuffle();
				std::cout << "Deck Shuffled\n" << std::endl;
				
			}

			//construct nine hands
			std::vector<Hand> hands;
			for (int i = 0; i < 9; i++){
				Hand h;
				hands.push_back(h);
			}
			cout << "Finish constructing hands\n" << endl;

			//draw cards into hands
			for (int cardNo = 1; cardNo <= 5; cardNo++){
				for (std::vector<Hand>::size_type handNo = 0; handNo != hands.size(); handNo++){
					hands[handNo] << (hands[handNo], deck);
				}
			}

			//determine ranks for hands
			for (std::vector<Hand>::size_type handNo = 0; handNo != hands.size(); handNo++){
				hands[handNo].setHandRank();
			}


			cout << "Finish drawing cards into hands\n" << endl;

			//print remaining cards in the deck
			std::cout << "Print remaining cards in deck: " << std::endl;
			for (std::vector<Card>::size_type cardNo = 0; cardNo != deck.size(); cardNo++){
				std::cout << deck.getCards()[cardNo].asString() << std::endl;
			}

			//print hands before sorting
			std::cout << "Print hands before sorting: " << std::endl;
			for (std::vector<Hand>::size_type i = 0; i != hands.size(); i++){
				std::cout << hands[i].asString() << std::endl;
			}
		
			//print sorted hands
			std::cout << "Sort hands according to less than operator: " << std::endl;
			sort(hands.begin(), hands.end());
			for (std::vector<Hand>::size_type i = 0; i != hands.size(); i++){
				std::cout << hands[i];
			}

			//print sorted hands by poker rank
			std::cout << "Sort hands according to poker_rank function: " << std::endl;
			sort(hands.begin(), hands.end(), poker_rank);
			for (std::vector<Hand>::size_type i = 0; i != hands.size(); i++){
				std::cout << hands[i].asString() <<  "(" << hands[i].rankAsString() << ")" << std::endl;
			}

			return 0;
		}
		catch (int e){
			std::cout << "Error: failure in loading file" << std::endl;
			return e;
		}

	}

}



//get information if hand rank is two pairs
std::vector<int> getTwoPairsInfo(const std::vector<Card> &cardsInHand){
	//twoPairsInfo[0] = rank of highest pair
	//twoPairsInfo[1] = rank of second highest pair
	//twoPairsInfo[2] = rank of fifth card
	std::vector<int> twoPairsInfo;
	if (cardsInHand[3].rank == cardsInHand[4].rank){
		twoPairsInfo.push_back(cardsInHand[4].rank);
		if (cardsInHand[1].rank == cardsInHand[2].rank){
			twoPairsInfo.push_back(cardsInHand[2].rank);
			twoPairsInfo.push_back(cardsInHand[0].rank);
		}
		else{
			twoPairsInfo.push_back(cardsInHand[0].rank);
			twoPairsInfo.push_back(cardsInHand[2].rank);
		}
	}
	else{
		twoPairsInfo.push_back(cardsInHand[2].rank);
		twoPairsInfo.push_back(cardsInHand[0].rank);
		twoPairsInfo.push_back(cardsInHand[4].rank);
	}
	return twoPairsInfo;
}

//get information if hand rank is one pair
std::vector<int> getOnePairInfo(const std::vector<Card> &cardsInHand){
	//onePairInfo[0] = rank of the pair
	//onePairInfo[1] = highest rank of unpaired card
	//onePairInfo[2] = next highest rank of unpaired card
	//onePairInfo[3] = next highest rank of unpaired card
	std::vector<int> onePairInfo;
	if (cardsInHand[0].rank == cardsInHand[1].rank){
		onePairInfo.push_back(cardsInHand[0].rank);
		onePairInfo.push_back(cardsInHand[4].rank);
		onePairInfo.push_back(cardsInHand[3].rank);
		onePairInfo.push_back(cardsInHand[2].rank);
	}
	else if (cardsInHand[1].rank == cardsInHand[2].rank){
		onePairInfo.push_back(cardsInHand[1].rank);
		onePairInfo.push_back(cardsInHand[4].rank);
		onePairInfo.push_back(cardsInHand[3].rank);
		onePairInfo.push_back(cardsInHand[0].rank);
	}
	else if (cardsInHand[2].rank == cardsInHand[3].rank){
		onePairInfo.push_back(cardsInHand[2].rank);
		onePairInfo.push_back(cardsInHand[4].rank);
		onePairInfo.push_back(cardsInHand[1].rank);
		onePairInfo.push_back(cardsInHand[0].rank);
	}
	else{
		onePairInfo.push_back(cardsInHand[4].rank);
		onePairInfo.push_back(cardsInHand[2].rank);
		onePairInfo.push_back(cardsInHand[1].rank);
		onePairInfo.push_back(cardsInHand[0].rank);
	}
	return onePairInfo;
}




//compare the rank of two hands
bool poker_rank(const Hand &hand2, const Hand &hand1){
	//use hand rank to decide if two hand ranks are different
	if (hand1.getRank() != hand2.getRank()){
		return hand1.getRank() < hand2.getRank();
	}
	else{
		std::vector<Card> cardsInHand = hand1.getCards();
		std::vector<Card> cardsInHand2 = hand2.getCards();
		//get vectors that contain information in the case of two pairs and one pair
		std::vector<int> info1 = getTwoPairsInfo(cardsInHand);
		std::vector<int> info2 = getTwoPairsInfo(cardsInHand2);
		std::vector<int> info3 = getOnePairInfo(cardsInHand);
		std::vector<int> info4 = getOnePairInfo(cardsInHand2);

		switch (hand1.getRank()){
		case Rank::straight_flush:
			//sorted by highest card in each hand
			return cardsInHand[4].operator<(cardsInHand2[4]);

		case Rank::four_kind:
			//sorted by rank of 4 cards that have the same rank
			return cardsInHand[2].rank < cardsInHand2[2].rank;

		case Rank::full_house:
			//sorted by rank of 3 cards that have the same rank
			//then by rank of 2 cards that have the same rank
			if (cardsInHand[2].rank == cardsInHand2[2].rank){
				return 1;
			}
			else{
				return cardsInHand[2].rank < cardsInHand2[2].rank;
			}

		case Rank::flush:
			//sorted by highest ranking card, then by next highest ranking card, etc
			for (std::vector<Card>::size_type i = cardsInHand.size() - 1; i != 0; i--){
				if (cardsInHand[i].rank != cardsInHand2[i].rank){
					return cardsInHand[i].rank < cardsInHand2[i].rank;
				}
			}
			return cardsInHand[0].rank < cardsInHand2[0].rank;

		case Rank::straight:
			//sorted by highest card in each hand
			return cardsInHand[4].operator<(cardsInHand2[4]);

		case Rank::three_kind:
			//sorted by the rank of the 3 cards that have the same rank
			return cardsInHand[2].rank < cardsInHand2[2].rank;

		case Rank::two_pairs:
			//sorted by the rank of higher pair, then by lower pair, then  by 5th card
			if (info1[0] != info2[0]){
				return info1[0] < info2[0];
			}
			else{
				if (info1[1] != info2[1]){
					return info1[1] < info2[1];
				}
				else{
					return info1[2] < info2[2];
				}
			}


		case Rank::one_pair:
			//sorted by the rank of the pair, then by the highest unpaired card
			//then next highest card, etc
			if (info3[0] != info4[0]){
				return info3[0] < info4[0];
			}
			else{
				if (info3[1] != info4[1]){
					return info3[1] < info4[1];
				}
				else{
					if (info3[2] != info4[2]){
						return info3[2] < info4[2];
					}
					else{
						return info3[3] < info4[3];
					}
				}
			}

		case Rank::no_rank:
			//sorted by highest ranking card, then by next highest ranking card
			for (std::vector<Card>::size_type i = cardsInHand.size() - 1; i != 0; i--){
				if (cardsInHand[i].rank != cardsInHand2[i].rank){
					return cardsInHand[i].rank < cardsInHand2[i].rank;
				}
				else{
					if (cardsInHand[i].suit != cardsInHand2[i].suit){
						return cardsInHand[i].suit < cardsInHand2[i].suit;
					}
				}
			}
			return cardsInHand[0].rank < cardsInHand2[0].rank;

		default:
			return false;

		}
	}
}

