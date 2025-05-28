#include <iostream>
#include <fstream>
using namespace std;

const int MAX = 100;

struct Appointment {
    string id, clientName, ic, email, sessionType;
    string counselor, date, time, duration, status, mode;
};

int convertDateToInt(const string& date) {
    // Expected format: DDMMYYYY (e.g., 01062025)
    if (date.length() != 8) return 0;
    int day = (date[0]-'0')*10 + (date[1]-'0');
    int month = (date[2]-'0')*10 + (date[3]-'0');
    int year = (date[4]-'0')*1000 + (date[5]-'0')*100 + (date[6]-'0')*10 + (date[7]-'0');
    return year * 10000 + month * 100 + day;
}

int convertStringToInt(const string& str) {
    int result = 0;
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
    }
    return result;
}

void swapAppointments(Appointment& a, Appointment& b) {
    Appointment temp = a;
    a = b;
    b = temp;
}

void cocktailSortByDate(Appointment arr[], int n, bool ascending) {
    bool swapped = true;
    int start = 0, end = n - 1;

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; ++i) {
            bool condition = ascending 
                             ? convertDateToInt(arr[i].date) > convertDateToInt(arr[i + 1].date)
                             : convertDateToInt(arr[i].date) < convertDateToInt(arr[i + 1].date);
            if (condition) {
                swapAppointments(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;
        swapped = false;
        --end;

        for (int i = end - 1; i >= start; --i) {
            bool condition = ascending 
                             ? convertDateToInt(arr[i].date) > convertDateToInt(arr[i + 1].date)
                             : convertDateToInt(arr[i].date) < convertDateToInt(arr[i + 1].date);
            if (condition) {
                swapAppointments(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        ++start;
    }
}

void cocktailSortByDuration(Appointment arr[], int n, bool ascending) {
    bool swapped = true;
    int start = 0, end = n - 1;

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; ++i) {
            bool condition = ascending 
                             ? convertStringToInt(arr[i].duration) > convertStringToInt(arr[i + 1].duration)
                             : convertStringToInt(arr[i].duration) < convertStringToInt(arr[i + 1].duration);
            if (condition) {
                swapAppointments(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;
        swapped = false;
        --end;

        for (int i = end - 1; i >= start; --i) {
            bool condition = ascending 
                             ? convertStringToInt(arr[i].duration) > convertStringToInt(arr[i + 1].duration)
                             : convertStringToInt(arr[i].duration) < convertStringToInt(arr[i + 1].duration);
            if (condition) {
                swapAppointments(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        ++start;
    }
}

void displayAppointments(const Appointment arr[], int n) {
    cout << "\n========== Sorted Appointments ==========\n\n";
    for (int i = 0; i < n; ++i) {
        cout << "Appointment #" << (i + 1) << "\n";
        cout << "----------------------------------------\n";
        cout << "ID             : " << arr[i].id << "\n";
        cout << "Client Name    : " << arr[i].clientName << "\n";
        cout << "IC Number      : " << arr[i].ic << "\n";
        cout << "Email          : " << arr[i].email << "\n";
        cout << "Session Type   : " << arr[i].sessionType << "\n";
        cout << "Counselor      : " << arr[i].counselor << "\n";
        cout << "Date (DDMMYYYY): " << arr[i].date << "\n";
        cout << "Time           : " << arr[i].time << "\n";
        cout << "Duration       : " << arr[i].duration << "\n";
        cout << "Status         : " << arr[i].status << "\n";
        cout << "Mode           : " << arr[i].mode << "\n";
        cout << "========================================\n\n";
    }
}

void dispSortMenu() {
    cout << "Home > My Appointments > Sort Appointments\n\n";
    cout << "1. Sort by Earliest Appointment Date\n";
    cout << "2. Sort by Latest Appointment Date\n";
    cout << "3. Sort by Shortest Duration\n";
    cout << "4. Sort by Longest Duration\n";
    cout << "Enter your choice (1-4): ";
}

int loadAppointments(Appointment arr[]) {
    ifstream file("appointments.txt");
    if (!file) {
        cout << "Error: Could not open appointments.txt\n";
        return 0;
    }

    int count = 0;
    while (count < MAX && getline(file, arr[count].id)) {
        getline(file, arr[count].clientName);
        getline(file, arr[count].ic);
        getline(file, arr[count].email);
        getline(file, arr[count].sessionType);
        getline(file, arr[count].counselor);
        getline(file, arr[count].date);
        getline(file, arr[count].time);
        getline(file, arr[count].duration);
        getline(file, arr[count].status);
        getline(file, arr[count].mode);
        ++count;
    }

    file.close();
    return count;
}

int main() {
    Appointment appointments[MAX];
    int total = loadAppointments(appointments);

    if (total == 0) {
        cout << "No appointments loaded.\n";
        return 1;
    }

    int choice;
    dispSortMenu();
    cin >> choice;

    switch (choice) {
        case 1:
            cocktailSortByDate(appointments, total, true);
            break;
        case 2:
            cocktailSortByDate(appointments, total, false);
            break;
        case 3:
            cocktailSortByDuration(appointments, total, true);
            break;
        case 4:
            cocktailSortByDuration(appointments, total, false);
            break;
        default:
            cout << "Invalid choice.\n";
            return 1;
    }

    displayAppointments(appointments, total);
    return 0;
}
