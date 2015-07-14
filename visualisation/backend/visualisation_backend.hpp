#ifndef SERENITY_VISUALISATION_BACKEND_HPP
#define SERENITY_VISUALISATION_BACKEND_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "boost/variant.hpp"

#include "stout/nothing.hpp"
#include "stout/try.hpp"

namespace mesos {
namespace serenity {

enum class VisualisationBackend {
  INFLUX_DB_8
};


/**
 * Enum of data series names
 */
enum class Series : uint8_t {
  SLACK_RESOURCES,
  CPU_USAGE_SYS,
  CPU_USAGE_USR,
  CPU_ALLOC,
  IPC,
};

static std::string SeriesString(Series series) {
  switch (series) {
    case Series::SLACK_RESOURCES: return "SlackResources";
    case Series::CPU_USAGE_SYS:   return "CpuUsageSys";
    case Series::CPU_USAGE_USR:   return "CpuUsageUsr";
    case Series::CPU_ALLOC:       return "CpuAllocation";
    case Series::IPC:             return "Ipc";
  }
}


/**
 * Enum of commonly used column names for storing serenity data
 */
enum class Tag : uint8_t {
  EXECUTOR_ID,
  FRAMEWORK_ID,
  NODE,
  TAG,
  VALUE,
};

static std::string TagString(Tag tag) {
  switch (tag) {
    case Tag::EXECUTOR_ID:  return "ExecutorId";
    case Tag::FRAMEWORK_ID: return "FrameworkId";
    case Tag::NODE:         return "Node";
    case Tag::TAG:          return "Tag";
    case Tag::VALUE:        return "Value";
  }
}

using Variant = boost::variant<int32_t, double_t, std::string>;

/**
 * Record to be stored in visualisation backend
 */
class VisualisationRecord {
 public:
  VisualisationRecord(const Series _series,
                      const double_t _timestamp,
                      const Variant _variant = 0.0) :
      seriesName(SeriesString(_series)),
      timestamp(_timestamp),
      tags(std::unordered_map<std::string,
           boost::variant<int32_t, double_t, std::string>>()) {
    setTag(Tag::VALUE, _variant);
  }


  double_t getTimestamp() const {
    return this->timestamp;
  }


  std::string getSeriesName() const {
    return this->seriesName;
  }


  const std::unordered_map<std::string,
      boost::variant<int32_t, double_t, std::string>>& getTags() const {
    return this->tags;
  }


  /**
   * Set column value in database
   * Key is std::string
   * Value accepts <int32_t, double_t, std::string>
   */
  template <typename T>
  void inline setTag(const std::string& tag, const T& val) {
    tags[tag] = val;
  }


  /**
   * Set column value in database
   * Key is one of commonly used tags
   * Value accepts <int32_t, double_t, std::string>
   */
  template <typename T>
  void inline setTag(const Tag tag, const T& val) {
    tags[TagString(tag)] = val;
  }


 /**
  * Variant types inside tags map.
  * Used for preparing json
  */
  enum class VariantType : uint8_t{
    INT32,
    DOUBLE,
    STRING,
  };


  static bool IsVariantString(Variant _variant) {
    return _variant.which() == static_cast<uint8_t>(VariantType::STRING);
  }

 protected:
  /**
   * String with tags that will be added to database
   * It's string->string, and not tag->string for purpose
   * of adding custom tags.
   */
  std::unordered_map<std::string, Variant> tags;

  const std::string seriesName;  //!< Series name in backend.
  const double_t    timestamp;
};


/**
 * Visualisation backend interface.
 */
class IVisualisationBackend {
 public:
  virtual void PutMetric(const VisualisationRecord& _visualisationRecord) = 0;


  virtual void PutMetric(const std::vector<VisualisationRecord>& _recordList){
    for (const auto& record : _recordList) {
      this->PutMetric(record);
    }
  }
};

}  // namespace serenity
}  // namespace mesos

#endif  // SERENITY_VISUALISATION_BACKEND_HPP
