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
    Node* returnNode = nullptr;

    // If the node is the tail
    if (tail->data->id == id) {
        return tail;
    }

    // If the node is the head
    if (head->data->id == id) {
        return head;
    }

    // If id is empty, return nullptr
    if (!id.empty()) {
        // Extract the numeric part of the ID
        int idNumber = std::stoi(id.substr(1));

        // Get the middle index of the list
        int middleIndex = count / 2;

        // If the id number is less than the middle index, start from the head
        if (idNumber < middleIndex) {
            Node* current = head;
            // Traverse the linked list until we found the node matched the id
            while(current != nullptr && returnNode == nullptr){
                // if node is found, set returnNode to point to the node
                if (current->data->id == id) {
                    returnNode = current;
                }
                current = current->next;
            }
        } else { // If the id number is greater than the middle index, start from the tail
            Node* current = tail;
            // Traverse the linked list until we found the node matched the id
            while(current != nullptr && returnNode == nullptr){
                // if node is found, set returnNode to point to the node
                if (current->data->id == id) {
                    returnNode = current;
                }
                current = current->prev;
            }
        }
    }

    return returnNode;
}

// Generate the new food item ID
std::string DoublyLinkedList::generateFoodID() const {
    // Check if the list is empty
    if (!tail) {
        return "F0001";
    }

    Node* current = head;
    Node* lastIDNode = head;

    //Since the list is sorted alphabetically, the last node in the list won't necessarily have the latest ID.
    //So, we must keep track of the node with the latest ID rather than assuming the last node has it.
    while (current != nullptr) {

        if(current->data->id > lastIDNode->data->id){
            lastIDNode = current;
        }
        current = current->next;
    }

    // Convert the last food item id to number, which is the last 4 characters of the id
    std::string lastID = lastIDNode->data->id;
    std::string last4Chars = lastID.substr(lastID.length() - 4);
    int lastIDNumber = std::stoi(last4Chars) + 1;

    // Concat the lastIDNumber to the string "F" and add 0 until the length of the id is 5
    std::stringstream newID;
    newID << 'F' << std::setw(4) << std::setfill('0') << lastIDNumber;
    return newID.str();
}