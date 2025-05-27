#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;

// Maximum limits for arrays
const int MAX_COUNSELORS = 50;
const int MAX_STUDENTS = 100;
const int MAX_APPOINTMENTS = 200;
const int MAX_NAME_LENGTH = 50;
const int MAX_SPECIALTY_LENGTH = 30;
const int MAX_TIME_SLOTS = 8;

// Structure definitions
struct TimeSlot {
    int hour;
    int minute;
    bool isAvailable;
    
    TimeSlot() {
        hour = 0;
        minute = 0;
        isAvailable = true;
    }
};

struct Counselor {
    int counselorID;
    char name[MAX_NAME_LENGTH];
    char specialty[MAX_SPECIALTY_LENGTH];
    TimeSlot timeSlots[MAX_TIME_SLOTS];
    int totalSlots;
    
    Counselor() {
        counselorID = 0;
        strcpy(name, "");
        strcpy(specialty, "");
        totalSlots = 0;
        // Initialize default time slots (9 AM to 5 PM)
        for(int i = 0; i < MAX_TIME_SLOTS; i++) {
            timeSlots[i].hour = 9 + i;
            timeSlots[i].minute = 0;
            timeSlots[i].isAvailable = true;
        }
        totalSlots = MAX_TIME_SLOTS;
    }
};

struct Student {
    int studentID;
    char name[MAX_NAME_LENGTH];
    char email[MAX_NAME_LENGTH];
    
    Student() {
        studentID = 0;
        strcpy(name, "");
        strcpy(email, "");
    }
};

struct Appointment {
    int appointmentID;
    int studentID;
    int counselorID;
    int day;
    int month;
    int year;
    int hour;
    int minute;
    char status[20]; // "Scheduled", "Completed", "Cancelled"
    
    Appointment() {
        appointmentID = 0;
        studentID = 0;
        counselorID = 0;
        day = 0;
        month = 0;
        year = 0;
        hour = 0;
        minute = 0;
        strcpy(status, "Scheduled");
    }
};

// Global arrays to store data
Counselor counselors[MAX_COUNSELORS];
Student students[MAX_STUDENTS];
Appointment appointments[MAX_APPOINTMENTS];

int counselorCount = 0;
int studentCount = 0;
int appointmentCount = 0;
int nextAppointmentID = 1;

// Manual string comparison function
int compareStrings(const char* str1, const char* str2) {
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0') {
        if(str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

// Manual string copy function
void copyString(char* dest, const char* src) {
    int i = 0;
    while(src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Helper function to find minimum of two numbers
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Cocktail Sort for Counselors by Name (for Jump Search preparation)
void cocktailSortCounselorsByName() {
    bool swapped = true;
    int start = 0;
    int end = counselorCount - 1;
    
    while(swapped) {
        // Reset swapped flag
        swapped = false;
        
        // Forward pass (left to right)
        for(int i = start; i < end; i++) {
            if(compareStrings(counselors[i].name, counselors[i + 1].name) > 0) {
                // Swap counselors
                Counselor temp = counselors[i];
                counselors[i] = counselors[i + 1];
                counselors[i + 1] = temp;
                swapped = true;
            }
        }
        
        // If no swapping occurred, array is sorted
        if(!swapped) break;
        
        // Decrease end point since largest element is at the end
        end--;
        
        // Reset swapped flag for backward pass
        swapped = false;
        
        // Backward pass (right to left)
        for(int i = end - 1; i >= start; i--) {
            if(compareStrings(counselors[i].name, counselors[i + 1].name) > 0) {
                // Swap counselors
                Counselor temp = counselors[i];
                counselors[i] = counselors[i + 1];
                counselors[i + 1] = temp;
                swapped = true;
            }
        }
        
        // Increase start point since smallest element is at the beginning
        start++;
    }
}

// Jump Search Algorithm for finding counselor by name (following your preferred format)
int jumpSearchCounselorByName(const char* counselorName, int n) {
    // Finding block size to be jumped
    int step = sqrt(n);
    
    // Finding the block where element is present (if it is present)
    int prev = 0;
    while (compareStrings(counselors[min(step, n)-1].name, counselorName) < 0) {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }
    
    // Doing a linear search for counselorName in block beginning with prev
    while (compareStrings(counselors[prev].name, counselorName) < 0) {
        prev++;
        // If we reached next block or end of array, element is not present
        if (prev == min(step, n))
            return -1;
    }
    
    // If element is found
    if (compareStrings(counselors[prev].name, counselorName) == 0)
        return prev;
        
    return -1;
}

// Manual bubble sort for counselors by name
void sortCounselorsByName() {
    for(int i = 0; i < counselorCount - 1; i++) {
        for(int j = 0; j < counselorCount - i - 1; j++) {
            if(compareStrings(counselors[j].name, counselors[j + 1].name) > 0) {
                // Swap counselors
                Counselor temp = counselors[j];
                counselors[j] = counselors[j + 1];
                counselors[j + 1] = temp;
            }
        }
    }
}

// Cocktail Sort Algorithm (Bidirectional Bubble Sort) for Appointments by ID
void cocktailSortAppointments() {
    bool swapped = true;
    int start = 0;
    int end = appointmentCount - 1;
    
    while(swapped) {
        // Reset swapped flag
        swapped = false;
        
        // Forward pass (left to right)
        for(int i = start; i < end; i++) {
            if(appointments[i].appointmentID > appointments[i + 1].appointmentID) {
                // Swap appointments
                Appointment temp = appointments[i];
                appointments[i] = appointments[i + 1];
                appointments[i + 1] = temp;
                swapped = true;
            }
        }
        
        // If no swapping occurred, array is sorted
        if(!swapped) break;
        
        // Decrease end point since largest element is at the end
        end--;
        
        // Reset swapped flag for backward pass
        swapped = false;
        
        // Backward pass (right to left)
        for(int i = end - 1; i >= start; i--) {
            if(appointments[i].appointmentID > appointments[i + 1].appointmentID) {
                // Swap appointments
                Appointment temp = appointments[i];
                appointments[i] = appointments[i + 1];
                appointments[i + 1] = temp;
                swapped = true;
            }
        }
        
        // Increase start point since smallest element is at the beginning
        start++;
    }
}

// Manual linear search for counselor by ID
int findCounselorByID(int counselorID) {
    for(int i = 0; i < counselorCount; i++) {
        if(counselors[i].counselorID == counselorID) {
            return i;
        }
    }
    return -1; // Not found
}

// Manual binary search for student by ID (assumes sorted array)
int binarySearchStudentByID(int studentID) {
    int left = 0;
    int right = studentCount - 1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;
        
        if(students[mid].studentID == studentID) {
            return mid;
        }
        else if(students[mid].studentID < studentID) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1; // Not found
}

// Jump Search Algorithm for finding appointment by ID (assumes sorted array)
int jumpSearchAppointmentByID(int appointmentID, int n) {
    // Finding block size to be jumped
    int step = sqrt(n);
    
    // Finding the block where element is present (if it is present)
    int prev = 0;
    while (appointments[min(step, n)-1].appointmentID < appointmentID) {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }
    
    // Doing a linear search for appointmentID in block beginning with prev
    while (appointments[prev].appointmentID < appointmentID) {
        prev++;
        // If we reached next block or end of array, element is not present
        if (prev == min(step, n))
            return -1;
    }
    
    // If element is found
    if (appointments[prev].appointmentID == appointmentID)
        return prev;
        
    return -1;
}

// Sort students by ID for binary search
void sortStudentsByID() {
    for(int i = 0; i < studentCount - 1; i++) {
        for(int j = 0; j < studentCount - i - 1; j++) {
            if(students[j].studentID > students[j + 1].studentID) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// Load data from files
void loadDataFromFiles() {
    // Load counselors
    ifstream counselorFile("counselors.txt");
    if(counselorFile.is_open()) {
        counselorCount = 0;
        while(counselorFile >> counselors[counselorCount].counselorID &&
              counselorFile.ignore() &&
              counselorFile.getline(counselors[counselorCount].name, MAX_NAME_LENGTH) &&
              counselorFile.getline(counselors[counselorCount].specialty, MAX_SPECIALTY_LENGTH)) {
            counselorCount++;
            if(counselorCount >= MAX_COUNSELORS) break;
        }
        counselorFile.close();
    }
    
    // Load students
    ifstream studentFile("students.txt");
    if(studentFile.is_open()) {
        studentCount = 0;
        while(studentFile >> students[studentCount].studentID &&
              studentFile.ignore() &&
              studentFile.getline(students[studentCount].name, MAX_NAME_LENGTH) &&
              studentFile.getline(students[studentCount].email, MAX_NAME_LENGTH)) {
            studentCount++;
            if(studentCount >= MAX_STUDENTS) break;
        }
        studentFile.close();
        sortStudentsByID(); // Sort for binary search
    }
    
    // Load appointments
    ifstream appointmentFile("appointments.txt");
    if(appointmentFile.is_open()) {
        appointmentCount = 0;
        int maxAppID = 0;
        while(appointmentFile >> appointments[appointmentCount].appointmentID >>
              appointments[appointmentCount].studentID >>
              appointments[appointmentCount].counselorID >>
              appointments[appointmentCount].day >>
              appointments[appointmentCount].month >>
              appointments[appointmentCount].year >>
              appointments[appointmentCount].hour >>
              appointments[appointmentCount].minute &&
              appointmentFile.ignore() &&
              appointmentFile.getline(appointments[appointmentCount].status, 20)) {
            
            if(appointments[appointmentCount].appointmentID > maxAppID) {
                maxAppID = appointments[appointmentCount].appointmentID;
            }
            appointmentCount++;
            if(appointmentCount >= MAX_APPOINTMENTS) break;
        }
        appointmentFile.close();
        nextAppointmentID = maxAppID + 1;
    }
}

// Save data to files
void saveDataToFiles() {
    // Save counselors
    ofstream counselorFile("counselors.txt");
    if(counselorFile.is_open()) {
        for(int i = 0; i < counselorCount; i++) {
            counselorFile << counselors[i].counselorID << endl;
            counselorFile << counselors[i].name << endl;
            counselorFile << counselors[i].specialty << endl;
        }
        counselorFile.close();
    }
    
    // Save students
    ofstream studentFile("students.txt");
    if(studentFile.is_open()) {
        for(int i = 0; i < studentCount; i++) {
            studentFile << students[i].studentID << endl;
            studentFile << students[i].name << endl;
            studentFile << students[i].email << endl;
        }
        studentFile.close();
    }
    
    // Save appointments
    ofstream appointmentFile("appointments.txt");
    if(appointmentFile.is_open()) {
        for(int i = 0; i < appointmentCount; i++) {
            appointmentFile << appointments[i].appointmentID << " "
                          << appointments[i].studentID << " "
                          << appointments[i].counselorID << " "
                          << appointments[i].day << " "
                          << appointments[i].month << " "
                          << appointments[i].year << " "
                          << appointments[i].hour << " "
                          << appointments[i].minute << endl;
            appointmentFile << appointments[i].status << endl;
        }
        appointmentFile.close();
    }
}

// Add new counselor
void addCounselor() {
    if(counselorCount >= MAX_COUNSELORS) {
        cout << "Maximum counselor limit reached!" << endl;
        return;
    }
    
    cout << "\n--- Add New Counselor ---" << endl;
    cout << "Enter Counselor ID: ";
    cin >> counselors[counselorCount].counselorID;
    cin.ignore();
    
    // Check if ID already exists
    if(findCounselorByID(counselors[counselorCount].counselorID) != -1) {
        cout << "Counselor ID already exists!" << endl;
        return;
    }
    
    cout << "Enter Counselor Name: ";
    cin.getline(counselors[counselorCount].name, MAX_NAME_LENGTH);
    
    cout << "Enter Counselor Specialty: ";
    cin.getline(counselors[counselorCount].specialty, MAX_SPECIALTY_LENGTH);
    
    counselorCount++;
    cout << "Counselor added successfully!" << endl;
}

// Add new student
void addStudent() {
    if(studentCount >= MAX_STUDENTS) {
        cout << "Maximum student limit reached!" << endl;
        return;
    }
    
    cout << "\n--- Add New Student ---" << endl;
    cout << "Enter Student ID: ";
    cin >> students[studentCount].studentID;
    cin.ignore();
    
    cout << "Enter Student Name: ";
    cin.getline(students[studentCount].name, MAX_NAME_LENGTH);
    
    cout << "Enter Student Email: ";
    cin.getline(students[studentCount].email, MAX_NAME_LENGTH);
    
    studentCount++;
    sortStudentsByID(); // Maintain sorted order
    cout << "Student added successfully!" << endl;
}

// Display all counselors
void displayCounselors() {
    cout << "\n--- List of Counselors ---" << endl;
    if(counselorCount == 0) {
        cout << "No counselors found." << endl;
        return;
    }
    
    sortCounselorsByName();
    
    cout << "ID\tName\t\t\tSpecialty" << endl;
    cout << "----------------------------------------" << endl;
    for(int i = 0; i < counselorCount; i++) {
        cout << counselors[i].counselorID << "\t"
             << counselors[i].name << "\t\t"
             << counselors[i].specialty << endl;
    }
}

// Check if time slot is available
bool isTimeSlotAvailable(int counselorID, int day, int month, int year, int hour, int minute) {
    for(int i = 0; i < appointmentCount; i++) {
        if(appointments[i].counselorID == counselorID &&
           appointments[i].day == day &&
           appointments[i].month == month &&
           appointments[i].year == year &&
           appointments[i].hour == hour &&
           appointments[i].minute == minute &&
           compareStrings(appointments[i].status, "Cancelled") != 0) {
            return false;
        }
    }
    return true;
}

// Book appointment
void bookAppointment() {
    if(appointmentCount >= MAX_APPOINTMENTS) {
        cout << "Maximum appointment limit reached!" << endl;
        return;
    }
    
    cout << "\n--- Book New Appointment ---" << endl;
    
    int studentID, counselorID;
    cout << "Enter Student ID: ";
    cin >> studentID;
    
    // Verify student exists
    if(binarySearchStudentByID(studentID) == -1) {
        cout << "Student not found!" << endl;
        return;
    }
    
    cout << "Enter Counselor ID: ";
    cin >> counselorID;
    
    // Verify counselor exists
    int counselorIndex = findCounselorByID(counselorID);
    if(counselorIndex == -1) {
        cout << "Counselor not found!" << endl;
        return;
    }
    
    int day, month, year, hour, minute;
    cout << "Enter appointment date (DD MM YYYY): ";
    cin >> day >> month >> year;
    
    cout << "Enter appointment time (HH MM): ";
    cin >> hour >> minute;
    
    // Check if time slot is available
    if(!isTimeSlotAvailable(counselorID, day, month, year, hour, minute)) {
        cout << "Time slot not available!" << endl;
        return;
    }
    
    // Create new appointment
    appointments[appointmentCount].appointmentID = nextAppointmentID++;
    appointments[appointmentCount].studentID = studentID;
    appointments[appointmentCount].counselorID = counselorID;
    appointments[appointmentCount].day = day;
    appointments[appointmentCount].month = month;
    appointments[appointmentCount].year = year;
    appointments[appointmentCount].hour = hour;
    appointments[appointmentCount].minute = minute;
    copyString(appointments[appointmentCount].status, "Scheduled");
    
    appointmentCount++;
    cout << "Appointment booked successfully! Appointment ID: " 
         << (nextAppointmentID - 1) << endl;
}

// Display appointments
void displayAppointments() {
    cout << "\n--- List of Appointments ---" << endl;
    if(appointmentCount == 0) {
        cout << "No appointments found." << endl;
        return;
    }
    
    cout << "App ID\tStudent ID\tCounselor ID\tDate\t\tTime\tStatus" << endl;
    cout << "---------------------------------------------------------------" << endl;
    for(int i = 0; i < appointmentCount; i++) {
        cout << appointments[i].appointmentID << "\t"
             << appointments[i].studentID << "\t\t"
             << appointments[i].counselorID << "\t\t"
             << appointments[i].day << "/" << appointments[i].month << "/" << appointments[i].year << "\t"
             << appointments[i].hour << ":" << appointments[i].minute << "\t"
             << appointments[i].status << endl;
    }
}

// Cancel appointment
void cancelAppointment() {
    cout << "\n--- Cancel Appointment ---" << endl;
    int appointmentID;
    cout << "Enter Appointment ID to cancel: ";
    cin >> appointmentID;
    
    bool found = false;
    for(int i = 0; i < appointmentCount; i++) {
        if(appointments[i].appointmentID == appointmentID) {
            copyString(appointments[i].status, "Cancelled");
            cout << "Appointment cancelled successfully!" << endl;
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "Appointment not found!" << endl;
    }
}

// Search appointments by student ID
void searchAppointmentsByStudent() {
    cout << "\n--- Search Appointments by Student ---" << endl;
    int studentID;
    cout << "Enter Student ID: ";
    cin >> studentID;
    
    bool found = false;
    cout << "\nAppointments for Student ID " << studentID << ":" << endl;
    cout << "App ID\tCounselor ID\tDate\t\tTime\tStatus" << endl;
    cout << "-----------------------------------------------" << endl;
    
    for(int i = 0; i < appointmentCount; i++) {
        if(appointments[i].studentID == studentID) {
            cout << appointments[i].appointmentID << "\t"
                 << appointments[i].counselorID << "\t\t"
                 << appointments[i].day << "/" << appointments[i].month << "/" << appointments[i].year << "\t"
                 << appointments[i].hour << ":" << appointments[i].minute << "\t"
                 << appointments[i].status << endl;
            found = true;
        }
    }
    
    if(!found) {
        cout << "No appointments found for this student." << endl;
    }
}

// Search counselor by name using Jump Search (Updated to match your format)
void searchCounselorByName() {
    cout << "\n--- Search Counselor by Name (Jump Search) ---" << endl;
    char counselorName[MAX_NAME_LENGTH];
    cout << "Enter Counselor Name: ";
    cin.ignore();
    cin.getline(counselorName, MAX_NAME_LENGTH);
    
    // First sort counselors using cocktail sort
    cocktailSortCounselorsByName();
    
    // Find the index of counselorName using Jump Search
    int index = jumpSearchCounselorByName(counselorName, counselorCount);
    
    if(index != -1) {
        cout << "\nCounselor '" << counselorName << "' is at index " << index << endl;
        cout << "\nCounselor Found:" << endl;
        cout << "ID\tName\t\t\tSpecialty" << endl;
        cout << "----------------------------------------" << endl;
        cout << counselors[index].counselorID << "\t"
             << counselors[index].name << "\t\t"
             << counselors[index].specialty << endl;
             
        // Show available time slots
        cout << "\nAvailable Time Slots:" << endl;
        cout << "Time\t\tStatus" << endl;
        cout << "--------------------" << endl;
        for(int i = 0; i < counselors[index].totalSlots; i++) {
            cout << counselors[index].timeSlots[i].hour << ":"
                 << (counselors[index].timeSlots[i].minute < 10 ? "0" : "")
                 << counselors[index].timeSlots[i].minute << "\t\t"
                 << (counselors[index].timeSlots[i].isAvailable ? "Available" : "Booked")
                 << endl;
        }
    } else {
        cout << "\nCounselor '" << counselorName << "' not found!" << endl;
    }
}

// Display counselors sorted by name using Cocktail Sort
void displayCounselorsSorted() {
    cout << "\n--- List of Counselors (Sorted by Name using Cocktail Sort) ---" << endl;
    if(counselorCount == 0) {
        cout << "No counselors found." << endl;
        return;
    }
    
    // Sort counselors using cocktail sort
    cocktailSortCounselorsByName();
    
    cout << "ID\tName\t\t\tSpecialty" << endl;
    cout << "----------------------------------------" << endl;
    for(int i = 0; i < counselorCount; i++) {
        cout << counselors[i].counselorID << "\t"
             << counselors[i].name << "\t\t"
             << counselors[i].specialty << endl;
    }
    
    cout << "\nNote: Counselors are now sorted alphabetically by name using Cocktail Sort algorithm." << endl;
}

// Search appointment by ID using Jump Search (Updated to match your format)
void searchAppointmentByID() {
    cout << "\n--- Search Appointment by ID (Jump Search) ---" << endl;
    int appointmentID;
    cout << "Enter Appointment ID: ";
    cin >> appointmentID;
    
    // First sort appointments using cocktail sort
    cocktailSortAppointments();
    
    // Find the index of appointmentID using Jump Search
    int index = jumpSearchAppointmentByID(appointmentID, appointmentCount);
    
    if(index != -1) {
        cout << "\nAppointment ID " << appointmentID << " is at index " << index << endl;
        cout << "\nAppointment Found:" << endl;
        cout << "App ID\tStudent ID\tCounselor ID\tDate\t\tTime\tStatus" << endl;
        cout << "---------------------------------------------------------------" << endl;
        cout << appointments[index].appointmentID << "\t"
             << appointments[index].studentID << "\t\t"
             << appointments[index].counselorID << "\t\t"
             << appointments[index].day << "/" << appointments[index].month << "/" << appointments[index].year << "\t"
             << appointments[index].hour << ":" << appointments[index].minute << "\t"
             << appointments[index].status << endl;
    } else {
        cout << "\nAppointment ID " << appointmentID << " not found!" << endl;
    }
}

// Search appointments by counselor name
void searchAppointmentsByCounselor() {
    cout << "\n--- Search Appointments by Counselor Name ---" << endl;
    char counselorName[MAX_NAME_LENGTH];
    cout << "Enter Counselor Name: ";
    cin.ignore();
    cin.getline(counselorName, MAX_NAME_LENGTH);
    
    // First sort counselors and find the counselor using jump search
    cocktailSortCounselorsByName();
    int counselorIndex = jumpSearchCounselorByName(counselorName, counselorCount);
    
    if(counselorIndex == -1) {
        cout << "Counselor not found!" << endl;
        return;
    }
    
    int counselorID = counselors[counselorIndex].counselorID;
    bool found = false;
    
    cout << "\nAppointments for Counselor: " << counselorName << endl;
    cout << "App ID\tStudent ID\tDate\t\tTime\tStatus" << endl;
    cout << "-----------------------------------------------" << endl;
    
    for(int i = 0; i < appointmentCount; i++) {
        if(appointments[i].counselorID == counselorID) {
            cout << appointments[i].appointmentID << "\t"
                 << appointments[i].studentID << "\t\t"
                 << appointments[i].day << "/" << appointments[i].month << "/" << appointments[i].year << "\t"
                 << appointments[i].hour << ":" << appointments[i].minute << "\t"
                 << appointments[i].status << endl;
            found = true;
        }
    }
    
    if(!found) {
        cout << "No appointments found for this counselor." << endl;
    }
}

// Display appointments (sorted using Cocktail Sort)
void displayAppointmentsSorted() {
    cout << "\n--- List of Appointments (Sorted by ID) ---" << endl;
    if(appointmentCount == 0) {
        cout << "No appointments found." << endl;
        return;
    }
    
    // Sort appointments using cocktail sort
    cocktailSortAppointments();
    
    cout << "App ID\tStudent ID\tCounselor ID\tDate\t\tTime\tStatus" << endl;
    cout << "---------------------------------------------------------------" << endl;
    for(int i = 0; i < appointmentCount; i++) {
        cout << appointments[i].appointmentID << "\t"
             << appointments[i].studentID << "\t\t"
             << appointments[i].counselorID << "\t\t"
             << appointments[i].day << "/" << appointments[i].month << "/" << appointments[i].year << "\t"
             << appointments[i].hour << ":" << appointments[i].minute << "\t"
             << appointments[i].status << endl;
    }
}

// Display main menu
void displayMenu() {
    cout << "\n========================================" << endl;
    cout << "    COUNSELOR BOOKING SYSTEM" << endl;
    cout << "========================================" << endl;
    cout << "1. Add Counselor" << endl;
    cout << "2. Add Student" << endl;
    cout << "3. Display All Counselors" << endl;
    cout << "4. Display Sorted Counselors (Cocktail Sort)" << endl;
    cout << "5. Search Counselor by Name (Jump Search)" << endl;
    cout << "6. Book Appointment" << endl;
    cout << "7. Display All Appointments" << endl;
    cout << "8. Display Sorted Appointments (Cocktail Sort)" << endl;
    cout << "9. Cancel Appointment" << endl;
    cout << "10. Search Appointments by Student" << endl;
    cout << "11. Search Appointments by Counselor Name" << endl;
    cout << "12. Search Appointment by ID (Jump Search)" << endl;
    cout << "13. Save Data" << endl;
    cout << "14. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    cout << "Loading data from files..." << endl;
    loadDataFromFiles();
    cout << "Data loaded successfully!" << endl;
    
    int choice;
    
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        
        // Clear input buffer in case of invalid input
        if(cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }
        
        switch(choice) {
            case 1:
                addCounselor();
                break;
            case 2:
                addStudent();
                break;
            case 3:
                displayCounselors();
                break;
            case 4:
                displayCounselorsSorted();
                break;
            case 5:
                searchCounselorByName();
                break;
            case 6:
                bookAppointment();
                break;
            case 7:
                displayAppointments();
                break;
            case 8:
                displayAppointmentsSorted();
                break;
            case 9:
                cancelAppointment();
                break;
            case 10:
                searchAppointmentsByStudent();
                break;
            case 11:
                searchAppointmentsByCounselor();
                break;
            case 12:
                searchAppointmentByID();
                break;
            case 13:
                saveDataToFiles();
                cout << "Data saved successfully!" << endl;
                break;
            case 14:
                saveDataToFiles();
                cout << "Exiting program. Data saved!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
        
        // Add a pause or newline for better user experience
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        
    } while(choice != 14);
    
    return 0;
}
