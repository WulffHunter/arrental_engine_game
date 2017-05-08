//
//  aec_render.h
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#ifndef aec_render_h
#define aec_render_h

#include "ae_components.h"
#include "aec_drawable.h"
#include "aec_character_sprite.h"
#include "aec_mask.h"

//
//
//STRUCTS FOR RENDERING
//
//

typedef struct {
    unsigned int size;
    int frame;
    int is_filled[AEC_ENTITY_COUNT + 1];
    uint64_t depth[AEC_ENTITY_COUNT + 1];
    uint64_t x[AEC_ENTITY_COUNT + 1];
    uint64_t y[AEC_ENTITY_COUNT + 1];
    uint64_t z[AEC_ENTITY_COUNT + 1];
    int entity[AEC_ENTITY_COUNT + 1];
} AEC_SpriteBuffer;

//
//
//START: RENDERING FUNCTIONS
//
//

void AEC_Render_Entity(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, AEC_Camera* camera, SDL_Renderer* renderer, float step);

void AEC_Render_CatalogToBuffer(AEC_EntityCatalog* entityCatalog, AEC_SpriteBuffer* sprite_buffer);

void AEC_Render_SpriteBuffer(AEC_SpriteBuffer* sprite_buffer, AEC_EntityCatalog* entityCatalog, AEC_Camera* camera, SDL_Renderer* renderer, float step);

//
//
//END: RENDERING FUNCTIONS

//
//
//START: SPRITE BUFFER FUNCTIONS
//
//

AEC_SpriteBuffer* AEC_SpriteBuffer_CreateNew();

void AEC_SpriteBuffer_Flush(AEC_SpriteBuffer* spriteBuffer);

//
//
//END: SPRITE BUFFER FUNCTIONS
//
//

#endif /* aec_render_h */
