#include "global.h"

#include "modding.h"

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
// note: these are only visible on the file select screen for now due to patching over base recomp patches
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
Color_RGB8 mapColor = {255, 255, 255}; // note: there's actually slightly different map colors, but we ignore them
Color_RGB8 mapPlayerColor = {200, 255, 0};
Color_RGB8 mapEntranceColor = {200, 0, 0};

// Ocarina playback colors
// note: this is for the "textbox" that appears when you play a song
Color_RGB8 trebleClefColor = {255, 100, 0}; // unimplemented due to mod conflicts

RECOMP_EXPORT void colors_set_human_tunic(u8 r, u8 g, u8 b) {
	humanTunicColor.r = r;
	humanTunicColor.g = g;
	humanTunicColor.b = b;
}

RECOMP_EXPORT void colors_set_a_button(u8 r, u8 g, u8 b) {
	buttonAColor.r = r;
	buttonAColor.g = g;
	buttonAColor.b = b;
}

RECOMP_EXPORT void colors_set_b_button(u8 r, u8 g, u8 b) {
	buttonBColor.r = r;
	buttonBColor.g = g;
	buttonBColor.b = b;
}

RECOMP_EXPORT void colors_set_c_button(u8 r, u8 g, u8 b) {
	buttonCColor.r = r;
	buttonCColor.g = g;
	buttonCColor.b = b;
}

RECOMP_EXPORT void colors_set_start_button(u8 r, u8 g, u8 b) {
	buttonStartColor.r = r;
	buttonStartColor.g = g;
	buttonStartColor.b = b;
}

RECOMP_EXPORT void colors_set_heart(u8 r, u8 g, u8 b) {
	heartColor.r = r;
	heartColor.g = g;
	heartColor.b = b;
}

RECOMP_EXPORT void colors_set_heart_background(u8 r, u8 g, u8 b) {
	heartBackgroundColor.r = r;
	heartBackgroundColor.g = g;
	heartBackgroundColor.b = b;
}

RECOMP_EXPORT void colors_set_heart_dd(u8 r, u8 g, u8 b) {
	heartDDColor.r = r;
	heartDDColor.g = g;
	heartDDColor.b = b;
}

RECOMP_EXPORT void colors_set_heart_dd_background(u8 r, u8 g, u8 b) {
	heartDDBackgroundColor.r = r;
	heartDDBackgroundColor.g = g;
	heartDDBackgroundColor.b = b;
}

RECOMP_EXPORT void colors_set_magic(u8 r, u8 g, u8 b) {
	magicColor.r = r;
	magicColor.g = g;
	magicColor.b = b;
}

RECOMP_EXPORT void colors_set_magic_chateau(u8 r, u8 g, u8 b) {
	magicChateauColor.r = r;
	magicChateauColor.g = g;
	magicChateauColor.b = b;
}

RECOMP_EXPORT void colors_set_tatl_inner(u8 r, u8 g, u8 b) {
	tatlColorInner.r = r;
	tatlColorInner.g = g;
	tatlColorInner.b = b;
}

RECOMP_EXPORT void colors_set_tatl_outer(u8 r, u8 g, u8 b) {
	tatlColorOuter.r = r;
	tatlColorOuter.g = g;
	tatlColorOuter.b = b;
}

RECOMP_EXPORT void colors_set_pause_extra(u8 r, u8 g, u8 b) {
	pauseMenuExtraColor.r = r;
	pauseMenuExtraColor.g = g;
	pauseMenuExtraColor.b = b;
}

RECOMP_EXPORT void colors_set_pause_item(u8 r, u8 g, u8 b) {
	pauseMenuItemColor.r = r;
	pauseMenuItemColor.g = g;
	pauseMenuItemColor.b = b;
}

RECOMP_EXPORT void colors_set_pause_map(u8 r, u8 g, u8 b) {
	pauseMenuMapColor.r = r;
	pauseMenuMapColor.g = g;
	pauseMenuMapColor.b = b;
}

RECOMP_EXPORT void colors_set_pause_quest(u8 r, u8 g, u8 b) {
	pauseMenuQuestColor.r = r;
	pauseMenuQuestColor.g = g;
	pauseMenuQuestColor.b = b;
}

RECOMP_EXPORT void colors_set_pause_mask(u8 r, u8 g, u8 b) {
	pauseMenuMaskColor.r = r;
	pauseMenuMaskColor.g = g;
	pauseMenuMaskColor.b = b;
}

RECOMP_EXPORT void colors_set_file_window_color(u8 r, u8 g, u8 b) {
    fileWindowColor.r = r;
    fileWindowColor.g = g;
    fileWindowColor.b = b;
}

RECOMP_EXPORT void colors_set_file_skybox_color(u8 r, u8 g, u8 b) {
    fileSkyboxColor.r = r;
    fileSkyboxColor.g = g;
    fileSkyboxColor.b = b;
}

RECOMP_EXPORT void colors_set_clock_uninverted_color(u8 r, u8 g, u8 b) {
    clockUninvertedColor.r = r;
    clockUninvertedColor.g = g;
    clockUninvertedColor.b = b;
}

RECOMP_EXPORT void colors_set_clock_inverted_color(u8 r, u8 g, u8 b) {
    clockInvertedColor.r = r;
    clockInvertedColor.g = g;
    clockInvertedColor.b = b;
}

RECOMP_EXPORT void colors_set_clock_day_color(u8 r, u8 g, u8 b) {
    clockDayColor.r = r;
    clockDayColor.g = g;
    clockDayColor.b = b;
}

RECOMP_EXPORT void colors_set_clock_hour_color(u8 r, u8 g, u8 b) {
    clockHourColor.r = r;
    clockHourColor.g = g;
    clockHourColor.b = b;
}

RECOMP_EXPORT void colors_set_clock_sun_color(u8 r, u8 g, u8 b) {
    clockSunColor.r = r;
    clockSunColor.g = g;
    clockSunColor.b = b;
}

RECOMP_EXPORT void colors_set_clock_moon_color(u8 r, u8 g, u8 b) {
    clockMoonColor.r = r;
    clockMoonColor.g = g;
    clockMoonColor.b = b;
}

RECOMP_EXPORT void colors_set_clock_center_star_color(u8 r, u8 g, u8 b) {
    clockCenterStarColor.r = r;
    clockCenterStarColor.g = g;
    clockCenterStarColor.b = b;
}

RECOMP_EXPORT void colors_set_clock_border_color(u8 r, u8 g, u8 b) {
    clockBorderColor.r = r;
    clockBorderColor.g = g;
    clockBorderColor.b = b;
}

RECOMP_EXPORT void colors_set_clock_hour_lines_color(u8 r, u8 g, u8 b) {
    clockHourLinesColor.r = r;
    clockHourLinesColor.g = g;
    clockHourLinesColor.b = b;
}

RECOMP_EXPORT void colors_set_clock_final_hours_color(u8 r, u8 g, u8 b) {
    clockFinalHoursColor.r = r;
    clockFinalHoursColor.g = g;
    clockFinalHoursColor.b = b;
}

RECOMP_EXPORT void colors_set_map_color(u8 r, u8 g, u8 b) {
    mapColor.r = r;
    mapColor.g = g;
    mapColor.b = b;
}

RECOMP_EXPORT void colors_set_map_player_color(u8 r, u8 g, u8 b) {
    mapPlayerColor.r = r;
    mapPlayerColor.g = g;
    mapPlayerColor.b = b;
}

RECOMP_EXPORT void colors_set_map_entrance_color(u8 r, u8 g, u8 b) {
    mapEntranceColor.r = r;
    mapEntranceColor.g = g;
    mapEntranceColor.b = b;
}