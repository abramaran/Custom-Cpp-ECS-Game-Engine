#pragma once
#include <cstdint>

//power-up generation variables
const uint32_t MAX_PWBOXES = 3;
const uint32_t SPAWN_PWBOX_TIME = 5;


const uint32_t MAX_HP = 100;
const uint32_t BULLET_HP = 200;
const float BULLET_INCREASE_TIME = 0.5;
//speed
const uint32_t MOVEMENT_SPEED = 200;
const uint32_t MOVEMENT_SPEED_JMP = 100;
const uint32_t JUMP_SPEED = 200;


const float distance = 0.475 * 2.5 * 30;
const float vel = distance * 1.5;
const uint32_t BELT_SPEED = vel;


//DASH
const uint32_t DASH_DISTANCE = 150;
const uint32_t DASH_SPEED = 1550; 

const float DASH_COOLDOWN = 1; 

//Stamina
const uint32_t MAX_STAMINA = 100;

const uint32_t DASH_STAMINA = 5;
const uint32_t JUMP_STAMINA = 5;
const uint32_t DIRECTFIST_STAMINA = 7;
const uint32_t CROCHETFIST_STAMINA = 15;
const uint32_t UPPERCUTFIST_STAMINA = 20;
const float BLOCK_STAMINA = 0.5;

//Damage
const uint32_t DIRECTFIST_DAMAGE = 10;
const uint32_t CROCHETFIST_DAMAGE = 10;
const uint32_t UPPERCUTFIST_DAMAGE = 20;
const uint32_t FALLINGHIT_DAMAGE = 20;
const uint32_t BULLET_DAMAGE_MIN = 5;
const uint32_t BULLET_DAMAGE_MAX = 25;
const uint32_t DAMAGE_TRAIN = 10;
const uint32_t DAMAGE_SAW = 10;


const uint32_t DIRECT_FEEDBACK = 1000;
const uint32_t CROCHET_FEEDBACK = 1000;
const uint32_t UPPERCUT_FEEDBACK = 1500;
const uint32_t FALLINGHIT_FEEDBACK = 800;

//Falling hit
const uint32_t RANGE_DOWN = 50;
const int FALLING_VEL= -1000;


//Box
const uint32_t defaultBoxSizeHalf = 5;
const uint32_t defaultBoxSize = 10;
const uint32_t areaHit = 10;

//PowerUps
const uint32_t exDam = 10;
const uint32_t exDef = 10;
const uint32_t exVel = 100;
const int exEst = 25;
const int exHP  = 25;
const float JUMP_COOLDOWN = 0.5;
const uint32_t STUN_EFFECT_COOLDOWN = 5;
const float STUN_EFFECT_TRAIN = 0.3;
const uint32_t PW_COOLDOWN = 5;
const uint32_t BLLT_COOLDOWN = 1;
