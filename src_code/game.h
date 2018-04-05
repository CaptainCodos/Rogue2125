
#pragma once

#include <AllMgrs.h>
#include "scenes/scene_menu.h"
#include "scenes/scene_settings.h"
#include "scenes/scene_gameplay.h"
#include "scenes/scene_pause.h"
#include "scenes/scene_highscores.h"

extern MenuScene menu;
extern SettingsScene settings;
extern GameplayScene gameplay;
extern PauseScene pause;
extern HighscoresScene highscores;

extern TextureMgr* txrMgr;
//extern SoundMgr* audioMgr;
extern FontMgr* fontMgr;
extern bool loadContentComplete;