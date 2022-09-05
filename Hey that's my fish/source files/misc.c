#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#include "../header files/prototypes.h"
#include "../header files/data_types.h"

bool get_screen_resolution(int *resX, int *resY) {

    RECT desktopRectangle;
    HWND desktopHandle = GetDesktopWindow();

    if (desktopHandle && GetWindowRect(desktopHandle, &desktopRectangle)) {

        *resX = 2*desktopRectangle.right;
        *resY = 2*desktopRectangle.bottom;

        return true;

    }

    return false;
}

void check_init(bool function, char *description, bool *error) {
    if (!function) {
        printf("%s failed to initialize\n", description);
        *error = true;
    }
}

bool validate_move(GameData gameData) {

    if (gameData.selectedHexagonI == gameData.selectedPenguinI) {

        if (gameData.selectedHexagonJ == gameData.selectedPenguinJ) {
            return false;
        }

        if (gameData.selectedHexagonJ > gameData.selectedPenguinJ) {

            for (int j = gameData.selectedPenguinJ + 1; j <= gameData.selectedHexagonJ; j++) {

                if (gameData.tileMap[gameData.selectedHexagonI][j].penguin) {
                    return false;
                }
                else if (!gameData.tileMap[gameData.selectedHexagonI][j].fish) {
                    return false;
                }

            }

        }

        else {

            for (int j = gameData.selectedHexagonJ; j < gameData.selectedPenguinJ; j++) {

                if (gameData.tileMap[gameData.selectedHexagonI][j].penguin) {
                    return false;
                }
                else if (!gameData.tileMap[gameData.selectedHexagonI][j].fish) {
                    return false;
                }

            }

        }

        return true;
    }

    else if (gameData.selectedHexagonJ == gameData.selectedPenguinJ +
             (abs(gameData.selectedHexagonI - gameData.selectedPenguinI) +
             (gameData.selectedPenguinI + 1)%2)/2) {

        if (gameData.selectedHexagonI > gameData.selectedPenguinI) {

            for (int i = gameData.selectedPenguinI + 1; i <= gameData.selectedHexagonI; i++) {

                int j = gameData.selectedPenguinJ +
                    (abs(i - gameData.selectedPenguinI) + (gameData.selectedPenguinI + 1)%2)/2;
                if (gameData.tileMap[i][j].penguin) {
                    return false;
                }
                else if (!gameData.tileMap[i][j].fish) {
                    return false;
                }

            }

        }

        else {

            for (int i = gameData.selectedHexagonI; i < gameData.selectedPenguinI; i++) {

                int j = gameData.selectedPenguinJ +
                    (abs(i - gameData.selectedPenguinI) + (gameData.selectedPenguinI + 1)%2)/2;
                if (gameData.tileMap[i][j].penguin) {
                    return false;
                }
                else if (!gameData.tileMap[i][j].fish) {
                    return false;
                }

            }

        }

        return true;
    }

    else if (gameData.selectedHexagonJ == gameData.selectedPenguinJ -
             (abs(gameData.selectedHexagonI - gameData.selectedPenguinI) +
             (gameData.selectedPenguinI)%2)/2) {

        if (gameData.selectedHexagonI > gameData.selectedPenguinI) {

            for (int i = gameData.selectedPenguinI + 1; i <= gameData.selectedHexagonI; i++) {

                int j = gameData.selectedPenguinJ -
                    (abs(i - gameData.selectedPenguinI) + (gameData.selectedPenguinI)%2)/2;
                if (gameData.tileMap[i][j].penguin) {
                    return false;
                }
                else if (!gameData.tileMap[i][j].fish) {
                    return false;
                }

            }

        }

        else {

            for (int i = gameData.selectedHexagonI; i < gameData.selectedPenguinI; i++) {

                int j = gameData.selectedPenguinJ -
                    (abs(i - gameData.selectedPenguinI) + (gameData.selectedPenguinI)%2)/2;
                if (gameData.tileMap[i][j].penguin) {
                    return false;
                }
                else if (!gameData.tileMap[i][j].fish) {
                    return false;
                }

            }

        }

        return true;
    }

    else {
        return false;
    }

}

bool check_possible_moves(int i, int j, Tile tileMap[TILE_ROW][TILE_COL]) {

    if (i > 0) {
        if (tileMap[i - 1][j].fish && !tileMap[i - 1][j].penguin) {
            return true;
        }
        if (i%2 == 0) {
            if (tileMap[i - 1][j + 1].fish && !tileMap[i - 1][j + 1].penguin) {
                return true;
            }
        }
        else {
            if (j > 0) {
                if (tileMap[i - 1][j - 1].fish && !tileMap[i - 1][j - 1].penguin) {
                    return true;
                }
            }
        }
    }

    if (i < TILE_ROW - 1) {
        if (tileMap[i + 1][j].fish && !tileMap[i + 1][j].penguin) {
            return true;
        }
        if (i%2 == 0) {
            if (tileMap[i + 1][j + 1].fish && !tileMap[i + 1][j + 1].penguin) {
                return true;
            }
        }
        else {
            if (j > 0) {
                if (tileMap[i + 1][j - 1].fish && !tileMap[i + 1][j - 1].penguin) {
                    return true;
                }
            }
        }
    }

    if (j > 0) {
        if (tileMap[i][j - 1].fish && !tileMap[i][j - 1].penguin) {
            return true;
        }
    }

    if (j < TILE_COL - 1) {
        if (tileMap[i][j + 1].fish && !tileMap[i][j + 1].penguin) {
            return true;
        }
    }

    return false;

}

void check_for_lost(GameData *gameData) {

    int temp[4];

    for (int i = 0; i < gameData->playerCount; i++) {
        if (!gameData->lost[i]) {
            temp[i] = 6 - gameData->playerCount;
        }
    }

    for (int i = 0; i < TILE_ROW; i++) {
        for (int j = 0; j < TILE_COL; j++) {

            if (gameData->tileMap[i][j].penguin && !check_possible_moves(i, j, gameData->tileMap)) {
                temp[gameData->tileMap[i][j].penguin - 1]--;
            }

        }
    }

    for (int i = 0; i < gameData->playerCount; i++) {
        if (temp[i] == 0 && !gameData->lost[i]) {
            gameData->lost[i] = true;
            remove_player(i + 1, gameData);
        }
    }

    return;

}

void remove_player(int player, GameData *gameData) {

    int tempCount = 6 - gameData->playerCount;

    for (int i = 0; i < TILE_ROW; i++) {
        for (int j = 0; j < TILE_COL; j++) {

            if (gameData->tileMap[i][j].penguin == player) {

                gameData->tileMap[i][j].penguin = 0;
                tempCount--;

                if (tempCount == 0) {
                    return;
                }
            }

        }
    }

}

// fix it !!!!!!!!!!!!!!!!!!!
// not really random
void generate_random_tile_map(Tile tileMap[TILE_ROW][TILE_COL]) {

    int fishCount[] = {FISH_COUNT_1, FISH_COUNT_2, FISH_COUNT_3};

    int random;

    time_t t;

    // sets the random seed to the current time
    srand((unsigned) time(&t));

    for (int i = 0; i < TILE_ROW; i++) {
        for (int j = 0; j < TILE_COL; j++) {

            tileMap[i][j].penguin = 0;

            if (i % 2 == 0 && j == TILE_COL - 1) {
                tileMap[i][j].fish = 0;
            }

            else if (fishCount[0] && fishCount[1] && fishCount[2]) {
                random = (rand() % 3) + 1;
                tileMap[i][j].fish = random;
                fishCount[random - 1]--;
            }

            else if (fishCount[0] && fishCount[1]) {
                random = (rand() % 2) + 1;
                tileMap[i][j].fish = random;
                fishCount[random - 1]--;
            }

            else if (fishCount[0] && fishCount[2]) {
                random = (rand() % 2) * 2 + 1;
                tileMap[i][j].fish = random;
                fishCount[random - 1]--;
            }

            else if (fishCount[1] && fishCount[2]) {
                random = (rand() % 2) + 2;
                tileMap[i][j].fish = random;
                fishCount[random - 1]--;
            }

            else if (fishCount[0]) {
                tileMap[i][j].fish = 1;
            }

            else if (fishCount[1]) {
                tileMap[i][j].fish = 2;
            }

            else if (fishCount[2]) {
                tileMap[i][j].fish = 3;
            }

        }
    }

    return;
}



