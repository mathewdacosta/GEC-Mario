#pragma once

// Screen dimensions
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 416

// Character movement characteristics
const float GRAVITY = 220.0f;
const float JUMP_FORCE_DECREMENT = 600.0f;
const float INITIAL_JUMP_FORCE = 300.0f;

const float MARIO_MOVE_SPEED = 96.0f;
const float LUIGI_MOVE_SPEED = 112.0f;

// Map properties
const int TILE_HEIGHT = 32;
const int TILE_WIDTH = 32;
const int MAP_HEIGHT = 13;
const int MAP_WIDTH = 16;

// Screen shake effect parameters
const float SCREEN_SHAKE_DURATION = 0.3f;

// Enemy parameters
const float KOOPA_INJURY_TIME = 3.5f;
const float KOOPA_INITIAL_JUMP_FORCE = 180.0f;
const float KOOPA_SPEED = 96.0f;
