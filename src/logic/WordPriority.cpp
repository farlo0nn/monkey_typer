#include "WordPriority.h"


bool WordPriority::operator()(const Word& a, const Word& b) const {
    float distA = std::hypot(a.position.x - 0, a.position.y - 0);
    float distB = std::hypot(b.position.x - 0, b.position.y - 0);
    return distA > distB;
}