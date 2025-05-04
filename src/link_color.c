#include "modding.h"
#include "global.h"
#include "recompconfig.h"
#include "recomputils.h"

#include "recolor.h"
#include "models.h"

#include "z64player.h"

#include "dl_patching.h"

u64 savedLink_005C40[32];
u64 savedLink_005D80[16];
extern u64 object_link_child_Tex_005C40[];
extern u64 object_link_child_Tex_005D80[];

RECOMP_IMPORT("*", void recomp_set_fd_anywhere(bool new_val));

RECOMP_HOOK_RETURN("Player_Init")
void load_textures(Actor* thisx, PlayState* play) {
    // load original textures
    if (GET_PLAYER_FORM == PLAYER_FORM_HUMAN && (savedLink_005C40[0] == 0 || savedLink_005D80[0] == 0)) {
        Lib_MemCpy(savedLink_005C40, SEGMENTED_TO_K0(object_link_child_Tex_005C40), sizeof(savedLink_005C40));
        Lib_MemCpy(savedLink_005D80, SEGMENTED_TO_K0(object_link_child_Tex_005D80), sizeof(savedLink_005D80));
    }
    // TODO TODO TODO remove
    recomp_set_fd_anywhere(true);
}

void** prevPlayerSkeleton = NULL;
bool patchingPlayerDls = false;
PlayerTransformation currentPlayerForm = PLAYER_FORM_MAX;

// Rainbow tunic for testing
// void hsv_to_rgb(float h, float s, float v, Color_RGB8* out) {
//     float r = 0, g = 0, b = 0;
//     if (s == 0) {
//         r = g = b = v;
//     } else {
//         int i;
//         float f, p, q, t;
//         h = h / 60.0f;
//         i = (int)(h);
//         f = h - i;
//         p = v * (1 - s);
//         q = v * (1 - f * s);
//         t = v * (1 - (1 - f) * s);
//         switch (i) {
//             case 0:
//                 r = v;
//                 g = t;
//                 b = p;
//                 break;
//             case 1:
//                 r = q;
//                 g = v;
//                 b = p;
//                 break;
//             case 2:
//                 r = p;
//                 g = v;
//                 b = t;
//                 break;
//             case 3:
//                 r = p;
//                 g = q;
//                 b = v;
//                 break;
//             case 4:
//                 r = t;
//                 g = p;
//                 b = v;
//                 break;
//             default:
//                 r = v;
//                 g = p;
//                 b = q;
//                 break;
//         }
//     }
//     out->r = r * 255;
//     out->g = g * 255;
//     out->b = b * 255;
// }

// RECOMP_HOOK("Play_Update") void on_play_update() {
//     static float hue = 0.0f;
//     hue += 2.0f;
//     if (hue >= 360.0f) {
//         hue -= 360.0f;
//     }
//     hsv_to_rgb(hue, 1.0f, 1.0f, &humanTunicColor);
// }
// End rainbow tunic

RECOMP_HOOK("Player_Init") void on_player_init() {
    prevPlayerSkeleton = NULL;
}

Gfx* updateFormPrimColor(Gfx* dl, PlayerTransformation form)
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
    
    gDPSetPrimColor(dl++, 0, 0xFF, color->r, color->g, color->b, 255);
    return dl;
}

Gfx* updateFormEnvColor(Gfx* dl, PlayerTransformation form)
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
    
    gDPSetEnvColor(dl++, color->r, color->g, color->b, 255);
    return dl;
}

Gfx prim_color_dls[PLAYER_FORM_MAX][2] = {
    {
        gsDPSetPrimColor(0, 0xFF, 0, 0, 0, 0),
        gsSPEndDisplayList()
    },
    {
        gsDPSetPrimColor(0, 0xFF, 0, 0, 0, 0),
        gsSPEndDisplayList()
    },
    {
        gsDPSetPrimColor(0, 0xFF, 0, 0, 0, 0),
        gsSPEndDisplayList()
    },
    {
        gsDPSetPrimColor(0, 0xFF, 0, 0, 0, 0),
        gsSPEndDisplayList()
    },
    {
        gsDPSetPrimColor(0, 0xFF, 0, 0, 0, 0),
        gsSPEndDisplayList()
    }
};

Gfx env_color_dls[PLAYER_FORM_MAX][2] = {
    {
        gsDPSetEnvColor(0, 0, 0, 0),
        gsSPEndDisplayList()
    },
    {
        gsDPSetEnvColor(0, 0, 0, 0),
        gsSPEndDisplayList()
    },
    {
        gsDPSetEnvColor(0, 0, 0, 0),
        gsSPEndDisplayList()
    },
    {
        gsDPSetEnvColor(0, 0, 0, 0),
        gsSPEndDisplayList()
    },
    {
        gsDPSetEnvColor(0, 0, 0, 0),
        gsSPEndDisplayList()
    }
};

RECOMP_HOOK("Player_DrawImpl") void on_player_draw(PlayState* play, void** skeleton, Vec3s* jointTable, s32 dListCount, s32 lod,
    PlayerTransformation playerForm, s32 boots, s32 face, OverrideLimbDrawFlex overrideLimbDraw,
    PostLimbDrawFlex postLimbDraw, Actor* actor)
{
    // Write the current prim colors to the color DLs.
    for (int i = 0; i < PLAYER_FORM_MAX; i++) {
        updateFormPrimColor(&prim_color_dls[i][0], i);
        updateFormEnvColor(&env_color_dls[i][0], i);
    }

    // When the player is drawn with a new skeleton, patch their DLs.
    // This prevents scanning every player DL every frame unnecessarily, which could add up if custom models are very large.
    if (skeleton && skeleton != prevPlayerSkeleton) {
        recomp_printf("skeleton changed\n");
        patchingPlayerDls = true;
        currentPlayerForm = playerForm;
    }

    prevPlayerSkeleton = skeleton;
}

// When objects are reloaded, reset the tracked skeleton so that edits are reapplied.
RECOMP_HOOK_RETURN("Object_LoadAll") void after_objects_loaded() {
    prevPlayerSkeleton = NULL;
}

RECOMP_HOOK_RETURN("Player_DrawImpl") void after_player_draw() {
    // Finished patching the player's DLs.
    patchingPlayerDls = false;
}

Gfx** curDList;
s32 curLimbIndex;

// When a limb is being drawn, patch its DL based on the current form if player DLs are currently being patched.
RECOMP_HOOK("Player_OverrideLimbDrawGameplayDefault")
void Recolor_OverrideLimbDrawDefault(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor) {
    Player* player = (Player*)actor;

    curLimbIndex = limbIndex;
    curDList = dList;
}

// When a limb is being drawn, patch its DL based on the current form if player DLs are currently being patched.
RECOMP_HOOK("Player_OverrideLimbDrawGameplayFirstPerson")
void Recolor_OverrideLimbDrawFirstPerson(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor) {
    Player* player = (Player*)actor;

    curLimbIndex = limbIndex;
    curDList = dList;
}

#define LINK_R 30
#define LINK_G 105
#define LINK_B 27
#define LINK_A 255

RECOMP_HOOK_RETURN("Player_OverrideLimbDrawGameplayDefault")
void Recolor_AfterOverrideLimbDrawDefault() {
    if (curDList != NULL && *curDList != NULL && patchingPlayerDls) {
        // Get the real address of the displaylist.
        Gfx* toPatch = (Gfx*)Lib_SegmentedToVirtual(*curDList);

        // Patch the displaylist based on the form's color to point to the custom color DL instead.
        patch_prim_color_with_dl(toPatch, LINK_R, LINK_G, LINK_B, LINK_A, &prim_color_dls[currentPlayerForm][0]);

        // Patch any other specific commands based on the form.
        switch (currentPlayerForm) {
            case PLAYER_FORM_DEKU:
                replace_deku(toPatch, curLimbIndex);
                break;
            case PLAYER_FORM_GORON:
                replace_goron(toPatch, curLimbIndex);
                break;
            case PLAYER_FORM_ZORA:
                replace_zora(toPatch, curLimbIndex);
                break;
            case PLAYER_FORM_FIERCE_DEITY:
                replace_fd(toPatch, curLimbIndex);
                break;
            default:
                break;
        }
    }


    curDList = NULL;
}

RECOMP_HOOK_RETURN("Player_OverrideLimbDrawGameplayDefault")
void Recolor_AfterOverrideLimbDrawFirstPerson() {
    Recolor_AfterOverrideLimbDrawDefault();
}
