#include "Helper.h"
#include <iostream>
#include <cstdlib>

// helper method to read and return user input in string
std::string readInput() {
    std::string input;
    // if Ctril+D (end of file) is not pressed
    if(!std::cin.eof()) {
        std::getline(std::cin, input);
    }    
    else{ // If the user presses Ctrl+D, exit the program     
        std::cerr << "\nGoodbye!" << std::endl;
        exit(EXIT_FAILURE);
    }
    return input;
}

// Function to check if the price is divisible by 5 cents
bool isDivisibleByFiveCents(const std::string& price_str) {
    double price = std::stod(price_str); // Convert string to double
    int price_cents = static_cast<int>(std::round(price * 100)); // Convert to cents
    return price_cents % 5 == 0; // Check if divisible by 5 cents
}