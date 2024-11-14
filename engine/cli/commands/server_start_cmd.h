#pragma once

#include <optional>
#include <string>
#include "utils/curl_utils.h"
#include "utils/url_parser.h"

namespace commands {

inline bool IsServerAlive(const std::string& host, int port) {
  auto url = url_parser::Url{
      .protocol = "http",
      .host = host + ":" + std::to_string(port),
      .pathParams = {"healthz"},
  };
  auto res = curl_utils::SimpleGetJson(url.ToFullPath());
  if (res.has_value()) {
    return true;
  }
  return false;
}

class ServerStartCmd {
 public:
  bool Exec(const std::string& host, int port,
            const std::optional<std::string>& log_level = std::nullopt);
};
}  // namespace commands
