#pragma once

#include <vector>

#include "playermodel.hpp"
#include "aimodel.hpp"
#include "light.hpp"

class Repository
{
public:
	std::vector<Model> staticModels;
	std::vector<AIModel> aiModels;
	PlayerModel playerModel;

	std::vector<DirLight> dirLights;
	std::vector<PointLight> pointLights;
	std::vector<SpotLight> spotLights;

	Repository();
private:
	void setUpModelInitialPositions();
};