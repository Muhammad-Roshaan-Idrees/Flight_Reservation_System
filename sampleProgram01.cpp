// Flight Resrvation System Project 
// Software Engineering
// 3rd Semester Bachelor of Science in Software Engineering


#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <windows.h>
#include <sstream>

using namespace std;

class Login {
private:
    string LoginID, Password;
public:
    Login() : LoginID(""), Password("") {}

    void setID(string id) { LoginID = id; }
    void setPW(string pw) { Password = pw; }

    string getID() { return LoginID; }
    string getPW() { return Password; }

    bool registration();
    bool login();
};

bool Login::registration() {
    system("cls");
    string id, pw;
    cout << "\tEnter Login ID: ";
    cin >> id;
    setID(id);

    start:
    cout << "\tEnter A Strong Password: ";
    cin >> pw;
    if (pw.length() >= 8) {
        setPW(pw);
    } else {
        cout << "\tEnter Minimum 8 Characters!" << endl;
        goto start;
    }

    ofstream outfile("Login.txt", ios::app);
    if (!outfile) {
        cout << "\tError: File Can't Open!" << endl;
        return false;
    } else {
        outfile << getID() << " : " << getPW() << endl;
        cout << "\tUser Registered Successfully!" << endl;
    }
    outfile.close();
    Sleep(3000);
    return true;
}

bool Login::login() {
    system("cls");
    string id, pw;
    cout << "\tEnter Login ID: ";
    cin >> id;

    cout << "\tEnter Password: ";
    cin >> pw;

    ifstream infile("Login.txt");
    if (!infile) {
        cout << "\tError: File Can't Open!" << endl;
        return false;
    } else {
        string line;
        bool found = false;
        while (getline(infile, line)) {
            stringstream ss(line);
            string userID, userPW;
            char delimiter;
            ss >> userID >> delimiter >> userPW;

            if (id == userID && pw == userPW) {
                found = true;
                cout << "\tPlease Wait";
                for (int i = 0; i < 3; i++) {
                    cout << ".";
                    Sleep(800);
                }
                system("cls");
                cout << "\tWelcome To This Page!" << endl;
                break;
            }
        }
        if (!found) {
            cout << "\tError: Incorrect Login ID Or Password!" << endl;
        }
    }
    infile.close();
    Sleep(5000);
    return true;
};


// Added some validation check portion

class Validations {
public:
    bool validateName(const string &name) {
        if (name.length() < 2 || name.length() > 50) return false;
        for (char ch : name) {
            if (!isalpha(ch) && !isspace(ch)) return false;
        }
        return true;
    }

    bool validatePassportNumber(const string &passportNumber) {
        if (passportNumber.length() != 9) return false;
        for (char ch : passportNumber) {
            if (!isalnum(ch)) return false;
        }
        return true;
    }

    bool validateAge(int age) {
        return age > 0 && age < 120;
    }

    bool validateFlightNumber(const string &flightNumber) {
        if (flightNumber.length() < 5 || flightNumber.length() > 6) return false;
        if (!isupper(flightNumber[0]) || !isupper(flightNumber[1])) return false;
        for (size_t i = 2; i < flightNumber.length(); ++i) {
            if (!isdigit(flightNumber[i])) return false;
        }
        return true;
    }

    bool validateDate(const string &date) {
        if (date.length() != 10 || date[2] != '-' || date[5] != '-') return false;
        for (size_t i = 0; i < date.length(); ++i) {
            if ((i != 2 && i != 5) && !isdigit(date[i])) return false;
        }
        return true;
    }

    bool validateEmail(const string &email) {
        size_t atPos = email.find('@');
        size_t dotPos = email.find('.', atPos);
        return (atPos != string::npos && dotPos != string::npos && dotPos > atPos);
    }

    bool validatePhoneNumber(const string &phoneNumber) {
        if (phoneNumber.length() < 10 || phoneNumber.length() > 15) return false;
        for (char ch : phoneNumber) {
            if (!isdigit(ch)) return false;
        }
        return true;
    }

    bool validateCreditCardNumber(const string &cardNumber) {
        int sum = 0;
        bool alternate = false;
        for (int i = cardNumber.length() - 1; i >= 0; --i) {
            int n = cardNumber[i] - '0';
            if (alternate) {
                n *= 2;
                if (n > 9) n -= 9;
            }
            sum += n;
            alternate = !alternate;
        }
        return (sum % 10==0);
    }
};

class Flight {
public:
    string flightNumber;
    string airline;
    string departureCity;
    string destinationCity;
    string departureDate;
    string departureTime;
    string arrivalTime;
    int duration;
    string aircraftType;
    int totalSeats;
    int availableSeats;
    double basePrice;
    string seatClasses[3];
    double seatPrices[3];
    string passengerList[100];
    int passengerCount;
    string flightStatus;

    Flight(string flightNum, string airlineName, string depCity, string destCity,
           string depDate, string depTime, string arrTime, int flightDuration,
           string aircraft, int seats, double price) {
        flightNumber = flightNum;
        airline = airlineName;
        departureCity = depCity;
        destinationCity = destCity;
        departureDate = depDate;
        departureTime = depTime;
        arrivalTime = arrTime;
        duration = flightDuration;
        aircraftType = aircraft;
        totalSeats = seats;
        availableSeats = seats;
        basePrice = price;
        passengerCount = 0;
        flightStatus = "On Time";

        seatClasses[0] = "Economy";
        seatClasses[1] = "Business";
        seatClasses[2] = "First Class";
        seatPrices[0] = basePrice;
        seatPrices[1] = basePrice * 2;
        seatPrices[2] = basePrice * 3;
    }

    // Book a seat for a passenger
    bool bookSeat(const string& passengerName) {
        if (availableSeats <= 0) {
            cout << "Flight is fully booked!" << endl;
            return false;
        }
        if (passengerCount < totalSeats) {
            passengerList[passengerCount] = passengerName;
            passengerCount++;
            availableSeats--;
            cout << "Seat booked for " << passengerName << " successfully!" << endl;
            return true;
        }
        return false;
    }

    // Cancel a booking
    bool cancelBooking(const string& passengerName) {
        for (int i = 0; i < passengerCount; i++) {
            if (passengerList[i] == passengerName) {
                // Shift remaining passengers up
                for (int j = i; j < passengerCount - 1; j++) {
                    passengerList[j] = passengerList[j + 1];
                }
                passengerList[passengerCount - 1] = ""; // Clear last entry
                passengerCount--;
                availableSeats++;
                cout << "Booking for " << passengerName << " canceled successfully!" << endl;
                return true;
            }
        }
        cout << "Passenger not found!" << endl;
        return false;
    }

    // Update flight status
    void updateStatus(const string& status) {
        flightStatus = status;
        cout << "Flight status updated to: " << status << endl;
    }
};


class Passenger {
public:
    string passengerID;
    string name;
    string contactNumber;
    string email;
    string seatNumber;
    string ticketClass;
    double ticketPrice;
    string specialRequest;

    Passenger() {}

    Passenger(string id, string passengerName, string contact, string emailAddress, 
              string seat, string tClass, double price, string request = "") {
        passengerID = id;
        name = passengerName;
        contactNumber = contact;
        email = emailAddress;
        seatNumber = seat;
        ticketClass = tClass;
        ticketPrice = price;
        specialRequest = request;
    }

    void displayPassengerDetails() {
        cout << "Passenger ID: " << passengerID << endl;
        cout << "Name: " << name << endl;
        cout << "Contact Number: " << contactNumber << endl;
        cout << "Email: " << email << endl;
        cout << "Seat Number: " << seatNumber << endl;
        cout << "Ticket Class: " << ticketClass << endl;
        cout << "Ticket Price: $" << ticketPrice << endl;
        if (!specialRequest.empty()) {
            cout << "Special Request: " << specialRequest << endl;
        } else {
            cout << "Special Request: None" << endl;
        }
    }

    void getInfoFromUser() {
        cout << "Enter Passenger ID: ";
        cin >> passengerID;
        cin.ignore(); // To clear the newline character from the buffer

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Contact Number: ";
        getline(cin, contactNumber);

        cout << "Enter Email: ";
        getline(cin, email);

        cout << "Enter Seat Number: ";
        getline(cin, seatNumber);

        cout << "Enter Ticket Class (Economy/Business/First): ";
        getline(cin, ticketClass);

        cout << "Enter Ticket Price: ";
        cin >> ticketPrice;
        cin.ignore();

        cout << "Enter Special Request (leave empty if none): ";
        getline(cin, specialRequest);
    }
};

class Ticket {
public:
    string ticketID;
    string flightNumber;
    string passengerID;
    string seatNumber;
    string ticketClass;
    double ticketPrice;
    string issueDate;
    string status;

    Ticket(string tID, string fNumber, string pID, string seat, string tClass, 
           double price, string date, string tStatus = "Confirmed") {
        ticketID = tID;
        flightNumber = fNumber;
        passengerID = pID;
        seatNumber = seat;
        ticketClass = tClass;
        ticketPrice = price;
        issueDate = date;
        status = tStatus;
    }

    void displayTicketDetails() {
        cout << "Ticket ID: " << ticketID << endl;
        cout << "Flight Number: " << flightNumber << endl;
        cout << "Passenger ID: " << passengerID << endl;
        cout << "Seat Number: " << seatNumber << endl;
        cout << "Ticket Class: " << ticketClass << endl;
        }
};

void displayMenu() {
    cout << "\nFlight Reservation System" << endl;
    cout << "1. Book Flight" << endl;
    cout << "2. Cancel Booking" << endl;
    cout << "3. Update Flight Status" << endl;
    cout << "4. View Passenger Details" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Login log;
    Validations validations;

    bool loggedIn = false;
    while (!loggedIn) {
        system("cls");
        int val;
        cout << "\tWelcome To Riphah International Airport\n";
        cout << "\t************************************\n";
        cout << "\t1. Register\n";
        cout << "\t2. Login\n";
        cout << "\t3. Exit\n";
        cout << "\tE2nter Choice: ";
        cin >> val;

        switch (val) {
            case 1:
                loggedIn = log.registration();
                break;
            case 2:
                loggedIn = log.login();
                break;
            case 3:
                system("cls");
                cout << "\tGood Luck!\n";
                Sleep(3000);
                exit(0);
            default:
                cout << "Invalid Option. Try Again!\n";
                Sleep(3000);
        }
    }

    // Sample flight data
    Flight flight("PK303", "Pakistan International Airlines", "Lahore", "Karachi",
                  "15-05-2024", "14:00", "16:00", 2, "Boeing 777", 100, 5000.0);

    int choice;
    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                // Book a flight
                string passengerName;
                cout << "Enter passenger's full name: ";
                cin.ignore();
                getline(cin, passengerName);
                if (flight.bookSeat(passengerName)) {
                    Passenger passenger;
                    passenger.getInfoFromUser();
                    Ticket ticket("T123", flight.flightNumber, passenger.passengerID, passenger.seatNumber,
                                  passenger.ticketClass, passenger.ticketPrice, "10-04-2024");
                    ticket.displayTicketDetails();
                }
                break;
            }
            case 2: {
                // Cancel booking
                string passengerName;
                cout << "Enter passenger's full name for cancellation: ";
                cin.ignore();
                getline(cin, passengerName);
                flight.cancelBooking(passengerName);
                break;
            }
            case 3: {
                // Update flight status
                string status;
                cout << "Enter new flight status: ";
                cin.ignore();
                getline(cin, status);
                flight.updateStatus(status);
                break;
            }
            case 4: {
                // View passenger details
                string passengerID;
                cout << "Enter passenger ID: ";
                cin.ignore();
                getline(cin, passengerID);
                // Simulate fetching and displaying passenger details
                Passenger passenger(passengerID, "John Doe", "1234567890", "john.doe@example.com", "12A",
                                    "Economy", 5000.0);
                passenger.displayPassengerDetails();
                break;
            }
            case 5:
                cout << "Thank you for using the Flight Reservation System. Goodbye!\n";
                Sleep(3000);
                return 0;
            default:
                cout << "Invalid option. Please try again.\n";
                Sleep(3000);
        }
    }

    return 0;
}


