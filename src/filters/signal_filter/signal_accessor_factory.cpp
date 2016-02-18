#include "signal_accessor_factory.hpp"

namespace mesos {
namespace serenity {

  Try<SignalAccessor> SignalAccessorFactory::make(Signal signal) {
    return SignalAccessor();
  }

  SignalAccessor SignalAccessorFactory::makeInstructions() {
    return SignalAccessor();
  }
  SignalAccessor SignalAccessorFactory::makeCycles() {
    return SignalAccessor();
  }
  SignalAccessor SignalAccessorFactory::makeCpuSystemTime() {
    return SignalAccessor();
  }
  SignalAccessor SignalAccessorFactory::makeCpuUserTime() {
    return SignalAccessor();
  }

}  // namespace serenity
}  // namespace mesos
