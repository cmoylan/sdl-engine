#pragma once

struct Vector2D {
    int x;
    int y;

    bool isZero() {
        return (x == 0) && (y == 0);
    }

    bool equals(Vector2D other) {
        return (x == other.x) && (y == other.y);
    }

    Vector2D delta(Vector2D other) {
        Vector2D difference = {
            x - other.x,
            y - other.y
        };
        return difference;
    }
};

typedef Vector2D Point;

inline std::ostream& operator<<(std::ostream& os, const Vector2D& object) {
    os << "[" << object.x << ", " << object.y << "]";
    return os;
}
