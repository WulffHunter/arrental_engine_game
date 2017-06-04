//
//  ae_components.c
//  arrental_engine
//
//  Created by Jared Rand on 2017-02-06.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#include "ae_components.h"
#include "arrental_engine.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

unsigned int AEC_Entity_CreateNew(AEC_EntityCatalog* entityCatalog)
{
    int entity_at = 0;
    while (entityCatalog->entity_id[entity_at] != 0)
    {
        entity_at++;
    }
    if (entity_at < AEC_ENTITY_COUNT)
    {
        entityCatalog->entity_id[entity_at] = entity_at + 1;
        return entity_at + 1;
    }
    return 0;
}

SDL_bool AEC_Entity_Exists(AEC_EntityCatalog* entityCatalog, unsigned int entity_id)
{
    return (entity_id > 0 && entityCatalog->entity_id[entity_id - 1] != 0);
}

uint64_t AEC_GetIsoDepth(AEC_EntityCatalog* entityCatalog, unsigned int entity_at)
{
    if (entityCatalog->entity_components[entity_at].component_mask[AEC_DISPLACEMENT])
    {
        return entityCatalog->displacement[entity_at].x + entityCatalog->displacement[entity_at].y + entityCatalog->displacement[entity_at].z;
    }
    return 0;
    //return entityCatalog->displacement[entity_at].y;
}

//Creates a randomized skin color in the range of realistic
AE_ColorBundle* AEC_GetRandomSkinColor()
{
    int_least8_t darken = (int_least8_t )AE_Random(0, 4);
    AE_ColorBundle* output = SDL_malloc(sizeof(AE_ColorBundle));
    Uint8 r = (Uint8)AE_Random(231, 255);
    Uint8 g = (Uint8)AE_Random(164, 216);
    Uint8 b = (Uint8)AE_Random(102, 165);
    Uint8 tone;
    if (darken == 3)
    {
        tone = (Uint8 )AE_Random(0, 60);
        output->r = AE_BlendColorChannel(r, 1, tone);
        output->g = AE_BlendColorChannel(g, 1, tone);
        output->b = AE_BlendColorChannel(b, 1, tone);
    }
    else
    {
        tone = (Uint8 )AE_Random(0, 15);
        output->r = AE_BlendColorChannel(r, 0x00, tone);
        output->g = AE_BlendColorChannel(g, 0x00, tone);
        output->b = AE_BlendColorChannel(b, 0x00, tone);
    }
    return output;
}

//
//
//START: CAMERA FUNCTIONS
//
//

AEC_Camera* AEC_Camera_CreateNew(uint64_t x, uint64_t y, uint64_t w, uint64_t h)
{
    AEC_Camera* output = SDL_malloc(sizeof(AEC_Camera));
    output->x = x;
    output->y = y;
    output->w = w;
    output->h = h;
    return output;
}

void AEC_Camera_Refocus(AEC_EntityCatalog* entityCatalog, unsigned int target_entity, AEC_Camera* camera)
{
    if (entityCatalog->entity_components[target_entity].component_mask[AEC_DISPLACEMENT])
    {
        camera->x = entityCatalog->displacement[target_entity].x - (camera->w / 2);
        camera->y = entityCatalog->displacement[target_entity].y - (camera->h / 2);
    }
}

void AEC_Camera_SetNewShake(AEC_Camera* camera, float shake_length, float shake_amount)
{
    camera->shake_length = shake_length;
    camera->shake_current_time = 0;
    camera->shake_amount = shake_amount;
}

void AEC_Camera_ShakeUpdate(AEC_Camera* camera, float step)
{
    if (camera->shake_length > 0)
    {
        camera->shake_current_time += step;
        camera->x += AE_Random(camera->shake_amount * -1, camera->shake_amount);
        camera->y += AE_Random(camera->shake_amount * -1, camera->shake_amount);
        if (camera->shake_current_time >= camera->shake_length)
        {
            AEC_Camera_SetNewShake(camera, 0, 0);
        }
    }
}

void AEC_Camera_HasTarget(AEC_Camera* camera, SDL_bool has_target)
{
    camera->has_target = has_target;
}

//
//
//END: CAMERA FUNCTIONS
//
//
