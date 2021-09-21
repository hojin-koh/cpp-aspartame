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

#include <cppcfwv0/pimpl-static.h>
#include <cstdint>

namespace aspartamev0 {

  // Scalar option
  template <typename T, int SIZE>
  struct Opt : public IOpt {
    using IOpt::IOpt;
    using typeValue = T;
    Opt(const typeValue& value);
    Opt(typeValue&& value) noexcept;
    Opt(const Opt& rhs);
    Opt(Opt&& rhs) noexcept;

    void reset();
    void set(const char* value, bool canThrow = true);
    const typeValue& getDefault();

    operator typeValue();
    operator typeValue() const;
    const typeValue& operator()() const; // explicit version of getting the value, for cases where the implicit conversion doesn't work
    typeValue& operator=(const typeValue& value);
    typeValue& operator=(typeValue&& value) noexcept;
    typeValue& operator=(const Opt& rhs);
    typeValue& operator=(Opt&& rhs) noexcept;
  private:
    class Impl; cppcfwv0::PImplS<Impl, SIZE> pimpl;
  };

  // Scalar option
  template <int SIZE>
  struct Opt<const char*, SIZE> : public IOpt {
    using IOpt::IOpt;
    using typeValue = const char*;
    Opt(const typeValue& value);
    Opt(const Opt& rhs);
    Opt(Opt&& rhs) noexcept;

    void reset();
    void set(const char* value, bool canThrow = true);
    const typeValue getDefault();

    operator typeValue();
    operator typeValue() const;
    const typeValue operator()() const; // explicit version of getting the value, for cases where the implicit conversion doesn't work
    typeValue operator=(const typeValue& value);
    typeValue operator=(const Opt& rhs);
    typeValue operator=(Opt&& rhs) noexcept;
  private:
    class Impl; cppcfwv0::PImplS<Impl, SIZE> pimpl;
  };

  using OptInt = Opt<int64_t, 16>;
  using OptFloat = Opt<double, 16>;
  using OptBool = Opt<bool, 2>;
  using OptStr = Opt<const char*, 16>;

}

#define ASPARTAMEV0_OPT_IMPL(typeValue, SIZE) \
  template class ::aspartamev0::Opt<typeValue, SIZE>; \
  template class ::cppcfwv0::PImplS<::aspartamev0::Opt<typeValue, SIZE>::Impl, SIZE>;
