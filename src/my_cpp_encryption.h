/*
 * my_cpp_encryption.h
 *
 *  Created on: 12.07.2014
 *      Author: joergw
 */

#ifndef MY_CPP_ENCRYPTION_H_
#define MY_CPP_ENCRYPTION_H_

#include "EncryptionMatrix.h"
using namespace std;

// Read a string from the console. NOTE: This could be
// changed in a later version to allow a GUI input.
string getPassphrase ( const string& commandlineText );


// "Direction" means whether to encrypt or decrypt.
CryptoDirection getDirection( const string& commandlineText );


// Read input text; check that only characters, space, and numbers are used.
// Repeat until input is correct.
string getInputtext ( const string& commandlineText );


// Check the passphrase. The only rule in our algorithm is
// that no character may appear more than once.
bool checkPassphrase( const string& passphrase );


// Encryption functionality
string convertString( const string& passphrase, const string& inputText, const CryptoDirection& direction );


// Output. Note that this could be changed to provide the output in a GUI.
void printResultText( const string& outputText );


// Only characters, numbers and space allowed in passphrases and cleartexts.
// Check this and provide a hint to the user if violated.
bool checkStringContent( const string& str );


// If called from the command line the first three arguments must be passphrase, direction and
// inputtext. If all is fine, we use this one.
// Return TRUE if successful, so we can decrypt and print the result.
bool processArgs( int argc, char** argv );


// Standard user help for command line access.
void printCommandLineUserhelp( );


#endif /* MY_CPP_ENCRYPTION_H_ */
