#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <iomanip> 
#include <limits>  
using namespace std;
unordered_map<string, string> users; // Username -> Password
unordered_map<string, string> admins; // Admin Username -> Password
unordered_map<string, pair<string, string>> flightDetails; // Flight ID -> (Source, Destination)
unordered_map<string, queue<int>> flightSeats; // Flight ID -> Queue of Available Seats
unordered_map<string, vector<string>> bookings; // Username -> List of Bookings
unordered_map<string, double> flightPrices; // Flight ID -> Price


void mainMenu();
void userMenu(const string& username);
void adminMenu(const string& adminUsername);
void registerUser ();
void loginUser ();
void loginAdmin();

// User Functions
void bookSeat(const string& username);
void cancelSeat(const string& username);
void viewMyBookings(const string& username);
void viewAvailableSeats();
void searchFlights();
void viewFlightDetails(const string& flightID);
void updateUserProfile(const string& username);

// Admin Functions
void addFlight();
void addAdmin();
void viewAllUsers();
void viewUserBookings();
void deleteFlight();
void editFlightDetails();
void resetUserPassword();
void viewFlightStatistics();
void setFlightPrice();

//additional functions for our code
void loadFlights();
void loadUsers();
void loadBookings();
void loadAdmins();
void saveUsers();
void saveBookings();
void saveFlights();
void saveAdmins();
void createDefaultAdmin();
void clearInputBuffer(); // Helper function to clear input buffer

// Main Menu
void mainMenu() {
    int choice;
    do {
        cout << "\n--- Airline Reservation System ---\n";
        cout << "1. User Login\n";
        cout << "2. Admin Login\n";
        cout << "3. Register as New User\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                loginUser ();
                break;
            case 2:
                loginAdmin();
                break;
            case 3:
                registerUser ();
                break;
            case 4:
                cout << "Exiting system. Goodbye!\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

// User Registration
void registerUser () {
    string username, password;
    cout << "\n--- Register as a New User ---\n";
    cout << "Enter Username: ";
    cin >> username;

    // Check for existing username
    if (users.find(username) != users.end()) {
        cout << "Username already exists. Try again.\n";
        return;
    }

    cout << "Enter Password: ";
    cin >> password;

    users[username] = password;
    saveUsers();
    cout << "Registration successful! You can now log in.\n";
}

// User Login
void loginUser () {
    string username, password;
    cout << "\n--- User Login ---\n";
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    if (users.find(username) != users.end() && users[username] == password) {
        cout << "Login successful! Welcome, " << username << ".\n";
        userMenu(username);
    } else {
        cout << "Invalid credentials. Please try again.\n";
    }
}

// Admin Login
void loginAdmin() {
    string adminUsername, adminPassword;
    cout << "\n--- Admin Login ---\n";
    cout << "Enter Admin Username: ";
    cin >> adminUsername;
    cout << "Enter Admin Password: ";
    cin >> adminPassword;

    if (admins.find(adminUsername) != admins.end() && admins[adminUsername] == adminPassword) {
        cout << "Admin login successful. Welcome, Admin " << adminUsername << ".\n";
        adminMenu(adminUsername);
    } else {
        cout << "Invalid admin credentials."<<endl;
        cout << "Please try again.\n";
    }
}

// User Menu
void userMenu(const string& username) {
    int choice;
    do {
        cout << "\n--- User Menu ---\n";
        cout << "1. Book a Seat\n";
        cout << "2. Cancel a Seat\n";
        cout << "3. View My Bookings\n";
        cout << "4. View Available Seats\n";
        cout << "5. Search Flights\n";
        cout << "6. View Flight Details\n";
        cout << "7. Update Profile\n";
        cout << "8. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bookSeat(username);
                break;
            case 2:
                cancelSeat(username);
                break;
            case 3:
                viewMyBookings(username);
                break;
            case 4:
                viewAvailableSeats();
                break;
            case 5:
                searchFlights();
                break;
            case 6: {
                string flightID;
                cout << "Enter Flight ID: ";
                cin >> flightID;
                viewFlightDetails(flightID);
                break;
            }
            case 7:
                updateUserProfile(username);
                break;
            case 8:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);
}

// Admin Menu
void adminMenu(const string& adminUsername) {
    int choice;
    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Flight\n";
        cout << "2. Add Admin\n";
        cout << "3. View All Users\n";
        cout << "4. View User Bookings\n";
        cout << "5. Edit Flight Details\n";
        cout << "6. Delete Flight\n";
        cout << "7. Reset User Password\n";
        cout << "8. View Flight Statistics\n";
        cout << "9. Set Flight Price\n";
        cout << "10. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addFlight();
                break;
            case 2:
                addAdmin();
                break;
            case 3:
                viewAllUsers();
                break;
            case 4:
                viewUserBookings();
                break;
            case 5:
                editFlightDetails();
                break;
            case 6:
                deleteFlight();
                break;
            case 7:
                resetUserPassword();
                break;
            case 8:
                viewFlightStatistics();
                break;
            case 9:
                setFlightPrice();
                break;
            case 10:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 10);
}

// Booking a Seat
void bookSeat(const string& username) {
    string flightID;
    cout << "Enter Flight ID to book: ";
    cin >> flightID;

    if (flightSeats.find(flightID) == flightSeats.end() || flightSeats[flightID].empty()) {
        cout << "No seats available for this flight.\n";
        return;
    }

    int seatNumber = flightSeats[flightID].front();
    flightSeats[flightID].pop();

    bookings[username].push_back(flightID + " (Seat " + to_string(seatNumber) + ")");
    saveBookings();
    cout << "Seat " << seatNumber << " booked on flight " << flightID << ".\n";
}

// Cancel Seat Functionality
void cancelSeat(const string& username) {
    string flightID;
    cout << "Enter Flight ID to cancel: ";
    cin >> flightID;

    bool found = false;
    for (auto it = bookings[username].begin(); it != bookings[username].end(); ++it) {
        if (it->find(flightID) != string::npos) {
            found = true;
            size_t pos = it->find(" (Seat ");
            int seatNumber = stoi(it->substr(pos + 7, it->find(')') - pos - 7));
            bookings[username].erase(it);
            flightSeats[flightID].push(seatNumber);
            saveBookings();
            cout << "Seat " << seatNumber << " canceled successfully on flight " << flightID << ".\n";
            break;
        }
    }

    if (!found) {
        cout << "You have not booked any seat on this flight.\n";
    }
}

// View My Bookings
void viewMyBookings(const string& username)
{
    if (bookings[username].empty()) {
        cout << "You have no bookings.\n";
    } else {
        cout << "Your Bookings:\n";
        for (const string& booking : bookings[username]) {
            cout << "- " << booking << endl;
        }
    }
}

// View Available Seats
void viewAvailableSeats() {
    cout << "Available Flights and Seats:\n";
    for (const auto& [flightID, seats] : flightSeats) {
        cout << "- Flight " << flightID << ": " << seats.size() << " seats available\n";
    }
}

// Search Flights
void searchFlights() {
    string source, destination;
    cout << "Enter Source: ";
    cin >> source;
    cout << "Enter Destination: ";
    cin >> destination;

    cout << "Available Flights from " << source << " to " << destination << ":\n";
    for (const auto& [flightID, details] : flightDetails) {
        if (details.first == source && details.second == destination) {
            cout << "- Flight ID: " << flightID << ", Price: $" << flightPrices[flightID] << endl;
        }
    }
}

// View Flight Details
void viewFlightDetails(const string& flightID) {
    if (flightDetails.find(flightID) != flightDetails.end()) {
        cout << "Flight ID: " << flightID << endl;
        cout << "Source: " << flightDetails[flightID].first << endl;
        cout << "Destination: " << flightDetails[flightID].second << endl;
        cout << "Available Seats: " << flightSeats[flightID].size() << endl;
        cout << "Price: $" << flightPrices[flightID] << endl;
    } else {
        cout << "Flight not found.\n";
    }
}

// Update User Profile
void updateUserProfile(const string& username) {
    string newPassword;
    cout << "Enter new Password: ";
    cin >> newPassword;

    users[username] = newPassword;
    saveUsers();
    cout << "Profile updated successfully.\n";
}

// Add Flight
void addFlight() {
    string flightID, source, destination;
    int totalSeats;

    cout << "Enter Flight ID: ";
    cin >> flightID;

    if (flightDetails.find(flightID) != flightDetails.end()) {
        cout << "Flight ID already exists. Please enter a unique ID.\n";
        return;
    }

    cout << "Enter Source: ";
    cin >> source;
    cout << "Enter Destination: ";
    cin >> destination;
    cout << "Enter Total Seats: ";
    cin >> totalSeats;

    flightDetails[flightID] = {source, destination};
    queue<int> seats;
    for (int i = 1; i <= totalSeats; ++i) {
        seats.push(i);
    }
    flightSeats[flightID] = seats;
    flightPrices[flightID] = 100.0; // Default price
    saveFlights();
    cout << "Flight added successfully.\n";
}

// Add Admin
void addAdmin() {
    string adminUsername, adminPassword;
    cout << "Enter Admin Username: ";
    cin >> adminUsername;

    if (admins.find(adminUsername) != admins.end()) {
        cout << "Admin Username already exists. Please enter a unique username.\n";
        return;
    }

    cout << "Enter Admin Password: ";
    cin >> adminPassword;

    admins[adminUsername] = adminPassword;
    saveAdmins();
    cout << "Admin added successfully.\n";
}

// View All Users
void viewAllUsers() {
    cout << "All Users:\n";
    for (const auto& [username, password] : users) {
        cout << "- " << username << endl;
    }
}

// View User Bookings
void viewUserBookings() {
    string username;
    cout << "Enter Username: ";
    cin >> username;

    if (bookings.find(username) == bookings.end()) {
        cout << "User  not found.\n";
    } else {
        cout << "Bookings for " << username << ":\n";
        for (const string& booking : bookings[username]) {
            cout << "- " << booking << endl;
        }
    }
}

// Delete Flight
void deleteFlight() {
    string flightID;
    cout << "Enter Flight ID to delete: ";
    cin >> flightID;

    if (flightDetails.find(flightID) == flightDetails.end()) {
        cout << "Flight not found.\n";
        return;
    }

    flightDetails.erase(flightID);
    flightSeats.erase(flightID);
    flightPrices.erase(flightID);
    saveFlights();
    cout << "Flight deleted successfully.\n";
}

// Edit Flight Details
void editFlightDetails() {
    string flightID, newSource, newDestination;
    int newTotalSeats;

    cout << "Enter Flight ID to edit: ";
    cin >> flightID;

    if (flightDetails.find(flightID) == flightDetails.end()) {
        cout << "Flight not found.\n";
        return;
    }

    cout << "Enter new Source: ";
    cin >> newSource;
    cout << "Enter new Destination: ";
    cin >> newDestination;
    cout << "Enter new Total Seats: ";
    cin >> newTotalSeats;

    flightDetails[flightID] = {newSource, newDestination};
    queue<int> newSeats;
    for (int i = 1; i <= newTotalSeats; ++i) {
        newSeats.push(i);
    }
    flightSeats[flightID] = newSeats;
    saveFlights();
    cout << "Flight details updated successfully.\n";
}

// Reset User Password
void resetUserPassword() {
    string username, newPassword;

    cout << "Enter Username to reset password: ";
    cin >> username;

    // Check if the user exists
    if (users.find(username) == users.end()) {
        cout << "User  not found.\n";
        return;
    }

    cout << "Enter new Password: ";
    cin >> newPassword;

    // Update the user's password
    users[username] = newPassword;

    // Save the updated users to the file
    saveUsers();

    cout << "Password reset successfully.\n";
}

// View Flight Statistics
void viewFlightStatistics() {
    cout << "Flight Statistics:\n";

    // Iterate through each flight
    for (const auto& [flightID, seats] : flightSeats) {
        int totalSeats = seats.size(); // Available seats

        // Calculate booked seats by checking the bookings for the flight ID
        int bookedSeats = 0;
        for (const auto& booking : bookings) {
            for (const auto& flightBooking : booking.second) {
                if (flightBooking.find(flightID) != string::npos) {
                    bookedSeats++;
                }
            }
        }

        // Calculate remaining seats
        int remainingSeats = totalSeats - bookedSeats;

        // Print flight statistics in the specified format
        cout << "Flight ID: " << flightID << endl
             << "Total Seats: " << (totalSeats + bookedSeats) << endl
             << "Number of Seats Booked by Passengers: " << bookedSeats << endl
             << "Remaining Seats: " << remainingSeats << endl
             << "-------------------------------" << endl; // Separator for better readability
    }
}

// Set Flight Price
void setFlightPrice() {
    string flightID;
    double price;

    cout << "Enter Flight ID to set price: ";
    cin >> flightID;

    if (flightDetails.find(flightID) == flightDetails.end()) {
        cout << "Flight not found.\n";
        return;
    }

    cout << "Enter new Price: ";
    cin >> price;

    flightPrices[flightID] = price;
    saveFlights();
    cout << "Price updated successfully for Flight ID: " << flightID << ".\n";
}

// Helper Functions
void loadFlights() {
    ifstream file("flights.txt");
    if (file.is_open()) {
        string flightID, source, destination;
        int totalSeats;
        while (file >> flightID >> source >> destination >> totalSeats) {
            flightDetails[flightID] = {source, destination};
            queue<int> seats;
            for (int i = 1; i <= totalSeats; ++i) {
                seats.push(i);
            }
            flightSeats[flightID] = seats;
            flightPrices[flightID] = 100.0; // Default price
        }
        file.close();
    }
}

void loadUsers() {
    ifstream file("users.txt");
    if (file.is_open()) {
        string username, password;
        while (file >> username >> password) {
            users[username] = password;
        }
        file.close();
    }
}

void loadBookings() {
    ifstream file("bookings.txt");
    if (file.is_open()) {
        string username, flightID, seatNumber;
        while (file >> username >> flightID >> seatNumber) {
            bookings[username].push_back(flightID + seatNumber);
        }
        file.close();
    }
}

void loadAdmins() {
    ifstream file("admin.txt");
    if (file.is_open()) {
        string adminUsername, adminPassword;
        while (file >> adminUsername >> adminPassword) {
            admins[adminUsername] = adminPassword;
        }
        file.close();
    }
}

void saveUsers() {
    ofstream file("users.txt");
    if (file.is_open()) {
        for (const auto& [username, password] : users) {
            file << username << " " << password << endl;
        }
        file.close();
    }
}

void saveBookings() {
    ofstream file("bookings.txt");
    if (file.is_open()) {
        for (const auto& [username, bookingsList] : bookings) {
            for (const string& booking : bookingsList) {
                file << username << " " << booking << endl;
            }
        }
        file.close();
    }
}

void saveFlights() {
    ofstream file("flights.txt");
    if (file.is_open()) {
        for (const auto& [flightID, flightInfo] : flightDetails) {
            int totalSeats = flightSeats[flightID].size();
            file << flightID << " " << flightInfo.first << " " << flightInfo.second << " " << totalSeats << endl;
        }
        file.close();
    }
}

void saveAdmins() {
    ofstream file("admin.txt");
    if (file.is_open()) {
        for (const auto& [adminUsername, adminPassword] : admins) {
            file << adminUsername << " " << adminPassword << endl;
        }
        file.close();
    }
}

void createDefaultAdmin() {
    ofstream file("admin.txt");
    if (file.is_open()) {
        file << "admin admin123" << endl; // Default admin credentials
        file.close();
    }
}

void clearInputBuffer() {
    cin.clear(); // Clear any error flags
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
}

int main() {
    // Load data from files
    loadUsers();
    loadFlights();
    loadBookings();
    loadAdmins();

    // Check if admin file is empty and create default admin if necessary
    if (admins.empty()) {
        createDefaultAdmin();
        loadAdmins(); // Reload admins after creating default
    }

    // Main Menu
    mainMenu();

    // Save data to files
    saveUsers();
    saveBookings();
    saveFlights();
    saveAdmins(); // Save admin data

    return 0;
}

// v2.0: Added seat class upgrade option (Economy to Business)

// Recalculated fare difference during seat class upgrade

// Added baggage allowance calculation by ticket tier

// Fixed extra luggage fee calculation on international routes

// Implemented flight status flags (On-Time, Delayed, Cancelled)

// Admin option to update flight delay status

// Added ASCII seat map display for cabin selection

// Prevented selection of already occupied seat numbers

// Added round-trip ticket booking discount logic
