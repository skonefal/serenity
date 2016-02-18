#ifndef SERENITY_SIGNAL_ACCESSOR_FACTORY_HPP
#define SERENITY_SIGNAL_ACCESSOR_FACTORY_HPP

#include "mesos/resources.hpp"

#include "stout/nothing.hpp"
#include "stout/try.hpp"

namespace mesos {
namespace serenity {

struct SignalAccessor {
  std::function<Try<double_t>(ResourceStatistics&)> getter;
  std::function<Try<Nothing>(ResourceStatistics&, double)> setter;
};

enum class Signal {
  INSTRUCTIONS,
  CYCLES,
  CPU_SYSTEM_TIME,
  CPU_USER_TIME
};

class SignalAccessorFactory {
 public:
  static Try<SignalAccessor> make(Signal signal);

 private:
  SignalAccessor makeInstructions();
  SignalAccessor makeCycles();
  SignalAccessor makeCpuSystemTime();
  SignalAccessor makeCpuUserTime();
};

}  // namespace serenity
}  // namespace mesos

#endif  // SERENITY_SIGNAL_ACCESSOR_FACTORY_HPP
