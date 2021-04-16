#pragma once

#include "Common.h"
#include "DebugConstants.h"

// Screen dimensions
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 416

// Audio mixer settings
const int MIXER_FREQUENCY = 44100;
const int MIXER_OUTPUT_CHANNELS = 2;
const int MIXER_CHUNK_SIZE = 2048;
const int MIXER_CHANNELS = 16;

// Physics
const float GRAVITY = 1130.0f;

// Player parameters
const float MARIO_WIDTH = 32;
const float MARIO_HEIGHT = 42;
const float LUIGI_WIDTH = 32;
const float LUIGI_HEIGHT = 42;

// Player movement parameters
const float INITIAL_JUMP_FORCE = 460.0f;
const float MARIO_MOVE_SPEED = 136.0f;
const float LUIGI_MOVE_SPEED = 152.0f;

// Enemy parameters
const int KOOPA_WIDTH = 32;
const int KOOPA_HEIGHT = 30;
const float KOOPA_INJURY_TIME = 3.8f;
const float KOOPA_INITIAL_JUMP_FORCE = 280.0f;
const float KOOPA_SPEED = 96.0f;
const int KOOPA_KILL_SCORE = 200;

// Map properties
const int TILE_HEIGHT = 32;
const int TILE_WIDTH = 32;
const int MAP_HEIGHT = 13;
const int MAP_WIDTH = 16;

// Screen shake effect parameters
const float SCREEN_SHAKE_DURATION = 0.35f;

// Level 1 parameters
const Vector2D LEVEL_1_SPAWNER_POSITION_0 = Vector2D(70, 20);
const Vector2D LEVEL_1_SPAWNER_POSITION_1 = Vector2D(410, 20);
const float LEVEL_1_SPAWNER_DELAY = 2.8f;
