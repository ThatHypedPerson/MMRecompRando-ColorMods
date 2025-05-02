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
extern u64 gLinkZoraSkinTLUT[];
extern u64 object_link_zora_Tex_005800[];
extern u64 object_link_zora_Tex_005A80[];
extern u64 object_link_zora_Tex_005B00[];
extern u64 object_link_zora_Tex_005D00[];
extern u64 object_link_zora_Tex_005F00[];
extern Vtx object_link_zoraVtx_0062C0[];

u64 savedLink_005D80[16];

u64 zora_base[] = {
#include "textures/zora_base.inc"
};

u64 zora_gradient[] = {
#include "textures/zora_gradient.inc"
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
    gsDPLoadTextureBlock(savedLink_005D80, G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
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
    gsDPLoadTextureBlock(savedLink_005D80, G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
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
    gsDPLoadTextureBlock(savedLink_005D80, G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
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
    gsDPLoadTextureBlock(savedLink_005D80, G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
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
    gsDPLoadTextureBlock(savedLink_005D80, G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
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

Gfx gLinkZoraHeadModifiedDL[] = {
    gsSPMatrix(0x0D000440, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_zoraVtx_0062C0[383], 10, 0),
    gsSPMatrix(0x0D0001C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005B00, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_zoraVtx_0062C0[393], 14, 10),
    gsSP2Triangles(1, 10, 11, 0, 2, 3, 12, 0),
    gsSP2Triangles(13, 0, 1, 0, 14, 15, 3, 0),
    gsSP2Triangles(5, 0, 16, 0, 17, 18, 5, 0),
    gsSP2Triangles(19, 4, 7, 0, 7, 8, 20, 0),
    gsSP2Triangles(9, 21, 22, 0, 23, 9, 6, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal256(gLinkZoraSkinTLUT),
    gsDPLoadTextureBlock(0x08000000, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR |
                         G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_zoraVtx_0062C0[407], 18, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 0, 3, 0),
    gsSP2Triangles(3, 0, 4, 0, 5, 3, 4, 0),
    gsSP2Triangles(3, 5, 6, 0, 6, 7, 3, 0),
    gsSP2Triangles(3, 7, 8, 0, 8, 1, 3, 0),
    gsSP2Triangles(9, 10, 11, 0, 11, 12, 9, 0),
    gsSP2Triangles(9, 12, 13, 0, 13, 14, 9, 0),
    gsSP2Triangles(15, 9, 14, 0, 15, 16, 9, 0),
    gsSP2Triangles(9, 16, 10, 0, 17, 10, 16, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal256(gLinkZoraSkinTLUT),
    gsDPLoadTextureBlock(0x09000000, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR |
                         G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_zoraVtx_0062C0[425], 9, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 1, 4, 0),
    gsSP2Triangles(1, 0, 4, 0, 1, 3, 5, 0),
    gsSP2Triangles(6, 7, 2, 0, 0, 2, 8, 0),
    gsSP1Triangle(2, 7, 8, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005800, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_zoraVtx_0062C0[434], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 5, 4, 0, 7, 8, 9, 0),
    gsSP2Triangles(7, 9, 10, 0, 6, 4, 11, 0),
    gsSP2Triangles(4, 12, 11, 0, 13, 14, 15, 0),
    gsSP2Triangles(16, 17, 7, 0, 15, 18, 19, 0),
    gsSP2Triangles(15, 14, 18, 0, 20, 13, 21, 0),
    gsSP2Triangles(18, 22, 19, 0, 23, 24, 25, 0),
    gsSP2Triangles(16, 7, 26, 0, 7, 27, 26, 0),
    gsSP1Triangle(28, 29, 30, 0),
    gsSPVertex(&object_link_zoraVtx_0062C0[465], 27, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 8, 9, 0),
    gsSP2Triangles(10, 11, 12, 0, 13, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 19, 20, 9, 0),
    gsSP2Triangles(9, 8, 21, 0, 22, 23, 24, 0),
    gsSP2Triangles(25, 13, 26, 0, 25, 14, 13, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005F00, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_zoraVtx_0062C0[492], 16, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 4, 0),
    gsSP2Triangles(0, 4, 5, 0, 5, 1, 0, 0),
    gsSP2Triangles(0, 6, 3, 0, 7, 6, 0, 0),
    gsSP2Triangles(7, 0, 2, 0, 8, 9, 10, 0),
    gsSP2Triangles(9, 11, 10, 0, 12, 11, 9, 0),
    gsSP2Triangles(9, 13, 14, 0, 14, 15, 9, 0),
    gsSP2Triangles(15, 12, 9, 0, 8, 13, 9, 0),
    gsDPPipeSync(),
    // gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    // gsDPLoadTextureBlock(object_link_zora_Tex_005D00, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
    //                      G_TX_NOMIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(zora_base, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_zoraVtx_0062C0[508], 22, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 0, 3, 0),
    gsSP2Triangles(4, 3, 5, 0, 4, 5, 6, 0),
    gsSP2Triangles(7, 8, 9, 0, 10, 11, 9, 0),
    gsSP2Triangles(10, 9, 12, 0, 7, 13, 14, 0),
    gsSP2Triangles(12, 15, 16, 0, 8, 7, 14, 0),
    gsSP2Triangles(17, 14, 13, 0, 9, 11, 7, 0),
    gsSP2Triangles(18, 19, 17, 0, 13, 18, 17, 0),
    gsSP2Triangles(20, 17, 19, 0, 19, 21, 20, 0),
    gsSP2Triangles(12, 16, 10, 0, 4, 20, 21, 0),
    // gradient overlay
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock(zora_gradient, G_IM_FMT_IA, G_IM_SIZ_16b, 16, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_zoraVtx_0062C0[508], 22, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 0, 3, 0),
    gsSP2Triangles(4, 3, 5, 0, 4, 5, 6, 0),
    gsSP2Triangles(7, 8, 9, 0, 10, 11, 9, 0),
    gsSP2Triangles(10, 9, 12, 0, 7, 13, 14, 0),
    gsSP2Triangles(12, 15, 16, 0, 8, 7, 14, 0),
    gsSP2Triangles(17, 14, 13, 0, 9, 11, 7, 0),
    gsSP2Triangles(18, 19, 17, 0, 13, 18, 17, 0),
    gsSP2Triangles(20, 17, 19, 0, 19, 21, 20, 0),
    gsSP2Triangles(12, 16, 10, 0, 4, 20, 21, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkZoraHatModifiedDL[] = {
    gsSPMatrix(0x0D0001C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_zoraVtx_0062C0[345], 9, 0),
    gsSPMatrix(0x0D000200, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    // gsDPSetTextureLUT(G_TT_RGBA16),
    // gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    // gsDPLoadTextureBlock(object_link_zora_Tex_005D00, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
    //                      G_TX_NOMIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(zora_base, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_zoraVtx_0062C0[354], 21, 9),
    gsSP2Triangles(9, 10, 3, 0, 3, 2, 11, 0),
    gsSP2Triangles(12, 0, 1, 0, 5, 13, 1, 0),
    gsSP2Triangles(4, 14, 15, 0, 16, 6, 4, 0),
    gsSP2Triangles(17, 7, 6, 0, 1, 18, 19, 0),
    gsSP2Triangles(3, 20, 4, 0, 0, 21, 22, 0),
    gsSP2Triangles(23, 24, 7, 0, 5, 8, 25, 0),
    gsSP2Triangles(8, 26, 27, 0, 0, 28, 2, 0),
    gsSP1Triangle(8, 7, 29, 0),
    gsSPVertex(&object_link_zoraVtx_0062C0[375], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(3, 2, 4, 0, 4, 5, 3, 0),
    gsSP2Triangles(4, 2, 6, 0, 6, 5, 4, 0),
    gsSP2Triangles(6, 2, 7, 0, 7, 2, 1, 0),
    gsDPPipeSync(),
    // gradient overlay
    gsSPMatrix(0x0D0001C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_zoraVtx_0062C0[345], 9, 0),
    gsSPMatrix(0x0D000200, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock(zora_gradient, G_IM_FMT_IA, G_IM_SIZ_16b, 16, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_zoraVtx_0062C0[354], 21, 9),
    gsSP2Triangles(9, 10, 3, 0, 3, 2, 11, 0),
    gsSP2Triangles(12, 0, 1, 0, 5, 13, 1, 0),
    gsSP2Triangles(4, 14, 15, 0, 16, 6, 4, 0),
    gsSP2Triangles(17, 7, 6, 0, 1, 18, 19, 0),
    gsSP2Triangles(3, 20, 4, 0, 0, 21, 22, 0),
    gsSP2Triangles(23, 24, 7, 0, 5, 8, 25, 0),
    gsSP2Triangles(8, 26, 27, 0, 0, 28, 2, 0),
    gsSP1Triangle(8, 7, 29, 0),
    gsSPVertex(&object_link_zoraVtx_0062C0[375], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(3, 2, 4, 0, 4, 5, 3, 0),
    gsSP2Triangles(4, 2, 6, 0, 6, 5, 4, 0),
    gsSP2Triangles(6, 2, 7, 0, 7, 2, 1, 0),
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

LodLimb gLinkZoraHeadLimbMod = { 
    { 1806, 0, 0 }, LINK_ZORA_LIMB_HAT - 1, LINK_ZORA_LIMB_COLLAR - 1,
    { gLinkZoraHeadModifiedDL, gLinkZoraHeadModifiedDL }
};

LodLimb gLinkZoraHatLimbMod = { 
    { -298, -700, 0 }, LIMB_DONE, LIMB_DONE,
    { gLinkZoraHatModifiedDL, gLinkZoraHatModifiedDL }
};

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
    &gLinkZoraHeadLimbMod, /* LINK_ZORA_LIMB_HEAD */
    &gLinkZoraHatLimbMod, /* LINK_ZORA_LIMB_HAT */
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

// zora boomerang

// extern Vtx gameplay_keepVtx_06FB60[];
// extern u64 gameplay_keep_Tex_0700B0[];
// extern u64 gameplay_keep_Tex_0704B0[];

// Gfx zoraBoomerangLeftModifiedDL[] = {
//     gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
//     gsDPPipeSync(),
//     gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
//     gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
//     gsDPSetTextureLUT(G_TT_NONE),
//     gsDPLoadTextureBlock(gameplay_keep_Tex_0704B0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
//                          G_TX_MIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
//     gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
//     gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
//     gsSPVertex(gameplay_keepVtx_06FB60, 12, 0),
//     gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
//     gsSP2Triangles(1, 4, 3, 0, 4, 5, 3, 0),
//     gsSP2Triangles(5, 6, 3, 0, 6, 7, 3, 0),
//     gsSP2Triangles(7, 2, 3, 0, 7, 8, 2, 0),
//     gsSP2Triangles(2, 9, 0, 0, 0, 9, 10, 0),
//     gsSP2Triangles(10, 8, 7, 0, 11, 10, 7, 0),
//     gsSP2Triangles(11, 7, 6, 0, 11, 6, 5, 0),
//     gsSP2Triangles(11, 5, 4, 0, 11, 4, 1, 0),
//     gsSP2Triangles(10, 11, 1, 0, 10, 1, 0, 0),
//     gsDPPipeSync(),
//     // gsDPLoadTextureBlock(gameplay_keep_Tex_0700B0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, 0, G_TX_MIRROR | G_TX_CLAMP,
//     //                      G_TX_MIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
//     gsDPLoadTextureBlock(zora_base, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, 0, G_TX_MIRROR | G_TX_CLAMP,
//                          G_TX_MIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
//     gsSPVertex(&gameplay_keepVtx_06FB60[12], 10, 0),
//     gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
//     gsSP2Triangles(3, 4, 2, 0, 4, 5, 2, 0),
//     gsSP2Triangles(5, 6, 2, 0, 5, 7, 6, 0),
//     gsSP2Triangles(8, 5, 4, 0, 8, 4, 3, 0),
//     gsSP2Triangles(8, 3, 1, 0, 8, 1, 0, 0),
//     gsSP2Triangles(9, 8, 0, 0, 9, 7, 5, 0),
//     gsSP2Triangles(8, 9, 5, 0, 0, 2, 6, 0),
//     // gradient overlay
//     gsDPPipeSync(),
//     gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
//     gsDPPipeSync(),
//     gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
//     gsDPLoadTextureBlock(zora_gradient, G_IM_FMT_IA, G_IM_SIZ_16b, 16, 32, 0, G_TX_MIRROR | G_TX_CLAMP,
//                          G_TX_MIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
//     gsSPVertex(&gameplay_keepVtx_06FB60[12], 10, 0),
//     gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
//     gsSP2Triangles(3, 4, 2, 0, 4, 5, 2, 0),
//     gsSP2Triangles(5, 6, 2, 0, 5, 7, 6, 0),
//     gsSP2Triangles(8, 5, 4, 0, 8, 4, 3, 0),
//     gsSP2Triangles(8, 3, 1, 0, 8, 1, 0, 0),
//     gsSP2Triangles(9, 8, 0, 0, 9, 7, 5, 0),
//     gsSP2Triangles(8, 9, 5, 0, 0, 2, 6, 0),
//     gsSPEndDisplayList(),
// };

// Gfx zoraBoomerangRightModifiedDL[] = {
//     gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
//     gsDPPipeSync(),
//     gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
//     gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
//     gsDPSetTextureLUT(G_TT_NONE),
//     gsDPLoadTextureBlock(gameplay_keep_Tex_0704B0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
//                          G_TX_MIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
//     gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
//     gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
//     gsSPVertex(&gameplay_keepVtx_06FB60[22], 12, 0),
//     gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
//     gsSP2Triangles(3, 4, 1, 0, 3, 5, 4, 0),
//     gsSP2Triangles(3, 6, 5, 0, 3, 7, 6, 0),
//     gsSP2Triangles(3, 0, 7, 0, 0, 8, 7, 0),
//     gsSP2Triangles(2, 9, 0, 0, 10, 9, 2, 0),
//     gsSP2Triangles(7, 8, 10, 0, 7, 10, 11, 0),
//     gsSP2Triangles(6, 7, 11, 0, 5, 6, 11, 0),
//     gsSP2Triangles(4, 5, 11, 0, 1, 4, 11, 0),
//     gsSP2Triangles(1, 11, 10, 0, 2, 1, 10, 0),
//     gsDPPipeSync(),
//     // gsDPLoadTextureBlock(gameplay_keep_Tex_0700B0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, 0, G_TX_MIRROR | G_TX_CLAMP,
//     //                      G_TX_MIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
//     gsDPLoadTextureBlock(zora_base, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, 0, G_TX_MIRROR | G_TX_CLAMP,
//                          G_TX_MIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
//     gsSPVertex(&gameplay_keepVtx_06FB60[34], 10, 0),
//     gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
//     gsSP2Triangles(0, 4, 3, 0, 0, 5, 4, 0),
//     gsSP2Triangles(0, 6, 5, 0, 6, 7, 5, 0),
//     gsSP2Triangles(4, 5, 8, 0, 3, 4, 8, 0),
//     gsSP2Triangles(1, 3, 8, 0, 2, 1, 8, 0),
//     gsSP2Triangles(2, 8, 9, 0, 5, 7, 9, 0),
//     gsSP2Triangles(5, 9, 8, 0, 6, 0, 2, 0),
//     // gradient overlay
//     gsDPPipeSync(),
//     gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
//     gsDPPipeSync(),
//     gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
//     gsDPLoadTextureBlock(zora_gradient, G_IM_FMT_IA, G_IM_SIZ_16b, 16, 32, 0, G_TX_MIRROR | G_TX_CLAMP,
//                          G_TX_MIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
//     gsSPVertex(&gameplay_keepVtx_06FB60[34], 10, 0),
//     gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
//     gsSP2Triangles(0, 4, 3, 0, 0, 5, 4, 0),
//     gsSP2Triangles(0, 6, 5, 0, 6, 7, 5, 0),
//     gsSP2Triangles(4, 5, 8, 0, 3, 4, 8, 0),
//     gsSP2Triangles(1, 3, 8, 0, 2, 1, 8, 0),
//     gsSP2Triangles(2, 8, 9, 0, 5, 7, 9, 0),
//     gsSP2Triangles(5, 9, 8, 0, 6, 0, 2, 0),
//     gsSPEndDisplayList(),
// };

// TODO zora fins:
// object_link_zora_DL_00CC38;
// object_link_zora_DL_00CDA0;
// object_link_zora_DL_010868;
// object_link_zora_DL_010978;
// object_link_zora_DL_0110A8;