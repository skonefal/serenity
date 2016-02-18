#include "signal_filter.hpp"

namespace mesos {
namespace serenity {

  void SignalFilter::allProductsReady() {
    Option<ResourceUsage> consumable = Consumer<ResourceUsage>::getConsumable();
    if (consumable.isNone()) {
      SERENITY_LOG(ERROR) << "Resource Usage is empty";
      produce(ResourceUsage());
      return;
    }
    ResourceUsage usage = consumable.get();

//    for (ResourceUsage_Executor executor : usage.mutable_executors()) {
//      ResourceStatistics* statistics = executor.mutable_statistics();
//      executor.sta
//    }

    return;
  }

//  ResourceStatistics& SignalFilter::filterStatistics(
//      ResourceStatistics& _statistics) {
//    for (const SignalAccessor& accessor : metrics) {
//      Try<double_t> metric = accessor.getter(_statistics);
//      if (metric.isError()) {
//        SERENITY_LOG(WARNING) << "Metric getter returned: " << metric.error();
//        return _statistics;
//      }
//
////      accessor.setter(_statistics, metric);
//    }
//    return _statistics;
//  }

  void SignalFilter::initialize() {
    tag = Tag(NAME);
  }

}  // namespace serenity
}  // namespace mesos
