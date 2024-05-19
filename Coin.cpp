#include "Coin.h" 

// Function for sorting coins
bool compareCoins(const Coin& coin1, const Coin& coin2) {
    return coin1.denom < coin2.denom; // Sort by denomination
}

// Function to load coin data from a file
std::vector<Coin> Coin::loadCoinData(const std::string& filename) {
    //open the file to read
    std::ifstream file(filename);

    // if file does not exist, throw runtime error and display error message
    if (!file.is_open()) {
        throw std::runtime_error("Error: could not open file " + filename);
    }

    // vector to store coin details
    std::vector<Coin> coins;
    std::string line;

    // Transverse each line in coins.dat
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        // Check delimeter validitiy
        // Count how many value are in the line separated by ',', must be 1
        int delimiterCount = 0;
        for (char c : line) {
            if (c == ',') {
                delimiterCount++;
            }
        }
        // if there are more than 1 delimeter
        if (delimiterCount != 1) {
            // display error message
            std::cerr << "Error: Incorrect number of values in coins.dat" << std::endl;
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

    // close the file
    file.close();

    // Return vector holding coin details
    return coins;
}

void Coin::addCount(int amount){
    count += amount;
}