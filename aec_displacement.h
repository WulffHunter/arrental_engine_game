//
//  aec_displacement.h
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#ifndef aec_displacement_h
#define aec_displacement_h

#include "ae_components.h"
#include "aec_character_sprite.h"

void AEC_Displacement_UpdateByVelocity(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, float step);

#endif /* aec_displacement_h */
