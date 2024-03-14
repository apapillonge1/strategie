#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

#define BTNHEIGHT 75
#define MAPSCALE 0.2

// #define TESTS_DIR_RPI "/home/pi/tests/"
// #define STRATS_DIR_RPI "/home/pi/strats/"
// #define RESSOURCES_DIR_RPI "/home/pi/ressources/"

// #define TESTS_DIR_PC "../tests/"
// #define STRATS_DIR_PC "../strats/"
// #define RESSOURCES_DIR_PC "../ressources/"

constexpr unsigned int playground_width = 3000;
constexpr unsigned int playground_height = 2000;

constexpr unsigned int border_gap = 10;
constexpr double scaling = 0.2;
constexpr double robot_scaling = 1; // how many times you need to multiply the img size to have 1pixel =  1mm in real life

#ifdef IS_RASPBERRY_PI

#define TESTS_DIR "/home/pi/tests/"
#define STRATS_DIR "/home/pi/strats/"
#define RESSOURCES_DIR "/home/pi/ressources/"

#else

#define TESTS_DIR "../../../tests/"
#define STRATS_DIR "../../../strats/"
#define RESSOURCES_DIR "../../ressources/"

#endif

constexpr std::string_view playground_image_resource = RESSOURCES_DIR "images/map.svg";

//constexpr std::string_view robot_image_resource = RESSOURCES_DIR "images/robot_ouvert.png";
constexpr std::string_view robot_image_resource = RESSOURCES_DIR "images/robot_ferme.png";

constexpr std::string_view fragile_plant_ressource = RESSOURCES_DIR "images/plants/fragile_plant.svg";
constexpr std::string_view fragile_plant_pot_ressource = RESSOURCES_DIR "images/plants/fragile_plant_pot.svg";

constexpr std::string_view regular_plant_ressource = RESSOURCES_DIR "images/plants/regular_plant.svg";
constexpr std::string_view regular_plant_pot_ressource = RESSOURCES_DIR "images/plants/regular_plant_pot.svg";

#endif // CONSTANTS_H
