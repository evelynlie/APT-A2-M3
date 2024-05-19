#include "DoublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList() : LinkedList() {
    tail = nullptr;
}

DoublyLinkedList::~DoublyLinkedList() {
    clear();
}

void DoublyLinkedList::addNode(Node *newNode) {
    // Check if the new node is null
    if (!newNode) return;
    
    // Check if the list is empty  
    // If the list is empty, set the head and tail to the new node
    if (!head) {
        head = tail = newNode;
    } else if (newNode->data->name < head->data->name) { // If the new node name is less than the head node name
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } else { // If the new node name is greater than the head node name
        Node* current = head;
        while (current->next && current->next->data->name < newNode->data->name) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next) {
            current->next->prev = newNode;
        } else {
            tail = newNode;
        }
        current->next = newNode;
    }

    // Increment the count of nodes in the list
    count++;
}

// Remove a node from the list
void DoublyLinkedList::removeNode(Node *node) {
    // Check if the node is null
    if (!node) return;
    
    // Check if the node is the head
    if (node == head) {
        head = node->next;
    } else {
        node->prev->next = node->next;
    }

    // Check if the node is the tail
    if (node == tail) {
        tail = node->prev;
    } else {
        node->next->prev = node->prev;
    }

    delete node;
    count--;
}

// Clear the list
void DoublyLinkedList::clear() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    count = 0;
}

// Get a node based on the given ID
Node* DoublyLinkedList::getNode(std::string id) const {
    // Extract the numeric part of the ID "F0001" -> "0001"
    int idNumber = std::stoi(id.substr(1));

    // Determine the middle index of the list
    int middleIndex = count / 2;

    // Check if the target ID number is less than or equal to the middle index
    // If id number is less than or equal to the middle index, traverse from head to middle
    if (idNumber <= middleIndex) {
        // Traverse from head to middle
        Node* current = head;
        while (current) {
            if (current->data->id == id) {
                return current;
            }
            current = current->next;
        }
    // If id number is greater than the middle index, traverse from tail to middle
    } else {
        // Traverse from tail to middle
        Node* current = tail;
        while (current) {
            if (current->data->id == id) {
                return current;
            }
            current = current->prev;
        }
    }

    return nullptr;
}

// Generate the new food item ID
std::string DoublyLinkedList::generateFoodID() const {
    // Check if the list is empty
    if (!tail) {
        return "F0001";
    }

    // Get the last ID from the tail node
    std::string lastID = tail->data->id;

    // Extract the numeric part of the ID, which is the last 4 characters
    std::string last4Chars = lastID.substr(lastID.length() - 4);
    int lastIDNumber = std::stoi(last4Chars) + 1;

    // Create the new ID by incrementing the last ID number and formatting it correctly
    std::string newID = "F" + std::string(4 - std::to_string(lastIDNumber).length(), '0') + std::to_string(lastIDNumber);

    return newID;
}