#include "Helper.h"
#include "Coin.h"
#include <iostream>
#include <cstdlib>

// Helper method to read and return user input in string
std::string readInput(bool main, bool helpMessage, const std::string question) {
    bool valid_input = false;
    std::string input;

    // If help message is enabled
    if (helpMessage) {
        while (!valid_input){
            input = "";
            // if Ctril+D (end of file) is not pressed
            if(!std::cin.eof()) {
                std::getline(std::cin, input);
            }    
            else { // If the user presses Ctrl+D, exit the program     
                std::cerr << "\nGoodbye!" << std::endl;
                exit(EXIT_FAILURE);
            }

            if (main) {
                // If the input is "help" and it's in the main menu, print message
                if (input == "help") {
                    std::cout << "Enter the number to execute the corresponding function above or Ctrl+D to terminate the program entirely, similar to \"7\".\n" << std::endl;
                    std::cout << HELP_MAIN_MENU;
                }
                else {
                    valid_input = true;
                }
            }
            else {
                // If the input is "help" and it's not in the main menu, print message
                if (input == "help") {
                    if (question.find("error message") == std::string::npos){
                        std::cout << "Enter \"Enter\" to return to the main menu or Ctrl+D to terminate the program entirely.\n" << std::endl;
                    }
                    else {
                        std::cout << "Enter Ctrl+D to terminate the program entirely or \"Y\" or \"N\" to answer the question.\n" << std::endl;
                    }
                    std::cout << question;
                }
                else {
                    valid_input = true;
                }
            }
        }
    }
    // If help message is disabled
    else {
        input = "";
        // if Ctril+D (end of file) is not pressed
        if(!std::cin.eof()) {
            std::getline(std::cin, input);
        }    
        else { // If the user presses Ctrl+D, exit the program     
            std::cerr << "\nGoodbye!" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    return input;
}

// Helper method to check if the price is divisible by 5 cents
bool isDivisibleByFiveCents(const std::string& price_str) {
    double price = std::stod(price_str); // Convert string to double
    int price_cents = static_cast<int>(std::round(price * 100)); // Convert to cents
    return price_cents % 5 == 0; // Check if divisible by 5 cents
}

// Helper method to validate if the given string is a number
bool isNumber(std::string s) {
    if (s.empty()){
        return false;
    }
    
    // Create an iterator to traverse the string from the beginning
    std::string::const_iterator it = s.begin();

    char dot = '.';    
    int nb_dots = 0;

    // Loop through each character in the string
    while (it != s.end()) {
        if (*it == dot) {
            nb_dots++;
            // If more than one dot is found, it's not a valid number, return false
            if (nb_dots > 1) {
                return false;
            }
        } else if (!isdigit(*it)) {
            // If the current character is not a digit, return false
            return false;
        }
        // Move to the next character in the string
        ++it;
    }

    return s[0] != dot;
}

// Helper method for sorting coins
bool compareCoins(const Coin& coin1, const Coin& coin2) {
    return coin1.denom < coin2.denom; // Sort by denomination
}