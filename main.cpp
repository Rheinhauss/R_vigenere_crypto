#include <iostream>
#include <string>
#include <vector>
#include "RCrypto.cpp"
using namespace std;

int main(int argc, char const *argv[]) {
    string str_t, str_key;
    vector<char> key, ans, t;
    cin >> str_key;
    cin >> str_t;
    for (char v : str_t)
        t.emplace_back(v);
    for (char v : str_key)
        key.emplace_back(v);
    RCrypto::vigenereCipher vc(key);
    if (argc == 1 || (argc == 2 && argv[1][0] == 'e')) {
        ans = vc.encrypt(t);
    } else if (argc == 2 && argv[1][0] == 'd') {
        ans = vc.decrypt(t);
    }
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