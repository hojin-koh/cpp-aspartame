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
#include <aspartamev0/opt.h>

#include <cppcfwv0/pimpl-static-inl.h>
#include <utility>
#include <cstdlib>
#include <string>
#include <stdexcept>

namespace aspartamev0 {

  template <typename T, int SIZE>
  struct Opt<T, SIZE>::Impl {
    Impl() : m_default(T()), m_data(m_default) {}
    Impl(const T& value) : m_default(value), m_data(value) {}

    T m_data;
    const T m_default;

    // Provide assignment operator that shouldn't be called but are needed to compile
    Impl& operator=(const Impl& rhs) {
      m_data = rhs.m_data;
      return *this;
    }
  };

  template <> // string specialization
  struct OptStr::Impl {
    Impl() : m_default(""), m_data("") {}
    Impl(const char* value) : m_default("RRR"), m_data("RRR") {}

    std::string m_data;
    const std::string m_default;

    // Provide assignment operator that shouldn't be called but are needed to compile
    Impl& operator=(const Impl& rhs) {
      m_data = rhs.m_data;
      return *this;
    }
  };

  template <typename T, int SIZE>
  Opt<T,SIZE>::Opt(const T& value) : pimpl(value) {}

  template <typename T, int SIZE>
  Opt<T,SIZE>::Opt(T&& value) noexcept : pimpl(std::move(value)) {}

  template <typename T, int SIZE>
  Opt<T,SIZE>::Opt(const Opt<T,SIZE>& rhs) : pimpl(rhs.pimpl) {}

  template <typename T, int SIZE>
  Opt<T,SIZE>::Opt(Opt<T,SIZE>&& rhs) noexcept : pimpl(std::move(rhs.pimpl)) {}

  template <typename T, int SIZE>
  Opt<T,SIZE>::operator T() {
    return pimpl->m_data;
  }

  template <typename T, int SIZE>
  Opt<T,SIZE>::operator T() const {
    return pimpl->m_data;
  }

  template <typename T, int SIZE>
  const T& Opt<T,SIZE>::operator()() const {
    return pimpl->m_data;
  }

  template <typename T, int SIZE>
  T& Opt<T,SIZE>::operator=(const T& value) {
    m_changed = true;
    return (pimpl->m_data = value);
  }

  template <typename T, int SIZE>
  T& Opt<T,SIZE>::operator=(T&& value) noexcept {
    m_changed = true;
    return (pimpl->m_data = std::move(value));
  }

  template <typename T, int SIZE>
  T& Opt<T,SIZE>::operator=(const Opt<T,SIZE>& rhs) {
    m_changed = true;
    return (pimpl->m_data = rhs.pimpl->m_data);
  }

  template <typename T, int SIZE>
  T& Opt<T,SIZE>::operator=(Opt<T,SIZE>&& rhs) noexcept {
    m_changed = true;
    return (pimpl->m_data = std::move(rhs.pimpl->m_data));
  }

  template <typename T, int SIZE>
  void Opt<T,SIZE>::reset() {
    m_changed = false;
    pimpl->m_data = pimpl->m_default;
  }

  template <typename T, int SIZE>
  const T& Opt<T,SIZE>::getDefault() {
    return pimpl->m_default;
  }

  template <> // int specialization
  void OptInt::set(const char* value, bool canThrow) {
    if (value == nullptr) throw std::domain_error("Encountered null pointer when trying to parse into an integer");
    char* ptrEnd;
    typeValue rslt = std::strtoll(value, &ptrEnd, 0);
    if (ptrEnd == value && canThrow) { // no valid things are parsed
      throw std::domain_error(std::string("String '") + value + "' is not a valid integer.");
    }
    pimpl->m_data = rslt;
  }

  template <> // float specialization
  void OptFloat::set(const char* value, bool canThrow) {
    if (value == nullptr) throw std::domain_error("Encountered null pointer when trying to parse into a number");
    char* ptrEnd;
    typeValue rslt = std::strtold(value, &ptrEnd);
    if (ptrEnd == value && canThrow) { // no valid things are parsed
      throw std::domain_error(std::string("String '") + value + "' is not a valid number.");
    }
    pimpl->m_data = rslt;
  }

  template <> // bool specialization
  void OptBool::set(const char* value, bool canThrow) {
    if (value == nullptr) throw std::domain_error("Encountered null pointer when trying to parse into a boolean value");
    while (std::isspace(value[0])) ++value;
    if (value[0] == 't' || value[0] == 'T' || value[0] == 'y' || value[0] == 'Y' || value[0] == 'o' || value[0] == 'O' || value[0] == 'v' || value[0] == 'V') {
      pimpl->m_data = true;
    } else if (value[0] == 'f' || value[0] == 'F' || value[0] == 'n' || value[0] == 'N' || value[0] == 'x' || value[0] == 'X') {
      pimpl->m_data = false;
    } else if (canThrow) {
      throw std::domain_error(std::string("String '") + value + "' is not a valid boolean value.");
    } else {
      pimpl->m_data = false;
    }
  }

  // ==== String Specizliation below ==== //


  template <>
  OptStr::operator const char*() {
    return pimpl->m_data.c_str();
  }

  template <>
  OptStr::operator const char*() const {
    return pimpl->m_data.c_str();
  }

  template<>
  const char* const OptStr::operator()() const {
    return pimpl->m_data.c_str();
  }

  template <>
  const char* OptStr::operator=(const char* const& value) {
    m_changed = true;
    return (pimpl->m_data = value).c_str();
  }

  template <>
  const char* OptStr::operator=(const OptStr& rhs) {
    m_changed = true;
    return (pimpl->m_data = rhs.pimpl->m_data).c_str();
  }

  template <>
  const char* OptStr::operator=(OptStr&& rhs) noexcept {
    m_changed = true;
    return (pimpl->m_data = std::move(rhs.pimpl->m_data)).c_str();
  }

  template <>
  const char* const OptStr::getDefault() {
    return pimpl->m_default.c_str();
  }

  template <> // string specialization
  void OptStr::set(const char* value, bool canThrow) {
    if (value == nullptr) throw std::domain_error("Encountered null pointer when trying to parse into a boolean value");
    pimpl->m_data = value;
  }

}

ASPARTAMEV0_OPT_IMPL(int64_t, 16);
ASPARTAMEV0_OPT_IMPL(double, 16);
ASPARTAMEV0_OPT_IMPL(bool, 2);
ASPARTAMEV0_OPT_IMPL(const char*, 16);
