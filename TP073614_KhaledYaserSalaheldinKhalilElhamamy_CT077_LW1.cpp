#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <chrono>
using namespace std;

class Node {
public:
    Node* next;
    string studentID;      
    string FullName;
    string programme;
    int yearOfStudy;
    double cgpa;
    string contactNumber; 

    Node(string id, string name, string prog, int year, double gpa, string contact = "") {
        studentID = id;
        FullName = name;
        programme = prog;
        yearOfStudy = year;
        cgpa = gpa;
        contactNumber = contact;
        next = nullptr;
    }
};


class ProgrammeNode {
public:
    ProgrammeNode* next;
    string code;
    string name;
    string faculty;
    int durationYears;
 
    ProgrammeNode(string c, string n, string f, int d) {
        code = c;
        name = n;
        faculty = f;
        durationYears = d;
        next = nullptr;
    }
};


int getValidInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid whole number (integer).\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }
}

double getValidCGPA(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid number for CGPA.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (value < 0.0 || value > 4.0) {
            cout << "Invalid CGPA! CGPA must be between 0.0 and 4.0. Please enter again.\n";
            continue;
        }
        return value;
    }
}

string getValidLine(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (value.empty()) {
            cout << "Input cannot be empty. Please enter again.\n";
            continue;
        }
        return value;
    }
}

bool isIdTaken(Node* head, const string& id) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->studentID == id) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

string getValidUniqueId(Node* head, const string& prompt) {
    string id;

    while (true) {
        id = getValidLine(prompt);

        // Remove TP if the user typed it
        if (id.substr(0, 2) == "TP") {
            id = id.substr(2);
        }

        // Check if all characters are digits
        bool valid = true;
        for (char c : id) {
            if (!isdigit(c)) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            cout << "Student ID must contain only numbers.\n";
            continue;
        }

        // Reject if more than 6 digits
        if (id.length() > 6) {
            cout << "Student ID cannot be more than 6 digits.\n";
            continue;
        }

        // Pad with leading zeros until it is 6 digits
        while (id.length() < 6) {
            id = "0" + id;
        }

        // Add TP prefix
        id = "TP" + id;

        if (isIdTaken(head, id)) {
            cout << "Student ID " << id << " already exists!\n";
            continue;
        }

        return id;
    }
}
 

void loadProgrammes(ProgrammeNode*& programmeHead, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "[Warning] Could not open programme file: " << filename << ". "
             << "Programme validation will be skipped.\n";
        return;
    }
 
    string line;
    bool isHeader = true;
    int loaded = 0, skipped = 0;
    ProgrammeNode* tail = nullptr;
 
    while (getline(file, line)) {
        if (line.empty()) continue;
        if (isHeader) {
            isHeader = false;
            continue;
        }
 
        stringstream ss(line);
        string code, name, faculty, durationStr;
 
        if (!getline(ss, code, ',') || !getline(ss, name, ',') ||
            !getline(ss, faculty, ',') || !getline(ss, durationStr, ',')) {
            skipped++;
            continue;
        }
 
        int duration;
        try {
            duration = stoi(durationStr);
        } catch (...) {
            skipped++;
            continue;
        }
 
        if (code.empty()) {
            skipped++;
            continue;
        }
 
        ProgrammeNode* newNode = new ProgrammeNode(code, name, faculty, duration);
        if (programmeHead == nullptr) {
            programmeHead = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
        loaded++;
    }
    file.close();
    cout << "Loaded " << loaded << " programme(s) from " << filename
         << " (" << skipped << " skipped).\n";
}
 

void displayProgrammes(ProgrammeNode* programmeHead) {
    if (programmeHead == nullptr) {
        cout << "No programme data is currently loaded.\n";
        return;
    }
    cout << "\n----------------------------------------------------------------------\n";
    cout << "Code    | Programme Name                                        | Years\n";
    cout << "----------------------------------------------------------------------\n";
    ProgrammeNode* temp = programmeHead;
    while (temp != nullptr) {
        cout << temp->code << "\t| " << temp->name << " | " << temp->durationYears << "\n";
        temp = temp->next;
    }
    cout << "----------------------------------------------------------------------\n";
}
 

ProgrammeNode* findProgrammeByCode(ProgrammeNode* programmeHead, const string& code) {
    ProgrammeNode* temp = programmeHead;
    while (temp != nullptr) {
        if (temp->code == code) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}
 

string getValidProgramme(ProgrammeNode* programmeHead, const string& prompt) {
    if (programmeHead == nullptr) {
        cout << "[Notice] No programme list loaded -- falling back to free-text entry.\n";
        return getValidLine(prompt);
    }
 
    displayProgrammes(programmeHead);
 
    while (true) {
        string code = getValidLine("Enter Programme Code from the list above: ");
        ProgrammeNode* match = findProgrammeByCode(programmeHead, code);
        if (match != nullptr) {
            return match->name;
        }
        cout << "Programme code '" << code << "' was not found. Please choose a code from the list above.\n";
    }
}
 
void freeProgrammeList(ProgrammeNode*& programmeHead) {
    while (programmeHead != nullptr) {
        ProgrammeNode* temp = programmeHead;
        programmeHead = programmeHead->next;
        delete temp;
    }
}

void insertAtBeginning(Node*& head, string id, string name, string prog, int year, double gpa, string contact = "") {
    Node* newNode = new Node(id, name, prog, year, gpa, contact);
    newNode->next = head;
    head = newNode;
    cout << "Successfully inserted at the beginning!\n";
}

void insertAtEnd(Node*& head, string id, string name, string prog, int year, double gpa, string contact = "") {
    Node* temp = head;
    Node* newNode = new Node(id, name, prog, year, gpa, contact);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void insertAtPosition(Node*& head, int index, string id, string name, string prog, int year, double gpa, string contact = "") {
    if (index <= 1 || head == nullptr) {
        insertAtBeginning(head, id, name, prog, year, gpa, contact);
        return;
    }
    Node* temp = head;
    Node* newNode = new Node(id, name, prog, year, gpa, contact);
    int count = 1;
    while (count != index - 1 && temp->next != nullptr) {
        temp = temp->next;
        count++;
    }
    newNode->next = temp->next;
    temp->next = newNode;
    cout << "Successfully inserted at position " << index << endl;
}

void traverse(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        cout << "ID: " << temp->studentID << " | Name: " << temp->FullName
             << " | Programme: " << temp->programme
             << " | Year: " << temp->yearOfStudy
             << " | CGPA: " << temp->cgpa << endl;
        temp = temp->next;
    }
}

void deleteById(Node*& head, string id) {
    if (head == nullptr) {
        cout << "The list is empty. Nothing to delete.\n";
        return;
    }
    Node* temp = head;
    Node* prev = head;

    if (head->studentID == id) {
        Node* nodeToDelete = head;
        head = head->next;
        delete nodeToDelete;
        cout << "Successfully deleted student ID: " << id << endl;
        return;
    }

    while (temp != nullptr && temp->studentID != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != nullptr) {
        prev->next = temp->next;
        delete temp;
        cout << "Successfully deleted student ID: " << id << endl;
    } else {
        cout << "Student ID " << id << " was not found in the system.\n";
    }
}

void searchByName(Node*& head, string name) {
    Node* temp = head;
    bool found = false;
    if (head == nullptr) {
        cout << "\nThe list is empty. Cannot search.\n";
        return;
    }
    while (temp != nullptr) {
        if (temp->FullName == name) {
            cout << "ID: " << temp->studentID
                 << " | Name: " << temp->FullName
                 << " | Programme: " << temp->programme
                 << " | CGPA: " << temp->cgpa << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "No student with the name '" << name << "' exists in the system.\n";
    }
}

void searchById(Node* head, string id) {
    Node* temp = head;
    if (head == nullptr) {
        cout << "\nThe list is empty. Cannot search.\n";
        return;
    }
    while (temp != nullptr) {
        if (temp->studentID == id) {
            cout << "ID: " << temp->studentID
                 << " | Name: " << temp->FullName
                 << " | Programme: " << temp->programme
                 << " | Year: " << temp->yearOfStudy
                 << " | CGPA: " << temp->cgpa << endl;
            return; 
        }
        temp = temp->next;
    }
    cout << "No student with ID '" << id << "' exists.\n";
}

void countRecords(Node*& head) {
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        temp = temp->next;
        count++;
    }
    cout << "The number of records are: " << count << endl;
}

Node* midPoint(Node* head) {
    Node* slow = head;
    Node* fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node* merge(Node* a, Node* b) {
    Node dummy("", "", "", 0, 0.0);
    Node* tail = &dummy;

    while (a != nullptr && b != nullptr) {
        if (a->cgpa > b->cgpa) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }

    if (a != nullptr) tail->next = a;
    else tail->next = b;

    return dummy.next;
}

Node* mergeSort(Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    Node* mid = midPoint(head);
    Node* a = head;
    Node* b = mid->next;
    mid->next = nullptr;

    a = mergeSort(a);
    b = mergeSort(b);

    return merge(a, b);
}

void loadFromCSV(Node*& head, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "[Warning] Could not open file: " << filename << ". Skipping.\n";
        return;
    }
    string line;
    bool isHeader = true;
    int loaded = 0, skipped = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;
        if (isHeader) {
            isHeader = false;
            continue; 
        }

        stringstream ss(line);
        string id, name, prog, yearStr, gpaStr, contact;

        if (!getline(ss, id, ',') || !getline(ss, name, ',') ||
            !getline(ss, prog, ',') || !getline(ss, yearStr, ',') ||
            !getline(ss, gpaStr, ',')) {
            skipped++;
            continue;
        }
        getline(ss, contact, ',');

        int year;
        double gpa;
        try {
            year = stoi(yearStr);
            gpa = stod(gpaStr);
        } catch (...) {
            skipped++; 
            continue;
        }

        if (id.empty() || isIdTaken(head, id)) {
            skipped++; 
            continue;
        }

        insertAtEnd(head, id, name, prog, year, gpa, contact);
        loaded++;
    }
    file.close();
    cout << "Loaded " << loaded << " record(s) from " << filename
         << " (" << skipped << " skipped).\n";
}

void freeList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int countNodes(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

void benchmarkFile(const string& filename) {
    Node* head = nullptr;

    auto loadStart = chrono::high_resolution_clock::now();
    loadFromCSV(head, filename);
    auto loadEnd = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> loadTime = loadEnd - loadStart;

    if (head == nullptr) {
        cout << "[Error] Failed to load records for file: " << filename << "\n";
        return;
    }

    int structuralCount = countNodes(head);

    Node* scanPtr = head;
    while (scanPtr->next != nullptr) {
        scanPtr = scanPtr->next;
    }
    string validTargetID = scanPtr->studentID;
    string validTargetName = scanPtr->FullName;
    string validTargetProg = scanPtr->programme;
    int validTargetYear = scanPtr->yearOfStudy;
    double validTargetCgpa = scanPtr->cgpa;
    string validTargetContact = scanPtr->contactNumber;

    streambuf* originalBuffer = cout.rdbuf();
    stringstream dummyStream;
    cout.rdbuf(dummyStream.rdbuf());

    auto countStart = chrono::high_resolution_clock::now();
    countRecords(head); 
    auto countEnd = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> countTime = countEnd - countStart;

    auto searchIdStart = chrono::high_resolution_clock::now();
    searchById(head, validTargetID);
    auto searchIdEnd = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> searchIdTime = searchIdEnd - searchIdStart;

    auto searchNameStart = chrono::high_resolution_clock::now();
    searchByName(head, validTargetName);
    auto searchNameEnd = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> searchNameTime = searchNameEnd - searchNameStart;

    auto insBegStart = chrono::high_resolution_clock::now();
    insertAtBeginning(head, "TP_BENCH_BEG", "Benchmark Beginning", "Data Structures", 1, 4.0);
    auto insBegEnd = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> insBegTime = insBegEnd - insBegStart;

    auto insEndStart = chrono::high_resolution_clock::now();
    insertAtEnd(head, "TP_BENCH_END", "Benchmark End", "Data Structures", 1, 4.0);
    auto insEndEnd = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> insEndTime = insEndEnd - insEndStart;

    int targetedMidpoint = structuralCount / 2;
    auto insPosStart = chrono::high_resolution_clock::now();
    insertAtPosition(head, targetedMidpoint, "TP_BENCH_POS", "Benchmark Position", "Data Structures", 1, 4.0);
    auto insPosEnd = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> insPosTime = insPosEnd - insPosStart;

    auto deleteStart = chrono::high_resolution_clock::now();
    deleteById(head, validTargetID);
    auto deleteEnd = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> deleteTime = deleteEnd - deleteStart;

    // Restore the record we just deleted (untimed) so the dataset is back to
    // its original size before Display/Sort run below.
    insertAtEnd(head, validTargetID, validTargetName, validTargetProg, validTargetYear, validTargetCgpa, validTargetContact);

    deleteById(head, "TP_BENCH_BEG");
    deleteById(head, "TP_BENCH_END");
    deleteById(head, "TP_BENCH_POS");

    auto displayStart = chrono::high_resolution_clock::now();
    traverse(head);
    auto displayEnd = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> displayTime = displayEnd - displayStart;

    auto sortStart = chrono::high_resolution_clock::now();
    head = mergeSort(head);
    auto sortEnd = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> sortTime = sortEnd - sortStart;

    cout.rdbuf(originalBuffer);

    cout << "\n=======================================================\n";
    cout << "   COMPREHENSIVE BENCHMARK ANALYSIS FOR: " << filename << "\n";
    cout << "=======================================================\n";
    cout << "Total Records Processed  : " << structuralCount << " nodes\n";
    cout << "Estimated Heap Footprint : " << (structuralCount * sizeof(Node)) << " Bytes (" 
         << (double)(structuralCount * sizeof(Node)) / 1024.0 << " KB)\n";
    cout << "-------------------------------------------------------\n";
    cout << "Operation Measured            | Execution Speed Time\n";
    cout << "-------------------------------------------------------\n";
    cout << "1. Load Dataset File          | " << loadTime.count() << " us\n";
    cout << "2. Add / Insert (Head)        | " << insBegTime.count() << " us\n";
    cout << "3. Add / Insert (End)         | " << insEndTime.count() << " us\n";
    cout << "4. Add / Insert (Position)    | " << insPosTime.count() << " us\n";
    cout << "5. Delete by Student ID       | " << deleteTime.count() << " us\n";
    cout << "6. Search - Linear (by ID)    | " << searchIdTime.count() << " us\n";
    cout << "7. Search - Linear (by Name)  | " << searchNameTime.count() << " us\n";
    cout << "8. Display All                | " << displayTime.count() << " us\n";
    cout << "9. Count Records              | " << countTime.count() << " us\n";
    cout << "10. Sort by CGPA              | " << sortTime.count() << " us\n";
    cout << "=======================================================\n";

    freeList(head);
}

void benchmarkAllFiles(const string filenames[], int size) {
    cout << "\n===== Running Comprehensive Load & Operations Benchmark =====\n";
    for (int i = 0; i < size; ++i) {
        benchmarkFile(filenames[i]);
    }
    cout << "\n===== Benchmark Metrics Compilation Complete =====\n";
}

void printMenu() {
    cout << "\n===== Student Record System =====\n";
    cout << "1. Insert student at the beginning\n";
    cout << "2. Insert student at the end\n";
    cout << "3. Insert student at a specific position\n";
    cout << "4. Display all students\n";
    cout << "5. Delete student by ID\n";
    cout << "6. Search student by name\n";
    cout << "7. Count total records\n";
    cout << "8. Merge Sort\n";
    cout << "9. Exit\n";
    cout << "10. Benchmark load & sort time for each CSV file\n";
    cout << "11. View available programmes\n";
    cout << "Enter your choice: ";
}
 
int main() {
    Node* head = nullptr;
    ProgrammeNode* programmeHead = nullptr;
 
    string csvFiles[4] = {
        "./datasets/students_500.csv",
        "./datasets/students_2000.csv",
        "./datasets/students_8000.csv",
        "./datasets/students_30000.csv"
    };
    const string programmeFile = "./datasets/programmes.csv";
 
    // Load the master programme list once at startup so every insertion
    // path (beginning/end/position) can validate against it.
    loadProgrammes(programmeHead, programmeFile);
 
    cout << "===== Initial Data Setup =====\n";
    cout << "Select which dataset file to load into active system memory:\n";
    cout << "1. students_500.csv\n2. students_2000.csv\n3. students_8000.csv\n4. students_30000.csv\n";
    int fileChoice = getValidInt("Enter choice (1-4): ");
    if (fileChoice >= 1 && fileChoice <= 4) {
        loadFromCSV(head, csvFiles[fileChoice - 1]);
    } else {
        cout << "Invalid selection. Initializing with empty system list.\n";
    }
 
    int choice;
    do {
        printMenu();
        cin >> choice;
 
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number from 1-11.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
 
        switch (choice) {
            case 1: {
                string id = getValidUniqueId(head, "Enter Student ID: ");
                string name = getValidLine("Enter Full Name: ");
                string prog = getValidProgramme(programmeHead, "Enter Programme: ");
                int year = getValidInt("Enter Year of Study: ");
                double gpa = getValidCGPA("Enter CGPA: ");
                insertAtBeginning(head, id, name, prog, year, gpa);
                break;
            }
            case 2: {
                string id = getValidUniqueId(head, "Enter Student ID: ");
                string name = getValidLine("Enter Full Name: ");
                string prog = getValidProgramme(programmeHead, "Enter Programme: ");
                int year = getValidInt("Enter Year of Study: ");
                double gpa = getValidCGPA("Enter CGPA: ");
                insertAtEnd(head, id, name, prog, year, gpa);
                cout << "Successfully inserted at the end!\n";
                break;
            }
            case 3: {
                int pos = getValidInt("Enter position to insert at: ");
                string id = getValidUniqueId(head, "Enter Student ID: ");
                string name = getValidLine("Enter Full Name: ");
                string prog = getValidProgramme(programmeHead, "Enter Programme: ");
                int year = getValidInt("Enter Year of Study: ");
                double gpa = getValidCGPA("Enter CGPA: ");
                insertAtPosition(head, pos, id, name, prog, year, gpa);
                break;
            }
            case 4:
                cout << "\n--- All Student Records ---\n";
                traverse(head);
                break;
            case 5: {
                string id = getValidLine("Enter Student ID to delete: ");
                deleteById(head, id);
                break;
            }
            case 6: {
                cout << "Search Options:\n1. Search by Full Name\n2. Search by Student ID\nEnter selection: ";
                int sType = getValidInt("");
                if (sType == 1) {
                    string name = getValidLine("Enter Full Name to search: ");
                    searchByName(head, name);
                } else if (sType == 2) {
                    string id = getValidLine("Enter Student ID to search: ");
                    searchById(head, id);
                } else {
                    cout << "Invalid option chosen.\n";
                }
                break;
            }
            case 7:
                countRecords(head);
                break;
            case 8: {
                head = mergeSort(head);   
                cout << "\n--- Sorted Records (by CGPA Descending) ---\n";
                traverse(head);
                break;
            }
            case 9:
                cout << "Exiting program. Goodbye!\n";
                break;
            case 10:
                benchmarkAllFiles(csvFiles, 4);
                break;
            case 11:
                cout << "\n--- Available Programmes (from " << programmeFile << ") ---\n";
                displayProgrammes(programmeHead);
                break;
            default:
                cout << "Invalid choice. Please select a number between 1 and 11.\n";
        }
    } while (choice != 9);
 
    freeList(head);
    freeProgrammeList(programmeHead);
    return 0;
}
