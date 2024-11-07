#include "modding.h"
#include "global.h"

#include "color.h"

// vanilla: 180, 180, 120
Color_RGB8 pauseMainColors[4] = {
    {120, 180, 120},	// green
    {180, 120, 120},	// red
    {120, 120, 180},	// blue
    {180, 60, 180},		// purple
};

// vanilla: 150, 140, 90
Color_RGB8 pauseExtraColors[4] = {
    {90, 150, 90},		// green
    {150, 90, 90},		// red
    {90, 90, 150},		// blue
    {150, 90, 150},		// purple
};

#define IS_PAUSE_STATE_GAMEOVER \
    ((pauseCtx->state >= PAUSE_STATE_GAMEOVER_0) && (pauseCtx->state <= PAUSE_STATE_GAMEOVER_10))

typedef enum {
    /* 0x00 */ PAUSE_STATE_OFF,
    /* 0x01 */ PAUSE_STATE_OPENING_0,
    /* 0x02 */ PAUSE_STATE_OPENING_1,
    /* 0x03 */ PAUSE_STATE_OPENING_2,
    /* 0x04 */ PAUSE_STATE_OPENING_3,
    /* 0x05 */ PAUSE_STATE_OPENING_4,
    /* 0x06 */ PAUSE_STATE_MAIN, // Pause menu ready for player inputs.
    /* 0x07 */ PAUSE_STATE_SAVEPROMPT,
    /* 0x08 */ PAUSE_STATE_GAMEOVER_0,
    /* 0x09 */ PAUSE_STATE_GAMEOVER_1,
    /* 0x0A */ PAUSE_STATE_GAMEOVER_2,
    /* 0x0B */ PAUSE_STATE_GAMEOVER_3,
    /* 0x0C */ PAUSE_STATE_GAMEOVER_4,
    /* 0x0D */ PAUSE_STATE_GAMEOVER_5,
    /* 0x0E */ PAUSE_STATE_GAMEOVER_SAVE_PROMPT,
    /* 0x0F */ PAUSE_STATE_GAMEOVER_7,
    /* 0x10 */ PAUSE_STATE_GAMEOVER_8,
    /* 0x11 */ PAUSE_STATE_GAMEOVER_CONTINUE_PROMPT,
    /* 0x12 */ PAUSE_STATE_GAMEOVER_10,
    /* 0x13 */ PAUSE_STATE_OWLWARP_0,
    /* 0x14 */ PAUSE_STATE_OWLWARP_1,
    /* 0x15 */ PAUSE_STATE_OWLWARP_2,
    /* 0x16 */ PAUSE_STATE_OWLWARP_3,
    /* 0x17 */ PAUSE_STATE_OWLWARP_SELECT, // Selecting the destination
    /* 0x18 */ PAUSE_STATE_OWLWARP_CONFIRM, // Confirming the choice given
    /* 0x19 */ PAUSE_STATE_OWLWARP_6,
    /* 0x1A */ PAUSE_STATE_UNPAUSE_SETUP, // Unpause
    /* 0x1B */ PAUSE_STATE_UNPAUSE_CLOSE
} PauseState;

s16 sGameOverPrimR = 0;
s16 sGameOverPrimG = 0;
s16 sGameOverPrimB = 0;
s16 sGameOverPrimAlpha = 255;
// s16 sCursorPrimR = 0;
// s16 sCursorPrimG = 0;
// s16 sCursorPrimB = 0;
// s16 sCursorEnvR = 0;
// s16 sCursorEnvG = 0;
// s16 sCursorEnvB = 0;
extern s16 sCursorPrimR;
extern s16 sCursorPrimG;
extern s16 sCursorPrimB;
extern s16 sCursorEnvR;
extern s16 sCursorEnvG;
extern s16 sCursorEnvB;
s16 sGameOverEnvR = 255;
s16 sGameOverEnvG = 0;
s16 sGameOverEnvB = 0;
// TODO: add cursor colors
s16 sCursorPrimColorTarget[][3] = {
    { 255, 255, 255 }, { 255, 255, 255 }, { 255, 255, 0 }, { 255, 255, 0 }, { 100, 150, 255 }, { 100, 255, 255 },
};
s16 sCursorEnvColorTarget[][3] = {
    { 0, 0, 0 }, { 170, 170, 170 }, { 0, 0, 0 }, { 255, 160, 0 }, { 0, 0, 100 }, { 0, 150, 255 },
};

typedef enum {
    /* 0 */ PAUSE_ITEM,
    /* 1 */ PAUSE_MAP,
    /* 2 */ PAUSE_QUEST,
    /* 3 */ PAUSE_MASK,
    /* 4 */ PAUSE_WORLD_MAP
} PauseMenuPage;

f32 sPauseMenuVerticalOffset = 0.0f;
f32 D_8082B90C = 0.0f;
f32 sPauseCursorLeftMoveOffsetX = 40.0f;
f32 sPauseCursorRightMoveOffsetX = -40.0f;

extern s16 sPauseCursorLeftX;
extern s16 sPauseCursorRightX;

s16 D_8082B920 = 10;

s16 sPauseZRCursorColorTimerInits[] = { 20, 4, 20, 10 };

extern TexturePtr sItemPageBgTextures[];
extern TexturePtr sMapPageBgTextures[];
extern TexturePtr sQuestPageBgTextures[];
extern TexturePtr sMaskPageBgTextures[];
extern s16 sInDungeonScene;

typedef enum {
    /* 0x00 */ PAUSE_MAIN_STATE_IDLE, // Await input for the next action
    /* 0x01 */ PAUSE_MAIN_STATE_SWITCHING_PAGE,
    /* 0x02 */ PAUSE_MAIN_STATE_SONG_PLAYBACK,
    /* 0x03 */ PAUSE_MAIN_STATE_EQUIP_ITEM,
    /* 0x04 */ PAUSE_MAIN_STATE_SONG_PROMPT_INIT,
    /* 0x05 */ PAUSE_MAIN_STATE_SONG_PROMPT,
    /* 0x06 */ PAUSE_MAIN_STATE_SONG_PROMPT_DONE,
    /* 0x07 */ PAUSE_MAIN_STATE_SONG_PROMPT_UNUSED,
    /* 0x08 */ PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG, // Await input but the cursor is on a song
    /* 0x09 */ PAUSE_MAIN_STATE_SONG_PLAYBACK_INIT,
    /* 0x0F */ PAUSE_MAIN_STATE_EQUIP_MASK = 0xF,
    /* 0x10 */ PAUSE_MAIN_STATE_BOMBERS_NOTEBOOK_OPEN,
    /* 0x11 */ PAUSE_MAIN_STATE_UNK
} PauseMainState;

typedef enum {
    /* 0x00 */ PAUSE_SAVEPROMPT_STATE_APPEARING,
    /* 0x01 */ PAUSE_SAVEPROMPT_STATE_1,
    /* 0x02 */ PAUSE_SAVEPROMPT_STATE_RETURN_TO_MENU,
    /* 0x03 */ PAUSE_SAVEPROMPT_STATE_3,
    /* 0x04 */ PAUSE_SAVEPROMPT_STATE_4,
    /* 0x05 */ PAUSE_SAVEPROMPT_STATE_5,
    /* 0x06 */ PAUSE_SAVEPROMPT_STATE_6,
    /* 0x07 */ PAUSE_SAVEPROMPT_STATE_7
} PauseSavePromptState;

Gfx* KaleidoScope_DrawPageSections(Gfx* gfx, Vtx* vertices, TexturePtr* textures);
void KaleidoScope_DrawItemSelect(PlayState* play);
void KaleidoScope_DrawDungeonMap(PlayState* play);
void KaleidoScope_DrawWorldMap(PlayState* play);
void KaleidoScope_DrawQuestStatus(PlayState* play);
void KaleidoScope_DrawMaskSelect(PlayState* play);

RECOMP_PATCH void KaleidoScope_DrawPages(PlayState* play, GraphicsContext* gfxCtx) {
    static s16 sCursorColorTimer = 10;
    static s16 sCursorColorTargetIndex = 0;
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 stepR;
    s16 stepG;
    s16 stepB;

    Color_RGB8 pauseMainColor = pauseMainColors[COLOR];

    OPEN_DISPS(gfxCtx);

    if (!IS_PAUSE_STATE_GAMEOVER) {
        if (pauseCtx->state != PAUSE_STATE_SAVEPROMPT) {

            stepR =
                ABS_ALT(sCursorPrimR - sCursorPrimColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][0]) /
                sCursorColorTimer;
            stepG =
                ABS_ALT(sCursorPrimG - sCursorPrimColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][1]) /
                sCursorColorTimer;
            stepB =
                ABS_ALT(sCursorPrimB - sCursorPrimColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][2]) /
                sCursorColorTimer;

            if (sCursorPrimR >= sCursorPrimColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][0]) {
                sCursorPrimR -= stepR;
            } else {
                sCursorPrimR += stepR;
            }

            if (sCursorPrimG >= sCursorPrimColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][1]) {
                sCursorPrimG -= stepG;
            } else {
                sCursorPrimG += stepG;
            }

            if (sCursorPrimB >= sCursorPrimColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][2]) {
                sCursorPrimB -= stepB;
            } else {
                sCursorPrimB += stepB;
            }

            stepR =
                ABS_ALT(sCursorEnvR - sCursorEnvColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][0]) /
                sCursorColorTimer;
            stepG =
                ABS_ALT(sCursorEnvG - sCursorEnvColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][1]) /
                sCursorColorTimer;
            stepB =
                ABS_ALT(sCursorEnvB - sCursorEnvColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][2]) /
                sCursorColorTimer;

            if (sCursorEnvR >= sCursorEnvColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][0]) {
                sCursorEnvR -= stepR;
            } else {
                sCursorEnvR += stepR;
            }

            if (sCursorEnvG >= sCursorEnvColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][1]) {
                sCursorEnvG -= stepG;
            } else {
                sCursorEnvG += stepG;
            }

            if (sCursorEnvB >= sCursorEnvColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][2]) {
                sCursorEnvB -= stepB;
            } else {
                sCursorEnvB += stepB;
            }

            sCursorColorTimer--;
            if (sCursorColorTimer == 0) {
                sCursorPrimR = sCursorPrimColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][0];
                sCursorPrimG = sCursorPrimColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][1];
                sCursorPrimB = sCursorPrimColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][2];
                sCursorEnvR = sCursorEnvColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][0];
                sCursorEnvG = sCursorEnvColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][1];
                sCursorEnvB = sCursorEnvColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][2];
                sCursorColorTargetIndex ^= 1;
                sCursorColorTimer = 10;
            }
        }

        if ((pauseCtx->pageIndex != PAUSE_ITEM) && (pauseCtx->pageIndex != PAUSE_QUEST)) {
            gDPPipeSync(POLY_OPA_DISP++);

            gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0,
                              TEXEL0, 0, SHADE, 0);

            // gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, pauseMainColor.r, pauseMainColor.g, pauseMainColor.b, 255);


            Matrix_RotateYF(0.0f, MTXMODE_NEW);
            Matrix_Translate(0.0f, sPauseMenuVerticalOffset / 100.0f, -93.0f, MTXMODE_APPLY);
            Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
            Matrix_RotateXFApply(-pauseCtx->itemPageRoll / 100.0f);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->itemPageVtx, sItemPageBgTextures);

            KaleidoScope_DrawItemSelect(play);
        }

        if ((pauseCtx->pageIndex != PAUSE_MAP) && (pauseCtx->pageIndex != PAUSE_MASK)) {
            gDPPipeSync(POLY_OPA_DISP++);

            gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0,
                              TEXEL0, 0, SHADE, 0);

            // gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, pauseMainColor.r, pauseMainColor.g, pauseMainColor.b, 255);


            Matrix_RotateYF(-1.57f, MTXMODE_NEW);
            Matrix_Translate(0.0f, sPauseMenuVerticalOffset / 100.0f, -93.0f, MTXMODE_APPLY);
            Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
            Matrix_RotateXFApply(-pauseCtx->mapPageRoll / 100.0f);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->mapPageVtx, sMapPageBgTextures);

            if (sInDungeonScene) {
                KaleidoScope_DrawDungeonMap(play);
                Gfx_SetupDL42_Opa(gfxCtx);
                gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                func_801091F0(play);
            } else {
                KaleidoScope_DrawWorldMap(play);
            }
        }

        if ((pauseCtx->pageIndex != PAUSE_QUEST) && (pauseCtx->pageIndex != PAUSE_ITEM)) {
            gDPPipeSync(POLY_OPA_DISP++);

            gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_BILERP);

            gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0,
                              TEXEL0, 0, SHADE, 0);

            // gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, pauseMainColor.r, pauseMainColor.g, pauseMainColor.b, 255);


            Matrix_RotateYF(-3.14f, MTXMODE_NEW);
            Matrix_Translate(0.0f, sPauseMenuVerticalOffset / 100.0f, -93.0f, MTXMODE_APPLY);
            Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
            Matrix_RotateXFApply(-pauseCtx->questPageRoll / 100.0f);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->questPageVtx, sQuestPageBgTextures);

            KaleidoScope_DrawQuestStatus(play);
        }

        if ((pauseCtx->pageIndex != PAUSE_MASK) && (pauseCtx->pageIndex != PAUSE_MAP)) {
            gDPPipeSync(POLY_OPA_DISP++);

            gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_BILERP);

            gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0,
                              TEXEL0, 0, SHADE, 0);

            // gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, pauseMainColor.r, pauseMainColor.g, pauseMainColor.b, 255);


            Matrix_RotateYF(1.57f, MTXMODE_NEW);
            Matrix_Translate(0.0f, sPauseMenuVerticalOffset / 100.0f, -93.0f, MTXMODE_APPLY);
            Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
            Matrix_RotateXFApply(-pauseCtx->maskPageRoll / 100.0f);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->maskPageVtx, sMaskPageBgTextures);

            KaleidoScope_DrawMaskSelect(play);
        }

        switch (pauseCtx->pageIndex) {
            case PAUSE_ITEM:
                if (pauseCtx->mainState <= PAUSE_MAIN_STATE_EQUIP_MASK) {
                    gDPPipeSync(POLY_OPA_DISP++);

                    gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0,
                                      PRIMITIVE, 0, TEXEL0, 0, SHADE, 0);

                    // gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, pauseMainColor.r, pauseMainColor.g, pauseMainColor.b, 255);


                    Matrix_RotateYF(0.0f, MTXMODE_NEW);
                    Matrix_Translate(0.0f, sPauseMenuVerticalOffset / 100.0f, -93.0f, MTXMODE_APPLY);
                    Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
                    Matrix_RotateXFApply(-pauseCtx->itemPageRoll / 100.0f);

                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    POLY_OPA_DISP =
                        KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->itemPageVtx, sItemPageBgTextures);

                    KaleidoScope_DrawItemSelect(play);
                }
                break;

            case PAUSE_MAP:
                gDPPipeSync(POLY_OPA_DISP++);

                gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE,
                                  0, TEXEL0, 0, SHADE, 0);

                // gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, pauseMainColor.r, pauseMainColor.g, pauseMainColor.b, 255);


                Matrix_RotateYF(-1.57f, MTXMODE_NEW);
                Matrix_Translate(0.0f, sPauseMenuVerticalOffset / 100.0f, -93.0f, MTXMODE_APPLY);
                Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
                Matrix_RotateXFApply(-pauseCtx->mapPageRoll / 100.0f);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->mapPageVtx, sMapPageBgTextures);

                if (sInDungeonScene) {
                    KaleidoScope_DrawDungeonMap(play);
                    Gfx_SetupDL42_Opa(gfxCtx);

                    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

                    func_801091F0(play);
                } else {
                    Matrix_RotateYF(R_PAUSE_WORLD_MAP_YAW / 1000.0f, MTXMODE_NEW);

                    if ((pauseCtx->state == PAUSE_STATE_OPENING_3) || (pauseCtx->state == PAUSE_STATE_OWLWARP_3) ||
                        (pauseCtx->state >= PAUSE_STATE_OWLWARP_6) ||
                        ((pauseCtx->state == PAUSE_STATE_SAVEPROMPT) &&
                         ((pauseCtx->savePromptState == PAUSE_SAVEPROMPT_STATE_3) ||
                          (pauseCtx->savePromptState == PAUSE_SAVEPROMPT_STATE_7)))) {
                        Matrix_Translate(0.0f, (R_PAUSE_WORLD_MAP_Y_OFFSET - 8000) / 100.0f,
                                         R_PAUSE_WORLD_MAP_DEPTH / 100.0f, MTXMODE_APPLY);
                    } else {
                        Matrix_Translate(0.0f, R_PAUSE_WORLD_MAP_Y_OFFSET / 100.0f, R_PAUSE_WORLD_MAP_DEPTH / 100.0f,
                                         MTXMODE_APPLY);
                    }

                    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
                    Matrix_RotateXFApply(-pauseCtx->mapPageRoll / 100.0f);

                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    KaleidoScope_DrawWorldMap(play);
                }
                break;

            case PAUSE_QUEST:
                gDPPipeSync(POLY_OPA_DISP++);

                gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE,
                                  0, TEXEL0, 0, SHADE, 0);

                // gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, pauseMainColor.r, pauseMainColor.g, pauseMainColor.b, 255);


                gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_BILERP);

                Matrix_RotateYF(-3.14f, MTXMODE_NEW);
                Matrix_Translate(0.0f, sPauseMenuVerticalOffset / 100.0f, -93.0f, MTXMODE_APPLY);
                Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
                Matrix_RotateXFApply(-pauseCtx->questPageRoll / 100.0f);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                POLY_OPA_DISP =
                    KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->questPageVtx, sQuestPageBgTextures);

                KaleidoScope_DrawQuestStatus(play);
                break;

            case PAUSE_MASK:
                gDPPipeSync(POLY_OPA_DISP++);

                gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE,
                                  0, TEXEL0, 0, SHADE, 0);

                // gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, pauseMainColor.r, pauseMainColor.g, pauseMainColor.b, 255);


                Matrix_RotateYF(1.57f, MTXMODE_NEW);
                Matrix_Translate(0.0f, sPauseMenuVerticalOffset / 100.0f, -93.0f, MTXMODE_APPLY);
                Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
                Matrix_RotateXFApply(-pauseCtx->maskPageRoll / 100.0f);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                POLY_OPA_DISP =
                    KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->maskPageVtx, sMaskPageBgTextures);

                KaleidoScope_DrawMaskSelect(play);
                break;
        }
    }

    CLOSE_DISPS(gfxCtx);
}

extern TexturePtr D_8082B998[];
extern TexturePtr D_8082B9A8[];

#define PAUSE_CURSOR_PAGE_LEFT 10
#define PAUSE_CURSOR_PAGE_RIGHT 11

extern Gfx gItemNamePanelDL[];
extern Gfx gZButtonIconDL[];
extern Gfx gRButtonIconDL[];
extern Gfx gAButtonIconDL[];
extern Gfx gCButtonIconsDL[];

extern u64 gPauseToDecideENGTex[];
extern u64 gPauseToEquipENGTex[];
extern u64 gPauseToViewNotebookENGTex[];
extern u64 gPauseToPlayMelodyENGTex[];

#define PAUSE_NAME_COLOR_SET_WHITE 0
#define PAUSE_NAME_COLOR_SET_GREY 1
#define PAUSE_ITEM_NONE 999

RECOMP_PATCH void KaleidoScope_DrawInfoPanel(PlayState* play) {
    static s16 sPauseZRCursorColorTargets[][4] = {
        { 180, 210, 255, 220 },
        { 100, 100, 150, 220 },
    };
    static s16 sPauseZRCursorColorTimer = 20;
    static s16 sPauseZRCursorColorIndex = 0;
    static s16 sPauseZRCursorRed;
    static s16 sPauseZRCursorGreen;
    static s16 sPauseZRCursorBlue;
    static s16 sPauseZRCursorAlpha;
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 stepR;
    s16 stepG;
    s16 stepB;
    s16 stepA;
    s16 y;
    s16 i;
    s16 j;

    Color_RGB8 pauseExtraColor = pauseExtraColors[COLOR];

    OPEN_DISPS(play->state.gfxCtx);

    stepR =
        ABS_ALT(sPauseZRCursorRed - sPauseZRCursorColorTargets[sPauseZRCursorColorIndex][0]) / sPauseZRCursorColorTimer;
    stepG = ABS_ALT(sPauseZRCursorGreen - sPauseZRCursorColorTargets[sPauseZRCursorColorIndex][1]) /
            sPauseZRCursorColorTimer;
    stepB = ABS_ALT(sPauseZRCursorBlue - sPauseZRCursorColorTargets[sPauseZRCursorColorIndex][2]) /
            sPauseZRCursorColorTimer;
    stepA = ABS_ALT(sPauseZRCursorAlpha - sPauseZRCursorColorTargets[sPauseZRCursorColorIndex][3]) /
            sPauseZRCursorColorTimer;

    if (sPauseZRCursorRed >= sPauseZRCursorColorTargets[sPauseZRCursorColorIndex][0]) {
        sPauseZRCursorRed -= stepR;
    } else {
        sPauseZRCursorRed += stepR;
    }

    if (sPauseZRCursorGreen >= sPauseZRCursorColorTargets[sPauseZRCursorColorIndex][1]) {
        sPauseZRCursorGreen -= stepG;
    } else {
        sPauseZRCursorGreen += stepG;
    }

    if (sPauseZRCursorBlue >= sPauseZRCursorColorTargets[sPauseZRCursorColorIndex][2]) {
        sPauseZRCursorBlue -= stepB;
    } else {
        sPauseZRCursorBlue += stepB;
    }

    if (sPauseZRCursorAlpha >= sPauseZRCursorColorTargets[sPauseZRCursorColorIndex][3]) {
        sPauseZRCursorAlpha -= stepA;
    } else {
        sPauseZRCursorAlpha += stepA;
    }

    sPauseZRCursorColorTimer--;
    if (sPauseZRCursorColorTimer == 0) {
        sPauseZRCursorRed = sPauseZRCursorColorTargets[sPauseZRCursorColorIndex][0];
        sPauseZRCursorGreen = sPauseZRCursorColorTargets[sPauseZRCursorColorIndex][1];
        sPauseZRCursorBlue = sPauseZRCursorColorTargets[sPauseZRCursorColorIndex][2];
        sPauseZRCursorAlpha = sPauseZRCursorColorTargets[sPauseZRCursorColorIndex][3];
        sPauseZRCursorColorTimer = sPauseZRCursorColorTimerInits[0];
        sPauseZRCursorColorIndex ^= 1;
    }

    y = pauseCtx->infoPanelOffsetY - 76;
    for (j = 0, i = 0; i < 7; i++, j += 4) {
        pauseCtx->infoPanelVtx[j + 0].v.ob[0] = pauseCtx->infoPanelVtx[j + 2].v.ob[0] = -72;

        pauseCtx->infoPanelVtx[j + 1].v.ob[0] = pauseCtx->infoPanelVtx[j + 3].v.ob[0] = 0;

        pauseCtx->infoPanelVtx[j + 0].v.ob[1] = pauseCtx->infoPanelVtx[j + 1].v.ob[1] = y;

        pauseCtx->infoPanelVtx[j + 2].v.ob[1] = pauseCtx->infoPanelVtx[j + 3].v.ob[1] = y - 24;

        pauseCtx->infoPanelVtx[j + 0].v.ob[2] = pauseCtx->infoPanelVtx[j + 1].v.ob[2] =
            pauseCtx->infoPanelVtx[j + 2].v.ob[2] = pauseCtx->infoPanelVtx[j + 3].v.ob[2] = 0;

        pauseCtx->infoPanelVtx[j + 0].v.flag = pauseCtx->infoPanelVtx[j + 1].v.flag =
            pauseCtx->infoPanelVtx[j + 2].v.flag = pauseCtx->infoPanelVtx[j + 3].v.flag = 0;

        pauseCtx->infoPanelVtx[j + 0].v.tc[0] = pauseCtx->infoPanelVtx[j + 0].v.tc[1] =
            pauseCtx->infoPanelVtx[j + 1].v.tc[1] = pauseCtx->infoPanelVtx[j + 2].v.tc[0] = 0;

        pauseCtx->infoPanelVtx[j + 1].v.tc[0] = pauseCtx->infoPanelVtx[j + 3].v.tc[0] = 72 * (1 << 5);

        pauseCtx->infoPanelVtx[j + 2].v.tc[1] = pauseCtx->infoPanelVtx[j + 3].v.tc[1] = 24 * (1 << 5);

        pauseCtx->infoPanelVtx[j + 0].v.cn[0] = pauseCtx->infoPanelVtx[j + 2].v.cn[0] =
            pauseCtx->infoPanelVtx[j + 0].v.cn[1] = pauseCtx->infoPanelVtx[j + 2].v.cn[1] =
                pauseCtx->infoPanelVtx[j + 0].v.cn[2] = pauseCtx->infoPanelVtx[j + 2].v.cn[2] =
                    pauseCtx->infoPanelVtx[j + 1].v.cn[0] = pauseCtx->infoPanelVtx[j + 3].v.cn[0] =
                        pauseCtx->infoPanelVtx[j + 1].v.cn[1] = pauseCtx->infoPanelVtx[j + 3].v.cn[1] =
                            pauseCtx->infoPanelVtx[j + 1].v.cn[2] = pauseCtx->infoPanelVtx[j + 3].v.cn[2] = 200;

        pauseCtx->infoPanelVtx[j + 0].v.cn[3] = pauseCtx->infoPanelVtx[j + 2].v.cn[3] =
            pauseCtx->infoPanelVtx[j + 1].v.cn[3] = pauseCtx->infoPanelVtx[j + 3].v.cn[3] = pauseCtx->alpha;
    }

    pauseCtx->infoPanelVtx[4].v.ob[0] = pauseCtx->infoPanelVtx[6].v.ob[0] = pauseCtx->infoPanelVtx[0].v.ob[0] + 72;

    pauseCtx->infoPanelVtx[5].v.ob[0] = pauseCtx->infoPanelVtx[7].v.ob[0] = pauseCtx->infoPanelVtx[4].v.ob[0] + 72;

    if ((pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) && (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE)) {
        pauseCtx->infoPanelVtx[8].v.ob[0] = pauseCtx->infoPanelVtx[10].v.ob[0] = sPauseCursorLeftX;

        pauseCtx->infoPanelVtx[9].v.ob[0] = pauseCtx->infoPanelVtx[11].v.ob[0] = pauseCtx->infoPanelVtx[8].v.ob[0] + 24;

        pauseCtx->infoPanelVtx[8].v.ob[1] = pauseCtx->infoPanelVtx[9].v.ob[1] = D_8082B920;

        pauseCtx->infoPanelVtx[10].v.ob[1] = pauseCtx->infoPanelVtx[11].v.ob[1] =
            pauseCtx->infoPanelVtx[8].v.ob[1] - 32;
    } else {
        pauseCtx->infoPanelVtx[8].v.ob[0] = pauseCtx->infoPanelVtx[10].v.ob[0] = sPauseCursorLeftX + 3;

        pauseCtx->infoPanelVtx[9].v.ob[0] = pauseCtx->infoPanelVtx[11].v.ob[0] = pauseCtx->infoPanelVtx[8].v.ob[0] + 18;

        pauseCtx->infoPanelVtx[8].v.ob[1] = pauseCtx->infoPanelVtx[9].v.ob[1] = D_8082B920 - 3;

        pauseCtx->infoPanelVtx[10].v.ob[1] = pauseCtx->infoPanelVtx[11].v.ob[1] =
            pauseCtx->infoPanelVtx[8].v.ob[1] - 26;
    }

    if ((pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_RIGHT) && (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE)) {
        pauseCtx->infoPanelVtx[12].v.ob[0] = pauseCtx->infoPanelVtx[14].v.ob[0] = sPauseCursorRightX;

        pauseCtx->infoPanelVtx[13].v.ob[0] = pauseCtx->infoPanelVtx[15].v.ob[0] =
            pauseCtx->infoPanelVtx[12].v.ob[0] + 24;

        pauseCtx->infoPanelVtx[12].v.ob[1] = pauseCtx->infoPanelVtx[13].v.ob[1] = D_8082B920;

        pauseCtx->infoPanelVtx[14].v.ob[1] = pauseCtx->infoPanelVtx[15].v.ob[1] =
            pauseCtx->infoPanelVtx[12].v.ob[1] - 32;
    } else {
        pauseCtx->infoPanelVtx[12].v.ob[0] = pauseCtx->infoPanelVtx[14].v.ob[0] = sPauseCursorRightX + 3;

        pauseCtx->infoPanelVtx[13].v.ob[0] = pauseCtx->infoPanelVtx[15].v.ob[0] =
            pauseCtx->infoPanelVtx[12].v.ob[0] + 18;

        pauseCtx->infoPanelVtx[12].v.ob[1] = pauseCtx->infoPanelVtx[13].v.ob[1] = D_8082B920 - 3;

        pauseCtx->infoPanelVtx[14].v.ob[1] = pauseCtx->infoPanelVtx[15].v.ob[1] =
            pauseCtx->infoPanelVtx[12].v.ob[1] - 26;
    }

    pauseCtx->infoPanelVtx[9].v.tc[0] = pauseCtx->infoPanelVtx[11].v.tc[0] = pauseCtx->infoPanelVtx[13].v.tc[0] =
        pauseCtx->infoPanelVtx[15].v.tc[0] = 24 * (1 << 5);

    pauseCtx->infoPanelVtx[10].v.tc[1] = pauseCtx->infoPanelVtx[11].v.tc[1] = pauseCtx->infoPanelVtx[14].v.tc[1] =
        pauseCtx->infoPanelVtx[15].v.tc[1] = 32 * (1 << 5);

    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    Matrix_Translate(0.0f, 0.0f, -144.0f, MTXMODE_NEW);
    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    // gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 150, 140, 90, 255);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, pauseExtraColor.r, pauseExtraColor.g, pauseExtraColor.b, 255);
    gSPVertex(POLY_OPA_DISP++, &pauseCtx->infoPanelVtx[0], 16, 0);

    gSPDisplayList(POLY_OPA_DISP++, gItemNamePanelDL);

    if ((pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) &&
        (!pauseCtx->mainState || (pauseCtx->mainState == PAUSE_MAIN_STATE_UNK))) {
        // gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 150, 140, 90, sPauseZRCursorAlpha);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, pauseExtraColor.r, pauseExtraColor.g, pauseExtraColor.b, sPauseZRCursorAlpha);
    }

    gSPDisplayList(POLY_OPA_DISP++, gZButtonIconDL);

    if ((pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_RIGHT) &&
        (!pauseCtx->mainState || (pauseCtx->mainState == PAUSE_MAIN_STATE_UNK))) {
        // gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 150, 140, 90, sPauseZRCursorAlpha);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, pauseExtraColor.r, pauseExtraColor.g, pauseExtraColor.b, sPauseZRCursorAlpha);
    }

    gSPDisplayList(POLY_OPA_DISP++, gRButtonIconDL);

    if (pauseCtx->cursorSpecialPos != 0) {
        j = (pauseCtx->cursorSpecialPos * 4) - 32;
        pauseCtx->cursorVtx[0].v.ob[0] = pauseCtx->infoPanelVtx[j].v.ob[0];
        pauseCtx->cursorVtx[0].v.ob[1] = pauseCtx->infoPanelVtx[j].v.ob[1];
    }

    y = pauseCtx->infoPanelOffsetY - 80;
    pauseCtx->infoPanelVtx[16].v.ob[1] = pauseCtx->infoPanelVtx[17].v.ob[1] = y;

    pauseCtx->infoPanelVtx[18].v.ob[1] = pauseCtx->infoPanelVtx[19].v.ob[1] = pauseCtx->infoPanelVtx[16].v.ob[1] - 16;

    pauseCtx->infoPanelVtx[18].v.tc[1] = pauseCtx->infoPanelVtx[19].v.tc[1] = 16 * (1 << 5);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetEnvColor(POLY_OPA_DISP++, 20, 30, 40, 0);

    if (pauseCtx->itemDescriptionOn ||
        ((pauseCtx->state == PAUSE_STATE_MAIN) && (pauseCtx->namedItem != PAUSE_ITEM_NONE) &&
         (pauseCtx->nameDisplayTimer < 40) &&
         (!pauseCtx->mainState || (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PLAYBACK) ||
          (pauseCtx->mainState == PAUSE_MAIN_STATE_UNK) ||
          ((pauseCtx->mainState >= PAUSE_MAIN_STATE_SONG_PROMPT_INIT) &&
           (pauseCtx->mainState <= PAUSE_MAIN_STATE_SONG_PROMPT_UNUSED)) ||
          (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG)) &&
         (pauseCtx->cursorSpecialPos == 0))) {
        if (!pauseCtx->mainState || (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PLAYBACK) ||
            (pauseCtx->mainState == PAUSE_MAIN_STATE_UNK) ||
            ((pauseCtx->mainState >= PAUSE_MAIN_STATE_SONG_PROMPT_INIT) &&
             (pauseCtx->mainState <= PAUSE_MAIN_STATE_SONG_PROMPT_UNUSED)) ||
            (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG)) {

            pauseCtx->infoPanelVtx[16].v.ob[0] = pauseCtx->infoPanelVtx[18].v.ob[0] = -63;

            pauseCtx->infoPanelVtx[17].v.ob[0] = pauseCtx->infoPanelVtx[19].v.ob[0] =
                pauseCtx->infoPanelVtx[16].v.ob[0] + 128;

            pauseCtx->infoPanelVtx[17].v.tc[0] = pauseCtx->infoPanelVtx[19].v.tc[0] = 128 * (1 << 5);

            gSPVertex(POLY_OPA_DISP++, &pauseCtx->infoPanelVtx[16], 4, 0);

            if (pauseCtx->nameColorSet == PAUSE_NAME_COLOR_SET_GREY) {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 70, 70, 70, 255);
            } else {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
            }

            POLY_OPA_DISP = Gfx_DrawTexQuad4b(POLY_OPA_DISP, pauseCtx->nameSegment, G_IM_FMT_IA, 128, 16, 0);
        }
    } else if ((pauseCtx->mainState <= PAUSE_MAIN_STATE_SONG_PLAYBACK) ||
               (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PROMPT_UNUSED) ||
               (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG) ||
               (pauseCtx->mainState == PAUSE_MAIN_STATE_UNK)) {
        pauseCtx->infoPanelVtx[20].v.ob[1] = pauseCtx->infoPanelVtx[21].v.ob[1] = y;

        pauseCtx->infoPanelVtx[22].v.ob[1] = pauseCtx->infoPanelVtx[23].v.ob[1] =
            pauseCtx->infoPanelVtx[20].v.ob[1] - 16;

        pauseCtx->infoPanelVtx[22].v.tc[1] = pauseCtx->infoPanelVtx[23].v.tc[1] = 16 * (1 << 5);

        gSPVertex(POLY_OPA_DISP++, &pauseCtx->infoPanelVtx[16], 8, 0);

        if (pauseCtx->state == PAUSE_STATE_SAVEPROMPT) {
            pauseCtx->infoPanelVtx[16].v.ob[0] = pauseCtx->infoPanelVtx[18].v.ob[0] = -33;

            pauseCtx->infoPanelVtx[17].v.ob[0] = pauseCtx->infoPanelVtx[19].v.ob[0] =
                pauseCtx->infoPanelVtx[16].v.ob[0] + 24;

            pauseCtx->infoPanelVtx[20].v.ob[0] = pauseCtx->infoPanelVtx[22].v.ob[0] =
                pauseCtx->infoPanelVtx[16].v.ob[0] + 0x10;

            pauseCtx->infoPanelVtx[21].v.ob[0] = pauseCtx->infoPanelVtx[23].v.ob[0] =
                pauseCtx->infoPanelVtx[20].v.ob[0] + 0x30;

            pauseCtx->infoPanelVtx[17].v.tc[0] = pauseCtx->infoPanelVtx[19].v.tc[0] = 24 * (1 << 5);

            pauseCtx->infoPanelVtx[21].v.tc[0] = pauseCtx->infoPanelVtx[23].v.tc[0] = 48 * (1 << 5);

            gSPDisplayList(POLY_OPA_DISP++, gAButtonIconDL);
            gDPPipeSync(POLY_OPA_DISP++);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);

            //! @bug: Incorrect dimensions. Should be 64x16
            POLY_OPA_DISP = Gfx_DrawTexQuad4b(POLY_OPA_DISP, gPauseToDecideENGTex, G_IM_FMT_IA, 48, 16, 4);

        } else if (pauseCtx->cursorSpecialPos != 0) {
            if ((pauseCtx->state == PAUSE_STATE_MAIN) && (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE)) {

                pauseCtx->infoPanelVtx[16].v.ob[0] = pauseCtx->infoPanelVtx[18].v.ob[0] = -63;

                pauseCtx->infoPanelVtx[17].v.ob[0] = pauseCtx->infoPanelVtx[19].v.ob[0] =
                    pauseCtx->infoPanelVtx[16].v.ob[0] + 128;

                pauseCtx->infoPanelVtx[17].v.tc[0] = pauseCtx->infoPanelVtx[19].v.tc[0] = 128 * (1 << 5);

                gDPPipeSync(POLY_OPA_DISP++);
                // TODO: add misc colors like this
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 200, 0, 255);
                // gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 100, 255, 255);

                if (pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) {
                    POLY_OPA_DISP =
                        Gfx_DrawTexQuad4b(POLY_OPA_DISP, D_8082B998[pauseCtx->pageIndex], G_IM_FMT_IA, 128, 16, 0);
                } else {
                    POLY_OPA_DISP =
                        Gfx_DrawTexQuad4b(POLY_OPA_DISP, D_8082B9A8[pauseCtx->pageIndex], G_IM_FMT_IA, 128, 16, 0);
                }
            }
        } else if ((!pauseCtx->pageIndex || (pauseCtx->pageIndex == PAUSE_MASK)) &&
                   (pauseCtx->namedItem != PAUSE_ITEM_NONE)) {
            pauseCtx->infoPanelVtx[16].v.ob[0] = pauseCtx->infoPanelVtx[18].v.ob[0] = -49;

            pauseCtx->infoPanelVtx[17].v.ob[0] = pauseCtx->infoPanelVtx[19].v.ob[0] =
                pauseCtx->infoPanelVtx[16].v.ob[0] + 48;

            pauseCtx->infoPanelVtx[20].v.ob[0] = pauseCtx->infoPanelVtx[22].v.ob[0] =
                pauseCtx->infoPanelVtx[16].v.ob[0] + 47;

            pauseCtx->infoPanelVtx[21].v.ob[0] = pauseCtx->infoPanelVtx[23].v.ob[0] =
                pauseCtx->infoPanelVtx[20].v.ob[0] + 64;

            pauseCtx->infoPanelVtx[17].v.tc[0] = pauseCtx->infoPanelVtx[19].v.tc[0] = 48 * (1 << 5);

            pauseCtx->infoPanelVtx[21].v.tc[0] = pauseCtx->infoPanelVtx[23].v.tc[0] = 64 * (1 << 5);

            gSPDisplayList(POLY_OPA_DISP++, gCButtonIconsDL);

            gDPPipeSync(POLY_OPA_DISP++);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);

            POLY_OPA_DISP = Gfx_DrawTexQuad4b(POLY_OPA_DISP, gPauseToEquipENGTex, G_IM_FMT_IA, 64, 16, 4);
        } else if ((pauseCtx->pageIndex == PAUSE_MAP) && sInDungeonScene) {
            // No code in this case
        } else if ((pauseCtx->pageIndex == PAUSE_QUEST) &&
                   (pauseCtx->cursorSlot[PAUSE_QUEST] == QUEST_BOMBERS_NOTEBOOK)) {
            if (pauseCtx->namedItem != PAUSE_ITEM_NONE) {
                // The cursor is on the bombers notebook
                pauseCtx->infoPanelVtx[16].v.ob[0] = pauseCtx->infoPanelVtx[18].v.ob[0] = -58;

                pauseCtx->infoPanelVtx[17].v.ob[0] = pauseCtx->infoPanelVtx[19].v.ob[0] =
                    pauseCtx->infoPanelVtx[16].v.ob[0] + 24;

                pauseCtx->infoPanelVtx[20].v.ob[0] = pauseCtx->infoPanelVtx[22].v.ob[0] =
                    pauseCtx->infoPanelVtx[16].v.ob[0] + 0x14;

                pauseCtx->infoPanelVtx[21].v.ob[0] = pauseCtx->infoPanelVtx[23].v.ob[0] =
                    pauseCtx->infoPanelVtx[20].v.ob[0] + 0x60;

                pauseCtx->infoPanelVtx[17].v.tc[0] = pauseCtx->infoPanelVtx[19].v.tc[0] = 24 * (1 << 5);

                pauseCtx->infoPanelVtx[21].v.tc[0] = pauseCtx->infoPanelVtx[23].v.tc[0] = 96 * (1 << 5);

                gSPDisplayList(POLY_OPA_DISP++, gAButtonIconDL);

                gDPPipeSync(POLY_OPA_DISP++);
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);

                POLY_OPA_DISP = Gfx_DrawTexQuad4b(POLY_OPA_DISP, gPauseToViewNotebookENGTex, G_IM_FMT_IA, 96, 16, 4);
            }
        } else if ((pauseCtx->pageIndex == PAUSE_QUEST) && (pauseCtx->cursorSlot[PAUSE_QUEST] >= QUEST_SONG_SONATA) &&
                   (pauseCtx->cursorSlot[PAUSE_QUEST] <= QUEST_SONG_SUN) && (pauseCtx->namedItem != PAUSE_ITEM_NONE)) {
            // The cursor is on a learned song
            pauseCtx->infoPanelVtx[16].v.ob[0] = pauseCtx->infoPanelVtx[18].v.ob[0] = -55;

            pauseCtx->infoPanelVtx[17].v.ob[0] = pauseCtx->infoPanelVtx[19].v.ob[0] =
                pauseCtx->infoPanelVtx[16].v.ob[0] + 24;

            pauseCtx->infoPanelVtx[20].v.ob[0] = pauseCtx->infoPanelVtx[22].v.ob[0] =
                pauseCtx->infoPanelVtx[16].v.ob[0] + 20;

            pauseCtx->infoPanelVtx[21].v.ob[0] = pauseCtx->infoPanelVtx[23].v.ob[0] =
                pauseCtx->infoPanelVtx[20].v.ob[0] + 96;

            pauseCtx->infoPanelVtx[17].v.tc[0] = pauseCtx->infoPanelVtx[19].v.tc[0] = 24 * (1 << 5);

            pauseCtx->infoPanelVtx[21].v.tc[0] = pauseCtx->infoPanelVtx[23].v.tc[0] = 96 * (1 << 5);

            gSPDisplayList(POLY_OPA_DISP++, gAButtonIconDL);

            gDPPipeSync(POLY_OPA_DISP++);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);

            POLY_OPA_DISP = Gfx_DrawTexQuad4b(POLY_OPA_DISP, gPauseToPlayMelodyENGTex, G_IM_FMT_IA, 96, 16, 4);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}