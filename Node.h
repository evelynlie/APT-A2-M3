#ifndef NODE_H
#define NODE_H
#include <string> 
#include "Coin.h"
#include <iostream>
#include <iomanip>


//The length of the id string not counting the nul terminator
#define IDLEN 5

//The maximum length of a food item name not counting the nul terminator
#define NAMELEN 40

//The maximum length of a food item description not counting the nul terminator.
#define DESCLEN 255

//The default coin level to reset the coins to on request
#define DEFAULT_COIN_COUNT 20

//The possible default food stock level that all new stock should start at and that we should reset to on restock
#define DEFAULT_FOOD_STOCK_LEVEL 20

//The number of denominations of currency available in the system 
#define NUM_DENOMS 8

/**
 * a structure to represent a price. One of the problems with the floating
 * point formats in C++ like float and double is that they have minor issues
 * of inaccuracy due to rounding. In the case of currency this really is
 * not acceptable so we introduce our own type to keep track of currency.
 **/
class Price
{
public:
    // The dollar value, and the cents value for some price
    unsigned dollars, cents;
};

/**
 * data structure to represent a food item within the system
 **/
class FoodItem
{
public:
    // The unique id for this food item
    std::string id;

    // The name of this food item
    std::string name;
    
    // The description of this food item   
    std::string description;
    
    // The price of this food item
    Price price;
    
    // How many of this food item do we have on hand? 
    unsigned on_hand;    
};

/**
 * the node that holds the data about a food item stored in memory
 **/
class Node
{
public:
    Node();
    ~Node();
    
    // Pointer to the data held for the node 
    FoodItem* data;

    // Pointer to the next node in the list 
    Node* next;

    // Pointer to the previous node in the list
    Node* prev;

    // Display food item to console
    void printNode() const;

    // Write node data into foods.dat file
    void writeNode(std::ostream& food_file) const;
};

#endif // NODE_H