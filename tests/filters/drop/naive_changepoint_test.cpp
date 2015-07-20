#include <list>
#include <string>

#include "gtest/gtest.h"

#include "stout/gtest.hpp"

#include "filters/drop.hpp"

#include "serenity/data_utils.hpp"

#include "tests/common/load_generator.hpp"

namespace mesos {
namespace serenity {
namespace tests {

using std::string;

/**
 * Check if NaiveChangePointDetector won't detect any change point
 * in stable load.
 */
TEST(NaiveChangePointDetectionTest, StableLoadNoChangePoint) {
  const uint64_t CONTENTION_COOLDOWN = 10;
  const double_t ABS_THRESHOLD = 0;
  const uint64_t LOAD_ITERATIONS = 100;
  NaiveChangePointDetector naiveChangePointDetector;
  naiveChangePointDetector.configure(
      ChangePointDetectionState::createForNaiveDetector(
          CONTENTION_COOLDOWN, ABS_THRESHOLD));

  LoadGenerator loadGen(
      math::constFunction, new ZeroNoise(), LOAD_ITERATIONS);

  for (; loadGen.end() ; loadGen++) {
    Result<ChangePointDetection> result =
      naiveChangePointDetector.processSample((*loadGen)());

    EXPECT_NONE(result);
  }
}


/**
 * Check if NaiveChangePointDetector won't detect any change point
 * in noisy load.
 */
TEST(NaiveChangePointDetectionTest, NoisyLoadNoChangePoint) {
  const uint64_t CONTENTION_COOLDOWN = 10;
  const double_t ABS_THRESHOLD = 0;
  const double_t MAX_NOISE = 9;
  const uint64_t LOAD_ITERATIONS = 100;
  NaiveChangePointDetector naiveChangePointDetector;
  naiveChangePointDetector.configure(
      ChangePointDetectionState::createForNaiveDetector(
          CONTENTION_COOLDOWN, ABS_THRESHOLD));

  LoadGenerator loadGen(
      math::constFunction,
      new SymetricNoiseGenerator(MAX_NOISE),
      LOAD_ITERATIONS);

  for (; loadGen.end() ; loadGen++) {
    Result<ChangePointDetection> result =
        naiveChangePointDetector.processSample((*loadGen)());

    EXPECT_NONE(result);
  }
}


/**
 * Check if NaiveChangePointDetector will detect some contentions
 * in stable load with drop.
 */
TEST(NaiveChangePointDetectionTest, StableLoadOneChangePoint) {
  const uint64_t CONTENTION_COOLDOWN = 10;
  const double_t ABS_THRESHOLD = 0;
  const uint64_t LOAD_ITERATIONS = 200;
  const double_t DROP_PROGRES = 1;
  NaiveChangePointDetector naiveChangePointDetector;
  naiveChangePointDetector.configure(
      ChangePointDetectionState::createForNaiveDetector(
          CONTENTION_COOLDOWN, ABS_THRESHOLD));

  LoadGenerator loadGen(
      math::constFunction, new ZeroNoise(), LOAD_ITERATIONS);
  bool dropped = false;
  int64_t cooldown = -1;
  for (; loadGen.end() ; loadGen++) {
    Result<ChangePointDetection> result =
      naiveChangePointDetector.processSample((*loadGen)());

    if (cooldown >= 0) cooldown--;

    if (dropped && cooldown < 0) {
      cooldown = CONTENTION_COOLDOWN;
      EXPECT_SOME(result);
    } else {
      EXPECT_NONE(result);
    }

    // Introduce a drop in the middle of the test..
    if (loadGen.iteration >= 100 &&
        loadGen.iteration < 150) {
      // After 11 iterations of 1 drop progress value should be below
      // threshold (-1).
      if (loadGen.iteration == 110)
        dropped = true;
      loadGen.modifier -= DROP_PROGRES;
    }
  }
}

}  //  namespace tests
}  //  namespace serenity
}  //  namespace mesos
