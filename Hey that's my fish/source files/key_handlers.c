#include <stdio.h>

#include "allegro5/allegro.h"
#include "allegro5/allegro_ttf.h"

#include "../header files/prototypes.h"
#include "../header files/data_types.h"

void key_handle_start_screen(ALLEGRO_EVENT event, GameData *gameData) {

    switch (event.keyboard.keycode) {
        
        // if the enter key is pressed on the start screen 
        // changes   the   screen   to   the   main   menu
        case ALLEGRO_KEY_ENTER:
            gameData->screen = MainMenu;
            gameData->button = Play;
            break;

    }

    return;
}

void key_handle_main_menu(ALLEGRO_EVENT event, GameData *gameData, bool *done, int resList[][2]) {

    // if the up arrow key is pressed in the main menu 
    // changes the selected button to the upper button
    if (event.keyboard.keycode == ALLEGRO_KEY_UP && gameData->button > Play) {
        gameData->button--;
    }

    // if the down arrow key is pressed in the main menu 
    // changes the selected  button to the lower  button
    else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN && gameData->button < Exit) {
        gameData->button++;
    }

    // if the enter key is pressed activates the selected button
    else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {

        switch (gameData->button) {

            // if the Play button is activated changed the screen
            // to the  player  count menue  and sets the  initial
            // player count to 2
            case Play:
                gameData->screen = PlayerCountMenu;
                gameData->button = New;
                gameData->playerCount = 2;
                break;

            // if the Settings button is ativated changes the 
            // screen to the Settings screen
            case Settings:
                for (int i = 0; i < RES_NUM + 1; i++) {
                    if (gameData->resX == resList[i][0] && gameData->resY == resList[i][1]) {
                        gameData->resIndex = i;
                    }
                }
                gameData->screen = SettingsMenu;
                gameData->button = Resolution;
                break;

            // if the Exit button is activated closes the game
            case Exit:
                *done = true;
                break;

        }

    }

    return;
}

void key_handle_player_count_menu(ALLEGRO_EVENT event, GameData *gameData, int *penguinCountTemp) {

    switch (event.keyboard.keycode) {

        case ALLEGRO_KEY_UP:
            if (gameData->button > New) {
                gameData->button--;
            }
            break;

        case ALLEGRO_KEY_DOWN:
            if (gameData->button < PlayerSelectBack) {
                gameData->button++;
            }
            break;

        case ALLEGRO_KEY_ENTER:

            switch (gameData->button) {

                case New:

                    gameData->screen = Game;
                    generate_random_tile_map(gameData->tileMap);
                    gameData->gamePhase = Player1PositionSelect;
                    *penguinCountTemp = 6 - gameData->playerCount;

                    gameData->selectedHexagonI = 0;
                    gameData->selectedHexagonJ = 0;

                    gameData->selectedPenguinI = -1;
                    gameData->selectedPenguinJ = -1;

                    gameData->playerDestroyedTiles[0] = 0;
                    gameData->playerDestroyedTiles[1] = 0;
                    gameData->playerDestroyedTiles[2] = 0;
                    gameData->playerDestroyedTiles[3] = 0;

                    gameData->playerEatenFish[0] = 0;
                    gameData->playerEatenFish[1] = 0;
                    gameData->playerEatenFish[2] = 0;
                    gameData->playerEatenFish[3] = 0;

                    gameData->lost[2] = true;
                    gameData->lost[3] = true;

                    for (int i = 0; i < gameData->playerCount; i++) {
                        gameData->lost[i] = false;
                    }

                    break;

                case PlayerSelectBack:

                    gameData->screen = MainMenu;
                    gameData->button = Play;
                    break;

            }

            break;

        // if the escape key is pressed goes back to the main menu
        case ALLEGRO_KEY_ESCAPE:
            gameData->screen = MainMenu;
            gameData->button = Play;
            break;

        case ALLEGRO_KEY_RIGHT:
            if (gameData->button == Players && gameData->playerCount < 4) {
                gameData->playerCount++;
            }
            break;

        case ALLEGRO_KEY_LEFT:
            if (gameData->button == Players && gameData->playerCount > 2) {
                gameData->playerCount--;
            }

    }

    return;
}

void key_handle_settings_menu(ALLEGRO_EVENT event, GameData *gameData, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *queue, int resList[][2]) {

    switch (event.keyboard.keycode) {

        case ALLEGRO_KEY_UP:
            if (gameData->button > Resolution) {
                gameData->button--;
            }
            break;

        case ALLEGRO_KEY_DOWN:
            if (gameData->button < SettingsBack) {
                gameData->button++;
            }
            break;

        case ALLEGRO_KEY_ESCAPE:
            gameData->screen = MainMenu;
            gameData->button = Play;
            break;

        case ALLEGRO_KEY_RIGHT:
            if (gameData->button == Resolution) {
                if (gameData->hasRes && gameData->resIndex < RES_NUM - 1) {
                    gameData->resIndex++;
                }
                else if (!gameData->hasRes && gameData->resIndex < RES_NUM) {
                    gameData->resIndex++;
                }
            }
            break;

        case ALLEGRO_KEY_LEFT:
            if (gameData->button == Resolution) {
                if (gameData->resIndex > 0) {
                    gameData->resIndex--;
                }
            }
            break;

        case ALLEGRO_KEY_ENTER:

            switch (gameData->button) {

                case Resolution:

                    gameData->resX = resList[gameData->resIndex][0];
                    gameData->resY = resList[gameData->resIndex][1];

                    gameData->hexagonLength = gameData->resY/24.0;
                    gameData->hexagonDistance = gameData->resY/96.0;
                    gameData->hexagonOutline = gameData->resY/240.0;
                    gameData->penguinOutline = gameData->resY/240.0;
                    gameData->menuHeight = (gameData->resY*7)/48.0;
                    gameData->menuThickness = gameData->resY/48.0;

                    gameData->fontSize_l = gameData->resY/10;
                    gameData->fontSize_m = gameData->resY/16;
                    gameData->fontSize_s = gameData->resY/24;

                    al_destroy_font(gameData->font_l);
                    al_destroy_font(gameData->font_m);
                    al_destroy_font(gameData->font_s);

                    gameData->font_l = al_load_ttf_font("ThaleahFat.ttf", gameData->fontSize_l, 0);
                    gameData->font_m = al_load_ttf_font("ThaleahFat.ttf", gameData->fontSize_m, 0);
                    gameData->font_s = al_load_ttf_font("ThaleahFat.ttf", gameData->fontSize_s, 0);

                    al_resize_display(display, gameData->resX, gameData->resY);

                    break;

                case FullScreen:

                    if (gameData->fullScreen) {
                        al_destroy_display(display);
                        al_set_new_display_flags(ALLEGRO_WINDOWED);
                        display = al_create_display(gameData->resX, gameData->resY);
                        al_register_event_source(queue, al_get_display_event_source(display));
                        gameData->fullScreen = false;
                    }

                    else {
                        al_destroy_display(display);
                        al_set_new_display_flags(ALLEGRO_FULLSCREEN);
                        display = al_create_display(gameData->resX, gameData->resY);
                        al_register_event_source(queue, al_get_display_event_source(display));
                        gameData->fullScreen = true;
                    }

                    break;

                case SettingsBack:
                    gameData->screen = MainMenu;
                    gameData->button = Play;
                    break;

            }

            break;

    }

    return;
}

void key_handle_game_screen(ALLEGRO_EVENT event, GameData *gameData, int *penguinCountTemp) {

    int tempSum = 0;

    switch (event.keyboard.keycode) {

        case ALLEGRO_KEY_RIGHT:
            if (gameData->selectedHexagonI%2 == 0 && gameData->selectedHexagonJ < TILE_COL - 2) {
                gameData->selectedHexagonJ++;
            }
            else if (gameData->selectedHexagonI%2 == 1 && gameData->selectedHexagonJ < TILE_COL - 1) {
                gameData->selectedHexagonJ++;
            }
            break;

        case ALLEGRO_KEY_LEFT:
            if (gameData->selectedHexagonJ > 0) {
                gameData->selectedHexagonJ--;
            }
            break;

        case ALLEGRO_KEY_UP:
            if (gameData->selectedHexagonI > 0) {
                if (gameData->selectedHexagonI%2 == 1 && gameData->selectedHexagonJ == TILE_COL - 1) {
                    gameData->selectedHexagonJ--;
                }
                gameData->selectedHexagonI--;
            }
            break;

        case ALLEGRO_KEY_DOWN:
            if (gameData->selectedHexagonI < TILE_ROW - 1) {
                if (gameData->selectedHexagonI%2 == 1 && gameData->selectedHexagonJ == TILE_COL - 1) {
                    gameData->selectedHexagonJ--;
                }
                gameData->selectedHexagonI++;                
            }
            break;

        case ALLEGRO_KEY_ENTER:

            if (gameData->gamePhase >= Player1PositionSelect && gameData->gamePhase <= Player4PositionSelect &&
                !gameData->tileMap[gameData->selectedHexagonI][gameData->selectedHexagonJ].penguin) {

                gameData->tileMap[gameData->selectedHexagonI][gameData->selectedHexagonJ].penguin = gameData->gamePhase;
                (*penguinCountTemp)--;

                for (int i = 0; i < TILE_ROW; i++) {
                    for (int j = 0; j < TILE_COL; j++) {
                        if (gameData->tileMap[i][j].penguin) {
                            if (!check_possible_moves(i, j, gameData->tileMap)) {
                                gameData->tileMap[gameData->selectedHexagonI][gameData->selectedHexagonJ].penguin = 0;
                                (*penguinCountTemp)++;
                            }
                        }
                    }
                }

            }

            if (*penguinCountTemp == 0) {

                *penguinCountTemp = 6 - gameData->playerCount;
                gameData->gamePhase++;

                if (gameData->gamePhase > gameData->playerCount) {
                    gameData->gamePhase = Player1Turn;
                }

            }

            if ((gameData->selectedPenguinI != -1 || gameData->selectedPenguinJ != -1) &&
                validate_move(*gameData)) {

                gameData->playerDestroyedTiles[gameData->gamePhase - Player1Turn]++;
                gameData->playerEatenFish[gameData->gamePhase - Player1Turn] +=
                    gameData->tileMap[gameData->selectedPenguinI][gameData->selectedPenguinJ].fish;

                gameData->tileMap[gameData->selectedPenguinI][gameData->selectedPenguinJ].fish = 0;
                gameData->tileMap[gameData->selectedPenguinI][gameData->selectedPenguinJ].penguin = 0;

                gameData->tileMap[gameData->selectedHexagonI][gameData->selectedHexagonJ].penguin = gameData->gamePhase - Player4PositionSelect;

                gameData->selectedPenguinI = -1;
                gameData->selectedPenguinJ = -1;

                check_for_lost(gameData);
                for (int i = 0; i < gameData->playerCount; i++) {
                    tempSum += (!gameData->lost[i]);
                }

                if (tempSum == 1) {
                    gameData->screen = WinnerScreen;
                }

                do {
                    gameData->gamePhase++;
                    if (gameData->gamePhase > gameData->playerCount + Player4PositionSelect) {
                        gameData->gamePhase = Player1Turn;
                    }
                } while (gameData->lost[(gameData->gamePhase) - Player1Turn]);

            }

            else if (gameData->gamePhase >= Player1Turn && gameData->gamePhase <= Player4Turn &&
                    gameData->tileMap[gameData->selectedHexagonI][gameData->selectedHexagonJ].penguin ==
                    gameData->gamePhase - Player4PositionSelect) {

                gameData->selectedPenguinI = gameData->selectedHexagonI;
                gameData->selectedPenguinJ = gameData->selectedHexagonJ;

            }

            break;

            case ALLEGRO_KEY_ESCAPE:
                gameData->screen = MainMenu;
                gameData->button = Play;
                break;

    }

    return;
}

void key_handle_winner_screen(ALLEGRO_EVENT event, GameData *gameData) {

    switch (event.keyboard.keycode) {

        case ALLEGRO_KEY_ESCAPE:
            gameData->screen = MainMenu;
            gameData->button = Play;
            break;
        
    }

    return;
}