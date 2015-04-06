#include "stdafx.h"
#include "FiveCardDraw.h"
#include "Game.h"
#include "Deck.h"
using  namespace std;

////////////////////////////////////////
// Utility Functions                 ///
////////////////////////////////////////

//different hand ranks
static const std::string handRanks[] = { "no_rank", "one_pair", "two_pairs", "three_kind", "straight", "flush", "full_house", "four_kind", "straight_flush" };

//parse response and return a vector of valid positions for discarding player's cards
//NOTE: vector[0] used to store number of invalid positions that user entered
bool is_anumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	//traverse the string until a character is not a digit
	while (it != s.end() && isdigit(*it)) {
		++it;
	}
	return !s.empty() && it == s.end();
}
vector<int> valid_input_positions(string response, unsigned int hand_size){


	istringstream ss(response);
	vector<int> user_inputs;
	user_inputs.push_back(0);
	string temp;

	


	while (ss >> temp){
		//convert string to numerical value
		if (!is_anumber(temp)){ cout << "Detecting non-numeric position value from user input" << endl; ++user_inputs[0]; continue; }
		size_t check = stoi(temp);

		//valid positions
		if (check >= 0 && check < hand_size){
			user_inputs.push_back(check);
		}
		else{
			cout << "detecting invliad position from user" << ": " << check << endl;
			//increment the counter for invalid positions
			++user_inputs[0];
		}
	}



	return user_inputs;
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

//compare two hands
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
			}
			return cardsInHand[0].rank < cardsInHand2[0].rank;

		default:
			return false;

		}
	}
}




////////////////////////////////////////////////
// Class Method Implementation                //
///////////////////////////////////////////////

//default constructor
FiveCardDraw::FiveCardDraw(){
	//initialize dealer position to zero
	dealer_position = 0;

	//generate 52 combinations of cards and add them to main deck
	Card curr_card;
	for (int suitIdx = Card::Suit::clubs; suitIdx != Card::Suit::spades; ++suitIdx){
		for (int rankIdx = Card::Rank::two; rankIdx != Card::Rank::ace; ++rankIdx){
			curr_card.rank = static_cast<Card::Rank>(rankIdx);
			curr_card.suit = static_cast<Card::Suit>(suitIdx);
			main_deck.add_card(curr_card);
		}
	}
}


//Helper Function for extra credit
//generate positions to discard for auto_player. Note: position 0 is the counter

vector<int>	FiveCardDraw::auto_valid_positions(Player &player){

	enum hand_rank{
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

	enum card_Rank{
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
		king,
		ace
	};


	player.player_hand.setHandRank();
	vector<int> valid_positions;
	valid_positions.push_back(0);

	


	//straight flush, full house, straight, or flush: do not discard or receive any cards;
	if ((player.getPlayerHand().getRank() == straight_flush) || (player.getPlayerHand().getRank() == full_house) || (player.getPlayerHand().getRank() == straight) || (player.getPlayerHand().getRank() == flush)) {
	
		return valid_positions;
	}
	//four of a kind or two pair: discard the unmatched card and receive one more card;
	
	else if (player.getPlayerHand().getRank() == four_kind){
		if (!(player.player_hand[0].rank == player.player_hand[1].rank)){

			valid_positions.push_back(0);
		}
		else{
			valid_positions.push_back(player.player_hand.size() - 1);
		}
		return valid_positions;
	}
	
	else if (player.getPlayerHand().getRank() == two_pairs){
		vector<int> two_pairs = getTwoPairsInfo(player.player_hand.getCards());
		vector<Card> myhand = player.player_hand.getCards();
		vector<int> vec_hand_rank;
		for (auto i : myhand){
			vec_hand_rank.push_back(i.rank);
		}
		int pos = find(vec_hand_rank.begin(), vec_hand_rank.end(), two_pairs[2]) - vec_hand_rank.begin();
		valid_positions.push_back(pos);
		
		return valid_positions;
	}
	//three of a kind: discard the two unmatched cards and receive two more cards;
	
	
	else if (player.getPlayerHand().getRank() == three_kind){

		vector<Card> myhand = player.player_hand.getCards();
		if (myhand[0].rank == myhand[1].rank && myhand[1].rank == myhand[2].rank){

			valid_positions.push_back(myhand.size() - 1);
			valid_positions.push_back(myhand.size() - 2);

		}
	    else if (myhand[1].rank == myhand[2].rank && myhand[2].rank == myhand[3].rank){
			valid_positions.push_back(0);
			valid_positions.push_back(myhand.size() - 1);
		}
		else{
			valid_positions.push_back(0);
			valid_positions.push_back(1);
		}
		return valid_positions;
	}
	
	//one pair: discard the three unmatched cards and receive three more cards;
	else if (player.getPlayerHand().getRank() == one_pair){
		vector<int> one_pair = getOnePairInfo(player.player_hand.getCards());
		vector<Card> myhand = player.player_hand.getCards();
		vector<int> vec_hand_rank;
		for (auto i : myhand){
			vec_hand_rank.push_back(i.rank);
		}
		for (int i = 1; i <= 3; ++i){
			int pos = find(vec_hand_rank.begin(), vec_hand_rank.end(), one_pair[i]) - vec_hand_rank.begin();
			valid_positions.push_back(pos);
		}
		return valid_positions;
	}
	else{
		vector<Card> myhand = player.player_hand.getCards();
		bool aced = false;
		int aced_index;
		for (size_t i = 0; i < myhand.size(); ++i){
			if (myhand[i].rank == ace){
				aced = true;
				aced_index = i;
				break;
			}
		}
		if (aced){
			for (size_t i = 0; i < myhand.size(); ++i){
				if (aced_index != i){
					valid_positions.push_back(i);
				}
			}

		}
		else{
			for (size_t i = 0; i < 3; ++i){
				valid_positions.push_back(i);
			}
		}
		return valid_positions;
	}
	

}

//method called before the given player's turn
int FiveCardDraw::before_turn(Player &player){
	//print player's name and his hand
	bool is_autoPlayer = false;
	player.player_hand.setHandRank();
	string info = player.player_name + " " + player.player_hand.asString();
	cout << info << endl;

	vector<int> user_inputs;

	char last = player.player_name[player.player_name.length() - 1];



	//char last = *player.player_name.rbegin();
	//string expected_star(1, last);
	if (last == '*'){
		cout << "Automated Player: " << info << " " << "is playing" << endl;

		user_inputs = auto_valid_positions(player);
	
	}
	else{
		//prompt the user to discard cards
		cout << "Please give positions of cards you want to discard" << endl;

		//get user response and parse it to get a vector of valid positions for discarding cards
		string response;
		getline(cin, response);

		unsigned int size = player.player_hand.size();
		user_inputs = valid_input_positions(response, size);

		//keep re-prompting if reponse is invalid
		while (user_inputs.size() == 1 && user_inputs[0] > 0){
			cout << "Please give positions of cards you want to discard" << endl;
			getline(cin, response);

			user_inputs = valid_input_positions(response, size);


		}

	}

	 
	 
	 //discard the cards to discard deck
	 try{
		 for (unsigned int i = 1; i < user_inputs.size(); ++i){
	
			 //add card to discard deck
			 discard_deck.add_card(player.player_hand[user_inputs[i]]);
			 //remove card from player's hand
			
			 player.player_hand.remove_card(user_inputs[i]);
		

			 //@updating the user_position vector

			 for (unsigned int j = 1; j < user_inputs.size(); ++j){
				 if (user_inputs[j] > user_inputs[i]){
					 user_inputs[j]--;
				 }

			 }
		 }
	 }
	 catch (Error error){
		 return error;
	 }


	return 0;
	
}


 //method called for the given player's turn
 int  FiveCardDraw:: turn(Player &player){
	 //compute number of replacement needed due to discarding cards
	 int NofCards_needed = VALID_HAND_SIZE - (player.player_hand.size());

	 //deal cards into player's hand until 5 cards in hand
	 while (NofCards_needed > 0){
		 //both decks have no cards
		 if (main_deck.size() == 0 && discard_deck.size() == 0){
			 return no_more_card_for_this_game_go_home;
		 }
		 //no cards in main deck, shuffle discard deck and deal card from it
		 else if (main_deck.size() == 0){
			 discard_deck.shuffle();
			 player.player_hand << discard_deck;
		 }
		 //deal card from main deck
		 else{
			 player.player_hand << main_deck;
		 }
		 NofCards_needed--;

	 }
	 return 0;
 }


 //method called after the given player's turn
 int  FiveCardDraw::after_turn(Player &player){
	 //print player's name and his hand
	 string info = player.player_name + " " + player.player_hand.asString();
	 cout << info << endl;
	 return 0;

 }
 

 //method called before game's round
 int  FiveCardDraw::before_round() { 
	 //too many players to distribute 5 cards to each player
	 if ((short)(VALID_HAND_SIZE * players.size()) > (main_deck.size() + discard_deck.size())){
		 return too_many_players; 
	 }

	 //shuffle main deck and distribute 5 cards to each player starting from dealer position
	 for (int i = 0; i < VALID_HAND_SIZE; ++i){
		 main_deck.shuffle();
		 for (size_t count = 1; count <= num_players_in_game(); count++){
			 (*players[(dealer_position + count) % num_players_in_game()]).player_hand << main_deck;
		 }

	 }
	 
	 //call before_turn method on each player
	 for (size_t count = 1; count <= num_players_in_game(); count++){
		 //check for exception
		 
		 int check_before_turn = before_turn(*players[ (dealer_position+ count)% num_players_in_game()     ]);
		

		 //return non-zero value to indicate failure
		 if (check_before_turn != 0){
			 return check_before_turn;
		 }
			 
	 }
	 return 0;

 }

 //method called for game's round
 int FiveCardDraw::round(){
	 //call turn and after_turn method on each player
	 for (size_t count = 1; count <= num_players_in_game(); count++){
		 //call turn on the player
		 int check_turn = turn(*players[(dealer_position + count) % num_players_in_game()]);

		 //immediately return non-zero value to indicate failure of calling turn method
		 if (check_turn != 0){
			 return check_turn;
		 }

		 //call after_turn on the player
		 after_turn(*players[(dealer_position + count) % num_players_in_game()]);
	 }
	 return 0;
 }
 

 //method called after game's round
 int FiveCardDraw::after_round(){
	 //sort players based on their hand rank
	 print_sorted_player();
	 //move all cards into main deck
	 reset();


	 //promt the user asking if anyone wants to leave
	 string response;
	 cout << "Anyone wants to leave?" << endl;
	 
	 //parse user response
	 getline(cin, response);


	 //keep promting the user until saying no
	 while (response.compare("no") != 0){

		 istringstream player_names(response);
		 vector<string> names;
		 string temp;
		 while (player_names >> temp){
			 names.push_back(temp);

		 }

		 for (size_t i = 0; i < num_players_in_game(); i++)
		 {
			 for (string s : names){
				 //matching player found
				 if ((*players[i]).player_name.compare(s) == 0){
					 //output statistics to file
					 ofstream player_file(s + ".txt");
					 player_file << *players[i];
					 players.erase(players.begin() + i);
					 player_file.close();
					 terminate();
				 }
			 }
			 
		 }

		 //repromt
		 cout << "Anyone wants to leave?" << endl;
		 getline(cin, response);

	 }

	 //promt the user and ask if anyone wants to join
	 cout << "Anyone wants to join?" << endl;
	 string join_response;
	 getline(cin, join_response);
	




	 //keep repromting until saying no
	 while (join_response.compare("no") != 0){
		 //parse user response
		 istringstream player_names_join(join_response);
		 vector<string> join_names;
		 string join_temp;
		 while (player_names_join >> join_temp){
			 join_names.push_back(join_temp);

		 }
		
		 for (string s : join_names){
			 //add player to the game
			 try{ 
				 add_player(s); 
			 //player already in the game
			 }catch(Error i) {
				 cout << "player: " << s << " already playing" << endl;
				 cout << "Error code: " << i << endl;
			 }
		 }

		 //reprompt
		 cout << "Anyone wants to join?" << endl;
		 getline(cin,join_response);

	 }

	 //increment dealer position
	 dealer_position = (dealer_position + 1) % num_players_in_game();
	 return 0;
 }


 
 //compare player's rank
 bool player_rank(const std::shared_ptr<Player> & p1, const std::shared_ptr<Player> &p2){
	 //return false if first pointer is singluar
	 if (p1 == 0){
		 return false;
	 }

	 //return true if first pointer is non-singluar but second pointer is singular
	 if (p1 != 0 && p2 == 0){
		 return true;
	 }

	 //otherwise, return normal comparison result based on their hands
	 return poker_rank((*p1).getPlayerHand(), (*p2).getPlayerHand());
 }


 //print information of sorted players bases on their hand ranks
 void FiveCardDraw::print_sorted_player(){
	
	 //make a copy of vector member variable
	 vector<shared_ptr<Player>> players_copy = players;

	 for (unsigned int i = 0; i < num_players_in_game(); ++i){
		 (*players_copy[i]).player_hand.setHandRank();
	 }

	 //sort
	 std::sort(players_copy.begin(), players_copy.end(), player_rank);

	 //update game statistics
	 for (unsigned int i = 0; i < num_players_in_game(); ++i){
		 //increment hands_won for players with highest rank
		 //NOTE: we assume it is possible for several players to have the same highest rank
		if ( player_rank(players[0],players[i]) == player_rank(players[i],players[0]) ){
			 (*players_copy[i]).hands_won++;
			 cout << "winner: " << (*players_copy[i]).player_name << endl;
		 }
		 //increment hands_lost for players not with highest rank
		 else{
			 (*players_copy[i]).hands_lost++;
		 }
	 }
	 
     //print each player's name, hands_won, hands_lost and current hand
	 for (unsigned int i = 0; i < players.size(); ++i){
		 Player current_player = *players_copy[i];
		 cout << "------------" << endl;
		 cout << current_player << endl;
		 cout << current_player.player_hand.asString() << endl;
		 cout << "------------" << endl;
	 }

	 //handle automated player's leaving
	 unsigned int game_size = num_players_in_game();
	 
	 for (unsigned int i = 0; i < num_players_in_game()-1; ++i){
		 char last = (*players_copy[i]).player_name[(*players_copy[i]).player_name.length() - 1];
		 if (last == '*'){
			 if (player_rank(players[0], players[i]) == player_rank(players[i], players[0])){
				 highest_automated_leave((*players_copy[i]).player_name);
			 }else{
				other_automated_leave((*players_copy[i]).player_name);
			 }
		 }
	 }

	 //check if automated player with lowest rank will leave
	 if (num_players_in_game() > 1){
		 char last = (*players_copy[num_players_in_game() - 1]).player_name[(*players_copy[num_players_in_game() - 1]).player_name.length() - 1];
		 if (last=='*' && player_rank(players[num_players_in_game() - 1], players[num_players_in_game() - 2]) != player_rank(players[num_players_in_game() - 2], players[num_players_in_game() - 1])){
			 lowest_automated_leave((*players_copy[num_players_in_game() - 1]).player_name);
		 }
	 }
 }


 void FiveCardDraw::highest_automated_leave(string automated_name){
	 unsigned int random_num = rand() % 100;
	
	 if (random_num <= 9){
		 for (size_t i = 0; i < num_players_in_game(); i++)
		 {
		     //matching player found
			 if ((*players[i]).player_name.compare(automated_name) == 0){
				//output statistics to file
				 ofstream player_file(automated_name.substr(0,automated_name.length()-1) + "_automated.txt");
				player_file << *players[i];
				players.erase(players.begin() + i);
				player_file.close();
				
				
				cout << "Automated player " << automated_name << " leave the game with highest rank with 10%" << endl;
				terminate();
			}
		 }
	 }
	 else{
		 cout << "Automated player " << automated_name << " does not leave the game with highest rank with 90%" << endl;
	 }
 }

 void FiveCardDraw::lowest_automated_leave(string automated_name){
	 unsigned int random_num = rand() % 100;
	 
	 if (random_num <= 89){
		 for (size_t i = 0; i < num_players_in_game(); i++)
		 {
			 //matching player found
			 if ((*players[i]).player_name.compare(automated_name) == 0){
				 //output statistics to file
				 ofstream player_file(automated_name.substr(0,automated_name.length() - 1) + "_automated.txt");
				 player_file << *players[i];
				 players.erase(players.begin() + i);
				 player_file.close();

				 cout << "Automated player " << automated_name << " leave the game with lowest rank with 90%" << endl;
				 terminate();
			 }
		 }
	 }
	 else{
		 cout << "Automated player " << automated_name << " does not leave the game with lowest rank with 10%" << endl;
	 }

 }

 void FiveCardDraw::other_automated_leave(string automated_name){
	 unsigned int random_num = rand() % 100;
	 if (random_num <= 49){
		 for (size_t i = 0; i < num_players_in_game(); i++)
		 {
			 //matching player found
			 if ((*players[i]).player_name.compare(automated_name) == 0){
				 //output statistics to file
				 ofstream player_file(automated_name.substr(0,automated_name.length() - 1) + "_automated.txt");
				 player_file << *players[i];
				 players.erase(players.begin() + i);
				 player_file.close();

				 cout << "Automated player " << automated_name << " leave the game with other rank with 50%" << endl;
				 terminate();
			 }
		 }
	 }
	 else{
		 cout << "Automated player " << automated_name << " does not leave the game with other rank with 50%" << endl;
	 }

 }




 //move all cards from players or discard deck into main deck
 void FiveCardDraw::reset(){

	 //move all cards from players into main deck
	 for (unsigned int i = 0; i < num_players_in_game(); ++i){
		 int size = (*players[i]).player_hand.size();
		 for (int j = 0; j < (size); ++j){
			 main_deck.add_card((*players[i]).player_hand[0]);
			 (*players[i]).player_hand.remove_card(0);
		 }


		 
	 }

	 //move all cards from discard deck into main deck
	 while (discard_deck.size() != 0){
		 main_deck.add_card(discard_deck.remove());
	 }

 }


 void FiveCardDraw::terminate(){
	 if (num_players_in_game() == 1){
		 char last = (*players[0]).player_name[(*players[0]).player_name.length() - 1];
		 if (last == '*'){
			 ofstream player_file((*players[0]).player_name.substr(0, (*players[0]).player_name.length()-1) + "_automated.txt");
			 player_file << *players[0];
			 players.erase(players.begin());
			 player_file.close();
		 }
		 else{
			 ofstream player_file((*players[0]).player_name + ".txt");
			 player_file << *players[0];
			 players.erase(players.begin());
			 player_file.close();
		 }

		 cout << "Only One player left. Stop the game" << endl;
		 throw Error::terminator;
	 }
 }
	
