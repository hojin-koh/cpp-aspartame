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
    OptArr(const std::initializer_list<typeValue>& value);
    OptArr(std::initializer_list<typeValue>&& value) noexcept;
    OptArr(const OptArr& rhs);
    OptArr(OptArr&& rhs) noexcept;

    decltype(sizeof(int)) size() const;
    //const T& operator[]( TODO

    void reset();
    void set(const char* value, bool canThrow = true);

    //const typeValue& operator()() const; // explicit version of getting the value, for cases where the implicit conversion doesn't work
    OptArr& operator=(const std::initializer_list<typeValue>& value);
    OptArr& operator=(std::initializer_list<typeValue>&& value) noexcept;
    OptArr& operator=(const OptArr& rhs);
    OptArr& operator=(OptArr&& rhs) noexcept;
  private:
    class Impl; cppcfwv0::PImplS<Impl, SIZE> pimpl;
  };

  // Scalar option - string specialization
  //template <int SIZE>
  //struct Opt<const char*, SIZE> : public IOpt {
  //  using IOpt::IOpt;
  //  using typeValue = const char*;
  //  Opt(const typeValue& value);
  //  Opt(const Opt& rhs);
  //  Opt(Opt&& rhs) noexcept;

  //  void reset();
  //  void set(const char* value, bool canThrow = true);
  //  const typeValue getDefault();

  //  operator typeValue();
  //  operator typeValue() const;
  //  const typeValue operator()() const; // explicit version of getting the value, for cases where the implicit conversion doesn't work
  //  typeValue operator=(const typeValue& value);
  //  typeValue operator=(const Opt& rhs);
  //  typeValue operator=(Opt&& rhs) noexcept;
  //private:
  //  class Impl; cppcfwv0::PImplS<Impl, SIZE> pimpl;
  //};

  //using OptArrInt = OptArr<int64_t, sizeof(int64_t)*2>;
  //using OptArrFloat = OptArr<double, sizeof(double)*2>;
  //using OptArrBool = OptArr<bool, sizeof(bool)*2>;
  using OptArrInt = OptArr<int64_t, 48>;
  using OptArrFloat = OptArr<double, 48>;
  using OptArrBool = OptArr<bool, 80>;
  //using OptStr = Opt<const char*, sizeof(char*)*2>;

}

#define ASPARTAMEV0_OPTARR_IMPL(typeValue, SIZE) \
  template class ::aspartamev0::OptArr<typeValue, SIZE>; \
  template class ::cppcfwv0::PImplS<::aspartamev0::OptArr<typeValue, SIZE>::Impl, SIZE>;