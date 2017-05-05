//
//  ae_components.h
//  arrental_engine
//
//  Created by Jared Rand on 2017-02-06.
//  Copyright © 2017 zapix_games. All rights reserved.
//

#ifndef ae_components_h
#define ae_components_h

#include "arrental_engine.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

//
//STRUCTS FOR GAMEPLAY
//

typedef struct {
    int x;
    int y;
} AEC_TrailPoint;

typedef struct {
    Uint64 x;
    Uint64 y;
    Uint64 w;
    Uint64 h;
} AEC_Camera;

//
//STRUCTS FOR GAMEPLAY
//

//
//ESSENTIAL VARIABLE: THE NUMBER OF AVAILIBLE COMPONENTS AND ENTITIES
//

static const unsigned int AEC_COMPONENT_COUNT = 8;
static const unsigned int AEC_ENTITY_COUNT = 1000;
static const unsigned int AEC_ENTITY_SPRITE_ALLOWANCE = 100;

typedef enum {
    AEC_DISPLACEMENT,
    AEC_DRAWABLE,
    AEC_VELOCITY,
    AEC_MASK,
    AEC_CHARACTER_SPRITE,
    AEC_TRAIL,
    AEC_PLAYER_CONTROLLED,
    AEC_NPC_MOVEMENT_AI
} AEC_Component;

typedef enum {
    AEC_TORSO,
    AEC_CHEST,
    AEC_LEG_LEFT,
    AEC_LEG_RIGHT
} AEC_CharacterSpriteParts;

typedef enum {
    AEC_MALE,
    AEC_FEMALE
} AEC_CharacterGender;

typedef enum {
    AEC_KEY_UP,
    AEC_KEY_DOWN,
    AEC_KEY_LEFT,
    AEC_KEY_RIGHT,
    AEC_KEY_INTERACT,
    AEC_KEY_ATTACK
} AEC_DirectionKeys;

//
//ESSENTIAL VARIABLE: THE NUMBER OF AVAILIBLE COMPONENTS AND ENTITIES
//

typedef struct {
    SDL_bool component_mask[AEC_COMPONENT_COUNT];
} COMPONENTS;

typedef struct {
    //These reference the world x and world y
    Uint64 x;
    Uint64 y;
    int z;
    SDL_RendererFlip reflection;
} DISPLACEMENT;

typedef struct {
    unsigned int width;
    unsigned int height;
} DRAWABLE;

typedef struct {
    SDL_bool direction_on[4];
    SDL_bool just_started_moving;
    SDL_bool moving;
    int max_vel;
    int xVel;
    int yVel;
} VELOCITY;

typedef struct {
    AE_Sprite sprite;
} MASK;

typedef struct {
    AE_Sprite bodySprites[4];
    SDL_bool draw_part[4];
    int distance_from_base;
    int_least8_t gender;
    SDL_bool leg_in;
    float leg_movement_time;
    float leg_clock;
    float x_scale;
    float y_scale;
} CHARACTER_SPRITE;

typedef struct {
    AEC_TrailPoint BUFFER[1000];
} TRAIL;

typedef struct {
    int player_id;
    SDL_Joystick* joystick;
    Uint8 joystick_id;
    SDL_GameController* controller;
    SDL_Keycode key_binds[6];
} PLAYER_CONTROLLED;

typedef struct {
    int hunger;
    int thirst;
    int work;
    int energy;
    int entity_to_follow;
} NPC_MOVEMENT_AI;

//
//THE STRUCT FOR DRAWING ALL SPRITES
//

typedef struct
{
    unsigned int size;
    int frame;
    int is_filled[AEC_ENTITY_COUNT + 1];
    Uint64 depth[AEC_ENTITY_COUNT + 1];
    Uint64 x[AEC_ENTITY_COUNT + 1];
    Uint64 y[AEC_ENTITY_COUNT + 1];
    Uint64 z[AEC_ENTITY_COUNT + 1];
    int entity[AEC_ENTITY_COUNT + 1];
} AEC_SpriteBuffer;

//
//THE STRUCT CONTAINING ALL COMPONENTS
//

typedef struct {
    int entity_id[AEC_ENTITY_COUNT];
    COMPONENTS entity_components[AEC_ENTITY_COUNT];
    DISPLACEMENT displacement[AEC_ENTITY_COUNT];
    DRAWABLE drawable[AEC_ENTITY_COUNT];
    VELOCITY velocity[AEC_ENTITY_COUNT];
    MASK mask[AEC_ENTITY_COUNT];
    CHARACTER_SPRITE character_sprite[AEC_ENTITY_COUNT];
    TRAIL trail[AEC_ENTITY_COUNT];
    PLAYER_CONTROLLED player_controlled[AEC_ENTITY_COUNT];
    NPC_MOVEMENT_AI npc_movement_ai[AEC_ENTITY_COUNT];
} AEC_EntityCatalog;

//
//THE STRUCT CONTAINING ALL COMPONENTS
//

//
//
//N/PC CHARACTER FUNCTIONS
//
//

static const unsigned int AEC_CHARACTER_WIDTH = 32;
static const unsigned int AEC_CHARACTER_HEIGHT = 32;
static const unsigned int AEC_CHARACTER_DOWN_FROM_BASE = 2;
static const unsigned int AEC_CHARACTER_X_CONSTANT = 2;
static const unsigned int AEC_CHARACTER_Y_CONSTANT = 2;
static const int DEAD_ZONE = 8000;

int AEC_CreateNewCharacter(AEC_EntityCatalog* entityCatalog, AE_LinkedTexture* characterSpriteSheet, AE_LinkedTexture* maskSpriteSheet);

SDL_bool AEC_Entity_SetPlayable(AEC_EntityCatalog* entityCatalog, int entity_id, SDL_bool isPlayable, int player_id);

SDL_bool AEC_CharacterSprite_CreateNew(int entity_id, AEC_EntityCatalog* entityCatalog, AE_LinkedTexture* characterSpriteSheet);

SDL_bool AEC_Mask_CreateNew(int entity_id, AEC_EntityCatalog* entityCatalog, AE_LinkedTexture* maskSpriteSheet);

AE_ColorBundle* AEC_GetRandomSkinColor();

void AEC_CharacterSprite_SetFlip(CHARACTER_SPRITE* characterSprite, SDL_RendererFlip flip);

void AEC_CharacterSprite_Render(CHARACTER_SPRITE* character_sprite, DISPLACEMENT* displacement, AEC_Camera* camera, SDL_Renderer* renderer, float step);

void AEC_Mask_Render(MASK* mask, DISPLACEMENT* displacement, float x_scale, float y_scale, AEC_Camera* camera, SDL_Renderer* renderer, float step);

void AEC_VelocityUpdateSimple(AEC_EntityCatalog* entityCatalog);

void AEC_DisplacementUpdate_ByVelocity(AEC_EntityCatalog* entityCatalog, float step);

void AEC_PlayerControlled_GetInput(AEC_EntityCatalog* entityCatalog, SDL_Event event);

void AEC_SetPlayerKeys(AEC_EntityCatalog* entityCatalog, int entity_id, SDL_Keycode* keys);

void AEC_Entities_Render(AEC_EntityCatalog* entityCatalog, AEC_Camera* camera, SDL_Renderer* renderer, float step);

void AEC_RenderEntity(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, AEC_Camera* camera, SDL_Renderer* renderer, float step);

Uint64 AEC_GetIsoDepth(AEC_EntityCatalog* entityCatalog, unsigned int entity_at);

void AEC_RenderCatalogToBuffer(AEC_EntityCatalog* entityCatalog, AEC_SpriteBuffer* sprite_buffer);

void AEC_RenderSpriteBuffer(AEC_SpriteBuffer* sprite_buffer, AEC_EntityCatalog* entityCatalog, AEC_Camera* camera, SDL_Renderer* renderer, float step);

void AEC_FlushSpriteBuffer(AEC_SpriteBuffer* spriteBuffer);

AEC_SpriteBuffer* AEC_Create_SpriteBuffer();

void AEC_CharacterMoveLegs(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, float step);

void AEC_CameraRefocus(AEC_EntityCatalog* entityCatalog, unsigned int target_entity, AEC_Camera* camera);

AEC_Camera* AEC_CameraCreate(Uint64 x, Uint64 y);

SDL_bool AEC_Drawable_IsInCamera(AEC_EntityCatalog* entityCatalog, unsigned int entity_at, AEC_Camera* camera);

#endif /* ae_components_h */
