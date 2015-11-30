/*  Copyright 2012 MaidSafe.net limited

    This MaidSafe Software is licensed to you under (1) the MaidSafe.net Commercial License,
    version 1.0 or later, or (2) The General Public License (GPL), version 3, depending on which
    licence you accepted on initial access to the Software (the "Licences").

    By contributing code to the MaidSafe Software, or to this project generally, you agree to be
    bound by the terms of the MaidSafe Contributor Agreement, version 1.0, found in the root
    directory of this project at LICENSE, COPYING and CONTRIBUTOR respectively and also
    available at: http://www.maidsafe.net/licenses

    Unless required by applicable law or agreed to in writing, the MaidSafe Software distributed
    under the GPL Licence is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS
    OF ANY KIND, either express or implied.

    See the Licences for the specific language governing permissions and limitations relating to
    use of the MaidSafe Software.                                                                 */

#ifndef MAIDSAFE_COMMON_ACTIVE_H_
#define MAIDSAFE_COMMON_ACTIVE_H_

#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>

namespace maidsafe {

class Active {
 public:
  typedef std::function<void()> Functor;
  Active();
  ~Active();
  void Send(Functor functor);

 private:
  Active(const Active&);
  Active& operator=(const Active&);
  void Run();
  // FIXME this should be atomic<bool> but clang is violently complaining !!
  bool running_;
  std::queue<Functor> functors_;
  std::mutex flags_mutex_, mutex_;
  std::condition_variable condition_;
  std::thread thread_;
};

}  // namespace maidsafe

#endif  // MAIDSAFE_COMMON_ACTIVE_H_
