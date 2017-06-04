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

static const float AEC_CHARSPRITE_FACE_RADIUS_SHORTENER = 30;
static const float AEC_CHARSPRITE_FACE_X_MAX = 5;
static const float AEC_CHARSPRITE_FACE_Y_MAX = 5;

SDL_bool AEC_CharacterSprite_CreateNew(AEC_EntityCatalog* entityCatalog, int entity_id, AE_LinkedTexture* characterSpriteSheet, AE_LinkedTexture* faceSpriteSheet, unsigned int numOfFaces);

void AEC_CharacterSprite_SetFlip(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, SDL_RendererFlip flip);

void AEC_CharacterSprite_Render(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, AEC_Camera* camera, SDL_Renderer* renderer, float step);

void AEC_CharacterSprite_MoveLegs(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, float step);

void AEC_CharacterSprite_SetTarget(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, unsigned int target_entity_at);

float AEC_CharacterSprite_Look_X(AEC_EntityCatalog* entityCatalog, unsigned int entity_at);

float AEC_CharacterSprite_Look_Y(AEC_EntityCatalog* entityCatalog, unsigned int entity_at);

#endif /* aec_character_sprite_h */
