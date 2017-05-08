//
//  aec_character.c
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#include </Users/JJ/Documents/arrental_engine/arrental_engine/Entity Types/Character/aec_character.h>
//#include "aec_character.h"

unsigned int AEC_Character_CreateNew(AEC_EntityCatalog* entityCatalog, AE_LinkedTexture* characterSpriteSheet, AE_LinkedTexture* maskSpriteSheet)
{
    //The location of the entity in the array;
    int entity_at = 0;
    while (entityCatalog->entity_id[entity_at] != 0) {
        entity_at++;
    }
    if (entity_at < AEC_ENTITY_COUNT)
    {
        entityCatalog->entity_id[entity_at] = entity_at + 1;
        
        //Set all the necessary components to SDL_TRUE
        entityCatalog->entity_components[entity_at].component_mask[AEC_DISPLACEMENT] = SDL_TRUE;
        entityCatalog->entity_components[entity_at].component_mask[AEC_DRAWABLE] = SDL_TRUE;
        entityCatalog->entity_components[entity_at].component_mask[AEC_VELOCITY] = SDL_TRUE;
        entityCatalog->entity_components[entity_at].component_mask[AEC_MASK] = SDL_TRUE;
        entityCatalog->entity_components[entity_at].component_mask[AEC_CHARACTER_SPRITE] = SDL_TRUE;
        entityCatalog->entity_components[entity_at].component_mask[AEC_TRAIL] = SDL_TRUE;
        
        //Character is an NPC by default
        entityCatalog->entity_components[entity_at].component_mask[AEC_NPC_MOVEMENT_AI] = SDL_TRUE;
        
        AEC_CharacterSprite_CreateNew(entity_at + 1, entityCatalog, characterSpriteSheet);
        AEC_Mask_CreateNew(entity_at + 1, entityCatalog, maskSpriteSheet);
        
        //TESTING CODE!!!
        entityCatalog->drawable[entity_at + 1].width = AEC_CHARACTER_WIDTH;
        entityCatalog->drawable[entity_at + 1].height = AEC_CHARACTER_HEIGHT;
        //TESTING CODE!!!
        
        //If the entity was created, return the id of that entity
        return entity_at + 1;
    }
    
    //If no space was found
    return 0;
}