//
//  main.c
//  arrental_engine
//
//  Created by Jared Rand on 2017-01-12.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#include "arrental_engine.h"
#include "ae_components.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const unsigned int MAX_SIZE = 254;
const int JOYSTICK_DEAD_ZONE = 8000;

char* TORSO_IMG = "/Users/JJ/Documents/arrental_engine/arrental_engine/Images/base_torso.png";
char* RLEG_IMG = "/Users/JJ/Documents/arrental_engine/arrental_engine/Images/base_right_leg.png";
char* LLEG_IMG = "/Users/JJ/Documents/arrental_engine/arrental_engine/Images/base_left_leg.png";
char* CHEST_IMG = "/Users/JJ/Documents/arrental_engine/arrental_engine/Images/base_chest_male.png";
char* ANIM_IMG = "/Users/JJ/Documents/arrental_engine/arrental_engine/Images/WulffAnimated.png";
char* CHAR_SHEET = "/Users/JJ/Documents/arrental_engine/arrental_engine/Images/character_spritesheet.png";
char* CHAR_MASK = "/Users/JJ/Documents/arrental_engine/arrental_engine/Images/character_mask.png";
char* GRASS = "/Users/JJ/Documents/arrental_engine/arrental_engine/Images/basic_grass.png";
char* LAND_OR_WATER = "/Users/JJ/Documents/arrental_engine/arrental_engine/Images/land_and_water.png";

//
//
//GRASS TILER
//
//

typedef struct
{
    AE_Sprite* sprite;
    Uint8 grass_img[SCREEN_WIDTH+32][SCREEN_HEIGHT+16];
} grass_tiler;

grass_tiler* grasstiler_create(AE_LinkedTexture* texture, Uint64 seed, Uint8 set)
{
    grass_tiler* output = malloc(sizeof(grass_tiler));
    
    output->sprite = AE_CreateSprite(texture, 0, 0, 20, 32, 16, 0, 0);
    
    //Set images to random grass
    for (int i = 0; i < SCREEN_WIDTH; i += 32)
    {
        for (int j = 0; j < SCREEN_HEIGHT; j += 16)
        {
            //output->grass_img[i][j] = AE_Random(0, 20);
            output->grass_img[i][j] = AE_PseudoRandomFromSeed_Int(seed, i, j, set, 0, 20);
        }
    }
    for (int i = -16; i < SCREEN_WIDTH; i += 32)
    {
        for (int j = -8; j < SCREEN_HEIGHT; j += 16)
        {
            //output->grass_img[i+16][j+8] = AE_Random(0, 20);
            output->grass_img[i+16][j+8] = AE_PseudoRandomFromSeed_Int(seed, i, j, set, 0, 20);
        }
    }
    return output;
}

void grasstiler_retile(grass_tiler* tiler, Uint64 seed, Uint8 set)
{
    //Set images to random grass
    for (int i = 0; i < SCREEN_WIDTH; i += 32)
    {
        for (int j = 0; j < SCREEN_HEIGHT; j += 16)
        {
            //tiler->grass_img[i][j] = AE_Random(0, 20);
            tiler->grass_img[i][j] = AE_PseudoRandomFromSeed_Int(seed, i, j, set, 0, 20);
        }
    }
    for (int i = -16; i < SCREEN_WIDTH; i += 32)
    {
        for (int j = -8; j < SCREEN_HEIGHT; j += 16)
        {
            //tiler->grass_img[i+16][j+8] = AE_Random(0, 20);
            tiler->grass_img[i+16][j+8] = AE_PseudoRandomFromSeed_Int(seed, i, j, set, 0, 20);
        }
    }
}

void grasstiler_render(grass_tiler* tiler, SDL_Renderer* renderer, float step)
{
    AE_Sprite* grass_sprite = tiler->sprite;
    for (int i = 0; i < SCREEN_WIDTH; i += 32)
    {
        for (int j = 0; j < SCREEN_HEIGHT; j += 16)
        {
            AE_SpriteRender(grass_sprite, renderer, i, j, tiler->grass_img[i][j], step);
        }
    }
    for (int i = -16; i < SCREEN_WIDTH; i += 32)
    {
        for (int j = -8; j < SCREEN_HEIGHT; j += 16)
        {
            AE_SpriteRender(grass_sprite, renderer, i, j, tiler->grass_img[i+16][j+8], step);
        }
    }
}

//
//
//WORLD TILER
//
//

typedef struct
{
    AE_Sprite* sprite;
    Uint8 world_img[SCREEN_WIDTH+5][SCREEN_HEIGHT+5];
} world_tiler;

world_tiler* worldtiler_create(AE_LinkedTexture* texture, Uint64 seed, Uint8 set)
{
    Uint8 temp = 0;
    world_tiler* output = malloc(sizeof(world_tiler));
    
    output->sprite = AE_CreateSprite(texture, 0, 0, 2, 5, 5, 0, 0);
    
    //Set images to random grass
    for (int i = 0; i < SCREEN_WIDTH; i += 5)
    {
        for (int j = 0; j < SCREEN_HEIGHT; j += 5)
        {
            output->world_img[i][j] = 0;
            //temp = AE_Random(0, 100);
            temp = AE_PseudoRandomFromSeed_Int(seed, i, j, set, 0, 100);
            if (temp > 60)
            {
                output->world_img[i][j] = 1;
            }
        }
    }
    return output;
}

void worldtiler_retile(world_tiler* tiler, Uint64 seed, Uint8 set)
{
    Uint8 temp = 0;
    //Set images to random grass
    for (int i = 0; i < SCREEN_WIDTH; i += 5)
    {
        for (int j = 0; j < SCREEN_HEIGHT; j += 5)
        {
            tiler->world_img[i][j] = 0;
            //temp = AE_Random(0, 100);
            temp = AE_PseudoRandomFromSeed_Int(seed, i, j, set, 0, 100);
            if (temp > 60)
            {
                tiler->world_img[i][j] = 1;
            }
        }
    }
}

void worldtiler_render(world_tiler* tiler, SDL_Renderer* renderer, float step)
{
    AE_Sprite* world_sprite = tiler->sprite;
    for (int i = 0; i < SCREEN_WIDTH; i += 5)
    {
        for (int j = 0; j < SCREEN_HEIGHT; j += 5)
        {
            AE_SpriteRender(world_sprite, renderer, i, j, tiler->world_img[i][j], step);
        }
    }
}

//
//
//INITIALIZE JOYSTICK
//
//


void initJoystick(SDL_Joystick* joystick)
{
    joystick = SDL_JoystickOpen(0);
    if (joystick == NULL)
    {
        printf("Unable to open joystick\n");
    }
}

//
//
//MAIN LOOP
//
//

int main(int argc, const char* argv[])
{
    
    AE_WindowBundle* windowBundle = AE_Initialize("Arrental Engine Test", SCREEN_WIDTH, SCREEN_HEIGHT, true);
    
    if (!windowBundle->initSuccess)
    {
        printf("Engine could not be intitialized.\n");
    }
    else
    {
        bool quit = false;
        
        SDL_Event e;
        
        Uint64 seed = AE_RandomSeed();
        Uint8 grass_set = 0;
        
        //Testing AEComponents
        SDL_Texture* spriteSheetTexture = AE_LoadTextureFromFile(windowBundle->renderer, CHAR_SHEET);
        SDL_Texture* maskTexture = AE_LoadTextureFromFile(windowBundle->renderer, CHAR_MASK);
        SDL_Texture* grassTexture = AE_LoadTextureFromFile(windowBundle->renderer, GRASS);
        SDL_Texture* lowTexture = AE_LoadTextureFromFile(windowBundle->renderer, LAND_OR_WATER);
        
        AE_LinkedTexture* spriteSheet = AE_CreateLinkedTexture(spriteSheetTexture);
        AE_LinkedTexture* char_mask = AE_CreateLinkedTexture(maskTexture);
        AE_LinkedTexture* grassLinked = AE_CreateLinkedTexture(grassTexture);
        AE_LinkedTexture* land_water = AE_CreateLinkedTexture(lowTexture);
        
        grass_tiler* tiler = grasstiler_create(grassLinked, seed, grass_set);
        world_tiler* world_tiler = worldtiler_create(land_water, seed, grass_set);
        
        AEC_EntityCatalog* entityCatalog = malloc(sizeof(AEC_EntityCatalog));
        AEC_SpriteBuffer* spriteBuffer = AEC_Create_SpriteBuffer();
        
        for (int i = 0; i < 10; i++)
        {
            AEC_CreateNewCharacter(entityCatalog, spriteSheet, char_mask);
            entityCatalog->displacement[i].x = AE_Random(32, SCREEN_WIDTH-32);
            entityCatalog->displacement[i].y = AE_Random(32, SCREEN_HEIGHT-32);
        }
        AEC_Entity_SetPlayable(entityCatalog, 1, true, 0);
        SDL_Keycode keys[6] = {SDLK_w, SDLK_s, SDLK_a, SDLK_d, SDLK_f, SDLK_SPACE};
        AEC_SetPlayerKeys(entityCatalog, 1, keys);
        
        AEC_Entity_SetPlayable(entityCatalog, 2, true, 1);
        SDL_Keycode keys_dual[6] = {SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT, SDLK_f, SDLK_SPACE};
        AEC_SetPlayerKeys(entityCatalog, 2, keys_dual);
        
        if (SDL_NumJoysticks() > 0)
        {
            initJoystick(entityCatalog->player_controlled[1].joystick);
            entityCatalog->player_controlled[1].joystick_id = SDL_JoystickInstanceID(entityCatalog->player_controlled[1].joystick);
        }
        
        
        
        AE_Timer* stepTimer = AE_Create_Timer();
        
        while (!quit)
        {
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
                const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
                if (currentKeyStates[SDL_SCANCODE_Q])
                {
                    for (int i = 0; i < 100; i++)
                    {
                        entityCatalog->displacement[i].x = AE_Random(32, SCREEN_WIDTH-32);
                        entityCatalog->displacement[i].y = AE_Random(32, SCREEN_HEIGHT-32);
                    }
                    //seed = AE_RandomSeed();
                    grass_set++;
                    grasstiler_retile(tiler, seed, grass_set);
                    worldtiler_retile(world_tiler, seed, grass_set);
                }
                if (currentKeyStates[SDL_SCANCODE_E])
                {
                    for (int i = 0; i < 100; i++)
                    {
                        entityCatalog->displacement[i].x = AE_Random(32, SCREEN_WIDTH-32);
                        entityCatalog->displacement[i].y = AE_Random(32, SCREEN_HEIGHT-32);
                    }
                    //seed = AE_RandomSeed();
                    grass_set--;
                    grasstiler_retile(tiler, seed, grass_set);
                    worldtiler_retile(world_tiler, seed, grass_set);
                }
                AEC_PlayerControlled_GetInput(entityCatalog, e);
                AEC_VelocityUpdateSimple(entityCatalog);
            }
            
            float time = AE_Timer_GetTime(stepTimer) / 1000.f;
            
            //Clear screen
            SDL_SetRenderDrawColor(windowBundle->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(windowBundle->renderer);
            
            grasstiler_render(tiler, windowBundle->renderer, time);
            //worldtiler_render(world_tiler, windowBundle->renderer, time);
            
            AEC_DisplacementUpdate_ByVelocity(entityCatalog, time);
            
            AEC_RenderCatalogToBuffer(entityCatalog, spriteBuffer);
            AEC_RenderSpriteBuffer(spriteBuffer, entityCatalog, windowBundle->renderer, time);
            //AEC_Entities_Render(entityCatalog, windowBundle->renderer, time);
            
            AE_Timer_Start(stepTimer);
            
            SDL_RenderPresent(windowBundle->renderer);
            
            AEC_FlushSpriteBuffer(spriteBuffer);
        }
        AE_DestroyLinkedTexture_Unsafe(spriteSheet);
    }
    
    AE_Close(windowBundle);
    
    return 0;
}
