#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <iostream>
#include <iomanip>

class LinkedList
{
public:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
    LinkedList();
    virtual ~LinkedList();

    virtual void addNode(Node *newNode);
    virtual void removeNode(Node *node);
    virtual void clear();
    virtual Node* getNode(std::string id) const;
    virtual std::string generateFoodID() const;

    void printList() const;
    void writeAllFoods(std::ostream& food_file) const;
};

#endif  // LINKEDLIST_H