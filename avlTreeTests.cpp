#include "catch.hpp"

#include <cstring>
#include "AVLTree.h"
#include "AVLNode.h"
#include <iostream>
using namespace std;
//
// Created by Frederick Wang on 2/13/20.
//

TEST_CASE("AVL Tree", "[avltree]"){
    AVLTree<int> x;
    int one = 1;
    int two = 2;
    int three = 3;
    int gazorbazorp = 4;
    int chefRamsey = 5;
    int moonAndSun = 6;
    int pickleRick = 7;
    x.addNode(one);
    x.addNode(two);
    x.addNode(three);
    x.addNode(gazorbazorp);
    x.addNode(chefRamsey);
    x.addNode(moonAndSun);
    x.addNode(pickleRick);

    SECTION("Inside vector"){
        REQUIRE(x.getSize() == 7);
        x.dump();
        REQUIRE(x.getSize() == 0);
        REQUIRE(x.isEmpty());
    }

    SECTION("Clear and Length Functions"){
        REQUIRE(x.getContent(one) == 1);
        REQUIRE(x.getContent(two) == 2);
        REQUIRE(x.getContent(three) == 3);
        REQUIRE(x.getContent(gazorbazorp) == 4);
        REQUIRE(x.getContent(chefRamsey) == 5);
        REQUIRE(x.getContent(moonAndSun) == 6);
        REQUIRE(x.getContent(pickleRick) == 7);
    }
}