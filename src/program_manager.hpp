#pragma once
#include "core/physics_world.hpp"
#include "core/renderer_scene.hpp"
#include "core/shared_state.hpp"
#include <vector>

/**
*  
*/
class ProgramManager {
  Shared &_shared;
  renderer::Scene &_scene;
  physics::World &_physics;

  std::vector<json> _recipes; // stored here, for future scene saving

public:
  ProgramManager(Shared &shared, renderer::Scene &scene, physics::World &physics);
  ~ProgramManager() = default;

  // Loader test
  void loadTestNRandomCubes(int n);
  void loadTestNRandomCubesAndSpheres(int n);
  void loadTestNRandomCylinders(int n); 

private:
  /* Recipes */
  void registerRecipe(json recipe);
  json recipeGroundDefault();
  json recipeCubeRandom(int size_max = 10, int spread_max = 100);
  json recipeSphereRandom(int size_max = 10, int spread_max = 100);
  json recipeCylinderRandom(int h_max = 10, int radius_max = 5, int spread_max = 100);


  // Spawner
  void spawnObject(json recipe);
};