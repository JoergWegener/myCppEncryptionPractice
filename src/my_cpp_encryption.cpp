//============================================================================
// Name        : my_cpp_encryption.cpp
// Author      : joergw
// Version     :
// Copyright   : Your copyright notice
// Description : Swap encryption from my school days, slightly enhanced
//============================================================================

#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <cctype>
#include "EncryptionMatrix.h"
#include "my_cpp_encryption.h"
using namespace std;


string          passphrase = "";
string          inputText  = "";
CryptoDirection direction;


int
main( int argc, char** argv ) {

	// Command line argument processing (if applicable)
	if ( argc != 0 ) {
		if ( !processArgs( argc, argv ) ) {
			return -1; // Failure :(
		}
	} else {
		// No command line => interactive.
		bool isPassphraseOK = false;

		// Main process: read a clear text, encrypt it, return it.
		do {
			passphrase = getPassphrase( "" );
			isPassphraseOK = checkPassphrase( passphrase );
		} while ( !isPassphraseOK );

		inputText = getInputtext( "" );

		direction = getDirection( "" );

	}

	// Conversion (encryption or decryption) and printout in one step
	printResultText( convertString( passphrase, inputText, direction ) );
	return 0;

}


// Read a string from the console. NOTE: This could be
// changed in a later version to allow a GUI input.
string
getPassphrase ( const string& commandlineText ) {

		bool isStringOk = false;
		string s = "";

		if ( commandlineText == "" ) {
			cout << "Please enter the passphrase:" << endl;
			do {
				getline(cin, s);
				isStringOk = checkStringContent(s);
			} while ( !isStringOk );

		} else {
			s = commandlineText;
		}

		// Remove spaces and convert to upper case
		s.erase( remove( s.begin(), s.end(), ' ' ), s.end() ); // Remove spaces
		for ( unsigned int i = 0; i < s.length(); i++ ) {
			s[i] = toupper( s[i] );
		}

		return s;
}


// Read the direction. Convert to the proper data type
// "Direction" means whether to encrypt or decrypt.
CryptoDirection
getDirection( const string& commandlineText ) {

	string s = "";
	char c; // first character of the string

	if ( commandlineText == "" ) {

		cout << "Please enter the direction: 'E' for encryption, 'D' for decryption:";

		do {
			getline( cin, s );
			c = s[0];
		} while ( (c != 'D') && (c != 'd') && (c != 'E') && (c != 'e') );

	} else {
		s = commandlineText;
	}

	if ( s[0] == 'D' || s[0] == 'd')
		return DECRYPT;
	else
		return ENCRYPT;
}


// Read input text; check that only characters, space, and numbers are used.
// Repeat until input is correct.
string
getInputtext ( const string& commandlineText ) {

	bool isStringOk = false;
	string s = "";

	if ( commandlineText == "" ) {

		cout << "Please enter the input text:" << endl;

		do {
			getline( cin, s );
			isStringOk = checkStringContent( s );
		} while ( !isStringOk );

	} else {
		s = commandlineText;
	}

	// Replace ÃŸ before conversion (otherwise it will not work)
	string newS = "";
	for ( unsigned int i = 0; i < s.length(); i++ ) {
		if ( s[i] == 'ß')
			newS += "SS";
		else if ( toupper( s[i] ) == 'Ã' )
			newS += "AE";
		else if ( toupper( s[i] ) == 'Ö' )
			newS += "OE";
		else if ( toupper( s[i] ) == 'Ü' )
			newS += "UE";
		else if ( s[i] != ' ' )// spaces are ignored, all other characters are simply capitalized
			newS += toupper( s[i] );
	}
	return newS;
}


// Check the passphrase. The only rule in our algorithm is
// that no character may appear more than once.
bool
checkPassphrase( const string& passphrase ) {

	for ( unsigned int i = 0; i < passphrase.length()-1; i++ ) {
		for ( unsigned int j = i+1; j < passphrase.length(); j++ ) {
			if ( passphrase[ i ] == passphrase[ j ] ) {
				cout << "The passphrase must contain each character a maximum of one time." << endl;
				return false;
			}
		}
	}

	return true;
}


// Encryption functionality
string
convertString( const string& passphrase, const string& inputText, const CryptoDirection& direction ) {
    if ( direction == ENCRYPT )
      	cout << "Text to be encrypted:" << endl << inputText << endl;
    else
       	cout << "Text to be decrypted:" << endl << inputText << endl;

    EncryptionMatrix myMatrix( passphrase );
    return myMatrix.convertText( inputText, direction );
}


// Output. Note that this could be changed to provide the output in a GUI.
void
printResultText( const string& outputText ) {
	string temp = outputText;
	cout << "Result Text:" << endl;

	// Output in chunks of 5 characters separated by space; if not enough left, the rest will be printed.
	while ( temp.length() >= 5 ){
		cout << temp. substr( 0, 5 ) << " ";
		temp = temp.substr( 5 );
	}
	cout << temp << endl;
}


// Only characters, numbers and space allowed in passphrases and cleartexts.
// Check this and provide a hint to the user if violated.
bool
checkStringContent( const string& str ) {
    if ( str == "" ) {
       	cout << "Please enter at least one character or number!" << endl;
        return false;
    }
    for ( unsigned int i = 0; i < str.length(); i++ ) {
    	// Acceptable chars are a-zA-Z0-9 und Space
    	string acceptableChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890 ";
    	// Error if we find characters that are NOT allowed.
    	if ( str.find_first_not_of( acceptableChars ) != string::npos) {
           	cout << "Please only use characters and numbers. No symbols or Umlauts allowed." << endl;
            return false;
        }
    }
    return true;
}


// If called from the command line the first three arguments must be passphrase, direction and
// inputtext. If all is fine, we use this one.
// Return TRUE if successful, so we can decrypt and print the result.
bool
processArgs( int argc, char** argv ) {
	if ( argc != 3 ) {
		// Wrong call
		printCommandLineUserhelp();
		return false;
	}

	if ( checkStringContent( argv[ 0 ] ) && checkPassphrase( argv[ 0 ] ) ) {
		passphrase = getPassphrase( argv[0] );
	} else {
		printCommandLineUserhelp();
		return false;
	}
	if ( ( argv[1][0] == 'D' ) ||
		 ( argv[1][0] == 'd' ) ||
		 ( argv[1][0] == 'E' ) ||
		 ( argv[1][0] == 'e' ) ) {
		direction  = getDirection( argv[1] );
	} else {
		printCommandLineUserhelp();
		return false;
	}
	inputText  = getInputtext( argv[2] );
	return true;
}


// Standard user help for command line access.
void
printCommandLineUserhelp( ) {
	cout << "Wrong call! Please call the program like that:" << endl;
	cout << "java EncryptionMain <passphrase> <direction> <inputtext>" << endl;
	cout << "where <direction> is D for decryption or E for encryption." << endl;
	cout << "Also note that you have to use \" in case of text with spaces!" << endl;
}


