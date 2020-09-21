/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CYLON_SRC_CYLON_CTX_CYLON_CONTEXT_HPP_
#define CYLON_SRC_CYLON_CTX_CYLON_CONTEXT_HPP_

#include <string>
#include "unordered_map"
#include "../net/comm_config.hpp"
#include "../net/communicator.hpp"
#include "memory_pool.hpp"

namespace cylon {

/**
 * The entry point to cylon operations
 */
class CylonContext {
 private:
  std::unordered_map<std::string, std::string> config{};
  bool is_distributed;
  cylon::net::Communicator *communicator{};
  cylon::MemoryPool *memory_pool{};
  int32_t sequence_no = 0;

 public:
  /**
   * Constructor
   * @param distributed <bool>
   */
  explicit CylonContext(bool distributed);

  /**
   * Initializes context
   * @return <cylon::CylonContext*>
   */
  static shared_ptr<CylonContext> Init();

  /**
   * Initializes distributed context
   * @param <cylon::net::CommConfig*> config Configuration to be passed on to the cylon::net::Communicator
   * @return <cylon::CylonContext*>
   */
  static shared_ptr<CylonContext> InitDistributed(net::CommConfig *config);

  /**
   * Completes and closes all operations under the context
   */
  void Finalize();

  /**
   * Adds a configuration
   * @param <std::string> key
   * @param <std::string> value
   */
  void AddConfig(const std::string &key, const std::string &value);

  /**
   * Returns a configuration
   * @param <std::string> key
   * @param <std::string> def Default value
   * @return <std::string> configuration value
   */
  std::string GetConfig(const std::string &key, const std::string &def = "");

  /**
   * Returns the Communicator instance
   * @return <cylon::net::Communicator>
   */
  net::Communicator *GetCommunicator() const;

  /**
   * Sets a Communicator
   * @param <cylon::net::Communicator*> pointer to another communicator
   */
  void setCommunicator(net::Communicator *communicator1);

  /**
   * Sets if distributed
   * @param <bool> distributed
   */
  void setDistributed(bool distributed);

  bool IsDistributed();

  /**
   * Returns the local rank
   * @return rank <int>
   */
  int GetRank();

  /**
   * Returns the world size
   * @return world size <int>
   */
  int GetWorldSize();

  /**
   * Returns the neighbors in the world
   * @param include_self
   * @return a std::vector<int> of ranks
   */
  vector<int> GetNeighbours(bool include_self);

  /**
   * Returns memory pool
   * @return <cylon::MemoryPool>
   */
  cylon::MemoryPool *GetMemoryPool();

  /**
   * Sets a memory pool
   * @param <cylon::MemoryPool> mem_pool
   */
  void SetMemoryPool(cylon::MemoryPool *mem_pool);

  /**
   * Returns the next sequence number
   * @return <int>
   */
  int32_t GetNextSequence();

  /**
   *
   */
  cylon::net::CommType GetCommType();

  /**
   * Performs a barrier operation
   */
  void Barrier() {
    this->GetCommunicator()->Barrier();
  }
};
}

#endif //CYLON_SRC_CYLON_CTX_CYLON_CONTEXT_HPP_
