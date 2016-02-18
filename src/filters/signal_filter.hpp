#ifndef SERENITY_SIGNAL_FILTER_HPP
#define SERENITY_SIGNAL_FILTER_HPP
void initialize();
#include <glog/logging.h>
//#include <functional>

//#include <cmath>
//#include <memory>
//#include <string>
#include <vector>

#include "messages/serenity.hpp"

#include "filters/signal_filter/base_filter_strategy.hpp"
#include "filters/signal_filter/signal_accessor_factory.hpp"

#include "serenity/serenity.hpp"

namespace mesos {
namespace serenity {

class SignalFilter : public Consumer<ResourceUsage>,
                     public Producer<ResourceUsage> {
 public:
  SignalFilter(BaseFilterStrategy& strategyPrototype) {

  }

  ~SignalFilter() {}

  void setFilterStrategy(BaseFilterStrategy& strategy);

  void addMetricToFilter(SignalAccessor metric);

  static constexpr const char* NAME = "SignalFilter";
 protected:
  void allProductsReady() override;

  ResourceStatistics& filterStatistics(ResourceStatistics&);

 private:
  void initialize();

  Tag tag;
  BaseFilterStrategy* strategyPrototype;
  std::vector<SignalAccessor> metrics;
};

}  // namespace serenity
}  // namespace mesos

#endif  // SERENITY_SIGNAL_FILTER_HPP
