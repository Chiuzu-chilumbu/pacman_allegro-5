// [HACKATHON 3-9]
// TODO: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.
#include "scene_settings.h"
#include "utility.h"
#include "shared.h"
#include "scene_menu.h"
#include "scene_game.h"
#include "scene_menu_object.h"


static ALLEGRO_BITMAP* gameTitleSettings = NULL;
static ALLEGRO_BITMAP* ghost1_logo = NULL;
static ALLEGRO_BITMAP* ghost2_logo = NULL;
static ALLEGRO_BITMAP* ghost3_logo = NULL;
static ALLEGRO_BITMAP* ghost4_logo = NULL;
static ALLEGRO_BITMAP* pacman_logo = NULL;
static ALLEGRO_BITMAP* volume_sprite = NULL;
static ALLEGRO_BITMAP* high_score = NULL;
//static ALLEGRO_BITMAP* volume_white = NULL;
static ALLEGRO_SAMPLE_ID menuBGM;

/* Static variables */
static int gameTitleWidth ;
static int gameTitleHeight ;
static int logo_H;
static int logo_W;
static Button music_volume_btn_minus;
static Button music_volume_btn_plus;
static Button effect_volume_btn_minus;
static Button effect_volume_btn_plus;
static Button menu_btn;
//static int game_sound = 0;
extern int game_highest_Score;

// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */

// TODO: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.
static void init(){
    
    //settings bitmaps
    gameTitleSettings = load_bitmap("Assets/title.png");
    gameTitleWidth = al_get_bitmap_width(gameTitleSettings);
    gameTitleHeight = al_get_bitmap_height(gameTitleSettings);
    
    //logo bitmaps
    pacman_logo = load_bitmap("Assets/pacman_move.png");
    ghost1_logo = load_bitmap("Assets/ghost_move_red.png");
    ghost2_logo = load_bitmap("Assets/ghost_move_pink.png");
    ghost3_logo = load_bitmap("Assets/ghost_move_blue.png");
    ghost4_logo = load_bitmap("Assets/ghost_move_orange.png");
    logo_H = al_get_bitmap_height(pacman_logo);
    logo_W = al_get_bitmap_width(pacman_logo);
    
    //volume settings
    volume_sprite = load_bitmap("Assets/volume_image.png");
    
    //audio
    stop_bgm(menuBGM);
    menuBGM = play_bgm(themeMusic, music_volume);

    //buttons
    music_volume_btn_minus = button_create(400, 210, 50, 50, "Assets/white_minus.png", "Assets/yellow_minus.png");
    music_volume_btn_plus = button_create(600, 210, 50, 50, "Assets/white_plus.png", "Assets/yellow_plus.png");
    effect_volume_btn_minus = button_create(400, 310, 50, 50, "Assets/white_minus.png", "Assets/yellow_minus.png");
    effect_volume_btn_plus = button_create(600, 310, 50, 50, "Assets/white_plus.png", "Assets/yellow_plus.png");
    menu_btn = button_create(30, 20, 50, 50, "Assets/white_home.png", "Assets/yellow_home.png");
    
    //high schore
    high_score = load_bitmap("Assets/high_score.png");
    
}

static void destroy(void){
    stop_bgm(menuBGM);
    al_destroy_bitmap(gameTitleSettings);
    al_destroy_bitmap(pacman_logo);
    al_destroy_bitmap(ghost4_logo);
    al_destroy_bitmap(ghost3_logo);
    al_destroy_bitmap(ghost2_logo);
    al_destroy_bitmap(ghost1_logo);
    al_destroy_bitmap(volume_sprite);
    al_destroy_bitmap(high_score);
    al_destroy_bitmap(menu_btn.hovered_img);
    al_destroy_bitmap(menu_btn.default_img);
    al_destroy_bitmap(music_volume_btn_plus.default_img);
    al_destroy_bitmap(music_volume_btn_plus.hovered_img);
    al_destroy_bitmap(music_volume_btn_minus.default_img);
    al_destroy_bitmap(music_volume_btn_minus.hovered_img);
    al_destroy_bitmap(effect_volume_btn_plus.default_img);
    al_destroy_bitmap(effect_volume_btn_plus.hovered_img);
    al_destroy_bitmap(effect_volume_btn_minus.default_img);
    al_destroy_bitmap(effect_volume_btn_minus.hovered_img);

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
    al_draw_text(settingsFont, al_map_rgb(255, 255, 0), SCREEN_W - 780, SCREEN_H - 390, ALLEGRO_ALIGN_LEFT, "Scores");
    al_draw_text(settingsFont, al_map_rgb(255, 255, 0), SCREEN_W - 780, SCREEN_H - 590, ALLEGRO_ALIGN_LEFT, "Music Vol");
    al_draw_text(settingsFont, al_map_rgb(255, 255, 0), SCREEN_W - 780, SCREEN_H - 490, ALLEGRO_ALIGN_LEFT, "Effect Vol");
    
    //draw logos
    al_draw_scaled_bitmap(pacman_logo, 16, 0, 16, 16, 570, 710, 70, 70, 0);
    al_draw_scaled_bitmap(ghost1_logo, 16, 0, 16, 16, 470, 710, 70, 70, 0);
    al_draw_scaled_bitmap(ghost2_logo, 16, 0, 16, 16, 370, 710, 70, 70, 0);
    al_draw_scaled_bitmap(ghost3_logo, 16, 0, 16, 16, 270, 710, 70, 70, 0);
    al_draw_scaled_bitmap(ghost4_logo, 16, 0, 16, 16, 170, 710, 70, 70, 0);

    //volume settings
    //music_volume
    al_draw_scaled_bitmap(volume_sprite, 0, 0, 225, 225, SCREEN_W / 3, SCREEN_H - 600, 70, 70, 0);
    al_draw_textf(settingsFont, al_map_rgb(255, 255, 0), SCREEN_W - 280, 210, ALLEGRO_ALIGN_CENTER, "%.1f", music_volume);
    drawButton(music_volume_btn_minus);
    drawButton(music_volume_btn_plus);
    
    //effect volume
    al_draw_scaled_bitmap(volume_sprite, 0, 0, 225, 225, SCREEN_W / 3, SCREEN_H - 500, 70, 70, 0);
    al_draw_textf(settingsFont, al_map_rgb(255, 255, 0), SCREEN_W - 280, 310, ALLEGRO_ALIGN_CENTER, "%.1f", effect_volume);
    drawButton(effect_volume_btn_minus);
    drawButton(effect_volume_btn_plus);
    
    //menu button
    drawButton(menu_btn);
    
    //High Score
    al_draw_text(menuFont, al_map_rgb(255, 255, 0), SCREEN_W - 380, SCREEN_H - 300, ALLEGRO_ALIGN_CENTER, "1ST");
    
    
    //high score label
    al_draw_scaled_bitmap(high_score, 0, 0, 300, 300, SCREEN_W / 3, SCREEN_H - 380, 70, 70, 0);
    al_draw_textf(menuFont, al_map_rgb(255, 255, 0), SCREEN_W - 280, SCREEN_H - 360, ALLEGRO_ALIGN_CENTER, "score");
    al_draw_textf(menuFont, al_map_rgb(255, 255, 0), SCREEN_W - 380, SCREEN_H - 360, ALLEGRO_ALIGN_CENTER, "rank");
   
    //high score rank
    al_draw_textf(settingsFont, al_map_rgb(255, 255, 0), SCREEN_W - 280, SCREEN_H - 315, ALLEGRO_ALIGN_CENTER, "%d", game_highest_Score);
    
}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f){
    music_volume_btn_minus.hovered = buttonHover(music_volume_btn_minus, mouse_x, mouse_y);
    music_volume_btn_plus.hovered = buttonHover(music_volume_btn_plus, mouse_x, mouse_y);
    effect_volume_btn_minus.hovered = buttonHover(effect_volume_btn_minus, mouse_x, mouse_y);
    effect_volume_btn_plus.hovered = buttonHover(effect_volume_btn_plus, mouse_x, mouse_y);
    menu_btn.hovered = buttonHover(menu_btn, mouse_x, mouse_y);
}


static void on_key_down(int key_code){
    switch(key_code){
        case ALLEGRO_KEY_ESCAPE:
            game_change_scene(scene_menu_create());
            break;
        default:
            break;
    }
}


static void on_mouse_down(){
    //volume
    if (music_volume_btn_minus.hovered){
        music_volume -= 0.1;
        if(music_volume < 0)
            music_volume = 0;
    }
    if (music_volume_btn_plus.hovered){
        music_volume += 0.1;
        if (music_volume > 1.0)
            music_volume = 1.0;
    }
    if (effect_volume_btn_minus.hovered){
        effect_volume -= 0.1;
        if(effect_volume < 0)
            effect_volume = 0;
    }
    if (effect_volume_btn_plus.hovered){
        effect_volume += 0.1;
        if (effect_volume > 1.0)
            effect_volume = 1.0;
    }
    //menu
    if (menu_btn.hovered)
        game_change_scene(scene_menu_create());
    
}
        
    
// The only function that is shared across files.
Scene scene_settings_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
    scene.initialize = &init;
	scene.name = "Settings";
	scene.draw = &draw;
    scene.destroy = &destroy;
    scene.on_key_up = &on_key_down;
    scene.on_mouse_move = &on_mouse_move;
    scene.on_mouse_down = &on_mouse_down;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Settings scene created");
	return scene;
}

