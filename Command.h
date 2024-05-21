#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <iomanip>
#include "DoublyLinkedList.h"
#include "Helper.h"
#include "Coin.h"

class Command
{
public:
    Command() {}
    virtual ~Command() {}
    virtual void execute(std::vector<Coin>& coins) const {};
    virtual void execute(DoublyLinkedList& foodList) const {};
    virtual void execute(char* food_file, DoublyLinkedList& foodList) const {};
    virtual void execute(DoublyLinkedList& foodList, std::vector<Coin>& coins) const {};
    virtual std::vector<Coin> execute(char* coin_file) const { return std::vector<Coin>(); };
    virtual void execute(char* food_file, char* coin_file, DoublyLinkedList& foodList, std::vector<Coin>& coins) const {};
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

class PurchaseMealCommand : public Command {
public:
    void execute(DoublyLinkedList& foodList, std::vector<Coin>& coins) const {
        purchaseMeal(foodList, coins);
    }

private:
    void purchaseMeal(DoublyLinkedList& foodList, std::vector<Coin> &coins) const;  
};

class DisplayBalanceCommand : public Command {
public:
    void execute(std::vector<Coin>& coins) const {
        displayBalance(coins);
    }

private:
    void displayBalance(std::vector<Coin>& coins) const;  
};

class SaveCommand : public Command {
public:
    void execute(char* food_file, char* coin_file, DoublyLinkedList& foodList, std::vector<Coin>& coins) const {
        saveFoodData(food_file, foodList);
        saveCoinData(coin_file, coins);
    }

private:
    void saveFoodData(char* food_file, DoublyLinkedList& foodList) const;
    void saveCoinData(char* coin_file, std::vector<Coin>& coins) const;
};

class LoadCommand : public Command {
public:
    void execute(char* food_file, DoublyLinkedList& foodList) const {
        loadFoodData(food_file, foodList);
    }

    std::vector<Coin> execute(char* coin_file) const { 
        return Coin::loadCoinData(coin_file); 
    }

private:
    void loadFoodData(char* food_file, DoublyLinkedList& foodList) const;
};

class RemoveStockCommand : public Command {
public:
    void execute(DoublyLinkedList& foodList) const {
       removeStock(foodList);
    }

private:
    void removeStock(DoublyLinkedList& foodList) const;
};

#endif  // COMMAND_H