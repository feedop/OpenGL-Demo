#include "movablemodel.hpp"

MovableModel::MovableModel(const char* path) : Model(path)
{}


PlayerModel::PlayerModel(const char* path) : MovableModel(path)
{}

void PlayerModel::move()
{}

AIModel::AIModel(const char* path) : MovableModel(path)
{}

void AIModel::move()
{}

