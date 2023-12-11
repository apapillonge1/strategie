#ifndef CONSTANTS_H
#define CONSTANTS_H

#define BTNHEIGHT 75
#define MAPSCALE 0.2


constexpr std::string_view playground_image_resource = ":/ressources/images/map.svg";
constexpr unsigned int playground_width = 3000;
constexpr unsigned int playground_height = 2000;
constexpr double scaling = 0.2;

constexpr std::string_view robot_image_resource = ":/ressources/images/robot.png";
constexpr double robot_scaling = 5; // how many times you need to multiply the img size to have 1pixel =  1mm in real life


#endif // CONSTANTS_H
