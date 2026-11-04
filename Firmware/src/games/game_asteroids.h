/***
 * 
 *              ASTEROIDS
 * 
 *  uses the original graphics (found in gfx/asteroids.h), adapted from the original format for our hardware.
 *  not a faithful re-implementation of the original. 
 *  does not have sound, as it uses almost all of program memory for the game logic.
 * 
 */

#pragma once
#include "gfx/asteroids.h"

Vector as_player_pos;
uint8_t as_direction;
Vector as_velocity;
uint16_t as_score;
uint8_t b_as_ufo_in_play;
uint8_t as_respawn_timer;
uint8_t as_lives;
uint8_t b_as_gameover;
uint8_t as_titlescreen;

struct AS_BULLET
{
    bool empty;
    Vector position;
    Vector velocity;
    uint8_t orientation;
};

struct AS_GAMEOBJECT
{
    enum class GameObjectType : uint8_t
    {
        EMPTY = 0,
        UFO = 1,
        ROCK_SMALL = 2,
        ROCK_MEDIUM = 3,
        ROCK_LARGE = 4,
    };

    GameObjectType type;
    uint8_t variantData;
    uint8_t width;
    uint8_t height;
    Vector position;
    Vector velocity;

    void update()
    {
        if (type == GameObjectType::EMPTY)
            return;

        position = position + velocity;
        if (type == GameObjectType::UFO && (position.x > 1023 || position.x < 0))
        {
            type = GameObjectType::EMPTY;
            b_as_ufo_in_play = 0;
            return;
        }
        position.clampToScreen();

        if (type == GameObjectType::UFO)
        {
            display.SHAPE(AS_UFO, position);
        }
        else if (type == GameObjectType::ROCK_LARGE)
        {
            uint8_t rocksize = (uint8_t)type - (uint8_t)GameObjectType::ROCK_SMALL;
            switch (variantData)
            {
            case 0:
                display.SHAPE(AS_ROCK1_L, position, rocksize);
                break;
            case 1:
                display.SHAPE(AS_ROCK1_L, position, rocksize);
                break;
            case 2:
                display.SHAPE(AS_ROCK1_L, position, rocksize);
                break;
            case 3:
            default:
                display.SHAPE(AS_ROCK1_L, position, rocksize);
                break;
            }
        }
        else
        {
            uint8_t rocksize = (uint8_t)type - (uint8_t)GameObjectType::ROCK_SMALL;
            switch (variantData)
            {
            case 0:
                display.SHAPE(AS_ROCK1, position, rocksize);
                break;
            case 1:
                display.SHAPE(AS_ROCK2, position, rocksize);
                break;
            case 2:
                display.SHAPE(AS_ROCK3, position, rocksize);
                break;
            case 3:
            default:
                display.SHAPE(AS_ROCK4, position, rocksize);
                break;
            }
        }

        // draw hitbox
        // display.RECT(position.x - (int16_t)width, position.y - (int16_t)height, position.x + (int16_t)width, position.y + (int16_t)height, 64);
    }

    inline bool ishit(Vector pos, int8_t expand_hitbox = 0) const
    {
        bool hitx = pos.x >= (position.x - (width + expand_hitbox)) && pos.x <= (position.x + (width + expand_hitbox));
        bool hity = pos.y >= (position.y - (height + expand_hitbox)) && pos.y <= (position.y + (height + expand_hitbox));
        return hitx && hity;
    }
};

const uint8_t AS_MAX_BULLETS = 2;
AS_BULLET as_bullets[AS_MAX_BULLETS];

const uint8_t AS_MAX_GAMEOBJECTS = 10;
AS_GAMEOBJECT as_gameobjects[AS_MAX_GAMEOBJECTS];

void AS_SPAWN_OBJECT(AS_GAMEOBJECT::GameObjectType type, Vector position, uint8_t orientation, uint16_t linearVelocity, uint8_t width, uint8_t height, uint8_t variant = 0)
{
    for (int i = 0; i < AS_MAX_GAMEOBJECTS; ++i)
    {
        if (as_gameobjects[i].type != AS_GAMEOBJECT::GameObjectType::EMPTY)
            continue;

        as_gameobjects[i].type = type;
        as_gameobjects[i].position = position;
        as_gameobjects[i].height = height;
        as_gameobjects[i].width = width;

        Vector vVel = {0, (int16_t)linearVelocity};
        vVel = vVel.rotate(orientation);
        as_gameobjects[i].velocity = vVel >> 8;

        as_gameobjects[i].variantData = variant;

        return;
    }
}

void init_asteroids()
{
    as_player_pos = {512, 512};
    as_direction = 0;
    as_velocity = {0, 0};
    as_score = 0;
    as_respawn_timer = 0;
    b_as_gameover = 0;
    as_lives = 4;
    as_titlescreen = 128;

    for (int i = 0; i < AS_MAX_BULLETS; ++i)
        as_bullets[i].empty = true;
    for (int i = 0; i < AS_MAX_GAMEOBJECTS; ++i)
        as_gameobjects[i].type = AS_GAMEOBJECT::GameObjectType::EMPTY;

    for (int i = 0; i < 2; ++i)
    {
        uint8_t random_dir = rand() & 0xFF;
        uint8_t random_distance = ((rand() & 0xFF) << 2) + 200;
        Vector pos = {0, random_distance};
        pos = pos.rotate(random_dir);

        AS_SPAWN_OBJECT(AS_GAMEOBJECT::GameObjectType::ROCK_LARGE, pos, rand() & 0xFF, 0x300, 100, 100, (uint8_t)(rand() % 0b11));
    }

    b_as_ufo_in_play = 0;
}

void game_asteroids()
{
    if (controller.State().R() && controller.State().L())
    {
        init_asteroids();
    }

    if (as_titlescreen)
    {
        --as_titlescreen;
        display.TEXT("ASTEROIDS", {62, 440}, 1);

        if (controller.Pressed().A() || controller.Pressed().B() || controller.Pressed().X() || controller.Pressed().Y())
            as_titlescreen = 0;
        return;
    }

    if (b_as_gameover)
    {
        if (as_lives > 0)
        {
            display.TEXT("YOU WIN", {337, 490});
        }
        else
        {
            display.TEXT("GAME OVER", {287, 490});
        }

        display.DECIMAL(as_score, {500, 400});

        if (controller.Pressed().A() || controller.Pressed().B() || controller.Pressed().X() || controller.Pressed().Y())
        {
            init_asteroids();
        }

        return;
    }

    bool ship_in_play = true;
    if (as_respawn_timer > 0)
    {
        --as_respawn_timer;
        ship_in_play = false;
    }

    if (ship_in_play)
    {
        bool thrusting = controller.State().B() || controller.State().A();
        bool shooting = controller.Pressed().X() || controller.Pressed().Y();

        const int16_t max_vel = 15 * 256;

        if (thrusting)
        {
            Vector thrust_dir = {0, 64};
            thrust_dir = thrust_dir.rotate(as_direction);
            as_velocity = as_velocity + thrust_dir;

            if (as_velocity.x > max_vel)
                as_velocity.x = max_vel;
            if (as_velocity.x < -max_vel)
                as_velocity.x = -max_vel;
            if (as_velocity.y > max_vel)
                as_velocity.y = max_vel;
            if (as_velocity.y < -max_vel)
                as_velocity.y = -max_vel;
        }

        as_direction += -controller.State().XAxis() * 2;

        Vector pos_increment = as_velocity >> 8;
        as_player_pos = as_player_pos + pos_increment;
        as_player_pos.clampToScreen();

        if (shooting)
        {
            for (int i = 0; i < AS_MAX_BULLETS; ++i)
            {
                if (!as_bullets[i].empty)
                    continue;
                as_bullets[i].empty = false;
                as_bullets[i].position = as_player_pos;
                as_bullets[i].orientation = as_direction;
                as_bullets[i].velocity = {0, 24 * 16};
                as_bullets[i].velocity = as_bullets[i].velocity.rotate(as_direction) >> 4;

                break;
            }
        }

        display.SHAPE_ANGLE(AS_SHIP, as_direction, as_player_pos);
        if (thrusting)
            display.SHAPE_ANGLE(AS_SHIP_THRUST, as_direction, as_player_pos);
    }

    for (int i = 0; i < AS_MAX_BULLETS; ++i)
    {
        if (as_bullets[i].empty)
            continue;
        as_bullets[i].position = as_bullets[i].position + as_bullets[i].velocity;

        if (as_bullets[i].position.x < 0 || as_bullets[i].position.x > 1023 || as_bullets[i].position.y < 0 || as_bullets[i].position.y > 1023)
        {
            as_bullets[i].empty = true;
            continue;
        }

        display.SHAPE_ANGLE(AS_SP_BULLET, as_bullets[i].orientation, as_bullets[i].position);
    }

    bool _player_died_just_now = false;
    bool gameobject_in_play = false;

    for (int i = 0; i < AS_MAX_GAMEOBJECTS; ++i)
    {
        if (as_gameobjects[i].type == AS_GAMEOBJECT::GameObjectType::EMPTY)
            continue;

        gameobject_in_play = true;
        as_gameobjects[i].update();

        if (ship_in_play && !_player_died_just_now)
        {
            if (as_gameobjects[i].ishit(as_player_pos, 20))
            {
                // Player dies
                as_respawn_timer = 90;
                as_player_pos = {512, 512};
                as_velocity = {0, 0};
                as_direction = 0;
                --as_lives;
                if (as_lives == 0)
                {
                    b_as_gameover = 1;
                }
                _player_died_just_now = true;
            }
        }

        bool object_dies = false;
        for (int b = 0; b < AS_MAX_BULLETS; ++b)
        {
            if (as_bullets[b].empty)
                continue;

            if (as_gameobjects[i].ishit(as_bullets[b].position))
            {
                as_bullets[b].empty = true;
                object_dies = true;
                break;
            }
        }

        if (object_dies == true)
        {
            AS_GAMEOBJECT died = as_gameobjects[i];
            as_gameobjects[i].type = AS_GAMEOBJECT::GameObjectType::EMPTY;

            int numchildren = (rand() & 0b11) + 2;
            if (numchildren > 4)
                numchildren = 3;

            switch (died.type)
            {
            case AS_GAMEOBJECT::GameObjectType::EMPTY:
                break;
            case AS_GAMEOBJECT::GameObjectType::UFO:
                as_score += 1000;
                b_as_ufo_in_play = 0;
                break;
            case AS_GAMEOBJECT::GameObjectType::ROCK_LARGE:
                as_score += 100;
                for (int i = 0; i < numchildren; ++i)
                {
                    AS_SPAWN_OBJECT(AS_GAMEOBJECT::GameObjectType::ROCK_MEDIUM, died.position, rand() & 0xFF, 0x400, 50, 50, rand() & 0b11);
                }
                break;
            case AS_GAMEOBJECT::GameObjectType::ROCK_MEDIUM:
                as_score += 200;
                for (int i = 0; i < numchildren; ++i)
                {
                    AS_SPAWN_OBJECT(AS_GAMEOBJECT::GameObjectType::ROCK_SMALL, died.position, rand() & 0xFF, 0x500, 25, 25, rand() & 0b11);
                }
                break;
            case AS_GAMEOBJECT::GameObjectType::ROCK_SMALL:
                as_score += 300;
                break;
            }
        }
    }

    if (!gameobject_in_play)
    {
        b_as_gameover = 1;
    }

    display.DECIMAL(as_score, {250, 0});
    int16_t x = 330;
    for (int i = 0; i < as_lives; ++i)
    {
        display.SHAPE(AS_LIFE, {x, 30});
        x += 55;
    }

    if (b_as_ufo_in_play == 0 && ((rand() & 0xFF) == 0x00))
    {
        b_as_ufo_in_play = 1;
        uint8_t right = rand() & 0b01;
        AS_SPAWN_OBJECT(AS_GAMEOBJECT::GameObjectType::UFO, {(int16_t)(right ? 1023 : 0), (int16_t)((rand() & 0b0111111111) + 256)}, right ? 250 : 128, 0x600, 30, 30);
    }
}

#define GAME_START init_asteroids
#define GAME_LOOP game_asteroids