#include "consoleui.h"

///Prompts the user with a formatted list of options
void BMCA::UI::promptList(std::vector<std::string> &options) {
    //display the header/table
    std::cout << options[0] << ':' << std::endl;

    //output each item avaliable in the menu with a corresponding id # to select it
    for (int i = 1; i < options.size(); i++)
        std::cout << "[" << i << "] - " << options[i] << std::endl;
}

///Gets user input int
int BMCA::UI::getIntInput(std::string prompt) {
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
int BMCA::UI::getIntInput(std::string prompt, int low, int high) {
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
int BMCA::UI::getIntInput(std::vector<std::string> prompt){
    promptList(prompt);
    return getIntInput("", 1, prompt.size()-1);
}

std::string BMCA::UI::getStringInput(std::string prompt){
    std::cout << prompt << std::endl;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

bool BMCA::UI::getBoolInput(std::string prompt){
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

void BMCA::UI::output(std::string text){

}

