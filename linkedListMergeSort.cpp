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

    // Constructor to easily initialize a new student record node
    Node(int id, string name, string prog, int year, double gpa) {
        studentID = id;
        FullName = name;
        programme = prog;
        yearOfStudy = year;
        cgpa = gpa;
        next = nullptr;
    }
};

// FIX: Added '&' so changes to head actually save back to main()
void insertAtBeginning(Node*& head, int id, string name, string prog, int year, double gpa) {
    Node* newNode = new Node(id, name, prog, year, gpa);
    newNode->next = head;
    head = newNode;
    cout << "Successfully inserted at the beginning!\n";
}

// FIX: Added '&' so an empty list can successfully assign its first node
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

int main(){
    Node* head = nullptr; 
    insertAtBeginning(head, 1, "khaled", "Degree", 2026, 3.6);
    traverse(head);
    insertAtEnd(head, 2, "Muhammed", "foundation", 2026, 4.0);
    traverse(head);
    insertAtPosition(head,1, 3, "Hussein", "degree", 2026, 3.9);
    traverse(head);
    return 0;
}