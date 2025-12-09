#include "program_manager.hpp"

ProgramManager::ProgramManager(Shared &shared, renderer::Scene &scene,
                               physics::World &physics)
    : _shared(shared), _scene(scene), _physics(physics) {
  // start randomizer for this translation unit
  srand(0);
};

void ProgramManager::loadTestNRandomCubes(int n) {
  json recipe_ground = recipeGroundDefault();
  spawnObject(recipe_ground);

  for (int i = 0; i < n; ++i) {
    json recipe_rand = recipeCubeRandom();
    spawnObject(recipe_rand);
  }
}

void ProgramManager::loadTestNRandomCubesAndSpheres(int n) 
{
  loadTestNRandomCubes(n);
  // spheres
  for (int i = 0; i < n; ++i) {
    json recipe_sphere_rand = recipeSphereRandom();
    spawnObject(recipe_sphere_rand);
  }
}

void ProgramManager::loadTestNRandomCylinders(int n) 
{
  json recipe_ground = recipeGroundDefault();
  spawnObject(recipe_ground);

  for (int i = 0; i < n; ++i) 
  {
    json recipe_rand = recipeCylinderRandom();
    spawnObject(recipe_rand);
  }

}


void ProgramManager::registerRecipe(json recipe) { _recipes.push_back(recipe); }

/* Recipes */
json ProgramManager::recipeGroundDefault() {
  json recipe;
  // Shared Properties
  recipe["type"] = "cube";
  recipe["dimensions"]["width"] = 1E3;
  recipe["dimensions"]["height"] = 1E3;
  recipe["dimensions"]["length"] = 1E3;

  recipe["color"]["r"] = 255;
  recipe["color"]["g"] = 255;
  recipe["color"]["b"] = 255;
  recipe["color"]["a"] = 0;
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
json ProgramManager::recipeCubeRandom(int size_max, int spread_max) {
  json recipe;

  recipe["type"] = "cube";
  recipe["dimensions"]["width"] = (float)(rand() % size_max);
  recipe["dimensions"]["length"] = (float)(rand() % size_max);
  recipe["dimensions"]["height"] = (float)(rand() % size_max);

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

json ProgramManager::recipeSphereRandom(int size_max, int spread_max) {
  json recipe;

  recipe["type"] = "sphere";
  recipe["dimensions"]["radius"] = (float)(rand() % size_max);
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

json ProgramManager::recipeCylinderRandom(int h_max, int radius_max, int spread_max)
{
  json recipe;

  recipe["type"] = "cylinder";
  recipe["dimensions"]["height"] = (float)(1+rand() % h_max);
  recipe["dimensions"]["radius"] = (float)(1+rand() % radius_max);
  recipe["resolution"] = (int)20;

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
void ProgramManager::spawnObject(json recipe) {
  _scene.addObject(recipe);
  _physics.addObject(recipe);
  _shared.registerEvent(OBJECT_ADDED);
  this->registerRecipe(std::move(recipe));
}
