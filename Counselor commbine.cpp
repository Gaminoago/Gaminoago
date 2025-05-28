#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

struct Appoint {
    string appointID;
    string ptName;
    int ptPhone;
    string ptEmail;
    string service;
    string cons;
    string appointDate;
    string appointTime;
    int duration;
    string status;
    string mode;
};

// Helper function to get minimum of two integers
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Calculate optimal jump size (square root of array size)
int Calculate_appoint(int n) {
    int jump = 1;
    while (jump * jump < n) {
        jump++;
    }
    return jump;
}

// Convert integer to string
string intToString(int num) {
    if (num == 0) return "0";
    
    string result = "";
    bool negative = false;
    
    if (num < 0) {
        negative = true;
        num = -num;
    }
    
    while (num > 0) {
        result = char('0' + (num % 10)) + result;
        num /= 10;
    }
    
    if (negative) {
        result = "-" + result;
    }
    
    return result;
}

// Jump search by counselor and status (combined search)
void Search_Cons_Status(Appoint appointments[], int n, string targetCounselor, string targetStatus) {
    if (n == 0) {
        cout << "\nNo appointments found!" << endl;
        return;
    }
    
    // Sort by counselor first, then by status using bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (appointments[j].cons > appointments[j + 1].cons || 
                (appointments[j].cons == appointments[j + 1].cons && 
                 appointments[j].status > appointments[j + 1].status)) {
                Appoint temp = appointments[j];
                appointments[j] = appointments[j + 1];
                appointments[j + 1] = temp;
            }
        }
    }
    
    int jump = Calculate_appoint(n);
    int prev = 0;
    bool found = false;
    
    // Jump search for counselor
    while (prev < n && appointments[min(jump, n) - 1].cons < targetCounselor) {
        prev = jump;
        jump += Calculate_appoint(n);
        if (prev >= n) break;
    }
    
    cout << "\n=================================================================" << endl;
    cout << "Appointments for Counselor: " << targetCounselor << " with Status: " << targetStatus << endl;
    cout << "=================================================================" << endl;
    
    // Linear search in the identified block for both counselor and status
    for (int i = prev; i < min(jump, n); i++) {
        if (appointments[i].cons == targetCounselor && appointments[i].status == targetStatus) {
            cout << "\nAppointment ID: A" << appointments[i].appointID << endl;
            cout << "Patient: " << appointments[i].ptName << endl;
            cout << "Phone: +60 " << appointments[i].ptPhone << endl;
            cout << "Email: " << appointments[i].ptEmail << endl;
            cout << "Service: " << appointments[i].service << endl;
            cout << "Date: " << appointments[i].appointDate << endl;
            cout << "Time: " << appointments[i].appointTime << endl;
            cout << "Duration: " << appointments[i].duration << " minutes" << endl;
            cout << "Mode: " << appointments[i].mode << endl;
            cout << "-----------------------------------------------------------------" << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "No appointments found for " << targetCounselor << " with status " << targetStatus << endl;
    }
}

// Jump search by counselor only
void Search_Counselor(Appoint appointments[], int n, string targetCounselor) {
    if (n == 0) {
        cout << "\nNo appointments found!" << endl;
        return;
    }
    
    // Sort appointments by counselor first (bubble sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (appointments[j].cons > appointments[j + 1].cons) {
                Appoint temp = appointments[j];
                appointments[j] = appointments[j + 1];
                appointments[j + 1] = temp;
            }
        }
    }
    
    int jump = Calculate_appoint(n);
    int prev = 0;
    bool found = false;
    
    // Jump search
    while (appointments[min(jump, n) - 1].cons < targetCounselor) {
        prev = jump;
        jump += Calculate_appoint(n);
        if (prev >= n) {
            cout << "\nNo appointments found with counselor: " << targetCounselor << endl;
            return;
        }
    }
    
    // Linear search in the identified block
    cout << "\n============================================" << endl;
    cout << "Appointments with Counselor: " << targetCounselor << endl;
    cout << "============================================" << endl;
    
    for (int i = prev; i < min(jump, n); i++) {
        if (appointments[i].cons == targetCounselor) {
            cout << "\nAppointment ID: A" << appointments[i].appointID << endl;
            cout << "Patient: " << appointments[i].ptName << endl;
            cout << "Phone: +60 " << appointments[i].ptPhone << endl;
            cout << "Email: " << appointments[i].ptEmail << endl;
            cout << "Service: " << appointments[i].service << endl;
            cout << "Date: " << appointments[i].appointDate << endl;
            cout << "Time: " << appointments[i].appointTime << endl;
            cout << "Duration: " << appointments[i].duration << " minutes" << endl;
            cout << "Status: " << appointments[i].status << endl;
            cout << "Mode: " << appointments[i].mode << endl;
            cout << "--------------------------------------------" << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "No appointments found with counselor: " << targetCounselor << endl;
    }
}

// Jump search by status only
void Search_Status(Appoint appointments[], int n, string targetStatus) {
    if (n == 0) {
        cout << "\nNo appointments found!" << endl;
        return;
    }
    
    // Sort appointments by status first (bubble sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (appointments[j].status > appointments[j + 1].status) {
                Appoint temp = appointments[j];
                appointments[j] = appointments[j + 1];
                appointments[j + 1] = temp;
            }
        }
    }
    
    int jump = Calculate_appoint(n);
    int prev = 0;
    bool found = false;
    
    // Jump search
    while (appointments[min(jump, n) - 1].status < targetStatus) {
        prev = jump;
        jump += Calculate_appoint(n);
        if (prev >= n) {
            cout << "\nNo appointments found with status: " << targetStatus << endl;
            return;
        }
    }
    
    // Linear search in the identified block
    cout << "\n=========================================" << endl;
    cout << "Appointments with Status: " << targetStatus << endl;
    cout << "=========================================" << endl;
    
    for (int i = prev; i < min(jump, n); i++) {
        if (appointments[i].status == targetStatus) {
            cout << "\nAppointment ID: A" << appointments[i].appointID << endl;
            cout << "Patient: " << appointments[i].ptName << endl;
            cout << "Phone: +60 " << appointments[i].ptPhone << endl;
            cout << "Email: " << appointments[i].ptEmail << endl;
            cout << "Service: " << appointments[i].service << endl;
            cout << "Counselor: " << appointments[i].cons << endl;
            cout << "Date: " << appointments[i].appointDate << endl;
            cout << "Time: " << appointments[i].appointTime << endl;
            cout << "Duration: " << appointments[i].duration << " minutes" << endl;
            cout << "Mode: " << appointments[i].mode << endl;
            cout << "----------------------------------------" << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "No appointments found with status: " << targetStatus << endl;
    }
}

// Function to add a new appointment with confirmation
int addAppointment(Appoint appointments[], int& count, int maxSize) {
    if (count >= maxSize) {
        cout << "Cannot add more appointments. Maximum limit reached!" << endl;
        return count;
    }
    
    Appoint newAppoint;
    char confirm;
    
    cout << "\n=== ADD NEW APPOINTMENT ===" << endl;
    
    // Generate new ID
    newAppoint.appointID = intToString(count + 1);
    cout << "Appointment ID: A" << newAppoint.appointID << endl;
    
    cin.ignore();
    cout << "Enter Patient Name: ";
    getline(cin, newAppoint.ptName);
    
    cout << "Enter Patient Phone (without +60): ";
    cin >> newAppoint.ptPhone;
    
    cin.ignore();
    cout << "Enter Patient Email: ";
    getline(cin, newAppoint.ptEmail);
    
    cout << "Enter Service: ";
    getline(cin, newAppoint.service);
    
    cout << "Enter Counselor Name: ";
    getline(cin, newAppoint.cons);
    
    cout << "Enter Appointment Date (DD/MM/YYYY): ";
    getline(cin, newAppoint.appointDate);
    
    cout << "Enter Appointment Time (HH:MM): ";
    getline(cin, newAppoint.appointTime);
    
    cout << "Enter Duration (minutes): ";
    cin >> newAppoint.duration;
    
    cin.ignore();
    cout << "Enter Status (Pending/Confirmed/Completed/Cancelled): ";
    getline(cin, newAppoint.status);
    
    cout << "Enter Mode (Online/In-person): ";
    getline(cin, newAppoint.mode);
    
    // Display appointment details for confirmation
    cout << "\n=== APPOINTMENT DETAILS ===" << endl;
    cout << "Appointment ID: A" << newAppoint.appointID << endl;
    cout << "Patient: " << newAppoint.ptName << endl;
    cout << "Phone: +60 " << newAppoint.ptPhone << endl;
    cout << "Email: " << newAppoint.ptEmail << endl;
    cout << "Service: " << newAppoint.service << endl;
    cout << "Counselor: " << newAppoint.cons << endl;
    cout << "Date: " << newAppoint.appointDate << endl;
    cout << "Time: " << newAppoint.appointTime << endl;
    cout << "Duration: " << newAppoint.duration << " minutes" << endl;
    cout << "Status: " << newAppoint.status << endl;
    cout << "Mode: " << newAppoint.mode << endl;
    
    cout << "\nDo you want to add this appointment? (y/n): ";
    cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        appointments[count] = newAppoint;
        count++;
        cout << "\nAppointment added successfully!" << endl;
    } else {
        cout << "\nAppointment not added." << endl;
    }
    
    return count;
}

// Function to display all appointments
void displayAllAppointments(Appoint appointments[], int n) {
    cout << "\n=== ALL APPOINTMENTS ===" << endl;
    cout << left
         << setw(5) << "ID" << " | "
         << setw(15) << "Name" << " | "
         << setw(15) << "Counselor" << " | "
         << setw(12) << "Status" << " | "
         << setw(12) << "Date" << " | "
         << setw(10) << "Time" << endl;
    cout << string(80, '-') << endl;
    
    for (int i = 0; i < n; i++) {
        cout << left
             << setw(5) << ("A" + appointments[i].appointID) << " | "
             << setw(15) << appointments[i].ptName << " | "
             << setw(15) << appointments[i].cons << " | "
             << setw(12) << appointments[i].status << " | "
             << setw(12) << appointments[i].appointDate << " | "
             << setw(10) << appointments[i].appointTime << endl;
    }
    cout << endl;
}

// Function to load appointments from appoints.txt
int loadAppointmentsFromFile(Appoint appointments[], int maxSize) {
    ifstream file("appoints.txt");
    int count = 0;
    
    if (!file.is_open()) {
        cout << "Error: Could not open appoints.txt file!" << endl;
        cout << "Make sure the file exists in the same directory." << endl;
        return 0;
    }
    
    Appoint rec;
    string line;
    
    while (!file.eof() && count < maxSize) {
        if (getline(file, rec.appointID) && !rec.appointID.empty()) {
            getline(file, rec.ptName);
            file >> rec.ptPhone;
            file.ignore();
            getline(file, rec.ptEmail);
            getline(file, rec.service);
            getline(file, rec.cons);
            getline(file, rec.appointDate);
            file >> rec.appointTime;
            file >> rec.duration;
            file.ignore();
            getline(file, rec.status);
            getline(file, rec.mode);
            
            appointments[count] = rec;
            count++;
        }
    }
    
    file.close();
    cout << "Loaded " << count << " appointments from appoints.txt" << endl;
    return count;
}

int main() {
    const int MAX_APPOINTMENTS = 1000;
    Appoint appointments[MAX_APPOINTMENTS];
    int appointmentCount = 0;
    int choice;
    string counselorName, status;
    
    cout << "===============================================" << endl;
    cout << "        JUMP SEARCH DEMO - COUNSELING SYSTEM" << endl;
    cout << "===============================================" << endl;
    
    // Load appointments from file
    appointmentCount = loadAppointmentsFromFile(appointments, MAX_APPOINTMENTS);
    
    if (appointmentCount == 0) {
        cout << "No appointments loaded from file." << endl;
        cout << "You can still use the program to add new appointments." << endl;
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }
    
    do {
        cout << "\n=== JUMP SEARCH OPTIONS ===" << endl;
        cout << "1. View All Appointments" << endl;
        cout << "2. Search by Counselor Appointment" << endl;
        cout << "3. Search by Status" << endl;
        cout << "4. Search by Counselor AND Status" << endl;
        cout << "5. Add New Appointment" << endl;
        cout << "6. Exit" << endl;
        cout << "\nEnter your choice (1-6): ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                displayAllAppointments(appointments, appointmentCount);
                break;
                
            case 2:
                cout << "\nEnter Counselor Name: ";
                cin >> counselorName;
                Search_Counselor(appointments, appointmentCount, counselorName);
                break;
                
            case 3:
                cout << "\nAvailable Status:" << endl;
                cout << "1. Pending" << endl;
                cout << "2. Confirmed" << endl;
                cout << "3. Completed" << endl;
                cout << "4. Cancelled" << endl;
                cout << "Select Status (1-4): ";
                cin >> status;
                
                if(status == "1") status = "Pending";
                else if(status == "2") status = "Confirmed";
                else if(status == "3") status = "Completed";
                else if(status == "4") status = "Cancelled";
                else {
                    cout << "Invalid selection!" << endl;
                    break;
                }
                
                Search_Status(appointments, appointmentCount, status);
                break;
                
            case 4:
                cout << "\nEnter Counselor Name: ";
                cin >> counselorName;
                
                cout << "\nAvailable Status:" << endl;
                cout << "1. Pending" << endl;
                cout << "2. Confirmed" << endl;
                cout << "3. Completed" << endl;
                cout << "4. Cancelled" << endl;
                cout << "Select Status (1-4): ";
                cin >> status;
                
                if(status == "1") status = "Pending";
                else if(status == "2") status = "Confirmed";
                else if(status == "3") status = "Completed";
                else if(status == "4") status = "Cancelled";
                else {
                    cout << "Invalid selection!" << endl;
                    break;
                }
                
                Search_Cons_Status(appointments, appointmentCount, counselorName, status);
                break;
                
            case 5:
                appointmentCount = addAppointment(appointments, appointmentCount, MAX_APPOINTMENTS);
                break;
                
            case 6:
                cout << "\nExiting... Thank you!" << endl;
                break;
                
            default:
                cout << "\nInvalid choice! Please try again." << endl;
        }
        
        if (choice != 6) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        
    } while (choice != 6);
    
    return 0;
}
