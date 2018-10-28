#include "global.hpp"

Global* Global::instance = nullptr;

const Global& Global::get() {
    if (!instance) {
        instance = new Global();
    }

    return *instance;
}

Global& Global::get_mutable() {
    if (!instance) {
        instance = new Global();
    }

    return *instance;
}

Global::Global() {}
