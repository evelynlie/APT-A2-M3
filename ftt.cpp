#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <limits>
#include <algorithm>
#include <random>
#include "DoublyLinkedList.h"
#include "Coin.h"
#include "Command.h"
#include "Helper.h"

void loadFoodData(const char *food_file, DoublyLinkedList &foodList);
void displayMainMenu();
void printBalance(const std::vector<Coin>& coins);
void removeFoodItem(DoublyLinkedList &foodList);
void saveFoodData(const char *food_file, DoublyLinkedList &foodList);
void saveCoinData(const char *coin_file, std::vector<Coin> &coins);
void purchaseMeal(DoublyLinkedList &foodList, std::vector<Coin> &coins);
std::string readInput();
bool isNumber(std::string s);
void removeStock(DoublyLinkedList &foodList);
bool isDivisibleByFiveCents(const std::string& price_str);

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv)
{
    // Validate command line arguments
    // TODO
    std::vector<Coin> coins;
    std::unique_ptr<Command> command; // unique_ptr to hold the command instance

    // Check if the number of arguments is correct (2 arguments)
    if (argc != 3) {
        std::cerr << "To run the program: " << argv[0] << " <food_file> <coin_file>"  << std::endl;
        return EXIT_FAILURE;
    }

    // Load Food and Coin Data
    DoublyLinkedList* foodList = new DoublyLinkedList();
    command = std::make_unique<LoadCommand>();
    command->execute(argv[1], *foodList);

    try {
        coins = command->execute(argv[2]);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        delete foodList;
        foodList = nullptr;
        return EXIT_FAILURE;
    }

    // Run the program
    bool exitProgram = false;
    while (!exitProgram) {
        int option = -1;
        bool valid_option = false;

        while (!valid_option) {
            // Display Main Menu
            displayMainMenu();
            std::string string_input = readInput();
            if (isNumber(string_input) == true && ((std::stoi(string_input) >= 1 && std::stoi(string_input) <= 7) || std::stoi(string_input) == 999)) {
                valid_option = true;
                option = std::stoi(string_input);
            }
            else {
                std::cout << "Invalid input. Please enter a number between 1 and 7.\n" << std::endl;
            }
        }

        // Process the selected option by assigning the appropriate command instance to the unique_ptr
        if (option == 1) {
            // Display Meal Options
            command = std::make_unique<DisplayMealCommand>(); 
        } else if (option == 2) {
            // Purchase Meal
            command = std::make_unique<PurchaseMealCommand>(); 
        } else if (option == 3) {
            // Save and Exit
            command = std::make_unique<SaveCommand>(); 
            exitProgram = true;
        } else if (option == 4) {
            // Add Food
            command = std::make_unique<AddFoodCommand>(); 
        } else if (option == 5) {
            // Remove Food
            command = std::make_unique<RemoveFoodCommand>(); 
        } else if (option == 6) {
            // Display Balance
            command = std::make_unique<DisplayBalanceCommand>(); 
        } else if (option == 7) {
            // Abort Program and free memory
            exitProgram = true;
        }
        // This is for a debug method to remove food from stock and test purchase meal
        else if (option == 999) {
            command = std::make_unique<RemoveStockCommand>();
        }

        if (command) { // If the unique_ptr holds a valid instance, execute the command based on the selected option
            if (option == 2) { // Purchase Meal command requires coins
                command->execute(*foodList, coins); 
            } 
            else if (option == 3) { // Save and Exit
                command->execute(argv[1], argv[2], *foodList, coins);
            }
            else if (option == 6) { // Display Balance
                command->execute(coins);
            }
            else {
                command->execute(*foodList); 
            }
        }

        std::cout << std::endl;
    }

    // Free memory
    delete foodList;
    foodList = nullptr;
    
    return EXIT_SUCCESS;
}

// Display main menu
void displayMainMenu(){
    std::cout<<"Main Menu: "<<std::endl;
    std::cout<<"   1. Display Meal Options "<<std::endl;
    std::cout<<"   2. Purchase Meal "<<std::endl;
    std::cout<<"   3. Save and Exit "<<std::endl;
    std::cout<<"Administrator-Only Menu: "<<std::endl;
    std::cout<<"   4. Add Food "<<std::endl;
    std::cout<<"   5. Remove Food "<<std::endl;
    std::cout<<"   6. Display Balance "<<std::endl;
    std::cout<<"   7. Abort Program "<<std::endl;
    std::cout<<"Select your option (1-7): ";
};