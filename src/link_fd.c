#include "modding.h"
#include "global.h"

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

Gfx gLinkFierceDeityLeftThighModifiedDL[] = {
    gsSPMatrix(0x0D000000, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_boyVtx_000C00[248], 1, 0),
    gsSPVertex(&object_link_boyVtx_000C00[249], 1, 1),
    gsSPVertex(&object_link_boyVtx_000C00[250], 2, 2),
    gsSPVertex(&object_link_boyVtx_000C00[252], 1, 4),
    gsSPVertex(&object_link_boyVtx_000C00[253], 3, 5),
    gsSPMatrix(0x0D000100, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
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
    gsDPSetPrimColor(0, 0x80, 250, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_boyVtx_000C00[256], 1, 8),
    gsSP1Triangle(1, 8, 4, 0),
    gsSPVertex(&object_link_boyVtx_000C00[257], 3, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(8, 9, 2, 0, 10, 2, 4, 0),
    gsSPVertex(&object_link_boyVtx_000C00[260], 1, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(8, 6, 0, 0),
    gsSPVertex(&object_link_boyVtx_000C00[261], 1, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(8, 0, 5, 0),
    gsSPVertex(&object_link_boyVtx_000C00[262], 2, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(4, 8, 9, 0),
    gsSPVertex(&object_link_boyVtx_000C00[264], 2, 8),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(2, 8, 9, 0),
    gsSPVertex(&object_link_boyVtx_000C00[266], 9, 8),
    gsSP2Triangles(3, 2, 8, 0, 5, 3, 9, 0),
    gsSP2Triangles(5, 10, 11, 0, 12, 13, 3, 0),
    gsSP2Triangles(14, 15, 7, 0, 7, 6, 16, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED), // fix
    gsDPSetTextureLUT(G_TT_RGBA16), // fix
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x003C),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_boyVtx_000C00[275], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_boyVtx_000C00[278], 3, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_boyVtx_000C00[281], 3, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_boyVtx_000C00[284], 9, 0),
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
    gsDPSetPrimColor(0, 0x80, 250, 255, 255, 255),
    gsSPVertex(&object_link_boyVtx_000C00[293], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 2, 1, 0),
    gsSPVertex(&object_link_boyVtx_000C00[297], 5, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityHatModifiedDL[] = {
    gsSPMatrix(0x0D0001C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_boyVtx_000C00[353], 2, 0),
    gsSPVertex(&object_link_boyVtx_000C00[355], 1, 2),
    gsSPVertex(&object_link_boyVtx_000C00[356], 3, 3),
    gsSPMatrix(0x0D000200, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    // gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    // gsDPSetTextureLUT(G_TT_RGBA16),
    // gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008128),
    // gsDPLoadTextureBlock_4b(object_link_boy_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
    //                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(Custom_FD_I, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_boyVtx_000C00[359], 18, 6),
    gsSP2Triangles(6, 0, 7, 0, 8, 9, 5, 0),
    gsSP2Triangles(3, 2, 10, 0, 11, 12, 2, 0),
    gsSP2Triangles(13, 4, 0, 0, 1, 5, 14, 0),
    gsSP2Triangles(15, 2, 1, 0, 16, 17, 1, 0),
    gsSP2Triangles(1, 18, 19, 0, 20, 5, 4, 0),
    gsSP2Triangles(21, 0, 3, 0, 22, 0, 23, 0),
    gsSPVertex(&object_link_boyVtx_000C00[377], 11, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(0, 3, 6, 0, 4, 7, 5, 0),
    gsSP2Triangles(8, 2, 1, 0, 0, 6, 1, 0),
    gsSP2Triangles(5, 8, 1, 0, 5, 6, 3, 0),
    gsSP2Triangles(3, 9, 4, 0, 5, 7, 8, 0),
    gsSP2Triangles(1, 6, 5, 0, 9, 3, 0, 0),
    gsSP2Triangles(10, 0, 2, 0, 9, 0, 10, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityHeadModifiedDL[] = {
    gsSPMatrix(0x0D000440, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_boyVtx_000C00[388], 6, 0),
    gsSPMatrix(0x0D0001C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_boyVtx_000C00[394], 7, 6),
    gsSP2Triangles(4, 6, 7, 0, 8, 2, 3, 0),
    gsSP2Triangles(5, 9, 10, 0, 0, 11, 12, 0),
    gsSPVertex(&object_link_boyVtx_000C00[401], 1, 6),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(6, 5, 0, 0),
    gsSPVertex(&object_link_boyVtx_000C00[402], 10, 6),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(6, 1, 4, 0, 7, 3, 5, 0),
    gsSP2Triangles(2, 8, 9, 0, 4, 10, 11, 0),
    gsSP2Triangles(12, 0, 13, 0, 14, 4, 2, 0),
    gsSP1Triangle(15, 0, 1, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(gLinkFierceDeityEyesTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_boyVtx_000C00[412], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_boyVtx_000C00[415], 32, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 3, 1, 4, 0),
    gsSP2Triangles(5, 6, 7, 0, 8, 9, 5, 0),
    gsSP2Triangles(10, 11, 12, 0, 0, 13, 4, 0),
    gsSP2Triangles(4, 1, 0, 0, 13, 7, 12, 0),
    gsSP2Triangles(13, 0, 8, 0, 7, 13, 8, 0),
    gsSP2Triangles(8, 5, 7, 0, 11, 4, 13, 0),
    gsSP2Triangles(11, 13, 12, 0, 14, 15, 6, 0),
    gsSP2Triangles(3, 16, 17, 0, 9, 18, 19, 0),
    gsSP2Triangles(9, 19, 20, 0, 21, 19, 22, 0),
    gsSP2Triangles(19, 21, 20, 0, 19, 18, 22, 0),
    gsSP2Triangles(18, 23, 22, 0, 5, 9, 20, 0),
    gsSP2Triangles(22, 23, 24, 0, 21, 22, 24, 0),
    gsSP2Triangles(25, 26, 27, 0, 27, 26, 24, 0),
    gsSP2Triangles(23, 28, 29, 0, 29, 28, 30, 0),
    gsSP2Triangles(24, 26, 21, 0, 25, 27, 30, 0),
    gsSP2Triangles(30, 27, 29, 0, 29, 27, 23, 0),
    gsSP2Triangles(23, 27, 24, 0, 2, 1, 31, 0),
    gsSP2Triangles(3, 31, 1, 0, 23, 2, 31, 0),
    gsSP2Triangles(23, 31, 17, 0, 31, 3, 17, 0),
    gsSP2Triangles(17, 16, 28, 0, 17, 28, 23, 0),
    gsSP1Triangle(5, 20, 14, 0),
    gsSPVertex(&object_link_boyVtx_000C00[447], 15, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
    gsSP1Triangle(12, 13, 14, 0),
    gsDPPipeSync(),
    // gsDPSetTextureLUT(G_TT_RGBA16),
    // gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008128),
    // gsDPLoadTextureBlock_4b(object_link_boy_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
    //                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(Custom_FD_I, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_boyVtx_000C00[462], 11, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 5, 6, 0, 6, 5, 7, 0),
    gsSP2Triangles(7, 5, 8, 0, 9, 7, 8, 0),
    gsSP1Triangle(9, 8, 10, 0),
    gsSPVertex(&object_link_boyVtx_000C00[473], 3, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_boyVtx_000C00[476], 20, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 2, 0),
    gsSP2Triangles(2, 4, 0, 0, 5, 6, 7, 0),
    gsSP2Triangles(6, 5, 8, 0, 9, 8, 10, 0),
    gsSP2Triangles(1, 10, 11, 0, 1, 12, 10, 0),
    gsSP2Triangles(2, 1, 11, 0, 12, 9, 10, 0),
    gsSP2Triangles(2, 13, 3, 0, 10, 13, 11, 0),
    gsSP2Triangles(10, 5, 13, 0, 8, 5, 10, 0),
    gsSP2Triangles(14, 15, 16, 0, 6, 8, 9, 0),
    gsSP2Triangles(17, 15, 7, 0, 16, 15, 18, 0),
    gsSP2Triangles(15, 17, 18, 0, 6, 18, 17, 0),
    gsSP2Triangles(6, 19, 18, 0, 6, 9, 19, 0),
    gsSP1Triangle(17, 7, 6, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED), // fix
    gsDPSetTextureLUT(G_TT_RGBA16), // fix
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008188),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_00A708, G_IM_FMT_CI, 32, 32, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_boyVtx_000C00[496], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 0, 0),
    gsSP2Triangles(5, 6, 7, 0, 8, 9, 10, 0),
    gsSP2Triangles(11, 12, 13, 0, 14, 15, 16, 0),
    gsSP2Triangles(17, 18, 19, 0, 17, 19, 20, 0),
    gsSP2Triangles(21, 22, 23, 0, 24, 25, 26, 0),
    gsSP2Triangles(2, 7, 6, 0, 7, 21, 27, 0),
    gsSP1Triangle(28, 29, 30, 0),
    gsSPVertex(&object_link_boyVtx_000C00[527], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 8, 9, 0),
    gsSP2Triangles(10, 11, 12, 0, 13, 14, 15, 0),
    gsSP2Triangles(4, 6, 16, 0, 17, 18, 19, 0),
    gsSP2Triangles(20, 21, 14, 0, 22, 23, 24, 0),
    gsSP2Triangles(25, 26, 27, 0, 25, 27, 28, 0),
    gsSP2Triangles(28, 27, 29, 0, 29, 22, 30, 0),
    gsSP2Triangles(29, 30, 28, 0, 30, 22, 24, 0),
    gsSPVertex(&object_link_boyVtx_000C00[558], 28, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 15, 16, 17, 0),
    gsSP2Triangles(18, 19, 7, 0, 20, 21, 22, 0),
    gsSP2Triangles(7, 19, 4, 0, 10, 23, 11, 0),
    gsSP2Triangles(24, 25, 26, 0, 27, 25, 24, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(gLinkFierceDeityMouthTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_boyVtx_000C00[586], 13, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSP2Triangles(4, 5, 2, 0, 4, 2, 1, 0),
    gsSP2Triangles(6, 7, 8, 0, 8, 7, 9, 0),
    gsSP2Triangles(10, 1, 11, 0, 12, 11, 4, 0),
    gsSP1Triangle(2, 5, 3, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008188),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_00A708, G_IM_FMT_CI, 32, 32, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 253, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_boyVtx_000C00[599], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(gLinkFierceDeityEarTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_boyVtx_000C00[602], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&object_link_boyVtx_000C00[605], 10, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(5, 6, 3, 0, 5, 7, 6, 0),
    gsSP1Triangle(8, 9, 1, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityRightShoulderModifiedDL[] = {
    gsSPMatrix(0x0D000440, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_boyVtx_000C00[893], 3, 0),
    gsSPVertex(&object_link_boyVtx_000C00[896], 2, 3),
    gsSPMatrix(0x0D000340, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    // gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    // gsDPSetTextureLUT(G_TT_RGBA16),
    // gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008128),
    // gsDPLoadTextureBlock_4b(object_link_boy_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
    //                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(Custom_FD_I, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_boyVtx_000C00[898], 15, 5),
    gsSP2Triangles(2, 5, 6, 0, 7, 8, 1, 0),
    gsSP2Triangles(3, 9, 10, 0, 11, 0, 2, 0),
    gsSP2Triangles(1, 12, 2, 0, 13, 14, 3, 0),
    gsSP2Triangles(15, 16, 2, 0, 17, 1, 4, 0),
    gsSP2Triangles(18, 4, 3, 0, 3, 0, 19, 0),
    gsSPVertex(&object_link_boyVtx_000C00[913], 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 0, 2, 9, 0),
    gsSP2Triangles(8, 7, 10, 0, 10, 9, 8, 0),
    gsSP2Triangles(9, 11, 0, 0, 10, 11, 9, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED), // fix
    gsDPSetTextureLUT(G_TT_RGBA16), // fix
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 190, 178, 178, 255),
    gsSPVertex(&object_link_boyVtx_000C00[925], 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(3, 2, 5, 0, 3, 5, 4, 0),
    gsSP2Triangles(8, 9, 7, 0, 1, 0, 9, 0),
    gsSP2Triangles(9, 8, 1, 0, 7, 6, 8, 0),
    gsSPEndDisplayList(),
};

Gfx gLinkFierceDeityLeftShoulderModifiedDL[] = {
    gsSPMatrix(0x0D000440, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_boyVtx_000C00[719], 4, 0),
    gsSPVertex(&object_link_boyVtx_000C00[723], 1, 4),
    gsSPMatrix(0x0D000280, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    // gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    // gsDPSetTextureLUT(G_TT_RGBA16),
    // gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008128),
    // gsDPLoadTextureBlock_4b(object_link_boy_Tex_008C88, G_IM_FMT_CI, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
    //                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(Custom_FD_I, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 15, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPVertex(&object_link_boyVtx_000C00[724], 15, 5),
    gsSP2Triangles(5, 6, 3, 0, 2, 7, 8, 0),
    gsSP2Triangles(9, 10, 4, 0, 3, 1, 11, 0),
    gsSP2Triangles(3, 12, 2, 0, 4, 13, 14, 0),
    gsSP2Triangles(3, 15, 16, 0, 0, 2, 17, 0),
    gsSP2Triangles(4, 0, 18, 0, 19, 1, 4, 0),
    gsSPVertex(&object_link_boyVtx_000C00[739], 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 9, 0, 2, 0),
    gsSP2Triangles(10, 7, 6, 0, 6, 9, 10, 0),
    gsSP2Triangles(2, 11, 9, 0, 9, 11, 10, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED), // fix
    gsDPSetTextureLUT(G_TT_RGBA16), // fix
    gsDPLoadTLUT_pal16(15, object_link_boy_TLUT_008108),
    gsDPLoadTextureBlock_4b(object_link_boy_Tex_008408, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMIRROR
                            | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x003C),
    gsSPVertex(&object_link_boyVtx_000C00[751], 7, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 3, 2, 6, 0),
    gsSP1Triangle(3, 6, 5, 0),
    gsSPVertex(&object_link_boyVtx_000C00[758], 7, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 4, 0),
    gsSP2Triangles(5, 4, 3, 0, 4, 6, 0, 0),
    gsSP1Triangle(0, 6, 1, 0),
    gsSPEndDisplayList(),
};

extern LodLimb gLinkFierceDeityRootLimb;

extern LodLimb gLinkFierceDeityWaistLimb;

extern LodLimb gLinkFierceDeityLowerRootLimb;

LodLimb gLinkFierceDeityRightThighLimbMod = { 
    { -399, 69, -249 }, LINK_FIERCE_DEITY_LIMB_RIGHT_SHIN - 1, LINK_FIERCE_DEITY_LIMB_LEFT_THIGH - 1,
    { gLinkFierceDeityRightThighModifiedDL, gLinkFierceDeityRightThighModifiedDL }
};

extern LodLimb gLinkFierceDeityRightShinLimb;

extern LodLimb gLinkFierceDeityRightFootLimb;

LodLimb gLinkFierceDeityLeftThighLimbMod = { 
    { -396, 76, 264 }, LINK_FIERCE_DEITY_LIMB_LEFT_SHIN - 1, LIMB_DONE,
    { gLinkFierceDeityLeftThighModifiedDL, gLinkFierceDeityLeftThighModifiedDL }
};

extern LodLimb gLinkFierceDeityLeftShinLimb;

extern LodLimb gLinkFierceDeityLeftFootLimb;

extern LodLimb gLinkFierceDeityUpperRootLimb;

LodLimb gLinkFierceDeityHeadLimbMod = { 
    { 1392, -259, 0 }, LINK_FIERCE_DEITY_LIMB_HAT - 1, LINK_FIERCE_DEITY_LIMB_COLLAR - 1,
    { gLinkFierceDeityHeadModifiedDL, gLinkFierceDeityHeadModifiedDL }
};

LodLimb gLinkFierceDeityHatLimbMod = { 
    { -298, -700, 0 }, LIMB_DONE, LIMB_DONE,
    { gLinkFierceDeityHatModifiedDL, gLinkFierceDeityHatModifiedDL }
};

extern LodLimb gLinkFierceDeityCollarLimb;

LodLimb gLinkFierceDeityLeftShoulderLimbMod = { 
    { 1039, -172, 680 }, LINK_FIERCE_DEITY_LIMB_LEFT_FOREARM - 1, LINK_FIERCE_DEITY_LIMB_RIGHT_SHOULDER - 1,
    { gLinkFierceDeityLeftShoulderModifiedDL, gLinkFierceDeityLeftShoulderModifiedDL }
};

extern LodLimb gLinkFierceDeityLeftForearmLimb;

extern LodLimb gLinkFierceDeityLeftHandLimb;

LodLimb gLinkFierceDeityRightShoulderLimbMod = { 
    { 1039, -173, -680 }, LINK_FIERCE_DEITY_LIMB_RIGHT_FOREARM - 1, LINK_FIERCE_DEITY_LIMB_SHEATH - 1,
    { gLinkFierceDeityRightShoulderModifiedDL, gLinkFierceDeityRightShoulderModifiedDL }
};

extern LodLimb gLinkFierceDeityRightForearmLimb;

extern LodLimb gLinkFierceDeityRightHandLimb;

extern LodLimb gLinkFierceDeitySheathLimb;

extern LodLimb gLinkFierceDeityTorsoLimb;

void* gLinkFierceDeitySkelLimbsMod[] = {
    &gLinkFierceDeityRootLimb, /* LINK_FIERCE_DEITY_LIMB_ROOT */
    &gLinkFierceDeityWaistLimb, /* LINK_FIERCE_DEITY_LIMB_WAIST */
    &gLinkFierceDeityLowerRootLimb, /* LINK_FIERCE_DEITY_LIMB_LOWER_ROOT */
    &gLinkFierceDeityRightThighLimbMod, /* LINK_FIERCE_DEITY_LIMB_RIGHT_THIGH */
    &gLinkFierceDeityRightShinLimb, /* LINK_FIERCE_DEITY_LIMB_RIGHT_SHIN */
    &gLinkFierceDeityRightFootLimb, /* LINK_FIERCE_DEITY_LIMB_RIGHT_FOOT */
    &gLinkFierceDeityLeftThighLimbMod, /* LINK_FIERCE_DEITY_LIMB_LEFT_THIGH */
    &gLinkFierceDeityLeftShinLimb, /* LINK_FIERCE_DEITY_LIMB_LEFT_SHIN */
    &gLinkFierceDeityLeftFootLimb, /* LINK_FIERCE_DEITY_LIMB_LEFT_FOOT */
    &gLinkFierceDeityUpperRootLimb, /* LINK_FIERCE_DEITY_LIMB_UPPER_ROOT */
    &gLinkFierceDeityHeadLimbMod, /* LINK_FIERCE_DEITY_LIMB_HEAD */
    &gLinkFierceDeityHatLimbMod, /* LINK_FIERCE_DEITY_LIMB_HAT */
    &gLinkFierceDeityCollarLimb, /* LINK_FIERCE_DEITY_LIMB_COLLAR */
    &gLinkFierceDeityLeftShoulderLimbMod, /* LINK_FIERCE_DEITY_LIMB_LEFT_SHOULDER */
    &gLinkFierceDeityLeftForearmLimb, /* LINK_FIERCE_DEITY_LIMB_LEFT_FOREARM */
    &gLinkFierceDeityLeftHandLimb, /* LINK_FIERCE_DEITY_LIMB_LEFT_HAND */
    &gLinkFierceDeityRightShoulderLimbMod, /* LINK_FIERCE_DEITY_LIMB_RIGHT_SHOULDER */
    &gLinkFierceDeityRightForearmLimb, /* LINK_FIERCE_DEITY_LIMB_RIGHT_FOREARM */
    &gLinkFierceDeityRightHandLimb, /* LINK_FIERCE_DEITY_LIMB_RIGHT_HAND */
    &gLinkFierceDeitySheathLimb, /* LINK_FIERCE_DEITY_LIMB_SHEATH */
    &gLinkFierceDeityTorsoLimb, /* LINK_FIERCE_DEITY_LIMB_TORSO */
};

FlexSkeletonHeader gLinkFierceDeitySkelMod = { 
    { gLinkFierceDeitySkelLimbsMod, ARRAY_COUNT(gLinkFierceDeitySkelLimbsMod) }, 18
};