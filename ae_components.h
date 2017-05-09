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

static const int AEC_CAMERA_SHAKE_MAX = 1;

typedef struct {
    uint64_t x;
    uint64_t y;
    uint64_t w;
    uint64_t h;
    float shake_length;
    float shake_current_time;
    float shake_amount;
    SDL_bool has_target;
} AEC_Camera;

typedef struct {
    uint64_t x;
    uint64_t y;
} AEC_TrailPoint;

//
//STRUCTS FOR GAMEPLAY
//

//
//ESSENTIAL VARIABLE: THE NUMBER OF AVAILIBLE COMPONENTS AND ENTITIES
//

static const unsigned int AEC_COMPONENT_COUNT = 9;
static const unsigned int AEC_ENTITY_COUNT = 1000;
static const unsigned int AEC_INVENTORY_MAX = 1000;
static const unsigned int AEC_INVENTORY_CATEGORY_COUNT = 5;

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

typedef enum {
    AEC_WEPTYPE_NONE,
    AEC_WEPTYPE_SWORD,
    AEC_WEPTYPE_BOW,
    AEC_WEPTYPE_MAGIC,
    AEC_WEPTYPE_POLEARM
} AEC_WeaponType;

typedef enum {
    AEC_INVTYPE_WEAPON,
    AEC_INVTYPE_ARMOR,
    AEC_INVTYPE_HELM,
    AEC_INVTYPE_MISC,
    AEC_INVTYPE_ARROW
} AEC_InventoryType;

//
//ESSENTIAL VARIABLE: THE NUMBER OF AVAILIBLE COMPONENTS AND ENTITIES
//

typedef struct {
    SDL_bool component_mask[AEC_COMPONENT_COUNT];
} COMPONENTS;

typedef struct {
    //These reference the world x and world y
    uint64_t x;
    uint64_t y;
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
    unsigned int entity_to_follow;
} NPC_MOVEMENT_AI;

typedef struct {
    unsigned int items[AEC_INVENTORY_CATEGORY_COUNT][AEC_INVENTORY_MAX];
    unsigned int item_count[AEC_INVENTORY_CATEGORY_COUNT];
    unsigned int equipped[AEC_INVENTORY_CATEGORY_COUNT];
} INVENTORY;

typedef struct {
    unsigned int weapon_type;
    SDL_bool is_in_use;
    float weapon_angle;
    uint64_t x_distance;
    uint64_t y_distance;
} WEAPON;

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
    INVENTORY inventory[AEC_ENTITY_COUNT];
    WEAPON weapon[AEC_ENTITY_COUNT];
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

unsigned int AEC_Entity_CreateNew(AEC_EntityCatalog* entityCatalog);

SDL_bool AEC_Entity_Exists(AEC_EntityCatalog* entityCatalog, unsigned int entity_id);

SDL_bool AEC_Entity_IsFilled(AEC_EntityCatalog* entityCatalog, unsigned int entity_id);

AE_ColorBundle* AEC_GetRandomSkinColor();

uint64_t AEC_GetIsoDepth(AEC_EntityCatalog* entityCatalog, unsigned int entity_at);

//
//
//START: CAMERA FUNCTIONS
//
//

AEC_Camera* AEC_Camera_CreateNew(uint64_t x, uint64_t y, uint64_t w, uint64_t h);

void AEC_Camera_Refocus(AEC_EntityCatalog* entityCatalog, unsigned int target_entity, AEC_Camera* camera);

void AEC_Camera_SetNewShake(AEC_Camera* camera, float shake_length, float shake_amount);

void AEC_Camera_ShakeUpdate(AEC_Camera* camera, float step);

void AEC_Camera_HasTarget(AEC_Camera* camera, SDL_bool has_target);

//
//
//END: CAMERA FUNCTIONS
//
//

#endif /* ae_components_h */
