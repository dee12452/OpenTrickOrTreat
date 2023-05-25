#include "Util.h"

template<typename T>
T Math::max(T first, T second) {
    return first > second ? first : second;
}

template<typename T>
T Math::min(T first, T second) {
    return first < second ? first : second;
}

float Math::toRads(float degrees) {
    return degrees * static_cast<float>(Compat::getPi() / 180);
}

float Math::toDegrees(float rads) {
    return rads * static_cast<float>(180 / Compat::getPi());
}
