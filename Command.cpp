#include "Command.h"
#include "DoublyLinkedList.h"
#include "Helper.h"
#include "Coin.h"
#include <map>

// Function to be executed to add an item to the food menu
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
        if (name.size() > NAMELEN) { // Display error message if exceed expected name length, ask for a valid name
            std::cout << "Invalid input. Please enter a valid name with a maximum length of " << NAMELEN << " characters.\n" << std::endl;
        }
        else if (name.size() == 0) {
            return; // Return to main menu if hitting enter on an empty line
        }
        else {
            // Capitalise the first letter of the new food name so that the list stays in alphabetical order
            name[0] = toupper(name[0]);
            valid_name = true;
        }
    }

    // Prompt user for food description
    bool valid_description = false;
    while (!valid_description) {
        std::cout << "Enter the item description: ";
        description = readInput();
        if (description.size() > DESCLEN) { // display error message if exceed expected description length, ask for a valid description
            std::cout << "Invalid input. Please enter a valid description with a maximum length of " << DESCLEN << " characters.\n" << std::endl;
        }
        else if (description.size() == 0) {
            return; // Return to main menu if hitting enter on an empty line
        }
        else {
            valid_description = true;
        }
    }

    // Prompt user for food price
    bool valid_price = false;
    while (!valid_price) {
        std::cout << "Enter the price for this item (in dollars and cents): ";
        price = readInput();
        // Return to main menu if hitting enter on an empty line
        if (price.size() == 0) {
            return;
        }
        // Validate input and print specific error message if invalid
        size_t decimalPointPos = price.find('.');

        // If better message is enabled, print the error message
        if (betterMessage){
            if (decimalPointPos == std::string::npos) {
                std::cout << "Invalid input. Price should have a decimal point in between the dollar and cent.\n" << std::endl;
            }
            else if (decimalPointPos <= 0 || decimalPointPos >= price.length() - 1) {
                std::cout << "Invalid input. Price should have at least 1 digit before and must have exactly 2 digits after the decimal point.\n" << std::endl;
            }
            else if (!std::all_of(price.begin(), price.begin() + decimalPointPos, ::isdigit) || !std::all_of(price.begin() + decimalPointPos + 1, price.end(), ::isdigit)) {
                std::cout << "Invalid input. Price should have digits only before and after the decimal point.\n" << std::endl;
            }
            else if (price.substr(price.find('.') + 1).length() != 2) {
                std::cout << "Invalid input. Price should have exactly 2 digit after the decimal point.\n" << std::endl;
            }
            else if (std::stod(price) <= 0.00) {
                std::cout << "Invalid input. Price should be greater than 0.00.\n" << std::endl;
            }
            else if (!isDivisibleByFiveCents(price)) {
                std::cout << "Invalid input. Price should be divisible by 5 cents so that the vending machine can give change.\n" << std::endl;
            }
            else {
                valid_price = true;
            }
        }
        else {
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
};

// Function to print a better error message
void printBetterMessageWithFormat(const std::string &message) {
    // Print an error message
    std::cout << "Error: " << message << "\nThe correct format for an ID is \"Fxxxx\", where x is a number.\n" << std::endl;
}

// Function to be executed to remove the food item based on input foodID
void RemoveFoodCommand::removeFoodItem(DoublyLinkedList &foodList) const {
    bool foundID = false;
    while(!foundID) {
        std::cout << "Enter the food id of the food to remove from the menu: ";
        std::string string_id = readInput();

        // Return to main menu if hitting enter on an empty line
        if (string_id.size() == 0) {
            return;
        }

        bool valid_id = false;
        if (betterMessage) {
            if (string_id[0] != 'F') {
                printBetterMessageWithFormat("The ID must start with the letter \"F\".");
            } else if (string_id.size() != 5) {
                printBetterMessageWithFormat("The ID must only consist of 5 characters.");
            } else if (!isNumber(string_id.substr(1))) {
                printBetterMessageWithFormat("The last 4 characters of the ID must be a number.");
            } else {
                valid_id = true;
            }
        } else {
            valid_id = true;
        }

        if (valid_id) {
            Node* toRemove = foodList.getNode(string_id);
            if (toRemove != nullptr) {
                std::cout << "\"" << toRemove->data->id << " – " 
                        << toRemove->data->description << "\"" 
                        << " has been removed from the system." << std::endl;
                foodList.removeNode(toRemove);
                foundID = true;
            } else {
                std::cout << "Invalid input. The given foodID is not in the menu." << std::endl;
            }
        }
    }
};

// Function to be executed to purchase the food item
void PurchaseMealCommand::purchaseMeal(DoublyLinkedList &foodList, std::vector<Coin> &coins) const {
    /* Instead of modifying the coins vector directly, we create a copy.
    Upon a successful purchase, update the original with the copy
    Otherwise, such as a case of unsuccessful refund, we don't modify the original coins vector at all */
    std::vector<Coin> coinCopy = coins;

    bool cancel = false;    // Has the user cancelled their purchase?
    bool pickedFood = false;// Has the user selected a valid food item?
    Node* food = nullptr;   // Pointer to the food node in the linked list
    int amountOwed = 0;     // How much the user has to pay

    std::string input;  // Variable that accepts input

    std::cout << "Purchase Meal" << std::endl;
    std::cout << "-------------" << std::endl;

    while(!pickedFood && !cancel){
        // Prompt user for food id
        std::cout << "Please enter the ID of the food you wish to purchase (or press enter to cancel):" << std::endl;
        input = readInput();
        
        // Get the food item (node) based on input id
        food = foodList.getNode(input);
        
        // Check if the returned Node pointer contain the Node (id found)
        if(food != nullptr){

            if(food->data->on_hand > 0){
                // We have the food in stock, so set the amount the user will owe, as well as the description
                amountOwed = food->data->price.dollars * 100 + food->data->price.cents;

                std::cout << "You have selected \"" << food->data->name << " - " << food->data->description << "\". This will cost you $" <<
                amountOwed/100 << "." << std::setw(2) << std::setfill('0') << amountOwed%100 << "." << std::setfill(' ') << std::endl;
                pickedFood = true;
            }
            else{
                // User entered a valid ID, but the food isn't in stock.
                std::cout << "Sorry, this item isn't available at the moment." << std::endl;
            }
        }
        else if(input == ""){
            // User left empty input, canceling their order
            cancel = true;
        }
        else {
            //User entered invalid food ID.
            std::cout << "Invalid input. The ID entered doesn't correspond to any item on our menu." << std::endl;

            if (betterMessage){
                // User entered invalid food ID.
                if (input[0] == 'F' && input.length() == 5 ){
                    std::cout << "Invalid input. The ID entered doesn't correspond to any item on our menu.\n" << std::endl;
                }
                else { // Specify the correct format for the ID
                    printBetterMessageWithFormat("The ID entered doesn't follow the correct format.");
                }
            }
        }
    }

    // Make sure the user hasn't cancelled their order
    if (!cancel) {
        std::cout << "Please hand over the money - type in the value of each note/coin in cents." << std::endl;
        std::cout << "Please enter Ctrl+D or enter on a new line to cancel this purchase." << std::endl;

        // Current coin the user is entering
        int coinValue;

        // Map to keep track of the coins the user has entered - key is denomination, value is counter
        std::map<int, int> userCoins;

        while (!cancel && amountOwed > 0) {

            std::cout << "You still need to give us $" << amountOwed/100 << "." << std::setw(2) << std::setfill('0') << amountOwed%100 << std::setfill(' ') << ": ";
            input = readInput();

            if (input != "") {
                if (isNumber(input)) {
                    coinValue = std::stoi(input);

                    // This check could be its own function, makes sure the denomination is valid
                    if (coinValue == FIVE_CENTS || coinValue == TEN_CENTS || coinValue == TWENTY_CENTS || coinValue == FIFTY_CENTS ||
                    coinValue == ONE_DOLLAR || coinValue == TWO_DOLLARS || coinValue == FIVE_DOLLARS || coinValue == TEN_DOLLARS ||
                    coinValue == TWENTY_DOLLARS || coinValue == FIFTY_DOLLARS)
                    {
                        // Denomination is valid, subtract from the amount owed and add/increment map value;
                        amountOwed -= coinValue;
                        
                        if (userCoins.count(coinValue) > 0) {
                            userCoins[coinValue]++;
                        }
                        else {
                            // When we add a new coin type to the map, start as 1 since the user has already entered it
                            userCoins[coinValue] = 1;
                        }
                    }
                    else {
                        std::cout << "Error: invalid denomination encountered." << std::endl;
                        if (betterMessage) {
                            std::cout << "Please enter a valid denomination in cents: 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000." << std::endl;
                        }
                    }
                }
                else {
                    std::cout << "Error: the coin/note value must be a number." << std::endl;
                    if (betterMessage) {
                        std::cout << "The number must be a valid denomination in cents: 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000." << std::endl;
                    }
                }
            }
            // Empty input
            else {
                cancel = true;
            }
        }

        // We need another cancellation check before handling the changes to the total balance
        if (!cancel) {

            // Add the user-inserted money to the total balance
            for (Coin& coin : coinCopy) {
                if (userCoins.count(coin.denom) > 0) {
                    // Remember that userCoins is a map where denomination is the key, and the value is the count.
                    coin.addCount(userCoins[coin.denom]);
                }
            }

            // amountOwed would be negative (or 0), so we need to flip the sign.
            // In a way, amountOwed now refers to the amount the vending machine owes the customer rather than the other way around.
            amountOwed *= -1;

            // Since the coins are ordered in ascending order, we need to start at the end of the coin vector
            int i = coinCopy.size() - 1;
            
            // This vector will store all the change the machine gives back to the user.
            std::vector<int> change;

            // Refund loop - note that if we have given the exact money, amountOwed == 0, so we won't go in this loop at all.
            while(amountOwed != 0 && i >= 0){
                // Give back the largest coin/note possible until we need to move to a smaller one or we run out of said coin.
                while(amountOwed >= coinCopy[i].denom && coinCopy[i].count > 0){
                    // We found a valid coin to refund, so decrement the counter in the list,
                    // subtract the coin from the amount owed, and add the coin to the change vector
                    amountOwed -= coinCopy[i].denom;
                    change.push_back(coinCopy[i].denom);
                    coinCopy[i].count--;
                }
                i--;
            }

            if(amountOwed == 0){
                // Purchase successful, print out the change refunded if there is any
                if(change.size() > 0){
                    std::cout << "Your change is: ";

                    for(unsigned i = 0; i < change.size(); i++){
                        if(change[i] >= 100){
                            // Denomination is greater than or equal to 100, so it's a dollar
                            std::cout << "$" << change[i] / 100 << " ";
                        }
                        else {
                            // Denomination is less than 100, so it's cents
                            std::cout << change[i] << "c ";
                        }
                    }
                    std::cout << std::endl;
                }

                // Update the food node and coin vector in the system accordingly.
                food->data->on_hand--;
                coins = coinCopy;
            }
            else{
                std::cout << "Error: The system cannot refund the exact change. Purchase cancelled." << std::endl;
            }
        }
    }
};

// Function to be executed to print vending machine balance
void DisplayBalanceCommand::displayBalance(std::vector<Coin>& coins) const {
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
};

// Function to be executed to update and save food data into foods.dat
void SaveCommand::saveFoodData(char *food_file, DoublyLinkedList &foodList) const {
    // Open the file to write
    std::ofstream file(food_file);

    // If file does not exist, display error message
    if (!file) {
        std::cerr << "Error: could not open file " << food_file << std::endl;
        exit(EXIT_FAILURE);
    }

    // Write the food item into foods.dat
    foodList.writeAllFoods(file);

    // Close the file
    file.close();
}

// Function to be executed to update and save coins data into coins.dat
void SaveCommand::saveCoinData(char *coin_file, std::vector<Coin>& coins) const {
    // Open the file to write
    std::ofstream file(coin_file);

    // If file does not exist, display error message
    if (!file) {
        std::cerr << "Error: could not open file " << coin_file << std::endl;
        exit(EXIT_FAILURE);
    }

    // Write the coin details into coins.dat
    for(const Coin& coin : coins) {
        file << coin.denom << "," 
            << coin.count << std::endl;
    }

    // Close the file
    file.close();
};

// Function to be executed ti load food data into linked list based on provided .dat file
void LoadCommand::loadFoodData(char *food_file, DoublyLinkedList &foodList) const {
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
            if (betterMessage) {
                std::cerr << "The correct format for an item is \"<ID>|<Name>|<Description>|<Price>\"." << std::endl;
            }
            exit(EXIT_FAILURE);
        }

        // Extracting ID
        std::getline(iss, token, '|');
        // If the ID is not in the correct format (Fxxxx), exit the program
        if (token.length() != IDLEN || token.substr(0, 1) != "F"){
            // Error: ID format is incorrect
            std::cerr << "Error: The format of an item's ID is incorrect in " << food_file << "." << std::endl;
            if (betterMessage) {
                std::cerr << "The correct ID format is \"Fxxxx\", where x is a number." << std::endl;
            }
            exit(EXIT_FAILURE);
        }
        foodItem->id = token;

        // Extracting Name
        std::getline(iss, token, '|');
        if (token.length() > NAMELEN) {
            // Error: Name is too long
            std::cerr << "Error: An item's name is too long in " << food_file << "." << std::endl;
            if (betterMessage) {
                std::cerr << "The maximum length of an item's name is 40 characters." << std::endl;
            }
            exit(EXIT_FAILURE);
        }
        foodItem->name = token;

        // Extracting Description
        std::getline(iss, token, '|');
        if (token.length() > DESCLEN) {
            // Error: Description is too long
            std::cerr << "Error: An item's description is too long in " << food_file << "." << std::endl;
            if (betterMessage) {    
                std::cerr << "The maximum length of an item's description is 255 characters." << std::endl;
            }
            exit(EXIT_FAILURE);
        }
        foodItem->description = token;

        //Set the food stock to the default level
        foodItem->on_hand = DEFAULT_FOOD_STOCK_LEVEL;

        // Extracting Price into dollars and cents
        std::getline(iss, token, '|');
        size_t decimalPointPos = token.find('.'); // Find the position of the dot
        // Validate input and print specific error message if invalid
        if (betterMessage) {
            if (decimalPointPos == std::string::npos) {
                std::cerr << "Error: An item's price should have a decimal point in between the dollar and cent.\n" << std::endl;
                exit(EXIT_FAILURE);
            }
            else if (decimalPointPos <= 0 || decimalPointPos >= token.length() - 1) {
                std::cerr << "Error: An item's price should have at least 1 digit before and must have exactly 2 digits after the decimal point.\n" << std::endl;
                exit(EXIT_FAILURE);
            }
            else if (!std::all_of(token.begin(), token.begin() + decimalPointPos, ::isdigit) || !std::all_of(token.begin() + decimalPointPos + 1, token.end(), ::isdigit)) {
                std::cerr << "Error: An item's price should have digits only before and after the decimal point.\n" << std::endl;
                exit(EXIT_FAILURE);
            }
            else if (token.substr(token.find('.') + 1).length() != 2) {
                std::cerr << "Error: An item's price should have exactly 2 digit after the decimal point.\n" << std::endl;
                exit(EXIT_FAILURE);
            }
            else if (std::stod(token) <= 0.00) {
                std::cerr << "Error: An item's price should be greater than 0.00.\n" << std::endl;
                exit(EXIT_FAILURE);
            }
            else if (!isDivisibleByFiveCents(token)) {
                std::cerr << "Error: An item's price should be divisible by 5 cents so that the vending machine can give change.\n" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else {
            if (decimalPointPos == std::string::npos ||
                decimalPointPos <= 0 || // Decimal point should not be at the beginning
                decimalPointPos >= token.length() - 1 || // Decimal point should not be at the end
                !std::all_of(token.begin(), token.begin() + decimalPointPos, ::isdigit) || // Digits before and after decimal point
                !std::all_of(token.begin() + decimalPointPos + 1, token.end(), ::isdigit) ||
                token.substr(token.find('.') + 1).length() != 2 ||
                std::stod(token) <= 0.00 || // Price is should be greater than 0.00
                !isDivisibleByFiveCents(token)) {  // Price should be divisible by 5 cents so that the vending machine can give change

                std::cerr << "Error: Price format is incorrect" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::string string_dollars = token.substr(0, decimalPointPos);
        std::string string_cents = token.substr(decimalPointPos + 1);
        foodItem->price.dollars = std::stoi(string_dollars);
        foodItem->price.cents = std::stoi(string_cents);

        // Create a new node and add it to the linked list
        Node* node = new Node;
        node->data = foodItem;
        foodList.addNode(node);
    }
    file.close();
};

// Function to be executed to remove food item stock
void RemoveStockCommand::removeStock(DoublyLinkedList &foodList) const {
    // Debug function that reduces a meal's stock quantity to 0.
    // Used to test purchasing when a meal is out of stock.

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

};

// Function to be executed to load coin data from a .dat file
std::vector<Coin> Coin::loadCoinData(const std::string& filename, bool betterMessage) {
    // Open the file to read
    std::ifstream file(filename);

    // If file does not exist, throw runtime error and display error message
    if (!file.is_open()) {
        throw std::runtime_error("Error: could not open file " + filename);
    }

    // Vector to store coin details
    std::vector<Coin> coins;
    std::string line;

    // Transverse each line in coins.dat
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        // Check delimeter validitiy by counting how many value are in the line separated by ',', must be 1
        int delimiterCount = 0;
        for (char c : line) {
            if (c == ',') {
                delimiterCount++;
            }
        }
        // If there are more than 1 delimeter
        if (delimiterCount != 1) {
            // display error message
            std::cerr << "Error: Incorrect number of values in coins.dat" << std::endl;
            if (betterMessage) {
                std::cerr << "The correct format for a coin is \"<denomination>,<quantity>\"." << std::endl;
            }
            // exit program
            exit(EXIT_FAILURE);
        }

        // Parse denomination
        std::getline(iss, token, DELIM[0]);
        Denomination denom = static_cast<Denomination>(std::stoi(token));
        // Check if denomination is valid
        if (denom != FIVE_CENTS && denom != TEN_CENTS && 
            denom != TWENTY_CENTS && denom != FIFTY_CENTS &&
            denom != ONE_DOLLAR && denom != TWO_DOLLARS && 
            denom != FIVE_DOLLARS && denom != TEN_DOLLARS &&
            denom != TWENTY_DOLLARS && denom != FIFTY_DOLLARS) {
            std::cerr << "Error: Invalid denomination in coins.dat" << std::endl;
            if (betterMessage) {
                std::cerr << "The valid denominations are 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000." << std::endl;
            }
            // Exist the program if denomination is invalid
            exit(EXIT_FAILURE);
        }

        // Parse quantity
        std::getline(iss, token, DELIM[0]);
        unsigned count = std::stoi(token);

        // Create Coin object and add to vector
        Coin coin;
        coin.denom = denom;
        coin.count = count;
        coins.push_back(coin);
    }

    // Sort the coins by denomination
    std::sort(coins.begin(), coins.end(), compareCoins);

    // Close the file
    file.close();

    // Return vector holding coin details
    return coins;
};