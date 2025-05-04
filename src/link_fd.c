#include "modding.h"
#include "global.h"
#include "recolor.h"
#include "dl_patching.h"

typedef enum LinkFierceDeityLimb {
    /* 0x00 */ LINK_FIERCE_DEITY_LIMB_NONE,
    /* 0x01 */ LINK_FIERCE_DEITY_LIMB_ROOT,
    /* 0x02 */ LINK_FIERCE_DEITY_LIMB_WAIST,
    /* 0x03 */ LINK_FIERCE_DEITY_LIMB_LOWER_ROOT,
    /* 0x04 */ LINK_FIERCE_DEITY_LIMB_RIGHT_THIGH,
    /* 0x05 */ LINK_FIERCE_DEITY_LIMB_RIGHT_SHIN,
    /* 0x06 */ LINK_FIERCE_DEITY_LIMB_RIGHT_FOOT,
    /* 0x07 */ LINK_FIERCE_DEITY_LIMB_LEFT_THIGH,
    /* 0x08 */ LINK_FIERCE_DEITY_LIMB_LEFT_SHIN,
    /* 0x09 */ LINK_FIERCE_DEITY_LIMB_LEFT_FOOT,
    /* 0x0A */ LINK_FIERCE_DEITY_LIMB_UPPER_ROOT,
    /* 0x0B */ LINK_FIERCE_DEITY_LIMB_HEAD,
    /* 0x0C */ LINK_FIERCE_DEITY_LIMB_HAT,
    /* 0x0D */ LINK_FIERCE_DEITY_LIMB_COLLAR,
    /* 0x0E */ LINK_FIERCE_DEITY_LIMB_LEFT_SHOULDER,
    /* 0x0F */ LINK_FIERCE_DEITY_LIMB_LEFT_FOREARM,
    /* 0x10 */ LINK_FIERCE_DEITY_LIMB_LEFT_HAND,
    /* 0x11 */ LINK_FIERCE_DEITY_LIMB_RIGHT_SHOULDER,
    /* 0x12 */ LINK_FIERCE_DEITY_LIMB_RIGHT_FOREARM,
    /* 0x13 */ LINK_FIERCE_DEITY_LIMB_RIGHT_HAND,
    /* 0x14 */ LINK_FIERCE_DEITY_LIMB_SHEATH,
    /* 0x15 */ LINK_FIERCE_DEITY_LIMB_TORSO,
    /* 0x16 */ LINK_FIERCE_DEITY_LIMB_MAX
} LinkFierceDeityLimb;

extern Vtx object_link_boyVtx_000C00[];
extern u64 object_link_boy_TLUT_008128[];
extern u64 object_link_boy_Tex_008C88[];
extern u64 object_link_boy_TLUT_008108[];
extern u64 object_link_boy_Tex_008408[];
extern u64 gLinkFierceDeityEyesTex[];
extern u64 object_link_boy_TLUT_008188[];
extern u64 object_link_boy_Tex_00A708[];
extern u64 gLinkFierceDeityMouthTex[];
extern u64 gLinkFierceDeityEarTex[];

u64 Custom_FD_I[] = {
#include "textures/fd_tunic.inc"
};

Gfx gLinkFierceDeityRightThighModifiedDL[] = {
    gsSPMatrix(0x0D000000, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_boyVtx_000C00[97], 2, 0),
    gsSPVertex(&object_link_boyVtx_000C00[99], 6, 2),
    gsSPMatrix(0x0D000040, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    // gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    // gsDPSetTextureLUT(G_TT_RGBA16),
    // gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008128),
    // gsDPLoadTextureBlock_4b(object_link_boy_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
    //                         | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(Custom_FD_I, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_boyVtx_000C00[105], 1, 8),
    gsSP1Triangle(4, 8, 1, 0),
    gsSPVertex(&object_link_boyVtx_000C00[106], 3, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(4, 2, 8, 0, 4, 9, 10, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(5, 0, 6, 0),
    gsSPVertex(&object_link_boyVtx_000C00[109], 1, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(5, 6, 8, 0),
    gsSPVertex(&object_link_boyVtx_000C00[110], 2, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(8, 9, 4, 0),
    gsSPVertex(&object_link_boyVtx_000C00[112], 11, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(8, 9, 2, 0, 10, 2, 3, 0),
    gsSP2Triangles(11, 12, 3, 0, 13, 3, 5, 0),
    gsSP2Triangles(3, 14, 15, 0, 7, 16, 17, 0),
    gsSP1Triangle(18, 6, 7, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED), // fix
    gsDPSetTextureLUT(G_TT_RGBA16), // fix
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x003C),
    gsSPVertex(&object_link_boyVtx_000C00[123], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_boyVtx_000C00[126], 3, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_boyVtx_000C00[129], 3, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_boyVtx_000C00[132], 9, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 5, 6, 0, 4, 7, 8, 0),
    gsSP2Triangles(4, 8, 5, 0, 7, 0, 2, 0),
    gsSP1Triangle(7, 2, 8, 0),
    gsDPPipeSync(),
    // gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008128),
    // gsDPLoadTextureBlock_4b(object_link_boy_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
    //                         | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(Custom_FD_I, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_boyVtx_000C00[141], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
    gsSPVertex(&object_link_boyVtx_000C00[145], 5, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSPEndDisplayList(),
};

Gfx fd_thigh_commands[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008128),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
};

Gfx fd_thigh_replacement[]= {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(Custom_FD_I, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(&env_color_dls[PLAYER_FORM_FIERCE_DEITY]),
    gsSPEndDisplayList(),
};

Gfx fd_thigh_commands2[] = {
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x003C),
};

Gfx fd_thigh_replacement2[]= {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED), // fix
    gsDPSetTextureLUT(G_TT_RGBA16), // fix
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x003C),
    gsSPEndDisplayList(),
};

Gfx fd_thigh_commands3[] = {
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 5, 6, 0, 4, 7, 8, 0),
    gsSP2Triangles(4, 8, 5, 0, 7, 0, 2, 0),
    gsSP1Triangle(7, 2, 8, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008128),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
};

Gfx fd_thigh_replacement3[] = {
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 5, 6, 0, 4, 7, 8, 0),
    gsSP2Triangles(4, 8, 5, 0, 7, 0, 2, 0),
    gsSP1Triangle(7, 2, 8, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(Custom_FD_I, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(&env_color_dls[PLAYER_FORM_FIERCE_DEITY]),
    gsSPEndDisplayList(),
};

Gfx fd_hat_commands[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008128),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
};

Gfx fd_hat_replacement[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(Custom_FD_I, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(&env_color_dls[PLAYER_FORM_FIERCE_DEITY]),
    gsSPEndDisplayList(),
};

Gfx fd_head_commands[] = {
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008128),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
};

Gfx fd_head_replacement[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(Custom_FD_I, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(&env_color_dls[PLAYER_FORM_FIERCE_DEITY]),
    gsSPEndDisplayList(),
};

Gfx fd_head_commands2[] = {
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008188),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_00A708, G_IM_FMT_CI, 32, 32, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_boyVtx_000C00[496], 32, 0),
};

Gfx fd_head_replacement2[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED), // fix
    gsDPSetTextureLUT(G_TT_RGBA16), // fix
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008188),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_00A708, G_IM_FMT_CI, 32, 32, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_boyVtx_000C00[496], 32, 0),
    gsSPEndDisplayList(),
};

Gfx fd_right_shoulder_commands[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008128),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
};

Gfx fd_right_shoulder_replacement[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(Custom_FD_I, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(&env_color_dls[PLAYER_FORM_FIERCE_DEITY]),
    gsSPEndDisplayList(),
};

Gfx fd_right_shoulder_commands2[] = {
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 190, 178, 178, 255),
};

Gfx fd_right_shoulder_replacement2[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED), // fix
    gsDPSetTextureLUT(G_TT_RGBA16), // fix
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 190, 178, 178, 255),
    gsSPEndDisplayList(),
};

Gfx fd_left_shoulder_commands[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008128),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
};

Gfx fd_left_shoulder_replacement[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(Custom_FD_I, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(&env_color_dls[PLAYER_FORM_FIERCE_DEITY]),
    gsSPEndDisplayList(),
};

Gfx fd_left_shoulder_commands2[] = {
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x003C),
};

Gfx fd_left_shoulder_replacement2[] = {
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED), // fix
    gsDPSetTextureLUT(G_TT_RGBA16), // fix
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x003C),
    gsSPEndDisplayList(),
};

void replace_fd(Gfx* toPatch, s32 curLimbIndex) {
    switch (curLimbIndex) {
        case LINK_FIERCE_DEITY_LIMB_LEFT_THIGH:
        case LINK_FIERCE_DEITY_LIMB_RIGHT_THIGH:
            replace_dl_commands_jump(toPatch, fd_thigh_commands, fd_thigh_replacement, ARRAY_COUNT(fd_thigh_commands));
            replace_dl_commands_jump(toPatch, fd_thigh_commands2, fd_thigh_replacement2, ARRAY_COUNT(fd_thigh_commands2));
            replace_dl_commands_jump(toPatch, fd_thigh_commands3, fd_thigh_replacement3, ARRAY_COUNT(fd_thigh_commands3));
            break;
        case LINK_FIERCE_DEITY_LIMB_HAT:
            replace_dl_commands_jump(toPatch, fd_hat_commands, fd_hat_replacement, ARRAY_COUNT(fd_hat_commands));
            break;
        case LINK_FIERCE_DEITY_LIMB_HEAD:
            replace_dl_commands_jump(toPatch, fd_head_commands, fd_head_replacement, ARRAY_COUNT(fd_head_commands));
            replace_dl_commands_jump(toPatch, fd_head_commands2, fd_head_replacement2, ARRAY_COUNT(fd_head_commands2));
            break;
        case LINK_FIERCE_DEITY_LIMB_RIGHT_SHOULDER:
            replace_dl_commands_jump(toPatch, fd_right_shoulder_commands, fd_right_shoulder_replacement, ARRAY_COUNT(fd_right_shoulder_commands));
            replace_dl_commands_jump(toPatch, fd_right_shoulder_commands2, fd_right_shoulder_replacement2, ARRAY_COUNT(fd_right_shoulder_commands2));
            break;
        case LINK_FIERCE_DEITY_LIMB_LEFT_SHOULDER:
            replace_dl_commands_jump(toPatch, fd_left_shoulder_commands, fd_left_shoulder_replacement, ARRAY_COUNT(fd_left_shoulder_commands));
            replace_dl_commands_jump(toPatch, fd_left_shoulder_commands2, fd_left_shoulder_replacement2, ARRAY_COUNT(fd_left_shoulder_commands2));
        default:
            break;
    }
}