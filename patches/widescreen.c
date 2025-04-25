#include "patches.h"

RECOMP_PATCH Gfx* dynGetMasterDisplayList(void) {
    g_GfxRequestedDisplayList = TRUE;

    Gfx* gdl = (Gfx*) g_GfxBuffers[g_GfxActiveBufferIndex];

    // @recomp: Enable RT64 Extended GBI
    gEXEnable(gdl++);

    return gdl;
}

// Set viewports (single player)
#if 1
RECOMP_PATCH Gfx* zbufClearCurrentPlayer(Gfx* gdl) {
    s32 start_x;
    s32 end_x;

    gDPPipeSync(gdl++);
    gDPSetRenderMode(gdl++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetColorImage(gdl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, z_buffer_width, OS_K0_TO_PHYSICAL(z_buffer));
    gDPSetCycleType(gdl++, G_CYC_FILL);
    gDPSetFillColor(gdl++, (GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0)));

    // @recomp: use gEXSetScissor instead
    // gDPSetScissor(gdl++, G_SC_NON_INTERLACE, 0, 0, viGetX(), viGetY());
    gEXSetScissor(gdl++, G_SC_NON_INTERLACE, G_EX_ORIGIN_LEFT, G_EX_ORIGIN_RIGHT, 0, 0, 0, 240);

    if (getPlayerCount() < 3) {
        start_x = 0;
        end_x = viGetX() - 1;
    } else if ((get_cur_playernum() == 0) || (get_cur_playernum() == 2)) {
        start_x = 0;
        end_x = (viGetX() / 2) - 1;
    } else {
        start_x = viGetX() / 2;
        end_x = viGetX() - 1;
    }

    gDPFillRectangle(gdl++, start_x, 0, end_x + 240, (z_buffer_height - 1));
    gDPPipeSync(gdl++);

    return gdl;
}
#endif

#if 1
RECOMP_PATCH Gfx* bgScissorCurrentPlayerView(Gfx* gdl, s32 left, s32 top, s32 width, s32 height) {
    struct player* player = g_CurrentPlayer;

    if (left < (s32) player->viewleft) {
        left = (s32) player->viewleft;
    }

    if (top < (s32) player->viewtop) {
        top = (s32) player->viewtop;
    }

    if (player->viewleft + player->viewx < width) {
        width = player->viewleft + player->viewx;
    }

    if (player->viewtop + player->viewy < height) {
        height = player->viewtop + player->viewy;
    }

    // @recomp: use gEXSetScissor instead
    // gDPSetScissor(arg0++, G_SC_NON_INTERLACE, left, top, width, height);
    gEXSetScissor(gdl++, G_SC_NON_INTERLACE, G_EX_ORIGIN_LEFT, G_EX_ORIGIN_RIGHT, 0, 0, 0, 240);

    return gdl;
}
#endif

#if 1
RECOMP_PATCH void modelSetDistanceDisabled(s32 param_1) {
    // @recomp: ModelDistance always disabled
    g_ModelDistanceDisabled = 1;
}
#endif

#if 1
RECOMP_PATCH Gfx* currentPlayerDrawFade(Gfx* gdl) {
    f32 frac = g_CurrentPlayer->colourscreenfrac;
    s32 r = g_CurrentPlayer->colourscreenred;
    s32 g = g_CurrentPlayer->colourscreengreen;
    s32 b = g_CurrentPlayer->colourscreenblue;

    if ((cameraFrameCounter1 != 0) || (cameraFrameCounter2 != 0)) {
        frac = 1.0f;
        b = 0;
        g = 0;
        r = 0;
    }

    if (frac > 0) {
        gDPPipeSync(gdl++);
        gDPSetCycleType(gdl++, G_CYC_1CYCLE);
        gDPSetColorDither(gdl++, G_CD_DISABLE);
        gDPSetTexturePersp(gdl++, G_TP_NONE);
        gDPSetAlphaCompare(gdl++, G_AC_NONE);
        gDPSetTextureLOD(gdl++, G_TL_TILE);
        gDPSetTextureFilter(gdl++, G_TF_BILERP);
        gDPSetTextureConvert(gdl++, G_TC_FILT);
        gDPSetTextureLUT(gdl++, G_TT_NONE);
        gDPSetRenderMode(gdl++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
        gDPSetCombineMode(gdl++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetPrimColor(gdl++, 0, 0, r, g, b, (s32) (frac * 255.0f));

        // gDPFillRectangle(gdl++, viGetViewLeft(), viGetViewTop(), (viGetViewLeft() + viGetViewWidth()),
        // (viGetViewTop() + viGetViewHeight()));

        // @recomp: Remove margins
        gDPFillRectangle(gdl++, 0, 0, 320, 240);

        gDPPipeSync(gdl++);
        gDPSetColorDither(gdl++, G_CD_BAYER);
        gDPSetTexturePersp(gdl++, G_TP_PERSP);
        gDPSetTextureLOD(gdl++, G_TL_LOD);
    }

    return gdl;
}
#endif

// @recomp: Culling of objects on the sides.
#if 1
RECOMP_PATCH void bgUpdateCurrentPlayerScreenMinMax(void) {
    f32 fx = -320.0f * 4.0f;            // @recomp:
    f32 fy = 0;                         // @recomp:
    f32 fwidth = (f32) viGetX() * 4.0f; // @recomp:
    f32 fheight = (f32) viGetY();       // @recomp:

    g_CurrentPlayer->screenxminf = (f32) viGetViewLeft() + 320.0f * -4.0f; // @recomp:

    if (g_CurrentPlayer->screenxminf < fx) {
        g_CurrentPlayer->screenxminf = fx;
    }

    if (fwidth < g_CurrentPlayer->screenxminf) {
        g_CurrentPlayer->screenxminf = fwidth;
    }

    g_CurrentPlayer->screenyminf = (f32) viGetViewTop();

    if (g_CurrentPlayer->screenyminf < fy) {
        g_CurrentPlayer->screenyminf = fy;
    }

    if (fheight < g_CurrentPlayer->screenyminf) {
        g_CurrentPlayer->screenyminf = fheight;
    }

    g_CurrentPlayer->screenxmaxf = (f32) (viGetViewLeft() + viGetViewWidth() + 320.0f * 4.0f); // @recomp:

    if (g_CurrentPlayer->screenxmaxf < fx) {
        g_CurrentPlayer->screenxmaxf = fx;
    }

    if (fwidth < g_CurrentPlayer->screenxmaxf) {
        g_CurrentPlayer->screenxmaxf = fwidth;
    }

    g_CurrentPlayer->screenymaxf = (f32) (viGetViewTop() + viGetViewHeight());

    if (g_CurrentPlayer->screenymaxf < fy) {
        g_CurrentPlayer->screenymaxf = fy;
    }

    if (fheight < g_CurrentPlayer->screenymaxf) {
        g_CurrentPlayer->screenymaxf = fheight;
    }
}
#endif
