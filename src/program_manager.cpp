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

void ProgramManager::loadTestVehicle()
{
  json recipe_ground = recipeGroundDefault();
  spawnObject(recipe_ground);

  json recipe_vehicle = recipeDebugVehicle();
  spawnObject(recipe_vehicle);


  for(int i = 10; i < 1000; i++)
  {
    json rst = recipeSphereTiny(0, i, 0);
    spawnObject(rst);
  }

}


void ProgramManager::registerRecipe(json recipe) { _recipes.push_back(recipe); }

/* Recipes */
json ProgramManager::recipeGroundDefault() {
  json recipe;
  // Shared Properties
  recipe["type"] = "ground";
  recipe["dimensions"]["width"] = 1E3;
  recipe["dimensions"]["height"] = 1E3;
  recipe["dimensions"]["length"] = 1E3;

  recipe["color"]["r"] = 255;
  recipe["color"]["g"] = 255;
  recipe["color"]["b"] = 255;
  recipe["color"]["a"] = 255;
  recipe["mass"] = 0.f;
  recipe["inertia"]["x"] = 0.f;
  recipe["inertia"]["y"] = 0.f;
  recipe["inertia"]["z"] = 0.f;
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
  recipe["inertia"]["x"] = 10.f;
  recipe["inertia"]["y"] = 10.f;
  recipe["inertia"]["z"] = 10.f;
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
  recipe["inertia"]["x"] = 10.f;
  recipe["inertia"]["y"] = 10.f;
  recipe["inertia"]["z"] = 10.f;
  recipe["position"]["x"] = (float)(rand() % spread_max);
  recipe["position"]["y"] = (float)(rand() % spread_max);
  recipe["position"]["z"] = (float)(rand() % spread_max);
  recipe["rotation"]["yaw"] = 0.f;
  recipe["rotation"]["pitch"] = 0.f;
  recipe["rotation"]["roll"] = 1.f;

  return recipe;
}

json ProgramManager::recipeSphereTiny(int pos_x, int pos_y, int pos_z) {
  json recipe;

  recipe["type"] = "sphere";
  recipe["dimensions"]["radius"] = (float)0.1;
  recipe["resolution"] = (int)20; // 20 rings, 20 slices

  recipe["color"]["r"] = (float)(rand() % 256);
  recipe["color"]["g"] = (float)(rand() % 256);
  recipe["color"]["b"] = (float)(rand() % 256);
  recipe["color"]["a"] = 255;

  recipe["mass"] = 100.f;
  recipe["inertia"]["x"] = 10.f;
  recipe["inertia"]["y"] = 10.f;
  recipe["inertia"]["z"] = 10.f;
  recipe["position"]["x"] = (float)pos_x;
  recipe["position"]["y"] = (float)pos_y;
  recipe["position"]["z"] = (float)pos_z;
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
  recipe["inertia"]["x"] = 10.f;
  recipe["inertia"]["y"] = 10.f;
  recipe["inertia"]["z"] = 10.f;
  recipe["position"]["x"] = (float)(rand() % spread_max);
  recipe["position"]["y"] = (float)(rand() % spread_max);
  recipe["position"]["z"] = (float)(rand() % spread_max);
  recipe["rotation"]["yaw"] = 0.f;
  recipe["rotation"]["pitch"] = 0.f;
  recipe["rotation"]["roll"] = 1.f;

  return recipe;
}

json ProgramManager::recipeDebugVehicle()
{
  // Approximate inertial params of BMW M3 2020+, 17 inch wheels
  json recipe;
  recipe["type"] = "car";

  // Body definition
  recipe["dimensions"]["chassis"]["width"] =  1.903f;
  recipe["dimensions"]["chassis"]["length"] = 4.801f;
  recipe["dimensions"]["chassis"]["height"] = 1.438f;
  
  recipe["dimensions"]["wheels"]["wheelbase"] = 2.857f;
  recipe["dimensions"]["wheels"]["track"] =  1.617f;
  recipe["dimensions"]["wheels"]["radius"] = 0.343f;   
  recipe["dimensions"]["wheels"]["thickness"] = 0.205f;
  recipe["dimensions"]["wheels"]["suspension_at_rest"] = 0.5f;


  recipe["color"]["r"] = 10;
  recipe["color"]["g"] = 255;
  recipe["color"]["b"] = 10;
  recipe["color"]["a"] = 255;

  recipe["mass"] = 1719.f;
  // Note: +x points to the right in the chassis frame
  recipe["inertia"]["x"] = (1719.f/2.f)*(2857.f/2.f)*(2857.f/2.f); // 50/50 mass dist, (m/2)*((wheelbase/2)^2)
  recipe["inertia"]["y"] = (1719.f/2.f)*(2857.f/2.f)*(2857.f/2.f); // 50/50 mass dist, (m/2)*((wheelbase/2)^2)
  recipe["inertia"]["z"] = (1719.f/2.f)*(1617.f/2.f)*(1617.f/2.f); // (m/2)*((wheel_track/2)^2) 

  recipe["position"]["x"] = 0.f;
  recipe["position"]["y"] = 5.f;
  recipe["position"]["z"] = 0.f;
  recipe["rotation"]["yaw"] = 0.f;
  recipe["rotation"]["pitch"] = 0.f;
  recipe["rotation"]["roll"] = 0.f;

  recipe["model"] = "debug_m3";

  return recipe;
}

// Spawner
void ProgramManager::spawnObject(json recipe) {
  _scene.addObject(recipe);
  _physics.addObject(recipe);
  _shared.registerEvent(OBJECT_ADDED);
  this->registerRecipe(std::move(recipe));
}
