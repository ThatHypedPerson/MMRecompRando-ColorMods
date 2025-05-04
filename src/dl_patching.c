#include "dl_patching.h"

#include "recomputils.h"

// Maximum commands to scan in case something goes terribly wrong.
#define MAX_SCAN 10000

u32 color_word_from_components(u8 r, u8 g, u8 b, u8 a) {
    return (_SHIFTL(r, 24, 8) | _SHIFTL(g, 16, 8) | _SHIFTL(b, 8, 8) | _SHIFTL(a, 0, 8));
}

// Scans a displaylist for a set color command of the given type passed in "command".
Gfx* scan_for_color(Gfx* dl, u32 command, u8 r, u8 g, u8 b, u8 a) {
    Gfx* cur_cmd = dl;
    // Build the 32-bit color word from the input colors.
    u32 color_word = color_word_from_components(r, g, b, a);

    for (u32 i = 0; i < MAX_SCAN; i++) {
        // Get the command ID (top 8 bits of the first word).
        u32 command_id = (cur_cmd->words.w0 >> 24) & 0xFF;
        switch (command_id) {
            case G_ENDDL:
                // Reached the end of the displaylist without finding the target command.
                return NULL;
            case G_DL:
                // If this is a branchlist (G_DL_NOPUSH) then treat it as the end of a displaylist.
                {
                    u32 push = (cur_cmd->words.w0 >> 16) & 0xFF;
                    if (push == G_DL_NOPUSH) {
                        return NULL;
                    }
                }
            default:
                // Just continue forward for any other command.
                break;
        }
        // If this is the right command ID, check if the color matches.
        if (command_id == command) {
            // Check the color.
            // TODO this can be changed into a threshold per-component check if catching similar colors is desirable.
            // This will allow detecting slightly differently colors for recoloring custom models.
            if (cur_cmd->words.w1 == color_word) {
                return cur_cmd;
            }
        }

        // Go to the next command.
        cur_cmd++;
    }

    recomp_printf("dl patching warning: hit scan limit (started at %08X)\n", (u32)dl);

    return NULL;
}

bool patch_prim_color(Gfx* dl, u8 old_r, u8 old_g, u8 old_b, u8 old_a, u8 new_r, u8 new_g, u8 new_b, u8 new_a) {
    // Look for a prim color command with the old color value.
    Gfx* to_patch = scan_for_color(dl, G_SETPRIMCOLOR, old_r, old_g, old_b, old_a);
    if (to_patch != NULL) {
        // Overwrite the color with the new value.
        to_patch->words.w1 = color_word_from_components(new_r, new_g, new_b, new_a);
        return true;
    }
    return false;
}

bool patch_env_color(Gfx* dl, u8 old_r, u8 old_g, u8 old_b, u8 old_a, u8 new_r, u8 new_g, u8 new_b, u8 new_a) {
    // Look for an env color command with the old color value.
    Gfx* to_patch = scan_for_color(dl, G_SETENVCOLOR, old_r, old_g, old_b, old_a);
    if (to_patch != NULL) {
        // Overwrite the color with the new value.
        to_patch->words.w1 = color_word_from_components(new_r, new_g, new_b, new_a);
        return true;
    }
    return false;
}

bool patch_prim_color_with_dl(Gfx* dl, u8 old_r, u8 old_g, u8 old_b, u8 old_a, Gfx* target) {
    // Look for an env color command with the old color value.
    Gfx* to_patch = scan_for_color(dl, G_SETPRIMCOLOR, old_r, old_g, old_b, old_a);
    if (to_patch != NULL) {
        // Overwrite the color command with a jump to the target DL.
        gSPDisplayList(to_patch, target);
        return true;
    }
    return false;
}

bool patch_env_color_with_dl(Gfx* dl, u8 old_r, u8 old_g, u8 old_b, u8 old_a, Gfx* target) {
    // Look for an env color command with the old color value.
    Gfx* to_patch = scan_for_color(dl, G_SETENVCOLOR, old_r, old_g, old_b, old_a);
    if (to_patch != NULL) {
        // Overwrite the color command with a jump to the target DL.
        gSPDisplayList(to_patch, target);
        return true;
    }
    return false;
}

bool replace_dl_commands(Gfx* to_scan, Gfx* to_find, Gfx* to_replace, u32 length) {
    Gfx* cur_cmd = to_scan;
    for (u32 i = 0; i < MAX_SCAN; i++) {
        // If the current command's words match the words of the first target command, check the remaining commands.
        if (cur_cmd->words.w0 == to_find[0].words.w0 && cur_cmd->words.w1 == to_find[0].words.w1) {
            // Check the remaining commands.
            bool didMatch = true;
            for (u32 commandIndex = 1; commandIndex < length; commandIndex++) {
                if (cur_cmd[commandIndex].words.w0 != to_find[commandIndex].words.w0 || cur_cmd[commandIndex].words.w1 != to_find[commandIndex].words.w1) {
                    didMatch = false;
                    break;
                }
            }
            // If all commands matched, perform the replacement and return true.
            if (didMatch) {
                Lib_MemCpy(cur_cmd, to_replace, sizeof(Gfx) * length);
                return true;
            }
        }
        switch (cur_cmd->words.w0) {
            case G_ENDDL:
                // Reached the end of the displaylist without finding the target command.
                return false;
            case G_DL:
                // If this is a branchlist (G_DL_NOPUSH) then treat it as the end of a displaylist.
                {
                    u32 push = (cur_cmd->words.w0 >> 16) & 0xFF;
                    if (push == G_DL_NOPUSH) {
                        return false;
                    }
                }
            default:
                // Just continue forward for any other command.
                break;
        }

        // Go to the next command.
        cur_cmd++;
    }
    return false;
}

bool replace_dl_commands_jump(Gfx* to_scan, Gfx* to_find, Gfx* target, u32 length) {
    Gfx* cur_cmd = to_scan;
    for (u32 i = 0; i < MAX_SCAN; i++) {
        // If the current command's words match the words of the first target command, check the remaining commands.
        if (cur_cmd->words.w0 == to_find[0].words.w0 && cur_cmd->words.w1 == to_find[0].words.w1) {
            // Check the remaining commands.
            bool didMatch = true;
            for (u32 commandIndex = 1; commandIndex < length; commandIndex++) {
                if (cur_cmd[commandIndex].words.w0 != to_find[commandIndex].words.w0 || cur_cmd[commandIndex].words.w1 != to_find[commandIndex].words.w1) {
                    didMatch = false;
                    break;
                }
            }
            // If all commands matched, perform the replacement and return true.
            if (didMatch) {
                gSPDisplayList(cur_cmd, target);
                // Replace the remaining commands with noops.
                for (u32 commandIndex = 1; commandIndex < length; commandIndex++) {
                    gSPNoOp(&cur_cmd[commandIndex]);
                }
                return true;
            }
        }
        switch (cur_cmd->words.w0) {
            case G_ENDDL:
                // Reached the end of the displaylist without finding the target command.
                return false;
            case G_DL:
                // If this is a branchlist (G_DL_NOPUSH) then treat it as the end of a displaylist.
                {
                    u32 push = (cur_cmd->words.w0 >> 16) & 0xFF;
                    if (push == G_DL_NOPUSH) {
                        return false;
                    }
                }
            default:
                // Just continue forward for any other command.
                break;
        }

        // Go to the next command.
        cur_cmd++;
    }
    // recomp_printf("didnt find\n");
    return false;
}