#pragma once
#include "Word.h"
#include <cmath>

struct WordPriority {
    bool operator()(const Word& a, const Word& b) const;
};
