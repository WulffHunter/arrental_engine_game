//
//  aec_character_sprite.c
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#include "aec_character_sprite.h"

SDL_bool AEC_CharacterSprite_CreateNew(AEC_EntityCatalog* entityCatalog, int entity_id, AE_LinkedTexture* characterSpriteSheet)
{
    if (AEC_Entity_Exists(entityCatalog, entity_id))
    {
        //Set the components catalog to show that the entity has a charactersprite
        entityCatalog->entity_components[entity_id - 1].component_mask[AEC_CHARACTER_SPRITE] = SDL_TRUE;
        
        //Fill the list of character bodypart sprites
        
        AE_FillSprite(&entityCatalog->character_sprite[entity_id - 1].bodySprites[AEC_TORSO], characterSpriteSheet, 0, 0, 1, 32, 32, 32/2, 32/2);
        AE_FillSprite(&entityCatalog->character_sprite[entity_id - 1].bodySprites[AEC_CHEST], characterSpriteSheet, 0, 64, 2, 32, 32, 32/2, 32/2);
        AE_FillSprite(&entityCatalog->character_sprite[entity_id - 1].bodySprites[AEC_LEG_LEFT], characterSpriteSheet, 32, 0, 1, 32, 32, 32/2, 32/2);
        AE_FillSprite(&entityCatalog->character_sprite[entity_id - 1].bodySprites[AEC_LEG_RIGHT], characterSpriteSheet, 0, 32, 1, 32, 32, 32/2, 32/2);
        
        //Set the skin color to a random color
        AE_ColorBundle* skinColor = AEC_GetRandomSkinColor();
        AE_SpriteSetColor(&entityCatalog->character_sprite[entity_id - 1].bodySprites[AEC_TORSO], skinColor, AE_SPRITE_KEEP_NONE);
        AE_SpriteSetColor(&entityCatalog->character_sprite[entity_id - 1].bodySprites[AEC_CHEST], skinColor, AE_SPRITE_KEEP_NONE);
        AE_SpriteSetColor(&entityCatalog->character_sprite[entity_id - 1].bodySprites[AEC_LEG_LEFT], skinColor, AE_SPRITE_KEEP_NONE);
        AE_SpriteSetColor(&entityCatalog->character_sprite[entity_id - 1].bodySprites[AEC_LEG_RIGHT], skinColor, AE_SPRITE_KEEP_NONE);
        
        free(skinColor);
        
        entityCatalog->character_sprite[entity_id - 1].draw_part[AEC_LEG_RIGHT] = SDL_TRUE;
        entityCatalog->character_sprite[entity_id - 1].draw_part[AEC_LEG_LEFT] = SDL_TRUE;
        entityCatalog->character_sprite[entity_id - 1].draw_part[AEC_TORSO] = SDL_TRUE;
        entityCatalog->character_sprite[entity_id - 1].draw_part[AEC_CHEST] = SDL_TRUE;
        
        //Set random gender
        int_least8_t gender = (int_least8_t )AE_Random(0, 4);
        
        if (gender >= 3)
        {
            entityCatalog->character_sprite[entity_id - 1].gender = AEC_FEMALE;
        }
        else
        {
            entityCatalog->character_sprite[entity_id - 1].gender = AEC_MALE;
        }
        entityCatalog->character_sprite[entity_id - 1].x_scale = 1;
        entityCatalog->character_sprite[entity_id - 1].y_scale = 1;
        entityCatalog->character_sprite[entity_id - 1].leg_movement_time = 0.15;
    }
    return SDL_FALSE;
}

void AEC_CharacterSprite_SetFlip(CHARACTER_SPRITE* characterSprite, SDL_RendererFlip flip)
{
    
    //For all of the bodyparts in the character sprite (NO MAGIC NUMBERS!)
    for (int i = 0; i < sizeof(characterSprite->bodySprites)/sizeof(characterSprite->bodySprites[0]); i++)
    {
        characterSprite->bodySprites[i].flip = flip;
    }
}

void AEC_CharacterSprite_Render(CHARACTER_SPRITE* character_sprite, DISPLACEMENT* displacement, AEC_Camera* camera, SDL_Renderer* renderer, float step)
{
    //Save the x and y to cut down on dereferences
    int x = (int)(displacement->x - camera->x);
    int y = (int)(displacement->y - camera->y);
    
    //The displacement of the leg on the body. It's 1 pixel, multiplied by the x_scale of the character
    int leg_displacement = 0;
    //If the character has its legs in, set the displacement
    if (character_sprite->leg_in)
    {
        if (displacement->reflection == SDL_FLIP_HORIZONTAL)
        {
            leg_displacement = -character_sprite->x_scale;
        }
        else
        {
            leg_displacement = character_sprite->x_scale;
        }
    }
    
    //If we're drawing the right leg, draw the right leg sprite
    if (character_sprite->draw_part[AEC_LEG_RIGHT] == SDL_TRUE)
    {
        AE_SpriteSetScale(&character_sprite->bodySprites[AEC_LEG_RIGHT], character_sprite->x_scale, character_sprite->y_scale, AE_SPRITE_KEEP_NONE);
        AE_SpriteRender(&character_sprite->bodySprites[AEC_LEG_RIGHT], renderer, x-(AEC_CHARACTER_WIDTH/2)*character_sprite->x_scale-leg_displacement, y-(AEC_CHARACTER_HEIGHT)*character_sprite->y_scale, 0, step);
    }
    //If we're drawing the left leg, draw the left leg sprite
    if (character_sprite->draw_part[AEC_LEG_LEFT] == SDL_TRUE)
    {
        AE_SpriteSetScale(&character_sprite->bodySprites[AEC_LEG_LEFT], character_sprite->x_scale, character_sprite->y_scale, AE_SPRITE_KEEP_NONE);
        AE_SpriteRender(&character_sprite->bodySprites[AEC_LEG_LEFT], renderer, x-(AEC_CHARACTER_WIDTH/2)*character_sprite->x_scale+leg_displacement, y-(AEC_CHARACTER_HEIGHT)*character_sprite->y_scale, 0, step);
    }
    //If we're drawing the torso, draw the torso sprite
    if (character_sprite->draw_part[AEC_TORSO])
    {
        AE_SpriteSetScale(&character_sprite->bodySprites[AEC_TORSO], character_sprite->x_scale, character_sprite->y_scale, AE_SPRITE_KEEP_NONE);
        AE_SpriteRender(&character_sprite->bodySprites[AEC_TORSO], renderer, x-(AEC_CHARACTER_WIDTH/2)*character_sprite->x_scale, y-(AEC_CHARACTER_HEIGHT)*character_sprite->y_scale, 0, step);
    }
    //If we're drawing the chest, draw the chest sprite
    if (character_sprite->draw_part[AEC_CHEST])
    {
        AE_SpriteSetScale(&character_sprite->bodySprites[AEC_CHEST], character_sprite->x_scale, character_sprite->y_scale, AE_SPRITE_KEEP_NONE);
        AE_SpriteRender(&character_sprite->bodySprites[AEC_CHEST], renderer, x-(AEC_CHARACTER_WIDTH/2)*character_sprite->x_scale, y-(AEC_CHARACTER_HEIGHT)*character_sprite->y_scale, character_sprite->gender, step);
    }
}

void AEC_CharacterSprite_MoveLegs(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, float step)
{
    if (entityCatalog->entity_components[entity_at].component_mask[AEC_CHARACTER_SPRITE] && entityCatalog->entity_components[entity_at].component_mask[AEC_VELOCITY])
    {
        //If the character is moving, move the legs
        if (entityCatalog->velocity[entity_at].moving)
        {
            //If the character just started moving, the legs begin inwards
            if (entityCatalog->velocity[entity_at].just_started_moving)
            {
                entityCatalog->character_sprite[entity_at].leg_in = SDL_TRUE;
                entityCatalog->velocity[entity_at].just_started_moving = SDL_FALSE;
                return;
            }
            //Add the current step to the leg clock
            entityCatalog->character_sprite[entity_at].leg_clock += step;
            //If it's time for the legs to change
            if (entityCatalog->character_sprite[entity_at].leg_clock >= entityCatalog->character_sprite[entity_at].leg_movement_time)
            {
                //Set the current clock to the modded clock time
                entityCatalog->character_sprite[entity_at].leg_clock = fmodf(entityCatalog->character_sprite[entity_at].leg_clock, entityCatalog->character_sprite[entity_at].leg_movement_time);
                //Reverse leg_in
                entityCatalog->character_sprite[entity_at].leg_in = (!entityCatalog->character_sprite[entity_at].leg_in);
            }
        }
        else
            //If the character isn't moving, reset the legs
        {
            entityCatalog->character_sprite[entity_at].leg_in = SDL_FALSE;
            entityCatalog->character_sprite[entity_at].leg_clock = 0;
        }
    }
}
