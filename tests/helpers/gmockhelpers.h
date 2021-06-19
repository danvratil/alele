// SPDX-FileCopyrightText: 2021 Daniel Vrátil <dvratil@kde.org>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL
//
// Inspired by similar implementation in Facebook's folly library
// https://github.com/facebook/folly

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace ::testing;

namespace testing {

namespace detail {

template<typename T>
class CoReturnImpl {
public:
    explicit CoReturnImpl(T &&value): m_value(std::move(value)) {}

    template<typename Result, typename ArgumentTuple>
    Result Perform(const ArgumentTuple &) const {
        return [](T value) -> Result { co_return value; }(m_value);
    }

private:
    T m_value;
};

} // namespace detail

template<typename T>
auto CoReturn(T ret) {
    return ::testing::MakePolymorphicAction(
            detail::CoReturnImpl<T>(std::move(ret)));
}

template<typename T>
auto CoReturn() {
    return ::testing::InvokeWithoutArgs([]() -> QCoro::Task<> { co_return; });
}

} // namespace testing


#define CO_TEST(test_suite_name, test_name)                                    \
  static_assert(                                                               \
      sizeof(GTEST_STRINGIFY_(test_suite_name)) > 1,                           \
      "test_suite_name must not be empty");                                    \
  static_assert(                                                               \
      sizeof(GTEST_STRINGIFY_(test_name)) > 1, "test_name must not be empty"); \
  class GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)                     \
      : public ::testing::Test {                                               \
   public:                                                                     \
    GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)() = default;            \
    ~GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)() override = default;  \
    GTEST_DISALLOW_COPY_AND_ASSIGN_(                                           \
        GTEST_TEST_CLASS_NAME_(test_suite_name, test_name));                   \
                                                                               \
   private:                                                                    \
    void TestBody() override;                                                  \
    QCoro::Task<> co_TestBody();                                               \
    static ::testing::TestInfo* const test_info_ GTEST_ATTRIBUTE_UNUSED_;      \
  };                                                                           \
                                                                               \
  ::testing::TestInfo* const GTEST_TEST_CLASS_NAME_(                           \
      test_suite_name, test_name)::test_info_ =                                \
      ::testing::internal::MakeAndRegisterTestInfo(                            \
          #test_suite_name,                                                    \
          #test_name,                                                          \
          nullptr,                                                             \
          nullptr,                                                             \
          ::testing::internal::CodeLocation(__FILE__, __LINE__),               \
          ::testing::internal::GetTestTypeId(),                                \
          ::testing::internal::SuiteApiResolver<                               \
              ::testing::Test>::GetSetUpCaseOrSuite(__FILE__, __LINE__),       \
          ::testing::internal::SuiteApiResolver<                               \
              ::testing::Test>::GetTearDownCaseOrSuite(__FILE__, __LINE__),    \
          new ::testing::internal::TestFactoryImpl<GTEST_TEST_CLASS_NAME_(     \
              test_suite_name, test_name)>);                                   \
  void GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::TestBody() {        \
    QCoro::waitFor(co_TestBody());                                             \
  }                                                                            \
  QCoro::Task<> GTEST_TEST_CLASS_NAME_(                                        \
      test_suite_name, test_name)::co_TestBody()

