// // temporarily disabled due to it overwriting some base recomp patches

// #include "modding.h"
// #include "global.h"

// #include "recolor.h"

// #define DEBUG_EDITOR_NONE 0x0
// #define PAUSE_STATE_OFF 0x0

// typedef enum {
//     /* 0 */ PICTO_BOX_STATE_OFF,         // Not using the pictograph
//     /* 1 */ PICTO_BOX_STATE_LENS,        // Looking through the lens of the pictograph
//     /* 2 */ PICTO_BOX_STATE_SETUP_PHOTO, // Looking at the photo currently taken
//     /* 3 */ PICTO_BOX_STATE_PHOTO
// } PictoBoxState;

// extern TexturePtr sStoryTextures[];
// extern TexturePtr sStoryTLUTs[];
// extern u64 gRupeeCounterIconTex[];
// extern u64 gSmallKeyCounterIconTex[];
// extern u64 gCounterDigit0Tex[];
// extern u64 gGoldSkulltulaCounterIconTex[];
// extern s16 sRupeeDigitsFirst[];
// extern s16 sRupeeDigitsCount[];
// extern Color_RGB16 sMinigameCountdownPrimColors[];
// extern TexturePtr sMinigameCountdownTextures[];
// extern s16 sMinigameCountdownTexWidths[];
// extern s16 sPictoState;
// extern u64 gPictoBoxFocusBorderTex[];
// extern u64 gPictoBoxFocusIconTex[];
// extern u64 gPictoBoxFocusTextTex[];
// extern void* gWorkBuffer;

// static Gfx sScreenFillSetupDL[] = {
//     gsDPPipeSync(),
//     gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
//                           G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
//     gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
//                          G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_1PRIMITIVE,
//                      G_AC_NONE | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
//     gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
//     gsSPEndDisplayList(),
// };

// void Interface_SetVertices(PlayState* play);
// void Interface_SetOrthoView(InterfaceContext* interfaceCtx);
// void Magic_DrawMeter(PlayState* play);
// void Interface_DrawItemButtons(PlayState* play);
// void Interface_DrawBButtonIcons(PlayState* play);
// void Interface_DrawCButtonIcons(PlayState* play);
// void Interface_DrawAButton(PlayState* play);
// void Interface_DrawPauseMenuEquippingIcons(PlayState* play);
// void Interface_DrawClock(PlayState* play);
// void Interface_DrawPerfectLetters(PlayState* play);
// void Interface_DrawMinigameIcons(PlayState* play);
// void Interface_DrawTimers(PlayState* play);

// // Color_RGB16 sRupeeCounterIconPrimColors[] = {
// //     { 200, 255, 100 },
// //     { 170, 170, 255 },
// //     { 255, 105, 105 },
// // };

// // Color_RGB16 sRupeeCounterIconEnvColors[] = {
// //     { 0, 80, 0 },
// //     { 10, 10, 80 },
// //     { 40, 10, 0 },
// // };

// RECOMP_PATCH void Interface_Draw(PlayState* play) {
//     s32 pad;
//     InterfaceContext* interfaceCtx = &play->interfaceCtx;
//     Player* player = GET_PLAYER(play);
//     Gfx* gfx;
//     s16 sp2CE;
//     s16 sp2CC;
//     s16 sp2CA;
//     s16 sp2C8;
//     PauseContext* pauseCtx = &play->pauseCtx;
//     f32 minigameCountdownScale;
//     s16 counterDigits[4];
//     s16 magicAlpha;

//     OPEN_DISPS(play->state.gfxCtx);

//     gSPSegment(OVERLAY_DISP++, 0x02, interfaceCtx->parameterSegment);
//     gSPSegment(OVERLAY_DISP++, 0x09, interfaceCtx->doActionSegment);
//     gSPSegment(OVERLAY_DISP++, 0x08, interfaceCtx->iconItemSegment);
//     gSPSegment(OVERLAY_DISP++, 0x0B, interfaceCtx->mapSegment);

//     if (pauseCtx->debugEditor == DEBUG_EDITOR_NONE) {
//         Interface_SetVertices(play);
//         Interface_SetOrthoView(interfaceCtx);

//         // Draw Grandma's Story
//         if (interfaceCtx->storyDmaStatus == STORY_DMA_DONE) {
//             gSPSegment(OVERLAY_DISP++, 0x07, interfaceCtx->storySegment);
//             Gfx_SetupDL39_Opa(play->state.gfxCtx);

//             gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_POINT);
//             gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);

//             // Load in Grandma's Story
//             gSPLoadUcodeL(OVERLAY_DISP++, gspS2DEX2_fifo);
//             gfx = OVERLAY_DISP;
//             Prerender_DrawBackground2D(&gfx, sStoryTextures[interfaceCtx->storyType],
//                                        sStoryTLUTs[interfaceCtx->storyType], SCREEN_WIDTH, SCREEN_HEIGHT, 2, 1, 0x8000,
//                                        0x100, 0.0f, 0.0f, 1.0f, 1.0f, 0);
//             OVERLAY_DISP = gfx;
//             gSPLoadUcode(OVERLAY_DISP++, SysUcode_GetUCode(), SysUcode_GetUCodeData());

//             gDPPipeSync(OVERLAY_DISP++);

//             // Fill the screen with a black rectangle
//             gDPSetRenderMode(OVERLAY_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
//             gDPSetCombineMode(OVERLAY_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
//             gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, R_STORY_FILL_SCREEN_ALPHA);
//             gDPFillRectangle(OVERLAY_DISP++, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
//         }

//         LifeMeter_Draw(play);

//         Gfx_SetupDL39_Overlay(play->state.gfxCtx);

//         // Draw Rupee Icon
//         // gDPSetPrimColor(OVERLAY_DISP++, 0, 0, sRupeeCounterIconPrimColors[CUR_UPG_VALUE(UPG_WALLET)].r,
//         //                 sRupeeCounterIconPrimColors[CUR_UPG_VALUE(UPG_WALLET)].g,
//         //                 sRupeeCounterIconPrimColors[CUR_UPG_VALUE(UPG_WALLET)].b, interfaceCtx->magicAlpha);
//         // gDPSetEnvColor(OVERLAY_DISP++, sRupeeCounterIconEnvColors[CUR_UPG_VALUE(UPG_WALLET)].r,
//         //                sRupeeCounterIconEnvColors[CUR_UPG_VALUE(UPG_WALLET)].g,
//         //                sRupeeCounterIconEnvColors[CUR_UPG_VALUE(UPG_WALLET)].b, 255);
//         gDPSetPrimColor(OVERLAY_DISP++, 0, 0, walletColors[CUR_UPG_VALUE(UPG_WALLET)][0].r,
//                         walletColors[CUR_UPG_VALUE(UPG_WALLET)][0].g,
//                         walletColors[CUR_UPG_VALUE(UPG_WALLET)][0].b, interfaceCtx->magicAlpha);
//         gDPSetEnvColor(OVERLAY_DISP++, walletColors[CUR_UPG_VALUE(UPG_WALLET)][1].r,
//                        walletColors[CUR_UPG_VALUE(UPG_WALLET)][1].g,
//                        walletColors[CUR_UPG_VALUE(UPG_WALLET)][1].b, 255);
//         OVERLAY_DISP =
//             Gfx_DrawTexRectIA8(OVERLAY_DISP, gRupeeCounterIconTex, 16, 16, 26, 206, 16, 16, 1 << 10, 1 << 10);

//         switch (play->sceneId) {
//             case SCENE_INISIE_N:
//             case SCENE_INISIE_R:
//             case SCENE_MITURIN:
//             case SCENE_HAKUGIN:
//             case SCENE_SEA:
//                 if (DUNGEON_KEY_COUNT(gSaveContext.mapIndex) >= 0) {
//                     // Small Key Icon
//                     gDPPipeSync(OVERLAY_DISP++);
//                     gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 200, 230, 255, interfaceCtx->magicAlpha);
//                     gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 20, 255);
//                     OVERLAY_DISP = Gfx_DrawTexRectIA8(OVERLAY_DISP, gSmallKeyCounterIconTex, 16, 16, 26, 190, 16, 16,
//                                                       1 << 10, 1 << 10);

//                     // Small Key Counter
//                     gDPPipeSync(OVERLAY_DISP++);
//                     gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE,
//                                       TEXEL0, 0, PRIMITIVE, 0);

//                     counterDigits[2] = 0;
//                     counterDigits[3] = DUNGEON_KEY_COUNT(gSaveContext.mapIndex);

//                     while (counterDigits[3] >= 10) {
//                         counterDigits[2]++;
//                         counterDigits[3] -= 10;
//                     }

//                     sp2CA = 42;

//                     if (counterDigits[2] != 0) {
//                         gDPPipeSync(OVERLAY_DISP++);
//                         gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, interfaceCtx->magicAlpha);

//                         OVERLAY_DISP =
//                             Gfx_DrawTexRectI8(OVERLAY_DISP, (u8*)gCounterDigit0Tex + (8 * 16 * counterDigits[2]), 8, 16,
//                                               43, 191, 8, 16, 1 << 10, 1 << 10);

//                         gDPPipeSync(OVERLAY_DISP++);
//                         gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->magicAlpha);
//                         gSPTextureRectangle(OVERLAY_DISP++, 168, 760, 200, 824, G_TX_RENDERTILE, 0, 0, 1 << 10,
//                                             1 << 10);

//                         sp2CA += 8;
//                     }

//                     gDPPipeSync(OVERLAY_DISP++);
//                     gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, interfaceCtx->magicAlpha);

//                     OVERLAY_DISP = Gfx_DrawTexRectI8(OVERLAY_DISP, (u8*)gCounterDigit0Tex + (8 * 16 * counterDigits[3]),
//                                                      8, 16, sp2CA + 1, 191, 8, 16, 1 << 10, 1 << 10);

//                     gDPPipeSync(OVERLAY_DISP++);
//                     gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->magicAlpha);
//                     gSPTextureRectangle(OVERLAY_DISP++, sp2CA * 4, 760, (sp2CA * 4) + 0x20, 824, G_TX_RENDERTILE, 0, 0,
//                                         1 << 10, 1 << 10);
//                 }
//                 break;

//             case SCENE_KINSTA1:
//             case SCENE_KINDAN2:
//                 // Gold Skulltula Icon
//                 gDPPipeSync(OVERLAY_DISP++);
//                 gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
//                 gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->magicAlpha);
//                 gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, 255);
//                 gDPLoadTextureBlock(OVERLAY_DISP++, gGoldSkulltulaCounterIconTex, G_IM_FMT_RGBA, G_IM_SIZ_32b, 24, 24,
//                                     0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
//                                     G_TX_NOLOD, G_TX_NOLOD);
//                 gSPTextureRectangle(OVERLAY_DISP++, 80, 748, 176, 820, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

//                 // Gold Skulluta Counter
//                 gDPPipeSync(OVERLAY_DISP++);
//                 gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE,
//                                   TEXEL0, 0, PRIMITIVE, 0);

//                 counterDigits[2] = 0;
//                 counterDigits[3] = Inventory_GetSkullTokenCount(play->sceneId);

//                 while (counterDigits[3] >= 10) {
//                     counterDigits[2]++;
//                     counterDigits[3] -= 10;
//                 }

//                 sp2CA = 42;

//                 if (counterDigits[2] != 0) {
//                     gDPPipeSync(OVERLAY_DISP++);
//                     gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, interfaceCtx->magicAlpha);

//                     OVERLAY_DISP = Gfx_DrawTexRectI8(OVERLAY_DISP, (u8*)gCounterDigit0Tex + (8 * 16 * counterDigits[2]),
//                                                      8, 16, 43, 191, 8, 16, 1 << 10, 1 << 10);

//                     gDPPipeSync(OVERLAY_DISP++);
//                     gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->magicAlpha);
//                     gSPTextureRectangle(OVERLAY_DISP++, 168, 760, 200, 824, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

//                     sp2CA += 8;
//                 }

//                 gDPPipeSync(OVERLAY_DISP++);
//                 gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, interfaceCtx->magicAlpha);

//                 OVERLAY_DISP = Gfx_DrawTexRectI8(OVERLAY_DISP, (u8*)gCounterDigit0Tex + (8 * 16 * counterDigits[3]), 8,
//                                                  16, sp2CA + 1, 191, 8, 16, 1 << 10, 1 << 10);

//                 gDPPipeSync(OVERLAY_DISP++);
//                 gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->magicAlpha);
//                 gSPTextureRectangle(OVERLAY_DISP++, sp2CA * 4, 760, (sp2CA * 4) + 0x20, 824, G_TX_RENDERTILE, 0, 0,
//                                     1 << 10, 1 << 10);
//                 break;

//             default:
//                 break;
//         }

//         // Rupee Counter
//         gDPPipeSync(OVERLAY_DISP++);
//         gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
//                           PRIMITIVE, 0);

//         counterDigits[0] = counterDigits[1] = 0;
//         counterDigits[2] = gSaveContext.save.saveInfo.playerData.rupees;

//         if ((counterDigits[2] > 9999) || (counterDigits[2] < 0)) {
//             counterDigits[2] &= 0xDDD;
//         }

//         while (counterDigits[2] >= 100) {
//             counterDigits[0]++;
//             counterDigits[2] -= 100;
//         }

//         while (counterDigits[2] >= 10) {
//             counterDigits[1]++;
//             counterDigits[2] -= 10;
//         }

//         sp2CC = sRupeeDigitsFirst[CUR_UPG_VALUE(UPG_WALLET)];
//         sp2C8 = sRupeeDigitsCount[CUR_UPG_VALUE(UPG_WALLET)];

//         magicAlpha = interfaceCtx->magicAlpha;
//         if (magicAlpha > 180) {
//             magicAlpha = 180;
//         }

//         for (sp2CE = 0, sp2CA = 42; sp2CE < sp2C8; sp2CE++, sp2CC++, sp2CA += 8) {
//             gDPPipeSync(OVERLAY_DISP++);
//             gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, magicAlpha);

//             OVERLAY_DISP = Gfx_DrawTexRectI8(OVERLAY_DISP, (u8*)gCounterDigit0Tex + (8 * 16 * counterDigits[sp2CC]), 8,
//                                              16, sp2CA + 1, 207, 8, 16, 1 << 10, 1 << 10);

//             gDPPipeSync(OVERLAY_DISP++);

//             if (gSaveContext.save.saveInfo.playerData.rupees == CUR_CAPACITY(UPG_WALLET)) {
//                 gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 120, 255, 0, interfaceCtx->magicAlpha);
//             } else if (gSaveContext.save.saveInfo.playerData.rupees != 0) {
//                 gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->magicAlpha);
//             } else {
//                 gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 100, 100, 100, interfaceCtx->magicAlpha);
//             }

//             gSPTextureRectangle(OVERLAY_DISP++, sp2CA * 4, 824, (sp2CA * 4) + 0x20, 888, G_TX_RENDERTILE, 0, 0, 1 << 10,
//                                 1 << 10);
//         }

//         Magic_DrawMeter(play);
//         Minimap_Draw(play);

//         if ((R_PAUSE_BG_PRERENDER_STATE != 2) && (R_PAUSE_BG_PRERENDER_STATE != 3)) {
//             Target_Draw(&play->actorCtx.targetCtx, play);
//         }

//         Gfx_SetupDL39_Overlay(play->state.gfxCtx);

//         Interface_DrawItemButtons(play);

//         if (player->transformation == GET_PLAYER_FORM) {
//             Interface_DrawBButtonIcons(play);
//         }
//         Interface_DrawCButtonIcons(play);

//         Interface_DrawAButton(play);

//         Interface_DrawPauseMenuEquippingIcons(play);

//         // Draw either the minigame countdown or the three-day clock
//         if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE)) {
//             if ((interfaceCtx->minigameState != MINIGAME_STATE_NONE) &&
//                 (interfaceCtx->minigameState < MINIGAME_STATE_NO_COUNTDOWN_SETUP)) {
//                 // Minigame Countdown
//                 if (((u32)interfaceCtx->minigameState % 2) == 0) {

//                     sp2CE = (interfaceCtx->minigameState >> 1) - 1;
//                     minigameCountdownScale = interfaceCtx->minigameCountdownScale / 100.0f;

//                     if (sp2CE == 3) {
//                         interfaceCtx->actionVtx[40 + 0].v.ob[0] = interfaceCtx->actionVtx[40 + 2].v.ob[0] = -20;
//                         interfaceCtx->actionVtx[40 + 1].v.ob[0] = interfaceCtx->actionVtx[40 + 3].v.ob[0] =
//                             interfaceCtx->actionVtx[40 + 0].v.ob[0] + 40;
//                         interfaceCtx->actionVtx[40 + 1].v.tc[0] = interfaceCtx->actionVtx[40 + 3].v.tc[0] = 40 << 5;
//                     }

//                     interfaceCtx->actionVtx[40 + 2].v.tc[1] = interfaceCtx->actionVtx[40 + 3].v.tc[1] = 32 << 5;

//                     Gfx_SetupDL42_Overlay(play->state.gfxCtx);

//                     gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
//                     gDPSetAlphaCompare(OVERLAY_DISP++, G_AC_THRESHOLD);
//                     gDPSetPrimColor(OVERLAY_DISP++, 0, 0, sMinigameCountdownPrimColors[sp2CE].r,
//                                     sMinigameCountdownPrimColors[sp2CE].g, sMinigameCountdownPrimColors[sp2CE].b,
//                                     interfaceCtx->minigameCountdownAlpha);

//                     Matrix_Translate(0.0f, -40.0f, 0.0f, MTXMODE_NEW);
//                     Matrix_Scale(minigameCountdownScale, minigameCountdownScale, 0.0f, MTXMODE_APPLY);

//                     gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx),
//                               G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
//                     gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[40], 4, 0);

//                     OVERLAY_DISP = Gfx_DrawTexQuadIA8(OVERLAY_DISP, sMinigameCountdownTextures[sp2CE],
//                                                       sMinigameCountdownTexWidths[sp2CE], 32, 0);
//                 }
//             } else {
//                 Interface_DrawClock(play);
//             }
//         }

//         // Draw the letters of minigame perfect
//         if (interfaceCtx->perfectLettersOn) {
//             Interface_DrawPerfectLetters(play);
//         }

//         Interface_DrawMinigameIcons(play);
//         Interface_DrawTimers(play);
//     }

//     // Draw pictograph focus icons
//     if (sPictoState == PICTO_BOX_STATE_LENS) {

//         Gfx_SetupDL39_Overlay(play->state.gfxCtx);

//         gDPSetAlphaCompare(OVERLAY_DISP++, G_AC_THRESHOLD);
//         gDPSetRenderMode(OVERLAY_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
//         gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
//         gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 155, 255);
//         gDPLoadTextureBlock_4b(OVERLAY_DISP++, gPictoBoxFocusBorderTex, G_IM_FMT_IA, 16, 16, 0, G_TX_MIRROR | G_TX_WRAP,
//                                G_TX_MIRROR | G_TX_WRAP, 4, 4, G_TX_NOLOD, G_TX_NOLOD);

//         gSPTextureRectangle(OVERLAY_DISP++, R_PICTO_FOCUS_BORDER_TOPLEFT_X << 2, R_PICTO_FOCUS_BORDER_TOPLEFT_Y << 2,
//                             (R_PICTO_FOCUS_BORDER_TOPLEFT_X << 2) + (16 << 2),
//                             (R_PICTO_FOCUS_BORDER_TOPLEFT_Y << 2) + (16 << 2), G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
//         gSPTextureRectangle(OVERLAY_DISP++, R_PICTO_FOCUS_BORDER_TOPRIGHT_X << 2, R_PICTO_FOCUS_BORDER_TOPRIGHT_Y << 2,
//                             (R_PICTO_FOCUS_BORDER_TOPRIGHT_X << 2) + (16 << 2),
//                             (R_PICTO_FOCUS_BORDER_TOPRIGHT_Y << 2) + (16 << 2), G_TX_RENDERTILE, 512, 0, 1 << 10,
//                             1 << 10);
//         gSPTextureRectangle(
//             OVERLAY_DISP++, R_PICTO_FOCUS_BORDER_BOTTOMLEFT_X << 2, R_PICTO_FOCUS_BORDER_BOTTOMLEFT_Y << 2,
//             (R_PICTO_FOCUS_BORDER_BOTTOMLEFT_X << 2) + (16 << 2), (R_PICTO_FOCUS_BORDER_BOTTOMLEFT_Y << 2) + (16 << 2),
//             G_TX_RENDERTILE, 0, 512, 1 << 10, 1 << 10);
//         gSPTextureRectangle(
//             OVERLAY_DISP++, R_PICTO_FOCUS_BORDER_BOTTOMRIGHT_X << 2, R_PICTO_FOCUS_BORDER_BOTTOMRIGHT_Y << 2,
//             (R_PICTO_FOCUS_BORDER_BOTTOMRIGHT_X << 2) + (16 << 2),
//             (R_PICTO_FOCUS_BORDER_BOTTOMRIGHT_Y << 2) + (16 << 2), G_TX_RENDERTILE, 512, 512, 1 << 10, 1 << 10);

//         gDPLoadTextureBlock_4b(OVERLAY_DISP++, gPictoBoxFocusIconTex, G_IM_FMT_I, 32, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
//                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

//         gSPTextureRectangle(OVERLAY_DISP++, R_PICTO_FOCUS_ICON_X << 2, R_PICTO_FOCUS_ICON_Y << 2,
//                             (R_PICTO_FOCUS_ICON_X << 2) + 0x80, (R_PICTO_FOCUS_ICON_Y << 2) + (16 << 2),
//                             G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

//         gDPLoadTextureBlock_4b(OVERLAY_DISP++, gPictoBoxFocusTextTex, G_IM_FMT_I, 32, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
//                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

//         gSPTextureRectangle(OVERLAY_DISP++, R_PICTO_FOCUS_TEXT_X << 2, R_PICTO_FOCUS_TEXT_Y << 2,
//                             (R_PICTO_FOCUS_TEXT_X << 2) + 0x80, (R_PICTO_FOCUS_TEXT_Y << 2) + 0x20, G_TX_RENDERTILE, 0,
//                             0, 1 << 10, 1 << 10);
//     }

//     // Draw pictograph photo
//     if (sPictoState >= PICTO_BOX_STATE_SETUP_PHOTO) {
//         if (!(play->actorCtx.flags & ACTORCTX_FLAG_PICTO_BOX_ON)) {
//             Play_CompressI8ToI5((play->pictoPhotoI8 != NULL) ? play->pictoPhotoI8 : gWorkBuffer,
//                                 (u8*)gSaveContext.pictoPhotoI5, PICTO_PHOTO_WIDTH * PICTO_PHOTO_HEIGHT);

//             interfaceCtx->unk_222 = interfaceCtx->unk_224 = 0;

//             sPictoState = PICTO_BOX_STATE_OFF;
//             gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
//             Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
//         } else {
//             s16 pictoRectTop;
//             s16 pictoRectLeft;

//             if (sPictoState == PICTO_BOX_STATE_SETUP_PHOTO) {
//                 sPictoState = PICTO_BOX_STATE_PHOTO;
//                 Message_StartTextbox(play, 0xF8, NULL);
//                 Interface_SetHudVisibility(HUD_VISIBILITY_NONE);
//                 player->stateFlags1 |= PLAYER_STATE1_200;
//             }

//             gDPPipeSync(OVERLAY_DISP++);
//             gDPSetRenderMode(OVERLAY_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
//             gDPSetCombineMode(OVERLAY_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
//             gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 200, 200, 200, 250);
//             gDPFillRectangle(OVERLAY_DISP++, 70, 22, 251, 151);

//             Gfx_SetupDL39_Overlay(play->state.gfxCtx);

//             gDPSetRenderMode(OVERLAY_DISP++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
//             gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM);
//             gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 250, 160, 160, 255);

//             // Picture is offset up by 33 pixels to give room for the message box at the bottom
//             pictoRectTop = PICTO_PHOTO_TOPLEFT_Y - 33;
//             for (sp2CC = 0; sp2CC < (PICTO_PHOTO_HEIGHT / 8); sp2CC++, pictoRectTop += 8) {
//                 pictoRectLeft = PICTO_PHOTO_TOPLEFT_X;
//                 gDPLoadTextureBlock(OVERLAY_DISP++,
//                                     (u8*)((play->pictoPhotoI8 != NULL) ? play->pictoPhotoI8 : gWorkBuffer) +
//                                         (0x500 * sp2CC),
//                                     G_IM_FMT_I, G_IM_SIZ_8b, PICTO_PHOTO_WIDTH, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
//                                     G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

//                 gSPTextureRectangle(OVERLAY_DISP++, pictoRectLeft << 2, pictoRectTop << 2,
//                                     (pictoRectLeft + PICTO_PHOTO_WIDTH) << 2, (pictoRectTop << 2) + (8 << 2),
//                                     G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
//             }
//         }
//     }

//     // Draw over the entire screen (used in gameover)
//     if (interfaceCtx->screenFillAlpha != 0) {
//         gDPPipeSync(OVERLAY_DISP++);
//         gSPDisplayList(OVERLAY_DISP++, sScreenFillSetupDL);
//         gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, interfaceCtx->screenFillAlpha);
//         gSPDisplayList(OVERLAY_DISP++, D_0E000000.fillRect);
//     }

//     CLOSE_DISPS(play->state.gfxCtx);
// }

// // map recolors
// // note: with the current syms this is not editable

// // extern Color_RGBA8 sMapColorTable[];

// // RECOMP_PATCH void MapData_GetMapColor(s32 colorIndex, Color_RGBA8* color) {
// //     // *color = sMapColorTable[colorIndex];
// //     Color_RGBA8 mapRecolor = {mapColor.r, mapColor.g, mapColor.b, sMapColorTable[colorIndex].a};
// //     *color = mapRecolor;
// // }

// // void MapDisp_Minimap_DrawActorIcon(PlayState* play, Actor* actor) {
// //     MapDataRoom* mapDataRoom;
// //     s32 posX;
// //     s32 posY;
// //     s32 texOffsetX;
// //     s32 texOffsetY;
// //     s32 texWidth;
// //     s32 texHeight;
// //     f32 scaleFrac;
// //     f32 unused1;
// //     f32 unused2;
// //     Player* player = GET_PLAYER(play);
// //     s32 scale;

// //     // inferred from `MapDisp_Minimap_DrawDoorActor`
// //     unused1 = fabsf(player->actor.world.pos.y - actor->world.pos.y);
// //     unused2 = 1.0f - (1 / 350.0f) * unused1;

// //     if (unused2 < 0.0f) {
// //         unused2 = 0.0f;
// //     }

// //     mapDataRoom = &sMapDisp.mapDataScene->rooms[sMapDisp.curRoom];
// //     if (mapDataRoom->mapId == MAP_DATA_NO_MAP) {
// //         return;
// //     }

// //     MapDisp_GetMapOffset(mapDataRoom, &texOffsetX, &texOffsetY);
// //     MapDisp_GetMapTexDim(mapDataRoom, &texWidth, &texHeight);

// //     scale = sMapDisp.mapDataScene->scale;
// //     if (sMapDisp.mapDataScene->scale == 0) {
// //         scale = 20;
// //     } else if (sMapDisp.mapDataScene->scale == -1) {
// //         s32 scaleTemp;

// //         MapDisp_GetMapScale(mapDataRoom, &scaleTemp);
// //         scale = scaleTemp;
// //     }

// //     scaleFrac = 1.0f / scale;
// //     if (!MapDisp_IsDataRotated(play)) {
// //         posX = (s32)((actor->world.pos.x - mapDataRoom->centerX) * scaleFrac) + sMapDisp.minimapBaseX +
// //                sMapDisp.minimapCurX - sMapDisp.minimapBaseX + texOffsetX;
// //         posY = (s32)((actor->world.pos.z - mapDataRoom->centerZ) * scaleFrac) + sMapDisp.minimapBaseY +
// //                sMapDisp.minimapCurY - sMapDisp.minimapBaseY + texOffsetY;
// //     } else {
// //         posX = -(s32)((actor->world.pos.x - mapDataRoom->centerX) * scaleFrac) + sMapDisp.minimapBaseX +
// //                sMapDisp.minimapCurX - sMapDisp.minimapBaseX + texOffsetX;
// //         posY = -(s32)((actor->world.pos.z - mapDataRoom->centerZ) * scaleFrac) + sMapDisp.minimapBaseY +
// //                sMapDisp.minimapCurY - sMapDisp.minimapBaseY + texOffsetY;
// //     }

// //     if ((posX > 0) && (posX < 0x3FF) && (posY > 0) && (posY < 0x3FF)) {
// //         OPEN_DISPS(play->state.gfxCtx);

// //         if ((actor->category == ACTORCAT_PLAYER) && (actor->flags & ACTOR_FLAG_80000000)) {
// //             s16 compassRot;

// //             Gfx_SetupDL42_Overlay(play->state.gfxCtx);
// //             gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
// //             gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
// //                               PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
// //             gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, play->interfaceCtx.minimapAlpha);
// //             gDPSetCombineMode(OVERLAY_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
// //             gDPSetRenderMode(OVERLAY_DISP++, G_RM_AA_DEC_LINE, G_RM_NOOP2);

// //             Matrix_Translate(posX - 160.0f, 120.0f - posY, 0.0f, MTXMODE_NEW);
// //             Matrix_RotateXFApply(-1.6f);
// //             compassRot = (s32)(0x7FFF - actor->focus.rot.y) / 1024;
// //             if (MapDisp_IsDataRotated(play)) {
// //                 compassRot += 0x7FFF;
// //             }
// //             Matrix_RotateYF(compassRot / 10.0f, MTXMODE_APPLY);
// //             Matrix_Scale(0.4f, 0.4f, 0.4f, MTXMODE_APPLY);
// //             MATRIX_FINALIZE_AND_LOAD(OVERLAY_DISP++, play->state.gfxCtx);
// //             // gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 200, 255, 0, play->interfaceCtx.minimapAlpha);
// //             gDPSetPrimColor(OVERLAY_DISP++, 0, 0, mapPlayerColor.r, mapPlayerColor.g, mapPlayerColor.b, play->interfaceCtx.minimapAlpha);
// //             gSPDisplayList(OVERLAY_DISP++, gCompassArrowDL);
// //         } else if ((actor->id == ACTOR_EN_BOX) && !Flags_GetTreasure(play, actor->params & 0x1F) &&
// //                    (MapDisp_GetStoreyY(player->actor.world.pos.y) == MapDisp_GetStoreyY(actor->world.pos.y))) {
// //             Gfx_SetupDL39_Overlay(play->state.gfxCtx);
// //             gDPPipeSync(OVERLAY_DISP++);
// //             gDPSetTextureLUT(OVERLAY_DISP++, G_TT_NONE);
// //             gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, play->interfaceCtx.minimapAlpha);
// //             gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, play->interfaceCtx.minimapAlpha);
// //             gDPPipeSync(OVERLAY_DISP++);

// //             gDPLoadTextureBlock_Runtime(OVERLAY_DISP++, gMapChestIconTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0,
// //                                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
// //                                         G_TX_NOLOD, G_TX_NOLOD);

// //             gSPTextureRectangle(OVERLAY_DISP++, (posX - 4) << 2, (posY - 4) << 2, (posX + 4) << 2, (posY + 4) << 2,
// //                                 G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
// //         } else {
// //             Gfx_SetupDL39_Overlay(play->state.gfxCtx);
// //             gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
// //             if (actor->flags & ACTOR_FLAG_80000000) {
// //                 gDPSetPrimColor(OVERLAY_DISP++, 0, 0, sMinimapActorCategoryColors[actor->category].r,
// //                                 sMinimapActorCategoryColors[actor->category].g,
// //                                 sMinimapActorCategoryColors[actor->category].b, play->interfaceCtx.minimapAlpha);
// //                 gSPTextureRectangle(OVERLAY_DISP++, (posX - 1) << 2, (posY - 1) << 2, (posX + 1) << 2, (posY + 1) << 2,
// //                                     G_TX_RENDERTILE, 0, 0, 0x0001, 0x0001);
// //             }
// //         }
// //         CLOSE_DISPS(play->state.gfxCtx);
// //     }
// // }

// // void MapDisp_Minimap_DrawRedCompassIcon(PlayState* play, s32 x, s32 z, s32 rot) {
// //     MapDataRoom* mapDataRoom;
// //     s32 posX;
// //     s32 posY;
// //     s32 texOffsetX;
// //     s32 texOffsetY;
// //     s32 texWidth;
// //     s32 texHeight;
// //     s32 scale;
// //     f32 scaleFrac;

// //     mapDataRoom = &sMapDisp.mapDataScene->rooms[sMapDisp.curRoom];
// //     if (mapDataRoom->mapId == MAP_DATA_NO_MAP) {
// //         return;
// //     }

// //     MapDisp_GetMapOffset(mapDataRoom, &texOffsetX, &texOffsetY);
// //     MapDisp_GetMapTexDim(mapDataRoom, &texWidth, &texHeight);
// //     scale = sMapDisp.mapDataScene->scale;

// //     if (sMapDisp.mapDataScene->scale == 0) {
// //         scale = 20;
// //     } else if (sMapDisp.mapDataScene->scale == -1) {
// //         s32 scaleTemp;

// //         MapDisp_GetMapScale(mapDataRoom, &scaleTemp);
// //         scale = scaleTemp;
// //     }

// //     scaleFrac = 1.0f / scale;
// //     if (!MapDisp_IsDataRotated(play)) {
// //         posX = (s32)((x - (f32)mapDataRoom->centerX) * scaleFrac) + sMapDisp.minimapBaseX +
// //                (sMapDisp.minimapCurX - sMapDisp.minimapBaseX) + texOffsetX;
// //         posY = (s32)((z - (f32)mapDataRoom->centerZ) * scaleFrac) + sMapDisp.minimapBaseY +
// //                (sMapDisp.minimapCurY - sMapDisp.minimapBaseY) + texOffsetY;
// //     } else {
// //         posX = -(s32)((x - (f32)mapDataRoom->centerX) * scaleFrac) + sMapDisp.minimapBaseX +
// //                (sMapDisp.minimapCurX - sMapDisp.minimapBaseX) + texOffsetX;
// //         posY = -(s32)((z - (f32)mapDataRoom->centerZ) * scaleFrac) + sMapDisp.minimapBaseY +
// //                (sMapDisp.minimapCurY - sMapDisp.minimapBaseY) + texOffsetY;
// //     }

// //     if ((posX > 0) && (posX < 0x3FF) && (posY > 0) && (posY < 0x3FF)) {
// //         OPEN_DISPS(play->state.gfxCtx);

// //         Gfx_SetupDL42_Overlay(play->state.gfxCtx);
// //         gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
// //         gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
// //                           PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
// //         gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, 255);
// //         gDPSetCombineMode(OVERLAY_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
// //         gDPSetRenderMode(OVERLAY_DISP++, G_RM_AA_DEC_LINE, G_RM_NOOP2);
// //         Matrix_Translate(posX - 160.0f, 120.0f - posY, 0.0f, MTXMODE_NEW);
// //         Matrix_RotateXFApply(-1.6f);
// //         if (MapDisp_IsDataRotated(play)) {
// //             rot += 0x7FFF;
// //         }
// //         Matrix_RotateYF(rot / 10.0f, MTXMODE_APPLY);
// //         Matrix_Scale(0.4f, 0.4f, 0.4f, MTXMODE_APPLY);
// //         MATRIX_FINALIZE_AND_LOAD(OVERLAY_DISP++, play->state.gfxCtx);
// //         // gDPSetPrimColor(OVERLAY_DISP++, 0, 255, 200, 0, 0, play->interfaceCtx.minimapAlpha);
// //         gDPSetPrimColor(OVERLAY_DISP++, 0, 255, mapEntranceColor.r, mapEntranceColor.g, mapEntranceColor.b, play->interfaceCtx.minimapAlpha);
// //         gSPDisplayList(OVERLAY_DISP++, gCompassArrowDL);

// //         CLOSE_DISPS(play->state.gfxCtx);
// //     }
// // }