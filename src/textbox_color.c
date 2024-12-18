#include "modding.h"
#include "global.h"

#include "recolor.h"

extern s16 sTextboxWidth;
extern s16 sTextboxHeight;
extern s16 sTextboxTexWidth;
extern s16 sTextboxTexHeight;
extern u64 gOcarinaTrebleClefTex[];

// // conflicts with better_double_sot
// RECOMP_PATCH void Message_DrawTextBox(PlayState* play, Gfx** gfxP) {
//     MessageContext* msgCtx = &play->msgCtx;
//     Gfx* gfx = *gfxP;

//     gDPPipeSync(gfx++);

//     if (((u32)msgCtx->textBoxType == TEXTBOX_TYPE_0) || (msgCtx->textBoxType == TEXTBOX_TYPE_2) ||
//         (msgCtx->textBoxType == TEXTBOX_TYPE_9) || (msgCtx->textBoxType == TEXTBOX_TYPE_A)) {
//         gDPSetRenderMode(gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
//     } else if (msgCtx->textBoxType == TEXTBOX_TYPE_3) {
//         gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
//         gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
//     }

//     gDPSetPrimColor(gfx++, 0, 0, msgCtx->textboxColorRed, msgCtx->textboxColorGreen, msgCtx->textboxColorBlue,
//                     msgCtx->textboxColorAlphaCurrent);

//     if (((u32)msgCtx->textBoxType == TEXTBOX_TYPE_0) || (msgCtx->textBoxType == TEXTBOX_TYPE_2) ||
//         (msgCtx->textBoxType == TEXTBOX_TYPE_6) || (msgCtx->textBoxType == TEXTBOX_TYPE_8) ||
//         (msgCtx->textBoxType == TEXTBOX_TYPE_9) || (msgCtx->textBoxType == TEXTBOX_TYPE_A)) {
//         gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment, G_IM_FMT_I, 128, 64, 0, G_TX_MIRROR | G_TX_WRAP,
//                                G_TX_NOMIRROR | G_TX_WRAP, 7, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
//     } else {
//         gDPPipeSync(gfx++);

//         if (msgCtx->textBoxType == TEXTBOX_TYPE_3) {
//             gDPSetEnvColor(gfx++, 0, 0, 0, 255);
//         } else if (msgCtx->textBoxType == TEXTBOX_TYPE_D) {
//             gDPSetEnvColor(gfx++, 20, 0, 10, 255);
//         } else {
//             gDPSetEnvColor(gfx++, 50, 20, 0, 255);
//         }
//         gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment, G_IM_FMT_IA, 128, 64, 0, G_TX_MIRROR | G_TX_WRAP,
//                                G_TX_MIRROR | G_TX_WRAP, 7, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
//     }

//     if (msgCtx->textBoxType == TEXTBOX_TYPE_A) {
//         gSPTextureRectangle(gfx++, msgCtx->textboxX << 2, (msgCtx->textboxY + 22) << 2,
//                             (msgCtx->textboxX + msgCtx->unk12008) << 2, (msgCtx->textboxY + 54) << 2, G_TX_RENDERTILE,
//                             0, 6, msgCtx->unk1200C << 1, 2 << 10);
//     } else {
//         gSPTextureRectangle(gfx++, msgCtx->textboxX << 2, (msgCtx->textboxY) << 2,
//                             (msgCtx->textboxX + sTextboxWidth) << 2, (msgCtx->textboxY + sTextboxHeight) << 2,
//                             G_TX_RENDERTILE, 0, 0, sTextboxTexWidth, sTextboxTexHeight);
//     }

//     // Draw treble clef
//     if (msgCtx->textBoxType == TEXTBOX_TYPE_3) {
//         gDPPipeSync(gfx++);
//         gDPSetCombineLERP(gfx++, 1, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, 1, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE,
//                           0);
//         // gDPSetPrimColor(gfx++, 0, 0, 255, 100, 0, 255);
//         gDPSetPrimColor(gfx++, 0, 0, trebleClefColor.r, trebleClefColor.g, trebleClefColor.b, 255);
//         gDPLoadTextureBlock_4b(gfx++, gOcarinaTrebleClefTex, G_IM_FMT_I, 16, 32, 0, G_TX_MIRROR | G_TX_WRAP,
//                                G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
//         gSPTextureRectangle(gfx++, 78 << 2, 166 << 2, 94 << 2, 198 << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
//     }

//     *gfxP = gfx++;
// }

extern s16 sOcarinaButtonAPrimR;
extern s16 sOcarinaButtonAPrimB;
extern s16 sOcarinaButtonAPrimG;
extern s16 sOcarinaButtonAEnvR;
extern s16 sOcarinaButtonAEnvB;
extern s16 sOcarinaButtonAEnvG;
extern s16 sOcarinaButtonCPrimR;
extern s16 sOcarinaButtonCPrimB;
extern s16 sOcarinaButtonCPrimG;
extern s16 sOcarinaButtonCEnvR;
extern s16 sOcarinaButtonCEnvB;
extern s16 sOcarinaButtonCEnvG;

void Message_ResetOcarinaButtonAlphas(void);

RECOMP_PATCH void Message_ResetOcarinaButtonState(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    msgCtx->ocarinaButtonsPosY[OCARINA_BTN_A] = 189;
    msgCtx->ocarinaButtonsPosY[OCARINA_BTN_C_DOWN] = 184;
    msgCtx->ocarinaButtonsPosY[OCARINA_BTN_C_RIGHT] = 179;
    msgCtx->ocarinaButtonsPosY[OCARINA_BTN_C_LEFT] = 174;
    msgCtx->ocarinaButtonsPosY[OCARINA_BTN_C_UP] = 169;

    Message_ResetOcarinaButtonAlphas();

    if (matchButtonColors) {
        sOcarinaButtonAPrimR = buttonAColor.r;
        sOcarinaButtonAPrimG = buttonAColor.g;
        sOcarinaButtonAPrimB = buttonAColor.b;
        sOcarinaButtonCPrimR = buttonCColor.r;
        sOcarinaButtonCPrimG = buttonCColor.g;
        sOcarinaButtonCPrimB = buttonCColor.b;
    } else {
        sOcarinaButtonAPrimR = 80;
        sOcarinaButtonAPrimG = 150;
        sOcarinaButtonAPrimB = 255;
        sOcarinaButtonCPrimR = 255;
        sOcarinaButtonCPrimG = 255;
        sOcarinaButtonCPrimB = 50;
    }
        
    sOcarinaButtonAEnvR = 10;
    sOcarinaButtonAEnvG = 10;
    sOcarinaButtonAEnvB = 10;
    sOcarinaButtonCEnvR = 10;
    sOcarinaButtonCEnvG = 10;
    sOcarinaButtonCEnvB = 10;
}

extern s32 sCharTexSize;
extern s32 sCharTexScale;

RECOMP_PATCH void Message_DrawTextboxIcon(PlayState* play, Gfx** gfxP, s16 x, s16 y) {
    // static Color_RGB16 sIconPrimColors[] = {
    //     { 0, 80, 200 },
    //     { 50, 130, 255 },
    // };
    // static Color_RGB16 sIconEnvColors[] = {
    //     { 0, 0, 0 },
    //     { 0, 130, 255 },
    // };
    // static s16 sIconPrimR = 0;
    // static s16 sIconPrimG = 80;
    // static s16 sIconPrimB = 200;
    Color_RGB16 sIconPrimColors[] = {
        { 0, 80, 200 },
        { 50, 130, 255 },
    };
    Color_RGB16 sIconEnvColors[] = {
        { 0, 0, 0 },
        { 0, 130, 255 },
    };
    s16 sIconPrimR = 0;
    s16 sIconPrimG = 80;
    s16 sIconPrimB = 200;
    
    if (matchButtonColors) {
        // TODO: add proper flashing?
        Color_RGB16 sIconPrimColors[] = {
            {buttonAColor.r, buttonAColor.g, buttonAColor.b},
            {buttonAColor.r, buttonAColor.g, buttonAColor.b},
        };
        Color_RGB16 sIconEnvColors[] = {
            { 0, 0, 0 },
            { 255, 255, 255 },
        };
        s16 sIconPrimR = buttonAColor.r;
        s16 sIconPrimG = buttonAColor.g;
        s16 sIconPrimB = buttonAColor.b;
    }

    static s16 sIconFlashTimer = 12;
    static s16 sIconFlashColorIndex = 0;
    static s16 sIconEnvR = 0;
    static s16 sIconEnvG = 0;
    static s16 sIconEnvB = 0;
    Gfx* gfx;
    MessageContext* msgCtx = &play->msgCtx;
    Font* font = &msgCtx->font;
    s16 primR;
    s16 primG;
    s16 primB;
    s16 envR;
    s16 envG;
    s16 envB;
    u8* iconTexture = msgCtx->font.iconBuf;

    gfx = *gfxP;

    if (!msgCtx->textIsCredits) {
        primR = ABS_ALT(sIconPrimR - sIconPrimColors[sIconFlashColorIndex].r) / sIconFlashTimer;
        primG = ABS_ALT(sIconPrimG - sIconPrimColors[sIconFlashColorIndex].g) / sIconFlashTimer;
        primB = ABS_ALT(sIconPrimB - sIconPrimColors[sIconFlashColorIndex].b) / sIconFlashTimer;

        if (sIconPrimR >= sIconPrimColors[sIconFlashColorIndex].r) {
            sIconPrimR -= primR;
        } else {
            sIconPrimR += primR;
        }

        if (sIconPrimG >= sIconPrimColors[sIconFlashColorIndex].g) {
            sIconPrimG -= primG;
        } else {
            sIconPrimG += primG;
        }

        if (sIconPrimB >= sIconPrimColors[sIconFlashColorIndex].b) {
            sIconPrimB -= primB;
        } else {
            sIconPrimB += primB;
        }

        envR = ABS_ALT(sIconEnvR - sIconEnvColors[sIconFlashColorIndex].r) / sIconFlashTimer;
        envG = ABS_ALT(sIconEnvG - sIconEnvColors[sIconFlashColorIndex].g) / sIconFlashTimer;
        envB = ABS_ALT(sIconEnvB - sIconEnvColors[sIconFlashColorIndex].b) / sIconFlashTimer;

        if (sIconEnvR >= sIconEnvColors[sIconFlashColorIndex].r) {
            sIconEnvR -= envR;
        } else {
            sIconEnvR += envR;
        }

        if (sIconEnvG >= sIconEnvColors[sIconFlashColorIndex].g) {
            sIconEnvG -= envG;
        } else {
            sIconEnvG += envG;
        }

        if (sIconEnvB >= sIconEnvColors[sIconFlashColorIndex].b) {
            sIconEnvB -= envB;
        } else {
            sIconEnvB += envB;
        }

        sIconFlashTimer--;
        if (sIconFlashTimer == 0) {
            sIconPrimR = sIconPrimColors[sIconFlashColorIndex].r;
            sIconPrimG = sIconPrimColors[sIconFlashColorIndex].g;
            sIconPrimB = sIconPrimColors[sIconFlashColorIndex].b;
            sIconEnvR = sIconEnvColors[sIconFlashColorIndex].r;
            sIconEnvG = sIconEnvColors[sIconFlashColorIndex].g;
            sIconEnvB = sIconEnvColors[sIconFlashColorIndex].b;
            sIconFlashTimer = 12;
            sIconFlashColorIndex ^= 1;
        }

        gDPPipeSync(gfx++);
        gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                          ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(gfx++, 0, 0, sIconPrimR, sIconPrimG, sIconPrimB, 255);
        gDPSetEnvColor(gfx++, sIconEnvR, sIconEnvG, sIconEnvB, 255);

        if (!play->pauseCtx.bombersNotebookOpen) {
            gDPLoadTextureBlock_4b(gfx++, iconTexture, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gfx++, x << 2, y << 2, (x + sCharTexSize) << 2, (y + sCharTexSize) << 2,
                                G_TX_RENDERTILE, 0, 0, sCharTexScale, sCharTexScale);
        }

        msgCtx->stateTimer++;
        *gfxP = gfx;
    }
}