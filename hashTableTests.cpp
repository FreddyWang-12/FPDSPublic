#include "catch.hpp"

#include <cstring>
#include "hashTable.h"
#include <iostream>
using namespace std;


TEST_CASE("HashTable class", "[hashtable]"){

    hashTable<string, int> x;
    x.addNewKey("hello", 1);
    x.addNewKey("hello", 2);
    x.addNewKey("hello", 3);
    x.addNewKey("nice", 1);
    x.addNewKey("new", 2);

    SECTION("emptyAt") {
        REQUIRE(x.emptyAt("not"));
        REQUIRE(!x.emptyAt("hello"));
        REQUIRE(!x.emptyAt("nice"));
        REQUIRE(!x.emptyAt("new"));
    }

    SECTION("getDataList"){
        LinkedList<int> y = x.getDataList("hello");
        REQUIRE(y.findValue(1));
        REQUIRE(y.findValue(2));
        REQUIRE(y.findValue(3));
    }

    SECTION("clear"){
        REQUIRE(x.getSize() == 5);
        x.clear();
        REQUIRE(x.getSize() == 0);
        REQUIRE(x.getCapacity() == 250000);
    }
}
