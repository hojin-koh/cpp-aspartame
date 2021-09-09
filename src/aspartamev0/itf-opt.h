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

