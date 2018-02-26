/// @file piece.h
//Contains the class piece, along with the declarations and definitions of its functions.

// Brock Ferrell
// CS2401
// November 23, 2015
// Project7

#ifndef PIECE_H
#define PIECE_H
enum color {black, white, blank};

class piece {
public:
	piece() {theColor = blank;}

	void flip()
	{
		/// No Parameters are used in the flip function.
		/// This function fliped a opposite color piece. 
		/// So if a player is black and comes across a white piece 
		/// that piece will flip from white to black.
		if (theColor == white) {
			theColor = black;
		}
		else if (theColor == black) {
			theColor = white;
		}
	}

	bool is_blank()const {return theColor == blank;}
	bool is_black()const 
	{
		/// Returns true if the color of the piece is black.
		return theColor == black;
	}
	bool is_white()const {return theColor == white;}
	void set_white() {theColor = white;}
	void set_black() {theColor = black;}

private:
	color theColor;

};

#endif

