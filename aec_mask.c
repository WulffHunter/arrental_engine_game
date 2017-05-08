//
//  aec_mask.c
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#include "aec_mask.h"

SDL_bool AEC_Mask_CreateNew(int entity_id, AEC_EntityCatalog* entityCatalog, AE_LinkedTexture* maskSpriteSheet)
{
    SDL_bool success = SDL_FALSE;
    for (int search = 0; search < AEC_ENTITY_COUNT; search++)
    {
        if (entityCatalog->entity_id[search] == entity_id)
        {
            //Set the components catalog to show that the entity has a charactersprite
            entityCatalog->entity_components[search].component_mask[AEC_MASK] = SDL_TRUE;
            
            //Fill the list of character bodypart sprites
            
            AE_FillSprite(&entityCatalog->mask[search].sprite, maskSpriteSheet, 0, 0, 1, 32, 32, 32/2, 32/2);
            AE_SpriteSetAlpha(&entityCatalog->mask[search].sprite, 64);
        }
    }
    return success;
}

void AEC_Mask_Render(MASK* mask, DISPLACEMENT* displacement, float x_scale, float y_scale, AEC_Camera* camera, SDL_Renderer* renderer, float step)
{
    int x = (int)(displacement->x - camera->x);
    int y = (int)(displacement->y - camera->y);
    AE_SpriteRender(&mask->sprite, renderer, x-(AEC_CHARACTER_WIDTH/2)*x_scale, y-(AEC_CHARACTER_HEIGHT)*y_scale, 0, step);
}
