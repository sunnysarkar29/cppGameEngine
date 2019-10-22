#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <iomanip>

// storyNode struct to carry information of each story event.
struct storyNode
{
    int id = -1;

    std::string eventDescription;

    storyNode *choice1 = NULL;
    std::string choice1Description;

    storyNode *choice2 = NULL;
    std::string choice2Description;

    storyNode *choice3 = NULL;
    std::string choice3Description;

    bool combat = true;

    storyNode *parent = NULL;
};

// characterNode struct to carry information of each character.
struct characterNode
{
    std::string characterName;

    int characterHealth; // Dictates HP.
    int originalHealth;

    int characterStrength; // Dictates damage.
    int characterSpeed;    // Dictates turn order.

    bool enemy;
    bool alive;

    characterNode *next;
};

// Edge struct delcared for use in the Vertex struct.
struct Edge;

// Vertex struct to carry information of each combat character.
struct Vertex
{
    characterNode *character;
    int turn;
    std::vector<Edge> Edges;
};

// Edge struct to be used in Vertex.
struct Edge
{
    Vertex *v;
};

// GameEngine class definition.
class GameEngine
{
  public:
    
    // GAMEENGINE FUNCTIONS.
    GameEngine();
    ~GameEngine();

    void saveToFile();
    void saveStoryTree();
    void saveCharacterNode();
    void saveCombatGraph();

    void sampleProjectGameEngine();

    // STORYTREE FUNCTIONS.
    void demoEvents();
    void insertEvent();
    void deleteEvent(int _id);
    void editEvent(int _id);
    storyNode *searchEvent(int _id);
    void viewEvent(int id);
    void printIDTree();
    int getNumEvents();
    storyNode *getStoryTreeRoot();
    void fixID();
    
    // CHARACTERLIST FUNCTIONS.
    void addCharacterNode();
    void deleteCharacterNode(std::string _characterName);
    void editCharacterNode();
    void printCharacters();
    
    characterNode *getCharacter(std::string characterName);
    characterNode *getCharacterListRoot();

    // COMBAT GRAPH FUNCTIONS.
    void addVertex();
    void addEdge();

    void buildBattle();
    void decisionPhase();
    void battlePhase();

    void displayEdges();
    void setAllTurnsZero();

    void printEnemy();
    void printFriendly();

    void sort(characterNode* arr[], int n);
    void attack(characterNode* character, bool enemyOrNot);

    bool playerCharactersAlive();
    bool enemyCharactersAlive();

    void resetEnemyHealth();
    void resetPlayerHealth();
    void reset();


  private:

    // STORYTREE DECLARATIONS.
    int numEvents;
    storyNode *storyTreeRoot;

    // CHARACTERLIST DECLARATIONS.
    characterNode *characterListRoot;

    // COMBATGRAPH DECLARATIONS.
    std::vector<Vertex> vertices;

    int enemiesLeft;

    characterNode *arr[];
};