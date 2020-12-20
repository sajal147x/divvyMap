/*hash.cpp*/

//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Spring 2020

#include <iostream>
#include <string>
#include <cctype>  
#include <regex>  

#include "hash.h"

using namespace std;

//
// isNumeric
//
// Returns true if the given string is numeric (all digits), false
// if not.  If the string is empty, false is returned since there 
// are no digits present.
//
bool isNumeric(string s)
{
	//
	regex pattern("[[:d:]]+", regex::ECMAScript);

	smatch matchResults; 

	if (regex_match(s, matchResults, pattern))
		return true;
	else
		return false;
}
//-------------------------------------------------------------------------------------------------------------------
int hashStationID(string ID, int N){
    int index = stoi(ID);
    return index %N;
    
}
//-------------------------------------------------------------------------------------------------------------------
int hashStationAbbrev(string Abbrev, int N){
    unsigned long long index = 5381;
    for (char c : Abbrev)
    {
        index = ((index << 5)+index)+c;
    }
    return index % N;
    
}
//-------------------------------------------------------------------------------------------------------------------
int hashTripID(string tripID, int N){
    tripID.erase(0,2);
    return (stoi(tripID)%N);
    }

//-------------------------------------------------------------------------------------------------------------------
int hashBikeID(string BikeID, int N){
    BikeID.erase(0,1);
    int index = stoi(BikeID);
    return index;
}


