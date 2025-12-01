## Todo: 
* [x] Copy assets to the build folder on build
    * [x] #blocked executable references copied assets from the build folder
    * [x] Add attribution to the artists for the models or other license-compliant stuff 

* [x] Rework camera controls
    * [x] Add precompute function (events + translation to the camera position)
    * [x] Add "player follow" functionality

* [x] GUI - debug console
    * [x] Crude display of player's ship position, orientation
    * [x] GUI code rework - make it extensible for the display of other parameters (we'd want forces later)

* [x] Implement Player Controls 
    * [x] Design interfaces for the control actions
    * [x] Translate them onto F/T commands of the ship

* [x] Physics for the player 
    * [x] Add a collider for the ship
    * [x] Add a rigid body for the ship
    * [x] Add an interface to apply forces/torques to a rigid body
    * [x] Debug tools for the ship collider position

* [x] Physics bridge
    * [x] Implement a bridge for coordinate transform between bullet and raylib
    * [x] Implement ad-hoc trajectory shaper -> (maybe) add a separate class for handling user input; 
          based on the user input, apply forces and torques to the ship.
    * [x] Debug tools for the forces/torques

* [x] Play tests!

* [x] Codebase refactoring 

## Game design

## Dev
Codebase Design Considerations:
* Avoid using raylib-cpp wrapper!


Division of features: 
1. Handled by **raylib**: 
- Rendering 
- Display math
- Shading
- Camera controls
- Input capture 

2. Handled by **bullet**: 
- Collisions
- Force response and capture
- All the other math

3. Handled by the pysics bridge (custom module - linikng physics with rendering): 
- Force profiler
