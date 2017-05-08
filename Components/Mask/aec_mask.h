//
//  aec_mask.h
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#ifndef aec_mask_h
#define aec_mask_h

#include "ae_components.h"

SDL_bool AEC_Mask_CreateNew(int entity_id, AEC_EntityCatalog* entityCatalog, AE_LinkedTexture* maskSpriteSheet);

void AEC_Mask_Render(MASK* mask, DISPLACEMENT* displacement, float x_scale, float y_scale, AEC_Camera* camera, SDL_Renderer* renderer, float step);

#endif /* aec_mask_h */
