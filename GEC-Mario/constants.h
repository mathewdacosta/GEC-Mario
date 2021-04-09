#pragma once

#include "Common.h"

// Screen dimensions
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 416

// Audio mixer settings
const int MIXER_FREQUENCY = 44100;
const int MIXER_OUTPUT_CHANNELS = 2;
const int MIXER_CHUNK_SIZE = 2048;
const int MIXER_CHANNELS = 16;

// Character movement characteristics
const float GRAVITY = 640.0f;
const float INITIAL_JUMP_FORCE = 330.0f;

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

// Level 1 parameters
const Vector2D LEVEL_1_SPAWNER_POSITION_0 = Vector2D(70, 20);
const Vector2D LEVEL_1_SPAWNER_POSITION_1 = Vector2D(410, 20);
const float LEVEL_1_SPAWNER_DELAY = 3.0f;
