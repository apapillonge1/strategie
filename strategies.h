#ifndef STRATEGIES_H
#define STRATEGIES_H

#include "JSON_overlay/jsonstatemachine.h"
#include "strategy/strategymanager.h"

struct VRAC_context {
    bool colorside;
    //path_finder & path_finder;
    //CanBusSocket can;
    //...
};

struct Line : public state<VRAC_context, nlohmann::json> {
public:
    Line(const std::string & name,  const nlohmann::json & params) : state<VRAC_context, nlohmann::json>(name, params){
    }

    virtual void on_entry(VRAC_context &, Event) override {}
        // read params to get the distance
        // send goal to path_finder to check if path is ok
        // send command to can


    virtual void on_exit(VRAC_context &, Event) override {}
};

template<>
inline action_factory<VRAC_context>::meta_factory_type action_factory<VRAC_context>::meta_factory = {
    {"Line",    [](const std::string & tag, const nlohmann::json &params) {return new Line(tag, params);} }//,
    //{"YourActionName", [](const std::string & tag, const nlohmann::json &params) {return new YourActionName(tag, params);} }
};

#endif // STRATEGIES_H
