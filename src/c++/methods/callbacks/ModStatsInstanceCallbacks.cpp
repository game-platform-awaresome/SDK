#include "c++/ModIOInstance.h"

namespace modio
{
std::map<u32, GetModStatsCall *> get_mod_stats_calls;
std::map<u32, GetAllModStatsCall *> get_all_mod_stats_calls;

void onGetModStats(void *object, ModioResponse modio_response, ModioStats modio_stats)
{
  u32 call_id = (u32)((uintptr_t)object);

  modio::Response response;
  response.initialize(modio_response);

  modio::Stats stats;

  if (modio_response.code == 200)
  {
    stats.initialize(modio_stats);
  }

  get_mod_stats_calls[call_id]->callback(response, stats);

  delete get_mod_stats_calls[call_id];
  get_mod_stats_calls.erase(call_id);
}

void onGetAllModStats(void *object, ModioResponse modio_response, ModioStats modio_mods_stats[], u32 modio_mods_stats_size)
{
  u32 call_id = (u32)((uintptr_t)object);

  modio::Response response;
  response.initialize(modio_response);

  std::vector<modio::Stats> mod_stats_vector;
  mod_stats_vector.resize(modio_mods_stats_size);
  for (u32 i = 0; i < modio_mods_stats_size; i++)
  {
    mod_stats_vector[i].initialize(modio_mods_stats[i]);
  }

  get_all_mod_stats_calls[call_id]->callback(response, mod_stats_vector);

  delete get_all_mod_stats_calls[call_id];
  get_all_mod_stats_calls.erase(call_id);
}

void clearModStatsRequestCalls()
{
  for (auto get_mod_stats_call : get_mod_stats_calls)
    delete get_mod_stats_call.second;
  get_mod_stats_calls.clear();

  for (auto get_all_mod_stats_call : get_all_mod_stats_calls)
    delete get_all_mod_stats_call.second;
  get_all_mod_stats_calls.clear();
}
} // namespace modio
