#include "mini_unordered_map.h"
#include <cassert>
#include <string>

int main() {
    MiniUnorderedMap<std::string, std::string> m;
    m["a"] = std::string(1000, 'x');
    m["b"] = std::string(2000, 'y');

    assert(m.at("a").size() == 1000);
    m.erase("a");
    m.clear();
    assert(m.size() == 0);
}