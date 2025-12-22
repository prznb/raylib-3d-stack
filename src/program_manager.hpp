#pragma once
#include "core/physics_world.hpp"
#include "core/renderer_scene.hpp"
#include "core/shared_state.hpp"
#include <vector>
#include <fstream>

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
  void loadTestWorldFromSavedFile()
  {
    std::ifstream file("output.json");
    json loaded = json::parse(file);

    for (const auto& recipe : loaded) 
    {
      _recipes.push_back(recipe);
      spawnObject(recipe);
    }
  }

  // Loading/saving test
  void saveSimulation()
  {
    // save physics world
    //_physics.save();

    nlohmann::json object_parameters = nlohmann::json::array();
    for (const auto& recipe :_recipes ) {
        object_parameters.push_back(recipe);
    }
    std::ofstream file("output.json");
    file << object_parameters.dump(4);     // pretty-printed with indent = 4
    file.close();
  }

  void loadTestVehicle();


private:
  /* Recipes */
  void registerRecipe(json recipe);
  json recipeGroundDefault();
  json recipeCubeRandom(int size_max = 10, int spread_max = 100);
  json recipeSphereRandom(int size_max = 10, int spread_max = 100);
  json recipeCylinderRandom(int h_max = 10, int radius_max = 5, int spread_max = 100);
  json recipeSphereTiny(int pos_x=0, int pos_y = 0, int pos_z = 0);
  json recipeDebugVehicle();

  // Spawner
  void spawnObject(json recipe);
};