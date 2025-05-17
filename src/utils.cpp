


#include <random>
#include <type_traits>

namespace utils {

    template <typename T>
    concept EnumWithCount = std::is_enum_v<T> && requires { T::COUNT; };

    template <typename T>
    requires EnumWithCount<T>
    auto getRandomEnumOption() -> T {
        auto generator = std::mt19937(std::random_device{}());
        auto random_index = generator() % static_cast<int>(T::COUNT);
        auto spawn_position = static_cast<T>(random_index);
        return spawn_position;
    }
}
