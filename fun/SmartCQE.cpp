// Compile with compiler flag  -std=c++14 or -std=c++20
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

vector<string> resp = {"NMSL", "WDNMD", "闭嘴吧孤儿", "你个 sjy，bb啥呢", "你妈死了", "你的全家福上为什么只有你一个人", "你的户口本怎么只有一页", "你这人怎么和cpy一样脑瘫", "你是shaobiao吗", "偷偷地告诉你，你妈死了", "LOSER SHUT UP", "呵呵 无论你说什么 你都是个孤儿", "L", "Go & Fuck Yourself", "作业写完了吗，傻逼？", "写题去了，还在这干啥呢", "草拟吗你个傻逼司马玩意儿", "你他妈再说一遍试试，信不信我顺着网线摸过去把你妈刀了","我吃你妈的骨灰拌饭","火葬场问你妈要几分熟"};
map<int, wstring> ct; map<int, int> cnt; const int CTS = 7; int lastNMSL = -1;
string brandName = "SmartSJY"; bool chroma = 1;
default_random_engine rd(random_device{}());
uniform_int_distribution<int> U;
// color id from 30m to 37m

int genRand(int min, int max) {
    return U(rd, decltype(U)::param_type(min, max-1));
}
std::wstring s2ws(const std::string& str)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(str);
}

std::string ws2s(const std::wstring& wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}
bool startswith(const string &src, const string& comp) {
    if (comp.size() < src.size()) return 0;
    for (unsigned i=0; i<src.size(); i++) if (comp[i] != src[i]) return 0;
    return 1;
}
string chromaText(const string &src_D) {
    wstring r = L"", src = s2ws(src_D);
    for (unsigned i=0; i < src.size(); ++i) {
        r += L"\033[" + ct[genRand(0, CTS)] + src.substr(i, 1);
    }
    r += L"\033[0m"; return ws2s(r);
}

bool InpCycle();
void Init();

int main() {
    ct[0] = L"37m"; ct[1] = L"31m"; ct[2] = L"32m";
    ct[3] = L"33m"; ct[4] = L"34m"; ct[5] = L"35m";
    ct[6] = L"36m"; // ct[7] = L"37m";
    Init(); do; while(!InpCycle());
    return 0;
}

bool InpCycle() {
    string inp; printf("> "); getline(cin, inp);
    // if (inp == "q") return 1;
    if (startswith("!# ", inp)) {
        string cmd = inp.substr(3);
        if (startswith("changebrand ", cmd)) {
            string subs = cmd.substr(12); brandName = subs;
            printf("Client brand changed to <%s>.\n", subs.c_str());
        } else if (cmd == "reload") {
            printf("Reloading...\n\n");
            Init();
        } else if (cmd == "chroma") {
            chroma = !chroma;
            printf("Chroma state is now %s.\n", chroma ? "enabled": "disabled");
        } else if (cmd == "clear") {
            system("clear");
        } else if (cmd == "stats") {
            printf("SAYS Statistics:\n");
            for (unsigned i=0; i<resp.size(); i++) {
                printf("%d - %s - %d time(s)\n",i, resp[i].c_str(),cnt[i]);
            }
        } else {
            printf("<%s> is not a valid command.\n", cmd.c_str());
        }
    } else {
        int xb; do xb = genRand(0, resp.size()); while (xb == lastNMSL); cnt[lastNMSL = xb]++;
        puts(chroma ? chromaText(resp[xb]).c_str() : resp[xb].c_str());
    } 
    return 0;
}
void Init() {
    printf("%s, your Personal caring chat bot.\n", chromaText(brandName).c_str());
    printf("Version Alpha 0.1\n\n");
    printf("Loading AI response system.. ["); fflush(stdout);
    for (unsigned i = 0; i < resp.size(); ++i) {
        printf(i & 1 ? "□" : "■"); fflush(stdout); usleep(genRand(80000, 300000) / 2);
    }
    printf("]\n\nCtrl+C to quit.\n\n"); fflush(stdout);
    usleep(genRand(900000, 1200000));
}