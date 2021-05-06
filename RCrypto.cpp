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
    virtual void _encrypt() = 0;
    virtual void _decrypt() = 0;

  public:
    crypto() {}
    crypto(std::vector<char>& k) {
        for (char v : k)
            key.emplace_back((v >= 'a' && v <= 'z') ? v - 'a' + 'A' : v);
    }
    std::vector<char> encrypt(std::vector<char>& pt) {
        _clear();
        plaintext = pt;
        _encrypt();
        return ciphertext;
    }
    std::vector<char> decrypt(std::vector<char>& ct) {
        _clear();
        ciphertext = ct;
        _decrypt();
        return plaintext;
    }
};

class vigenereCipher : public crypto {
    const int base = 'A';
    inline bool _check(char& v) {
        if (v <= 'z' && v >= 'a')
            v -= 'a' - 'A';
        if (v <= 'Z' && v >= 'A')
            return true;
        return false;
    }
    inline void _encrypt() {
        int index = 0;
        for (auto v : plaintext) {
            if (_check(v))
                ciphertext.emplace_back(
                    (v + key[index++ % key.size()] - base - base) % 26 + base);
        }
    }
    inline void _decrypt() {
        int index = 0;
        for (auto v : ciphertext) {
            if (_check(v))
                plaintext.emplace_back(v - key[index++ % key.size()] + base);
        }
    }

  public:
    vigenereCipher() {}
    vigenereCipher(std::vector<char>& k) : crypto(k) {}
};
class caesarCipher : public vigenereCipher {
  public:
    caesarCipher(std::vector<char>& k) {
        if (k.size() < 1)
            exit(-1);
        key.emplace_back((k[0] >= 'a' && k[0] <= 'z') ? k[0] - 'a' + 'A' : k[0]);
    }
};
} // namespace RCrypto