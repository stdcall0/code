#ifndef COLOR_HEADER
#define COLOR_HEADER

#include <string>
#include <sstream>
#include <cstring>

inline std::string _int2str(int x) {
  std::ostringstream oss;
  oss << x; return oss.str();
}
inline std::string _translate(int b) {
  b &= (1 << 21) - 1;
  if (!b) return "";
  std::string ret = "\033[";
  if (b & 1 << 20) ret += "0;";
  // Foreground Color
  for (int i = 0; i < 8; ++i)
    if (b & 1 << i) { ret += _int2str(30 + i) + ";"; break; }
  // Background Color
  for (int i = 8; i < 16; ++i)
    if (b & 1 << i) { ret += _int2str(32 + i) + ";"; break; }
  // Modifier
  if (b & 1 << 16) ret += "1;";
  if (b & 1 << 17) ret += "4;";
  if (b & 1 << 18) ret += "5;";
  if (b & 1 << 19) ret += "7;";

  if (ret[ret.size() - 1] != ';') return "";
  ret[ret.size() - 1] = 'm';
  return ret;
}

namespace FG { enum { Black = 1, Red = 2, Green = 4, Yellow = 8, Blue = 16, Purple = 32, Cyan = 64, White = 128 }; }
namespace BG { enum { Black = 256, Red = 512, Green = 1024, Yellow = 2048, Blue = 4096, Purple = 8192, Cyan = 16384, White = 32768 }; }
namespace M { enum { Light = 65536, Underline = 131072, Blink = 262144, Revert = 524288, Reset = 1048576 }; }

class _c2c_wrapper {
private:
  std::string s;
public:
  _c2c_wrapper(const std::string& s) : s(s) {}
  operator const char* () const { return s.c_str(); }
  const char* operator()() const { return s.c_str(); }
  const char* operator~() const { return s.c_str(); }
};
inline _c2c_wrapper c2c(int CCODE = M::Reset) {
  return _c2c_wrapper(_translate(CCODE));
}
class _CCManager {
public:
  _c2c_wrapper operator[] (int CCODE) const { return c2c(CCODE); }
};
const _CCManager CC;
inline std::string c2s(int CCODE = M::Reset) {
  return _translate(CCODE);
}

#endif
