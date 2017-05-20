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
    SDL_bool moving;
    float xVel, yVel;
    float max_xVel, max_yVel;
    float accel_xVel, accel_yVel;
    if (entityCatalog->entity_id[entity_at] > 0)
    {
        if (entityCatalog->entity_components[entity_at].component_mask[AEC_VELOCITY])
        {
            moving = SDL_FALSE;
            
            xVel = entityCatalog->velocity[entity_at].xVel;
            yVel = entityCatalog->velocity[entity_at].yVel;
            
            max_xVel = entityCatalog->velocity[entity_at].max_vel*AEC_CHARACTER_X_CONSTANT;
            max_yVel = entityCatalog->velocity[entity_at].max_vel*AEC_CHARACTER_Y_CONSTANT;
            
            accel_xVel = entityCatalog->velocity[entity_at].accel_vel*AEC_CHARACTER_X_CONSTANT;
            accel_yVel = entityCatalog->velocity[entity_at].accel_vel*AEC_CHARACTER_Y_CONSTANT;
            
            if (entityCatalog->velocity[entity_at].direction_on[AEC_KEY_UP])
            {
                //Move isometrically
                if (xVel + accel_xVel <= max_xVel)
                {
                    xVel += accel_xVel;
                }
                if (yVel - accel_yVel >= (max_yVel * -1))
                {
                    yVel -= accel_yVel;
                }
                moving = SDL_TRUE;
            }
            if (entityCatalog->velocity[entity_at].direction_on[AEC_KEY_DOWN])
            {
                //Move isometrically
                if (xVel - accel_xVel >= (max_xVel * -1))
                {
                    xVel -= accel_xVel;
                }
                if (yVel + accel_yVel <= max_yVel)
                {
                    yVel += accel_yVel;
                }
                moving = SDL_TRUE;
            }
            if (entityCatalog->velocity[entity_at].direction_on[AEC_KEY_LEFT])
            {
                //Move isometrically
                if (xVel - accel_xVel >= (max_xVel * -1))
                {
                    xVel -= accel_xVel;
                }
                if (yVel - accel_yVel >= (max_yVel * -1))
                {
                    yVel -= accel_yVel;
                }
                moving = SDL_TRUE;
            }
            if (entityCatalog->velocity[entity_at].direction_on[AEC_KEY_RIGHT])
            {
                //Move isometrically
                if (xVel + accel_xVel <= max_xVel)
                {
                    xVel += accel_xVel;
                }
                if (yVel + accel_yVel <= max_yVel)
                {
                    yVel += accel_yVel;
                }
                moving = SDL_TRUE;
            }
            if (!moving)
            {
                xVel = yVel = 0;
                
                /*if (yVel < 0)
                {
                    yVel += accel_yVel;
                }
                else if (yVel > 0)
                {
                    yVel -= accel_yVel;
                }
                if (xVel < 0)
                {
                    xVel += accel_xVel;
                }
                else if (xVel > 0)
                {
                    xVel -= accel_xVel;
                }*/
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
