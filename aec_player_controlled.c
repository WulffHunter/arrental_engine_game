//
//  aec_player_controlled.c
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#include "aec_player_controlled.h"

void AEC_PlayerControlled_GetInput(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, SDL_Event event)
{
    if (entityCatalog->entity_id[entity_at] > 0)
    {
        if (entityCatalog->entity_components[entity_at].component_mask[AEC_PLAYER_CONTROLLED] && entityCatalog->entity_components[entity_at].component_mask[AEC_VELOCITY])
        {
            if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
            {
                if (event.key.keysym.sym == entityCatalog->player_controlled[entity_at].key_binds[AEC_KEY_UP])
                {
                    entityCatalog->velocity[entity_at].direction_on[AEC_KEY_UP] = SDL_TRUE;
                }
                if (event.key.keysym.sym == entityCatalog->player_controlled[entity_at].key_binds[AEC_KEY_DOWN])
                {
                    entityCatalog->velocity[entity_at].direction_on[AEC_KEY_DOWN] = SDL_TRUE;
                }
                if (event.key.keysym.sym == entityCatalog->player_controlled[entity_at].key_binds[AEC_KEY_LEFT])
                {
                    entityCatalog->velocity[entity_at].direction_on[AEC_KEY_LEFT] = SDL_TRUE;
                }
                if (event.key.keysym.sym == entityCatalog->player_controlled[entity_at].key_binds[AEC_KEY_RIGHT])
                {
                    entityCatalog->velocity[entity_at].direction_on[AEC_KEY_RIGHT] = SDL_TRUE;
                }
                if (event.key.keysym.sym == entityCatalog->player_controlled[entity_at].key_binds[AEC_KEY_ATTACK])
                {
                    AEC_Weapon_Activate(entityCatalog, entity_at);
                }
            }
            if (event.type == SDL_KEYUP && event.key.repeat == 0)
            {
                if (event.key.keysym.sym == entityCatalog->player_controlled[entity_at].key_binds[AEC_KEY_UP])
                {
                    entityCatalog->velocity[entity_at].direction_on[AEC_KEY_UP] = SDL_FALSE;
                }
                if (event.key.keysym.sym == entityCatalog->player_controlled[entity_at].key_binds[AEC_KEY_DOWN])
                {
                    entityCatalog->velocity[entity_at].direction_on[AEC_KEY_DOWN] = SDL_FALSE;
                }
                if (event.key.keysym.sym == entityCatalog->player_controlled[entity_at].key_binds[AEC_KEY_LEFT])
                {
                    entityCatalog->velocity[entity_at].direction_on[AEC_KEY_LEFT] = SDL_FALSE;
                }
                if (event.key.keysym.sym == entityCatalog->player_controlled[entity_at].key_binds[AEC_KEY_RIGHT])
                {
                    entityCatalog->velocity[entity_at].direction_on[AEC_KEY_RIGHT] = SDL_FALSE;
                }
            }
            else if (event.type == SDL_JOYAXISMOTION)
            {
                if (event.jaxis.which == entityCatalog->player_controlled[entity_at].joystick_id)
                {
                    /*if (event.jaxis.axis == 0)
                    {
                        //If it's going left
                        if (event.jaxis.value < -DEAD_ZONE)
                        {
                            entityCatalog->velocity[entity_at].direction_on[AEC_KEY_LEFT] = SDL_TRUE;
                            entityCatalog->velocity[entity_at].direction_on[AEC_KEY_RIGHT] = SDL_FALSE;
                        }
                        //If it's going right
                        else if (event.jaxis.value > DEAD_ZONE)
                        {
                            entityCatalog->velocity[entity_at].direction_on[AEC_KEY_RIGHT] = SDL_TRUE;
                            entityCatalog->velocity[entity_at].direction_on[AEC_KEY_LEFT] = SDL_FALSE;
                        }
                        else
                        {
                            entityCatalog->velocity[entity_at].direction_on[AEC_KEY_LEFT] = SDL_FALSE;
                            entityCatalog->velocity[entity_at].direction_on[AEC_KEY_RIGHT] = SDL_FALSE;
                        }
                    }
                    if (event.jaxis.axis == 1)
                    {
                        //If it's going up
                        if (event.jaxis.value < -DEAD_ZONE)
                        {
                            entityCatalog->velocity[entity_at].direction_on[AEC_KEY_UP] = SDL_TRUE;
                            entityCatalog->velocity[entity_at].direction_on[AEC_KEY_DOWN] = SDL_FALSE;
                        }
                        //If it's going down
                        else if (event.jaxis.value > DEAD_ZONE)
                        {
                            entityCatalog->velocity[entity_at].direction_on[AEC_KEY_DOWN] = SDL_TRUE;
                            entityCatalog->velocity[entity_at].direction_on[AEC_KEY_UP] = SDL_FALSE;
                        }
                        else
                        {
                            entityCatalog->velocity[entity_at].direction_on[AEC_KEY_UP] = SDL_FALSE;
                            entityCatalog->velocity[entity_at].direction_on[AEC_KEY_DOWN] = SDL_FALSE;
                        }
                    }*/
                    
                    double axis_x = 0;
                    double axis_y = 0;
                    
                    if (event.jaxis.axis == 0)
                    {
                        axis_x = entityCatalog->player_controlled[entity_at].jaxis_x = event.jaxis.value;
                        axis_y = entityCatalog->player_controlled[entity_at].jaxis_y;
                    }
                    if (event.jaxis.axis == 1)
                    {
                        axis_x = entityCatalog->player_controlled[entity_at].jaxis_x;
                        axis_y = entityCatalog->player_controlled[entity_at].jaxis_y = event.jaxis.value;
                    }
                    
                    printf("Currently at: %f, %f: %f\n", axis_x,axis_y, AE_VectorLength(axis_x, axis_y));
                    
                    double pi_over_three_x = (1 / 2);
                    double pi_over_three_y = (pow(3, (1 / 2)) / 2);
                    
                    //If the axis is moved to the left
                    if (AE_VectorIsClockwise(axis_x, axis_y, -1 * pi_over_three_x, pi_over_three_y) && !AE_VectorIsClockwise(axis_x, axis_y, -1 * pi_over_three_x, -1 * pi_over_three_y) && (AE_VectorLength(axis_x, axis_y) > DEAD_ZONE))
                    {
                        entityCatalog->velocity[entity_at].direction_on[AEC_KEY_LEFT] = SDL_TRUE;
                    }
                    else
                    {
                        entityCatalog->velocity[entity_at].direction_on[AEC_KEY_LEFT] = SDL_FALSE;
                    }
                    
                    //If the axis is moved to the right
                    if (AE_VectorIsClockwise(axis_x, axis_y, pi_over_three_x, pi_over_three_y) && !AE_VectorIsClockwise(axis_x, axis_y, pi_over_three_x, -1 * pi_over_three_y) && (AE_VectorLength(axis_x, axis_y) > DEAD_ZONE))
                    {
                        entityCatalog->velocity[entity_at].direction_on[AEC_KEY_RIGHT] = SDL_TRUE;
                    }
                    else
                    {
                        entityCatalog->velocity[entity_at].direction_on[AEC_KEY_RIGHT] = SDL_FALSE;
                    }
                    
                    //If the axis is moved up
                    if (!AE_VectorIsClockwise(axis_x, axis_y, pi_over_three_y, pi_over_three_x) && AE_VectorIsClockwise(axis_x, axis_y, -1 * pi_over_three_y, pi_over_three_x) && (AE_VectorLength(axis_x, axis_y) > DEAD_ZONE))
                    {
                        entityCatalog->velocity[entity_at].direction_on[AEC_KEY_UP] = SDL_TRUE;
                    }
                    else
                    {
                        entityCatalog->velocity[entity_at].direction_on[AEC_KEY_UP] = SDL_FALSE;
                    }
                    
                    //If the axis is moved down
                    if (!AE_VectorIsClockwise(axis_x, axis_y, -1 * pi_over_three_y, -1 * pi_over_three_x) && AE_VectorIsClockwise(axis_x, axis_y, pi_over_three_y, -1 * pi_over_three_x) && (AE_VectorLength(axis_x, axis_y) > DEAD_ZONE))
                    {
                        entityCatalog->velocity[entity_at].direction_on[AEC_KEY_DOWN] = SDL_TRUE;
                    }
                    else
                    {
                        entityCatalog->velocity[entity_at].direction_on[AEC_KEY_DOWN] = SDL_FALSE;
                    }
                }
            }
        }
    }
}

void AEC_PlayerControlled_SetPlayerKeys(AEC_EntityCatalog* entityCatalog, int entity_id, SDL_Keycode* keys)
{
    for (int search = 0; search < AEC_ENTITY_COUNT; search++)
    {
        if (entityCatalog->entity_id[search] == entity_id)
        {
            if (entityCatalog->entity_components[search].component_mask[AEC_PLAYER_CONTROLLED])
            {
                for (int i = 0; i < 6; i++)
                {
                    entityCatalog->player_controlled[search].key_binds[i] = keys[i];
                }
            }
        }
    }
}

SDL_bool AEC_PlayerControlled_SetPlayable(AEC_EntityCatalog* entityCatalog, int entity_id, SDL_bool isPlayable, int player_id)
{
    //Whether resetting the entity playability was successful or not
    SDL_bool success = SDL_FALSE;
    if (entity_id > 0 && entity_id < AEC_ENTITY_COUNT)
    {
        entityCatalog->entity_components[entity_id - 1].component_mask[AEC_PLAYER_CONTROLLED] = isPlayable;
        entityCatalog->entity_components[entity_id - 1].component_mask[AEC_NPC_MOVEMENT_AI] = !isPlayable;
        if (isPlayable)
        {
            entityCatalog->player_controlled[entity_id - 1].player_id = player_id;
        }
        success = SDL_TRUE;
    }
    return success;
}
