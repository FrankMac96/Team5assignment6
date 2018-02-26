// File: game.cxx
///Assignment6 Documentation TESTTEST
/// This file contains the functions for game.cc. These functions allow the player to play othello until the game reaches a winner or tie. 
#include <cassert>    /// Provides assert
#include <climits>    /// Provides INT_MAX and INT_MIN
#include <iostream>   /// Provides cin, cout
#include <queue>      /// Provides queue<string>
#include <string>     /// Provides string
#include "game.h"     /// Provides definition of game class
using namespace std;

namespace main_savitch_14
{
//************************************************************************* 
// STATIC MEMBER CONSTANTS
// const int game::SEARCH_LEVELS;

//*************************************************************************
// PUBLIC MEMBER FUNCTIONS

game::who game::play( )
// The play function should not be overridden. It plays one round of the
// game, with the human player moving first and the computer second.
// The return value is the winner of the game (or NEUTRAL for a tie).

/// This function  produces a human move first, and then a computer move.
/// The return value for this function is the winner of the game, or NEUTRAL for a tie.
{
	restart( );

	while (!is_game_over( ))
	{
		display_status( );
		whosTurn();
		if (last_mover( ) == COMPUTER) {
			countingPieces();
			make_human_move( );
		}
		else {
			make_computer_move( );
		}
	}
	display_status( );
	return HUMAN;
}



//*************************************************************************
// OPTIONAL VIRTUAL FUNCTIONS (overriding these functions is optional)


void game::display_message(const string& message) const
/// This function displays a message to the player through standard output. 
/// The parameter  of this function is the meassage being displayed. 
{
	cout << message;
}

string game::get_user_move( ) const
/// This function is used to generate a move by the user. The string answer is used to hold the move the player wishes to make.
/// If the player cannot move, this function will alow the player to skip. The player can enter moves until a valid move is entered.
{
	string answer;

	display_message("If you cannot move, please press 'S'\n");
	display_message("Your move, please: ");
	getline(cin, answer);
	return answer;
}

game::who game::winning()const
/// This function evaluates the game board and calcutes which player is winning.
{

	int value = evaluate();

	if (value > 0) {
		return last_mover();
	} else if (value < 0) {
		return next_mover();
	} else {
		return NEUTRAL;
	}

}

//*************************************************************************
/// PRIVATE FUNCTIONS (these are the same for every game)

int game::eval_with_lookahead(int look_ahead, int beat_this)
/// Evaluates a board position with lookahead.
/// --int look_aheads:  How deep the lookahead should go to evaluate the move.
/// --int beat_this: Value of another move that we're considering. If the
/// current board position can't beat this, then cut it short.
/// The return value is large if the position is good for the player who just
/// moved.
{
	queue<string> moves;   /// All possible opponent moves
	int value;             /// Value of a board position after opponent moves
	int best_value;        /// Evaluation of best opponent move
	game* future;          /// Pointer to a future version of this game

	/// Base case:
	if (look_ahead == 0 || is_game_over( ))
	{
		if (last_mover( ) == COMPUTER)
			return evaluate( );
		else
			return -evaluate( );
	}

	/// Recursive case:

	compute_moves(moves);
	/// assert(!moves.empty( ));
	best_value = INT_MIN;
	while (!moves.empty( ))
	{
		future = clone( );
		future->make_move(moves.front( ));
		value = future->eval_with_lookahead(look_ahead - 1, best_value);
		delete future;
		if (value > best_value)
		{
			if (-value <= beat_this)
				return INT_MIN + 1; // Alpha-beta pruning
			best_value = value;
		}
		moves.pop( );
	}

	// The value was calculated from the opponent's perspective.
	// The answer we return should be from player's perspective, so multiply times -1:
	return -best_value;
}

void game::make_computer_move( )
{
	queue<string> moves;
	int value;
	int best_value;
	string best_move;
	game* future;

	// Compute all legal moves that the computer could make.
	compute_moves(moves);
	//assert(!moves.empty( ));

	// Evaluate each possible legal move, saving the index of the best
	// in best_index and saving its value in best_value.
	best_value = INT_MIN;
	while (!moves.empty( ))
	{
		future = clone( );
		future->make_move(moves.front( ));
		value = future->eval_with_lookahead(SEARCH_LEVELS, best_value);
		delete future;
		if (value >= best_value)
		{
			best_value = value;
			best_move = moves.front( );
		}
		moves.pop( );
	}

	// Make the best move.
	make_move(best_move);
}

void game::make_human_move( ) {
	string move;

	move = get_user_move( );
	while (!is_legal(move))
	{
		display_message("Illegal move.\n");
		move = get_user_move( );
	}
	make_move(move);
}

}



