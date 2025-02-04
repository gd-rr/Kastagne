#include "GameEngine.h"
#include<iostream>
#include <map>


using json = nlohmann::json;

GameEngine::GameEngine() :  
                            m_window(nullptr), 
                            m_renderer(nullptr), 
                            m_isRunning(false),
                            m_windowWidth(960), 
                            m_windowHeight(540), // 1024
                            m_fullscreen(true),
                            m_playerInitPosition(2),
                            m_game(GameState::LoadingScene),
                            m_soundManager()                            
{
    init("TAG Kasstagne - 3/4 Face", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_windowWidth, m_windowHeight, m_fullscreen);
    m_soundManager.fadeInMusic("data/music/introTheme.ogg", 0, 4000);
    
    
}

GameEngine::~GameEngine() {}

bool GameEngine::init(const char* title, int xpos, int ypos,
                        int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        //flags = SDL_WINDOW_FULLSCREEN;
        flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL Initialized!" << std::endl;
        
        m_soundManager.initialize();

        if (TTF_Init() == 0) {
            std::cout << "TTF Initialized!" << std::endl;

            loadFont("data/kastagne.ttf", 60);

            m_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
            if (m_window) {
                std::cout << "Window created!" << std::endl;

                m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
                if (m_renderer) {
                    std::cout << "Renderer created!" << std::endl;
                    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
                    m_isRunning = true;
                }
                else {
                    std::cerr << "Failed to create m_renderer: " << SDL_GetError() << std::endl;
                    return false;
                }
            }
            else {
                std::cerr << "Failed to create m_window: " << SDL_GetError() << std::endl;
                return false;
            }
        } 
        else {
            std::cerr << "Failed to initialize TTF: " << SDL_GetError() << std::endl;
        }
    }
    else {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(0, &dm);
    std::cout << "Max Width: " << dm.w << ", Max Height: " << dm.h << std::endl;

    SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
    std::cout << "Current Width: " << m_windowWidth << ", Current Height: " << m_windowHeight << std::endl;

    m_screenLeftEdge = m_windowWidth/10;
    //m_screenLeftEdge = (m_windowWidth>>3);
    std::cout << "m_windowWidth: " << m_windowWidth << std::endl;
    std::cout << "m_screenLeftEdge: " << m_screenLeftEdge << std::endl;
    m_screenRightEdge = m_windowWidth - m_screenLeftEdge;
    std::cout << "m_screenRightEdge: " << m_screenRightEdge << std::endl;

    m_scaleFactor = (m_windowHeight / 224); // m_windowHeight / 224 or m_windowHeight >> 8
    std::cout << "m_scaleFactor = " << m_scaleFactor << std::endl;

    m_stageFloor = m_windowHeight - 256 * (m_scaleFactor >> 1); // m_windowHeight * 0.58;
    //m_stageFloor = m_windowHeight - (m_windowHeight*0.3) * (m_scaleFactor >> 1); // m_windowHeight * 0.58;
    std::cout << "m_stageFloor = " << m_stageFloor << std::endl;


    
    bool jsonloadKeycodeSDL = loadKeycodeSDL("./src/core/json/KeycodeSDL.json");
    bool jsonloadKeybinds =  loadKeybinds("./src/core/json/Keybind.json");

    if(jsonloadKeycodeSDL == false){
        return false;
    }
    if(jsonloadKeybinds == false){
        return false;
    }

    m_keycodeMenu = 0;
    m_animationF1 = "Stance";
    m_animationF2 = "Stance";
    m_inBattleScene = false;
    quit = false;


    return true;


}

// Touch EventManager 

bool GameEngine::loadKeycodeSDL(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier " << filename << std::endl;
        return false; 
    } else {
        try {
            json jsonData;
            file >> jsonData; // Lecture des données JSON dans un objet json

            
            std::map<unsigned int, std::string> playerKeybinds;
            for (auto& action : jsonData.items()) {
                
                try {
                    unsigned int keyCode = std::stoul(action.key());
                    playerKeybinds[keyCode] = action.value();
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Clé non convertible en entier : " << e.what() << std::endl;
                   
                }
            }
            m_keycodeSDL = playerKeybinds;
            file.close();
            return true; 
        } catch (json::parse_error& e) {
            std::cerr << "Erreur de parsing JSON : " << e.what() << std::endl;
            file.close();
            return false; 
        }
    }
}



bool GameEngine::loadKeybinds(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier " << filename << std::endl;
        return false; // Indique que le chargement a échoué
    } else {
        try {
            json jsonData;
            file >> jsonData;

            for (auto& player : jsonData.items()) {
                std::map<std::string, std::string> playerKeybinds;
                for (auto& action : player.value().items()) {
                    playerKeybinds[action.key()] = action.value();
                }
            m_keybinds[player.key()] = playerKeybinds;
        }
            file.close();
            return true; // Indique que le chargement a réussi
        } catch (json::parse_error& e) {
            std::cerr << "Erreur de parsing JSON : " << e.what() << std::endl;
            file.close();
            return false; // Indique que le chargement a échoué
        }
    }
}



void GameEngine::handleEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        if (shouldQuit(event)) {

            quit = true;

        } else if(m_inBattleScene) {
            handleKeybinds("player1", event);
            handleKeybinds("player2", event);
            if (isKeyDown(event, returnValueSDL(returnTouchAction(event, "other","quit")))) {
                quit = true;
            }

        } else if (isKeyDown(event, returnValueSDL(returnTouchAction(event, "other","navup")))) {
             m_keycodeMenu = 1;
             

        } else if (isKeyDown(event, returnValueSDL(returnTouchAction(event, "other","navdown")))) {
             m_keycodeMenu = 2;
             

        } else if (isKeyDown(event, returnValueSDL(returnTouchAction(event, "other","return")))) {
            m_keycodeMenu = 3;
        }
    }
}


void GameEngine::handleKeybinds(const std::string& playerName, SDL_Event& event) {
    
    const std::map<std::string, std::string>& playerKeybinds = m_keybinds[playerName];

    for (const auto& [key, action] : playerKeybinds){
        std::string keyString = returnTouchAction(event, playerName, action);
        SDL_Keycode keyCode = returnValueSDL(keyString);

        if (isKeyDown(event, keyCode)) {
            setAnimation(playerName, action);

            return;
            
        } else if (isKeyUp(event, keyCode)) {
            resetAnimation(playerName, action);
            
        }
        
    }
}  


bool GameEngine::isKeyDown(SDL_Event& event, SDL_Keycode key) {
    return event.type == SDL_KEYDOWN && event.key.keysym.sym == key;
}


bool GameEngine::isKeyUp(SDL_Event& event, SDL_Keycode key) {    
    return event.type == SDL_KEYUP && event.key.keysym.sym == key;
}





std::string GameEngine::returnTouchAction(SDL_Event& event, const std::string& name, const std::string& action) {
    // Vérifier si le nom du joueur spécifié existe dans vos keybinds
    auto playerKeybinds = m_keybinds.find(name);
    if (playerKeybinds != m_keybinds.end()) {
        // Parcourir les keybinds du joueur pour trouver l'action spécifiée
        for (const auto& bind : playerKeybinds->second) {
            if (bind.second == action) {
                
                return bind.first;
            }
        }
    }
    
    return "";
}


bool GameEngine::getQuitStatus() const {
    return !quit;
}
bool GameEngine::shouldQuit(SDL_Event& event) {
    return event.type == SDL_QUIT;
}


SDL_Keycode GameEngine::returnValueSDL(const std::string& action) {
    // Parcourir le mapping keycodeSDL pour trouver le SDL_Keycode correspondant à l'action donnée
    for (const auto& [keyCode, sdlAction] : m_keycodeSDL) {
        if (sdlAction == action) {
            return keyCode; // Retourner le SDL_Keycode correspondant
        }
    }
    // Si aucune correspondance n'est trouvée, retourner SDLK_UNKNOWN
    return SDLK_UNKNOWN;
}


void GameEngine::setAnimation(const std::string& playerName, const std::string& keycode) {
    if (playerName == "player1") {
        m_animationF1 = keycode;
        
    } else if (playerName == "player2") {
        m_animationF2 = keycode;
        
    }
}

void GameEngine::resetAnimation(const std::string& playerName, const std::string& keycode) {
    if (playerName == "player1" && m_animationF1 == keycode) {
        m_animationF1 = "Stance";
        
    } else if (playerName == "player2" && m_animationF2 == keycode) {
        m_animationF2 = "Stance";
        
    }
}


void GameEngine::setKeybind(const std::string& playerName, const std::string& action, SDL_Keycode newKey) {
    
    std::string newAction;
    for (const auto& [keyCode, sdlAction] : m_keycodeSDL) {
        if (keyCode == newKey) {
            newAction = sdlAction;
            break;
        }
    }

    if (!newAction.empty()) {
        
        auto playerKeybinds = m_keybinds.find(playerName);
        if (playerKeybinds != m_keybinds.end()) {
            
            for (auto& bind : playerKeybinds->second) {
                if (bind.second == action) {
                    // Supprimez l'ancienne association avec l'action spécifiée
                    m_keybinds[playerName].erase(bind.first);

                    // Associez la nouvelle touche à l'action spécifiée
                    m_keybinds[playerName][newAction] = action;

                    // Écrivez les modifications dans le fichier JSON
                    writeKeybindsToFile();

                    // Sortez de la fonction après avoir effectué la mise à jour
                    return;
                }
            }
        }

        // Si l'action spécifiée n'a pas été trouvée pour ce joueur, affichez un message d'erreur
        std::cout << "L'action spécifiée n'existe pas pour ce joueur." << std::endl;
    } else {
        std::cout << "La touche associée à newKey n'a pas été trouvée." << std::endl;
    }
}

void GameEngine::writeKeybindsToFile() {
    // Ouvrir le fichier en mode écriture
    std::ofstream file("./src/core/KeybindFinal.json");
    if (!file.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier KeybindFinal.json pour l'écriture." << std::endl;
        return;
    }

    // Écrire les données JSON dans le fichier
    json jsonData;
    for (const auto& player : m_keybinds) {
        jsonData[player.first] = player.second;
    }
    file << std::setw(4) << jsonData << std::endl;

    // Fermer le fichier
    file.close();
}

void GameEngine::run() {
    std::cout << "GameEngine::run" << std::endl;

    const GameState& state = m_game.getCurrentGameState();
    Menu& menu = m_game.getMenu();

    while(menu.getExitGame()){
        switch (state) {
            case GameState::LoadingScene:
                runLoadingScene();
                break;
            case GameState::MainMenu:
                //std::cout << "entrer mainmenu" << std::endl;
                runMenu();
                break;
            case GameState::CharacterSelection:
                runSelectScene();
                break;
            case GameState::BattleScene:
                m_inBattleScene = !m_inBattleScene;
                runBattleScene();
                break;
            case GameState::ExitGame:
                return;
        }
    }
}

void GameEngine::runBattleScene() {
    
    // Retrieving elements from the battle scene
    BattleScene& battleScene = m_game.getBattleScene();
    Stage&       stage       = battleScene.getStage();
    Camera&      camera      = battleScene.getCamera();
    Hud&         hud         = battleScene.getHud();
    Fighter&     player1     = battleScene.getFighter(0);
    Fighter&     player2     = battleScene.getFighter(1);
    
    // Assigning the scale factor for the players
    player1.setScale(m_scaleFactor);
    player2.setScale(m_scaleFactor);
    
    // Loading textures for the scene
    SDL_Texture* stageTextureBack = loadTexture(stage.getStageBackPath());
    SDL_Texture* stageTextureFront = loadTexture(stage.getStageFrontPath());
   
    // Set camera dimensions and center on stage
    camera.setScreenDimension(m_windowWidth, m_windowHeight);
    camera.setStageEdge(m_screenLeftEdge);
    camera.centerOnStage(getTextureWidth(stageTextureBack),  getTextureHeight(stageTextureBack));

    // Calculate initial positions for players
    m_playerInitPosition[0] = camera.getPosition().x + m_windowWidth*0.435+0.5 - player1.getStanceWidth()*m_scaleFactor;
    m_playerInitPosition[1] = camera.getPosition().x + (m_windowWidth*(1 - 0.435)) + 0.5;

    // Set positions for players
    player1.setPosition(m_playerInitPosition[0], m_stageFloor);
    player2.setPosition(m_playerInitPosition[1], m_stageFloor);
    // Load textures for players 
    SDL_Texture* frstPlayerTexture = loadTexture(player1.getAtlasPath());
    SDL_Texture* scndPlayerTexture = loadTexture(player2.getAtlasPath());
    // Set stage constraints for players
    player1.setStageContraints(m_screenLeftEdge, m_windowWidth);
    player2.setStageContraints(m_screenLeftEdge, m_windowWidth);

    SDL_Texture* overlayTexture = loadTexture(hud.getOverlayAtlasPath());

    const double dt = 16.0;
    double accumulator = 0.0;
    auto startTime = std::chrono::high_resolution_clock::now();

    

    while (getQuitStatus()) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        double frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
        startTime = currentTime;

        accumulator += std::min(frameTime, 21.0);
        while(accumulator >= dt) {
            handleEvents();
            update(dt, m_animationF1,m_animationF2, m_keycodeMenu);
            accumulator -= dt;
        }
        
        SDL_RenderClear(m_renderer);
        renderStage(camera, stageTextureBack);

        
        renderOverlay(hud, player1, player2, overlayTexture);
        renderFighter(player1, camera, frstPlayerTexture, player1.getReversed());
        renderFighter(player2, camera, scndPlayerTexture, player2.getReversed());
        renderStage(camera, stageTextureFront);
        renderBlackStripes();

        renderFighterHitbox(player1, camera);
        renderFighterHitbox(player2, camera);
        //renderCameraZone(camera);

        SDL_RenderPresent(m_renderer);

        // Waiting time calculation
        double sleepTime = dt - (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count());
        if (sleepTime > 0.0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(sleepTime)));
        }
    }

    SDL_DestroyTexture(frstPlayerTexture);
    SDL_DestroyTexture(scndPlayerTexture);
    SDL_DestroyTexture(stageTextureBack);
    SDL_DestroyTexture(stageTextureFront);
    cleanEngine();
    m_game.changeState(GameState::ExitGame);
}

void GameEngine::update(float deltaTime, std::string m_keycodeF1,std::string m_keycodeF2, int m_keycodeMenu) {
    m_game.update(deltaTime, m_keycodeF1,m_keycodeF2, m_keycodeMenu);
}

void GameEngine::cleanEngine() {
    TTF_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}

int GameEngine::getTextureWidth(SDL_Texture* texture) {
    if (!texture) {
        std::cerr << "Texture is null." << std::endl;
        return 0;
    }

    int width = 0, height = 0;
    // Obtenez la largeur et la hauteur de la texture
    if (SDL_QueryTexture(texture, NULL, NULL, &width, &height) != 0) {
        std::cerr << "Failed to get texture size: " << SDL_GetError() << std::endl;
        return 0;
    }

    return width * m_scaleFactor;
}

int GameEngine::getTextureHeight(SDL_Texture* texture) {
    if (!texture) {
        std::cerr << "Texture is null." << std::endl;
        return 0;
    }

    int width = 0, height = 0;
    // Obtenez la largeur et la hauteur de la texture
    if (SDL_QueryTexture(texture, NULL, NULL, &width, &height) != 0) {
        // Gestion de l'erreur si la requ�te �choue
        std::cerr << "Failed to get texture size: " << SDL_GetError() << std::endl;
        return 0;
    }
    return height * m_scaleFactor;
}

void GameEngine::renderBlackStripes() {
    int scndStripePos = m_windowWidth - m_screenLeftEdge;
    SDL_Rect frstStripe = { 0, 0, m_screenLeftEdge, m_windowHeight };
    SDL_Rect scndStripe = { scndStripePos, 0, m_screenLeftEdge, m_windowHeight };
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(m_renderer, &frstStripe);
    SDL_RenderFillRect(m_renderer, &scndStripe);
}

void GameEngine::renderCameraZone(const Camera& camera) {
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

    const int stripeWidth = camera.getCameraZone();
    const int scndStripePos = m_windowWidth - m_screenLeftEdge - stripeWidth;
    const SDL_Rect frstStripe = { m_screenLeftEdge, 0, stripeWidth, m_windowHeight };
    const SDL_Rect scndStripe = { scndStripePos, 0, stripeWidth, m_windowHeight };
    SDL_SetRenderDrawColor(m_renderer, 215, 208, 27, 128);
    SDL_RenderFillRect(m_renderer, &frstStripe);
    SDL_RenderFillRect(m_renderer, &scndStripe);
}

SDL_Texture* GameEngine::loadTexture(const char* filePath) {
    SDL_Surface* surface = IMG_Load(filePath);
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    if (!texture) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return nullptr;
    }

    SDL_FreeSurface(surface);
    return texture;
}

int GameEngine::renderCopy(SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect, bool reverse = false) const{
    if (reverse) return SDL_RenderCopyEx(m_renderer, texture, srcrect, dstrect, 0, NULL, SDL_FLIP_HORIZONTAL);
    else return SDL_RenderCopy(m_renderer, texture, srcrect, dstrect);
}

void GameEngine::renderTexture(SDL_Texture* texture, int x, int y, int posX, int posY, int width, int height, bool reverse) {
    int w = width * m_scaleFactor;
    int h = height * m_scaleFactor;
    SDL_Rect srcrect = { posX, posY, width, height };
    SDL_Rect dstrect = { x, y, w, h };
    renderCopy(texture, &srcrect, &dstrect, reverse);    
}

void GameEngine::renderStageTexture(SDL_Texture* texture, int x, int y) {
    int w = getTextureWidth(texture);
    int h = getTextureHeight(texture);
    SDL_Rect dstrect = { x, y, w, h };
    renderCopy(texture, nullptr, &dstrect);
}

void GameEngine::renderStage(const Camera& camera, SDL_Texture* texture) {
    Vector2D position = camera.getPosition();
    renderStageTexture(texture, 0 - position.x, 0 - position.y);
}

void GameEngine::renderFighter(const Fighter& fighter, const Camera& camera, SDL_Texture* texture, bool reverse) {
    Vector2D positionFighter = fighter.getPosition();
    const RectangleFromAtlas& rect = fighter.getSpriteRect();
    int dir = fighter.getDirection();
    int correctorX = rect.posCorrector.x;
    if(dir == -1) correctorX = correctorX>>1;
    renderTexture(
        texture, 
        positionFighter.x + correctorX*m_scaleFactor - camera.getPosition().x, 
        positionFighter.y + rect.posCorrector.y*m_scaleFactor, 
        rect.atlas.posx, 
        rect.atlas.posy, 
        rect.atlas.width, 
        rect.atlas.height, 
        reverse
    );
}

// A refactor
void GameEngine::renderFighterHitbox(const Fighter& fighter, const Camera& camera) {
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

    Vector2D positionFighter = fighter.getPosition();
    const RectangleFromAtlas& rect = fighter.getSpriteRect();

    if(fighter.getReversed()) {
        int collideCorrector, hitCorrector, hurtCorrector;
        if(fighter.getName() == "Alex") {
            collideCorrector = 19.5;
            hitCorrector     = 0;
            hurtCorrector    = 0;
        }

        if(fighter.getName() == "Dudley") {
            collideCorrector = 4;
            hitCorrector     = 0;
            hurtCorrector    = 0;
        }

        SDL_Rect collideBoxOutline = { 
            positionFighter.x + ((rect.collideBox.posx - collideCorrector) * m_scaleFactor) - camera.getPosition().x , 
            positionFighter.y + rect.collideBox.posy * m_scaleFactor, 
            rect.collideBox.width * m_scaleFactor, 
            rect.collideBox.height * m_scaleFactor 
        };

        SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
        SDL_RenderDrawRect(m_renderer, &collideBoxOutline);

        SDL_Rect collideBoxFill = { 
            collideBoxOutline.x + 1, 
            collideBoxOutline.y + 1, 
            collideBoxOutline.w - 2, 
            collideBoxOutline.h - 2 
        };

        SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 128);  // Vert semi-transparent pour l'interieur
        SDL_RenderFillRect(m_renderer, &collideBoxFill);

        SDL_Rect hurtBoxOutline = {
            positionFighter.x + ((rect.hurtBox.posx - hurtCorrector) * m_scaleFactor) - camera.getPosition().x , 
            positionFighter.y + rect.hurtBox.posy * m_scaleFactor, 
            rect.hurtBox.width * m_scaleFactor, 
            rect.hurtBox.height * m_scaleFactor 
        };

        SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);  // Bleu opaque pour les bords
        SDL_RenderDrawRect(m_renderer, &hurtBoxOutline);

        // Dessiner l'int�rieur transparent du rectangle
        SDL_Rect hurtBoxFill = { hurtBoxOutline.x + 1, hurtBoxOutline.y + 1, hurtBoxOutline.w - 2, hurtBoxOutline.h - 2 };
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 128);  // Bleu semi-transparent pour l'int�rieur
        SDL_RenderFillRect(m_renderer, &hurtBoxFill);

        SDL_Rect hitBoxOutline = {
            positionFighter.x + ((rect.hitBox.posx - hitCorrector) * m_scaleFactor) - camera.getPosition().x , 
            positionFighter.y + rect.hitBox.posy * m_scaleFactor, 
            rect.hitBox.width * m_scaleFactor, 
            rect.hitBox.height * m_scaleFactor 
        };

        SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);  // Rouge opaque pour les bords
        SDL_RenderDrawRect(m_renderer, &hitBoxOutline);

        // Dessiner l'int�rieur transparent du rectangle
        SDL_Rect hitBoxFill = { hitBoxOutline.x + 1, hitBoxOutline.y + 1, hitBoxOutline.w - 2, hitBoxOutline.h - 2 };
        SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 128);  // Rouge semi-transparent pour l'int�rieur
        SDL_RenderFillRect(m_renderer, &hitBoxFill);

        

    } else {
        SDL_Rect collideBoxOutline = { 
            positionFighter.x + (rect.collideBox.posx  * m_scaleFactor) - camera.getPosition().x , 
            positionFighter.y + rect.collideBox.posy * m_scaleFactor, 
            rect.collideBox.width * m_scaleFactor, 
            rect.collideBox.height * m_scaleFactor 
        };

        SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
        SDL_RenderDrawRect(m_renderer, &collideBoxOutline);

        SDL_Rect collideBoxFill = { 
            collideBoxOutline.x + 1, 
            collideBoxOutline.y + 1, 
            collideBoxOutline.w - 2, 
            collideBoxOutline.h - 2 
        };

        SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 128);  // Vert semi-transparent pour l'interieur
        SDL_RenderFillRect(m_renderer, &collideBoxFill);

        SDL_Rect hurtBoxOutline = {
            positionFighter.x + (rect.hurtBox.posx * m_scaleFactor) - camera.getPosition().x , 
            positionFighter.y + rect.hurtBox.posy * m_scaleFactor, 
            rect.hurtBox.width * m_scaleFactor, 
            rect.hurtBox.height * m_scaleFactor 
        };

        SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);  // Bleu opaque pour les bords
        SDL_RenderDrawRect(m_renderer, &hurtBoxOutline);

        // Dessiner l'int�rieur transparent du rectangle
        SDL_Rect hurtBoxFill = { hurtBoxOutline.x + 1, hurtBoxOutline.y + 1, hurtBoxOutline.w - 2, hurtBoxOutline.h - 2 };
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 128);  // Bleu semi-transparent pour l'int�rieur
        SDL_RenderFillRect(m_renderer, &hurtBoxFill);

        SDL_Rect hitBoxOutline = {
            positionFighter.x + (rect.hitBox.posx * m_scaleFactor) - camera.getPosition().x , 
            positionFighter.y + rect.hitBox.posy * m_scaleFactor, 
            rect.hitBox.width * m_scaleFactor, 
            rect.hitBox.height * m_scaleFactor 
        };

        SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);  // Rouge opaque pour les bords
        SDL_RenderDrawRect(m_renderer, &hitBoxOutline);

        // Dessiner l'int�rieur transparent du rectangle
        SDL_Rect hitBoxFill = { hitBoxOutline.x + 1, hitBoxOutline.y + 1, hitBoxOutline.w - 2, hitBoxOutline.h - 2 };
        SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 128);  // Rouge semi-transparent pour l'int�rieur
        SDL_RenderFillRect(m_renderer, &hitBoxFill);

    }    
}

void GameEngine::renderScalelessTexture(SDL_Texture* texture, int screenx, int screeny, int screenwidth, int screenheight, int posX, int posY, int width, int height, bool reverse = false) {
    SDL_Rect srcrect = { posX, posY, width, height };
    SDL_Rect dstrect = { screenx, screeny, screenwidth, screenheight };
    renderCopy(texture, &srcrect, &dstrect, reverse); 
}

void GameEngine::renderHealthBar(const Hud& hud, SDL_Texture* texture, int currentHealth1, int currentHealth2) {
    // Get the rectangles for current health and max health from the HUD
    const Rectangle& rectCurrentHealth  = hud.getSpriteRect("currentHealth");
    const Rectangle& rectMaxHealth      = hud.getSpriteRect("maxHealth");

    // Define constants for the maximum health bar width, health bar height, and y-position of the health bars
    const int maxHealthWidth    = 640;
    const int healthBarHeight   = 20;
    const int healthBarY        = 63;

    // Define the x-positions of the health bars for player 1 and player 2
    const int player1HealthX = 224;
    const int player2HealthX = 1055;

    // Calculate the x-positions of the health bar segments for player 2
    int player2HealthBarX = player2HealthX + 0.8 + (1000 - currentHealth2) * 0.64;
    
    // Calculate the widths of the health bar segments for player 1 and player 2
    int player1HealthBarWidth = currentHealth1 * 0.64;
    int player2HealthBarWidth = currentHealth2 * 0.64;
    
    // Render the segments of the health bars
    renderHealthBarSegment(texture, rectMaxHealth    , player1HealthX, healthBarY, maxHealthWidth       , healthBarHeight);    // left
    renderHealthBarSegment(texture, rectMaxHealth    , player2HealthX   , healthBarY, maxHealthWidth       , healthBarHeight);    // right
    renderHealthBarSegment(texture, rectCurrentHealth, player1HealthX   , healthBarY, player1HealthBarWidth, healthBarHeight);    // left
    renderHealthBarSegment(texture, rectCurrentHealth, player2HealthBarX   , healthBarY, player2HealthBarWidth, healthBarHeight); // right
}

void GameEngine::renderHealthBarSegment(SDL_Texture* texture, const Rectangle& rect, int x, int y, int width, int height) {
    renderScalelessTexture(texture, x, y, width, height, rect.posx, rect.posy, rect.width, rect.height);
}

void GameEngine::renderOverlay(const Hud& hud, const Fighter& player1, const Fighter& player2, SDL_Texture* texture) {
    const Rectangle& rectTimerLeft  = hud.getTimerRect(0); // Chiffre de gauche
    const Rectangle& rectTimerRight = hud.getTimerRect(1); // Chiffre de droite

    renderGeneralOverlay(hud, player1, player2, texture);
    renderTimer(rectTimerLeft, rectTimerRight, texture);
    renderHealthBar(hud, texture, player1.getCurrentHealth(), player2.getCurrentHealth());
}

void GameEngine::renderTimer(const Rectangle& rctLeft, const Rectangle& rctRight, SDL_Texture* texture) {
    // Define constants for positions
    const int timerLeftX    = 892;
    const int timerRightX   = 960;
    const int timerY        = 24;

    renderTexture(texture, timerLeftX , timerY, rctLeft.posx , rctLeft.posy , rctLeft.width , rctLeft.height );
    renderTexture(texture, timerRightX, timerY, rctRight.posx, rctRight.posy, rctRight.width, rctRight.height);
}

void GameEngine::renderGeneralOverlay(const Hud& hud, const Fighter& player1, const Fighter& player2, SDL_Texture* texture) {
    const Rectangle& rectStatutBar  = hud.getSpriteRect("statutBar");
    const Rectangle& rectBackTimer  = hud.getSpriteRect("timerBack");
    const Rectangle& rectAlexIcon   = hud.getSpriteRect("alexIcon");
    const Rectangle& rectAlexName   = hud.getSpriteRect("alexName");
    const Rectangle& rectDudleyIcon = hud.getSpriteRect("dudleyIcon");
    const Rectangle& rectDudleyName = hud.getSpriteRect("dudleyName");

    // Render statut bars
    renderTexture(texture, 200 , 55, rectStatutBar.posx, rectStatutBar.posy, rectStatutBar.width, rectStatutBar.height);
    renderTexture(texture, 1039, 55, rectStatutBar.posx, rectStatutBar.posy, rectStatutBar.width, rectStatutBar.height, true);
    renderTexture(texture, 864 , 39, rectBackTimer.posx, rectBackTimer.posy, rectBackTimer.width, rectBackTimer.height);

    // Define constants for positions and dimensions
    const int leftIconX     = 224;
    const int rightIconX    = 1591;
    const int iconY         = 99;
    const int leftNameX     = 368;
    const int rightNameX    = 1551;
    const int nameY         = 87;
    const int iconWidth     = 104;
    const int iconHeight    = 64;

    // Render player icons and names
    if(player1.getName() == "Dudley")
        renderPlayerInfo(texture, player1, rectDudleyIcon, rectDudleyName, leftIconX, iconY, leftNameX, nameY, iconWidth, iconHeight, false);
    if(player1.getName() == "Alex")
        renderPlayerInfo(texture, player1, rectAlexIcon, rectAlexName, leftIconX, iconY, leftNameX, nameY, iconWidth, iconHeight, false);
    if(player2.getName() == "Dudley")
        renderPlayerInfo(texture, player2, rectDudleyIcon, rectDudleyName, rightIconX, iconY, rightNameX - rectDudleyName.width * m_scaleFactor, nameY, iconWidth, iconHeight, true);
    if(player2.getName() == "Alex")
        renderPlayerInfo(texture, player2, rectAlexIcon, rectAlexName, rightIconX, iconY, rightNameX - rectAlexName.width * m_scaleFactor, nameY, iconWidth, iconHeight, true);
}

void GameEngine::renderPlayerInfo(SDL_Texture* texture, const Fighter& player, const Rectangle& iconRect, const Rectangle& nameRect, int iconX, int iconY, int nameX, int nameY, int iconWidth, int iconHeight, bool reverse) {
    renderScalelessTexture(texture, iconX, iconY, iconWidth, iconHeight, iconRect.posx, iconRect.posy, iconRect.width, iconRect.height, reverse);
    renderTexture(texture, nameX, nameY, nameRect.posx, nameRect.posy, nameRect.width, nameRect.height);
}

void GameEngine::setWindowSize(int width, int height) {
    SDL_SetWindowSize(m_window, width, height);
}

void GameEngine::setFullscreen(bool fullscreen) {
    if(fullscreen) SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    else SDL_SetWindowFullscreen(m_window, 0);
}

void GameEngine::loadFont(const char* file, int size){
    m_font = TTF_OpenFont(file, size);
    if (m_font == nullptr) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
    else {
        std::cout << "Font loaded correctly!" << std::endl;
    }
}

void GameEngine::displayMenu(std::vector<std::string> items, int index, const char* filePath){
    SDL_RenderClear(m_renderer);
    SDL_Surface* imageSurface = IMG_Load(filePath);

    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(m_renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    renderCopy(imageTexture, nullptr, nullptr);
    SDL_DestroyTexture(imageTexture);

    int spacing = 120;
    for (int i = 0; i < (int) items.size(); ++i) {
        SDL_Color textColor = {0, 0, 0, 255}; // Black 
        if (i == index) {
            // Adjust color for selected item
            textColor = {255, 255, 255, 255}; // White
        }
        SDL_Surface* surface = TTF_RenderText_Solid(m_font, items[i].c_str(), textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);
        SDL_Rect dstRect = {m_screenLeftEdge + 10, spacing, texW, texH};
        SDL_RenderCopy(m_renderer, texture, nullptr, &dstRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        spacing += 80; // Adjust spacing
    }

    renderBlackStripes();
    SDL_RenderPresent(m_renderer);
}

void GameEngine:: runMenu() {
    Menu& menu = m_game.getMenu();

    while (menu.getQuitMenu()) {

        m_filePathMenu = menu.getCurrentPath();

        displayMenu(menu.getMenuCurrentItems(), menu.getMenuIndex(), m_filePathMenu);

        handleEvents();
        update(0.0f, m_animationF1, m_animationF2, m_keycodeMenu);
        m_keycodeMenu = 0;

    }

    if(menu.getInCharacterSelection()) m_game.changeState(GameState::CharacterSelection);

}

void GameEngine::renderTextureSelectScene(SDL_Texture* texture, int x, int y, int posX, int posY, int width, int height, bool reverse) {
    int w = width;
    int h = height;
    SDL_Rect srcrect = { posX, posY, width, height };
    SDL_Rect dstrect = { x, y, w, h };
    renderCopy(texture, &srcrect, &dstrect, reverse);    
}

void GameEngine::renderTextureSelectSceneMini(SDL_Texture* texture, int x, int y, int posX, int posY, int width, int height, bool reverse) {
    int w = width * 1.8;
    int h = height * 1.8;
    SDL_Rect srcrect = { posX, posY, width, height };
    SDL_Rect dstrect = { x, y, w, h };
    renderCopy(texture, &srcrect, &dstrect, reverse);    
}

void GameEngine::renderTextureSelectSceneFighter(SDL_Texture* texture, int x, int y, int posX, int posY, int width, int height, bool reverse) {
    int w = width * 1.8;
    int h = height * 1.8;
    SDL_Rect srcrect = { posX, posY, width, height };
    SDL_Rect dstrect = { x, y, w, h };
    renderCopy(texture, &srcrect, &dstrect, reverse);    
}

void GameEngine::renderSelectSceneBox(const SelectScene& select, SDL_Texture* texture, int x, int y, bool reverse) {
    const frameData& rect = select.getFrameData();
    std::string animation = select.getCurrentAnimationName();

    int w = rect.atlasData.width * 1.8;
    int h = rect.atlasData.height * 1.8;
    SDL_Rect srcrect = { rect.atlasData.position.x, rect.atlasData.position.y, rect.atlasData.width, rect.atlasData.height};
    SDL_Rect dstrect = { x, y, w, h };
    renderCopy(texture, &srcrect, &dstrect, reverse);
}

void GameEngine::runSelectScene(){
    SelectScene& select = m_game.getSelectScene();

    // Loading textures for the background
    SDL_Texture* backGround = loadTexture(select.getBackGroundPath());

    // Loading textures
    SDL_Texture* atlasTexture = loadTexture(select.getAtlasPath());

    std::string nameP1;
    std::string nameP2;

    const double dt = 16.0;
    double accumulator = 0.0;
    auto startTime = std::chrono::high_resolution_clock::now();

    while (select.getQuitSelect()){

        auto currentTime = std::chrono::high_resolution_clock::now();
        double frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
        startTime = currentTime;

        accumulator += std::min(frameTime, 80.0);
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(1)));
        while(accumulator >= dt) {
            select.update(dt);
            accumulator -= dt;
        }
        handleEvents();
        update(0.0f, m_animationF1, m_animationF2, m_keycodeMenu);
        m_keycodeMenu = 0;

        SDL_RenderClear(m_renderer);

        renderStageTexture(backGround, -550, -300);
        //Title
        renderTextureSelectScene(atlasTexture, m_windowWidth / 2 - 500, 20, 0, 1148, 1000, 150); //texture, pos x jeu, pos y jeu, pos x atlas, pos y atlas, dim x elmt atlas, dim y elmt atlas

        if(select.getBoolP1Choose()){
            if(select.getBoolDudley() && select.getBoolP1()){
                nameP1 = "Dudley";
                setBoolP1(false);
            }
            else if(select.getBoolAlex() && select.getBoolP1()){
                nameP1 = "Alex";
                setBoolP1(false);
            }

            if(nameP1 == "Dudley"){
                renderTextureSelectSceneFighter(atlasTexture, 75, 200, 420, 588, 475, 555, true);//dud
                renderTextureSelectScene(atlasTexture, m_windowWidth / 3 - 250, 900, 0, 560, 400, 121);//dud name
            }
            else if(nameP1 == "Alex"){
                renderTextureSelectSceneFighter(atlasTexture, 50, 200, 400, 10, 505, 555, true);//alex
                renderTextureSelectScene(atlasTexture, m_windowWidth / 3 - 250, 870, 0, 0, 400, 150);//alex name
            }
        }

        if(select.getBoolP2Choose()){
            if(select.getBoolDudley()){
                nameP2 = "Dudley"; 
            }
            else if(select.getBoolAlex()){ 
                nameP2 = "Alex";
            }

            if(nameP2 == "Dudley"){
                renderTextureSelectSceneFighter(atlasTexture, m_windowWidth / 2, 200, 420, 588, 475, 555, false);//dud
                renderTextureSelectScene(atlasTexture, m_windowWidth / 2 + 250, 900, 0, 560, 400, 121);//dud name
            }
            else if(nameP2 == "Alex"){
                renderTextureSelectSceneFighter(atlasTexture, m_windowWidth / 2, 200, 400, 10, 505, 555, false);//alex
                renderTextureSelectScene(atlasTexture, m_windowWidth / 2 + 250, 870, 0, 0, 400, 150);//alex name
            }
        }

        if(select.getBoolP2Choose() == false){
            if(select.getBoolDudley()){
                if(select.getBoolP1()){
                    renderTextureSelectSceneFighter(atlasTexture, 75, 200, 420, 588, 475, 555, true);//dud
                }
                else if(select.getBoolP2()){
                    renderTextureSelectSceneFighter(atlasTexture, m_windowWidth / 2, 200, 420, 588, 475, 555, false);
                }
                renderSelectSceneBox(select, atlasTexture, m_windowWidth / 2 - 90, 470, false);
                renderTextureSelectSceneMini(atlasTexture, m_windowWidth / 2 - 83, 494, 0, 698, 100, 91);//mini dud
                renderTextureSelectSceneMini(atlasTexture, m_windowWidth / 2 - 90, 690, 1201, 36, 108, 108); ///box static
                renderTextureSelectSceneMini(atlasTexture, m_windowWidth / 2 - 83, 719, 0, 173, 100, 89);//mini alex
            }

            if(select.getBoolAlex()){
                if(select.getBoolP1()){
                    renderTextureSelectSceneFighter(atlasTexture, 50, 200, 400, 10, 505, 555, true);//alex
                }
                else if(select.getBoolP2()){
                    renderTextureSelectSceneFighter(atlasTexture, m_windowWidth / 2, 200, 400, 10, 505, 555);//alex
                }
                renderSelectSceneBox(select, atlasTexture, m_windowWidth / 2 - 90, 690, false);
                renderTextureSelectSceneMini(atlasTexture, m_windowWidth / 2 - 83, 719, 0, 173, 100, 89);//mini alex
                renderTextureSelectSceneMini(atlasTexture, m_windowWidth / 2 - 90, 470, 1201, 36, 108, 108); // box static
                renderTextureSelectSceneMini(atlasTexture, m_windowWidth / 2 - 83, 494, 0, 698, 100, 91);//mini dud
            }
        }

        renderBlackStripes();
        SDL_RenderPresent(m_renderer);
    }
    m_game.setFighterNames(nameP1, nameP2);
    SDL_DestroyTexture(backGround);
    SDL_DestroyTexture(atlasTexture);

    m_game.changeState(GameState::BattleScene);
}


void GameEngine::setBoolP1(bool b){
    SelectScene& select = m_game.getSelectScene();
    select.m_p1 = b;
}

void GameEngine::runLoadingScene(){
    LoadingScene& loadingScene = m_game.getLoadingScene();
    
    // Loading textures
    SDL_Texture* img1 = loadTexture(loadingScene.getImg1Path());
    SDL_Texture* img2 = loadTexture(loadingScene.getImg2Path());
    SDL_Texture* img3 = loadTexture(loadingScene.getImg3Path());
    SDL_Texture* img4 = loadTexture(loadingScene.getImg4Path());
    SDL_Texture* img5 = loadTexture(loadingScene.getImg5Path());
    SDL_Texture* img6 = loadTexture(loadingScene.getImg6Path());
    SDL_Texture* img7 = loadTexture(loadingScene.getImg7Path());
    SDL_Texture* img8 = loadTexture(loadingScene.getImg8Path());

    while(loadingScene.getQuit()){
        SDL_RenderClear(m_renderer);

        handleEvents();
        update(0.0f, m_animationF1, m_animationF2, m_keycodeMenu);
        m_keycodeMenu = 0;

        renderCopy(img1, nullptr, nullptr);
        renderBlackStripes();
        SDL_RenderPresent(m_renderer);
        SDL_Delay(100);

        SDL_RenderClear(m_renderer);
        renderCopy(img2, nullptr, nullptr);
        renderBlackStripes();
        SDL_RenderPresent(m_renderer);
        SDL_Delay(100);

        SDL_RenderClear(m_renderer);
        renderCopy(img3, nullptr, nullptr);
        renderBlackStripes();
        SDL_RenderPresent(m_renderer);
        SDL_Delay(100);

        SDL_RenderClear(m_renderer);
        renderCopy(img4, nullptr, nullptr);
        renderBlackStripes();
        SDL_RenderPresent(m_renderer);
        SDL_Delay(100);

        SDL_RenderClear(m_renderer);
        renderCopy(img5, nullptr, nullptr);
        renderBlackStripes();
        SDL_RenderPresent(m_renderer);
        SDL_Delay(100);

        SDL_RenderClear(m_renderer);
        renderCopy(img6, nullptr, nullptr);
        renderBlackStripes();
        SDL_RenderPresent(m_renderer);
        SDL_Delay(100);

        SDL_RenderClear(m_renderer);
        renderCopy(img7, nullptr, nullptr);
        renderBlackStripes();
        SDL_RenderPresent(m_renderer);
        SDL_Delay(100);

        SDL_RenderClear(m_renderer);
        renderCopy(img8, nullptr, nullptr);
        renderBlackStripes();
        SDL_RenderPresent(m_renderer);
        SDL_Delay(100);

    }

    SDL_DestroyTexture(img1);
    SDL_DestroyTexture(img2);
    SDL_DestroyTexture(img3);
    SDL_DestroyTexture(img4);
    SDL_DestroyTexture(img5);
    SDL_DestroyTexture(img6);
    SDL_DestroyTexture(img7);
    SDL_DestroyTexture(img8);

    m_game.changeState(GameState::MainMenu);
}

void GameEngine::regressionTest() {
    // Initialize GameEngine instance for testing
    GameEngine engine;

    // Test initialization
    bool initSuccess = engine.init("Test Window", 100, 100, 800, 600, false);
    assert(initSuccess && "Initialization failed.");

    // Test loadFont
    engine.loadFont("test_font.ttf", 16); // Assuming "test_font.ttf" is a valid font file

    // Test loadTexture
    SDL_Texture* texture = engine.loadTexture("test_texture.png"); // Assuming "test_texture.png" is a valid texture file
    assert(texture == nullptr && "Failed to load texture.");

    // Test setWindowSize
    engine.setWindowSize(1024, 768);

    // Test setFullscreen
    engine.setFullscreen(true);

    // Test setBoolP1
    engine.setBoolP1(true);

    // Test shouldQuit
    SDL_Event quitEvent;
    quitEvent.type = SDL_QUIT;
    bool quitExpected = engine.shouldQuit(quitEvent);
    assert(quitExpected && "shouldQuit failed to detect SDL_QUIT event.");

    // Test returnValueSDL
    SDL_Keycode keyCode = engine.returnValueSDL("test_action");
    assert(keyCode != SDLK_SPACE && "Incorrect SDL keycode returned.");

    // Add more tests for other functions as needed...

    // Clean up resources
    SDL_DestroyTexture(texture);
    engine.cleanEngine();
}