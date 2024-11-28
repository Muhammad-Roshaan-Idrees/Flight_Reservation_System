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
class User {
public:
    string username, password, fullName, phoneNumber, cnic, address, postalCode, country, email, city, province, gender;
    int age;
    vector<string> notifications;

    User() = default;

    User(string user, string pass, string name, string phone, string id, string addr, string postal, string cnt,
         string mail, string cty, string prov, string gend, int ag)
        : username(user), password(pass), fullName(name), phoneNumber(phone), cnic(id), address(addr), postalCode(postal),
          country(cnt), email(mail), city(cty), province(prov), gender(gend), age(ag) {}

    void displayProfile() const {
        cout << "Name: " << fullName << ", Email: " << email << ", Phone: " << phoneNumber
             << ", CNIC: " << cnic << ", Country: " << country << ", City: " << city
             << ", Province: " << province << ", Gender: " << gender << ", Age: " << age << endl;
    }

    void viewNotifications() const {
        if (notifications.empty()) {
            cout << "No notifications." << endl;
        } else {
            cout << "Notifications:" << endl;
            for (const auto& note : notifications) {
                cout << "- " << note << endl;
            }
        }
    }
};
class AirlineSystem {
private:
    vector<Flight> flights;
    map<string, User> users;
    map<string, vector<pair<string, string>>> bookings; // Flight ID -> (username, seat class)
    vector<pair<string, string>> adminNotifications;    // Pending approvals (flightID, username)
    string currentUser;
    string adminUsername = "admin";
    string adminPassword = "admin";

public:
    AirlineSystem() {
        // Example Flights
        flights.emplace_back("F001", "New York", "10:00 AM", "International", 10, 20, 15, 5);
        flights.emplace_back("F002", "London", "2:00 PM", "International", 8, 18, 12, 4);
    }