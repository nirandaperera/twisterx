#ifndef TWISTERX_SRC_TWISTERX_CTX_TWISTERX_CONTEXT_H_
#define TWISTERX_SRC_TWISTERX_CTX_TWISTERX_CONTEXT_H_

#include <string>
#include "unordered_map"
#include "../net/comm_config.h"
#include "../net/communicator.h"

namespace twisterx {
class TwisterXContext {
 private:
  std::unordered_map<std::string, std::string> config{};
  bool distributed;
  twisterx::net::Communicator *communicator{};

  explicit TwisterXContext(bool distributed);

 public:
  static TwisterXContext *Init();
  void Finalize();

  static TwisterXContext *InitDistributed(net::CommConfig *config);
  void AddConfig(const std::string &key, const std::string &value);
  std::string GetConfig(const std::string &key, const std::string &def = "");
  net::Communicator *GetCommunicator() const;
  int GetRank();
  int GetWorldSize();
  vector<int> GetNeighbours(bool include_self);
};
}

#endif //TWISTERX_SRC_TWISTERX_CTX_TWISTERX_CONTEXT_H_
