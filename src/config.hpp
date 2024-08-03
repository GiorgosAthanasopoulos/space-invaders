#pragma once

// sprites/music/sounds
// To configure look at the string path parameters of Load* function calls in
// asset_manager.cpp

// window
#define WIN_FLAGS FLAG_WINDOW_RESIZABLE
#define WIN_W 1280
#define WIN_H 720
#define WIN_TITLE "SpaceInvaders"
#define WIN_FPS 60
#define WIN_MIN_W 640
#define WIN_MIN_H 480
#define WIN_MAX_W 3840
#define WIN_MAX_H 2160
#define WIN_BG BLACK

// keybind
#define KEY_EXIT KEY_NULL
#define KEY_PLAYER_MOVE_LEFT KEY_A
#define KEY_PLAYER_MOVE_RIGHT KEY_D
#define KEY_PLAYER_SHOOT KEY_SPACE
#define KEY_RESTART KEY_SPACE
#define KEY_PAUSE_GAME KEY_P
#define KEY_MUTE KEY_M
#define KEY_FREEZE KEY_F

// debug
#define DEBUG false
#define DEBUG_HTBX_THICK 1
#define DEBUG_HTBX_COLOR RED

// bullet
#define BULLET_COLOR WHITE
#define BULLET_SPEED_RATIO 2
#define BULLET_SIZE_RATIO 20

// player
#define PLAYER_COLOR GREEN
#define PLAYER_SPEED_RATIO 3
#define PLAYER_SIZE_RATIO 12
#define SHOOT_INTERVAL 0.75f

// enemy
#define ENEMY_COLOR GREEN
#define ENEMY_SPEED_RATIO 5
#define ENEMY_SIZE_RATIO 15

// ui
#define FONT_SIZE 100
#define LARGE_FONT_SIZE 100 * FONT_SIZE
#define SCORE_TEXT_PADDING_X 120
#define SCORE_TEXT_PADDING_Y 0
#define SCORE_TEXT_COLOR GREEN
#define WON_TEXT_COLOR GREEN
#define LOST_TEXT_COLOR RED
#define PAUSED_TEXT_COLOR WHITE

// game
#define SCORE_INTERVAL 10
#define ENEMIES_COUNT_ROW 11
#define ENEMIES_COUNT_COL 4
#define ENEMIES_SHOOT_TIMER 2
#define ENEMY_SHOOT_CHANCE_PERCENTAGE 33

// audio
#define MUSIC_VOLUME 1.0f
#define SOUND_VOLUME 1.0f
