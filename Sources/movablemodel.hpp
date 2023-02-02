#pragma once

#include "model.hpp"

class MovableModel : public Model
{
public:
    virtual void move() = 0;
protected:
    MovableModel(const char* path);
};

class PlayerModel : public MovableModel
{
public:
    PlayerModel(const char* path);
    void move() override;
};

class AIModel : public MovableModel
{
public:
    AIModel(const char* path);
    void move() override;
};