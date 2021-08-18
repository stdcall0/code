#ifndef UTIL_HEADER
#define UTIL_HEADER
#include <codecvt>
#include <locale>
#include <random>
#include <string>

int genRand(int min, int max) {
    static std::default_random_engine rd(std::random_device{}());
    static std::uniform_int_distribution<int> U;
    return U(rd, decltype(U)::param_type(min, max-1));
}
std::wstring s2ws(const std::string& str) {
  using convert_typeX = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_typeX, wchar_t> converterX;
  return converterX.from_bytes(str);
}
std::string ws2s(const std::wstring& wstr) {
  using convert_typeX = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_typeX, wchar_t> converterX;
  return converterX.to_bytes(wstr);
}
bool startswith(const std::string &src, const std::string& comp) {
  if (comp.size() < src.size()) return 0;
  for (unsigned i=0; i<src.size(); i++) if (comp[i] != src[i]) return 0;
  return 1;
}

#endif