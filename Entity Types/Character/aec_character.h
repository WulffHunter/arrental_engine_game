//
//  aec_character.h
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#ifndef aec_character_h
#define aec_character_h

#include "ae_components.h"
#include "aec_character_sprite.h"
#include "aec_mask.h"

unsigned int AEC_Character_CreateNew(AEC_EntityCatalog* entityCatalog, AE_LinkedTexture* characterSpriteSheet, AE_LinkedTexture* maskSpriteSheet);

#endif /* aec_character_h */
