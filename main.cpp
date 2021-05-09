#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include "RCrypto.cpp"
using namespace std;
void fail() {
    cout << "invalid arguments." << endl;
    exit(-1);
}
int main(int argc, char const *argv[]) {
    string str_t, str_key;
    vector<char> key, ans, t;
    if (argc == 2 && strcmp(argv[1], "h")) {
        cout << "Usage:"
             << "\t(e|d) key text\n"
             << "\n"
             << "e\tencrypt\n"
             << "d\tdecrypt\n"
             << endl;
        return 0;
    }
    if (argc == 3) {
        for (int i = 0; argv[1][i] != 0; i++)
            key.push_back(argv[1][i]);
        for (int i = 0; argv[2][i] != 0; i++)
            t.push_back(argv[2][i]);
        RCrypto::vigenereCipher vc(key);
        ans = vc.encrypt(t);
    } else if (argc == 4) {
        for (int i = 0; argv[2][i] != 0; i++)
            key.push_back(argv[2][i]);
        for (int i = 0; argv[3][i] != 0; i++)
            t.push_back(argv[3][i]);
        RCrypto::vigenereCipher vc(key);
        if (argv[1][0] == 'e')
            ans = vc.encrypt(t);
        else if (argv[1][0] == 'd')
            ans = vc.decrypt(t);
        else
            fail();
    } else
        fail();
    for (char v : ans)
        cout << v;
    cout << endl;
    return 0;
}
/*
ABCCCCZZZ
AAAAAAAAAZZZZZZZZ
ABCCCCZZZZABBBBYY
*/