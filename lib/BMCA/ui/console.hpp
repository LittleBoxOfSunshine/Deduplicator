#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <iostream>
#include <string>
#include <vector>
#include <limits>

namespace BMCA {

namespace UI {

    ///Prompts the user with a formatted list of options (first element is header/title)
    void promptList(std::vector<std::string> &options){
        //display the header/table
        std::cout << options[0] << ':' << std::endl;

        //output each item avaliable in the menu with a corresponding id # to select it
        for (int i = 1; i < options.size(); i++)
            std::cout << "[" << i << "] - " << options[i] << std::endl;
    }

    ///Gets user input int
    int getIntInput(std::string prompt){
        //display prompt
        std::cout << prompt << std::endl;
        int input;

        //continue prompting until input is valid
        while (!(std::cin >> input)) {
            std::cout << "Please enter a valid integer..." << std::endl << prompt << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        return input;
    }

    ///Gets user input int with range checking
    int getIntInput(std::string prompt, int low, int high){
        //prompt user for input until it is valid
        while (true) {
            int input;
            input = getIntInput(prompt);

            //input was valid, return it
            if (input >= low && input <= high)
                return input;
            //input was invalid, notify user of the error and continue prompting
            else
                std::cout << "Please enter a valid number " << low << "-" << high << "..."  << std::endl;
        }
    }

    ///Gets user input int with a list of prompts (menus)
    int getIntInput(std::vector<std::string> prompt){
        promptList(prompt);
        return getIntInput("", 1, prompt.size()-1);
    }

    ///Gets user input as a string
    std::string getStringInput(std::string prompt){
        std::cout << prompt << std::endl;
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    ///Gets user input bool, prompts [Y/n] and error checks the input
    bool getBoolInput(std::string prompt){
        std::cout << prompt << std::endl << "[Y/n]" << std::endl;
            std::string input;
        while(true){
        std::getline(std::cin, input);
        if(input == "Y" || input == "y")
            return true;
        else if (input == "N" || input == "n")
            return false;
        else
            std::cout << "Please enter a valid response..." << std::endl;
        }
    }

    ///
    void output(std::string text){

    }
}
}

#endif // CONSOLEUI_H

