//
// Copyright (C) 2022 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "host/commands/cvd/unittests/selector/selector_parser_substring_test_helper.h"

namespace cuttlefish {
namespace selector {

TEST_P(SubstringTest, Substring) {
  ASSERT_EQ((parser_ != std::nullopt), expected_result_);
}

INSTANTIATE_TEST_SUITE_P(
    CvdParser, SubstringTest,
    testing::Values(SubstringTestInput{"--name cvd", true},
                    SubstringTestInput{"--name cvd cv", true},
                    SubstringTestInput{"--name cvd c v", true},
                    SubstringTestInput{"--name cvd c,v,d", true},
                    SubstringTestInput{"--name cvd c v,d", true},
                    SubstringTestInput{"--name cvd c", true},
                    SubstringTestInput{"c v --name cvd d", true},
                    SubstringTestInput{"c --name cvd v", true},
                    SubstringTestInput{"--name cvd c,", false},
                    SubstringTestInput{"--name cvd c v,,d", false}));

}  // namespace selector
}  // namespace cuttlefish