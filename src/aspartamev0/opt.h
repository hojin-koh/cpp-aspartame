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

// Option classes
#pragma once
#include <aspartamev0/itf-opt.h>

#include <cppcfwv0/pimpl.h>

namespace aspartamev0 {

  // Scalar option
  template <typename T>
  struct Opt : public IOptScalar {
    Opt();
    Opt(const T& value);

    void reset();
    const char* getStr() const;
    void setStr(const char* input);

    operator T();
    operator T() const;
    T& operator=(const T& rhs);
    T& operator=(T&& rhs);
  private:
    class Impl; cppcfwv0::PImpl<Impl> pimpl;
  };

}

