/*
 * Copyright (c) 2014, Hewlett-Packard Development Company, LP.
 * The license and distribution terms for this file are placed in LICENSE.txt.
 */
#ifndef FOEDUS_THREAD_THREAD_REF_HPP_
#define FOEDUS_THREAD_THREAD_REF_HPP_

#include <vector>

#include "foedus/cxx11.hpp"
#include "foedus/fwd.hpp"
#include "foedus/thread/fwd.hpp"
#include "foedus/thread/thread_id.hpp"
#include "foedus/xct/fwd.hpp"

namespace foedus {
namespace thread {
/**
 * @brief A view of Thread object for other SOCs and master engine.
 * @ingroup THREAD
 */
class ThreadRef CXX11_FINAL {
 public:
  ThreadRef();
  ThreadRef(Engine* engine, ThreadId id);

  /**
   * Conditionally try to occupy this thread, or impersonate. If it fails, it immediately returns.
   * @param[in] session the session to run on this thread
   * @return whether successfully impersonated.
   */
  bool          try_impersonate(ImpersonateSession *session);
  Engine*       get_engine() const { return engine_; }
  ThreadId      get_thread_id() const { return id_; }
  ThreadGroupId get_numa_node() const { return decompose_numa_node(id_); }
  xct::McsBlock* get_mcs_blocks() const { return mcs_blocks_; }
  ThreadControlBlock* get_control_block() const { return control_block_; }

 private:
  Engine*               engine_;

  /** Unique ID of this thread. */
  ThreadId              id_;

  ThreadControlBlock*   control_block_;

  /** Pre-allocated MCS blocks. index 0 is not used so that successor_block=0 means null. */
  xct::McsBlock*        mcs_blocks_;
};


/**
 * @brief A view of Thread group object for other SOCs and master engine.
 * @ingroup THREAD
 */
class ThreadGroupRef CXX11_FINAL {
 public:
  ThreadGroupRef();
  ThreadGroupRef(Engine* engine, ThreadGroupId group_id);

  ThreadGroupId           get_group_id() const { return group_id_; }

  /** Returns Thread object for the given ordinal in this group. */
  ThreadRef*              get_thread(ThreadLocalOrdinal ordinal) { return &threads_[ordinal]; }

 private:
  Engine*                 engine_;
  ThreadGroupId           group_id_;
  std::vector<ThreadRef>  threads_;
};


}  // namespace thread
}  // namespace foedus
#endif  // FOEDUS_THREAD_THREAD_REF_HPP_
