


#include <random>
#include <type_traits>
#include <__random/random_device.h>

namespace utils {

    template<typename T, typename = void>
    struct has_count : std::false_type {};

    template<typename T>
    struct has_count<T, std::void_t<decltype(T::COUNT)>> : std::true_type {};

    template<typename T>
    concept EnumWithCount = std::is_enum_v<T> && has_count<T>::value;

    template <typename T>
    requires EnumWithCount<T>
    auto getRandomEnumOption() -> T {
        std::random_device rdev;
        std::mt19937 rgen(rdev());
        std::uniform_int_distribution<int> dist(0,static_cast<int>(T::COUNT)-1);
        auto spawn_position = static_cast<T>(dist(rgen));
        return spawn_position;
    }
}
