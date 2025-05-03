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

extern u64 savedLink_005C40[32];
extern u64 savedLink_005D80[16];
extern u64 object_link_child_Tex_005C40[];
extern u64 object_link_child_Tex_005D80[];

RECOMP_HOOK_RETURN("Player_Init")
void load_textures(Actor* thisx, PlayState* play) {
    // load original textures
    if (GET_PLAYER_FORM == PLAYER_FORM_HUMAN && (savedLink_005C40[0] == 0 || savedLink_005D80[0] == 0)) {
        Lib_MemCpy(savedLink_005C40, SEGMENTED_TO_K0(object_link_child_Tex_005C40), sizeof(savedLink_005C40));
        Lib_MemCpy(savedLink_005D80, SEGMENTED_TO_K0(object_link_child_Tex_005D80), sizeof(savedLink_005D80));
    }
}

static bool human_changed;
static bool deku_changed;
static bool goron_changed;
static bool zora_changed;
static bool fd_changed;

RECOMP_HOOK("GameState_Update")
void on_game_update() {
    // human replacement
    if (recomp_get_config_u32("replace_human")) {
        gPlayerSkeletons[PLAYER_FORM_HUMAN] = &gLinkHumanSkelMod;
        sPlayerFirstPersonRightShoulderDLs[PLAYER_FORM_HUMAN] = &gLinkHumanRightShoulderModifiedDL;
        gPlayerWaistDLs[PLAYER_FORM_HUMAN * 2 + 0] = &gLinkHumanWaistModifiedDL;
        gPlayerWaistDLs[PLAYER_FORM_HUMAN * 2 + 1] = &gLinkHumanWaistModifiedDL;
        human_changed = true;
    } else if (human_changed) {
        gPlayerSkeletons[PLAYER_FORM_HUMAN] = &gLinkHumanSkel;
        sPlayerFirstPersonRightShoulderDLs[PLAYER_FORM_HUMAN] = &gLinkHumanRightShoulderDL;
        gPlayerWaistDLs[PLAYER_FORM_HUMAN * 2 + 0] = &gLinkHumanWaistDL;
        gPlayerWaistDLs[PLAYER_FORM_HUMAN * 2 + 1] = &gLinkHumanWaistDL;
        human_changed = false;
    }

    // deku replacement
    if (recomp_get_config_u32("replace_deku")) {
        gPlayerSkeletons[PLAYER_FORM_DEKU] = &gLinkDekuSkelMod;
        gPlayerWaistDLs[PLAYER_FORM_DEKU * 2 + 0] = &gLinkDekuWaistModifiedDL;
        gPlayerWaistDLs[PLAYER_FORM_DEKU * 2 + 1] = &gLinkDekuWaistModifiedDL;
        deku_changed = true;
    } else if (deku_changed) {
        gPlayerSkeletons[PLAYER_FORM_DEKU] = &gLinkDekuSkel;
        gPlayerWaistDLs[PLAYER_FORM_DEKU * 2 + 0] = &gLinkDekuWaistDL;
        gPlayerWaistDLs[PLAYER_FORM_DEKU * 2 + 1] = &gLinkDekuWaistDL;
        deku_changed = false;
    }

    // goron replacement
    if (recomp_get_config_u32("replace_goron")) {
        gPlayerSkeletons[PLAYER_FORM_GORON] = &gLinkGoronSkelMod;
        gPlayerWaistDLs[PLAYER_FORM_GORON * 2 + 0] = &gLinkGoronWaistModifiedDL;
        gPlayerWaistDLs[PLAYER_FORM_GORON * 2 + 1] = &gLinkGoronWaistModifiedDL;
        D_801BFDD0[0].dList = &gLinkGoronCurledModifiedDL; // ?
        D_801BFDD0[1].dList = &gLinkGoronRollingSpikesAndEffectModifiedDL; // ?
        goron_changed = true;
    } else if (goron_changed) {
        gPlayerSkeletons[PLAYER_FORM_GORON] = &gLinkGoronSkel;
        gPlayerWaistDLs[PLAYER_FORM_GORON * 2 + 0] = &gLinkGoronWaistDL;
        gPlayerWaistDLs[PLAYER_FORM_GORON * 2 + 1] = &gLinkGoronWaistDL;
        D_801BFDD0[0].dList = &gLinkGoronCurledDL; // ?
        D_801BFDD0[1].dList = &gLinkGoronRollingSpikesAndEffectDL; // ?
        goron_changed = false;
    }

    // zora replacement
    if (recomp_get_config_u32("replace_zora")) {
        gPlayerSkeletons[PLAYER_FORM_ZORA] = &gLinkZoraSkelMod;
        gPlayerWaistDLs[PLAYER_FORM_ZORA * 2 + 0] = &gLinkZoraWaistModifiedDL;
        gPlayerWaistDLs[PLAYER_FORM_ZORA * 2 + 1] = &gLinkZoraWaistModifiedDL;
        zora_changed = true;
    } else if (zora_changed) {
        gPlayerSkeletons[PLAYER_FORM_ZORA] = &gLinkZoraSkel;
        gPlayerWaistDLs[PLAYER_FORM_ZORA * 2 + 0] = &gLinkZoraWaistDL;
        gPlayerWaistDLs[PLAYER_FORM_ZORA * 2 + 1] = &gLinkZoraWaistDL;
        zora_changed = false;
    }

    // fd replacement
    if (recomp_get_config_u32("replace_fd")) {
        gPlayerSkeletons[PLAYER_FORM_FIERCE_DEITY] = &gLinkFierceDeitySkelMod;
        fd_changed = true;
    } else if (fd_changed) {
        gPlayerSkeletons[PLAYER_FORM_FIERCE_DEITY] = &gLinkFierceDeitySkel;
        fd_changed = false;
    }
}

void updateFormColor(PlayState* play, PlayerTransformation form)
{
    Color_RGB8* color;

    switch (form) {
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
        default:
            color = &humanTunicColor;
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