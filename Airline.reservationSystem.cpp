#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

// Flight Class
class Flight {
public:
    string flightID;
    string destination;
    string departureTime;
    string type;                   // National or International
    map<string, int> seats;        // Class -> Available Seats

    Flight(string id, string dest, string time, string flightType, int business, int economy, int standard, int vip)
        : flightID(id), destination(dest), departureTime(time), type(flightType) {
        seats["Business"] = business;
        seats["Economy"] = economy;
        seats["Standard"] = standard;
        seats["VIP"] = vip;
    }

    void displayFlight() const {
        cout << "Flight ID: " << flightID << ", Type: " << type << ", Destination: " << destination
             << ", Departure: " << departureTime << "\nAvailable Seats -> Business: " << seats.at("Business")
             << ", Economy: " << seats.at("Economy") << ", Standard: " << seats.at("Standard")
             << ", VIP: " << seats.at("VIP") << endl;
    }
};
