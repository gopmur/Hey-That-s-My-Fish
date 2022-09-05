/////////////////////////////
/////////////////////////////
//                         //
//   HEY THAT'S MY FISH!   //
//       ALI  JAFARI       //
//                         //
/////////////////////////////
/////////////////////////////

//-------INCLUDES-------//

#include <stdbool.h>
#include <stdio.h>

#include "allegro5/allegro.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"

#include "../header files/defines.h"
#include "../header files/data_types.h"
#include "../header files/prototypes.h"

//---------MAIN---------//

int main() {

    int resList[][2] = {
        { 800,  600  },
        { 1024, 768  },
        { 1152, 864  },
        { 1280, 600  },
        { 1280, 720  },
        { 1280, 768  },
        { 1280, 800  },
        { 1280, 960  },
        { 1280, 1024 },
        { 1360, 768  },
        { 1366, 768  },
        { 1400, 1050 },
        { 1440, 900  },
        { 1600, 900  },
        { 1600, 1200 },
        { 1680, 1050 },
        { 1792, 1344 },
        { 1856, 1392 },
        { 1920, 1080 },
        { 1920, 1200 },
        { 1920, 1440 },
        { 2048, 1152 },
        { 2048, 1536 },
        { 2560, 1600 },
        { 0,    0,   }
    };

    GameData gameData;

    bool error = false;
    bool redraw = true;
    bool done = false;

    gameData.hasRes = false;

    ALLEGRO_EVENT event;

    int penguinCountTemp;

    gameData.resX = 800;
    gameData.resY = 600;

    get_screen_resolution(&gameData.resX, &gameData.resY);

    for (int i = 0; i < RES_NUM; i++) {
        if (gameData.resX == resList[i][0] && gameData.resY == resList[i][1]) {
            gameData.resIndex = i;
            gameData.hasRes = true;
        }
    }

    if (!gameData.hasRes) {
        resList[RES_NUM][0] = gameData.resX;
        resList[RES_NUM][1] = gameData.resY;
        gameData.resIndex = RES_NUM;
    }

    gameData.fullScreen = true;

    // the firts screen shown to the user is the start screen
    gameData.screen = StartScreen;

    gameData.hexagonLength = gameData.resY/24.0;
    gameData.hexagonDistance = gameData.resY/96.0;
    gameData.hexagonOutline = gameData.resY/240.0;
    gameData.penguinOutline = gameData.resY/240.0;
    gameData.menuHeight = (gameData.resY*7)/48.0;
    gameData.menuThickness = gameData.resY/48.0;

    gameData.fontSize_l = gameData.resY/10;
    gameData.fontSize_m = gameData.resY/16;
    gameData.fontSize_s = gameData.resY/24;

    check_init(al_init(), "Allegro", &error);
    check_init(al_init_ttf_addon(), "Allegro TTF addon", &error);
    check_init(al_init_primitives_addon(), "Allegro primitives addon", &error);
    check_init(al_install_keyboard(), "Allegro keyboard", &error);

    al_set_new_display_flags(ALLEGRO_FULLSCREEN);

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_DISPLAY *display = al_create_display(gameData.resX, gameData.resY);
    gameData.font_l = al_load_ttf_font("ThaleahFat.ttf", gameData.fontSize_l, 0);
    gameData.font_m = al_load_ttf_font("ThaleahFat.ttf", gameData.fontSize_m, 0);
    gameData.font_s = al_load_ttf_font("ThaleahFat.ttf", gameData.fontSize_s, 0);

    check_init(timer, "Timer", &error);
    check_init(queue, "Event queue", &error);
    check_init(display, "Display", &error);
    if (!gameData.font_l) {
        gameData.font_l = al_load_ttf_font("../../Hey that's my fish/fonts/ThaleahFat.ttf", gameData.fontSize_l, 0);
        gameData.font_m = al_load_ttf_font("../../Hey that's my fish/fonts/ThaleahFat.ttf", gameData.fontSize_m, 0);
        gameData.font_s = al_load_ttf_font("../../Hey that's my fish/fonts/ThaleahFat.ttf", gameData.fontSize_s, 0);
    }
    check_init(gameData.font_l, "Font \"ThaleahFat.ttf\"", &error);

    // if any errors occurred ends the program
    if (error) {
        al_destroy_timer(timer);
        al_destroy_event_queue(queue);
        al_destroy_display(display);
        al_destroy_font(gameData.font_l);
        al_destroy_font(gameData.font_m);
        al_destroy_font(gameData.font_s);
        return 1;
    }

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);
    while (!done) {

        al_wait_for_event(queue, &event);

        // checks for event type
        switch (event.type) {

            // if event is a timer event redraws the screen
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;

            // if event is a key down event checks the current screen
            // then  checks  the  key  code  of  the  pressed  button
            // then  according  to  the  current  situation  runs the 
            // required operation
            case ALLEGRO_EVENT_KEY_DOWN:

                switch (gameData.screen) {

                    case StartScreen:
                        key_handle_start_screen(event, &gameData);
                        break;

                    case MainMenu:
                        key_handle_main_menu(event, &gameData, &done, resList);
                        break;

                    case PlayerCountMenu:
                        key_handle_player_count_menu(event, &gameData, &penguinCountTemp);
                        break;

                    case SettingsMenu:
                        key_handle_settings_menu(event, &gameData, display, queue, resList);
                        break;

                    case Game:
                        key_handle_game_screen(event, &gameData, &penguinCountTemp);
                        break;

                    case WinnerScreen:
                        key_handle_winner_screen(event, &gameData);
                        break;

                }

                break;

                // if the close button is pressed sets the done flag to true
                // ending the program
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;

        }

        // checks the current screen and calls the draw function of the 
        // current screen
        if (redraw && al_is_event_queue_empty(queue)) {

            switch (gameData.screen) {

                case StartScreen:
                    draw_start_screen(gameData);
                    break;

                case MainMenu:
                    draw_main_menu(gameData);
                    break;

                case SettingsMenu:
                    draw_settings_menu(gameData, resList);
                    break;

                case PlayerCountMenu:
                    draw_player_select_menu(gameData);
                    break;

                case Game:
                    draw_game_screen(gameData);
                    break;

                case WinnerScreen:
                    draw_winner_screen(gameData);
                    break;

            }

            al_flip_display();

            redraw = false;

        }

    }

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    al_destroy_font(gameData.font_l);
    al_destroy_font(gameData.font_m);
    al_destroy_font(gameData.font_s);

    return 0;
    
}