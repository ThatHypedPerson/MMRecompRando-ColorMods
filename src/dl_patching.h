#ifndef __COLOR_PATCHING_H__
#define __COLOR_PATCHING_H__

#include "global.h"

// Searches for a prim color command in the provided displaylist and replaces the new color with the target if found.
bool patch_prim_color(Gfx* dl, u8 old_r, u8 old_g, u8 old_b, u8 old_a, u8 new_r, u8 new_g, u8 new_b, u8 new_a);
// Searches for an env color command in the provided displaylist and replaces the new color with the target if found.
bool patch_env_color(Gfx* dl, u8 old_r, u8 old_g, u8 old_b, u8 old_a, u8 new_r, u8 new_g, u8 new_b, u8 new_a);

// Searches for a prim color command in the provided displaylist and replaces it with a jump to a target displaylist if found.
bool patch_prim_color_with_dl(Gfx* dl, u8 old_r, u8 old_g, u8 old_b, u8 old_a, Gfx* target);
// Searches for an env color command in the provided displaylist and replaces it with a jump to a target displaylist if found.
bool patch_env_color_with_dl(Gfx* dl, u8 old_r, u8 old_g, u8 old_b, u8 old_a, Gfx* target);

// Searches for an arbitrary list of commands in the provided displaylist and replaces them with the provided replacement commands if found.
// Use this when the commands you want to replace with are the same length as the original commands.
bool replace_dl_commands(Gfx* to_scan, Gfx* to_find, Gfx* to_replace, u32 length);

// Searches for an arbitrary list of commands in the provided displaylist and replaces them with a call to the provided displaylist if found.
// Make sure you terminate the target displaylist with an end displaylist command.
// Use this when the commands you want to replace with are longer or shorter than the original commands.
bool replace_dl_commands_jump(Gfx* to_scan, Gfx* to_find, Gfx* target, u32 length);

#endif
