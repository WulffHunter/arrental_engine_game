//
//  aec_character.c
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#include "aec_character.h"

unsigned int AEC_Character_CreateNew(AEC_EntityCatalog* entityCatalog, AE_LinkedTexture* characterSpriteSheet, AE_LinkedTexture* maskSpriteSheet)
{
    //The location of the entity in the array;
    int entity_at = AEC_Entity_CreateNew(entityCatalog);
    if (entity_at > 0)
    {
        //Set all the necessary components to SDL_TRUE
        entityCatalog->entity_components[entity_at - 1].component_mask[AEC_DISPLACEMENT] = SDL_TRUE;
        entityCatalog->entity_components[entity_at - 1].component_mask[AEC_DRAWABLE] = SDL_TRUE;
        entityCatalog->entity_components[entity_at - 1].component_mask[AEC_VELOCITY] = SDL_TRUE;
        entityCatalog->entity_components[entity_at - 1].component_mask[AEC_MASK] = SDL_TRUE;
        entityCatalog->entity_components[entity_at - 1].component_mask[AEC_CHARACTER_SPRITE] = SDL_TRUE;
        entityCatalog->entity_components[entity_at - 1].component_mask[AEC_TRAIL] = SDL_TRUE;
        
        //Character is an NPC by default
        entityCatalog->entity_components[entity_at - 1].component_mask[AEC_NPC_MOVEMENT_AI] = SDL_TRUE;
        
        AEC_CharacterSprite_CreateNew(entityCatalog, entity_at, characterSpriteSheet);
        AEC_Mask_CreateNew(entityCatalog, entity_at, maskSpriteSheet);
        
        entityCatalog->velocity[entity_at - 1].accel_vel = AEC_CHARACTER_VELOCITY_ACCEL;
        entityCatalog->velocity[entity_at - 1].max_vel = AEC_CHARACTER_VELOCITY_MAX;
        
        //TESTING CODE!!!
        entityCatalog->drawable[entity_at - 1].width = AEC_CHARACTER_WIDTH;
        entityCatalog->drawable[entity_at - 1].height = AEC_CHARACTER_HEIGHT;
        //TESTING CODE!!!
    }
    //Return the ID of the entity
    return entity_at;
}
