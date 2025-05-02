#include "modding.h"
#include "global.h"

typedef enum LinkDekuLimb {
    /* 0x00 */ LINK_DEKU_LIMB_NONE,
    /* 0x01 */ LINK_DEKU_LIMB_ROOT,
    /* 0x02 */ LINK_DEKU_LIMB_WAIST,
    /* 0x03 */ LINK_DEKU_LIMB_LOWER_ROOT,
    /* 0x04 */ LINK_DEKU_LIMB_RIGHT_THIGH,
    /* 0x05 */ LINK_DEKU_LIMB_RIGHT_SHIN,
    /* 0x06 */ LINK_DEKU_LIMB_RIGHT_FOOT,
    /* 0x07 */ LINK_DEKU_LIMB_LEFT_THIGH,
    /* 0x08 */ LINK_DEKU_LIMB_LEFT_SHIN,
    /* 0x09 */ LINK_DEKU_LIMB_LEFT_FOOT,
    /* 0x0A */ LINK_DEKU_LIMB_UPPER_ROOT,
    /* 0x0B */ LINK_DEKU_LIMB_HEAD,
    /* 0x0C */ LINK_DEKU_LIMB_HAT,
    /* 0x0D */ LINK_DEKU_LIMB_COLLAR,
    /* 0x0E */ LINK_DEKU_LIMB_LEFT_SHOULDER,
    /* 0x0F */ LINK_DEKU_LIMB_LEFT_FOREARM,
    /* 0x10 */ LINK_DEKU_LIMB_LEFT_HAND,
    /* 0x11 */ LINK_DEKU_LIMB_RIGHT_SHOULDER,
    /* 0x12 */ LINK_DEKU_LIMB_RIGHT_FOREARM,
    /* 0x13 */ LINK_DEKU_LIMB_RIGHT_HAND,
    /* 0x14 */ LINK_DEKU_LIMB_SHEATH,
    /* 0x15 */ LINK_DEKU_LIMB_TORSO,
    /* 0x16 */ LINK_DEKU_LIMB_MAX
} LinkDekuLimb;

extern Vtx object_link_nutsVtx_000000[];
extern u64 object_link_nuts_TLUT_003EB0[];
extern u64 object_link_nuts_Tex_0042B0[];
extern u64 object_link_nuts_Tex_0043B0[];
extern u64 object_link_nuts_Tex_0044B0[];
extern u64 object_link_nuts_Tex_0048B0[];

u64 savedLink_005C40[32];

Gfx gLinkDekuWaistModifiedDL[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal256(object_link_nuts_TLUT_003EB0),
    gsDPLoadTextureBlock(object_link_nuts_Tex_0042B0, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPDisplayList(0x0C000000),
    gsSPVertex(&object_link_nutsVtx_000000[132], 18, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 0, 2, 0, 6, 7, 0, 0),
    gsSP2Triangles(8, 9, 10, 0, 11, 3, 5, 0),
    gsSP2Triangles(8, 3, 11, 0, 5, 12, 13, 0),
    gsSP2Triangles(13, 12, 10, 0, 10, 9, 13, 0),
    gsSP2Triangles(11, 9, 8, 0, 14, 7, 15, 0),
    gsSP2Triangles(10, 16, 15, 0, 0, 7, 14, 0),
    gsSP2Triangles(10, 1, 17, 0, 17, 1, 0, 0),
    gsSP2Triangles(17, 16, 10, 0, 15, 16, 14, 0),
    gsDPPipeSync(),
    // gsDPLoadTLUT_pal256(object_link_nuts_TLUT_003EB0),
    // gsDPLoadTextureBlock(object_link_nuts_Tex_0043B0, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
    //                      G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(savedLink_005C40, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 0, 181, 57, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_nutsVtx_000000[150], 14, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 5, 0, 0, 5, 1, 0, 0),
    gsSP2Triangles(6, 7, 4, 0, 7, 5, 4, 0),
    gsSP2Triangles(6, 8, 7, 0, 9, 8, 6, 0),
    gsSP2Triangles(10, 11, 9, 0, 10, 9, 6, 0),
    gsSP2Triangles(12, 11, 10, 0, 12, 13, 11, 0),
    gsSP2Triangles(2, 13, 12, 0, 2, 3, 13, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkDekuHeadModifiedDL[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal256(object_link_nuts_TLUT_003EB0),
    gsDPLoadTextureBlock(object_link_nuts_Tex_0044B0, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_nutsVtx_000000[210], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
    gsSP2Triangles(8, 9, 10, 0, 10, 9, 11, 0),
    gsSP2Triangles(12, 0, 2, 0, 13, 6, 7, 0),
    gsSP2Triangles(14, 15, 16, 0, 15, 17, 16, 0),
    gsSP2Triangles(18, 17, 19, 0, 17, 15, 19, 0),
    gsSP2Triangles(15, 14, 19, 0, 20, 21, 22, 0),
    gsSP2Triangles(20, 23, 21, 0, 20, 22, 24, 0),
    gsSP2Triangles(25, 21, 23, 0, 25, 22, 21, 0),
    gsSP2Triangles(26, 27, 13, 0, 28, 29, 12, 0),
    gsSP2Triangles(27, 26, 30, 0, 27, 30, 31, 0),
    gsSPVertex(&object_link_nutsVtx_000000[242], 11, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 8, 9, 0),
    gsSP1Triangle(9, 8, 10, 0),
    gsDPPipeSync(),
    // gsDPLoadTLUT_pal256(object_link_nuts_TLUT_003EB0),
    // gsDPLoadTextureBlock(object_link_nuts_Tex_0043B0, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
    //                      G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(savedLink_005C40, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPDisplayList(0x0C000000),
    gsSPVertex(&object_link_nutsVtx_000000[253], 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(4, 6, 5, 0, 6, 7, 8, 0),
    gsSP2Triangles(7, 1, 8, 0, 3, 9, 10, 0),
    gsSP2Triangles(7, 2, 1, 0, 6, 11, 7, 0),
    gsSP2Triangles(4, 11, 6, 0, 10, 4, 3, 0),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_link_nuts_Tex_0048B0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_NOMIRROR |
                         G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
    gsSPDisplayList(0x0C000000),
    gsSPVertex(&object_link_nutsVtx_000000[265], 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP2Triangles(4, 3, 2, 0, 2, 5, 4, 0),
    gsSP2Triangles(6, 5, 2, 0, 1, 6, 2, 0),
    gsSP2Triangles(7, 6, 1, 0, 7, 8, 6, 0),
    gsSP2Triangles(9, 8, 7, 0, 7, 10, 9, 0),
    gsSP2Triangles(7, 11, 10, 0, 7, 1, 11, 0),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal256(object_link_nuts_TLUT_003EB0),
    gsDPLoadTextureBlock(object_link_nuts_Tex_0042B0, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPDisplayList(0x0C000000),
    gsSPVertex(&object_link_nutsVtx_000000[277], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(0, 4, 3, 0, 3, 5, 1, 0),
    gsSP2Triangles(5, 6, 1, 0, 0, 7, 4, 0),
    gsSP2Triangles(8, 9, 10, 0, 9, 11, 10, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 15, 13, 0),
    gsSP2Triangles(10, 16, 17, 0, 10, 11, 16, 0),
    gsSP2Triangles(16, 18, 17, 0, 18, 19, 17, 0),
    gsSP2Triangles(20, 18, 21, 0, 20, 19, 18, 0),
    gsSP2Triangles(20, 21, 22, 0, 21, 23, 22, 0),
    gsSP2Triangles(22, 24, 25, 0, 22, 23, 24, 0),
    gsSP2Triangles(24, 13, 25, 0, 13, 15, 25, 0),
    gsSP2Triangles(26, 27, 28, 0, 29, 30, 31, 0),
    gsSPVertex(&object_link_nutsVtx_000000[309], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 1, 7, 0, 8, 9, 7, 0),
    gsSP2Triangles(10, 11, 5, 0, 12, 13, 14, 0),
    gsSP2Triangles(15, 7, 9, 0, 9, 16, 15, 0),
    gsSP2Triangles(14, 5, 12, 0, 12, 17, 13, 0),
    gsSP2Triangles(16, 18, 15, 0, 19, 12, 5, 0),
    gsSP2Triangles(20, 7, 15, 0, 21, 20, 15, 0),
    gsSP2Triangles(19, 22, 12, 0, 12, 22, 17, 0),
    gsSP2Triangles(23, 24, 25, 0, 23, 17, 26, 0),
    gsSP2Triangles(27, 18, 28, 0, 27, 29, 30, 0),
    gsSP2Triangles(25, 17, 23, 0, 30, 18, 27, 0),
    gsSP2Triangles(28, 29, 27, 0, 26, 24, 23, 0),
    gsSPVertex(&object_link_nutsVtx_000000[340], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 5, 9, 3, 0),
    gsSP2Triangles(10, 11, 2, 0, 12, 13, 14, 0),
    gsSP2Triangles(15, 6, 8, 0, 3, 16, 4, 0),
    gsSP2Triangles(2, 11, 0, 0, 0, 17, 1, 0),
    gsSP2Triangles(2, 4, 10, 0, 4, 16, 10, 0),
    gsSP2Triangles(18, 19, 20, 0, 21, 22, 23, 0),
    gsSP2Triangles(24, 25, 26, 0, 27, 28, 18, 0),
    gsSP2Triangles(29, 30, 31, 0, 19, 28, 29, 0),
    gsSP2Triangles(23, 19, 29, 0, 19, 18, 28, 0),
    gsSP1Triangle(30, 28, 27, 0),
    gsSPVertex(&object_link_nutsVtx_000000[372], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 0, 7, 0, 8, 9, 10, 0),
    gsSP2Triangles(11, 12, 13, 0, 14, 4, 3, 0),
    gsSP2Triangles(5, 4, 0, 0, 1, 15, 2, 0),
    gsSP2Triangles(16, 17, 18, 0, 19, 20, 21, 0),
    gsSP2Triangles(22, 23, 24, 0, 25, 26, 27, 0),
    gsSP2Triangles(2, 28, 23, 0, 28, 24, 23, 0),
    gsSP2Triangles(24, 19, 29, 0, 25, 30, 22, 0),
    gsSP2Triangles(22, 24, 29, 0, 30, 23, 22, 0),
    gsSP2Triangles(3, 5, 31, 0, 19, 24, 28, 0),
    gsSPVertex(&object_link_nutsVtx_000000[404], 18, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 15, 16, 17, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkDekuHatModifiedDL[] = {
    gsSPMatrix(0x0D0001C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPDisplayList(0x0C000000),
    gsSPVertex(&object_link_nutsVtx_000000[164], 7, 0),
    gsSPMatrix(0x0D000200, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    // gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    // gsDPSetTextureLUT(G_TT_RGBA16),
    // gsDPLoadTLUT_pal256(object_link_nuts_TLUT_003EB0),
    // gsDPLoadTextureBlock(object_link_nuts_Tex_0043B0, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
    //                      G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    // gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(savedLink_005C40, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 0, 181, 57, 255),
    gsSPVertex(&object_link_nutsVtx_000000[171], 25, 7),
    gsSP2Triangles(1, 2, 7, 0, 0, 8, 4, 0),
    gsSP2Triangles(9, 10, 4, 0, 11, 4, 12, 0),
    gsSP2Triangles(13, 14, 4, 0, 15, 2, 6, 0),
    gsSP2Triangles(5, 16, 17, 0, 18, 19, 5, 0),
    gsSP2Triangles(20, 3, 5, 0, 21, 6, 22, 0),
    gsSP2Triangles(6, 4, 23, 0, 5, 24, 25, 0),
    gsSP2Triangles(26, 1, 27, 0, 28, 5, 1, 0),
    gsSP2Triangles(0, 3, 29, 0, 0, 30, 31, 0),
    gsSPVertex(&object_link_nutsVtx_000000[196], 14, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 4, 0),
    gsSP2Triangles(4, 5, 2, 0, 2, 5, 0, 0),
    gsSP2Triangles(4, 6, 7, 0, 0, 5, 7, 0),
    gsSP2Triangles(3, 6, 4, 0, 2, 1, 3, 0),
    gsSP2Triangles(8, 7, 9, 0, 7, 5, 4, 0),
    gsSP2Triangles(8, 10, 7, 0, 7, 10, 0, 0),
    gsSP2Triangles(0, 10, 1, 0, 7, 6, 11, 0),
    gsSP2Triangles(9, 7, 11, 0, 12, 3, 1, 0),
    gsSP1Triangle(12, 1, 13, 0),
    gsSPEndDisplayList(),
};

extern LodLimb gLinkDekuRootLimb;

LodLimb gLinkDekuWaistLimbMod = { 
    { 0, 0, 0 }, LINK_DEKU_LIMB_LOWER_ROOT - 1, LINK_DEKU_LIMB_UPPER_ROOT - 1,
    { gLinkDekuWaistModifiedDL, gLinkDekuWaistModifiedDL }
};

extern LodLimb gLinkDekuLowerRootLimb;

extern LodLimb gLinkDekuRightThighLimb;

extern LodLimb gLinkDekuRightShinLimb;

extern LodLimb gLinkDekuRightFootLimb;

extern LodLimb gLinkDekuLeftThighLimb;

extern LodLimb gLinkDekuLeftShinLimb;

extern LodLimb gLinkDekuLeftFootLimb;

extern LodLimb gLinkDekuUpperRootLimb;

LodLimb gLinkDekuHeadLimbMod = { 
    { 705, 0, 0 }, LINK_DEKU_LIMB_HAT - 1, LINK_DEKU_LIMB_COLLAR - 1,
    { gLinkDekuHeadModifiedDL, gLinkDekuHeadModifiedDL }
};

LodLimb gLinkDekuHatLimbMod = { 
    { -500, -1400, 0 }, LIMB_DONE, LIMB_DONE,
    { gLinkDekuHatModifiedDL, gLinkDekuHatModifiedDL }
};

extern LodLimb gLinkDekuCollarLimb;

extern LodLimb gLinkDekuLeftShoulderLimb;

extern LodLimb gLinkDekuLeftForearmLimb;

extern LodLimb gLinkDekuLeftHandLimb;

extern LodLimb gLinkDekuRightShoulderLimb;

extern LodLimb gLinkDekuRightForearmLimb;

extern LodLimb gLinkDekuRightHandLimb;

extern LodLimb gLinkDekuSheathLimb;

extern LodLimb gLinkDekuTorsoLimb;

void* gLinkDekuSkelLimbsMod[] = {
    &gLinkDekuRootLimb, /* LINK_DEKU_LIMB_ROOT */
    &gLinkDekuWaistLimbMod, /* LINK_DEKU_LIMB_WAIST */
    &gLinkDekuLowerRootLimb, /* LINK_DEKU_LIMB_LOWER_ROOT */
    &gLinkDekuRightThighLimb, /* LINK_DEKU_LIMB_RIGHT_THIGH */
    &gLinkDekuRightShinLimb, /* LINK_DEKU_LIMB_RIGHT_SHIN */
    &gLinkDekuRightFootLimb, /* LINK_DEKU_LIMB_RIGHT_FOOT */
    &gLinkDekuLeftThighLimb, /* LINK_DEKU_LIMB_LEFT_THIGH */
    &gLinkDekuLeftShinLimb, /* LINK_DEKU_LIMB_LEFT_SHIN */
    &gLinkDekuLeftFootLimb, /* LINK_DEKU_LIMB_LEFT_FOOT */
    &gLinkDekuUpperRootLimb, /* LINK_DEKU_LIMB_UPPER_ROOT */
    &gLinkDekuHeadLimbMod, /* LINK_DEKU_LIMB_HEAD */
    &gLinkDekuHatLimbMod, /* LINK_DEKU_LIMB_HAT */
    &gLinkDekuCollarLimb, /* LINK_DEKU_LIMB_COLLAR */
    &gLinkDekuLeftShoulderLimb, /* LINK_DEKU_LIMB_LEFT_SHOULDER */
    &gLinkDekuLeftForearmLimb, /* LINK_DEKU_LIMB_LEFT_FOREARM */
    &gLinkDekuLeftHandLimb, /* LINK_DEKU_LIMB_LEFT_HAND */
    &gLinkDekuRightShoulderLimb, /* LINK_DEKU_LIMB_RIGHT_SHOULDER */
    &gLinkDekuRightForearmLimb, /* LINK_DEKU_LIMB_RIGHT_FOREARM */
    &gLinkDekuRightHandLimb, /* LINK_DEKU_LIMB_RIGHT_HAND */
    &gLinkDekuSheathLimb, /* LINK_DEKU_LIMB_SHEATH */
    &gLinkDekuTorsoLimb, /* LINK_DEKU_LIMB_TORSO */
};

FlexSkeletonHeader gLinkDekuSkelMod = { 
    { gLinkDekuSkelLimbsMod, ARRAY_COUNT(gLinkDekuSkelLimbsMod) }, 18
};