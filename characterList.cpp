#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "GameEngine.hpp"

// Prints the list of characters with their stats and status'.
void GameEngine::printCharacters()
{
    //Initialze traverse node
    characterNode *currCharacter = characterListRoot;

    //Check if there are no characters in the linked list
    if (currCharacter == NULL)
    {
        std::cout << "\nThere are no characters."
                  << std::endl
                  << std::endl;
        return;
    }

    //Traverse through linked list
    while (currCharacter != NULL)
    {

        //Print stats
        std::cout << "\n=======================" << std::endl;
        std::cout << "Character Name  : " << currCharacter->characterName << std::endl;
        std::cout << "    Health      : " << currCharacter->characterHealth << std::endl;
        std::cout << "    Speed       : " << currCharacter->characterSpeed << std::endl;
        std::cout << "    Strength    : " << currCharacter->characterStrength << std::endl;

        //check if enemy
        if (currCharacter->enemy)
        {
            std::cout << "    Is Enemy    : True" << std::endl;
        }
        else
        {
            std::cout << "    Is Enemy    : False" << std::endl;
        }

        currCharacter = currCharacter->next;
    }

    std::cout << std::endl;
}

// Adds a character node using user input values into the character list.
void GameEngine::addCharacterNode()
{
    //Initialize variables
    characterNode *newCharacter = new characterNode;
    std::string inStatement;

    //Set characters name
    std::cout << "What is your character's name?" << std::endl;
    std::getline(std::cin, inStatement);
    newCharacter->characterName = inStatement;

    //Sets characters health
    std::cout << "What is " << newCharacter->characterName << "'s health?" << std::endl;
    std::getline(std::cin, inStatement);
    bool isValidEntry = true;

    //Make sure return value is not empty
    if (inStatement == "")
    {
        isValidEntry = false;
    }
    //Make sure return value is a number
    else
    {
        for (int i = 0; i < inStatement.length(); i++)
        {
            if (!isdigit(inStatement[i]))
            {
                isValidEntry = false;
            }
        }
    }

    //Keep looping until a valid entry is put in
    while (isValidEntry == false)
    {

        //Make sure return value is a number
        std::cout << "Please enter a valid integer." << std::endl;
        std::getline(std::cin, inStatement);

        isValidEntry = true;

        if (inStatement == "")
        {
            isValidEntry = false;
        }
        //Make sure return value is a number
        else
        {
            for (int i = 0; i < inStatement.length(); i++)
            {
                if (!isdigit(inStatement[i]))
                {
                    isValidEntry = false;
                }
            }
        }
    }

    newCharacter->characterHealth = stoi(inStatement);
    newCharacter->originalHealth = newCharacter -> characterHealth;
    newCharacter -> alive = true;

    //Set characters health
    std::cout << "What is " << newCharacter->characterName << "'s strength?" << std::endl;
    std::getline(std::cin, inStatement);
    isValidEntry = true;

    //Same meathod of checking if input is a valid entry from above
    if (inStatement == "")
    {
        isValidEntry = false;
    }
    else
    {
        for (int i = 0; i < inStatement.length(); i++)
        {
            if (!isdigit(inStatement[i]))
            {
                isValidEntry = false;
            }
        }
    }

    while (isValidEntry == false)
    {
        std::cout << "Please enter a valid integer." << std::endl;
        std::getline(std::cin, inStatement);

        isValidEntry = true;

        if (inStatement == "")
        {
            isValidEntry = false;
        }
        else
        {
            for (int i = 0; i < inStatement.length(); i++)
            {
                if (!isdigit(inStatement[i]))
                {
                    isValidEntry = false;
                }
            }
        }
    }

    newCharacter->characterStrength = stoi(inStatement);

    //Sets characters speed
    std::cout << "What is " << newCharacter->characterName << "'s speed?" << std::endl;
    std::getline(std::cin, inStatement);
    isValidEntry = true;

    //Same meathod of checking if input is a valid entry from above
    if (inStatement == "")
    {
        isValidEntry = false;
    }
    else
    {
        for (int i = 0; i < inStatement.length(); i++)
        {
            if (!isdigit(inStatement[i]))
            {
                isValidEntry = false;
            }
        }
    }

    while (isValidEntry == false)
    {
        std::cout << "Please enter a valid integer." << std::endl;
        std::getline(std::cin, inStatement);

        isValidEntry = true;

        if (inStatement == "")
        {
            isValidEntry = false;
        }
        else
        {
            for (int i = 0; i < inStatement.length(); i++)
            {
                if (!isdigit(inStatement[i]))
                {
                    isValidEntry = false;
                }
            }
        }
    }

    newCharacter->characterSpeed = stoi(inStatement);

    //Set if character is an enemy or not
    std::string choice;
    std::cout << "Is " << newCharacter->characterName << " an enemy (Y/N)?" << std::endl;
    std::getline(std::cin, choice);

    //Will loop if the entry is not valid;
    while (!(choice == "Y" || choice == "N" || choice == "y" || choice == "n"))
    {
        std::cout << "Invalid Entry. Please enter Y for yes or N for no." << std::endl;
        std::getline(std::cin, choice);
    }

    //If no is entered, make character friend
    if (choice == "N" || choice == "n")
    {
        newCharacter->enemy = false;
    }

    //if yes is entered, make character enemy
    if (choice == "Y" || choice == "y")
    {
        newCharacter->enemy = true;
    }

    //Test Cases
    std::cout << newCharacter->characterName << " has been added."
              << std::endl
              << std::endl;

    //sets pointer to the next character equal to NULL
    newCharacter->next = NULL;

    //If there are no characters in the linked list, set root equal to the new character
    if (characterListRoot == NULL)
    {
        characterListRoot = newCharacter;
        return;
    }

    //If already characters in linked list, traverse through and add new character to the end of the linked list
    characterNode *currNode = characterListRoot;
    while (currNode->next != NULL)
    {
        currNode = currNode->next;
    }

    currNode->next = newCharacter;
}

// Deletes a character node from the character list.
void GameEngine::deleteCharacterNode(std::string _characterName)
{
    //Initialize variables
    characterNode *temp = getCharacter(_characterName);
    characterNode *prev = characterListRoot;

    // Deletion if the node to delete is non-existant.
    if (temp == NULL)
    {
        std::cout << _characterName << " does not exist."
                  << std::endl
                  << std::endl;
        return;
    }

    //Inform user of what character is being removed
    std::cout << _characterName << " was removed."
              << std::endl
              << std::endl;

    // If the desired character is at root of LL
    if (temp == characterListRoot)
    {
        //set root equal to the next item in the linked list
        characterListRoot = temp->next;
        delete temp;
        return;
    }

    //Traverse array
    while (prev != temp)
    {
        //Traverse until the next element is the desired delete node
        if (prev->next == temp)
        {
            break;
        }
        prev = prev->next;
    }

    // Set the next node equal to the next of the delete node, and then delete the delete node
    prev->next = temp->next;
    delete temp;
}

// Prints editCharacterUI.
void editCharacterUI()
{
    std::cout << "-== CHARACTER EDIT OPTIONS ==-" << std::endl;
    std::cout << "1. Name" << std::endl;
    std::cout << "2. Health" << std::endl;
    std::cout << "3. Strength" << std::endl;
    std::cout << "4. Speed" << std::endl;
    std::cout << "5. Enemy" << std::endl;
    std::cout << "6. Go Back" << std::endl;
}
// Edits the character node's values
void GameEngine::editCharacterNode()
{
    //Initialize variables
    std::string input;
    int numCharacters = 1;
    characterNode *temp = characterListRoot;

    //If there are no elements in the LL, tell user there are no characters and return
    if (characterListRoot == NULL)
    {
        std::cout << "No characters added." << std::endl
                  << std::endl
                  << std::endl;
        return;
    }

    //Print all characters in the LL
    std::cout << std::endl;
    std::cout << "--- Character List ---" << std::endl;
    while (temp != NULL)
    {

        std::cout << numCharacters << ") " << temp->characterName << std::endl;

        temp = temp->next;
        numCharacters++;
    }
    std::cout << std::endl;

    //Ask user which character they would like to edit
    std::cout << "Which character do you want to edit?" << std::endl;
    std::getline(std::cin, input);

    //Loop until a valid character is added
    while (getCharacter(input) == NULL)
    {
        std::cout << "Please enter a valid character name." << std::endl;
        std::getline(std::cin, input);
    }

    //Find the desired character that user wants to edit
    characterNode *editNode = getCharacter(input);

    //Initialize Variables
    bool characterEditUIOn = true;
    int characterEditUIChoice = 0;

    //Loop until user does not want to change anymore values
    while (characterEditUIOn)
    {
        switch (characterEditUIChoice)
        {
        case 1:
            //Prints original name
            std::cout << "Current Name: " << editNode->characterName << std::endl;

            //Asks user for new name
            std::cout << "Please enter the new name:" << std::endl;
            std::getline(std::cin, input);

            //Sets character name to the new given name
            editNode->characterName = input;
            characterEditUIChoice = 0;
            break;

        case 2:
            //Show original health
            std::cout << "Current Health: " << editNode->characterHealth << std::endl;

            //Asks user for new health
            std::cout << "Please enter the new health: " << std::endl;
            std::getline(std::cin, input);

            //Sets character health to the new given health
            editNode->characterHealth = stoi(input);
            editNode -> originalHealth = editNode -> characterHealth;
            characterEditUIChoice = 0;
            break;

        case 3:
            //Show original strength
            std::cout << "Current Strength: " << editNode->characterStrength << std::endl;

            //Asks user for new strength
            std::cout << "Please enter the new strength: " << std::endl;
            std::getline(std::cin, input);

            //Sets character strength to the new given strength
            editNode->characterStrength = stoi(input);

            characterEditUIChoice = 0;
            break;

        case 4:
            //Show original speed
            std::cout << "Current Speed: " << editNode->characterSpeed << std::endl;

            //Asks user for new speed
            std::cout << "Please enter the new speed: " << std::endl;
            std::getline(std::cin, input);

            //Sets character speed to the new given speed
            editNode->characterSpeed = stoi(input);

            characterEditUIChoice = 0;
            break;

        case 5:
            //show is current character is enemy or not
            if (editNode->enemy == true)
            {
                std::cout << "Current enemy setting is set to true." << std::endl;
            }
            else
            {
                std::cout << "Current enemy setting is set to false." << std::endl;                
            }

            //Asks user for new value of enemy
            std::cout << "Please enter the new enemy setting (1 for true, 0 for false):" << std::endl;
            std::getline(std::cin, input);

            //Loop until there is a valid entry
            while (!(input == "1" || input == "0"))
            {
                std::cout << "Please enter 1 for true or 0 for false." << std::endl;
                std::getline(std::cin, input);
            }

            //Set enemy to true
            if (input == "1")
            {
                editNode->enemy = true;
            }
            //Set enemy to false
            else if (input == "0")
            {
                editNode->enemy = false;
            }

            characterEditUIChoice = 0;
            break;

        case 6:
            //Break out of while loop
            characterEditUIOn = false;
            characterEditUIChoice = 0;

            break;

        default:
            //no valid input was entered. goo back to top
            editCharacterUI();
            std::cout << "Please enter a valid value" << std:: endl;
            std::getline(std::cin, input);
            characterEditUIChoice = stoi(input);
        }
    }

    std::cout << std::endl;
}

// Search function that returns the characterNode with a given name.
characterNode *GameEngine::getCharacter(std::string _characterName)
{
    //create a variable that will traverse LL
    characterNode *currCharacter = characterListRoot;

    while (currCharacter != NULL)
    {
        //If the current node has a name that is the same as the given name, return the current node
        if (currCharacter->characterName == _characterName)
        {
            return currCharacter;
        }

        currCharacter = currCharacter->next;
    }

    //return null if no node is found
    return NULL;
}

// Gets the characterListRoot from CharacterList.
characterNode *GameEngine::getCharacterListRoot()
{
    //returns the root of the character LL
    return characterListRoot;
}