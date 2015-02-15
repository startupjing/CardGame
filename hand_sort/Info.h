// Info.h
//
// author: Jing Lu  jinglu@wustl.edu
//
// purpose: define enumeration for error codes 

enum code{
	success,     //code 0: successful execution
	arg_fail,    //code 1: fail to satisfy argument requirements
	file_fail,   //code 2: fail to open file
	print_fail   //code 3: no valid cards
};