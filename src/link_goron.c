#include "recolor.h"
#include "dl_patching.h"

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

extern u64 object_link_goron_Tex_002780[];

u64 Goron_Tunic_I[] = {
#include "textures/goron_tunic.inc"
};

Gfx goron_texture_commands[] = {
    gsDPLoadTextureBlock(object_link_goron_Tex_002780, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 16, 0, G_TX_NOMIRROR |
        G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 3, 4, G_TX_NOLOD, G_TX_NOLOD)
};

Gfx goron_texture_replacement[] = {
    gsDPLoadTextureBlock(Goron_Tunic_I, G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0, G_TX_NOMIRROR |
                         G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(&prim_color_dls[PLAYER_FORM_GORON]),
    gsSPEndDisplayList(),
};

void replace_goron(Gfx* toPatch, s32 curLimbIndex) {
    switch (curLimbIndex) {
        case LINK_GORON_LIMB_WAIST:
            // Replace the white prim color in the waist DL with a jump to the current Goron color.
            patch_prim_color_with_dl(toPatch, 255, 255, 255, 255, &prim_color_dls[PLAYER_FORM_GORON][0]);
            replace_dl_commands_jump(toPatch, goron_texture_commands, goron_texture_replacement, ARRAY_COUNT(goron_texture_commands));
            break;
        case LINK_GORON_LIMB_HAT:
            replace_dl_commands_jump(toPatch, goron_texture_commands, goron_texture_replacement, ARRAY_COUNT(goron_texture_commands));
        default:
            break;
    }
}
