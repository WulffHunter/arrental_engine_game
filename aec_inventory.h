//
//  aec_inventory.h
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-08.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#ifndef aec_inventory_h
#define aec_inventory_h

#include "ae_components.h"

int AEC_Inventory_AddItem(AEC_EntityCatalog* entityCatalog, unsigned int entity_id, unsigned int type, unsigned int item);

int AEC_Inventory_ItemExists(AEC_EntityCatalog* entityCatalog, unsigned int entity_id, unsigned int type, unsigned int item);

SDL_bool AEC_Inventory_RemoveItem(AEC_EntityCatalog* entityCatalog, unsigned int entity_id, unsigned int type, int item_address);

#endif /* aec_inventory_h */
