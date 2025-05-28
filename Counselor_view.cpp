#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct Appoint {
	string appointID;
	string ptName;
	string ptPhone;
	string ptEmail;
	string service;
	string cons;
	string appointDate;
	string appointTime;
	int duration;
	string status;
	string mode;
};

Appoint appointments[100];
int appointmentCount = 0;

void loadFromFile() {
    ifstream file("appoints.txt");
    if(!file.is_open()) {
        cout << "Error: Cannot open appoints.txt file!" << endl;
        return;
    }
    
    appointmentCount = 0;
    while(file >> appointments[appointmentCount].appointID 
          && getline(file, appointments[appointmentCount].ptName) 
          && file >> appointments[appointmentCount].ptPhone
          && file >> appointments[appointmentCount].ptEmail
          && getline(file, appointments[appointmentCount].service)
          && getline(file, appointments[appointmentCount].cons)
          && file >> appointments[appointmentCount].appointDate
          && file >> appointments[appointmentCount].appointTime
          && file >> appointments[appointmentCount].duration
          && getline(file, appointments[appointmentCount].status)
          && getline(file, appointments[appointmentCount].mode)) {
        
        // Remove leading whitespace from getline strings
        if(!appointments[appointmentCount].ptName.empty() && appointments[appointmentCount].ptName[0] == ' ') {
            appointments[appointmentCount].ptName = appointments[appointmentCount].ptName.substr(1);
        }
        if(!appointments[appointmentCount].service.empty() && appointments[appointmentCount].service[0] == ' ') {
            appointments[appointmentCount].service = appointments[appointmentCount].service.substr(1);
        }
        if(!appointments[appointmentCount].cons.empty() && appointments[appointmentCount].cons[0] == ' ') {
            appointments[appointmentCount].cons = appointments[appointmentCount].cons.substr(1);
        }
        if(!appointments[appointmentCount].status.empty() && appointments[appointmentCount].status[0] == ' ') {
            appointments[appointmentCount].status = appointments[appointmentCount].status.substr(1);
        }
        if(!appointments[appointmentCount].mode.empty() && appointments[appointmentCount].mode[0] == ' ') {
            appointments[appointmentCount].mode = appointments[appointmentCount].mode.substr(1);
        }
        
        appointmentCount++;
        if(appointmentCount >= 100) break;
    }
    
    file.close();
    cout << "Loaded " << appointmentCount << " appointments from file." << endl;
}

void dispMainMenu() {
	cout << "\nCounseling System" << endl << endl;
    cout << "1. Search by Counselor and Status" << endl;
    cout << "2. Exit" << endl;
}

void searchConsByStatus() {
    if(appointmentCount == 0) {
        cout << "\nNo appointments found!" << endl;
        return;
    }
    
    string counselorName, status;
    bool found = false;
    
    cin.ignore();
    cout << "Enter Counselor Name: ";
    getline(cin, counselorName);
    
    cout << "\nAvailable Status:" << endl;
    cout << "1. Pending" << endl;
    cout << "2. Confirmed" << endl;
    cout << "3. Completed" << endl;
    cout << "4. Cancelled" << endl;
    cout << "5. Approved" << endl;
    cout << "Select Status (1-5): ";
    cin >> status;
    
    if(status == "1") {
        status = "Pending";
    } else if (status == "2") {
        status = "Confirmed";
    } else if (status == "3") {
        status = "Completed";
    } else if (status == "4") {
        status = "Cancelled";
    } else if (status == "5") {
        status = "Approved";
    } else {
        cout << "Invalid status selection." << endl;
        return;
    }
    
    cout << "\nAppointments for Counselor: " << counselorName << " with Status: " << status << endl;
    cout << "=================================================================" << endl;
    
    for(int i = 0; i < appointmentCount; i++) {
        if(appointments[i].cons == counselorName && appointments[i].status == status) {
            cout << "\nAppointment ID: CP" << appointments[i].appointID << endl;
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
    
    if(!found) {
        cout << "No appointments found for " << counselorName << " with status " << status << endl;
    }
}

int main() {
    loadFromFile();
    
	int option;
	
	do {
        dispMainMenu();
        cout << "Enter your choice: ";
        cin >> option;
        
        switch(option) {
            case 1:
                searchConsByStatus();
                break;
            case 2:
                cout << "\nThank you for using the Counseling System!" << endl;
                break;
            default:
                cout << "Invalid choice! Please enter 1 or 2." << endl;
        }
        
        if(option != 2) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        
    } while(option != 2);
	
    return 0;
}
