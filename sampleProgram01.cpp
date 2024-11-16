// Flight Resrvation System Project 
// Software Engineering
// 3rd Semester Bachelor of Science in Software Engineering


#include <iostream>
#include <string>
#include <cctype>

using namespace std;

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
        return (sum % 10 == 0);
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
