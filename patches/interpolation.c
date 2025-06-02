#include "patches.h"

#if 0

extern Mtx roomMatrices[300];
s32 setupRoomTransformationMatrix(s32 room);

RECOMP_PATCH Gfx * applyRoomMatrixToDisplayList(Gfx *gdl,int roomID)
{
    s32 roomIndex;
    //gEXEnable(gdl++);


    gEXMatrixGroupDecomposed(gdl++, (roomID), G_EX_PUSH, G_MTX_MODELVIEW,
    G_EX_COMPONENT_AUTO, G_EX_COMPONENT_AUTO, G_EX_COMPONENT_AUTO,
    G_EX_COMPONENT_INTERPOLATE, G_EX_COMPONENT_INTERPOLATE, G_EX_COMPONENT_SKIP,
    G_EX_COMPONENT_INTERPOLATE, G_EX_ORDER_AUTO, G_EX_EDIT_ALLOW);
    
    roomIndex = setupRoomTransformationMatrix(roomID);
    gSPMatrix(gdl++, &roomMatrices[roomIndex], G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    //gEXPopMatrixGroup(gdl++, G_MTX_MODELVIEW);
    

    return gdl;
}
#endif