#include<iostream>
#include<string> 
#include<fstream>
#include<conio.h> // _getch()
#include<iomanip> // setw
using namespace std;

// HANNAH
struct appoint {
	string appointID; 		// Appointment ID
	string appointSvc; 		// Service (svc.txt)
	string appointCouns; 	// Counsellor Name (staff.txt)
	string appointMode; 	// Mode (Online or Offline)
	int appointDate; 		// Date (YYYYMMDD)
	string appointTime; 	// Time
	string appointPtName; 	// Patient Name
	int appointPtPhone; 	// Patient Phone
	string appointPtEmail; 	// Patient Email
	double appointGrossAmt; // Gross Amount (svc.txt)
	double appointNetAmt; 	// Net Amount
	string appointPayStat; 	// Payment Status (Unpaid or Paid)
	string appointStat; 	// Appointment Status (Pending, Approved, Rejected or Cancelled)
};

// HANNAH
struct cat {
	string catID; 	// Category ID
	string catName; // Category Name
};

// HANNAH
struct svc {
	string svcName;  // Service Name
	int svcDur; 	 // Service Duration
	double svcPrice; // Service Price 
};

// HANNAH
struct result { 
    string name;	  // Take Test User Name
    int phone;		  // Take Test User Phone
	string email;	  // Take Test User Email
    int score;		  // Test Score
    string situation; // Test Situation (Low Stress, Moderate Stress, High Stress or Very High Stress)
};

// HANNAH
struct qn {  
    string questionText; // Question
    string options[4];   // Question Options (Never, Sometimes, Often and Always)
    int points[4];       // Question Points (0, 1, 2 and 3)
};

// HANNAH
struct tx {
    string appointID;    // Appointment ID
    string ptName;       // Patient Name
    int ptPhone;     	 // Patient Phone
	string ptEmail;		 // Patient Email
    string summary;      // Treatment Summary
    string intervention; // Intervention Measures
    string response;     // Patient Response
    string progress;     // Treatment Progress
    string homework;     // Homework Assigned
    string nextSession;  // Next Session (Yes, Maybe or No)
};

// HANNAH
struct coupon {
	string couponCode; // Coupon Code
	float couponDis;   // Coupon Discount Percentage (0.5=50%)
	int couponQty;	   // Coupon Quantity
	string couponStat; // Coupon Status (Active or Inactive)
};

// HANNAH
struct ticket {
	string name; 	// Create Ticket User Name
	int phone;		// Create Ticket User Phone
	string email;	// Create Ticket User Email
	int date;		// Create Ticket Date
	string content; // Ticket Content
	string status;	// Ticket Status (Created, In Progress, Resolved or Closed)
};

// Function copied from TPD4124 project - TEO & FOOK
void maskPwd(string& password) {
    char ch;

    while ((ch = _getch()) != 13) { // 13 is Enter key
        if (ch == 8) { 				// 8 is backspace key
            if (!password.empty()) {
                password.erase(password.size() - 1);
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << '*';
        }
    }

    cout << endl;
}

// Function copied from TPD4124 project - TEO & FOOK
bool isValidEmail(const string& email) {
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);
	
    return atPos != string::npos && dotPos != string::npos && dotPos > atPos;
}

// Function copied from TPD4124 project - TEO & FOOK
bool isValidPhone(int phone) {
    string phoneStr = to_string(phone);
        
	if (phoneStr.length() >= 9 && phoneStr.length() <= 10) {
        return true;
    }
        
    return false;
}

// Function copied from TPD4124 project, TEO & FOOK
bool verifyCaptcha() {
    srand(time(0));
    int num1 = rand() % 10;
    int num2 = rand() % 10;
    int correctAnswer = num1 + num2;
    int userAnswer;
    
    cout << "Please solve this math problem: " << num1 << " + " << num2 << " = ";
    cin >> userAnswer;
    
    if (userAnswer == correctAnswer) {
        cout << "Verification successful!\n\n";
        return true;
    } else {
        cout << "Incorrect answer. Please try again.\n\n";
        return false;
    }
}

// FOOK
void checkAppointDateInput(int& date) {
    cout << "Enter Date (YYYYMMDD format): ";
    cin >> date;
    
    int day, mth, year;
    int maxDays;
    
    do {
        year = date / 10000;
        mth = (date / 100) % 100;
        day = date % 100;
  
        if (year != 2025) {
            cout << "Invalid selection. Please enter a date in 2025 (YYYYMMDD format): ";
            cin >> date;
            continue;
        }
  
        if (mth < 1 || mth > 12) {
            cout << "Invalid selection. Please enter a valid month (YYYYMMDD format): ";
            cin >> date;
            continue;
        }

        if (mth == 4 || mth == 6 || mth == 9 || mth == 11) {
            maxDays = 30;
        }
        else if (mth == 2) {
            maxDays = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
        }
        else {
            maxDays = 31;
        }

        if (day < 1 || day > maxDays) {
            cout << "Invalid selection. Please enter a valid day (1-" << maxDays << ") for month " << mth << ": ";
            cin >> date;
        }
    } while (day < 1 || day > maxDays || mth < 1 || mth > 12 || year != 2025);
}

// Base class for User - TEO
class User {
	private: 			 
		string fName; 	 // First name 
		string lName; 	 // Last name
		int phone; 	 	 // Phone
		string email; 	 // Email
		string password; // Password
		string status; 	 // Status (Active or Inactive)
		
	public:
		// Constructor
		User(string fName, string lName, int ph, string em, string pwd, string stat) {
			// Solution from ChatGPT: Use this-> to refer to the member variable because names are same
			this->fName= fName;
			this->lName= lName;
			this->phone= ph;
			this->email= em;
			this->password= pwd;
			this->status= stat;
		}
		
		// Destructor
		~User() {
		}

		/* 	[Error] 'std::string User::fName' is protected
			Suggestion by ChatGPT: Either change protected to public or using set & get functions */
	    string getFName() { 
			return fName; 
		}
		
	    void setFName(string& fName) { 
			this->fName = fName; 
		}
	
	    string getLName() { 
			return lName; 
		}
	    
		void setLName(string& lName) { 
			this->lName = lName; 
		}
	
	    int getPhone() { 
			return phone; 
		}
	    
		void setPhone(int phone) { 
			this->phone = phone; 
		}
	
	    string getEmail() { 
			return email; 
		}
	    
		void setEmail(string& email) { 
			this->email = email; 
		}
	
	    string getPassword() { 
			return password; 
		}
	    
		void setPassword( string& password) { 
			this->password = password; 
		}
	
	    string getStatus() { 
			return status; 
		}
	    
		void setStatus(string& status) { 
			this->status = status; 
		}
};

// Derived class for Staff - TEO
class Staff: public User {
	private:
		string nric;
		string role;
		
	public:
	    // Constructor
	    Staff(string fName, string lName, int phone, string email, string password, string status, string nric, string role)
	        : User(fName, lName, phone, email, password, status) { // This line is generated by ChatGPT, initialiser list that calls the parent class constructor
	        this->nric = nric;
	        this->role = role;
	    }
		
		// Destructor
		~Staff() {
		} 
		
		string getNric() { 
			return nric; 
		}

    	void setNric(string nric) { 
			this->nric = nric; 
		}

    	string getRole() { 
			return role; 
		}

    	void setRole(string role) { 
			this->role = role; 
		}	 
};

// Derived class for Patient - TEO
class Pt: public User {
	private:
		int age;
		
	public:
		// Constructor
		Pt(string fName, string lName, int phone, string email, string password, string status, int age)
		    : User(fName, lName, phone, email, password, status) { 
		    this->age = age;
		}

		// Destructor
		~Pt() {
		}
		
		int getAge() const { 
			return age; 
		}
		
    	void setAge(int age) { 
			this->age = age; 
		}
};

// Hash table for staffs using quadratic probing, TDS4223 lecture class - TEO
class StaffHT {
	private:
	    const int TBL_SIZE = 100;
	    Staff** tbl;
	
	    // Hash function for generate index to be saved in
	    int hashFn(int phone) {
	        return phone % TBL_SIZE;
	    }
	
	public:
	    // Constructor
	    StaffHT() {
	        tbl = new Staff*[TBL_SIZE];
	        for (int i = 0; i < TBL_SIZE; i++) { // This for loop is suggested and generated by ChatGPT
	            tbl[i] = NULL;
	        }
	    }
	
	    // Destructor
	    ~StaffHT() {
	        for (int i = 0; i < TBL_SIZE; i++) { // This for loop is suggested and generated by ChatGPT
	            if (tbl[i] != NULL) {
	                delete tbl[i];
	            }
	        }
	        delete[] tbl;
	    }

		// Getter for table element, function generated by ChatGPT
		Staff* getTableElement(int index) {
			if (index >= 0 && index < TBL_SIZE)
				return tbl[index];
			return NULL;
		}
		
		// Setter for table element, function generated by ChatGPT
		void setTableElement(int index, Staff* value) {
			if (index >= 0 && index < TBL_SIZE)
				tbl[index] = value;
		}

		// Getter for TBL_SIZE
		int getTblSize() {
			return TBL_SIZE;
		}
	
	    // Insert Staff into hash table using quadratic probing
	    void insert(Staff* staff) {
		    int hash = hashFn(staff->getPhone());
		    int i = 0;
		
		    // Quadratic probing
		    while (tbl[(hash + i * i) % TBL_SIZE] != NULL) {
		        i++;
		        if (i >= TBL_SIZE) {
		            cout << "Hash table is full!" << endl;
		            return;
		        }
		    }
		
		    // Found an empty slot, create a new Staff object and copy data
		    tbl[(hash + i * i) % TBL_SIZE] = new Staff(
		        staff->getFName(),
		        staff->getLName(),
		        staff->getPhone(),
		        staff->getEmail(),
		        staff->getPassword(),
		        staff->getStatus(),
		        staff->getNric(),
		        staff->getRole()
		    );
		}
	
	    // Load Staff from file and insert into hash table
	    void loadFromFile() {
		    ifstream inFile("staff.txt");
		    if (inFile.is_open()) {
		        bool isLoaded = false;
		        while (!inFile.eof()) {
		            string fName, lName, email, password, status, role, nric;
		            int phone;
		
		            if (!getline(inFile, fName) || fName.empty()) {
						break;  // Read first name, stop if empty or EOF
					} 

		            getline(inFile, lName); 	// Read last name
		            inFile >> phone;        	// Read phone
		            inFile.ignore();        	// Skip newline after phone, this line is generated by ChatGPT
		            getline(inFile, email);  	// Read email
		            getline(inFile, nric);   	// Read NRIC
		            getline(inFile, password); 	// Read password
		            getline(inFile, role);     	// Read role
		            getline(inFile, status);   	// Read status
		
		            // Create Staff object and insert into hash table
		            Staff* staff = new Staff(fName, lName, phone, email, password, status, nric, role);
		            insert(staff);
		
		            // Skip empty line (use to seperate record)
		            string temp;
		            getline(inFile, temp);
		
		            isLoaded = true;
		        }
		        inFile.close();
		        if (!isLoaded) {
		            // cout << "Staff loaded successfully!" << endl;
		        } else {
		            cout << "No staff found." << endl;
		        }
		    } else {
		        cout << "Unable to open staff.txt for reading." << endl;
		    }
		}
	
	    // Display all staff in the hash table
	    void displayAllStaff() {
	        int count = 0;
	        for (int i = 0; i < TBL_SIZE; i++) {
	            if (tbl[i] != NULL) {
	                cout << "\n--- Staff " << ++count << " ---" << endl;
	                cout << "First Name : " << tbl[i]->getFName() << endl;
	                cout << "Last Name  : " << tbl[i]->getLName() << endl;
	                cout << "Phone      : " << tbl[i]->getPhone() << endl;
	                cout << "Email      : " << tbl[i]->getEmail() << endl;
	                cout << "NRIC       : " << tbl[i]->getNric() << endl;
	                cout << "Role       : " << tbl[i]->getRole() << endl;
	                cout << "Status     : " << tbl[i]->getStatus() << endl;
	            }
	        }
	        if (count == 0) {
	            cout << "No staff found." << endl;
	        }
	    }
	    
	    // Sort staff by Email (Selection Sort)
		void sortByEmail() {
		    // Collect all non-NULL staff into an array
		    Staff** staffs = new Staff*[TBL_SIZE];
		    int size = 0;
		    
		    for (int i = 0; i < TBL_SIZE; i++) {
		        if (tbl[i] != NULL) {
		            staffs[size++] = tbl[i];
		        }
		    }
		    
		    // Selection sort by email
		    for (int i = 0; i < size - 1; i++) {
		        int currentMin = i; 
		        for (int j = i + 1; j < size; j++) {
		            if (staffs[j]->getEmail() < staffs[currentMin]->getEmail()) {
		                currentMin = j;
		            }
		        }
		        if (currentMin != i) {
		            Staff* temp = staffs[i];
		            staffs[i] = staffs[currentMin];
		            staffs[currentMin] = temp;
		        }
		    }
		    
		    // Display sorted staff
		    cout << "\n--- Staff Sorted by Email ---\n";
		    for (int i = 0; i < TBL_SIZE; i++) {
		        cout << "\n--- Staff " << i+1 << " ---" << endl;
		        cout << "First Name : " << staffs[i]->getFName() << endl;
		        cout << "Last Name  : " << staffs[i]->getLName() << endl;
		        cout << "Phone      : " << staffs[i]->getPhone() << endl;
		        cout << "Email      : " << staffs[i]->getEmail() << endl;
		        cout << "NRIC       : " << staffs[i]->getNric() << endl;
		        cout << "Role       : " << staffs[i]->getRole() << endl;
		        cout << "Status     : " << staffs[i]->getStatus() << endl;
		    }
		    
		    // Free the temporary array
		    delete[] staffs;
		}

		// Search Staff by Email (Binary Search)
		void searchByEmail() {
		    string targetEmail;
		    
		    cout << "\nEnter email to search: ";
		    cin.ignore();
		    getline(cin, targetEmail);

			if (!isValidEmail(targetEmail)) {
				cout << "Invalid email format. Please try again.\n" << endl;
				return;
			}
		    
		    // Count non-null staff
		    int count = 0;
		    for (int i = 0; i < TBL_SIZE; i++) {
		        if (tbl[i] != NULL) {
		            count++;
		        }
		    }
		        
		    if (count == 0) {
		        cout << "No staff available to search." << endl;
		        return;
		    }
		        
		    // Create dynamic array
		    Staff** staffs = new Staff*[count];
		    int index = 0;
		    for (int i = 0; i < TBL_SIZE; i++) {
		        if (tbl[i] != NULL) {
		            staffs[index++] = tbl[i];
		        }
		    }  
		     
		    // Sort by email first (selection sort)
		    for (int i = 0; i < count - 1; i++) {
		        int currentMin = i; 
		        for (int j = i + 1; j < count; j++) {
		            if (staffs[j]->getEmail() < staffs[currentMin]->getEmail()) {
		                currentMin = j;
		            }
		        }
		        if (currentMin != i) {
		            Staff* temp = staffs[i];
		            staffs[i] = staffs[currentMin];
		            staffs[currentMin] = temp;
		        }
		    }
		    
		    int first = 0;
		    int last = count - 1;
		    int found = 0;
		    
		    while (first <= last) {
		        int mid = first + (last - first) / 2;
		        string currentEmail = staffs[mid]->getEmail();
		
		        if (currentEmail == targetEmail) {
		            // Display the found staff
		            cout << "\n--- Staff Found ---" << endl;
		            cout << "First Name : " << staffs[mid]->getFName() << endl;
		            cout << "Last Name  : " << staffs[mid]->getLName() << endl;
		            cout << "Phone      : " << staffs[mid]->getPhone() << endl;
		            cout << "Email      : " << staffs[mid]->getEmail() << endl;
		            cout << "NRIC       : " << staffs[mid]->getNric() << endl;
		            cout << "Role       : " << staffs[mid]->getRole() << endl;
		            cout << "Status     : " << staffs[mid]->getStatus() << endl;
		            found = 1;
		
		            // Check for duplicates on left side
		            int firstDup = mid - 1;
		            while (firstDup >= 0 && staffs[firstDup]->getEmail() == targetEmail) {
		                cout << "\n--- Staff Found ---" << endl;
		                cout << "First Name : " << staffs[firstDup]->getFName() << endl;
		                cout << "Last Name  : " << staffs[firstDup]->getLName() << endl;
		                cout << "Phone      : " << staffs[firstDup]->getPhone() << endl;
		                cout << "Email      : " << staffs[firstDup]->getEmail() << endl;
		                cout << "NRIC       : " << staffs[firstDup]->getNric() << endl;
		                cout << "Role       : " << staffs[firstDup]->getRole() << endl;
		                cout << "Status     : " << staffs[firstDup]->getStatus() << endl;
		                found++;
		                firstDup--;
		            }
		
		            // Check for duplicates on right side
		            int lastDup = mid + 1;
		            while (lastDup < count && staffs[lastDup]->getEmail() == targetEmail) {
		                cout << "\n--- Staff Found ---" << endl;
		                cout << "First Name : " << staffs[lastDup]->getFName() << endl;
		                cout << "Last Name  : " << staffs[lastDup]->getLName() << endl;
		                cout << "Phone      : " << staffs[lastDup]->getPhone() << endl;
		                cout << "Email      : " << staffs[lastDup]->getEmail() << endl;
		                cout << "NRIC       : " << staffs[lastDup]->getNric() << endl;
		                cout << "Role       : " << staffs[lastDup]->getRole() << endl;
		                cout << "Status     : " << staffs[lastDup]->getStatus() << endl;
		                found++;
		                lastDup++;
		            }
		
		            cout << "\nTotal matches found: " << found << endl;
		            delete[] staffs;
		            return;
		        }
		
		        if (currentEmail < targetEmail) {
		            first = mid + 1;
		        } else {
		            last = mid - 1;
		        }
		    }
		
		    if (!found) {
		        cout << "No staff found with email: " << targetEmail << endl;
		    }
		    delete[] staffs; 
		}
		
		// Make UserManager a friend so it can access private members
    	friend class UserManager;
			
		int getTableSize() { 
			return TBL_SIZE; 
		}
		
		Staff* getEntry(int index) { 
			return tbl[index]; 
		}
};

// TEO
class StaffManager {
	public:
	    void addStaff(StaffHT& staffTable) {
	        string fName, lName, email, password, status, role, nric;
	        int phone;
	
	        cout << "\nEnter First Name: ";
	        cin.ignore(); 
	        getline(cin, fName);
	        cout << "Enter Last Name: ";
	        getline(cin, lName);
	        cout << "Enter Phone Number: +60";
			bool validPhone = false;

			while (!validPhone) {
				if (cin >> phone) {
					if (isValidPhone(phone)) {
						validPhone = true;
					} else {
						cout << "Invalid phone number. Please enter 9-10 digits: +60";
					}
				}
			}

			cin.ignore();

			bool validEmail = false;
			while (!validEmail) {
				cout << "Enter Email: ";
				cin >> email;
				if (isValidEmail(email)) {
					validEmail = true;
				} else {
					cout << "Invalid email format. Please try again.\n";
				}
			}

			cin.ignore();
	        cout << "\nEnter NRIC: ";
	        getline(cin, nric);
	        cout << "Enter Password: ";
			maskPwd(password);
			int roleOp;
			bool roleLoop=1;

			do {
				cout << "\n--- Available Roles ---\n";
				cout << "1. Admin\n";
				cout << "2. Staff\n";
				cout << "3. Counsellor\n\n";

				cout << "Select role (1-3): ";
				cin >> roleOp;

				switch(roleOp) {
					case 1: {
						role="Admin";
						cout << "Selected: Admin\n\n";
						roleLoop=1;
						break;
					}

					case 2: {
						role="Staff";
						cout << "Selected: Staff\n\n";
						roleLoop=1;
						break;
					}

					case 3: {
						role="Counsellor";
						cout << "Selected: Counsellor\n\n";
						roleLoop=1;
						break;
					}

					default: {
						cout << "Invalid choice, please try again.\n";
						roleLoop=0;
					}
				}
			} while(roleLoop==0);

			cin.ignore();
			
			status="Active";
	
	        // Create new Staff object
	        Staff* newStaff = new Staff(fName, lName, phone, email, password, status, nric, role);
	
	        char choice;
	        cout << "Do you want to save this staff? (Y/N): ";
	        cin >> choice;
	
	        if (toupper(choice) == 'Y') {
	            saveStaffToFile(newStaff);
	            staffTable.insert(newStaff); 
	        } else {
	            delete newStaff; // Clean up if not saving
				cout << "Staff not saved!" << endl;
	        }
	    }
	
	    void saveStaffToFile(Staff* staff) {
	        ofstream outFile;
	        outFile.open("staff.txt", ios::app);
	
	        if (outFile.is_open()) {
	            outFile << staff->getFName() << endl;
	            outFile << staff->getLName() << endl;
	            outFile << staff->getPhone() << endl;
	            outFile << staff->getEmail() << endl;
	            outFile << staff->getNric() << endl;
	            outFile << staff->getPassword() << endl;
	            outFile << staff->getRole() << endl;
	            outFile << staff->getStatus() << endl << endl;
	
	            cout << "Staff saved successfully!" << endl;
	            outFile.close();
	        } else {
	            cout << "Unable to open staff.txt for saving." << endl;
	        }
	    }
};

// HANNAH
class SvcHT {
	private:
		const int TBL_SIZE = 100;
		svc** tbl;

		// Hash function for service name
		int hashFn(string name) {
			int sum = 0;
			// for loop is generated by ChatGPT
			for (int i = 0; i < name.length(); i++) {
				sum += (int)name[i]; // Sum ASCII values
			}
			return sum % TBL_SIZE;   // Hashing to table size
		}

	public:
		// Constructor
		SvcHT() {
			tbl = new svc*[TBL_SIZE]; 
			for (int i = 0; i < TBL_SIZE; i++) {
				tbl[i] = NULL; 
			}
		}

		// Destructor
		~SvcHT() {
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					delete tbl[i];
				}
			}
			delete[] tbl;
		}

		// Insert service into the hash table using quadratic probing
		void insert(svc* service) {
			int hash = hashFn(service->svcName);
			int i = 0;

			// Quadratic probing
			while (tbl[(hash + i * i) % TBL_SIZE] != NULL) {
				i++;
				if (i >= TBL_SIZE) {
					cout << "Hash table is full!" << endl;
					return;
				}
			}

			// Found an empty slot
			tbl[(hash + i * i) % TBL_SIZE] = new svc;
			*tbl[(hash + i * i) % TBL_SIZE] = *service;
		}

		// Read services from file and insert into hash table
		void loadFromFile() {
			ifstream inFile("svc.txt");
			svc* service;

			if (inFile.is_open()) {
				while (!inFile.eof()) {
					service = new svc;

					getline(inFile, service->svcName);
					if (service->svcName.empty() || inFile.eof()) {
						delete service;
						break;
					}

					inFile >> service->svcDur; 
					inFile >> service->svcPrice; 
					inFile.ignore(); 
					
					string temp;
					getline(inFile, temp);

					insert(service);
				}
				inFile.close();
				// cout << "Services loaded successfully!" << endl;
			} else {
				cout << "Unable to open svc.txt for reading." << endl;
			}
		}

		// Display all services in the hash table
		void dispAllSvc() {
			int count = 0;
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					cout << "\n--- Service " << ++count << " ---" << endl;
					cout << "Service Name : " << tbl[i]->svcName << endl;
					cout << "Duration     : " << tbl[i]->svcDur << " minutes" << endl;
					cout << "Price        : RM " << tbl[i]->svcPrice << endl;
				}
			}
			if (count == 0) {
				cout << "No services found." << endl;
			}
		}

		int getTableSize() { 
			return TBL_SIZE; 
		}

		svc* getEntry(int index) { 
			return tbl[index]; 
		}

		void searchServiceByName() {
			// Convert services to array for selection
			svc* serviceArray[TBL_SIZE];
			int count = 0;
			
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					serviceArray[count++] = tbl[i];
				}
			}
			
			if (count == 0) {
				cout << "No services available to search." << endl;
				return;
			}
			
			// Sort array by name
			for (int i = 0; i < count - 1; i++) {
				int minIndex = i; // Assume current position has the alphabetically first name
				
				// Find the service with the "smallest" name in unsorted portion
				for (int j = i + 1; j < count; j++) {
					if (serviceArray[j]->svcName < serviceArray[minIndex]->svcName) {
						minIndex = j;
					}
				}
				
				// Swap if needed
				if (minIndex != i) {
					svc* temp = serviceArray[i];
					serviceArray[i] = serviceArray[minIndex];
					serviceArray[minIndex] = temp;
				}
			}
			
			// Display available services
			cout << "\n--- Available Services ---\n";
			for (int i = 0; i < count; i++) {
				cout << i+1 << ". " << serviceArray[i]->svcName << endl;
			}
			
			// Get user selection
			int selection;
			do {
				cout << "\nSelect a service (1-" << count << "): ";
				cin >> selection;
				
				if (selection < 1 || selection > count) {
					cout << "Invalid selection. Please choose from the list (1-" << count << ")." << endl;
				}
			} while (selection < 1 || selection > count);
			
			string name = serviceArray[selection-1]->svcName;
			
			// Binary search
			int left = 0, right = count - 1;
			bool found = false;
			
			while (left <= right) {
				int mid = left + (right - left) / 2;
				
				if (serviceArray[mid]->svcName == name) {
					cout << "\n--- Service Found ---" << endl;
					cout << "Name     : " << serviceArray[mid]->svcName << endl;
					cout << "Duration : " << serviceArray[mid]->svcDur << endl;
					cout << "Price    : " << serviceArray[mid]->svcPrice << endl;
					found = true;
					break;
				}
				
				if (serviceArray[mid]->svcName < name) {
					left = mid + 1;
				} else {
					right = mid - 1;
				}
			}
			
			if (!found) {
				cout << "Service not found." << endl;
			}
		}

		void editService() {
			// Create an array of services
			svc* serviceArray[TBL_SIZE];
			int count = 0;
			
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					serviceArray[count++] = tbl[i];
				}
			}
			
			if (count == 0) {
				cout << "No services available to edit." << endl;
				return;
			}
			
			// Display all services with numbers
			cout << "\n--- Available Services ---\n";
			for (int i = 0; i < count; i++) {
				cout << (i+1) << ". " << serviceArray[i]->svcName << endl;
			}
			
			// Let user select a service
			int serviceChoice;
			cout << "\nEnter the number of the service to edit (1-" << count << "): ";
			cin >> serviceChoice;
			
			if (serviceChoice < 1 || serviceChoice > count) {
				cout << "Invalid selection." << endl;
				return;
			}
			
			svc* selectedService = serviceArray[serviceChoice-1];
			int choice;
			
			do {
				cout << "\n--- Edit Service ---" << endl;
				cout << "1. Edit Service Name (Current: " << selectedService->svcName << ")" << endl;
				cout << "2. Edit Price        (Current: " << selectedService->svcPrice << ")" << endl;
				cout << "3. Edit Duration     (Current: " << selectedService->svcDur << ")" << endl;
				cout << "0. Save and Return\n" << endl;
				cout << "Select field to edit (0-3): ";
				cin >> choice;
				
				cin.ignore();
				
				switch(choice) {
					case 1: {
						string newName;
						cout << "Enter new Service Name: ";
						getline(cin, newName);
						selectedService->svcName = newName;
						break;
					}
					case 2: {
						double newPrice;
						cout << "Enter new Price: ";
						cin >> newPrice;
						selectedService->svcPrice = newPrice;
						break;
					}
					case 3: {
						int newDuration;
						cout << "Enter new Duration: ";
						cin >> newDuration;
						selectedService->svcDur = newDuration;
						break;
					}
					case 0:
						cout << selectedService->svcName << "service updated successfully!" << endl;
						break;
					default:
						cout << "Invalid choice, please try again." << endl;
				}
			} while (choice != 0);
		}

		void deleteService() {
			// Create an array of services
			svc* serviceArray[TBL_SIZE];
			int count = 0;
			
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					serviceArray[count++] = tbl[i];
				}
			}
			
			if (count == 0) {
				cout << "No services available to delete." << endl;
				return;
			}
			
			// Display all services with numbers
			cout << "\n--- Available Services ---\n";
			for (int i = 0; i < count; i++) {
				cout << (i+1) << ". " << serviceArray[i]->svcName << endl;
			}
			
			// Let user select a service
			int choice;
			cout << "\nEnter the number of the service to delete (1-" << count << "): ";
			cin >> choice;
			
			if (choice < 1 || choice > count) {
				cout << "Invalid selection." << endl;
				return;
			}
			
			svc* selectedService = serviceArray[choice-1];
			
			// Find and delete the selected service in the hash tableï¼Œthis for loop generated from ChatGPT
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] == selectedService) {
					delete tbl[i];
					tbl[i] = NULL;
					cout << "Service deleted successfully." << endl;
					return;
				}
			}
		}

		void sortServicesByPriceLowToHigh() {
		// Create an array of services
		svc* serviceArray[TBL_SIZE];
		int count = 0;
		
		// Collect non-NULL services
		for (int i = 0; i < TBL_SIZE; i++) {
			if (tbl[i] != NULL) {
				serviceArray[count++] = tbl[i];
			}
		}
		
		// Selection Sort (ascending order by price)
		for (int i = 0; i < count - 1; i++) {
			int minIndex = i; // Assume current position is the minimum
			
			// Find the minimum price in the remaining unsorted array
			for (int j = i + 1; j < count; j++) {
				if (serviceArray[j]->svcPrice < serviceArray[minIndex]->svcPrice) {
					minIndex = j;
				}
			}
			
			// Swap if a smaller price is found
			if (minIndex != i) {
				svc* temp = serviceArray[i];
				serviceArray[i] = serviceArray[minIndex];
				serviceArray[minIndex] = temp;
			}
		}
			
			// Display sorted services
			cout << "\n--- Services Sorted by Price (Low to High) ---\n\n";
			cout << left << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Duration" << endl;
			cout << string(50, '-') << endl;
			
			for (int i = 0; i < count; i++) {
				cout << left << setw(20) << serviceArray[i]->svcName 
					<< setw(10) << serviceArray[i]->svcPrice 
					<< setw(10) << serviceArray[i]->svcDur << endl;
			}
		}

		void sortServicesByPriceHighToLow() {
			// Create an array of services
			svc* serviceArray[TBL_SIZE];
			int count = 0;
			
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					serviceArray[count++] = tbl[i];
				}
			}
			
			// Selection Sort (descending order by price)
			for (int i = 0; i < count - 1; i++) {
				int maxIndex = i; // Assume current position is the minimum
			
				// Find the minimum price in the remaining unsorted array
				for (int j = i + 1; j < count; j++) {
					if (serviceArray[j]->svcPrice > serviceArray[maxIndex]->svcPrice) {
						maxIndex = j;
					}
				}
			
				// Swap if a smaller price is found
				if (maxIndex != i) {
					svc* temp = serviceArray[i];
					serviceArray[i] = serviceArray[maxIndex];
					serviceArray[maxIndex] = temp;
				}
			}
			
			// Display sorted services
			cout << "\n--- Services Sorted by Price (High to Low) ---\n\n";
			cout << left << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Duration" << endl;
			cout << string(50, '-') << endl;
			
			for (int i = 0; i < count; i++) {
				cout << left << setw(20) << serviceArray[i]->svcName 
					<< setw(10) << serviceArray[i]->svcPrice 
					<< setw(10) << serviceArray[i]->svcDur << endl;
			}
		}

		void sortServicesByDurationShortToLong() {
			// Create an array of services
			svc* serviceArray[TBL_SIZE];
			int count = 0;
			
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					serviceArray[count++] = tbl[i];
				}
			}
			
			// Selection Sort (ascending order by duration)
			for (int i = 0; i < count - 1; i++) {
				int minIndex = i; // Assume current position is the minimum
			
				// Find the minimum price in the remaining unsorted array
				for (int j = i + 1; j < count; j++) {
					if (serviceArray[j]->svcDur < serviceArray[minIndex]->svcDur) {
						minIndex = j;
					}
				}
			
				// Swap if a smaller price is found
				if (minIndex != i) {
					svc* temp = serviceArray[i];
					serviceArray[i] = serviceArray[minIndex];
					serviceArray[minIndex] = temp;
				}
			}
			
			// Display sorted services
			cout << "\n--- Services Sorted by Duration (Short to Long) ---\n\n";
			cout << left << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Duration" << endl;
			cout << string(50, '-') << endl;
			
			for (int i = 0; i < count; i++) {
				cout << left << setw(20) << serviceArray[i]->svcName 
					<< setw(10) << serviceArray[i]->svcPrice 
					<< setw(10) << serviceArray[i]->svcDur << endl;
			}
		}

		void sortServicesByDurationLongToShort() {
		// Create an array of services
		svc* serviceArray[TBL_SIZE];
		int count = 0;
		
		for (int i = 0; i < TBL_SIZE; i++) {
			if (tbl[i] != NULL) {
				serviceArray[count++] = tbl[i];
			}
		}
		
		// Selection Sort (descending order by duration - longest to shortest)
		for (int i = 0; i < count - 1; i++) {
			int maxIndex = i; // Track position of maximum duration
			
			// Find the service with maximum duration in unsorted portion
			for (int j = i + 1; j < count; j++) {
				if (serviceArray[j]->svcDur > serviceArray[maxIndex]->svcDur) {
					maxIndex = j;
				}
			}
			
			// Swap if a longer duration is found
			if (maxIndex != i) {
				svc* temp = serviceArray[i];
				serviceArray[i] = serviceArray[maxIndex];
				serviceArray[maxIndex] = temp;
			}
		}
		
		// Display sorted services
		cout << "\n--- Services Sorted by Duration (Long to Short) ---\n\n";
		cout << left << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Duration" << endl;
		cout << string(50, '-') << endl;
		
		for (int i = 0; i < count; i++) {
			cout << left << setw(20) << serviceArray[i]->svcName 
				<< setw(10) << serviceArray[i]->svcPrice 
				<< setw(10) << serviceArray[i]->svcDur << endl;
		}
	}
};

// HANNAH
class Svc {
	public:
	    // Function to add a new service
	    void addSvc(SvcHT& serviceTable) {
	        string name;
	        int duration;
	        double price;
	
	        cout << "\nEnter Service Name: ";
	        cin.ignore();
	        getline(cin, name);
	        cout << "Enter Service Duration (in minutes): ";
	        cin >> duration;
	        cout << "Enter Service Price: ";
	        cin >> price;
	
	        svc newService;
	        newService.svcName = name;
	        newService.svcDur = duration;
	        newService.svcPrice = price;
	
	        char choice;
	        cout << "\nDo you want to save this service? (Y/N): ";
	        cin >> choice;
	
	        if (toupper(choice) == 'Y') {
	            saveSvcToFile(newService);  
	            serviceTable.insert(&newService);  
	        } else {
				cout << "Service not saved!" << endl;
			}
	    }
	
	    // Save service to file
	    void saveSvcToFile(svc& service) {
	        ofstream outFile;
	        outFile.open("svc.txt", ios::app); 
	
	        if (outFile.is_open()) {
	            outFile << service.svcName << endl;
	            outFile << service.svcDur << endl;
	            outFile << service.svcPrice << endl << endl;
	
	            cout << "Service saved successfully!" << endl;
	            outFile.close();
	        } else {
	            cout << "Unable to open svc.txt for saving." << endl;
	        }
	    }
};

// HANNAH
class CouponHT {
	private:
		const int TBL_SIZE = 100;
		coupon** tbl; 
		
		// Hash function for coupon code
		int hashFn(const string& code) {
			int sum = 0;
			for (int i = 0; i < code.length(); i++) {
				sum += (int)code[i]; 	// Sum ASCII values
			}
			return sum % TBL_SIZE; 		// Hashing to table size
		}

	public:
		// Constructor
		CouponHT() {
			tbl = new coupon*[TBL_SIZE]; 
			for (int i = 0; i < TBL_SIZE; i++) {
				tbl[i] = NULL; 
			}
		}
		
		// Destructor
		~CouponHT() {
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					delete tbl[i]; 
				}
			}
			delete[] tbl; // Free the dynamic array
		}

		// Add to CouponHT class
		int getTableSize() const {
			return TBL_SIZE;
		}

		coupon* getEntry(int index) const {
			if (index >= 0 && index < TBL_SIZE)
				return tbl[index];
			return NULL;
		}
		
		// Insert coupon into the hash table using quadratic probing
		void insert(coupon* cp) {
			int hash = hashFn(cp->couponCode);
			int i = 0;
			
			// Quadratic probing
			while (tbl[(hash + i * i) % TBL_SIZE] != NULL) {
				i++;
				if (i >= TBL_SIZE) {
					cout << "Hash table is full!" << endl;
					return;
				}
			}
			
			// Found an empty slot, create a new coupon object and copy data
			tbl[(hash + i * i) % TBL_SIZE] = new coupon;
			*tbl[(hash + i * i) % TBL_SIZE] = *cp; 
		}
		
		// Load coupons from file (coupon.txt)
		void loadFromFile() {
			ifstream inFile("coupon.txt");
			
			if (!inFile.is_open()) {
				cout << "Unable to open coupon.txt for reading." << endl;
				return;
			}
			
			// Clear existing entries
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					delete tbl[i];
					tbl[i] = NULL;
				}
			}
			
			string code, status, line;
			float discount;
			int qty;
			
			while (getline(inFile, code)) {
				// Skip empty lines
				if (code.empty()) {
					continue;
				}
				
				// Read discount
				if (!(inFile >> discount)) {
					break;
				}
				inFile.ignore(); // Skip newline
				
				// Read quantity
				if (!(inFile >> qty)) {
					break;
				}
				inFile.ignore(); // Skip newline
				
				// Read status
				if (!getline(inFile, status)) {
					break;
				}
				
				// Skip empty line if present
				getline(inFile, line);
				
				// Create and insert coupon
				coupon* cp = new coupon();
				cp->couponCode = code;
				cp->couponDis = discount;
				cp->couponQty = qty;
				cp->couponStat = status;
				
				// cout << cp->couponCode << ", Discount: " << cp->couponDis << ", Qty: " << cp->couponQty << ", Status: '" << cp->couponStat << "'" << endl;
				
				insert(cp);
			}
			
			inFile.close();
		}

		// Display all coupons in hash table
		void displayAllCoupons() {
			int count = 0;
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					cout << "\n--- Coupon " << ++count << " ---" << endl;
					cout << "Coupon Code     : " << tbl[i]->couponCode << endl;
					cout << "Discount        : " << tbl[i]->couponDis * 100 << "%" << endl;
					cout << "Quantity Left   : " << tbl[i]->couponQty << endl;
					cout << "Status          : " << tbl[i]->couponStat << endl;
				}
			}
			if (count == 0) {
				cout << "No coupons found." << endl;
			}
		}
		
		// Save new coupon to coupon.txt
		void saveCouponToFile(coupon* cp) {
			ofstream outFile;
			outFile.open("coupon.txt", ios::app); 
			
			if (outFile.is_open()) {
				outFile << cp->couponCode << endl;
				outFile << cp->couponDis << endl;
				outFile << cp->couponQty << endl;
				outFile << cp->couponStat << endl << endl;
				cout << "Coupon saved successfully!" << endl;
				outFile.close();
			} else {
				cout << "Unable to open coupon.txt for saving." << endl;
			}
		}
		
		// Edit an existing coupon
		void editCoupon() {
			// Create an array of coupons
			coupon* couponArray[TBL_SIZE];
			int count = 0;
			
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					couponArray[count++] = tbl[i];
				}
			}
			
			if (count == 0) {
				cout << "No coupons available to edit." << endl;
				return;
			}
			
			// Display all coupons with numbers
			cout << "\n--- Available Coupons ---\n";
			for (int i = 0; i < count; i++) {
				cout << (i+1) << ". " << couponArray[i]->couponCode << " (" 
					<< couponArray[i]->couponDis * 100 << "%, " 
					<< couponArray[i]->couponQty << " left, " 
					<< couponArray[i]->couponStat << ")" << endl;
			}
			
			// Let user select a coupon
			int couponChoice;
			cout << "\nEnter the number of the coupon to edit (1-" << count << "): ";
			cin >> couponChoice;
			
			if (couponChoice < 1 || couponChoice > count) {
				cout << "Invalid selection." << endl;
				return;
			}
			
			coupon* selectedCoupon = couponArray[couponChoice-1];
			int choice;
			
			do {
				cout << "\n--- Edit Coupon ---" << endl;
				cout << "1. Edit Coupon Code     (Current: " << selectedCoupon->couponCode << ")" << endl;
				cout << "2. Edit Discount        (Current: " << selectedCoupon->couponDis * 100 << "%)" << endl;
				cout << "3. Edit Quantity        (Current: " << selectedCoupon->couponQty << ")" << endl;
				cout << "4. Edit Status          (Current: " << selectedCoupon->couponStat << ")" << endl;
				cout << "0. Save and Return\n" << endl;
				cout << "Select field to edit (0-4): ";
				cin >> choice;
				
				cin.ignore();
				
				switch(choice) {
					case 1: {
						string newCode;
						cout << "Enter new Coupon Code: ";
						getline(cin, newCode);
						selectedCoupon->couponCode = newCode;
						break;
					}
					case 2: {
						float newDiscount;
						cout << "Enter new Discount (as decimal, e.g., 0.5 for 50%): ";
						cin >> newDiscount;
						selectedCoupon->couponDis = newDiscount;
						break;
					}
					case 3: {
						int newQuantity;
						cout << "Enter new Quantity: ";
						cin >> newQuantity;
						selectedCoupon->couponQty = newQuantity;
						break;
					}
					case 4: {
						int statusChoice;
						cout << "\n--- Available Status ---\n";
						cout << "1. Active\n";
						cout << "2. Inactive\n\n";
						
						do {
							cout << "Select status (1-2): ";
							cin >> statusChoice;
							
							if (statusChoice < 1 || statusChoice > 2) {
								cout << "Invalid selection. Please choose from the list (1-2)." << endl;
							}
						} while (statusChoice < 1 || statusChoice > 2);
						
						selectedCoupon->couponStat = (statusChoice == 1) ? "Active" : "Inactive";
						cout << "Selected: " << selectedCoupon->couponStat << endl;
						break;
					}
					case 0:
						updateCouponFile();
						cout << selectedCoupon->couponCode << " coupon updated successfully!" << endl;
						break;
					default:
						cout << "Invalid choice, please try again." << endl;
				}
			} while (choice != 0);
		}
		
		// Delete a coupon
		void deleteCoupon() {
			// Create an array of coupons
			coupon* couponArray[TBL_SIZE];
			int count = 0;
			int tableIndices[TBL_SIZE]; // To track original indices
			
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					couponArray[count] = tbl[i];
					tableIndices[count] = i;
					count++;
				}
			}
			
			if (count == 0) {
				cout << "No coupons available to delete." << endl;
				return;
			}
			
			// Display all coupons with numbers
			cout << "\n--- Available Coupons ---\n";
			for (int i = 0; i < count; i++) {
				cout << (i+1) << ". " << couponArray[i]->couponCode << " (" 
					<< couponArray[i]->couponDis * 100 << "%, " 
					<< couponArray[i]->couponQty << " left, " 
					<< couponArray[i]->couponStat << ")" << endl;
			}
			
			// Let user select a coupon
			int couponChoice;
			cout << "\nEnter the number of the coupon to delete (1-" << count << "): ";
			cin >> couponChoice;
			
			if (couponChoice < 1 || couponChoice > count) {
				cout << "Invalid selection." << endl;
				return;
			}
			
			int selectedIndex = tableIndices[couponChoice-1];
			coupon* selectedCoupon = tbl[selectedIndex];
			
			char confirm;
			cout << "\nAre you sure you want to delete coupon " 
				<< selectedCoupon->couponCode << "? (Y/N): ";
			cin >> confirm;
			
			if (toupper(confirm) == 'Y') {
				// Delete the coupon from the hash table
				delete tbl[selectedIndex];
				
				// Set the entry to NULL
				tbl[selectedIndex] = NULL;
				
				// Update the file
				updateCouponFile();
				cout << "Coupon deleted successfully!" << endl;
			} else {
				cout << "Deletion cancelled." << endl;
			}
		}
		
		// Update coupon.txt file after edits or deletions
		void updateCouponFile() {
			ofstream outFile("coupon.txt");
			
			if (outFile.is_open()) {
				for (int i = 0; i < TBL_SIZE; i++) {
					if (tbl[i] != NULL) {
						outFile << tbl[i]->couponCode << endl;
						outFile << tbl[i]->couponDis << endl;
						outFile << tbl[i]->couponQty << endl;
						outFile << tbl[i]->couponStat << endl << endl;
					}
				}
				outFile.close();
			} else {
				cout << "Unable to open coupon.txt for updating." << endl;
			}
		}

		void sortCouponsByDiscountLowToHigh() {
			// Create an array of coupons
			coupon* couponArray[TBL_SIZE];
			int count = 0;
			
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					couponArray[count++] = tbl[i];
				}
			}
			
			// Selection sort by discount (low to high)
			for (int i = 0; i < count - 1; i++) {
				int minIndex = i;
				
				// Find the coupon with minimum discount in unsorted portion
				for (int j = i + 1; j < count; j++) {
					if (couponArray[j]->couponDis < couponArray[minIndex]->couponDis) {
						minIndex = j;
					}
				}
				
				// Swap if a smaller discount is found
				if (minIndex != i) {
					coupon* temp = couponArray[i];
					couponArray[i] = couponArray[minIndex];
					couponArray[minIndex] = temp;
				}
			}
			
			// Display sorted coupons
			cout << "\n--- Coupons Sorted by Discount (Least to Most) ---\n\n";
			cout << left << setw(15) << "Code" << setw(15) << "Discount (%)" << setw(10) << "Stock" << setw(10) << "Status" << endl;
			cout << string(50, '-') << endl;
			
			for (int i = 0; i < count; i++) {
				cout << left << setw(15) << couponArray[i]->couponCode 
					<< setw(15) << (couponArray[i]->couponDis * 100)
					<< setw(10) << couponArray[i]->couponQty 
					<< setw(10) << couponArray[i]->couponStat << endl;
			}
		}

		void sortCouponsByDiscountHighToLow() {
			// Create an array of coupons
			coupon* couponArray[TBL_SIZE];
			int count = 0;
			
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					couponArray[count++] = tbl[i];
				}
			}
			
			// Selection sort by discount (high to low)
			for (int i = 0; i < count - 1; i++) {
				int maxIndex = i; 
				
				// Find the coupon with maximum discount in unsorted portion
				for (int j = i + 1; j < count; j++) {
					if (couponArray[j]->couponDis > couponArray[maxIndex]->couponDis) {
						maxIndex = j;
					}
				}
				
				// Swap if a higher discount is found
				if (maxIndex != i) {
					coupon* temp = couponArray[i];
					couponArray[i] = couponArray[maxIndex];
					couponArray[maxIndex] = temp;
				}
			}
			
			// Display sorted coupons
			cout << "\n--- Coupons Sorted by Discount (Most to Least) ---\n\n";
			cout << left << setw(15) << "Code" << setw(15) << "Discount (%)" << setw(10) << "Stock" << setw(10) << "Status" << endl;
			cout << string(50, '-') << endl;
			
			for (int i = 0; i < count; i++) {
				cout << left << setw(15) << couponArray[i]->couponCode 
					<< setw(15) << (couponArray[i]->couponDis * 100)
					<< setw(10) << couponArray[i]->couponQty 
					<< setw(10) << couponArray[i]->couponStat << endl;
			}
		}

		void sortCouponsByStockLowToHigh() {
			// Create an array of coupons
			coupon* couponArray[TBL_SIZE];
			int count = 0;
			
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					couponArray[count++] = tbl[i];
				}
			}
			
			// Selection sort by stock quantity (low to high)
			for (int i = 0; i < count - 1; i++) {
				int minIndex = i; 
				
				// Find the coupon with minimum stock in unsorted portion
				for (int j = i + 1; j < count; j++) {
					if (couponArray[j]->couponQty < couponArray[minIndex]->couponQty) {
						minIndex = j;
					}
				}
				
				// Swap if a smaller stock quantity is found
				if (minIndex != i) {
					coupon* temp = couponArray[i];
					couponArray[i] = couponArray[minIndex];
					couponArray[minIndex] = temp;
				}
			}
			
			// Display sorted coupons
			cout << "\n--- Coupons Sorted by Stock (Least to Most) ---\n\n";
			cout << left << setw(15) << "Code" << setw(15) << "Discount (%)" << setw(10) << "Stock" << setw(10) << "Status" << endl;
			cout << string(50, '-') << endl;
			
			for (int i = 0; i < count; i++) {
				cout << left << setw(15) << couponArray[i]->couponCode 
					<< setw(15) << (couponArray[i]->couponDis * 100)
					<< setw(10) << couponArray[i]->couponQty 
					<< setw(10) << couponArray[i]->couponStat << endl;
			}
		}

		void sortCouponsByStockHighToLow() {
			// Create an array of coupons
			coupon* couponArray[TBL_SIZE];
			int count = 0;
			
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					couponArray[count++] = tbl[i];
				}
			}
			
			// Selection sort by stock quantity (high to low)
			for (int i = 0; i < count - 1; i++) {
				int maxIndex = i; 
				
				// Find the coupon with maximum stock in unsorted portion
				for (int j = i + 1; j < count; j++) {
					if (couponArray[j]->couponQty > couponArray[maxIndex]->couponQty) {
						maxIndex = j;
					}
				}
				
				// Swap if a larger stock quantity is found
				if (maxIndex != i) {
					coupon* temp = couponArray[i];
					couponArray[i] = couponArray[maxIndex];
					couponArray[maxIndex] = temp;
				}
			}
			
			// Display sorted coupons
			cout << "\n--- Coupons Sorted by Stock (Most to Least) ---\n\n";
			cout << left << setw(15) << "Code" << setw(15) << "Discount (%)" << setw(10) << "Stock" << setw(10) << "Status" << endl;
			cout << string(50, '-') << endl;
			
			for (int i = 0; i < count; i++) {
				cout << left << setw(15) << couponArray[i]->couponCode 
					<< setw(15) << (couponArray[i]->couponDis * 100)
					<< setw(10) << couponArray[i]->couponQty 
					<< setw(10) << couponArray[i]->couponStat << endl;
			}
		}

		void searchCouponByCode() {
			// Convert coupons to array for selection
			coupon* couponArray[TBL_SIZE];
			int count = 0;
			
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					couponArray[count++] = tbl[i];
				}
			}
			
			if (count == 0) {
				cout << "No coupons available to search." << endl;
				return;
			}
			
			// Sort array by code
			for (int i = 0; i < count - 1; i++) {
			int minIndex = i; // Track position of minimum code
			
			// Find the coupon with minimum code in unsorted portion
			for (int j = i + 1; j < count; j++) {
				if (couponArray[j]->couponCode < couponArray[minIndex]->couponCode) {
					minIndex = j;
				}
			}
			
			// Swap if a smaller code is found
			if (minIndex != i) {
				coupon* temp = couponArray[i];
				couponArray[i] = couponArray[minIndex];
				couponArray[minIndex] = temp;
			}
		}
			
			// Display available coupons
			cout << "\n--- Available Coupons ---\n";
			for (int i = 0; i < count; i++) {
				cout << i+1 << ". " << couponArray[i]->couponCode << endl;
			}
			
			// Get user selection
			int selection;
			do {
				cout << "\nSelect a coupon (1-" << count << "): ";
				cin >> selection;
				
				if (selection < 1 || selection > count) {
					cout << "Invalid selection. Please choose from the list (1-" << count << ")." << endl;
				}
			} while (selection < 1 || selection > count);
			
			string code = couponArray[selection-1]->couponCode;
			
			// Binary search
			int left = 0, right = count - 1;
			bool found = false;
			
			while (left <= right) {
				int mid = left + (right - left) / 2;
				
				if (couponArray[mid]->couponCode == code) {
					cout << "\n--- Coupon Found ---" << endl;
					cout << "Code     : " << couponArray[mid]->couponCode << endl;
					cout << "Discount : " << couponArray[mid]->couponDis * 100 << "%" << endl;
					cout << "Stock    : " << couponArray[mid]->couponQty << endl;
					cout << "Status   : " << couponArray[mid]->couponStat << endl;
					found = true;
					break;
				}
				
				if (couponArray[mid]->couponCode < code) {
					left = mid + 1;
				} else {
					right = mid - 1;
				}
			}
			
			if (!found) {
				cout << "Coupon not found." << endl;
			}
		}

		void searchCouponByStatus() {
		// Convert coupons to array for selection
		coupon* couponArray[TBL_SIZE];
		int count = 0;
		
		for (int i = 0; i < TBL_SIZE; i++) {
			if (tbl[i] != NULL) {
				couponArray[count++] = tbl[i];
			}
		}
		
		if (count == 0) {
			cout << "No coupons available to search." << endl;
			return;
		}
		
		// Sort array by status
		for (int i = 0; i < count - 1; i++) {
			int minIndex = i; // Track position of minimum status value
			
			// Find the coupon with minimum status in unsorted portion
			for (int j = i + 1; j < count; j++) {
				if (couponArray[j]->couponStat < couponArray[minIndex]->couponStat) {
					minIndex = j;
				}
			}
			
			// Swap if a smaller status is found
			if (minIndex != i) {
				coupon* temp = couponArray[i];
				couponArray[i] = couponArray[minIndex];
				couponArray[minIndex] = temp;
			}
		}
		
		// Show status selection menu
		cout << "\n--- Search Coupons by Status ---\n";
		cout << "1. Active\n";
		cout << "2. Inactive\n";
		
		// Get user selection
		int selection;
		do {
			cout << "\nSelect a status (1-2): ";
			cin >> selection;
			
			if (selection < 1 || selection > 2) {
				cout << "Invalid selection. Please choose from the list (1-2)." << endl;
			}
		} while (selection < 1 || selection > 2);
		
		string status = (selection == 1) ? "Active" : "Inactive";
		
		// Binary search
		int left = 0, right = count - 1;
		bool found = false;
		
		// First find any matching status
		int foundIndex = -1;
		while (left <= right) {
			int mid = left + (right - left) / 2;
			
			if (couponArray[mid]->couponStat == status) {
				foundIndex = mid;
				found = true;
				break;
			}
			
			if (couponArray[mid]->couponStat < status) {
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		}
		
		if (!found) {
			cout << "No " << status << " coupons found." << endl;
			return;
		}
		
		// Find all coupons with the same status
		cout << "\n--- " << status << " Coupons ---\n\n";
		cout << left << setw(15) << "Code" << setw(15) << "Discount (%)" << setw(10) << "Stock" << endl;
		cout << string(40, '-') << endl;
		
		// Go left from foundIndex to find all matching coupons
		int startIndex = foundIndex;
		while (startIndex >= 0 && couponArray[startIndex]->couponStat == status) {
			startIndex--;
		}
		startIndex++;
		
		// Go right from startIndex to display all matching coupons
		int i = startIndex;
		while (i < count && couponArray[i]->couponStat == status) {
			cout << left << setw(15) << couponArray[i]->couponCode 
				<< setw(15) << (couponArray[i]->couponDis * 100)
				<< setw(10) << couponArray[i]->couponQty << endl;
			i++;
		}
	}
};

// HANNAH
class Coupon {
	public:
		// Function to add a new coupon
		void addCoupon(CouponHT& couponTable) {
			string code, status;
			float discount;
			int quantity;

			cout << "\nEnter Coupon Code: ";
			cin.ignore(); 
			getline(cin, code);
			
			cout << "Enter Discount (as decimal, e.g., 0.5 for 50%): ";
			cin >> discount;
			
			cout << "Enter Quantity: ";
			cin >> quantity;
			
			// Status selection
			int statusChoice;
			cout << "\n--- Available Status ---\n";
			cout << "1. Active\n";
			cout << "2. Inactive\n\n";
			
			do {
				cout << "Select status (1-2): ";
				cin >> statusChoice;
				
				if (statusChoice < 1 || statusChoice > 2) {
					cout << "Invalid selection. Please choose from the list (1-2)." << endl;
				}
			} while (statusChoice < 1 || statusChoice > 2);
			
			status = (statusChoice == 1) ? "Active" : "Inactive";
			cout << "Selected: " << status << endl;

			// Populate data
			coupon newCoupon;
			newCoupon.couponCode = code;
			newCoupon.couponDis = discount;
			newCoupon.couponQty = quantity;
			newCoupon.couponStat = status;

			char choice;
			cout << "\nDo you want to save this coupon? (Y/N): ";
			cin >> choice;

			if (toupper(choice) == 'Y') {
				couponTable.saveCouponToFile(&newCoupon);  
				couponTable.insert(&newCoupon); 
			} else {
				cout << "Coupon not saved!" << endl;
			}
		}
};

// TEO
class AppointHT {
	private:
		const int TBL_SIZE= 100;
		appoint** tbl;
		
	    int hashFn(string id) {
	        int sum = 0;
	        
	        for (int i = 0; i < id.length(); i++) { // Generate from ChatGPT
	            sum += (int)id[i];   // Sum ASCII values
	        }
	        
	        return sum % TBL_SIZE; 
	    }
	    
	public:
		// Constructor
	    AppointHT() {
	        tbl = new appoint*[TBL_SIZE]; // Dynamic array
	        for (int i = 0; i < TBL_SIZE; i++) {
	            tbl[i] = NULL;
	        }
	    }
	    
	    // Destructor
	    ~AppointHT() {
	        for (int i = 0; i < TBL_SIZE; i++) {
	            if (tbl[i] != NULL) {
	                delete tbl[i];
	            }
	        }
	        delete[] tbl;
	    }

		// Getter for table element
		appoint* getTableElement(int index) {
			if (index >= 0 && index < TBL_SIZE)
				return tbl[index];
			return NULL;
		}
		
		// Setter for table element
		void setTableElement(int index, appoint* value) {
			if (index >= 0 && index < TBL_SIZE)
				tbl[index] = value;
		}
	    
	    // Insert appointment using quadratic probing
	    void insert(appoint* apt) {
	        int hash = hashFn(apt->appointID);
	        int i = 0;
	        
	        while (tbl[(hash + i*i) % TBL_SIZE] != NULL) {
	            i++;
	            if (i >= TBL_SIZE) {
	                cout << "Hash table is full!" << endl;
	                return;
	            }
	        }
	        
	        // Found empty slot
	        tbl[(hash + i*i) % TBL_SIZE] = new appoint;
	        *tbl[(hash + i*i) % TBL_SIZE] = *apt;
	    }
	    
	    // Read appointments from file and insert into hash table 
		void loadFromFile() {
		    ifstream inFile("appoint.txt");
		    appoint* apt;
		    
		    if (inFile.is_open()) {
		        while (!inFile.eof()) {
		            apt = new appoint;
		            
		            getline(inFile, apt->appointID);
		            if (apt->appointID.empty() || inFile.eof()) {
		                delete apt;
		                break;
		            }
		            
		            getline(inFile, apt->appointSvc);
		            getline(inFile, apt->appointCouns);
		            getline(inFile, apt->appointMode);
		            inFile >> apt->appointDate;
		            inFile.ignore();
		            getline(inFile, apt->appointTime);
		            getline(inFile, apt->appointPtName);
		            inFile >> apt->appointPtPhone;
		            inFile.ignore();
		            getline(inFile, apt->appointPtEmail);
		            inFile >> apt->appointGrossAmt;
		            inFile >> apt->appointNetAmt;
		            inFile.ignore();
		            getline(inFile, apt->appointPayStat);
		            getline(inFile, apt->appointStat);
		            
		            string temp;
		            getline(inFile, temp);
		            
		            insert(apt);
		        }
		        inFile.close();
		    } else {
		        cout << "Unable to open appoint.txt for reading." << endl;
		    }
		}
		
		// Display all appointments in hash table
		void displayAllAppoint() {
		    int count = 0;
		    for (int i = 0; i < TBL_SIZE; i++) {
		        if (tbl[i] != NULL) {
		            cout << "\n--- Appointment " << ++count << " ---" << endl;
		            cout << "ID            : " << tbl[i]->appointID << endl;
		            cout << "Service       : " << tbl[i]->appointSvc << endl;
		            cout << "Counselor     : " << tbl[i]->appointCouns << endl;
		            cout << "Mode          : " << tbl[i]->appointMode << endl;
		            cout << "Date          : " << tbl[i]->appointDate << endl;
		            cout << "Time          : " << tbl[i]->appointTime << endl;
		            cout << "Patient Name  : " << tbl[i]->appointPtName << endl;
		            cout << "Patient Phone : " << tbl[i]->appointPtPhone << endl;
		            cout << "Patient Email : " << tbl[i]->appointPtEmail << endl;
		            cout << "Amount        : " << tbl[i]->appointNetAmt << endl;
		            cout << "Payment       : " << tbl[i]->appointPayStat << endl;
		            cout << "Status        : " << tbl[i]->appointStat << endl;
		        }
		    }
		    if (count == 0) {
		        cout << "No appointments found." << endl;
		    }
		}

		// Display appointments for a specific patient by email
		void displayPatientAppointments(string email) {
			int count = 0;
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL && tbl[i]->appointPtEmail == email) {
					cout << "\n--- Appointment " << ++count << " ---" << endl;
					cout << "ID            : " << tbl[i]->appointID << endl;
					cout << "Service       : " << tbl[i]->appointSvc << endl;
					cout << "Counselor     : " << tbl[i]->appointCouns << endl;
					cout << "Mode          : " << tbl[i]->appointMode << endl;
					cout << "Date          : " << tbl[i]->appointDate << endl;
					cout << "Time          : " << tbl[i]->appointTime << endl;
					cout << "Amount        : " << tbl[i]->appointNetAmt << endl;
					cout << "Payment       : " << tbl[i]->appointPayStat << endl;
					cout << "Status        : " << tbl[i]->appointStat << endl;
				}
			}
			if (count == 0) {
		        cout << "No appointments found." << endl;
			}
		}

		int getTableSize() { 
			return TBL_SIZE; 
		}

		appoint* getEntry(int index) { 
			return tbl[index]; 
		}

		int getHash(string id) {
			return hashFn(id);
		}

		friend void sortByDateAscending(AppointHT& appointmentTable);  //Allow function to get private value
		friend void sortByDateDescending(AppointHT& appointmentTable); 
		friend void sortByTimeAscending(AppointHT& appointmentTable); 
		friend void sortByTimeDescending(AppointHT& appointmentTable); 
		friend void sortByNetAmountAscending(AppointHT& appointmentTable); 
		friend void sortByNetAmountDescending(AppointHT& appointmentTable); 
		friend void PatientsortByDateAscending(AppointHT& appointmentTable, string patientEmail);  
		friend void PatientsortByDateDescending(AppointHT& appointmentTable, string patientEmail); 
		friend void PatientsortByTimeAscending(AppointHT& appointmentTable, string patientEmail); 
		friend void PatientsortByTimeDescending(AppointHT& appointmentTable, string patientEmail); 
		friend void PatientsortByNetAmountAscending(AppointHT& appointmentTable, string patientEmail); 
		friend void PatientsortByNetAmountDescending(AppointHT& appointmentTable, string patientEmail); 
};

// TEO
class Appoint {
	private:
		appoint data;
		
	public:
		// Constructor
	    Appoint() {
	        data.appointID = "";
	        data.appointSvc = "";
	        data.appointCouns = "";
	        data.appointMode = "";
	        data.appointDate = 0;
	        data.appointTime = "";
	        data.appointPtName = "";
	        data.appointPtPhone = 0;
	        data.appointPtEmail = "";
	        data.appointGrossAmt = 0.0;
	        data.appointNetAmt = 0.0;
	        data.appointPayStat = "Unpaid";
	        data.appointStat = "Pending";
	    }
	    
	    // Destructor
	    ~Appoint() {
		}
		
		void addAppoint(AppointHT& appointmentTable, SvcHT& serviceTable, StaffHT& staffTable) {
		    string id, service, counselor, mode, time, ptName, ptEmail;
		    int date, ptPhone;
		    double grossAmt = 0.0;
		    
			// Generate auto incremented appointment ID by finding max ID in hash table
			// Generate from ChatGPT, what I code is modulo part to get last 4 digits
			int maxNum = 0;
			for (int i = 0; i < appointmentTable.getTableSize(); i++) {
				appoint* entry = appointmentTable.getEntry(i);
				if (entry != NULL) {
					string currentID = entry->appointID;
					if (currentID.length() >= 6 && currentID.substr(0,2) == "CP") {
						// Extract the numeric part and convert to int
						string numStr = currentID.substr(2); // Get characters after "CP"
						int idNum = stoi(numStr);
							// Get last 4 digits using modulo
							int last4Digits = idNum % 10000;
							if (last4Digits > maxNum) {
								maxNum = last4Digits;
							}
					}
				}
			}
		    
		    // Format new ID
		    id = "CP" + string(4 - to_string(maxNum + 1).length(), '0') + to_string(maxNum + 1);
		    cout << "\nAppointment ID: " << id << endl;
			
			// Process service selection
			int serviceCount = 0;
			for (int i = 0; i < serviceTable.getTableSize(); i++) {
				if (serviceTable.getEntry(i) != NULL) {
					serviceCount++;
				}
			}
			
			if (serviceCount == 0) {
				cout << "No services available. Please add services first." << endl;
				return;
			}

			svc** services = new svc*[serviceCount];
			int index = 0;
			for (int i = 0; i < serviceTable.getTableSize(); i++) {
				if (serviceTable.getEntry(i) != NULL) {
					services[index++] = serviceTable.getEntry(i);
				}
			}

			// Sort services
			for (int i = 0; i < serviceCount - 1; i++) {
				int currentMin = i;
				for (int j = i + 1; j < serviceCount; j++) {
					if (services[j]->svcName < services[currentMin]->svcName) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					svc* temp = services[i];
					services[i] = services[currentMin];
					services[currentMin] = temp;
				}
			}

			cout << "\nAvailable Services:\n";
			for (int i = 0; i < serviceCount; i++) {
				cout << i+1 << ". " << services[i]->svcName 
					<< " (" << services[i]->svcDur << " min, RM " 
					<< services[i]->svcPrice << ")" << endl;
			}

			int selection;
			do {
				cout << "\nSelect a service (1-" << serviceCount << "): ";
				cin >> selection;
				
				if (selection < 1 || selection > serviceCount) {
					cout << "Invalid selection. Please choose from the list (1-" << serviceCount << ")." << endl;
				}
			} while (selection < 1 || selection > serviceCount);

			service = services[selection-1]->svcName;
			grossAmt = services[selection-1]->svcPrice;
			cout << "Selected: " << service << " (RM " << grossAmt << ")" << endl;

			delete[] services;

			// Process counselor selection using StaffHT
			int counselorCount = 0;
			for (int i = 0; i < staffTable.getTableSize(); i++) {
				if (staffTable.getEntry(i) != NULL && 
					staffTable.getEntry(i)->getRole() == "Counsellor" && 
					staffTable.getEntry(i)->getStatus() == "Active") {
					counselorCount++;
				}
			}
			
			if (counselorCount == 0) {
				cout << "No counselors available. Cannot proceed without counselors." << endl;
				// Return or handle the no-counselor situation appropriately
			} else {
				Staff** counselors = new Staff*[counselorCount];
				int cIndex = 0;
				
				for (int i = 0; i < staffTable.getTableSize(); i++) {
					if (staffTable.getEntry(i) != NULL && 
						staffTable.getEntry(i)->getRole() == "Counsellor" && 
						staffTable.getEntry(i)->getStatus() == "Active") {
						counselors[cIndex++] = staffTable.getEntry(i);
					}
				}
				
				// Sort counselors by name
				for (int i = 0; i < counselorCount - 1; i++) {
					int currentMin = i;
					for (int j = i + 1; j < counselorCount; j++) {
						string fullName1 = counselors[j]->getFName() + " " + counselors[j]->getLName();
						string fullName2 = counselors[currentMin]->getFName() + " " + counselors[currentMin]->getLName();
						if (fullName1 < fullName2) {
							currentMin = j;
						}
					}
					if (currentMin != i) {
						Staff* temp = counselors[i];
						counselors[i] = counselors[currentMin];
						counselors[currentMin] = temp;
					}
				}

				cout << "\nAvailable Counselors:\n";
				for (int i = 0; i < counselorCount; i++) {
					cout << i+1 << ". " << counselors[i]->getFName() << " " 
						<< counselors[i]->getLName() << endl;
				}

				int counselorSelection;
				do {
					cout << "\nSelect a counselor (1-" << counselorCount << "): ";
					cin >> counselorSelection;
					
					if (counselorSelection < 1 || counselorSelection > counselorCount) {
						cout << "Invalid selection. Please choose from the list (1-" << counselorCount << ")." << endl;
					}
				} while (counselorSelection < 1 || counselorSelection > counselorCount);

				counselor = counselors[counselorSelection-1]->getFName() + " " + 
						counselors[counselorSelection-1]->getLName();
				cout << "Selected: " << counselor << endl << endl;
				
				delete[] counselors;
			}

			
			cin.ignore();

			int modeOp;
			cout << "Available Modes:\n";
			cout << "1. Online\n";
			cout << "2. Offline\n\n";

			do {
				cout << "Select a mode (1-2): ";
				cin >> modeOp;
				
				if (modeOp < 1 || modeOp > 2) {
					cout << "Invalid selection. Please choose from the list (1-2)." << endl;
				}
			} while (modeOp < 1 || modeOp > 2);

			switch (modeOp) {
				case 1: {
					mode = "Online";
					cout << "Selected: Online\n\n";
					break;
				}
				case 2: {
					mode = "Offline";
					cout << "Selected: Offline\n\n";
					break;
				}
			}

			checkAppointDateInput(date);

			cin.ignore();
			int timeChoice;
			cout << "\nAvailable Time Slots:\n";
			cout << "1. 0800 (08:00 AM)\n";
			cout << "2. 1000 (10:00 AM)\n";
			cout << "3. 1300 (01:00 AM)\n";
			cout << "4. 1500 (03:00 PM)\n";
			cout << "5. 1700 (05:00 PM)\n";
			cout << "6. 2000 (08:00 PM)\n";

			do {
				cout << "\nSelect a time slot (1-6): ";
				cin >> timeChoice;
				
				if (timeChoice < 1 || timeChoice > 6) {
					cout << "Invalid selection. Please choose from the list (1-6)." << endl;
				}
			} while (timeChoice < 1 || timeChoice > 6);

			switch (timeChoice) {
				case 1:
					time = "0800";
					break;
				case 2:
					time = "1000";
					break;
				case 3:
					time = "1300";
					break;
				case 4:
					time = "1500";
					break;
				case 5:
					time = "1700";
					break;
				case 6:
					time = "2000";
					break;
			}

			cout << "Selected time: " << time << endl;

			cin.ignore();
			cout << "\nEnter Patient Name: ";
			getline(cin, ptName);

			cout << "Enter Patient Phone: ";
			cin >> ptPhone;
			cin.ignore();

			cout << "Enter Patient Email: ";
			getline(cin, ptEmail);

			string couponCode = "";
			float discount = 0.0;
			char hasCoupon;
			CouponHT couponTable;
			coupon* appliedCoupon = NULL; // Store the applied coupon for later use
			
			cout << "\nDo you have a coupon? (Y/N): ";
			cin >> hasCoupon;

			if (toupper(hasCoupon) == 'Y') {
				couponTable.loadFromFile();
				
				bool validCoupon = false;
				int attempts = 0;
				
				while (!validCoupon && attempts < 3) {
					cout << "Enter Coupon Code: ";
					cin >> couponCode;
					
					// Check if coupon exists and is valid
					bool found = false;
					for (int i = 0; i < couponTable.getTableSize(); i++) {
						coupon* currentCoupon = couponTable.getEntry(i);
						if (currentCoupon != NULL && currentCoupon->couponCode == couponCode) {
							found = true;
							
							if (currentCoupon->couponStat == "Active" && currentCoupon->couponQty > 0) {
								discount = currentCoupon->couponDis;
								validCoupon = true;
								appliedCoupon = currentCoupon; // Store the coupon for later use
								
								cout << "Coupon applied! " << discount * 100 << "% discount." << endl;
								break;
							} else if (currentCoupon->couponStat != "Active") {
								cout << "This coupon is inactive." << endl;
								break;
							} else if (currentCoupon->couponQty <= 0) {
								cout << "This coupon is out of stock." << endl;
								break;
							}
						}
					}
					
					if (!found) {
						cout << "Invalid coupon code." << endl;
					}
					
					if (!validCoupon) {
						attempts++;
						if (attempts < 3) {
							char retry;
							cout << "Try another coupon? (Y/N): ";
							cin >> retry;
							if (toupper(retry) != 'Y') {
								break;
							}
						} else {
							cout << "Maximum attempts reached." << endl;
						}
					}
				}
			}

			// Calculate net amount with discount
			double netAmt = grossAmt;
			if (discount > 0) {
				netAmt = grossAmt * (1 - discount);
				cout << "\nOriginal Amount: RM " << fixed << setprecision(2) << grossAmt << endl;
				cout << "Discount: " << discount * 100 << "%" << endl;
				cout << "Net Amount: RM " << fixed << setprecision(2) << netAmt << endl;
			}

			// Fill data
			appoint apt;
			apt.appointID = id;
			apt.appointSvc = service;
			apt.appointCouns = counselor;
			apt.appointMode = mode;
			apt.appointDate = date;
			apt.appointTime = time;
			apt.appointPtName = ptName;
			apt.appointPtPhone = ptPhone;
			apt.appointPtEmail = ptEmail;
			apt.appointGrossAmt = grossAmt;
			apt.appointNetAmt = netAmt; // Use the calculated net amount
			apt.appointPayStat = "Unpaid";
			apt.appointStat = "Pending";

			char choice;
			cout << "\nDo you want to save this appointment? (Y/N): ";
			cin >> choice;
			
			if (toupper(choice) == 'Y') {
				// Only decrement coupon quantity when appointment is saved
				if (appliedCoupon != NULL) {
					appliedCoupon->couponQty--; // Decrement coupon quantity
					couponTable.updateCouponFile(); // Update coupon file
				}
				
				saveAppointToFile(apt);
				appointmentTable.insert(&apt);
				cout << "Appointment added successfully!" << endl;
			} else {
				cout << "Appointment not saved!" << endl;
			}
		}

		// Save appointment to file using Linked List
		void saveAppointToFile(appoint& apt) {
		    ofstream outFile;
		    outFile.open("appoint.txt", ios::app);  
		
		    if (outFile.is_open()) {
		        outFile << apt.appointID << endl;
		        outFile << apt.appointSvc << endl;
		        outFile << apt.appointCouns << endl;
		        outFile << apt.appointMode << endl;
		        outFile << apt.appointDate << endl;
		        outFile << apt.appointTime << endl;
		        outFile << apt.appointPtName << endl;
		        outFile << apt.appointPtPhone << endl;
		        outFile << apt.appointPtEmail << endl;
		        outFile << apt.appointGrossAmt << endl;
		        outFile << apt.appointNetAmt << endl;
		        outFile << apt.appointPayStat << endl;
		        outFile << apt.appointStat << endl << endl;
		
		        outFile.close();
		    } else {
		        cout << "Unable to open appoint.txt for saving." << endl;
		    }
		}

		// Edit appointment - modeled after editPatient
		void editAppointment(AppointHT& appointmentTable) {
			// Create an array of appointments
			appoint* appointArray[appointmentTable.getTableSize()];
			int count = 0;
			int tableIndices[appointmentTable.getTableSize()]; // To track original indices
			
			for (int i = 0; i < appointmentTable.getTableSize(); i++) {
				if (appointmentTable.getEntry(i) != NULL) {
					appointArray[count] = appointmentTable.getEntry(i);
					tableIndices[count] = i;
					count++;
				}
			}
			
			if (count == 0) {
				cout << "No appointments available to edit." << endl;
				return;
			}
			
			// Display all appointments with numbers
			cout << "\n--- Available Appointments ---\n";
			for (int i = 0; i < count; i++) {
				cout << (i+1) << ". " << appointArray[i]->appointID << " - " 
					<< appointArray[i]->appointPtName << " (" 
					<< appointArray[i]->appointDate << " " 
					<< appointArray[i]->appointTime << ")" << endl;
			}
			
			// Let user select an appointment
			int aptChoice;
			cout << "\nEnter the number of the appointment to edit (1-" << count << "): ";
			cin >> aptChoice;
			
			if (aptChoice < 1 || aptChoice > count) {
				cout << "Invalid selection." << endl;
				return;
			}
			
			int selectedIndex = tableIndices[aptChoice-1];
			appoint* selectedApt = appointmentTable.getEntry(selectedIndex);
			int choice;
			
			do {
				cout << "\n--- Edit Appointment ---" << endl;
				cout << " 1. Edit Service        (Current: " << selectedApt->appointSvc << ")" << endl;
				cout << " 2. Edit Counselor      (Current: " << selectedApt->appointCouns << ")" << endl;
				cout << " 3. Edit Mode           (Current: " << selectedApt->appointMode << ")" << endl;
				cout << " 4. Edit Date           (Current: " << selectedApt->appointDate << ")" << endl;
				cout << " 5. Edit Time           (Current: " << selectedApt->appointTime << ")" << endl;
				cout << " 6. Edit Patient Name   (Current: " << selectedApt->appointPtName << ")" << endl;
				cout << " 7. Edit Patient Phone  (Current: " << selectedApt->appointPtPhone << ")" << endl;
				cout << " 8. Edit Patient Email  (Current: " << selectedApt->appointPtEmail << ")" << endl;
				cout << " 9. Edit Amount         (Current: " << selectedApt->appointNetAmt << ")" << endl;
				cout << "10. Edit Payment Status (Current: " << selectedApt->appointPayStat << ")" << endl;
				cout << "11. Edit Status         (Current: " << selectedApt->appointStat << ")" << endl;
				cout << " 0. Save and Return\n" << endl;
				cout << "Select field to edit (0-11): ";
				cin >> choice;
				
				cin.ignore();
				
				switch(choice) {
					case 1: {
						string newSvc;
						cout << "Enter new Service: ";
						getline(cin, newSvc);
						selectedApt->appointSvc = newSvc;
						break;
					}
					case 2: {
						string newCouns;
						cout << "Enter new Counselor: ";
						getline(cin, newCouns);
						selectedApt->appointCouns = newCouns;
						break;
					}
					case 3: {
						int modeOp;
						cout << "\n--- Available Modes ---\n";
						cout << "1. Online\n";
						cout << "2. Offline\n\n";
						cout << "Enter your choice (1-2): ";
						cin >> modeOp;
						cin.ignore();
						
						switch(modeOp) {
							case 1: {
								selectedApt->appointMode = "Online";
								cout << "Selected: Online\n";
								break;
							}
							case 2: {
								selectedApt->appointMode = "Offline";
								cout << "Selected: Offline\n";
								break;
							}
							default: {
								cout << "Invalid choice, mode unchanged." << endl;
							}
						}
						break;
					}
					case 4: {
						int newDate;
						cout << "Enter new Date (YYYYMMDD): ";
						cin >> newDate;
						cin.ignore();
						selectedApt->appointDate = newDate;
						break;
					}
					case 5: {
						string newTime;
						cout << "Enter new Time (HHMM): ";
						getline(cin, newTime);
						selectedApt->appointTime = newTime;
						break;
					}
					case 6: {
						string newName;
						cout << "Enter new Patient Name: ";
						getline(cin, newName);
						selectedApt->appointPtName = newName;
						break;
					}
					case 7: {
						int newPhone;
						cout << "Enter new Patient Phone: ";
						cin >> newPhone;
						cin.ignore();
						selectedApt->appointPtPhone = newPhone;
						break;
					}
					case 8: {
						string newEmail;
						cout << "Enter new Patient Email: ";
						getline(cin, newEmail);
						selectedApt->appointPtEmail = newEmail;
						break;
					}
					case 9: {
						double newAmount;
						cout << "Enter new Amount: ";
						cin >> newAmount;
						cin.ignore();
						selectedApt->appointNetAmt = newAmount;
						selectedApt->appointGrossAmt = newAmount;
						break;
					}
					case 10: {
						int statusOp;
						cout << "\n--- Payment Status Options ---\n";
						cout << "1. Paid\n";
						cout << "2. Unpaid\n\n";
						cout << "Enter your choice (1-2): ";
						cin >> statusOp;
						cin.ignore();
						
						switch(statusOp) {
							case 1: {
								selectedApt->appointPayStat = "Paid";
								cout << "Selected: Paid\n";
								break;
							}
							case 2: {
								selectedApt->appointPayStat = "Unpaid";
								cout << "Selected: Unpaid\n";
								break;
							}
							default: {
								cout << "Invalid choice, payment status unchanged." << endl;
							}
						}
						break;
					}
					case 11: {
						int statusOp;
						cout << "\n--- Appointment Status Options ---\n";
						cout << "1. Pending\n";
						cout << "2. Confirmed\n";
						cout << "3. Completed\n";
						cout << "4. Cancelled\n\n";
						cout << "Enter your choice (1-4): ";
						cin >> statusOp;
						cin.ignore();
						
						switch(statusOp) {
							case 1: {
								selectedApt->appointStat = "Pending";
								cout << "Selected: Pending\n";
								break;
							}
							case 2: {
								selectedApt->appointStat = "Confirmed";
								cout << "Selected: Confirmed\n";
								break;
							}
							case 3: {
								selectedApt->appointStat = "Completed";
								cout << "Selected: Completed\n";
								break;
							}
							case 4: {
								selectedApt->appointStat = "Cancelled";
								cout << "Selected: Cancelled\n";
								break;
							}
							default: {
								cout << "Invalid choice, appointment status unchanged." << endl;
							}
						}
						break;
					}
					case 0:
						// Save updates to file
						updateAppointmentFile(appointmentTable);
						cout << "Appointment " << selectedApt->appointID << " updated successfully!" << endl;
						break;
					default:
						cout << "Invalid choice, please try again." << endl;
				}
			} while (choice != 0);
		}

		// Delete appointment
		void deleteAppointment(AppointHT& appointmentTable) {
			// Create an array of appointments
			appoint* appointArray[appointmentTable.getTableSize()];
			int count = 0;
			int tableIndices[appointmentTable.getTableSize()]; // To track original indices
			
			for (int i = 0; i < appointmentTable.getTableSize(); i++) {
				if (appointmentTable.getEntry(i) != NULL) {
					appointArray[count] = appointmentTable.getEntry(i);
					tableIndices[count] = i;
					count++;
				}
			}
			
			if (count == 0) {
				cout << "No appointments available to delete." << endl;
				return;
			}
			
			// Display all appointments with numbers
			cout << "\n--- Available Appointments ---\n";
			for (int i = 0; i < count; i++) {
				cout << (i+1) << ". " << appointArray[i]->appointID << " - " 
					<< appointArray[i]->appointPtName << " (" 
					<< appointArray[i]->appointDate << " " 
					<< appointArray[i]->appointTime << ")" << endl;
			}
			
			// Let user select an appointment
			int aptChoice;
			cout << "\nEnter the number of the appointment to delete (1-" << count << "): ";
			cin >> aptChoice;
			
			if (aptChoice < 1 || aptChoice > count) {
				cout << "Invalid selection." << endl;
				return;
			}
			
			int selectedIndex = tableIndices[aptChoice-1];
			appoint* selectedApt = appointmentTable.getEntry(selectedIndex);
			
			char confirm;
			cout << "\nAre you sure you want to delete appointment " << selectedApt->appointID 
				<< " for " << selectedApt->appointPtName << "? (Y/N): ";
			cin >> confirm;
			
			if (toupper(confirm) == 'Y') {
				// Delete the appointment from the hash table
				delete appointmentTable.getEntry(selectedIndex);
				appointmentTable.setTableElement(selectedIndex, NULL);
				
				// Update the file
				updateAppointmentFile(appointmentTable);
				cout << "Appointment deleted successfully!" << endl;
			} else {
				cout << "Deletion cancelled." << endl;
			}
		}

		void updateAppointmentFile(AppointHT& appointmentTable) {
			ofstream outFile("appoint.txt");
			
			if (outFile.is_open()) {
				for (int i = 0; i < appointmentTable.getTableSize(); i++) {
					appoint* apt = appointmentTable.getEntry(i);
					if (apt != NULL) {
						outFile << apt->appointID << endl;
						outFile << apt->appointSvc << endl;
						outFile << apt->appointCouns << endl;
						outFile << apt->appointMode << endl;
						outFile << apt->appointDate << endl;
						outFile << apt->appointTime << endl;
						outFile << apt->appointPtName << endl;
						outFile << apt->appointPtPhone << endl;
						outFile << apt->appointPtEmail << endl;
						outFile << apt->appointGrossAmt << endl;
						outFile << apt->appointNetAmt << endl;
						outFile << apt->appointPayStat << endl;
						outFile << apt->appointStat << endl << endl;
					}
				}
				outFile.close();
			} else {
				cout << "Unable to open appoint.txt for updating." << endl;
			}
		}

};

/* 	[Error] request for member 'TBL_SIZE' in 'serviceTable', which is of non-class type 'int'
	[Error] request for member 'tbl' in 'serviceTable', which is of non-class type 'int'
*/

// HANNAH
class CatHT {
	private:
	    const int TBL_SIZE = 100;
	    cat** tbl;  
	
	    // Hash function for category ID
	    int hashFn(string id) {
	        int sum = 0;
	        for (int i = 0; i < id.length(); i++) {
	            sum += (int)id[i]; // Sum ASCII values
	        }
	        return sum % TBL_SIZE; // Hashing to table size
	    }
	
	public:
	    // Constructor
	    CatHT() {
	        tbl = new cat*[TBL_SIZE]; // Dynamic array for the hash table
	        for (int i = 0; i < TBL_SIZE; i++) {
	            tbl[i] = NULL; // Initialize each slot as NULL
	        }
	    }
	
	    // Destructor
	    ~CatHT() {
	        for (int i = 0; i < TBL_SIZE; i++) {
	            if (tbl[i] != NULL) {
	                delete tbl[i]; 
	            }
	        }
	        delete[] tbl; 
	    }
	
	    // Insert category into the hash table using quadratic probing
	    void insert(cat* category) {
	        int hash = hashFn(category->catID);
	        int i = 0;
	
	        // Quadratic probing
	        while (tbl[(hash + i * i) % TBL_SIZE] != NULL) {
	            i++;
	            if (i >= TBL_SIZE) {
	                cout << "Hash table is full!" << endl;
	                return;
	            }
	        }
	
	        // Found an empty slot, create a new cat object and copy data
	        tbl[(hash + i * i) % TBL_SIZE] = new cat;
	        *tbl[(hash + i * i) % TBL_SIZE] = *category;  
	    }
	
	    // Load categories from file (cat.txt)
		void loadFromFile() {
		    ifstream inFile("cat.txt");
		    cat* category;
		
		    if (inFile.is_open()) {
		        while (!inFile.eof()) {
		            category = new cat;
		
		            getline(inFile, category->catID);
		            if (category->catID.empty() || inFile.eof()) {
		                delete category; // Clean up if we have an empty line or EOF
		                break;
		            }
		
		            getline(inFile, category->catName);
		
		            string temp;
		            getline(inFile, temp);
		
		            insert(category); 
		        }
		        inFile.close();
		        // cout << "Categories loaded successfully!" << endl;
		    } else {
		        cout << "Unable to open cat.txt for reading." << endl;
		    }
		}
	
	    // Display all categories in hash table
	    void displayAllCategories() {
	        int count = 0;
	        for (int i = 0; i < TBL_SIZE; i++) {
	            if (tbl[i] != NULL) {
	                cout << "\n--- Category " << ++count << " ---" << endl;
	                cout << "Category ID   : " << tbl[i]->catID << endl;
	                cout << "Category Name : " << tbl[i]->catName << endl;
	            }
	        }
	        if (count == 0) {
	            cout << "No categories found." << endl;
	        }
	    }
	
	    // Save new category to cat.txt
	    void saveCatToFile(cat* category) {
	        ofstream outFile;
	        outFile.open("cat.txt", ios::app); // Append mode
	
	        if (outFile.is_open()) {
	            outFile << category->catID << endl;
	            outFile << category->catName << endl << endl;
	            cout << "Category saved successfully!" << endl;
	            outFile.close();
	        } else {
	            cout << "Unable to open cat.txt for saving." << endl;
	        }
	    }

		void editCategory() {
			// Create an array of categories
			cat* catArray[TBL_SIZE];
			int count = 0;
			
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					catArray[count++] = tbl[i];
				}
			}
			
			if (count == 0) {
				cout << "No categories available to edit." << endl;
				return;
			}
			
			// Display all categories with numbers
			cout << "\n--- Available Categories ---\n";
			for (int i = 0; i < count; i++) {
				cout << (i+1) << ". " << catArray[i]->catName << endl;
			}
			
			// Let user select a category
			int catChoice;
			cout << "\nEnter the number of the category to edit (1-" << count << "): ";
			cin >> catChoice;
			
			if (catChoice < 1 || catChoice > count) {
				cout << "Invalid selection." << endl;
				return;
			}
			
			cat* selectedCat = catArray[catChoice-1];
			int choice;
			
			do {
				cout << "\n--- Edit Category ---" << endl;
				cout << "1. Edit Category ID   (Current: " << selectedCat->catID << ")" << endl;
				cout << "2. Edit Category Name (Current: " << selectedCat->catName << ")" << endl;
				cout << "0. Save and Return\n" << endl;
				cout << "Select field to edit (0-2): ";
				cin >> choice;
				
				cin.ignore();
				
				switch(choice) {
					case 1: {
						string newID;
						cout << "Enter new Category ID: ";
						getline(cin, newID);
						selectedCat->catID = newID;
						break;
					}
					case 2: {
						string newName;
						cout << "Enter new Category Name: ";
						getline(cin, newName);
						selectedCat->catName = newName;
						break;
					}
					case 0:
						cout << selectedCat->catName << " category updated successfully!" << endl;
						break;
					default:
						cout << "Invalid choice, please try again." << endl;
				}
			} while (choice != 0);
		}
};

// HANNAH
class Cat {
	public:
		// Function to add a new category
		void addCat(CatHT& categoryTable) {
			string id, name;

			cout << "\nEnter Category ID: ";
			cin.ignore(); 
			getline(cin, id);
			cout << "Enter Category Name: ";
			getline(cin, name);

			// Populate data
			cat newCategory;
			newCategory.catID = id;
			newCategory.catName = name;

			char choice;
			cout << "\nDo you want to save this category? (Y/N): ";
			cin >> choice;

			if (toupper(choice) == 'Y') {
				categoryTable.saveCatToFile(&newCategory); 
				categoryTable.insert(&newCategory);  
			} else {
				cout << "Category not saved!" << endl;
			}
		}
};

// TEO
class PtHT {
	private:
	    const int TBL_SIZE = 100;
	    Pt** tbl;
	
	    int hashFn(int phone) {
	        return phone % TBL_SIZE; // Hashing to table size
	    }
	
	public:
	    PtHT() {
	        tbl = new Pt*[TBL_SIZE]; 
	        for (int i = 0; i < TBL_SIZE; i++) {
	            tbl[i] = NULL; 
	        }
	    }
	
	    ~PtHT() {
	        for (int i = 0; i < TBL_SIZE; i++) {
	            if (tbl[i] != NULL) {
	                delete tbl[i];
	            }
	        }
	        delete[] tbl;
	    }

		// Getter for table element
		Pt* getTableElement(int index) {
			if (index >= 0 && index < TBL_SIZE)
				return tbl[index];
			return NULL;
		}
		
		// Setter for table element
		void setTableElement(int index, Pt* value) {
			if (index >= 0 && index < TBL_SIZE)
				tbl[index] = value;
		}

		// Getter for TBL_SIZE
		int getTblSize() {
			return TBL_SIZE;
		}
	
	    void insert(Pt* patient) {
			int hash = hashFn(patient->getPhone());
	        int i = 0;
	        
	        // Quadratic probing
	        while (tbl[(hash + i * i) % TBL_SIZE] != NULL) {
	            i++;
	            if (i >= TBL_SIZE) {
	                cout << "Hash table is full!" << endl;
	                return;
	            }
	        }
			
			// Found an empty slot, create a new Pt object and copy data
	        tbl[(hash + i * i) % TBL_SIZE] = new Pt(patient->getFName(), patient->getLName(), patient->getPhone(), patient->getEmail(), patient->getPassword(), patient->getStatus(), patient->getAge()); 
	    }
		
		void loadFromFile() {
		    ifstream inFile("patient.txt");
		    Pt* patient;
		
		    if (inFile.is_open()) {
		        bool isLoaded = false;  // Track if patients are successfully loaded
		        while (true) {
		            patient = new Pt("", "", 0, "", "", "", 0);  
		
		            string fName, lName, email, password, status;
		            int phone, age;
		
		            if (!getline(inFile, fName) || fName.empty()) break;  
		            if (!getline(inFile, lName) || lName.empty()) break;  
		
		            patient->setFName(fName);
		            patient->setLName(lName);
		
		            inFile >> phone;
		            inFile.ignore();  
		            getline(inFile, email);
		
		            patient->setPhone(phone);  
		            patient->setEmail(email);  
		
		            inFile >> age;
		            inFile.ignore();  
		
		            patient->setAge(age);  
		
		            getline(inFile, password);
		            getline(inFile, status);
		
		            patient->setPassword(password);  
		            patient->setStatus(status);      
		
		            string temp;
		            getline(inFile, temp);
		
		            insert(patient); 
		
		            isLoaded = true;  
		        }
		
		        inFile.close();
		
		        if (isLoaded) {
		            // cout << "Patients loaded successfully!" << endl;
		        } else {
		            cout << "No patients found." << endl;
		        }
		    } else {
		        cout << "Unable to open pt.txt for reading." << endl;
		    }
		}
	
		void displayAllPatients() {
		    int count = 0;
		    for (int i = 0; i < TBL_SIZE; i++) {
		        if (tbl[i] != NULL) {
		            cout << "\n--- Patient " << ++count << " ---" << endl;
		            cout << "First Name  : " << tbl[i]->getFName() << endl;
		            cout << "Last Name   : " << tbl[i]->getLName() << endl;
		            cout << "Phone       : " << tbl[i]->getPhone() << endl;
		            cout << "Email       : " << tbl[i]->getEmail() << endl;
		            cout << "Age         : " << tbl[i]->getAge() << endl;
		            cout << "Status      : " << tbl[i]->getStatus() << endl;
		        }
		    }
		    if (count == 0) {
		        cout << "No patients found." << endl;
		    }
		}
	    
		void savePatientToFile(Pt* patient) {
		    ofstream outFile;
		    outFile.open("patient.txt", ios::app); 
		
		    if (outFile.is_open()) {
		        outFile << patient->getFName() << endl;
		        outFile << patient->getLName() << endl;
		        outFile << patient->getPhone() << endl;
		        outFile << patient->getEmail() << endl;
		        outFile << patient->getAge() << endl;
		        outFile << patient->getPassword() << endl;
		        outFile << patient->getStatus() << endl << endl;
		
		        cout << "Patient saved successfully!" << endl;
		        outFile.close();
		    } else {
		        cout << "Unable to open pt.txt for saving." << endl;
		    }
		}
		
		// Sort patients by Email (Selection Sort)
		void sortByEmail() {
		    // First, collect all non-NULL patients into an array
		    Pt** patients = new Pt*[TBL_SIZE];
		    int size = 0;
		    
		    for (int i = 0; i < TBL_SIZE; i++) {
		        if (tbl[i] != NULL) {
		            patients[size++] = tbl[i];
		        }
		    }
		    
		    // Selection sort by email
		    for (int i = 0; i < size - 1; i++) {
		        int currentMin = i; 
		        for (int j = i + 1; j < size; j++) {
		            if (patients[j]->getEmail() < patients[currentMin]->getEmail()) {
		                currentMin = j;
		            }
		        }
		        if (currentMin != i) {
		            Pt* temp = patients[i];
		            patients[i] = patients[currentMin];
		            patients[currentMin] = temp;
		        }
		    }
		    
		    // Display sorted patients
		    cout << "\n--- Patients Sorted by Email ---\n";
		    for (int i = 0; i < TBL_SIZE; i++) {
		        cout << "\n--- Patient " << i+1 << " ---" << endl;
		        cout << "First Name  : " << patients[i]->getFName() << endl;
		        cout << "Last Name   : " << patients[i]->getLName() << endl;
		        cout << "Phone       : " << patients[i]->getPhone() << endl;
		        cout << "Email       : " << patients[i]->getEmail() << endl;
		        cout << "Age         : " << patients[i]->getAge() << endl;
		        cout << "Status      : " << patients[i]->getStatus() << endl;
		    }
		    
		    // Free the temporary array
		    delete[] patients;
		}
		
		// Search Patient by Email (Binary Search)
		void searchByEmail() {
		    string targetEmail;
		    
		    cout << "Enter email to search: ";
		    cin.ignore();
		    getline(cin, targetEmail);

			if (!isValidEmail(targetEmail)) {
				cout << "Invalid email format. Please try again.\n" << endl;
				return;
			}
			
		    // Count non-null patients
		    int count = 0;
		    for (int i = 0; i < TBL_SIZE; i++) {
		        if (tbl[i] != NULL) {
		            count++;
		        }
		    }
		        
		    if (count == 0) {
		        cout << "No patients available to search." << endl;
		        return;
		    }
		        
		    // Create dynamic array
		    Pt** patients = new Pt*[count];
		    int index = 0;
		    for (int i = 0; i < TBL_SIZE; i++) {
		        if (tbl[i] != NULL) {
		            patients[index++] = tbl[i];
		        }
		    }  
		     
		    // Sort by email first (selection sort)
		    for (int i = 0; i < count - 1; i++) {
		        int currentMin = i; 
		        for (int j = i + 1; j < count; j++) {
		            if (patients[j]->getEmail() < patients[currentMin]->getEmail()) {
		                currentMin = j;
		            }
		        }
		        if (currentMin != i) {
		            Pt* temp = patients[i];
		            patients[i] = patients[currentMin];
		            patients[currentMin] = temp;
		        }
		    }
		    
		    int first = 0;
		    int last = count - 1;
		    int found = 0;
		    
		    while (first <= last) {
		        int mid = first + (last - first) / 2;
		        string currentEmail = patients[mid]->getEmail();
		
		        if (currentEmail == targetEmail) {
		            // Display the found patient
		            cout << "\n--- Patient Found ---" << endl;
		            cout << "First Name  : " << patients[mid]->getFName() << endl;
		            cout << "Last Name   : " << patients[mid]->getLName() << endl;
		            cout << "Phone       : " << patients[mid]->getPhone() << endl;
		            cout << "Email       : " << patients[mid]->getEmail() << endl;
		            cout << "Age         : " << patients[mid]->getAge() << endl;
		            cout << "Status      : " << patients[mid]->getStatus() << endl;
		            found = 1;
		
		            // Check for duplicates on left side
		            int firstDup = mid - 1;
		            while (firstDup >= 0 && patients[firstDup]->getEmail() == targetEmail) {
		                cout << "\n--- Patient Found ---" << endl;
		                cout << "First Name  : " << patients[firstDup]->getFName() << endl;
		                cout << "Last Name   : " << patients[firstDup]->getLName() << endl;
		                cout << "Phone       : " << patients[firstDup]->getPhone() << endl;
		                cout << "Email       : " << patients[firstDup]->getEmail() << endl;
		                cout << "Age         : " << patients[firstDup]->getAge() << endl;
		                cout << "Status      : " << patients[firstDup]->getStatus() << endl;
		                found++;
		                firstDup--;
		            }
		
		            // Check for duplicates on right side
		            int lastDup = mid + 1;
		            while (lastDup < count && patients[lastDup]->getEmail() == targetEmail) {
		                cout << "\n--- Patient Found ---" << endl;
		                cout << "First Name  : " << patients[lastDup]->getFName() << endl;
		                cout << "Last Name   : " << patients[lastDup]->getLName() << endl;
		                cout << "Phone       : " << patients[lastDup]->getPhone() << endl;
		                cout << "Email       : " << patients[lastDup]->getEmail() << endl;
		                cout << "Age         : " << patients[lastDup]->getAge() << endl;
		                cout << "Status      : " << patients[lastDup]->getStatus() << endl;
		                found++;
		                lastDup++;
		            }
		
		            cout << "\nTotal matches found: " << found << endl;
		            delete[] patients;
		            return;
		        }
		
		        if (currentEmail < targetEmail) {
		            first = mid + 1;
		        } else {
		            last = mid - 1;
		        }
		    }
		
		    if (!found) {
		        cout << "No patients found with email: " << targetEmail << endl;
		    }
		    delete[] patients; 
		}
		
		// Make UserManager a friend so it can access private members
		friend class UserManager;
};

// TEO
class PtManager {
	public:
		// When a user enters an email that doesn't exist, the system tries to create a new patient account but encounters an error.
		// Suggestion by ChatGPT: modify the addPt() method to accept a pre-provided email:
		void addPt(PtHT& patientTable, string email = "") {
			string fName, lName, password;
			int phone, age;
			
			cout << "\nEnter First Name: ";
			cin >> fName;
			cout << "Enter Last Name: ";
			cin >> lName;
			cout << "Enter Phone Number: +60";
			bool validPhone = false;

			while (!validPhone) {
				if (cin >> phone) {
					if (isValidPhone(phone)) {
						validPhone = true;
					} else {
						cout << "Invalid phone number. Please enter 9-10 digits: +60";
					}
				}
			}
			
			if (email.empty()) { // This line generated by ChatGPT
				bool validEmail = false;
				while (!validEmail) {
					cout << "Enter Email: ";
					cin >> email;
					if (isValidEmail(email)) {
						validEmail = true;
					} else {
						cout << "Invalid email format. Please try again.\n";
					}
				}
			}

			cout << "Enter Password: ";
			maskPwd(password);
			
			cout << "Enter Age: ";
			cin >> age;

			// Directly set status to "Active"
			Pt* newPatient = new Pt(fName, lName, phone, email, password, "Active", age);

			char choice;
			cout << "\nDo you want to save this patient? (Y/N): ";
			cin >> choice;

			if (toupper(choice) == 'Y') {
				patientTable.savePatientToFile(newPatient);
				patientTable.insert(newPatient);
			} else {
				cout << "Patient not saved!" << endl;
			}
		}
};

// HANNAH
class testHT {
	private:
		const int TBL_SIZE = 100;
		qn** tbl;
		
		// Hash function for question text
		int hashFn(const string& question) {
			int sum = 0;
			for (int i = 0; i < question.length(); i++) {
				sum += (int)question[i];
			}
			return sum % TBL_SIZE;
		}

	public:
		// Constructor
		testHT() {
			tbl = new qn*[TBL_SIZE];
			for (int i = 0; i < TBL_SIZE; i++) {
				tbl[i] = NULL;
			}
		}

		// Destructor
		~testHT() {
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					delete tbl[i];
				}
			}
			delete[] tbl;
		}

		// Load questions from a file
		void loadQuestionsFromFile() {
			ifstream inFile("qn.txt");
			string line;
			int count = 0;

			while (getline(inFile, line)) {
				if (line.empty()) continue;  

				qn* newQn = new qn;
				newQn->questionText = line;
				newQn->options[0] = "Never";    newQn->points[0] = 0;
				newQn->options[1] = "Sometimes"; newQn->points[1] = 1;
				newQn->options[2] = "Often";    newQn->points[2] = 2;
				newQn->options[3] = "Always";   newQn->points[3] = 3;

				int hash = hashFn(newQn->questionText);
				int i = 0;
				while (tbl[(hash + i * i) % TBL_SIZE] != NULL) {
					i++;
					if (i >= TBL_SIZE) {
						cout << "Hash table is full!" << endl;
						delete newQn;
						return;
					}
				}

				tbl[(hash + i * i) % TBL_SIZE] = newQn;
				count++;
			}

			// cout << "Questions loaded successfully!" << endl;
			inFile.close();
		}

		// Function to display all questions
		void displayAllQuestions() {
			int count = 0;
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					cout << "\n--- Question " << ++count << " ---" << endl;
					cout << "Question Text : " << tbl[i]->questionText << endl;
					for (int j = 0; j < 4; j++) {
						cout << "Option " << j + 1 << "      : " << tbl[i]->options[j] << " (" << tbl[i]->points[j] << " points)" << endl;
					}
				}
			}
			if (count == 0) {
				cout << "No questions available." << endl;
			}
		}

		// Function to get a question based on index
		qn* getQuestion(int index) {
			int count = 0;
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					if (count == index) {
						return tbl[i];
					}
					count++;
				}
			}
			return NULL;
		}
		
		void saveQnToFile(qn* question) {
			ofstream outFile;
			outFile.open("qn.txt", ios::app); // Append mode
		
			if (outFile.is_open()) {
				outFile << question->questionText << endl;
				cout << "Question saved successfully!" << endl;
				outFile.close();
			} else {
				cout << "Unable to open qn.txt for saving." << endl;
			}
		}
		
		void insert(qn* question) {
			int hash = hashFn(question->questionText);
			int i = 0;
			while (tbl[(hash + i * i) % TBL_SIZE] != NULL) {
				i++;
				if (i >= TBL_SIZE) {
					cout << "Hash table is full!" << endl;
					return;
				}
			}
			tbl[(hash + i * i) % TBL_SIZE] = new qn;
			*tbl[(hash + i * i) % TBL_SIZE] = *question;
		}

		// Function to edit a question
		void editQuestion(testHT& questionTable) {
			// Create an array of questions
			qn* questionArray[10]; 
			int count = 0;
			int tableIndices[10]; // To track original indices
			
			for (int i = 0; i < questionTable.TBL_SIZE; i++) {
				if (questionTable.tbl[i] != NULL) {
					questionArray[count] = questionTable.tbl[i];
					tableIndices[count] = i;
					count++;
				}
			}
			
			if (count == 0) {
				cout << "No questions available to edit." << endl;
				return;
			}
			
			// Display all questions with numbers
			cout << "\n--- Available Questions ---\n";
			for (int i = 0; i < count; i++) {
				cout << (i+1) << ". " << questionArray[i]->questionText << endl;
			}
			
			// Let admin select a question
			int questionChoice;
			cout << "\nEnter the number of the question to edit (1-" << count << "): ";
			cin >> questionChoice;
			
			if (questionChoice < 1 || questionChoice > count) {
				cout << "Invalid selection." << endl;
				return;
			}
			
			int selectedIndex = tableIndices[questionChoice-1];
			qn* selectedQuestion = questionTable.tbl[selectedIndex];
			
			// Edit menu
			int choice;
			do {
				cout << "\n--- Edit Question ---" << endl;
				cout << "1. Edit Question Text (Current: " << selectedQuestion->questionText << ")" << endl;
				cout << "0. Save and Return\n" << endl;
				cout << "Select field to edit (0-1): ";
				cin >> choice;
				
				cin.ignore(); // Clear input buffer
				
				switch(choice) {
					case 1: {
						string newText;
						cout << "Enter new Question Text: ";
						getline(cin, newText);
						selectedQuestion->questionText = newText;
						break;
					}
					case 0:
						// Update the file
						updateQuestionFile(questionTable);
						cout << "Question updated successfully!" << endl;
						break;
					default:
						cout << "Invalid choice, please try again." << endl;
				}
			} while (choice != 0);
		}

		// Function to update the question file after editing
		void updateQuestionFile(testHT& questionTable) {
			ofstream outFile("qn.txt");
			
			if (outFile.is_open()) {
				for (int i = 0; i < questionTable.TBL_SIZE; i++) {
					if (questionTable.tbl[i] != NULL) {
						outFile << questionTable.tbl[i]->questionText << endl;
					}
				}
				outFile.close();
			} else {
				cout << "Unable to open qn.txt for updating." << endl;
			}
		}
};

// HANNAH
class resultHT {
	private:
		const int TBL_SIZE = 100;
		result** tbl;

		// Hash function for the phone number
		int hashFn(int phone) {
			return phone % TBL_SIZE;
		}

	public:
		resultHT() {
			tbl = new result*[TBL_SIZE];
			for (int i = 0; i < TBL_SIZE; i++) {
				tbl[i] = NULL;
			}
		}

		~resultHT() {
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					delete tbl[i];
				}
			}
			delete[] tbl;
		}

		// Getter for TBL_SIZE
		int getTableSize() {
			return TBL_SIZE;
		}

		result* getEntry(int index) const { 
			return tbl[index]; 
		}

		// Load results from file
		void loadResultsFromFile() {
			ifstream inFile("result.txt");
			
			if (inFile.is_open()) {
				while (!inFile.eof()) {
					result* newResult = new result;
					
					getline(inFile, newResult->name);
					if (newResult->name.empty() || inFile.eof()) {
						delete newResult;
						break;
					}
					
					inFile >> newResult->phone;
					inFile.ignore(); 

					inFile >> newResult->email;
					
					inFile >> newResult->score;
					inFile.ignore(); 
					
					getline(inFile, newResult->situation);
					
					string temp;
					getline(inFile, temp);
					
					int hash = hashFn(newResult->phone);
					int i = 0;
					while (tbl[(hash + i * i) % TBL_SIZE] != NULL) {
						i++;
						if (i >= TBL_SIZE) {
							cout << "Hash table is full!" << endl;
							delete newResult;
							return;
						}
					}
					tbl[(hash + i * i) % TBL_SIZE] = newResult;
				}
				inFile.close();
			} else {
				cout << "Unable to open result.txt for reading." << endl;
			}
		}

		// Function to display all test results
		void displayAllResults() {
			int count = 0;
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					cout << "\n--- Result " << ++count << " ---" << endl;
					cout << "Name      : " << tbl[i]->name << endl;
					cout << "Phone     : " << tbl[i]->phone << endl;
					cout << "Email     : " << tbl[i]->email << endl;
					cout << "Score     : " << tbl[i]->score << endl;
					cout << "Situation : " << tbl[i]->situation << endl;
				}
			}
			if (count == 0) {
				cout << "No results found." << endl;
			}
		}

		void displayPatientResult(string email) {
				int count = 0;
				for (int i = 0; i < TBL_SIZE; i++) {
					if (tbl[i] != NULL && tbl[i]->email == email) {
						cout << "\n--- Result " << ++count << " ---" << endl;
						cout << "Score     : " << tbl[i]->score << endl;
						cout << "Situation : " << tbl[i]->situation << endl;
					}
				}
				if (count == 0) {
					cout << "No results found." << endl;
				}
		}

		// Function to save result to file
		void saveResultToFile(result* res) {
			ofstream outFile("result.txt", ios::app);
			if (outFile.is_open()) {
				outFile << res->name << endl;
				outFile << res->phone << endl;
				outFile << res->email << endl;
				outFile << res->score << endl;
				outFile << res->situation << endl;
				outFile << endl;  // Empty line between results
				outFile.close();
				cout << "Result saved successfully!" << endl;
			} else {
				cout << "Unable to open result.txt for saving." << endl;
			}
		}

		// Function to insert result into the hash table
		void insert(result* res) {
			int hash = hashFn(res->phone);
			int i = 0;
			while (tbl[(hash + i * i) % TBL_SIZE] != NULL) {
				i++;
			}
			tbl[(hash + i * i) % TBL_SIZE] = res;
		}

		// Add this function to the resultHT class
		void deleteResult(resultHT& resultTable) {
			// Create an array of results
			result* resultArray[resultTable.getTableSize()];
			int count = 0;
			int tableIndices[resultTable.getTableSize()]; // To track original indices
			
			for (int i = 0; i < resultTable.getTableSize(); i++) {
				if (resultTable.getEntry(i) != nullptr) {
					resultArray[count] = resultTable.getEntry(i);
					tableIndices[count] = i;
					count++;
				}
			}
			
			if (count == 0) {
				cout << "No results available to delete." << endl;
				return;
			}
			
			// Display all results with numbers
			cout << "\n--- Available Results ---\n";
			for (int i = 0; i < count; i++) {
				cout << (i+1) << ". " << resultArray[i]->name << " - " 
					<< resultArray[i]->email << " (Score: " 
					<< resultArray[i]->score << ")" << endl;
			}
			
			// Let user select a result
			int resultChoice;
			cout << "\nEnter the number of the result to delete (1-" << count << "): ";
			cin >> resultChoice;
			
			if (resultChoice < 1 || resultChoice > count) {
				cout << "Invalid selection." << endl;
				return;
			}
			
			int selectedIndex = tableIndices[resultChoice-1];
			result* selectedResult = resultTable.getEntry(selectedIndex);
			
			char confirm;
			cout << "\nAre you sure you want to delete result for " 
				<< selectedResult->name << " (Email: " << selectedResult->email << ")? (Y/N): ";
			cin >> confirm;
			
			if (toupper(confirm) == 'Y') {
				// Delete the result from the hash table
				delete resultTable.getEntry(selectedIndex);
				
				// Set the entry to NULL
				setTableElement(selectedIndex, NULL);
				
				// Update the file
				updateResultFile(resultTable);
				cout << "Result deleted successfully!" << endl;
			} else {
				cout << "Deletion cancelled." << endl;
			}
		}

		// Function to allow a patient to delete their own results
		void deleteResult(resultHT& resultTable, string currentEmail) {
			// Create an array of results that belong to the current user
			result* resultArray[resultTable.getTableSize()];
			int count = 0;
			int tableIndices[resultTable.getTableSize()]; // To track original indices
			
			for (int i = 0; i < resultTable.getTableSize(); i++) {
				if (resultTable.getEntry(i) != nullptr && resultTable.getEntry(i)->email == currentEmail) {
					resultArray[count] = resultTable.getEntry(i);
					tableIndices[count] = i;
					count++;
				}
			}
			
			if (count == 0) {
				cout << "You have no test results available to delete." << endl;
				return;
			}
			
			// Display only the current user's results with numbers
			cout << "\n--- Your Test Results ---\n";
			for (int i = 0; i < count; i++) {
				cout << (i+1) << ". Score: " << resultArray[i]->score 
					<< " - Situation: " << resultArray[i]->situation << endl;
			}
			
			// Let user select a result
			int resultChoice;
			cout << "\nEnter the number of the result to delete (1-" << count << "): ";
			cin >> resultChoice;
			
			if (resultChoice < 1 || resultChoice > count) {
				cout << "Invalid selection." << endl;
				return;
			}
			
			int selectedIndex = tableIndices[resultChoice-1];
			result* selectedResult = resultTable.getEntry(selectedIndex);
			
			char confirm;
			cout << "\nAre you sure you want to delete this result? (Y/N): ";
			cin >> confirm;
			
			if (toupper(confirm) == 'Y') {
				// Delete the result from the hash table
				delete resultTable.getEntry(selectedIndex);
				
				// Set the entry to NULL
				resultTable.setTableElement(selectedIndex, NULL);
				
				// Update the file
				resultTable.updateResultFile(resultTable);
				cout << "Result deleted successfully!" << endl;
			} else {
				cout << "Deletion cancelled." << endl;
			}
		}

		// Add this setter method to the resultHT class
		void setTableElement(int index, result* value) {
			if (index >= 0 && index < TBL_SIZE)
				tbl[index] = value;
		}

		// Add this function to update the result file after deletion
		void updateResultFile(resultHT& resultTable) {
			ofstream outFile("result.txt");
			
			if (outFile.is_open()) {
				for (int i = 0; i < resultTable.getTableSize(); i++) {
					result* res = resultTable.getEntry(i);
					if (res != NULL) {
						outFile << res->name << endl;
						outFile << res->phone << endl;
						outFile << res->email << endl;
						outFile << res->score << endl;
						outFile << res->situation << endl;
						outFile << endl;  // Empty line between results
					}
				}
				outFile.close();
			} else {
				cout << "Unable to open result.txt for updating." << endl;
			}
		}
};

// Class to manage the test and calculate results - HANNAH
class test {
	private:
		testHT& testTable;
		resultHT& resultTable;

	public:
		test(testHT& t, resultHT& r) : testTable(t), resultTable(r) {}

		~test(){}

		// Function to take the test
		void takeTest() {
			string name, email;
			int phone;
			int score = 0;
			
			cin.ignore(); 
			cout << "\nEnter your full name: ";
			getline(cin, name);
			cout << "Enter your phone number: ";
			cin >> phone;
			cin.ignore();  
			
			
			cout << "Enter your email: ";
			cin >> email;

			int questionIndex = 0;
			qn* currentQuestion = NULL;
		
			// Loop through all questions in the hash table
			while ((currentQuestion = testTable.getQuestion(questionIndex)) != NULL) {
				cout << "\n--- Question " << questionIndex + 1 << " ---\n";
				cout << currentQuestion->questionText << endl;
				for (int i = 0; i < 4; i++) {
					cout << "  " << i + 1 << ". " << currentQuestion->options[i] << endl;
				}
		
				int answer;
				cout << "\nYour answer (1-4): ";
				cin >> answer;
		
				if (answer >= 1 && answer <= 4) {
					score += currentQuestion->points[answer - 1];
				} else {
					cout << "Invalid choice, please try again." << endl;
					continue;
				}
		
				questionIndex++;
			}
		
			string situation;
			if (score <= 7) {
				situation = "Low Stress";
			} else if (score <= 15) {
				situation = "Moderate Stress";
			} else if (score <= 22) {
				situation = "High Stress";
			} else {
				situation = "Very High Stress";
			}
		
			result* newResult = new result;
			newResult->name = name;
			newResult->phone = phone;
			newResult->score = score;
			newResult->situation = situation;
		
			cout << "\nYour total score: " << score << endl;
			cout << "Your situation  : " << situation << endl;
		
			char save;
			cout << "\nDo you want to save the result? (Y/N): ";
			cin >> save;
			if (save == 'Y' || save == 'y') {
				resultTable.saveResultToFile(newResult);
				resultTable.insert(newResult);
			} else {
				cout << "Result not saved!" << endl;
			}
		}
};

// TEO
class TxHT {
	private:
	    const int TBL_SIZE = 100; 
	    tx** tbl;                 
	
	    // Hash function for appointID
	    int hashFn(string appointID) {
	        int sum = 0;
	        for (int i = 0; i < appointID.length(); i++) {
	            sum += (int)appointID[i]; // Sum ASCII values
	        }
	        return sum % TBL_SIZE;
	    }
	
	public:
	    // Constructor
	    TxHT() {
	        tbl = new tx*[TBL_SIZE];
	        for (int i = 0; i < TBL_SIZE; i++) {
	            tbl[i] = NULL;
	        }
	    }
	
	    // Destructor
	    ~TxHT() {
	        for (int i = 0; i < TBL_SIZE; i++) {
	            if (tbl[i] != NULL) {
	                delete tbl[i];
	            }
	        }
	        delete[] tbl;
	    }

		// Getter for TBL_SIZE
		int getTblSize() {
			return TBL_SIZE;
		}

		tx* getEntry(int index) const { 
			return tbl[index]; 
		}
	
	    // Insert treatment record using quadratic probing
	    void insert(tx* treatment) {
	        int hash = hashFn(treatment->appointID);
	        int i = 0;
	        while (tbl[(hash + i * i) % TBL_SIZE] != NULL) {
	            i++;
	            if (i >= TBL_SIZE) {
	                cout << "Hash table is full!" << endl;
	                return;
	            }
	        }
	        tbl[(hash + i * i) % TBL_SIZE] = new tx;
	        *tbl[(hash + i * i) % TBL_SIZE] = *treatment;
	    }
	
	    // Load treatment records from file
	    void loadFromFile() {
	        ifstream inFile("tx.txt");
	        tx* treatment;
	
	        if (inFile.is_open()) {
	            while (!inFile.eof()) {
	                treatment = new tx;
	                getline(inFile, treatment->appointID);
	                if (treatment->appointID.empty() || inFile.eof()) {
	                    delete treatment;
	                    break;
	                }
	                getline(inFile, treatment->ptName);
		            inFile >> treatment->ptPhone;
		            inFile.ignore();
                	getline(inFile, treatment->ptEmail);
	                getline(inFile, treatment->summary);
	                getline(inFile, treatment->intervention);
	                getline(inFile, treatment->response);
	                getline(inFile, treatment->progress);
	                getline(inFile, treatment->homework);
	                getline(inFile, treatment->nextSession);
	                string temp;
	                getline(inFile, temp); 
	                insert(treatment);
	            }
	            inFile.close();
	            // cout << "Treatment records loaded successfully!" << endl;
	        } else {
	            cout << "Unable to open tx.txt for reading." << endl;
	        }
	    }
	
	    // Display all treatment records
	    void displayAllTx() {
	        int count = 0;
	        for (int i = 0; i < TBL_SIZE; i++) {
	            if (tbl[i] != NULL) {
	                cout << "\n--- Treatment " << ++count << " ---" << endl;
	                cout << "Appointment ID : " << tbl[i]->appointID << endl;
	                cout << "Patient Name   : " << tbl[i]->ptName << endl;
	                cout << "Patient Phone  : " << tbl[i]->ptPhone << endl;
	                cout << "Patient Email  : " << tbl[i]->ptEmail << endl;
	                cout << "Summary        : " << tbl[i]->summary << endl;
	                cout << "Intervention   : " << tbl[i]->intervention << endl;
	                cout << "Response       : " << tbl[i]->response << endl;
	                cout << "Progress       : " << tbl[i]->progress << endl;
	                cout << "Homework       : " << tbl[i]->homework << endl;
	                cout << "Next Session   : " << tbl[i]->nextSession << endl;
	            }
	        }
	        if (count == 0) {
	            cout << "No treatment records found." << endl;
	        }
	    }

		void displayPatientTx(string email) {
			int count = 0;
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL && tbl[i]->ptEmail == email) {
	                cout << "\n--- Treatment " << ++count << " ---" << endl;
	                cout << "Appointment ID: " << tbl[i]->appointID << endl;
	                // cout << "Patient Name  : " << tbl[i]->ptName << endl;
	                // cout << "Patient Phone : " << tbl[i]->ptPhone << endl;
	                cout << "Summary       : " << tbl[i]->summary << endl;
	                cout << "Intervention  : " << tbl[i]->intervention << endl;
	                cout << "Response      : " << tbl[i]->response << endl;
	                cout << "Progress      : " << tbl[i]->progress << endl;
	                cout << "Homework      : " << tbl[i]->homework << endl;
	                cout << "Next Session  : " << tbl[i]->nextSession << endl;
				}
			}
			if (count == 0) {
	            cout << "No treatment records found." << endl;
			}
		}
};

// TEO
class Tx {
	private:
	    tx data; // Treatment record data
	
	public:
	    // Constructor
	    Tx() {
	        data.appointID = "";
	        data.ptName = "";
	        data.ptPhone = 0;
	        data.ptEmail = "";
	        data.summary = "";
	        data.intervention = "";
	        data.response = "";
	        data.progress = "";
	        data.homework = "";
	        data.nextSession = "";
	    }
	
	    // Destructor
	    ~Tx() {}
	
	    // Add new treatment record
	    void addTx(TxHT& treatmentTable) {
	        string appointID, ptName, ptEmail, summary, intervention, response, progress, homework, nextSession;
			int ptPhone;
	        cin.ignore();
	        cout << "\nEnter Appointment ID: ";
	        getline(cin, appointID);
	        cout << "Enter Patient Name: ";
	        getline(cin, ptName);
	        cout << "Enter Patient Phone: ";
			cin >> ptPhone;
			cin.ignore();
			cout << "Enter Patient Email: ";
			getline(cin, ptEmail);
	        cout << "Enter Summary: ";
	        getline(cin, summary);
	        cout << "Enter Intervention: ";
	        getline(cin, intervention);
	        cout << "Enter Response: ";
	        getline(cin, response);
	        cout << "Enter Progress: ";
	        getline(cin, progress);
	        cout << "Enter Homework: ";
	        getline(cin, homework);

			int nextSessionOp;
			bool nextSessionLoop=1;

			do {
				cout << "\n--- Available Choices ---\n";
				cout << "1. Yes\n";
				cout << "2. Maybe\n";
				cout << "3. No\n\n";

				cout << "Select choice (1-3): ";
				cin >> nextSessionOp;

				switch(nextSessionOp) {
					case 1: {
						nextSession="Yes";
						cout << "Selected: Yes\n";
						nextSessionLoop=1;
						break;
					}

					case 2: {
						nextSession="Maybe";
						cout << "Selected: Maybe\n";
						nextSessionLoop=1;
						break;
					}

					case 3: {
						nextSession="No";
						cout << "Selected: No\n";
						nextSessionLoop=1;
						break;
					}

					default: {
						cout << "Invalid choice, please try again.\n";
						nextSessionLoop=0;
					}
				}
			} while(nextSessionLoop==0);
	
	        tx treatment;
	        treatment.appointID = appointID;
	        treatment.ptName = ptName;
	        treatment.ptPhone = ptPhone;
	        treatment.ptEmail = ptEmail;
	        treatment.summary = summary;
	        treatment.intervention = intervention;
	        treatment.response = response;
	        treatment.progress = progress;
	        treatment.homework = homework;
	        treatment.nextSession = nextSession;
	
	        char choice;
	        cout << "\nDo you want to save this treatment record? (Y/N): ";
	        cin >> choice;
	
	        if (toupper(choice) == 'Y') {
	            saveTxToFile(treatment);
	            treatmentTable.insert(&treatment);
	            cout << "Treatment record added successfully!" << endl;
	        } else {
				cout << "Treatment not saved!" << endl;
			}
	    }
	
	    // Save treatment record to file
	    void saveTxToFile(tx& treatment) {
	        ofstream outFile;
	        outFile.open("tx.txt", ios::app);
	        if (outFile.is_open()) {
	            outFile << treatment.appointID << endl;
	            outFile << treatment.ptName << endl;
	            outFile << treatment.ptPhone << endl;
	            outFile << treatment.ptEmail << endl;
	            outFile << treatment.summary << endl;
	            outFile << treatment.intervention << endl;
	            outFile << treatment.response << endl;
	            outFile << treatment.progress << endl;
	            outFile << treatment.homework << endl;
	            outFile << treatment.nextSession << endl << endl;
	            cout << "Treatment record saved successfully!" << endl;
	            outFile.close();
	        } else {
	            cout << "Unable to open tx.txt for saving." << endl;
	        }
	    }

		// Edit treatment record
		void editTreatment(TxHT& treatmentTable) {
			// Create an array of treatments
			tx* txArray[treatmentTable.getTblSize()];
			int count = 0;
			int tableIndices[treatmentTable.getTblSize()]; // To track original indices
			
			for (int i = 0; i < treatmentTable.getTblSize(); i++) {
				if (treatmentTable.getEntry(i) != NULL) {
					txArray[count] = treatmentTable.getEntry(i);
					tableIndices[count] = i;
					count++;
				}
			}
			
			if (count == 0) {
				cout << "No treatment records available to edit." << endl;
				return;
			}
			
			// Display all treatment records with numbers
			cout << "\n--- Available Treatment Records ---\n";
			for (int i = 0; i < count; i++) {
				cout << (i+1) << ". " << txArray[i]->appointID << " - " 
					<< txArray[i]->ptName << endl;
			}
			
			// Let user select a treatment record
			int txChoice;
			cout << "\nEnter the number of the treatment record to edit (1-" << count << "): ";
			cin >> txChoice;
			
			if (txChoice < 1 || txChoice > count) {
				cout << "Invalid selection." << endl;
				return;
			}
			
			int selectedIndex = tableIndices[txChoice-1];
			tx* selectedTx = treatmentTable.getEntry(selectedIndex);
			int choice;
			
			do {
				cout << "\n--- Edit Treatment ---" << endl;
				cout << "1. Edit Patient Name  (Current: " << selectedTx->ptName << ")" << endl;
				cout << "2. Edit Patient Phone (Current: " << selectedTx->ptPhone << ")" << endl;
				cout << "3. Edit Patient Email (Current: " << selectedTx->ptEmail << ")" << endl;
				cout << "4. Edit Summary       (Current: " << selectedTx->summary << ")" << endl;
				cout << "5. Edit Intervention  (Current: " << selectedTx->intervention << ")" << endl;
				cout << "6. Edit Response      (Current: " << selectedTx->response << ")" << endl;
				cout << "7. Edit Progress      (Current: " << selectedTx->progress << ")" << endl;
				cout << "8. Edit Homework      (Current: " << selectedTx->homework << ")" << endl;
				cout << "9. Edit Next Session  (Current: " << selectedTx->nextSession << ")" << endl;
				cout << "0. Save and Return\n" << endl;
				cout << "Select field to edit (0-9): ";
				cin >> choice;
				
				cin.ignore();
				
				switch(choice) {
					case 1: {
						string newName;
						cout << "Enter new Patient Name: ";
						getline(cin, newName);
						selectedTx->ptName = newName;
						break;
					}
					case 2: {
						int newPhone;
						cout << "Enter new Patient Phone: ";
						cin >> newPhone;
						cin.ignore();
						selectedTx->ptPhone = newPhone;
						break;
					}
					case 3: {
						string newEmail;
						cout << "Enter new Patient Email: ";
						getline(cin, newEmail);
						selectedTx->ptEmail = newEmail;
						break;
					}
					case 4: {
						string newSummary;
						cout << "Enter new Summary: ";
						getline(cin, newSummary);
						selectedTx->summary = newSummary;
						break;
					}
					case 5: {
						string newIntervention;
						cout << "Enter new Intervention: ";
						getline(cin, newIntervention);
						selectedTx->intervention = newIntervention;
						break;
					}
					case 6: {
						string newResponse;
						cout << "Enter new Response: ";
						getline(cin, newResponse);
						selectedTx->response = newResponse;
						break;
					}
					case 7: {
						string newProgress;
						cout << "Enter new Progress: ";
						getline(cin, newProgress);
						selectedTx->progress = newProgress;
						break;
					}
					case 8: {
						string newHomework;
						cout << "Enter new Homework: ";
						getline(cin, newHomework);
						selectedTx->homework = newHomework;
						break;
					}
					case 9: {
						int nextSessionOp;
						cout << "\n--- Available Choices ---\n";
						cout << "1. Yes\n";
						cout << "2. Maybe\n";
						cout << "3. No\n\n";
						cout << "Select choice (1-3): ";
						cin >> nextSessionOp;
						cin.ignore();
						
						switch(nextSessionOp) {
							case 1: {
								selectedTx->nextSession = "Yes";
								cout << "Selected: Yes\n";
								break;
							}
							case 2: {
								selectedTx->nextSession = "Maybe";
								cout << "Selected: Maybe\n";
								break;
							}
							case 3: {
								selectedTx->nextSession = "No";
								cout << "Selected: No\n";
								break;
							}
							default: {
								cout << "Invalid choice, next session status unchanged." << endl;
							}
						}
						break;
					}
					case 0:
						// Save updates to file
						updateTreatmentFile(treatmentTable);
						cout << "Treatment record for " << selectedTx->ptName << " updated successfully!" << endl;
						break;
					default:
						cout << "Invalid choice, please try again." << endl;
				}
			} while (choice != 0);
		}

		// Helper function to update the treatment file after edits or deletions
		void updateTreatmentFile(TxHT& treatmentTable) {
			ofstream outFile("tx.txt");
			
			if (outFile.is_open()) {
				for (int i = 0; i < treatmentTable.getTblSize(); i++) {
					tx* treatment = treatmentTable.getEntry(i);
					if (treatment != NULL) {
						outFile << treatment->appointID << endl;
						outFile << treatment->ptName << endl;
						outFile << treatment->ptPhone << endl;
						outFile << treatment->ptEmail << endl;
						outFile << treatment->summary << endl;
						outFile << treatment->intervention << endl;
						outFile << treatment->response << endl;
						outFile << treatment->progress << endl;
						outFile << treatment->homework << endl;
						outFile << treatment->nextSession << endl << endl;
					}
				}
				outFile.close();
			} else {
				cout << "Unable to open tx.txt for updating." << endl;
			}
		}
};

// TEO
class UserManager {
public:
	// Search across both patient and staff by email
	void searchUsersByEmail(PtHT& patientTable, StaffHT& staffTable) {
		string targetEmail;
		bool userFound = false;
		
		cout << "\nEnter email to search: ";
		cin.ignore();
		getline(cin, targetEmail);

		if (!isValidEmail(targetEmail)) {
			cout << "Invalid email format. Please try again.\n" << endl;
			return;
		}
		
		Pt* foundPatient = NULL;
		Staff* foundStaff = NULL;
		int patientIndex = -1;
		int staffIndex = -1;
		
		// Check patient table first
		for (int i = 0; i < patientTable.TBL_SIZE; i++) {
			if (patientTable.tbl[i] != NULL && patientTable.tbl[i]->getEmail() == targetEmail) {
				foundPatient = patientTable.tbl[i];
				patientIndex = i;
				userFound = true;
				
				cout << "\n--- Patient Found ---" << endl;
				cout << "First Name  : " << foundPatient->getFName() << endl;
				cout << "Last Name   : " << foundPatient->getLName() << endl;
				cout << "Phone       : " << foundPatient->getPhone() << endl;
				cout << "Email       : " << foundPatient->getEmail() << endl;
				cout << "Age         : " << foundPatient->getAge() << endl;
				cout << "Status      : " << foundPatient->getStatus() << endl;
				
				int action;
				cout << "\nActions:" << endl;
				cout << "1. Edit Patient" << endl;
				cout << "2. Delete Patient" << endl;
				cout << "0. Return to Menu" << endl;
				cout << "Select an action: ";
				cin >> action;
				
				switch(action) {
					case 1: 
						editPatient(patientTable, patientIndex);
						break;
					case 2: 
						deletePatient(patientTable, patientIndex);
						break;
					case 0:
						break;
					default:
						cout << "Invalid choice, please try again." << endl;
				}
				
				return;
			}
		}
		
		// If not found in patient table, check staff table
		for (int i = 0; i < staffTable.TBL_SIZE; i++) {
			if (staffTable.tbl[i] != NULL && staffTable.tbl[i]->getEmail() == targetEmail) {
				foundStaff = staffTable.tbl[i];
				staffIndex = i;
				userFound = true;
				
				// Display found staff
				cout << "\n--- Staff Found ---" << endl;
				cout << "First Name : " << foundStaff->getFName() << endl;
				cout << "Last Name  : " << foundStaff->getLName() << endl;
				cout << "Phone      : " << foundStaff->getPhone() << endl;
				cout << "Email      : " << foundStaff->getEmail() << endl;
				cout << "NRIC       : " << foundStaff->getNric() << endl;
				cout << "Role       : " << foundStaff->getRole() << endl;
				cout << "Status     : " << foundStaff->getStatus() << endl;
				
				// Ask user for action
				int action;
				cout << "\nActions:" << endl;
				cout << "1. Edit Staff" << endl;
				cout << "2. Delete Staff" << endl;
				cout << "0. Return to Menu" << endl;
				cout << "Select an action: ";
				cin >> action;
				
				switch(action) {
					case 1: // Edit staff
						editStaff(staffTable, staffIndex);
						break;
					case 2: // Delete staff
						deleteStaff(staffTable, staffIndex);
						break;
					case 0:
						break;
					default:
						cout << "Invalid choice, please try again." << endl;
				}
				
				return;
			}
		}
		
		// If no user found
		if (!userFound) {
			cout << "\nNo users found with email: " << targetEmail << endl;
		}
	}
    
	// Search for a specific user by email and return pointers to found objects
	void searchUserByEmail(string email, PtHT& patientTable, StaffHT& staffTable, 
						Pt*& foundPatient, Staff*& foundStaff, bool& userFound) {
		userFound = false;
		foundPatient = NULL;
		foundStaff = NULL;
		
		// First search in patients
		for (int i = 0; i < patientTable.TBL_SIZE; i++) {
			if (patientTable.tbl[i] != NULL && patientTable.tbl[i]->getEmail() == email) {
				foundPatient = patientTable.tbl[i];
				userFound = true;
				return;
			}
		}
		
		// If not found in patients, search in staff
		for (int i = 0; i < staffTable.TBL_SIZE; i++) {
			if (staffTable.tbl[i] != NULL && staffTable.tbl[i]->getEmail() == email) {
				foundStaff = staffTable.tbl[i];
				userFound = true;
				return;
			}
		}
	}

	// Edit patient information
	void editPatient(PtHT& patientTable, int index) {
		if (index < 0 || index >= patientTable.TBL_SIZE || patientTable.tbl[index] == NULL) {
			cout << "Invalid patient index." << endl;
			return;
		}
		
		Pt* patient = patientTable.tbl[index];
		int choice;
		
		do {
			cout << "\n--- Edit Patient ---" << endl;
			cout << "1. Edit First Name (Current: " << patient->getFName() << ")" << endl;
			cout << "2. Edit Last Name  (Current: " << patient->getLName() << ")" << endl;
			cout << "3. Edit Phone      (Current: " << patient->getPhone() << ")" << endl;
			cout << "4. Edit Age        (Current: " << patient->getAge() << ")" << endl;
			cout << "5. Edit Password" << endl;
			cout << "6. Change Status   (Current: " << patient->getStatus() << ")" << endl;
			cout << "0. Save and Return\n" << endl;
			cout << "Select field to edit (0-6): ";
			cin >> choice;
			
			cin.ignore();
			
			switch(choice) {
				case 1: {
					string newFName;
					cout << "Enter new First Name: ";
					getline(cin, newFName);
					patient->setFName(newFName);
					break;
				}
				case 2: {
					string newLName;
					cout << "Enter new Last Name: ";
					getline(cin, newLName);
					patient->setLName(newLName);
					break;
				}
				case 3: {
					int newPhone;
					cout << "Enter new Phone: ";
					cin >> newPhone;
					patient->setPhone(newPhone);
					break;
				}
				case 4: {
					int newAge;
					cout << "Enter new Age: ";
					cin >> newAge;
					patient->setAge(newAge);
					break;
				}
				case 5: {
					string newPassword;
					cout << "Enter new Password: ";
					maskPwd(newPassword);
					patient->setPassword(newPassword);
					break;
				}
				case 6: {
					string newStatus;
					
					int newStatusOp;

					cout << "\n--- Available Status ---\n";
					cout << "1. Active\n";
					cout << "2. Inactive\n\n";

					cout << "Enter your choice (1-2): ";
					cin >> newStatusOp;

					switch(newStatusOp) {
						case 1: {
							newStatus="Active";
							cout << "Selected: Active\n";
							break;
						}

						case 2: {
							newStatus="Inactive";
							cout << "Selected: Inactive\n";
							break;
						}

						default: {
							newStatus=patient->getStatus();
							cout << "Invalid choice, please try again." << endl;
						}
					}

					patient->setStatus(newStatus);
					break;
				}
				case 0:
					saveUpdatedPatients(patientTable);
					cout << patient->getFName() << " profile updated successfully!" << endl;
					break;
				default:
					cout << "Invalid choice, please try again." << endl;
			}
		} while (choice != 0);
	}

	// Delete patient
	void deletePatient(PtHT& patientTable, int index) {
		if (index < 0 || index >= patientTable.TBL_SIZE || patientTable.tbl[index] == NULL) {
			cout << "Invalid patient index." << endl;
			return;
		}
		
		char confirm;
		cout << "Are you sure you want to delete this patient? (Y/N): ";
		cin >> confirm;
		
		if (toupper(confirm) == 'Y') {
			// Delete patient
			delete patientTable.tbl[index];
			patientTable.tbl[index] = NULL;
			
			// Save updates to file
			saveUpdatedPatients(patientTable);
			cout << "Patient deleted successfully!" << endl;
		} else {
			cout << "Deletion cancelled." << endl;
		}
	}

	// Edit staff information
	void editStaff(StaffHT& staffTable, int index) {
		if (index < 0 || index >= staffTable.TBL_SIZE || staffTable.tbl[index] == NULL) {
			cout << "Invalid staff index." << endl;
			return;
		}
		
		Staff* staff = staffTable.tbl[index];
		int choice;
		
		do {
			cout << "\n--- Edit Staff ---" << endl;
			cout << "1. Edit First Name (Current: " << staff->getFName() << ")" << endl;
			cout << "2. Edit Last Name  (Current: " << staff->getLName() << ")" << endl;
			cout << "3. Edit Phone      (Current: " << staff->getPhone() << ")" << endl;
			cout << "4. Edit NRIC       (Current: " << staff->getNric() << ")" << endl;
			cout << "5. Edit Role       (Current: " << staff->getRole() << ")" << endl;
			cout << "6. Edit Password" << endl;
			cout << "7. Change Status   (Current: " << staff->getStatus() << ")" << endl;
			cout << "0. Save and Return\n" << endl;
			cout << "Select field to edit (0-7): ";
			cin >> choice;
			
			cin.ignore();
			
			switch(choice) {
				case 1: {
					string newFName;
					cout << "\nEnter new First Name: ";
					getline(cin, newFName);
					staff->setFName(newFName);
					break;
				}
				case 2: {
					string newLName;
					cout << "\nEnter new Last Name: ";
					getline(cin, newLName);
					staff->setLName(newLName);
					break;
				}
				case 3: {
					int newPhone;
					cout << "\nEnter new Phone: ";
					cin >> newPhone;
					staff->setPhone(newPhone);
					break;
				}
				case 4: {
					string newNric;
					cout << "\nEnter new NRIC: ";
					getline(cin, newNric);
					staff->setNric(newNric);
					break;
				}
				case 5: {
					string newRole;
					int newRoleOp;

					cout << "\n--- Available Roles ---\n";
					cout << "1. Admin\n";
					cout << "2. Staff\n";
					cout << "3. Counsellor\n\n";

					cout << "Enter your choice (1-3): ";
					cin >> newRoleOp;

					switch(newRoleOp) {
						case 1: {
							newRole="Admin";
							cout << "Selected: Admin\n";
							break;
						}

						case 2: {
							newRole="Staff";
							cout << "Selected: Staff\n";
							break;
						}

						case 3: {
							newRole="Counsellor";
							cout << "Selected: Counsellor\n";
							break;
						}

						default: {
							newRole=staff->getRole();
							cout << "Invalid choice, please try again." << endl;
						}
					}

					staff->setRole(newRole);

					break;
				}
				case 6: {
					string newPassword;
					cout << "\nEnter new Password: ";
					maskPwd(newPassword);
					staff->setPassword(newPassword);
					break;
				}
				case 7: {
					string newStatus;
					int newStatusOp;

					cout << "\n--- Available Status ---\n";
					cout << "1. Active\n";
					cout << "2. Inactive\n\n";

					cout << "Enter your choice (1-2): ";
					cin >> newStatusOp;

					switch(newStatusOp) {
						case 1: {
							newStatus="Active";
							cout << "Selected: Active\n";
							break;
						}

						case 2: {
							newStatus="Inactive";
							cout << "Selected: Inactive\n";
							break;
						}

						default: {
							newStatus=staff->getStatus();
							cout << "Invalid choice, please try again." << endl;
						}
					}

					staff->setStatus(newStatus);

					break;
				}
				case 0:
					saveUpdatedStaff(staffTable);
					cout << staff->getFName() << " profile updated successfully!" << endl;
					break;
				default:
					cout << "Invalid choice, please try again." << endl;
			}
		} while (choice != 0);
	}

	// Delete staff
	void deleteStaff(StaffHT& staffTable, int index) {
		if (index < 0 || index >= staffTable.TBL_SIZE || staffTable.tbl[index] == NULL) {
			cout << "Invalid staff index." << endl;
			return;
		}
		
		char confirm;
		cout << "Are you sure you want to delete this staff? (Y/N): ";
		cin >> confirm;
		
		if (toupper(confirm) == 'Y') {
			delete staffTable.tbl[index];
			staffTable.tbl[index] = NULL;
			
			saveUpdatedStaff(staffTable);
			cout << "Staff deleted successfully!" << endl;
		} else {
			cout << "Deletion cancelled." << endl;
		}
	}

	// Save updated patient information to file
	void saveUpdatedPatients(PtHT& patientTable) {
		ofstream outFile("patient.txt");
		
		if (outFile.is_open()) {
			for (int i = 0; i < patientTable.TBL_SIZE; i++) {
				if (patientTable.tbl[i] != NULL) {
					outFile << patientTable.tbl[i]->getFName() << endl;
					outFile << patientTable.tbl[i]->getLName() << endl;
					outFile << patientTable.tbl[i]->getPhone() << endl;
					outFile << patientTable.tbl[i]->getEmail() << endl;
					outFile << patientTable.tbl[i]->getAge() << endl;
					outFile << patientTable.tbl[i]->getPassword() << endl;
					outFile << patientTable.tbl[i]->getStatus() << endl << endl;
				}
			}
			outFile.close();
		} else {
			cout << "Unable to open patient.txt for writing." << endl;
		}
	}

	// Save updated staff information to file
	void saveUpdatedStaff(StaffHT& staffTable) {
		ofstream outFile("staff.txt");
		
		if (outFile.is_open()) {
			for (int i = 0; i < staffTable.TBL_SIZE; i++) {
				if (staffTable.tbl[i] != NULL) {
					outFile << staffTable.tbl[i]->getFName() << endl;
					outFile << staffTable.tbl[i]->getLName() << endl;
					outFile << staffTable.tbl[i]->getPhone() << endl;
					outFile << staffTable.tbl[i]->getEmail() << endl;
					outFile << staffTable.tbl[i]->getNric() << endl;
					outFile << staffTable.tbl[i]->getPassword() << endl;
					outFile << staffTable.tbl[i]->getRole() << endl;
					outFile << staffTable.tbl[i]->getStatus() << endl << endl;
				}
			}
			outFile.close();
		} else {
			cout << "Unable to open staff.txt for writing." << endl;
		}
	}

};

// Hash table for tickets using quadratic probing
class TicketHT {
	private:
		const int TBL_SIZE = 100;
		ticket** tbl;
		
		// Hash function for ticket name
		int hashFn(string name) {
			int sum = 0;
			
			for (int i = 0; i < name.length(); i++) {
				sum += (int)name[i];   // Sum ASCII values
			}
			
			return sum % TBL_SIZE;
		}
		
	public:
		// Constructor
		TicketHT() {
			tbl = new ticket*[TBL_SIZE]; 
			for (int i = 0; i < TBL_SIZE; i++) {
				tbl[i] = NULL;
			}
		}
		
		// Destructor
		~TicketHT() {
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					delete tbl[i];
				}
			}
			delete[] tbl;
		}

		// Getter for table element
		ticket* getEntry(int index) {
			if (index >= 0 && index < TBL_SIZE)
				return tbl[index];
			return NULL;
		}
		
		// Setter for table element
		void setTableElement(int index, ticket* value) {
			if (index >= 0 && index < TBL_SIZE)
				tbl[index] = value;
		}
		
		// Insert ticket using quadratic probing
		void insert(ticket* tkt) {
			int hash = hashFn(tkt->name);
			int i = 0;
			
			// Quadratic probing: h+0Â², h+1Â², h+2Â², h+3Â²...
			while (tbl[(hash + i*i) % TBL_SIZE] != NULL) {
				i++;
				if (i >= TBL_SIZE) {
					cout << "Hash table is full!" << endl;
					return;
				}
			}
			
			tbl[(hash + i*i) % TBL_SIZE] = new ticket;
			*tbl[(hash + i*i) % TBL_SIZE] = *tkt;
		}
		
		// Read tickets from file and insert into hash table
		void loadFromFile() {
			ifstream inFile("ticket.txt");
			ticket* tkt;
			
			if (inFile.is_open()) {
				while (!inFile.eof()) {
					tkt = new ticket;
					
					getline(inFile, tkt->name);
					if (tkt->name.empty() || inFile.eof()) {
						delete tkt;
						break;
					}
					
					inFile >> tkt->phone;
					inFile.ignore();
					getline(inFile, tkt->email);
					inFile >> tkt->date;
					inFile.ignore();
					getline(inFile, tkt->content);
					getline(inFile, tkt->status);
					
					string temp;
					getline(inFile, temp);
					
					insert(tkt);
				}
				inFile.close();
				cout << "Tickets loaded successfully!" << endl;
			} else {
				cout << "Unable to open ticket.txt for reading." << endl;
			}
		}
		
		// Display all tickets in hash table
		void displayAllTickets() {
			int count = 0;
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL) {
					cout << "\n--- Ticket " << ++count << " ---" << endl;
					cout << "Name    : " << tbl[i]->name << endl;
					cout << "Phone   : " << tbl[i]->phone << endl;
					cout << "Email   : " << tbl[i]->email << endl;
					cout << "Date    : " << tbl[i]->date << endl;
					cout << "Content : " << tbl[i]->content << endl;
					cout << "Status  : " << tbl[i]->status << endl;
				}
			}
			if (count == 0) {
				cout << "No tickets found." << endl;
			}
		}

		// Display tickets for a specific user by email
		void displayUserTickets(string email) {
			int count = 0;
			for (int i = 0; i < TBL_SIZE; i++) {
				if (tbl[i] != NULL && tbl[i]->email == email) {
					cout << "\n--- Ticket " << ++count << " ---" << endl;
					cout << "Name    : " << tbl[i]->name << endl;
					cout << "Phone   : " << tbl[i]->phone << endl;
					cout << "Date    : " << tbl[i]->date << endl;
					cout << "Content : " << tbl[i]->content << endl;
					cout << "Status  : " << tbl[i]->status << endl;
				}
			}
			if (count == 0) {
				cout << "No tickets found." << endl;
			}
		}

		int getTableSize() { 
		return TBL_SIZE; 
	}
};

// Base class for Ticket
class Ticket {
	protected:
		ticket data; 
		
	public:
		// Constructor
		Ticket() {
			data.name = "";
			data.phone = 0;
			data.email = "";
			data.date = 0;
			data.content = "";
			data.status = "Created";
		}
		
		// Destructor
		~Ticket() {

		}
		
		// Save ticket to file
		void saveTicketToFile(ticket& tkt, string filename = "ticket.txt") {
			ofstream outFile;
			outFile.open(filename, ios::app);  
		
			if (outFile.is_open()) {
				outFile << tkt.name << endl;
				outFile << tkt.phone << endl;
				outFile << tkt.email << endl;
				outFile << tkt.date << endl;
				outFile << tkt.content << endl;
				outFile << tkt.status << endl << endl;
		
				outFile.close();
			} else {
				cout << "Unable to open " << filename << " for saving." << endl;
			}
		}
		
		// Update tickets file
		void updateTicketFile(TicketHT& ticketTable, string filename = "ticket.txt") {
			ofstream outFile(filename);
			
			if (outFile.is_open()) {
				for (int i = 0; i < ticketTable.getTableSize(); i++) {
					ticket* tkt = ticketTable.getEntry(i);
					if (tkt != NULL) {
						outFile << tkt->name << endl;
						outFile << tkt->phone << endl;
						outFile << tkt->email << endl;
						outFile << tkt->date << endl;
						outFile << tkt->content << endl;
						outFile << tkt->status << endl << endl;
					}
				}
				outFile.close();
			} else {
				cout << "Unable to open " << filename << " for updating." << endl;
			}
    	}
};

// Derived class for ticket management
class TicketManager : public Ticket {
public:
    // Add new ticket
    void addTicket(TicketHT& ticketTable, string currentLastName, string currentFirstName, int currentPhone, string currentEmail) {
        string name, content;
        int date, phone;
        string email;
        
        name = currentFirstName + " " + currentLastName;
        phone = currentPhone;
        email = currentEmail;
        
        checkAppointDateInput(date);
        cin.ignore();
        
        cout << "Enter Content: ";
        getline(cin, content);
        
        // Fill data
        ticket tkt;
        tkt.name = name;
        tkt.phone = phone;
        tkt.email = email;
        tkt.date = date;
        tkt.content = content;
        tkt.status = "Created";
        
        char choice;
        cout << "\nDo you want to save this ticket? (Y/N): ";
        cin >> choice;
        
        if (toupper(choice) == 'Y') {
            saveTicketToFile(tkt);
            ticketTable.insert(&tkt);
            cout << "Ticket added successfully!" << endl;
        } else {
            cout << "Ticket not saved!" << endl;
        }
    }
    
	// Add new ticket
	void addTicket(TicketHT& ticketTable) {
		string firstName, lastName, name, content, email;
		int date, phone;
		
		cin.ignore();
		cout << "\nEnter First Name: ";
		getline(cin, firstName);
		
		cout << "Enter Last Name: ";
		getline(cin, lastName);
		
		// Combine first and last name
		name = firstName + " " + lastName;
		
		cout << "Enter Phone Number: +60";
		bool validPhone = false;

		while (!validPhone) {
			if (cin >> phone) {
				if (isValidPhone(phone)) {
					validPhone = true;
				} else {
					cout << "Invalid phone number. Please enter 9-10 digits: +60";
				}
			}
		}
		cin.ignore();
		
		bool validEmail = false;
		while (!validEmail) {
			cout << "Enter Email: ";
			cin >> email;
			if (isValidEmail(email)) {
				validEmail = true;
			} else {
				cout << "Invalid email format. Please try again.\n";
			}
		}
		
		checkAppointDateInput(date);
		cin.ignore();
		
		cout << "Enter Content: ";
		getline(cin, content);
		
		// Fill data
		ticket tkt;
		tkt.name = name;
		tkt.phone = phone;
		tkt.email = email;
		tkt.date = date;
		tkt.content = content;
		tkt.status = "Created";
		
		char choice;
		cout << "\nDo you want to save this ticket? (Y/N): ";
		cin >> choice;
		
		if (toupper(choice) == 'Y') {
			saveTicketToFile(tkt);
			ticketTable.insert(&tkt);
			cout << "Ticket added successfully!" << endl;
		} else {
			cout << "Ticket not saved!" << endl;
		}
	}
    
    // Edit ticket
    void editTicket(TicketHT& ticketTable) {
        // Create an array of tickets
        ticket* ticketArray[ticketTable.getTableSize()];
        int count = 0;
        int tableIndices[ticketTable.getTableSize()]; // To track original indices
        
        for (int i = 0; i < ticketTable.getTableSize(); i++) {
            if (ticketTable.getEntry(i) != NULL) {
                ticketArray[count] = ticketTable.getEntry(i);
                tableIndices[count] = i;
                count++;
            }
        }
        
        if (count == 0) {
            cout << "No tickets available to edit." << endl;
            return;
        }
        
        // Display all tickets with numbers
        cout << "\n--- Available Tickets ---\n";
        for (int i = 0; i < count; i++) {
            cout << (i+1) << ". " << ticketArray[i]->name << " - " 
                << ticketArray[i]->date << " (" 
                << ticketArray[i]->content.substr(0, 20) << "...)" << endl;
        }
        
        // Let user select a ticket
        int tktChoice;
        cout << "\nEnter the number of the ticket to edit (1-" << count << "): ";
        cin >> tktChoice;
        
        if (tktChoice < 1 || tktChoice > count) {
            cout << "Invalid selection." << endl;
            return;
        }
        
        int selectedIndex = tableIndices[tktChoice-1];
        ticket* selectedTkt = ticketTable.getEntry(selectedIndex);
        int choice;
        
        do {
            cout << "\n--- Edit Ticket ---" << endl;
            cout << "1. Edit Content (Current: " << selectedTkt->content << ")" << endl;
            cout << "2. Edit Status  (Current: " << selectedTkt->status << ")" << endl;
            cout << "0. Save and Return\n" << endl;
            cout << "Select field to edit (0-2): ";
            cin >> choice;
            
            cin.ignore();
            
            switch(choice) {
                case 1: {
                    string newContent;
                    cout << "Enter new Content: ";
                    getline(cin, newContent);
                    selectedTkt->content = newContent;
                    break;
                }
                case 2: {
                    int statusOp;
                    cout << "\n--- Status Options ---\n";
                    cout << "1. Created\n";
                    cout << "2. In Progress\n";
                    cout << "3. Resolved\n";
                    cout << "4. Closed\n\n";
                    cout << "Enter your choice (1-4): ";
                    cin >> statusOp;
                    cin.ignore();
                    
                    switch(statusOp) {
                        case 1:
                            selectedTkt->status = "Created";
                            break;
                        case 2:
                            selectedTkt->status = "In Progress";
                            break;
                        case 3:
                            selectedTkt->status = "Resolved";
                            break;
                        case 4:
                            selectedTkt->status = "Closed";
                            break;
                        default:
                            cout << "Invalid choice, status unchanged." << endl;
                    }
                    break;
                }
                case 0:
                    updateTicketFile(ticketTable);
                    cout << "Ticket updated successfully!" << endl;
                    break;
                default:
                    cout << "Invalid choice, please try again." << endl;
            }
        } while (choice != 0);
    }
    
    // Delete ticket
    void deleteTicket(TicketHT& ticketTable) {
        // Create an array of tickets
        ticket* ticketArray[ticketTable.getTableSize()];
        int count = 0;
        int tableIndices[ticketTable.getTableSize()]; // To track original indices
        
        for (int i = 0; i < ticketTable.getTableSize(); i++) {
            if (ticketTable.getEntry(i) != NULL) {
                ticketArray[count] = ticketTable.getEntry(i);
                tableIndices[count] = i;
                count++;
            }
        }
        
        if (count == 0) {
            cout << "No tickets available to delete." << endl;
            return;
        }
        
        // Display all tickets with numbers
        cout << "\n--- Available Tickets ---\n";
        for (int i = 0; i < count; i++) {
            cout << (i+1) << ". " << ticketArray[i]->name << " - " 
                << ticketArray[i]->date << " (" 
                << ticketArray[i]->content.substr(0, 20) << "...)" << endl;
        }
        
        // Let user select a ticket
        int tktChoice;
        cout << "\nEnter the number of the ticket to delete (1-" << count << "): ";
        cin >> tktChoice;
        
        if (tktChoice < 1 || tktChoice > count) {
            cout << "Invalid selection." << endl;
            return;
        }
        
        int selectedIndex = tableIndices[tktChoice-1];
        ticket* selectedTkt = ticketTable.getEntry(selectedIndex);
        
        char confirm;
        cout << "\nAre you sure you want to delete ticket for " << selectedTkt->name << "? (Y/N): ";
        cin >> confirm;
        
        if (toupper(confirm) == 'Y') {
            // Delete the ticket from the hash table
            delete ticketTable.getEntry(selectedIndex);
            ticketTable.setTableElement(selectedIndex, NULL);
            
            // Update the file
            updateTicketFile(ticketTable);
            cout << "Ticket deleted successfully!" << endl;
        } else {
            cout << "Deletion cancelled." << endl;
        }
    }

	// Overloaded deleteTicket - only delete specific user's tickets
    void deleteTicket(TicketHT& ticketTable, string currentEmail) {
        // Create an array of tickets
        ticket* ticketArray[ticketTable.getTableSize()];
        int count = 0;
        int tableIndices[ticketTable.getTableSize()]; // To track original indices
        
        for (int i = 0; i < ticketTable.getTableSize(); i++) {
            if (ticketTable.getEntry(i) != NULL && ticketTable.getEntry(i)->email == currentEmail) {
                ticketArray[count] = ticketTable.getEntry(i);
                tableIndices[count] = i;
                count++;
            }
        }
        
        if (count == 0) {
            cout << "No tickets available to delete." << endl;
            return;
        }
        
        // Display user's tickets with numbers
        cout << "\n--- Your Tickets ---\n";
        for (int i = 0; i < count; i++) {
            cout << (i+1) << ". Date: " << ticketArray[i]->date << " - " 
                << "Content: " << ticketArray[i]->content.substr(0, 20) << "..." << endl;
        }
        
        // Let user select a ticket
        int tktChoice;
        cout << "\nEnter the number of the ticket to delete (1-" << count << "): ";
        cin >> tktChoice;
        
        if (tktChoice < 1 || tktChoice > count) {
            cout << "Invalid selection." << endl;
            return;
        }
        
        int selectedIndex = tableIndices[tktChoice-1];
        ticket* selectedTkt = ticketTable.getEntry(selectedIndex);
        
        char confirm;
        cout << "\nAre you sure you want to delete this ticket? (Y/N): ";
        cin >> confirm;
        
        if (toupper(confirm) == 'Y') {
            delete ticketTable.getEntry(selectedIndex);
            ticketTable.setTableElement(selectedIndex, NULL);
            
            updateTicketFile(ticketTable);
            cout << "Ticket deleted successfully!" << endl;
        } else {
            cout << "Deletion cancelled." << endl;
        }
    }
};

class SearchSort{
	private:
		int first, last, mid, found = 0;
		int i, j;
		int currentMin = 0;
		int count = 0;
		int index = 0;
				
	public:
		// Display search appointment details
		void displayAppointment(appoint* apt) {
			if (!apt) return;
			cout << "\n--- Appointment Found ---\n";
			cout << "ID             : " << apt->appointID << "\n";
			cout << "Service        : " << apt->appointSvc << "\n";
			cout << "Counselor      : " << apt->appointCouns << "\n";
			cout << "Mode           : " << apt->appointMode << "\n";
			cout << "Date           : " << apt->appointDate << "\n";
			cout << "Time           : " << apt->appointTime << "\n";
			cout << "Patient        : " << apt->appointPtName << "\n";
			cout << "Phone          : " << apt->appointPtPhone << "\n";
			cout << "Email          : " << apt->appointPtEmail << "\n";
			cout << "Net Amount     : " << apt->appointNetAmt << "\n";
			cout << "Payment Status : " << apt->appointPayStat << "\n";
			cout << "Status         : " << apt->appointStat << "\n";
		}

		// Sort appointments by patient name (Selection Sort)
		void sortByPTName(appoint** apps, int size) {
			for ( i = 0; i < size - 1; i++) {
				currentMin = i; 
				for ( j = i + 1; j < size; j++) {
					if (apps[j]->appointPtName < apps[currentMin]->appointPtName) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					appoint* temp = apps[i];
					apps[i] = apps[currentMin];
					apps[currentMin] = temp;
				}
			}
		}
		
		// Sort appointments by Counsellors (Selection Sort)
		void sortByCouns(appoint** apps, int size) {
			for ( i = 0; i < size - 1; i++) {
				currentMin = i; 
				for ( j = i + 1; j < size; j++) {
					if (apps[j]->appointCouns < apps[currentMin]->appointCouns) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					appoint* temp = apps[i];
					apps[i] = apps[currentMin];
					apps[currentMin] = temp;
				}
			}
		}
		
		//Sort appointments by Email (Selection Sort
		void sortByEmail(appoint** apps, int size){
		for ( i = 0; i < size - 1; i++) {
				currentMin = i; 
				for ( j = i + 1; j < size; j++) {
					if (apps[j]->appointPtEmail < apps[currentMin]->appointPtEmail) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					appoint* temp = apps[i];
					apps[i] = apps[currentMin];
					apps[currentMin] = temp;
				}
			}
		}
		
		// Sort appointments by Service (Selection Sort)
		void sortByService(appoint** apps, int size) {
			for (int i = 0; i < size - 1; i++) {
				currentMin = i;
				for (int j = i + 1; j < size; j++) {
					if (apps[j]->appointSvc < apps[currentMin]->appointSvc) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					appoint* temp = apps[i];
					apps[i] = apps[currentMin];
					apps[currentMin] = temp;
				}
			}
		}
		
		// Sort appointments by Mode (Selection Sort)
		void sortByMode(appoint** apps, int size) {
			for (int i = 0; i < size - 1; i++) {
				currentMin = i;
				for (int j = i + 1; j < size; j++) {
					if (apps[j]->appointMode < apps[currentMin]->appointMode) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					appoint* temp = apps[i];
					apps[i] = apps[currentMin];
					apps[currentMin] = temp;
				}
			}
		}
		
		// Sort appointments by Patient's Phone (Selection Sort)
		void sortByPtPhone(appoint** apps, int size) {
			for (int i = 0; i < size - 1; i++) {
				currentMin = i;
				for (int j = i + 1; j < size; j++) {
					if (apps[j]->appointPtPhone < apps[currentMin]->appointPtPhone) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					appoint* temp = apps[i];
					apps[i] = apps[currentMin];
					apps[currentMin] = temp;
				}
			}
		}
		
		// Sort appointments by Payment Status (Selection Sort)
		void sortByPaymentState(appoint** apps, int size) {
			for (int i = 0; i < size - 1; i++) {
				currentMin = i;
				for (int j = i + 1; j < size; j++) {
					if (apps[j]->appointPayStat < apps[currentMin]->appointPayStat) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					appoint* temp = apps[i];
					apps[i] = apps[currentMin];
					apps[currentMin] = temp;
				}
			}
		}
		
		// Sort appointments by Appointment Status (Selection Sort)
		void sortByStatus(appoint** apps, int size) {
			for (int i = 0; i < size - 1; i++) {
				currentMin = i;
				for (int j = i + 1; j < size; j++) {
					if (apps[j]->appointStat < apps[currentMin]->appointStat) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					appoint* temp = apps[i];
					apps[i] = apps[currentMin];
					apps[currentMin] = temp;
				}
			}
		}
		
		// Searh Appointment by Patient Name (Binary Search)
		void SearchbyPatientName(AppointHT& appointmentTable) {
			string targetName;
			
			cout << "\nEnter Customer Name to search: ";
			cin.ignore();
			getline(cin, targetName);
			
			// Count non-null appointments
			count = 0;
			for ( i = 0; i < appointmentTable.getTableSize() ; i++) {
				if (appointmentTable.getEntry(i) != NULL) {
					count++;
				}
			}
				
			if (count == 0) {
				cout << "No appointments available to search." << endl;
				return;
			}
				
			// Create dynamic array
			appoint** appointments = new appoint*[count];
			index = 0;
			for ( i = 0; i < appointmentTable.getTableSize() ; i++) {
				if (appointmentTable.getEntry(i) != NULL) {
					appointments[index++] = appointmentTable.getEntry(i);
				}
			}  
			
			//Call sort Function
			sortByPTName(appointments, count);
			
			first = 0;
			last = count - 1;
			found = 0;
			
			while (first <= last) {
					mid = first + (last - first) / 2;
					string currentName = appointments[mid]->appointPtName;
	
					if (currentName == targetName) {
						// Display the found appointment
						displayAppointment(appointments[mid]);
						found = 1;
	
						// Check for duplicates on left side	*Idea From AI for solving data duplicate
						int firstDup = mid - 1;
						while (firstDup >= 0 && appointments[firstDup]->appointPtName == targetName) {
							displayAppointment(appointments[firstDup]);
							found++;
							firstDup--;
						}
	
						// Check for duplicates on right side	*Idea From AI *Idea From AI for solving data duplicate
						int lastDup = mid + 1;
						while (lastDup < count && appointments[lastDup]->appointPtName == targetName) {
							displayAppointment(appointments[lastDup]);
							found++;
							lastDup++;
						}
	
						cout << "\nTotal matches found: " << found << endl;
						delete[] appointments;
						return;
					}
	
					if (currentName < targetName) {
						first = mid + 1;
					} else {
						last = mid - 1;
					}
				}
	
				if (!found) {
					cout << "No appointments found for: " << targetName << endl;
				}
				delete[] appointments; 
		}
	
		// Searh Appointment by Email (Binary Search)
		void SearchbyEmail(AppointHT& appointmentTable) {
			string targetEmail;
			
			cout << "\nEnter counsellor to search: ";
			cin.ignore();
			getline(cin, targetEmail);
			
			// Count non-null appointments
			count = 0;
			for ( i = 0; i < appointmentTable.getTableSize() ; i++) {
				if (appointmentTable.getEntry(i) != NULL) {
					count++;
				}
			}
				
			if (count == 0) {
				cout << "No appointments available to search." << endl;
				return;
			}
				
			// Create dynamic array
			appoint** appointments = new appoint*[count];
			index = 0;
			for ( i = 0; i < appointmentTable.getTableSize() ; i++) {
				if (appointmentTable.getEntry(i) != NULL) {
					appointments[index++] = appointmentTable.getEntry(i);
				}
			}  
			
			sortByEmail(appointments, count);
			
			first = 0;
			last = count - 1;
			found = 0;
			
			while (first <= last) {
					mid = first + (last - first) / 2;
					string currentEmail = appointments[mid]->appointPtEmail;
	
					if (currentEmail == targetEmail) {
						// Display the found appointment
						displayAppointment(appointments[mid]);
						found = 1;
	
						// Check for duplicates on left side
						int firstDup = mid - 1;
						while (firstDup >= 0 && appointments[firstDup]->appointPtEmail == targetEmail) {
							displayAppointment(appointments[firstDup]);
							found++;
							firstDup--;
						}
	
						// Check for duplicates on right side
						int lastDup = mid + 1;
						while (lastDup < count && appointments[lastDup]->appointPtEmail == targetEmail) {
							displayAppointment(appointments[lastDup]);
							found++;
							lastDup++;
						}
	
						cout << "\nTotal matches found: " << found << endl;
						delete[] appointments;
						return;
					}
	
					if (currentEmail < targetEmail) {
						first = mid + 1;
					} else {
						last = mid - 1;
					}
				}
	
				if (!found) {
					cout << "No appointments found for: " << targetEmail << endl;
				}
				delete[] appointments; 
		}
		
		// Search appointments by Service (Binary Search)
		void SearchbyService(AppointHT& appointmentTable, SvcHT& serviceHT) {
			int serviceCount = 0;
			for (int i = 0; i < serviceHT.getTableSize(); i++) {
				if (serviceHT.getEntry(i) != NULL) {
					serviceCount++;
				}
			}
			
			if (serviceCount == 0) {
				cout << "No services available. Please add services first." << endl;
				return;
			}

			// Create and populate services array
			svc** services = new svc*[serviceCount];
			int index = 0;
			for (int i = 0; i < serviceHT.getTableSize(); i++) {
				if (serviceHT.getEntry(i) != NULL) {
					services[index++] = serviceHT.getEntry(i);
				}
			}

			// Sort services by name
			for (int i = 0; i < serviceCount - 1; i++) {
				int currentMin = i;
				for (int j = i + 1; j < serviceCount; j++) {
					if (services[j]->svcName < services[currentMin]->svcName) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					svc* temp = services[i];
					services[i] = services[currentMin];
					services[currentMin] = temp;
				}
			}

			// Display available services
			cout << "\n--- Available Services ---\n";
			for (int i = 0; i < serviceCount; i++) {
				cout << i+1 << ". " << services[i]->svcName << endl;
			}

			// Get user selection
			int selection;
			do {
				cout << "\nSelect a service (1-" << serviceCount << "): ";
				cin >> selection;
				
				if (selection < 1 || selection > serviceCount) {
					cout << "Invalid selection. Please choose from the list (1-" << serviceCount << ")." << endl;
				}
			} while (selection < 1 || selection > serviceCount);

			string targetSvc = services[selection-1]->svcName;
			
			// Count non-null appointments
			int count = 0;
			for (i = 0; i < appointmentTable.getTableSize(); i++) {
				if (appointmentTable.getEntry(i) != NULL) {
					count++;
				}
			}
				
			if (count == 0) {
				cout << "No appointments available to search." << endl;
				return;
			}
				
			// Create dynamic array
			appoint** appointments = new appoint*[count];
			index = 0;
			for (i = 0; i < appointmentTable.getTableSize(); i++) {
				if (appointmentTable.getEntry(i) != NULL) {
					appointments[index++] = appointmentTable.getEntry(i);
				}
			}  
			
			sortByService(appointments, count);
			
			first = 0;
			last = count - 1;
			found = 0;
			
			while (first <= last) {
				int mid = first + (last - first) / 2;
				string currentSvc = appointments[mid]->appointSvc;
		
				if (currentSvc == targetSvc) {
					// Display the found appointment
					displayAppointment(appointments[mid]);
					found++;
		
					// Check for duplicates on left side
					int firstDup = mid - 1;
					while (firstDup >= 0 && appointments[firstDup]->appointSvc == targetSvc) {
						displayAppointment(appointments[firstDup]);
						found++;
						firstDup--;
					}
		
					// Check for duplicates on right side
					int lastDup = mid + 1;
					while (lastDup < count && appointments[lastDup]->appointSvc == targetSvc) {
						displayAppointment(appointments[lastDup]);
						found++;
						lastDup++;
					}
		
					cout << "\nTotal matches found: " << found << endl;
					delete[] appointments;
					return;
				}
		
				if (currentSvc < targetSvc) {
					first = mid + 1;
				} else {
					last = mid - 1;
				}
			}
		
			if (!found) {
				cout << "No appointments found for service: " << targetSvc << endl;
			}
			delete[] appointments; 
		}
		
		// Search appointments by Patient's Phone (Binary Search)
		void SearchbyPtPhone(AppointHT& appointmentTable) {
			int targetPhone;
			
			cout << "\nEnter patient's phone number to search: ";
			cin >> targetPhone;
			cin.ignore(); // Clear newline
			
			// Count non-null appointments
			count = 0;
			for (i = 0; i < appointmentTable.getTableSize(); i++) {
				if (appointmentTable.getEntry(i) != NULL) {
					count++;
				}
			}
				
			if (count == 0) {
				cout << "No appointments available to search." << endl;
				return;
			}
				
			// Create dynamic array
			appoint** appointments = new appoint*[count];
			index = 0;
			for (i = 0; i < appointmentTable.getTableSize(); i++) {
				if (appointmentTable.getEntry(i) != NULL) {
					appointments[index++] = appointmentTable.getEntry(i);
				}
			}  
			
			sortByPtPhone(appointments, count);
			
			first = 0;
			last = count - 1;
			found = 0;
			
			while (first <= last) {
				int mid = first + (last - first) / 2;
				int currentPhone = appointments[mid]->appointPtPhone;
		
				if (currentPhone == targetPhone) {
					// Display the found appointment
					displayAppointment(appointments[mid]);
					found++;
		
					// Check for duplicates on left side
					int firstDup = mid - 1;
					while (firstDup >= 0 && appointments[firstDup]->appointPtPhone == targetPhone) {
						displayAppointment(appointments[firstDup]);
						found++;
						firstDup--;
					}
		
					// Check for duplicates on right side
					int lastDup = mid + 1;
					while (lastDup < count && appointments[lastDup]->appointPtPhone == targetPhone) {
						displayAppointment(appointments[lastDup]);
						found++;
						lastDup++;
					}
		
					cout << "\nTotal matches found: " << found << endl;
					delete[] appointments;
					return;
				}
		
				if (currentPhone < targetPhone) {
					first = mid + 1;
				} else {
					last = mid - 1;
				}
			}
		
			if (!found) {
				cout << "No appointments found for phone number: " << targetPhone << endl;
			}
			delete[] appointments; 
		}

		// Search appointments by Appointment Status (Binary Search)
		void SearchbyStatus(AppointHT& appointmentTable) {
			string targetStat;
			
			int choice;
			
			cout << "\n--- Search Appointments by Status ---\n";
			cout << "1. Pending\n";
			cout << "2. Approved\n";
			cout << "3. Rejected\n";
			cout << "4. Cancelled\n";
			cout << "\nEnter your choice (1-4): ";
			cin >> choice;
			
			switch(choice) {
				case 1: 
					targetStat = "Pending"; 
					break;
				case 2: 
					targetStat = "Approved"; 
					break;
				case 3: 
					targetStat = "Rejected"; 
					break;
				case 4: 
					targetStat = "Cancelled"; 
					break;
				default:
					cout << "Invalid choice. Returning to menu.\n";
					return;
			}
			
			// Count non-null appointments
			count = 0;
			for (i = 0; i < appointmentTable.getTableSize(); i++) {
				if (appointmentTable.getEntry(i) != NULL) {
					count++;
				}
			}
				
			if (count == 0) {
				cout << "No appointments available to search." << endl;
				return;
			}
				
			// Create dynamic array
			appoint** appointments = new appoint*[count];
			index = 0;
			for (i = 0; i < appointmentTable.getTableSize(); i++) {
				if (appointmentTable.getEntry(i) != NULL) {
					appointments[index++] = appointmentTable.getEntry(i);
				}
			}  
			
			sortByStatus(appointments, count);
			
			first = 0;
			last = count - 1;
			found = 0;
			
			while (first <= last) {
				int mid = first + (last - first) / 2;
				string currentStat = appointments[mid]->appointStat;
		
				if (currentStat == targetStat) {
					// Display the found appointment
					displayAppointment(appointments[mid]);
					found++;
		
					// Check for duplicates on left side
					int firstDup = mid - 1;
					while (firstDup >= 0 && appointments[firstDup]->appointStat == targetStat) {
						displayAppointment(appointments[firstDup]);
						found++;
						firstDup--;
					}
		
					// Check for duplicates on right side
					int lastDup = mid + 1;
					while (lastDup < count && appointments[lastDup]->appointStat == targetStat) {
						displayAppointment(appointments[lastDup]);
						found++;
						lastDup++;
					}
		
					cout << "\nTotal matches found: " << found << endl;
					delete[] appointments;
					return;
				}
		
				if (currentStat < targetStat) {
					first = mid + 1;
				} else {
					last = mid - 1;
				}
			}
		
			if (!found) {
				cout << "No appointments found for status: " << targetStat << endl;
			}
			delete[] appointments; 
		}
		
		// Patient search appointments by Counsellor (Binary Search)
		void PatientSearchByCounsellor(AppointHT& appointmentTable, string patientEmail) {
	    
		string counsellorName;
		cout << "\nEnter counsellor name to search: ";
		cin.ignore();
		getline(cin, counsellorName);
		
		// Count non-null appointments that belong to the patient
	    count = 0;
	    for (i = 0; i < appointmentTable.getTableSize(); i++) {
	        if (appointmentTable.getEntry(i) != NULL && 
	            appointmentTable.getEntry(i)->appointPtEmail == patientEmail) {
	            count++;
	        }
	    }
	        
	    if (count == 0) {
	        cout << "You don't have any appointments." << endl;
	        return;
	    }
	        
	    // Create dynamic array of patient's appointments only
	    appoint** patientAppointments = new appoint*[count];
	    index = 0;
	    for (i = 0; i < appointmentTable.getTableSize(); i++) {
	        if (appointmentTable.getEntry(i) != NULL && 
	            appointmentTable.getEntry(i)->appointPtEmail == patientEmail) {
	            patientAppointments[index++] = appointmentTable.getEntry(i);
	        }
	    }
	    
	    // Sort appointments by counsellor name
	    sortByCouns(patientAppointments, count);
	    
	    // Binary search
	    first = 0;
	    last = count - 1;
	    found = 0;
	    
	    while (first <= last) {
	        mid = first + (last - first) / 2;
	        string currentCouns = patientAppointments[mid]->appointCouns;
	
	        if (currentCouns == counsellorName) {
	            // Display the found appointment
	            displayAppointment(patientAppointments[mid]);
	            found = 1;
	
	            // Check for duplicates on left side
	            int firstDup = mid - 1;
	            while (firstDup >= 0 && patientAppointments[firstDup]->appointCouns == counsellorName) {
	                displayAppointment(patientAppointments[firstDup]);
	                found++;
	                firstDup--;
	            }
	
	            // Check for duplicates on right side
	            int lastDup = mid + 1;
	            while (lastDup < count && patientAppointments[lastDup]->appointCouns == counsellorName) {
	                displayAppointment(patientAppointments[lastDup]);
	                found++;
	                lastDup++;
	            }
	
	            cout << "\nTotal appointments found: " << found << endl;
	            delete[] patientAppointments;
	            return;
	        }
	
	        if (currentCouns < counsellorName) {
	            first = mid + 1;
	        } else {
	            last = mid - 1;
	        }
	    }
	
	    if (!found) {
	        cout << "No appointments found with counsellor: " << counsellorName << endl;
	    }
	    
	    delete[] patientAppointments;
	}

		// Patient search appointments by Service (Binary Search)
		void PatientSearchByService(AppointHT& appointmentTable, SvcHT& serviceHT, string patientEmail) {
			// Count services
			int serviceCount = 0;
			for (int i = 0; i < serviceHT.getTableSize(); i++) {
				if (serviceHT.getEntry(i) != NULL) {
					serviceCount++;
				}
			}
			
			if (serviceCount == 0) {
				cout << "No services available in the system." << endl;
				return;
			}

			// Create and populate services array
			svc** services = new svc*[serviceCount];
			int serviceIndex = 0;
			for (int i = 0; i < serviceHT.getTableSize(); i++) {
				if (serviceHT.getEntry(i) != NULL) {
					services[serviceIndex++] = serviceHT.getEntry(i);
				}
			}

			// Sort services by name
			for (int i = 0; i < serviceCount - 1; i++) {
				int currentMin = i;
				for (int j = i + 1; j < serviceCount; j++) {
					if (services[j]->svcName < services[currentMin]->svcName) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					svc* temp = services[i];
					services[i] = services[currentMin];
					services[currentMin] = temp;
				}
			}

			// Display available services
			cout << "\n--- Available Services ---\n";
			for (int i = 0; i < serviceCount; i++) {
				cout << i+1 << ". " << services[i]->svcName << endl;
			}

			// Get user selection
			int selection;
			do {
				cout << "\nSelect a service (1-" << serviceCount << "): ";
				cin >> selection;
				
				if (selection < 1 || selection > serviceCount) {
					cout << "Invalid selection. Please choose from the list (1-" << serviceCount << ")." << endl;
				}
			} while (selection < 1 || selection > serviceCount);

			string targetService = services[selection-1]->svcName;
			
			// Count patient's appointments
			int count = 0;
		    for (i = 0; i < appointmentTable.getTableSize(); i++) {
		        if (appointmentTable.getEntry(i) != NULL && 
		            appointmentTable.getEntry(i)->appointPtEmail == patientEmail) {
		            count++;
		        }
		    }
		        
		    if (count == 0) {
		        cout << "You don't have any appointments." << endl;
		        return;
		    }
		        
		    appoint** patientAppointments = new appoint*[count];
		    index = 0;
		    for (i = 0; i < appointmentTable.getTableSize(); i++) {
		        if (appointmentTable.getEntry(i) != NULL && 
		            appointmentTable.getEntry(i)->appointPtEmail == patientEmail) {
		            patientAppointments[index++] = appointmentTable.getEntry(i);
		        }
		    }
		    
		    sortByService(patientAppointments, count);
		    
		    first = 0;
		    last = count - 1;
		    found = 0;
		    
		    while (first <= last) {
		        mid = first + (last - first) / 2;
		        string currentService = patientAppointments[mid]->appointSvc;
		
		        if (currentService == targetService) {
		            displayAppointment(patientAppointments[mid]);
		            found = 1;
		
		            int leftDup = mid - 1;
		            while (leftDup >= 0 && patientAppointments[leftDup]->appointSvc == targetService) {
		                displayAppointment(patientAppointments[leftDup]);
		                found++;
		                leftDup--;
		            }
		
		            int rightDup = mid + 1;
		            while (rightDup < count && patientAppointments[rightDup]->appointSvc == targetService) {
		                displayAppointment(patientAppointments[rightDup]);
		                found++;
		                rightDup++;
		            }
		
		            cout << "\nTotal appointments found: " << found << endl;
		            delete[] patientAppointments;
		            return;
		        }
		
		        if (currentService < targetService) {
		            first = mid + 1;
		        } else {
		            last = mid - 1;
		        }
		    }
		
		    cout << "No appointments found with service: " << targetService << endl;
		    delete[] patientAppointments;
		}

		// Search Treatments by Appointment ID (Binary Search)
		void SearchTxByAppointID(TxHT& treatmentTable) {
		    string targetID;
		    
		    cout << "\nEnter Appointment ID to search: ";
		    cin.ignore();
		    getline(cin, targetID);
		    
		    count = 0;
		    for (i = 0; i < treatmentTable.getTblSize(); i++) {
		        if (treatmentTable.getEntry(i) != NULL) {
		            count++;
		        }
		    }
		        
		    if (count == 0) {
		        cout << "No treatments available." << endl;
		        return;
		    }
		        
		    tx** treatments = new tx*[count];
		    index = 0;
		    for (i = 0; i < treatmentTable.getTblSize(); i++) {
		        if (treatmentTable.getEntry(i) != NULL) {
		            treatments[index++] = treatmentTable.getEntry(i);
		        }
		    }  
		    
		    for (i = 0; i < count - 1; i++) {
		        currentMin = i;
		        for (j = i + 1; j < count; j++) {
		            if (treatments[j]->appointID < treatments[currentMin]->appointID) {
		                currentMin = j;
		            }
		        }
		        if (currentMin != i) {
		            tx* temp = treatments[i];
		            treatments[i] = treatments[currentMin];
		            treatments[currentMin] = temp;
		        }
		    }
		    
		    first = 0;
		    last = count - 1;
		    found = 0;
		    
		    while (first <= last) {
		        mid = first + (last - first) / 2;
		        string currentID = treatments[mid]->appointID;
		
		        if (currentID == targetID) {
		            DisplayTreatment(treatments[mid]);
		            found = 1;
		
		            int firstDup = mid - 1;
		            while (firstDup >= 0 && treatments[firstDup]->appointID == targetID) {
		                DisplayTreatment(treatments[firstDup]);
		                found++;
		                firstDup--;
		            }
		
		            int lastDup = mid + 1;
		            while (lastDup < count && treatments[lastDup]->appointID == targetID) {
		                DisplayTreatment(treatments[lastDup]);
		                found++;
		                lastDup++;
		            }
		
		            cout << "\nTotal matches: " << found << endl;
		            delete[] treatments;
		            return;
		        }
		
		        if (currentID < targetID) {
		            first = mid + 1;
		        } else {
		            last = mid - 1;
		        }
		    }
		
		    if (!found) {
		        cout << "No treatments found for ID: " << targetID << endl;
		    }
		    delete[] treatments;
		}
		
		// Search Treatments by Patient Name (Binary Search)
		void SearchTxByPatientName(TxHT& treatmentTable) {
		    string targetName;
		    
		    cout << "\nEnter Patient Name to search: ";
		    cin.ignore();
		    getline(cin, targetName);
		    
		    count = 0;
		    for (i = 0; i < treatmentTable.getTblSize(); i++) {
		        if (treatmentTable.getEntry(i) != NULL) {
		            count++;
		        }
		    }
		        
		    if (count == 0) {
		        cout << "No treatments available." << endl;
		        return;
		    }
		        
		    tx** treatments = new tx*[count];
		    index = 0;
		    for (i = 0; i < treatmentTable.getTblSize(); i++) {
		        if (treatmentTable.getEntry(i) != NULL) {
		            treatments[index++] = treatmentTable.getEntry(i);
		        }
		    }  
		    
		    for (i = 0; i < count - 1; i++) {
		        currentMin = i;
		        for (j = i + 1; j < count; j++) {
		            if (treatments[j]->ptName < treatments[currentMin]->ptName) {
		                currentMin = j;
		            }
		        }
		        if (currentMin != i) {
		            tx* temp = treatments[i];
		            treatments[i] = treatments[currentMin];
		            treatments[currentMin] = temp;
		        }
		    }
		    
		    first = 0;
		    last = count - 1;
		    found = 0;
		    
		    while (first <= last) {
		        mid = first + (last - first) / 2;
		        string currentName = treatments[mid]->ptName;
		
		        if (currentName == targetName) {
		            DisplayTreatment(treatments[mid]);
		            found = 1;
		
		            int firstDup = mid - 1;
		            while (firstDup >= 0 && treatments[firstDup]->ptName == targetName) {
		                DisplayTreatment(treatments[firstDup]);
		                found++;
		                firstDup--;
		            }
		
		            int lastDup = mid + 1;
		            while (lastDup < count && treatments[lastDup]->ptName == targetName) {
		                DisplayTreatment(treatments[lastDup]);
		                found++;
		                lastDup++;
		            }
		
		            cout << "\nTotal matches: " << found << endl;
		            delete[] treatments;
		            return;
		        }
		
		        if (currentName < targetName) {
		            first = mid + 1;
		        } else {
		            last = mid - 1;
		        }
		    }
		
		    if (!found) {
		        cout << "No treatments found for patient: " << targetName << endl;
		    }
		    delete[] treatments;
		}
		
		// Search Treatments by Patient Phone (Binary Search)
		void SearchTxByPatientPhone(TxHT& treatmentTable) {
		    int targetPhone;
		    
		    cout << "\nEnter Patient Phone to search: ";
		    cin >> targetPhone;
		    cin.ignore();
		    
		    count = 0;
		    for (i = 0; i < treatmentTable.getTblSize(); i++) {
		        if (treatmentTable.getEntry(i) != NULL) {
		            count++;
		        }
		    }
		        
		    if (count == 0) {
		        cout << "No treatments available." << endl;
		        return;
		    }
		        
		    tx** treatments = new tx*[count];
		    index = 0;
		    for (i = 0; i < treatmentTable.getTblSize(); i++) {
		        if (treatmentTable.getEntry(i) != NULL) {
		            treatments[index++] = treatmentTable.getEntry(i);
		        }
		    }  
		    
		    for (i = 0; i < count - 1; i++) {
		        currentMin = i;
		        for (j = i + 1; j < count; j++) {
		            if (treatments[j]->ptPhone < treatments[currentMin]->ptPhone) {
		                currentMin = j;
		            }
		        }
		        if (currentMin != i) {
		            tx* temp = treatments[i];
		            treatments[i] = treatments[currentMin];
		            treatments[currentMin] = temp;
		        }
		    }
		    
		    first = 0;
		    last = count - 1;
		    found = 0;
		    
		    while (first <= last) {
		        mid = first + (last - first) / 2;
		        int currentPhone = treatments[mid]->ptPhone;
		
		        if (currentPhone == targetPhone) {
		            DisplayTreatment(treatments[mid]);
		            found = 1;
		
		            int firstDup = mid - 1;
		            while (firstDup >= 0 && treatments[firstDup]->ptPhone == targetPhone) {
		                DisplayTreatment(treatments[firstDup]);
		                found++;
		                firstDup--;
		            }
		
		            int lastDup = mid + 1;
		            while (lastDup < count && treatments[lastDup]->ptPhone == targetPhone) {
		                DisplayTreatment(treatments[lastDup]);
		                found++;
		                lastDup++;
		            }
		
		            cout << "\nTotal matches: " << found << endl;
		            delete[] treatments;
		            return;
		        }
		
		        if (currentPhone < targetPhone) {
		            first = mid + 1;
		        } else {
		            last = mid - 1;
		        }
		    }
		
		    if (!found) {
		        cout << "No treatments found for phone: " << targetPhone << endl;
		    }
		    delete[] treatments;
		}
		
		// Search Treatments by Patient Email (Binary Search)
		void SearchTxByPatientEmail(TxHT& treatmentTable) {
		    string targetEmail;
		    
		    cout << "\nEnter Patient Email to search: ";
		    cin.ignore();
		    getline(cin, targetEmail);
		    
		    count = 0;
		    for (i = 0; i < treatmentTable.getTblSize(); i++) {
		        if (treatmentTable.getEntry(i) != NULL) {
		            count++;
		        }
		    }
		        
		    if (count == 0) {
		        cout << "No treatments available." << endl;
		        return;
		    }
		        
		    tx** treatments = new tx*[count];
		    index = 0;
		    for (i = 0; i < treatmentTable.getTblSize(); i++) {
		        if (treatmentTable.getEntry(i) != NULL) {
		            treatments[index++] = treatmentTable.getEntry(i);
		        }
		    }  
		    
		    for (i = 0; i < count - 1; i++) {
		        currentMin = i;
		        for (j = i + 1; j < count; j++) {
		            if (treatments[j]->ptEmail < treatments[currentMin]->ptEmail) {
		                currentMin = j;
		            }
		        }
		        if (currentMin != i) {
		            tx* temp = treatments[i];
		            treatments[i] = treatments[currentMin];
		            treatments[currentMin] = temp;
		        }
		    }
		    
		    first = 0;
		    last = count - 1;
		    found = 0;
		    
		    while (first <= last) {
		        mid = first + (last - first) / 2;
		        string currentEmail = treatments[mid]->ptEmail;
		
		        if (currentEmail == targetEmail) {
		            DisplayTreatment(treatments[mid]);
		            found = 1;
		
		            int firstDup = mid - 1;
		            while (firstDup >= 0 && treatments[firstDup]->ptEmail == targetEmail) {
		                DisplayTreatment(treatments[firstDup]);
		                found++;
		                firstDup--;
		            }
		
		            int lastDup = mid + 1;
		            while (lastDup < count && treatments[lastDup]->ptEmail == targetEmail) {
		                DisplayTreatment(treatments[lastDup]);
		                found++;
		                lastDup++;
		            }
		
		            cout << "\nTotal matches: " << found << endl;
		            delete[] treatments;
		            return;
		        }
		
		        if (currentEmail < targetEmail) {
		            first = mid + 1;
		        } else {
		            last = mid - 1;
		        }
		    }
		
		    if (!found) {
		        cout << "No treatments found for email: " << targetEmail << endl;
		    }
		    delete[] treatments;
		}
		
		// Helper function to display treatment details
		void DisplayTreatment(tx* treatment) {
		    cout << "\n--- Treatment Details ---" << endl;
		    cout << "Appointment ID : " << treatment->appointID << endl;
		    cout << "Patient Name   : " << treatment->ptName << endl;
		    cout << "Patient Phone  : " << treatment->ptPhone << endl;
		    cout << "Patient Email  : " << treatment->ptEmail << endl;
		    cout << "Summary        : " << treatment->summary << endl;
		    cout << "Intervention   : " << treatment->intervention << endl;
		    cout << "Response       : " << treatment->response << endl;
		    cout << "Progress       : " << treatment->progress << endl;
		    cout << "Homework       : " << treatment->homework << endl;
		    cout << "Next Session   : " << treatment->nextSession << endl;
		}

		// Search Results by Situation (Binary Search)
		void SearchResultsBySituation(resultHT& resultTable) {
		    string targetSituation;
			int targetSituationOp;
		    
			cout << "\n--- Available Situation ---\n";
			cout << "1. Low Stress\n";
			cout << "2. Moderate Stress\n";
			cout << "3. High Stress\n";
			cout << "4. Very High Stress\n\n";

			cout << "Enter your choice (1-4): ";
			cin >> targetSituationOp;

			switch(targetSituationOp) {
				case 1: {
					targetSituation="Low Stress";
					cout << "Selected: Low Stress\n";
					break;
				}

				case 2: {
					targetSituation="Moderate Stress";
					cout << "Selected: Moderate Stress\n";
					break;
				}

				case 3: {
					targetSituation="High Stress";
					cout << "Selected: High Stress\n";
					break;
				}

				case 4: {
					targetSituation="Very High Stress";
					cout << "Selected: Very High Stress\n";
					break;
				}

				default: {
					cout << "Invalid choice, please try again.\n";
				}
			}
		    
		    // Count non-null results
		    count = 0;
		    for (i = 0; i < resultTable.getTableSize(); i++) {
		        if (resultTable.getEntry(i) != NULL) {
		            count++;
		        }
		    }
		        
		    if (count == 0) {
		        cout << "No test results available to search." << endl;
		        return;
		    }
		        
		    // Create dynamic array
		    result** results = new result*[count];
		    index = 0;
		    for (i = 0; i < resultTable.getTableSize(); i++) {
		        if (resultTable.getEntry(i) != NULL) {
		            results[index++] = resultTable.getEntry(i);
		        }
		    }  
		    
		    // Sort results by situation (selection sort)
		    for (i = 0; i < count - 1; i++) {
		        currentMin = i;
		        for (j = i + 1; j < count; j++) {
		            if (results[j]->situation < results[currentMin]->situation) {
		                currentMin = j;
		            }
		        }
		        if (currentMin != i) {
		            result* temp = results[i];
		            results[i] = results[currentMin];
		            results[currentMin] = temp;
		        }
		    }
		    
		    // Binary search
		    first = 0;
		    last = count - 1;
		    found = 0;
		    
		    while (first <= last) {
		        mid = first + (last - first) / 2;
		        string currentSituation = results[mid]->situation;
		
		        if (currentSituation == targetSituation) {
		            // Display found result
		            cout << "\n--- Result Found ---" << endl;
		            cout << "Patient Name : " << results[mid]->name << endl;
		            cout << "Phone        : " << results[mid]->phone << endl;
		            cout << "Email        : " << results[mid]->email << endl;
		            cout << "Score        : " << results[mid]->score << endl;
		            cout << "Situation    : " << results[mid]->situation << endl;
		            found = 1;
		
		            // Check for duplicates on left side
		            int firstDup = mid - 1;
		            while (firstDup >= 0 && results[firstDup]->situation == targetSituation) {
		                cout << "\n--- Result Found ---" << endl;
		                cout << "Patient Name : " << results[firstDup]->name << endl;
		                cout << "Score        : " << results[firstDup]->score << endl;
		                cout << "Situation    : " << results[firstDup]->situation << endl;
		                found++;
		                firstDup--;
		            }
		
		            // Check for duplicates on right side
		            int lastDup = mid + 1;
		            while (lastDup < count && results[lastDup]->situation == targetSituation) {
		                cout << "\n--- Result Found ---" << endl;
		                cout << "Patient Name : " << results[lastDup]->name << endl;
		                cout << "Score        : " << results[lastDup]->score << endl;
		                cout << "Situation    : " << results[lastDup]->situation << endl;
		                found++;
		                lastDup++;
		            }
		
		            cout << "\nTotal matches found: " << found << endl;
		            delete[] results;
		            return;
		        }
		
		        if (currentSituation < targetSituation) {
		            first = mid + 1;
		        } else {
		            last = mid - 1;
		        }
		    }
		
		    if (!found) {
		        cout << "\nNo results found for situation: " << targetSituation << endl;
		    }
		    delete[] results;
		}
		
		// Search Results by Name (Binary Search)
		void SearchResultsByName(resultHT& resultTable) {
		    string targetName;
		    
		    cout << "\nEnter patient name to search: ";
		    cin.ignore();
		    getline(cin, targetName);
		    
		    // Count non-null results
		    count = 0;
		    for (i = 0; i < resultTable.getTableSize(); i++) {
		        if (resultTable.getEntry(i) != NULL) {
		            count++;
		        }
		    }
		        
		    if (count == 0) {
		        cout << "No test results available to search." << endl;
		        return;
		    }
		        
		    // Create dynamic array
		    result** results = new result*[count];
		    index = 0;
		    for (i = 0; i < resultTable.getTableSize(); i++) {
		        if (resultTable.getEntry(i) != NULL) {
		            results[index++] = resultTable.getEntry(i);
		        }
		    }  
		    
		    // Sort results by name (selection sort)
		    for (i = 0; i < count - 1; i++) {
		        currentMin = i;
		        for (j = i + 1; j < count; j++) {
		            if (results[j]->name < results[currentMin]->name) {
		                currentMin = j;
		            }
		        }
		        if (currentMin != i) {
		            result* temp = results[i];
		            results[i] = results[currentMin];
		            results[currentMin] = temp;
		        }
		    }
		    
		    // Binary search
		    first = 0;
		    last = count - 1;
		    found = 0;
		    
		    while (first <= last) {
		        mid = first + (last - first) / 2;
		        string currentName = results[mid]->name;
		
		        if (currentName == targetName) {
		            // Display found result
		            cout << "\n--- Result Found ---" << endl;
		            cout << "Patient Name : " << results[mid]->name << endl;
		            cout << "Phone        : " << results[mid]->phone << endl;
		            cout << "Email        : " << results[mid]->email << endl;
		            cout << "Score        : " << results[mid]->score << endl;
		            cout << "Situation    : " << results[mid]->situation << endl;
		            found = 1;
		
		            // Check for duplicates on left side
		            int firstDup = mid - 1;
		            while (firstDup >= 0 && results[firstDup]->name == targetName) {
		                cout << "\n--- Result Found ---" << endl;
		                cout << "Patient Name : " << results[firstDup]->name << endl;
		                cout << "Phone        : " << results[firstDup]->phone << endl;
		                cout << "Email        : " << results[firstDup]->email << endl;
		                cout << "Score        : " << results[firstDup]->score << endl;
		                cout << "Situation    : " << results[firstDup]->situation << endl;
		                found++;
		                firstDup--;
		            }
		
		            // Check for duplicates on right side
		            int lastDup = mid + 1;
		            while (lastDup < count && results[lastDup]->name == targetName) {
		                cout << "\n--- Result Found ---" << endl;
		                cout << "Patient Name : " << results[lastDup]->name << endl;
		                cout << "Phone        : " << results[lastDup]->phone << endl;
		                cout << "Email        : " << results[lastDup]->email << endl;
		                cout << "Score        : " << results[lastDup]->score << endl;
		                cout << "Situation    : " << results[lastDup]->situation << endl;
		                found++;
		                lastDup++;
		            }
		
		            cout << "\nTotal matches found: " << found << endl;
		            delete[] results;
		            return;
		        }
		
		        if (currentName < targetName) {
		            first = mid + 1;
		        } else {
		            last = mid - 1;
		        }
		    }
		
		    if (!found) {
		        cout << "No results found for name: " << targetName << endl;
		    }
		    delete[] results;
		}
		
		// Search Results by Phone (Binary Search)
		void SearchResultsByPhone(resultHT& resultTable) {
		    int targetPhone;
		    
		    cout << "\nEnter patient phone to search: ";
		    cin >> targetPhone;
		    cin.ignore();
		    
		    // Count non-null results
		    count = 0;
		    for (i = 0; i < resultTable.getTableSize(); i++) {
		        if (resultTable.getEntry(i) != NULL) {
		            count++;
		        }
		    }
		        
		    if (count == 0) {
		        cout << "No test results available to search." << endl;
		        return;
		    }
		        
		    // Create dynamic array
		    result** results = new result*[count];
		    index = 0;
		    for (i = 0; i < resultTable.getTableSize(); i++) {
		        if (resultTable.getEntry(i) != NULL) {
		            results[index++] = resultTable.getEntry(i);
		        }
		    }  
		    
		    // Sort results by phone (selection sort)
		    for (i = 0; i < count - 1; i++) {
		        currentMin = i;
		        for (j = i + 1; j < count; j++) {
		            if (results[j]->phone < results[currentMin]->phone) {
		                currentMin = j;
		            }
		        }
		        if (currentMin != i) {
		            result* temp = results[i];
		            results[i] = results[currentMin];
		            results[currentMin] = temp;
		        }
		    }
		    
		    // Binary search
		    first = 0;
		    last = count - 1;
		    found = 0;
		    
		    while (first <= last) {
		        mid = first + (last - first) / 2;
		        int currentPhone = results[mid]->phone;
		
		        if (currentPhone == targetPhone) {
		            // Display found result
		            cout << "\n--- Result Found ---" << endl;
		            cout << "Patient Name : " << results[mid]->name << endl;
		            cout << "Phone        : " << results[mid]->phone << endl;
		            cout << "Email        : " << results[mid]->email << endl;
		            cout << "Score        : " << results[mid]->score << endl;
		            cout << "Situation    : " << results[mid]->situation << endl;
		            found = 1;
		
		            // Check for duplicates on left side
		            int firstDup = mid - 1;
		            while (firstDup >= 0 && results[firstDup]->phone == targetPhone) {
		                cout << "\n--- Result Found ---" << endl;
		                cout << "Patient Name : " << results[firstDup]->name << endl;
		                cout << "Phone        : " << results[firstDup]->phone << endl;
		                cout << "Email        : " << results[firstDup]->email << endl;
		                cout << "Score        : " << results[firstDup]->score << endl;
		                cout << "Situation    : " << results[firstDup]->situation << endl;
		                found++;
		                firstDup--;
		            }
		
		            // Check for duplicates on right side
		            int lastDup = mid + 1;
		            while (lastDup < count && results[lastDup]->phone == targetPhone) {
		                cout << "\n--- Result Found ---" << endl;
		                cout << "Patient Name : " << results[lastDup]->name << endl;
		                cout << "Phone        : " << results[lastDup]->phone << endl;
		                cout << "Email        : " << results[lastDup]->email << endl;
		                cout << "Score        : " << results[lastDup]->score << endl;
		                cout << "Situation    : " << results[lastDup]->situation << endl;
		                found++;
		                lastDup++;
		            }
		
		            cout << "\nTotal matches found: " << found << endl;
		            delete[] results;
		            return;
		        }
		
		        if (currentPhone < targetPhone) {
		            first = mid + 1;
		        } else {
		            last = mid - 1;
		        }
		    }
		
		    if (!found) {
		        cout << "No results found for phone: " << targetPhone << endl;
		    }
		    delete[] results;
		}
		
		// Search Results by Email (Binary Search)
		void SearchResultsByEmail(resultHT& resultTable) {
		    string targetEmail;
		    
		    cout << "\nEnter patient email to search: ";
		    cin.ignore();
		    getline(cin, targetEmail);
		    
		    // Count non-null results
		    count = 0;
		    for (i = 0; i < resultTable.getTableSize(); i++) {
		        if (resultTable.getEntry(i) != NULL) {
		            count++;
		        }
		    }
		        
		    if (count == 0) {
		        cout << "No test results available to search." << endl;
		        return;
		    }
		        
		    // Create dynamic array
		    result** results = new result*[count];
		    index = 0;
		    for (i = 0; i < resultTable.getTableSize(); i++) {
		        if (resultTable.getEntry(i) != NULL) {
		            results[index++] = resultTable.getEntry(i);
		        }
		    }  
		    
		    // Sort results by email (selection sort)
		    for (i = 0; i < count - 1; i++) {
		        currentMin = i;
		        for (j = i + 1; j < count; j++) {
		            if (results[j]->email < results[currentMin]->email) {
		                currentMin = j;
		            }
		        }
		        if (currentMin != i) {
		            result* temp = results[i];
		            results[i] = results[currentMin];
		            results[currentMin] = temp;
		        }
		    }
		    
		    // Binary search
		    first = 0;
		    last = count - 1;
		    found = 0;
		    
		    while (first <= last) {
		        mid = first + (last - first) / 2;
		        string currentEmail = results[mid]->email;
		
		        if (currentEmail == targetEmail) {
		            // Display found result
		            cout << "\n--- Result Found ---" << endl;
		            cout << "Patient Name : " << results[mid]->name << endl;
		            cout << "Phone        : " << results[mid]->phone << endl;
		            cout << "Email        : " << results[mid]->email << endl;
		            cout << "Score        : " << results[mid]->score << endl;
		            cout << "Situation    : " << results[mid]->situation << endl;
		            found = 1;
		
		            // Check for duplicates on left side
		            int firstDup = mid - 1;
		            while (firstDup >= 0 && results[firstDup]->email == targetEmail) {
		                cout << "\n--- Result Found ---" << endl;
		                cout << "Patient Name : " << results[firstDup]->name << endl;
		                cout << "Phone        : " << results[firstDup]->phone << endl;
		                cout << "Email        : " << results[firstDup]->email << endl;
		                cout << "Score        : " << results[firstDup]->score << endl;
		                cout << "Situation    : " << results[firstDup]->situation << endl;
		                found++;
		                firstDup--;
		            }
		
		            // Check for duplicates on right side
		            int lastDup = mid + 1;
		            while (lastDup < count && results[lastDup]->email == targetEmail) {
		                cout << "\n--- Result Found ---" << endl;
		                cout << "Patient Name : " << results[lastDup]->name << endl;
		                cout << "Phone        : " << results[lastDup]->phone << endl;
		                cout << "Email        : " << results[lastDup]->email << endl;
		                cout << "Score        : " << results[lastDup]->score << endl;
		                cout << "Situation    : " << results[lastDup]->situation << endl;
		                found++;
		                lastDup++;
		            }
		
		            cout << "\nTotal matches found: " << found << endl;
		            delete[] results;
		            return;
		        }
		
		        if (currentEmail < targetEmail) {
		            first = mid + 1;
		        } else {
		            last = mid - 1;
		        }
		    }
		
		    if (!found) {
		        cout << "No results found for email: " << targetEmail << endl;
		    }
		    delete[] results;
		}

		// Sort and Display Results by Score (High to Low) - Selection Sort
		void sortResultsByScoreDescending(resultHT& resultTable) {
			// Count non-null results
			count = 0;
			for (i = 0; i < resultTable.getTableSize(); i++) {
				if (resultTable.getEntry(i) != NULL) {
					count++;
				}
			}
			if (count == 0) {
				cout << "No test results to display." << endl;
				return;
			}
		
			// Create dynamic array
			result** results = new result*[count];
			index = 0;
			for (i = 0; i < resultTable.getTableSize(); i++) {
				if (resultTable.getEntry(i) != NULL) {
					results[index++] = resultTable.getEntry(i);
				}
			}
		
			// Sort results by score (descending - high to low)
			for (i = 0; i < count - 1; i++) {
				currentMin = i;
				for (j = i + 1; j < count; j++) {
					if (results[j]->score > results[currentMin]->score) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					result* temp = results[i];
					results[i] = results[currentMin];
					results[currentMin] = temp;
				}
			}
		
			// Display the sorted results
			cout << "\n--- Results Sorted by Score (High to Low) ---" << endl;
			for (i = 0; i < count; i++) {
				cout << "\n--- Result " << i+1 << " ---" << endl;
				cout << "Patient Name : " << results[i]->name << endl;
				cout << "Phone        : " << results[i]->phone << endl;
				cout << "Email        : " << results[i]->email << endl;
				cout << "Score        : " << results[i]->score << endl;
				cout << "Situation    : " << results[i]->situation << endl;
			}
		
			// Clean up
			delete[] results;
		}
		
		// Sort and Display Results by Score (Low to High) - Selection Sort
		void sortResultsByScoreAscending(resultHT& resultTable) {
			// Count non-null results
			count = 0;
			for (i = 0; i < resultTable.getTableSize(); i++) {
				if (resultTable.getEntry(i) != NULL) {
					count++;
				}
			}
			if (count == 0) {
				cout << "No test results to display." << endl;
				return;
			}
		
			// Create dynamic array
			result** results = new result*[count];
			index = 0;
			for (i = 0; i < resultTable.getTableSize(); i++) {
				if (resultTable.getEntry(i) != NULL) {
					results[index++] = resultTable.getEntry(i);
				}
			}
		
			// Sort results by score (ascending - low to high)
			for (i = 0; i < count - 1; i++) {
				currentMin = i;
				for (j = i + 1; j < count; j++) {
					if (results[j]->score < results[currentMin]->score) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					result* temp = results[i];
					results[i] = results[currentMin];
					results[currentMin] = temp;
				}
			}
		
			// Display the sorted results
			cout << "\nResults sorted by score (low to high):" << endl;
			for (i = 0; i < count; i++) {
				cout << "\n--- Result " << i+1 << " ---" << endl;
				cout << "Patient Name : " << results[i]->name << endl;
				cout << "Phone        : " << results[i]->phone << endl;
				cout << "Email        : " << results[i]->email << endl;
				cout << "Score        : " << results[i]->score << endl;
				cout << "Situation    : " << results[i]->situation << endl;
			}
		
			// Clean up
			delete[] results;
		}
		
		// Function to display patient information
		void displayPatient(Pt* patient) {
			if (!patient) return;
			cout << "\n--- Patient Details ---" << endl;
			cout << "First Name: " << patient->getFName() << endl;
			cout << "Last Name : " << patient->getLName() << endl;
			cout << "Phone     : " << patient->getPhone() << endl;
			cout << "Email     : " << patient->getEmail() << endl;
			cout << "Age       : " << patient->getAge() << endl;
			cout << "Status    : " << patient->getStatus() << endl;
		}

		// Search Patients by First Name (Binary Search)
		void SearchbyFirstName(PtHT& patientTable) {
			string targetFName;
			cout << "\nEnter first name to search: ";
			cin.ignore();
			getline(cin, targetFName);
			
			// Count non-null patients
			count = 0;
			for (i = 0; i < patientTable.getTblSize(); i++) {
				if (patientTable.getTableElement(i) != NULL) {
					count++;
				}
			}
				
			if (count == 0) {
				cout << "No patients available to search." << endl;
				return;
			}
				
			// Create dynamic array
			Pt** patients = new Pt*[count];
			index = 0;
			for (i = 0; i < patientTable.getTblSize(); i++) {
				if (patientTable.getTableElement(i) != NULL) {
					patients[index++] = patientTable.getTableElement(i);
				}
			}  
			
			// Sort by first name first (selection sort)
			for (i = 0; i < count - 1; i++) {
				currentMin = i; 
				for (j = i + 1; j < count; j++) {
					if (patients[j]->getFName() < patients[currentMin]->getFName()) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					Pt* temp = patients[i];
					patients[i] = patients[currentMin];
					patients[currentMin] = temp;
				}
			}
			
			first = 0;
			last = count - 1;
			found = 0;
			
			while (first <= last) {
				mid = first + (last - first) / 2;
				string currentFName = patients[mid]->getFName();

				if (currentFName == targetFName) {
					displayPatient(patients[mid]);
					found = 1;

					// Check for duplicates on left side
					int firstDup = mid - 1;
					while (firstDup >= 0 && patients[firstDup]->getFName() == targetFName) {
						displayPatient(patients[firstDup]);
						found++;
						firstDup--;
					}

					// Check for duplicates on right side
					int lastDup = mid + 1;
					while (lastDup < count && patients[lastDup]->getFName() == targetFName) {
						displayPatient(patients[lastDup]);
						found++;
						lastDup++;
					}

					cout << "\nTotal matches found: " << found << endl;
					delete[] patients;
					return;
				}

				if (currentFName < targetFName) {
					first = mid + 1;
				} else {
					last = mid - 1;
				}
			}

			if (!found) {
				cout << "No patients found with first name: " << targetFName << endl;
			}
			delete[] patients; 
		}

		// Search Patients by Last Name (Binary Search)
		void SearchbyLastName(PtHT& patientTable) {
			string targetLName;
			cout << "\nEnter last name to search: ";
			cin.ignore();
			getline(cin, targetLName);
			
			// Count non-null patients
			count = 0;
			for (i = 0; i < patientTable.getTblSize(); i++) {
				if (patientTable.getTableElement(i) != NULL) {
					count++;
				}
			}
				
			if (count == 0) {
				cout << "No patients available to search." << endl;
				return;
			}
				
			// Create dynamic array
			Pt** patients = new Pt*[count];
			index = 0;
			for (i = 0; i < patientTable.getTblSize(); i++) {
				if (patientTable.getTableElement(i) != NULL) {
					patients[index++] = patientTable.getTableElement(i);
				}
			}  
			
			// Sort by last name first (selection sort)
			for (i = 0; i < count - 1; i++) {
				currentMin = i; 
				for (j = i + 1; j < count; j++) {
					if (patients[j]->getLName() < patients[currentMin]->getLName()) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					Pt* temp = patients[i];
					patients[i] = patients[currentMin];
					patients[currentMin] = temp;
				}
			}
			
			first = 0;
			last = count - 1;
			found = 0;
			
			while (first <= last) {
				mid = first + (last - first) / 2;
				string currentLName = patients[mid]->getLName();

				if (currentLName == targetLName) {
					displayPatient(patients[mid]);
					found = 1;

					// Check for duplicates on left side
					int firstDup = mid - 1;
					while (firstDup >= 0 && patients[firstDup]->getLName() == targetLName) {
						displayPatient(patients[firstDup]);
						found++;
						firstDup--;
					}

					// Check for duplicates on right side
					int lastDup = mid + 1;
					while (lastDup < count && patients[lastDup]->getLName() == targetLName) {
						displayPatient(patients[lastDup]);
						found++;
						lastDup++;
					}

					cout << "\nTotal matches found: " << found << endl;
					delete[] patients;
					return;
				}

				if (currentLName < targetLName) {
					first = mid + 1;
				} else {
					last = mid - 1;
				}
			}

			if (!found) {
				cout << "No patients found with last name: " << targetLName << endl;
			}
			delete[] patients; 
		}

		// Search Patients by Phone (Binary Search)
		void SearchbyPhone(PtHT& patientTable) {
			int targetPhone;
			cout << "\nEnter phone number to search: +60";
			bool validPhone = false;

			while (!validPhone) {
				if (cin >> targetPhone) {
					if (isValidPhone(targetPhone)) {
						validPhone = true;
					} else {
						cout << "Invalid phone number. Please enter 9-10 digits: +60";
					}
				}
			}
			
			// Count non-null patients
			count = 0;
			for (i = 0; i < patientTable.getTblSize(); i++) {
				if (patientTable.getTableElement(i) != NULL) {
					count++;
				}
			}
				
			if (count == 0) {
				cout << "No patients available to search." << endl;
				return;
			}
				
			// Create dynamic array
			Pt** patients = new Pt*[count];
			index = 0;
			for (i = 0; i < patientTable.getTblSize(); i++) {
				if (patientTable.getTableElement(i) != NULL) {
					patients[index++] = patientTable.getTableElement(i);
				}
			}  
			
			// Sort by phone first (selection sort)
			for (i = 0; i < count - 1; i++) {
				currentMin = i; 
				for (j = i + 1; j < count; j++) {
					if (patients[j]->getPhone() < patients[currentMin]->getPhone()) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					Pt* temp = patients[i];
					patients[i] = patients[currentMin];
					patients[currentMin] = temp;
				}
			}
			
			first = 0;
			last = count - 1;
			found = 0;
			
			while (first <= last) {
				mid = first + (last - first) / 2;
				int currentPhone = patients[mid]->getPhone();

				if (currentPhone == targetPhone) {
					displayPatient(patients[mid]);
					found = 1;

					// Check for duplicates on left side
					int firstDup = mid - 1;
					while (firstDup >= 0 && patients[firstDup]->getPhone() == targetPhone) {
						displayPatient(patients[firstDup]);
						found++;
						firstDup--;
					}

					// Check for duplicates on right side
					int lastDup = mid + 1;
					while (lastDup < count && patients[lastDup]->getPhone() == targetPhone) {
						displayPatient(patients[lastDup]);
						found++;
						lastDup++;
					}

					cout << "\nTotal matches found: " << found << endl;
					delete[] patients;
					return;
				}

				if (currentPhone < targetPhone) {
					first = mid + 1;
				} else {
					last = mid - 1;
				}
			}

			if (!found) {
				cout << "No patients found with phone: " << targetPhone << endl;
			}
			delete[] patients; 
		}

		// Search Patients by Status (Binary Search)
		void SearchbyStatus(PtHT& patientTable) {
			string targetStatus;
			
			int statusChoice;
			cout << "\n--- Search by Status ---\n";
			cout << "1. Active\n";
			cout << "2. Inactive\n";
			cout << "\nEnter your choice (1-2): ";
			cin >> statusChoice;

			switch(statusChoice) {
				case 1:
					targetStatus = "Active";
					break;
				case 2:
					targetStatus = "Inactive";
					break;
				default:
					cout << "Invalid choice. Returning to menu.\n";
					return;
			}
			
			// Count non-null patients
			count = 0;
			for (i = 0; i < patientTable.getTblSize(); i++) {
				if (patientTable.getTableElement(i) != NULL) {
					count++;
				}
			}
				
			if (count == 0) {
				cout << "No patients available to search." << endl;
				return;
			}
				
			// Create dynamic array
			Pt** patients = new Pt*[count];
			index = 0;
			for (i = 0; i < patientTable.getTblSize(); i++) {
				if (patientTable.getTableElement(i) != NULL) {
					patients[index++] = patientTable.getTableElement(i);
				}
			}  
			
			// Sort by status first (selection sort)
			for (i = 0; i < count - 1; i++) {
				currentMin = i; 
				for (j = i + 1; j < count; j++) {
					if (patients[j]->getStatus() < patients[currentMin]->getStatus()) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					Pt* temp = patients[i];
					patients[i] = patients[currentMin];
					patients[currentMin] = temp;
				}
			}
			
			first = 0;
			last = count - 1;
			found = 0;
			
			while (first <= last) {
				mid = first + (last - first) / 2;
				string currentStatus = patients[mid]->getStatus();

				if (currentStatus == targetStatus) {
					displayPatient(patients[mid]);
					found = 1;

					// Check for duplicates on left side
					int firstDup = mid - 1;
					while (firstDup >= 0 && patients[firstDup]->getStatus() == targetStatus) {
						displayPatient(patients[firstDup]);
						found++;
						firstDup--;
					}

					// Check for duplicates on right side
					int lastDup = mid + 1;
					while (lastDup < count && patients[lastDup]->getStatus() == targetStatus) {
						displayPatient(patients[lastDup]);
						found++;
						lastDup++;
					}

					cout << "\nTotal matches found: " << found << endl;
					delete[] patients;
					return;
				}

				if (currentStatus < targetStatus) {
					first = mid + 1;
				} else {
					last = mid - 1;
				}
			}

			if (!found) {
				cout << "No patients found with status: " << targetStatus << endl;
			}
			delete[] patients; 
		}

		// Sort Patients by Age (Young to Old - Ascending)
		void sortByAgeAscending(PtHT& patientTable) {
			// Count non-null patients
			count = 0;
			for (i = 0; i < patientTable.getTblSize(); i++) {
				if (patientTable.getTableElement(i) != NULL) {
					count++;
				}
			}
			
			if (count == 0) {
				cout << "No patients to display." << endl;
				return;
			}
			
			// Create dynamic array
			Pt** patients = new Pt*[count];
			index = 0;
			for (i = 0; i < patientTable.getTblSize(); i++) {
				if (patientTable.getTableElement(i) != NULL) {
					patients[index++] = patientTable.getTableElement(i);
				}
			}
			
			// Selection sort by age (ascending)
			for (i = 0; i < count - 1; i++) {
				currentMin = i;
				for (j = i + 1; j < count; j++) {
					if (patients[j]->getAge() < patients[currentMin]->getAge()) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					Pt* temp = patients[i];
					patients[i] = patients[currentMin];
					patients[currentMin] = temp;
				}
			}
			
			// Display sorted patients
			cout << "\nPatients sorted by age (young to old): " << endl;
			for (i = 0; i < count; i++) {
				cout << "\n--- Patient " << i+1 << " ---" << endl;
				cout << "First Name: " << patients[i]->getFName() << endl;
				cout << "Last Name : " << patients[i]->getLName() << endl;
				cout << "Age       : " << patients[i]->getAge() << endl;
				cout << "Phone     : " << patients[i]->getPhone() << endl;
				cout << "Email     : " << patients[i]->getEmail() << endl;
				cout << "Status    : " << patients[i]->getStatus() << endl;
			}
			
			delete[] patients;
		}

		// Sort Patients by Age (Old to Young - Descending)
		void sortByAgeDescending(PtHT& patientTable) {
			// Count non-null patients
			count = 0;
			for (i = 0; i < patientTable.getTblSize(); i++) {
				if (patientTable.getTableElement(i) != NULL) {
					count++;
				}
			}
			
			if (count == 0) {
				cout << "No patients to display." << endl;
				return;
			}
			
			// Create dynamic array
			Pt** patients = new Pt*[count];
			index = 0;
			for (i = 0; i < patientTable.getTblSize(); i++) {
				if (patientTable.getTableElement(i) != NULL) {
					patients[index++] = patientTable.getTableElement(i);
				}
			}
			
			// Selection sort by age (descending)
			for (i = 0; i < count - 1; i++) {
				currentMin = i;
				for (j = i + 1; j < count; j++) {
					if (patients[j]->getAge() > patients[currentMin]->getAge()) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					Pt* temp = patients[i];
					patients[i] = patients[currentMin];
					patients[currentMin] = temp;
				}
			}
			
			// Display sorted patients
			cout << "\nPatients sorted by age (old to young):" << endl;
			for (i = 0; i < count; i++) {
				cout << "\n--- Patient " << i+1 << " ---" << endl;
				cout << "First Name: " << patients[i]->getFName() << endl;
				cout << "Last Name : " << patients[i]->getLName() << endl;
				cout << "Age       : " << patients[i]->getAge() << endl;
				cout << "Phone     : " << patients[i]->getPhone() << endl;
				cout << "Email     : " << patients[i]->getEmail() << endl;
				cout << "Status    : " << patients[i]->getStatus() << endl;
			}
			
			delete[] patients;
		}

		// Function to display staff information
		void displayStaff(Staff* staff) {
			if (!staff) return;
			cout << "\n--- Staff Details ---" << endl;
			cout << "First Name : " << staff->getFName() << endl;
			cout << "Last Name  : " << staff->getLName() << endl;
			cout << "Phone      : " << staff->getPhone() << endl;
			cout << "Email      : " << staff->getEmail() << endl;
			cout << "NRIC       : " << staff->getNric() << endl;
			cout << "Role       : " << staff->getRole() << endl;
			cout << "Status     : " << staff->getStatus() << endl;
		}

		// Search Staff by First Name (Binary Search)
		void SearchStaffByFirstName(StaffHT& staffTable) {
			string targetFName;
			cout << "\nEnter first name to search: ";
			cin.ignore();
			getline(cin, targetFName);
			
			// Count non-null staff
			count = 0;
			for (i = 0; i < staffTable.getTblSize(); i++) {
				if (staffTable.getTableElement(i) != NULL) {
					count++;
				}
			}
				
			if (count == 0) {
				cout << "No staff available to search." << endl;
				return;
			}
				
			// Create dynamic array
			Staff** staffs = new Staff*[count];
			index = 0;
			for (i = 0; i < staffTable.getTblSize(); i++) {
				if (staffTable.getTableElement(i) != NULL) {
					staffs[index++] = staffTable.getTableElement(i);
				}
			}  
			
			// Sort by first name (selection sort)
			for (i = 0; i < count - 1; i++) {
				currentMin = i; 
				for (j = i + 1; j < count; j++) {
					if (staffs[j]->getFName() < staffs[currentMin]->getFName()) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					Staff* temp = staffs[i];
					staffs[i] = staffs[currentMin];
					staffs[currentMin] = temp;
				}
			}
			
			first = 0;
			last = count - 1;
			found = 0;
			
			while (first <= last) {
				mid = first + (last - first) / 2;
				string currentFName = staffs[mid]->getFName();

				if (currentFName == targetFName) {
					displayStaff(staffs[mid]);
					found = 1;

					// Check for duplicates on left side
					int firstDup = mid - 1;
					while (firstDup >= 0 && staffs[firstDup]->getFName() == targetFName) {
						displayStaff(staffs[firstDup]);
						found++;
						firstDup--;
					}

					// Check for duplicates on right side
					int lastDup = mid + 1;
					while (lastDup < count && staffs[lastDup]->getFName() == targetFName) {
						displayStaff(staffs[lastDup]);
						found++;
						lastDup++;
					}

					cout << "\nTotal matches found: " << found << endl;
					delete[] staffs;
					return;
				}

				if (currentFName < targetFName) {
					first = mid + 1;
				} else {
					last = mid - 1;
				}
			}

			if (!found) {
				cout << "No staff found with first name: " << targetFName << endl;
			}
			delete[] staffs; 
		}

		// Search Staff by Last Name (Binary Search)
		void SearchStaffByLastName(StaffHT& staffTable) {
			string targetLName;
			cout << "\nEnter last name to search: ";
			cin.ignore();
			getline(cin, targetLName);
			
			// Count non-null staff
			count = 0;
			for (i = 0; i < staffTable.getTblSize(); i++) {
				if (staffTable.getTableElement(i) != NULL) {
					count++;
				}
			}
				
			if (count == 0) {
				cout << "No staff available to search." << endl;
				return;
			}
				
			// Create dynamic array
			Staff** staffs = new Staff*[count];
			index = 0;
			for (i = 0; i < staffTable.getTblSize(); i++) {
				if (staffTable.getTableElement(i) != NULL) {
					staffs[index++] = staffTable.getTableElement(i);
				}
			}  
			
			// Sort by last name (selection sort)
			for (i = 0; i < count - 1; i++) {
				currentMin = i; 
				for (j = i + 1; j < count; j++) {
					if (staffs[j]->getLName() < staffs[currentMin]->getLName()) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					Staff* temp = staffs[i];
					staffs[i] = staffs[currentMin];
					staffs[currentMin] = temp;
				}
			}
			
			first = 0;
			last = count - 1;
			found = 0;
			
			while (first <= last) {
				mid = first + (last - first) / 2;
				string currentLName = staffs[mid]->getLName();

				if (currentLName == targetLName) {
					displayStaff(staffs[mid]);
					found = 1;

					// Check for duplicates on left side
					int firstDup = mid - 1;
					while (firstDup >= 0 && staffs[firstDup]->getLName() == targetLName) {
						displayStaff(staffs[firstDup]);
						found++;
						firstDup--;
					}

					// Check for duplicates on right side
					int lastDup = mid + 1;
					while (lastDup < count && staffs[lastDup]->getLName() == targetLName) {
						displayStaff(staffs[lastDup]);
						found++;
						lastDup++;
					}

					cout << "\nTotal matches found: " << found << endl;
					delete[] staffs;
					return;
				}

				if (currentLName < targetLName) {
					first = mid + 1;
				} else {
					last = mid - 1;
				}
			}

			if (!found) {
				cout << "No staff found with last name: " << targetLName << endl;
			}
			delete[] staffs; 
		}

		// Search Staff by Phone (Binary Search)
		void SearchStaffByPhone(StaffHT& staffTable) {
			int targetPhone;
			cout << "\nEnter phone number to search: +60";
			bool validPhone = false;

			while (!validPhone) {
				if (cin >> targetPhone) {
					if (isValidPhone(targetPhone)) {
						validPhone = true;
					} else {
						cout << "Invalid phone number. Please enter 9-10 digits: +60";
					}
				}
			}
			
			// Count non-null staff
			count = 0;
			for (i = 0; i < staffTable.getTblSize(); i++) {
				if (staffTable.getTableElement(i) != NULL) {
					count++;
				}
			}
				
			if (count == 0) {
				cout << "No staff available to search." << endl;
				return;
			}
				
			// Create dynamic array
			Staff** staffs = new Staff*[count];
			index = 0;
			for (i = 0; i < staffTable.getTblSize(); i++) {
				if (staffTable.getTableElement(i) != NULL) {
					staffs[index++] = staffTable.getTableElement(i);
				}
			}  
			
			// Sort by phone (selection sort)
			for (i = 0; i < count - 1; i++) {
				currentMin = i; 
				for (j = i + 1; j < count; j++) {
					if (staffs[j]->getPhone() < staffs[currentMin]->getPhone()) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					Staff* temp = staffs[i];
					staffs[i] = staffs[currentMin];
					staffs[currentMin] = temp;
				}
			}
			
			first = 0;
			last = count - 1;
			found = 0;
			
			while (first <= last) {
				mid = first + (last - first) / 2;
				int currentPhone = staffs[mid]->getPhone();

				if (currentPhone == targetPhone) {
					displayStaff(staffs[mid]);
					found = 1;

					// Check for duplicates on left side
					int firstDup = mid - 1;
					while (firstDup >= 0 && staffs[firstDup]->getPhone() == targetPhone) {
						displayStaff(staffs[firstDup]);
						found++;
						firstDup--;
					}

					// Check for duplicates on right side
					int lastDup = mid + 1;
					while (lastDup < count && staffs[lastDup]->getPhone() == targetPhone) {
						displayStaff(staffs[lastDup]);
						found++;
						lastDup++;
					}

					cout << "\nTotal matches found: " << found << endl;
					delete[] staffs;
					return;
				}

				if (currentPhone < targetPhone) {
					first = mid + 1;
				} else {
					last = mid - 1;
				}
			}

			if (!found) {
				cout << "No staff found with phone: " << targetPhone << endl;
			}
			delete[] staffs; 
		}

		// Search Staff by Role (Binary Search)
		void SearchStaffByRole(StaffHT& staffTable) {
			string targetRole;
			cout << "\nEnter role to search: ";
			cin.ignore();
			getline(cin, targetRole);
			
			// Count non-null staff
			count = 0;
			for (i = 0; i < staffTable.getTblSize(); i++) {
				if (staffTable.getTableElement(i) != NULL) {
					count++;
				}
			}
				
			if (count == 0) {
				cout << "No staff available to search." << endl;
				return;
			}
				
			// Create dynamic array
			Staff** staffs = new Staff*[count];
			index = 0;
			for (i = 0; i < staffTable.getTblSize(); i++) {
				if (staffTable.getTableElement(i) != NULL) {
					staffs[index++] = staffTable.getTableElement(i);
				}
			}  
			
			// Sort by role (selection sort)
			for (i = 0; i < count - 1; i++) {
				currentMin = i; 
				for (j = i + 1; j < count; j++) {
					if (staffs[j]->getRole() < staffs[currentMin]->getRole()) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					Staff* temp = staffs[i];
					staffs[i] = staffs[currentMin];
					staffs[currentMin] = temp;
				}
			}
			
			first = 0;
			last = count - 1;
			found = 0;
			
			while (first <= last) {
				mid = first + (last - first) / 2;
				string currentRole = staffs[mid]->getRole();

				if (currentRole == targetRole) {
					displayStaff(staffs[mid]);
					found = 1;

					// Check for duplicates on left side
					int firstDup = mid - 1;
					while (firstDup >= 0 && staffs[firstDup]->getRole() == targetRole) {
						displayStaff(staffs[firstDup]);
						found++;
						firstDup--;
					}

					// Check for duplicates on right side
					int lastDup = mid + 1;
					while (lastDup < count && staffs[lastDup]->getRole() == targetRole) {
						displayStaff(staffs[lastDup]);
						found++;
						lastDup++;
					}

					cout << "\nTotal matches found: " << found << endl;
					delete[] staffs;
					return;
				}

				if (currentRole < targetRole) {
					first = mid + 1;
				} else {
					last = mid - 1;
				}
			}

			if (!found) {
				cout << "No staff found with role: " << targetRole << endl;
			}
			delete[] staffs; 
		}

		// Search Staff by Status (Binary Search)
		void SearchStaffByStatus(StaffHT& staffTable) {
			string targetStatus;
			
			int statusChoice;
			cout << "\n--- Search by Status ---\n";
			cout << "1. Active\n";
			cout << "2. Inactive\n";
			cout << "\nEnter your choice (1-2): ";
			cin >> statusChoice;

			switch(statusChoice) {
				case 1:
					targetStatus = "Active";
					break;
				case 2:
					targetStatus = "Inactive";
					break;
				default:
					cout << "Invalid choice. Returning to menu.\n";
					return;
			}
			
			// Count non-null staff
			count = 0;
			for (i = 0; i < staffTable.getTblSize(); i++) {
				if (staffTable.getTableElement(i) != NULL) {
					count++;
				}
			}
				
			if (count == 0) {
				cout << "No staff available to search." << endl;
				return;
			}
				
			// Create dynamic array
			Staff** staffs = new Staff*[count];
			index = 0;
			for (i = 0; i < staffTable.getTblSize(); i++) {
				if (staffTable.getTableElement(i) != NULL) {
					staffs[index++] = staffTable.getTableElement(i);
				}
			}  
			
			// Sort by status (selection sort)
			for (i = 0; i < count - 1; i++) {
				currentMin = i; 
				for (j = i + 1; j < count; j++) {
					if (staffs[j]->getStatus() < staffs[currentMin]->getStatus()) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					Staff* temp = staffs[i];
					staffs[i] = staffs[currentMin];
					staffs[currentMin] = temp;
				}
			}
			
			first = 0;
			last = count - 1;
			found = 0;
			
			while (first <= last) {
				mid = first + (last - first) / 2;
				string currentStatus = staffs[mid]->getStatus();

				if (currentStatus == targetStatus) {
					displayStaff(staffs[mid]);
					found = 1;

					// Check for duplicates on left side
					int firstDup = mid - 1;
					while (firstDup >= 0 && staffs[firstDup]->getStatus() == targetStatus) {
						displayStaff(staffs[firstDup]);
						found++;
						firstDup--;
					}

					// Check for duplicates on right side
					int lastDup = mid + 1;
					while (lastDup < count && staffs[lastDup]->getStatus() == targetStatus) {
						displayStaff(staffs[lastDup]);
						found++;
						lastDup++;
					}

					cout << "\nTotal matches found: " << found << endl;
					delete[] staffs;
					return;
				}

				if (currentStatus < targetStatus) {
					first = mid + 1;
				} else {
					last = mid - 1;
				}
			}

			if (!found) {
				cout << "No staff found with status: " << targetStatus << endl;
			}
			delete[] staffs; 
		}

		// Sort and Display Results by Score (High to Low) for a specific patient - Selection Sort
		void sortPatientResultsByScoreDescending(resultHT& resultTable, string patientEmail) {
			// Count non-null results for this patient
			count = 0;
			for (i = 0; i < resultTable.getTableSize(); i++) {
				if (resultTable.getEntry(i) != NULL && 
					resultTable.getEntry(i)->email == patientEmail) {
					count++;
				}
			}
			if (count == 0) {
				cout << "No test results found for your account." << endl;
				return;
			}

			// Create dynamic array of only this patient's results
			result** patientResults = new result*[count];
			index = 0;
			for (i = 0; i < resultTable.getTableSize(); i++) {
				if (resultTable.getEntry(i) != NULL && 
					resultTable.getEntry(i)->email == patientEmail) {
					patientResults[index++] = resultTable.getEntry(i);
				}
			}

			// Sort results by score (descending - high to low)
			for (i = 0; i < count - 1; i++) {
				currentMin = i;
				for (j = i + 1; j < count; j++) {
					if (patientResults[j]->score > patientResults[currentMin]->score) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					result* temp = patientResults[i];
					patientResults[i] = patientResults[currentMin];
					patientResults[currentMin] = temp;
				}
			}

			// Display the sorted results
			cout << "\nYour results sorted by score (high to low):" << endl;
			for (i = 0; i < count; i++) {
				cout << "\n--- Result " << i+1 << " ---" << endl;
				cout << "Score        : " << patientResults[i]->score << endl;
				cout << "Situation    : " << patientResults[i]->situation << endl;
			}

			// Clean up
			delete[] patientResults;
		}

		// Sort and Display Results by Score (Low to High) for a specific patient - Selection Sort
		void sortPatientResultsByScoreAscending(resultHT& resultTable, string patientEmail) {
			// Count non-null results for this patient
			count = 0;
			for (i = 0; i < resultTable.getTableSize(); i++) {
				if (resultTable.getEntry(i) != NULL && 
					resultTable.getEntry(i)->email == patientEmail) {
					count++;
				}
			}
			if (count == 0) {
				cout << "No test results found for your account." << endl;
				return;
			}

			// Create dynamic array of only this patient's results
			result** patientResults = new result*[count];
			index = 0;
			for (i = 0; i < resultTable.getTableSize(); i++) {
				if (resultTable.getEntry(i) != NULL && 
					resultTable.getEntry(i)->email == patientEmail) {
					patientResults[index++] = resultTable.getEntry(i);
				}
			}

			// Sort results by score (descending - low to high)
			for (i = 0; i < count - 1; i++) {
				currentMin = i;
				for (j = i + 1; j < count; j++) {
					if (patientResults[j]->score < patientResults[currentMin]->score) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					result* temp = patientResults[i];
					patientResults[i] = patientResults[currentMin];
					patientResults[currentMin] = temp;
				}
			}

			// Display the sorted results
			cout << "\nYour results sorted by score (high to low):" << endl;
			for (i = 0; i < count; i++) {
				cout << "\n--- Result " << i+1 << " ---" << endl;
				cout << "Score        : " << patientResults[i]->score << endl;
				cout << "Situation    : " << patientResults[i]->situation << endl;
			}

			// Clean up
			delete[] patientResults;
		}

		// Search appointments by Appointment ID (Binary Search)
		void SearchbyID(AppointHT& appointmentTable) {
			string targetID;
			
			cout << "\nEnter appointment ID to search: ";
			cin.ignore();
			getline(cin, targetID);
			
			// Count non-null appointments
			count = 0;
			for (i = 0; i < appointmentTable.getTableSize(); i++) {
				if (appointmentTable.getEntry(i) != NULL) {
				count++;
				}
			}
				
			if (count == 0) {
				cout << "No appointments available to search." << endl;
				return;
			}
				
			// Create dynamic array
			appoint** appointments = new appoint*[count];
			index = 0;
			for (i = 0; i < appointmentTable.getTableSize(); i++) {
				if (appointmentTable.getEntry(i) != NULL) {
				appointments[index++] = appointmentTable.getEntry(i);
				}
			}  
			
			first = 0;
			last = count - 1;
			found = 0;
			
			while (first <= last) {
				int mid = first + (last - first) / 2;
				string currentID = appointments[mid]->appointID;
			
				if (currentID == targetID) {
				// Display the found appointment
				displayAppointment(appointments[mid]);
				found++;
			
				// Check for duplicates on left side
				int firstDup = mid - 1;
				while (firstDup >= 0 && appointments[firstDup]->appointStat == targetID) {
				displayAppointment(appointments[firstDup]);
				found++;
				firstDup--;
				}
			
				// Check for duplicates on right side
				int lastDup = mid + 1;
				while (lastDup < count && appointments[lastDup]->appointID == targetID) {
				displayAppointment(appointments[lastDup]);
				found++;
				lastDup++;
				}
			
				cout << "\nTotal matches found: " << found << endl;
				delete[] appointments;
				return;
				}
			
				if (currentID < targetID) {
				first = mid + 1;
				} else {
				last = mid - 1;
				}
			}
			
			if (!found) {
				cout << "No appointments found for status: " << targetID << endl;
			}
			delete[] appointments; 
		}

		// Search appointments by Appointment ID for a specific patient (Binary Search)
		void PatientSearchByID(AppointHT& appointmentTable, string patientEmail) {
			string targetID;
			
			cout << "\nEnter appointment ID to search: ";
			cin.ignore();
			getline(cin, targetID);
			
			// Count non-null appointments that belong to the patient
			int count = 0;
			for (int i = 0; i < appointmentTable.getTableSize(); i++) {
				if (appointmentTable.getEntry(i) != NULL && 
				appointmentTable.getEntry(i)->appointPtEmail == patientEmail) {
				count++;
				}
			}
				
			if (count == 0) {
				cout << "You don't have any appointments." << endl;
				return;
			}
				
			// Create dynamic array of patient's appointments only
			appoint** patientAppointments = new appoint*[count];
			int index = 0;
			for (int i = 0; i < appointmentTable.getTableSize(); i++) {
				if (appointmentTable.getEntry(i) != NULL && 
				appointmentTable.getEntry(i)->appointPtEmail == patientEmail) {
				patientAppointments[index++] = appointmentTable.getEntry(i);
				}
			}
			
			// Binary search
			int first = 0;
			int last = count - 1;
			bool found = false;
			
			while (first <= last) {
				int mid = first + (last - first) / 2;
				string currentID = patientAppointments[mid]->appointID;

				if (currentID == targetID) {
				// Display the found appointment
				displayAppointment(patientAppointments[mid]);
				found = true;
				break;
				}

				if (currentID < targetID) {
				first = mid + 1;
				} else {
				last = mid - 1;
				}
			}

			if (!found) {
				cout << "No appointment found with ID: " << targetID << endl;
			}
			
			delete[] patientAppointments;
		}

		// Display tickets function
		void displayTickets(ticket** tickets, int count, const string& title) {
			cout << "\n" << title << endl;
			for (i = 0; i < count; i++) {
				cout << "\n--- Ticket " << i+1 << " ---" << endl;
				cout << "Name    : " << tickets[i]->name << endl;
				cout << "Phone   : " << tickets[i]->phone << endl;
				cout << "Email   : " << tickets[i]->email << endl;
				cout << "Date    : " << tickets[i]->date << endl;
				cout << "Content : " << tickets[i]->content << endl;
			}
		}

		// Sort Tickets by Date (Newest to Oldest - Descending)
		void sortTicketByDateDescending(TicketHT& ticketTable) {
			// Count non-null tickets
			count = 0;
			for (i = 0; i < ticketTable.getTableSize(); i++) {
				if (ticketTable.getEntry(i) != NULL) {
					count++;
				}
			}
			
			if (count == 0) {
				cout << "No tickets to display." << endl;
				return;
			}
			
			// Create dynamic array
			ticket** tickets = new ticket*[count];
			index = 0;
			for (i = 0; i < ticketTable.getTableSize(); i++) {
				if (ticketTable.getEntry(i) != NULL) {
					tickets[index++] = ticketTable.getEntry(i);
				}
			}
			
			// Selection sort by date (descending)
			for (i = 0; i < count - 1; i++) {
				currentMin = i;
				for (j = i + 1; j < count; j++) {
					if (tickets[j]->date > tickets[currentMin]->date) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					ticket* temp = tickets[i];
					tickets[i] = tickets[currentMin];
					tickets[currentMin] = temp;
				}
			}
			
			// Display sorted tickets
			displayTickets(tickets, count, "Tickets sorted by date (Newest to Oldest):");
			
			delete[] tickets;
		}

		// Sort Tickets by Date (Oldest to Newest - Ascending)
		void sortTicketByDateAscending(TicketHT& ticketTable) {
			// Count non-null tickets
			count = 0;
			for (i = 0; i < ticketTable.getTableSize(); i++) {
				if (ticketTable.getEntry(i) != NULL) {
					count++;
				}
			}
			
			if (count == 0) {
				cout << "No tickets to display." << endl;
				return;
			}
			
			// Create dynamic array
			ticket** tickets = new ticket*[count];
			index = 0;
			for (i = 0; i < ticketTable.getTableSize(); i++) {
				if (ticketTable.getEntry(i) != NULL) {
					tickets[index++] = ticketTable.getEntry(i);
				}
			}
			
			// Selection sort by date (Ascending)
			for (i = 0; i < count - 1; i++) {
				currentMin = i;
				for (j = i + 1; j < count; j++) {
					if (tickets[j]->date < tickets[currentMin]->date) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					ticket* temp = tickets[i];
					tickets[i] = tickets[currentMin];
					tickets[currentMin] = temp;
				}
			}
			
			// Display sorted tickets
			displayTickets(tickets, count, "Tickets sorted by date (Newest to Oldest):");
			
			delete[] tickets;
		}
		
		// Sort Tickets by Date (Oldest to Newest - Ascending) for specific patient
		void sortPatientTicketByDateAscending(TicketHT& ticketTable, string patientEmail) {
			// Count non-null tickets that belong to the patient
			count = 0;
			for (i = 0; i < ticketTable.getTableSize(); i++) {
				if (ticketTable.getEntry(i) != NULL && 
					ticketTable.getEntry(i)->email == patientEmail) {
					count++;
				}
			}
			
			if (count == 0) {
				cout << "No tickets found for this patient." << endl;
				return;
			}
			
			// Create dynamic array of patient's tickets only
			ticket** patientTickets = new ticket*[count];
			index = 0;
			for (i = 0; i < ticketTable.getTableSize(); i++) {
				if (ticketTable.getEntry(i) != NULL && 
					ticketTable.getEntry(i)->email == patientEmail) {
					patientTickets[index++] = ticketTable.getEntry(i);
				}
			}
			
			// Selection sort by date (ascending)
			for (i = 0; i < count - 1; i++) {
				currentMin = i;
				for (j = i + 1; j < count; j++) {
					if (patientTickets[j]->date < patientTickets[currentMin]->date) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					ticket* temp = patientTickets[i];
					patientTickets[i] = patientTickets[currentMin];
					patientTickets[currentMin] = temp;
				}
			}
			
			// Display sorted tickets
			displayTickets(patientTickets, count, "Your tickets sorted by date (Oldest to Newest):");
			
			delete[] patientTickets;
		}

		// Sort Tickets by Date (Newest to Oldest - Descending) for specific patient
		void sortPatientTicketByDateDescending(TicketHT& ticketTable, string patientEmail) {
			// Count non-null tickets that belong to the patient
			count = 0;
			for (i = 0; i < ticketTable.getTableSize(); i++) {
				if (ticketTable.getEntry(i) != NULL && 
					ticketTable.getEntry(i)->email == patientEmail) {
					count++;
				}
			}
			
			if (count == 0) {
				cout << "No tickets found for this patient." << endl;
				return;
			}
			
			// Create dynamic array of patient's tickets only
			ticket** patientTickets = new ticket*[count];
			index = 0;
			for (i = 0; i < ticketTable.getTableSize(); i++) {
				if (ticketTable.getEntry(i) != NULL && 
					ticketTable.getEntry(i)->email == patientEmail) {
					patientTickets[index++] = ticketTable.getEntry(i);
				}
			}
			
			// Selection sort by date (descending)
			for (i = 0; i < count - 1; i++) {
				currentMin = i;
				for (j = i + 1; j < count; j++) {
					if (patientTickets[j]->date > patientTickets[currentMin]->date) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					ticket* temp = patientTickets[i];
					patientTickets[i] = patientTickets[currentMin];
					patientTickets[currentMin] = temp;
				}
			}
			
			// Display sorted tickets
			displayTickets(patientTickets, count, "Your tickets sorted by date (Newest to Oldest):");
			
			delete[] patientTickets;
		}
		
		// Search Ticket by Name (Binary Search)
		void searchTicketByName(TicketHT& ticketTable) {
			string targetName;
			cout << "\nEnter name to search: ";
			cin.ignore();
			getline(cin, targetName);
			
			// Count non-null tickets
			count = 0;
			for (i = 0; i < ticketTable.getTableSize(); i++) {
				if (ticketTable.getEntry(i) != NULL) {
					count++;
				}
			}
				
			if (count == 0) {
				cout << "No tickets available to search." << endl;
				return;
			}
				
			// Create dynamic array
			ticket** tickets = new ticket*[count];
			index = 0;
			for (i = 0; i < ticketTable.getTableSize(); i++) {
				if (ticketTable.getEntry(i) != NULL) {
					tickets[index++] = ticketTable.getEntry(i);
				}
			}  
			
			// Sort by name (selection sort)
			for (i = 0; i < count - 1; i++) {
				currentMin = i; 
				for (j = i + 1; j < count; j++) {
					if (tickets[j]->name < tickets[currentMin]->name) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					ticket* temp = tickets[i];
					tickets[i] = tickets[currentMin];
					tickets[currentMin] = temp;
				}
			}
			
			// Binary search
			first = 0;
			last = count - 1;
			found = 0;
			
			while (first <= last) {
				mid = first + (last - first) / 2;
				string currentName = tickets[mid]->name;

				if (currentName == targetName) {
					displayTicket(tickets[mid]);
					found = 1;

					// Check for duplicates on left side
					int left = mid - 1;
					while (left >= 0 && tickets[left]->name == targetName) {
						displayTicket(tickets[left]);
						found++;
						left--;
					}

					// Check for duplicates on right side
					int right = mid + 1;
					while (right < count && tickets[right]->name == targetName) {
						displayTicket(tickets[right]);
						found++;
						right++;
					}

					cout << "\nTotal matches found: " << found << endl;
					delete[] tickets;
					return;
				}

				if (currentName < targetName) {
					first = mid + 1;
				} else {
					last = mid - 1;
				}
			}

			if (!found) {
				cout << "No ticket found with name: " << targetName << endl;
			}
			delete[] tickets; 
		}

		// Search Ticket by Phone (Binary Search)
		void searchTicketByPhone(TicketHT& ticketTable) {
			int targetPhone;
			cout << "\nEnter phone number to search: ";
			bool validPhone = false;

			while (!validPhone) {
				if (cin >> targetPhone) {
					if (isValidPhone(targetPhone)) {
						validPhone = true;
					} else {
						cout << "Invalid phone number. Please enter 9-10 digits: +60";
					}
				}
			}
			cin.ignore();
			
			// Count non-null tickets
			count = 0;
			for (i = 0; i < ticketTable.getTableSize(); i++) {
				if (ticketTable.getEntry(i) != NULL) {
					count++;
				}
			}
				
			if (count == 0) {
				cout << "No tickets available to search." << endl;
				return;
			}
				
			// Create dynamic array
			ticket** tickets = new ticket*[count];
			index = 0;
			for (i = 0; i < ticketTable.getTableSize(); i++) {
				if (ticketTable.getEntry(i) != NULL) {
					tickets[index++] = ticketTable.getEntry(i);
				}
			}  
			
			// Sort by phone (selection sort)
			for (i = 0; i < count - 1; i++) {
				currentMin = i; 
				for (j = i + 1; j < count; j++) {
					if (tickets[j]->phone < tickets[currentMin]->phone) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					ticket* temp = tickets[i];
					tickets[i] = tickets[currentMin];
					tickets[currentMin] = temp;
				}
			}
			
			// Binary search
			first = 0;
			last = count - 1;
			found = 0;
			
			while (first <= last) {
				mid = first + (last - first) / 2;
				int currentPhone = tickets[mid]->phone;

				if (currentPhone == targetPhone) {
					displayTicket(tickets[mid]);
					found = 1;

					// Check for duplicates on left side
					int left = mid - 1;
					while (left >= 0 && tickets[left]->phone == targetPhone) {
						displayTicket(tickets[left]);
						found++;
						left--;
					}

					// Check for duplicates on right side
					int right = mid + 1;
					while (right < count && tickets[right]->phone == targetPhone) {
						displayTicket(tickets[right]);
						found++;
						right++;
					}

					cout << "\nTotal matches found: " << found << endl;
					delete[] tickets;
					return;
				}

				if (currentPhone < targetPhone) {
					first = mid + 1;
				} else {
					last = mid - 1;
				}
			}

			if (!found) {
				cout << "No ticket found with phone: " << targetPhone << endl;
			}
			delete[] tickets;
		}

		// Search Ticket by Email (Binary Search)
		void searchTicketByEmail(TicketHT& ticketTable) {
			string targetEmail;
			cout << "\nEnter email to search: ";
			cin.ignore();
			getline(cin, targetEmail);
			
			// Count non-null tickets
			count = 0;
			for (i = 0; i < ticketTable.getTableSize(); i++) {
				if (ticketTable.getEntry(i) != NULL) {
					count++;
				}
			}
				
			if (count == 0) {
				cout << "No tickets available to search." << endl;
				return;
			}
				
			// Create dynamic array
			ticket** tickets = new ticket*[count];
			index = 0;
			for (i = 0; i < ticketTable.getTableSize(); i++) {
				if (ticketTable.getEntry(i) != NULL) {
					tickets[index++] = ticketTable.getEntry(i);
				}
			}  
			
			// Sort by email (selection sort)
			for (i = 0; i < count - 1; i++) {
				currentMin = i; 
				for (j = i + 1; j < count; j++) {
					if (tickets[j]->email < tickets[currentMin]->email) {
						currentMin = j;
					}
				}
				if (currentMin != i) {
					ticket* temp = tickets[i];
					tickets[i] = tickets[currentMin];
					tickets[currentMin] = temp;
				}
			}
			
			// Binary search
			first = 0;
			last = count - 1;
			found = 0;
			
			while (first <= last) {
				mid = first + (last - first) / 2;
				string currentEmail = tickets[mid]->email;

				if (currentEmail == targetEmail) {
					displayTicket(tickets[mid]);
					found = 1;

					// Check for duplicates on left side
					int left = mid - 1;
					while (left >= 0 && tickets[left]->email == targetEmail) {
						displayTicket(tickets[left]);
						found++;
						left--;
					}

					// Check for duplicates on right side
					int right = mid + 1;
					while (right < count && tickets[right]->email == targetEmail) {
						displayTicket(tickets[right]);
						found++;
						right++;
					}

					cout << "\nTotal matches found: " << found << endl;
					delete[] tickets;
					return;
				}

				if (currentEmail < targetEmail) {
					first = mid + 1;
				} else {
					last = mid - 1;
				}
			}

			if (!found) {
				cout << "No ticket found with email: " << targetEmail << endl;
			}
			delete[] tickets;
		}

		// Display ticket details
		void displayTicket(ticket* t) {
			cout << "\n--- Ticket Found ---" << endl;
			cout << "Name: " << t->name << endl;
			cout << "Phone: " << t->phone << endl;
			cout << "Email: " << t->email << endl;
			cout << "Date: " << t->date << endl;
			cout << "Content: " << t->content << endl;
		}

};

// Display search appointment details
void displaysortedAppointment(appoint* apt) {
        if (!apt) return;
        cout << "\n--- Appointment Found ---\n";
        cout << "ID: " << apt->appointID << "\n";
        cout << "Service: " << apt->appointSvc << "\n";
		cout << "Counselor: " << apt->appointCouns << "\n";
		cout << "Mode: " << apt->appointMode << "\n";
        cout << "Date: " << apt->appointDate << "\n";
        cout << "Time: " << apt->appointTime << "\n";
		cout << "Patient: " << apt->appointPtName << "\n";
		cout << "Phone: " << apt->appointPtPhone << "\n";
		cout << "Email: " << apt->appointPtEmail << "\n";
		// cout << "Gross Amount: " << apt->appointGrossAmt << "\n";
		cout << "Net Amount: " << apt->appointNetAmt << "\n";
		cout << "Payment Status: " << apt->appointPayStat << "\n";
        cout << "Status: " << apt->appointStat << "\n";
}
	
// Sort and Display appointments by Date to Ascending (Selection Sort)
void sortByDateAscending(AppointHT& appointmentTable) {
        // Count non-null appointments
        int count = 0;
        int i, j;
        int index;
        for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
            if (appointmentTable.tbl[i] != NULL) {
                count++;
            }
        }
        if (count == 0) {
            cout << "No appointments to display." << endl;
            return;
        }

        // Create dynamic array
        appoint** apps = new appoint*[count];
        index = 0;
        for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
            if (appointmentTable.tbl[i] != NULL) {
                apps[index++] = appointmentTable.tbl[i];
            }
        }
		
		// Sort Appointment by Dates (Ascending)
        for (i = 0; i < count - 1; i++) {
            int currentDate = i;
            for (int j = i + 1; j < count; j++) {
                if (apps[j]->appointDate < apps[currentDate]->appointDate) {
                    currentDate = j;
                }
            }
            if (currentDate != i) {
                appoint* temp = apps[i];
                apps[i] = apps[currentDate];
                apps[currentDate] = temp;
            }
        }

        // Display the sorted appointments
        cout << "\nAppointments sorted by date (ascending):" << endl;
        for (i = 0; i < count; i++) {
            displaysortedAppointment(apps[i]);
        }

        // Clean up
        delete[] apps;
}
    
// Sort and Display appointments by Date to Decending (Selection Sort)
void sortByDateDescending(AppointHT& appointmentTable) {
        // Count non-null appointments
        int count = 0;
        int i, j;
        int index;
        for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
            if (appointmentTable.tbl[i] != NULL) {
                count++;
            }
        }
        if (count == 0) {
            cout << "No appointments to display." << endl;
            return;
        }

        // Create dynamic array
        appoint** apps = new appoint*[count];
        index = 0;
        for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
            if (appointmentTable.tbl[i] != NULL) {
                apps[index++] = appointmentTable.tbl[i];
            }
        }
	
		for (i = 0; i < count - 1; i++) {
            int currentDate = i;
            for (j = i + 1; j < count; j++) {
                if (apps[j]->appointDate > apps[currentDate]->appointDate) {
                    currentDate = j;
                }
            }
            if (currentDate != i) {
                appoint* temp = apps[i];
                apps[i] = apps[currentDate];
                apps[currentDate] = temp;
            }
        }

        // Display the sorted appointments
        cout << "\nAppointments sorted by date (ascending):" << endl;
        for (i = 0; i < count; i++) {
            displaysortedAppointment(apps[i]);
        }

        // Clean up
        delete[] apps;
}
	
//Sort and Display appoinments by Time to Ascending (Selection Sort)
void sortByTimeAscending(AppointHT& appointmentTable) {
        // Count non-null appointments
        int count = 0;
        int i, j;
        int index;
		for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
            if (appointmentTable.tbl[i] != NULL) {
                count++;
            }
        }
        if (count == 0) {
            cout << "No appointments to display." << endl;
            return;
        }

        // Create dynamic array
        appoint** apps = new appoint*[count];
        index = 0;
        for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
            if (appointmentTable.tbl[i] != NULL) {
                apps[index++] = appointmentTable.tbl[i];
            }
        }
		
		// Sort Appointment by Time (Ascending)
        for (i = 0; i < count - 1; i++) {
            int currentTime = i;
            for (j = i + 1; j < count; j++) {
                if (apps[j]->appointDate < apps[currentTime]->appointDate ||
                    // If dates are equal, compare times
                    (apps[j]->appointDate == apps[currentTime]->appointDate &&
                     apps[j]->appointTime < apps[currentTime]->appointTime)) {
                    currentTime = j;
                }
            }
            if (currentTime != i) {
                appoint* temp = apps[i];
                apps[i] = apps[currentTime];
                apps[currentTime] = temp;
            }
        }

        // Display the sorted appointments
        cout << "\nAppointments sorted by date (ascending):" << endl;
        for (i = 0; i < count; i++) {
            displaysortedAppointment(apps[i]);
        }

        // Clean up
        delete[] apps;
}
	
//Sort and Display appoinments by Time to Descending (Selection Sort)
void sortByTimeDescending(AppointHT& appointmentTable) {
        // Count non-null appointments
        int count = 0;
        int i, j;
        int index;
		for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
            if (appointmentTable.tbl[i] != NULL) {
                count++;
            }
        }
        if (count == 0) {
            cout << "No appointments to display." << endl;
            return;
        }

        // Create dynamic array
        appoint** apps = new appoint*[count];
        index = 0;
        for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
            if (appointmentTable.tbl[i] != NULL) {
                apps[index++] = appointmentTable.tbl[i];
            }
        }
		
		// Sort Appointment by Time (Descending)
        for (i = 0; i < count - 1; i++) {
            int currentTime = i;
            for (j = i + 1; j < count; j++) {
                if (apps[j]->appointDate > apps[currentTime]->appointDate ||
                    // If dates are equal, compare times
                    (apps[j]->appointDate == apps[currentTime]->appointDate &&
                     apps[j]->appointTime > apps[currentTime]->appointTime)) {
                    currentTime = j;
                }
            }
            if (currentTime != i) {
                appoint* temp = apps[i];
                apps[i] = apps[currentTime];
                apps[currentTime] = temp;
            }
        }

        // Display the sorted appointments
        cout << "\nAppointments sorted by date (ascending):" << endl;
        for (i = 0; i < count; i++) {
            displaysortedAppointment(apps[i]);
        }

        // Clean up
        delete[] apps;
}
	
// Sort and Display appointmets by Net Amount to Ascending (Selection Sort)
void sortByNetAmountAscending(AppointHT& appointmentTable){
	// Count non-null appointments
        int count = 0;
        int i, j;
        int index;
        for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
            if (appointmentTable.tbl[i] != NULL) {
                count++;
            }
        }
        if (count == 0) {
            cout << "No appointments to display." << endl;
            return;
        }

        // Create dynamic array
        appoint** apps = new appoint*[count];
        index = 0;
        for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
            if (appointmentTable.tbl[i] != NULL) {
                apps[index++] = appointmentTable.tbl[i];
            }
        }
		
		// Sort Appointment by  (Ascending)
        for (i = 0; i < count - 1; i++) {
            int currentNA = i;
            for (j = i + 1; j < count; j++) {
                if (apps[j]->appointNetAmt < apps[currentNA]->appointNetAmt) {
                    currentNA = j;
                }
            }
            if (currentNA != i) {
                appoint* temp = apps[i];
                apps[i] = apps[currentNA];
                apps[currentNA] = temp;
            }
        }

        // Display the sorted appointments
        cout << "\nAppointments sorted by date (ascending):" << endl;
        for (i = 0; i < count; i++) {
            displaysortedAppointment(apps[i]);
        }

        // Clean up
        delete[] apps;
}
	
// Sort and Display appointmets by Net Amount to Descending (Selection Sort)
void sortByNetAmountDescending(AppointHT& appointmentTable){
	// Count non-null appointments
        int count = 0;
        int i, j;
        int index;
        for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
            if (appointmentTable.tbl[i] != NULL) {
                count++;
            }
        }
        if (count == 0) {
            cout << "No appointments to display." << endl;
            return;
        }

        // Create dynamic array
        appoint** apps = new appoint*[count];
        index = 0;
        for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
            if (appointmentTable.tbl[i] != NULL) {
                apps[index++] = appointmentTable.tbl[i];
            }
        }
		
		// Sort Appointment by  (Descending)
        for (i = 0; i < count - 1; i++) {
            int currentNA = i;
            for (j = i + 1; j < count; j++) {
                if (apps[j]->appointNetAmt > apps[currentNA]->appointNetAmt) {
                    currentNA = j;
                }
            }
            if (currentNA != i) {
                appoint* temp = apps[i];
                apps[i] = apps[currentNA];
                apps[currentNA] = temp;
            }
        }

        // Display the sorted appointments
        cout << "\nAppointments sorted by Net Amount (descending):" << endl;
        for (i = 0; i < count; i++) {
            displaysortedAppointment(apps[i]);
        }

        // Clean up
        delete[] apps;
}

// Patient Sort and Display appointments by Date to Ascending (Selection Sort)
void PatientsortByDateAscending(AppointHT& appointmentTable, string patientEmail) {
	    int count;
        int i, j;
        int index;
		// Count patient's appointments
	    count = 0;
	    for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
	        if (appointmentTable.tbl[i] != NULL && 
	            appointmentTable.tbl[i]->appointPtEmail == patientEmail) {
	            count++;
	        }
	    }
	    
	    if (count == 0) {
	        cout << "You don't have any appointments." << endl;
	        return;
	    }
	
	    // Create dynamic array of patient's appointments only
	    appoint** apps = new appoint*[count];
	    index = 0;
	    for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
	        if (appointmentTable.tbl[i] != NULL && 
	            appointmentTable.tbl[i]->appointPtEmail == patientEmail) {
	            apps[index++] = appointmentTable.tbl[i];
	        }
	    }
	    
	    // Sort Appointment by Dates (Ascending)
	    for (i = 0; i < count - 1; i++) {
	        int currentDate = i;
	        for (j = i + 1; j < count; j++) {
	            if (apps[j]->appointDate < apps[currentDate]->appointDate) {
	                currentDate = j;
	            }
	        }
	        if (currentDate != i) {
	            appoint* temp = apps[i];
	            apps[i] = apps[currentDate];
	            apps[currentDate] = temp;
	        }
	    }
	
	    // Display the sorted appointments
	    cout << "\nYour appointments sorted by date (oldest to newest):" << endl;
	    for (i = 0; i < count; i++) {
	        displaysortedAppointment(apps[i]);
	    }
	
	    // Clean up
	    delete[] apps;
}
	
	// Patient Sort and Display appointments by Date to Descending (Selection Sort)
void PatientsortByDateDescending(AppointHT& appointmentTable, string patientEmail) {
	    int count;
        int i, j;
        int index;
		// Count patient's appointments
	    count = 0;
	    for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
	        if (appointmentTable.tbl[i] != NULL && 
	            appointmentTable.tbl[i]->appointPtEmail == patientEmail) {
	            count++;
	        }
	    }
	    
	    if (count == 0) {
	        cout << "You don't have any appointments." << endl;
	        return;
	    }
	
	    // Create dynamic array of patient's appointments only
	    appoint** apps = new appoint*[count];
	    index = 0;
	    for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
	        if (appointmentTable.tbl[i] != NULL && 
	            appointmentTable.tbl[i]->appointPtEmail == patientEmail) {
	            apps[index++] = appointmentTable.tbl[i];
	        }
	    }
	
	    // Sort Appointment by Dates (Descending)
	    for (i = 0; i < count - 1; i++) {
	        int currentDate = i;
	        for (j = i + 1; j < count; j++) {
	            if (apps[j]->appointDate > apps[currentDate]->appointDate) {
	                currentDate = j;
	            }
	        }
	        if (currentDate != i) {
	            appoint* temp = apps[i];
	            apps[i] = apps[currentDate];
	            apps[currentDate] = temp;
	        }
	    }
	
	    // Display the sorted appointments
	    cout << "\nYour appointments sorted by date (newest to oldest):" << endl;
	    for (i = 0; i < count; i++) {
	        displaysortedAppointment(apps[i]);
	    }
	
	    // Clean up
	    delete[] apps;
}

// Patient Sort and Display appointments by Time to Ascending (Selection Sort)
void PatientsortByTimeAscending(AppointHT& appointmentTable, string patientEmail) {
	    int count;
        int i, j;
        int index;
		// Count patient's appointments
	    count = 0;
	    for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
	        if (appointmentTable.tbl[i] != NULL && 
	            appointmentTable.tbl[i]->appointPtEmail == patientEmail) {
	            count++;
	        }
	    }
	    
	    if (count == 0) {
	        cout << "You don't have any appointments." << endl;
	        return;
	    }
	
	    // Create dynamic array of patient's appointments only
	    appoint** apps = new appoint*[count];
	    index = 0;
	    for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
	        if (appointmentTable.tbl[i] != NULL && 
	            appointmentTable.tbl[i]->appointPtEmail == patientEmail) {
	            apps[index++] = appointmentTable.tbl[i];
	        }
	    }
	    
	    // Sort Appointment by Time (Ascending)
	    for (i = 0; i < count - 1; i++) {
	        int currentTime = i;
	        for (j = i + 1; j < count; j++) {
	            if (apps[j]->appointDate < apps[currentTime]->appointDate ||
	                // If dates are equal, compare times
	                (apps[j]->appointDate == apps[currentTime]->appointDate &&
	                 apps[j]->appointTime < apps[currentTime]->appointTime)) {
	                currentTime = j;
	            }
	        }
	        if (currentTime != i) {
	            appoint* temp = apps[i];
	            apps[i] = apps[currentTime];
	            apps[currentTime] = temp;
	        }
	    }
	
	    // Display the sorted appointments
	    cout << "\nYour appointments sorted by time (earliest first):" << endl;
	    for (i = 0; i < count; i++) {
	        displaysortedAppointment(apps[i]);
	    }
	
	    // Clean up
	    delete[] apps;
}
	
// Patient Sort and Display appointments by Time to Descending (Selection Sort)
void PatientsortByTimeDescending(AppointHT& appointmentTable, string patientEmail) {
	    int count;
        int i, j;
        int index;
		// Count patient's appointments
	    count = 0;
	    for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
	        if (appointmentTable.tbl[i] != NULL && 
	            appointmentTable.tbl[i]->appointPtEmail == patientEmail) {
	            count++;
	        }
	    }
	    
	    if (count == 0) {
	        cout << "You don't have any appointments." << endl;
	        return;
	    }
	
	    // Create dynamic array of patient's appointments only
	    appoint** apps = new appoint*[count];
	    index = 0;
	    for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
	        if (appointmentTable.tbl[i] != NULL && 
	            appointmentTable.tbl[i]->appointPtEmail == patientEmail) {
	            apps[index++] = appointmentTable.tbl[i];
	        }
	    }
	    
	    // Sort Appointment by Time (Descending)
	    for (i = 0; i < count - 1; i++) {
	        int currentTime = i;
	        for (j = i + 1; j < count; j++) {
	            if (apps[j]->appointDate > apps[currentTime]->appointDate ||
	                // If dates are equal, compare times
	                (apps[j]->appointDate == apps[currentTime]->appointDate &&
	                 apps[j]->appointTime > apps[currentTime]->appointTime)) {
	                currentTime = j;
	            }
	        }
	        if (currentTime != i) {
	            appoint* temp = apps[i];
	            apps[i] = apps[currentTime];
	            apps[currentTime] = temp;
	        }
	    }
	
	    // Display the sorted appointments
	    cout << "\nYour appointments sorted by time (latest first):" << endl;
	    for (i = 0; i < count; i++) {
	        displaysortedAppointment(apps[i]);
	    }
	
	    // Clean up
	    delete[] apps;
}
	
// Patient Sort and Display appointments by Net Amount to Ascending (Selection Sort)
void PatientsortByNetAmountAscending(AppointHT& appointmentTable, string patientEmail) {
	    int count;
        int i, j;
        int index;
		// Count patient's appointments
	    count = 0;
	    for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
	        if (appointmentTable.tbl[i] != NULL && 
	            appointmentTable.tbl[i]->appointPtEmail == patientEmail) {
	            count++;
	        }
	    }
	    
	    if (count == 0) {
	        cout << "You don't have any appointments." << endl;
	        return;
	    }
	
	    // Create dynamic array of patient's appointments only
	    appoint** apps = new appoint*[count];
	    index = 0;
	    for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
	        if (appointmentTable.tbl[i] != NULL && 
	            appointmentTable.tbl[i]->appointPtEmail == patientEmail) {
	            apps[index++] = appointmentTable.tbl[i];
	        }
	    }
	    
	    // Sort Appointment by Net Amount (Ascending)
	    for (i = 0; i < count - 1; i++) {
	        int currentNA = i;
	        for (j = i + 1; j < count; j++) {
	            if (apps[j]->appointNetAmt < apps[currentNA]->appointNetAmt) {
	                currentNA = j;
	            }
	        }
	        if (currentNA != i) {
	            appoint* temp = apps[i];
	            apps[i] = apps[currentNA];
	            apps[currentNA] = temp;
	        }
	    }
	
	    // Display the sorted appointments
	    cout << "\nYour appointments sorted by cost (lowest to highest):" << endl;
	    for (i = 0; i < count; i++) {
	        displaysortedAppointment(apps[i]);
	    }
	
	    // Clean up
	    delete[] apps;
}
	
// Patient Sort and Display appointments by Net Amount to Descending (Selection Sort)
void PatientsortByNetAmountDescending(AppointHT& appointmentTable, string patientEmail) {
	    int count;
        int i, j;
        int index;
		// Count patient's appointments
	    count = 0;
	    for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
	        if (appointmentTable.tbl[i] != NULL && 
	            appointmentTable.tbl[i]->appointPtEmail == patientEmail) {
	            count++;
	        }
	    }
	    
	    if (count == 0) {
	        cout << "You don't have any appointments." << endl;
	        return;
	    }
	
	    // Create dynamic array of patient's appointments only
	    appoint** apps = new appoint*[count];
	    index = 0;
	    for (i = 0; i < appointmentTable.TBL_SIZE; i++) {
	        if (appointmentTable.tbl[i] != NULL && 
	            appointmentTable.tbl[i]->appointPtEmail == patientEmail) {
	            apps[index++] = appointmentTable.tbl[i];
	        }
	    }
	    
	    // Sort Appointment by Net Amount (Descending)
	    for (i = 0; i < count - 1; i++) {
	        int currentNA = i;
	        for (j = i + 1; j < count; j++) {
	            if (apps[j]->appointNetAmt > apps[currentNA]->appointNetAmt) {
	                currentNA = j;
	            }
	        }
	        if (currentNA != i) {
	            appoint* temp = apps[i];
	            apps[i] = apps[currentNA];
	            apps[currentNA] = temp;
	        }
	    }
	
	    // Display the sorted appointments
	    cout << "\nYour appointments sorted by cost (highest to lowest):" << endl;
	    for (i = 0; i < count; i++) {
	        displaysortedAppointment(apps[i]);
	    }
	
	    // Clean up
	    delete[] apps;
}

int main() {
    AppointHT appointmentTable;
    Appoint appointment;
    SvcHT serviceTable;
    Svc serviceManager;
    CatHT categoryTable;
    Cat categoryManager;
    PtHT patientTable;
    PtManager patientManager;
    StaffHT staffTable;
    StaffManager staffManager;
    testHT testTable;
    resultHT resultTable;
    TxHT treatmentTable;
    Tx treatment;
    UserManager userManager;
    SearchSort ss;
	Coupon couponManager;
	CouponHT couponTable;
	TicketHT ticketTable;
    TicketManager ticketManager;

    // Load data from files
    appointmentTable.loadFromFile();
    serviceTable.loadFromFile();
    categoryTable.loadFromFile();
    patientTable.loadFromFile();
    staffTable.loadFromFile();
    testTable.loadQuestionsFromFile();
    resultTable.loadResultsFromFile();
    treatmentTable.loadFromFile();
	couponTable.loadFromFile();
	ticketTable.loadFromFile();
    
    test testManager(testTable, resultTable);

    // Main program loop
    bool exitProgram = false;
    
    while (!exitProgram) {
        // User authentication variables
        string currentEmail = "";
        string currentFirstName = "";
        string currentLastName = "";
        int currentPhone = 0;
        int currentRole = -1;  // -1: not logged in, 0: patient, 1: counsellor, 2: staff, 3: admin
        string currentStatus = "";
        bool isLoggedIn = false;

        // Login loop
        bool loginSuccessful = false;

        while (!loginSuccessful) {
            // Prompt for email at program start
            string email;
            cout << "Welcome to Counselling System\n\n";
            cout << "Please enter your email: ";
            cin >> email;

			if (!isValidEmail(email)) {
				cout << "Invalid email format. Please try again.\n" << endl;
				continue;
			}

			if (!verifyCaptcha()) {
				continue; 
			}

            // Check if user exists
            bool userFound = false;
            Pt* foundPatient = NULL;
            Staff* foundStaff = NULL;

            // Use UserManager to search for the user
            userManager.searchUserByEmail(email, patientTable, staffTable, foundPatient, foundStaff, userFound);

            if (!userFound) {
                // User doesn't exist, ask if they want to create a new patient account
                char createAccount;
                cout << "Email not found. Would you like to create a new patient account? (Y/N): ";
                cin >> createAccount;
                
                if (toupper(createAccount) == 'Y') {
                    // Use patientManager to add new patient with pre-provided email
                    patientManager.addPt(patientTable, email);
                    
                    // Search for the newly created patient to get their info
                    Pt* newPatient = NULL;
                    Staff* dummy = NULL;
                    bool found = false;
                    userManager.searchUserByEmail(email, patientTable, staffTable, newPatient, dummy, found);
                    
                    if (found && newPatient != NULL) {
                        // Set current user information
                        currentEmail = newPatient->getEmail();
                        currentFirstName = newPatient->getFName();
                        currentLastName = newPatient->getLName();
                        currentPhone = newPatient->getPhone();
                        currentRole = 0; // Patient role
                        currentStatus = "Active"; // Default status is Active
                        isLoggedIn = true;
                        loginSuccessful = true;
                        
                        cout << "Account created successfully! You are now logged in as a patient.\n";
                    } else {
                        char retry;
                        cout << "Error creating account. Would you like to try again? (Y/N): ";
                        cin >> retry;
                        
                        if (toupper(retry) != 'Y') {
                            cout << "Exiting program.\n";
                            return 0;
                        }
                        // If Y, the loop will continue automatically
                    }
                } else {
                    cout << "Account creation cancelled. Exiting program.\n";
                    return 0;
                }
            } else {
                // User exists
                if (foundPatient != NULL) {
                    cout << "Welcome back! Are you " << foundPatient->getFName() << "? (Y/N): ";
                    char confirm;
                    cin >> confirm;
                    
                    if (tolower(confirm) == 'y') {
                        cout << "Would you like to login? (Y/N): ";
                        char loginChoice;
                        cin >> loginChoice;
                        
                        if (tolower(loginChoice) == 'y') {
                            cout << "Please enter your password: ";
                            string inputPassword;
                            maskPwd(inputPassword);
                            
                            if (foundPatient->getPassword() == inputPassword) {
                                // Set current user info
                                currentEmail = foundPatient->getEmail();
                                currentFirstName = foundPatient->getFName();
                                currentLastName = foundPatient->getLName();
                                currentPhone = foundPatient->getPhone();
                                currentRole = 0; // Patient role
                                currentStatus = foundPatient->getStatus();
                                isLoggedIn = true;
                                loginSuccessful = true;
                            } else {
                                cout << "Incorrect password. Please try again.\n";
                            }
                        } else {
                            cout << "Login cancelled. Please try again.\n";
                        }
                    } else {
                        cout << "Please enter the correct email.\n\n";
                    }
                } else if (foundStaff != NULL) {
                    cout << "Welcome back! Are you " << foundStaff->getFName() << "? (Y/N): ";
                    char confirm;
                    cin >> confirm;
                    
                    if (tolower(confirm) == 'y') {
                        cout << "Would you like to login? (Y/N): ";
                        char loginChoice;
                        cin >> loginChoice;
                        
                        if (tolower(loginChoice) == 'y') {
                            cout << "Please enter your password: ";
                            string inputPassword;
                            maskPwd(inputPassword);
                            
                            if (foundStaff->getPassword() == inputPassword) {
                                // Set current user info
                                currentEmail = foundStaff->getEmail();
                                currentFirstName = foundStaff->getFName();
                                currentLastName = foundStaff->getLName();
                                currentPhone = foundStaff->getPhone();
                                
                                // Determine role based on staff role
                                string role = foundStaff->getRole();
                                if (role == "Counsellor") {
                                    currentRole = 1; // Counsellor
                                } else if (role == "Staff") {
                                    currentRole = 2; // Staff
                                } else if (role == "Admin") {
                                    currentRole = 3; // Admin
                                }
                                
                                currentStatus = foundStaff->getStatus();
                                isLoggedIn = true;
                                loginSuccessful = true;
                            } else {
                                cout << "Incorrect password. Please try again.\n";
                            }
                        } else {
                            cout << "Login cancelled. Please try again.\n";
                        }
                    } else {
                        cout << "Please enter the correct email.\n";
                    }
                }
            }
        }

		// After successful login, check user status
		if (loginSuccessful) {
			// Verify user status
			if (currentStatus == "Inactive") {
				cout << "Your account is currently inactive. Login denied. Please contact us for assistance.\n\n";
				loginSuccessful = false;
				continue;  // Return to login loop
			} else {
				cout << "Login successful!"<< endl;
			}
		}

        // Display appropriate menu based on user role
        int choice;
        bool loggedOut = false;
        do {
            cout << "\n==== Counselling System ====\n";
            cout << "Logged in as " << currentLastName << " " << currentFirstName << " (" << currentEmail << ")\n\n";
            
            // Main menu options based on role
            if (currentRole == 0) { // Patient
                cout << " 1. View Services\n";
                cout << " 2. Manage Appointments\n";
                cout << " 3. View Treatments\n";
                cout << " 4. Manage Tests\n";
                cout << " 5. Manage Tickets\n";
                cout << " 6. Edit My Profile\n"; 
				cout << " 0. Logout\n";
	            cout << "-1. Exit Program\n\n";
	            
	            cout << "Enter your choice (-1-6): ";
	            cin >> choice;
            } else if (currentRole == 1) { // Counsellor
                cout << " 1. View Services\n";
                cout << " 2. Manage Appointments\n";
                cout << " 3. Manage Treatments\n";
                cout << " 4. Manage Tests\n";
		        cout << " 5. View Patients\n"; 
                cout << " 6. Manage Tickets\n";
		        cout << " 7. Edit My Profile\n"; 
				cout << " 0. Logout\n";
	            cout << "-1. Exit Program\n\n";
	            
	            cout << "Enter your choice (-1-7): ";
	            cin >> choice;
            } else if (currentRole == 2) { // Staff
                cout << " 1. Manage Services\n";
                cout << " 2. Manage Appointments\n";
                cout << " 3. Manage Treatments\n";
                cout << " 4. Manage Tests\n";
                cout << " 5. Manage Users\n";
                cout << " 6. Manage Coupons\n";
                cout << " 7. Manage Tickets\n";
		        cout << " 8. Edit My Profile\n";
				cout << " 0. Logout\n";
	            cout << "-1. Exit Program\n\n";
	            
	            cout << "Enter your choice (-1-8): ";
	            cin >> choice;
            } else if (currentRole == 3) { // Admin
                cout << " 1. Manage Categories\n";
                cout << " 2. Manage Services\n";
                cout << " 3. Manage Appointments\n";
                cout << " 4. Manage Treatments\n";
                cout << " 5. Manage Tests\n";
                cout << " 6. Manage Users\n";
                cout << " 7. Manage Coupons\n";
                cout << " 8. Manage Tickets\n";
		        cout << " 9. Edit My Profile\n";
				cout << " 0. Logout\n";
	            cout << "-1. Exit Program\n\n";
	            
	            cout << "Enter your choice (-1-9): ";
	            cin >> choice;
            }
            
            // Handle main menu selection
            if (choice == 0) {
                cout << "Logging out...\n\n";
                loggedOut = true;
                continue;
            } else if (choice == -1) {
                cout << "Exiting program...\n";
                loggedOut = true;
                exitProgram = true;
                continue;
            }
            
            int subChoice = -1, subChoice2=-1, subChoice3=-1;
            
            if (currentRole == 0) { // Patient
            	
                switch(choice) {
                	// View Services
                    case 1: 
                        cout << "\n--- View Services ---\n";
						cout << "1. View All Services" << endl;
						cout << "2. Search Services by Name" << endl;
						cout << "3. Sort Services" << endl;
                        cout << "0. Back to Main Menu\n\n";

                        cout << "Enter your choice (0-3): ";
                        cin >> subChoice;

						switch(subChoice) {
							case 1: 
								// View All Services
								serviceTable.dispAllSvc();
								break;
							case 2: 
								// Search Services by Name
								serviceTable.searchServiceByName();
								break;
							case 3: 
								cout << "\n--- Sort Services ---\n";
								cout << "1. Sort Services by Price    (Low to High)" << endl;
								cout << "2. Sort Services by Price    (High to Low)" << endl;
								cout << "3. Sort Services by Duration (Short to Long)" << endl;
								cout << "4. Sort Services by Duration (Long to Short)" << endl;
                        		cout << "0. Back to Main Menu\n\n";
								
		                        cout << "Enter your choice (0-4): ";
		                        cin >> subChoice2;
								
								switch(subChoice2) {
									case 1: {
										serviceTable.sortServicesByPriceLowToHigh();
										break;
									}
									
									case 2: {
										serviceTable.sortServicesByPriceHighToLow();
										break;
									}
									
									case 3: {
										serviceTable.sortServicesByDurationShortToLong();
										break;
									}
									
									case 4: {
										serviceTable.sortServicesByDurationLongToShort();
										break;
									}
									
									case 0: {
										break;
									}
								}
								
								break;
							case 0: 
								// Back to Main Menu
								break;
						}
                        break;
                        
                    // Manage Appointments
                    case 2: 
                        cout << "\n--- Appointment Management ---\n";
                        cout << "1. Book New Appointment\n";
                        cout << "2. View My Appointments\n";
                        cout << "3. Search Appointments\n";
                        cout << "4. Sort Appointments\n";
                        cout << "5. Delete Appointment\n";
                        cout << "0. Back to Main Menu\n\n";
                        
                        cout << "Enter your choice (0-5): ";
                        cin >> subChoice;
                        
                        switch(subChoice) {
                            case 1:
                            	
                                appointment.addAppoint(appointmentTable, serviceTable, staffTable);
                                break;
                            case 2: {
                            	
                            	appointmentTable.displayPatientAppointments(currentEmail);
                            	
								break;
							}
							case 3: {
                            	cout << "\n--- Search Appointments ---\n";
                        		cout << "1. Search Appointments by ID\n";
                        		cout << "2. Search Appointments by Counsellor Name\n";
                        		cout << "3. Search Appointments by Service\n";
                        		cout << "0. Back to Main Menu\n\n";
                        
		                        cout << "Enter your choice (0-3): ";
		                        cin >> subChoice2;
		                        
		                        switch(subChoice2) {
									case 1: {
										ss.PatientSearchByID(appointmentTable, currentEmail);
										break;
									}

		                        	case 2: {
		                        		ss.PatientSearchByCounsellor(appointmentTable, currentEmail);
										break;
									}
									
									case 3: {
										ss.PatientSearchByService(appointmentTable, serviceTable, currentEmail);
										break;
									}
									
									case 0: {
										break;
									}
								}
		                        
								break;
							}
							case 4: {
								cout << "\n--- Sort Appointments ---\n";
		                        cout << "1. Sort Appointments by Date (Newest to Oldest)\n";
		                        cout << "2. Sort Appointments by Date (Oldest to Newest)\n";
		                        cout << "3. Sort Appointments by Time (Newest to Oldest)\n";
		                        cout << "4. Sort Appointments by Time (Oldest to Newest)\n";
		                        cout << "5. Sort Appointments by Amount (Most to Least)\n";
		                        cout << "6. Sort Appointments by Amount (Least to Most)\n";
                        		cout << "0. Back to Main Menu\n\n";
                        
		                        cout << "Enter your choice (0-6): ";
		                        cin >> subChoice2;
		                        
		                        switch(subChoice2) {
		                        	case 1: {
		                        		PatientsortByDateDescending(appointmentTable, currentEmail);
										break;
									}
									
									case 2: {
										PatientsortByDateAscending(appointmentTable, currentEmail);
										break;
									}
									
									case 3: {
										PatientsortByTimeDescending(appointmentTable, currentEmail);
										break;
									}
									
									case 4: {
										PatientsortByTimeAscending(appointmentTable, currentEmail);
										break;
									}
									
									case 5: {
										PatientsortByNetAmountDescending(appointmentTable, currentEmail);
										break;
									}
									
									case 6: {
										PatientsortByNetAmountAscending(appointmentTable, currentEmail);
										break;
									}
									
									case 0: {
										break;
									}
								}
		                        
								break;
							} 
							case 5: {
                            	cout << "--- Delete Appointment ---\n\n";
								
								break;
							}
                            case 0:
                                break;
                            default:
                                cout << "Invalid choice, please try again.\n";
                        }
                        break;
                        
                    // View Treatments
                    case 3: {
                    	cout << "--- View Treatment ---\n\n";
                    	cout << "1. View All Treatment\n";
                    	cout << "2. Search Treatment by Appointment ID\n";
                        cout << "0. Back to Main Menu\n\n";
                        
                        cout << "Enter your choice (0-2): ";
                        cin >> subChoice;
                        
                        switch(subChoice) {
                        	case 1: {
                        		treatmentTable.displayPatientTx(currentEmail);
                        		
								break;
							} 

							case 2: {
								ss.SearchTxByAppointID(treatmentTable);
								break;
							}
							
							default:
                                cout << "Invalid choice, please try again.\n";
						}
							
						break;
					}
					
					// Manage Test
                    case 4: 
                        cout << "\n--- Test Management ---\n";
                        cout << "1. Take New Test\n";
                        cout << "2. View All Results\n";
                        cout << "3. Search Results by Situation\n";
                        cout << "4. Sort Results\n";
                        cout << "5. Delete Results\n";
                        cout << "0. Back to Main Menu\n\n";
                        
                        cout << "Enter your choice (0-5): ";
                        cin >> subChoice;
                        
                        switch(subChoice) {
                            case 1:
								 
                                testManager.takeTest();
                                
                                break;
                            case 2:
                            	
                            	resultTable.displayPatientResult(currentEmail);
                            	
                                break;

							case 3: {
								ss.SearchResultsBySituation(resultTable);
								break;
							}
                                
                            case 4:
                            	cout << "\n--- Sort Results ---\n";
                            	cout << "1. Sort Results by Score (High to Low)\n";
                            	cout << "2. Sort Results by Score (Low to High)\n";
		                        cout << "0. Back to Main Menu\n\n";
		                        
		                        cout << "Enter your choice (0-2): ";
		                        cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
										ss.sortPatientResultsByScoreDescending(resultTable, currentEmail);
										break;
									}

									case 2: {
										ss.sortPatientResultsByScoreAscending(resultTable, currentEmail);
										break;
									}
								}

							case 5: {
								resultTable.deleteResult(resultTable, currentEmail);
								break;
							}

                            case 0:
                                break;
                                
                            default:
                                cout << "Invalid choice, please try again.\n";
                        }
                        break;
					
					case 5: {
                        cout << "\n--- Ticket Management ---\n";
                        cout << "1. Create Ticket\n";
                        cout << "2. View My Tickets\n";
                        cout << "3. Sort Tickets\n";
                        cout << "4. Delete Ticket\n";
                        cout << "0. Back to Main Menu\n\n";
                        
                        cout << "Enter your choice (0-4): ";
						cin >> subChoice;

						switch(subChoice) {
							case 1: {
								ticketManager.addTicket(ticketTable, currentLastName, currentFirstName, currentPhone, currentEmail);
								break;
							}

							case 2: {
								ticketTable.displayUserTickets(currentEmail);
								break;
							}

							case 3: {
                            	cout << "\n--- Sort Tickets ---\n";
                            	cout << "1. Sort Tickets by Date (Newest to Oldest)\n";
                            	cout << "2. Sort Tickets by Date (Oldest to Newest)\n";
		                        cout << "0. Back to Main Menu\n\n";
		                        
		                        cout << "Enter your choice (0-2): ";
		                        cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
										ss.sortPatientTicketByDateDescending(ticketTable, currentEmail);
										break;
									}

									case 2: {
										ss.sortPatientTicketByDateAscending(ticketTable, currentEmail);
										break;
									}

									case 0: {
										break;
									}

									default: {
										cout << "Invalid choice, please try again.\n";
									}
								}

								break;
							}

							case 4: {
								ticketManager.deleteTicket(ticketTable, currentEmail);
								break;
							}

							case 0: {
								break;
							}

							default: {
								cout << "Invalid choice, please try again.\n";
							}
						}


						break;
					}
                        
                    // Edit My Profile
					case 6: 
						
						for (int i = 0; i < patientTable.getTblSize(); i++) {
						    if (patientTable.getTableElement(i) != NULL && patientTable.getTableElement(i)->getEmail() == currentEmail) {
						        userManager.editPatient(patientTable, i);
						        break;
						    }
						}
						
		                break;
		                
		            case 0: {
						break;
					}
		                
                    default:
                        cout << "Invalid choice, please try again.\n";
                }
            } else if (currentRole == 1) { // Counsellor
                switch(choice) {
                	// View Services
                    case 1: 
                        cout << "\n--- View Services ---\n";
						cout << "1. View All Services" << endl;
						cout << "2. Search Services by Name" << endl;
						cout << "3. Sort Services" << endl;
                        cout << "0. Back to Main Menu\n\n";

                        cout << "Enter your choice (0-3): ";
                        cin >> subChoice;

						switch(subChoice) {
							case 1: 
								// View All Services
								serviceTable.dispAllSvc();
								break;
							case 2: 
								// Search Services by Name
								serviceTable.searchServiceByName();
								break;
							case 3: 
								cout << "\n--- Sort Services ---\n";
								cout << "1. Sort Services by Price    (Low to High)" << endl;
								cout << "2. Sort Services by Price    (High to Low)" << endl;
								cout << "3. Sort Services by Duration (Short to Long)" << endl;
								cout << "4. Sort Services by Duration (Long to Short)" << endl;
                        		cout << "0. Back to Main Menu\n\n";
								
		                        cout << "Enter your choice (0-4): ";
		                        cin >> subChoice2;
								
								switch(subChoice2) {
									case 1: {
										serviceTable.sortServicesByPriceLowToHigh();
										break;
									}
									
									case 2: {
										serviceTable.sortServicesByPriceHighToLow();
										break;
									}
									
									case 3: {
										serviceTable.sortServicesByDurationShortToLong();
										break;
									}
									
									case 4: {
										serviceTable.sortServicesByDurationLongToShort();
										break;
									}
									
									case 0: {
										break;
									}
								}
								
								break;
							case 0: 
								// Back to Main Menu
								break;
						}
                        break;
                    
                    // Manage Appointments
                    case 2: 
                        cout << "\n--- Appointment Management ---\n";
                        cout << "1. Book New Appointment\n";
                        cout << "2. View All Appointments\n";
                        cout << "3. Search Appointments\n";
                        cout << "4. Sort Appointments\n";
                        cout << "5. Edit Appointment\n";
                        cout << "0. Back to Main Menu\n\n";
                        cout << "Enter your choice (0-5): ";
                        cin >> subChoice;
                        
                        switch(subChoice) {
                            case 1:
                            	
                                appointment.addAppoint(appointmentTable, serviceTable, staffTable);
                                break;
                            case 2: {
                            	
                            	appointmentTable.displayAllAppoint();
                            	
								break;
							}
							case 3: {
                            	cout << "\n--- Search Appointments ---\n";
                        		cout << "1. Search Appointments by ID\n";
                        		cout << "2. Search Appointments by Service\n";
                        		cout << "3. Search Appointments by Patient Name\n";
                        		cout << "4. Search Appointments by Patient Phone\n";
                        		cout << "5. Search Appointments by Patient Email\n";
                        		cout << "6. Search Appointments by Status\n";
                        		cout << "0. Back to Main Menu\n\n";
                        
		                        cout << "Enter your choice (0-6): ";
		                        cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
		                        		ss.SearchbyID(appointmentTable);
										break;
									}

									case 2: {
										ss.SearchbyService(appointmentTable, serviceTable);
										break;
									}

									case 3: {
										ss.SearchbyPatientName(appointmentTable);
										break;
									}

									case 4: {
										ss.SearchbyPtPhone(appointmentTable);
										break;
									}

									case 5: {
										ss.SearchbyEmail(appointmentTable);
										break;
									}

									case 6: {
										ss.SearchbyStatus(appointmentTable);
										break;
									}

									case 0:
										break;
										
									default:
										cout << "Invalid choice, please try again.\n";
								}
		                        
								break;
							}
							case 4: {
								cout << "--- Sort Appointments ---\n\n";
		                        cout << "1. Sort Appointments by Date (Newest to Oldest)\n";
		                        cout << "2. Sort Appointments by Date (Oldest to Newest)\n";
		                        cout << "3. Sort Appointments by Time (Newest to Oldest)\n";
		                        cout << "4. Sort Appointments by Time (Oldest to Newest)\n";
                        		cout << "0. Back to Main Menu\n\n";
                        
		                        cout << "Enter your choice (0-4): ";
		                        cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
										sortByDateAscending(appointmentTable);
										break;
									} 
									
									case 2: {
										sortByDateDescending(appointmentTable);
										break;
									} 
									
									case 3: {
										sortByTimeAscending(appointmentTable);
										break;
									} 
									
									case 4: {
										sortByTimeDescending(appointmentTable);
										break;
									} 
									break;
								}

								break;
							} 
							case 5: {
                            	appointment.editAppointment(appointmentTable);
								break;
							}
                            case 0:
                                break;
                            default:
                                cout << "Invalid choice, please try again.\n";
                        }
                        break;
                        
                    case 3: // Manage Treatments
                        cout << "\n--- Treatment Management ---\n";
                        cout << "1. Add New Treatment\n";
                        cout << "2. View All Treatments\n";
                        cout << "3. Search Treatments\n";
                        cout << "4. Edit Treatments\n";
                        cout << "0. Back to Main Menu\n\n";
                        cout << "Enter your choice (0-4): ";
                        cin >> subChoice;
                        
                        switch(subChoice) {
                            case 1:
                                treatment.addTx(treatmentTable);
                                break;
                            case 2:
                                treatmentTable.displayAllTx();
                                break;
                            case 3:
                            	cout << "--- Search Treatments ---\n\n";
                            	cout << "1. Search Treatments by Appointment ID\n";
                            	cout << "2. Search Treatments by Patient Name\n";
                            	cout << "3. Search Treatments by Patient Phone\n";
                            	cout << "4. Search Treatments by Patient Email\n";
		                        cout << "0. Back to Main Menu\n\n";
		                        
		                        cout << "Enter your choice: ";
		                        cin >> subChoice2;

								switch (subChoice2) {
									case 1: {
										ss.SearchTxByAppointID(treatmentTable);
										break;
									}

									case 2: {
										ss.SearchTxByPatientName(treatmentTable);
										break;
									}

									case 3: {
										ss.SearchTxByPatientPhone(treatmentTable);
										break;
									}

									case 4: {
										ss.SearchTxByPatientEmail(treatmentTable);
										break;
									}

									case 0: {
										break;
									}

									default: {
										cout << "Invalid choice, please try again.\n";
									}
								}	

								break;
							
							case 4: {
								treatment.editTreatment(treatmentTable);
								break;
							}

                            case 0:
                                break;
                            default:
                                cout << "Invalid choice, please try again.\n";
                        }
                        break;
                        
                    // Manage Test
                    case 4: 
                        cout << "\n--- Test Management ---\n";
                        cout << "1. Take New Test\n";
                        cout << "2. View All Results\n";
                        cout << "3. Search Results\n";
                        cout << "4. Sort Results\n";
                        cout << "5. Delete Results\n";
                        cout << "6. View All Question\n";
                        cout << "7. Edit Question\n";
                        cout << "0. Back to Main Menu\n\n";
                        
                        cout << "Enter your choice (0-7): ";
                        cin >> subChoice;
                        
                        switch(subChoice) {
                            case 1:
								 
                                testManager.takeTest();
                                
                                break;
                            case 2:
                            	
                            	resultTable.displayAllResults();
                            	
                                break;
                            case 3:
                            	cout << "\n--- Search Results ---\n";
                            	cout << "1. Search Results by Name\n";
                            	cout << "2. Search Results by Phone\n";
                            	cout << "3. Search Results by Email\n";
                            	cout << "4. Search Results by Situation\n";
                        		cout << "0. Back to Main Menu\n\n";
                        		
                        		cout << "Enter your choice (0-4): ";
                        		cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
										ss.SearchResultsByName(resultTable);

										break;
									}

									case 2: {
										ss.SearchResultsByPhone(resultTable);

										break;
									}

									case 3: {
										ss.SearchResultsByEmail(resultTable);

										break;
									}

									case 4: {
										ss.SearchResultsBySituation(resultTable);

										break;
									}

									case 0: {
										break;
									}

									default: {
										cout << "Invalid choice, please try again.\n";
									}
								}
                        		
                        		break;
                            case 4:
                            	cout << "\n--- Sort Results ---\n";
                            	cout << "1. Sort Results by Score (High to Low)\n";
                            	cout << "2. Sort Results by Score (Low to High)\n";
		                        cout << "0. Back to Main Menu\n\n";
		                        
		                        cout << "Enter your choice (0-2): ";
		                        cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
										ss.sortResultsByScoreDescending(resultTable);
										break;
									}

									case 2: {
										ss.sortResultsByScoreAscending(resultTable);
										break;
									}

									case 0: {
										break;
									}

									default: {
										cout << "Invalid choice, please try again.\n";
									}
								}
                        		
                        		break;
							
							case 5: {
								resultTable.deleteResult(resultTable);
								break;
							}
                        	case 6: {
                            	
                            	testTable.displayAllQuestions();
                            	
								break;
							}

							case 7: {
								testTable.editQuestion(testTable);
								break;
							}

                            case 0:
                                break;
                                
                            default:
                                cout << "Invalid choice, please try again.\n";
                        }
                        break;
                        
                    case 5: // Manage Patients
		                cout << "\n--- Patient Management ---\n";
		                cout << "1. Add New Patients\n";
		                cout << "2. View All Patients\n";
		                cout << "3. Search Patients\n";
		                cout << "4. Sort Patients\n";
		                cout << "0. Back to Main Menu\n\n";
		                
		                cout << "Enter your choice: ";
		                cin >> subChoice;
		                
		                switch(subChoice) {
		                	case 1: {
                                patientManager.addPt(patientTable);
                                
								break;
							}
							
		                    case 2:
		                        patientTable.displayAllPatients();
		                        break;
		                        
		                    case 3: {
                        		cout << "\n--- Search Patients ---\n";
                        		cout << "1. Search Patients by First Name\n";
                        		cout << "2. Search Patients by Last Name\n";
                        		cout << "3. Search Patients by Phone\n";
                        		cout << "4. Search Patients by Email\n";
                        		cout << "5. Search Patients by Status\n";
                        		cout << "0. Back to Main Menu\n\n";
		                
				                cout << "Enter your choice (0-5): ";
				                cin >> subChoice2;
		                    	
		                    	switch(subChoice2) {
									case 1: {
										ss.SearchbyFirstName(patientTable);
										break;
									}

									case 2: {
										ss.SearchbyLastName(patientTable);
										break;
									}

									case 3: {
										ss.SearchbyPhone(patientTable);
										break;
									}
									
									case 5: {
										ss.SearchbyStatus(patientTable);
										break;
									}

		                    		case 4: {
		                    			patientTable.searchByEmail();
										break;
									}

									case 0: {
														break;
													}

													default: {
														cout << "Invalid choice, please try again.\n";
													}
								}
								
								break;
							}
							
							case 4: {
                        		cout << "\n--- Sort Patients ---\n";
                        		cout << "1. Sort Patients by Age (Young to Old)\n";
                        		cout << "2. Sort Patients by Age (Old to Young)\n";
                        		cout << "0. Back to Main Menu\n\n";
		                
				                cout << "Enter your choice (0-2): ";
				                cin >> subChoice2;
		                    	
		                    	switch(subChoice2) {
													case 1: {
														ss.sortByAgeAscending(patientTable);
														break;
													}

													case 2: {
														ss.sortByAgeDescending(patientTable);
														break;
													}

						                    		case 0: {
														break;
													}

													default: {
														cout << "Invalid choice, please try again.\n";
													}
												}
								
								break;
							}
		                        
		                    case 0:
		                        break;
		                        
		                    default:
		                        cout << "Invalid choice, please try again.\n";
		                }
		                
		                break;

					case 6: {
                        cout << "\n--- Ticket Management ---\n";
                        cout << "1. Create Ticket\n";
                        cout << "2. View My Tickets\n";
                        cout << "3. Sort Tickets\n";
                        cout << "4. Delete Ticket\n";
                        cout << "0. Back to Main Menu\n\n";
                        
                        cout << "Enter your choice (0-4): ";
						cin >> subChoice;

						switch(subChoice) {
							case 1: {
								ticketManager.addTicket(ticketTable, currentLastName, currentFirstName, currentPhone, currentEmail);
								break;
							}

							case 2: {
								ticketTable.displayUserTickets(currentEmail);
								break;
							}

							case 3: {
                            	cout << "\n--- Sort Tickets ---\n";
                            	cout << "1. Sort Tickets by Date (Newest to Oldest)\n";
                            	cout << "2. Sort Tickets by Date (Oldest to Newest)\n";
		                        cout << "0. Back to Main Menu\n\n";
		                        
		                        cout << "Enter your choice (0-2): ";
		                        cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
										ss.sortPatientTicketByDateDescending(ticketTable, currentEmail);
										break;
									}

									case 2: {
										ss.sortPatientTicketByDateAscending(ticketTable, currentEmail);
										break;
									}

									case 0: {
										break;
									}

									default: {
										cout << "Invalid choice, please try again.\n";
									}
								}

								break;
							}

							case 4: {
								ticketManager.deleteTicket(ticketTable, currentEmail);
								break;
							}

							case 0: {
								break;
							}

							default: {
								cout << "Invalid choice, please try again.\n";
							}
						}


						break;
					}
		                
		            case 7: // Edit My Profile
						for (int i = 0; i < staffTable.getTblSize(); i++) {
						    if (staffTable.getTableElement(i) != NULL && 
						        staffTable.getTableElement(i)->getEmail() == currentEmail) {
						        userManager.editStaff(staffTable, i);
						        break;
						    }
						}
		                break;
		                
                    default:
                        cout << "Invalid choice, please try again.\n";
                }
            } else if (currentRole == 2) { // Staff
                switch(choice) {
                	// View Services
                    case 1: 
                        cout << "\n--- Manage Services ---\n";
						cout << "1. Add New Service" << endl;
						cout << "2. View All Services" << endl;
						cout << "3. Search Services by Name" << endl;
						cout << "4. Sort Services" << endl;
						cout << "5. Edit Service" << endl;
                        cout << "0. Back to Main Menu\n\n";

                        cout << "Enter your choice (0-5): ";
                        cin >> subChoice;

						switch(subChoice) {
							case 1:
								serviceManager.addSvc(serviceTable);
								break;
							case 2: 
								// View All Services
								serviceTable.dispAllSvc();
								break;
							case 3: 
								// Search Services by Name
								cout << "--- Search Services by Name ---\n\n" << endl;
								serviceTable.searchServiceByName();
								break;
							case 4: 
								cout << "\n--- Sort Services ---\n";
								cout << "1. Sort Services by Price    (Low to High)" << endl;
								cout << "2. Sort Services by Price    (High to Low)" << endl;
								cout << "3. Sort Services by Duration (Short to Long)" << endl;
								cout << "4. Sort Services by Duration (Long to Short)" << endl;
                        		cout << "0. Back to Main Menu\n\n";
								
		                        cout << "Enter your choice (0-4): ";
		                        cin >> subChoice2;
								
								switch(subChoice2) {
									case 1: {
										serviceTable.sortServicesByPriceLowToHigh();
										break;
									}
									
									case 2: {
										serviceTable.sortServicesByPriceHighToLow();
										break;
									}
									
									case 3: {
										serviceTable.sortServicesByDurationShortToLong();
										break;
									}
									
									case 4: {
										serviceTable.sortServicesByDurationLongToShort();
										break;
									}
									
									case 0: {
										break;
									}
								}
								
								break;
								
							case 5: {
								serviceTable.editService();
								break;
							}
							
							case 0: 
								// Back to Main Menu
								break;
						}
                        break;
                	
                	// Manage Appointments
                    case 2: 
                        cout << "\n--- Appointment Management ---\n";
                        cout << "1. Book New Appointment\n";
                        cout << "2. View All Appointments\n";
                        cout << "3. Search Appointments\n";
                        cout << "4. Sort Appointments\n";
                        cout << "5. Edit Appointment\n";
                        cout << "6. Delete Appointment\n";
                        cout << "0. Back to Main Menu\n\n";
                        cout << "Enter your choice (0-6): ";
                        cin >> subChoice;
                        
                        switch(subChoice) {
                            case 1:
                            	
                                appointment.addAppoint(appointmentTable, serviceTable, staffTable);
                                break;
                            case 2: {
                            	
                            	appointmentTable.displayAllAppoint();
                            	
								break;
							}
							case 3: {
								cout << "\n--- Search Appointments ---\n";
                        		cout << "1. Search Appointments by ID\n";
                        		cout << "2. Search Appointments by Service\n";
                        		cout << "3. Search Appointments by Patient Name\n";
                        		cout << "4. Search Appointments by Patient Phone\n";
                        		cout << "5. Search Appointments by Patient Email\n";
                        		cout << "6. Search Appointments by Status\n";
                        		cout << "0. Back to Main Menu\n\n";
                        
		                        cout << "Enter your choice (0-6): ";
		                        cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
		                        		ss.SearchbyID(appointmentTable);
										break;
									}

									case 2: {
										ss.SearchbyService(appointmentTable, serviceTable);
										break;
									}

									case 3: {
										ss.SearchbyPatientName(appointmentTable);
										break;
									}

									case 4: {
										ss.SearchbyPtPhone(appointmentTable);
										break;
									}

									case 5: {
										ss.SearchbyEmail(appointmentTable);
										break;
									}

									case 6: {
										ss.SearchbyStatus(appointmentTable);
										break;
									}

									case 0:
										break;
										
									default:
										cout << "Invalid choice, please try again.\n";
								}
		                        
								break;
							}
							case 4: {
								cout << "--- Sort Appointments ---\n\n";
		                        cout << "1. Sort Appointments by Date   (Newest to Oldest)\n";
		                        cout << "2. Sort Appointments by Date   (Oldest to Newest)\n";
		                        cout << "3. Sort Appointments by Time   (Newest to Oldest)\n";
		                        cout << "4. Sort Appointments by Time   (Oldest to Newest)\n";
		                        cout << "5. Sort Appointments by Amount (Highest to Lowest)\n";
		                        cout << "6. Sort Appointments by Amount (Lowest to Highest)\n";
                        		cout << "0. Back to Main Menu\n\n";
                        
		                        cout << "Enter your choice (0-6): ";
		                        cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
										sortByDateAscending(appointmentTable);
										break;
									} 
									
									case 2: {
										sortByDateDescending(appointmentTable);
										break;
									} 
									
									case 3: {
										sortByTimeAscending(appointmentTable);
										break;
									} 
									
									case 4: {
										sortByTimeDescending(appointmentTable);
										break;
									} 

									case 5: {
										sortByNetAmountAscending(appointmentTable);
										break;
									} 

									case 6: {
										sortByNetAmountDescending(appointmentTable);
										break;
									} 
									break;
								}

								break;
							} 
							case 5: {
                            	appointment.editAppointment(appointmentTable);
								break;
							}
							case 6: {
								appointment.deleteAppointment(appointmentTable);
								break;
							}
                            case 0:
                                break;
                            default:
                                cout << "Invalid choice, please try again.\n";
                        }
                        break;
                    
                    // Manage Treatments
                    case 3: 
                        cout << "\n--- Treatment Management ---\n";
                        cout << "1. Add New Treatment\n";
                        cout << "2. View All Treatments\n";
                        cout << "3. Search Treatments\n";
                        cout << "0. Back to Main Menu\n\n";
                        
                        cout << "Enter your choice (0-3): ";
                        cin >> subChoice;
                        
                        switch(subChoice) {
                            case 1:
                                treatment.addTx(treatmentTable);
                                break;
                            case 2:
                                treatmentTable.displayAllTx();
                                break;
                            case 3:
                            	cout << "--- Search Treatments ---\n\n";
                            	cout << "1. Search Treatments by Appointment ID\n";
                            	cout << "2. Search Treatments by Patient Name\n";
                            	cout << "3. Search Treatments by Patient Phone\n";
                            	cout << "4. Search Treatments by Patient Email\n";
		                        cout << "0. Back to Main Menu\n\n";
		                        
		                        cout << "Enter your choice: ";
		                        cin >> subChoice2;

								switch (subChoice2) {
									case 1: {
										ss.SearchTxByAppointID(treatmentTable);
										break;
									}

									case 2: {
										ss.SearchTxByPatientName(treatmentTable);
										break;
									}

									case 3: {
										ss.SearchTxByPatientPhone(treatmentTable);
										break;
									}

									case 4: {
										ss.SearchTxByPatientEmail(treatmentTable);
										break;
									}

									case 0: {
										break;
									}

									default: {
										cout << "Invalid choice, please try again.\n";
									}
								}	

                            case 0:
                                break;
                            default:
                                cout << "Invalid choice, please try again.\n";
                        }
                        break;
                        
                    // Manage Test
                    case 4: 
                        cout << "\n--- Test Management ---\n";
                        cout << "1. Take New Test\n";
                        cout << "2. View All Results\n";
                        cout << "3. Search Results\n";
                        cout << "4. Sort Results\n";
                        cout << "5. Delete Results\n";
                        cout << "6. View All Question\n";
                        cout << "7. Edit Question\n";
                        cout << "0. Back to Main Menu\n\n";
                        
                        cout << "Enter your choice (0-7): ";
                        cin >> subChoice;
                        
                        switch(subChoice) {
                            case 1:
								 
                                testManager.takeTest();
                                
                                break;
                            case 2:
                            	
                            	resultTable.displayAllResults();
                            	
                                break;
                            case 3:
                            	cout << "\n--- Search Results ---\n";
                            	cout << "1. Search Results by Name\n";
                            	cout << "2. Search Results by Phone\n";
                            	cout << "3. Search Results by Email\n";
                            	cout << "4. Search Results by Situation\n";
                        		cout << "0. Back to Main Menu\n\n";
                        		
                        		cout << "Enter your choice (0-4): ";
                        		cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
										ss.SearchResultsByName(resultTable);

										break;
									}

									case 2: {
										ss.SearchResultsByPhone(resultTable);

										break;
									}

									case 3: {
										ss.SearchResultsByEmail(resultTable);

										break;
									}

									case 4: {
										ss.SearchResultsBySituation(resultTable);

										break;
									}

									case 0: {
										break;
									}

									default: {
										cout << "Invalid choice, please try again.\n";
									}
								}
                        		
                        		break;
                            case 4:
                            	cout << "\n--- Sort Results ---\n";
                            	cout << "1. Sort Results by Score (High to Low)\n";
                            	cout << "2. Sort Results by Score (Low to High)\n";
		                        cout << "0. Back to Main Menu\n\n";
		                        
		                        cout << "Enter your choice (0-2): ";
		                        cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
										ss.sortResultsByScoreDescending(resultTable);
										break;
									}

									case 2: {
										ss.sortResultsByScoreAscending(resultTable);
										break;
									}

									case 0: {
										break;
									}

									default: {
										cout << "Invalid choice, please try again.\n";
									}
								}
                        		
                        		break;
							case 5: {
								resultTable.deleteResult(resultTable);
								break;
							}
                        	case 6: {
                            	
                            	testTable.displayAllQuestions();
                            	
								break;
							}

							case 7: {
								testTable.editQuestion(testTable);
								break;
							}
                            case 0:
                                break;
                                
                            default:
                                cout << "Invalid choice, please try again.\n";
                        }
                        break;
                        
                    case 5: {
		                cout << "\n--- Users Management ---\n";
		                cout << "1. Manage Patients\n";
		                cout << "2. Manage Staffs\n";
		                cout << "0. Back to Main Menu\n\n";
		                
		                cout << "Enter your choice (0-2): ";
		                cin >> subChoice;
		                
		                switch(subChoice) {
		                	case 1: {
		                		cout << "\n--- Patient Management ---\n";
				                cout << "1. Add New Patient\n";
				                cout << "2. View All Patients\n";
				                cout << "3. Search Patients\n";
				                cout << "4. Sort Patients\n";
				                cout << "0. Back to Main Menu\n\n";
				                
				                cout << "Enter your choice: ";
				                cin >> subChoice2;
				                
				                switch(subChoice2) {
				                	case 1: {
		                                patientManager.addPt(patientTable);
		                                
										break;
									}
									
				                    case 2:
				                        patientTable.displayAllPatients();
				                        break;
				                        
				                    case 3: {
		                        		cout << "\n--- Search Patients ---\n";
		                        		cout << "1. Search Patients by First Name\n";
		                        		cout << "2. Search Patients by Last Name\n";
		                        		cout << "3. Search Patients by Phone\n";
		                        		cout << "4. Search Patients by Email\n";
		                        		cout << "5. Search Patients by Status\n";
		                        		cout << "0. Back to Main Menu\n\n";
				                
						                cout << "Enter your choice (0-5): ";
						                cin >> subChoice2;
				                    	
										switch(subChoice2) {
											case 1: {
												ss.SearchbyFirstName(patientTable);
												break;
											}

											case 2: {
												ss.SearchbyLastName(patientTable);
												break;
											}

											case 3: {
												ss.SearchbyPhone(patientTable);
												break;
											}
											
											case 5: {
												ss.SearchbyStatus(patientTable);
												break;
											}

											case 4: {
												patientTable.searchByEmail();
												break;
											}

											case 0: {
														break;
													}

													default: {
														cout << "Invalid choice, please try again.\n";
													}
										}
										
										break;
									}
									
									case 4: {
		                        		cout << "\n--- Sort Patients ---\n";
		                        		cout << "1. Sort Patients by Age (Young to Old)\n";
		                        		cout << "2. Sort Patients by Age (Old to Young)\n";
		                        		cout << "0. Back to Main Menu\n\n";
				                
						                cout << "Enter your choice (0-2): ";
						                cin >> subChoice2;
				                    	
				                    	switch(subChoice2) {
													case 1: {
														ss.sortByAgeAscending(patientTable);
														break;
													}

													case 2: {
														ss.sortByAgeDescending(patientTable);
														break;
													}

						                    		case 0: {
														break;
													}

													default: {
														cout << "Invalid choice, please try again.\n";
													}
												}
										
										break;
									}
				                        
				                    case 0:
				                        break;
				                        
				                    default:
				                        cout << "Invalid choice, please try again.\n";
				                }
		                
								break;
							}
							
							case 2: {
		                		cout << "\n--- Staff Management ---\n";
				                cout << "1. Add New Staff\n";
				                cout << "2. View All Staffs\n";
				                cout << "3. Search Staffs\n";
				                cout << "0. Back to Main Menu\n\n";
				                
				                cout << "Enter your choice (0-3): ";
				                cin >> subChoice2;
				                
				                switch(subChoice2) {
				                	case 1: {
		                                staffManager.addStaff(staffTable);
		                                
										break;
									}
									
				                    case 2:
		                                staffTable.displayAllStaff();
		                                
				                        break;
				                        
				                    case 3: {
		                        		cout << "--- Search Staffs ---\n\n";
		                        		cout << "1. Search Staffs by First Name\n";
		                        		cout << "2. Search Staffs by Last Name\n";
		                        		cout << "3. Search Staffs by Phone\n";
		                        		cout << "4. Search Staffs by Email\n";
		                        		cout << "5. Search Staffs by Role\n";
		                        		cout << "6. Search Staffs by Status\n";
		                        		cout << "0. Back to Main Menu\n\n";
				                
						                cout << "Enter your choice (0-6): ";
						                cin >> subChoice2;
				                    	
				                    	switch(subChoice2) {
											case 1: {
												ss.SearchStaffByFirstName(staffTable);
												break;
											}

											case 2: {
												ss.SearchStaffByLastName(staffTable);
												break;
											}

											case 3: {
												ss.SearchStaffByPhone(staffTable);
												break;
											}
											
				                    		case 4: {
			    								staffTable.searchByEmail();
												break;
											}

											case 5: {
												ss.SearchStaffByRole(staffTable);
												break;
											}

											case 6: {
												ss.SearchStaffByStatus(staffTable);
												break;
											}

											case 0: {
														break;
													}

													default: {
														cout << "Invalid choice, please try again.\n";
													}
										}
										
										break;
									}
				                        
				                    case 0:
				                        break;
				                        
				                    default:
				                        cout << "Invalid choice, please try again.\n";
				                }
		                
								break;
							}
						}
						
						break;
					}

					case 6: {
						cout << "\n--- Coupon Management ---\n";
						cout << "1. Add Coupon\n";
						cout << "2. View All Coupons\n";
						cout << "3. Search Coupons\n";
						cout << "4. Sort Coupons\n";
						cout << "5. Edit Coupon\n";
		                cout << "0. Back to Main Menu\n\n";
		                
		                cout << "Enter your choice (0-5): ";
		                cin >> subChoice;

						switch(subChoice) {
							case 1: {
								couponManager.addCoupon(couponTable);
								break;
							}

							case 2: {
								couponTable.displayAllCoupons();
								break;
							}

							case 3: {
								cout << "--- Search Coupons ---\n\n";
								cout << "1. Search Coupons by Code\n";
								cout << "2. Search Coupons by Status\n";
		                        cout << "0. Back to Main Menu\n\n";
				                
						        cout << "Enter your choice (0-2): ";
						        cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
										couponTable.searchCouponByCode();
										break;
									}

									case 2: {
										couponTable.searchCouponByStatus();
										break;
									}

									case 0: {
										break;
									}

									default: {
										cout << "Invalid choice, please try again.\n";
									}
								}

								break;
							}

							case 4: {
								cout << "--- Sort Coupons ---\n\n";
								cout << "1. Sort Coupons by Discount Percentage (Least to Most)\n";
								cout << "2. Sort Coupons by Discount Percentage (Most to Least)\n";
								cout << "3. Sort Coupons by Stock (Least to Most)\n";
								cout << "4. Sort Coupons by Stock (Most to Least)\n";
		                        cout << "0. Back to Main Menu\n\n";
				                
						        cout << "Enter your choice (0-4): ";
						        cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
										couponTable.sortCouponsByDiscountLowToHigh();
										break;
									}

									case 2: {
										couponTable.sortCouponsByDiscountHighToLow(); 
										break;
									}

									case 3: {
										couponTable.sortCouponsByStockLowToHigh();
										break;
									}

									case 4: {
										couponTable.sortCouponsByStockHighToLow();
									}

									case 0: {
										break;
									}

									default: {
										cout << "Invalid choice, please try again.\n";
									}
								}

								break;
							}

							case 5: {
								couponTable.editCoupon();
								break;
							}

							case 0: {
								break;
							}

							default: {
								cout << "Invalid choice, please try again.\n";
							}
						}

						break;
					}

					case 7: {
                        cout << "\n--- Ticket Management ---\n";
                        cout << "1. Create Ticket\n";
                        cout << "2. View All Tickets\n";
                        cout << "3. Search Tickets\n";
                        cout << "4. Sort Tickets\n";
                        cout << "5. Edit Ticket\n";
                        cout << "6. Delete Ticket\n";
                        cout << "0. Back to Main Menu\n\n";
                        
                        cout << "Enter your choice (0-6): ";
						cin >> subChoice;

						switch(subChoice) {
							case 1: {
								ticketManager.addTicket(ticketTable);
								break;
							}

							case 2: {
								ticketTable.displayAllTickets();
								break;
							}

							case 3: {
								cout << "--- Search Tickets ---\n\n";
								cout << "1. Search Tickets by Name\n";
								cout << "2. Search Tickets by Phone\n";
								cout << "3. Search Tickets by email\n";
		                        cout << "0. Back to Main Menu\n\n";
				                
						        cout << "Enter your choice (0-3): ";
						        cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
										ss.searchTicketByName(ticketTable);
										break;
									}

									case 2: {
										ss.searchTicketByPhone(ticketTable);
										break;
									}

									case 3: {
										ss.searchTicketByEmail(ticketTable);
										break;
									}

									case 0: {
										break;
									}

									default: {
										cout << "Invalid choice, please try again.\n";
									}
								}

								break;
							}

							case 4: {
                            	cout << "\n--- Sort Tickets ---\n";
                            	cout << "1. Sort Tickets by Date (Newest to Oldest)\n";
                            	cout << "2. Sort Tickets by Date (Oldest to Newest)\n";
		                        cout << "0. Back to Main Menu\n\n";
		                        
		                        cout << "Enter your choice (0-2): ";
		                        cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
										ss.sortTicketByDateDescending(ticketTable);
										break;
									}

									case 2: {
										ss.sortTicketByDateAscending(ticketTable);
										break;
									}

									case 0: {
										break;
									}

									default: {
										cout << "Invalid choice, please try again.\n";
									}
								}

								break;
							}

							case 5: {
								ticketManager.editTicket(ticketTable);
								break;
							}

							case 6: {
								ticketManager.deleteTicket(ticketTable);
								break;
							}

							case 0: {
								break;
							}

							default: {
								cout << "Invalid choice, please try again.\n";
							}
						}


						break;
					}
					
					case 8: // Edit My Profile
						for (int i = 0; i < staffTable.getTblSize(); i++) {
							if (staffTable.getTableElement(i) != NULL && 
								staffTable.getTableElement(i)->getEmail() == currentEmail) {
								userManager.editStaff(staffTable, i);
								break;
							}
						}
						break;

		            default:
		                cout << "Invalid choice, please try again.\n";
		        }
		    } else if (currentRole == 3) { // Admin
		                switch(choice) {
		                	// View Services
		                    case 2: 
		                        cout << "\n--- Manage Services ---\n";
								cout << "1. Add New Services" << endl;
								cout << "2. View All Services" << endl;
								cout << "3. Search Services by Name" << endl;
								cout << "4. Sort Services" << endl;
								cout << "5. Edit Services" << endl;
								cout << "6. Delete Services" << endl;
		                        cout << "0. Back to Main Menu\n\n";
		
		                        cout << "Enter your choice (0-6): ";
		                        cin >> subChoice;
		
								switch(subChoice) {
									case 1:
										serviceManager.addSvc(serviceTable);
										break;
									case 2: 
										// View All Services
										serviceTable.dispAllSvc();
										break;
									case 3: 
										// Search Services by Name
										cout << "--- Search Services by Name ---\n\n" << endl;
										serviceTable.searchServiceByName();
										break;
									case 4: 
										cout << "\n--- Sort Services ---\n";
										cout << "1. Sort Services by Price    (Low to High)" << endl;
										cout << "2. Sort Services by Price    (High to Low)" << endl;
										cout << "3. Sort Services by Duration (Short to Long)" << endl;
										cout << "4. Sort Services by Duration (Long to Short)" << endl;
		                        		cout << "0. Back to Main Menu\n\n";
										
				                        cout << "Enter your choice (0-4): ";
				                        cin >> subChoice2;
										
										switch(subChoice2) {
											case 1: {
												serviceTable.sortServicesByPriceLowToHigh();
												break;
											}
											
											case 2: {
												serviceTable.sortServicesByPriceHighToLow();
												break;
											}
											
											case 3: {
												serviceTable.sortServicesByDurationShortToLong();
												break;
											}
											
											case 4: {
												serviceTable.sortServicesByDurationLongToShort();
												break;
											}
											
											case 0: {
												break;
											}
										}
										
										break;
										
									case 5: {
										serviceTable.editService();
										break;
									}
									
									case 6: {
										serviceTable.deleteService();
										break;
									}
									
									case 0: {
										break;
									}
		                    	}
								break;
		                    	
		                    case 1: // Manage Categories
		                        cout << "\n--- Category Management ---\n";
		                        cout << "1. Add New Category\n";
		                        cout << "2. View All Categories\n";
		                        cout << "3. Edit Category\n";
		                        cout << "0. Back to Main Menu\n\n";
		                        cout << "Enter your choice (0-3): ";
		                        cin >> subChoice;
		                        
		                        switch(subChoice) {
		                            case 1:
		                                categoryManager.addCat(categoryTable);
		                                break;
		                            case 2:
		                                categoryTable.displayAllCategories();
		                                break;
		                            case 3: {
		                            	categoryTable.editCategory();
										break;
									}
		                            case 0:
		                                break;
		                            default:
		                                cout << "Invalid choice, please try again.\n";
		                        }
		                        break;
		                        
		                    // Manage Appointments
		                    case 3: 
		                        cout << "\n--- Appointment Management ---\n";
		                        cout << "1. Book New Appointment\n";
		                        cout << "2. View All Appointments\n";
		                        cout << "3. Search Appointments\n";
		                        cout << "4. Sort Appointments\n";
		                        cout << "5. Edit Appointment\n";
		                        cout << "6. Delete Appointment\n";
		                        cout << "0. Back to Main Menu\n\n";
		                        cout << "Enter your choice (0-6): ";
		                        cin >> subChoice;
		                        
		                        switch(subChoice) {
		                            case 1:
		                            	
		                                appointment.addAppoint(appointmentTable, serviceTable, staffTable);
		                                break;
		                            case 2: {
		                            	
		                            	appointmentTable.displayAllAppoint();
		                            	
										break;
									}
									case 3: {
										cout << "\n--- Search Appointments ---\n";
                        		cout << "1. Search Appointments by ID\n";
                        		cout << "2. Search Appointments by Service\n";
                        		cout << "3. Search Appointments by Patient Name\n";
                        		cout << "4. Search Appointments by Patient Phone\n";
                        		cout << "5. Search Appointments by Patient Email\n";
                        		cout << "6. Search Appointments by Status\n";
                        		cout << "0. Back to Main Menu\n\n";
                        
		                        cout << "Enter your choice (0-6): ";
		                        cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
		                        		ss.SearchbyID(appointmentTable);
										break;
									}

									case 2: {
										ss.SearchbyService(appointmentTable, serviceTable);
										break;
									}

									case 3: {
										ss.SearchbyPatientName(appointmentTable);
										break;
									}

									case 4: {
										ss.SearchbyPtPhone(appointmentTable);
										break;
									}

									case 5: {
										ss.SearchbyEmail(appointmentTable);
										break;
									}

									case 6: {
										ss.SearchbyStatus(appointmentTable);
										break;
									}

									case 0:
										break;
										
									default:
										cout << "Invalid choice, please try again.\n";
								}
		                        
								break;
											}
											case 4: {
												cout << "--- Sort Appointments ---\n\n";
												cout << "1. Sort Appointments by Date   (Newest to Oldest)\n";
												cout << "2. Sort Appointments by Date   (Oldest to Newest)\n";
												cout << "3. Sort Appointments by Time   (Newest to Oldest)\n";
												cout << "4. Sort Appointments by Time   (Oldest to Newest)\n";
												cout << "5. Sort Appointments by Amount (Highest to Lowest)\n";
												cout << "6. Sort Appointments by Amount (Lowest to Highest)\n";
												cout << "0. Back to Main Menu\n\n";
										
												cout << "Enter your choice (0-6): ";
												cin >> subChoice2;

												switch(subChoice2) {
													case 1: {
														sortByDateAscending(appointmentTable);
														break;
													} 
													
													case 2: {
														sortByDateDescending(appointmentTable);
														break;
													} 
													
													case 3: {
														sortByTimeAscending(appointmentTable);
														break;
													} 
													
													case 4: {
														sortByTimeDescending(appointmentTable);
														break;
													} 

													case 5: {
														sortByNetAmountAscending(appointmentTable);
														break;
													} 

													case 6: {
														sortByNetAmountDescending(appointmentTable);
														break;
													} 
													break;
												}
												break;
											} 
											case 5: {
												appointment.editAppointment(appointmentTable);
												break;
											}
											case 6: {
												appointment.deleteAppointment(appointmentTable);
												break;
											}
											case 0:
												break;
											default:
												cout << "Invalid choice, please try again.\n";
										}
		                        	break;
		                    
		                    // Manage Treatments
		                    case 4: 
		                        cout << "\n--- Treatment Management ---\n";
		                        cout << "1. Add New Treatment\n";
		                        cout << "2. View All Treatments\n";
		                        cout << "3. Search Treatments\n";
		                        cout << "4. Edit Treatments\n";
		                        cout << "0. Back to Main Menu\n\n";
		                        
		                        cout << "Enter your choice (0-4): ";
		                        cin >> subChoice;
		                        
		                        switch(subChoice) {
		                            case 1:
		                                treatment.addTx(treatmentTable);
		                                break;
		                            case 2:
		                                treatmentTable.displayAllTx();
		                                break;
		                            case 3:
		                            	cout << "--- Search Treatments ---\n\n";
		                            	cout << "1. Search Treatments by Appointment ID\n";
		                            	cout << "2. Search Treatments by Patient Name\n";
		                            	cout << "3. Search Treatments by Patient Phone\n";
		                            	cout << "4. Search Treatments by Patient Email\n";
				                        cout << "0. Back to Main Menu\n\n";
				                        
				                        cout << "Enter your choice: ";
				                        cin >> subChoice2;

										switch (subChoice2) {
											case 1: {
												ss.SearchTxByAppointID(treatmentTable);
												break;
											}

											case 2: {
												ss.SearchTxByPatientName(treatmentTable);
												break;
											}

											case 3: {
												ss.SearchTxByPatientPhone(treatmentTable);
												break;
											}

											case 4: {
												ss.SearchTxByPatientEmail(treatmentTable);
												break;
											}

											case 0: {
												break;
											}

											default: {
												cout << "Invalid choice, please try again.\n";
											}
										}	

										break;

									case 4: {
										treatment.editTreatment(treatmentTable);
										break;
									}

		                            case 0:
		                                break;
		                            default:
		                                cout << "Invalid choice, please try again.\n";
		                        }
		                        break;
		                        
		                    // Manage Test
		                    case 5: 
		                        cout << "\n--- Test Management ---\n";
		                        cout << "1. Take New Test\n";
		                        cout << "2. View All Results\n";
		                        cout << "3. Search Results\n";
		                        cout << "4. Sort Results\n";
		                        cout << "5. Delete Results\n";
		                        cout << "6. Add New Question\n";
		                        cout << "7. Edit Question\n";
		                        cout << "8. Delete Questions\n";
		                        cout << "0. Back to Main Menu\n\n";
		                        
		                        cout << "Enter your choice (0-8): ";
		                        cin >> subChoice;
		                        
		                        switch(subChoice) {
		                            case 1:
										 
		                                testManager.takeTest();
		                                
		                                break;
		                            case 2:
		                            	
		                            	resultTable.displayAllResults();
		                            	
		                                break;
		                            case 3:
		                            	cout << "\n--- Search Results ---\n";
		                            	cout << "1. Search Results by Name\n";
		                            	cout << "2. Search Results by Phone\n";
		                            	cout << "3. Search Results by Email\n";
		                            	cout << "4. Search Results by Situation\n";
		                        		cout << "0. Back to Main Menu\n\n";
		                        		
		                        		cout << "Enter your choice (0-4): ";
		                        		cin >> subChoice2;

										switch(subChoice2) {
											case 1: {
												ss.SearchResultsByName(resultTable);
												break;
											}

											case 2: {
												ss.SearchResultsByPhone(resultTable);
												break;
											}

											case 3: {
												ss.SearchResultsByEmail(resultTable);
												break;
											}

											case 4: {
												ss.SearchResultsBySituation(resultTable);
												break;
											}

											case 0: {
												break;
											}

											default: {
												cout << "Invalid choice, please try again.\n";
											}
										}
		                        		
		                        		break;

		                            case 4:
		                            	cout << "\n--- Sort Results ---\n";
		                            	cout << "1. Sort Results by Score (High to Low)\n";
		                            	cout << "2. Sort Results by Score (Low to High)\n";
				                        cout << "0. Back to Main Menu\n\n";
				                        
				                        cout << "Enter your choice (0-2): ";
				                        cin >> subChoice2;

										switch(subChoice2) {
											case 1: {
												ss.sortResultsByScoreDescending(resultTable);
												break;
											}

											case 2: {
												ss.sortResultsByScoreAscending(resultTable);
												break;
											}

											case 0: {
												break;
											}
											
											default: {
												cout << "Invalid choice, please try again.\n";
											}
										}
		                        		
		                        		break;
									case 5: {
										resultTable.deleteResult(resultTable);
										break;
									}
		                        	case 6: {
		                            	
		                            	testTable.displayAllQuestions();
		                            	
										break;
									}
									case 7: {
										testTable.editQuestion(testTable);
										break;
									}
		                            case 0:
		                                break;
		                                
		                            default:
		                                cout << "Invalid choice, please try again.\n";
		                        }
		                        break;
		                        
		                    case 6: {
				                cout << "\n--- Users Management ---\n";
				                cout << "1. Manage Patients\n";
				                cout << "2. Manage Staffs\n";
				                cout << "0. Back to Main Menu\n\n";
				                
				                cout << "Enter your choice (0-2): ";
				                cin >> subChoice;
				                
				                switch(subChoice) {
				                	case 1: {
				                		cout << "\n--- Patient Management ---\n";
						                cout << "1. Add New Patient\n";
						                cout << "2. View All Patients\n";
						                cout << "3. Search Patients\n";
						                cout << "4. Sort Patients\n";
						                cout << "0. Back to Main Menu\n\n";
						                
						                cout << "Enter your choice: ";
						                cin >> subChoice2;
						                
						                switch(subChoice2) {
						                	case 1: {
				                                patientManager.addPt(patientTable);
				                                
												break;
											}
											
						                    case 2:
						                        patientTable.displayAllPatients();
						                        break;
						                        
						                    case 3: {
				                        		cout << "\n--- Search Patients ---\n";
				                        		cout << "1. Search Patients by First Name\n";
				                        		cout << "2. Search Patients by Last Name\n";
				                        		cout << "3. Search Patients by Phone\n";
				                        		cout << "4. Search Patients by Email\n";
				                        		cout << "5. Search Patients by Status\n";
				                        		cout << "0. Back to Main Menu\n\n";
						                
								                cout << "Enter your choice (0-5): ";
								                cin >> subChoice2;
						                    	
												switch(subChoice2) {
													case 1: {
														ss.SearchbyFirstName(patientTable);
														break;
													}

													case 2: {
														ss.SearchbyLastName(patientTable);
														break;
													}

													case 3: {
														ss.SearchbyPhone(patientTable);
														break;
													}
													
													case 5: {
														ss.SearchbyStatus(patientTable);
														break;
													}

													case 4: {
														patientTable.searchByEmail();
														break;
													}

													case 0: {
														break;
													}

													default: {
														cout << "Invalid choice, please try again.\n";
													}
												}
												
												break;
											}
											
											case 4: {
				                        		cout << "\n--- Sort Patients ---\n";
				                        		cout << "1. Sort Patients by Age (Young to Old)\n";
				                        		cout << "2. Sort Patients by Age (Old to Young)\n";
				                        		cout << "0. Back to Main Menu\n\n";
						                
								                cout << "Enter your choice (0-2): ";
								                cin >> subChoice2;
						                    	
						                    	switch(subChoice2) {
													case 1: {
														ss.sortByAgeAscending(patientTable);
														break;
													}

													case 2: {
														ss.sortByAgeDescending(patientTable);
														break;
													}

						                    		case 0: {
														break;
													}

													default: {
														cout << "Invalid choice, please try again.\n";
													}
												}
												
												break;
											}
						                        
						                    case 0:
						                        break;
						                        
						                    default:
						                        cout << "Invalid choice, please try again.\n";
						                }
				                
										break;
									}
									
									case 2: {
				                		cout << "\n--- Staff Management ---\n";
						                cout << "1. Add New Staff\n";
						                cout << "2. View All Staffs\n";
						                cout << "3. Search Staffs\n";
						                cout << "0. Back to Main Menu\n\n";
						                
						                cout << "Enter your choice (0-3): ";
						                cin >> subChoice2;
						                
						                switch(subChoice2) {
						                	case 1: {
				                                staffManager.addStaff(staffTable);
				                                
												break;
											}
											
						                    case 2:
				                                staffTable.displayAllStaff();
				                                
						                        break;
						                        
						                    case 3: {
				                        		cout << "--- Search Staffs ---\n\n";
				                        		cout << "1. Search Staffs by First Name\n";
				                        		cout << "2. Search Staffs by Last Name\n";
				                        		cout << "3. Search Staffs by Phone\n";
				                        		cout << "4. Search Staffs by Email\n";
				                        		cout << "5. Search Staffs by Role\n";
				                        		cout << "6. Search Staffs by Status\n";
				                        		cout << "0. Back to Main Menu\n\n";
						                
								                cout << "Enter your choice (0-6): ";
								                cin >> subChoice2;
						                    	
												switch(subChoice2) {
													case 1: {
														ss.SearchStaffByFirstName(staffTable);
														break;
													}

													case 2: {
														ss.SearchStaffByLastName(staffTable);
														break;
													}

													case 3: {
														ss.SearchStaffByPhone(staffTable);
														break;
													}
													
													case 4: {
														staffTable.searchByEmail();
														break;
													}

													case 5: {
														ss.SearchStaffByRole(staffTable);
														break;
													}

													case 6: {
														ss.SearchStaffByStatus(staffTable);
														break;
													}

													case 0: {
																break;
															}

															default: {
																cout << "Invalid choice, please try again.\n";
															}
												}
												
												break;
											}
						                        
						                    case 0:
						                        break;
						                        
						                    default:
						                        cout << "Invalid choice, please try again.\n";
						                }
				                
										break;
									}
								}
								
								break;
							}

							case 7: {
						cout << "\n--- Coupon Management ---\n";
						cout << "1. Add Coupon\n";
						cout << "2. View All Coupons\n";
						cout << "3. Search Coupons\n";
						cout << "4. Sort Coupons\n";
						cout << "5. Edit Coupon\n";
						cout << "6. Delete Coupon\n";
		                cout << "0. Back to Main Menu\n\n";
		                
		                cout << "Enter your choice (0-6): ";
		                cin >> subChoice;

						switch(subChoice) {
							case 1: {
								couponManager.addCoupon(couponTable);
								break;
							}

							case 2: {
								couponTable.displayAllCoupons();
								break;
							}

							case 3: {
								cout << "--- Search Coupons ---\n\n";
								cout << "1. Search Coupons by Code\n";
								cout << "2. Search Coupons by Status\n";
		                        cout << "0. Back to Main Menu\n\n";
				                
						        cout << "Enter your choice (0-2): ";
						        cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
										couponTable.searchCouponByCode();
										break;
									}

									case 2: {
										couponTable.searchCouponByStatus();
										break;
									}

									case 0: {
										break;
									}

									default: {
										cout << "Invalid choice, please try again.\n";
									}
								}

								break;
							}

							case 4: {
								cout << "--- Sort Coupons ---\n\n";
								cout << "1. Sort Coupons by Discount Percentage (Least to Most)\n";
								cout << "2. Sort Coupons by Discount Percentage (Most to Least)\n";
								cout << "3. Sort Coupons by Stock (Least to Most)\n";
								cout << "4. Sort Coupons by Stock (Most to Least)\n";
		                        cout << "0. Back to Main Menu\n\n";
				                
						        cout << "Enter your choice (0-4): ";
						        cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
										couponTable.sortCouponsByDiscountLowToHigh();
										break;
									}

									case 2: {
										couponTable.sortCouponsByDiscountHighToLow(); 
										break;
									}

									case 3: {
										couponTable.sortCouponsByStockLowToHigh();
										break;
									}

									case 4: {
										couponTable.sortCouponsByStockHighToLow();
									}

									case 0: {
										break;
									}

									default: {
										cout << "Invalid choice, please try again.\n";
									}
								}

								break;
							}

							case 5: {
								couponTable.editCoupon();
								break;
							}

							case 6: {
								couponTable.deleteCoupon();
								break;
							}

							case 0: {
								break;
							}

							default: {
								cout << "Invalid choice, please try again.\n";;
							}
						}

						break;
					}
							
					case 8: {
                        cout << "\n--- Ticket Management ---\n";
                        cout << "1. Create Ticket\n";
                        cout << "2. View All Tickets\n";
                        cout << "3. Search Tickets\n";
                        cout << "4. Sort Tickets\n";
                        cout << "5. Edit Ticket\n";
                        cout << "6. Delete Ticket\n";
                        cout << "0. Back to Main Menu\n\n";
                        
                        cout << "Enter your choice (0-6): ";
						cin >> subChoice;

						switch(subChoice) {
							case 1: {
								ticketManager.addTicket(ticketTable);
								break;
							}

							case 2: {
								ticketTable.displayAllTickets();
								break;
							}

							case 3: {
								cout << "--- Search Tickets ---\n\n";
								cout << "1. Search Tickets by Name\n";
								cout << "2. Search Tickets by Phone\n";
								cout << "3. Search Tickets by email\n";
		                        cout << "0. Back to Main Menu\n\n";
				                
						        cout << "Enter your choice (0-3): ";
						        cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
										ss.searchTicketByName(ticketTable);
										break;
									}

									case 2: {
										ss.searchTicketByPhone(ticketTable);
										break;
									}

									case 3: {
										ss.searchTicketByEmail(ticketTable);
										break;
									}

									case 0: {
										break;
									}

									default: {
										cout << "Invalid choice, please try again.\n";
									}
								}

								break;
							}

							case 4: {
                            	cout << "\n--- Sort Tickets ---\n";
                            	cout << "1. Sort Tickets by Date (Newest to Oldest)\n";
                            	cout << "2. Sort Tickets by Date (Oldest to Newest)\n";
		                        cout << "0. Back to Main Menu\n\n";
		                        
		                        cout << "Enter your choice (0-2): ";
		                        cin >> subChoice2;

								switch(subChoice2) {
									case 1: {
										ss.sortTicketByDateDescending(ticketTable);
										break;
									}

									case 2: {
										ss.sortTicketByDateAscending(ticketTable);
										break;
									}

									case 0: {
										break;
									}

									default: {
										cout << "Invalid choice, please try again.\n";
									}
								}

								break;
							}

							case 5: {
								ticketManager.editTicket(ticketTable);
								break;
							}

							case 6: {
								ticketManager.deleteTicket(ticketTable);
								break;
							}

							case 0: {
								break;
							}

							default: {
								cout << "Invalid choice, please try again.\n";
							}
						}


						break;
					}
					
					case 9: // Edit My Profile
								for (int i = 0; i < staffTable.getTblSize(); i++) {
									if (staffTable.getTableElement(i) != NULL && 
										staffTable.getTableElement(i)->getEmail() == currentEmail) {
										userManager.editStaff(staffTable, i);
										break;
									}
								}
								break;
								
                    default:
                        cout << "Invalid choice, please try again.\n";
                }
            }
        } while (!loggedOut);
    }

    return 0;
}
