/*hash.h*/

//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Spring 2020
// 
// Lab Week 11: hashing of dates and lottery numbers (SOLUTION)
// 

#include <string>

using namespace std;

bool isNumeric(string s);
int hashStationID(string ID, int N);
int hashTripID(string tripID, int N);
int hashStationAbbrev(string Abbrev, int N);
int hashBikeID(string bikeid, int N);
