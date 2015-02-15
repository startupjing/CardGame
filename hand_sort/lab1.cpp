// lab1.cpp 
//
//author: Jing Lu jinglu@wustl.edu
//
//Purpose: Read five card definition strings at a time and print its poker hand rank
//         In the end, print all cards in sorted order(sorted by rank and then by suit)
//

#include "stdafx.h"
#include "Card.h"
#include "Hand.h"
#include "Info.h"
#include <string>  
#include <vector>
#include <iostream>  
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>

using namespace std;
int parseInput(vector<Card> &, char *);
int message(char *, char *);
int printCards(const vector<Card> &);
int printHandRank(const vector<Card> &);
bool is_number(const std::string &);

vector<int> getTwoPairsInfo(const vector<Card> &);
vector<int> getOnePairInfo(const vector<Card> &);
int extraCredit(const vector<Card> &);


int main(int argc, char* argv[]){
	//useful constants for argument positions
	const int minimum_arguments = 2;
	const int file_index = 1;
	const int program_name_index = 0;

	//check usage of arguments, print useful message if invalid arguments
	if (argc != minimum_arguments || strcmp(argv[file_index], "--help") == 0){
		char *usage = "<filename>";
		return message(argv[program_name_index], usage);
	}
	else{
		vector<Card> cards;
		vector<Card> buffer;

		//record success or failure of method execution
		int status;
		//parse input file and store cards into vector
		status = parseInput(cards, argv[file_index]);
		//error in parsing
		if (status != success){
			return status;
		}
		//successful parsing
		else{

			//print poker hand rank
			status = printHandRank(cards);

			//if want to run extra credit portion, 
			//comment the line "status = printHandRank(cards);"
			//and comment out the line "status = extraCredit(cards);"

			//status = extraCredit(cards);

			//print message if error in print poker hand rank
			if (status != success){
				cout << "Error when printing poker hand rank" << endl;
				return status;
			}

			//print each card in sorted order
			sort(cards.begin(), cards.end());
			cout << "------- All Cards -------" << endl;
			status = printCards(cards);
			//print message if error in print cards
			if (status != success){
				cout << "Error when printing sorted cards" << endl;
				return status;
			}
		}
		return success;
	}

}

// print out useful message
int message(char *program_name, char *usage){
	cout << "Usage: " << program_name << " " << usage
		<< endl
		<< "Purpose: Read five card definition strings at a time and print its poker hand rank. " 
		<< "In the end, print all cards in sorted order(sorted by rank and then by suit)"
		<< endl;
	return arg_fail;
}

// parsecard definition strings(skip if invalid) and construct cards into vector
int parseInput(vector<Card> &cards, char *filename){
	//card definition string
	string cardDef;
	//suit and rank information of current card
	char cardSuit;
	string cardRank;
	//current card
	Card currCard;

	//construct ifstream and open the given file
	ifstream ifs(filename);

	//successfully open file
	if (ifs.is_open()){
		string line, cardDef;

		//use a buffer to store card definition strings on a line
		vector<Card> buffer;

		//read by lines
		while (getline(ifs, line)){
			//skip empty lines
			if (line.length() == 0){
				continue;
			}
			//skip words after comment symbol
			else if (line.find_first_of("//") != string::npos){
				line = line.substr(0, line.find_first_of("//"));
			}

			istringstream record(line);

			//read word by word
			while (record >> cardDef){
				//card definition string should be length of 2 or 3
				if (cardDef.size() == 2 || cardDef.size() == 3){
					//retrieve suit and rank of current card
					cardSuit = cardDef[cardDef.size() - 1];
					cardRank = cardDef.substr(0, cardDef.size() - 1);

					//assign suit to card if valid
					switch (cardSuit){
					case 'c':
					case 'C':
						currCard.suit = Card::clubs;
						break;
					case 'd':
					case 'D':
						currCard.suit = Card::diamonds;
						break;
					case 'h':
					case 'H':
						currCard.suit = Card::hearts;
						break;
					case 's':
					case 'S':
						currCard.suit = Card::spades;
						break;
						//invalid suit information, process next string
					default:
						cout << "Warning: Invalid suit information in card definition string" << endl;
						continue;
					}

					//assign rank to card if valid
					//case when rank info is numerical value
					if (is_number(cardRank)){
						//conver to numerical value
						istringstream argsin(cardRank);
						int idx;
						argsin >> idx;
						//consider 02c, 03S, 09d as invalid string
						if (idx >= 2 && idx <= 9 && cardRank.size() == 2){
							cout << "Warning: Invalid string format(02c, 03S, 09d, etc)" << endl;
							continue;
						}
						//check range
						if (idx >= 2 && idx <= 10){
							currCard.rank = Card::Rank(idx - 2);
						}
						//invalid rank information, process next string
						else{
							cout << "Warning: Invalid rank information in card definition string" << endl;
							continue;
						}
					}
					//case when rank info is not numerical value
					else{
						//jack
						if (cardRank.compare("J") == 0 || cardRank.compare("j") == 0){
							currCard.rank = Card::jack;
						}
						//queen
						else if (cardRank.compare("Q") == 0 || cardRank.compare("q") == 0){
							currCard.rank = Card::queen;
						}
						//king
						else if (cardRank.compare("K") == 0 || cardRank.compare("k") == 0){
							currCard.rank = Card::king;
						}
						//ace
						else if (cardRank.compare("A") == 0 || cardRank.compare("a") == 0){
							currCard.rank = Card::ace;
						}
						//invalid rank information, process next string
						else{
							cout << "Warning: Invalid rank information in card definition string" << endl;
							continue;
						}
					}
					//add card into buffer if valid
					buffer.push_back(currCard);
				}
				//invalid length for card definition string, process next string
				else{
					cout << "Warning: Invalid length of card definition string" << endl;
					continue;
				}

			}

			//valid line if five valid card definition strings exist
			//store cards into card vector
			if (buffer.size() == 5){
				for (vector<Card>::size_type i = 0; i != buffer.size(); i++){
					cards.push_back(buffer[i]);
				}
			}
			//print message if invalid line found
			else{
				cout << "Warning: Not a hand" << endl;
			}
			//clear the buffer for next round
			buffer.clear();
		}
		ifs.close();
		return success;
	}
	//fail to open file
	else{
		cout << "Error in opening input file" << endl;
		return file_fail;
	}
}

// print each card in the vector
int printCards(const vector<Card> &cards){
	//empty card deck
	if (cards.size() < 1){
		cout << "Empty card deck" << endl;
		return print_fail;
	}

	Card currCard;
	//card information
	static const string suits[] = { "Clubs", "Diamonds", "Hearts", "Spades" };
	static const string ranks[] = { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };

	//traverse the vector to print each card
	for (vector<Card>::size_type i = 0; i != cards.size(); i++){
		currCard = cards[i];
		//build a string and print out
		string cardInfo = ranks[currCard.rank] + " of " + suits[currCard.suit];
		cout << cardInfo << endl;
	}
	return success;
}


//print poker hand rank and five cards in the hand
int printHandRank(const vector<Card> &cards){
	//empty card deck
	if (cards.size() < 1){
		cout << "Warning: Empty card deck" << endl;
		return print_fail;
	}
	cout << "------- Poker Hand Ranks: --------" << endl;
	//create a vector to store five cards at a time
	vector<Card> hand;
	//total number of hands
	unsigned int numberOfHand = cards.size() / 5;

	for (unsigned int i = 0; i<numberOfHand; ++i){
		//clear previous storage
		hand.clear();
	    //select five cards at each time
		for (vector<Card>::size_type j = 5 * i; j <= 5 * i + 4; j++){
			hand.push_back(cards[j]);
		}
		//sort current hand of cards
		sort(hand.begin(), hand.end());

		//variable to record rank results
		int straight = 0, flush = 0, four=0, three=0, fullhouse=0;
	    
		//index used for the comparison
		vector<Card>::size_type k = 0;
		int offset = 0;

		//check if cards in hand are consecutive in rank
		//if so, set straight to 1
		while (k<hand.size()-1 && hand[k + 1].rank - hand[k].rank == 1){
			k++;
		}
		if (k == hand.size()-1){
			straight = 1;
		}


		//check if cards in hand are of the same suit
		//if so, set flush to 1
		k = 0;
		while (k<hand.size() - 1 && hand[k].suit == hand[k + 1].suit){
			k++;
		}
		if (k == hand.size() - 1){
			flush = 1;
		}

		//determine case of straight flush
		if (straight && flush){
			cout << "Valid Hand No." << i << ": straight flush" << endl;
			cout << "Cards in hand: " << endl;
			printCards(hand);
			continue;
		}


		//check fours
		//since the cards are already sorted by rank, if four of a kind exists,
		//the only card with different rank must either be the first card or last card in hand
		k = 0;
		offset = 0;
		while (k < hand.size() - 3){
			while (offset<3 && hand[k + offset].rank == hand[k + offset + 1].rank){
				offset++;
			}
			if (offset == 3){
				four = 1;
			}
			offset = 0;
			k++;
		}

	    //deterime case of four of a kind
		if (four){
			cout << "Valid Hand No." << i << ": four of a kind" << endl;
			cout << "Cards in hand: " << endl;
			printCards(hand);
			continue;
		}


		//check case of threes and full house
		k = 0;
		offset = 0;
		while (k < hand.size() - 2){
			while (offset<2 && hand[k + offset].rank == hand[k + offset + 1].rank){
				offset++;
			}
			if (offset == 2){
				//three of a kind
				three = 1;
				//continue to check if full house exists
				if (k == 0 && hand[k + 3].rank == hand[k + 4].rank){
					fullhouse = 1;
				}
				else if (k == 2 && hand[k - 2].rank == hand[k - 1].rank){
					fullhouse = 1;
				}
			}
			offset = 0;
			k++;
		}
		
		//deterime case of fullhouse, flush, straight and three of a kind
		if (fullhouse){
			cout << "Valid Hand No." << i << ": full house" << endl;
			cout << "Cards in hand: " << endl;
			printCards(hand);
			continue;
		}
		else if (flush){
			cout << "Valid Hand No." << i << ": flush" << endl;
			cout << "Cards in hand: " << endl;
			printCards(hand);
			continue;
		}
		else if (straight){
			cout << "Valid Hand No." << i << ": straight" << endl;
			cout << "Cards in hand: " << endl;
			printCards(hand);
			continue;
		}
		else if (three){
			cout << "Valid Hand No." << i << ": three of a kind" << endl;
			cout << "Cards in hand: " << endl;
			printCards(hand);
			continue;
		}


		//check case of two or one pairs
		k = 0;
		int pairs = 0;
		while (k < hand.size() - 1){
			if (hand[k].rank == hand[k + 1].rank){
				pairs++;
			}
			k++;
		}

		//determine case of one, two pairs or no rank
		if (pairs == 2){
			cout << "Valid Hand No." << i << ": two pairs" << endl;
			cout << "Cards in hand: " << endl;
			printCards(hand);
			continue;
		}
		else if (pairs == 1){
			cout << "Valid Hand No." << i << ": one pair" << endl;
			cout << "Cards in hand: " << endl;
			printCards(hand);
			continue;
		}
		else{
			cout << "Valid Hand No." << i << ": no rank" << endl;
			cout << "Cards in hand: " << endl;
			printCards(hand);
			continue;
		}
		
	}
	return success;
}



//extra credit portion
int extraCredit(const vector<Card> &cards){
	//empty card deck
	if (cards.size() < 1){
		cout << "Warning: Empty card deck" << endl;
		return print_fail;
	}
	cout << "------- Extra credit: --------" << endl;
	//create a vector to store hands
	vector<Hand> hands;

	//create a vector to store five cards at a time
	vector<Card> hand;
	//create a hand to store hand info
	Hand currHand;

	//total number of hands
	unsigned int numberOfHand = cards.size() / 5;

	for (unsigned int i = 0; i<numberOfHand; ++i){
		//clear previous storage
		hand.clear();
		//select five cards at each time
		for (vector<Card>::size_type j = 5 * i; j <= 5 * i + 4; j++){
			hand.push_back(cards[j]);
		}
		//sort current hand of cards
		sort(hand.begin(), hand.end());

		//store five cards into current hand
		currHand.cardsInHand = hand;

		//variable to record rank results
		int straight = 0, flush = 0, four = 0, three = 0, fullhouse = 0;

		//index used for the comparison
		vector<Card>::size_type k = 0;
		int offset = 0;

		//check if cards in hand are consecutive in rank
		//if so, set straight to 1
		while (k<hand.size() - 1 && hand[k + 1].rank - hand[k].rank == 1){
			k++;
		}
		if (k == hand.size() - 1){
			straight = 1;
		}


		//check if cards in hand are of the same suit
		//if so, set flush to 1
		k = 0;
		while (k<hand.size() - 1 && hand[k].suit == hand[k + 1].suit){
			k++;
		}
		if (k == hand.size() - 1){
			flush = 1;
		}

		//determine case of straight flush
		if (straight && flush){
			currHand.rank = Hand::straight_flush;
			hands.push_back(currHand);
			continue;
		}


		//check fours
		//since the cards are already sorted by rank, if four of a kind exists,
		//the only card with different rank must either be the first card or last card in hand
		k = 0;
		offset = 0;
		while (k < hand.size() - 3){
			while (offset<3 && hand[k + offset].rank == hand[k + offset + 1].rank){
				offset++;
			}
			if (offset == 3){
				four = 1;
			}
			offset = 0;
			k++;
		}

		//deterime case of four of a kind
		if (four){
			currHand.rank = Hand::four_kind;
			hands.push_back(currHand);
			continue;
		}


		//check case of threes and full house
		k = 0;
		offset = 0;
		while (k < hand.size() - 2){
			while (offset<2 && hand[k + offset].rank == hand[k + offset + 1].rank){
				offset++;
			}
			if (offset == 2){
				//three of a kind
				three = 1;
				//continue to check if full house exists
				if (k == 0 && hand[k + 3].rank == hand[k + 4].rank){
					fullhouse = 1;
				}
				else if (k == 2 && hand[k - 2].rank == hand[k - 1].rank){
					fullhouse = 1;
				}
			}
			offset = 0;
			k++;
		}

		//deterime case of fullhouse, flush, straight and three of a kind
		if (fullhouse){
			currHand.rank = Hand::full_house;
			hands.push_back(currHand);
			continue;
		}
		else if (flush){
			currHand.rank = Hand::flush;
			hands.push_back(currHand);
			continue;
		}
		else if (straight){
			currHand.rank = Hand::straight;
			hands.push_back(currHand);
			continue;
		}
		else if (three){
			currHand.rank = Hand::three_kind;
			hands.push_back(currHand);
			continue;
		}


		//check case of two or one pairs
		k = 0;
		int pairs = 0;
		while (k < hand.size() - 1){
			if (hand[k].rank == hand[k + 1].rank){
				pairs++;
			}
			k++;
		}

		//determine case of one, two pairs or no rank
		if (pairs == 2){
			currHand.rank = Hand::two_pairs;
			hands.push_back(currHand);
			continue;
		}
		else if (pairs == 1){
			currHand.rank = Hand::one_pair;
			hands.push_back(currHand);
			continue;
		}
		else{
			currHand.rank = Hand::no_rank;
			hands.push_back(currHand);
			continue;
		}

	}

	//sort hands by the defined operator<
	//reverse the sorted vector so that highest ranks come first
	sort(hands.begin(), hands.end());
	reverse(hands.begin(), hands.end());
	
	//hand information
	static const string handRank[] = { "no rank", "one pair", "two pairs", "three of a kind", "straight", "flush", "full house", "four of a kind", "straight flush"};
	
	
	//traverse the vector to print each hand
	int i = 0;
	for (Hand curr: hands){
		cout << "Valid Hand No." << i << " : " << handRank[curr.rank] << endl;
		//print cards in each hand
		cout << "Cards in hand: " << endl;
		printCards(curr.cardsInHand);
		i++;
	}
		
	return success;
}



// check if a string contains a numerical value
bool is_number(const string& s)
{
	string::const_iterator it = s.begin();
	//traverse the string until a character is not a digit
	while (it != s.end() && isdigit(*it)) {
		++it;
	}
	return !s.empty() && it == s.end();
}


//define less than operator for card
bool Card::operator< (const Card & card) const{
	//first compare rank and then suit
	return (rank < card.rank) || ((rank == card.rank) && (suit < card.suit));
}

//define less than operator for hand
bool Hand::operator< (const Hand & hand) const{
	//use hand rank to decide if two hand ranks are different
	if (rank != hand.rank){
		return rank < hand.rank;
	}
	else{
		//get vectors that contain information in the case of two pairs and one pair
		vector<int> info1 = getTwoPairsInfo(cardsInHand);
		vector<int> info2 = getTwoPairsInfo(hand.cardsInHand);
		vector<int> info3 = getOnePairInfo(cardsInHand);
		vector<int> info4 = getOnePairInfo(hand.cardsInHand);

		switch (rank){
		case Hand::straight_flush:
			//sorted by highest card in each hand
			return cardsInHand[4].operator<(hand.cardsInHand[4]);

		case Hand::four_kind:
			//sorted by rank of 4 cards that have the same rank
			return cardsInHand[2].rank < hand.cardsInHand[2].rank;

		case Hand::full_house:
			//sorted by rank of 3 cards that have the same rank 
			//then by rank of 2 cards that have the same rank
			if (cardsInHand[2].rank == hand.cardsInHand[2].rank){
				return 1;
			}
			else{
				return cardsInHand[2].rank < hand.cardsInHand[2].rank;
			}

		case Hand::flush:
			//sorted by highest ranking card, then by next highest ranking card, etc
			for (vector<Card>::size_type i = cardsInHand.size()-1; i != 0; i--){
				if (cardsInHand[i].rank != hand.cardsInHand[i].rank){
					return cardsInHand[i].rank < hand.cardsInHand[i].rank;
				}
			}
			return cardsInHand[0].rank < hand.cardsInHand[0].rank;

		case Hand::straight:
			//sorted by highest card in each hand
			return cardsInHand[4].operator<(hand.cardsInHand[4]);

		case Hand::three_kind:
			//sorted by the rank of the 3 cards that have the same rank
			return cardsInHand[2].rank < hand.cardsInHand[2].rank;

		case Hand::two_pairs:
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

			
		case Hand::one_pair:
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

		case Hand::no_rank:
			//sorted by highest ranking card, then by next highest ranking card
			for (vector<Card>::size_type i = cardsInHand.size()-1; i != 0; i--){
				if (cardsInHand[i].rank != hand.cardsInHand[i].rank){
					return cardsInHand[i].rank < hand.cardsInHand[i].rank;
				}
			}
			return cardsInHand[0].rank < hand.cardsInHand[0].rank;

		default:
			return false;

		}
	}
}

//get information if hand rank is two pairs
vector<int> getTwoPairsInfo(const vector<Card> &cardsInHand){
	//twoPairsInfo[0] = rank of highest pair
	//twoPairsInfo[1] = rank of second highest pair
	//twoPairsInfo[2] = rank of fifth card
	vector<int> twoPairsInfo;
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
vector<int> getOnePairInfo(const vector<Card> &cardsInHand){
	//onePairInfo[0] = rank of the pair
	//onePairInfo[1] = highest rank of unpaired card
	//onePairInfo[2] = next highest rank of unpaired card
	//onePairInfo[3] = next highest rank of unpaired card
	vector<int> onePairInfo;
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