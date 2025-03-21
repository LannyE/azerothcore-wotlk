#ifndef BOT_LOG_TRAITS_H_
#define BOT_LOG_TRAITS_H_

#include "botcommon.h"

#include "StringConvert.h"

namespace NPCBots
{

template<typename ST, ST Size>
constexpr std::array<ST, Size> index_array = ([]<typename T, T... I>(std::integer_sequence<T, I...>&&) { return std::array{ I... }; })(std::make_integer_sequence<ST, Size>{});

namespace StringConvert
{
    template<typename T>
    static std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, std::string>
    ToString(T t)
    {
        return Bcore::Impl::StringConvertImpl::For<T>::ToString(t);
    }

    template<typename T>
    static std::enable_if_t<std::is_trivially_constructible_v<std::string, T> || std::is_same_v<std::string, T>, std::string>
    ToString(T t)
    {
        return std::string{ t };
    }

    template<typename T>
    static std::enable_if_t<!std::is_trivially_constructible_v<std::string, T> && !std::is_same_v<std::string, T> && std::is_constructible_v<std::string, T>, std::string>
    ToString(T t)
    {
        return std::string(t);
    }
}

template<typename T>
concept Stringable = requires(T t) { StringConvert::ToString(t); };

template<typename... Ts>
concept LoggableCount = (sizeof...(Ts) <= MAX_BOT_LOG_PARAMS);

template<typename... Ts>
concept LoggableArguments = LoggableCount<Ts...> && (Stringable<Ts> && ...);

}

#endif
