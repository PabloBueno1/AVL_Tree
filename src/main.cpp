#include <iostream>
#include "tree.h"
#include <string>
#include <sstream>

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

std::string verifyName(std::string Name);
std::string verifyID(std::string ID);
bool isName(std::string name);
bool isNumber(std::string ID);

int main(){
    AVLTree tree;

    // most of the main is adapted from the slides on the project 1 breakdown

    std::string temp;
    std::getline(std::cin,temp);
    int numLines = std::stoi(temp);

    // read num of lines for the loop

    for (int i = 0; i < numLines; i++){
        std::string line;
        std::getline(std::cin,line);

        std::istringstream in(line);

        std::string command;
        in >> command;

        // reads the first word which is the command and the
        // based on the command it changes how the rest is read

        if (command == "insert") {

            std::string tempName;
            std::getline(in, tempName, '"');
            std::getline(in, tempName, '"');

            std::string name = verifyName(tempName);
            // check if name is valid

            std::string tempID;
            std::getline(in, tempID, ' ');
            std::getline(in, tempID);

            std::string ID = verifyID(tempID);
            // check ID is valid

            // IF all is good then do things to the tree
            if (!ID.empty() && !name.empty()){
                tree = tree.insert(name, ID);
            }
        }

        else if (command == "remove"){
            std::string removeID;
            std::getline(in, removeID, ' ');
            std::getline(in,removeID);

            removeID = verifyID(removeID);

            if (!removeID.empty()){
                tree = tree.remove(removeID);
            }

                // finds out the number N and then converts to int and calls remove
            // call remove
        }

        else if (command == "search"){
            std::string nameOrId;
            std::getline(in, nameOrId,'"');

            if (isName(nameOrId)){
                std::getline(in, nameOrId,'"');
                tree.searchName(nameOrId);
            }
            else{
                std::getline(in, nameOrId, ' ');
                nameOrId = nameOrId.substr(1);
                tree.searchID(nameOrId);
            }
            // checks if it is a ID or name and performs appropriate search
        }

        else if (command == "printInorder"){
            std::string trash;
            std::getline(in, trash);
            tree.printInorder();
            std::cout << std::endl;
            // removes the space and calls print
        }

        else if (command == "printPreorder"){
            std::string trash;
            std::getline(in, trash);
            tree.printPreorder();
            std::cout << std::endl;
            // removes the space and calls print
        }

        else if (command == "printPostorder"){
            std::string trash;
            std::getline(in, trash);
            tree.printPostorder();
            std::cout << std::endl;
            // removes the space and calls print
        }

        else if (command == "printLevelCount"){
            std::string trash;
            std::getline(in, trash);
            tree.printLevelCount();
            // removes the space and calls print
        }

        else if (command == "removeInorder"){
            std::string removeOrder;
            std::getline(in, removeOrder, ' ');
            std::getline(in,removeOrder);

            if (isNumber(removeOrder)){
                int order = std::stoi(removeOrder);

                tree = tree.removeInOrder(order);
                // finds out the number N and then converts to int and calls remove
            }
            else{
                std::cout << "unsuccessful" << std::endl;
            }
        }

        else {
            std::cout << "unsuccessful" << std::endl;
        }

    }

	return 0;
}

std::string verifyName(std::string name) {

    for (char c : name){
        if (!std::isalpha(c) && !std::isblank(c)){
            std::cout << "unsuccessful" << std::endl;
            return "";
        }
    }
    return name;
}

std::string verifyID(std::string ID) {
    if (ID.length() != 8){
        std::cout << "unsuccessful" << std::endl;
        return "";
    }
    for (char c : ID){
        if (!std::isdigit(c)){
            std::cout << "unsuccessful" << std::endl;
            return "";
        }
    }
    return ID;
}

bool isName(std::string name){
    int first = 0;
    for (char c : name){
        if (!std::isalpha(c) && !std::isblank(c)){
            return false;
        }
    }
    return true;
}

bool isNumber(std::string ID){
    for (char c : ID){
        if (!std::isdigit(c)){
            return false;
        }
    }
    return true;
}