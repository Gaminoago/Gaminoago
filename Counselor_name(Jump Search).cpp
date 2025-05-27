#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Maximum limits for arrays
const int MAX_COUNSELORS = 50;

// Structure definition
struct Counselor {
    int counselorID;
    string name;
    string specialty;
    
    Counselor() {
        counselorID = 0;
        name = "";
        specialty = "";
    }
};

// Global array to store
Counselor counselors[MAX_COUNSELORS];
int counselorCount = 0;

// Manual square root function (integer approximation)
int integerSqrt(int n) {
    if (n == 0 || n == 1) return n;
    
    int result = 1;
    while (result * result <= n) {
        result++;
    }
    return result - 1;
}

// Cocktail Sort for Counselors by Name
void cocktailSortCounselorsByName() {
    bool swapped = true;
    int start = 0;
    int end = counselorCount - 1;
    
    while(swapped) {
        swapped = false;
        
        // Forward pass
        for(int i = start; i < end; i++) {
            if(counselors[i].name > counselors[i + 1].name) {
                Counselor temp = counselors[i];
                counselors[i] = counselors[i + 1];
                counselors[i + 1] = temp;
                swapped = true;
            }
        }
        
        if(!swapped) break;
        end--;
        swapped = false;
        
        // Backward pass
        for(int i = end - 1; i >= start; i--) {
            if(counselors[i].name > counselors[i + 1].name) {
                Counselor temp = counselors[i];
                counselors[i] = counselors[i + 1];
                counselors[i + 1] = temp;
                swapped = true;
            }
        }
        start++;
    }
}

// Jump Search using your exact format
int jump_Search(Counselor a[], int n, const string& item) {
    int i = 0;
    int m = integerSqrt(n); //initializing block size= √(n)
    
    while(a[m].name <= item && m < n) {
        // the control will continue to jump the blocks
        i = m;  // shift the block
        m += integerSqrt(n);
        if(m > n - 1)  // if m exceeds the array size
            return -1;
    }
    
    for(int x = i; x < m; x++) { //linear search in current block
        if(a[x].name == item)
            return x; //position of element being searched
    }
    return -1;
}

// Load counselor data from file
void loadCounselorData() {
    ifstream counselorFile("counselors.txt");
    if(counselorFile.is_open()) {
        counselorCount = 0;
        string line;
        while(counselorFile >> counselors[counselorCount].counselorID &&
              counselorFile.ignore() &&
              getline(counselorFile, counselors[counselorCount].name) &&
              getline(counselorFile, counselors[counselorCount].specialty)) {
            counselorCount++;
            if(counselorCount >= MAX_COUNSELORS) break;
        }
        counselorFile.close();
        cout << "Loaded " << counselorCount << " counselors from file." << endl;
    } else {
        cout << "Could not open counselors.txt file!" << endl;
    }
}

// Display all counselors with back option
void displayAllCounselors() {
    char choice;
    do {
        cout << "\n--- All Counselors ---" << endl;
        if(counselorCount == 0) {
            cout << "No counselors loaded." << endl;
        } else {
            cout << "ID\tName\t\t\tSpecialty" << endl;
            cout << "----------------------------------------" << endl;
            for(int i = 0; i < counselorCount; i++) {
                cout << counselors[i].counselorID << "\t"
                     << counselors[i].name << "\t\t"
                     << counselors[i].specialty << endl;
            }
        }
        
        cout << "\nPress 'b' to go back to main menu or any other key to refresh: ";
        cin >> choice;
        cin.ignore();
        
    } while(choice != 'b' && choice != 'B');
}

// Display counselors sorted by name with back option
void displaySortedCounselors() {
    char choice;
    do {
        cout << "\n--- Counselors Sorted by Name (Using Cocktail Sort) ---" << endl;
        if(counselorCount == 0) {
            cout << "No counselors loaded." << endl;
        } else {
            // Sort counselors using cocktail sort
            cocktailSortCounselorsByName();
            
            cout << "ID\tName\t\t\tSpecialty" << endl;
            cout << "----------------------------------------" << endl;
            for(int i = 0; i < counselorCount; i++) {
                cout << counselors[i].counselorID << "\t"
                     << counselors[i].name << "\t\t"
                     << counselors[i].specialty << endl;
            }
        }
        
        cout << "\nPress 'b' to go back to main menu or any other key to refresh: ";
        cin >> choice;
        cin.ignore();
        
    } while(choice != 'b' && choice != 'B');
}

// Search counselor by name using Jump Search with back option
void searchCounselorByName() {
    char choice;
    do {
        cout << "\n--- Search Counselor by Name (Jump Search) ---" << endl;
        
        if(counselorCount == 0) {
            cout << "No counselors loaded." << endl;
        } else {
            string counselorName;
            cout << "Enter Counselor Name: ";
            getline(cin, counselorName);
            
            // First sort counselors using cocktail sort
            cout << "Sorting counselors for jump search..." << endl;
            cocktailSortCounselorsByName();
            
            // Find the index using Jump Search (your format)
            int loc = jump_Search(counselors, counselorCount, counselorName);
            
            if(loc >= 0) {
                cout << "\n✓ SUCCESS: Counselor '" << counselorName << "' found at location: " << loc << endl;
                cout << "\nCounselor Details:" << endl;
                cout << "ID\tName\t\t\tSpecialty" << endl;
                cout << "----------------------------------------" << endl;
                cout << counselors[loc].counselorID << "\t"
                     << counselors[loc].name << "\t\t"
                     << counselors[loc].specialty << endl;
            } else {
                cout << "\n✗ NOT FOUND: Counselor '" << counselorName << "' is not found in the list." << endl;
                cout << "\nAvailable counselors:" << endl;
                for(int i = 0; i < counselorCount; i++) {
                    cout << "- " << counselors[i].name << endl;
                }
            }
        }
        
        cout << "\nPress 'b' to go back to main menu, 's' to search again, or any other key to refresh: ";
        cin >> choice;
        cin.ignore();
        
    } while(choice != 'b' && choice != 'B');
}

// Reload data with back option
void reloadData() {
    char choice;
    do {
        cout << "\n--- Reload Data ---" << endl;
        cout << "Reloading counselor data from file..." << endl;
        loadCounselorData();
        
        cout << "\nPress 'b' to go back to main menu or any other key to reload again: ";
        cin >> choice;
        cin.ignore();
        
    } while(choice != 'b' && choice != 'B');
}

// Display menu
void displayMenu() {
    cout << "\n========================================" << endl;
    cout << "    JUMP SEARCH SYSTEM" << endl;
    cout << "========================================" << endl;
    cout << "1. Display All Counselors" << endl;
    cout << "2. Display Sorted Counselors" << endl;
    cout << "3. Search Counselor by Name (Jump Search)" << endl;
    cout << "4. Reload Data from File" << endl;
    cout << "5. Exit" << endl;
    cout << "========================================" << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "    JUMP SEARCH DEMONSTRATION" << endl;
    cout << "========================================" << endl;
    
    cout << "\nLoading counselor data from file..." << endl;
    loadCounselorData();
    
    if(counselorCount == 0) {
        cout << "\nNo data loaded. Please ensure 'counselors.txt' exists with proper format:" << endl;
        cout << "Format per counselor:" << endl;
        cout << "[ID]" << endl;
        cout << "[Name]" << endl;
        cout << "[Specialty]" << endl;
        return 1;
    }
    
    int choice;
    
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer
        
        // Clear input buffer in case of invalid input
        if(cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }
        
        switch(choice) {
            case 1:
                displayAllCounselors();
                break;
            case 2:
                displaySortedCounselors();
                break;
            case 3:
                searchCounselorByName();
                break;
            case 4:
                reloadData();
                break;
            case 5:
                cout << "Exiting Jump Search System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                cout << "Press Enter to continue...";
                cin.get();
                break;
        }
        
    } while(choice != 5);
    
    return 0;
}