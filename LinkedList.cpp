#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;
   count = 0;
}

LinkedList::~LinkedList() {
   clear();
}

// Add node to the linked list in ascending order based on the food item name
void LinkedList::addNode(Node *newNode) {
    // TODO
    if (head == nullptr || newNode->data->name < head->data->name) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        // Traverse the list until we find the correct position to insert the new node
        // While loop will stop when we reach the end of the list or the new node name is less than the current node name
        while (current->next != nullptr && current->next->data->name < newNode->data->name) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    count++;
}

// Remove node from the linked list
void LinkedList::removeNode(Node *node) {
    // TODO
    if (head == node) {
        head = head->next;
        delete node;
    } else {
        Node* temp = head;
        // Traverse the list until we found the node to be deleted
        while (temp->next != node) {
            temp = temp->next;
        }
        // link the previous node to the next node
        temp->next = node->next;
        // remove node from linked list
        delete node;
    }
    count--;
}

// Get node based on given food id
Node* LinkedList::getNode(std::string id) const {
    Node* returnNode = nullptr;

    Node* current = head;
    // Traverse the linked list until we found the node matched the id
    while(current != nullptr && returnNode == nullptr){
        // if node is found, set returnNode to point to the node
        if (current->data->id == id) {
            returnNode = current;
        }
        current = current->next;
    }

    return returnNode;
}

// Function to clear every item in linked list
void LinkedList::clear(){
    Node* current = head;
    Node* next_node = nullptr;
    
    // Traverse all node in the linked list
    while (current != nullptr) {
        // get the next node
        next_node = current->next;
        // delete current node from linked list
        removeNode(current);
        // set current node to next node
        current = next_node;
    }
}

// Display food menu
void LinkedList::printList() const {
    std::cout << "\nFood Menu" << std::endl;
    std::cout << std::string(9, '-') << std::endl;
    std::cout << std::left << std::setw(5) << "ID" << "|";
    std::cout << std::left << std::setw(50) << "Name" << "|";
    std::cout << std::left << std::setw(9) << "Price" << std::endl;
    std::cout << std::string(66, '-') << std::endl;

    Node* current = head;
    // Traverse all node in the linked list
    while (current != nullptr) {
        // Display the fooditem details to console
        current->printNode();
        // Iterate to next node
        current = current->next;
    }
}

// Generate the new food item id
std::string LinkedList::generateFoodID() const {
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
    std::string newID;
    if (lastIDNumber < 10) {
        newID = "F000" + std::to_string(lastIDNumber);
    } else if (lastIDNumber < 100) {
        newID = "F00" + std::to_string(lastIDNumber);
    } else if (lastIDNumber < 1000) {
        newID = "F0" + std::to_string(lastIDNumber);
    }
    return newID;
}

// Write the food data into foods.dat file
void LinkedList::writeAllFoods(std::ostream& food_file) const {
    Node* current = head;
    // Traverse all node in the linked list
    while (current != nullptr) {
        // Write the fooditem details into foods.dat
        current->writeNode(food_file);
        // Iterate to next node
        current = current->next;
    }
 }