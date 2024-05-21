#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "LinkedList.h"
#include "Node.h"
#include <iostream>
#include <iomanip>

class DoublyLinkedList : public LinkedList 
{
public:
    // The end of the list
    Node* tail;
    
    // Constructor and Destructor
    DoublyLinkedList();
    ~DoublyLinkedList();

    // Add node to the doubly linked list in ascending order based on the food item name
    void addNode(Node* newNode);

    // Remove node from the doubly linked list
    void removeNode(Node* aNode);

    // Clear the doubly linked list
    void clear();

    // Print the doubly linked list to the console
    Node* getNode(std::string id) const;

    // Generate a unique foodID
    std::string generateFoodID() const;
};

#endif  // DOUBLYLINKEDLIST_H