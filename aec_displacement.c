//
//  aec_displacement.c
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#include "aec_displacement.h"

void AEC_Displacement_UpdateByVelocity(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, float step)
{
    if (entityCatalog->entity_id[entity_at] > 0)
    {
        if (entityCatalog->entity_components[entity_at].component_mask[AEC_DISPLACEMENT] && entityCatalog->entity_components[entity_at].component_mask[AEC_VELOCITY])
        {
            if (entityCatalog->velocity[entity_at].moving)
            {
                uint64_t current_x = entityCatalog->displacement[entity_at].x;
                uint64_t new_x = (entityCatalog->displacement[entity_at].x += AE_FloatBase(entityCatalog->velocity[entity_at].xVel * step));
                entityCatalog->displacement[entity_at].y += AE_FloatBase(entityCatalog->velocity[entity_at].yVel * step);
                if (current_x < new_x)
                {
                    entityCatalog->displacement[entity_at].reflection = SDL_FLIP_HORIZONTAL;
                    AEC_CharacterSprite_SetFlip(&entityCatalog->character_sprite[entity_at], SDL_FLIP_HORIZONTAL);
                }
                else if (current_x > new_x)
                {
                    entityCatalog->displacement[entity_at].reflection = SDL_FLIP_NONE;
                    AEC_CharacterSprite_SetFlip(&entityCatalog->character_sprite[entity_at], SDL_FLIP_NONE);
                }
            }
            AEC_CharacterSprite_MoveLegs(entityCatalog, entity_at, step);
        }
    }
}
