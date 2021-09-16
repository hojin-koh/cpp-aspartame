/*
 * Copyright 2020-2021, Hojin Koh
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

// Option interfaces
#pragma once

namespace aspartamev0 {

  // Basic interface for all options
  struct IOpt {
    bool isChanged() const { return m_changed; }
    void reset() = 0;

    IOpt() = default;
    // No copy or move for options
    IOpt(IOpt&& rhs) noexcept = delete;
    IOpt& operator=(IOpt&& rhs) noexcept = delete;
    IOpt(const IOpt& rhs) = delete;
    IOpt& operator=(const IOpt& rhs) = delete;
  protected:
    ~IOpt() = default; // To prevent polymorphic use
    bool m_changed {false};
  };

  struct IOptScalar : public IOpt {
    using IOpt::IOpt;
    const char* getStr() const = 0;
    void setStr(const char* input) = 0;
  };

}

