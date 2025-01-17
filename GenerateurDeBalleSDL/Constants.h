#include <iostream>

#pragma once

// Param�tre de la fen�tre Windows
const std::string WINDOW_NAME = "Rebond Ball Generator";
const std::string PATH= "../RESSOURCES/Font/Roboto-Medium.ttf";

const int WINDOW_SIZE_X = 1600;
const int WINDOW_SIZE_Y = 900;

// Param�tre du jeu
const bool IS_RUNNING = true;
const bool IS_PAUSED = false;
const bool IS_FULL_WINDOW = false;
const int LIMIT_FPS = 60;
const int SPAWN_DELAY = 0;
const int LAST_SPAWN_TIME = 0;
const bool DARK_MODE = true;
const int MAX_BALL = 10000;