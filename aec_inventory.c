//
//  aec_inventory.c
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-08.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#include "aec_inventory.h"

int AEC_Inventory_AddItem(AEC_EntityCatalog* entityCatalog, unsigned int entity_id, unsigned int type, unsigned int item)
{
    int inserted = 0;
    if (AEC_Entity_Exists(entityCatalog, entity_id))
    {
        unsigned int entity_item_count = entityCatalog->inventory[entity_id - 1].item_count[type];
        if (entity_item_count == AEC_INVENTORY_MAX)
        {
            inserted = -1;
        }
        else
        {
            entityCatalog->inventory[entity_id - 1].items[type][entity_item_count] = item;
            entityCatalog->inventory[entity_id - 1].item_count[type]++;
        }
    }
    return inserted;
}

int AEC_Inventory_ItemExists(AEC_EntityCatalog* entityCatalog, unsigned int entity_id, unsigned int type, unsigned int item)
{
    if (AEC_Entity_Exists(entityCatalog, entity_id))
    {
        for (int i = 0; i < entityCatalog->inventory[entity_id - 1].item_count[type]; i++)
        {
            if (entityCatalog->inventory[entity_id - 1].items[type][i] == item)
            {
                return i;
            }
        }
    }
    return -1;
}

SDL_bool AEC_Inventory_RemoveItem(AEC_EntityCatalog* entityCatalog, unsigned int entity_id, unsigned int type, int item_address)
{
    if (AEC_Entity_Exists(entityCatalog, entity_id) && item_address >= 0)
    {
        for (int i = item_address + 1; i < entityCatalog->inventory[entity_id - 1].item_count[type]; i++)
        {
            entityCatalog->inventory[entity_id - 1].items[type][i - 1] = entityCatalog->inventory[entity_id - 1].items[type][i];
        }
        entityCatalog->inventory[entity_id - 1].item_count[type]--;
        entityCatalog->inventory[entity_id - 1].items[type][entityCatalog->inventory[entity_id - 1].item_count[type]] = 0;
        return SDL_TRUE;
    }
    return SDL_FALSE;
}
