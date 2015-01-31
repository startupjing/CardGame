// lab0.cpp 
//
//author: Jing Lu jinglu@wustl.edu
//
//Purpose: Read card definition strings from input file, construct cards, and then print card string

#include "stdafx.h"
#include "Card.h"
#include "Info.h"
#include <string>  
#include <vector>
#include <iostream>  
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

int parseInput(vector<Card> &, char *);
int message(char *);
int printCards(const vector<Card> &);
bool is_number(const std::string &);


int main(int argc, char* argv[]){
	//useful constants for argument positions
	const int minimum_arguments = 2;
	const int file_index = 1;
	const int program_name_index = 0;

	//check usage of arguments, print useful message if invalid arguments
	if (argc != minimum_arguments || strcmp(argv[file_index], "--help") == 0){
		return message(argv[program_name_index]);
	}
	try{
		vector<Card> cards;
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
			//print each card
			status = printCards(cards);
			//print message if error in print cards
			if (status != success){
				cout << "Error when printing cards" << endl;
				return status;
			}
		}
		return success;
	}
	catch (...){
		cout << "caught exception" << endl;
		return -1;
	}
}

// print out useful message
int message(char *program_name){
	cout << "Usage: " << program_name << " <filename>"
		<< endl <<
		"Purpose: Read card definition strings from input file, construct cards, and then print card string"
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
	ifstream ifs;
	ifs.open(filename);
	//successfully open file
	if (ifs.is_open()){
		while (ifs >> cardDef){
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
						continue;
					}
					//check range
					if (idx >= 2 && idx <= 10){
						currCard.rank = Card::Rank(idx - 1);
					}
					//invalid rank information, process next string
					else{
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
						continue;
					}
				}
				//add card into vector if valid
				cards.push_back(currCard);
			}
			//invalid length for card definition string, process next string
			else{
				continue;
			}

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
	static const string ranks[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

	cout << "------- Cards information: --------" << endl;
	//traverse the vector to print each card
	for (vector<Card>::size_type i = 0; i != cards.size(); i++){
		currCard = cards[i];
		//build a string and print out
		string cardInfo = ranks[currCard.rank] + " of " + suits[currCard.suit];
		cout << cardInfo << endl;
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
