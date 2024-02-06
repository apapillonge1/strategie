#ifndef COMMONACTIONS_H
#define COMMONACTIONS_H

#include "strategy/STM/state.h"
#include "context.h"

struct Line : public state<Context, nlohmann::json> {
public:
    Line(const std::string & name,  const nlohmann::json & params) : state<Context, nlohmann::json>(name, params){
    }

    virtual void on_entry(Context &, Event) override {
        //qDebug() <<  nlohmann::to_string(params);
        speed = nlohmann::to_string(params["speed"]["selected"]);
        std::cout << "speed : " << speed << std::endl;

        distance = params["distance"];
        std::cout << "distance : " << distance << std::endl;

        forward = params["forward"];
        std::cout << "forward : " << forward << std::endl;
    }
    // read params to get the distance
    // send goal to path_finder to check if path is ok
    // send command to can

    virtual void on_exit(Context &, Event) override {
    }

private:
    int distance;
    std::string speed;
    bool forward;
};

struct Rotate : public state<Context, nlohmann::json> {
public:
    Rotate(const std::string & name,  const nlohmann::json & params) : state<Context, nlohmann::json>(name, params){
    }

    virtual void on_entry(Context &, Event) override {
        qDebug() <<  nlohmann::to_string(params);
    }
    // read params to get the distance
    // send goal to path_finder to check if path is ok
    // send command to can


    virtual void on_exit(Context &, Event) override {}

private:
    bool displayed;
    bool relative;
    int theta;
    std::string speed;
};

struct XYT : public state<Context, nlohmann::json> {
public:
    XYT(const std::string & name,  const nlohmann::json & params) : state<Context, nlohmann::json>(name, params){
    }

    virtual void on_entry(Context &, Event) override {
        qDebug() <<  nlohmann::to_string(params);
    }
    // read params to get the distance
    // send goal to path_finder to check if path is ok
    // send command to can


    virtual void on_exit(Context &, Event) override {}
};

struct Homing : public state<Context, nlohmann::json> {
public:
    Homing(const std::string & name,  const nlohmann::json & params) : state<Context, nlohmann::json>(name, params){
    }

    virtual void on_entry(Context &, Event) override {
        qDebug() <<  nlohmann::to_string(params);
    }
    // read params to get the distance
    // send goal to path_finder to check if path is ok
    // send command to can


    virtual void on_exit(Context &, Event) override {}
};

struct Wait : public state<Context, nlohmann::json> {
public:
    Wait(const std::string & name,  const nlohmann::json & params) : state<Context, nlohmann::json>(name, params){
    }

    virtual void on_entry(Context &, Event) override {
        qDebug() <<  nlohmann::to_string(params);
    }
    // read params to get the distance
    // send goal to path_finder to check if path is ok
    // send command to can


    virtual void on_exit(Context &, Event) override {}
};

struct AddPoints : public state<Context, nlohmann::json> {
public:
    AddPoints(const std::string & name,  const nlohmann::json & params) : state<Context, nlohmann::json>(name, params){
    }

    virtual void on_entry(Context &, Event) override {
        qDebug() <<  nlohmann::to_string(params);
    }
    // read params to get the distance
    // send goal to path_finder to check if path is ok
    // send command to can


    virtual void on_exit(Context &, Event) override {}
};

struct RegisterPoints : public state<Context, nlohmann::json> {
public:
    RegisterPoints(const std::string & name,  const nlohmann::json & params) : state<Context, nlohmann::json>(name, params){
    }

    virtual void on_entry(Context &, Event) override {
        qDebug() <<  nlohmann::to_string(params);
    }
    // read params to get the distance
    // send goal to path_finder to check if path is ok
    // send command to can


    virtual void on_exit(Context &, Event) override {}
};

struct CollectPoints : public state<Context, nlohmann::json> {
public:
    CollectPoints(const std::string & name,  const nlohmann::json & params) : state<Context, nlohmann::json>(name, params){
    }

    virtual void on_entry(Context &, Event) override {
        qDebug() <<  nlohmann::to_string(params);
    }
    // read params to get the distance
    // send goal to path_finder to check if path is ok
    // send command to can


    virtual void on_exit(Context &, Event) override {}
};

struct HandShake : public state<Context, nlohmann::json> {
public:
    HandShake(const std::string & name,  const nlohmann::json & params) : state<Context, nlohmann::json>(name, params){
    }

    virtual void on_entry(Context &, Event) override {
        qDebug() <<  nlohmann::to_string(params);
    }
    // read params to get the distance
    // send goal to path_finder to check if path is ok
    // send command to can


    virtual void on_exit(Context &, Event) override {}
};

struct SetOdometry : public state<Context, nlohmann::json> {
public:
    SetOdometry(const std::string & name,  const nlohmann::json & params) : state<Context, nlohmann::json>(name, params){
    }

    virtual void on_entry(Context &, Event) override {
        qDebug() <<  nlohmann::to_string(params);
    }
    // read params to get the distance
    // send goal to path_finder to check if path is ok
    // send command to can


    virtual void on_exit(Context &, Event) override {}
};

#endif // COMMONACTIONS_H
