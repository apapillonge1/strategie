#include "strategies.h"

Context ctx{.colorside = true};

auto stm = make_stm_from_json<action_factory<Context>>(ctx, "strategy", "../strats"); //<action_factory<context_vrac>>(ctx, "strat_name", "strat_directory");
auto manager = new strategyManager(stm);
