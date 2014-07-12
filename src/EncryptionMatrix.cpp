/*
 * EncryptionMatrix.cpp
 *
 *  Created on: 12.07.2014
 *      Author: joergw
 */

#include "EncryptionMatrix.h"
#include <algorithm>
#include <iostream>

EncryptionMatrix::EncryptionMatrix( std::string& passphrase ) {

	std::string charsForMatrixInsertion = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; // these still need to be inserted into the matrix

	// Write the passphrase into the beginning of the matrix
	this->encryptionString = passphrase;

	// Delete the characters from the passphrase from the string of
	// characters yet to be added (they have already been added, at the start).
	for ( char& c : passphrase ) {
		charsForMatrixInsertion.erase( std::remove( charsForMatrixInsertion.begin(), charsForMatrixInsertion.end(), c ), charsForMatrixInsertion.end() );
	}

	// Now add the rest of the characters NOT contained in the passphrase to the
	// encryption string.
	this->encryptionString += charsForMatrixInsertion;
}

std::string
EncryptionMatrix::convertText( std::string& inputText, CryptoDirection& direction ) const {
	std::string outputText = ""; // This is the result

	// Loop over the input string. Build pairs of characters.
	// Determine their position
	for ( int i = 0; i < inputText.length() / 2; i++ ) {
		char c1, c2;      // Characters to be compared

		c1 = inputText[ i * 2 ];
		c2 = inputText[ ( i * 2 ) +1 ];
		MatrixPoint point1 = this->findPosition( c1 );
		MatrixPoint point2 = this->findPosition( c2 );

		// Now we have to look at the relative positions and
		// do the encryption.
		outputText += this->createTargetCharPair( point1, point2, direction );

	}

	// If there is an uneven number of chars, the last one is moved
	// down / up one square
	if ( ( inputText.length() % 2 ) == 1 ) {
		char c;
		c = inputText[ inputText.length() - 1 ];
		MatrixPoint point = this->findPosition( c );
		MatrixPoint newPoint( point.x, ( point.y + direction + MATRIXDIM ) % MATRIXDIM );
		outputText += this->getChar( newPoint );
	}

	return outputText;

}

char
EncryptionMatrix::getChar( MatrixPoint& point ) const {
	return encryptionString[ point.y * MATRIXDIM + point.x ];
}


EncryptionMatrix::~EncryptionMatrix() {
	delete encryptionString;
}

MatrixPoint
EncryptionMatrix::findPosition(char c) const {
	int position = encryptionString.find( c );
	MatrixPoint point( position, MATRIXDIM );
	return point;
}

std::string
EncryptionMatrix::createTargetCharPair( MatrixPoint point1,	MatrixPoint point2, CryptoDirection direction) const {

	std::string result = "";
	MatrixPoint* newPoint = 0;
	// Determine the relative position of the 2 characters
	if ( ( point1.x != point2.x ) && ( point1.y != point2.y ) ) {
		// Both axes are different. Swap horizontally
		newPoint = new MatrixPoint( point2.x, point1.y );
		result += getChar( *newPoint ); // move c1 horizontally
		delete newPoint;
		newPoint = new MatrixPoint( point1.x, point2.y );
        result += getChar( *newPoint ); // move c2 horizontally
        delete newPoint;
	} else if ( ( point1.x == point2.x ) && ( point1.y != point2.y ) ) {
		// On the same X axis. Move both chars down / up one space; roll over if needed
		newPoint = new MatrixPoint( point1.x, ( point1.y + direction + MATRIXDIM ) % MATRIXDIM );
		result += getChar( *newPoint );
		delete newPoint;
		newPoint = new MatrixPoint( point2.x, ( point2.y + direction + MATRIXDIM ) % MATRIXDIM );
		result += getChar( *newPoint );
		delete newPoint;
	} else if ( ( point1.x != point2.x ) && ( point1.y == point2.y ) ) {
		// On the same Y axis. Move right / left one space; roll over if needed
		newPoint = new MatrixPoint( ( point1.x + direction + MATRIXDIM ) % MATRIXDIM, point1.y );
		result += getChar( *newPoint );
		delete newPoint;
		newPoint = new MatrixPoint( ( point2.x + direction + MATRIXDIM ) % MATRIXDIM, point2.y );
		result += getChar( *newPoint );
		delete newPoint;
	} else if ( ( point1.x == point2.x ) && ( point1.y == point2.y ) ) {
		// Identical characters: move both one space down / up, roll over if needed
		newPoint = new MatrixPoint( point1.x, ( point1.y + direction + MATRIXDIM ) % MATRIXDIM );
		result += getChar( *newPoint );
		delete newPoint;
		newPoint = new MatrixPoint( point2.x, ( point2.y + direction + MATRIXDIM ) % MATRIXDIM );
		result += getChar( *newPoint );
		delete newPoint;
	} else {
		// SHIT this is not supposed to happen!
		std::cout << "Clusterfuck; this coding should be completely unreachable!" << std::endl;
	}
	return result;
}



