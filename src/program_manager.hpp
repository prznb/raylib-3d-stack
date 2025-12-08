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
  ProgramManager(Shared &shared, renderer::Scene &scene,
                 physics::World &physics)
      : _shared(shared), _scene(scene), _physics(physics) 
      {
        // start randomizer for this translation unit 
        srand(0);
      };
  ~ProgramManager() = default;

  void loadTestNRandomCubes(int n) 
  {
    json recipe_ground = recipeGroundDefault();
    spawnObject(recipe_ground);

    for (int i = 0; i < n; ++i) {
      json recipe_rand = recipeCubeRandom();
      spawnObject(recipe_rand);
    }
  }

  void loadTestNRandomCubesAndSpheres(int n)
  {
    loadTestNRandomCubes(n);
    // spheres
    for (int i = 0; i < n; ++i) {
      json recipe_sphere_rand = recipeSphereRandom();
      spawnObject(recipe_sphere_rand);
    }
  }

private:
  
  void registerRecipe(json recipe)
  {
    _recipes.push_back(recipe);
  }

  /* Recipes */
  json recipeGroundDefault()
  {
    json recipe;
    // Shared Properties
    recipe["type"] = "cube";
    recipe["side_length"] = 1E3;
    recipe["color"]["r"] = 0;
    recipe["color"]["g"] = 0;
    recipe["color"]["b"] = 255;
    recipe["color"]["a"] = 255;
    recipe["mass"] = 0.f;
    recipe["inertia"] = 0.f;
    //-250, -500, -250
    recipe["position"]["x"] = -250;
    recipe["position"]["y"] = -500;
    recipe["position"]["z"] = -250;
    recipe["rotation"]["yaw"] = 0.f;
    recipe["rotation"]["pitch"] = 0.f;
    recipe["rotation"]["roll"] = 0.f;
    return recipe;
  }

  // Cube, random size, random position, random color
  json recipeCubeRandom(int size_max = 10, int spread_max = 100)
  {
    json recipe;

    recipe["type"] = "cube";
    recipe["side_length"] = (float)(rand() % size_max);

    recipe["color"]["r"] = (float)(rand() % 256);
    recipe["color"]["g"] = (float)(rand() % 256);
    recipe["color"]["b"] = (float)(rand() % 256);
    recipe["color"]["a"] = 255;

    recipe["mass"] = 10.f;
    recipe["inertia"] = 10.f;
    recipe["position"]["x"] = (float)(rand() % spread_max);
    recipe["position"]["y"] = (float)(rand() % spread_max);
    recipe["position"]["z"] = (float)(rand() % spread_max);
    recipe["rotation"]["yaw"] = 0.f;
    recipe["rotation"]["pitch"] = 0.f;
    recipe["rotation"]["roll"] = 1.f;

    return recipe;
  }
  
  json recipeSphereRandom(int size_max = 10, int spread_max = 100)
  {
    json recipe;

    recipe["type"] = "sphere";
    recipe["radius"] = (float)(rand() % size_max);
    recipe["resolution"] = (int)20; // 20 rings, 20 slices

    recipe["color"]["r"] = (float)(rand() % 256);
    recipe["color"]["g"] = (float)(rand() % 256);
    recipe["color"]["b"] = (float)(rand() % 256);
    recipe["color"]["a"] = 255;

    recipe["mass"] = 10.f;
    recipe["inertia"] = 10.f;
    recipe["position"]["x"] = (float)(rand() % spread_max);
    recipe["position"]["y"] = (float)(rand() % spread_max);
    recipe["position"]["z"] = (float)(rand() % spread_max);
    recipe["rotation"]["yaw"] = 0.f;
    recipe["rotation"]["pitch"] = 0.f;
    recipe["rotation"]["roll"] = 1.f;

    return recipe;
  }

  // Spawner
  void spawnObject(json recipe) 
  {
    _scene.addObject(recipe);
    _physics.addObject(recipe);
    _shared.registerEvent(OBJECT_ADDED);
    this->registerRecipe(std::move(recipe));
  }
};