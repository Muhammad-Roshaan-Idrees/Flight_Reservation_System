//added some validation check portion
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

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
