#include "WinTxt.h"
#include <unistd.h>
#include <iostream>
#include <termios.h>
#include <cstdlib>
#include <sys/select.h>

WinTxt::WinTxt(){
     m_player1.p = 'O';
     m_player1.x = 26;
     m_player1.y = 0;
     m_player1.h = 150;
         
     m_player2.p = 'O';
     m_player2.x = 45;
     m_player2.y = 0; 
     m_player2.h = 150;

     for (int i = 0; i < 69; i++){
              m_terrain_ground[i]= ' ';
              m_terrain_jump[i] = ' ';
     }
     m_terrain_ground[69] = '|';
     m_terrain_jump[69] = '|';
     m_terrain_ground[0] = '|';
     m_terrain_jump[0] = '|';
     m_terrain_ground[m_player1.x] = m_player1.p;
     m_terrain_ground[m_player2.x] = m_player1.p;

     m_time = 99; 
     m_round = 1;
}


WinTxt::~WinTxt(){
     m_player1.p = ' ';
     m_player1.x = 0; 
     m_player1.y = 0;
     m_player1.h = 0;
         
     m_player2.p = ' ';
     m_player2.x = 0; 
     m_player2.y = 0;
     m_player2.h = 0;

     for (int i = 0; i < 70; i++){
          m_terrain_ground[i] = ' ';
          m_terrain_jump[i] = ' ';
     }

     m_time = 0; 
     m_round = 0;
}

//movements
void WinTxt::moveRight(Player& p) {
     if(m_terrain_ground[p.x + 1] != '|' && m_terrain_ground[p.x + 1] != m_player1.p && m_terrain_ground[p.x + 1] != m_player2.p){
          m_terrain_ground[p.x] = ' '; // Efface la position actuelle du joueur
          p.x = p.x + 1; // Met à jour la position du joueur
          m_terrain_ground[p.x] = p.p; // Met à jour la position dans terrain_ground
     }
}


void WinTxt::moveLeft(Player& p){
     if(m_terrain_ground[p.x - 1] != '|' && m_terrain_ground[p.x - 1] != m_player1.p && m_terrain_ground[p.x - 1] != m_player2.p){
          m_terrain_ground[p.x] = ' '; // Efface la position actuelle du joueur
          p.x = p.x - 1; // Met à jour la position du joueur
          m_terrain_ground[p.x] = p.p; // Met à jour la position dans terrain_ground
     }
}

void WinTxt::jumpUp(Player& p){
     m_terrain_ground[p.x] = ' '; // Efface la position actuelle du joueur
     p.y = p.x; // Met à jour la position du joueur
     m_terrain_jump[p.y] = p.p; // Met à jour la position dans terrain_ground
}

void WinTxt::jumpDown(Player& p){
     m_terrain_jump[p.y] = ' '; // Efface la position actuelle du joueur
     p.y = 0; // Met à jour la position du joueur
     m_terrain_ground[p.x] = p.p; // Met à jour la position dans terrain_ground
}

void WinTxt::crouch(Player& p){
     m_terrain_ground[p.x] = 'o';
}

void WinTxt::punch(Player& p){
     m_terrain_ground[p.x] = 'P';
}

void WinTxt::kick(Player& p){
     m_terrain_ground[p.x] = 'K';
}

void WinTxt::reset(Player& p){
     m_terrain_ground[p.x] = 'O';
}

//tests position/health
bool WinTxt::testPositionP1(){
     bool contact = false;
     if(m_terrain_ground[m_player2.x - 1] == m_player1.p){
          contact = true;
          return contact;
     }
     else {
          return contact;
     }
}

bool WinTxt::testPositionP2(){
     bool contact = false;
     if(m_terrain_ground[m_player1.x + 1] == m_player2.p){
          contact = true;
          return contact;
     }
     else {
          return contact;
     }
}

bool WinTxt::testHealth(){
     bool fin = false;
     if(m_player1.h == 0 || m_player2.h == 0){
          fin = true;
          return fin;
     }
     else{
          return fin;
     }
     
}

//updates
void WinTxt::updateHealthP1(){
     m_player1.h = m_player1.h - 25;
}

void WinTxt::updateHealthP2(){
     m_player2.h = m_player2.h - 25;
}

void WinTxt::updateRound(){
     m_round = m_round + 1;

     m_terrain_ground[m_player1.x] = ' '; // Efface la position actuelle du joueur
     m_player1.x = 26;
     m_player1.h = 150;
     m_terrain_ground[m_player1.x] = m_player1.p; // Met à jour la position dans terrain_ground

     m_terrain_ground[m_player2.x] = ' '; // Efface la position actuelle du joueur
     m_player2.x = 45;
     m_player2.h = 150;
     m_terrain_ground[m_player2.x] = m_player2.p; // Met à jour la position dans terrain_ground

}

//display
void WinTxt::afficher(){
     std::cout << " ____________________________________________________________________ " << std::endl;
     std::cout << "|         Health : " << m_player1.h << "          Round : " << m_round << "          health : " << m_player2.h << "      |" << std::endl;
     std::cout << "|                               Time : " << m_time << "                            |" << std::endl;
     
     std::cout << "|                                                                    |" << std::endl;
     std::cout << "|                                                                    |" << std::endl;
     std::cout << "|                                                                    |" << std::endl;
     std::cout << "|                                                                    |" << std::endl;
     std::cout << "|                                                                    |" << std::endl;
     for(int i = 0; i < 70; i++){
          std::cout << m_terrain_jump[i];
     }
     std::cout << std::endl;

     for(int i = 0; i < 70; i++){
          std::cout << m_terrain_ground[i];
     }
     std::cout << std::endl;

     std::cout << "|____________________________________________________________________|" << std::endl;
}

//events
void WinTxt::event(){
     bool stop = false;
     char c;

    struct termios old_tio, new_tio;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    while(!stop){
        system("clear");
        afficher();

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 10000; // 10 ms timeout

        fd_set tempfds = readfds;
        int ret = select(STDIN_FILENO + 1, &tempfds, NULL, NULL, &tv);
        if (ret > 0 && FD_ISSET(STDIN_FILENO, &tempfds)) {
            std::cin >> c;
            switch (c){
               //keybind player1, left player
               case 'd':
                   moveRight(m_player1);
                   break;
     
               case 'q':
                   moveLeft(m_player1);
                   break;
                   
               case 's':
                   crouch(m_player1);
                   system("clear");
                   afficher();
                   usleep(250000);
                   reset(m_player1);
                   break;
     
               case 'z':
                   jumpUp(m_player1);
                   system("clear");
                   afficher();
                   usleep(250000);
                   jumpDown(m_player1);
                   break;
     
               case 'e':
                   punch(m_player1);
                   system("clear");
                   afficher();
                   usleep(300000);
                   if(testPositionP2() == true){
                       updateHealthP2();
                   }
                   reset(m_player1);
                   break;
     
               case 'a':
                   kick(m_player1);
                   system("clear");
                   afficher();
                   usleep(300000);
                   if(testPositionP2() == true){
                       updateHealthP2();
                   }
                   reset(m_player1);
                   break;
     
               //keybind player2, right player
               case 'k':
                   moveLeft(m_player2);
                   break;
               case 'm':
                   moveRight(m_player2);
                   break;
     
               case 'l':
                   crouch(m_player2);
                   system("clear");
                   afficher();
                   usleep(250000);
                   reset(m_player2);
                   break;
     
               case 'o':
                   jumpUp(m_player2);
                   system("clear");
                   afficher();
                   usleep(250000);
                   jumpDown(m_player2);
                   break;
     
               case 'p':
                   punch(m_player2);
                   system("clear");
                   afficher();
                   usleep(300000);
                   if(testPositionP1() == true){
                       updateHealthP1();
                   }
                   reset(m_player2);
                   break;
     
               case 'i':
                   kick(m_player2);
                   system("clear");
                   afficher();
                   usleep(300000);
                   if(testPositionP1() == true){
                       updateHealthP1();
                   }
                   reset(m_player2);
                   break;
     
               case 'b':
                   stop = true;
                   break;
     
               default:
                   break;
            }
            if(testHealth() == true){
                stop = true;
            }
        }
     }
     system("clear");
     if (m_player1.h == 0){
     std::cout << "Player 2 WIN !!!" << std::endl;
     }
     if (m_player2.h == 0){
     std::cout << "Player 1 WIN !!!" << std::endl;
     }
     usleep(900000);
     std::cout << "Play again ?" << std::endl;
     std::cout << "Enter [y/n]" << std::endl;
     char e;
     std::cin >> e;
     if(e == 'y'){
      updateRound();
      system("clear");
      event();
     }

    system("clear");
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}

//run
void WinTxt::runTxt(){
     event();
}

// Test for the WinTxt class
void WinTxt::regressionTest(){
     //initialize
     WinTxt win;

     // Test player1 initialization
    assert(win.m_player1.p == 'O');
    assert(win.m_player1.x == 26);
    assert(win.m_player1.y == 0);
    assert(win.m_player1.h == 150);

    // Test player2 initialization
    assert(win.m_player2.p == 'O');
    assert(win.m_player2.x == 45);
    assert(win.m_player2.y == 0);
    assert(win.m_player2.h == 150);

    // Test terrain initialization
    assert(win.m_terrain_ground[69] == '|');
    assert(win.m_terrain_jump[69] == '|');
    assert(win.m_terrain_ground[0] == '|');
    assert(win.m_terrain_jump[0] == '|');
    assert(win.m_terrain_ground[26] == 'O');
    assert(win.m_terrain_ground[45] == 'O');

    // Test time and round initialization
    assert(win.m_time == 99);
    assert(win.m_round == 1);

     //test P1
     //test moveRight P1
     win.moveRight(win.m_player1);
     assert(win.m_terrain_ground[26] == ' ');
     assert(win.m_player1.x == 27);
     assert(win.m_terrain_ground[27] == 'O');
     //test moveLeft P1
     win.moveLeft(win.m_player1);
     assert(win.m_terrain_ground[27] == ' ');
     assert(win.m_player1.x == 26);
     assert(win.m_terrain_ground[26] == 'O');
     //test JumpUp P1
     win.jumpUp(win.m_player1);
     assert(win.m_terrain_ground[26] == ' ');
     assert(win.m_player1.y == 26);
     assert(win.m_terrain_jump[26] == 'O');
     //test JumpDown P1
     win.jumpDown(win.m_player1);
     assert(win.m_terrain_jump[26] == ' ');
     assert(win.m_player1.y == 0);
     assert(win.m_terrain_ground[26] == 'O');
     //test crouch P1
     win.crouch(win.m_player1);
     assert(win.m_terrain_ground[26] == 'o');
     //test punch P1
     win.punch(win.m_player1);
     assert(win.m_terrain_ground[26] == 'P');
     //test kick P1
     win.kick(win.m_player1);
     assert(win.m_terrain_ground[26] == 'K');
     //test reset P1
     win.reset(win.m_player1);
     assert(win.m_terrain_ground[26] == 'O');
     //test updateHealthP1
     win.updateHealthP1();
     assert(win.m_player1.h == 125);

     //test P2
     //test moveRight P2
     win.moveRight(win.m_player2);
     assert(win.m_terrain_ground[45] == ' ');
     assert(win.m_player2.x == 46);
     assert(win.m_terrain_ground[46] == 'O');
     //test moveLeft P1
     win.moveLeft(win.m_player2);
     assert(win.m_terrain_ground[46] == ' ');
     assert(win.m_player2.x == 45);
     assert(win.m_terrain_ground[45] == 'O');
     //test JumpUp P1
     win.jumpUp(win.m_player2);
     assert(win.m_terrain_ground[45] == ' ');
     assert(win.m_player2.y == 45);
     assert(win.m_terrain_jump[45] == 'O');
     //test JumpDown P1
     win.jumpDown(win.m_player2);
     assert(win.m_terrain_jump[45] == ' ');
     assert(win.m_player2.y == 0);
     assert(win.m_terrain_ground[45] == 'O');
     //test crouch P1
     win.crouch(win.m_player2);
     assert(win.m_terrain_ground[45] == 'o');
     //test punch P1
     win.punch(win.m_player2);
     assert(win.m_terrain_ground[45] == 'P');
     //test kick P1
     win.kick(win.m_player2);
     assert(win.m_terrain_ground[45] == 'K');
     //test reset P1
     win.reset(win.m_player2);
     assert(win.m_terrain_ground[45] == 'O');
     //test updateHealthP1
     win.updateHealthP2();
     assert(win.m_player2.h == 125);
     
     //test testPositionP1
     win.m_player2.x = 27;
     assert(win.testPositionP1() == true);
     //test testPositionP2
     win.m_player1.x = 44;
     assert(win.testPositionP2() == true);
     //test testHealth
     win.m_player1.h = 0;
     assert(win.testHealth() == true);

     //test updateRound
     win.m_player1.x = 1;
     win.m_player2.x = 2;
     win.updateRound();
     assert(win.m_round == 2);
     assert(win.m_terrain_ground[1] == ' ');
     assert(win.m_terrain_ground[2] == ' ');
     assert(win.m_player1.x == 26);
     assert(win.m_player1.h == 150);
     assert(win.m_player2.x == 45);
     assert(win.m_player2.h == 150);
     assert(win.m_terrain_ground[26] == 'O');
     assert(win.m_terrain_ground[45] == 'O');
}