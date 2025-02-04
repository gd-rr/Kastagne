# Compilation
CC 		 = g++
CFLAGS   = -g #-Wall
LFLAGS   = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Directories
BIN_DIR  = ./bin
BRG_DIR  = ./bin/regression
DOC_DIR  = ./doc
LIB_DIR  = ./lib
OBJ_DIR  = ./obj/src
ORG_DIR  = ./obj/regression
SRC_DIR  = ./src
COR_DIR  = ./src/core
CAM_DIR  = ./src/core/camera
FGT_DIR  = ./src/core/fighter
HUD_DIR  = ./src/core/hud
JSN_DIR  = ./src/core/json
MEN_DIR  = ./src/core/menu
SCN_DIR  = ./src/core/scene
STG_DIR  = ./src/core/stage
GAM_DIR  = ./src/game
HIT_DIR  = ./src/hitbox
REG_DIR  = ./src/regression
SDL_DIR  = ./src/sdl
TXT_DIR  = ./src/text
UTL_DIR  = ./src/utils

# Creation of binaries files
#all: docs $(BIN_DIR)/game $(BIN_DIR)/gameTxt $(BIN_DIR)/regressionCamera $(BIN_DIR)/regressionStateMachine $(BIN_DIR)/regressionHud $(BIN_DIR)/regressionBattleScene
all: $(BIN_DIR)/game $(BIN_DIR)/gameTxt $(BRG_DIR)/regressionMenu $(BRG_DIR)/regressionLoadingScene $(BRG_DIR)/regressionSelectScene $(BRG_DIR)/regressionWinTxt $(BRG_DIR)/regressionCamera $(BRG_DIR)/regressionStateMachine $(BRG_DIR)/regressionHud $(BRG_DIR)/regressionBattleScene $(BRG_DIR)/regressionStage $(BRG_DIR)/regressionSoundManager $(BRG_DIR)/regressionFighter $(BRG_DIR)/regressionGame $(BRG_DIR)/regressionGameEngine

# Creation of documentation
#docs:
#	doxygen $(DOC_DIR)/doxyfile

# Creation of game executable
$(BIN_DIR)/game: $(OBJ_DIR)/mainSDL.o $(OBJ_DIR)/Game.o $(OBJ_DIR)/GameEngine.o $(OBJ_DIR)/Fighter.o $(OBJ_DIR)/Stage.o $(OBJ_DIR)/Camera.o $(OBJ_DIR)/StateMachine.o $(OBJ_DIR)/Hud.o $(OBJ_DIR)/SoundManager.o $(OBJ_DIR)/BattleScene.o $(OBJ_DIR)/SelectScene.o $(OBJ_DIR)/LoadingScene.o $(OBJ_DIR)/Menu.o
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

# Creation of game text version executable
$(BIN_DIR)/gameTxt : $(OBJ_DIR)/mainTxt.o $(OBJ_DIR)/WinTxt.o
	$(CC) $(CFLAGS) $^ -o $@

$(BRG_DIR)/regressionMenu : $(ORG_DIR)/regressionMenu.o $(OBJ_DIR)/Menu.o
	$(CC) $(CFLAGS) $^ -o $@

$(BRG_DIR)/regressionGame : $(ORG_DIR)/regressionGame.o $(OBJ_DIR)/Game.o $(OBJ_DIR)/Menu.o $(OBJ_DIR)/LoadingScene.o $(OBJ_DIR)/SelectScene.o $(OBJ_DIR)/BattleScene.o $(OBJ_DIR)/Stage.o $(OBJ_DIR)/Camera.o $(OBJ_DIR)/Hud.o $(OBJ_DIR)/Fighter.o $(OBJ_DIR)/StateMachine.o
	$(CC) $(CFLAGS) $^ -o $@

$(BRG_DIR)/regressionLoadingScene : $(ORG_DIR)/regressionLoadingScene.o $(OBJ_DIR)/LoadingScene.o
	$(CC) $(CFLAGS) $^ -o $@

$(BRG_DIR)/regressionSelectScene : $(ORG_DIR)/regressionSelectScene.o $(OBJ_DIR)/SelectScene.o
	$(CC) $(CFLAGS) $^ -o $@

$(BRG_DIR)/regressionWinTxt : $(ORG_DIR)/regressionWinTxt.o $(OBJ_DIR)/WinTxt.o
	$(CC) $(CFLAGS) $^ -o $@

$(BRG_DIR)/regressionCamera : $(ORG_DIR)/regressionCamera.o $(OBJ_DIR)/Camera.o
	$(CC) $(CFLAGS) $^ -o $@

$(BRG_DIR)/regressionStateMachine : $(ORG_DIR)/regressionStateMachine.o $(OBJ_DIR)/StateMachine.o
	$(CC) $(CFLAGS) $^ -o $@

$(BRG_DIR)/regressionHud : $(ORG_DIR)/regressionHud.o $(OBJ_DIR)/Hud.o
	$(CC) $(CFLAGS) $^ -o $@

$(BRG_DIR)/regressionBattleScene : $(ORG_DIR)/regressionBattleScene.o $(OBJ_DIR)/BattleScene.o $(OBJ_DIR)/Stage.o $(OBJ_DIR)/Camera.o $(OBJ_DIR)/Hud.o $(OBJ_DIR)/Fighter.o $(OBJ_DIR)/StateMachine.o
	$(CC) $(CFLAGS) $^ -o $@

$(BRG_DIR)/regressionStage : $(ORG_DIR)/regressionStage.o $(OBJ_DIR)/Stage.o
	$(CC) $(CFLAGS) $^ -o $@

$(BRG_DIR)/regressionFighter : $(ORG_DIR)/regressionFighter.o $(OBJ_DIR)/Fighter.o $(OBJ_DIR)/StateMachine.o
	$(CC) $(CFLAGS) $^ -o $@

$(BRG_DIR)/regressionSoundManager : $(ORG_DIR)/regressionSoundManager.o $(OBJ_DIR)/SoundManager.o
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

$(BRG_DIR)/regressionGameEngine : $(ORG_DIR)/regressionGameEngine.o $(OBJ_DIR)/GameEngine.o  $(OBJ_DIR)/Game.o $(OBJ_DIR)/Menu.o $(OBJ_DIR)/LoadingScene.o $(OBJ_DIR)/SelectScene.o $(OBJ_DIR)/BattleScene.o $(OBJ_DIR)/Stage.o $(OBJ_DIR)/Camera.o $(OBJ_DIR)/Hud.o $(OBJ_DIR)/Fighter.o $(OBJ_DIR)/StateMachine.o $(OBJ_DIR)/SoundManager.o
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

# regressionTest.o

$(ORG_DIR)/regressionMenu.o: $(REG_DIR)/regressionMenu.cpp $(MEN_DIR)/Menu.h
	$(CC) $(CFLAGS) -c $< -o $@

$(ORG_DIR)/regressionGame.o: $(REG_DIR)/regressionGame.cpp $(GAM_DIR)/Game.h $(GAM_DIR)/GameState.h
	$(CC) $(CFLAGS) -c $< -o $@

$(ORG_DIR)/regressionLoadingScene.o: $(REG_DIR)/regressionLoadingScene.cpp $(SCN_DIR)/LoadingScene.h
	$(CC) $(CFLAGS) -c $< -o $@

$(ORG_DIR)/regressionSelectScene.o: $(REG_DIR)/regressionSelectScene.cpp $(SCN_DIR)/SelectScene.h
	$(CC) $(CFLAGS) -c $< -o $@

$(ORG_DIR)/regressionWinTxt.o: $(REG_DIR)/regressionWinTxt.cpp $(TXT_DIR)/WinTxt.h
	$(CC) $(CFLAGS) -c $< -o $@

$(ORG_DIR)/regressionCamera.o: $(REG_DIR)/regressionCamera.cpp $(CAM_DIR)/Camera.h
	$(CC) $(CFLAGS) -c $< -o $@

$(ORG_DIR)/regressionStateMachine.o: $(REG_DIR)/regressionStateMachine.cpp $(FGT_DIR)/StateMachine.h
	$(CC) $(CFLAGS) -c $< -o $@

$(ORG_DIR)/regressionFighter.o: $(REG_DIR)/regressionFighter.cpp $(FGT_DIR)/Fighter.h $(FGT_DIR)/StateMachine.h
	$(CC) $(CFLAGS) -c $< -o $@

$(ORG_DIR)/regressionHud.o: $(REG_DIR)/regressionHud.cpp $(HUD_DIR)/Hud.h
	$(CC) $(CFLAGS) -c $< -o $@

$(ORG_DIR)/regressionBattleScene.o: $(REG_DIR)/regressionBattleScene.cpp $(SCN_DIR)/BattleScene.h
	$(CC) $(CFLAGS) -c $< -o $@

$(ORG_DIR)/regressionStage.o: $(REG_DIR)/regressionStage.cpp $(STG_DIR)/Stage.h
	$(CC) $(CFLAGS) -c $< -o $@

$(ORG_DIR)/regressionSoundManager.o: $(REG_DIR)/regressionSoundManager.cpp $(SDL_DIR)/SoundManager.h
	$(CC) $(CFLAGS) -c $< -o $@

$(ORG_DIR)/regressionGameEngine.o: $(REG_DIR)/regressionGameEngine.cpp $(SDL_DIR)/GameEngine.h 
	$(CC) $(CFLAGS) -c $< -o $@

# Camera.o
$(OBJ_DIR)/Camera.o: $(CAM_DIR)/Camera.cpp $(CAM_DIR)/Camera.h $(UTL_DIR)/Vector2D.h
	$(CC) $(CFLAGS) -c $< -o $@

# Fighter.o
$(OBJ_DIR)/Fighter.o: $(FGT_DIR)/Fighter.cpp $(FGT_DIR)/Fighter.h $(FGT_DIR)/StateMachine.h $(UTL_DIR)/Vector2D.h
	$(CC) $(CFLAGS) -c $< -o $@

# StateMachine.o
$(OBJ_DIR)/StateMachine.o: $(FGT_DIR)/StateMachine.cpp $(FGT_DIR)/StateMachine.h
	$(CC) $(CFLAGS) -c $< -o $@

# Hud.o
$(OBJ_DIR)/Hud.o : $(HUD_DIR)/Hud.cpp $(HUD_DIR)/Hud.h
	$(CC) $(CFLAGS) -c $< -o $@

# Menu.o
$(OBJ_DIR)/Menu.o : $(MEN_DIR)/Menu.cpp $(MEN_DIR)/Menu.h
	$(CC) $(CFLAGS) -c $< -o $@

# BattleScene.o
$(OBJ_DIR)/BattleScene.o : $(SCN_DIR)/BattleScene.cpp $(SCN_DIR)/BattleScene.h $(FGT_DIR)/Fighter.h $(STG_DIR)/Stage.h $(CAM_DIR)/Camera.h $(HUD_DIR)/Hud.h
	$(CC) $(CFLAGS) -c $< -o $@

# LoadingScene.o
$(OBJ_DIR)/LoadingScene.o : $(SCN_DIR)/LoadingScene.cpp $(SCN_DIR)/LoadingScene.h
	$(CC) $(CFLAGS) -c $< -o $@

# SelectScene.o
$(OBJ_DIR)/SelectScene.o : $(SCN_DIR)/SelectScene.cpp $(SCN_DIR)/SelectScene.h $(UTL_DIR)/Vector2D.h
	$(CC) $(CFLAGS) -c $< -o $@

# Stage.o
$(OBJ_DIR)/Stage.o: $(STG_DIR)/Stage.cpp $(STG_DIR)/Stage.h
	$(CC) $(CFLAGS) -c $< -o $@

# Game.o
$(OBJ_DIR)/Game.o: $(GAM_DIR)/Game.cpp $(GAM_DIR)/Game.h $(GAM_DIR)/GameState.h $(MEN_DIR)/Menu.h $(SCN_DIR)/LoadingScene.h $(SCN_DIR)/SelectScene.h $(SCN_DIR)/BattleScene.h
	$(CC) $(CFLAGS) -c $< -o $@

# GameEngine.o
$(OBJ_DIR)/GameEngine.o: $(SDL_DIR)/GameEngine.cpp $(SDL_DIR)/GameEngine.h $(GAM_DIR)/Game.h $(SDL_DIR)/SoundManager.h 
	$(CC) $(CFLAGS) -c $< -o $@

# SoundManager.o
$(OBJ_DIR)/SoundManager.o : $(SDL_DIR)/SoundManager.cpp $(SDL_DIR)/SoundManager.h
	$(CC) $(CFLAGS) -c $< -o $@

# WinTxt.o
$(OBJ_DIR)/WinTxt.o: $(TXT_DIR)/WinTxt.cpp $(TXT_DIR)/WinTxt.h
	$(CC) $(CFLAGS) -c $< -o $@

# mainSDL.o
$(OBJ_DIR)/mainSDL.o: $(SRC_DIR)/mainSDL.cpp $(SDL_DIR)/GameEngine.h
	$(CC) $(CFLAGS) -c $< -o $@

# mainTxt.o
$(OBJ_DIR)/mainTxt.o: $(SRC_DIR)/mainTxt.cpp $(TXT_DIR)/WinTxt.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean obj files
clean:
	rm $(OBJ_DIR)/*.o $(ORG_DIR)/*.o

# Clean obj and binary files
clean_all:
	rm $(OBJ_DIR)/*.o $(ORG_DIR)/*.o $(BIN_DIR)/game $(BIN_DIR)/gameTxt $(BRG_DIR)/*