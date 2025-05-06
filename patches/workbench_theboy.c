#include "patches.h"

#if 0
RECOMP_PATCH Gfx *sub_GAME_7F009254(Gfx *gdl) {
    D_8002A7D0 = (1 - D_8002A7D0);
    switch (gunbarrel_mode - 2)
    {
    case 0:
        gdl = manipulateGunbarrelAndLogoMatrices(gdl);
        g_TitleX += XINC;
        if (word_CODE_bss_80069584 < 0) {
            word_CODE_bss_80069584 = 200;
            titleTransitionX = (g_TitleX - XDEC);
        } else {
#if defined(VERSION_EU)
            word_CODE_bss_80069584 -= 7;
#else
            word_CODE_bss_80069584 -= 6;
#endif
        }
        if (g_TitleX > 1390.0f) {
            gunbarrel_mode++;
            g_TitleX = 1276.0f;
        }
        break;

    case 1:
        #if defined(LEFTOVERDEBUG)
        gSPDisplayList(gdl++, &dlBasicGeometry);
        gdl = insert_imageDL(gdl++);
        gdl = insert_imageDL(gdl++);
        gdl = insert_imageDL(gdl++);
        gdl = insert_imageDL(gdl++);
        gdl = insert_imageDL(gdl++);
        #endif
        gdl = insert_sniper_sight_eye_intro(gdl++);
        gdl = insert_sight_backdrop_eye_intro(gdl++);
        
        if (g_TitleX < 600.0f) {
            gdl = insert_bond_eye_intro(gdl);
        }
        g_TitleX -= XDEC3;
        if (g_TitleX <= -80.0f) {
            gunbarrel_mode++;
            intro_eye_counter = 20;
        }
        break;

    case 2:
        gdl = insert_sniper_sight_eye_intro(gdl);
        gdl = insert_sight_backdrop_eye_intro(gdl);
        gdl = insert_bond_eye_intro(gdl);
        intro_eye_counter--;
        if (intro_eye_counter < 0) {
            gunbarrel_mode++;
            die_blood_image_routine(0);
            intro_state_blood_animation = 0;
            intro_eye_counter = 1;
        }
        break;

    case 3:
        intro_eye_counter--;
        if (intro_eye_counter == 0) {
            intro_state_blood_animation = die_blood_image_routine(1);
            intro_eye_counter = 2;
        }
        gdl = insert_sniper_sight_eye_intro(gdl);
        gdl = insert_sight_backdrop_eye_intro(gdl);
        gdl = insert_bond_eye_intro(gdl);
        gdl = gunbarrelBloodOverlayDL(gdl);
        if (intro_state_blood_animation != 0) {
            gunbarrel_mode++;
            word_CODE_bss_80069584 = 0;
            titleTransitionX = g_TitleX;
            intro_eye_counter = 0;
        }
        break;

    case 4:
        word_CODE_bss_80069584 += INCVAL;
        intro_eye_counter++;
        g_TitleX = ((sins(word_CODE_bss_80069584) * 64.0f) / 32768.0f) + titleTransitionX;
        gdl = insert_sniper_sight_eye_intro(gdl);
        gdl = insert_sight_backdrop_eye_intro(gdl);
        gdl = insert_bond_eye_intro(gdl);
        gdl = sub_GAME_7F01CA18(gdl);
        if (intro_eye_counter >= INTRO_EYE_COUNTER_CASE_4)
        {
            intro_eye_counter = 0;
            gunbarrel_mode++;
        }
        break;

    case 5:
        word_CODE_bss_80069584 += INCVAL;
        g_TitleX = ((sins(word_CODE_bss_80069584) * 64.0f) / 32768.0f) + titleTransitionX;
        gdl = insert_sniper_sight_eye_intro(gdl);
        gdl = insert_sight_backdrop_eye_intro(gdl);
        gdl = insert_bond_eye_intro(gdl);
        gdl = sub_GAME_7F01CA18(gdl);
        
        intro_eye_counter += INTRO_EYE_COUNTER_CASE_5_ADD;
        
        gdl = sub_GAME_7F007E70(gdl, intro_eye_counter);
        if (intro_eye_counter >= 0xF7) {
            intro_eye_counter = 0;
            gunbarrel_mode++;                
        }
        break;

    case 6:
        gSPDisplayList(gdl++, &dlBasicGeometry);
        gdl = insert_imageDL(gdl);
        if (intro_eye_counter++ >= INTRO_EYE_COUNTER_CASE_6) {
            intro_eye_counter = 0;
            gunbarrel_mode++;
        }
        break;
    };

    return gdl;
}
#endif

#if 0
RECOMP_PATCH s16 bondviewGetCurrentPlayerViewportUly(void)
{
    f32 t;

    if (getPlayerCount() == 2)
    {
        if (get_cur_playernum() == 0)
        {
#ifdef VERSION_EU
            return 0;
#else
            return VIEWPORT_ULY_2P_PLAYER_1;
#endif
        }

        return VIEWPORT_ULY_2P_PLAYER_2;
    }

    if (getPlayerCount() >= 3)
    {
        if (get_cur_playernum() < 2)
        {
#ifdef VERSION_EU
            return 0;
#else
            return VIEWPORT_ULY_4P_PLAYER_12;
#endif
        }

        return VIEWPORT_ULY_4P_PLAYER_34;
    }

    if (cameraBufferToggle != 0)
    {
        if (cur_player_get_screen_setting() == SCREEN_SIZE_WIDESCREEN)
        {
            return VIEWPORT_ULY_CAM_WIDESCREEN;
        }
        else if (cur_player_get_screen_setting() == SCREEN_SIZE_CINEMA)
        {
            return VIEWPORT_ULY_CAM_CINEMA;
        }
        else
        {
            return VIEWPORT_ULY_CAM_FULLSCREEN;
        }
    }

    if (cur_player_get_screen_setting() == SCREEN_SIZE_WIDESCREEN)
    {
        t = bondviewGetPauseAnimationPercent();
        return (s16) ((s32) (WIDESCREEN_ULY_SCALE_FACTOR * t) + VIEWPORT_ULY_WIDESCREEN_OFFSET);
    }
    else if (cur_player_get_screen_setting() == SCREEN_SIZE_CINEMA)
    {
        t = bondviewGetPauseAnimationPercent();
        return (s16) ((s32) (CINEMA_ULY_SCALE_FACTOR * t) + VIEWPORT_ULY_CINEMA_OFFSET);
    }
    else
    {
#ifdef VERSION_EU
            return 0;
#else
            return VIEWPORT_ULY_DEFAULT;
#endif
    }
}
#endif

#if 0
RECOMP_PATCH void bondviewMovePlayerUpdateViewport(s8 stick_x, s8 stick_y, u16 buttons)
{
#ifdef VERSION_EU
    f32 faspect;
#endif

    set_cur_player_fovy(FOV_Y_F);

    // This call doesn't do anything, the call viSetFovY(g_CurrentPlayer->fovy); in lvlRender
    // will actually change the field of view.
    // The call above should set g_CurrentPlayer->fovy, but it doesn't seem to affect
    // the fov....
    viSetFovY(FOV_Y_F);

    if (cameraFrameCounter1 != 0)
    {
        if ((cameraFrameCounter1 >= 4) && (resolution != 0) && (viGetFrameBuf2() == (u8*)(cfb_16[1])))
        {
            cameraBufferToggle = 1;
            cameraFrameCounter1 = 0;
        }
        else
        {
            cameraFrameCounter1 += 1;
        }
    }
    else
    {
        if (cameraFrameCounter2 != 0)
        {
            if ((cameraFrameCounter2 >= 4) && (viGetFrameBuf2() == (u8*)(cfb_16[0])))
            {
                cameraBufferToggle = 0;
                cameraFrameCounter2 = 0;
            }
            else
            {
                cameraFrameCounter2 += 1;
            }
        }
    }

    if ((cameraBufferToggle != 0) && (viGetFrameBuf2() == (u8*)(cfb_16[1])))
    {
        viSetFrameBuf2((u8 *) resolution);
    }

#ifdef VERSION_EU
    if (get_screen_ratio() == SCREEN_RATIO_16_9)
    {
        faspect = ((f32) bondviewGetCurrentPlayerViewportWidth() / (f32) bondviewGetCurrentPlayerViewportHeight()) * 0.75f * WIDESCREEN_ASPECT;
    }
    else
    {
        faspect = (f32) bondviewGetCurrentPlayerViewportWidth() / (f32) bondviewGetCurrentPlayerViewportHeight();
    }

    if (cameraBufferToggle == 0)
    {
        faspect *= EU_CAMERA_8003642C_ASPECT;
    }

    set_cur_player_aspect(faspect);
    viSetAspect(faspect);

#else

    if (get_screen_ratio() == SCREEN_RATIO_16_9)
    {
        set_cur_player_aspect(((f32) bondviewGetCurrentPlayerViewportWidth() / (f32) bondviewGetCurrentPlayerViewportHeight()) * 0.75f * WIDESCREEN_ASPECT);
        viSetAspect(((f32) bondviewGetCurrentPlayerViewportWidth() / (f32) bondviewGetCurrentPlayerViewportHeight()) * 0.75f * WIDESCREEN_ASPECT);
    }
    else
    {
        set_cur_player_aspect((f32) bondviewGetCurrentPlayerViewportWidth() / (f32) bondviewGetCurrentPlayerViewportHeight());
        viSetAspect((f32) bondviewGetCurrentPlayerViewportWidth() / (f32) bondviewGetCurrentPlayerViewportHeight());
    }
#endif

    set_cur_player_screen_size( bondviewGetCurrentPlayerViewportWidth(), bondviewGetCurrentPlayerViewportHeight());
    set_cur_player_viewport_size( get_curplayer_viewport_ulx(), bondviewGetCurrentPlayerViewportUly());
    viSetXY(getWidth320or440(), getHeight330or240());
    viSetBuf(getWidth320or440(), getHeight330or240());
    viSetViewSize(bondviewGetCurrentPlayerViewportWidth(), bondviewGetCurrentPlayerViewportHeight());
    viSetViewPosition(get_curplayer_viewport_ulx(), bondviewGetCurrentPlayerViewportUly());
    currentPlayerUpdateColourScreenProperties();
    currentPlayerTickChrFade();
    set_BONDdata_autoaim_y(cur_player_get_autoaim());
    set_BONDdata_autoaim_x(cur_player_get_autoaim());
    set_BONDdata_lookahead_setting(cur_player_get_lookahead());
    gunSetGunAmmoVisible(GUNAMMOREASON_OPTION, cur_player_get_ammo_onscreen_setting());

    gunSetSightVisible(
        GUNSIGHTREASON_1,
        (getPlayerCount() == 1 && cur_player_get_sight_onscreen_control())
            || (getPlayerCount() >= 2 && g_playerPerm->sight)
    );

#if defined(VERSION_EU)
    if (1);
#endif

    if ((g_CameraMode == CAMERAMODE_NONE) || ((g_CameraMode == CAMERAMODE_FP) && (is_timer_active != 0)) || (g_CameraMode == CAMERAMODE_FADE_TO_TITLE))
    {
        if (get_cur_playernum() == 0)
        {
            mission_timer += g_ClockTimer;
        }

        MoveBond(stick_x, stick_y, buttons, (u16) g_CurrentPlayer->buttons_pressed);
    }
    else
    {
        bondviewFrozenMoveBond(stick_x, stick_y, buttons, (u16) g_CurrentPlayer->buttons_pressed);
    }

#if defined(BUGFIX_R1)
    watch_time_0 += jpD_800484D0;
#else
    // VERSION_US
    watch_time_0 += speedgraphframes;
#endif

    if (stop_time_flag != 0)
    {
        if ((lvlGetControlsLockedFlag() == 0) && ((buttons & ~(g_CurrentPlayer->buttons_pressed) & (CONT_A | B_BUTTON | Z_TRIG | START_BUTTON | CONT_R | CONT_L))))
        {
            stop_time_flag = 2;

            if (currentPlayerIsFadeComplete())
            {
                if (g_CurrentPlayer->colourscreenfrac == 0.0f)
                {
                    currentPlayerSetFadeColour(0, 0, 0, 0.0f);
                    currentPlayerSetFadeFrac(60.0f, 1.0f);
                }
            }
            else
            {
                if (g_CurrentPlayer->colourfadefracnew == 0.0f)
                {
                    currentPlayerSetFadeFrac(g_CurrentPlayer->colourfadetime60, 1.0f);
                }
            }
        }

        if ((stop_time_flag == 2) && currentPlayerIsFadeComplete() && (g_CurrentPlayer->colourscreenfrac == 1.0f))
        {
            bossReturnTitleStage();
        }
    }

    if (g_CameraAfterCinema)
    {
        sub_GAME_7F07B1A4();
    }

    if (g_CurrentPlayer->bonddead)
    {
        if (g_CurrentPlayer->redbloodfinished == FALSE)
        {
            currentPlayerEquipWeaponWrapper(GUNLEFT, 0);
            currentPlayerEquipWeaponWrapper(GUNRIGHT, 0);

            if (0)
            {
                // removed?
            };
        }

        if (g_CurrentPlayer->redbloodfinished && g_CurrentPlayer->deathanimfinished && (camera_mode >= CAMERAMODE_SWIRL))
        {
            bossRunTitleStage();
        }
    }

    if ((g_CameraMode == CAMERAMODE_FADE_TO_TITLE) && currentPlayerIsFadeComplete())
    {
        bossRunTitleStage();
    }

    g_CurrentPlayer->buttons_pressed = buttons;
}
#endif
