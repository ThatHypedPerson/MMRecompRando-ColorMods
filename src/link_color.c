#include "modding.h"
#include "global.h"
#include "recompconfig.h"

#include "recolor.h"
#include "models.h"

#include "z64player.h"

// alternate goron form
typedef struct {
    /* 0x0 */ Color_RGB8 color;
    /* 0x4 */ Gfx* dList;
} struct_801BFDD0; // size = 0x8
extern struct_801BFDD0 D_801BFDD0[];

RECOMP_HOOK("GameState_Update")
void on_game_update() {
    // human replacement
    if (recomp_get_config_u32("replace_human")) {
        gPlayerSkeletons[PLAYER_FORM_HUMAN] = &gLinkHumanSkelMod;
        sPlayerFirstPersonRightShoulderDLs[PLAYER_FORM_HUMAN] = &gLinkHumanRightShoulderModifiedDL;
        gPlayerWaistDLs[PLAYER_FORM_HUMAN * 2 + 0] = &gLinkHumanWaistModifiedDL;
        gPlayerWaistDLs[PLAYER_FORM_HUMAN * 2 + 1] = &gLinkHumanWaistModifiedDL;
    } else {
        gPlayerSkeletons[PLAYER_FORM_HUMAN] = &gLinkHumanSkel;
        sPlayerFirstPersonRightShoulderDLs[PLAYER_FORM_HUMAN] = &gLinkHumanRightShoulderDL;
        gPlayerWaistDLs[PLAYER_FORM_HUMAN * 2 + 0] = &gLinkHumanWaistDL;
        gPlayerWaistDLs[PLAYER_FORM_HUMAN * 2 + 1] = &gLinkHumanWaistDL;
    }

    // deku replacement
    if (recomp_get_config_u32("replace_deku")) {
        gPlayerSkeletons[PLAYER_FORM_DEKU] = &gLinkDekuSkelMod;
        gPlayerWaistDLs[PLAYER_FORM_DEKU * 2 + 0] = &gLinkDekuWaistModifiedDL;
        gPlayerWaistDLs[PLAYER_FORM_DEKU * 2 + 1] = &gLinkDekuWaistModifiedDL;
    } else {
        gPlayerSkeletons[PLAYER_FORM_DEKU] = &gLinkDekuSkel;
        gPlayerWaistDLs[PLAYER_FORM_DEKU * 2 + 0] = &gLinkDekuWaistDL;
        gPlayerWaistDLs[PLAYER_FORM_DEKU * 2 + 1] = &gLinkDekuWaistDL;
    }

    // goron replacement
    if (recomp_get_config_u32("replace_goron")) {
        gPlayerSkeletons[PLAYER_FORM_GORON] = &gLinkGoronSkelMod;
        gPlayerWaistDLs[PLAYER_FORM_GORON * 2 + 0] = &gLinkGoronWaistModifiedDL;
        gPlayerWaistDLs[PLAYER_FORM_GORON * 2 + 1] = &gLinkGoronWaistModifiedDL;
        D_801BFDD0[0].dList = &gLinkGoronCurledModifiedDL; // ?
        D_801BFDD0[1].dList = &gLinkGoronRollingSpikesAndEffectModifiedDL; // ?
    } else {
        gPlayerSkeletons[PLAYER_FORM_GORON] = &gLinkGoronSkel;
        gPlayerWaistDLs[PLAYER_FORM_GORON * 2 + 0] = &gLinkGoronWaistDL;
        gPlayerWaistDLs[PLAYER_FORM_GORON * 2 + 1] = &gLinkGoronWaistDL;
        D_801BFDD0[0].dList = &gLinkGoronCurledDL; // ?
        D_801BFDD0[1].dList = &gLinkGoronRollingSpikesAndEffectDL; // ?
    }

    // zora replacement
    if (recomp_get_config_u32("replace_zora")) {
        gPlayerSkeletons[PLAYER_FORM_ZORA] = &gLinkZoraSkelMod;
        gPlayerWaistDLs[PLAYER_FORM_ZORA * 2 + 0] = &gLinkZoraWaistModifiedDL;
        gPlayerWaistDLs[PLAYER_FORM_ZORA * 2 + 1] = &gLinkZoraWaistModifiedDL;
    } else {
        gPlayerSkeletons[PLAYER_FORM_ZORA] = &gLinkZoraSkel;
        gPlayerWaistDLs[PLAYER_FORM_ZORA * 2 + 0] = &gLinkZoraWaistDL;
        gPlayerWaistDLs[PLAYER_FORM_ZORA * 2 + 1] = &gLinkZoraWaistDL;
    }

    // fd replacement
    if (recomp_get_config_u32("replace_fd")) {
        gPlayerSkeletons[PLAYER_FORM_FIERCE_DEITY] = &gLinkFierceDeitySkelMod;
    } else {
        gPlayerSkeletons[PLAYER_FORM_FIERCE_DEITY] = &gLinkFierceDeitySkel;
    }
}

void updateFormColor(PlayState* play, PlayerTransformation form)
{
    Color_RGB8* color;
    Player* player = GET_PLAYER(play);

    switch (player->transformation) {
        case PLAYER_FORM_HUMAN:
            color = &humanTunicColor;
            break;
        case PLAYER_FORM_DEKU:
            color = &dekuTunicColor;
            break;
        case PLAYER_FORM_GORON:
            color = &goronTunicColor;
            break;
        case PLAYER_FORM_ZORA:
            color = &zoraTunicColor;
            break;
        case PLAYER_FORM_FIERCE_DEITY:
            color = &fdTunicColor;
            break;
    }
    
    OPEN_DISPS(play->state.gfxCtx);
    gDPSetEnvColor(POLY_OPA_DISP++, color->r, color->g, color->b, 0);
    CLOSE_DISPS(play->state.gfxCtx);
}

s32 Player_OverrideLimbDrawGameplayCommon(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void func_80125CE0(Player* player, struct_80124618* arg1, Vec3f* pos, Vec3s* rot);

RECOMP_HOOK("Player_OverrideLimbDrawGameplayDefault")
void Recolor_OverrideLimbDrawDefault(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor) {
    Player* player = (Player*)actor;
    updateFormColor(play, player->transformation);
}

RECOMP_HOOK("Player_OverrideLimbDrawGameplayFirstPerson")
void Recolor_OverrideLimbDrawFirstPerson(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor) {
    Player* player = (Player*)actor;
    updateFormColor(play, player->transformation);
}