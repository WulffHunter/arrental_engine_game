//
//  aec_weapon.c
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-08.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#include "aec_weapon.h"

int AEC_Weapon_CreateNew(AEC_EntityCatalog* entityCatalog, unsigned int entity_id)
{
    if (AEC_Entity_Exists(entityCatalog, entity_id))
    {
        entityCatalog->weapon[entity_id - 1].activated = SDL_FALSE;
        entityCatalog->weapon[entity_id - 1].is_in_use = SDL_FALSE;
    }
    return 0;
}

int AEC_Weapon_GetWeaponType(AEC_EntityCatalog* entityCatalog, unsigned int entity_id)
{
    //TESTING CODE UNTIL DATABASE IS WORKING
    return AEC_WEPTYPE_SWORD;
    //TESTING CODE UNTIL DATABASE IS WORKING
    
    /*It should look like:
    if (AEC_Entity_Exists(entityCatalog, entity_id))
    {
        return AEC_Database[AEC_DATABASE_WEAPONS][AEC_DB_WEP_TYPE][entityCatalog->inventory[entity_id - 1].inventory[AEC_INVTYPE_WEAPON][entityCatalog->inventory[entity_id - 1].equipped[AEC_INVTYPE_WEAPON]]];
    }
     */
}

float AEC_Weapon_GetClockLength(AEC_EntityCatalog* entityCatalog, unsigned int entity_id)
{
    //TESTING CODE UNTIL DATABASE IS WORKING
    return 1;
    //TESTING CODE UNTIL DATABASE IS WORKING
    
    /*It should look like:
     if (AEC_Entity_Exists(entityCatalog, entity_id))
     {
     return AEC_Database[AEC_DATABASE_WEAPONS][AEC_DB_WEP_CLOCKLENGTH][entityCatalog->inventory[entity_id - 1].inventory[AEC_INVTYPE_WEAPON][entityCatalog->inventory[entity_id - 1].equipped[AEC_INVTYPE_WEAPON]]];
     }
     */
}

void AEC_Weapon_Activate(AEC_EntityCatalog* entityCatalog, unsigned int entity_id)
{
    if (AEC_Entity_Exists(entityCatalog, entity_id))
    {
        entityCatalog->weapon[entity_id - 1].activated = SDL_TRUE;
    }
}

void AEC_Weapon_Step(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, float step)
{
    if (entityCatalog->weapon[entity_at].activated)
    {
        entityCatalog->weapon[entity_at].activated = SDL_FALSE;
        if (!entityCatalog->weapon[entity_at].is_in_use)
        {
            entityCatalog->weapon[entity_at].is_in_use = SDL_TRUE;
            entityCatalog->weapon[entity_at].weapon_current_time = 0;
            entityCatalog->weapon[entity_at].weapon_clock_length = AEC_Weapon_GetClockLength(entityCatalog, entity_at + 1);
            return;
        }
    }
    if (entityCatalog->weapon[entity_at].is_in_use)
    {
        entityCatalog->weapon[entity_at].weapon_current_time += step;
        if (entityCatalog->weapon[entity_at].weapon_current_time > entityCatalog->weapon[entity_at].weapon_clock_length)
        {
            entityCatalog->weapon[entity_at].is_in_use = SDL_FALSE;
            entityCatalog->weapon[entity_at].weapon_current_time = 0;
            entityCatalog->weapon[entity_at].weapon_clock_length = 0;
        }
    }
}

void AEC_Weapon_SwordRotate(AEC_EntityCatalog* entityCatalog, unsigned int entity_id);
