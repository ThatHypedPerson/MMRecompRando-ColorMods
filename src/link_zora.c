#include "recolor.h"
#include "dl_patching.h"

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
extern u64 object_link_zora_Tex_005A80[];
extern u64 object_link_zora_Tex_005D00[];
extern u64 object_link_zora_Tex_005800[];
extern Vtx object_link_zoraVtx_0062C0[];

u64 zora_base[] = {
#include "textures/zora_base.inc"
};

u64 zora_gradient[] = {
#include "textures/zora_gradient.inc"
};

Gfx zora_thigh_commands[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005A80, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
};

Gfx zora_thigh_replacement[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(savedLink_005D80, G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(&env_color_dls[PLAYER_FORM_ZORA]),
    gsSPEndDisplayList(),
};

Gfx zora_thigh_commands2[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005A80, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
};

Gfx zora_thigh_replacement2[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(savedLink_005D80, G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(&env_color_dls[PLAYER_FORM_ZORA]),
    gsSPEndDisplayList(),
};

Gfx zora_thigh_commands3[] = {
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005800, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(12, 0, 13, 0, 14, 0, 15, 0),
};

Gfx zora_thigh_replacement3[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED), // fix thigh
    gsDPSetTextureLUT(G_TT_RGBA16), // fix thigh
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005800, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    // gsSP2Triangles(12, 0, 13, 0, 14, 0, 15, 0),
    gsSPEndDisplayList(),
};

Gfx zora_right_thigh_commands[] = {
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005800, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_zoraVtx_0062C0[138], 9, 0),
};

Gfx zora_right_thigh_replacement[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED), // fix thigh
    gsDPSetTextureLUT(G_TT_RGBA16), // fix thigh
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005800, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_zoraVtx_0062C0[138], 9, 0),
    gsSPEndDisplayList(),
};

Gfx zora_left_thigh_commands[] = {
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005800, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_zoraVtx_0062C0[285], 9, 0),
};

Gfx zora_left_thigh_replacement[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED), // fix thigh
    gsDPSetTextureLUT(G_TT_RGBA16), // fix thigh
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005800, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_zoraVtx_0062C0[285], 9, 0),
    gsSPEndDisplayList(),
};

Gfx zora_waist_commands[] = {
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005A80, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
};

Gfx zora_waist_replacement[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(savedLink_005D80, G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(&env_color_dls[PLAYER_FORM_ZORA]),
    gsSPEndDisplayList(),
};

Gfx zora_head_commands[] = {
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005D00, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
};

Gfx zora_head_replacement[] = {
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(zora_base, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx zora_head_commands2[] = {
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
};

Gfx zora_head_replacement2[] = {
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

Gfx zora_hat_commands[] = {
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal256(object_link_zora_TLUT_005000),
    gsDPLoadTextureBlock(object_link_zora_Tex_005D00, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
};

Gfx zora_hat_replacement[] = {
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(zora_base, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPEndDisplayList(),
};

Gfx zora_hat_commands2[] = {
    gsSPVertex(&object_link_zoraVtx_0062C0[375], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(3, 2, 4, 0, 4, 5, 3, 0),
    gsSP2Triangles(4, 2, 6, 0, 6, 5, 4, 0),
    gsSP2Triangles(6, 2, 7, 0, 7, 2, 1, 0),
};

Gfx zora_hat_replacement2[] = {
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

void replace_zora(Gfx* toPatch, s32 curLimbIndex) {
    switch (curLimbIndex) {
        case LINK_ZORA_LIMB_RIGHT_THIGH:
        case LINK_ZORA_LIMB_LEFT_THIGH:
            replace_dl_commands_jump(toPatch, zora_thigh_commands, zora_thigh_replacement, ARRAY_COUNT(zora_thigh_commands));
            replace_dl_commands_jump(toPatch, zora_thigh_commands2, zora_thigh_replacement2, ARRAY_COUNT(zora_thigh_commands2));
            replace_dl_commands_jump(toPatch, zora_thigh_commands3, zora_thigh_replacement3, ARRAY_COUNT(zora_thigh_commands3));
            if (curLimbIndex == LINK_ZORA_LIMB_LEFT_THIGH) {
                replace_dl_commands_jump(toPatch, zora_left_thigh_commands, zora_left_thigh_replacement, ARRAY_COUNT(zora_left_thigh_commands));
            }
            else {
                replace_dl_commands_jump(toPatch, zora_right_thigh_commands, zora_right_thigh_replacement, ARRAY_COUNT(zora_right_thigh_commands));
            }
            break;
        case LINK_ZORA_LIMB_WAIST:
            replace_dl_commands_jump(toPatch, zora_waist_commands, zora_waist_replacement, ARRAY_COUNT(zora_waist_commands));
            break;
        case LINK_ZORA_LIMB_HEAD:
            replace_dl_commands_jump(toPatch, zora_head_commands, zora_head_replacement, ARRAY_COUNT(zora_head_commands));
            replace_dl_commands_jump(toPatch, zora_head_commands2, zora_head_replacement2, ARRAY_COUNT(zora_head_commands2));
            break;
        case LINK_ZORA_LIMB_HAT:
            replace_dl_commands_jump(toPatch, zora_hat_commands, zora_hat_replacement, ARRAY_COUNT(zora_hat_commands));
            replace_dl_commands_jump(toPatch, zora_hat_commands2, zora_hat_replacement2, ARRAY_COUNT(zora_hat_commands2));
            break;
        default:
            break;
    }
}