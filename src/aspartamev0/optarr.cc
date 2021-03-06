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
#include <aspartamev0/optarr.h>

#include <cppcfwv0/pimpl-static-inl.h>
#include <utility>
#include <deque>
//#include <string>
//#include <cstdlib>
//#include <stdexcept>

namespace aspartamev0 {

  template <typename T, int SIZE>
  struct OptArr<T, SIZE>::Impl {
    Impl() {}
    Impl(const std::initializer_list<T>& value) : m_default(value), m_data(value) {};

    // Use deque here to avoid the annoying vector<bool> specialization
    const std::deque<T> m_default;
    std::deque<T> m_data;

    // Provide assignment operator that shouldn't be called but are needed to compile
    Impl& operator=(const Impl& rhs) {
      m_data = rhs.m_data;
      return *this;
    }
  };

  template <typename T, int SIZE>
  OptArr<T,SIZE>::OptArr() : pimpl() {}

  template <typename T, int SIZE>
  OptArr<T,SIZE>::OptArr(const std::initializer_list<T> value) : pimpl(value) {}

  template <typename T, int SIZE>
  OptArr<T,SIZE>::OptArr(const OptArr<T,SIZE>& rhs) : pimpl(rhs.pimpl) {}

  template <typename T, int SIZE>
  OptArr<T,SIZE>::OptArr(OptArr<T,SIZE>&& rhs) noexcept : pimpl(std::move(rhs.pimpl)) {}


  template <typename T, int SIZE>
  decltype(sizeof(int)) OptArr<T,SIZE>::size() const {
    return pimpl->m_data.size();
  }

  template <typename T, int SIZE>
  T& OptArr<T,SIZE>::operator[](int64_t pos) {
    if (pos < 0) {
      return pimpl->m_data.at(size()+pos);
    } else {
      return pimpl->m_data.at(pos);
    }
  }

  template <typename T, int SIZE>
  const T OptArr<T,SIZE>::operator[](int64_t pos) const {
    if (pos < 0) {
      return pimpl->m_data.at(size()+pos);
    } else {
      return pimpl->m_data.at(pos);
    }
  }


  template <typename T, int SIZE>
  void OptArr<T,SIZE>::clear() {
    pimpl->m_data.clear();
  }

  template <typename T, int SIZE>
  void OptArr<T,SIZE>::reset() {
    pimpl->m_data = pimpl->m_default;
  }



  //template <typename T, int SIZE>
  //T& Opt<T,SIZE>::operator=(const T& value) {
  //  return (pimpl->m_data = value);
  //}

  //template <typename T, int SIZE>
  //T& Opt<T,SIZE>::operator=(T&& value) noexcept {
  //  return (pimpl->m_data = std::move(value));
  //}

  //template <typename T, int SIZE>
  //T& Opt<T,SIZE>::operator=(const Opt<T,SIZE>& rhs) {
  //  return (pimpl->m_data = rhs.pimpl->m_data);
  //}

  //template <typename T, int SIZE>
  //T& Opt<T,SIZE>::operator=(Opt<T,SIZE>&& rhs) noexcept {
  //  return (pimpl->m_data = std::move(rhs.pimpl->m_data));
  //}

  //template <typename T, int SIZE>
  //const T& Opt<T,SIZE>::getDefault() {
  //  return pimpl->m_default;
  //}

  //template <> // int specialization
  //void OptInt::set(const char* value, bool canThrow) {
  //  if (value == nullptr) throw std::domain_error("Encountered null pointer when trying to parse into an integer");
  //  char* ptrEnd;
  //  typeValue rslt = std::strtoll(value, &ptrEnd, 0);
  //  if (ptrEnd == value && canThrow) { // no valid things are parsed
  //    throw std::domain_error(std::string("String '") + value + "' is not a valid integer.");
  //  }
  //  pimpl->m_data = rslt;
  //}

  //template <> // float specialization
  //void OptFloat::set(const char* value, bool canThrow) {
  //  if (value == nullptr) throw std::domain_error("Encountered null pointer when trying to parse into a number");
  //  char* ptrEnd;
  //  typeValue rslt = std::strtold(value, &ptrEnd);
  //  if (ptrEnd == value && canThrow) { // no valid things are parsed
  //    throw std::domain_error(std::string("String '") + value + "' is not a valid number.");
  //  }
  //  pimpl->m_data = rslt;
  //}

  //template <> // bool specialization
  //void OptBool::set(const char* value, bool canThrow) {
  //  if (value == nullptr) throw std::domain_error("Encountered null pointer when trying to parse into a boolean value");
  //  while (std::isspace(value[0])) ++value;
  //  if (value[0] == 't' || value[0] == 'T' || value[0] == 'y' || value[0] == 'Y' || value[0] == 'o' || value[0] == 'O' || value[0] == 'v' || value[0] == 'V') {
  //    pimpl->m_data = true;
  //  } else if (value[0] == 'f' || value[0] == 'F' || value[0] == 'n' || value[0] == 'N' || value[0] == 'x' || value[0] == 'X') {
  //    pimpl->m_data = false;
  //  } else if (canThrow) {
  //    throw std::domain_error(std::string("String '") + value + "' is not a valid boolean value.");
  //  } else {
  //    pimpl->m_data = false;
  //  }
  //}


  //// ==== String Specialization below ==== //

  //template <> // string specialization
  //struct OptStr::Impl {
  //  Impl() : m_default(""), m_data("") {}
  //  Impl(const char* value) : m_default(value), m_data(value) {}

  //  const std::string m_default;
  //  std::string m_data;

  //  // Provide assignment operator that shouldn't be called but are needed to compile
  //  Impl& operator=(const Impl& rhs) {
  //    m_data = rhs.m_data;
  //    return *this;
  //  }
  //};

  //template <>
  //OptStr::Opt(const char* const& value) : pimpl(value) {}

  //template <>
  //OptStr::Opt(const OptStr& rhs) : pimpl(rhs.pimpl) {}

  //template <>
  //OptStr::Opt(OptStr&& rhs) noexcept : pimpl(std::move(rhs.pimpl)) {}


  //template <>
  //OptStr::operator const char*() {
  //  return pimpl->m_data.c_str();
  //}

  //template <>
  //OptStr::operator const char*() const {
  //  return pimpl->m_data.c_str();
  //}

  //template<>
  //const char* const OptStr::operator()() const {
  //  return pimpl->m_data.c_str();
  //}

  //template <>
  //const char* OptStr::operator=(const char* const& value) {
  //  if (value == nullptr) throw std::domain_error("Encountered null pointer when assigning string");
  //  return (pimpl->m_data = value).c_str();
  //}

  //template <>
  //const char* OptStr::operator=(const OptStr& rhs) {
  //  return (pimpl->m_data = rhs.pimpl->m_data).c_str();
  //}

  //template <>
  //const char* OptStr::operator=(OptStr&& rhs) noexcept {
  //  return (pimpl->m_data = std::move(rhs.pimpl->m_data)).c_str();
  //}

  //template <>
  //const char* const OptStr::getDefault() {
  //  return pimpl->m_default.c_str();
  //}

  //template <>
  //void OptStr::reset() {
  //  pimpl->m_data = pimpl->m_default;
  //}

  //template <>
  //void OptStr::set(const char* value, bool canThrow) {
  //  if (value == nullptr) throw std::domain_error("Encountered null pointer when trying to set a string value");
  //  pimpl->m_data = value;
  //}

}

ASPARTAMEV0_OPTARR_IMPL(int64_t, 160);
ASPARTAMEV0_OPTARR_IMPL(double, 160);
ASPARTAMEV0_OPTARR_IMPL(bool, 160);
//ASPARTAMEV0_OPT_IMPL(const char*, sizeof(char*)*2);
