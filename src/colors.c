#include "global.h"

// Player transformation colors
Color_RGB8 humanTunicColor = {30, 105, 27};

// Button Colors
Color_RGB8 buttonAColor = {100, 200, 255};
Color_RGB8 buttonBColor = {100, 255, 120};
Color_RGB8 buttonCColor = {255, 240, 0};
Color_RGB8 buttonStartColor = {255, 130, 60};
bool matchButtonColors = false; // match all instances of these button colors (i.e. ocarina notes)

// Health Colors
// note: hearts are handled in odd ways, unsure if anything would break though
Color_RGB8 heartColor = {255, 70, 50};
Color_RGB8 heartBackgroundColor = {50, 40, 60};
Color_RGB8 heartDDColor = {200, 0, 0};
Color_RGB8 heartDDBackgroundColor = {255, 255, 255};

// Magic Colors
Color_RGB8 magicColor = {0, 200, 0};
Color_RGB8 magicChateauColor = {128, 128, 200};

// Tatl Colors
// note: there are different colors for every Tatl interaction, we set them all to be the same though
Color_RGB8 tatlColorInner = {255, 255, 230};
Color_RGB8 tatlColorOuter = {220, 160, 80};

// Pause Colors
// Color_RGB8 pauseMenuColor = {180, 180, 120};
Color_RGB8 pauseMenuExtraColor = {150, 140, 90};
// note: different colors for each screen?
Color_RGB8 pauseMenuItemColor = {180, 180, 120};
Color_RGB8 pauseMenuMapColor = {180, 180, 120};
Color_RGB8 pauseMenuQuestColor = {180, 180, 120};
Color_RGB8 pauseMenuMaskColor = {180, 180, 120};
// TODO: add cursor colors

// File select colors
// note: the skybox texture is colored, therefore there is no default so we'll only change it if needed
Color_RGB8 fileWindowColor = {100, 150, 255};
Color_RGB8 fileSkyboxColor = {255, 255, 255};
bool recolorFileSkybox = false;