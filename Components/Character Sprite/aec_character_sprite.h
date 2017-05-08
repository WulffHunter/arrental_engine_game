//
//  aec_character_sprite.h
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#ifndef aec_character_sprite_h
#define aec_character_sprite_h

#include "ae_components.h"

SDL_bool AEC_CharacterSprite_CreateNew(int entity_id, AEC_EntityCatalog* entityCatalog, AE_LinkedTexture* characterSpriteSheet);

void AEC_CharacterSprite_SetFlip(CHARACTER_SPRITE* characterSprite, SDL_RendererFlip flip);

void AEC_CharacterSprite_Render(CHARACTER_SPRITE* character_sprite, DISPLACEMENT* displacement, AEC_Camera* camera, SDL_Renderer* renderer, float step);

void AEC_CharacterSprite_MoveLegs(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, float step);

#endif /* aec_character_sprite_h */
