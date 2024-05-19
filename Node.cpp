#include "Node.h"

Node::Node(){
    // TODO
    data = nullptr;
    next = nullptr;
    prev = nullptr;
};

Node::~Node(){
    // TODO
    delete data; // delete the FoodItem
};

// display food item to console
void Node::printNode() const {
    std::cout << std::left << std::setw(5) << data->id << "|";
    std::cout << std::left << std::setw(50) << data->name << "|";
    std::cout << "$" << std::right << std::setw(2) << data->price.dollars << ".";
    std::cout << std::setw(2) << std::setfill('0') << data->price.cents 
        << std::setfill(' ') << std::endl;
}

// write node data into foods.dat file
void Node::writeNode(std::ostream& food_file) const {
    food_file << data->id << "|" 
        << data->name << "|" 
        << data->description << "|" 
        << data->price.dollars << "."
        << std::setw(2) << std::setfill('0') << data->price.cents 
        << std::setfill(' ') << std::endl;
}