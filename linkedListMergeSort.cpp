#include <iostream>
using namespace std;
#include <string>

class Node {
public:
    Node* next;
    int studentID;
    string FullName;
    string programme;
    int yearOfStudy;
    double cgpa;
      
    Node(int id, string name, string prog, int year, double gpa) {
        studentID = id;
        FullName = name;
        programme = prog;
        yearOfStudy = year;
        cgpa = gpa;
        next = nullptr;
    }
};


void insertAtBeginning(Node*& head, int id, string name, string prog, int year, double gpa) {
    Node* newNode = new Node(id, name, prog, year, gpa);
    newNode->next = head;
    head = newNode;
    cout << "Successfully inserted at the beginning!\n";
}


void insertAtEnd(Node*& head, int id, string name, string prog, int year, double gpa){
    Node* temp = head;
    Node* newNode = new Node(id, name, prog, year, gpa);
    if (head == nullptr) {
        head = newNode;
        cout << "\n[Success] List was empty. Successfully inserted as first node!\n";
        return;
    }
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
    cout << "Successfully inserted at the end!\n";
}

void insertAtPosition(Node*& head, int index, int id, string name, string prog, int year, double gpa){
    if (index <= 1 || head == nullptr) {
        insertAtBeginning(head, id, name, prog, year, gpa);
        return;
    }
    Node* temp = head;
    Node* newNode = new Node(id, name, prog, year, gpa);
    int count = 1;
    while(count != index - 1 && temp->next != nullptr){
        temp = temp->next;
        count++;
    }
    newNode->next = temp->next;
    temp->next = newNode;
    cout << "Successfully inserted at the " << index << endl;
}






void traverse(Node* head){
    Node* temp = head;
    while(temp != NULL){
        cout << "ID: " << temp->studentID << " | Name: " << temp->FullName << " | CGPA: " << temp->cgpa << endl;
        temp = temp->next;
    }
}

void deleteById(Node* &head, int id){
    Node* temp = head;
    Node* prev = head;
    //if its the first node
    if(head->studentID == id){
        Node* nodeToDelete = head;
        head = head->next;
        delete nodeToDelete;
        cout << "Successfully deleted student ID: " << id << endl;
        return;
    }

    while(temp->studentID != id && temp != nullptr ){
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

void searchByName(Node* &head, string name){
    Node* temp = head;
    bool found = false;
    if (head == nullptr) {
        cout << "\n The list is empty. Cannot search.\n";
        return;
    }
    while(temp!=nullptr){
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

void countRecords(Node* &head){
    int count = 0;
    Node* temp = head;  
    while(temp!=nullptr){
        temp= temp->next;
        count++;
    }

    cout <<"The number of records are: "<< count;
}

Node* midPoint(Node* head){
    Node* slow = head;
    Node* fast = head->next;

    while(fast!=NULL && fast->next !=NULL){
        slow = slow->next;
        fast = fast-> next;
    }
    return slow;
}




void printMenu(){
    cout << "\n===== Student Record System =====\n";
    cout << "1. Insert student at the beginning\n";
    cout << "2. Insert student at the end\n";
    cout << "3. Insert student at a specific position\n";
    cout << "4. Display all students\n";
    cout << "5. Delete student by ID\n";
    cout << "6. Search student by name\n";
    cout << "7. Count total records\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}
 
int main(){
    Node* head = nullptr;
    int choice;
 
    do {
        printMenu();
        cin >> choice;
 
        // Guard against non-numeric input so the menu doesn't loop forever
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number from 1-8.\n";
            continue;
        }
 
        switch (choice) {
            case 1: {
                int id, year;
                double gpa;
                string name, prog;
                cout << "Enter Student ID: "; cin >> id;
                cout << "Enter Full Name: "; cin.ignore(); getline(cin, name);
                cout << "Enter Programme: "; getline(cin, prog);
                cout << "Enter Year of Study: "; cin >> year;
                cout << "Enter CGPA: "; cin >> gpa;
                insertAtBeginning(head, id, name, prog, year, gpa);
                break;
            }
            case 2: {
                int id, year;
                double gpa;
                string name, prog;
                cout << "Enter Student ID: "; cin >> id;
                cout << "Enter Full Name: "; cin.ignore(); getline(cin, name);
                cout << "Enter Programme: "; getline(cin, prog);
                cout << "Enter Year of Study: "; cin >> year;
                cout << "Enter CGPA: "; cin >> gpa;
                insertAtEnd(head, id, name, prog, year, gpa);
                break;
            }
            case 3: {
                int id, year, pos;
                double gpa;
                string name, prog;
                cout << "Enter position to insert at: "; cin >> pos;
                cout << "Enter Student ID: "; cin >> id;
                cout << "Enter Full Name: "; cin.ignore(); getline(cin, name);
                cout << "Enter Programme: "; getline(cin, prog);
                cout << "Enter Year of Study: "; cin >> year;
                cout << "Enter CGPA: "; cin >> gpa;
                insertAtPosition(head, pos, id, name, prog, year, gpa);
                break;
            }
            case 4:
                cout << "\n--- All Student Records ---\n";
                traverse(head);
                break;
            case 5: {
                int id;
                cout << "Enter Student ID to delete: "; cin >> id;
                deleteById(head, id);
                break;
            }
            case 6: {
                string name;
                cout << "Enter Full Name to search: "; cin.ignore(); getline(cin, name);
                searchByName(head, name);
                break;
            }
            case 7:
                countRecords(head);
                break;
            case 8:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please select a number between 1 and 8.\n";
        }
 
    } while (choice != 8);

    
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
}


