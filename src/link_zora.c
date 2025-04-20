#include "modding.h"
#include "global.h"

typedef enum LinkZoraLimb {
    /* 0x00 */ LINK_ZORA_LIMB_NONE,
    /* 0x01 */ LINK_ZORA_LIMB_ROOT,
    /* 0x02 */ LINK_ZORA_LIMB_WAIST,
    /* 0x03 */ LINK_ZORA_LIMB_LOWER_ROOT,
    /* 0x04 */ LINK_ZORA_LIMB_RIGHT_THIGH,
    /* 0x05 */ LINK_ZORA_LIMB_RIGHT_SHIN,
    /* 0x06 */ LINK_ZORA_LIMB_RIGHT_FOOT,
    /* 0x07 */ LINK_ZORA_LIMB_LEFT_THIGH,
    /* 0x08 */ LINK_ZORA_LIMB_LEFT_SHIN,
    /* 0x09 */ LINK_ZORA_LIMB_LEFT_FOOT,
    /* 0x0A */ LINK_ZORA_LIMB_UPPER_ROOT,
    /* 0x0B */ LINK_ZORA_LIMB_HEAD,
    /* 0x0C */ LINK_ZORA_LIMB_HAT,
    /* 0x0D */ LINK_ZORA_LIMB_COLLAR,
    /* 0x0E */ LINK_ZORA_LIMB_LEFT_SHOULDER,
    /* 0x0F */ LINK_ZORA_LIMB_LEFT_FOREARM,
    /* 0x10 */ LINK_ZORA_LIMB_LEFT_HAND,
    /* 0x11 */ LINK_ZORA_LIMB_RIGHT_SHOULDER,
    /* 0x12 */ LINK_ZORA_LIMB_RIGHT_FOREARM,
    /* 0x13 */ LINK_ZORA_LIMB_RIGHT_HAND,
    /* 0x14 */ LINK_ZORA_LIMB_SHEATH,
    /* 0x15 */ LINK_ZORA_LIMB_TORSO,
    /* 0x16 */ LINK_ZORA_LIMB_MAX
} LinkZoraLimb;

extern u64 object_link_zora_TLUT_005000[];
extern u64 object_link_zora_Tex_005800[];
extern u64 object_link_zora_Tex_005A80[];
extern u64 object_link_zora_Tex_005B00[];
extern Vtx object_link_zoraVtx_0062C0[];

u64 human_link_tex_005D80[] = {
#include "textures/tex_005D80.i8.inc.c"
};

Gfx gLinkZoraRightThighModifiedDL[] = {
    gsSPMatrix(0x0D000000, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_zoraVtx_0062C0[101], 2, 0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(&object_link_zoraVtx_0062C0[103], 10, 2),
    gsSPMatrix(0x0D000040, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    // gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    // gsDPSetTextureLUT(G_TT_RGBA16),
    // gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    // gsDPLoadTextureBlock(object_link_zora_Tex_005A80, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
    //                      G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(human_link_tex_005D80, G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_zoraVtx_0062C0[113], 12, 12),
    gsSP2Triangles(7, 12, 13, 0, 9, 11, 14, 0),
    gsSP2Triangles(2, 15, 16, 0, 3, 17, 2, 0),
    gsSP2Triangles(11, 4, 18, 0, 19, 3, 7, 0),
    gsSP2Triangles(20, 5, 2, 0, 21, 4, 5, 0),
    gsSP1Triangle(22, 4, 23, 0),
    gsSPVertex(&object_link_zoraVtx_0062C0[125], 4, 12),
    gsSP1Triangle(2, 6, 3, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED), // fix thigh
    gsDPSetTextureLUT(G_TT_RGBA16), // fix thigh
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005800, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(12, 0, 13, 0, 14, 0, 15, 0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 0x80, 0, 0, 0, 255),
    gsSPVertex(&object_link_zoraVtx_0062C0[129], 4, 12),
    gsSP2Triangles(8, 1, 12, 0, 10, 13, 1, 0),
    gsSP1Triangle(14, 15, 10, 0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    // gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    // gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    // gsDPLoadTextureBlock(object_link_zora_Tex_005A80, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
    //                      G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(human_link_tex_005D80, G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_zoraVtx_0062C0[133], 5, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSP1Triangle(1, 0, 4, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED), // fix thigh
    gsDPSetTextureLUT(G_TT_RGBA16), // fix thigh
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005800, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_zoraVtx_0062C0[138], 9, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(4, 2, 1, 0, 3, 6, 4, 0),
    gsSP2Triangles(7, 6, 8, 0, 6, 3, 8, 0),
    gsSP2Triangles(1, 5, 4, 0, 8, 0, 7, 0),
    gsSP1Triangle(2, 7, 0, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkZoraLeftThighModifiedDL[] = {
    gsSPMatrix(0x0D000000, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_zoraVtx_0062C0[248], 2, 0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(&object_link_zoraVtx_0062C0[250], 10, 2),
    gsSPMatrix(0x0D000100, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    // gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    // gsDPSetTextureLUT(G_TT_RGBA16),
    // gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    // gsDPLoadTextureBlock(object_link_zora_Tex_005A80, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
    //                      G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(human_link_tex_005D80, G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_zoraVtx_0062C0[260], 12, 12),
    gsSP2Triangles(12, 13, 8, 0, 14, 10, 6, 0),
    gsSP2Triangles(15, 16, 2, 0, 2, 17, 3, 0),
    gsSP2Triangles(18, 4, 10, 0, 8, 3, 19, 0),
    gsSP2Triangles(2, 11, 20, 0, 11, 4, 21, 0),
    gsSP1Triangle(22, 4, 23, 0),
    gsSPVertex(&object_link_zoraVtx_0062C0[272], 4, 12),
    gsSP1Triangle(3, 5, 2, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED), // fix thigh
    gsDPSetTextureLUT(G_TT_RGBA16), // fix thigh
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005800, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(12, 0, 13, 0, 14, 0, 15, 0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 0x80, 0, 0, 0, 255),
    gsSPVertex(&object_link_zoraVtx_0062C0[276], 4, 12),
    gsSP2Triangles(12, 1, 9, 0, 1, 13, 7, 0),
    gsSP1Triangle(7, 14, 15, 0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    // gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    // gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    // gsDPLoadTextureBlock(object_link_zora_Tex_005A80, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
    //                      G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(human_link_tex_005D80, G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_zoraVtx_0062C0[280], 5, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSP1Triangle(4, 2, 1, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED), // fix thigh
    gsDPSetTextureLUT(G_TT_RGBA16), // fix thigh
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005800, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_zoraVtx_0062C0[285], 9, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(1, 0, 4, 0, 4, 6, 5, 0),
    gsSP2Triangles(7, 6, 8, 0, 7, 5, 6, 0),
    gsSP2Triangles(4, 3, 1, 0, 8, 2, 7, 0),
    gsSP1Triangle(2, 8, 0, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkZoraWaistModifiedDL[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005B00, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_zoraVtx_0062C0[294], 22, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
    gsSP2Triangles(2, 12, 0, 0, 11, 13, 9, 0),
    gsSP2Triangles(6, 14, 10, 0, 10, 9, 6, 0),
    gsSP2Triangles(8, 14, 6, 0, 5, 15, 3, 0),
    gsSP2Triangles(16, 17, 18, 0, 18, 19, 16, 0),
    gsSP2Triangles(2, 20, 21, 0, 21, 12, 2, 0),
    gsDPPipeSync(),
    // gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    // gsDPLoadTextureBlock(object_link_zora_Tex_005A80, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
    //                      G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(human_link_tex_005D80, G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_zoraVtx_0062C0[316], 23, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 4, 6, 0),
    gsSP2Triangles(8, 9, 10, 0, 11, 12, 13, 0),
    gsSP2Triangles(14, 15, 16, 0, 1, 0, 15, 0),
    gsSP2Triangles(15, 12, 1, 0, 17, 9, 18, 0),
    gsSP2Triangles(0, 16, 15, 0, 19, 20, 4, 0),
    gsSP2Triangles(7, 19, 4, 0, 19, 9, 20, 0),
    gsSP2Triangles(19, 18, 9, 0, 21, 13, 18, 0),
    gsSP2Triangles(13, 21, 11, 0, 12, 11, 1, 0),
    gsSP2Triangles(16, 22, 14, 0, 18, 13, 17, 0),
    gsSP2Triangles(10, 14, 8, 0, 14, 22, 8, 0),
    gsSP1Triangle(9, 8, 20, 0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 0x80, 0, 0, 0, 255),
    gsSPVertex(&object_link_zoraVtx_0062C0[339], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP2Triangles(2, 4, 5, 0, 2, 5, 3, 0),
    gsSPEndDisplayList(),
};

extern LodLimb gLinkZoraRootLimb;

LodLimb gLinkZoraWaistLimbMod = { 
    { 0, 0, 0 }, LINK_ZORA_LIMB_LOWER_ROOT - 1, LINK_ZORA_LIMB_UPPER_ROOT - 1,
    { gLinkZoraWaistModifiedDL, gLinkZoraWaistModifiedDL }
};

extern LodLimb gLinkZoraLowerRootLimb;

LodLimb gLinkZoraRightThighLimbMod = { 
    { -442, -5, -350 }, LINK_ZORA_LIMB_RIGHT_SHIN - 1, LINK_ZORA_LIMB_LEFT_THIGH - 1,
    { gLinkZoraRightThighModifiedDL, gLinkZoraRightThighModifiedDL }
};

extern LodLimb gLinkZoraRightShinLimb;

extern LodLimb gLinkZoraRightFootLimb;

LodLimb gLinkZoraLeftThighLimbMod = { 
    { -442, -5, 350 }, LINK_ZORA_LIMB_LEFT_SHIN - 1, LIMB_DONE,
    { gLinkZoraLeftThighModifiedDL, gLinkZoraLeftThighModifiedDL }
};

extern LodLimb gLinkZoraLeftShinLimb;

extern LodLimb gLinkZoraLeftFootLimb;

extern LodLimb gLinkZoraUpperRootLimb;

extern LodLimb gLinkZoraHeadLimb;

extern LodLimb gLinkZoraHatLimb;

extern LodLimb gLinkZoraCollarLimb;

extern LodLimb gLinkZoraLeftShoulderLimb;

extern LodLimb gLinkZoraLeftForearmLimb;

extern LodLimb gLinkZoraLeftHandLimb;

extern LodLimb gLinkZoraRightShoulderLimb;

extern LodLimb gLinkZoraRightForearmLimb;

extern LodLimb gLinkZoraRightHandLimb;

extern LodLimb gLinkZoraSheathLimb;

extern LodLimb gLinkZoraTorsoLimb;

void* gLinkZoraSkelLimbsMod[] = {
    &gLinkZoraRootLimb, /* LINK_ZORA_LIMB_ROOT */
    &gLinkZoraWaistLimbMod, /* LINK_ZORA_LIMB_WAIST */
    &gLinkZoraLowerRootLimb, /* LINK_ZORA_LIMB_LOWER_ROOT */
    &gLinkZoraRightThighLimbMod, /* LINK_ZORA_LIMB_RIGHT_THIGH */
    &gLinkZoraRightShinLimb, /* LINK_ZORA_LIMB_RIGHT_SHIN */
    &gLinkZoraRightFootLimb, /* LINK_ZORA_LIMB_RIGHT_FOOT */
    &gLinkZoraLeftThighLimbMod, /* LINK_ZORA_LIMB_LEFT_THIGH */
    &gLinkZoraLeftShinLimb, /* LINK_ZORA_LIMB_LEFT_SHIN */
    &gLinkZoraLeftFootLimb, /* LINK_ZORA_LIMB_LEFT_FOOT */
    &gLinkZoraUpperRootLimb, /* LINK_ZORA_LIMB_UPPER_ROOT */
    &gLinkZoraHeadLimb, /* LINK_ZORA_LIMB_HEAD */
    &gLinkZoraHatLimb, /* LINK_ZORA_LIMB_HAT */
    &gLinkZoraCollarLimb, /* LINK_ZORA_LIMB_COLLAR */
    &gLinkZoraLeftShoulderLimb, /* LINK_ZORA_LIMB_LEFT_SHOULDER */
    &gLinkZoraLeftForearmLimb, /* LINK_ZORA_LIMB_LEFT_FOREARM */
    &gLinkZoraLeftHandLimb, /* LINK_ZORA_LIMB_LEFT_HAND */
    &gLinkZoraRightShoulderLimb, /* LINK_ZORA_LIMB_RIGHT_SHOULDER */
    &gLinkZoraRightForearmLimb, /* LINK_ZORA_LIMB_RIGHT_FOREARM */
    &gLinkZoraRightHandLimb, /* LINK_ZORA_LIMB_RIGHT_HAND */
    &gLinkZoraSheathLimb, /* LINK_ZORA_LIMB_SHEATH */
    &gLinkZoraTorsoLimb, /* LINK_ZORA_LIMB_TORSO */
};

FlexSkeletonHeader gLinkZoraSkelMod = { 
    { gLinkZoraSkelLimbsMod, ARRAY_COUNT(gLinkZoraSkelLimbsMod) }, 18
};