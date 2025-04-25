#ifndef EXTERNS_H
#define EXTERNS_H

#include "patches.h"

u32 __osSetFpcCsr(u32);
void* setSPToEnd(u8* stack, u32 size);
void mainproc(void* args);
void osInitialize(void);
s32 boot_osPiRawStartDma(s32, u32, void*, u32);
void osCreateThread(OSThread*, OSId, void (*)(void*), void*, void*, OSPri);

s16 viGetViewLeft(void);
s16 viGetViewTop(void);
s16 viGetViewWidth(void);
s16 viGetViewTop(void);
s16 viGetViewHeight(void);

s16 viGetX(void);
s16 viGetY(void);

s32 get_cur_playernum(void);
s32 getPlayerCount(void);

u16 joyGetButtons(s8 contpadnum, u16 mask);
u16 joyGetButtonsPressedThisFrame(s8 contpadnum, u16 mask);

f32 bondviewGetPauseAnimationPercent(void);
u32 cur_player_get_screen_setting(void);
void currentPlayerSetScreenPosition(f32 left, f32 top);

s32 alCSPGetState(ALCSPlayer* seqp);
void musicTrack1Stop(void);
void musicTrack1ApplySeqpVol(u16 volume);
void romCopy(void* target, void* source, u32 size);
u32 decompressdata(u8* src, u8* dst, struct huft* hlist);
u16 musicTrack1GetVolume(void);
void musicTrack2ApplySeqpVol(u16 volume);
void musicTrack3ApplySeqpVol(u16 volume);
u16 musicTrack2GetVolume(void);
u16 musicTrack3GetVolume(void);
void alCSPPlay(ALCSPlayer* seqp);
void alCSPSetSeq(ALCSPlayer* seqp, ALCSeq* seq);
void musicTrack2Stop(void);
void musicTrack3Stop(void);
f32 get_room_data_float1(void);
struct CurrentEnvironmentRecord *fogGetCurrentEnvironmentp(void);
Gfx *viSetFillColor(Gfx *gdl, s32 r, s32 g, s32 b);
void sub_GAME_7F093880(f32 offset_x, f32 offset_y, coord3d *out);
f32 getPlayer_c_screenwidth(void);
s32 sub_GAME_7F0938FC(coord3d *arg0, coord3d *arg1, f32 *arg2);
s32 sub_GAME_7F093A78(coord3d *arg0, coord3d *arg1, f32 *arg2);
f32 getPlayer_c_screentop(void);
f32 getPlayer_c_screenheight(void);
s32 sub_GAME_7F0938FC(coord3d *arg0, coord3d *arg1, f32 *arg2);
s32 sub_GAME_7F093BFC(coord3d *arg0, coord3d *arg1, f32 *arg2);
f32 getPlayer_c_screentop(void);
f32 getPlayer_c_screenleft(void);
void sub_GAME_7F093FA4(SkyRelated18 *arg0, f32 arg1);
void texSelect(Gfx **gdlptr, struct sImageTableEntry *tconfig, u32 arg2, s32 arg3, u32 ulst);
Mtxf *currentPlayerGetProjectionMatrixF(void);
void matrix_4x4_multiply(Mtxf *lhs, Mtxf *rhs, Mtxf *result);
Mtxf *camGetWorldToScreenMtxf(void);
void sub_GAME_7F097388(SkyRelated18 *arg0, Mtxf *arg1, u16 arg2, f32 arg3, f32 arg4, SkyRelated38 *arg5);
f32 skyClamp(f32 a, f32 b, f32 c);
Mtx *dynAllocateMatrix(void);
void/*Vtx?*/ *dynAllocate7F0BD6C4(s32 count);
void skyChooseCloudVtxColour(SkyRelated18 *arg0, f32 arg1);
Gfx *sub_GAME_7F097818(Gfx *gdl, SkyRelated38 *arg1, SkyRelated38 *arg2, SkyRelated38 *arg3, f32 arg4, s32 textured);
Gfx* sub_GAME_7F09343C(Gfx*, s32);

extern struct sImageTableEntry *skywaterimages;
extern Mtxf dword_CODE_bss_80079E98;
extern f32 g_SkyCloudOffset;
extern struct player* g_CurrentPlayer;
extern s32 cameraFrameCounter1;
extern s32 cameraFrameCounter2;
extern s32 cameraBufferToggle;
extern s32 g_ModelDistanceDisabled;
extern s32 z_buffer_height;
extern s32 z_buffer_width;
extern s32 z_buffer;
extern u8 sp_main[32768];
extern OSThread mainThread;
extern s32* stack_pointer;
extern s32 g_ModelDistanceDisabled;
extern u8* g_GfxBuffers[3];
extern u8 g_GfxActiveBufferIndex;
extern s32 g_GfxRequestedDisplayList;
extern VideoSettings* g_ViBackData;
extern s32 bgViewRelated[4];
extern s32 g_musicXTrack2CurrentTrackNum;
extern ALCSPlayer* g_musicXTrack2SeqPlayer;
extern s8 g_sndBootswitchSound;
extern s32 g_musicXTrack1CurrentTrackNum;
extern ALCSPlayer* g_musicXTrack1SeqPlayer;
extern u16 g_musicTrackLength[64];
extern u16 g_musicTrackCompressedLength[63];
extern u8* g_musicXTrack1SeqData;
extern RareALSeqBankFile* g_musicDataTable;
extern ALCSeq g_musicXTrack1Seq;
extern u8* g_musicXTrack2SeqData;
extern ALCSeq g_musicXTrack2Seq;
extern s32 g_musicXTrack3CurrentTrackNum;
extern ALCSPlayer* g_musicXTrack3SeqPlayer;
extern u8* g_musicXTrack3SeqData;
extern ALCSeq g_musicXTrack3Seq;

#endif
