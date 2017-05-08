//
//  aec_render.c
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#include </Users/JJ/Documents/arrental_engine/arrental_engine/Events/Step/aec_renderer.h>
//#include "aec_renderer.h"

//
//
//START: RENDERING FUNCTIONS
//
//

void AEC_Render_Entity(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, AEC_Camera* camera, SDL_Renderer* renderer, float step)
{
    if (entityCatalog->entity_id[entity_at] > 0)
    {
        //If there is a character sprite and a displacement and it's drawable
        if (entityCatalog->entity_components[entity_at].component_mask[AEC_DISPLACEMENT] && entityCatalog->entity_components[entity_at].component_mask[AEC_DRAWABLE] && AEC_Drawable_IsInCamera(entityCatalog, entity_at, camera))
        {
            if (entityCatalog->entity_components[entity_at].component_mask[AEC_MASK])
            {
                AEC_Mask_Render(&entityCatalog->mask[entity_at], &entityCatalog->displacement[entity_at], 1, 1, camera, renderer, step);
            }
            if (entityCatalog->entity_components[entity_at].component_mask[AEC_CHARACTER_SPRITE])
            {
                AEC_CharacterSprite_Render(&entityCatalog->character_sprite[entity_at], &entityCatalog->displacement[entity_at], camera, renderer, step);
            }
        }
    }
}

void AEC_Render_CatalogToBuffer(AEC_EntityCatalog* entityCatalog, AEC_SpriteBuffer* spriteBuffer)
{
    unsigned int heap_size = 0;
    unsigned int heap_at = 1;
    int frame = spriteBuffer->frame + 1;
    uint64_t x, y, z;
    //unsigned int i, parent;
    uint64_t temp_depth;
    for (int search = 0; search < AEC_ENTITY_COUNT; search++)
    {
        if (entityCatalog->entity_components[search].component_mask[AEC_DRAWABLE] && entityCatalog->entity_components[search].component_mask[AEC_DISPLACEMENT])
        {
            //Prepare data for heap insertion
            temp_depth = AEC_GetIsoDepth(entityCatalog, search);
            x = entityCatalog->displacement[search].x;
            y = entityCatalog->displacement[search].y;
            z = entityCatalog->displacement[search].z;
            
            //Prepare variables for heap insertion
            heap_size++;
            heap_at = heap_size;
            spriteBuffer->is_filled[heap_at] = frame;
            
            while (heap_at > 0 && spriteBuffer->y[heap_at-1] >= y && spriteBuffer->is_filled[heap_at-1] == frame)
            {
                spriteBuffer->entity[heap_at] = spriteBuffer->entity[heap_at-1];
                spriteBuffer->depth[heap_at] = spriteBuffer->depth[heap_at-1];
                spriteBuffer->x[heap_at] = spriteBuffer->x[heap_at-1];
                spriteBuffer->y[heap_at] = spriteBuffer->y[heap_at-1];
                spriteBuffer->z[heap_at] = spriteBuffer->z[heap_at-1];
                
                heap_at = heap_at-1;
            }
            
            //ORIGINAL CODE
            
            spriteBuffer->is_filled[heap_at] = frame;
            spriteBuffer->x[heap_at] = x;
            spriteBuffer->y[heap_at] = y;
            spriteBuffer->z[heap_at]= z;
            spriteBuffer->entity[heap_at] = search;
            spriteBuffer->depth[heap_at] = temp_depth;
        }
    }
    spriteBuffer->size = heap_size;
    spriteBuffer->frame = frame;
    /**printf("Checking: ");
     for (int q=0;q<heap_size+1;q++)
     {
     if (spriteBuffer->is_filled[q] == frame)
     {
     printf("%d ", spriteBuffer->y[q]);
     }
     }
     printf("\n");*/
}

void AEC_Render_SpriteBuffer(AEC_SpriteBuffer* spriteBuffer, AEC_EntityCatalog* entityCatalog, AEC_Camera* camera, SDL_Renderer* renderer, float step)
{
    int frame = spriteBuffer->frame;
    //for (int i = AEC_ENTITY_COUNT; i > 0; i--)
    for (int i = 0; i < AEC_ENTITY_COUNT + 1; i++)
    {
        if (spriteBuffer->is_filled[i] == frame)
        {
            AEC_Render_Entity(entityCatalog, spriteBuffer->entity[i], camera, renderer, step);
        }
    }
}

//
//
//END: RENDERING FUNCTIONS
//
//

//
//
//START: SPRITE BUFFER FUNCTIONS
//
//

//Creates an empty buffer for sprites before rendering
AEC_SpriteBuffer* AEC_SpriteBuffer_CreateNew()
{
    //Allocates the empty buffer
    AEC_SpriteBuffer* output = malloc(sizeof(AEC_SpriteBuffer));
    output->size = 0;
    output->frame = 0;
    //Empties the entire arrays
    for (int i = 0; i < AEC_ENTITY_COUNT; i++)
    {
        output->depth[i] = 0;
        output->entity[i] = 0;
        output->is_filled[i] = 0;
    }
    return output;
}

void AEC_SpriteBuffer_Flush(AEC_SpriteBuffer* spriteBuffer)
{
    //Clears out the entire sprite buffer
    for (int i = 0; i < AEC_ENTITY_COUNT; i++)
    {
        spriteBuffer->is_filled[i] = SDL_FALSE;
    }
}

//
//
//END: SPRITE BUFFER FUNCTIONS
//
//
