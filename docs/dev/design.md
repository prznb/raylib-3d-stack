## Requirements for 0.0.1

* [ ] (Abstract) Object support:
    * [ ] cubes
    * [ ] cones
    * [ ] spheres
    * [ ] capsules
* [ ] (Physics) Object inertia inference from shape and mass
* [ ] Save and load mesh configuration to the scene from HDD files
* [ ] Program modes:
    * [ ] *EDIT* - place actors on the screen
    * [ ] *RUN* - runs the simulation
* [ ] GUI: 
    * [ ] Interface for placing objects
    * [ ] Display the number of objects in the world/scene


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
