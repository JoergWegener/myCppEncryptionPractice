/*
 * EncryptionMatrix.h
 *
 *  Created on: 12.07.2014
 *      Author: joergw
 */

#ifndef ENCRYPTIONMATRIX_H_
#define ENCRYPTIONMATRIX_H_

#include "MatrixPoint.h"

enum CryptoDirection : int {
	DECRYPT = -1, ENCRYPT = 1
};

class EncryptionMatrix {
public:

	EncryptionMatrix( const std::string & passphrase );

	// This is the main method. Needs proper documentation.
	std::string convertText( const std::string& inputText, const CryptoDirection& direction ) const;

	virtual ~EncryptionMatrix();

private:

	const short MATRIXDIM = 6; // I hate magic numbers, always use constants

	// The encryption matrix is a 6x6 matrix. It contains all characters
	// and the numbers 0..9. SPACE is not needed, because it will always
	// be ignored.
	// Note that this is the MENTAL representation of the algorithm! The technical
	// one is one where there is one linear string, and the X and Y coordinates are
	// calculated from the one-dimensional position when needed on the basis of the
	// position and the matrix dimension.
	std::string encryptionString = "";


	// Method that reads a char from a MatrixPoint. Useful for encryption.
	char getChar ( const MatrixPoint& point ) const;


	// Helper method determines the MatrixPoint of a char.
	MatrixPoint findPosition ( char c ) const;


	// Helper method that returns a string of 2 chars for the clear chars provided.
	// This result has to be added to the encrypted / decrypted string.
	std::string createTargetCharPair ( const MatrixPoint& point1, const MatrixPoint& point2, const CryptoDirection& direction ) const ;

};

#endif /* ENCRYPTIONMATRIX_H_ */
