#ifndef UNIT_HPP
#define UNIT_HPP

#include <cmath>
#include <iostream>
#include <string>

namespace Unit {

    const float EPS = 1e-6;

    const float BATTLEFIELD_WIDTH = 1440.0f;
    const float BATTLEFIELD_HEIGHT = 900.0f;

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
        MoveRight,
        MoveLeft,
        MoveUp,
        MoveDown,

        Confirm,
        Back,
        Pause,
        Toggle,

        Basic,
        Wide,
        Offensive,
        Defensive,
        Focus,
        
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

    enum class Modifier {
        MovementModifier,
        ArrowModifier,
        SizeModifier,
        BulletSizeModifier,
        CooldownModifier,
        StaggerModifier,
        ModifierCount // This should always be the last element
    };
    const int NUM_MODIFIERS = static_cast<int>(Modifier::ModifierCount);

    enum class Lock {
        MovementLock,
        ArrowLock,
        BasicLock,
        WideLock,
        OffensiveLock,
        DefensiveLock,
        LockCount // This should always be the last element
    };
    const int NUM_LOCKS = static_cast<int>(Lock::LockCount);

    enum Layer {
        Background = 0,
        Underlay = 10,
        Character = 20,
        Bullet = 30,
        Overlap = 40,
        Foreground = 50,
        HUD = 60,
        UI = 70
    };

    inline Input moveToInput(Move move) {
        switch (move) {
            case Move::Basic:     return Input::Basic;
            case Move::Wide:      return Input::Wide;
            case Move::Offensive: return Input::Offensive;
            case Move::Defensive: return Input::Defensive;
            default:              return Input::InputCount; // Invalid input fallback
        }
    }
    inline Lock moveToLock(Move move) {
        switch (move) {
            case Move::Basic:     return Lock::BasicLock;
            case Move::Wide:      return Lock::WideLock;
            case Move::Offensive: return Lock::OffensiveLock;
            case Move::Defensive: return Lock::DefensiveLock;
            default:              return Lock::LockCount; // Invalid lock fallback
        }
    }
};

#endif // UNIT_HPP