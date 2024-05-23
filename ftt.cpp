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
        exit(EXIT_FAILURE);
    }

    // Get input either Y or N from the user to enable help messages
    bool validMessage = false;
    bool helpMessage = false;
        while (!validMessage){
        std::string input = "";
        // Ask if the user wants to display better messages
        std::cout << "Do you want to enable \"help\" commands? (Y/N): ";
        input = readInput(false, "Do you want to enable \"help\" commands? (Y/N): ");
        if (input == "Y" || input == "y") {
            helpMessage = true;
            validMessage = true;
        }
        else if (input == "N" || input == "n") {
            validMessage = true;
        }
        else { // If the input is not Y or N, display an error message
            std::cerr << "Error: Please enter either Y or N.\n" << std::endl;
        }
    }

    // Get input either Y or N from the user to display better messages
    validMessage = false;
    bool betterMessage = false;
        while (!validMessage){
        std::string input = "";
        // Ask if the user wants to display better messages
        std::cout << "Do you want to display better error messages? (Y/N): ";
        input = readInput(false, helpMessage, "Do you want to display better error messages? (Y/N): ");
        if (input == "Y" || input == "y") {
            betterMessage = true;
            validMessage = true;
        }
        else if (input == "N" || input == "n") {
            validMessage = true;
        }
        else { // If the input is not Y or N, display an error message
            std::cerr << "Error: Please enter either Y or N.\n" << std::endl;
        }
    }

    // Load Food and Coin Data
    DoublyLinkedList* foodList = new DoublyLinkedList();
    command = std::make_unique<LoadCommand>(betterMessage, helpMessage);
    command->execute(argv[1], *foodList);

    try {
        coins = command->execute(argv[2], betterMessage);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        delete foodList;
        foodList = nullptr;
        exit(EXIT_FAILURE);
    }

    // Run the program
    bool exitProgram = false;
    while (!exitProgram) {
        int option = -1;
        bool valid_option = false;

        while (!valid_option) {
            // Display Main Menu
            if (helpMessage) {
                std::cout << HELP_MAIN_MENU;
            } else {
                std::cout << DEFAULT_MAIN_MENU;
            }
            std::string string_input = readInput(true, helpMessage);
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
            command = std::make_unique<DisplayMealCommand>(betterMessage, helpMessage); 
        } else if (option == 2) {
            // Purchase Meal
            command = std::make_unique<PurchaseMealCommand>(betterMessage, helpMessage); 
        } else if (option == 3) {
            // Save and Exit
            command = std::make_unique<SaveCommand>(betterMessage, helpMessage); 
            exitProgram = true;
        } else if (option == 4) {
            // Add Food
            command = std::make_unique<AddFoodCommand>(betterMessage, helpMessage); 
        } else if (option == 5) {
            // Remove Food
            command = std::make_unique<RemoveFoodCommand>(betterMessage, helpMessage); 
        } else if (option == 6) {
            // Display Balance
            command = std::make_unique<DisplayBalanceCommand>(betterMessage, helpMessage); 
        } else if (option == 7) {
            // Abort Program and free memory
            exitProgram = true;
        }
        // This is for a debug method to remove food from stock and test purchase meal
        else if (option == 999) {
            command = std::make_unique<RemoveStockCommand>(betterMessage, helpMessage);
        }

        if (command && option != 7) { // If the unique_ptr holds a valid instance and exitProgram is false, execute the command based on the selected option
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
    
    exit(EXIT_SUCCESS);
}