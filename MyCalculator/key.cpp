#include "key.h"

Key::Key(const strkeyext_t &text) : m_keyText(text) {

}

Key::~Key() {

}

const strkeyext_t &Key::getKeyText() const {
    return m_keyText;
}
