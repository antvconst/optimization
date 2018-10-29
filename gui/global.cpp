#include "global.hpp"

Globals* Globals::instance = nullptr;

const Globals& Globals::get() {
    if (!instance) {
        instance = new Globals();
    }

    return *instance;
}

Globals& Globals::get_mutable() {
    if (!instance) {
        instance = new Globals();
    }

    return *instance;
}

Globals::Globals() {}
