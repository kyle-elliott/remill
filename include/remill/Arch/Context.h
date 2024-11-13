/*
 * Copyright (c) 2022 Trail of Bits, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#pragma once


#include <stdint.h>

#include <string>
#include <functional>
#include <map>
#include <string_view>

namespace remill {

using ContextValues = std::map<std::string, uint64_t>;

/// A decoding context is contextual information about the state of the program that affects decoding, ie. the thumb mode register on ARM
/// We allow clients to interpose on a context for resolution

/// We return a function of successor -> DecodingContext. The decoder defines a relation on the
/// previous context and the successor address that produces a new decoding.
/// This definition of returned contexts allows us to cleanly handle situations like indirect jumps in arm
///
class DecodingContext {

 private:
  ContextValues context_value;

 public:
  bool operator==(const DecodingContext &rhs) const;

  DecodingContext() = default;

  DecodingContext(ContextValues context_value);


  void UpdateContextReg(std::string creg, uint64_t value);
  void DropReg(const std::string &creg);

  bool HasValueForReg(const std::string &creg) const;


  uint64_t GetContextValue(const std::string &context_reg) const;
  DecodingContext PutContextReg(std::string creg, uint64_t value) const;
  DecodingContext ContextWithoutRegister(const std::string &creg) const;

  const ContextValues &GetContextValues() const;
};

}  // namespace remill
