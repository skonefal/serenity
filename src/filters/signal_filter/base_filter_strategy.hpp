#ifndef SERENITY_BASE_FILTER_STRATEGY_HPP
#define SERENITY_BASE_FILTER_STRATEGY_HPP

namespace mesos {
namespace serenity {

class BaseFilterStrategy {
 public:
  BaseFilterStrategy() {}

  virtual ~BaseFilterStrategy();

  virtual double_t filter() = 0;

  virtual BaseFilterStrategy* clone() = 0;
};

}  // namespace serenity
}  // namespace mesos

#endif  // SERENITY_BASE_FILTER_STRATEGY_HPP
