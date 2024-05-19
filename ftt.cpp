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
#include <map>
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

    // Check if the number of arguments is correct (2 arguments)
    if (argc != 3) {
        std::cerr << "To run the program: " << argv[0] << " <food_file> <coin_file>"  << std::endl;
        return EXIT_FAILURE;
    }

    // Load Food and Coin Data
    DoublyLinkedList* foodList = new DoublyLinkedList();
    loadFoodData(argv[1], *foodList);

    try {
        coins = Coin::loadCoinData(argv[2]);
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

        // Process the selected option
        if (option == 1) {
            // Display Meal Options
            DisplayMealCommand displayCommand;
            displayCommand.execute(*foodList); // Execute the command
        } else if (option == 2) {
            // Purchase Meal
            purchaseMeal(*foodList, coins);
        } else if (option == 3) {
            // Save and Exit
            saveFoodData(argv[1], *foodList);
            saveCoinData(argv[2], coins);
            exitProgram = true;
        } else if (option == 4) {
            // Add Food
            AddFoodCommand addCommand;
            addCommand.execute(*foodList);
        } else if (option == 5) {
            // Remove Food
            removeFoodItem(*foodList);
        } else if (option == 6) {
            // Display Balance
            printBalance(coins);
        } else if (option == 7) {
            // Abort Program and free memory
            exitProgram = true;
        }
        //This is for a debug method to remove food from stock and test purchase meal
        else if (option == 999) {
            removeStock(*foodList);
        }

        std::cout << std::endl;
    }

    // Free memory
    delete foodList;
    foodList = nullptr;
    
    return EXIT_SUCCESS;
}

// Function to load food data into linked list based on provided .dat file
void loadFoodData(const char *food_file, DoublyLinkedList &foodList) {
    // Open the file to read
    std::ifstream file(food_file);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << food_file << std::endl;
        exit(EXIT_FAILURE);
    }

    // Read the file line by line
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        FoodItem* foodItem = new FoodItem;

        // Count how many value are in the line separated by '|', must be 3
        int count = 0;
        for (char c : line) {
            if (c == '|') {
                count++;
            }
        }
        if (count != 3) {
            std::cerr << "Error: Incorrect number of values in " << food_file << std::endl;
            exit(EXIT_FAILURE);
        }

        // Extracting ID
        std::getline(iss, token, '|');
        // If the ID is not in the correct format (Fxxxx), exit the program
        if (token.length() != IDLEN || token.substr(0, 1) != "F"){
            // Error: ID format is incorrect
            std::cerr << "Error: ID format is incorrect" << std::endl;
            exit(EXIT_FAILURE);
        }
        foodItem->id = token;

        // Extracting Name
        std::getline(iss, token, '|');
        if (token.length() > NAMELEN) {
            // Error: Name is too long
            std::cerr << "Error: Name is too long" << std::endl;
            exit(EXIT_FAILURE);
        }
        foodItem->name = token;

        // Extracting Description
        std::getline(iss, token, '|');
        if (token.length() > DESCLEN) {
            // Error: Description is too long
            std::cerr << "Error: Description is too long" << std::endl;
            exit(EXIT_FAILURE);
        }
        foodItem->description = token;

        //Set the food stock to the default level
        foodItem->on_hand = DEFAULT_FOOD_STOCK_LEVEL;

        // Extracting Price into dollars and cents
        std::getline(iss, token, '|');
        size_t dotPosition = token.find('.'); // Find the position of the dot
        if (dotPosition == std::string::npos || token.substr(dotPosition + 1).length() != 2) { // If the dot is not found or there are not 2 digits after the dot
            // Error: Price format is incorrect
            std::cerr << "Error: Price format is incorrect" << std::endl;
            exit(EXIT_FAILURE);
        }
        std::string string_dollars = token.substr(0, dotPosition);
        std::string string_cents = token.substr(dotPosition + 1);
        foodItem->price.dollars = std::stoi(string_dollars);
        foodItem->price.cents = std::stoi(string_cents);

        // Create a new node and add it to the linked list
        Node* node = new Node;
        node->data = foodItem;
        foodList.addNode(node);
    }
    file.close();
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
}

// Print Balance
void printBalance(const std::vector<Coin>& coins) {
    double totalBalance = 0;

    // Calculate total balance
    for (const Coin& coin : coins) {
        totalBalance += coin.count * coin.denom / 100.0;       
    }

    // Find the length of the highest value to format the output
    int maxValueLength = std::to_string(totalBalance).length() + 2;

    // Display balance to console
    std::cout << "\nBalance Summary" << std::endl;
    std::cout << std::string(15, '-') << std::endl;
    std::cout << "Denom  | Quantity | Value"<< std::endl;
    std::cout << std::string(15 + maxValueLength, '-') << std::endl;

    for (const Coin& coin : coins) {
        std::cout << std::left << std::setw(7) << coin.denom << "| ";
        std::cout << std::left << std::setw(9) << coin.count << "|";
        std::cout << std::right << "$" << std::setw(maxValueLength - 5) << std::fixed << std::setprecision(2) << (coin.count * coin.denom / 100.0) << std::endl;
    }

    // Round the total balance to the nearest dollar
    int roundedTotalBalance = static_cast<int>(totalBalance);

    std::cout << std::string(15 + maxValueLength, '-') << std::endl;
    std::cout << std::right << std::setw(21) << "$ " << std::fixed << std::setprecision(2) << roundedTotalBalance << ".00" << std::endl;
}

// Remove the food item based on input food id
void removeFoodItem(DoublyLinkedList &foodList) {
    bool valid_id = false;
    while(!valid_id) {
        std::cout << "Enter the food id of the food to remove from the menu: ";
        std::string string_id = readInput();

        // return to main menu if hitting enter on an empty line
        if (string_id.size() == 0) {
            return;
        }
        
        // get the food item (node) based on input id
        Node* toRemove = foodList.getNode(string_id);

        // check if the returned Node pointer contain the Node (id found)
        if (toRemove != nullptr) {
            // Display item removed message on console
            std::cout << "\"" << toRemove->data->id << " – " 
                << toRemove->data->description << "\"" 
                << " has been removed from the system." << std::endl;
            // remove the food item from the menu
            foodList.removeNode(toRemove);
            valid_id = true;
        }
        // display error message if food id not found, ask for a valid id
        else{
            std::cout << "Invalid input. Please enter a valid food id.\n" << std::endl;
        }
    }
}

// Purchase the food item
void purchaseMeal(DoublyLinkedList &foodList, std::vector<Coin> &coins) {
    /*Instead of modifying the coins vector directly, we create a copy.
    Upon a successful purchase, update the original with the copy
    Otherwise, such as a case of unsuccessful refund, we don't modify the original coins vector at all*/
    std::vector<Coin> coinCopy = coins;

    bool cancel = false;    //Has the user cancelled their purchase?
    bool pickedFood = false;//Has the user selected a valid food item?
    Node* food = nullptr;   //Pointer to the food node in the linked list
    int amountOwed = 0;     //How much the user has to pay

    std::string input;  //Variable that accepts input

    std::cout << "Purchase Meal" << std::endl;
    std::cout << "-------------" << std::endl;

    while(!pickedFood && !cancel){
        // prompt user for food id
        std::cout << "Please enter the ID of the food you wish to purchase(or leave empty to cancel):" << std::endl;
        input = readInput();
        
        // get the food item (node) based on input id
        food = foodList.getNode(input);
        
        // check if the returned Node pointer contain the Node (id found)
        if(food != nullptr){

            if(food->data->on_hand > 0){
                //We have the food in stock, so set the amount the user will owe, as well as the description
                amountOwed = food->data->price.dollars * 100 + food->data->price.cents;

                std::cout << "You have selected \"" << food->data->name << " - " << food->data->description << "\". This will cost you $" <<
                amountOwed/100 << "." << std::setw(2) << std::setfill('0') << amountOwed%100 << "." << std::setfill(' ') << std::endl;
                pickedFood = true;
            }
            else{
                //User entered a valid ID, but the food isn't in stock.
                std::cout << "Sorry, this item isn't available at the moment." << std::endl;
            }
        }
        else if(input == ""){
            //User left empty input, canceling their order
            cancel = true;
        }
        else {
            //User entered invalid food ID.
            std::cout << "Invalid input. The ID entered doesn't correspond to any item on our menu." << std::endl;
        }
    }

    //Make sure the user hasn't canceled their order
    if(!cancel){
        std::cout << "Please hand over the money - type in the value of each note/coin in cents." << std::endl;
        std::cout << "Please enter Ctrl+D or enter on a new line to cancel this purchase." << std::endl;

        //Current coin the user is entering
        int coinValue;

        //Map to keep track of the coins the user has entered - key is denomination, value is counter
        std::map<int, int> userCoins;

        while(!cancel && amountOwed > 0){

            std::cout << "You still need to give us $" << amountOwed/100 << "." << std::setw(2) << std::setfill('0') << amountOwed%100 << std::setfill(' ') << ": ";
            input = readInput();

            if(input != ""){
                if(isNumber(input)){
                    coinValue = std::stoi(input);

                    //This check could be its own function, makes sure the denomination is valid
                    if(coinValue == FIVE_CENTS || coinValue == TEN_CENTS || coinValue == TWENTY_CENTS || coinValue == FIFTY_CENTS ||
                    coinValue == ONE_DOLLAR || coinValue == TWO_DOLLARS || coinValue == FIVE_DOLLARS || coinValue == TEN_DOLLARS ||
                    coinValue == TWENTY_DOLLARS || coinValue == FIFTY_DOLLARS)
                    {
                        //Denomination is valid, subtract from the amount owed and add/increment map value;
                        amountOwed -= coinValue;
                        
                        if(userCoins.count(coinValue) > 0){
                            userCoins[coinValue]++;
                        }
                        else {
                            //When we add a new coin type to the map, start as 1 since the user has already entered it
                            userCoins[coinValue] = 1;
                        }
                    }
                    else{
                        std::cout << "Error: invalid denomination encountered." << std::endl;
                    }
                }
                else{
                    std::cout << "Error: the coin/note value must be a number." << std::endl;
                }
            }
            //Empty input
            else{
                cancel = true;
            }
        }

        //We need another cancellation check before handling the changes to the total balance
        if(!cancel){

            //Add the user-inserted money to the total balance
            for (Coin& coin : coinCopy) {
                if(userCoins.count(coin.denom) > 0){
                    //remember that userCoins is a map where denomination is the key, and the value is the count.
                    coin.addCount(userCoins[coin.denom]);
                }
            }

            //amountOwed would be negative (or 0), so we need to flip the sign.
            //In a way, amountOwed now refers to the amount the vending machine owes the customer rather than the other way around.
            amountOwed *= -1;

            //Since the coins are ordered in ascending order, we need to start at the end of the coin vector
            int i = coinCopy.size() - 1;
            
            //This vector will store all the change the machine gives back to the user.
            std::vector<int> change;

            //Refund loop - note that if we have given the exact money, amountOwed == 0, so we won't go in this loop at all.
            while(amountOwed != 0 && i >= 0){
                //Give back the largest coin/note possible until we need to move to a smaller one
                //or we run out of said coin.
                while(amountOwed >= coinCopy[i].denom && coinCopy[i].count > 0){
                    //We found a valid coin to refund, so decrement the counter in the list,
                    //subtract the coin from the amount owed, and add the coin to the change vector
                    amountOwed -= coinCopy[i].denom;
                    change.push_back(coinCopy[i].denom);
                    coinCopy[i].count--;
                }
                i--;
            }

            if(amountOwed == 0){
                //Purchase successful, print out the change refunded if there is any
                if(change.size() > 0){
                    std::cout << "Your change is: ";

                    for(unsigned i = 0; i < change.size(); i++){
                        if(change[i] >= 100){
                            //Denomination is greater than or equal to 100, so it's a dollar
                            std::cout << "$" << change[i] / 100 << " ";
                        }
                        else {
                            //Denomination is less than 100, so it's cents
                            std::cout << change[i] << "c ";
                        }
                    }
                    std::cout << std::endl;
                }

                //Update the food node and coin vector in the system accordingly.
                food->data->on_hand--;
                coins = coinCopy;
            }
            else{
                std::cout << "Error: The system cannot refund the exact change. Purchase cancelled." << std::endl;
            }
        }

    }
}

// function to save food data into foods.dat
void saveFoodData(const char *food_file, DoublyLinkedList &foodList) {
    // open the file to write
    std::ofstream file(food_file);

    // if file does not exist, display error message
    if (!file) {
        std::cerr << "Error: could not open file " << food_file << std::endl;
        exit(EXIT_FAILURE);
    }

    // write the food item into foods.dat
    foodList.writeAllFoods(file);

    // Close the file
    file.close();
}

// function to save coins data into coins.dat
void saveCoinData(const char *coin_file, std::vector<Coin>& coins) {
    // open the file to write
    std::ofstream file(coin_file);

    // if file does not exist, display error message
    if (!file) {
        std::cerr << "Error: could not open file " << coin_file << std::endl;
        exit(EXIT_FAILURE);
    }

    // write the coin details into coins.dat
    for(const Coin& coin : coins) {
        file << coin.denom << "," 
            << coin.count << std::endl;
    }

    // Close the file
    file.close();
}

// helper method to validate if the given string is a number
// Adapted from Assignment 1 Start Code
bool isNumber(std::string s) {
    std::string::const_iterator it = s.begin();
    char dot = '.';
    int nb_dots = 0;
    bool exit = false;
    while (it != s.end() && exit == false) 
    {
        if (*it == dot)
        {
            nb_dots++;
            if (nb_dots>1)
            {
                exit = true;
            }
        }   
        else if (!isdigit(*it))
        {
            exit = true;
        } 

        ++it;
    }
    return !s.empty() && s[0] != dot && it == s.end();
}

void removeStock(DoublyLinkedList &foodList){
    //Debug function that reduces a meal's stock quantity to 0.
    //Used to test purchasing when a meal is out of stock.

    std::string input;
    Node* food = nullptr;
    bool cancel = false;

    std::cout << "This is a debug function that removes all stocks of a meal." << std::endl;

    while(food == nullptr && !cancel){
        std::cout << "Enter meal ID, or leave blank to cancel:" << std::endl;
        input = readInput();

        food = foodList.getNode(input);

        if(input == ""){
            cancel = true;
        }
    }

    if(!cancel){
        food->data->on_hand = 0;
        std::cout << "Stock for meal with ID " << food->data->id << " reduced to 0." << std::endl;
    }
    else {
        std::cout << "Remove stock cancelled." << std::endl;
    }

}

