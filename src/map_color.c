#include "modding.h"
#include "global.h"

#include "recolor.h"

// missing graphics stuff
static u32 sLoadTextureBlock_siz[] = {
    G_IM_SIZ_4b,
    G_IM_SIZ_8b,
    G_IM_SIZ_16b,
    G_IM_SIZ_32b,
};
static u32 sLoadTextureBlock_siz_LOAD_BLOCK[] = {
    G_IM_SIZ_4b_LOAD_BLOCK,
    G_IM_SIZ_8b_LOAD_BLOCK,
    G_IM_SIZ_16b_LOAD_BLOCK,
    G_IM_SIZ_32b_LOAD_BLOCK,
};
static u32 sLoadTextureBlock_siz_INCR[] = {
    G_IM_SIZ_4b_INCR,
    G_IM_SIZ_8b_INCR,
    G_IM_SIZ_16b_INCR,
    G_IM_SIZ_32b_INCR,
};
static u32 sLoadTextureBlock_siz_SHIFT[] = {
    G_IM_SIZ_4b_SHIFT,
    G_IM_SIZ_8b_SHIFT,
    G_IM_SIZ_16b_SHIFT,
    G_IM_SIZ_32b_SHIFT,
};
static u32 sLoadTextureBlock_siz_BYTES[] = {
    G_IM_SIZ_4b_BYTES,
    G_IM_SIZ_8b_BYTES,
    G_IM_SIZ_16b_BYTES,
    G_IM_SIZ_32b_BYTES,
};
static u32 sLoadTextureBlock_siz_LINE_BYTES[] = {
    G_IM_SIZ_4b_LINE_BYTES,
    G_IM_SIZ_8b_LINE_BYTES,
    G_IM_SIZ_16b_LINE_BYTES,
    G_IM_SIZ_32b_LINE_BYTES,
};

/**
 * Implements a version of gDPLoadTextureBlock using table lookups instead of token pasting, to allow values to be
 * passed into `siz` during runtime.
 */
#define gDPLoadTextureBlock_Runtime(pkt, timg, fmt, siz, width, height, pal, cms, cmt, masks, maskt, shifts, shiftt)   \
    _DW({                                                                                                              \
        gDPSetTextureImage(pkt, fmt, sLoadTextureBlock_siz_LOAD_BLOCK[siz], 1, timg);                                  \
        gDPSetTile(pkt, fmt, sLoadTextureBlock_siz_LOAD_BLOCK[siz], 0, 0, G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms,   \
                   masks, shifts);                                                                                     \
        gDPLoadSync(pkt);                                                                                              \
        gDPLoadBlock(pkt, G_TX_LOADTILE, 0, 0,                                                                         \
                     (((width) * (height) + sLoadTextureBlock_siz_INCR[siz]) >> sLoadTextureBlock_siz_SHIFT[siz]) - 1, \
                     CALC_DXT(width, sLoadTextureBlock_siz_BYTES[siz]));                                               \
        gDPPipeSync(pkt);                                                                                              \
        gDPSetTile(pkt, fmt, sLoadTextureBlock_siz[siz], (((width)*sLoadTextureBlock_siz_LINE_BYTES[siz]) + 7) >> 3,   \
                   0, G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts);                                   \
        gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0, ((width)-1) << G_TEXTURE_IMAGE_FRAC,                                \
                       ((height)-1) << G_TEXTURE_IMAGE_FRAC);                                                          \
    })

Mtx* Matrix_Finalize(GraphicsContext* gfxCtx) {
    return Matrix_ToMtx(GRAPH_ALLOC(gfxCtx, sizeof(Mtx)));
}

#define MATRIX_FINALIZE_AND_LOAD(pkt, gfxCtx) \
    gSPMatrix(pkt, Matrix_Finalize(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW)

// actual recoloring starts here

typedef struct {
    /* 0x0 */ u16 mapId;
    /* 0x2 */ s16 centerX;
    /* 0x4 */ s16 floorY;
    /* 0x6 */ s16 centerZ;
    /* 0x8 */ u16 flags;
} MapDataRoom; // size = 0xA

typedef struct {
    /* 0x0 */ s16 room;
    /* 0x2 */ s16 chestFlagId;
    /* 0x4 */ s16 x;
    /* 0x6 */ s16 y;
    /* 0x8 */ s16 z;
} MapDataChest; // size = 0xA

typedef struct {
    /* 0x0 */ MapDataRoom* rooms;
    /* 0x4 */ s16 scale;
} MapDataScene; // size  = 0x8

typedef struct {
    /* 0x00 */ MapDataScene* mapDataScene;
    /* 0x04 */ s32 curRoom;
    /* 0x08 */ s16 minimapBaseX;
    /* 0x0A */ s16 minimapBaseY;
    /* 0x0C */ s16 minimapCurX;
    /* 0x0E */ s16 minimapCurY;
    /* 0x10 */ TexturePtr minimapCurTex; // gameplay cur minimap room
    /* 0x14 */ s32 prevRoom;
    /* 0x18 */ TexturePtr minimapPrevTex;
    /* 0x1C */ s16 minimapPrevX; // for room swap animation
    /* 0x1E */ s16 minimapPrevY; // for room swap animation
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 swapAnimTimer;
    /* 0x28 */ void* texBuff0;
    /* 0x2C */ void* texBuff1;
    /* 0x30 */ s16 sceneMinX; //scene minBounds.x
    /* 0x32 */ s16 sceneMinZ; //scene minBounds.z
    /* 0x34 */ s16 sceneWidth; //scene boundsWidth.x
    /* 0x36 */ s16 sceneHeight; //scene boundsWidth.z
    /* 0x38 */ s16 sceneMidX; //scene boundsMidpoint.x
    /* 0x3A */ s16 sceneMidZ; //scene boundsMidpoint.z
    /* 0x3C */ s16* roomStoreyList; // list of lowest storey each room crosses
    /* 0x40 */ s16 numStoreys; // number of distinct storeys
    /* 0x42 */ s16 pauseMapCurStorey;
    /* 0x44 */ s16 bottomStorey; // configures what storey 0 is displayed as
    /* 0x48 */ s16* storeyYList; // list of min Ys for each storey
    /* 0x4C */ s16 timer;
    /* 0x50 */ s32 numChests;
    /* 0x54 */ MapDataChest* mapDataChests;
    /* 0x58 */ s16 bossRoomStorey;
    /* 0x5A */ s16 unk5A;
} MapDisp; // size = 0x5C

#define MAP_DATA_NO_MAP 0xFFFF

// extern MapDisp sMapDisp;
extern MapDisp D_801BEBB8;

// extern Gfx gCompassArrowDL[];
extern Gfx gameplay_keep_DL_01ED00[];
extern u64 gMapChestIconTex[];

static Color_RGBA8 sMinimapActorCategoryColors[12] = {
    { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 0, 255, 0, 255 },     { 255, 255, 255, 255 },
    { 255, 255, 255, 255 }, { 255, 0, 0, 255 },     { 255, 255, 255, 255 }, { 255, 255, 255, 255 },
    { 255, 255, 255, 255 }, { 255, 0, 0, 255 },     { 255, 255, 255, 255 }, { 255, 255, 255, 255 },
};

// void MapDisp_GetMapOffset(MapDataRoom* mapDataRoom, s32* offsetX, s32* offsetY);
// void MapDisp_GetMapTexDim(MapDataRoom* mapDataRoom, s32* width, s32* height);
// void MapDisp_GetMapScale(MapDataRoom* mapDataRoom, s32* scale);
// s32 MapDisp_IsDataRotated(PlayState* play);
// f32 MapDisp_GetStoreyY(f32 checkY)
void func_801030F4(MapDataRoom* mapDataRoom, s32* offsetX, s32* offsetY);
void func_80103090(MapDataRoom* mapDataRoom, s32* width, s32* height);
void func_801030B4(MapDataRoom* mapDataRoom, s32* scale);
s32 func_801039EC(PlayState* play);
f32 func_80102F9C(f32 checkY);

// extern Color_RGBA8 sMapColorTable[];
extern Color_RGBA8 D_801BED40[];

// RECOMP_PATCH void MapData_GetMapColor(s32 colorIndex, Color_RGBA8* color) {
RECOMP_PATCH void func_801094A0(s32 colorIndex, Color_RGBA8* color) {
    // *color = sMapColorTable[colorIndex];
    // Color_RGBA8 mapRecolor = {mapColor.r, mapColor.g, mapColor.b, sMapColorTable[colorIndex].a};
    Color_RGBA8 mapRecolor = {mapColor.r, mapColor.g, mapColor.b, D_801BED40[colorIndex].a};
    *color = mapRecolor;
}

// void MapDisp_Minimap_DrawActorIcon(PlayState* play, Actor* actor) {
RECOMP_PATCH void func_80103A58(PlayState* play, Actor* actor) {
    MapDataRoom* mapDataRoom;
    s32 posX;
    s32 posY;
    s32 texOffsetX;
    s32 texOffsetY;
    s32 texWidth;
    s32 texHeight;
    f32 scaleFrac;
    f32 unused1;
    f32 unused2;
    Player* player = GET_PLAYER(play);
    s32 scale;

    MapDisp sMapDisp = D_801BEBB8; // temp

    // inferred from `MapDisp_Minimap_DrawDoorActor`
    unused1 = fabsf(player->actor.world.pos.y - actor->world.pos.y);
    unused2 = 1.0f - (1 / 350.0f) * unused1;

    if (unused2 < 0.0f) {
        unused2 = 0.0f;
    }

    mapDataRoom = &sMapDisp.mapDataScene->rooms[sMapDisp.curRoom];
    if (mapDataRoom->mapId == MAP_DATA_NO_MAP) {
        return;
    }

    // MapDisp_GetMapOffset(mapDataRoom, &texOffsetX, &texOffsetY);
    func_801030F4(mapDataRoom, &texOffsetX, &texOffsetY);
    // MapDisp_GetMapTexDim(mapDataRoom, &texWidth, &texHeight);
    func_80103090(mapDataRoom, &texWidth, &texHeight);

    scale = sMapDisp.mapDataScene->scale;
    if (sMapDisp.mapDataScene->scale == 0) {
        scale = 20;
    } else if (sMapDisp.mapDataScene->scale == -1) {
        s32 scaleTemp;

        // MapDisp_GetMapScale(mapDataRoom, &scaleTemp);
        func_801030B4(mapDataRoom, &scaleTemp);
        scale = scaleTemp;
    }

    scaleFrac = 1.0f / scale;
    // if (!MapDisp_IsDataRotated(play)) {
    if (!func_801039EC(play)) {
        posX = (s32)((actor->world.pos.x - mapDataRoom->centerX) * scaleFrac) + sMapDisp.minimapBaseX +
               sMapDisp.minimapCurX - sMapDisp.minimapBaseX + texOffsetX;
        posY = (s32)((actor->world.pos.z - mapDataRoom->centerZ) * scaleFrac) + sMapDisp.minimapBaseY +
               sMapDisp.minimapCurY - sMapDisp.minimapBaseY + texOffsetY;
    } else {
        posX = -(s32)((actor->world.pos.x - mapDataRoom->centerX) * scaleFrac) + sMapDisp.minimapBaseX +
               sMapDisp.minimapCurX - sMapDisp.minimapBaseX + texOffsetX;
        posY = -(s32)((actor->world.pos.z - mapDataRoom->centerZ) * scaleFrac) + sMapDisp.minimapBaseY +
               sMapDisp.minimapCurY - sMapDisp.minimapBaseY + texOffsetY;
    }

    if ((posX > 0) && (posX < 0x3FF) && (posY > 0) && (posY < 0x3FF)) {
        OPEN_DISPS(play->state.gfxCtx);

        if ((actor->category == ACTORCAT_PLAYER) && (actor->flags & ACTOR_FLAG_80000000)) {
            s16 compassRot;

            Gfx_SetupDL42_Overlay(play->state.gfxCtx);
            gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                              PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
            gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, play->interfaceCtx.minimapAlpha);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
            gDPSetRenderMode(OVERLAY_DISP++, G_RM_AA_DEC_LINE, G_RM_NOOP2);

            Matrix_Translate(posX - 160.0f, 120.0f - posY, 0.0f, MTXMODE_NEW);
            Matrix_RotateXFApply(-1.6f);
            compassRot = (s32)(0x7FFF - actor->focus.rot.y) / 1024;
            // if (MapDisp_IsDataRotated(play)) {
            if (func_801039EC(play)) {
                compassRot += 0x7FFF;
            }
            Matrix_RotateYF(compassRot / 10.0f, MTXMODE_APPLY);
            Matrix_Scale(0.4f, 0.4f, 0.4f, MTXMODE_APPLY);
            MATRIX_FINALIZE_AND_LOAD(OVERLAY_DISP++, play->state.gfxCtx);
            // gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 200, 255, 0, play->interfaceCtx.minimapAlpha);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, mapPlayerColor.r, mapPlayerColor.g, mapPlayerColor.b, play->interfaceCtx.minimapAlpha);
            // gSPDisplayList(OVERLAY_DISP++, gCompassArrowDL);
            gSPDisplayList(OVERLAY_DISP++, gameplay_keep_DL_01ED00);
        } else if ((actor->id == ACTOR_EN_BOX) && !Flags_GetTreasure(play, actor->params & 0x1F) &&
                //    (MapDisp_GetStoreyY(player->actor.world.pos.y) == MapDisp_GetStoreyY(actor->world.pos.y))) {
                   (func_80102F9C(player->actor.world.pos.y) == func_80102F9C(actor->world.pos.y))) {
            Gfx_SetupDL39_Overlay(play->state.gfxCtx);
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetTextureLUT(OVERLAY_DISP++, G_TT_NONE);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, play->interfaceCtx.minimapAlpha);
            gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, play->interfaceCtx.minimapAlpha);
            gDPPipeSync(OVERLAY_DISP++);

            gDPLoadTextureBlock_Runtime(OVERLAY_DISP++, gMapChestIconTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0,
                                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                        G_TX_NOLOD, G_TX_NOLOD);

            gSPTextureRectangle(OVERLAY_DISP++, (posX - 4) << 2, (posY - 4) << 2, (posX + 4) << 2, (posY + 4) << 2,
                                G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        } else {
            Gfx_SetupDL39_Overlay(play->state.gfxCtx);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            if (actor->flags & ACTOR_FLAG_80000000) {
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, sMinimapActorCategoryColors[actor->category].r,
                                sMinimapActorCategoryColors[actor->category].g,
                                sMinimapActorCategoryColors[actor->category].b, play->interfaceCtx.minimapAlpha);
                gSPTextureRectangle(OVERLAY_DISP++, (posX - 1) << 2, (posY - 1) << 2, (posX + 1) << 2, (posY + 1) << 2,
                                    G_TX_RENDERTILE, 0, 0, 0x0001, 0x0001);
            }
        }
        CLOSE_DISPS(play->state.gfxCtx);
    }
}

// RECOMP_PATCH void MapDisp_Minimap_DrawRedCompassIcon(PlayState* play, s32 x, s32 z, s32 rot) {
RECOMP_PATCH void func_80105FE0(PlayState* play, s32 x, s32 z, s32 rot) {
    MapDataRoom* mapDataRoom;
    s32 posX;
    s32 posY;
    s32 texOffsetX;
    s32 texOffsetY;
    s32 texWidth;
    s32 texHeight;
    s32 scale;
    f32 scaleFrac;

    MapDisp sMapDisp = D_801BEBB8; // temp

    mapDataRoom = &sMapDisp.mapDataScene->rooms[sMapDisp.curRoom];
    if (mapDataRoom->mapId == MAP_DATA_NO_MAP) {
        return;
    }

    // MapDisp_GetMapOffset(mapDataRoom, &texOffsetX, &texOffsetY);
    func_801030F4(mapDataRoom, &texOffsetX, &texOffsetY);
    // MapDisp_GetMapTexDim(mapDataRoom, &texWidth, &texHeight);
    func_80103090(mapDataRoom, &texWidth, &texHeight);
    scale = sMapDisp.mapDataScene->scale;

    if (sMapDisp.mapDataScene->scale == 0) {
        scale = 20;
    } else if (sMapDisp.mapDataScene->scale == -1) {
        s32 scaleTemp;

        // MapDisp_GetMapScale(mapDataRoom, &scaleTemp);
        func_801030B4(mapDataRoom, &scaleTemp);
        scale = scaleTemp;
    }

    scaleFrac = 1.0f / scale;
    // if (!MapDisp_IsDataRotated(play)) {
    if (!func_801039EC(play)) {
        posX = (s32)((x - (f32)mapDataRoom->centerX) * scaleFrac) + sMapDisp.minimapBaseX +
               (sMapDisp.minimapCurX - sMapDisp.minimapBaseX) + texOffsetX;
        posY = (s32)((z - (f32)mapDataRoom->centerZ) * scaleFrac) + sMapDisp.minimapBaseY +
               (sMapDisp.minimapCurY - sMapDisp.minimapBaseY) + texOffsetY;
    } else {
        posX = -(s32)((x - (f32)mapDataRoom->centerX) * scaleFrac) + sMapDisp.minimapBaseX +
               (sMapDisp.minimapCurX - sMapDisp.minimapBaseX) + texOffsetX;
        posY = -(s32)((z - (f32)mapDataRoom->centerZ) * scaleFrac) + sMapDisp.minimapBaseY +
               (sMapDisp.minimapCurY - sMapDisp.minimapBaseY) + texOffsetY;
    }

    if ((posX > 0) && (posX < 0x3FF) && (posY > 0) && (posY < 0x3FF)) {
        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL42_Overlay(play->state.gfxCtx);
        gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, 255);
        gDPSetCombineMode(OVERLAY_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetRenderMode(OVERLAY_DISP++, G_RM_AA_DEC_LINE, G_RM_NOOP2);
        Matrix_Translate(posX - 160.0f, 120.0f - posY, 0.0f, MTXMODE_NEW);
        Matrix_RotateXFApply(-1.6f);
        // if (MapDisp_IsDataRotated(play)) {
        if (func_801039EC(play)) {
            rot += 0x7FFF;
        }
        Matrix_RotateYF(rot / 10.0f, MTXMODE_APPLY);
        Matrix_Scale(0.4f, 0.4f, 0.4f, MTXMODE_APPLY);
        MATRIX_FINALIZE_AND_LOAD(OVERLAY_DISP++, play->state.gfxCtx);
        // gDPSetPrimColor(OVERLAY_DISP++, 0, 255, 200, 0, 0, play->interfaceCtx.minimapAlpha);
        gDPSetPrimColor(OVERLAY_DISP++, 0, 255, mapEntranceColor.r, mapEntranceColor.g, mapEntranceColor.b, play->interfaceCtx.minimapAlpha);
        // gSPDisplayList(OVERLAY_DISP++, gCompassArrowDL);
        gSPDisplayList(OVERLAY_DISP++, gameplay_keep_DL_01ED00);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}