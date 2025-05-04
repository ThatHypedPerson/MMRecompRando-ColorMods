#include "recolor.h"
#include "dl_patching.h"

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

extern u64 object_link_nuts_TLUT_003EB0[];
extern u64 object_link_nuts_Tex_0042B0[];
extern u64 object_link_nuts_Tex_0043B0[];

Gfx deku_hat_commands[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal256(object_link_nuts_TLUT_003EB0),
    gsDPLoadTextureBlock(object_link_nuts_Tex_0043B0, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
};

Gfx deku_hat_replacement[] = {
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(savedLink_005C40, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 0, 181, 57, 255),
    gsSPDisplayList(&env_color_dls[PLAYER_FORM_DEKU]),
    gsSPEndDisplayList(),
};

Gfx deku_head_commands[] = {
    gsDPLoadTLUT_pal256(object_link_nuts_TLUT_003EB0),
    gsDPLoadTextureBlock(object_link_nuts_Tex_0043B0, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
};

Gfx deku_head_replacement[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(savedLink_005C40, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(&env_color_dls[PLAYER_FORM_DEKU]),
    gsSPEndDisplayList(),
};

Gfx deku_waist_commands[] = {
    gsDPLoadTLUT_pal256(object_link_nuts_TLUT_003EB0),
    gsDPLoadTextureBlock(object_link_nuts_Tex_0043B0, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
};

Gfx deku_waist_replacement[] = {
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(savedLink_005C40, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(&prim_color_dls[PLAYER_FORM_DEKU]),
    gsSPEndDisplayList(),
};

void replace_deku(Gfx* toPatch, s32 curLimbIndex) {
    switch (curLimbIndex) {
        case LINK_DEKU_LIMB_HAT:
            replace_dl_commands_jump(toPatch, deku_hat_commands, deku_hat_replacement, ARRAY_COUNT(deku_hat_commands));
            break;
        case LINK_DEKU_LIMB_WAIST:
            replace_dl_commands_jump(toPatch, deku_waist_commands, deku_waist_replacement, ARRAY_COUNT(deku_waist_commands));
            break;
        case LINK_DEKU_LIMB_HEAD:
            replace_dl_commands_jump(toPatch, deku_head_commands, deku_head_replacement, ARRAY_COUNT(deku_head_commands));
            break;
        default:
            break;
    }
}