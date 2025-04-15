#include "modding.h"
#include "global.h"

#include "recolor.h"
#include "models.h"

#include "z64player.h"

RECOMP_CALLBACK("*", recomp_on_play_init)
void replaceLinkModels() {
    // human replacement
    gPlayerSkeletons[PLAYER_FORM_HUMAN] = &gLinkHumanSkelMod;
    sPlayerFirstPersonRightShoulderDLs[PLAYER_FORM_HUMAN] = &gLinkHumanRightShoulderModifiedDL;
    gPlayerWaistDLs[PLAYER_FORM_HUMAN * 2 + 0] = &gLinkHumanWaistModifiedDL;
    gPlayerWaistDLs[PLAYER_FORM_HUMAN * 2 + 1] = &gLinkHumanWaistModifiedDL;
}

void updateFormColor(PlayState* play, s32 limbIndex, Gfx** dList, PlayerTransformation form)
{
    Color_RGB8* color;
    Player* player = GET_PLAYER(play);

    switch (player->transformation) {
        case PLAYER_FORM_HUMAN:
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
    updateFormColor(play, limbIndex, dList, player->transformation);
}

RECOMP_HOOK("Player_OverrideLimbDrawGameplayFirstPerson")
void Recolor_OverrideLimbDrawFirstPerson(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor) {
    Player* player = (Player*)actor;
    updateFormColor(play, limbIndex, dList, player->transformation);
}