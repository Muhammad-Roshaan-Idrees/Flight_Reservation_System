#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

const int MAX_CRIMES = 100;
const int MAX_OFFENDERS = 50;

// Crime structure
struct Crime
{
    int id;
    string description;
    string location;
    string date;
};

// Offender structure
struct Offender
{
    int id;
    string name;
    int crimeCount;
    int committedCrimes[MAX_CRIMES];
};

Crime crimes[MAX_CRIMES];
int crimeCount = 0;
Offender offenders[MAX_OFFENDERS];
int offenderCount = 0;

// Generate Crime ID
int generatedCrimeId()
{
    static int nextID = 1;
    return nextID++;
}

// Generate Offender ID
int generatedOffenderId()
{
    static int nextID = 1;
    return nextID++;
}

// Add Crime
void addCrime()
{
    system("cls");
    if (crimeCount == MAX_CRIMES)
    {
        cout << "Crime Storage Full." << endl;
        return;
    }

    Crime crime;
    crime.id = generatedCrimeId();
    cout << "Enter crime description: ";
    cin.ignore();
    getline(cin, crime.description);
    cout << "Enter crime location: ";
    getline(cin, crime.location);
    cout << "Enter date of crime (YYYY-MM-DD): ";
    getline(cin, crime.date);
    crimes[crimeCount++] = crime;
    cout << "Crime added successfully!" << endl;
}

// Add Offender
void addOffender()
{
    system("cls");
    if (offenderCount == MAX_OFFENDERS)
    {
        cout << "Offender Storage Full." << endl;
        return;
    }

    Offender offender;
    offender.id = generatedOffenderId();
    cout << "Enter offender name: ";
    cin.ignore();
    getline(cin, offender.name);
    offender.crimeCount = 0;
    offenders[offenderCount++] = offender;
    cout << "Offender added successfully!" << endl;
}

// Update Crime
void updateCrime()
{
    system("cls");
    int crimeID;
    cout << "Enter Crime ID to update: ";
    cin >> crimeID;

    int crimeIndex = -1;
    for (int i = 0; i < crimeCount; i++)
    {
        if (crimes[i].id == crimeID)
        {
            crimeIndex = i;
            break;
        }
    }

    if (crimeIndex == -1)
    {
        cout << "Crime not found." << endl;
        return;
    }

    cout << "Updating Crime ID: " << crimes[crimeIndex].id << endl;
    cout << "Enter new crime description: ";
    cin.ignore();
    getline(cin, crimes[crimeIndex].description);
    cout << "Enter new crime location: ";
    getline(cin, crimes[crimeIndex].location);
    cout << "Enter new date of crime (YYYY-MM-DD): ";
    getline(cin, crimes[crimeIndex].date);
    cout << "Crime updated successfully!" << endl;
}

// Update Offender
void updateOffender()
{
    system("cls");
    int offenderID;
    cout << "Enter Offender ID to update: ";
    cin >> offenderID;

    int offenderIndex = -1;
    for (int i = 0; i < offenderCount; i++)
    {
        if (offenders[i].id == offenderID)
        {
            offenderIndex = i;
            break;
        }
    }

    if (offenderIndex == -1)
    {
        cout << "Offender not found." << endl;
        return;
    }

    cout << "Updating Offender ID: " << offenders[offenderIndex].id << endl;
    cout << "Enter new offender name: ";
    cin.ignore();
    getline(cin, offenders[offenderIndex].name);
    cout << "Offender updated successfully!" << endl;
}

// Display Crimes by Offender
void displayCrimesByOffender()
{
    system("cls");
    int offenderID;
    cout << "Enter Offender ID to view crimes: ";
    cin >> offenderID;

    int offenderIndex = -1;
    for (int i = 0; i < offenderCount; i++)
    {
        if (offenders[i].id == offenderID)
        {
            offenderIndex = i;
            break;
        }
    }

    if (offenderIndex == -1)
    {
        cout << "Offender not found!" << endl;
        return;
    }

    cout << "Crimes committed by Offender ID: " << offenders[offenderIndex].id << endl;
    for (int i = 0; i < offenders[offenderIndex].crimeCount; i++)
    {
        int crimeID = offenders[offenderIndex].committedCrimes[i];
        for (int j = 0; j < crimeCount; j++)
        {
            if (crimes[j].id == crimeID)
            {
                cout << "Crime ID: " << crimes[j].id << endl;
                cout << "Description: " << crimes[j].description << endl;
                cout << "Location: " << crimes[j].location << endl;
                cout << "Date: " << crimes[j].date << endl;
                cout << endl;
                break;
            }
        }
    }
}

// Count Crimes by Offender
void countCrimesByOffender()
{
    system("cls");
    int offenderID;
    cout << "Enter Offender ID to count crimes: ";
    cin >> offenderID;

    int offenderIndex = -1;
    for (int i = 0; i < offenderCount; i++)
    {
        if (offenders[i].id == offenderID)
        {
            offenderIndex = i;
            break;
        }
    }

    if (offenderIndex == -1)
    {
        cout << "Offender not found!" << endl;
        return;
    }

    cout << "Total crimes committed by Offender ID: " << offenders[offenderIndex].id
         << " is " << offenders[offenderIndex].crimeCount << endl;
}

// Search Crime by Date
void searchCrimeByDate()
{
    system("cls");
    if (crimeCount == 0)
    {
        cout << "No crimes recorded." << endl;
        return;
    }

    string searchDate;
    cout << "Enter the date of the crime to search (YYYY-MM-DD): ";
    cin.ignore();
    getline(cin, searchDate);

    bool crimeFound = false;

    for (int i = 0; i < crimeCount; i++)
    {
        if (crimes[i].date == searchDate)
        {
            cout << "\tCrime found!" << endl;
            cout << "\tCrime ID: " << crimes[i].id << endl;
            cout << "\tDescription: " << crimes[i].description << endl;
            cout << "\tLocation: " << crimes[i].location << endl;
            cout << "\tDate: " << crimes[i].date << endl;
            cout << endl;

            crimeFound = true;
        }
    }

    if (!crimeFound)
    {
        cout << "No crimes found for the date: " << searchDate << endl;
    }
}

// Sort Crimes
void sortCrimes()
{
    sort(crimes, crimes + crimeCount, [](const Crime &a, const Crime &b) {
        return a.description < b.description;
    });
    cout << "Crimes sorted by description!" << endl;
}

// Sort Offenders
void sortOffenders()
{
    sort(offenders, offenders + offenderCount, [](const Offender &a, const Offender &b) {
        return a.name < b.name;
    });
    cout << "Offenders sorted by name!" << endl;
}

// Display Statistics
void displayStatistics()
{
    cout << "Total Crimes Recorded: " << crimeCount << endl;
    cout << "Total Offenders Recorded: " << offenderCount << endl;
}

int main()
{
    string choice;
    do {
        cout << "\n\t\t ______________________________________________\n";
        cout << "\t\t|       |" << setw(40) << "|\n";
        cout << "\t\t| [1]   |     Add Crime" << setw(31) << "|\n";
        cout << "\t\t| [2]   |     Add Offender" << setw(27) << "|\n";
        cout << "\t\t| [3]   |     Update Crime" << setw(25) << "|\n";
        cout << "\t\t| [4]   |     Update Offender" << setw(21) << "|\n";
        cout << "\t\t| [5]   |     Record Crime by Offender" << setw(17) << "|\n";
        cout << "\t\t| [6]   |     Search Crime by Description" << setw(7) << "|\n";
        cout << "\t\t| [7]   |     Search Offender by Name" << setw(10) << "|\n";
        cout << "\t\t| [8]   |     Display All Crimes" << setw(18) << "|\n";
        cout << "\t\t| [9]   |     Display All Offenders" << setw(15) << "|\n";
        cout << "\t\t| [10]  |     Display Crimes by Offender" << setw(4) << "|\n";
        cout << "\t\t| [11]  |     Count Crimes by Offender" << setw(5) << "|\n";
        cout << "\t\t| [12]  |     Search Crime by Date" << setw(6) << "|\n";
        cout << "\t\t| [13]  |     Sort Crimes" << setw(16) << "|\n";
        cout << "\t\t| [14]  |     Sort Offenders" << setw(15) << "|\n";
        cout << "\t\t| [15]  |     Display Statistics" << setw(10) << "|\n";
        cout << "\t\t| [16]  |     Delete Crime Record" << setw(14) << "|\n";
        cout << "\t\t| [17]  |     Delete Offender Record" << setw(13) << "|\n";
        cout << "\t\t| [0]   |     Exit" << setw(31) << "|\n";
        cout << "\t\t|       |" << setw(40) << "|\n";
        cout << "\t\t|_______|______________________________________|\n";
        cout << "\n\t\tEnter your choice ... ";
        cin >> choice;

        if (choice == "1")
        {
            addCrime();
        }
        else if (choice == "2")
        {
            addOffender();
        }
        else if (choice == "3")
        {
            updateCrime();
        }
        else if (choice == "4")
        {
            updateOffender();
        }
        else if (choice == "5")
        {
            recordCrimeByOffender();
        }
        else if (choice == "6")
        {
            searchCrimeByDescription();
        }
        else if (choice == "7")
        {
            searchOffenderByName();
        }
        else if (choice == "8")
        {
            displayAllCrimes();
        }
        else if (choice == "9")
        {
            displayAllOffenders();
        }
        else if (choice == "10")
        {
            displayCrimesByOffender();
        }
        else if (choice == "11")
        {
            countCrimesByOffender();
        }
        else if (choice == "12")
        {
            searchCrimeByDate();
        }
        else if (choice == "13")
        {
            sortCrimes();
        }
        else if (choice == "14")
        {
            sortOffenders();
        }
        else if (choice == "15")
        {
            displayStatistics();
        }
        else if (choice == "16")
        {
            deleteCrime();
        }
        else if (choice == "17")
        {
            deleteOffender();
        }
        else if (choice == "0")
        {
            cout << "\n\n\t\tThanks for using this system\n\n" << endl;
        }
        else
        {
            system("cls");
            cout << "Invalid choice!" << endl;
        }

    } while (choice != "0");

    return 0;
}