# OpenGL Demo

Author: Filip Skrzeczkowski

An OpenGL Demo program featuring a Star Wars inspired scene.

## How to build?

The package contains a Visual Studio 2022 .sln file. Use it to build and launch the project.
When starting, please make sure that the directory containing the solution file and all the resources is the working directory.

## How to use?

Upon launching the application two windows should appear. An OpenGl window containing the scene and an ImGui window for configuration.
In order to move around the scene use WASD and arrow keys.

Important note: The controls work only if the OpenGL window is focused. 

### Controls: ###

 * W, S - turn up/down (adjust the pitch angle), please note that W corresponds to "dive down" and S to "pull up"
 * A, D - turn left/right (adjust the yaw angle)
 * left and right arrow keys - roll left/right (adjust the roll angle)
 * up and down arrow keys - increase or decrease velocity respectively

### Configuration ###

Use the second ImGui window to:
 * change the shading method,
 * choose one of the three cameras (third-person camera can be inverted too),
 * switch to night time (the main directional light gets weaker over a few seconds),
 * select the fog density and its color,
 * enable turbulence (periodic rolling left/right of the player model),
 * adjust the relative direction of front-facing spotlights attached to the player model

## Technical aspects

The application is written in C++ 20. It uses OpenGL for graphics and ImGui for UI as well as Assimp for model loading.
Three shading methods are implemented:
 * Texture only (no light)
 * Gouraud shading
 * Phong shading (includes deferred shading)

 The scene contains a main directional lights, several static point lights (big ships' engines) and spotlights attached to moving objects
 (both front and back).

## Credits ##
Models downloaded from:
 * Venator:
   https://downloadfree3d.com/3d-models/aircraft/spaceship/venator-class-star-destroyer/
 * Acclamator:
   "Acclamator-class assault ship" (https://skfb.ly/oxF7x) by 𝓵𝓲𝓰𝓱𝓽𝔀𝓪𝓻𝓻𝓲𝓸𝓻 is licensed under Creative Commons Attribution (http://creativecommons.org/licenses/by/4.0/).
 * ARC-170:
   "ARC-170 Fighter" (https://skfb.ly/6pOS6) by StarWars-Universe is licensed under CC Attribution-NonCommercial-ShareAlike (http://creativecommons.org/licenses/by-nc-sa/4.0/).
 * Lucrehulk:
   "Star Wars Battlefront 2 CIS Lucrehulk" (https://skfb.ly/o6DNr) by Neut2000 is licensed under Creative Commons Attribution (http://creativecommons.org/licenses/by/4.0/).
 * Droid Tri-fighter:
   "Droid Tri Fighter" (https://skfb.ly/6RSyA) by Steven is licensed under Creative Commons Attribution-NonCommercial (http://creativecommons.org/licenses/by-nc/4.0/).