#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <iomanip>
#include "DoublyLinkedList.h"
#include "Helper.h"
#include "Coin.h"

// Base class for all commands
class Command
{
protected:
    bool betterMessage;
public:
    // Constructor and Destructor
    Command(bool betterMessage) : betterMessage(betterMessage) {}
    virtual ~Command() {}
    
    // Execute the command based on the given parameters
    virtual void execute(std::vector<Coin>& coins) const {};
    virtual void execute(DoublyLinkedList& foodList) const {};
    virtual void execute(char* food_file, DoublyLinkedList& foodList) const {};
    virtual void execute(DoublyLinkedList& foodList, std::vector<Coin>& coins) const {};
    virtual std::vector<Coin> execute(char* coin_file) const { return std::vector<Coin>(); };
    virtual void execute(char* food_file, char* coin_file, DoublyLinkedList& foodList, std::vector<Coin>& coins) const {};
};

// Display the meal items
class DisplayMealCommand : public Command {
public:
    DisplayMealCommand(bool betterMessage) : Command(betterMessage) {}

    void execute(DoublyLinkedList& foodList) const {
        foodList.printList();
    };
};

// Add a new food item
class AddFoodCommand : public Command {
public:
    AddFoodCommand(bool betterMessage) : Command(betterMessage) {}

    void execute(DoublyLinkedList& foodList) const {
        addFoodItem(foodList);
    }

private:
    void addFoodItem(DoublyLinkedList& foodList) const;  
};

// Remove a food item
class RemoveFoodCommand : public Command {
public:
    RemoveFoodCommand(bool betterMessage) : Command(betterMessage) {}

    void execute(DoublyLinkedList& foodList) const {
        removeFoodItem(foodList);
    }

private:
    void removeFoodItem(DoublyLinkedList& foodList) const;  
};

// Purchase a meal
class PurchaseMealCommand : public Command {
public:
    PurchaseMealCommand(bool betterMessage) : Command(betterMessage) {}

    void execute(DoublyLinkedList& foodList, std::vector<Coin>& coins) const {
        purchaseMeal(foodList, coins);
    }

private:
    void purchaseMeal(DoublyLinkedList& foodList, std::vector<Coin> &coins) const;  
};

// Display the balance
class DisplayBalanceCommand : public Command {
public:
    DisplayBalanceCommand(bool betterMessage) : Command(betterMessage) {}

    void execute(std::vector<Coin>& coins) const {
        displayBalance(coins);
    }

private:
    void displayBalance(std::vector<Coin>& coins) const;  
};

// Save the data
class SaveCommand : public Command {
public:
    SaveCommand(bool betterMessage) : Command(betterMessage) {}

    void execute(char* food_file, char* coin_file, DoublyLinkedList& foodList, std::vector<Coin>& coins) const {
        saveFoodData(food_file, foodList);
        saveCoinData(coin_file, coins);
    }

private:
    void saveFoodData(char* food_file, DoublyLinkedList& foodList) const;
    void saveCoinData(char* coin_file, std::vector<Coin>& coins) const;
};

// Load the data
class LoadCommand : public Command {
public:
    LoadCommand(bool betterMessage) : Command(betterMessage) {}

    void execute(char* food_file, DoublyLinkedList& foodList) const {
        loadFoodData(food_file, foodList);
    }

    std::vector<Coin> execute(char* coin_file) const { 
        return Coin::loadCoinData(coin_file); 
    }

private:
    void loadFoodData(char* food_file, DoublyLinkedList& foodList) const;
};

// Remove food stock
class RemoveStockCommand : public Command {
public:
    RemoveStockCommand(bool betterMessage) : Command(betterMessage) {}

    void execute(DoublyLinkedList& foodList) const {
       removeStock(foodList);
    }

private:
    void removeStock(DoublyLinkedList& foodList) const;
};

#endif  // COMMAND_H