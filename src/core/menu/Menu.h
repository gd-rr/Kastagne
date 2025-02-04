/*******************************************************************************
 * @file menu.h
 * @brief Defines the Menu class for managing the menu system.
 ******************************************************************************/

#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <cassert>

/*******************************************************************************
 * @class Menu
 * @brief Manages the menu system.
 ******************************************************************************/
class Menu {
private:
    std::vector<std::string> m_menuItems[10]; /**< tab of menu items. */
    std::vector<std::string> m_menuCurrentItems; /**< Current menu items being displayed. */
    int m_menuIndex; /**< Index of the selected menu item. */
    bool m_quit; /**< Flag indicating if the menu should quit. */
    bool m_inCharacterSelection; /**< Flag indicating if the menu is in character selection mode. */
    bool m_exitGame; /**< Flag indicating if the game should exit. */
    const char* m_currentPath; /**< Current path in the menu. */
    
public:

    /***************************************************************************
     * @brief Default constructor for the Menu class.
     **************************************************************************/
    Menu();
    
    /***************************************************************************
     * @brief Destructor for the Menu class.
     **************************************************************************/
    ~Menu();

    // Initialize
    /***************************************************************************
     * @brief Initializes the menu.
     **************************************************************************/
    void initialize();

    // Updates
    /***************************************************************************
     * @brief Handles menu events.
     * @param event The event to handle.
     **************************************************************************/
    void updateEvent(int event);
    
    /***************************************************************************
     * @brief Updates the current path in the menu.
     **************************************************************************/
    void updatePath();
    
    /***************************************************************************
     * @brief Updates the menu.
     **************************************************************************/
    void update();

    // Setters
    /***************************************************************************
     * @brief Sets the menu index.
     * @param index The index to set.
     **************************************************************************/
    void setMenuIndex(int index);

    // Getters
    /***************************************************************************
     * @brief Gets the current menu items.
     * @return The current menu items.
     **************************************************************************/
    std::vector<std::string> getMenuCurrentItems();
    
    /***************************************************************************
     * @brief Gets the menu index.
     * @return The menu index.
     **************************************************************************/
    int getMenuIndex();
    
    /***************************************************************************
     * @brief Gets the quit flag.
     * @return The quit flag.
     **************************************************************************/
    const bool& getQuitMenu() const;
    
    /***************************************************************************
     * @brief Gets the character selection flag.
     * @return The character selection flag.
     **************************************************************************/
    const bool& getInCharacterSelection() const;
    
    /***************************************************************************
     * @brief Gets the exit game flag.
     * @return The exit game flag.
     **************************************************************************/
    const bool& getExitGame() const;
    
    /***************************************************************************
     * @brief Gets the current path.
     * @return The current path.
     **************************************************************************/
    const char* getCurrentPath();

    /***************************************************************************
     * @brief Performs regression testing for the Menu class.
     **************************************************************************/
    static void regressionTest();

};

#endif
