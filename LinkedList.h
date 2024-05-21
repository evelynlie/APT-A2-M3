#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <iostream>
#include <iomanip>

class LinkedList
{
public:
    // The beginning of the list
    Node* head;
  
    unsigned count;
    LinkedList();
    virtual ~LinkedList();
    
    // Add node to the linked list in ascending order based on the food item name
    virtual void addNode(Node *newNode);

    // Remove node from the linked list
    virtual void removeNode(Node *node);

    // Clear the linked list
    virtual void clear();

    // Get node based on given foodID
    virtual Node* getNode(std::string id) const;

    // Generate a unique foodID
    virtual std::string generateFoodID() const;

    // Print the linked list to the console
    void printList() const;

    // Write all food items to the foods.dat file
    void writeAllFoods(std::ostream& food_file) const;
};

#endif  // LINKEDLIST_H