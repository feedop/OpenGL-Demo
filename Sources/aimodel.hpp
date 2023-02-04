#pragma once

#include "model.hpp"

class AIModel : public MovableModel
{
public:
    AIModel(const char* path);
    void move() override;
};