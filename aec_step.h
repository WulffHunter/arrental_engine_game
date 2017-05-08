//
//  aec_step.h
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#ifndef aec_step_h
#define aec_step_h

#include "ae_components.h"
#include "aec_displacement.h"
#include "aec_velocity.h"
#include "aec_player_controlled.h"

void AEC_Step_InputEvent(AEC_EntityCatalog* entityCatalog, SDL_Event e);

void AEC_Step_TimeEvent(AEC_EntityCatalog* entityCatalog, float step);

#endif /* aec_step_h */
