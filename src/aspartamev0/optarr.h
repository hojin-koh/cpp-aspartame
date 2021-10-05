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

// Option classes - array version
#pragma once
#include <aspartamev0/itf-opt.h>

#include <cppcfwv0/pimpl-static.h>
#include <cstdint>
#include <initializer_list>

namespace aspartamev0 {

  // Array option
  template <typename T, int SIZE>
  struct OptArr : public IOpt {
    using IOpt::IOpt;
    using typeValue = T;
    OptArr();
    OptArr(const std::initializer_list<typeValue> value);
    OptArr(const OptArr& rhs);
    OptArr(OptArr&& rhs) noexcept;

    decltype(sizeof(int)) size() const;
    T& operator[](int64_t pos);
    const T operator[](int64_t pos) const; // Indexing is read-only

    void clear();
    void reset();
    void set(int64_t pos, const char* value, bool canThrow = true);

    OptArr& operator=(std::initializer_list<typeValue> value);
    OptArr& operator=(const OptArr& rhs);
    OptArr& operator=(OptArr&& rhs) noexcept;
  private:
    class Impl; cppcfwv0::PImplS<Impl, SIZE> pimpl;
  };

  using OptArrInt = OptArr<int64_t, 160>;
  using OptArrFloat = OptArr<double, 160>;
  using OptArrBool = OptArr<bool, 160>;
  //using OptStr = Opt<const char*, sizeof(char*)*2>;

}

#define ASPARTAMEV0_OPTARR_IMPL(typeValue, SIZE) \
  template class ::aspartamev0::OptArr<typeValue, SIZE>; \
  template class ::cppcfwv0::PImplS<::aspartamev0::OptArr<typeValue, SIZE>::Impl, SIZE>;
