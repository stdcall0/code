#if __cplusplus < 201103L
#error Use -std=c++17
#endif

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
#if !defined(_WIN32) && !defined(WIN32)
    printf("This program cannot run in non-windows systems.\n");
    return 2;
#endif

    system("color F0"); // set Console color

    if (argc != 2) {
        printf("Usage: \n%s <filename>.csv/.txt\nPress any key to quit...\n", argv[0]);
        system("pause >nul 2>nul");
    }

    string fName = argv[1];
    ifstream fin(fName.c_str());
    if (!fin.is_open()) {
        printf("Cannot open the file. Is the path correct?\n%s\n", fName.c_str());
        return 1;
    }

    ofstream fout("output.txt");

    if (!fout.is_open()) {
        printf("Cannot open the output file. Is the disk full or no permission?\n");
        return 1;
    }

    fout << "Dim WList = Array("; bool first = 1; int cnt = 0;

    int loc; string t; while (!getline(fin, t).eof()) {
        loc = 1; for (int i=0; i<t.size(); i++) {
            if (!isalpha(t[i]) && t[i] != '-') loc = false;
        }
        if (!loc) {
            printf("Word %s contains non-alphabet character(s).\nKeep it (K), remove all non-alphabet character(s) (R) or skip it (S)?\nEnter your choice (ENTER for default 'SKIP'): ", t.c_str());
            fflush(stdout);
            string sel; do {
                getline(cin, sel);
                if (sel == "") { sel = "s"; break; }
                if (sel.size() != 1 || !isalpha(sel[0])) { printf("Please enter a valid choice: "); continue; }
                sel[0] = tolower(sel[0]);
                if (sel[0] != 'k' && sel[0] != 'r' && sel[0] != 's') { printf("Please enter a valid choice: "); continue; }
                break;
            } while (1);
            if (sel[0] == 's') continue;
            if (sel[0] == 'r') {
                string n;
                for (char c : t) if (isalpha(c) || c == '-') n += c;
                t = n;
            }
        }
        while ((loc = t.find(" ")) != string::npos) t.replace(loc, 1, " ");
        
        loc = 1; for (int i=0; i<t.size(); i++) {
            if (!islower(t[i]) && t[i] != '-') loc = false;
        }
        if (!loc) {
            printf("Word %s contains uppercase character(s).\nKeep it (K), or convert to lowercase (C)?\nEnter your choice (ENTER for default 'K'): ", t.c_str());
            
            string sel; do {
                getline(cin, sel);
                if (sel == "") { sel = "k"; break; }
                if (sel.size() != 1 || !isalpha(sel[0])) { printf("Please enter a valid choice: "); continue; }
                sel[0] = tolower(sel[0]);
                if (sel[0] != 'k' && sel[0] != 'c') { printf("Please enter a valid choice: "); continue; }
                break;
            } while (1);
            if (sel[0] == 'c') {
                string n;
                for (char c : t) n += tolower(c);
                t = n;
            }
        }
        if (first) fout << '"' << t << '"';
        else fout << ", \"" << t << '"'; ++ cnt;
        first = 0;
    }
    fout << ");\n"; printf("%d words proceed. Result saves to output.txt\n", cnt);
    fout.close(); fin.close(); system("pause");
    return 0;
}
