#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>

#include "GameEngine.hpp"

// CONSTRUCTOR.
GameEngine::GameEngine()
{
  storyTreeRoot = NULL;
  numEvents = 0;

  characterListRoot = NULL;
}

// Helper function used in ~GameEngine(). Clears memory associated with the storyTree.
void treeDestructor(storyNode *storyTreeRoot)
{
  // Returns if storyTreeRoot is NULL.
  if (storyTreeRoot == NULL)
  {
    return;
  }
  // Else deletes the storyTreeRoot and sets it equal to NULL.
  else
  {
    // Call to each branch of storyTreeRoot.
    treeDestructor(storyTreeRoot->choice1);
    treeDestructor(storyTreeRoot->choice2);
    treeDestructor(storyTreeRoot->choice3);

    delete storyTreeRoot;
    storyTreeRoot = NULL;
  }
}

// DESTRUCTOR.
GameEngine::~GameEngine()
{
  // Calls treeDestuctor() to delete all nodes in the storyTree.
  treeDestructor(storyTreeRoot);

  // Declarations to delete nodes characterList.
  characterNode *current = characterListRoot;
  characterNode *next;

  // Loop that deletes all nodes in the characterList.
  while (current != NULL)
  {
    next = current->next;
    delete current;
    current = next;
  }
}

// Function used to sample the entire game with combat.
void GameEngine::sampleProjectGameEngine()
{
  // Returns when the story has not been created yet.
  if (storyTreeRoot == NULL)
  {
    std::cout << "Story tree is empty." << std::endl;
    return;
  }

  // Variable declarations to parse through storyTree.
  storyNode *temp = storyTreeRoot;

  // Runs through the story tree using the users inputs.
  while (temp != NULL)
  {
    // Prints the event description.
    std::cout << temp->eventDescription << std::endl;

    // Checks if combat is enable for the current node and exexcutes combat function if true.
    if (temp->combat == true)
    {
      // Declarations to check for combat compatibility.
      characterNode *temp2 = getCharacterListRoot();

      bool hasEnemy = false;
      bool hasFriend = false;

      // If both enemies and friends exist, then combat is allowed.
      while(temp2 != NULL)
      {
        if(temp2 -> enemy)
        {
          hasEnemy = true;
        }
        else
        {
          hasFriend = true;
        }
        
        temp2 = temp2->next;
      }

      // If at least one enemy exists within the characterList.
      if (hasEnemy && hasFriend)
      {
        buildBattle();
        decisionPhase();
        battlePhase();
      }
    }

    // Prints choice 1 if available.
    if (temp->choice1 != NULL)
    {
      std::cout << "Choice 1: " << temp->choice1Description << std::endl;
    }

    // Prints choice 2 if available.
    if (temp->choice2 != NULL)
    {
      std::cout << "Choice 2: " << temp->choice2Description << std::endl;
    }

    // Prints choice 3 if available.
    if (temp->choice3 != NULL)
    {
      std::cout << "Choice 3: " << temp->choice3Description << std::endl;
    }

    // Prints game over if there are no choices to be made.
    if (temp->choice1 == NULL && temp->choice2 == NULL && temp->choice3 == NULL)
    {
      std::cout << "GAME OVER. Thanks for playing!" << std::endl;
      resetPlayerHealth();
      resetEnemyHealth();
      return;
    }

    // Delcarations for user input.
    std::string input;
    std::cout << "Please make a choice of the above options." << std::endl;
    std::getline(std::cin, input);

    bool checkChoice = true;

    // Loop that checks the user's choice to make sure it is allowed.
    while (checkChoice)
    {
      if (temp->choice1 != NULL && input == "1")
      {
        temp = temp->choice1;
        checkChoice = false;
      }
      else if (temp->choice2 != NULL && input == "2")
      {
        temp = temp->choice2;
        checkChoice = false;
      }
      else if (temp->choice3 != NULL && input == "3")
      {
        temp = temp->choice3;
        checkChoice = false;
      }
      else
      {
        std::cout << "Please enter a valid choice." << std::endl;
        std::getline(std::cin, input);
      }
    }
  }
}

// Helper for saveToFUle(). Saves the textual data within the characterList to an
// external file.
void GameEngine::saveCharacterNode()
{
  // Declaration of an output file.
  std::ofstream output("outputCharacterNode.txt");
  if (output.is_open())
  {
    // Declarations to parse through characterList.
    characterNode *root = characterListRoot;
    while (root != NULL)
    {
      // Outputs the stats of a character to the text file.
      output << "Name: " << root->characterName << "\n";
      output << "Speed: " << root->characterHealth << "\n";
      output << "Strength: " << root->characterStrength << "\n";
      output << "Speed: " << root->characterSpeed << "\n";
      if (root->enemy == true)
      {
        output << "Enemy: true"
               << "\n";
      }
      else
      {
        output << "Enemy: false"
               << "\n";
      }
      root = root->next;
    }
  }
  // If opening the output file fails for any reason, displays the error to the user.
  else
  {
    std::cout << "Unable to open outputCharacterNode.txt" << std::endl;
  }
}

// Helper function used to print storyTree events to an external text file.
void storyTreeRecursion(storyNode *storyTreeRoot)
{
  // Declaration of an output file.
  std::ofstream output("outputStoryTree.txt", std::ios_base::app | std::ios_base::out);
  output << "hello";

  // If the storyTreeRoot is NULL, there there is no data to export.
  if (storyTreeRoot == NULL)
  {
    return;
  }

  // Exports the ID of the current storyTree node.
  output << "Current ID : " << storyTreeRoot->id;

  // Exports whether or no the current storyTree node has combat.
  if (storyTreeRoot->combat == true)
  {
    output << " (C)"
           << "\n";
  }
  else
  {
    output << "\n";
  }

  // Loop that outputs the branch Ids and their descriptions.
  if (storyTreeRoot->choice1 != NULL)
  {
    output << " Branch 1 ID : " << storyTreeRoot->choice1->id << "\n";
  }
  else
  {
    output << " Branch 1 ID : Does Not Exist"
           << "\n";
  }

  if (storyTreeRoot->choice2 != NULL)
  {
    output << " Branch 2 ID : " << storyTreeRoot->choice2->id << "\n";
  }
  else
  {
    output << " Branch 2 ID : Does Not Exist"
           << "\n";
  }

  if (storyTreeRoot->choice3 != NULL)
  {
    output << " Branch 3 ID : " << storyTreeRoot->choice3->id << "\n";
  }
  else
  {
    output << " Branch 3 ID : Does Not Exist"
           << "\n";
  }

  // Outputs the remaining storyTree nodes.
  storyTreeRecursion(storyTreeRoot->choice1);
  storyTreeRecursion(storyTreeRoot->choice2);
  storyTreeRecursion(storyTreeRoot->choice3);
}

// Saves storyTree data to an external file.
void GameEngine::saveStoryTree()
{
  // Calls storyTreeRecursion to save story nodes.
  storyTreeRecursion(storyTreeRoot);
}

// Saves the textual data within existing data structures to an external file.
void GameEngine::saveToFile()
{
  // Calls to saveCharacterNode() and saveStoryTree().
  // Saves storyTree data and characterList data to an external file.
  saveCharacterNode();
  saveStoryTree();
}

// Demos the story tree using user input choices without combat.
void GameEngine::demoEvents()
{
  // Returns when the story has not been created yet.
  if (storyTreeRoot == NULL)
  {
    std::cout << "Story tree is empty." << std::endl;
    return;
  }

  // Variable declarations.
  storyNode *temp = storyTreeRoot;

  // Runs through the story tree using the users inputs.
  while (temp != NULL)
  {
    // Prints the event description.
    std::cout << temp->eventDescription << std::endl;

    // Prints choice 1 if available.
    if (temp->choice1 != NULL)
    {
      std::cout << "Choice 1: " << temp->choice1Description << std::endl;
    }

    // Prints choice 2 if available.
    if (temp->choice2 != NULL)
    {
      std::cout << "Choice 2: " << temp->choice2Description << std::endl;
    }

    // Prints choice 3 if available.
    if (temp->choice3 != NULL)
    {
      std::cout << "Choice 3: " << temp->choice3Description << std::endl;
    }

    // Prints game over if there are no choices to be made.
    if (temp->choice1 == NULL && temp->choice2 == NULL && temp->choice3 == NULL)
    {
      std::cout << "GAME OVER. Thanks for playing!" << std::endl;
      return;
    }

    // Asks the user to make a choice from the above options.
    std::string input;
    std::cout << "Please make a choice of the above options." << std::endl;
    std::getline(std::cin, input);

    bool checkChoice = true;

    // Loop that checks if the user input was correct.
    while (checkChoice)
    {
      if (temp->choice1 != NULL && input == "1")
      {
        temp = temp->choice1;
        checkChoice = false;
      }
      else if (temp->choice2 != NULL && input == "2")
      {
        temp = temp->choice2;
        checkChoice = false;
      }
      else if (temp->choice3 != NULL && input == "3")
      {
        temp = temp->choice3;
        checkChoice = false;
      }
      // Prints an error statement if the user's input was non-valid and accepts another input.
      else
      {
        std::cout << "Please enter a valid choice." << std::endl;
        std::getline(std::cin, input);
      }
    }
  }
}

// Helper function that allows the user to construct their story.
void insertEventReccursion(storyNode *storyTreeRoot, int *numEvents, storyNode *_parent)
{
  // Declaration of variables for user input.
  std::string event;
  std::string choice;
  std::string eventDescription;

  // Asks user for the event description and accepts and answer.
  std::cout << "\n\nEnter description for this event:" << std::endl;
  std::getline(std::cin, event);

  // Constructs the storyTreeNode with the event description entered above.
  storyTreeRoot->eventDescription = event;
  storyTreeRoot->id = ++(*numEvents);
  storyTreeRoot->choice1 = NULL;
  storyTreeRoot->choice2 = NULL;
  storyTreeRoot->choice3 = NULL;

  // Asks the user if the event has combat in it and accepts an answer.
  std::string isCombat;
  std::cout << "Is this a combat event? (Y/N)" << std::endl;
  std::getline(std::cin, isCombat);

  // Checks that the user input is correct.
  while (!(isCombat == "Y" || isCombat == "N" || isCombat == "y" || isCombat == "n"))
  {
    std::cout << "Invalid Entry. Please enter Y for yes or N for no." << std::endl;
    std::getline(std::cin, isCombat);
  }

  // If no, the combat of the node is set to false.
  if (isCombat == "n" || isCombat == "N")
  {
    storyTreeRoot->combat = false;
  }

  storyTreeRoot->parent = _parent;
  _parent = storyTreeRoot;

  //Make choice 1.
  std::cout << "\nCurrent Event: " << storyTreeRoot->eventDescription << std::endl;
  std::cout << "Would you like to add another choice to this branch (1/3)? (Y/N)" << std::endl;
  std::getline(std::cin, choice);

  // Checks user input to see if it is correct.
  while (!(choice == "Y" || choice == "N" || choice == "y" || choice == "n"))
  {
    std::cout << "Invalid Entry. Please enter Y for yes or N for no." << std::endl;
    std::getline(std::cin, choice);
  }

  // If, no then the function returns.
  if (choice == "N" || choice == "n")
  {
    return;
  }

  // Asks the user for the choice description and accepts an input.
  std::cout << "\nEnter the choice description: " << std::endl;
  std::getline(std::cin, eventDescription);

  // Builds the storyNode with the choice description and recursively calls the function.
  storyTreeRoot->choice1Description = eventDescription;
  storyTreeRoot->choice1 = new storyNode;
  insertEventReccursion(storyTreeRoot->choice1, numEvents, _parent);

  //Make choice 2.
  std::cout << "\nCurrent Event: " << storyTreeRoot->eventDescription << std::endl;
  std::cout << "Would you like to add another choice to this branch (2/3)? (Y/N)" << std::endl;
  std::getline(std::cin, choice);

  // Checks user input to see if it is correct.
  while (!(choice == "Y" || choice == "N" || choice == "y" || choice == "n"))
  {
    std::cout << "Invalid Entry. Please enter Y for yes or N for no." << std::endl;
    std::getline(std::cin, choice);
  }

  // If no, then the function returns.
  if (choice == "N" || choice == "n")
  {
    return;
  }

  // Asks the user for the choice description and accepts an input.
  std::cout << "\nEnter the choice description: " << std::endl;
  std::getline(std::cin, eventDescription);

  // Builds the storyNode with the choice description and recursively calls the function.
  storyTreeRoot->choice2Description = eventDescription;
  storyTreeRoot->choice2 = new storyNode;
  insertEventReccursion(storyTreeRoot->choice2, numEvents, _parent);

  //Make choice 3.
  std::cout << "\nCurrent Event: " << storyTreeRoot->eventDescription << std::endl;
  std::cout << "Would you like to add another choice to this branch (3/3)? (Y/N)" << std::endl;
  std::getline(std::cin, choice);

  // Checks user input to see if it is correct.
  while (!(choice == "Y" || choice == "N" || choice == "y" || choice == "n"))
  {
    std::cout << "Invalid Entry. Please enter Y for yes or N for no." << std::endl;
    std::getline(std::cin, choice);
  }

  // If no, then the function returns.
  if (choice == "N" || choice == "n")
  {
    return;
  }

  // Asks the user for the choice description and accepts an input.
  std::cout << "\nEnter the choice description: " << std::endl;
  std::getline(std::cin, eventDescription);

  // Builds the storyNode with the choice description and recursively calls the function.
  storyTreeRoot->choice3Description = eventDescription;
  storyTreeRoot->choice3 = new storyNode;
  insertEventReccursion(storyTreeRoot->choice3, numEvents, _parent);
}

// Inserts all the events inside the story tree.
void GameEngine::insertEvent()
{
  // Constructs the storyTree using inserEventRecusion().
  storyTreeRoot = new storyNode;
  insertEventReccursion(storyTreeRoot, &numEvents, NULL);
}

// Helper that deletes all nodes of a single event.
void deleteAllEvent(storyNode *deleteNode)
{
  // If statements that check if the parent's choice pointers exists and sets them to NULL if needed.
  if (deleteNode->parent->choice1 == deleteNode)
  {
    deleteNode->parent->choice1 = NULL;
  }
  if (deleteNode->parent->choice2 == deleteNode)
  {
    deleteNode->parent->choice2 = NULL;
  }
  if (deleteNode->parent->choice3 == deleteNode)
  {
    deleteNode->parent->choice3 = NULL;
  }

  // Calls the function recusively if the deleteNode (and all choices after it) are not NULL.
  if (deleteNode->choice1 != NULL)
  {
    deleteAllEvent(deleteNode->choice1);
  }
  if (deleteNode->choice2 != NULL)
  {
    deleteAllEvent(deleteNode->choice2);
  }
  if (deleteNode->choice3 != NULL)
  {
    deleteAllEvent(deleteNode->choice3);
  }

  // Deletion of the current node.
  delete deleteNode;
  deleteNode = NULL;
}

// Deletes a story node with a given id along with all subsiquent choices.
void GameEngine::deleteEvent(int _id)
{
  // Declaration for user input.
  std::string choice;

  // Ensures that the user knows that they are deleting all the events after the deleteNode.
  std::cout << "WARNING: All story events after this will be deleted. Would you like to continue (Y/N)?" << std::endl;
  std::getline(std::cin, choice);

  // Checks that the user input is correct.
  while (!(choice == "Y" || choice == "N" || choice == "y" || choice == "n"))
  {
    std::string choice;
    std::cout << "Invalid Entry. Please enter Y for yes or N for no.\nWARNING: All story events after this will be deleted. Would you like to continue (Y/N)?" << std::endl;
    std::getline(std::cin, choice);
  }

  // If no, then the function returns.
  if (choice == "N" || choice == "n")
  {
    return;
  }

  // Sets deleteNode to the storyNode with the proper ID and deletes it.
  storyNode *deleteNode = searchEvent(_id);

  // If the root is being deleted.
  if(deleteNode == storyTreeRoot)
  {
    delete storyTreeRoot;
    storyTreeRoot = NULL;
    return;
  }

  deleteAllEvent(deleteNode);
}

// Prints the editEventUI.
void editEventUI()
{
  std::cout << "-=== EDIT OPTIONS ===-" << std::endl;
  std::cout << "1. Change Event Description" << std::endl;
  std::cout << "2. Change Choice 1 Description" << std::endl;
  std::cout << "3. Change Choice 2 Description" << std::endl;
  std::cout << "4. Change Choice 3 Description" << std::endl;
  std::cout << "5. Change Combat Setting" << std::endl;
  std::cout << "6. Exit Edit Options" << std::endl;
}

// Edits an event to change its contents.
void GameEngine::editEvent(int _id)
{
  // Delcaration of temp.
  storyNode *temp = searchEvent(_id);

  // Declarations for editEventUI and user input.
  bool editEventUIOn = true;
  int editEventUIChoice = 0;
  std::string input;

  // Keeps editEventUIOn.
  while (editEventUIOn)
  {
    // Switch statement for editEventUI.
    switch (editEventUIChoice)
    {
    case 1:

      // Displays the current event of the node to the user and asks them to change it.
      std::cout << "Current Event Description: \n"
                << temp->eventDescription << std::endl;
      std::cout << "Please enter the new event description:" << std::endl;
      std::getline(std::cin, input);

      // Changes the eventDescription of the current node.
      temp->eventDescription = input;

      editEventUIChoice = 0;
      break;

    case 2:

      // Allows the user to edit choice1 if it is not NULL.
      if (temp->choice1 == NULL)
      {
        std::cout << "Unable to edit choice 1 description because it does not exist."
                  << std::endl;

        editEventUIChoice = 0;
        break;
      }

      // Changes choice1Description to user input.
      std::cout << "Current Choice 1 Description: \n"
                << temp->choice1Description << std::endl;
      std::cout << "Please enter the new choice 1 description:" << std::endl;
      std::getline(std::cin, input);

      temp->choice1Description = input;

      editEventUIChoice = 0;
      break;

    case 3:

      // Allows the user to edit choice2 if it is not NULL.
      if (temp->choice2 == NULL)
      {
        std::cout << "Unable to edit choice 2 description because it does not exist." << std::endl;

        editEventUIChoice = 0;
        break;
      }

      // Changes choice2Description to user input.
      std::cout << "Current Choice 2 Description: \n"
                << temp->choice2Description << std::endl;
      std::cout << "Please enter the new choice 2 description:" << std::endl;
      std::getline(std::cin, input);

      temp->choice2Description = input;

      editEventUIChoice = 0;
      break;

    case 4:

      // Allows the user to edit choice3 if it is not NULL.
      if (temp->choice3 == NULL)
      {
        std::cout << "Unable to edit choice 3 description because it does not exist." << std::endl;

        editEventUIChoice = 0;
        break;
      }

      // Changes choice3Description to user input.
      std::cout << "Current Choice 3 Description: \n"
                << temp->choice3Description << std::endl;
      std::cout << "Please enter the new choice 3 description:" << std::endl;
      std::getline(std::cin, input);

      temp->choice3Description = input;

      editEventUIChoice = 0;
      break;

    case 5:

      // Loop that checks if combat is true and allows the user to change it.
      if (temp->combat == true)
      {
        std::cout << "Current combat setting is set to true." << std::endl;
        std::cout << "Please enter the new combat setting (1 for true, 0 for false):" << std::endl;
        std::getline(std::cin, input);

        while (!(input == "1" || input == "0"))
        {
          std::cout << "Please enter 1 for true or 0 for false." << std::endl;
          std::getline(std::cin, input);
        }

        if (input == "1")
        {
          temp->combat = true;
        }
        else if (input == "0")
        {
          temp->combat = false;
        }
      }
      // Loop that checks if combat is false and allows the user to change it.
      else if (temp->combat == false)
      {
        std::cout << "Current combat setting is set to false." << std::endl;
        std::cout << "Please enter the new combat setting (1 for true, 0 for false):" << std::endl;
        std::getline(std::cin, input);

        while (!(input == "1" || input == "0"))
        {
          std::cout << "Please enter 1 for true or 0 for false." << std::endl;
          std::getline(std::cin, input);
        }

        if (input == "1")
        {
          temp->combat = true;
        }
        else if (input == "0")
        {
          temp->combat = false;
        }
      }

      editEventUIChoice = 0;
      break;

    case 6:

      // Exits the editEventUI.
      editEventUIOn = false;
      editEventUIChoice = 0;
      break;

    default:

      // Prints editEventUI() and asks for user input.
      editEventUI();
      std::getline(std::cin, input);
      editEventUIChoice = stoi(input);
    }
  }
}

// Stores all storyNode pointers that exist within the tree to a vector.
void updateVec(storyNode *root, std::vector<storyNode*> *vec)
{
  if (root == NULL)
  {
    return;
  }
  
  // Stores root.
  vec -> push_back(root);
  
  // Stores all nodes recursively.
  updateVec(root -> choice1, vec);
  updateVec(root -> choice2, vec);
  updateVec(root -> choice3, vec);
}

// Finds an storyNode pointer within the vector.
storyNode *findEvent(std::vector<storyNode*> vec, int _id)
{
  for (int i = 0; i < vec.size(); i++)
  {
    if (vec[i] -> id == _id)
    {
      return vec[i];
    }
  }
  return NULL;
}

// Searches for an event with a given ID.
storyNode *GameEngine::searchEvent(int _id)
{
  // Declaration of a vector to store storyNodes.
  std::vector<storyNode*> vec;
  // Call to update vector.
  updateVec(storyTreeRoot, &vec);
  return findEvent(vec, _id);
}

// Allows the user to view an event with a specific id.
void GameEngine::viewEvent(int id)
{
  // Defines the temp storyNode as a node with a specific ID.
  storyNode *temp = searchEvent(id);

  // If the node was not found, then a print statement saying it doesn't exist is printed.
  if (temp == NULL)
  {
    std::cout << "Event ID does not exist in tree. Print the ID tree to see available options." << std::endl;
  }
  // Prints all relevant data within the storyNode if it is found.
  else
  {
    // Prints id.
    std::cout << "The ID of this tree is: " << temp->id << std::endl;

    // Prints event description.
    std::cout << "Event description is: " << std::endl;
    std::cout << temp->eventDescription << std::endl;

    // Prints the description of all the choices.
    std::cout << "Choice 1 description is: " << std::endl;
    std::cout << temp->choice1Description << std::endl;
    std::cout << "Choice 2 description is: " << std::endl;
    std::cout << temp->choice2Description << std::endl;
    std::cout << "Choice 3 description is: " << std::endl;
    std::cout << temp->choice3Description << std::endl;

    // Prints whether or not combat is assigned to the storyNode.
    if (temp->combat == true)
    {
      std::cout << "Combat is set to true for this node." << std::endl;
    }
    else
    {
      std::cout << "Combat is set to false for this node." << std::endl;
    }
  }
}

// Getter function for numEvents.
int GameEngine::getNumEvents()
{
  // Return numEvents.
  return numEvents;
}

// Helper function for printIDTree(). Prints a 2D representation of the
// story tree using ids.
void printIDHelper(storyNode *storyTreeRoot)
{
  // Returns if the tree is empty because there is nothing to print.
  if (storyTreeRoot == NULL)
  {
    return;
  }

  // Prints the ID of the current storyNode.
  std::cout << "Current ID : " << storyTreeRoot->id;

  // Prints whether or not there is combat in the node.
  if (storyTreeRoot->combat == true)
  {
    std::cout << " (C)" << std::endl;
  }
  else
  {
    std::cout << std::endl;
  }

  // Loop that prints the branch IDs.
  if (storyTreeRoot->choice1 != NULL)
  {
    std::cout << " Branch 1 ID : " << storyTreeRoot->choice1->id << std::endl;
  }
  else
  {
    std::cout << " Branch 1 ID : Does Not Exist" << std::endl;
  }

  if (storyTreeRoot->choice2 != NULL)
  {
    std::cout << " Branch 2 ID : " << storyTreeRoot->choice2->id << std::endl;
  }
  else
  {
    std::cout << " Branch 2 ID : Does Not Exist" << std::endl;
  }

  if (storyTreeRoot->choice3 != NULL)
  {
    std::cout << " Branch 3 ID : " << storyTreeRoot->choice3->id << std::endl;
  }
  else
  {
    std::cout << " Branch 3 ID : Does Not Exist" << std::endl;
  }

  // Recursive calls of printIDHelper.
  printIDHelper(storyTreeRoot->choice1);
  printIDHelper(storyTreeRoot->choice2);
  printIDHelper(storyTreeRoot->choice3);
}

// Calls the printIDTreeHelper to print a 2D tree.
void GameEngine::printIDTree()
{
  // If the storyTreeRoot is NULL, then the storyTree is empty.
  if (storyTreeRoot == NULL)
  {
    std::cout << "Tree is Empty" << std::endl;
    return;
  }

  // Calls printIDHelper() if the tree isn't empty.
  printIDHelper(storyTreeRoot);
}

// Getter function for storyTreeRoot.
storyNode *GameEngine::getStoryTreeRoot()
{
  // Returns storyTreeRoot.
  return storyTreeRoot;
}

// Helper to fixID
void fixIdHelper(storyNode *root, int *numEvents)
{
  //Check if the current node it root
  if (root == NULL)
  {
    return;
  }

  //Make num events bigger by 1 at the address and set id
  root->id = ++*numEvents;
  
  //Run through recursion
  fixIdHelper(root->choice1, numEvents);
  fixIdHelper(root->choice2, numEvents);
  fixIdHelper(root->choice3, numEvents);
}

// Reset ID to be in order of left to right
void GameEngine::fixID()
{
  //Initialize variables
  int eventCounter = 0;
  
  //Run helper to set correct id for tree node
  fixIdHelper(storyTreeRoot, &eventCounter);

  //Update numEvents
  numEvents = eventCounter;
}