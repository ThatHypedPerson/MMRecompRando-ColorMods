#include "modding.h"
#include "global.h"

#include "recolor.h"

extern u64 gTatlCUpENGTex[];
extern u64 gTatlCUpGERTex[];
extern u64 gTatlCUpFRATex[];
extern u64 gTatlCUpESPTex[];
extern u64 gButtonBackgroundTex[];

s16 D_801BF9D4[] = {
    0xA7,  // EQUIP_SLOT_B
    0xE3,  // EQUIP_SLOT_C_LEFT
    0xF9,  // EQUIP_SLOT_C_DOWN
    0x10F, // EQUIP_SLOT_C_RIGHT
};
s16 D_801BF9DC[] = {
    0x11, // EQUIP_SLOT_B
    0x12, // EQUIP_SLOT_C_LEFT
    0x22, // EQUIP_SLOT_C_DOWN
    0x12, // EQUIP_SLOT_C_RIGHT
};
s16 D_801BF9E4[] = {
    0x23F, // EQUIP_SLOT_B
    0x26C, // EQUIP_SLOT_C_LEFT
    0x26C, // EQUIP_SLOT_C_DOWN
    0x26C, // EQUIP_SLOT_C_RIGHT
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

typedef enum {
    /* 0 */ DEBUG_EDITOR_NONE,
    /* 1 */ DEBUG_EDITOR_INVENTORY_INIT,
    /* 2 */ DEBUG_EDITOR_INVENTORY,
    /* 3 */ DEBUG_EDITOR_EVENTS
} DebugEditor;

#define DO_ACTION_TEX_WIDTH 48
#define DO_ACTION_TEX_HEIGHT 16
#define DO_ACTION_TEX_SIZE ((DO_ACTION_TEX_WIDTH * DO_ACTION_TEX_HEIGHT) / 2)

typedef enum {
    /* 0 */ PICTO_BOX_STATE_OFF,         // Not using the pictograph
    /* 1 */ PICTO_BOX_STATE_LENS,        // Looking through the lens of the pictograph
    /* 2 */ PICTO_BOX_STATE_SETUP_PHOTO, // Looking at the photo currently taken
    /* 3 */ PICTO_BOX_STATE_PHOTO
} PictoBoxState;
s16 sPictoState = PICTO_BOX_STATE_OFF;

u16 sCUpInvisible = 0;
u16 sCUpTimer = 0;

Gfx* Gfx_DrawTexRectIA8_DropShadow(Gfx* gfx, TexturePtr texture, s16 textureWidth, s16 textureHeight, s16 rectLeft,
                                   s16 rectTop, s16 rectWidth, s16 rectHeight, u16 dsdx, u16 dtdy, s16 r, s16 g, s16 b,
                                   s16 a);
Gfx* Gfx_DrawRect_DropShadow(Gfx* gfx, s16 rectLeft, s16 rectTop, s16 rectWidth, s16 rectHeight, u16 dsdx, u16 dtdy,
                             s16 r, s16 g, s16 b, s16 a);


RECOMP_PATCH void Interface_DrawItemButtons(PlayState* play) {
    static TexturePtr cUpLabelTextures[] = {
        gTatlCUpENGTex, gTatlCUpENGTex, gTatlCUpGERTex, gTatlCUpFRATex, gTatlCUpESPTex,
    };
    static s16 startButtonLeftPos[] = {
        // Remnant of OoT
        130, 136, 136, 136, 136,
    };
    static s16 D_801BFAF4[] = {
        0x1D, // EQUIP_SLOT_B
        0x1B, // EQUIP_SLOT_C_LEFT
        0x1B, // EQUIP_SLOT_C_DOWN
        0x1B, // EQUIP_SLOT_C_RIGHT
    };
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    Player* player = GET_PLAYER(play);
    PauseContext* pauseCtx = &play->pauseCtx;
    MessageContext* msgCtx = &play->msgCtx;
    s16 temp; // Used as both an alpha value and a button index
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    gDPPipeSync(OVERLAY_DISP++);
    gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    // B Button Color & Texture
    // OVERLAY_DISP = Gfx_DrawTexRectIA8_DropShadow(
    //     OVERLAY_DISP, gButtonBackgroundTex, 0x20, 0x20, D_801BF9D4[EQUIP_SLOT_B], D_801BF9DC[EQUIP_SLOT_B],
    //     D_801BFAF4[EQUIP_SLOT_B], D_801BFAF4[EQUIP_SLOT_B], D_801BF9E4[EQUIP_SLOT_B] * 2, D_801BF9E4[EQUIP_SLOT_B] * 2,
    //     100, 255, 120, interfaceCtx->bAlpha);
    OVERLAY_DISP = Gfx_DrawTexRectIA8_DropShadow(
        OVERLAY_DISP, gButtonBackgroundTex, 0x20, 0x20, D_801BF9D4[EQUIP_SLOT_B], D_801BF9DC[EQUIP_SLOT_B],
        D_801BFAF4[EQUIP_SLOT_B], D_801BFAF4[EQUIP_SLOT_B], D_801BF9E4[EQUIP_SLOT_B] * 2, D_801BF9E4[EQUIP_SLOT_B] * 2,
        buttonBColor.r, buttonBColor.g, buttonBColor.b, interfaceCtx->bAlpha);
    gDPPipeSync(OVERLAY_DISP++);

    // C-Left Button Color & Texture
    OVERLAY_DISP = Gfx_DrawRect_DropShadow(OVERLAY_DISP, D_801BF9D4[EQUIP_SLOT_C_LEFT], D_801BF9DC[EQUIP_SLOT_C_LEFT],
                                           D_801BFAF4[EQUIP_SLOT_C_LEFT], D_801BFAF4[EQUIP_SLOT_C_LEFT],
                                           D_801BF9E4[EQUIP_SLOT_C_LEFT] * 2, D_801BF9E4[EQUIP_SLOT_C_LEFT] * 2, 
										   buttonCColor.r, buttonCColor.g, buttonCColor.b, interfaceCtx->cLeftAlpha);
    // C-Down Button Color & Texture
    OVERLAY_DISP = Gfx_DrawRect_DropShadow(OVERLAY_DISP, D_801BF9D4[EQUIP_SLOT_C_DOWN], D_801BF9DC[EQUIP_SLOT_C_DOWN],
                                           D_801BFAF4[EQUIP_SLOT_C_DOWN], D_801BFAF4[EQUIP_SLOT_C_DOWN],
                                           D_801BF9E4[EQUIP_SLOT_C_DOWN] * 2, D_801BF9E4[EQUIP_SLOT_C_DOWN] * 2,
										   buttonCColor.r, buttonCColor.g, buttonCColor.b, interfaceCtx->cDownAlpha);
    // C-Right Button Color & Texture
    OVERLAY_DISP = Gfx_DrawRect_DropShadow(OVERLAY_DISP, D_801BF9D4[EQUIP_SLOT_C_RIGHT], D_801BF9DC[EQUIP_SLOT_C_RIGHT],
                                           D_801BFAF4[EQUIP_SLOT_C_RIGHT], D_801BFAF4[EQUIP_SLOT_C_RIGHT],
                                           D_801BF9E4[EQUIP_SLOT_C_RIGHT] * 2, D_801BF9E4[EQUIP_SLOT_C_RIGHT] * 2,
										   buttonCColor.r, buttonCColor.g, buttonCColor.b, interfaceCtx->cRightAlpha);

    if (!IS_PAUSE_STATE_GAMEOVER) {
        if ((play->pauseCtx.state != PAUSE_STATE_OFF) || (play->pauseCtx.debugEditor != DEBUG_EDITOR_NONE)) {
            // OVERLAY_DISP = Gfx_DrawRect_DropShadow(OVERLAY_DISP, 0x88, 0x11, 0x16, 0x16, 0x5B6, 0x5B6, 0xFF, 0x82, 0x3C,
            //                                        interfaceCtx->startAlpha);
            OVERLAY_DISP = Gfx_DrawRect_DropShadow(OVERLAY_DISP, 0x88, 0x11, 0x16, 0x16, 0x5B6, 0x5B6,
													buttonStartColor.r, buttonStartColor.g, buttonStartColor.b, interfaceCtx->startAlpha);
            // Start Button Texture, Color & Label
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->startAlpha);
            gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, 0);
            gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                              PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
            gDPLoadTextureBlock_4b(OVERLAY_DISP++, interfaceCtx->doActionSegment + DO_ACTION_TEX_SIZE * 2, G_IM_FMT_IA,
                                   DO_ACTION_TEX_WIDTH, DO_ACTION_TEX_HEIGHT, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(OVERLAY_DISP++, 0x01F8, 0x0054, 0x02D4, 0x009C, G_TX_RENDERTILE, 0, 0, 0x04A6, 0x04A6);
        }
    }

    if (interfaceCtx->tatlCalling && (play->pauseCtx.state == PAUSE_STATE_OFF) &&
        (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE) && (play->csCtx.state == CS_STATE_IDLE) &&
        (sPictoState == PICTO_BOX_STATE_OFF)) {
        if (sCUpInvisible == 0) {
            // C-Up Button Texture, Color & Label (Tatl Text)
            gDPPipeSync(OVERLAY_DISP++);

            if ((gSaveContext.hudVisibility == HUD_VISIBILITY_NONE) ||
                (gSaveContext.hudVisibility == HUD_VISIBILITY_NONE_ALT) ||
                (gSaveContext.hudVisibility == HUD_VISIBILITY_A_HEARTS_MAGIC_WITH_OVERWRITE) ||
                (msgCtx->msgMode != MSGMODE_NONE)) {
                temp = 0;
            } else if (player->stateFlags1 & PLAYER_STATE1_200000) {
                temp = 70;
            } else {
                temp = interfaceCtx->aAlpha;
            }

            OVERLAY_DISP =
                // Gfx_DrawRect_DropShadow(OVERLAY_DISP, 0xFE, 0x10, 0x10, 0x10, 0x800, 0x800, 0xFF, 0xF0, 0, temp);
                Gfx_DrawRect_DropShadow(OVERLAY_DISP, 0xFE, 0x10, 0x10, 0x10, 0x800, 0x800, buttonCColor.r, buttonCColor.g, buttonCColor.b, temp);

            gDPPipeSync(OVERLAY_DISP++);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, temp);
            gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, 0);
            gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                              PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
            gDPLoadTextureBlock_4b(OVERLAY_DISP++, cUpLabelTextures[gSaveContext.options.language], G_IM_FMT_IA, 32, 12,
                                   0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(OVERLAY_DISP++, 0x03DC, 0x0048, 0x045C, 0x0078, G_TX_RENDERTILE, 0, 0, 1 << 10,
                                1 << 10);
        }

        sCUpTimer--;
        if (sCUpTimer == 0) {
            sCUpInvisible ^= 1;
            sCUpTimer = 10;
        }
    }

    gDPPipeSync(OVERLAY_DISP++);

    // Empty C Button Arrows
    for (temp = EQUIP_SLOT_C_LEFT; temp <= EQUIP_SLOT_C_RIGHT; temp++) {
        if (GET_CUR_FORM_BTN_ITEM(temp) > 0xF0) {
            if (temp == EQUIP_SLOT_C_LEFT) {
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, buttonCColor.r, buttonCColor.g, buttonCColor.b, interfaceCtx->cLeftAlpha);
            } else if (temp == EQUIP_SLOT_C_DOWN) {
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, buttonCColor.r, buttonCColor.g, buttonCColor.b, interfaceCtx->cDownAlpha);
            } else { // EQUIP_SLOT_C_RIGHT
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, buttonCColor.r, buttonCColor.g, buttonCColor.b, interfaceCtx->cRightAlpha);
            }
            OVERLAY_DISP = Gfx_DrawTexRectIA8(OVERLAY_DISP, ((u8*)gButtonBackgroundTex + ((32 * 32) * (temp + 1))),
                                              0x20, 0x20, D_801BF9D4[temp], D_801BF9DC[temp], D_801BFAF4[temp],
                                              D_801BFAF4[temp], D_801BF9E4[temp] * 2, D_801BF9E4[temp] * 2);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

f32 D_801BF9CC[] = { -380.0f, -350.0f };

void Interface_SetPerspectiveView(PlayState* play, s32 topY, s32 bottomY, s32 leftX, s32 rightX);
void Interface_SetPerfectLetters(PlayState* play, s16 perfectLettersType);

RECOMP_PATCH void Interface_DrawAButton(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    s16 aAlpha;

    OPEN_DISPS(play->state.gfxCtx);

    aAlpha = interfaceCtx->aAlpha;

    if (aAlpha > 100) {
        aAlpha = 100;
    }

    Gfx_SetupDL42_Overlay(play->state.gfxCtx);

    Interface_SetPerspectiveView(play, 25 + R_A_BTN_Y_OFFSET, 70 + R_A_BTN_Y_OFFSET, 192, 237);

    gSPClearGeometryMode(OVERLAY_DISP++, G_CULL_BOTH);
    gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetAlphaCompare(OVERLAY_DISP++, G_AC_THRESHOLD);

    Matrix_Translate(0.0f, 0.0f, -38.0f, MTXMODE_NEW);
    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
    Matrix_RotateXFApply(interfaceCtx->aButtonRoll / 10000.0f);

    // Draw A button Shadow
    gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(OVERLAY_DISP++);
    gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[4], 4, 0);
    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, aAlpha);

    OVERLAY_DISP = Gfx_DrawTexQuadIA8(OVERLAY_DISP, gButtonBackgroundTex, 32, 32, 0);

    // Draw A Button Colored
    gDPPipeSync(OVERLAY_DISP++);
    Interface_SetPerspectiveView(play, 23 + R_A_BTN_Y_OFFSET, 68 + R_A_BTN_Y_OFFSET, 190, 235);
    gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[0], 4, 0);
    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, buttonAColor.r, buttonAColor.g, buttonAColor.b, interfaceCtx->aAlpha);
    gSP1Quadrangle(OVERLAY_DISP++, 0, 2, 3, 1, 0);

    // Draw A Button Do-Action
    gDPPipeSync(OVERLAY_DISP++);
    Interface_SetPerspectiveView(play, 23 + R_A_BTN_Y_OFFSET, 68 + R_A_BTN_Y_OFFSET, 190, 235);
    gSPSetGeometryMode(OVERLAY_DISP++, G_CULL_BACK);
    gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->aAlpha);
    gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, 0);

    Matrix_Translate(0.0f, 0.0f, D_801BF9CC[gSaveContext.options.language] / 10.0f, MTXMODE_NEW);
    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
    Matrix_RotateXFApply(interfaceCtx->aButtonRoll / 10000.0f);
    gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[8], 4, 0);

    // Draw Action Label
    if (((interfaceCtx->aButtonState <= A_BTN_STATE_1) || (interfaceCtx->aButtonState == A_BTN_STATE_3))) {
        OVERLAY_DISP = Gfx_DrawTexQuad4b(OVERLAY_DISP, interfaceCtx->doActionSegment, 3, DO_ACTION_TEX_WIDTH,
                                         DO_ACTION_TEX_HEIGHT, 0);
    } else {
        OVERLAY_DISP = Gfx_DrawTexQuad4b(OVERLAY_DISP, interfaceCtx->doActionSegment + DO_ACTION_TEX_SIZE, 3,
                                         DO_ACTION_TEX_WIDTH, DO_ACTION_TEX_HEIGHT, 0);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

// songwall
#define THIS ((EnGakufu*)thisx)
struct EnGakufu;
typedef void (*EnGakufuActionFunc)(struct EnGakufu*, PlayState*);
typedef struct EnGakufu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s32 songIndex;
    /* 0x148 */ u8 buttonIndex[8];
    /* 0x150 */ EnGakufuActionFunc actionFunc;
} EnGakufu; // size = 0x154

extern f32 sOcarinaBtnWallYOffsets[];
extern TexturePtr sOcarinaBtnWallTextures[];
extern Gfx gGakufuButtonIndexDL[];

RECOMP_PATCH void EnGakufu_Draw(Actor* thisx, PlayState* play) {
    s32 i;
    s32 pad;
    EnGakufu* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    gDPPipeSync(POLY_XLU_DISP++);
    gSPSegment(POLY_XLU_DISP++, 0x02, play->interfaceCtx.parameterSegment);

    for (i = 0; (i < ARRAY_COUNT(this->buttonIndex)) && (this->buttonIndex[i] != OCARINA_BTN_INVALID); i++) {
        Matrix_Push();
        Matrix_Translate(30 * i - 105, sOcarinaBtnWallYOffsets[this->buttonIndex[i]] * 7.5f, 1.0f, MTXMODE_APPLY);
        Matrix_Scale(0.6f, 0.6f, 0.6f, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetTextureLUT(POLY_XLU_DISP++, G_TT_NONE);
        gDPLoadTextureBlock(POLY_XLU_DISP++, sOcarinaBtnWallTextures[this->buttonIndex[i]], G_IM_FMT_IA, G_IM_SIZ_8b,
                            16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD,
                            G_TX_NOLOD);

        if (matchButtonColors) {
            if (this->buttonIndex[i] == OCARINA_BTN_A) {
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, buttonAColor.r, buttonAColor.g, buttonAColor.b, 200);
            } else {
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, buttonCColor.r, buttonCColor.g, buttonCColor.b, 200);
            }
        } else {
            if (this->buttonIndex[i] == OCARINA_BTN_A) {
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 80, 150, 255, 200);
            } else {
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 50, 200);
            }
        }

        gSPDisplayList(POLY_XLU_DISP++, gGakufuButtonIndexDL);

        Matrix_Pop();
    }

    gSPSegment(POLY_XLU_DISP++, 0x02, play->sceneSegment);

    CLOSE_DISPS(play->state.gfxCtx);
}