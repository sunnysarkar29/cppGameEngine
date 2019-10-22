#include <iostream>
#include <array>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stdio.h>

#include "GameEngine.hpp"

// Creates a vertex with new characterNodes.
Vertex createVertex(characterNode *_character)
{
    // Variable declarations.
    Vertex nv;
    //nv.turn = false;
    nv.character = _character;

    // Test Case
    // std::cout << "Adding: " << nv.character->characterName << "..." << std::endl;
    return nv;
}

// Adds a vertex to the graph.
void GameEngine::addVertex()
{
    //Finds the first character in the character LL
    characterNode *temp = getCharacterListRoot();

    //Traverses through the character node LL
    while (temp != NULL)
    {
        //Adds a vertex for each character in the LL
        vertices.push_back(createVertex(temp));
        temp = temp->next;
    }
}

// Adds an edge to the vertices vector.
void GameEngine::addEdge()
{
    // Loop that finds all the enemies and add edges to all the vertices.
    for (int i = 0; i < vertices.size(); i++)
    {
        for (int j = 0; j < vertices.size(); j++)
        {
            if (vertices[i].character->enemy != vertices[j].character->enemy)
            {
                Edge av;
                av.v = &vertices[j];
                vertices[i].Edges.push_back(av);
            }
        }
    }
}

// Creates the graph needed to initiate battle.
void GameEngine::buildBattle()
{
    //Checks if there are characters in the characters LL and prints error if empty
    if (characterListRoot == NULL)
    {
        std::cout << "No characters exist, combat cannot begin. Please add characters." << std::endl;
        return;
    }

    //Creates all vertices of characters
    addVertex();

    //Creates an edge between characters
    addEdge();
}

// Prints list of enemy characters.
void GameEngine::printEnemy()
{
    std::cout << "\n=======================" << std::endl;
    characterNode *temp = characterListRoot;
    while (temp != NULL)
    {
        if (temp->enemy == true && temp->alive == true)
        {
            std::cout << "Character Name: " << temp->characterName << " || Health: " << temp->characterHealth << " || Speed: " << temp->characterSpeed << " || Strength: " << temp->characterStrength << std::endl;
        }
        temp = temp->next;
    }
}

// Print list of non-enemy characters
void GameEngine::printFriendly()
{
    std::cout << "\n=======================" << std::endl;
    characterNode *temp = characterListRoot;
    while (temp != NULL)
    {
        if (temp->enemy == false)
        {
            std::cout << "Character Name: " << temp->characterName << " || Health: " << temp->characterHealth << " || Speed: " << temp->characterSpeed << " || Strength: " << temp->characterStrength << std::endl;
        }
        temp = temp->next;
    }
}

// Sorts the character array to determine turn order by using characterSpeed.
void GameEngine::sort(characterNode *arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j]->characterSpeed < arr[j + 1]->characterSpeed)
            {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Asks the user on how to proceed with the battle.
void GameEngine::decisionPhase()
{
    // Sets all the turns to zero.
    reset();

    // Declaration for iteration and replacement.
    int iterator = 0;
    bool replace = true;

    // Declaration for user input.
    std::string input;
    arr[vertices.size()];

    // Prints a list of the friendly characters.
    std::cout << std::endl;
    std::cout << "These are friendly characters:";
    printFriendly();

    // Prints a list of the enemy characters.
    std::cout << std::endl;
    std::cout << "These are enemy characters:";
    printEnemy();

    // Makes an array with all the characters inside.
    for (int i = 0; i < vertices.size(); i++)
    {
        arr[i] = vertices[i].character;
    }

    // Calls the sort function to sort the array by turn order.
    sort(arr, vertices.size());

    // Loop that dictates turn order.
    while (replace)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (arr[iterator]->characterName == vertices[i].character->characterName)
            {
                vertices[i].turn += 1;
            }
        }
        iterator++;
        if (iterator == vertices.size())
        {
            break;
        }
    }

    // Prints a list of turn orders and whether or not they are enemies or friends.
    iterator = 1;
    std::cout << std::endl;
    std::cout << "This is the order by which each character will act. Use it to decide who you want to attack.";
    std::cout << "\n=======================" << std::endl;
    for (int i = 0; i < vertices.size(); i++)
    {
        std::cout << iterator++ << ") "
                  << "Name: " << arr[i]->characterName << " || ";
        if (arr[i]->enemy == true)
        {
            std::cout << "Enemy" << std::endl;
        }
        else
        {
            std::cout << "Friendly" << std::endl;
        }
    }
}

// Shows and displays all the attack options as well as the enemy's moves.
void GameEngine::attack(characterNode *character, bool enemyOrNot)
{
    // Declarations for character input.
    std::string input;
    int iterator = 0;
    bool choice = true;

    // Increases iterater if the characterNode pointer is an enemy.
    if (enemyOrNot)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (arr[i]->enemy != true && arr[i]->alive == true)
            {
                iterator = i;
                break;
            }
        }

        // Print statements.
        arr[iterator]->characterHealth = arr[iterator]->characterHealth - character->characterStrength;

        std::cout << arr[iterator]->characterName << " was attacked by " << character->characterName << ", losing " << character->characterStrength << " HP." << std::endl;

        // Prints if the character has died or their HP if they are still alive.
        if (arr[iterator]->characterHealth <= 0)
        {
            std::cout << arr[iterator]->characterName << " has died. RIP." << std::endl;
            arr[iterator]->alive = false;
            return;
        }
        else
        {
            std::cout << arr[iterator]->characterName << " has " << arr[iterator]->characterHealth << " HP left." << std::endl;
        }
    }
    // If the characterNode pointer passed in is not an enemy, this will run.
    else if (enemyOrNot == false)
    {
        while (choice)
        {
            // Prints the enemy list for the user to chose from.
            printEnemy();

            // Asks the user who they want to attack
            std::cout << "Who do you want to attack?" << std::endl;
            std::getline(std::cin, input);

            // Checks that the enetered name is a valid name.
            for (int i = 0; i < vertices.size(); i++)
            {
                if (input != vertices[i].character->characterName && i == vertices.size())
                {
                    std::cout << "Please enter a valid enemy name." << std::endl;
                }
                if (input == vertices[i].character->characterName)
                {
                    iterator = i;
                    choice = false;
                    break;
                }
            }
        }

        // Prints who was attacked and for how much HP.
        std::cout << character->characterName << " attacked " << input << ", dealing " << character->characterStrength << " damage." << std::endl;

        // Prints the characters HP remaining after the attack.
        getCharacter(input)->characterHealth = getCharacter(input)->characterHealth - character->characterStrength;
        if (getCharacter(input)->characterHealth <= 0)
        {
            std::cout << input << " has 0 hp left." << std::endl;
        }
        else
        {
            std::cout << input << " has " << getCharacter(input)->characterHealth << " HP left." << std::endl;
        }

        // If the remaining HP of the attack character is 0, prints that they have died.
        if (getCharacter(input)->characterHealth <= 0)
        {
            std::cout << "You killed " << getCharacter(input)->characterName << std::endl;
            getCharacter(input)->alive = false;
            return;
        }
    }
}

// Runs through the battle phase with the decisions.
void GameEngine::battlePhase()
{
    // Variable declarations for the battle phase.
    bool combat = true;
    bool playerAlive = true;
    bool enemyAlive = true;
    std::cout << "-=== BATTLE PHASE ===-" << std::endl;

    // This loop keeps running as long as there is a friendly character and enemy character alive.
    while (playerAlive == true && enemyAlive == true)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (arr[i]->enemy == true && arr[i]->alive == true)
            {
                combat = true;
                //std::cout << arr[i] << " attacks one of your characters." << std::endl;
                attack(arr[i], combat);
            }
            else if (arr[i]->enemy != true && arr[i]->alive == true)
            {
                combat = false;
                std::cout << "It is your turn to attack" << std::endl;
                attack(arr[i], combat);
            }

            // If there are not any friends or enemies left then the battle phase is over.
            if (!playerCharactersAlive())
            {
                std::cout << "All your characters are dead. You lose." << std::endl;
                delete[]&arr;
                vertices.clear();
                //Edges.clear();
                return;
            }
            if (!enemyCharactersAlive())
            {
                std::cout << "All enemy characters are dead. You win this engagement." << std::endl;
                resetEnemyHealth();
                delete[]&arr;
                vertices.clear();
                //Edges.clear();
                return;
            }
        }
    }
}

// Resets the enemy health for the next battle.
void GameEngine::resetEnemyHealth()
{
    characterNode *temp = characterListRoot;
    while (temp != NULL)
    {
        if (temp->enemy == true)
        {
            temp->characterHealth = temp->originalHealth;
            temp->alive = true;
        }
        temp = temp -> next;
    }
}

void GameEngine::resetPlayerHealth()
{
    characterNode *temp = characterListRoot;
    while (temp != NULL)
    {
        if (temp->enemy == false)
        {
            temp->characterHealth = temp->originalHealth;
            temp->alive = true;
        }
        temp = temp -> next;
    }
}

// Checks if any friendly characters are alive.
bool GameEngine::enemyCharactersAlive()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (arr[i]->enemy == true && arr[i]->alive == true)
        {
            return true;
        }
    }
    return false;
}

// Checks if any friendly characters are alive.
bool GameEngine::playerCharactersAlive()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (arr[i]->enemy == false && arr[i]->alive == true)
        {
            return true;
        }
    }
    return false;
}

// Displays a map between all characters in the combat graph (NOT USED - TEST FUNCTION).
void GameEngine::displayEdges()
{
    std::cout << "In Function" << std::endl;

    for (int i = 0; i < vertices.size(); i++)
    {
        std::cout << "name" << std::endl;
        std::cout << vertices[i].character->characterName;

        for (int j = 0; j < vertices[i].Edges.size(); j++)
        {
            std::cout << " --> " << vertices[i].Edges[j].v->character->characterName;
        }
        std::cout << std::endl;
    }
}

// Resets turn counter for each user once all characters have gone.
void GameEngine::setAllTurnsZero()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i].turn = 0;
    }
}

void GameEngine::reset()
{

}
