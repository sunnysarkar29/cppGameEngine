// Included libraries.
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <iomanip>

// Included class definition "GameEngine".
#include "GameEngine.hpp"

// WELCOME UI
void welcome();

// MAIN UI FUNCTIONS
void mainUI();
void clearTextFiles();
void saveProject();
void sampleProject();

// STORY TREE FUNCTIONS
void storyTreeUI();
void addEvent();
void deleteEvent();
void editEvent();
void demoStory();

// CHARACTER NODES FUNCTIONS
void characterNodesUI();
void addCharacter();
void deleteCharacter();
void editCharacter();
void printCharacters();

// Declaration of the "GameEngine" project class.
GameEngine project;

int main()
{
    // Prints the welcomeUI.
    welcome();

    // Declaration of choice variables for use in menus.
    int mainUIChoice = 0;
    int storyTreeUIChoice = 0;
    int characterNodesUIChoice = 0;
    int combatGraphUIChoice = 0;

    // Declaration of choice for user input using getline.
    std::string choice;

    // Declaration of UIOn to ensure a UI will remain until the user is done.
    bool storyTreeUIOn;
    bool characterNodesUIOn;
    bool combatGraphUIOn;

    // Declaration of isValidEntry to ensure that the user is inputting integers
    // while interacting with the UI.
    bool isValidEntry = true;

    // Runs the game engine until the user is done.
    while (true)
    {
        // Switch statement for the mainUI.
        switch (mainUIChoice)
        {
        case 1:

            // Allows the storyTreeUI to be displayed.
            storyTreeUIOn = true;

            // Runs the storyTreeUI until the user is done.
            while (storyTreeUIOn)
            {
                // Switch statement for the storyTreeUI.
                switch (storyTreeUIChoice)
                {
                case 1:

                    // Runs addEvent() if the user selects "1" in the storyTreeUI.
                    // Then returns the user to the storyTreeUI.
                    addEvent();
                    storyTreeUIChoice = 0;
                    break;

                case 2:

                    // Runs deleteEvent() if the user selects "2" in the storyTreeUI.
                    // Then returns the user to the storyTreeUI.
                    deleteEvent();
                    project.fixID();
                    storyTreeUIChoice = 0;
                    break;

                case 3:

                    // Runs editEdit() if the user selects "3" in the storyTreeUI.
                    // Then returns the user to the storyTreeUI.
                    editEvent();
                    project.fixID();
                    storyTreeUIChoice = 0;
                    break;

                case 4:

                    // Runs demoStory() if the user selects "4" in the storyTreeUI.
                    // Then returns the user to the storyTreeUI.
                    demoStory();
                    storyTreeUIChoice = 0;
                    break;

                case 5:

                    // Returns to user to the mainUI if the user selects "5" in the storyTreeUI.
                    std::cout << "Returning to Main Menu..." << std::endl;

                    storyTreeUIOn = false;
                    storyTreeUIChoice = 0;

                    break;

                default:

                    // Runs storyTreeUI and asks for the users choice.
                    storyTreeUI();
                    std::getline(std::cin, choice);

                    // Loop that checks if the user input an integer.
                    isValidEntry = true;

                    if (choice == "")
                    {
                        isValidEntry = false;
                    }
                    else
                    {
                        for (int i = 0; i < choice.length(); i++)
                        {
                            if (!isdigit(choice[i]))
                            {
                                isValidEntry = false;
                            }
                        }
                    }

                    while (isValidEntry == false)
                    {
                        std::cout << "Please enter a valid integer." << std::endl;
                        std::getline(std::cin, choice);

                        isValidEntry = true;

                        if (choice == "")
                        {
                            choice = false;
                        }
                        else
                        {
                            for (int i = 0; i < choice.length(); i++)
                            {
                                if (!isdigit(choice[i]))
                                {
                                    isValidEntry = false;
                                }
                            }
                        }
                    }

                    // Converts the choice given by the user to the storyTreeUIChoice.
                    storyTreeUIChoice = stoi(choice);
                }
            }

            // Once the user is done with the storyTreeUI, this will return the user to the mainUI.
            mainUIChoice = 0;
            break;

        case 2:

            // Allows the characterNodesUI to be displayed.
            characterNodesUIOn = true;

            // Runs the characterNodesUI until the user is done.
            while (characterNodesUIOn)
            {
                // Switch statement for the characterNodesUI.
                switch (characterNodesUIChoice)
                {
                case 1:

                    // Runs addCharacter() if the user selects "1" in the characterNodesUI.
                    // Then returns the user to the characterNodesUI.
                    addCharacter();
                    characterNodesUIChoice = 0;
                    break;

                case 2:

                    // Runs deleteCharacter() if the user selects "2" in the characterNodesUI.
                    // Then returns the user to the characterNodesUI.
                    deleteCharacter();
                    characterNodesUIChoice = 0;
                    break;

                case 3:

                    // Runs editCharacter() if the user selects "3" in the characterNodesUI.
                    // Then returns the user to the characterNodesUI.
                    editCharacter();
                    characterNodesUIChoice = 0;
                    break;

                case 4:

                    // Runs printCCharacters() if the user selects "4" in the characterNodesUI.
                    // Then returns the user to the characterNodesUI.
                    printCharacters();
                    characterNodesUIChoice = 0;
                    break;

                case 5:

                    // Returns to user to the mainUI if the user selects "5" in the characterNodesUI.
                    std::cout << "Returning to Main Menu..." << std::endl;

                    characterNodesUIOn = false;
                    characterNodesUIChoice = 0;

                    break;

                default:

                    // Runs characterNodesUI and asks for the users choice.
                    characterNodesUI();
                    std::getline(std::cin, choice);

                    // Loop that checks if the user input an integer.
                    isValidEntry = true;

                    if (choice == "")
                    {
                        isValidEntry = false;
                    }
                    else
                    {
                        for (int i = 0; i < choice.length(); i++)
                        {
                            if (!isdigit(choice[i]))
                            {
                                isValidEntry = false;
                            }
                        }
                    }

                    while (isValidEntry == false)
                    {
                        std::cout << "Please enter a valid integer." << std::endl;
                        std::getline(std::cin, choice);

                        isValidEntry = true;

                        if (choice == "")
                        {
                            choice = false;
                        }
                        else
                        {
                            for (int i = 0; i < choice.length(); i++)
                            {
                                if (!isdigit(choice[i]))
                                {
                                    isValidEntry = false;
                                }
                            }
                        }
                    }

                    // Converts the choice given by the user to the characterNodesUIChoice.
                    characterNodesUIChoice = stoi(choice);
                }
            }

            // Once the user is done with the characterNodesUI, this will return the user to the mainUI.
            mainUIChoice = 0;
            break;

        case 3:

            // Runs saveProject() if the user selects "3" in the mainUI.
            // Then returns the user to the mainUI.
            saveProject();
            mainUIChoice = 0;
            break;

        case 4:

            // Runs sampleProject() if the user selects "4" in the mainUI.
            // Then returns the user to the mainUI.
            sampleProject();
            mainUIChoice = 0;
            break;

        case 5:

            // Quits the game engine and terminates the program.
            std::cout << "Quiting Game Engine..." << std::endl;
            return 0;

        default:

            // Runs mainUI and asks for the users choice.
            mainUI();
            std::getline(std::cin, choice);

            // Loop that checks if the user input an integer.
            isValidEntry = true;

            if (choice == "")
            {
                isValidEntry = false;
            }
            else
            {
                for (int i = 0; i < choice.length(); i++)
                {
                    if (!isdigit(choice[i]))
                    {
                        isValidEntry = false;
                    }
                }
            }

            while (isValidEntry == false)
            {
                std::cout << "Please enter a valid integer." << std::endl;
                std::getline(std::cin, choice);

                isValidEntry = true;

                if (choice == "")
                {
                    choice = false;
                }
                else
                {
                    for (int i = 0; i < choice.length(); i++)
                    {
                        if (!isdigit(choice[i]))
                        {
                            isValidEntry = false;
                        }
                    }
                }
            }

            // Converts the choice given by the user to the mainUIChoice.
            mainUIChoice = stoi(choice);
        }
    }
}

// Prints welcomeUI.
void welcome()
{
    std::cout << "\n===========================================================================\n"
              << "   _____          __  __ ______   ______ _   _  _____ _____ _   _ ______ \n"
              << "  / ____|   /\\   |  \\/  |  ____| |  ____| \\ | |/ ____|_   _| \\ | |  ____|\n"
              << " | |  __   /  \\  | \\  / | |__    | |__  |  \\| | |  __  | | |  \\| | |__   \n"
                 " | | |_ | / /\\ \\ | |\\/| |  __|   |  __| | . ` | | |_ | | | | . ` |  __|  \n"
              << " | |__| |/ ____ \\| |  | | |____  | |____| |\\  | |__| |_| |_| |\\  | |____ \n"
              << "  \\_____/_/    \\_\\_|  |_|______| |______|_| \\_|\\_____|_____|_| \\_|______|\n"
              << "     MITCHELL PHELPS             SUNNY SARKAR             JOSEPH DENG     \n"
              << "===========================================================================\n"
              << std::endl;
}

// Prints the mainUI.
void mainUI()
{
    std::cout << "-=== MAIN MENU ===-" << std::endl;
    std::cout << "1. Story Options" << std::endl;
    std::cout << "2. Character Options" << std::endl;
    std::cout << "3. Save Project (Export Current Data Structures)" << std::endl;
    std::cout << "4. Sample Project" << std::endl;
    std::cout << "5. Quit" << std::endl;
}

// Exports the data from the current project into readable text files.
void saveProject()
{
    // Runs saveToFile() found inside the GameEngine class.
    project.saveToFile();
}

// Allows the user to play the created game.
void sampleProject()
{
    // Runs sampleProjectGameEngine() found inside the GameEngine class.
    project.sampleProjectGameEngine();
}

// Prints the storyTreeUI.
void storyTreeUI()
{
    std::cout << "-=== STORY MENU ===-" << std::endl;
    std::cout << "1. Construct Story" << std::endl;
    std::cout << "2. Delete Event" << std::endl;
    std::cout << "3. Edit Event" << std::endl;
    std::cout << "4. Demo Story" << std::endl;
    std::cout << "5. Go Back" << std::endl;
}

// Allows the user to add a storyNode to the existing tree.
void addEvent()
{
    // Runs insertEvent() found inside the GameEngine class.
    project.insertEvent();
}

// Allows the user to delete a storyNode with a given ID.
void deleteEvent()
{
    if(project.getNumEvents() == 0)
    {
        std::cout << "Story tree is empty. Nothing to delete." << std::endl;
        return;
    }
    
    // Declaration of choice and idChoice to check user input.
    std::string choice;
    std::string idChoice;

    // Asks the user if they know the ID and recieves their answer.
    std::cout << "Do you know the ID of the node you want to delete (Y/N)?" << std::endl;
    std::getline(std::cin, choice);

    // Loops that checks if the user input Y/y or N/n.
    while (!(choice == "Y" || choice == "N" || choice == "y" || choice == "n"))
    {
        std::cout << "Invalid Entry. Please enter Y for yes or N for no." << std::endl;
        std::getline(std::cin, choice);
    }

    // If yes, the user is prompted to input the ID.
    if (choice == "Y" || choice == "y")
    {
        std::cout << "Please enter the ID of the node." << std::endl;
        std::getline(std::cin, idChoice);

        // If the ID does not exist within the storyTree, then the user is asked for a
        // valid ID.        
        while (!(stoi(idChoice) > 0 && stoi(idChoice) <= project.getNumEvents()))
        {
            std::cout << "Please enter a valid ID." << std::endl;
            std::getline(std::cin, idChoice);
        }

        // deleteEvent() from the GameEngine class is run with the user input ID.
        project.deleteEvent(stoi(idChoice));

        return;
    }
    // If no, the user is presented with a list of IDs.
    else if (choice == "N" || choice == "n")
    {
        while (true)
        {
            std::cout << "Please chose an ID from the list below." << std::endl;

            // printIDTree() form the GameEngine class is run.
            project.printIDTree();

            std::getline(std::cin, idChoice);

            // If the ID does not exist within the storyTree, then the user is asked for a
            // valid ID.        
            int idChoiceInt = stoi(idChoice);
            while (!(stoi(idChoice) > 0 && stoi(idChoice) <= project.getNumEvents()))
            {
                std::cout << "Please enter a valid ID." << std::endl;
                std::getline(std::cin, idChoice);
            }

            // viewEvent() from the GameEngine class is run with the ID choice of the user.
            project.viewEvent(stoi(idChoice));

            // Asks the user if the printed event is the correct on.
            std::cout << "Is this the correct event (Y/N)?" << std::endl;
            std::getline(std::cin, choice);

            // Loops that checks if the user input Y/y or N/n.
            while (!(choice == "Y" || choice == "N" || choice == "y" || choice == "n"))
            {
                std::cout << "Invalid Entry. Please enter Y for yes or N for no." << std::endl;
                std::getline(std::cin, choice);
            }

            // If yes, then deleteEvent() from the GameEngine class is run with the ID choice of
            // the user.
            if (choice == "Y" || choice == "y")
            {
                project.deleteEvent(stoi(idChoice));
                return;
            }
            // If no, then the while loop is run again.
        }
    }
}

// Allows the user to edit a storyNode.
void editEvent()
{
    if (project.getNumEvents() == 0)
    {
        std::cout << "Story tree is empty. Nothing to edit." << std::endl;
        return;
    }

    // Declaration of choice and idChoice to check user input.
    std::string choice;
    std::string idChoice;

    // Asks the user if they know the ID and recieves their answer.
    std::cout << "Do you know the ID of the node you want to delete (Y/N)?" << std::endl;
    std::getline(std::cin, choice);

    // Loops that checks if the user input Y/y or N/n.
    while (!(choice == "Y" || choice == "N" || choice == "y" || choice == "n"))
    {
        std::cout << "Invalid Entry. Please enter Y for yes or N for no." << std::endl;
        std::getline(std::cin, choice);
    }

    // If yes, the user is prompted to input the ID.
    if (choice == "Y" || choice == "y")
    {
        std::cout << "Please enter the ID of the node." << std::endl;
        std::getline(std::cin, idChoice);

        // If the ID does not exist within the storyTree, then the user is asked for a
        // valid ID.
        while (!(stoi(idChoice) > 0 && stoi(idChoice) <= project.getNumEvents()))
        {
            std::cout << "Please enter a valid ID." << std::endl;
            std::getline(std::cin, idChoice);
        }

        // editEvent() from the GameEngine class is run with the user input ID.
        project.editEvent(stoi(idChoice));
        return;
    }
    // If no, the user is presented with a list of IDs.
    else if (choice == "N" || choice == "n")
    {
        while (true)
        {
            std::cout << "Please chose an ID from the list below." << std::endl;

            // printIDTree() form the GameEngine class is run.
            project.printIDTree();

            std::getline(std::cin, idChoice);

            // If the ID does not exist within the storyTree, then the user is asked for a
            // valid ID.
            while (!(stoi(idChoice) > 0 && stoi(idChoice) <= project.getNumEvents()))
            {
                std::cout << "Please enter a valid ID." << std::endl;
                std::getline(std::cin, idChoice);
            }

            // viewEvent() from the GameEngine class is run with the ID choice of the user.
            project.viewEvent(stoi(idChoice));

            std::cout << "Is this the correct event (Y/N)?" << std::endl;
            std::getline(std::cin, choice);

            // Loops that checks if the user input Y/y or N/n.
            while (!(choice == "Y" || choice == "N" || choice == "y" || choice == "n"))
            {
                std::cout << "Invalid Entry. Please enter Y for yes or N for no." << std::endl;
                std::getline(std::cin, choice);
            }

            // If yes, then deleteEvent() from the GameEngine class is run with the ID choice of
            // the user.
            if (choice == "Y" || choice == "y")
            {
                project.editEvent(stoi(idChoice));
                return;
            }
            // If no, then the while loop is run again.
        }
    }
}

// Allows the user to demo the story.
void demoStory()
{
    // Runs demoEvent() from the GameEngine class.
    project.demoEvents();
}

// Prints the characterNodesUI.
void characterNodesUI()
{
    std::cout << "-=== CHARACTER MENU ===-" << std::endl;
    std::cout << "1. Add Character" << std::endl;
    std::cout << "2. Delete Character" << std::endl;
    std::cout << "3. Edit Character" << std::endl;
    std::cout << "4. Print Characters" << std::endl;
    std::cout << "5. Go Back" << std::endl;
}

// Allows the user to add a characterNode.
void addCharacter()
{
    // Runs addCharacterNode() from the GameEngine class.
    project.addCharacterNode();
}

// Allows the user to delete a characterNode.
void deleteCharacter()
{
    // Declarations for the number of characters and the characterListRoot;
    int numCharacters = 1;
    characterNode *temp = project.getCharacterListRoot();

    std::cout << "\n--- Character List ---" << std::endl;

    // Loops that prints the names of all existing characters in a list.
    while (temp != NULL)
    {
        std::cout << numCharacters << ") " << temp->characterName << std::endl;

        temp = temp->next;
        numCharacters++;
    }

    std::cout << std::endl;

    // Declaration to recieve input from user.
    std::string characterName;

    // Prompts user for the name of the character they want to delete.
    std::cout << "What is the name of the character you want to delete?" << std::endl;
    std::getline(std::cin, characterName);

    // Checks that the entered name is valid.
    while (project.getCharacter(characterName) == NULL)
    {
        std::cout << "Please enter a valid character name." << std::endl;
        std::getline(std::cin, characterName);
    }

    // Runs deleteCharacterNode() from the GameEngine class with the provided character name.
    project.deleteCharacterNode(characterName);
}

// Allows the user to edit a characterNode.
void editCharacter()
{
    // Runs editCharacterNode() from the GameEngine class.
    project.editCharacterNode();
}

// Prints a list of created characters and their stats.
void printCharacters()
{
    // Runs printCharacters() from the GameEngine class.
    project.printCharacters();
}
