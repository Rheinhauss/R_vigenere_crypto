#include <cctype>
#include <vector>
namespace RCrypto {

class crypto {
  protected:
    std::vector<char> ciphertext;
    std::vector<char> plaintext;
    std::vector<char> key;
    inline void _clear() {
        ciphertext.clear();
        plaintext.clear();
    }
    inline virtual void _encrypt() = 0;
    inline virtual void _decrypt() = 0;
    inline virtual char char_process_key(char ch) { return ch; };
    inline virtual char char_process_ct(char ch) { return ch; };
    inline virtual char char_process_pt(char ch) { return ch; };
    inline virtual char char_process(char ch) { return ch; };

  public:
    crypto() {}
    crypto(std::vector<char>& k) {
        for (char v : k)
            key.emplace_back(char_process_key(v));
    }
    std::vector<char> encrypt(std::vector<char>& pt) {
        _clear();
        for (auto ch : pt)
            plaintext.push_back(char_process_pt(ch));
        _encrypt();
        return ciphertext;
    }
    std::vector<char> decrypt(std::vector<char>& ct) {
        _clear();
        for (auto ch : ct)
            ciphertext.push_back(char_process_ct(ch));
        _decrypt();
        return plaintext;
    }
};

class vigenereCipher : public crypto {
    const int base = 'A';
    inline bool _check(char& v) {
        if (v <= 'Z' && v >= 'A')
            return true;
        else
            return false;
    }
    inline char char_process(char ch) {
        if (isalpha(ch) || ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r')
            return ch;
        exit(-1);
    }
    inline char char_process_ct(char ch) { return char_process(ch); }
    inline char char_process_pt(char ch) { return char_process(ch); }
    inline void _encrypt() { code(true); }
    inline void _decrypt() { code(false); }
    inline void code(bool mtd) {
        std::vector<char> tmp;
        auto len = (mtd ? plaintext : ciphertext).size();
        for (int j = 0; j < len; j++) {
            char tmp_ch =
                mtd ? ((plaintext[j] - 'A' + key[j % key.size()] - 'A') % 26 + 'A')
                    : ((ciphertext[j] - 'A' - key[j % key.size()] - 'A' + 260) % 26 +
                       'A');
            tmp.push_back(tmp_ch);
        }
        (!mtd ? plaintext : ciphertext) = tmp;
    }

  public:
    vigenereCipher() {}
    vigenereCipher(std::vector<char>& k) : crypto(k) {}
};
class caesarCipher : public vigenereCipher {
  public:
    caesarCipher(std::vector<char>& k) {
        if (k.size() != 1)
            exit(-1);
        key.emplace_back((k[0] >= 'a' && k[0] <= 'z') ? k[0] - 'a' + 'A' : k[0]);
    }
};
} // namespace RCrypto