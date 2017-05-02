//
//  ae_components.c
//  arrental_engine
//
//  Created by Jared Rand on 2017-02-06.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#include "ae_components.h"
#include "arrental_engine.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

int AEC_CreateNewCharacter(AEC_EntityCatalog* entityCatalog, AE_LinkedTexture* characterSpriteSheet, AE_LinkedTexture* maskSpriteSheet)
{
    //The location of the entity in the array;
    int entity_at = 0;
    while (entityCatalog->entity_id[entity_at] != 0) {
        entity_at++;
    }
    if (entity_at < AEC_ENTITY_COUNT)
    {
        entityCatalog->entity_id[entity_at] = entity_at + 1;
        
        //Set all the necessary components to SDL_TRUE
        entityCatalog->entity_components[entity_at].component_mask[AEC_DISPLACEMENT] = SDL_TRUE;
        entityCatalog->entity_components[entity_at].component_mask[AEC_DRAWABLE] = SDL_TRUE;
        entityCatalog->entity_components[entity_at].component_mask[AEC_VELOCITY] = SDL_TRUE;
        entityCatalog->entity_components[entity_at].component_mask[AEC_MASK] = SDL_TRUE;
        entityCatalog->entity_components[entity_at].component_mask[AEC_CHARACTER_SPRITE] = SDL_TRUE;
        entityCatalog->entity_components[entity_at].component_mask[AEC_TRAIL] = SDL_TRUE;
        
        //Character is an NPC by default
        entityCatalog->entity_components[entity_at].component_mask[AEC_NPC_MOVEMENT_AI] = SDL_TRUE;
        
        AEC_CharacterSprite_CreateNew(entity_at + 1, entityCatalog, characterSpriteSheet);
        AEC_Mask_CreateNew(entity_at + 1, entityCatalog, maskSpriteSheet);
        
        //If the entity was created, return the id of that entity
        return entity_at + 1;
    }
    
    //If no space was found
    return 0;
}

SDL_bool AEC_Entity_SetPlayable(AEC_EntityCatalog* entityCatalog, int entity_id, SDL_bool isPlayable, int player_id)
{
    //Whether resetting the entity playability was successful or not
    SDL_bool success = SDL_FALSE;
    if (entity_id > 0 && entity_id < AEC_ENTITY_COUNT)
    {
        entityCatalog->entity_components[entity_id-1].component_mask[AEC_PLAYER_CONTROLLED] = isPlayable;
        entityCatalog->entity_components[entity_id-1].component_mask[AEC_NPC_MOVEMENT_AI] = !isPlayable;
        if (isPlayable)
        {
            entityCatalog->player_controlled[entity_id-1].player_id = player_id;
        }
        success = SDL_TRUE;
    }
    return success;
}

SDL_bool AEC_CharacterSprite_CreateNew(int entity_id, AEC_EntityCatalog* entityCatalog, AE_LinkedTexture* characterSpriteSheet)
{
    SDL_bool success = SDL_FALSE;
    for (int search = 0; search < AEC_ENTITY_COUNT; search++)
    {
        if (entityCatalog->entity_id[search] == entity_id)
        {
            //Set the components catalog to show that the entity has a charactersprite
            entityCatalog->entity_components[search].component_mask[AEC_CHARACTER_SPRITE] = SDL_TRUE;
            
            //Fill the list of character bodypart sprites
            
            AE_FillSprite(&entityCatalog->character_sprite[search].bodySprites[AEC_TORSO], characterSpriteSheet, 0, 0, 1, 32, 32, 32/2, 32/2);
            AE_FillSprite(&entityCatalog->character_sprite[search].bodySprites[AEC_CHEST], characterSpriteSheet, 0, 64, 2, 32, 32, 32/2, 32/2);
            AE_FillSprite(&entityCatalog->character_sprite[search].bodySprites[AEC_LEG_LEFT], characterSpriteSheet, 32, 0, 1, 32, 32, 32/2, 32/2);
            AE_FillSprite(&entityCatalog->character_sprite[search].bodySprites[AEC_LEG_RIGHT], characterSpriteSheet, 0, 32, 1, 32, 32, 32/2, 32/2);
            
            //Set the skin color to a random color
            AE_ColorBundle* skinColor = AEC_GetRandomSkinColor();
            AE_SpriteSetColor(&entityCatalog->character_sprite[search].bodySprites[AEC_TORSO], skinColor, AE_SPRITE_KEEP_NONE);
            AE_SpriteSetColor(&entityCatalog->character_sprite[search].bodySprites[AEC_CHEST], skinColor, AE_SPRITE_KEEP_NONE);
            AE_SpriteSetColor(&entityCatalog->character_sprite[search].bodySprites[AEC_LEG_LEFT], skinColor, AE_SPRITE_KEEP_NONE);
            AE_SpriteSetColor(&entityCatalog->character_sprite[search].bodySprites[AEC_LEG_RIGHT], skinColor, AE_SPRITE_KEEP_NONE);
            
            free(skinColor);
            
            entityCatalog->character_sprite[search].draw_part[AEC_LEG_RIGHT] = SDL_TRUE;
            entityCatalog->character_sprite[search].draw_part[AEC_LEG_LEFT] = SDL_TRUE;
            entityCatalog->character_sprite[search].draw_part[AEC_TORSO] = SDL_TRUE;
            entityCatalog->character_sprite[search].draw_part[AEC_CHEST] = SDL_TRUE;
            
            //Set random gender
            int_least8_t gender = (int_least8_t )AE_Random(0, 4);
            
            if (gender >= 3)
            {
                entityCatalog->character_sprite[search].gender = AEC_FEMALE;
            }
            else
            {
                entityCatalog->character_sprite[search].gender = AEC_MALE;
            }
            entityCatalog->character_sprite[search].x_scale = 1;
            entityCatalog->character_sprite[search].y_scale = 1;
            entityCatalog->velocity[search].max_vel = 50;
            entityCatalog->character_sprite[search].leg_movement_time = 0.15;
        }
    }
    return success;
}

SDL_bool AEC_Mask_CreateNew(int entity_id, AEC_EntityCatalog* entityCatalog, AE_LinkedTexture* maskSpriteSheet)
{
    SDL_bool success = SDL_FALSE;
    for (int search = 0; search < AEC_ENTITY_COUNT; search++)
    {
        if (entityCatalog->entity_id[search] == entity_id)
        {
            //Set the components catalog to show that the entity has a charactersprite
            entityCatalog->entity_components[search].component_mask[AEC_MASK] = SDL_TRUE;
            
            //Fill the list of character bodypart sprites
            
            AE_FillSprite(&entityCatalog->mask[search].sprite, maskSpriteSheet, 0, 0, 1, 32, 32, 32/2, 32/2);
            AE_SpriteSetAlpha(&entityCatalog->mask[search].sprite, 64);
        }
    }
    return success;
}

void AEC_CharacterSprite_SetFlip(CHARACTER_SPRITE* characterSprite, SDL_RendererFlip flip)
{
    
    //For all of the bodyparts in the character sprite (NO MAGIC NUMBERS!)
    for (int i = 0; i < sizeof(characterSprite->bodySprites)/sizeof(characterSprite->bodySprites[0]); i++)
    {
        characterSprite->bodySprites[i].flip = flip;
    }
}

void AEC_CharacterSprite_Render(CHARACTER_SPRITE* character_sprite, DISPLACEMENT* displacement, SDL_Renderer* renderer, float step)
{
    //Save the x and y to cut down on dereferences
    int x = displacement->x;
    int y = displacement->y;
    
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

void AEC_Mask_Render(MASK* mask, DISPLACEMENT* displacement, float x_scale, float y_scale, SDL_Renderer* renderer, float step)
{
    AE_SpriteRender(&mask->sprite, renderer, displacement->x-(AEC_CHARACTER_WIDTH/2)*x_scale, displacement->y-(AEC_CHARACTER_HEIGHT)*y_scale, 0, step);
}

void AEC_Entities_Render(AEC_EntityCatalog* entityCatalog, SDL_Renderer* renderer, float step)
{
    
    for (int search = 0; search < AEC_ENTITY_COUNT; search++)
    {
        if (entityCatalog->entity_id[search] > 0)
        {
            //If there is a character sprite and a displacement and it's drawable
            if (entityCatalog->entity_components[search].component_mask[AEC_DISPLACEMENT] && entityCatalog->entity_components[search].component_mask[AEC_DRAWABLE])
            {
                if (entityCatalog->entity_components[search].component_mask[AEC_MASK])
                {
                    AEC_Mask_Render(&entityCatalog->mask[search], &entityCatalog->displacement[search], 1, 1, renderer, step);
                }
                if (entityCatalog->entity_components[search].component_mask[AEC_CHARACTER_SPRITE])
                {
                    AEC_CharacterSprite_Render(&entityCatalog->character_sprite[search], &entityCatalog->displacement[search], renderer, step);
                }
            }
        }
    }
}

void AEC_RenderEntity(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, SDL_Renderer* renderer, float step)
{
    if (entityCatalog->entity_id[entity_at] > 0)
        {
            //If there is a character sprite and a displacement and it's drawable
        if (entityCatalog->entity_components[entity_at].component_mask[AEC_DISPLACEMENT] && entityCatalog->entity_components[entity_at].component_mask[AEC_DRAWABLE])
        {
            if (entityCatalog->entity_components[entity_at].component_mask[AEC_MASK])
            {
                AEC_Mask_Render(&entityCatalog->mask[entity_at], &entityCatalog->displacement[entity_at], 1, 1, renderer, step);
            }
            if (entityCatalog->entity_components[entity_at].component_mask[AEC_CHARACTER_SPRITE])
            {
                AEC_CharacterSprite_Render(&entityCatalog->character_sprite[entity_at], &entityCatalog->displacement[entity_at], renderer, step);
            }
        }
    }
}

void AEC_VelocityUpdateSimple(AEC_EntityCatalog* entityCatalog)
{
    SDL_bool moving = SDL_FALSE;
    int xVel = 0;
    int yVel = 0;
    for (int search = 0; search < AEC_ENTITY_COUNT; search++)
    {
        if (entityCatalog->entity_id[search] > 0)
        {
            if (entityCatalog->entity_components[search].component_mask[AEC_VELOCITY])
            {
                moving = SDL_FALSE;
                int max_xVel = entityCatalog->velocity[search].max_vel*AEC_CHARACTER_X_CONSTANT;
                int max_yVel = entityCatalog->velocity[search].max_vel*AEC_CHARACTER_Y_CONSTANT;
                if (entityCatalog->velocity[search].direction_on[AEC_KEY_UP])
                {
                    //Move isometrically
                    xVel = max_xVel;
                    yVel = -max_yVel;
                    moving = SDL_TRUE;
                }
                if (entityCatalog->velocity[search].direction_on[AEC_KEY_DOWN])
                {
                    //Move isometrically
                    xVel = -max_xVel;
                    yVel = max_yVel;
                    moving = SDL_TRUE;
                }
                if (entityCatalog->velocity[search].direction_on[AEC_KEY_LEFT])
                {
                    //Move isometrically
                    xVel = -max_xVel;
                    yVel = -max_yVel;
                    moving = SDL_TRUE;
                }
                if (entityCatalog->velocity[search].direction_on[AEC_KEY_RIGHT])
                {
                    //Move isometrically
                    xVel = max_xVel;
                    yVel = max_yVel;
                    moving = SDL_TRUE;
                }
                if (!moving)
                {
                    xVel = 0;
                    yVel = 0;
                }
                entityCatalog->velocity[search].moving = moving;
                entityCatalog->velocity[search].xVel = xVel;
                entityCatalog->velocity[search].yVel = yVel;
            }
        }
    }
}

void AEC_DisplacementUpdate_ByVelocity(AEC_EntityCatalog* entityCatalog, float step)
{
    for (int search = 0; search < AEC_ENTITY_COUNT; search++)
    {
        if (entityCatalog->entity_id[search] > 0)
        {
            if (entityCatalog->entity_components[search].component_mask[AEC_DISPLACEMENT] && entityCatalog->entity_components[search].component_mask[AEC_VELOCITY])
            {
                if (entityCatalog->velocity[search].moving)
                {
                    int current_x = entityCatalog->displacement[search].x;
                    int new_x = (entityCatalog->displacement[search].x += AE_FloatBase(entityCatalog->velocity[search].xVel * step));
                    entityCatalog->displacement[search].y += AE_FloatBase(entityCatalog->velocity[search].yVel * step);
                    if (current_x < new_x)
                    {
                        entityCatalog->displacement[search].reflection = SDL_FLIP_HORIZONTAL;
                        AEC_CharacterSprite_SetFlip(&entityCatalog->character_sprite[search], SDL_FLIP_HORIZONTAL);
                    }
                    else if (current_x > new_x)
                    {
                        entityCatalog->displacement[search].reflection = SDL_FLIP_NONE;
                        AEC_CharacterSprite_SetFlip(&entityCatalog->character_sprite[search], SDL_FLIP_NONE);
                    }
                }
                AEC_CharacterMoveLegs(entityCatalog, search, step);
            }
        }
    }
}

void AEC_PlayerControlled_GetInput(AEC_EntityCatalog* entityCatalog, SDL_Event event)
{
    for (int search = 0; search < AEC_ENTITY_COUNT; search++)
    {
        if (entityCatalog->entity_id[search] > 0)
        {
            if (entityCatalog->entity_components[search].component_mask[AEC_PLAYER_CONTROLLED] && entityCatalog->entity_components[search].component_mask[AEC_VELOCITY])
            {
                if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
                {
                    if (event.key.keysym.sym == entityCatalog->player_controlled[search].key_binds[AEC_KEY_UP])
                    {
                        entityCatalog->velocity[search].direction_on[AEC_KEY_UP] = SDL_TRUE;
                    }
                    if (event.key.keysym.sym == entityCatalog->player_controlled[search].key_binds[AEC_KEY_DOWN])
                    {
                        entityCatalog->velocity[search].direction_on[AEC_KEY_DOWN] = SDL_TRUE;
                    }
                    if (event.key.keysym.sym == entityCatalog->player_controlled[search].key_binds[AEC_KEY_LEFT])
                    {
                        entityCatalog->velocity[search].direction_on[AEC_KEY_LEFT] = SDL_TRUE;
                    }
                    if (event.key.keysym.sym == entityCatalog->player_controlled[search].key_binds[AEC_KEY_RIGHT])
                    {
                        entityCatalog->velocity[search].direction_on[AEC_KEY_RIGHT] = SDL_TRUE;
                    }
                }
                if (event.type == SDL_KEYUP && event.key.repeat == 0)
                {
                    if (event.key.keysym.sym == entityCatalog->player_controlled[search].key_binds[AEC_KEY_UP])
                    {
                        entityCatalog->velocity[search].direction_on[AEC_KEY_UP] = SDL_FALSE;
                    }
                    if (event.key.keysym.sym == entityCatalog->player_controlled[search].key_binds[AEC_KEY_DOWN])
                    {
                        entityCatalog->velocity[search].direction_on[AEC_KEY_DOWN] = SDL_FALSE;
                    }
                    if (event.key.keysym.sym == entityCatalog->player_controlled[search].key_binds[AEC_KEY_LEFT])
                    {
                        entityCatalog->velocity[search].direction_on[AEC_KEY_LEFT] = SDL_FALSE;
                    }
                    if (event.key.keysym.sym == entityCatalog->player_controlled[search].key_binds[AEC_KEY_RIGHT])
                    {
                        entityCatalog->velocity[search].direction_on[AEC_KEY_RIGHT] = SDL_FALSE;
                    }
                }
                else if (event.type == SDL_JOYAXISMOTION)
                {
                    if (event.jaxis.which == entityCatalog->player_controlled[search].joystick_id)
                    {
                        if (event.jaxis.axis == 0)
                        {
                            //If it's going left
                            if (event.jaxis.value < -DEAD_ZONE)
                            {
                                entityCatalog->velocity[search].direction_on[AEC_KEY_LEFT] = SDL_TRUE;
                                entityCatalog->velocity[search].direction_on[AEC_KEY_RIGHT] = SDL_FALSE;
                            }
                            //If it's going right
                            else if (event.jaxis.value > DEAD_ZONE)
                            {
                                entityCatalog->velocity[search].direction_on[AEC_KEY_RIGHT] = SDL_TRUE;
                                entityCatalog->velocity[search].direction_on[AEC_KEY_LEFT] = SDL_FALSE;
                            }
                            else
                            {
                                entityCatalog->velocity[search].direction_on[AEC_KEY_LEFT] = SDL_FALSE;
                                entityCatalog->velocity[search].direction_on[AEC_KEY_RIGHT] = SDL_FALSE;
                            }
                        }
                        if (event.jaxis.axis == 1)
                        {
                            //If it's going up
                            if (event.jaxis.value < -DEAD_ZONE)
                            {
                                entityCatalog->velocity[search].direction_on[AEC_KEY_UP] = SDL_TRUE;
                                entityCatalog->velocity[search].direction_on[AEC_KEY_DOWN] = SDL_FALSE;
                            }
                            //If it's going down
                            else if (event.jaxis.value > DEAD_ZONE)
                            {
                                entityCatalog->velocity[search].direction_on[AEC_KEY_DOWN] = SDL_TRUE;
                                entityCatalog->velocity[search].direction_on[AEC_KEY_UP] = SDL_FALSE;
                            }
                            else
                            {
                                entityCatalog->velocity[search].direction_on[AEC_KEY_UP] = SDL_FALSE;
                                entityCatalog->velocity[search].direction_on[AEC_KEY_DOWN] = SDL_FALSE;
                            }
                        }
                    }
                }
            }
        }
    }
}

void AEC_SetPlayerKeys(AEC_EntityCatalog* entityCatalog, int entity_id, SDL_Keycode* keys)
{
    for (int search = 0; search < AEC_ENTITY_COUNT; search++)
    {
        if (entityCatalog->entity_id[search] == entity_id)
        {
            if (entityCatalog->entity_components[search].component_mask[AEC_PLAYER_CONTROLLED])
            {
                for (int i = 0; i < 6; i++)
                {
                    entityCatalog->player_controlled[search].key_binds[i] = keys[i];
                }
            }
        }
    }
}

int AEC_GetIsoDepth(AEC_EntityCatalog* entityCatalog, unsigned int entity_at)
{
    if (entityCatalog->entity_components[entity_at].component_mask[AEC_DISPLACEMENT])
    {
        return entityCatalog->displacement[entity_at].x + entityCatalog->displacement[entity_at].y + entityCatalog->displacement[entity_at].z;
    }
    return 0;
    //return entityCatalog->displacement[entity_at].y;
}

void AEC_RenderCatalogToBuffer(AEC_EntityCatalog* entityCatalog, AEC_SpriteBuffer* spriteBuffer)
{
    unsigned int heap_size = 0;
    unsigned int heap_at = 1;
    int frame = spriteBuffer->frame + 1;
    int x, y, z;
    //unsigned int i, parent;
    int temp_depth;
    for (int search = 0; search < AEC_ENTITY_COUNT; search++)
    {
        if (entityCatalog->entity_components[search].component_mask[AEC_DRAWABLE] && entityCatalog->entity_components[search].component_mask[AEC_DISPLACEMENT])
        {
            //Prepare data for heap insertion
            temp_depth = AEC_GetIsoDepth(entityCatalog, search);
            x = entityCatalog->displacement[search].x;
            y = entityCatalog->displacement[search].y;
            z = entityCatalog->displacement[search].z;
            
            //ORIGINAL CODE
            heap_size++;
            heap_at = heap_size;
            spriteBuffer->is_filled[heap_at] = frame;
            
            //PART OF HEAP INSERT
            //spriteBuffer->is_filled[heap_at+1] = frame;
            
            //While the parent is greater than the child and the parent is intended to be drawn, swap the parent and child data
            //while (spriteBuffer->depth[heap_at / 2] > temp_depth && spriteBuffer->is_filled[heap_at / 2] == frame)
            //while (spriteBuffer->y[heap_at / 2] > y && spriteBuffer->x[heap_at / 2] > x && spriteBuffer->z[heap_at / 2] > z && spriteBuffer->is_filled[heap_at / 2])
            
            //ORIGINAL CODE
            while (heap_at > 0 && spriteBuffer->y[heap_at-1] >= y && spriteBuffer->is_filled[heap_at-1] == frame)
            {
                spriteBuffer->entity[heap_at] = spriteBuffer->entity[heap_at-1];
                spriteBuffer->depth[heap_at] = spriteBuffer->depth[heap_at-1];
                spriteBuffer->x[heap_at] = spriteBuffer->x[heap_at-1];
                spriteBuffer->y[heap_at] = spriteBuffer->y[heap_at-1];
                spriteBuffer->z[heap_at] = spriteBuffer->z[heap_at-1];
                
                heap_at = heap_at-1;
            }
            
            //ORIGINAL CODE
            
            spriteBuffer->is_filled[heap_at] = frame;
            spriteBuffer->x[heap_at] = x;
            spriteBuffer->y[heap_at] = y;
            spriteBuffer->z[heap_at]= z;
            spriteBuffer->entity[heap_at] = search;
            spriteBuffer->depth[heap_at] = temp_depth;
        }
    }
    spriteBuffer->size = heap_size;
    spriteBuffer->frame = frame;
    /**printf("Checking: ");
    for (int q=0;q<heap_size+1;q++)
    {
        if (spriteBuffer->is_filled[q] == frame)
        {
            printf("%d ", spriteBuffer->y[q]);
        }
    }
    printf("\n");*/
}

void AEC_RenderSpriteBuffer(AEC_SpriteBuffer* spriteBuffer, AEC_EntityCatalog* entityCatalog, SDL_Renderer* renderer, float step)
{
    int frame = spriteBuffer->frame;
    //for (int i = AEC_ENTITY_COUNT; i > 0; i--)
    for (int i = 0; i < AEC_ENTITY_COUNT + 1; i++)
    {
        if (spriteBuffer->is_filled[i] == frame)
        {
            AEC_RenderEntity(entityCatalog, spriteBuffer->entity[i], renderer, step);
        }
    }
}

void AEC_FlushSpriteBuffer(AEC_SpriteBuffer* spriteBuffer)
{
    for (int i = 0; i < AEC_ENTITY_COUNT; i++)
    {
        spriteBuffer->is_filled[i] = SDL_FALSE;
    }
}

AEC_SpriteBuffer* AEC_Create_SpriteBuffer()
{
    AEC_SpriteBuffer* output = malloc(sizeof(AEC_SpriteBuffer));
    output->size = 0;
    output->frame = 0;
    for (int i = 0; i < AEC_ENTITY_COUNT; i++)
    {
        output->depth[i] = 0;
        output->entity[i] = 0;
        output->is_filled[i] = SDL_FALSE;
    }
    return output;
}

AE_ColorBundle* AEC_GetRandomSkinColor()
{
    int_least8_t darken = (int_least8_t )AE_Random(0, 4);
    AE_ColorBundle* output = malloc(sizeof(AE_ColorBundle));
    Uint8 r = (Uint8)AE_Random(231, 255);
    Uint8 g = (Uint8)AE_Random(164, 216);
    Uint8 b = (Uint8)AE_Random(102, 165);
    Uint8 tone;
    if (darken == 3)
    {
        tone = (Uint8 )AE_Random(0, 60);
        output->r = AE_BlendColorChannel(r, 1, tone);
        output->g = AE_BlendColorChannel(g, 1, tone);
        output->b = AE_BlendColorChannel(b, 1, tone);
    }
    else
    {
        tone = (Uint8 )AE_Random(0, 15);
        output->r = AE_BlendColorChannel(r, 0x00, tone);
        output->g = AE_BlendColorChannel(g, 0x00, tone);
        output->b = AE_BlendColorChannel(b, 0x00, tone);
    }
    return output;
}

void AEC_CharacterMoveLegs(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, float step)
{
    if (entityCatalog->entity_components[entity_at].component_mask[AEC_CHARACTER_SPRITE] && entityCatalog->entity_components[entity_at].component_mask[AEC_VELOCITY])
    {
        if (entityCatalog->velocity[entity_at].moving)
        {
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
        {
            entityCatalog->character_sprite[entity_at].leg_in = SDL_FALSE;
            entityCatalog->character_sprite[entity_at].leg_clock = 0;
        }
    }
}
