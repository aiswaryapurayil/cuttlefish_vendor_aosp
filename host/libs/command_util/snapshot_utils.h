/*
 * Copyright (C) 2023 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <string>

#include "common/libs/utils/result.h"
#include "host/libs/config/cuttlefish_config.h"

namespace cuttlefish {

/*
 * Copy recursively from src_dir_path to dest_dir_path as long as
 * the predicate function returns true
 */
Result<void> CopyDirectoryRecursively(const std::string& src_dir_path,
                                      const std::string& dest_dir_path,
                                      const bool verify_dest_dir_empty = false);

Result<Json::Value> CreateMetaInfo(const CuttlefishConfig& config,
                                   const std::string& snapshot_path);

std::string SnapshotMetaJsonPath(const std::string& snapshot_path);

inline constexpr const char kMetaInfoJsonFileName[] = "snapshot_meta_info.json";
inline constexpr const char kGuestSnapshotField[] = "guest_snapshot";
inline constexpr const char kSnapshotPathField[] = "snapshot_path";
inline constexpr const char kCfHomeField[] = "HOME";

}  // namespace cuttlefish
