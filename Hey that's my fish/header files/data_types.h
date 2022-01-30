#pragma once

#include "allegro5/allegro_font.h"

#include "defines.h"

typedef enum {
    StartScreen,
    MainMenu,
    SettingsMenu,
    PlayerCountMenu,
    Game,
    WinnerScreen
} Screen;

typedef enum {
    Play, Settings, Exit,
    New, Players, Load, PlayerSelectBack,
    Resolution, FullScreen, SettingsBack
} Button;

typedef enum {
    Player1PositionSelect = 1, Player2PositionSelect,
    Player3PositionSelect, Player4PositionSelect,
    Player1Turn, Player2Turn, Player3Turn, Player4Turn
} GamePhase;

typedef struct {

    int fish;
    int penguin;

} Tile;

typedef struct {

    bool done;

    int resX;
    int resY;

    int resIndex;
    bool hasRes;
    bool fullScreen;

    ALLEGRO_FONT *font_l;
    ALLEGRO_FONT *font_m;
    ALLEGRO_FONT *font_s;

    int fontSize_l;
    int fontSize_m;
    int fontSize_s;

    Screen screen;

    Button button;

    GamePhase gamePhase;

    Tile tileMap[TILE_ROW][TILE_COL];

    float hexagonLength;
    float hexagonDistance;
    float hexagonOutline;
    float penguinOutline;
    float menuHeight;
    float menuThickness;

    int playerCount;

    int selectedHexagonI;
    int selectedHexagonJ;

    int selectedPenguinI;
    int selectedPenguinJ;

    int playerDestroyedTiles[4];
    int playerEatenFish[4];

    bool lost[4];

} GameData;