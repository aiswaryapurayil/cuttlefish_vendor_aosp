/*
 * Copyright (C) 2022 The Android Open Source Project
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

#include <filesystem>
#include <unordered_map>

#include <android-base/logging.h>
#include <android-base/strings.h>
#include <gflags/gflags.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <test/cpp/util/grpc_tool.h>
#include <test/cpp/util/test_config.h>

#include "common/libs/utils/contains.h"
#include "common/libs/utils/result.h"
#include "host/libs/config/cuttlefish_config.h"

using grpc::InsecureChannelCredentials;

namespace cuttlefish {
namespace {

bool PrintStream(std::stringstream* ss, const grpc::string& output) {
  (*ss) << output;
  return true;
}

class InsecureCliCredentials final : public grpc::testing::CliCredentials {
 public:
  std::shared_ptr<grpc::ChannelCredentials> GetChannelCredentials()
      const override {
    return InsecureChannelCredentials();
  }
  const grpc::string GetCredentialUsage() const override { return ""; }
};

std::vector<char*> ConvertToCharVec(const std::vector<std::string>& str_vec) {
  std::vector<char*> char_vec;
  char_vec.reserve(str_vec.size());
  for (const auto& str : str_vec) {
    char_vec.push_back(const_cast<char*>(str.c_str()));
  }
  return char_vec;
}

void RunGrpcCommand(const std::vector<std::string>& arguments,
                    std::stringstream& output_stream) {
  int grpc_cli_argc = arguments.size();
  auto new_arguments = ConvertToCharVec(arguments);
  char** grpc_cli_argv = new_arguments.data();

  grpc::testing::InitTest(&grpc_cli_argc, &grpc_cli_argv, true);
  grpc::testing::GrpcToolMainLib(
      grpc_cli_argc, (const char**)grpc_cli_argv, InsecureCliCredentials(),
      std::bind(PrintStream, &output_stream, std::placeholders::_1));
}

std::string RunGrpcCommand(const std::vector<std::string>& arguments) {
  std::stringstream output_stream;
  RunGrpcCommand(arguments, output_stream);
  return output_stream.str();
}

std::vector<std::string> GetServiceList(const std::string& server_address) {
  std::vector<std::string> service_list;
  std::stringstream output_stream;

  std::vector<std::string> arguments{"grpc_cli", "ls", server_address};
  RunGrpcCommand(arguments, output_stream);

  std::string service_name;
  while (std::getline(output_stream, service_name)) {
    if (service_name.compare("grpc.reflection.v1alpha.ServerReflection") == 0) {
      continue;
    }
    service_list.emplace_back(service_name);
  }

  return service_list;
}

Result<std::string> GetServerAddress(
    const std::vector<std::string>& server_address_list,
    const std::string& service_name) {
  std::vector<std::string> candidates;
  for (const auto& server_address : server_address_list) {
    for (auto& full_service_name : GetServiceList(server_address)) {
      if (android::base::EndsWith(full_service_name, service_name)) {
        candidates.emplace_back(server_address);
        break;
      }
    }
  }

  CF_EXPECT(candidates.size() > 0, service_name + " is not found.");
  CF_EXPECT(candidates.size() < 2, service_name + " is ambiguous.");

  return candidates[0];
}

Result<std::string> GetFullServiceName(const std::string& server_address,
                                       const std::string& service_name) {
  std::vector<std::string> candidates;
  for (auto& full_service_name : GetServiceList(server_address)) {
    if (android::base::EndsWith(full_service_name, service_name)) {
      candidates.emplace_back(full_service_name);
    }
  }

  CF_EXPECT(candidates.size() > 0, service_name + " is not found.");
  CF_EXPECT(candidates.size() < 2, service_name + " is ambiguous.");

  return candidates[0];
}

Result<std::string> GetFullMethodName(const std::string& server_address,
                                      const std::string& service_name,
                                      const std::string& method_name) {
  const auto& full_service_name =
      CF_EXPECT(GetFullServiceName(server_address, service_name));
  return full_service_name + "/" + method_name;
}

Result<void> HandleLsCmd(const std::vector<std::string>& server_address_list,
                         const std::vector<std::string>& args,
                         const std::vector<std::string>& options) {
  CF_EXPECT(args.size() < 3, "too many arguments");

  if (args.size() > 0) {
    std::vector<std::string> grpc_arguments{"grpc_cli", "ls"};

    const auto& service_name = args[0];
    const auto& server_address =
        CF_EXPECT(GetServerAddress(server_address_list, service_name));
    grpc_arguments.push_back(server_address);
    if (args.size() > 1) {
      // ls subcommand with 2 arguments; service_name and method_name
      const auto& method_name = args[1];
      const auto& full_method_name = CF_EXPECT(
          GetFullMethodName(server_address, service_name, method_name));
      grpc_arguments.push_back(full_method_name);
    } else {
      // ls subcommand with 1 argument; service_name
      const auto& full_service_name =
          CF_EXPECT(GetFullServiceName(server_address, service_name));
      grpc_arguments.push_back(full_service_name);
    }
    grpc_arguments.insert(grpc_arguments.end(), options.begin(), options.end());

    std::cout << RunGrpcCommand(grpc_arguments);
  } else {
    // ls subcommand with no arguments
    for (const auto& server_address : server_address_list) {
      std::vector<std::string> grpc_arguments{"grpc_cli", "ls", server_address};
      grpc_arguments.insert(grpc_arguments.end(), options.begin(),
                            options.end());

      std::cout << RunGrpcCommand(grpc_arguments);
    }
  }

  return {};
}

Result<void> HandleTypeCmd(const std::vector<std::string>& server_address_list,
                           const std::vector<std::string>& args,
                           const std::vector<std::string>& options) {
  // TODO(b/264201498)
  LOG(INFO) << "TODO(b/264201498)";
  return {};
}

Result<void> HandleCallCmd(const std::vector<std::string>& server_address_list,
                           const std::vector<std::string>& args,
                           const std::vector<std::string>& options) {
  CF_EXPECT(args.size() > 2,
            "need to specify a service name, a method name, and text-formatted "
            "proto");
  CF_EXPECT(args.size() < 4, "too many arguments");

  std::vector<std::string> grpc_arguments{"grpc_cli", "call"};
  // TODO(b/265384449): support the case without text-formatted proto.
  const auto& service_name = args[0];
  const auto& method_name = args[1];
  const auto& proto_text_format = args[2];

  const auto& server_address =
      CF_EXPECT(GetServerAddress(server_address_list, service_name));
  grpc_arguments.push_back(server_address);
  const auto& full_method_name =
      CF_EXPECT(GetFullMethodName(server_address, service_name, method_name));
  grpc_arguments.push_back(full_method_name);
  grpc_arguments.push_back(proto_text_format);

  grpc_arguments.insert(grpc_arguments.end(), options.begin(), options.end());

  std::cout << RunGrpcCommand(grpc_arguments);

  return {};
}

Result<void> CvdEnvMain(int argc, char** argv) {
  ::android::base::InitLogging(argv, android::base::StderrLogger);
  CF_EXPECT(argc >= 3, " need to specify a receiver and a command");

  const auto& receiver = argv[1];
  const auto& cmd = argv[2];

  std::vector<std::string> options;
  std::vector<std::string> args;
  for (int i = 3; i < argc; i++) {
    if (android::base::StartsWith(argv[i], '-')) {
      options.push_back(argv[i]);
    } else {
      args.push_back(argv[i]);
    }
  }

  const auto* config = CuttlefishConfig::Get();
  CF_EXPECT(config != nullptr, "Unable to find the config");
  std::vector<std::string> server_address_list;
  const auto& instances = config->Instances();
  auto receiver_instance = std::find_if(
      begin(instances), end(instances), [&receiver](const auto& instance) {
        return receiver == instance.instance_name();
      });

  CF_EXPECT(receiver_instance != std::end(instances),
            "there is no instance of which name is "
                << receiver << ". please check instance name by cvd fleet");

  for (const auto& entry : std::filesystem::directory_iterator(
           receiver_instance->grpc_socket_path())) {
    LOG(DEBUG) << "loading " << entry.path();
    server_address_list.emplace_back("unix:" + entry.path().string());
  }

  auto command_map =
      std::unordered_map<std::string, std::function<Result<void>(
                                          const std::vector<std::string>&,
                                          const std::vector<std::string>&,
                                          const std::vector<std::string>&)>>{{
          {"call", HandleCallCmd},
          {"ls", HandleLsCmd},
          {"type", HandleTypeCmd},
      }};

  CF_EXPECT(Contains(command_map, cmd), cmd << " isn't supported");

  CF_EXPECT(command_map[cmd](server_address_list, args, options));

  return {};
}

}  // namespace
}  // namespace cuttlefish

int main(int argc, char** argv) {
  const auto& ret = cuttlefish::CvdEnvMain(argc, argv);
  CHECK(ret.ok()) << ret.error().Message();
  return 0;
}
