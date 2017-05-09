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
    AE_ColorBundle* output = malloc(sizeof(AE_ColorBundle));
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
    AEC_Camera* output = malloc(sizeof(AEC_Camera));
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

//
//
//END: CAMERA FUNCTIONS
//
//
