//
//  aec_mask.c
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#include "aec_mask.h"

SDL_bool AEC_Mask_CreateNew(AEC_EntityCatalog* entityCatalog, int entity_id, AE_LinkedTexture* maskSpriteSheet)
{
    if (AEC_Entity_Exists(entityCatalog, entity_id))
    {
        //Set the components catalog to show that the entity has a charactersprite
        entityCatalog->entity_components[entity_id - 1].component_mask[AEC_MASK] = SDL_TRUE;
        
        //Fill the list of character bodypart sprites
        
        AE_FillSprite(&entityCatalog->mask[entity_id - 1].sprite, maskSpriteSheet, 0, 0, 1, 32, 32, 32/2, 32/2);
        AE_SpriteSetAlpha(&entityCatalog->mask[entity_id - 1].sprite, 64);
        return SDL_TRUE;
    }
    return SDL_FALSE;
}

void AEC_Mask_Render(MASK* mask, DISPLACEMENT* displacement, float x_scale, float y_scale, AEC_Camera* camera, SDL_Renderer* renderer, float step)
{
    int x = (int)(displacement->x - camera->x);
    int y = (int)(displacement->y - camera->y);
    AE_SpriteRender(&mask->sprite, renderer, x-(AEC_CHARACTER_WIDTH/2)*x_scale, y-(AEC_CHARACTER_HEIGHT)*y_scale, 0, step);
}
