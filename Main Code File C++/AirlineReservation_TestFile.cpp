#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

// Structs for user, flight, and booking
struct User {
    string name, username, password, phone, address;
    unordered_map<string, int> bookings; // flightID -> seat number
};

struct Flight {
    string flightID, source, destination, departureTime, arrivalTime;
    int totalSeats, price;
    queue<int> availableSeats; // Queue of available seat numbers
};

unordered_map<string, User> users;
unordered_map<string, Flight> flights;
unordered_map<string, string> admins; // admin username -> password

// Function declarations
void loadUsers();
void loadFlights();
void loadAdmins();
void saveUsers();
void saveFlights();
void saveAdmins();
void displayWelcome();
void displayExitMessage();
bool userLogin(string &username);
bool adminLogin();
void registerUser();
void adminMenu();
void userMenu(const string &username);
void bookSeat(const string &username);
void cancelSeat(const string &username);
void viewBookings(const string &username);
void viewFlightSeats(const string &flightID);
void saveFlights();

// Function to load users from the file
void loadUsers() {
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, username, password, phone, address;
        getline(ss, name, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, phone, ',');
        getline(ss, address);
        users[username] = {name, username, password, phone, address};
    }
    file.close();
}

// Function to load flights from the file
void loadFlights() {
    ifstream file("flights.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string flightID, source, destination, departureTime, arrivalTime;
        int totalSeats, price;
        ss >> flightID >> source >> destination >> departureTime >> arrivalTime >> totalSeats >> price;
        Flight flight = {flightID, source, destination, departureTime, arrivalTime, totalSeats, price};

        // Add all seats to available seats queue
        for (int i = 1; i <= totalSeats; ++i) {
            flight.availableSeats.push(i);
        }

        flights[flightID] = flight;
    }
    file.close();
}

// Function to load admins from the file
void loadAdmins() {
    ifstream file("admins.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, password;
        getline(ss, username, ',');
        getline(ss, password);
        admins[username] = password;
    }
    file.close();
}

// Function to save users to the file
void saveUsers() {
    ofstream file("users.txt");
    for (const auto &user : users) {
        file << user.second.name << "," << user.second.username << ","
             << user.second.password << "," << user.second.phone << ","
             << user.second.address << endl;
    }
    file.close();
}

// Function to save flights to the file
void saveFlights() {
    ofstream file("flights.txt");
    for (const auto &flight : flights) {
        file << flight.second.flightID << "," << flight.second.source << ","
             << flight.second.destination << "," << flight.second.departureTime << ","
             << flight.second.arrivalTime << "," << flight.second.totalSeats << ","
             << flight.second.price;

        // Create a temporary copy of the availableSeats queue
        queue<int> tempQueue = flight.second.availableSeats;

        // Save available seats
        while (!tempQueue.empty()) {
            file << "," << tempQueue.front();
            tempQueue.pop();
        }
        file << endl;
    }
    file.close();
}

// Function to save admins to the file
void saveAdmins() {
    ofstream file("admins.txt");
    for (const auto &admin : admins) {
        file << admin.first << "," << admin.second << endl;
    }
    file.close();
}

// Function to display the welcome message
void displayWelcome() {
    ifstream file("welcome.txt");
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

// Function to display the exit message
void displayExitMessage() {
    ifstream file("exit.txt");
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

// Function for user login
bool userLogin(string &username) {
    string enteredUsername, enteredPassword;
    cout << "Enter Username: ";
    cin >> enteredUsername;
    cout << "Enter Password: ";
    cin >> enteredPassword;

    if (users.find(enteredUsername) != users.end() && users[enteredUsername].password == enteredPassword) {
        username = enteredUsername;
        return true;
    }
    cout << "Invalid username or password.\n";
    return false;
}

// Function for admin login
bool adminLogin() {
    string enteredUsername, enteredPassword;
    cout << "Enter Admin Username: ";
    cin >> enteredUsername;
    cout << "Enter Admin Password: ";
    cin >> enteredPassword;

    if (admins.find(enteredUsername) != admins.end() && admins[enteredUsername] == enteredPassword) {
        return true;
    }
    cout << "Invalid admin username or password.\n";
    return false;
}

// Function to register a new user
void registerUser() {
    string name, username, password, phone, address;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter phone number: ";
    cin >> phone;
    cout << "Enter address: ";
    cin.ignore();
    getline(cin, address);

    User newUser = {name, username, password, phone, address};
    users[username] = newUser;
    saveUsers(); // Save updated user data to file
    cout << "User registered successfully.\n";
}

// Admin menu
void adminMenu() {
    int choice;
    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Flight\n";
        cout << "2. View Users\n";
        cout << "3. Add Admin\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string flightID, source, destination, departureTime, arrivalTime;
                int totalSeats, price;
                cout << "Enter Flight ID: ";
                cin >> flightID;
                cout << "Enter Source: ";
                cin >> source;
                cout << "Enter Destination: ";
                cin >> destination;
                cout << "Enter Departure Time: ";
                cin >> departureTime;
                cout << "Enter Arrival Time: ";
                cin >> arrivalTime;
                cout << "Enter Total Seats: ";
                cin >> totalSeats;
                cout << "Enter Price: ";
                cin >> price;

                Flight newFlight = {flightID, source, destination, departureTime, arrivalTime, totalSeats, price};

                // Add all seats to available seats queue
                for (int i = 1; i <= totalSeats; ++i) {
                    newFlight.availableSeats.push(i);
                }

                flights[flightID] = newFlight;
                saveFlights(); // Save updated flight data to file
                cout << "Flight added successfully.\n";
                break;
            }
            case 2:
                // View all users
                for (const auto& user : users) {
                    cout << "User: " << user.first << ", Name: " << user.second.name << endl;
                }
                break;
            case 3: {
                // Add new admin
                string adminUsername, adminPassword;
                cout << "Enter Admin Username: ";
                cin >> adminUsername;
                cout << "Enter Admin Password: ";
                cin >> adminPassword;

                admins[adminUsername] = adminPassword;
                saveAdmins(); // Save updated admin data to file
                cout << "New admin added successfully.\n";
                break;
            }
            case 4:
                cout << "Exiting Admin menu.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

// User menu
void userMenu(const string& username) {
    int choice;
    do {
        cout << "\n--- User Menu ---\n";
        cout << "1. View Bookings\n";
        cout << "2. Book a Seat\n";
        cout << "3. Cancel a Booking\n";
        cout << "4. View Flight Seats\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewBookings(username);
                break;
            case 2:
                bookSeat(username);
                break;
            case 3:
                cancelSeat(username);
                break;
            case 4: {
                string flightID;
                cout << "Enter flight ID to view seats: ";
                cin >> flightID;
                viewFlightSeats(flightID);
                break;
            }
case 5:
                cout << "Exiting User menu.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);
}

// Function to view the bookings of a user
void viewBookings(const string &username) {
    if (users[username].bookings.empty()) {
        cout << "No bookings found for this user.\n";
        return;
    }

    cout << "Your bookings:\n";
    for (const auto &booking : users[username].bookings) {
        cout << "Flight ID: " << booking.first << ", Seat Number: " << booking.second << endl;
    }
}

// Function to book a seat for the user
void bookSeat(const string &username) {
    string flightID;
    cout << "Enter Flight ID: ";
    cin >> flightID;

    if (flights.find(flightID) == flights.end()) {
        cout << "Flight ID not found.\n";
        return;
    }

    if (flights[flightID].availableSeats.empty()) {
        cout << "No available seats on this flight.\n";
        return;
    }

    // Assign the first available seat
    int seatNumber = flights[flightID].availableSeats.front();
    flights[flightID].availableSeats.pop();

    // Save the booking
    users[username].bookings[flightID] = seatNumber;
    cout << "Seat " << seatNumber << " booked successfully on flight " << flightID << ".\n";

    saveFlights(); // Save updated flight data to file
    saveUsers();   // Save updated user data to file
}

// Function to cancel a seat booking
void cancelSeat(const string &username) {
    string flightID;
    cout << "Enter Flight ID: ";
    cin >> flightID;

    if (users[username].bookings.find(flightID) == users[username].bookings.end()) {
        cout << "No booking found for this flight.\n";
        return;
    }

    // Retrieve the seat number and push it back to the available seats
    int seatNumber = users[username].bookings[flightID];
    flights[flightID].availableSeats.push(seatNumber);

    // Remove the booking from the user's bookings
    users[username].bookings.erase(flightID);
    cout << "Booking on flight " << flightID << " canceled successfully.\n";

    saveFlights(); // Save updated flight data to file
    saveUsers();   // Save updated user data to file
}

// Function to view available seats for a specific flight
void viewFlightSeats(const string &flightID) {
    if (flights.find(flightID) == flights.end()) {
        cout << "Flight ID not found.\n";
        return;
    }

    cout << "Available seats for flight " << flightID << ":\n";
    queue<int> tempQueue = flights[flightID].availableSeats;
    if (tempQueue.empty()) {
        cout << "No available seats.\n";
        return;
    }

    while (!tempQueue.empty()) {
        cout << "Seat " << tempQueue.front() << endl;
        tempQueue.pop();
    }
}

// Main program entry point
int main() {
    // Load data from files
    loadUsers();
    loadFlights();
    loadAdmins();

    displayWelcome();

    int choice;
    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Login as User\n";
        cout << "2. Login as Admin\n";
        cout << "3. Register as New User\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        string username;

        switch (choice) {
            case 1:
                if (userLogin(username)) {
                    userMenu(username);
                }
                break;
            case 2:
                if (adminLogin()) {
                    adminMenu();
                }
                break;
            case 3:
                registerUser();
                break;
            case 4:
                cout << "Exiting program.\n";
                displayExitMessage();
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}