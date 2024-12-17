#include "modding.h"
#include "global.h"

#include "recolor.h"

extern s16 sHeartsPrimColors[3][3];
extern s16 sHeartsEnvColors[3][3];
extern s16 sHeartsPrimFactors[3][3];
extern s16 sHeartsEnvFactors[3][3];
extern s16 sHeartsDDPrimColors[3][3];
extern s16 sHeartsDDEnvColors[3][3];
extern s16 sHeartsDDPrimFactors[3][3];
extern s16 sHeartsDDEnvFactors[3][3];

extern s16 sBeatingHeartsDDPrim[3];
extern s16 sBeatingHeartsDDEnv[3];
extern s16 sHeartsDDPrim[2][3];
extern s16 sHeartsDDEnv[2][3];

RECOMP_PATCH void LifeMeter_UpdateColors(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    f32 factorBeating = interfaceCtx->lifeColorChange * 0.1f;
    f32 ddFactor;
    s32 type = 0;
    s32 ddType;
    s16 rFactor;
    s16 gFactor;
    s16 bFactor;

    if (interfaceCtx) {}

    if (interfaceCtx->lifeColorChangeDirection != 0) {
        interfaceCtx->lifeColorChange--;
        if (interfaceCtx->lifeColorChange <= 0) {
            interfaceCtx->lifeColorChange = 0;
            interfaceCtx->lifeColorChangeDirection = 0;
        }
    } else {
        interfaceCtx->lifeColorChange++;
        if (interfaceCtx->lifeColorChange >= 10) {
            interfaceCtx->lifeColorChange = 10;
            interfaceCtx->lifeColorChangeDirection = 1;
        }
    }

    ddFactor = factorBeating;

    // interfaceCtx->heartsPrimR[0] = 255;
    // interfaceCtx->heartsPrimG[0] = 70;
    // interfaceCtx->heartsPrimB[0] = 50;
    interfaceCtx->heartsPrimR[0] = heartColor.r;
    interfaceCtx->heartsPrimG[0] = heartColor.g;
    interfaceCtx->heartsPrimB[0] = heartColor.b;

    // interfaceCtx->heartsEnvR[0] = 50;
    // interfaceCtx->heartsEnvG[0] = 40;
    // interfaceCtx->heartsEnvB[0] = 60;
    interfaceCtx->heartsEnvR[0] = heartBackgroundColor.r;
    interfaceCtx->heartsEnvG[0] = heartBackgroundColor.g;
    interfaceCtx->heartsEnvB[0] = heartBackgroundColor.b;

    interfaceCtx->heartsPrimR[1] = sHeartsPrimColors[type][0];
    interfaceCtx->heartsPrimG[1] = sHeartsPrimColors[type][1];
    interfaceCtx->heartsPrimB[1] = sHeartsPrimColors[type][2];

    interfaceCtx->heartsEnvR[1] = sHeartsEnvColors[type][0];
    interfaceCtx->heartsEnvG[1] = sHeartsEnvColors[type][1];
    interfaceCtx->heartsEnvB[1] = sHeartsEnvColors[type][2];

    rFactor = sHeartsPrimFactors[0][0] * factorBeating;
    gFactor = sHeartsPrimFactors[0][1] * factorBeating;
    bFactor = sHeartsPrimFactors[0][2] * factorBeating;

    // interfaceCtx->beatingHeartPrim[0] = (u8)(rFactor + 255) & 0xFF;
    // interfaceCtx->beatingHeartPrim[1] = (u8)(gFactor + 70) & 0xFF;
    // interfaceCtx->beatingHeartPrim[2] = (u8)(bFactor + 50) & 0xFF;
    interfaceCtx->beatingHeartPrim[0] = (u8)(rFactor + heartColor.r) & 0xFF;
    interfaceCtx->beatingHeartPrim[1] = (u8)(gFactor + heartColor.g) & 0xFF;
    interfaceCtx->beatingHeartPrim[2] = (u8)(bFactor + heartColor.b) & 0xFF;

    rFactor = sHeartsEnvFactors[0][0] * factorBeating;
    gFactor = sHeartsEnvFactors[0][1] * factorBeating;
    bFactor = sHeartsEnvFactors[0][2] * factorBeating;

    if (1) {}
    ddType = type;

    // interfaceCtx->beatingHeartEnv[0] = (u8)(rFactor + 50) & 0xFF;
    // interfaceCtx->beatingHeartEnv[1] = (u8)(gFactor + 40) & 0xFF;
    // interfaceCtx->beatingHeartEnv[2] = (u8)(bFactor + 60) & 0xFF;
    interfaceCtx->beatingHeartEnv[0] = (u8)(rFactor + heartBackgroundColor.r) & 0xFF;
    interfaceCtx->beatingHeartEnv[1] = (u8)(gFactor + heartBackgroundColor.g) & 0xFF;
    interfaceCtx->beatingHeartEnv[2] = (u8)(bFactor + heartBackgroundColor.b) & 0xFF;

    // note: double defense acts differently from regular hearts for some reason

    // sHeartsDDPrim[0][0] = 255;
    // sHeartsDDPrim[0][1] = 255;
    // sHeartsDDPrim[0][2] = 255;
    sHeartsDDPrim[0][0] = heartDDBackgroundColor.r;
    sHeartsDDPrim[0][1] = heartDDBackgroundColor.g;
    sHeartsDDPrim[0][2] = heartDDBackgroundColor.b;

    // sHeartsDDEnv[0][0] = 200;
    // sHeartsDDEnv[0][1] = 0;
    // sHeartsDDEnv[0][2] = 0;
    sHeartsDDEnv[0][0] = heartDDColor.r;
    sHeartsDDEnv[0][1] = heartDDColor.g;
    sHeartsDDEnv[0][2] = heartDDColor.b;

    sHeartsDDPrim[1][0] = sHeartsDDPrimColors[ddType][0];
    sHeartsDDPrim[1][1] = sHeartsDDPrimColors[ddType][1];
    sHeartsDDPrim[1][2] = sHeartsDDPrimColors[ddType][2];

    sHeartsDDEnv[1][0] = sHeartsDDEnvColors[ddType][0];
    sHeartsDDEnv[1][1] = sHeartsDDEnvColors[ddType][1];
    sHeartsDDEnv[1][2] = sHeartsDDEnvColors[ddType][2];

    rFactor = sHeartsDDPrimFactors[ddType][0] * ddFactor;
    gFactor = sHeartsDDPrimFactors[ddType][1] * ddFactor;
    bFactor = sHeartsDDPrimFactors[ddType][2] * ddFactor;

    // sBeatingHeartsDDPrim[0] = (u8)(rFactor + 255) & 0xFF;
    // sBeatingHeartsDDPrim[1] = (u8)(gFactor + 255) & 0xFF;
    // sBeatingHeartsDDPrim[2] = (u8)(bFactor + 255) & 0xFF;
    sBeatingHeartsDDPrim[0] = (u8)(rFactor + heartDDBackgroundColor.r) & 0xFF;
    sBeatingHeartsDDPrim[1] = (u8)(gFactor + heartDDBackgroundColor.g) & 0xFF;
    sBeatingHeartsDDPrim[2] = (u8)(bFactor + heartDDBackgroundColor.b) & 0xFF;

    rFactor = sHeartsDDEnvFactors[ddType][0] * ddFactor;
    gFactor = sHeartsDDEnvFactors[ddType][1] * ddFactor;
    bFactor = sHeartsDDEnvFactors[ddType][2] * ddFactor;

    // sBeatingHeartsDDEnv[0] = (u8)(rFactor + 200) & 0xFF;
    // sBeatingHeartsDDEnv[1] = (u8)(gFactor + 0) & 0xFF;
    // sBeatingHeartsDDEnv[2] = (u8)(bFactor + 0) & 0xFF;
    sBeatingHeartsDDEnv[0] = (u8)(rFactor + heartDDColor.r) & 0xFF;
    sBeatingHeartsDDEnv[1] = (u8)(gFactor + heartDDColor.g) & 0xFF;
    sBeatingHeartsDDEnv[2] = (u8)(bFactor + heartDDColor.b) & 0xFF;
}

extern u64 gameplay_keep_Tex_0447B0[];
extern u64 gameplay_keep_Tex_044BB0[];
extern Vtx object_gi_heartsVtx_000000[];

Gfx gGiHeartContainerDL[] = {
    gsDPSetPrimColor(0, 0x80, 255, 0, 100, 255),
    // gsDPSetPrimColor(0, 0x80, heartColor.r, heartColor.g, heartColor.b, 255),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, PRIMITIVE,
                       ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetEnvColor(100, 0, 50, 255),
    // gsDPSetEnvColor(heartColor.r, heartColor.g, heartColor.b, 255), // unsure what these will be set to later
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0x0FA0, 0x0FA0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(gameplay_keep_Tex_0447B0, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 4, 0x0000, 1, 0, G_TX_NOMIRROR | G_TX_WRAP, 5, 15, G_TX_NOMIRROR | G_TX_WRAP,
                5, 15),
    gsDPSetTileSize(1, 0, 0, 0x007C, 0x007C),
    gsSPClearGeometryMode(G_CULL_BACK | G_FOG),
    gsSPSetGeometryMode(G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPVertex(&object_gi_heartsVtx_000000[160], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_gi_heartsVtx_000000[163], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 4, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 8, 9, 0),
    gsSP2Triangles(9, 10, 11, 0, 11, 12, 13, 0),
    gsSP2Triangles(13, 14, 15, 0, 15, 16, 17, 0),
    gsSP2Triangles(17, 18, 19, 0, 19, 20, 21, 0),
    gsSP2Triangles(21, 22, 23, 0, 24, 25, 26, 0),
    gsSP2Triangles(27, 28, 24, 0, 29, 30, 27, 0),
    gsSPVertex(&object_gi_heartsVtx_000000[194], 20, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 0, 0),
    gsSP2Triangles(5, 6, 3, 0, 7, 8, 5, 0),
    gsSP2Triangles(9, 10, 7, 0, 11, 12, 13, 0),
    gsSP2Triangles(14, 15, 11, 0, 16, 17, 14, 0),
    gsSP1Triangle(18, 19, 16, 0),
    gsSPEndDisplayList(),
};

Gfx gGiHeartPieceDL[] = {
    gsDPSetPrimColor(0, 0x80, 255, 0, 100, 255),
    // gsDPSetPrimColor(0, 0x80, heartColor.r, heartColor.g, heartColor.b, 255),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, PRIMITIVE,
                       ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetEnvColor(100, 0, 50, 255),
    // gsDPSetEnvColor(heartColor.r, heartColor.g, heartColor.b, 255), // unsure what these will be set to later
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0x0FA0, 0x0FA0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(gameplay_keep_Tex_0447B0, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadMultiBlock(gameplay_keep_Tex_044BB0, 0x0100, 1, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR |
                       G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 15, 15),
    gsSPClearGeometryMode(G_CULL_BACK | G_FOG),
    gsSPSetGeometryMode(G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPVertex(&object_gi_heartsVtx_000000[214], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_gi_heartsVtx_000000[217], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 4, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 8, 9, 0),
    gsSP2Triangles(10, 11, 12, 0, 12, 13, 14, 0),
    gsSP2Triangles(14, 15, 16, 0, 16, 17, 18, 0),
    gsSP2Triangles(18, 19, 20, 0, 20, 21, 22, 0),
    gsSP2Triangles(23, 24, 25, 0, 26, 27, 23, 0),
    gsSP2Triangles(28, 29, 26, 0, 30, 31, 28, 0),
    gsSPVertex(&object_gi_heartsVtx_000000[249], 21, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 0, 0),
    gsSP2Triangles(5, 6, 3, 0, 7, 8, 5, 0),
    gsSP2Triangles(9, 10, 11, 0, 12, 13, 9, 0),
    gsSP2Triangles(14, 15, 12, 0, 16, 17, 14, 0),
    gsSP1Triangle(18, 19, 20, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL1, PRIMITIVE, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, PRIMITIVE,
                       ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetPrimColor(0, 0x80, 170, 255, 255, 255),
    gsDPSetEnvColor(0, 100, 255, 255),
    gsSPTexture(0x0DAC, 0x0DAC, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(gameplay_keep_Tex_044BB0, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_gi_heartsVtx_000000[270], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_gi_heartsVtx_000000[273], 24, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 2, 4, 0),
    gsSP2Triangles(4, 5, 6, 0, 5, 7, 8, 0),
    gsSP2Triangles(9, 8, 10, 0, 10, 11, 12, 0),
    gsSP2Triangles(13, 12, 14, 0, 15, 13, 16, 0),
    gsSP2Triangles(16, 17, 18, 0, 17, 19, 20, 0),
    gsSP2Triangles(21, 22, 19, 0, 22, 21, 1, 0),
    gsSP2Triangles(2, 3, 0, 0, 4, 23, 3, 0),
    gsSP2Triangles(6, 23, 4, 0, 8, 6, 5, 0),
    gsSP2Triangles(7, 10, 8, 0, 12, 9, 10, 0),
    gsSP2Triangles(11, 14, 12, 0, 14, 16, 13, 0),
    gsSP2Triangles(18, 15, 16, 0, 20, 18, 17, 0),
    gsSP1Triangle(20, 19, 22, 0),
    gsSPEndDisplayList(),
};