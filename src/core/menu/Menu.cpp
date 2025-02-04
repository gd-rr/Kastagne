#include "Menu.h"
#include <iostream>

Menu::Menu() : m_menuItems(),
               m_menuCurrentItems(),
               m_menuIndex(),
               m_quit(),
               m_inCharacterSelection(),
               m_exitGame(true),
               m_currentPath(nullptr){

}


Menu::~Menu(){
    for (int i = 0; i < 10; i++){
        m_menuItems[i] = {};
    }

    m_menuCurrentItems = {};

    m_quit = true;
    m_inCharacterSelection = true;
    m_exitGame = false;
}

//initialize
void Menu::initialize(){
    m_menuItems[0] = {"Versus", "Training", "Options", "Exit Game"}; //Menu Principale
    m_menuItems[1] = {"Player VS Player", "Player VS CPU", "Return"}; //Menu Versus
    m_menuItems[2] = {"Characters selection", "Training options", "Return"}; //Menu Training
    m_menuItems[3] = {"Position", "Block", "Parry", "Counter", "Return"}; //Menu Training options
    m_menuItems[4] = {"Game options", "Keybinds", "Audio options", "Return"}; //Menu Options
    m_menuItems[5] = {"Round Time", "Round Number", "Damage level", "Return"}; //Menu Game options
    m_menuItems[6] = {"Player 1", "Player 2", "Return"}; //Menu Keybinds
    m_menuItems[7] = {"1", "1", "1", "1", "Return"}; //Menu Keybins player 1
    m_menuItems[8] = {"2", "2", "2", "2", "Return"}; //Menu Keybins player 2
    m_menuItems[9] = {"Main volume", "Voices volume", "Effects volume", "Music volume", "Return"}; //Menu Audio options

    m_menuCurrentItems = m_menuItems[0];

    m_menuIndex = 0;

    m_quit = true;
    m_inCharacterSelection = false;
    m_exitGame = true;

    m_currentPath = "data/images/menu/Menu1.png";
}

//updates
void Menu::updateEvent(int event){ //changer les keycode de eventmanager a game
    switch (event){
        case 1:
            if (m_menuIndex == 0) {
                m_menuIndex = m_menuCurrentItems.size() - 1;
            } else {
                m_menuIndex--;
            }
            break;
        case 2:
            if (m_menuIndex == (int) m_menuCurrentItems.size() - 1) {
                m_menuIndex = 0;
            } else {
                m_menuIndex++;
            }
            break;
        case 3:
            updatePath();
            update();
            break;
        default:
            break;
    }
}

void Menu::updatePath(){
    int i = rand()%4;
    if(i == 0){
        m_currentPath = "data/images/menu/Menu1.png";
    }
    else if(i == 1){
        m_currentPath = "data/images/menu/Menu2.png";
    }
    else if(i == 2){
        m_currentPath = "data/images/menu/Menu3.png";
    }
    else if(i == 3){
        m_currentPath = "data/images/menu/Menu4.png";
    }
}

void Menu::update(){
    //Menu Principale
    if(m_menuCurrentItems == m_menuItems[0]){
        if (m_menuIndex == 0){//Versus
            m_menuIndex = 0;
            m_menuCurrentItems = m_menuItems[1];
            return;
        }
        if (m_menuIndex == 1){//Training
            m_menuIndex = 0;
            m_menuCurrentItems = m_menuItems[2];
            return;
        }
        if (m_menuIndex == 2){//Options
            m_menuIndex = 0;
            m_menuCurrentItems = m_menuItems[4];
            return;
        }
        if (m_menuIndex == 3){//m_exitGame
            m_quit = !m_quit;
            m_exitGame = !m_exitGame;
        }
    }
    //Menu Versus
    if(m_menuCurrentItems == m_menuItems[1]){
        if (m_menuIndex == 0){//Player VS Player
            //lancer character Selection Player VS Player
            m_quit = !m_quit;
            m_inCharacterSelection = !m_inCharacterSelection;
        }
        if (m_menuIndex == 1){//Player VS CPU
            //lancer Character Selection Player VS CPU
        }
        if (m_menuIndex == 2){//Exit
            m_menuIndex = 0;
            m_menuCurrentItems = m_menuItems[0];
            return;
        }
    }
    //Menu Training
    if(m_menuCurrentItems == m_menuItems[2]){
        if (m_menuIndex == 0){//character selection
            //lancer character Selection Player alone for training
        }
        if (m_menuIndex == 1){//Training options
            m_menuIndex = 0;
            m_menuCurrentItems = m_menuItems[3];
            return;
        }
        if (m_menuIndex == 2){//Exit
            m_menuIndex = 0;
            m_menuCurrentItems = m_menuItems[0];
            return;
        }
    }
    //Menu Training Options
    if(m_menuCurrentItems == m_menuItems[3]){
        if (m_menuIndex == 0){//Position
            
        }
        if (m_menuIndex == 1){//Block
            
        }
        if (m_menuIndex == 2){//Parry
            
        }
        if (m_menuIndex == 3){//Counter
            
        }
        if (m_menuIndex == 4){//Exit
            m_menuIndex = 0;
            m_menuCurrentItems = m_menuItems[2];
            return;
        }
    }
    //Menu Options 
    if(m_menuCurrentItems == m_menuItems[4]){
        if (m_menuIndex == 0){//Game Options
            m_menuIndex = 0;
            m_menuCurrentItems = m_menuItems[5];
            return;
        }
        if (m_menuIndex == 1){//Keybinds
            m_menuIndex = 0;
            m_menuCurrentItems = m_menuItems[6];
            return;
        }
        if (m_menuIndex == 2){//Audio Options
            m_menuIndex = 0;
            m_menuCurrentItems = m_menuItems[9];
            return;
        }
        if (m_menuIndex == 3){//Exit
            m_menuIndex = 0;
            m_menuCurrentItems = m_menuItems[0];
            return;
        }
    }
    //Menu Game Options
    if(m_menuCurrentItems == m_menuItems[5]){
        if (m_menuIndex == 0){//Round Time
            
        }
        if (m_menuIndex == 1){//Round Number

        }
        if (m_menuIndex == 2){//Damage level
            
        }
        if (m_menuIndex == 3){//Exit
            m_menuIndex = 0;
            m_menuCurrentItems = m_menuItems[4];
            return;
        }
    }
    //Menu Keybinds
    if(m_menuCurrentItems == m_menuItems[6]){
        if (m_menuIndex == 0){//Player 1
            m_menuIndex = 0;
            m_menuCurrentItems = m_menuItems[7];
            return;
        }
        if (m_menuIndex == 1){//Player 2
            m_menuIndex = 0;
            m_menuCurrentItems = m_menuItems[8];
            return;
        }
        if (m_menuIndex == 2){//Exit
            m_menuIndex = 0;
            m_menuCurrentItems = m_menuItems[4];
            return;
        }
    }
    //Menu Keybinds Player 1
    if(m_menuCurrentItems == m_menuItems[7]){
        if (m_menuIndex == 0){//touche ???
            
        }
        if (m_menuIndex == 1){//touche ???

        }
        if (m_menuIndex == 2){//touche ???

        }
        if (m_menuIndex == 4){//touche ???

        }
        if (m_menuIndex == 4){//Exit
            m_menuIndex = 0;
            m_menuCurrentItems = m_menuItems[6];
            return;
        }
    }
    //Menu Keybinds Player 2
    if(m_menuCurrentItems == m_menuItems[8]){
        if (m_menuIndex == 0){//touche ???
            
        }
        if (m_menuIndex == 1){//touche ???

        }
        if (m_menuIndex == 2){//touche ???

        }
        if (m_menuIndex == 4){//touche ???

        }
        if (m_menuIndex == 4){//Exit
            m_menuIndex = 0;
            m_menuCurrentItems = m_menuItems[6];
            return;
        }
    }
    //Menu Audio options
    if(m_menuCurrentItems == m_menuItems[9]){
        if (m_menuIndex == 0){//Main volume
            
        }
        if (m_menuIndex == 1){//Voices volume

        }
        if (m_menuIndex == 2){//Effects volume
            
        }
        if (m_menuIndex == 3){//Music volume
            
        }
        if (m_menuIndex == 4){//Exit
            m_menuIndex = 0;
            m_menuCurrentItems = m_menuItems[4];
            return;
        }
    }
}

//getters
std::vector<std::string> Menu::getMenuCurrentItems(){
    return m_menuCurrentItems;
}

int Menu::getMenuIndex(){
    return m_menuIndex;
}

void Menu::setMenuIndex(int index){
    m_menuIndex = index;
}

const bool& Menu::getQuitMenu() const {
    return m_quit;
}

const bool& Menu::getInCharacterSelection() const{
    return m_inCharacterSelection;
}

const bool& Menu::getExitGame() const{
    return m_exitGame;
}

const char* Menu::getCurrentPath(){
    return m_currentPath;
}

// Test for the Menu class
void Menu::regressionTest(){
    // Initialize
    Menu menu;

    menu.initialize();

    // Test initialization
    assert(menu.getMenuCurrentItems() == menu.m_menuItems[0]);
    assert(menu.getMenuIndex() == 0);
    assert(menu.getQuitMenu() == true);
    assert(menu.getInCharacterSelection() == false);
    assert(menu.getExitGame() == true);
    assert(std::string(menu.getCurrentPath()) == "data/images/menu/Menu1.png");

    // Test updateEvent
    // Simulate moving down the menu
    menu.updateEvent(2); // Move down
    assert(menu.getMenuIndex() == 1);

    // Simulate moving up the menu
    menu.updateEvent(1); // Move up
    assert(menu.getMenuIndex() == 0);

    // Test update
    // Simulate selecting "Versus" in the main menu
    menu.update();
    assert(menu.getMenuCurrentItems() == menu.m_menuItems[1]);

    // Simulate moving up the menu
    menu.updateEvent(1); // Move up
    assert(menu.getMenuIndex() == 2);

    // Test update
    // Simulate selecting "Return" in the main menu
    menu.update();
    assert(menu.getMenuCurrentItems() == menu.m_menuItems[0]);

    // Test setMenuIndex
    menu.setMenuIndex(2);
    assert(menu.getMenuIndex() == 2);

}