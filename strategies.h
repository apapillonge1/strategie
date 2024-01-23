#ifndef STRATEGIES_H
#define STRATEGIES_H

#include "JSON_overlay/jsonstatemachine.h"

#include "commonActions.h"
#include "robotActions.h"

template<>
inline action_factory<Context>::meta_factory_type action_factory<Context>::meta_factory = {
    {"Line",    [](const std::string & tag, const nlohmann::json &params) {return new Line(tag, params);} },
    {"Rotate",    [](const std::string & tag, const nlohmann::json &params) {return new Line(tag, params);} },
    {"XYT",    [](const std::string & tag, const nlohmann::json &params) {return new Line(tag, params);} },
    {"Homing",    [](const std::string & tag, const nlohmann::json &params) {return new Line(tag, params);} },
    {"Wait",    [](const std::string & tag, const nlohmann::json &params) {return new Line(tag, params);} },
    {"AddPoints",    [](const std::string & tag, const nlohmann::json &params) {return new Line(tag, params);} },
    {"RegisterPoints",    [](const std::string & tag, const nlohmann::json &params) {return new Line(tag, params);} },

    //{"YourActionName", [](const std::string & tag, const nlohmann::json &params) {return new YourActionName(tag, params);} }
};

#endif // STRATEGIES_H
