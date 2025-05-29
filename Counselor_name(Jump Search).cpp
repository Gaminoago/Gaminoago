#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;   

//COMPARISONS:
//Original Search Functions: 
//Just iterate through all appointments and collect matches.
//Always scan entire list regardless of matches found early or not. 
//No prerequisite to sort data.
//Simpler code, easier to maintain.
//Jump Search Versions:
//Array must be sorted on cons or status before searching.
//Search jumps forward in blocks (step = √n), then does linear scan inside the block.
//Reduces number of comparisons and speeds up search in big datasets.
//More efficient for large datasets but adds sorting overhead if data not pre-sorted.



struct Appoint {
    string appointID;
    string ptName;
    int ptPhone;
    string ptEmail; 
    string service;
    string cons;
    int appointDate; // Stored as integer in DDMMYYYY format
    int appointTime; // Changed to int
    int duration;
    string status;
    string mode;
};

// Helper function to convert integer to string
string intToString(int num) {
    if (num == 0) return "0";
    string result = "";
    while (num > 0) {
        result = char('0' + (num % 10)) + result;
        num /= 10;
    }
    return result;
}

// Helper function to truncate strings for display
string truncateString(const string& str, int maxWidth) {
    if (str.length() <= maxWidth) return str;
    return str.substr(0, maxWidth - 3) + "...";
}

// Display appointments in column style
void displayAppointments(Appoint appointments[], int count) {
    if (count == 0) {
        cout << "\nNo appointments found!\n";
        return;
    }
    
    // Column widths - adjusted for better alignment
    const int id_width = 8;
    const int name_width = 18;
    const int phone_width = 15;
    const int email_width = 25;
    const int service_width = 18; // Increased width for longer service names
    const int cons_width = 16;
    const int date_width = 12;
    const int time_width = 8;
    const int duration_width = 8;
    const int status_width = 12;
    const int mode_width = 10;
    
    cout << "\n";
    // Header with separators
    cout << "+" << string(id_width, '-') 
         << "+" << string(name_width, '-')
         << "+" << string(phone_width, '-')
         << "+" << string(email_width, '-')
         << "+" << string(service_width, '-')
         << "+" << string(cons_width, '-')
         << "+" << string(date_width, '-')
         << "+" << string(time_width, '-')
         << "+" << string(duration_width, '-')
         << "+" << string(status_width, '-')
         << "+" << string(mode_width, '-') << "+" << endl;
    
    cout << "|" << left << setw(id_width) << "ID" 
         << "|" << setw(name_width) << "NAME"
         << "|" << setw(phone_width) << "PHONE"
         << "|" << setw(email_width) << "EMAIL"
         << "|" << setw(service_width) << "SERVICE"
         << "|" << setw(cons_width) << "COUNSELOR"
         << "|" << setw(date_width) << "DATE"
         << "|" << setw(time_width) << "TIME"
         << "|" << setw(duration_width) << "MINS"
         << "|" << setw(status_width) << "STATUS"
         << "|" << setw(mode_width) << "MODE" << "|" << endl;
    
    cout << "+" << string(id_width, '-') 
         << "+" << string(name_width, '-')
         << "+" << string(phone_width, '-')
         << "+" << string(email_width, '-')
         << "+" << string(service_width, '-')
         << "+" << string(cons_width, '-')
         << "+" << string(date_width, '-')
         << "+" << string(time_width, '-')
         << "+" << string(duration_width, '-')
         << "+" << string(status_width, '-')
         << "+" << string(mode_width, '-') << "+" << endl;
    
    for (int i = 0; i < count; i++) {
        // Format phone number with leading zeros
        string phoneNum = intToString(appointments[i].ptPhone);
        while (phoneNum.length() < 10) {
            phoneNum = "0" + phoneNum;
        }
        phoneNum = "+60" + phoneNum;
        
        // Format date as DD/MM/YYYY for better readability
        string dateStr = intToString(appointments[i].appointDate);
        while (dateStr.length() < 8) {
            dateStr = "0" + dateStr;
        }
        string formattedDate = dateStr.substr(0,2) + "/" + dateStr.substr(2,2) + "/" + dateStr.substr(4,4);
        
        // Format time as HH:MM from integer
        string timeStr = intToString(appointments[i].appointTime);
        while (timeStr.length() < 4) {
            timeStr = "0" + timeStr;
        }
        string formattedTime = timeStr.substr(0,2) + ":" + timeStr.substr(2,2);
        
        cout << "|" << left 
             << setw(id_width) << ("CP" + appointments[i].appointID)
             << "|" << setw(name_width) << truncateString(appointments[i].ptName, name_width-1)
             << "|" << setw(phone_width) << phoneNum
             << "|" << setw(email_width) << truncateString(appointments[i].ptEmail, email_width-1)
             << "|" << setw(service_width) << truncateString(appointments[i].service, service_width-1)
             << "|" << setw(cons_width) << truncateString(appointments[i].cons, cons_width-1)
             << "|" << setw(date_width) << formattedDate
             << "|" << setw(time_width) << formattedTime
             << "|" << setw(duration_width) << intToString(appointments[i].duration)
             << "|" << setw(status_width) << appointments[i].status
             << "|" << setw(mode_width) << appointments[i].mode << "|" << endl;
    }
    
    // Bottom border
    cout << "+" << string(id_width, '-') 
         << "+" << string(name_width, '-')
         << "+" << string(phone_width, '-')
         << "+" << string(email_width, '-')
         << "+" << string(service_width, '-')
         << "+" << string(cons_width, '-')
         << "+" << string(date_width, '-')
         << "+" << string(time_width, '-')
         << "+" << string(duration_width, '-')
         << "+" << string(status_width, '-')
         << "+" << string(mode_width, '-') << "+" << endl;
    
    cout << "\nTotal appointments: " << count << endl;
}

// Sorting functions
void sort_duration_asc(Appoint appointments[], int n) {
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;
        for (int i = start; i < end; i++) {
            if (appointments[i].duration > appointments[i+1].duration) {
                swap(appointments[i], appointments[i+1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        end--;
        for (int i = end - 1; i >= start; i--) {
            if (appointments[i].duration > appointments[i+1].duration) {
                swap(appointments[i], appointments[i+1]);
                swapped = true;
            }
        }
        start++;
    }
}

void sort_duration_desc(Appoint appointments[], int n) {
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;
        for (int i = start; i < end; i++) {
            if (appointments[i].duration < appointments[i+1].duration) {
                swap(appointments[i], appointments[i+1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        end--;
        for (int i = end - 1; i >= start; i--) {
            if (appointments[i].duration < appointments[i+1].duration) {
                swap(appointments[i], appointments[i+1]);
                swapped = true;
            }
        }
        start++;
    }
}

void sort_date_asc(Appoint appointments[], int n) {
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;
        for (int i = start; i < end; i++) {
            if (appointments[i].appointDate > appointments[i+1].appointDate) {
                swap(appointments[i], appointments[i+1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        end--;
        for (int i = end - 1; i >= start; i--) {
            if (appointments[i].appointDate > appointments[i+1].appointDate) {
                swap(appointments[i], appointments[i+1]);
                swapped = true;
            }
        }
        start++;
    }
}

void sort_date_desc(Appoint appointments[], int n) {
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;
        for (int i = start; i < end; i++) {
            if (appointments[i].appointDate < appointments[i+1].appointDate) {
                swap(appointments[i], appointments[i+1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        end--;
        for (int i = end - 1; i >= start; i--) {
            if (appointments[i].appointDate < appointments[i+1].appointDate) {
                swap(appointments[i], appointments[i+1]);
                swapped = true;
            }
        }
        start++;
    }
}

// Search functions
void Search_Counselor(Appoint appointments[], int n, string target) {
    Appoint results[100];
    int foundCount = 0;
    for (int i = 0; i < n; i++) {
        if (appointments[i].cons == target) {
            results[foundCount++] = appointments[i];
        }
    }
    if (foundCount) {
        cout << "\n=== Results (" << foundCount << " found) ===\n";
        displayAppointments(results, foundCount);
    } else {
        cout << "Counselor not found!\n";
    }
}

void Search_Status(Appoint appointments[], int n, string target) {
    Appoint results[100];
    int foundCount = 0;
    for (int i = 0; i < n; i++) {
        if (appointments[i].status == target) {
            results[foundCount++] = appointments[i];
        }
    }
    if (foundCount) {
        cout << "\n=== Results (" << foundCount << " found) ===\n";
        displayAppointments(results, foundCount);
    } else {
        cout << "Status not found!\n";
    }
}

// New service search function
void searchService(Appoint appointments[], int count) {
    int choice;
    string service;
    
    cout << "\n== Available Service Types ==" << endl;
    cout << "1. Individual Therapy" << endl;
    cout << "2. Couples Therapy" << endl;
    cout << "3. Family Therapy" << endl << endl;
    cout << "Select Service Type (1-3): ";
    
    while (true) {
        if (cin >> choice) {
            if (choice >= 1 && choice <= 3) {
                cin.ignore();
                break;
            } else {
                cout << "Invalid choice! Please enter a number between 1 and 3: ";
            }
        } else {
            cout << "Invalid input! Please enter a valid number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    
    // Map choice to service name (using full service names)
    if (choice == 1) service = "Individual Therapy";
    else if (choice == 2) service = "Couples Therapy";
    else service = "Family Therapy";
    
    // Search for appointments with the selected service
    Appoint results[100];
    int foundCount = 0;
    
    for (int i = 0; i < count; i++) {
        if (appointments[i].service == service) {
            results[foundCount++] = appointments[i];
        }
    }
    
    if (foundCount > 0) {
        cout << "\n=== Results for " << service << " (" << foundCount << " found) ===\n";
        displayAppointments(results, foundCount);
    } else {
        cout << "\nNo appointments found for " << service << "!\n";
    }
}

// Input validation helper
int getValidChoice(int min, int max) {
    int choice;
    while (true) {
        if (cin >> choice) {
            if (choice >= min && choice <= max) {
                cin.ignore();
                return choice;
            } else {
                cout << "Invalid choice! Please enter a number between " << min << " and " << max << ": ";
            }
        } else {
            cout << "Invalid input! Please enter a valid number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

// Update appointment status
void updateAppointmentStatus(Appoint appointments[], int count) {
    if (count == 0) {
        cout << "\nNo appointments available to update!\n";
        return;
    }
    
    string appointID;
    cout << "\nEnter Appointment ID to update (without CP): ";
    cin >> appointID;
    cin.ignore();
    
    // Find appointment
    int foundIndex = -1;
    for (int i = 0; i < count; i++) {
        if (appointments[i].appointID == appointID) {
            foundIndex = i;
            break;
        }
    }
    
    if (foundIndex == -1) {
        cout << "Appointment ID not found!\n";
        return;
    }
    
    // Display current appointment details
    cout << "\n=== Current Appointment Details ===\n";
    Appoint temp[1] = {appointments[foundIndex]};
    displayAppointments(temp, 1);
    
    cout << "\nCurrent Status: " << appointments[foundIndex].status << endl;
    cout << "\nSelect New Status:" << endl;
    cout << "1. Pending" << endl;
    cout << "2. Confirmed" << endl;
    cout << "3. Completed" << endl;
    cout << "4. Cancelled" << endl;
    cout << "5. Cancel Update" << endl;
    cout << "Enter choice (1-5): ";
    
    int choice = getValidChoice(1, 5);
    
    if (choice == 5) {
        cout << "Update cancelled.\n";
        return;
    }
    
    string oldStatus = appointments[foundIndex].status;
    string newStatus;
    
    if (choice == 1) newStatus = "Pending";
    else if (choice == 2) newStatus = "Confirmed";
    else if (choice == 3) newStatus = "Completed";
    else newStatus = "Cancelled";
    
    // Confirmation before updating
    cout << "\nConfirm Status Update:" << endl;
    cout << "Change status from '" << oldStatus << "' to '" << newStatus << "'?" << endl;
    cout << "1. Yes, confirm update" << endl;
    cout << "2. No, cancel update" << endl;
    cout << "Enter choice (1-2): ";
    
    int confirm = getValidChoice(1, 2);
    
    if (confirm == 2) {
        cout << "\nUpdate cancelled. No changes made.\n";
        return;
    }
    
    // Proceed with update
    appointments[foundIndex].status = newStatus;
    
    cout << "\nStatus successfully updated from '" << oldStatus 
         << "' to '" << newStatus << "'!\n";
    
    // Display updated appointment
    cout << "\n=== Updated Appointment Details ===\n";
    displayAppointments(temp, 1);
}

// Add new appointment
void addAppointment(Appoint appointments[], int& count, int maxSize) {
    if (count >= maxSize) {
        cout << "Database full!\n";
        return;
    }
    
    Appoint a;
    cout << "\nAppointment ID: CP";
    cin >> a.appointID; cin.ignore();
    
    cout << "Patient Name: ";
    getline(cin, a.ptName);
    
    // Validate phone number
    while (true) {
        cout << "Phone (+60): ";
        if (cin >> a.ptPhone) {
            if (a.ptPhone > 0) {
                cin.ignore();
                break;
            } else {
                cout << "Invalid phone number! Please enter a positive number.\n";
            }
        } else {
            cout << "Invalid input! Please enter numbers only.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    
    cout << "Email: ";
    getline(cin, a.ptEmail);
    
    cout << "Service:" << endl;
    cout << "1. Individual Therapy" << endl;
    cout << "2. Couples Therapy" << endl;
    cout << "3. Family Therapy" << endl;
    cout << "Select Service (1-3): ";
    int choice = getValidChoice(1, 3);
    if (choice == 1) a.service = "Individual Therapy";
    else if (choice == 2) a.service = "Couples Therapy";
    else a.service = "Family Therapy";
    
    cout << "Counselor: ";
    getline(cin, a.cons);
    
    // Validate date
    string dateInput;
    while (true) {
        cout << "Date (DDMMYYYY): ";
        getline(cin, dateInput);
        
        if (dateInput.length() != 8) {
            cout << "Invalid date! Must be exactly 8 digits (DDMMYYYY). Please try again.\n";
            continue;
        }
        
        bool valid = true;
        int dateValue = 0;
        for (int j = 0; j < dateInput.length(); j++) {
            char c = dateInput[j];
            if (c < '0' || c > '9') {
                valid = false;
                break;
            }
            dateValue = dateValue * 10 + (c - '0');
        }
        
        if (valid) {
            // Basic date validation
            int day = (dateValue / 1000000) % 100;
            int month = (dateValue / 10000) % 100;
            int year = dateValue % 10000;
            
            if (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 2024) {
                a.appointDate = dateValue;
                break;
            } else {
                cout << "Invalid date values! Please check day (01-31), month (01-12), and year (>=2024).\n";
            }
        } else {
            cout << "Invalid date! Must contain only digits. Please try again.\n";
        }
    }
    
    // Validate time (now as integer)
    while (true) {
        cout << "Time (HHMM): ";
        if (cin >> a.appointTime) {
            if (a.appointTime >= 0 && a.appointTime <= 2359) {
                int hour = a.appointTime / 100;
                int minute = a.appointTime % 100;
                if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59) {
                    cin.ignore();
                    break;
                }
            }
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Invalid time! Please enter in HHMM format (e.g., 1430 for 2:30 PM).\n";
    }
    
    // Validate duration
    while (true) {
        cout << "Duration (mins): ";
        if (cin >> a.duration) {
            if (a.duration > 0 && a.duration <= 480) { // Max 8 hours
                cin.ignore();
                break;
            } else {
                cout << "Invalid duration! Please enter a value between 1 and 480 minutes.\n";
            }
        } else {
            cout << "Invalid input! Please enter numbers only.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    
    cout << "Status (1.Pending 2.Confirmed 3.Completed 4.Cancelled): ";
    choice = getValidChoice(1, 4);
    if (choice == 1) a.status = "Pending";
    else if (choice == 2) a.status = "Confirmed";
    else if (choice == 3) a.status = "Completed";
    else a.status = "Cancelled";
    
    cout << "Mode (1.Online 2.Physical): ";
    choice = getValidChoice(1, 2);
    a.mode = (choice == 1) ? "Online" : "Physical";
    
    appointments[count++] = a;
    cout << "\nAppointment added successfully!\n";
}

// Fixed file loading function with better error handling and debugging
int loadAppointments(Appoint appointments[], int maxSize) {
    ifstream file("appoints.txt");
    int count = 0;
    if (!file) {
        cout << "No appointment file found or cannot open file.\n";
        return 0;
    }
    
    string line;
    while (count < maxSize && getline(file, line)) {
        // Skip empty lines
        if (line.empty()) continue;
        
        appointments[count].appointID = line;
        
        // Read patient name
        if (!getline(file, appointments[count].ptName)) {
            cout << "Error reading patient name for appointment " << count + 1 << endl;
            break;
        }
        
        // Read phone number
        if (!(file >> appointments[count].ptPhone)) {
            cout << "Error reading phone number for appointment " << count + 1 << endl;
            break;
        }
        file.ignore(); // ignore the newline after the number
        
        // Read email
        if (!getline(file, appointments[count].ptEmail)) {
            cout << "Error reading email for appointment " << count + 1 << endl;
            break;
        }
        
        // Read service
        if (!getline(file, appointments[count].service)) {
            cout << "Error reading service for appointment " << count + 1 << endl;
            break;
        }
        
        // Read counselor
        if (!getline(file, appointments[count].cons)) {
            cout << "Error reading counselor for appointment " << count + 1 << endl;
            break;
        }
        
        // Read appointment date
        if (!(file >> appointments[count].appointDate)) {
            cout << "Error reading appointment date for appointment " << count + 1 << endl;
            break;
        }
        file.ignore(); // ignore the newline after the number
        
        // Read appointment time (now as integer)
        if (!(file >> appointments[count].appointTime)) {
            cout << "Error reading appointment time for appointment " << count + 1 << endl;
            break;
        }
        file.ignore(); // ignore the newline after the number
        
        // Read duration
        if (!(file >> appointments[count].duration)) {
            cout << "Error reading duration for appointment " << count + 1 << endl;
            break;
        }
        file.ignore(); // ignore the newline after the number
        
        // Read status
        if (!getline(file, appointments[count].status)) {
            cout << "Error reading status for appointment " << count + 1 << endl;
            break;
        }
        
        // Read mode
        if (!getline(file, appointments[count].mode)) {
            cout << "Error reading mode for appointment " << count + 1 << endl;
            break;
        }
        
        // Skip empty line if present
        getline(file, line);
        
        count++;
        cout << "Loaded appointment " << count << " - ID: " << appointments[count-1].appointID << endl;
    }
    
    file.close();
    cout << "Successfully loaded " << count << " appointments from file.\n";
    return count;
}

void saveAppointments(Appoint appointments[], int count) {
    ofstream file("appoints.txt");
    for (int i = 0; i < count; i++) {
        file << appointments[i].appointID << "\n"
             << appointments[i].ptName << "\n"
             << appointments[i].ptPhone << "\n"
             << appointments[i].ptEmail << "\n"
             << appointments[i].service << "\n"
             << appointments[i].cons << "\n"
             << appointments[i].appointDate << "\n"
             << appointments[i].appointTime << "\n"
             << appointments[i].duration << "\n"
             << appointments[i].status << "\n"
             << appointments[i].mode << "\n";
        if (i < count - 1) file << "\n"; // Add blank line between records except for the last one
    }
    file.close();
}

// Menu helpers
void clearScreen() {
    system("cls||clear");
}

void showMenu(const string& title, const string options[], int optionCount) {
    clearScreen();
    cout << "\n" << string(50, '=') << endl;
    cout << "          " << title << endl;
    cout << string(50, '=') << endl;
    for (int i = 0; i < optionCount; i++) {
        cout << (i + 1) << ". " << options[i] << "\n";
    }
    cout << string(50, '-') << endl;
    cout << "Enter choice: ";
}

void waitForEnter() {
    cout << "\nPress ENTER to continue...";
    cin.ignore();
}

int main() {
    const int MAX = 100;
    Appoint appointments[MAX];
    int count = loadAppointments(appointments, MAX);
    int choice;
    
    // Menu options
    string mainMenu[] = {"View Appointments", "Add Appointment", "Update Status", "Exit"};
    string viewMenu[] = {"All Appointments", "Sort Appointments", "Search", "Back"};
    string sortMenu[] = {"Earliest Date", "Latest Date", "Shortest Duration", "Longest Duration", "Back"};
    string searchMenu[] = {"By ID", "By Phone", "By Service", "By Counselor", "By Status", "By Mode", "Back"};
    
    while (true) {
        showMenu("MAIN MENU", mainMenu, 4);
        choice = getValidChoice(1, 4);
        
        if (choice == 4) break;
        
        if (choice == 2) {
            addAppointment(appointments, count, MAX);
            saveAppointments(appointments, count);
            waitForEnter();
            continue;
        }
        
        if (choice == 3) {
            updateAppointmentStatus(appointments, count);
            saveAppointments(appointments, count);
            waitForEnter();
            continue;
        }
        
        if (choice == 1) {
            // View Appointments
            while (true) {
                showMenu("MY APPOINTMENTS", viewMenu, 4);
                choice = getValidChoice(1, 4);
                
                if (choice == 4) break;
                
                if (choice == 1) {
                    displayAppointments(appointments, count);
                    waitForEnter();
                    continue;
                }
                
                if (choice == 2) {
                    // Sorting
                    while (true) {
                        showMenu("SORT BY", sortMenu, 5);
                        choice = getValidChoice(1, 5);
                        if (choice == 5) break;
                        
                        if (choice == 1) sort_date_asc(appointments, count);
                        else if (choice == 2) sort_date_desc(appointments, count);
                        else if (choice == 3) sort_duration_asc(appointments, count);
                        else if (choice == 4) sort_duration_desc(appointments, count);
                        
                        displayAppointments(appointments, count);
                        waitForEnter();
                    }
                    continue;
                }
                
                if (choice == 3) {
                    // Searching
                    while (true) {
                        showMenu("SEARCH BY", searchMenu, 7);
                        choice = getValidChoice(1, 7);
                        if (choice == 7) break;
                        
                        string input;
                        int phoneInput;
                        Appoint results[100];
                        int foundCount = 0;
                        
                        switch (choice) {
                            case 1:
                                cout << "Enter ID (without CP): ";
                                cin >> input; cin.ignore();
                                for (int i = 0; i < count; i++) {
                                    if (appointments[i].appointID == input) {
                                        results[foundCount++] = appointments[i];
                                    }
                                }
                                if (foundCount) {
                                    cout << "\n=== Results (" << foundCount << " found) ===\n";
                                    displayAppointments(results, foundCount);
                                } else {
                                    cout << "ID not found!\n";
                                }
                                break;
                                
                            case 2:
                                cout << "Enter phone (without +60): ";
                                while (true) {
                                    if (cin >> phoneInput) {
                                        cin.ignore();
                                        break;
                                    } else {
                                        cout << "Invalid input! Please enter numbers only: ";
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                    }
                                }
                                for (int i = 0; i < count; i++) {
                                    if (appointments[i].ptPhone == phoneInput) {
                                        results[foundCount++] = appointments[i];
                                    }
                                }
                                if (foundCount) {
                                    cout << "\n=== Results (" << foundCount << " found) ===\n";
                                    displayAppointments(results, foundCount);
                                } else {
                                    cout << "Phone not found!\n";
                                }
                                break;
                                
                            case 3:
                                searchService(appointments, count);
                                break;
                                
                            case 4:
                                cout << "Enter Counselor Name: ";
                                getline(cin, input);
                                Search_Counselor(appointments, count, input);
                                break;
                                
                            case 5:
                                cout << "Enter Status (Pending/Confirmed/Completed/Cancelled): ";
                                getline(cin, input);
                                Search_Status(appointments, count, input);
                                break;
                                
                            case 6:
                                cout << "Enter Mode (Online/Physical): ";
                                getline(cin, input);
                                for (int i = 0; i < count; i++) {
                                    if (appointments[i].mode == input) {
                                        results[foundCount++] = appointments[i];
                                    }
                                }
                                if (foundCount) {
                                    cout << "\n=== Results (" << foundCount << " found) ===\n";
                                    displayAppointments(results, foundCount);
                                } else {
                                    cout << "Mode not found!\n";
                                }
                                break;
                        }
                        waitForEnter();
                    }
                }
            }
        }
    }
    
    saveAppointments(appointments, count);
    cout << "\nThank you for using the Appointment Management System!\n";
    return 0;
}
