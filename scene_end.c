#include "scene_end.h"
#include "scene_settings.h"
#include "utility.h"
#include "shared.h"
#include "scene_menu.h"
#include "scene_game.h"
#include "scene_menu_object.h"



static ALLEGRO_BITMAP* gameTitleSettings = NULL;
static ALLEGRO_SAMPLE_ID menuBGM;

/* Static variables */
static int gameTitleWidth ;
static int gameTitleHeight ;
extern int game_highest_Score;
static Button menu_btn;

static void init(){
    
    //settings bitmaps
    gameTitleSettings = load_bitmap("Assets/title.png");
    gameTitleWidth = al_get_bitmap_width(gameTitleSettings);
    gameTitleHeight = al_get_bitmap_height(gameTitleSettings);
    
    
    //audio
    stop_bgm(menuBGM);
    menuBGM = play_bgm(themeMusic, music_volume);

    //menu button
    menu_btn = button_create(30, 20, 50, 50, "Assets/white_home.png", "Assets/yellow_home.png");
}

static void destroy(void){
    stop_bgm(menuBGM);
    al_destroy_bitmap(gameTitleSettings);
    al_destroy_bitmap(menu_btn.hovered_img);
    al_destroy_bitmap(menu_btn.default_img);

}


static void draw(void){
    al_clear_to_color(al_map_rgb(0, 0, 0));
    //title
    const float scale = 0.5;
    const float offset_width = (SCREEN_W >> 1) - 0.5 * scale * gameTitleWidth;
    const float offset_height = (SCREEN_H >> 3) - 0.5 * scale * gameTitleHeight;
    
    //draw title image
    al_draw_scaled_bitmap(
        gameTitleSettings, 0, 0, gameTitleWidth, gameTitleHeight,
        offset_width, offset_height, gameTitleWidth * scale, gameTitleHeight * scale, 0
    );
    
    //Text labels
    al_draw_text(menuFont, al_map_rgb(255, 255, 0), SCREEN_W - 480, SCREEN_H - 490, ALLEGRO_ALIGN_LEFT, "GAME OVER!");
    al_draw_text(menuFont, al_map_rgb(255, 255, 0), SCREEN_W - 490, SCREEN_H - 390, ALLEGRO_ALIGN_LEFT, "SCORE:");
    al_draw_textf(settingsFont, al_map_rgb(255, 255, 0), SCREEN_W - 290, SCREEN_H - 405, ALLEGRO_ALIGN_CENTER, "%d", game_highest_Score);
    al_draw_text(menuFont, al_map_rgb(255, 255, 0), SCREEN_W - 380, SCREEN_H - 290, ALLEGRO_ALIGN_CENTER, "Press \"Enter\" to play");
    
    //button
    drawButton(menu_btn);
}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f){
    menu_btn.hovered = buttonHover(menu_btn, mouse_x, mouse_y);
}

static void on_key_down(int key_code){
    switch(key_code){
        case ALLEGRO_KEY_ENTER:
            game_change_scene(scene_main_create());
            break;
        default:
            break;
    }
}

static void on_mouse_down(){
    if (menu_btn.hovered)
        game_change_scene(scene_menu_create());
}
        
    
Scene scene_end_create(void) {
    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    scene.initialize = &init;
    scene.name = "End";
    scene.draw = &draw;
    scene.destroy = &destroy;
    scene.on_key_up = &on_key_down;
    scene.on_mouse_move = &on_mouse_move;
    scene.on_mouse_down = &on_mouse_down;
    // TODO: Register more event callback functions such as keyboard, mouse, ...
    game_log("end scene created");
    return scene;
}


