#include "modding.h"
#include "global.h"

typedef enum LinkGoronLimb {
    /* 0x00 */ LINK_GORON_LIMB_NONE,
    /* 0x01 */ LINK_GORON_LIMB_ROOT,
    /* 0x02 */ LINK_GORON_LIMB_WAIST,
    /* 0x03 */ LINK_GORON_LIMB_LOWER_ROOT,
    /* 0x04 */ LINK_GORON_LIMB_RIGHT_THIGH,
    /* 0x05 */ LINK_GORON_LIMB_RIGHT_SHIN,
    /* 0x06 */ LINK_GORON_LIMB_RIGHT_FOOT,
    /* 0x07 */ LINK_GORON_LIMB_LEFT_THIGH,
    /* 0x08 */ LINK_GORON_LIMB_LEFT_SHIN,
    /* 0x09 */ LINK_GORON_LIMB_LEFT_FOOT,
    /* 0x0A */ LINK_GORON_LIMB_UPPER_ROOT,
    /* 0x0B */ LINK_GORON_LIMB_HEAD,
    /* 0x0C */ LINK_GORON_LIMB_HAT,
    /* 0x0D */ LINK_GORON_LIMB_COLLAR,
    /* 0x0E */ LINK_GORON_LIMB_LEFT_SHOULDER,
    /* 0x0F */ LINK_GORON_LIMB_LEFT_FOREARM,
    /* 0x10 */ LINK_GORON_LIMB_LEFT_HAND,
    /* 0x11 */ LINK_GORON_LIMB_RIGHT_SHOULDER,
    /* 0x12 */ LINK_GORON_LIMB_RIGHT_FOREARM,
    /* 0x13 */ LINK_GORON_LIMB_RIGHT_HAND,
    /* 0x14 */ LINK_GORON_LIMB_SHEATH,
    /* 0x15 */ LINK_GORON_LIMB_TORSO,
    /* 0x16 */ LINK_GORON_LIMB_MAX
} LinkGoronLimb;

extern u64 object_link_goron_TLUT_002000[];
extern u64 object_link_goron_Tex_002780[];
extern u64 object_link_goron_Tex_002D40[];
extern Vtx object_link_goronVtx_004380[];
extern Vtx object_link_goronVtx_00A6A8[];
extern u64 object_link_goron_Tex_00C6B8[];
extern u64 object_link_goron_Tex_00CEB8[];
extern u64 object_link_goron_Tex_00CFB8[];
extern u64 object_link_goron_Tex_00D0B8[];
extern u64 object_link_goron_Tex_00D2B8[];
extern u64 object_link_goron_Tex_00D3B8[];
extern u64 object_link_goron_Tex_00D4B8[];
extern u64 object_link_goron_Tex_00D8B8[];

u64 Goron_Tunic_I[] = {
#include "textures/goron_tunic.inc"
};

Gfx gLinkGoronWaistModifiedDL[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    // gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    // gsDPLoadTextureBlock(object_link_goron_Tex_002780, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 16, 0, G_TX_NOMIRROR |
    //                      G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTextureBlock(Goron_Tunic_I, G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0, G_TX_NOMIRROR |
                         G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_goronVtx_004380[252], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSP2Triangles(4, 5, 2, 0, 2, 1, 4, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkGoronHatModifiedDL[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPMatrix(0x0D0001C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_link_goron_Tex_002D40, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, 0, G_TX_NOMIRROR |
                         G_TX_WRAP, G_TX_NOMIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_goronVtx_004380[258], 8, 0),
    gsSPMatrix(0x0D000200, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPPipeSync(),
    // gsDPLoadTextureBlock(object_link_goron_Tex_002780, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 16, 0, G_TX_NOMIRROR |
    //                      G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock(Goron_Tunic_I, G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0, G_TX_NOMIRROR |
                         G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_goronVtx_004380[266], 20, 8),
    gsSP2Triangles(8, 9, 0, 0, 10, 11, 0, 0),
    gsSP2Triangles(1, 2, 12, 0, 2, 0, 13, 0),
    gsSP2Triangles(3, 14, 4, 0, 15, 0, 4, 0),
    gsSP2Triangles(16, 17, 1, 0, 5, 1, 18, 0),
    gsSP2Triangles(19, 6, 5, 0, 6, 20, 21, 0),
    gsSP2Triangles(22, 7, 6, 0, 23, 3, 7, 0),
    gsSP2Triangles(3, 24, 25, 0, 3, 26, 27, 0),
    gsSPVertex(&object_link_goronVtx_004380[286], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(4, 0, 5, 0, 0, 2, 5, 0),
    gsSP2Triangles(6, 7, 0, 0, 6, 0, 4, 0),
    gsSP2Triangles(6, 4, 3, 0, 7, 1, 0, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkGoronCurledModifiedDL[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, COMBINED, 0, ENVIRONMENT, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(0x0C000010),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal256(object_link_goron_TLUT_002000),
    gsDPLoadTextureBlock(object_link_goron_Tex_00CFB8, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_MIRROR | G_TX_CLAMP,
                         G_TX_MIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(object_link_goronVtx_00A6A8, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 6, 4, 0, 7, 8, 9, 0),
    gsSP2Triangles(9, 10, 7, 0, 11, 12, 13, 0),
    gsSP2Triangles(14, 15, 16, 0, 16, 15, 17, 0),
    gsSP2Triangles(18, 19, 20, 0, 15, 21, 17, 0),
    gsSP2Triangles(22, 23, 11, 0, 12, 11, 23, 0),
    gsSP2Triangles(19, 18, 24, 0, 25, 26, 1, 0),
    gsSP2Triangles(26, 2, 1, 0, 18, 27, 24, 0),
    gsSP2Triangles(28, 29, 30, 0, 17, 21, 31, 0),
    gsSPVertex(&object_link_goronVtx_00A6A8[32], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 6, 8, 9, 0),
    gsSP2Triangles(10, 11, 12, 0, 11, 10, 13, 0),
    gsSP2Triangles(2, 1, 14, 0, 2, 14, 15, 0),
    gsSP2Triangles(15, 14, 16, 0, 17, 12, 11, 0),
    gsSP2Triangles(18, 19, 20, 0, 20, 21, 18, 0),
    gsSP2Triangles(7, 6, 22, 0, 23, 24, 18, 0),
    gsSP2Triangles(23, 18, 25, 0, 25, 18, 26, 0),
    gsSP2Triangles(19, 18, 27, 0, 27, 18, 24, 0),
    gsSP2Triangles(28, 29, 30, 0, 31, 30, 29, 0),
    gsSPVertex(&object_link_goronVtx_00A6A8[64], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_link_goron_Tex_00D0B8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0, G_TX_MIRROR | G_TX_CLAMP,
                         G_TX_MIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_goronVtx_00A6A8[67], 7, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSP2Triangles(4, 5, 0, 0, 0, 6, 4, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_link_goron_Tex_00D4B8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, 0, G_TX_MIRROR | G_TX_CLAMP,
                         G_TX_MIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_goronVtx_00A6A8[74], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSP2Triangles(0, 3, 4, 0, 4, 5, 0, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_link_goron_Tex_00D2B8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_MIRROR | G_TX_CLAMP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_goronVtx_00A6A8[80], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 5, 4, 0, 7, 8, 9, 0),
    gsSP2Triangles(10, 11, 12, 0, 11, 13, 12, 0),
    gsSP2Triangles(14, 1, 0, 0, 15, 14, 0, 0),
    gsSP2Triangles(16, 17, 18, 0, 19, 20, 21, 0),
    gsSP2Triangles(22, 23, 24, 0, 22, 25, 23, 0),
    gsSP2Triangles(26, 27, 28, 0, 26, 28, 29, 0),
    gsSPVertex(&object_link_goronVtx_00A6A8[110], 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(4, 3, 6, 0, 7, 8, 9, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_link_goron_Tex_00D3B8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_MIRROR | G_TX_CLAMP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_goronVtx_00A6A8[120], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(4, 6, 5, 0, 7, 8, 9, 0),
    gsSP2Triangles(7, 10, 8, 0, 11, 12, 13, 0),
    gsSP2Triangles(14, 15, 16, 0, 17, 18, 19, 0),
    gsSP2Triangles(20, 21, 22, 0, 23, 24, 25, 0),
    gsSP2Triangles(26, 27, 28, 0, 29, 30, 31, 0),
    gsSPVertex(&object_link_goronVtx_00A6A8[152], 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 7, 9, 8, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal256(object_link_goron_TLUT_002000),
    gsDPLoadTextureBlock(object_link_goron_Tex_00C6B8, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 64, 0, G_TX_MIRROR | G_TX_CLAMP,
                         G_TX_MIRROR | G_TX_CLAMP, 5, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_goronVtx_00A6A8[162], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(5, 4, 6, 0, 7, 8, 9, 0),
    gsSP2Triangles(9, 8, 10, 0, 11, 12, 13, 0),
    gsSP2Triangles(13, 14, 11, 0, 11, 14, 15, 0),
    gsSP2Triangles(15, 16, 11, 0, 17, 18, 19, 0),
    gsSP2Triangles(20, 21, 22, 0, 22, 23, 20, 0),
    gsSP2Triangles(19, 24, 17, 0, 25, 26, 27, 0),
    gsSP2Triangles(28, 26, 25, 0, 25, 29, 28, 0),
    gsSP2Triangles(30, 29, 25, 0, 25, 31, 30, 0),
    gsSPVertex(&object_link_goronVtx_00A6A8[194], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 9, 7, 6, 0),
    gsSP2Triangles(6, 10, 11, 0, 12, 10, 6, 0),
    gsSP2Triangles(13, 14, 15, 0, 16, 17, 18, 0),
    gsSP2Triangles(18, 19, 16, 0, 20, 19, 18, 0),
    gsSP2Triangles(18, 21, 20, 0, 22, 21, 18, 0),
    gsSP2Triangles(23, 24, 25, 0, 25, 26, 23, 0),
    gsSP2Triangles(27, 28, 29, 0, 29, 30, 27, 0),
    gsSP1Triangle(27, 30, 31, 0),
    gsSPVertex(&object_link_goronVtx_00A6A8[226], 23, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(5, 4, 6, 0, 6, 7, 5, 0),
    gsSP2Triangles(8, 9, 10, 0, 11, 12, 13, 0),
    gsSP2Triangles(14, 15, 16, 0, 16, 17, 14, 0),
    gsSP2Triangles(18, 19, 20, 0, 21, 9, 8, 0),
    gsSP1Triangle(5, 7, 22, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    // gsDPLoadTextureBlock(object_link_goron_Tex_00CEB8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 16, 0, G_TX_MIRROR | G_TX_CLAMP,
    //                      G_TX_MIRROR | G_TX_CLAMP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock(Goron_Tunic_I, G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_CLAMP,
                         G_TX_MIRROR | G_TX_CLAMP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_goronVtx_00A6A8[249], 14, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 0, 2, 8, 0),
    gsSP2Triangles(9, 10, 5, 0, 10, 2, 5, 0),
    gsSP2Triangles(9, 4, 11, 0, 2, 3, 5, 0),
    gsSP2Triangles(4, 9, 5, 0, 2, 10, 8, 0),
    gsSP2Triangles(10, 6, 8, 0, 8, 7, 0, 0),
    gsSP2Triangles(6, 10, 12, 0, 12, 10, 9, 0),
    gsSP2Triangles(13, 7, 6, 0, 2, 1, 3, 0),
    gsSPTexture(0, 0x1A2C, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, SHADE, ENVIRONMENT, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, COMBINED,
                       0, ENVIRONMENT, 0),
    gsDPSetPrimColor(0, 0xFF, 128, 128, 128, 255),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_link_goron_Tex_00D8B8, G_IM_FMT_I, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_MIRROR | G_TX_WRAP, 3, 3, 3, 2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                         G_SHADING_SMOOTH),
    gsSPVertex(&object_link_goronVtx_00A6A8[263], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 2, 1, 0),
    gsSP2Triangles(2, 3, 4, 0, 5, 4, 3, 0),
    gsSPTexture(0x03E8, 0x0A28, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_link_goron_Tex_00D8B8, G_IM_FMT_I, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_MIRROR | G_TX_WRAP, 3, 3, 3, 2),
    gsSPVertex(&object_link_goronVtx_00A6A8[269], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(3, 4, 0, 0, 3, 5, 4, 0),
    gsSPTexture(0x03E8, 0x1450, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_link_goron_Tex_00D8B8, G_IM_FMT_I, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_MIRROR | G_TX_WRAP, 3, 3, 3, 2),
    gsSPVertex(&object_link_goronVtx_00A6A8[275], 7, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(3, 4, 2, 0, 4, 5, 2, 0),
    gsSP2Triangles(5, 6, 2, 0, 6, 0, 2, 0),
    gsSPTexture(0x125C, 0x0834, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_link_goron_Tex_00D8B8, G_IM_FMT_I, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_MIRROR | G_TX_WRAP, 3, 3, 3, 2),
    gsSPVertex(&object_link_goronVtx_00A6A8[282], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP2Triangles(2, 4, 3, 0, 4, 5, 3, 0),
    gsSPTexture(0, 0x1A2C, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(object_link_goron_Tex_00D8B8, G_IM_FMT_I, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_MIRROR | G_TX_WRAP, 3, 3, 3, 2),
    gsSPVertex(&object_link_goronVtx_00A6A8[288], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 0, 3, 0),
    gsSP2Triangles(4, 3, 0, 0, 3, 4, 5, 0),
    gsSPEndDisplayList(),
};

extern Gfx object_link_goron_DL_00C540[];
extern Gfx object_link_goron_DL_0127B0[];
extern Gfx object_link_goron_DL_0134D0[];

Gfx gLinkGoronRollingSpikesAndEffectModifiedDL[] = {
    gsSPDisplayList(gLinkGoronCurledModifiedDL),
    gsSPDisplayList(object_link_goron_DL_00C540),
    gsSPDisplayList(object_link_goron_DL_0127B0),
    gsSPDisplayList(object_link_goron_DL_0134D0),
    gsSPEndDisplayList(),
};

extern LodLimb gLinkGoronRootLimb;

LodLimb gLinkGoronWaistLimbMod = { 
    { 0, 0, 0 }, LINK_GORON_LIMB_LOWER_ROOT - 1, LINK_GORON_LIMB_UPPER_ROOT - 1,
    { gLinkGoronWaistModifiedDL, gLinkGoronWaistModifiedDL }
};

extern LodLimb gLinkGoronLowerRootLimb;

extern LodLimb gLinkGoronRightThighLimb;

extern LodLimb gLinkGoronRightShinLimb;

extern LodLimb gLinkGoronRightFootLimb;

extern LodLimb gLinkGoronLeftThighLimb;

extern LodLimb gLinkGoronLeftShinLimb;

extern LodLimb gLinkGoronLeftFootLimb;

extern LodLimb gLinkGoronUpperRootLimb;

extern LodLimb gLinkGoronHeadLimb;

LodLimb gLinkGoronHatLimbMod = { 
    { -831, -998, 0 }, LIMB_DONE, LIMB_DONE,
    { gLinkGoronHatModifiedDL, gLinkGoronHatModifiedDL }
};

extern LodLimb gLinkGoronCollarLimb;

extern LodLimb gLinkGoronLeftShoulderLimb;

extern LodLimb gLinkGoronLeftForearmLimb;

extern LodLimb gLinkGoronLeftHandLimb;

extern LodLimb gLinkGoronRightShoulderLimb;

extern LodLimb gLinkGoronRightForearmLimb;

extern LodLimb gLinkGoronRightHandLimb;

extern LodLimb gLinkGoronSheathLimb;

extern LodLimb gLinkGoronTorsoLimb;

void* gLinkGoronSkelLimbsMod[] = {
    &gLinkGoronRootLimb, /* LINK_GORON_LIMB_ROOT */
    &gLinkGoronWaistLimbMod, /* LINK_GORON_LIMB_WAIST */
    &gLinkGoronLowerRootLimb, /* LINK_GORON_LIMB_LOWER_ROOT */
    &gLinkGoronRightThighLimb, /* LINK_GORON_LIMB_RIGHT_THIGH */
    &gLinkGoronRightShinLimb, /* LINK_GORON_LIMB_RIGHT_SHIN */
    &gLinkGoronRightFootLimb, /* LINK_GORON_LIMB_RIGHT_FOOT */
    &gLinkGoronLeftThighLimb, /* LINK_GORON_LIMB_LEFT_THIGH */
    &gLinkGoronLeftShinLimb, /* LINK_GORON_LIMB_LEFT_SHIN */
    &gLinkGoronLeftFootLimb, /* LINK_GORON_LIMB_LEFT_FOOT */
    &gLinkGoronUpperRootLimb, /* LINK_GORON_LIMB_UPPER_ROOT */
    &gLinkGoronHeadLimb, /* LINK_GORON_LIMB_HEAD */
    &gLinkGoronHatLimbMod, /* LINK_GORON_LIMB_HAT */
    &gLinkGoronCollarLimb, /* LINK_GORON_LIMB_COLLAR */
    &gLinkGoronLeftShoulderLimb, /* LINK_GORON_LIMB_LEFT_SHOULDER */
    &gLinkGoronLeftForearmLimb, /* LINK_GORON_LIMB_LEFT_FOREARM */
    &gLinkGoronLeftHandLimb, /* LINK_GORON_LIMB_LEFT_HAND */
    &gLinkGoronRightShoulderLimb, /* LINK_GORON_LIMB_RIGHT_SHOULDER */
    &gLinkGoronRightForearmLimb, /* LINK_GORON_LIMB_RIGHT_FOREARM */
    &gLinkGoronRightHandLimb, /* LINK_GORON_LIMB_RIGHT_HAND */
    &gLinkGoronSheathLimb, /* LINK_GORON_LIMB_SHEATH */
    &gLinkGoronTorsoLimb, /* LINK_GORON_LIMB_TORSO */
};

FlexSkeletonHeader gLinkGoronSkelMod = { 
    { gLinkGoronSkelLimbsMod, ARRAY_COUNT(gLinkGoronSkelLimbsMod) }, 18
};