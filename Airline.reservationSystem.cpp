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
class AirlineSystem
{
private:
    vector<Flight> flights;
    map<string, User> users;
    map<string, vector<pair<string, string>>> bookings; // Flight ID -> (username, seat class)
    vector<pair<string, string>> adminNotifications;    // Pending approvals (flightID, username)
    string currentUser;
    string adminUsername = "admin";
    string adminPassword = "admin";

public:
    AirlineSystem()
    {
        // Example Flights
        flights.emplace_back("F001", "New York", "10:00 AM", "International", 10, 20, 15, 5);
        flights.emplace_back("F002", "London", "2:00 PM", "International", 8, 18, 12, 4);
    }

    // Admin Functions
    bool adminLogin(const string &username, const string &password)
    {
        if (username == adminUsername && password == adminPassword)
        {
            cout << "Admin Login Successful!" << endl;
            return true;
        }
        cout << "Invalid Admin Credentials!" << endl;
        return false;
    }

    void viewAdminNotifications()
    {
        if (adminNotifications.empty())
        {
            cout << "No pending notifications." << endl;
            return;
        }

        for (size_t i = 0; i < adminNotifications.size(); ++i)
        {
            auto &notif = adminNotifications[i];
            cout << i + 1 << ". Approve booking for User: " << notif.second
                 << " on Flight: " << notif.first << "? (Y/N): ";
            char decision;
            cin >> decision;
            if (decision == 'Y' || decision == 'y')
            {
                users[notif.second].notifications.push_back("Your booking for flight " + notif.first + " has been approved.");
                cout << "Booking approved." << endl;
            }
            else
            {
                // Revert the seat deduction if the booking is rejected
                auto &flightSeats = find_if(flights.begin(), flights.end(), [&notif](const Flight &flight)
                                            { return flight.flightID == notif.first; })
                                        ->seats;

                if (notif.second == "Business")
                    flightSeats["Business"]++;
                if (notif.second == "Economy")
                    flightSeats["Economy"]++;
                if (notif.second == "Standard")
                    flightSeats["Standard"]++;
                if (notif.second == "VIP")
                    flightSeats["VIP"]++;

                bookings[notif.first].erase(remove_if(bookings[notif.first].begin(), bookings[notif.first].end(),
                                                      [&notif](const auto &pair)
                                                      { return pair.first == notif.second; }),
                                            bookings[notif.first].end());
                users[notif.second].notifications.push_back("Your booking for flight " + notif.first + " has been rejected.");
                cout << "Booking rejected and removed." << endl;
            }
        }
        adminNotifications.clear();
    }
 void deleteFlight()
    {
        string flightID;
        cout << "Enter the Flight ID to delete: ";
        cin >> flightID;

        auto it = find_if(flights.begin(), flights.end(), [&flightID](const Flight &flight)
                          { return flight.flightID == flightID; });

        if (it != flights.end())
        {
            // Clear all bookings for this flight
            bookings.erase(flightID);

            // Remove the flight from the flights list
            flights.erase(it);

            // Notify users about flight cancellation
            for (auto &user : users)
            {
                user.second.notifications.push_back("Flight " + flightID + " has been canceled.");
            }

            cout << "Flight " << flightID << " has been successfully deleted." << endl;
        }
        else
        {
            cout << "Flight not found!" << endl;
        }
    }

    // Add Flight with Duplicate ID Check
    void addFlight()
    {
        string flightID, destination, departureTime, type;
        int business, economy, standard, vip;

        cout << "Enter Flight ID: ";
        cin >> flightID;

        // Check if flight with the same ID already exists
        auto it = find_if(flights.begin(), flights.end(), [&flightID](const Flight &flight)
                          { return flight.flightID == flightID; });
        if (it != flights.end())
        {
            cout << "Flight with this ID already exists!" << endl;
            return;
        }

        cout << "Enter Destination: ";
        cin.ignore();
        getline(cin, destination);
        cout << "Enter Departure Time: ";
        getline(cin, departureTime);
        cout << "Enter Type (National/International): ";
        getline(cin, type);

        cout << "Enter Available Seats for Business, Economy, Standard, and VIP classes: ";
        cin >> business >> economy >> standard >> vip;

        flights.emplace_back(flightID, destination, departureTime, type, business, economy, standard, vip);
        cout << "Flight added successfully!" << endl;
    }

    // User Functions
    bool login(const string &username, const string &password)
    {
        if (users.find(username) != users.end() && users[username].password == password)
        {
            currentUser = username;
            cout << "Login successful! Welcome, " << users[currentUser].fullName << endl;
            return true;
        }
        cout << "Invalid credentials!" << endl;
        return false;
    }

    bool isUsernameUnique(const string &username) {
    return users.find(username) == users.end();  // Checks if the username is already taken
}

bool isValidUsername(const string &username) {
    return username.length() >= 4;  // Username must be at least 4 characters long
}

bool isValidPassword(const string &password) {
    return password.length() >= 6;  // Password must be at least 6 characters long
}

bool isValidPhoneNumber(const string &phoneNumber) {
    return regex_match(phoneNumber, regex(R"(\d{11})"));  // Validates a 11-digit phone number
}

bool isValidEmail(const string &email) {
    return regex_match(email, regex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})"));  // Simple email format validation
}

bool isValidCNIC(const string &cnic) {
    return regex_match(cnic, regex(R"(\d{5}-\d{7}-\d)"));  // Validates CNIC format e.g., 12345-1234567-1
}

bool isValidPostalCode(const string &postalCode) {
    return regex_match(postalCode, regex(R"(\d{5})"));  // Validates postal code format e.g., 12345
}

bool isValidAge(int age) {
    return age >= 18 && age <= 100;  // Age should be between 18 and 100
}
void signup() {
    string username, password, fullName, phoneNumber, cnic, address, postalCode, country, email, city, province, gender;
    int age;

    // Collect user details
    cout << "Enter Username: ";
    cin >> username;

    if (!isValidUsername(username)) {
        cout << "Username must be at least 4 characters long.\n";
        return;
    }

    if (!isUsernameUnique(username)) {
        cout << "Username already exists. Please choose a different one.\n";
        return;
    }

    cout << "Enter Password: ";
    cin >> password;

    if (!isValidPassword(password)) {
        cout << "Password must be at least 6 characters long.\n";
        return;
    }

    cout << "Enter Full Name: ";
    cin.ignore();
    getline(cin, fullName);

    cout << "Enter Phone Number: ";
    getline(cin, phoneNumber);

    if (!isValidPhoneNumber(phoneNumber)) {
        cout << "Invalid phone number. It should be 11 digits long.\n";
        return;
    }

    cout << "Enter CNIC: ";
    getline(cin, cnic);

    if (!isValidCNIC(cnic)) {
        cout << "Invalid CNIC format. It should be in the format 12345-1234567-1.\n";
        return;
    }

    cout << "Enter Address: ";
    getline(cin, address);

    cout << "Enter Postal Code: ";
    getline(cin, postalCode);

    if (!isValidPostalCode(postalCode)) {
        cout << "Invalid postal code. It should be 5 digits long.\n";
        return;
    }

    cout << "Enter Country: ";
    getline(cin, country);

    cout << "Enter Email: ";
    getline(cin, email);

    if (!isValidEmail(email)) {
        cout << "Invalid email format.\n";
        return;
    }

    cout << "Enter City: ";
    getline(cin, city);

    cout << "Enter Province: ";
    getline(cin, province);

    cout << "Enter Gender: ";
    getline(cin, gender);

    cout << "Enter Age: ";
    cin >> age;

    if (!isValidAge(age)) {
        cout << "Age must be between 18 and 100.\n";
        return;
    }

    // Create and store the user
    users[username] = User(username, password, fullName, phoneNumber, cnic, address, postalCode, country, email, city, province, gender, age);
    cout << "Signup successful!" << endl;
}


void viewFlights() const
{
    for (const auto &flight : flights)
    {
        flight.displayFlight();
    }
}

void bookFlight()
{
    string flightID, seatClass;
    cout << "Enter Flight ID to book: ";
    cin >> flightID;
    cout << "Choose Seat Class (Business, Economy, Standard, VIP): ";
    cin >> seatClass;

    for (auto &flight : flights)
    {
        if (flight.flightID == flightID)
        {
            if (flight.seats[seatClass] > 0)
            {
                flight.seats[seatClass]--;
                bookings[flightID].emplace_back(currentUser, seatClass);
                adminNotifications.emplace_back(flightID, currentUser);
                cout << "Booking successful! Waiting for admin approval." << endl;
                return;
            }
            else
            {
                cout << "No seats available in " << seatClass << " class." << endl;
                return;
            }
        }
    }
    cout << "Flight not found!" << endl;
}

void viewNotifications()
{
    users[currentUser].viewNotifications();
}
};
int main()
{
    AirlineSystem system;
    while (true)
    {
        cout << "\n1. Login (User)\n2. Signup\n3. Admin Panel\n0. Exit\nChoose: ";
        int choice;
        cin >> choice;
        if (choice == 0)
            break;

        switch (choice)
        {
        case 1:
        {
            string username, password;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            if (system.login(username, password))
            {
                while (true)
                {
                    cout << "\n1. View Flights\n2. Book Flight\n3. View Notifications\n0. Logout\nChoose: ";
                    int userChoice;
                    cin >> userChoice;
                    if (userChoice == 0)
                        break;
                    if (userChoice == 1)
                        system.viewFlights();
                    else if (userChoice == 2)
                        system.bookFlight();
                    else if (userChoice == 3)
                        system.viewNotifications();
                    else
                        cout << "Invalid choice!" << endl;
                }
            }
            break;
        }
        case 2:
            system.signup();
            break;
        case 3:
        {
            string username, password;
            cout << "Admin Username: ";
            cin >> username;
            cout << "Admin Password: ";
            cin >> password;
            if (system.adminLogin(username, password))
            {
                while (true)
                {
                    cout << "\n1. Add Flight\n2. Delete Flight\n3. View Notifications\n0. Logout\nChoose: ";
                    int adminChoice;
                    cin >> adminChoice;
                    if (adminChoice == 0)
                        break;
                    if (adminChoice == 1)
                        system.addFlight();
                    else if (adminChoice == 2)
                        system.deleteFlight();
                    else if (adminChoice == 3)
                        system.viewAdminNotifications();
                    else
                        cout << "Invalid choice!" << endl;
                }
            }
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}