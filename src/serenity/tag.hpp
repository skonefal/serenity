#ifndef SERENITY_TAG_HPP
#define SERENITY_TAG_HPP

namespace mesos {
namespace serenity {

enum ModuleType {
  RESOURCE_ESTIMATOR,
  QOS_CONTROLLER,
  UNDEFINED,
};


class Tag {
public:
  Tag() : type(ModuleType::UNDEFINED),
          name("UndefinedTag") {}

  Tag(const ModuleType& _type, const std::string& _name)
      : type(_type) {
    this->name = getPrefix() + ": ";
  }

  explicit Tag(const std::string& _name)
      : type(UNDEFINED) {
    std::string prefix = getPrefix();
    this->name = prefix + _name + ": ";
  }

  const inline std::string NAME() const {
    return name;
  }

  const inline ModuleType TYPE() const {
    return type;
  }

  friend std::ostream& operator<<(std::ostream& out, const Tag& tag) {
    out << tag.name << ": ";
    return out;
  }

private:
  const std::string getPrefix() {
    std::string prefix;
    switch (this->type) {
      case RESOURCE_ESTIMATOR:
        prefix = "[SerenityEstimator] ";
        break;
      case QOS_CONTROLLER:
        prefix = "[SerenityQoS] ";
        break;
      default:
        prefix = "[Serenity] ";
        break;
    }

    return prefix;
  }

  ModuleType type;
  std::string name;
};

}  // namespace serenity
}  // namespace mesos

#endif  // SERENITY_TAG_HPP
