#ifndef GAME_UNITS_H
#define GAME_UNITS_H

#include <cmath>
#include <iostream>

namespace Unit {

    const float EPS = 1e-6;

    struct Vec2D {
        float x = 0.0f;
        float y = 0.0f;

        Vec2D() = default;
        Vec2D(float x, float y) : x(x), y(y) {}

        Vec2D operator+(const Vec2D& rhs) const { return {x + rhs.x, y + rhs.y}; }
        Vec2D operator-(const Vec2D& rhs) const { return {x - rhs.x, y - rhs.y}; }
        Vec2D operator*(float scalar) const { return {x * scalar, y * scalar}; }
        Vec2D operator/(float scalar) const { return {x / scalar, y / scalar}; }

        Vec2D& operator+=(const Vec2D& rhs) { x += rhs.x; y += rhs.y; return *this; }
        Vec2D& operator-=(const Vec2D& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
        Vec2D& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
        Vec2D& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

        Vec2D operator-() const { return {-x, -y}; }
        Vec2D operator=(const Vec2D& rhs) { if (this != &rhs) { x = rhs.x; y = rhs.y; } return *this; }

        const float EPS = 1e-6;
        bool operator==(const Vec2D& rhs) const { return std::abs(x - rhs.x) < EPS && std::abs(y - rhs.y) < EPS; }
        bool operator!=(const Vec2D& rhs) const { return !(*this == rhs); }

        float dot(const Vec2D& rhs) const { return x * rhs.x + y * rhs.y; }
        float magnitude() const { return std::sqrt(x * x + y * y); }
        float magnitudeSquared() const { return x * x + y * y; }
        Vec2D normalized() const { float m = magnitude(); return m == 0 ? Vec2D() : *this / m; }

        friend std::ostream& operator<<(std::ostream& os, const Vec2D& v) {
            return os << "Vec2D(" << v.x << ", " << v.y << ")";
        }

        friend Vec2D operator*(float scalar, const Vec2D& v) { return v * scalar; }
    };

    enum class Input {
        Basic,
        Wide,
        Offensive,
        Defensive,
        Focus,
        Toggle,
        Pause,
        MoveRight,
        MoveLeft,
        MoveUp,
        MoveDown,
        InputCount // This should always be the last element
    };
    const int NUM_INPUTS = static_cast<int>(Input::InputCount);

    enum class Move {
        Basic,
        Wide,
        Offensive,
        Defensive,
        MoveCount // This should always be the last element
    };
    const int NUM_MOVES = static_cast<int>(Move::MoveCount);

    enum class StatusEffect {
        Invincible,
        Stun,
        Paralyze,
        Confuse,
        Poison,
        DeathToll,
        Mini,
        Slow,
        StatusEffectCount // This should always be the last element
    };
    const int NUM_STATUS_EFFECTS = static_cast<int>(StatusEffect::StatusEffectCount);

    enum class Lock {
        MoveLock,
        ArrowLock,
        BasicLock,
        WideLock,
        OffensiveLock,
        DefensiveLock,
        LockCount // This should always be the last element
    };
    const int NUM_LOCKS = static_cast<int>(Lock::LockCount);

    enum class Modifier {
        SpeedModifier,
        SizeModifier,
        BulletSizeModifier,
        CooldownModifier,
        FlinchModifier,
        ModifierCount // This should always be the last element
    };
    const int NUM_MODIFIERS = static_cast<int>(Modifier::ModifierCount);

};

#endif // GAME_UNITS_H