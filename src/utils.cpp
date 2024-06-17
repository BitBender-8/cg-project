#include "../includes/utils.h"

Color::Color(ColorHex hex) : r{static_cast<GLclampf>((hex >> 24) & 0xFF) / 255.0f},
                             g{static_cast<GLclampf>((hex >> 16) & 0xFF) / 255.0f},
                             b{static_cast<GLclampf>((hex >> 8) & 0xFF) / 255.0f},
                             a{static_cast<GLclampf>(hex & 0xFF) / 255.0f}
{
}

bool Position::operator==(const Position &other) const
{
    return (x == other.x && y == other.y);
}

std::size_t PositionHasher::operator()(const Position &pos) const
{
    return std::hash<int>()(pos.x) ^ (std::hash<int>()(pos.y) << 1);
}
