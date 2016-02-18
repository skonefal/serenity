#include <gtest/gtest.h>

#include "mesos/resources.hpp"
#include "filters/signal_filter.hpp"
#include "filters/signal_filter/signal_accessor_factory.hpp"

namespace mesos {
namespace serenity {
namespace tests {

TEST(MetricFilterTest, Basic) {
//  SignalAccessor metric;
//  ResourceUsage_Executor executor;
//  PerfStatistics perf;
//  ResourceStatistics stats;
//
//
//  std::function<Try<double_t>(ResourceStatistics&)> getterLambda = [](ResourceStatistics& stats) -> Try<double_t> { return stats.perf().instructions(); };
//
//
//  double_t newValue = 2.0;
//  std::function<Try<Nothing>(ResourceStatistics&, double)> setterLambda =
//      [](ResourceStatistics& stats, double value) -> Try<Nothing>{
//        uint64_t val = 22;
//        stats.mutable_perf()->set_instructions(val);
//        return Nothing(); };


//  metric.getter = std::bind(&PerfStatistics::instructions, std::placeholders::_1);


//  metric.getter = std::bind(&PerfStatistics::instructions,std::placeholders::_1);

//  metric.getter = &PerfStatistics::instructions;

//  metric.setGetterFunction<PerfStatistics>(&PerfStatistics::instructions);

//  auto wykop = &ResourceUsage_Executor:: ::cpus_user_time_secs;

//  metric.setGetterFunction<ResourceStatistics>(&ResourceStatistics::cpus_user_time_secs);

//  metric.getUint64 = &PerfStatistics::instructions;

  ASSERT_TRUE(true);
}

}  // namespace tests
}  // namespace serenity
}  // namespace mesos
