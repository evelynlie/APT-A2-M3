#include "Command.h"
#include "DoublyLinkedList.h"
#include "Helper.h"

void AddFoodCommand::addFoodItem(DoublyLinkedList &foodList) const {
    std::string lastID = foodList.generateFoodID();
    std::string name;
    std::string description;
    std::string price;
    std::cout << "This new meal item will have the Item id of " << lastID << std::endl;
    // Prompt user for food name
    bool valid_name = false;
    while (!valid_name) {
        std::cout << "Enter the item name: ";
        name = readInput();
        if (name.size() > NAMELEN) { // display error message if exceed expected name length, ask for a valid name
            std::cout << "Invalid input. Please enter a valid name with a maximum length of " << NAMELEN << " characters.\n" << std::endl;
        }
        else if (name.size() == 0) {
            return; // return to main menu if hitting enter on an empty line
        }
        else {
            //Capitalise the first letter of the new food name so that the list stays in alphabetical order
            name[0] = toupper(name[0]);
            valid_name = true;
        }
    }

    // prompt user for food description
    bool valid_description = false;
    while (!valid_description) {
        std::cout << "Enter the item description: ";
        description = readInput();
        if (description.size() > DESCLEN) { // display error message if exceed expected description length, ask for a valid description
            std::cout << "Invalid input. Please enter a valid description with a maximum length of " << DESCLEN << " characters.\n" << std::endl;
        }
        else if (description.size() == 0) {
            return; // return to main menu if hitting enter on an empty line
        }
        else {
            valid_description = true;
        }
    }

    // prompt user for food price
    bool valid_price = false;
    while (!valid_price) {
        std::cout << "Enter the price for this item (in dollars and cents): ";
        price = readInput();
        // return to main menu if hitting enter on an empty line
        if (price.size() == 0) {
            return;
        }
        // Check if input has a decimal point and consists of digits before and after it
        size_t decimalPointPos = price.find('.');
        if (decimalPointPos != std::string::npos &&
            decimalPointPos > 0 && // Decimal point should not be at the beginning
            decimalPointPos < price.length() - 1 && // Decimal point should not be at the end
            std::all_of(price.begin(), price.begin() + decimalPointPos, ::isdigit) && // Digits before and after decimal point
            std::all_of(price.begin() + decimalPointPos + 1, price.end(), ::isdigit) &&
            price.substr(price.find('.') + 1).length() == 2 && 
            std::stod(price) > 0.00 && // Price is should be greater than 0.00
            isDivisibleByFiveCents(price)) {  // Price should be divisible by 5 cents so that the vending machine can give change

            valid_price = true;
        }

        // If input is invalid, clear input buffer and prompt again
        if (!valid_price) {
            std::cout << "Invalid input. Please enter a valid price (in cents) with a decimal point and digits only.\n" << std::endl;
        }
    }
    std::cout << "\nThis item \"" << name << " - " << description << "\" has now been added to the food menu" << std::endl;

    // Add food item to the foodList using given inputs
    FoodItem* foodItem = new FoodItem;
    foodItem->id = lastID;
    foodItem->name = name;
    foodItem->description = description;
    foodItem->price.dollars = std::stoi(price.substr(0, price.find('.')));
    foodItem->price.cents = std::stoi(price.substr(price.find('.') + 1));
    foodItem->on_hand = DEFAULT_FOOD_STOCK_LEVEL;

    // Create a new node and add it to the linked list
    Node* node = new Node;
    node->data = foodItem;
    foodList.addNode(node);
}