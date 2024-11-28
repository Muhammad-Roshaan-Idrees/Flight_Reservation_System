#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Sub Inspector Class
class SubInspector {
public:
    string name;
    string password;

    SubInspector(string n, string p) : name(n), password(p) {}
    void editCase() {
        string caseId, newDescription;
        cout << "Enter Case ID to edit: ";
        cin >> caseId;

        ifstream caseFile("cases.txt");
        ofstream tempFile("temp.txt");
        string line;
        bool found = false;

        if (caseFile.is_open() && tempFile.is_open()) {
            while (getline(caseFile, line)) {
                if (line.find(caseId) == 0) {
                    found = true;
                    cout << "Enter new case description: ";
                    cin.ignore();
                    getline(cin, newDescription);
                    size_t pos = line.rfind(","); // Find last comma
                    line = line.substr(0, pos) + "," + newDescription; // Replace description
                }
                tempFile << line << endl;
            }
            caseFile.close();
            tempFile.close();
            if (found) {
                remove("cases.txt");
                rename("temp.txt", "cases.txt");
                cout << "Case updated successfully.\n";
            } else {
                cout << "Case ID not found.\n";
                remove("temp.txt");
            }
        }
    }

    void trackCaseStatus(const string& caseId) {
        ifstream resolvedFile("resolved.txt"), deniedFile("denial.txt");
        string line;
        bool found = false;

        while (getline(resolvedFile, line)) {
            if (line.find(caseId) != string::npos) {
                cout << "Status: Approved\nDetails: " << line << endl;
                found = true;
                break;
            }
        }
        resolvedFile.close();

        if (!found) {
            while (getline(deniedFile, line)) {
                if (line.find(caseId) != string::npos) {
                    cout << "Status: Denied\nDetails: " << line << endl;
                    found = true;
                    break;
                }
            }
        }
        deniedFile.close();

        if (!found) cout << "Status: Pending\n";
    }
    void searchCase(const string& query) {
        ifstream caseFile("cases.txt");
        string line;
        bool found = false;

        while (getline(caseFile, line)) {
            if (line.find(query) != string::npos) {
                cout << "Found Case: " << line << endl;
                found = true;
            }
        }
        caseFile.close();

        if (!found) cout << "No matching cases found.\n";
    }
    void generateReport() {
        ifstream caseFile("cases.txt"), resolvedFile("resolved.txt"), deniedFile("denial.txt");
        ofstream reportFile("report.txt");
        string line;

        reportFile << "Pending Cases:\n";
        while (getline(caseFile, line)) reportFile << line << endl;
        caseFile.close();

        reportFile << "\nApproved Cases:\n";
        while (getline(resolvedFile, line)) reportFile << line << endl;
        resolvedFile.close();

        reportFile << "\nDenied Cases:\n";
        while (getline(deniedFile, line)) reportFile << line << endl;
        deniedFile.close();

        reportFile.close();
        cout << "Report generated as report.txt.\n";
    }

    bool login(string inputName, string inputPassword) {
        return inputName == name && inputPassword == password;
    }

    void addCase() {
        string caseId, caseName, phone, cnic, description, signature;
        cout << "Enter Case ID: ";
        cin >> caseId;
        cout << "Enter Case Name: ";
        cin.ignore(); // to ignore any extra newlines
        getline(cin, caseName);
        cout << "Enter Phone Number (10 digits): ";
        cin >> phone;
        cout << "Enter CNIC (format: xxxxx-xxxxxxx-x): ";
        cin >> cnic;
        cout << "Enter Case Description: ";
        cin.ignore(); // to ignore any extra newlines
        getline(cin, description);
        cout << "Enter Signature: ";
        getline(cin, signature);

        // Save case to file
        ofstream caseFile("cases.txt", ios::app);
        if (caseFile.is_open()) {
            caseFile << caseId << "," << caseName << "," << phone << "," << cnic << "," << description << endl;
            caseFile.close();
            // Save signature to file
            ofstream sigFile("signature.txt", ios::app);
            if (sigFile.is_open()) {
                sigFile << "Case ID: " << caseId << " | Signature: " << signature << endl;
                sigFile.close();
            }
            cout << "Case added successfully and sent to SHO for approval.\n";
        } else {
            cout << "Error opening case file.\n";
        }
    }

    void viewDenialRecords() {
        ifstream denialFile("denial.txt");
        string line;
        cout << "Denied Cases:\n";
        if (denialFile.is_open()) {
            while (getline(denialFile, line)) {
                cout << line << endl;
            }
            denialFile.close();
        } else {
            cout << "No denied cases found.\n";
        }
    }

    void resendCase() {
        string caseId;
        cout << "Enter Case ID to resend: ";
        cin >> caseId;

        // Read the case from cases.txt and resend it to SHO
        // In real case, we'd add resend counter logic here

        cout << "Case " << caseId << " resent to SHO.\n";
    }
};

// SHO Class
class SHO {
public:
    string name;
    string password;

    SHO(string n, string p) : name(n), password(p) {}

    bool login(string inputName, string inputPassword) {
        return inputName == name && inputPassword == password;
    }
    //added new function
    void denyCase(int caseChoice) {
        ifstream caseFile("cases.txt");
        ofstream denialFile("denial.txt", ios::app);
        string line, comment;
        int caseNumber = 1;
        string deniedCase;

        if (caseFile.is_open() && denialFile.is_open()) {
            while (getline(caseFile, line)) {
                if (caseNumber == caseChoice) {
                    cout << "Enter comment for denial: ";
                    cin.ignore();
                    getline(cin, comment);
                    denialFile << line << " | Comment: " << comment << endl;
                    cout << "Case denied with comment.\n";
                    break;
                }
                caseNumber++;
            }
            caseFile.close();
            denialFile.close();
        }
    }

    
    void viewAndApproveCases() {
        ifstream caseFile("cases.txt");
        string line;
        cout << "Pending Cases:\n";
        if (caseFile.is_open()) {
            int caseNumber = 1;
            while (getline(caseFile, line)) {
                cout << "Case " << caseNumber++ << ": " << line << endl;
            }
            caseFile.close();

            // Approve or Deny
            int caseChoice;
            cout << "Enter the case number to approve/deny: ";
            cin >> caseChoice;
            char decision;
            cout << "Approve or Deny (A/D): ";
            cin >> decision;

            // Handle case approval or denial
            if (decision == 'A' || decision == 'a') {
                approveCase(caseChoice);
            } else if (decision == 'D' || decision == 'd') {
                denyCase(caseChoice);
            } else {
                cout << "Invalid choice. Try again.\n";
            }
        } else {
            cout << "No pending cases found.\n";
        }
    }

    void approveCase(int caseChoice) {
        ifstream caseFile("cases.txt");
        string line;
        int caseNumber = 1;
        string approvedCase;
        if (caseFile.is_open()) {
            while (getline(caseFile, line)) {
                if (caseNumber == caseChoice) {
                    approvedCase = line;
                    break;
                }
                caseNumber++;
            }
            caseFile.close();

            if (!approvedCase.empty()) {
                // Save the approved case to the resolved file
                ofstream resolvedFile("resolved.txt", ios::app);
                if (resolvedFile.is_open()) {
                    resolvedFile << approvedCase << endl;
                    resolvedFile.close();

                    // Remove case from pending file (or mark as resolved)
                    cout << "Case approved and moved to resolved cases.\n";
                }
            }
        }
    }

    void denyCase(int caseChoice) {
        ifstream caseFile("cases.txt");
        string line;
        int caseNumber = 1;
        string deniedCase;
        if (caseFile.is_open()) {
            while (getline(caseFile, line)) {
                if (caseNumber == caseChoice) {
                    deniedCase = line;
                    break;
                }
                caseNumber++;
            }
            caseFile.close();

            if (!deniedCase.empty()) {
                // Save the denied case to the denial file
                ofstream denialFile("denial.txt", ios::app);
                if (denialFile.is_open()) {
                    denialFile << deniedCase << endl;
                    denialFile.close();

                    // Remove case from pending file (or mark as denied)
                    cout << "Case denied and moved to denied cases.\n";
                }
            }
        }
    }

    void viewApprovedCases() {
        ifstream resolvedFile("resolved.txt");
        string line;
        cout << "Approved Cases:\n";
        if (resolvedFile.is_open()) {
            while (getline(resolvedFile, line)) {
                cout << line << endl;
            }
            resolvedFile.close();
        } else {
            cout << "No approved cases found.\n";
        }
    }

    void viewDeniedCases() {
        ifstream denialFile("denial.txt");
        string line;
        cout << "Denied Cases:\n";
        if (denialFile.is_open()) {
            while (getline(denialFile, line)) {
                cout << line << endl;
            }
            denialFile.close();
        } else {
            cout << "No denied cases found.\n";
        }
    }
};

// Function to display the contents of a text file
void displayFileContent(const string &filename) {
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
}

int main() {
    SubInspector si("John", "sub123");
    SHO sho("Doe", "sho123");

    // Display the contents of the welcome.txt file
    displayFileContent("welcome.txt");

    while (true) {
        cout << "Login as:\n1. Sub Inspector\n2. SHO\n3. Exit\nChoose an option: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string name, pass;
            cout << "Enter Sub Inspector Name: ";
            cin >> name;
            cout << "Enter Password: ";
            cin >> pass;
            if (si.login(name, pass)) {
                while (true) {
                    cout << "Sub Inspector Menu:\n1. Add Case\n2. View Denied Cases\n3. Resend Case\n4. Logout\nChoose an option: ";
                    int siChoice;
                    cin >> siChoice;
                    if (siChoice == 1) si.addCase();
                    else if (siChoice == 2) si.viewDenialRecords();
                    else if (siChoice == 3) si.resendCase();
                    else break; // Logout
                }
            } else {
                cout << "Invalid Name or Password.\n";
            }
        } else if (choice == 2) {
            string name, pass;
            cout << "Enter SHO Name: ";
            cin >> name;
            cout << "Enter Password: ";
            cin >> pass;

            if (sho.login(name, pass)) {
                while (true) {
                    cout << "SHO Menu:\n1. View and Approve/Deny Cases\n2. View Approved Cases\n3. View Denied Cases\n4. Logout\nChoose an option: ";
                    int shoChoice;
                    cin >> shoChoice;

                    if (shoChoice == 1) {
                        sho.viewAndApproveCases();
                    } else if (shoChoice == 2) {
                        sho.viewApprovedCases();
                    } else if (shoChoice == 3) {
                        sho.viewDeniedCases();
                    } else if (shoChoice == 4) {
                        break; // Logout
                    } else {
                        cout << "Invalid option. Try again.\n";
                    }
                }
            } else {
                cout << "Invalid Name or Password.\n";
            }
        } else if (choice == 3) {
            // Display the contents of the exit.txt file
            displayFileContent("exit.txt");
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}