#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

#include "../header files/prototypes.h"
#include "../header files/data_types.h"
#include "../header files/defines.h"

void draw_hexagon(float x, float y, float length, ALLEGRO_COLOR color) {

    al_draw_filled_triangle(x, y, x, y - length, x + length*COS30, y - length/2, color);
    al_draw_filled_triangle(x, y, x + length*COS30, y - length/2, x + length*COS30, y + length/2, color);
    al_draw_filled_triangle(x, y, x + length*COS30, y + length/2, x, y + length, color);

    al_draw_filled_triangle(x, y, x, y - length, x - length*COS30, y - length/2, color);
    al_draw_filled_triangle(x, y, x - length*COS30, y - length/2, x - length*COS30, y + length/2, color);
    al_draw_filled_triangle(x, y, x - length*COS30, y + length/2, x, y + length, color);

    return;
}

void draw_start_screen(GameData gameData) {

    al_clear_to_color(al_map_rgb(BLACK_BACKGROUND_COLOR));

    al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY - gameData.fontSize_l - gameData.fontSize_m)/2, ALLEGRO_ALIGN_CENTER, "HEY THAT'S MY FISH!");
    al_draw_text(gameData.font_m, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY + gameData.fontSize_l - gameData.fontSize_m)/2, ALLEGRO_ALIGN_CENTER, "PRESS ENTER TO START");

    return;
}

void draw_main_menu(GameData gameData) {

    al_clear_to_color(al_map_rgb(BLACK_BACKGROUND_COLOR));

    switch (gameData.button) {

        case Play:
            al_draw_text(gameData.font_l, al_map_rgb(SELECTED_TEXT_COLOR), gameData.resX/2, (gameData.resY - 3*gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "PLAY");
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY - gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "SETTINGS");
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY + gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "EXIT");
            break;

        case Settings:
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY - 3*gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "PLAY");
            al_draw_text(gameData.font_l, al_map_rgb(SELECTED_TEXT_COLOR), gameData.resX/2, (gameData.resY - gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "SETTINGS");
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY + gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "EXIT");
            break;

        case Exit:
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY - 3*gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "PLAY");
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY - gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "SETTINGS");
            al_draw_text(gameData.font_l, al_map_rgb(SELECTED_TEXT_COLOR), gameData.resX/2, (gameData.resY + gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "EXIT");
            break;

    }

    return;
}

void draw_player_select_menu(GameData gameData) {

    al_clear_to_color(al_map_rgb(BLACK_BACKGROUND_COLOR));

    switch (gameData.button) {

        case New:
            al_draw_text(gameData.font_l, al_map_rgb(SELECTED_TEXT_COLOR), gameData.resX/2, (gameData.resY - 4*gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "NEW");
            al_draw_textf(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY - 2*gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "< %d PLAYER MODE >", gameData.playerCount);
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, gameData.resY/2, ALLEGRO_ALIGN_CENTER, "LOAD");
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY + 2*gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "BACK");
            break;

        case Players:
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY - 4*gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "NEW");
            al_draw_textf(gameData.font_l, al_map_rgb(SELECTED_TEXT_COLOR), gameData.resX/2, (gameData.resY - 2*gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "< %d PLAYER MODE >", gameData.playerCount);
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, gameData.resY/2, ALLEGRO_ALIGN_CENTER, "LOAD");
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY + 2*gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "BACK");
            break;

        case Load:
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY - 4*gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "NEW");
            al_draw_textf(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY - 2*gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "< %d PLAYER MODE >", gameData.playerCount);
            al_draw_text(gameData.font_l, al_map_rgb(SELECTED_TEXT_COLOR), gameData.resX/2, gameData.resY/2, ALLEGRO_ALIGN_CENTER, "LOAD");
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY + 2*gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "BACK");
            break;

        case PlayerSelectBack:
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY - 4*gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "NEW");
            al_draw_textf(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY - 2*gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "< %d PLAYER MODE >", gameData.playerCount);
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, gameData.resY/2, ALLEGRO_ALIGN_CENTER, "LOAD");
            al_draw_text(gameData.font_l, al_map_rgb(SELECTED_TEXT_COLOR), gameData.resX/2, (gameData.resY + 2*gameData.fontSize_l)/2, ALLEGRO_ALIGN_CENTER, "BACK");
            break;

    }

}

void draw_game_screen(GameData gameData) {

    al_clear_to_color(al_map_rgb(BLACK_BACKGROUND_COLOR));

    al_draw_rectangle(gameData.menuThickness/2, gameData.resY - gameData.menuHeight + gameData.menuThickness/2,
                      gameData.resX - gameData.menuThickness/2, gameData.resY - gameData.menuThickness/2,
                      al_map_rgb(GAME_MENU_BORDER_COLOR), gameData.menuThickness);

    switch (gameData.gamePhase) {

        case Player1PositionSelect:
            al_draw_text(gameData.font_s, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, gameData.resY - gameData.menuHeight/2 - gameData.fontSize_s/2,
                         ALLEGRO_ALIGN_CENTER, "Player 1's turn to place the penguins");
            break;

        case Player2PositionSelect:
            al_draw_text(gameData.font_s, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, gameData.resY - gameData.menuHeight/2 - gameData.fontSize_s/2,
                         ALLEGRO_ALIGN_CENTER, "Player 2's turn to place the penguins");
            break;

        case Player3PositionSelect:
            al_draw_text(gameData.font_s, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, gameData.resY - gameData.menuHeight/2 - gameData.fontSize_s/2,
                         ALLEGRO_ALIGN_CENTER, "Player 3's turn to place the penguins");
            break;

        case Player4PositionSelect:
            al_draw_text(gameData.font_s, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, gameData.resY - gameData.menuHeight/2 - gameData.fontSize_s/2,
                         ALLEGRO_ALIGN_CENTER, "Player 4's turn to place the penguins");
            break;

        case Player1Turn:
            al_draw_text(gameData.font_s, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, gameData.resY - gameData.menuHeight/2 - gameData.fontSize_s/2,
                         ALLEGRO_ALIGN_CENTER, "Player 1's turn to play");
            break;

        case Player2Turn:
            al_draw_text(gameData.font_s, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, gameData.resY - gameData.menuHeight/2 - gameData.fontSize_s/2,
                         ALLEGRO_ALIGN_CENTER, "Player 2's turn to play");
            break;

        case Player3Turn:
            al_draw_text(gameData.font_s, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, gameData.resY - gameData.menuHeight/2 - gameData.fontSize_s/2,
                         ALLEGRO_ALIGN_CENTER, "Player 3's turn to play");
            break;

        case Player4Turn:
            al_draw_text(gameData.font_s, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, gameData.resY - gameData.menuHeight/2 - gameData.fontSize_s/2,
                         ALLEGRO_ALIGN_CENTER, "Player 4's turn to play");
            break;

    }

    for (int i = 0; i < gameData.playerCount; i++) {
        al_draw_textf(gameData.font_s, al_map_rgb(WHITE_TEXT_COLOR), 20, 20 + i*gameData.fontSize_s, ALLEGRO_ALIGN_LEFT,
                      "Player %d's eaten fish: %2d", i + 1, gameData.playerEatenFish[i]);
    }

    float x;
    float y = gameData.resY/2 - 7*(gameData.hexagonDistance*COS30/2 + gameData.hexagonLength*3/2)/2 - gameData.menuHeight/2 + 50;

    for (int i = 0; i < TILE_ROW; i++) {

        if (i%2 == 0) x = gameData.resX/2 - 3*gameData.hexagonDistance - 6*COS30*gameData.hexagonLength;
        else x = gameData.resX/2 - 7*gameData.hexagonDistance/2 - 7*COS30*gameData.hexagonLength;

        for (int j = 0; j < TILE_COL; j++) {

            if (i == gameData.selectedHexagonI && j == gameData.selectedHexagonJ) {
                if ((gameData.selectedPenguinI != -1 || gameData.selectedPenguinJ != -1) && validate_move(gameData)) {
                    draw_hexagon(x, y, gameData.hexagonLength + gameData.hexagonOutline, al_map_rgb(VALID_HEXAGON_OUTLINE_COLOR));
                }

                else if ((gameData.selectedPenguinI != -1 || gameData.selectedPenguinJ != -1)) {
                    draw_hexagon(x, y, gameData.hexagonLength + gameData.hexagonOutline, al_map_rgb(INVALID_HEXAGON_OUTLINE_COLOR));
                    draw_hexagon(x, y, gameData.hexagonLength, al_map_rgb(BLACK_BACKGROUND_COLOR));
                }

                else {
                    draw_hexagon(x, y, gameData.hexagonLength + gameData.hexagonOutline, al_map_rgb(WHITE_HEXAGON_OUTLINE_COLOR));
                    draw_hexagon(x, y, gameData.hexagonLength, al_map_rgb(BLACK_BACKGROUND_COLOR));
                }
            }

            switch (gameData.tileMap[i][j].fish) {

                case 1:
                    draw_hexagon(x, y, gameData.hexagonLength, al_map_rgb(HEXAGON_COLOR_1));
                    break;

                case 2:
                    draw_hexagon(x, y, gameData.hexagonLength, al_map_rgb(HEXAGON_COLOR_2));
                    break;

                case 3:
                    draw_hexagon(x, y, gameData.hexagonLength, al_map_rgb(HEXAGON_COLOR_3));
                    break;

            }

            if (i == gameData.selectedPenguinI && j == gameData.selectedPenguinJ) {
                al_draw_filled_circle(x, y, gameData.hexagonLength/2 + gameData.penguinOutline, al_map_rgb(PLAYER_OUTLINE_COLOR));
            }

            switch (gameData.tileMap[i][j].penguin) {

                case 1:
                    al_draw_filled_circle(x, y, gameData.hexagonLength/2, al_map_rgb(PLAYER_COLOR_1));
                    break;

                case 2:
                    al_draw_filled_circle(x, y, gameData.hexagonLength/2, al_map_rgb(PLAYER_COLOR_2));
                    break;

                case 3:
                    al_draw_filled_circle(x, y, gameData.hexagonLength/2, al_map_rgb(PLAYER_COLOR_3));
                    break;

                case 4:
                    al_draw_filled_circle(x, y, gameData.hexagonLength/2, al_map_rgb(PLAYER_COLOR_4));
                    break;

            }

            x += 2*COS30*gameData.hexagonLength + gameData.hexagonDistance;

        }

        y += gameData.hexagonDistance*COS30/2 + gameData.hexagonLength*3/2;

    }

    return;
}

void draw_settings_menu(GameData gameData, int resList[][2]) {

    al_clear_to_color(al_map_rgb(BLACK_BACKGROUND_COLOR));

    switch (gameData.button) {

        case Resolution:
            al_draw_textf(gameData.font_l, al_map_rgb(SELECTED_TEXT_COLOR), gameData.resX/2, gameData.resY/2 - 3*gameData.fontSize_l/2, ALLEGRO_ALIGN_CENTER, "< RESOLUTION: %d x %d >", resList[gameData.resIndex][0], resList[gameData.resIndex][1]);
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, gameData.resY/2 - gameData.fontSize_l/2, ALLEGRO_ALIGN_CENTER, "FULLSCREEN");
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, gameData.resY/2 + gameData.fontSize_l/2, ALLEGRO_ALIGN_CENTER, "BACK");
            break;

        case FullScreen:
            al_draw_textf(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, gameData.resY/2 - 3*gameData.fontSize_l/2, ALLEGRO_ALIGN_CENTER, "< RESOLUTION: %d x %d >", resList[gameData.resIndex][0], resList[gameData.resIndex][1]);
            al_draw_text(gameData.font_l, al_map_rgb(SELECTED_TEXT_COLOR), gameData.resX/2, gameData.resY/2 - gameData.fontSize_l/2, ALLEGRO_ALIGN_CENTER, "FULLSCREEN");
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, gameData.resY/2 + gameData.fontSize_l/2, ALLEGRO_ALIGN_CENTER, "BACK");
            break;

        case SettingsBack:
            al_draw_textf(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, gameData.resY/2 - 3*gameData.fontSize_l/2, ALLEGRO_ALIGN_CENTER, "< RESOLUTION: %d x %d >", resList[gameData.resIndex][0], resList[gameData.resIndex][1]);
            al_draw_text(gameData.font_l, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, gameData.resY/2 - gameData.fontSize_l/2, ALLEGRO_ALIGN_CENTER, "FULLSCREEN");
            al_draw_text(gameData.font_l, al_map_rgb(SELECTED_TEXT_COLOR), gameData.resX/2, gameData.resY/2 + gameData.fontSize_l/2, ALLEGRO_ALIGN_CENTER, "BACK");
            break;

    }

    return;
}

void draw_winner_screen(GameData gameData) {

    al_clear_to_color(al_map_rgb(BLACK_BACKGROUND_COLOR));

    int temp;

    int sortedPlayers[4];
    int sortedPlayerEatenFish[4];
    for (int i = 0; i < gameData.playerCount; i++) {
        sortedPlayers[i] = i + 1;
        sortedPlayerEatenFish[i] = gameData.playerEatenFish[i];
    }

    // sorts players eaten fish 
    for (int i = 0; i < gameData.playerCount - 1; i++) {
        for (int j = 0; j < gameData.playerCount - i - 1; j++) {
            if (sortedPlayerEatenFish[j + 1] > sortedPlayerEatenFish[j]) {

                temp = sortedPlayerEatenFish[j];
                sortedPlayerEatenFish[j] = sortedPlayerEatenFish[j + 1];
                sortedPlayerEatenFish[j + 1] = temp;

                temp = sortedPlayers[j];
                sortedPlayers[j] = sortedPlayers[j + 1];
                sortedPlayers[j + 1] = temp;

            }
        }
    } 

    
    al_draw_textf(gameData.font_m, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY - 2*gameData.fontSize_m - (gameData.playerCount - 1)*gameData.fontSize_s)/2, ALLEGRO_ALIGN_CENTER, "THE WINNER IS PLAYER %d", sortedPlayers[0]);
    al_draw_textf(gameData.font_m, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY - (gameData.playerCount - 1)*gameData.fontSize_s)/2, ALLEGRO_ALIGN_CENTER, "WHITH %d FISH EATEN AND %d TILES DESTROYED", sortedPlayerEatenFish[0], gameData.playerDestroyedTiles[sortedPlayers[0] - 1]);
    for (int i = 1; i < gameData.playerCount; i++) {
        al_draw_textf(gameData.font_s, al_map_rgb(WHITE_TEXT_COLOR), gameData.resX/2, (gameData.resY + 2*gameData.fontSize_m - (gameData.playerCount - 1 -2*(i - 1))*gameData.fontSize_s)/2,
        ALLEGRO_ALIGN_CENTER, "PLAYER %d ATE %d FISH AND DESTROYED %d TILES", sortedPlayers[i], sortedPlayerEatenFish[i], gameData.playerDestroyedTiles[sortedPlayers[i] - 1]);
    }

    return;
}