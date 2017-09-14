#ifndef KEY_H
#define KEY_H

#include <string>

using strkeyext_t = std::string;

class Key {
private:
    const strkeyext_t m_keyText;
protected:
    Key() = default;
    Key(const strkeyext_t &text);
    Key(const Key &rhs) = delete;
    Key &operator=(const Key &rhs) = delete;
    Key(const Key &&rhs) = delete;
    Key &operator=(const Key &&rhs) = delete;
    virtual ~Key();
protected:
    virtual const strkeyext_t &getKeyText() const;
};

#endif // KEY_H
