#include "modding.h"
#include "global.h"

#include "recolor.h"

#define DEBUG_EDITOR_NONE 0x0
#define PAUSE_STATE_OFF 0x0

extern u64 gThreeDayClockHour1Tex[];
extern u64 gThreeDayClockHour2Tex[];
extern u64 gThreeDayClockHour3Tex[];
extern u64 gThreeDayClockHour4Tex[];
extern u64 gThreeDayClockHour5Tex[];
extern u64 gThreeDayClockHour6Tex[];
extern u64 gThreeDayClockHour7Tex[];
extern u64 gThreeDayClockHour8Tex[];
extern u64 gThreeDayClockHour9Tex[];
extern u64 gThreeDayClockHour10Tex[];
extern u64 gThreeDayClockHour11Tex[];
extern u64 gThreeDayClockHour12Tex[];
extern u64 gFinalHoursClockDigit0Tex[];
extern u64 gFinalHoursClockDigit1Tex[];
extern u64 gFinalHoursClockDigit2Tex[];
extern u64 gFinalHoursClockDigit3Tex[];
extern u64 gFinalHoursClockDigit4Tex[];
extern u64 gFinalHoursClockDigit5Tex[];
extern u64 gFinalHoursClockDigit6Tex[];
extern u64 gFinalHoursClockDigit7Tex[];
extern u64 gFinalHoursClockDigit8Tex[];
extern u64 gFinalHoursClockDigit9Tex[];
extern u64 gFinalHoursClockColonTex[];
extern u64 gThreeDayClockHourLinesTex[];
extern u64 gThreeDayClockBorderTex[];
extern u64 gThreeDayClockDiamondTex[];
extern u64 gThreeDayClockStarMinuteTex[];
extern u64 gThreeDayClockSunHourTex[];
extern u64 gThreeDayClockMoonHourTex[];
extern u64 gFinalHoursClockFrameTex[];

extern s16 D_801BF974;
extern s16 D_801BF978;
extern s16 D_801BF97C;
extern f32 D_801BF980;
extern s32 D_801BF984;
extern s16 sFinalHoursClockColorTimer;
extern s16 sFinalHoursClockColorTargetIndex;

extern s16 sFinalHoursClockDigitsRed;
extern s16 sFinalHoursClockFrameEnvRed;
extern s16 sFinalHoursClockFrameEnvGreen;
extern s16 sFinalHoursClockFrameEnvBlue;

Gfx* Gfx_DrawTexRect4b(Gfx* gfx, TexturePtr texture, s32 fmt, s16 textureWidth, s16 textureHeight, s16 rectLeft,
                       s16 rectTop, s16 rectWidth, s16 rectHeight, s32 cms, s32 masks, s32 rects, u16 dsdx, u16 dtdy);

RECOMP_PATCH void Interface_DrawClock(PlayState* play) {
    static s16 sThreeDayClockAlpha = 255;
    static s16 sClockAlphaTimer1 = 0;
    static s16 sClockAlphaTimer2 = 0;
    static u16 sThreeDayClockHours[] = {
        CLOCK_TIME(0, 0),  CLOCK_TIME(1, 0),  CLOCK_TIME(2, 0),  CLOCK_TIME(3, 0),  CLOCK_TIME(4, 0),
        CLOCK_TIME(5, 0),  CLOCK_TIME(6, 0),  CLOCK_TIME(7, 0),  CLOCK_TIME(8, 0),  CLOCK_TIME(9, 0),
        CLOCK_TIME(10, 0), CLOCK_TIME(11, 0), CLOCK_TIME(12, 0), CLOCK_TIME(13, 0), CLOCK_TIME(14, 0),
        CLOCK_TIME(15, 0), CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), CLOCK_TIME(19, 0),
        CLOCK_TIME(20, 0), CLOCK_TIME(21, 0), CLOCK_TIME(22, 0), CLOCK_TIME(23, 0), CLOCK_TIME(24, 0) - 1,
    };
    static TexturePtr sThreeDayClockHourTextures[] = {
        gThreeDayClockHour12Tex, gThreeDayClockHour1Tex, gThreeDayClockHour2Tex,  gThreeDayClockHour3Tex,
        gThreeDayClockHour4Tex,  gThreeDayClockHour5Tex, gThreeDayClockHour6Tex,  gThreeDayClockHour7Tex,
        gThreeDayClockHour8Tex,  gThreeDayClockHour9Tex, gThreeDayClockHour10Tex, gThreeDayClockHour11Tex,
        gThreeDayClockHour12Tex, gThreeDayClockHour1Tex, gThreeDayClockHour2Tex,  gThreeDayClockHour3Tex,
        gThreeDayClockHour4Tex,  gThreeDayClockHour5Tex, gThreeDayClockHour6Tex,  gThreeDayClockHour7Tex,
        gThreeDayClockHour8Tex,  gThreeDayClockHour9Tex, gThreeDayClockHour10Tex, gThreeDayClockHour11Tex,
    };
    static s16 sClockInvDiamondPrimRed = 0;
    static s16 sClockInvDiamondPrimGreen = 155;
    static s16 sClockInvDiamondPrimBlue = 255;
    static s16 sClockInvDiamondEnvRed = 0;
    static s16 sClockInvDiamondEnvGreen = 0;
    static s16 sClockInvDiamondEnvBlue = 0;
    static s16 sClockInvDiamondTimer = 15;
    static s16 sClockInvDiamondTargetIndex = 0;
    static s16 sClockInvDiamondPrimRedTargets[] = { 100, 0 };
    static s16 sClockInvDiamondPrimGreenTargets[] = { 205, 155 };
    static s16 sClockInvDiamondPrimBlueTargets[] = { 255, 255 };
    static s16 sClockInvDiamondEnvRedTargets[] = { 30, 0 };
    static s16 sClockInvDiamondEnvGreenTargets[] = { 30, 0 };
    static s16 sClockInvDiamondEnvBlueTargets[] = { 100, 0 };
    static s16 sFinalHoursClockDigitsRedTargets[] = { 255, 0 };
    static s16 sFinalHoursClockFrameEnvRedTargets[] = { 100, 0 };
    static s16 sFinalHoursClockFrameEnvGreenTargets[] = { 30, 0 };
    static s16 sFinalHoursClockFrameEnvBlueTargets[] = { 100, 0 };
    static TexturePtr sFinalHoursDigitTextures[] = {
        gFinalHoursClockDigit0Tex, gFinalHoursClockDigit1Tex, gFinalHoursClockDigit2Tex, gFinalHoursClockDigit3Tex,
        gFinalHoursClockDigit4Tex, gFinalHoursClockDigit5Tex, gFinalHoursClockDigit6Tex, gFinalHoursClockDigit7Tex,
        gFinalHoursClockDigit8Tex, gFinalHoursClockDigit9Tex, gFinalHoursClockColonTex,
    };
    static s16 sFinalHoursDigitSlotPosXOffset[] = {
        127, 136, 144, 151, 160, 168, 175, 184,
    };
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    MessageContext* msgCtx = &play->msgCtx;
    s16 sp1E6;
    f32 temp_f14;
    u32 timeUntilMoonCrash;
    f32 sp1D8;
    f32 timeInMinutes;
    f32 timeInSeconds;
    f32 sp1CC;
    s32 pad1;
    s16 sp1C6;
    s16 currentHour;
    u16 time;
    s16 pad2;
    s16 colorStep;
    s16 finalHoursClockSlots[8];
    s16 index;

    OPEN_DISPS(play->state.gfxCtx);

    if ((R_TIME_SPEED != 0) &&
        ((msgCtx->msgMode == MSGMODE_NONE) || ((play->actorCtx.flags & ACTORCTX_FLAG_1) && !Play_InCsMode(play)) ||
         (msgCtx->msgMode == MSGMODE_NONE) || ((msgCtx->currentTextId >= 0x100) && (msgCtx->currentTextId <= 0x200)) ||
         (gSaveContext.gameMode == GAMEMODE_END_CREDITS)) &&
        !FrameAdvance_IsEnabled(&play->state) && !Environment_IsTimeStopped() && (gSaveContext.save.day <= 3)) {
        /**
         * Section: Changes Clock's transparancy depending if Player is moving or not and possibly other things
         */
        if (gSaveContext.hudVisibility == HUD_VISIBILITY_ALL) {
            if (func_801234D4(play)) {
                sThreeDayClockAlpha = 80;
                sClockAlphaTimer1 = 5;
                sClockAlphaTimer2 = 20;
            } else if (sClockAlphaTimer2 != 0) {
                sClockAlphaTimer2--;
            } else if (sClockAlphaTimer1 != 0) {
                colorStep = ABS_ALT(sThreeDayClockAlpha - 255) / sClockAlphaTimer1;
                sThreeDayClockAlpha += colorStep;

                if (sThreeDayClockAlpha >= 255) {
                    sThreeDayClockAlpha = 255;
                    sClockAlphaTimer1 = 0;
                }
            } else {
                if (play->actorCtx.flags & ACTORCTX_FLAG_1) {
                    sThreeDayClockAlpha = 255;
                } else {
                    sThreeDayClockAlpha = interfaceCtx->bAlpha;
                }
                sClockAlphaTimer2 = 0;
                sClockAlphaTimer1 = 0;
            }
        } else {
            if (play->actorCtx.flags & ACTORCTX_FLAG_1) {
                sThreeDayClockAlpha = 255;
            } else {
                sThreeDayClockAlpha = interfaceCtx->bAlpha;
            }
            sClockAlphaTimer2 = 0;
            sClockAlphaTimer1 = 0;
        }

        if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE)) {
            Gfx_SetupDL39_Overlay(play->state.gfxCtx);

            /**
             * Section: Draw Clock's Hour Lines
             */
            gDPSetAlphaCompare(OVERLAY_DISP++, G_AC_THRESHOLD);
            gDPSetRenderMode(OVERLAY_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            // gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 130, 130, 130, sThreeDayClockAlpha);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, clockHourLinesColor.r, clockHourLinesColor.g, clockHourLinesColor.b, sThreeDayClockAlpha);
            gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0,
                              0, PRIMITIVE, 0);

            OVERLAY_DISP = Gfx_DrawTexRect4b(OVERLAY_DISP, gThreeDayClockHourLinesTex, 4, 64, 35, 96, 180, 128, 35, 1,
                                             6, 0, 1 << 10, 1 << 10);

            /**
             * Section: Draw Clock's Border
             */
            gDPPipeSync(OVERLAY_DISP++);
            // gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, sThreeDayClockAlpha);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, clockBorderColor.r, clockBorderColor.g, clockBorderColor.b, sThreeDayClockAlpha);
            gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0,
                              0, PRIMITIVE, 0);

            //! @bug A texture height of 50 is given below. The texture is only 48 units height
            //!      resulting in this reading into the next texture. This results in a white
            //!      dot in the bottom center of the clock. For the three-day clock, this is
            //!      covered by the diamond. However, it can be seen by the final-hours clock.
            OVERLAY_DISP = Gfx_DrawTexRect4b(OVERLAY_DISP, gThreeDayClockBorderTex, 4, 64, 50, 96, 168, 128, 50, 1, 6,
                                             0, 1 << 10, 1 << 10);

            if (((CURRENT_DAY >= 4) ||
                 ((CURRENT_DAY == 3) && (((void)0, gSaveContext.save.time) >= (CLOCK_TIME(0, 0) + 5)) &&
                  (((void)0, gSaveContext.save.time) < CLOCK_TIME(6, 0))))) {
                Gfx_SetupDL42_Overlay(play->state.gfxCtx);
                gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            } else {
                /**
                 * Section: Draw Three-Day Clock's Diamond
                 */
                gDPPipeSync(OVERLAY_DISP++);

                // @recolor: set inverted diamond to only be one color since the blinking was problematic
                // Time is slowed down to half speed with inverted song of time
                if (gSaveContext.save.timeSpeedOffset == -2) {
                    // // Clock diamond is blue and flashes white
                    // colorStep =
                    //     ABS_ALT(sClockInvDiamondPrimRed - sClockInvDiamondPrimRedTargets[sClockInvDiamondTargetIndex]) /
                    //     sClockInvDiamondTimer;
                    // if (sClockInvDiamondPrimRed >= sClockInvDiamondPrimRedTargets[sClockInvDiamondTargetIndex]) {
                    //     sClockInvDiamondPrimRed -= colorStep;
                    // } else {
                    //     sClockInvDiamondPrimRed += colorStep;
                    // }

                    // colorStep = ABS_ALT(sClockInvDiamondPrimGreen -
                    //                     sClockInvDiamondPrimGreenTargets[sClockInvDiamondTargetIndex]) /
                    //             sClockInvDiamondTimer;
                    // if (sClockInvDiamondPrimGreen >= sClockInvDiamondPrimGreenTargets[sClockInvDiamondTargetIndex]) {
                    //     sClockInvDiamondPrimGreen -= colorStep;
                    // } else {
                    //     sClockInvDiamondPrimGreen += colorStep;
                    // }

                    // colorStep = ABS_ALT(sClockInvDiamondPrimBlue -
                    //                     sClockInvDiamondPrimBlueTargets[sClockInvDiamondTargetIndex]) /
                    //             sClockInvDiamondTimer;
                    // if (sClockInvDiamondPrimBlue >= sClockInvDiamondPrimBlueTargets[sClockInvDiamondTargetIndex]) {
                    //     sClockInvDiamondPrimBlue -= colorStep;
                    // } else {
                    //     sClockInvDiamondPrimBlue += colorStep;
                    // }

                    // colorStep =
                    //     ABS_ALT(sClockInvDiamondEnvRed - sClockInvDiamondEnvRedTargets[sClockInvDiamondTargetIndex]) /
                    //     sClockInvDiamondTimer;
                    // if (sClockInvDiamondEnvRed >= sClockInvDiamondEnvRedTargets[sClockInvDiamondTargetIndex]) {
                    //     sClockInvDiamondEnvRed -= colorStep;
                    // } else {
                    //     sClockInvDiamondEnvRed += colorStep;
                    // }

                    // colorStep = ABS_ALT(sClockInvDiamondEnvGreen -
                    //                     sClockInvDiamondEnvGreenTargets[sClockInvDiamondTargetIndex]) /
                    //             sClockInvDiamondTimer;
                    // if (sClockInvDiamondEnvGreen >= sClockInvDiamondEnvGreenTargets[sClockInvDiamondTargetIndex]) {
                    //     sClockInvDiamondEnvGreen -= colorStep;
                    // } else {
                    //     sClockInvDiamondEnvGreen += colorStep;
                    // }

                    // colorStep =
                    //     ABS_ALT(sClockInvDiamondEnvBlue - sClockInvDiamondEnvBlueTargets[sClockInvDiamondTargetIndex]) /
                    //     sClockInvDiamondTimer;
                    // if (sClockInvDiamondEnvBlue >= sClockInvDiamondEnvBlueTargets[sClockInvDiamondTargetIndex]) {
                    //     sClockInvDiamondEnvBlue -= colorStep;
                    // } else {
                    //     sClockInvDiamondEnvBlue += colorStep;
                    // }

                    // sClockInvDiamondTimer--;

                    // if (sClockInvDiamondTimer == 0) {
                    //     sClockInvDiamondPrimRed = sClockInvDiamondPrimRedTargets[sClockInvDiamondTargetIndex];
                    //     sClockInvDiamondPrimGreen = sClockInvDiamondPrimGreenTargets[sClockInvDiamondTargetIndex];
                    //     sClockInvDiamondPrimBlue = sClockInvDiamondPrimBlueTargets[sClockInvDiamondTargetIndex];
                    //     sClockInvDiamondEnvRed = sClockInvDiamondEnvRedTargets[sClockInvDiamondTargetIndex];
                    //     sClockInvDiamondEnvGreen = sClockInvDiamondEnvGreenTargets[sClockInvDiamondTargetIndex];
                    //     sClockInvDiamondEnvBlue = sClockInvDiamondEnvBlueTargets[sClockInvDiamondTargetIndex];
                    //     sClockInvDiamondTimer = 15;
                    //     sClockInvDiamondTargetIndex ^= 1;
                    // }

                    gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE,
                                      0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
                    // gDPSetPrimColor(OVERLAY_DISP++, 0, 0, sClockInvDiamondPrimRed, sClockInvDiamondPrimGreen, 255,
                    //                 sThreeDayClockAlpha);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, clockInvertedColor.r, clockInvertedColor.g, clockInvertedColor.b, sThreeDayClockAlpha);
                    // unsure whether the env is visible
                    gDPSetEnvColor(OVERLAY_DISP++, sClockInvDiamondEnvRed, sClockInvDiamondEnvGreen,
                                   sClockInvDiamondEnvBlue, 0);
                } else {
                    // Clock diamond is green for regular timeSpeedOffset
                    gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                    // gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 170, 100, sThreeDayClockAlpha);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, clockUninvertedColor.r, clockUninvertedColor.g, clockUninvertedColor.b, sThreeDayClockAlpha);
                }

                OVERLAY_DISP = Gfx_DrawTexRectIA8(OVERLAY_DISP, gThreeDayClockDiamondTex, 40, 32, 140, 190, 40, 32,
                                                  1 << 10, 1 << 10);

                /**
                 * Section: Draw Three-Day Clock's Day-Number over Diamond
                 */
                gDPPipeSync(OVERLAY_DISP++);
                // gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 155, sThreeDayClockAlpha);
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, clockDayColor.r, clockDayColor.g, clockDayColor.b, sThreeDayClockAlpha);

                OVERLAY_DISP = Gfx_DrawTexRectIA8(OVERLAY_DISP, interfaceCtx->doActionSegment + 0x780, 48, 27, 137, 192,
                                                  48, 27, 1 << 10, 1 << 10);

                /**
                 * Section: Draw Three-Day Clock's Star (for the Minute Tracker)
                 */
                gDPPipeSync(OVERLAY_DISP++);

                if (D_801BF974 != 0) {
                    D_801BF980 += 0.02f;
                    D_801BF97C += 11;
                } else {
                    D_801BF980 -= 0.02f;
                    D_801BF97C -= 11;
                }

                D_801BF978--;
                if (D_801BF978 == 0) {
                    D_801BF978 = 10;
                    D_801BF974 ^= 1;
                }

                timeInSeconds = TIME_TO_SECONDS_F(gSaveContext.save.time);
                timeInSeconds -= ((s16)(timeInSeconds / 3600.0f)) * 3600.0f;

                Gfx_SetupDL42_Overlay(play->state.gfxCtx);

                gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                if (sThreeDayClockAlpha != 255) {
                    // gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 110, sThreeDayClockAlpha);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, clockCenterStarColor.r, clockCenterStarColor.g, clockCenterStarColor.b, sThreeDayClockAlpha);
                } else {
                    // gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 110, D_801BF97C);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, clockCenterStarColor.r, clockCenterStarColor.g, clockCenterStarColor.b, D_801BF97C);
                }

                gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetAlphaCompare(OVERLAY_DISP++, G_AC_THRESHOLD);
                gDPSetRenderMode(OVERLAY_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

                Matrix_Translate(0.0f, -86.0f, 0.0f, MTXMODE_NEW);
                Matrix_Scale(1.0f, 1.0f, D_801BF980, MTXMODE_APPLY);
                Matrix_RotateZF(-(timeInSeconds * 0.0175f) / 10.0f, MTXMODE_APPLY);

                gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[12], 4, 0);
                gDPLoadTextureBlock_4b(OVERLAY_DISP++, gThreeDayClockStarMinuteTex, G_IM_FMT_I, 16, 16, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
                gSP1Quadrangle(OVERLAY_DISP++, 0, 2, 3, 1, 0);
            }

            /**
             * Section: Cuts off Three-Day Clock's Sun and Moon when they dip below the clock
             */
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetScissorFrac(OVERLAY_DISP++, G_SC_NON_INTERLACE, 400, 620, 880,
                              R_THREE_DAY_CLOCK_SUN_MOON_CUTOFF * 4.0f);

            // determines the current hour
            for (sp1C6 = 0; sp1C6 <= 24; sp1C6++) {
                if (((void)0, gSaveContext.save.time) < sThreeDayClockHours[sp1C6 + 1]) {
                    break;
                }
            }

            /**
             * Section: Draw Three-Day Clock's Sun (for the Day-Time Hours Tracker)
             */
            time = gSaveContext.save.time;
            sp1D8 = Math_SinS(time) * -40.0f;
            temp_f14 = Math_CosS(time) * -34.0f;

            gDPPipeSync(OVERLAY_DISP++);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            // gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 100, 110, sThreeDayClockAlpha);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, clockSunColor.r, clockSunColor.g, clockSunColor.b, sThreeDayClockAlpha);

            Matrix_Translate(sp1D8, temp_f14, 0.0f, MTXMODE_NEW);
            Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);

            gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[16], 4, 0);

            OVERLAY_DISP = Gfx_DrawTexQuadIA8(OVERLAY_DISP, gThreeDayClockSunHourTex, 24, 24, 0);

            /**
             * Section: Draw Three-Day Clock's Moon (for the Night-Time Hours Tracker)
             */
            sp1D8 = Math_SinS(time) * 40.0f;
            temp_f14 = Math_CosS(time) * 34.0f;

            gDPPipeSync(OVERLAY_DISP++);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            // gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 55, sThreeDayClockAlpha);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, clockMoonColor.r, clockMoonColor.g, clockMoonColor.b, sThreeDayClockAlpha);

            Matrix_Translate(sp1D8, temp_f14, 0.0f, MTXMODE_NEW);
            Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
            gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[20], 4, 0);

            OVERLAY_DISP = Gfx_DrawTexQuadIA8(OVERLAY_DISP, gThreeDayClockMoonHourTex, 24, 24, 0);

            /**
             * Section: Cuts off Three-Day Clock's Hour Digits when they dip below the clock
             */
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetScissorFrac(OVERLAY_DISP++, G_SC_NON_INTERLACE, 400, 620, 880,
                              R_THREE_DAY_CLOCK_HOUR_DIGIT_CUTOFF * 4.0f);

            /**
             * Section: Draws Three-Day Clock's Hour Digit Above the Sun
             */
            sp1CC = gSaveContext.save.time * 0.000096131f; // (2.0f * 3.15f / 0x10000)

            // Rotates Three-Day Clock's Hour Digit To Above the Sun
            Matrix_Translate(0.0f, R_THREE_DAY_CLOCK_Y_POS / 10.0f, 0.0f, MTXMODE_NEW);
            Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
            Matrix_RotateZF(-(sp1CC - 3.15f), MTXMODE_APPLY);
            gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            // Draws Three-Day Clock's Hour Digit Above the Sun
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0,
                              0, PRIMITIVE, 0);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, sThreeDayClockAlpha);
            gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[24], 8, 0);

            OVERLAY_DISP = Gfx_DrawTexQuad4b(OVERLAY_DISP, sThreeDayClockHourTextures[sp1C6], 4, 16, 11, 0);

            // Colours the Three-Day Clocks's Hour Digit Above the Sun
            gDPPipeSync(OVERLAY_DISP++);
            // gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 155, sThreeDayClockAlpha);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, clockHourColor.r, clockHourColor.g, clockHourColor.b, sThreeDayClockAlpha);
            gSP1Quadrangle(OVERLAY_DISP++, 4, 6, 7, 5, 0);

            /**
             * Section: Draws Three-Day Clock's Hour Digit Above the Moon
             */

            // Rotates Three-Day Clock's Hour Digit To Above the Moon
            Matrix_Translate(0.0f, R_THREE_DAY_CLOCK_Y_POS / 10.0f, 0.0f, MTXMODE_NEW);
            Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
            Matrix_RotateZF(-sp1CC, MTXMODE_APPLY);
            gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            // Draws Three-Day Clock's Hour Digit Above the Moon
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0,
                              0, PRIMITIVE, 0);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, sThreeDayClockAlpha);
            gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[32], 8, 0);

            OVERLAY_DISP = Gfx_DrawTexQuad4b(OVERLAY_DISP, sThreeDayClockHourTextures[sp1C6], 4, 16, 11, 0);

            // Colours the Three-Day Clocks's Hour Digit Above the Moon
            gDPPipeSync(OVERLAY_DISP++);
            // gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 155, sThreeDayClockAlpha);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, clockHourColor.r, clockHourColor.g, clockHourColor.b, sThreeDayClockAlpha);
            gSP1Quadrangle(OVERLAY_DISP++, 4, 6, 7, 5, 0);

            gSPDisplayList(OVERLAY_DISP++, D_0E000000.setScissor);

            // Final Hours
            if ((CURRENT_DAY >= 4) ||
                ((CURRENT_DAY == 3) && (((void)0, gSaveContext.save.time) >= (CLOCK_TIME(0, 0) + 5)) &&
                 (((void)0, gSaveContext.save.time) < CLOCK_TIME(6, 0)))) {
                if (((void)0, gSaveContext.save.time) >= CLOCK_TIME(5, 0)) {
                    // The Final Hours clock will flash red

                    colorStep = ABS_ALT(sFinalHoursClockDigitsRed -
                                        sFinalHoursClockDigitsRedTargets[sFinalHoursClockColorTargetIndex]) /
                                sFinalHoursClockColorTimer;
                    if (sFinalHoursClockDigitsRed >=
                        sFinalHoursClockDigitsRedTargets[sFinalHoursClockColorTargetIndex]) {
                        sFinalHoursClockDigitsRed -= colorStep;
                    } else {
                        sFinalHoursClockDigitsRed += colorStep;
                    }

                    colorStep = ABS_ALT(sFinalHoursClockFrameEnvRed -
                                        sFinalHoursClockFrameEnvRedTargets[sFinalHoursClockColorTargetIndex]) /
                                sFinalHoursClockColorTimer;
                    if (sFinalHoursClockFrameEnvRed >=
                        sFinalHoursClockFrameEnvRedTargets[sFinalHoursClockColorTargetIndex]) {
                        sFinalHoursClockFrameEnvRed -= colorStep;
                    } else {
                        sFinalHoursClockFrameEnvRed += colorStep;
                    }

                    colorStep = ABS_ALT(sFinalHoursClockFrameEnvGreen -
                                        sFinalHoursClockFrameEnvGreenTargets[sFinalHoursClockColorTargetIndex]) /
                                sFinalHoursClockColorTimer;
                    if (sFinalHoursClockFrameEnvGreen >=
                        sFinalHoursClockFrameEnvGreenTargets[sFinalHoursClockColorTargetIndex]) {
                        sFinalHoursClockFrameEnvGreen -= colorStep;
                    } else {
                        sFinalHoursClockFrameEnvGreen += colorStep;
                    }

                    colorStep = ABS_ALT(sFinalHoursClockFrameEnvBlue -
                                        sFinalHoursClockFrameEnvBlueTargets[sFinalHoursClockColorTargetIndex]) /
                                sFinalHoursClockColorTimer;
                    if (sFinalHoursClockFrameEnvBlue >=
                        sFinalHoursClockFrameEnvBlueTargets[sFinalHoursClockColorTargetIndex]) {
                        sFinalHoursClockFrameEnvBlue -= colorStep;
                    } else {
                        sFinalHoursClockFrameEnvBlue += colorStep;
                    }

                    sFinalHoursClockColorTimer--;

                    if (sFinalHoursClockColorTimer == 0) {
                        sFinalHoursClockDigitsRed = sFinalHoursClockDigitsRedTargets[sFinalHoursClockColorTargetIndex];
                        sFinalHoursClockFrameEnvRed =
                            sFinalHoursClockFrameEnvRedTargets[sFinalHoursClockColorTargetIndex];
                        sFinalHoursClockFrameEnvGreen =
                            sFinalHoursClockFrameEnvGreenTargets[sFinalHoursClockColorTargetIndex];
                        sFinalHoursClockFrameEnvBlue =
                            sFinalHoursClockFrameEnvBlueTargets[sFinalHoursClockColorTargetIndex];
                        sFinalHoursClockColorTimer = 6;
                        sFinalHoursClockColorTargetIndex ^= 1;
                    }
                }

                sp1E6 = sThreeDayClockAlpha;
                if (sp1E6 != 0) {
                    sp1E6 = 255;
                }

                Gfx_SetupDL39_Overlay(play->state.gfxCtx);

                /**
                 * Section: Draws Final-Hours Clock's Frame
                 */
                gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gDPSetAlphaCompare(OVERLAY_DISP++, G_AC_THRESHOLD);
                gDPSetRenderMode(OVERLAY_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
                gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                                  PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
                // gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 195, sp1E6);
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, clockFinalHoursColor.r, clockFinalHoursColor.g, clockFinalHoursColor.b, sp1E6);
                gDPSetEnvColor(OVERLAY_DISP++, sFinalHoursClockFrameEnvRed, sFinalHoursClockFrameEnvGreen,
                               sFinalHoursClockFrameEnvBlue, 0);

                OVERLAY_DISP = Gfx_DrawTexRect4b(OVERLAY_DISP, gFinalHoursClockFrameTex, 3, 80, 13, 119, 202, 80, 13, 0,
                                                 0, 0, 1 << 10, 1 << 10);

                timeUntilMoonCrash = TIME_UNTIL_MOON_CRASH;
                timeInMinutes = TIME_TO_MINUTES_F(timeUntilMoonCrash);

                // digits for hours
                finalHoursClockSlots[0] = 0;
                finalHoursClockSlots[1] = timeInMinutes / 60.0f;
                finalHoursClockSlots[2] = timeInMinutes / 60.0f;

                while (finalHoursClockSlots[1] >= 10) {
                    finalHoursClockSlots[0]++;
                    finalHoursClockSlots[1] -= 10;
                }

                // digits for minutes
                finalHoursClockSlots[3] = 0;
                finalHoursClockSlots[4] = (s32)timeInMinutes % 60;
                finalHoursClockSlots[5] = (s32)timeInMinutes % 60;

                while (finalHoursClockSlots[4] >= 10) {
                    finalHoursClockSlots[3]++;
                    finalHoursClockSlots[4] -= 10;
                }

                // digits for seconds
                finalHoursClockSlots[6] = 0;
                finalHoursClockSlots[7] =
                    timeUntilMoonCrash - (u32)((finalHoursClockSlots[2] * ((f32)0x10000 / 24)) +
                                               (finalHoursClockSlots[5] * ((f32)0x10000 / (24 * 60))));

                while (finalHoursClockSlots[7] >= 10) {
                    finalHoursClockSlots[6]++;
                    finalHoursClockSlots[7] -= 10;
                }

                // Colon separating hours from minutes and minutes from seconds
                finalHoursClockSlots[2] = finalHoursClockSlots[5] = 10;

                /**
                 * Section: Draws Final-Hours Clock's Digits
                 */
                gDPPipeSync(OVERLAY_DISP++);
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, sFinalHoursClockDigitsRed, 0, 0, sp1E6);
                gDPSetEnvColor(OVERLAY_DISP++, sFinalHoursClockDigitsRed, 0, 0, 0);

                for (sp1C6 = 0; sp1C6 < 8; sp1C6++) {
                    index = sFinalHoursDigitSlotPosXOffset[sp1C6];

                    OVERLAY_DISP =
                        Gfx_DrawTexRectI8(OVERLAY_DISP, sFinalHoursDigitTextures[finalHoursClockSlots[sp1C6]], 8, 8,
                                          index, 205, 8, 8, 1 << 10, 1 << 10);
                }
            }
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}