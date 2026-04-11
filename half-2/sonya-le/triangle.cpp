#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    long long x, y;

    Point(long long x = 0, long long y = 0) : x(x), y(y) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

struct Triangle {
    Point a, b, c;

    Triangle(const Point& a, const Point& b, const Point& c) : a(a), b(b), c(c) {}

    void print() const {
        cout << "Triangle: (" << a.x << "," << a.y << ") - "
             << "(" << b.x << "," << b.y << ") - "
             << "(" << c.x << "," << c.y << ")\n";
    }
};

// Векторное произведение
long long cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

// Вычитание векторов
Point sub(const Point& a, const Point& b) {
    return Point(a.x - b.x, a.y - b.y);
}

// Ориентация трех точек
// Возвращает: >0 - против часовой, <0 - по часовой
long long orientation(const Point& a, const Point& b, const Point& c) {
    return cross(sub(b, a), sub(c, a));
}

// Проверка, лежит ли точка на отрезке (строго внутри или на концах)
bool pointOnSegment(const Point& p, const Point& a, const Point& b) {
    if (orientation(a, b, p) != 0) return false;
    return (min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
            min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y));
}

// Проверка, лежит ли точка строго внутри треугольника
bool pointInTriangleStrict(const Point& p, const Point& a, const Point& b, const Point& c) {
    long long o1 = orientation(a, b, p);
    long long o2 = orientation(b, c, p);
    long long o3 = orientation(c, a, p);

    // Точка внутри, если все ориентации одного знака и не равны 0
    // (строго внутри, не на границе)
    bool allPositive = (o1 > 0 && o2 > 0 && o3 > 0);
    bool allNegative = (o1 < 0 && o2 < 0 && o3 < 0);

    return allPositive || allNegative;
}

// Проверка, лежит ли точка внутри или на границе треугольника
bool pointInTriangleOrBoundary(const Point& p, const Point& a, const Point& b, const Point& c) {
    long long o1 = orientation(a, b, p);
    long long o2 = orientation(b, c, p);
    long long o3 = orientation(c, a, p);

    // Проверяем, что все ориентации не имеют разных знаков
    bool hasPositive = (o1 > 0)  (o2 > 0)  (o3 > 0);
    bool hasNegative = (o1 < 0)  (o2 < 0)  (o3 < 0);

    return !(hasPositive && hasNegative);
}

// Структура узла двусвязного списка
struct Node {
    Point point;
    int index;
    Node* prev;
    Node* next;

    Node(const Point& p, int idx) : point(p), index(idx), prev(nullptr), next(nullptr) {}
};

bool isEar(Node* v, const vector<Node*>& allNodes) {
    Point a = v->prev->point;
    Point b = v->point;
    Point c = v->next->point;

    // Проверка 1: угол должен быть выпуклым (< 180°)
    // Для многоугольника против часовой стрелки orientation > 0
    if (orientation(a, b, c) <= 0) {
        return false;
    }

    // Проверка 2: внутри треугольника не должно быть других вершин
    Node* curr = v->next->next;
    while (curr != v->prev) {
        Point p = curr->point;

        // Если точка лежит на границе треугольника - это не ухо
        if (pointOnSegment(p, a, b)  pointOnSegment(p, b, c)  pointOnSegment(p, c, a)) {
            return false;
        }

        // Если точка строго внутри треугольника - это не ухо
        if (pointInTriangleStrict(p, a, b, c)) {
            return false;
        }

        curr = curr->next;
    }

    return true;
}

vector<Node*> createCircularList(const vector<Point>& polygon) {
    vector<Node*> nodes;
    int n = polygon.size();

    for (int i = 0; i < n; i++) {
        nodes.push_back(new Node(polygon[i], i));
    }

    for (int i = 0; i < n; i++) {
        nodes[i]->prev = nodes[(i + n - 1) % n];
        nodes[i]->next = nodes[(i + 1) % n];
    }

    return nodes;
}

// Очистка памяти
void cleanNodes(vector<Node*>& nodes) {
    for (Node* node : nodes) {
        delete node;
    }
    nodes.clear();
}

// Ушная триангуляция
vector<Triangle> earTriangulation(const vector<Point>& polygon) {
    vector<Triangle> triangles;
    int n = polygon.size();

    if (n < 3) {
        return triangles;
    }

    if (n == 3) {
        triangles.push_back(Triangle(polygon[0], polygon[1], polygon[2]));
        return triangles;
    }
    vector<Node*> nodes = createCircularList(polygon);
    int remaining = n;
    Node* current = nodes[0];

    while (remaining > 3) {
        bool earFound = false;
        Node* start = current;
        do {
            if (isEar(current, nodes)) {
                triangles.push_back(Triangle(
                    current->prev->point,
                    current->point,
                    current->next->point
                ));
                current->prev->next = current->next;
                current->next->prev = current->prev;
                Node* toDelete = current;
                current = current->next;

                // Отключаем удаленную вершину
                toDelete->prev = nullptr;
                toDelete->next = nullptr;

                remaining--;
                earFound = true;
                break;
            }
            current = current->next;
        } while (current != start);
        if (!earFound) {
            break;
        }
    }
    if (remaining == 3) {
        triangles.push_back(Triangle(
            current->point,
            current->next->point,
            current->next->next->point
        ));
    }
    cleanNodes(nodes);

    return triangles;
}

// Функция для проверки ориентации многоугольника (против часовой стрелки)
bool isCounterClockwise(const vector<Point>& v) {
    long long area = 0;
    int n = v.size();

    for (int i = 0; i < n; i++) {
        const Point& a = v[i];
        const Point& b = v[(i + 1) % n];
        area += (a.x * b.y - b.x * a.y);
    }

    return area > 0;
}

// Переворот порядка вершин
vector<Point> reversev(const vector<Point>& v) {
    vector<Point> reversed(v.rbegin(), v.rend());
    return reversed;
}

int main() {
    cout << "Example 1:" << endl;
    vector<Point> a  = {
        Point(0, 0),
        Point(3, 0),
        Point(4, 2),
        Point(2, 3),
        Point(0, 2)
    };

    if (!isCounterClockwise(a)) {
        a = reversev(a);
    }

    vector<Triangle> result1 = earTriangulation(a);
    for (const auto& tri : result1) {
        tri.print();
    }
    cout << endl << "Example 2:" << endl;
    vector<Point> b = {
        Point(0, 0),
        Point(3, 0),
        Point(4, 2),
        Point(3, 4),
        Point(0, 4),
        Point(-1, 2)
    };

    vector<Triangle> result2 = earTriangulation(b);
    for (const auto& tri : result2) {
        tri.print();
    }

    cout << endl << "Example 3:" << endl;
    vector<Point> c = {
        Point(0, 0),
        Point(3, 0),
        Point(1, 3)
    };

    vector<Triangle> result3 = earTriangulation(c);
    for (const auto& tri : result3) {
        tri.print();
    }
    cout << endl << "Example 4:" << endl;
    vector<Point> d = {
        Point(0, 0),
        Point(4, 0),
        Point(4, 2),
        Point(2, 2),
        Point(2, 4),
        Point(0, 4)
    };

    if (!isCounterClockwise(d)) {
        d = reversev(d);
    }

    vector<Triangle> result4 = earTriangulation(d);
    for (const auto& tri : result4) {
        tri.print();
    }

    return 0;
}
