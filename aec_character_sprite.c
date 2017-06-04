//
//  aec_character_sprite.c
//  arrental_engine
//
//  Created by Jared Rand on 2017-05-07.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#include "aec_character_sprite.h"

SDL_bool AEC_CharacterSprite_CreateNew(AEC_EntityCatalog* entityCatalog, int entity_id, AE_LinkedTexture* characterSpriteSheet, AE_LinkedTexture* faceSpriteSheet, unsigned int numOfFaces)
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
        AE_FillSprite(&entityCatalog->character_sprite[entity_id - 1].bodySprites[AEC_FACE], faceSpriteSheet, 0, 0, numOfFaces, 32, 32, 32/2, 32/2);
        
        //Set the skin color to a random color
        AE_ColorBundle* skinColor = AEC_GetRandomSkinColor();
        AE_SpriteSetColor(&entityCatalog->character_sprite[entity_id - 1].bodySprites[AEC_TORSO], skinColor, AE_SPRITE_KEEP_NONE);
        AE_SpriteSetColor(&entityCatalog->character_sprite[entity_id - 1].bodySprites[AEC_CHEST], skinColor, AE_SPRITE_KEEP_NONE);
        AE_SpriteSetColor(&entityCatalog->character_sprite[entity_id - 1].bodySprites[AEC_LEG_LEFT], skinColor, AE_SPRITE_KEEP_NONE);
        AE_SpriteSetColor(&entityCatalog->character_sprite[entity_id - 1].bodySprites[AEC_LEG_RIGHT], skinColor, AE_SPRITE_KEEP_NONE);
        AE_SpriteSetColor(&entityCatalog->character_sprite[entity_id - 1].bodySprites[AEC_FACE], skinColor, AE_SPRITE_KEEP_NONE);
        
        free(skinColor);
        
        entityCatalog->character_sprite[entity_id - 1].draw_part[AEC_LEG_RIGHT] = SDL_TRUE;
        entityCatalog->character_sprite[entity_id - 1].draw_part[AEC_LEG_LEFT] = SDL_TRUE;
        entityCatalog->character_sprite[entity_id - 1].draw_part[AEC_TORSO] = SDL_TRUE;
        entityCatalog->character_sprite[entity_id - 1].draw_part[AEC_CHEST] = SDL_TRUE;
        entityCatalog->character_sprite[entity_id - 1].draw_part[AEC_FACE] = SDL_TRUE;
        
        //Set random gender
        int_least8_t gender = (int_least8_t )AE_Random(0, 4);
        int face_min, face_max;
        
        if (gender >= 3)
        {
            entityCatalog->character_sprite[entity_id - 1].gender = AEC_FEMALE;
            face_min = 12;
            face_max = -3;
        }
        else
        {
            entityCatalog->character_sprite[entity_id - 1].gender = AEC_MALE;
            face_min = 0;
            face_max = -9;
        }
        
        entityCatalog->character_sprite[entity_id - 1].face = AE_Random(face_min, numOfFaces + face_max);
        
        entityCatalog->character_sprite[entity_id - 1].x_scale = 1;
        entityCatalog->character_sprite[entity_id - 1].y_scale = 1;
        entityCatalog->character_sprite[entity_id - 1].leg_movement_time = 0.15;
    }
    return SDL_FALSE;
}

void AEC_CharacterSprite_SetFlip(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, SDL_RendererFlip flip)
{
    
    //For all of the bodyparts in the character sprite (NO MAGIC NUMBERS!)
    for (int i = 0; i < sizeof(entityCatalog->character_sprite[entity_at].bodySprites)/sizeof(AE_Sprite); i++)
    {
        entityCatalog->character_sprite[entity_at].bodySprites[i].flip = flip;
    }
}

void AEC_CharacterSprite_Render(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, AEC_Camera* camera, SDL_Renderer* renderer, float step)
{
    if (entityCatalog->entity_components[entity_at].component_mask[AEC_DISPLACEMENT] && entityCatalog->entity_components[entity_at].component_mask[AEC_CHARACTER_SPRITE])
    {
        CHARACTER_SPRITE* character_sprite = &entityCatalog->character_sprite[entity_at];
        DISPLACEMENT* displacement = &entityCatalog->displacement[entity_at];
        
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
        //If we're drawing the chest, draw the chest sprite
        if (character_sprite->draw_part[AEC_FACE])
        {
            AE_SpriteSetScale(&character_sprite->bodySprites[AEC_CHEST], character_sprite->x_scale, character_sprite->y_scale, AE_SPRITE_KEEP_NONE);
            AE_SpriteRender(&character_sprite->bodySprites[AEC_FACE], renderer, x - (AEC_CHARACTER_WIDTH/2) * character_sprite->x_scale + AE_FloatBase(AEC_CharacterSprite_Look_X(entityCatalog, entity_at) * character_sprite->x_scale), y - ((AEC_CHARACTER_HEIGHT) * character_sprite->y_scale) + AE_FloatBase(AEC_CharacterSprite_Look_X(entityCatalog, entity_at) * character_sprite->y_scale), character_sprite->face, step);
        }
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

void AEC_CharacterSprite_SetTarget(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, unsigned int target_entity_id)
{
    if (entityCatalog->entity_components[entity_at].component_mask[AEC_CHARACTER_SPRITE])
    {
        if (entityCatalog->entity_components[entity_at].component_mask[AEC_DISPLACEMENT])
        {
            if (AEC_Entity_Exists(entityCatalog, target_entity_id) && entityCatalog->entity_components[target_entity_id].component_mask[AEC_DISPLACEMENT])
            {
                entityCatalog->character_sprite[entity_at].target_entity_id = target_entity_id;
            }
        }
        else
        {
            entityCatalog->character_sprite[entity_at].target_entity_id = 0;
        }
    }
}

float AEC_CharacterSprite_Look_X(AEC_EntityCatalog* entityCatalog, unsigned int entity_at)
{
    /*float output = 0;
    //If the called entity has a character sprite and displacement
    if (entityCatalog->entity_components[entity_at].component_mask[AEC_CHARACTER_SPRITE] && entityCatalog->entity_components[entity_at].component_mask[AEC_DISPLACEMENT])
    {
        //Save the target entity id
        unsigned int target_entity_id = entityCatalog->character_sprite[entity_at].target_entity_id;
        
        //If the target entity exists and has a displacement
        if (AEC_Entity_Exists(entityCatalog, target_entity_id) && entityCatalog->entity_components[target_entity_id].component_mask[AEC_DISPLACEMENT])
        {
            
            //Calculate the length of the line between the entity and its target
            float radius = (float)(AE_PointDistance_D(entityCatalog->displacement[entity_at].x, entityCatalog->displacement[entity_at].y, entityCatalog->displacement[target_entity_id].x, entityCatalog->displacement[target_entity_id].y) / AEC_CHARSPRITE_FACE_RADIUS_SHORTENER);
            
            //Calculate the angle of the entity to its target
            float angle = (float)atan2((double)((entityCatalog->displacement[entity_at].y - entityCatalog->displacement[target_entity_id].y) / 30), (double)((entityCatalog->displacement[entity_at].x - entityCatalog->displacement[target_entity_id].x) / 30));
            
            //If the result is within the face radius
            if (radius <= AEC_CHARSPRITE_FACE_RADIUS_MAX && radius >= AEC_CHARSPRITE_FACE_RADIUS_MAX * -1)
            {
                output = ((entityCatalog->displacement[entity_at].x - entityCatalog->displacement[target_entity_id].x) / 30);
            }
            //Else return the face at max distance
            else
            {
                output = (AE_Lengthdir_X(AEC_CHARSPRITE_FACE_RADIUS_MAX, angle));
            }
        }
    }
    return output;*/
    
    float output = 0;
    //If the called entity has a character sprite and displacement
    if (entityCatalog->entity_components[entity_at].component_mask[AEC_CHARACTER_SPRITE] && entityCatalog->entity_components[entity_at].component_mask[AEC_DISPLACEMENT])
    {
        //Save the target entity id
        unsigned int target_entity_id = entityCatalog->character_sprite[entity_at].target_entity_id;
        
        //If the target entity exists and has a displacement
        if (AEC_Entity_Exists(entityCatalog, target_entity_id) && entityCatalog->entity_components[target_entity_id].component_mask[AEC_DISPLACEMENT])
        {
            
            //Calculate the length of the line between the entity and its target
            float radius = (float)((entityCatalog->displacement[entity_at].x - entityCatalog->displacement[target_entity_id].x) / AEC_CHARSPRITE_FACE_RADIUS_SHORTENER);
            
            //If the result is within the face radius
            if (radius <= AEC_CHARSPRITE_FACE_X_MAX)
            {
                output = radius;
            }
            //Else return the face at max distance
            else
            {
                output = AEC_CHARSPRITE_FACE_X_MAX * ((radius < 0) ? -1 : 1);
            }
        }
    }
    return output;
}

float AEC_CharacterSprite_Look_Y(AEC_EntityCatalog* entityCatalog, unsigned int entity_at)
{
    /*float output = 0;
    //If the called entity has a character sprite and displacement
    if (entityCatalog->entity_components[entity_at].component_mask[AEC_CHARACTER_SPRITE] && entityCatalog->entity_components[entity_at].component_mask[AEC_DISPLACEMENT])
    {
        //Save the target entity id
        unsigned int target_entity_id = entityCatalog->character_sprite[entity_at].target_entity_id;
        
        //If the target entity exists and has a displacement
        if (AEC_Entity_Exists(entityCatalog, target_entity_id) && entityCatalog->entity_components[target_entity_id].component_mask[AEC_DISPLACEMENT])
        {
            
            //Calculate the length of the line between the entity and its target
            float radius = (float)(AE_PointDistance_D(entityCatalog->displacement[entity_at].x, entityCatalog->displacement[entity_at].y, entityCatalog->displacement[target_entity_id].x, entityCatalog->displacement[target_entity_id].y) / AEC_CHARSPRITE_FACE_RADIUS_SHORTENER);
            
            //Calculate the angle of the entity to its target
            float angle = (float)atan2((double)((entityCatalog->displacement[entity_at].y - entityCatalog->displacement[target_entity_id].y) / 30), (double)((entityCatalog->displacement[entity_at].x - entityCatalog->displacement[target_entity_id].x) / 30));
            
            //If the result is within the face radius
            if (radius <= AEC_CHARSPRITE_FACE_RADIUS_MAX && radius >= AEC_CHARSPRITE_FACE_RADIUS_MAX * -1)
            {
                output = ((entityCatalog->displacement[entity_at].y - entityCatalog->displacement[target_entity_id].y) / 30);
            }
            //Else return the face at max distance
            else
            {
                output = (AE_Lengthdir_Y(AEC_CHARSPRITE_FACE_RADIUS_MAX, angle));
            }
        }
    }
    return output;*/
    
    float output = 0;
    //If the called entity has a character sprite and displacement
    if (entityCatalog->entity_components[entity_at].component_mask[AEC_CHARACTER_SPRITE] && entityCatalog->entity_components[entity_at].component_mask[AEC_DISPLACEMENT])
    {
        //Save the target entity id
        unsigned int target_entity_id = entityCatalog->character_sprite[entity_at].target_entity_id;
        
        //If the target entity exists and has a displacement
        if (AEC_Entity_Exists(entityCatalog, target_entity_id) && entityCatalog->entity_components[target_entity_id].component_mask[AEC_DISPLACEMENT])
        {
            
            //Calculate the length of the line between the entity and its target
            float radius = (float)((entityCatalog->displacement[entity_at].y - entityCatalog->displacement[target_entity_id].y) / AEC_CHARSPRITE_FACE_RADIUS_SHORTENER);
            
            //If the result is within the face radius
            if (radius <= AEC_CHARSPRITE_FACE_Y_MAX)
            {
                output = radius;
            }
            //Else return the face at max distance
            else
            {
                output = AEC_CHARSPRITE_FACE_Y_MAX * ((radius < 0) ? -1 : 1);
            }
        }
    }
    return output;
}
