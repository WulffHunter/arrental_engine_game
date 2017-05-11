//
//  aec_player_controlled.h
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#ifndef aec_player_controlled_h
#define aec_player_controlled_h

#include "ae_components.h"
#include "aec_weapon.h"

void AEC_PlayerControlled_GetInput(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, SDL_Event event);

void AEC_PlayerControlled_SetPlayerKeys(AEC_EntityCatalog* entityCatalog, int entity_id, SDL_Keycode* keys);

SDL_bool AEC_PlayerControlled_SetPlayable(AEC_EntityCatalog* entityCatalog, int entity_id, SDL_bool isPlayable, int player_id);

#endif /* aec_player_controlled_h */
