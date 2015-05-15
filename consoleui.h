#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <iostream>
#include <string>
#include <vector>
#include <limits>

namespace BMCA {

namespace UI {

    ///Prompts the user with a formatted list of options (first element is header/title)
    void promptList(std::vector<std::string> &options);

    ///Gets user input int
    int getIntInput(std::string prompt);

    ///Gets user input int with range checking
    int getIntInput(std::string prompt, int low, int high);

    ///Gets user input int with a list of prompts (menus)
    int getIntInput(std::vector<std::string> prompt);

    ///Gets user input as a string
    std::string getStringInput(std::string prompt);

    ///Gets user input bool, prompts [Y/n] and error checks the input
    bool getBoolInput(std::string prompt);

    ///
    void output(std::string text);
}
}

#endif // CONSOLEUI_H

