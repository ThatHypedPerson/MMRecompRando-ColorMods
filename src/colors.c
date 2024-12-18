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

// Wallet colors
// note: {prim, env}, i'm not sure if the env color is visible though
Color_RGB8 walletColors[3][2] = {
	{{200, 255, 100}, {0, 80, 0}},		// child wallet
	{{170, 170, 255}, {10, 10, 80}},	// adult wallet
	{{255, 105, 105}, {40, 10, 0}},		// giant wallet
};

// Clock UI colors
Color_RGB8 clockUninvertedColor = {0, 170, 100};
Color_RGB8 clockInvertedColor = {0, 155, 255};		// mmr inverted B?
Color_RGB8 clockDayColor = {255, 255, 155};
Color_RGB8 clockHourColor = {255, 255, 155};
Color_RGB8 clockSunColor = {255, 100, 110};
Color_RGB8 clockMoonColor = {255, 255, 55};
Color_RGB8 clockCenterStarColor = {255, 255, 110};
Color_RGB8 clockBorderColor = {255, 255, 255};
Color_RGB8 clockHourLinesColor = {130, 130, 130};
Color_RGB8 clockFinalHoursColor = {255, 255, 195};

// Map colors
Color_RGB8 mapColor = {};
Color_RGB8 mapPlayer = {};
Color_RGB8 mapEntrance = {};
