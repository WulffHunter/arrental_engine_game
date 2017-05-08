//
//  aec_step.c
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#include </Users/JJ/Documents/arrental_engine/arrental_engine/Events/Step/aec_step.h>
//#include "aec_step.h"

void AEC_Step_InputEvent(AEC_EntityCatalog* entityCatalog, SDL_Event event);
{
    for (int entity_at = 0; entity_at < AEC_ENTITY_COUNT; entity_at++)
    {
        AEC_PlayerControlled_GetInput(entityCatalog, entity_at, event)
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
