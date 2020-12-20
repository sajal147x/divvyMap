//
// Name: Sajal Gupta
// U. of Illinois, Chicago
// CS 251: Spring 2020
// 

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#include "hash.h"
#include "hashmap.h"
#include "util.h"
using namespace std;


struct stationData
{
    string ID;
    string Abbrev;
    string FullName;
    string Latitude;
    string Longitude;
    string Capacity;
    string OnlineDate;
   stationData()
   {
       ID = "";
       Abbrev = "";
       FullName = "";
       Latitude = "";
       Longitude = "";
       Capacity = "";
       OnlineDate = "";
   }
};
//--------------------------------------------------------------------------------------------------------------------
struct tripData
{
    string TripID;
    string StartTime;
    string StopTime;
    string BikeID;
    string Duration;
    string From;
    string To;
    string Identifiers;
    string BirthYear;
    tripData()
    {
        TripID = "";
        StartTime = "";
        StopTime = "";
        BikeID = "";
        Duration = "";
        From = "";
        To = "";
        Identifiers = "";
        BirthYear = "";
    }
};
//--------------------------------------------------------------------------------------------------------------------
int string2int(string s)
{
	if (s == "")
		return 0;
	else
		return stoi(s);
}
//--------------------------------------------------------------------------------------------------------------------
bool inputTripDataByTripID(string filename, hashmap<string, tripData>& tripsByID, hashmap<string, int>& tripsByBikeID){
    ifstream infile(filename);
    if (!infile.good())
	{
		cout << "**Error: unable to open '" << filename << "'..." << endl;
		return false;
	}
    string line;
	getline(infile, line);  // input and discard first row --- header row
	int count = 0;
	int usageCount = 0;
	int bikecount = 0;
	while (getline(infile, line))
    {
        stringstream s(line);
        string tripID, startTime, stopTime, bikeID, duration, to, from, identifiers, birthYear;
        getline(s, tripID, ',');
        getline(s, startTime, ',');
        getline(s, stopTime, ',');
        getline(s, bikeID, ',');
        getline(s, duration, ',');
        getline(s, from, ',');
        getline(s, to, ',');
        getline(s, identifiers, ',');
        getline(s, birthYear, ',');
        tripData td;
        td.TripID = tripID;
        td.StartTime = startTime;
        td.StopTime = stopTime;
        td.BikeID = bikeID;
        td.Duration = duration;
        td.From = from;
        td.To = to;
        td.Identifiers = identifiers;
        td.BirthYear = birthYear;
        tripsByID.insert(tripID, td, hashTripID);
        count++;
        bool found = tripsByBikeID.search(bikeID, usageCount, hashBikeID);
        if (!found){
            usageCount = 1;
            tripsByBikeID.insert(bikeID, usageCount, hashBikeID);
            bikecount++;
        }
        else{
            usageCount++;
            tripsByBikeID.insert(bikeID, usageCount, hashBikeID);
        }
    }
    cout<<"# of trips: "<<count<<endl;
    cout<<"# of bikes: "<<bikecount<<endl;
    return true;
}
//--------------------------------------------------------------------------------------------------------------------
bool inputStationDataByID(string filename, hashmap<string, stationData>& stationsByID, hashmap<string, stationData>& stationsByAbbrev)
{
    ifstream infile(filename);
    
	
	if (!infile.good())
	{
		cout << "**Error: unable to open '" << filename << "'..." << endl;
		return false;
	}
    string line;
	
	getline(infile, line);  // input and discard first row --- header row
	
	int count = 0;
	
	while (getline(infile, line))
    {
        stringstream s(line);
        string id, abbrev, fullname, latitude, longitude, capacity, onlineDate;
        getline(s, id, ',');
        getline(s, abbrev, ',');
        getline(s, fullname, ',');
        getline(s, latitude, ',');
        getline(s, longitude, ',');
        getline(s, capacity, ',');
        getline(s, onlineDate, ',');
        stationData sd;
        sd.ID = id;
        sd.Abbrev = abbrev;
        sd.FullName = fullname;
        sd.Latitude = latitude;
        sd.Longitude = longitude;
        sd.Capacity = capacity;
        sd.OnlineDate = onlineDate;
        stationsByID.insert(id, sd, hashStationID);
        stationsByAbbrev.insert(abbrev, sd, hashStationAbbrev);
        count++;
    }
    cout<<"# of stations: "<<count<<endl;
    return true;
}

//--------------------------------------------------------------------------------------------------------------------
string getDuration(string dur){
    int totalSeconds = stoi(dur);
    int totalHours = totalSeconds/3600;
    int totalMinutes = totalSeconds/60;
    if (totalHours == 0){
        if (totalMinutes == 0){
            return dur + " seconds";
        }
        else{
            return (to_string(totalMinutes)+" minutes, "+to_string(totalSeconds%60)+" seconds");
        }
    }
    else{
        return (to_string(totalHours) + " hours, "+
                to_string(totalMinutes%60)+" minutes, "
                +to_string(totalSeconds%3600)+" seconds");
    }
}
//--------------------------------------------------------------------------------------------------------------------
int main()
{
    cout<<"** DIVVY analysis program **"<<endl<<endl;
    const int N = 10000;
    const int N2 = 2500000;
    const int N3 = 50000;
    hashmap<string, stationData> stationsByID(N);
    hashmap<string, tripData> tripsByID(N2);
    hashmap<string, stationData> stationsByAbbrev(N);
    hashmap<string, int> tripsByBikeID(N3);
    vector<string> mapKeys;
    vector<string> tripKeys;
    stationData sd;
    tripData td;
    string userInput, userInput2;
    cout<<"Enter stations file> ";
    cin>>userInput;
    cout<<"Enter trips file> ";
    cin>>userInput2;
    cout<<endl<<"Reading "<<userInput<<endl<<"Reading "<<userInput2<<endl<<endl;
    
    bool success = inputStationDataByID(userInput, stationsByID, stationsByAbbrev);
    if (!success)
	{
        cout << "No data, file not found?" << endl;
		return 0;
	}
    bool success2 = inputTripDataByTripID(userInput2, tripsByID, tripsByBikeID);
    if (!success2)
	{
        cout << "No data, file not found?" << endl;
		return 0;
	}
    mapKeys = stationsByID.getKeys(mapKeys);
    tripKeys = tripsByID.getKeys(tripKeys);
    string command;
    cout<<endl<<"Please enter a command, help, or #> ";
    cin>>command;
    while(command!="#"){
        if (command=="#"){
            return 0;
        }
        if (command == "help"){
            cout<<"Available commands:"<<endl;
            cout<<" Enter a station id (e.g. 341)"<<endl;
            cout<<" Enter a station abbreviation (e.g. Adler)"<<endl;
            cout<<" Enter a trip id (e.g. Tr10426561)"<<endl;
            cout<<" Enter a bike id (e.g. B5218)"<<endl;
            cout<<" Nearby station (e.g. nearby 41.86 -87.62 0.5)"<<endl;
            cout<<" Similar trips (e.g. similar Tr10424639 0.3)"<<endl<<endl;
            cout<<"Please enter a command, help, or #> ";
            cin>>command;
        }
        //Command 1
        else if(isNumeric(command)){
            bool found = stationsByID.search(command, sd, hashStationID);
            if (!found){
                cout<<"Station not found"<<endl<<endl;
                cout<<"Please enter a command, help, or #> ";
                cin>>command;
            }
            else{
                cout<<"Station:"<<endl;
                cout<<" ID: "<<command<<endl;
                cout<<" Abbrev: "<<sd.Abbrev<<endl;
                cout<<" Fullname: "<<sd.FullName<<endl;
                cout<<" Location: ("<<stod(sd.Latitude)<<", "<<stod(sd.Longitude)<<")"<<endl;
                cout<<" Capacity: "<<sd.Capacity<<endl;
                cout<<" Online date: "<<sd.OnlineDate<<endl<<endl;
                cout<<"Please enter a command, help, or #> ";
                cin>>command;
            }
        }
        //command 3
        else if(command.substr(0,2)=="Tr"){
            bool found = tripsByID.search(command, td, hashTripID);
            if (!found){
                cout<<"Trip not found"<<endl<<endl;
                cout<<"Please enter a command, help, or #> ";
                cin>>command;
            }
            else{
                stationData sdTo, sdFrom;
                stationsByID.search(td.From, sdFrom, hashStationID);
                stationsByID.search(td.To, sdTo, hashStationID);
                cout<<"Trip:"<<endl;
                cout<<" ID: "<<command<<endl;
                cout<<" Starttime: "<<td.StartTime<<endl;
                cout<<" Bikeid: "<<td.BikeID<<endl;
                cout<<" Duration: "<<getDuration(td.Duration)<<endl;
                cout<<" From station: "<<sdFrom.Abbrev<<" ("<<td.From<<")"<<endl;
                cout<<" To station: "<<sdTo.Abbrev<<" ("<<td.To<<")"<<endl;
                cout<<" Rider identifies as: "<<td.Identifiers<<endl;
                cout<<" Birthyear: "<<td.BirthYear<<endl<<endl;
                cout<<"Please enter a command, help, or #> ";
                cin>>command;
            }
        }
        //command 4
        else if(command[0] == 'B' && (isNumeric(command.substr(1,1))==true)){
            int usage;
            bool found = tripsByBikeID.search(command, usage, hashBikeID);
            if (!found){
                cout<<"Bike not found"<<endl<<endl;
                cout<<"Please enter a command, help, or #> ";
                cin>>command;
            }
            else{
                cout<<"Bike: "<<endl;
                cout<<" ID: "<<command<<endl;
                cout<<" Usage: "<<usage<<endl<<endl;
                cout<<"Please enter a command, help, or #> ";
                cin>>command;
            }
          }
        //command 5
        else if(command == "nearby"){
            string lat, lon;
            string Distance;
            double lat1, lon1, userDistance, lat2, lon2;
            bool isNearby = false;
            multimap<double, string> nearbyStations;
            cin>>lat;
            cin>>lon;
            lat1 = stod(lat);
            lon1 = stod(lon);
            cin>>Distance;
            userDistance = stod(Distance);
            for (unsigned int i = 0; i < mapKeys.size(); i++){
                bool found = stationsByID.search(mapKeys[i], sd, hashStationID);
                if (found){
                    lat2 = stod(sd.Latitude);
                    lon2 = stod(sd.Longitude);
                    if (distBetween2Points(lat1, lon1, lat2, lon2)<=userDistance){
                        nearbyStations.insert(pair<double, string>(distBetween2Points(lat1, lon1, lat2, lon2),mapKeys.at(i)));
                        isNearby = true;
                }
                }
            }
            multimap<double, string>::iterator j;
            cout<<"Stations within "<<Distance<<" miles of ("<<lat<<", "<<lon<<")"<<endl;
            if (isNearby == false){
                cout<<" none found"<<endl<<endl;
                cout<<"Please enter a command, help, or #> ";
                cin>>command;
            }
            else{
                for (j = nearbyStations.begin(); j != nearbyStations.end(); j++){
                    cout<<" Station "<<j->second<<": ";
                    cout<<j->first<<" miles"<<endl;
                }
                cout<<endl;
                cout<<"Please enter a command, help, or #> ";
                cin>>command;
            }
        }
        //command 6
        else if(command == "similar")
        {
            string usertripID;
            string userdistance, fromID, toID;
            double userDistance, lat, lon, userStartLat, userStartLon, userEndLat, userEndLon;
            
            int tripCount = 0;
            cin>>usertripID;
            cin>>userdistance;
            userDistance = stod(userdistance);
            set <int> S;
            set <int> D;
            cout<<"Trips that follow a similar path (+/-"<<userdistance<<" miles) as "<<usertripID<<endl;
            bool findTrip = tripsByID.search(usertripID, td, hashTripID);
            if (findTrip == true){
                fromID = td.From;
                toID = td.To;
                stationsByID.search(fromID, sd, hashStationID);
                userStartLat = stod(sd.Latitude);
                userStartLon = stod(sd.Longitude);
                for (unsigned int i = 0; i < mapKeys.size(); i++){
                    if (stationsByID.search(mapKeys[i], sd, hashStationID)){
                        lat = stod(sd.Latitude);
                        lon = stod(sd.Longitude);
                    }
                    if(distBetween2Points(userStartLat, userStartLon, lat, lon)<=userDistance){
                        S.insert(stoi(mapKeys[i]));
                    }
                }
                stationsByID.search(toID, sd, hashStationID);
                userEndLat = stod(sd.Latitude);
                userEndLon = stod(sd.Longitude);
                for (unsigned int i = 0; i < mapKeys.size(); i++){
                    if (stationsByID.search(mapKeys[i], sd, hashStationID)){
                        lat = stod(sd.Latitude);
                        lon = stod(sd.Longitude);
                    }
                    if(distBetween2Points(userEndLat, userEndLon, lat, lon)<=userDistance){
                        D.insert(stoi(mapKeys[i]));
                    }
                }
            
            
                for (unsigned int i = 0; i < tripKeys.size();i++){
                    tripsByID.search(tripKeys[i], td, hashTripID);
                    if (S.count(stoi(td.From)) > 0 && D.count(stoi(td.To))>0){
                        tripCount++;
                    }
                }
            
                cout<<" nearby starting points: ";
                for (int e:S){
                    cout<<e<<" ";
                }
                cout<<endl;
                cout<<" nearby ending points: ";
                for (int e:D){
                    cout<<e<<" ";
            }
                cout<<endl;
                cout<<" trip count: "<<tripCount<<endl<<endl;
                cout<<"Please enter a command, help, or #> ";
                cin>>command;
            }
            else{
                cout<<" no such trip"<<endl<<endl;
                cout<<"Please enter a command, help, or #> ";
                cin>>command;
            }
        }
        //command2
        else{
            string cmd2, userAbbrev;
            getline(cin, cmd2);
            userAbbrev = command + cmd2;
            stationData sd;
            bool found = stationsByAbbrev.search(userAbbrev, sd, hashStationAbbrev);
            if (!found){
                cout<<"Station not found"<<endl<<endl;
                cout<<"Please enter a command, help, or #> ";
                cin>>command;
        }
            else{
                cout<<"Station:"<<endl;
                cout<<" ID: "<<sd.ID<<endl;
                cout<<" Abbrev: "<<userAbbrev<<endl;
                cout<<" Fullname: "<<sd.FullName<<endl;
                cout<<" Location: ("<<stod(sd.Latitude)<<", "<<stod(sd.Longitude)<<")"<<endl;
                cout<<" Capacity: "<<sd.Capacity<<endl;
                cout<<" Online date: "<<sd.OnlineDate<<endl<<endl;
                cout<<"Please enter a command, help, or #> ";
                cin>>command;
            }
        }
        }
        
    return 0;
    
}