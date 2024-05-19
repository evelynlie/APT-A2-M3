#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "LinkedList.h"
#include "Node.h"
#include <iostream>
#include <iomanip>

class DoublyLinkedList : public LinkedList 
{
public:
    // the end of the list
    Node* tail;
    
    DoublyLinkedList();
    ~DoublyLinkedList();

    void addNode(Node* newNode);
    void removeNode(Node* aNode);
    void clear();
    Node* getNode(std::string id) const;
    std::string generateFoodID() const;
};

#endif  // DOUBLYLINKEDLIST_H