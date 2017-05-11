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

int AEC_Weapon_CreateNew(AEC_EntityCatalog* entityCatalog, unsigned int entity_id);

int AEC_Weapon_GetWeaponType(AEC_EntityCatalog* entityCatalog, unsigned int entity_id);

float AEC_Weapon_GetClockLength(AEC_EntityCatalog* entityCatalog, unsigned int entity_id);

void AEC_Weapon_Activate(AEC_EntityCatalog* entityCatalog, unsigned int entity_id);

void AEC_Weapon_Step(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, float step);

void AEC_Weapon_SwordRotate(AEC_EntityCatalog* entityCatalog, unsigned int entity_at);

#endif /* aec_weapon_h */
