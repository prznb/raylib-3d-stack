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
