#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

#define BTNHEIGHT 75
#define MAPSCALE 0.2


constexpr std::string_view playground_image_resource = ":/ressources/images/map.svg";
constexpr unsigned int playground_width = 3000;
constexpr unsigned int playground_height = 2000;

constexpr unsigned int border_gap = 10;
constexpr double scaling = 0.2;

//constexpr std::string_view robot_image_resource = ":/ressources/images/robot_ouvert.png";
constexpr std::string_view robot_image_resource = ":/ressources/images/robot_ferme.png";
constexpr double robot_scaling = 1; // how many times you need to multiply the img size to have 1pixel =  1mm in real life

constexpr std::string_view fragile_plant_ressource = ":/ressources/images/plants/fragile_plant.svg";
constexpr std::string_view fragile_plant_pot_ressource = ":/ressources/images/plants/fragile_plant_pot.svg";

constexpr std::string_view regular_plant_ressource = ":/ressources/images/plants/regular_plant.svg";
constexpr std::string_view regular_plant_pot_ressource = ":/ressources/images/plants/regular_plant_pot.svg";

#endif // CONSTANTS_H
