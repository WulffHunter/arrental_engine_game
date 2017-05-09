//
//  aec_weapon.h
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-08.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#ifndef aec_weapon_h
#define aec_weapon_h

#include "ae_components.h"

int AEC_Weapon_CreateNew(AEC_EntityCatalog* entityCatalog);

SDL_bool AEC_Weapon_IsInInventory(unsigned int weapon_id);

#endif /* aec_weapon_h */
