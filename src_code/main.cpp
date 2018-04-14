#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <random>

using namespace std;

MenuScene menu;
SettingsScene settings;
GameplayScene gameplay;
PauseScene pause;
HighscoresScene highscores;

TextureMgr* txrMgr;
FontMgr* fontMgr;
bool loadContentComplete;

int counter;

int main() 
{
	counter = 0;
	srand(time(NULL));
	txrMgr = TextureMgr::GetInstance();
	fontMgr = FontMgr::GetInstance();
	Engine::Start(1600, 900, "Rogue2125", &menu);
}