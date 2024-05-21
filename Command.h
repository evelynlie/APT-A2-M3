#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <iomanip>
#include "DoublyLinkedList.h"

class Command
{
public:
    Command() {}
    virtual ~Command() {}
    virtual void execute(DoublyLinkedList& foodList) const = 0;
};

class DisplayMealCommand : public Command {
public:
    void execute(DoublyLinkedList& foodList) const {
        foodList.printList();
    };
};

class AddFoodCommand : public Command {
public:
    void execute(DoublyLinkedList& foodList) const {
        addFoodItem(foodList);
    }

private:
    void addFoodItem(DoublyLinkedList& foodList) const;  
};

class RemoveFoodCommand : public Command {
public:
    void execute(DoublyLinkedList& foodList) const {
        removeFoodItem(foodList);
    }

private:
    void removeFoodItem(DoublyLinkedList& foodList) const;  
};

#endif  // COMMAND_H