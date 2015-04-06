// lab3.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include "Game.h"
#include "Error.h"
using namespace std;

#define MIN_NUM_ARGS 4


int main(int argc, char* argv[]){
	//number of arguments not enough
	if (argc < MIN_NUM_ARGS){
		cout << "Too few arguments" << endl;
		cout << "Usage: lab3 <Game name> <player1's name> <player2's name> ... " << endl;
		return Error::two_few_arguments;
	}


	shared_ptr<Game>game_holder;
	try{
		//start the game with the given name
		Game::start_game(argv[1]);
		//obtain a pointer to the game
		shared_ptr<Game> ptr_newg = Game::instance();
		game_holder = ptr_newg;


		//add players to the game
		for (int i = 2; i < argc; i++){
			string temp(argv[i]);
			
			(*ptr_newg).add_player(temp);
		}

		//continue the game if at least two players
		while ((*ptr_newg).num_players_in_game() >= 2){
			(*ptr_newg).before_round();
			(*ptr_newg).round();
			(*ptr_newg).after_round();

		}

	}
	//catch exception and stop the game
	catch (Error i){
		cout << "Exception caught, stop the game" << endl;
		try{
			(*game_holder).stop_game();
		}
		catch (Error j){
			return j;
		}
		return i;
	}

	//stop the game in the end
	try{
		(*game_holder).stop_game();
		return Error::Success;
	}
	catch(Error k){
		return k;

	}
  
}