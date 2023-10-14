
#include <cstdint>
#include <cwctype>
#include <utility>
namespace ara {
namespace core{
    using Byte = std::byte;
    using in_place_t = std::in_place_t;
    template <class Tp>
    using in_place_type_t = std::in_place_type_t<Tp>;
    template <std::size_t Idx>
    using in_place_index_t = std::in_place_index_t<Idx>;
}
}
