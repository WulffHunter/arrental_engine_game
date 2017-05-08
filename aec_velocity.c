//
//  aec_velocity.c
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#include "aec_velocity.h"

void AEC_Velocity_UpdateSimple(AEC_EntityCatalog* entityCatalog, unsigned int entity_at)
{
    SDL_bool moving = SDL_FALSE;
    int xVel = 0;
    int yVel = 0;
    if (entityCatalog->entity_id[entity_at] > 0)
    {
        if (entityCatalog->entity_components[entity_at].component_mask[AEC_VELOCITY])
        {
            moving = SDL_FALSE;
            int max_xVel = entityCatalog->velocity[entity_at].max_vel*AEC_CHARACTER_X_CONSTANT;
            int max_yVel = entityCatalog->velocity[entity_at].max_vel*AEC_CHARACTER_Y_CONSTANT;
            if (entityCatalog->velocity[entity_at].direction_on[AEC_KEY_UP])
            {
                //Move isometrically
                xVel = max_xVel;
                yVel = -max_yVel;
                moving = SDL_TRUE;
            }
            if (entityCatalog->velocity[entity_at].direction_on[AEC_KEY_DOWN])
            {
                //Move isometrically
                xVel = -max_xVel;
                yVel = max_yVel;
                moving = SDL_TRUE;
            }
            if (entityCatalog->velocity[entity_at].direction_on[AEC_KEY_LEFT])
            {
                //Move isometrically
                xVel = -max_xVel;
                yVel = -max_yVel;
                moving = SDL_TRUE;
            }
            if (entityCatalog->velocity[entity_at].direction_on[AEC_KEY_RIGHT])
            {
                //Move isometrically
                xVel = max_xVel;
                yVel = max_yVel;
                moving = SDL_TRUE;
            }
            if (!moving)
            {
                xVel = 0;
                yVel = 0;
            }
            if (moving)
            {
                if (!entityCatalog->velocity[entity_at].moving)
                {
                    entityCatalog->velocity[entity_at].just_started_moving = SDL_TRUE;
                }
                else
                {
                    entityCatalog->velocity[entity_at].just_started_moving = SDL_FALSE;
                }
            }
            entityCatalog->velocity[entity_at].moving = moving;
            entityCatalog->velocity[entity_at].xVel = xVel;
            entityCatalog->velocity[entity_at].yVel = yVel;
        }
    }
}
