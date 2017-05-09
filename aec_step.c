//
//  aec_step.c
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#include "aec_step.h"

void AEC_Step_InputEvent(AEC_EntityCatalog* entityCatalog, SDL_Event event)
{
    for (int entity_at = 0; entity_at < AEC_ENTITY_COUNT; entity_at++)
    {
        AEC_PlayerControlled_GetInput(entityCatalog, entity_at, event);
        AEC_Velocity_UpdateSimple(entityCatalog, entity_at);
    }
}

void AEC_Step_TimeEvent(AEC_EntityCatalog* entityCatalog, float step)
{
    for (int entity_at = 0; entity_at < AEC_ENTITY_COUNT; entity_at++)
    {
        AEC_Displacement_UpdateByVelocity(entityCatalog, entity_at, step);
    }
}

void AEC_Step_CameraEvent(AEC_EntityCatalog* entityCatalog, unsigned int entity_id, AEC_Camera* camera, float step)
{
    if (AEC_Entity_Exists(entityCatalog, entity_id))
    {
        if (camera->has_target)
        {
            AEC_Camera_Refocus(entityCatalog, entity_id - 1, camera);
            AEC_Camera_ShakeUpdate(camera, step);
        }
    }
}
