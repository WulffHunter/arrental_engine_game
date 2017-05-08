//
//  aec_drawable.c
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#include "aec_drawable.h"

SDL_bool AEC_Drawable_IsInCamera(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, AEC_Camera* camera)
{
    if (entityCatalog->entity_components[entity_at].component_mask[AEC_DISPLACEMENT] && entityCatalog->entity_components[entity_at].component_mask[AEC_DRAWABLE])
    {
        int x_compare = (int)(entityCatalog->displacement[entity_at].x - camera->x);
        int y_compare = (int)(entityCatalog->displacement[entity_at].y - camera->y);
        //Return whether or not the entity is in the camera
        /*return (
         entityCatalog->displacement[entity_at].x + (entityCatalog->drawable[entity_at].width / 2) >= camera->x
         && entityCatalog->displacement[entity_at].x - (entityCatalog->drawable[entity_at].width / 2) <= (camera->x + camera->w)
         && entityCatalog->displacement[entity_at].y - (entityCatalog->drawable[entity_at].height) <= (camera->y + camera->h)
         && entityCatalog->displacement[entity_at].y >= camera->y
         );*/
        //printf("%d %d %d %d\n", left_side, right_side, up_side, down_side);
        return (
                x_compare >= (int)((entityCatalog->drawable[entity_at].width / 2)*-1)
                && x_compare <= (int)(camera->w + (entityCatalog->drawable[entity_at].width / 2))
                && y_compare <= (int)(camera->h + (entityCatalog->drawable[entity_at].height))
                && y_compare >= 0
                );
    }
    return SDL_FALSE;
}

//TODO
SDL_bool AEC_Drawable_IsIntersecting(AEC_EntityCatalog* entityCatalog, unsigned int entity1, unsigned int entity2)
{
    if (entityCatalog->entity_components[entity1].component_mask[AEC_DISPLACEMENT] && entityCatalog->entity_components[entity1].component_mask[AEC_DRAWABLE] && entityCatalog->entity_components[entity2].component_mask[AEC_DISPLACEMENT] && entityCatalog->entity_components[entity2].component_mask[AEC_DRAWABLE])
    {
        //Return whether the 2 entities are intersecting
        //TODO
        return SDL_TRUE;
    }
    return SDL_FALSE;
}
