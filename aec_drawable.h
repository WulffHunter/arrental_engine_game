//
//  aec_drawable.h
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#ifndef aec_drawable_h
#define aec_drawable_h

#include "ae_components.h"

SDL_bool AEC_Drawable_IsInCamera(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, AEC_Camera* camera);

SDL_bool AEC_Drawable_IsIntersecting(AEC_EntityCatalog* entityCatalog, unsigned int entity1, unsigned int entity2);

#endif /* aec_drawable_h */
