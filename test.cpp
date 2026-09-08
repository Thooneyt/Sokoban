// Copyright 2026 Dr. Daly
// Editted by Soon Thao
// Unit tests for PS3b
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Sokoban Tests

#include <iostream>
#include <string>
#include <fstream>


#include <boost/test/unit_test.hpp>

#include "Sokoban.hpp"


using sf::Image;
using sf::Vector2u;
using SB::Sokoban;
using SB::Direction;

BOOST_AUTO_TEST_CASE(TestIsWinAndPlayerLoc) {
    Sokoban Testgame;
    std::ifstream Inputfile("levels/autograder/autowin.lvl");
    if (!Inputfile) {
        throw std::runtime_error("Error: Could not open file!");
    }
    Inputfile >> Testgame;
    BOOST_REQUIRE(Testgame.playerLoc() == sf::Vector2u({2, 2}));
    BOOST_REQUIRE(Testgame.isWon() == true);
}

BOOST_AUTO_TEST_CASE(TestMovePlayers) {
    Sokoban Testgame;
    std::ifstream Inputfile("levels/autograder/level1.lvl");
    if (!Inputfile) {
        throw std::runtime_error("Error: Could not open file!");
    }
    Inputfile >> Testgame;
    sf::Vector2u prevPlayerLoc = Testgame.playerLoc();
    Testgame.movePlayer(Direction::Up);
    BOOST_REQUIRE(prevPlayerLoc != Testgame.playerLoc());
    prevPlayerLoc = Testgame.playerLoc();
    Testgame.movePlayer(Direction::Right);
    BOOST_REQUIRE(prevPlayerLoc == Testgame.playerLoc());
}

BOOST_AUTO_TEST_CASE(TestPlayerOffScreen) {
    Sokoban Testgame;
    std::ifstream Inputfile("testcases2.lvl");
    Inputfile >> Testgame;
    sf::Vector2u prevPlayerLoc = Testgame.playerLoc();
    Testgame.movePlayer(Direction::Right);
    prevPlayerLoc = Testgame.playerLoc();
    Testgame.movePlayer(Direction::Right);
    BOOST_REQUIRE(prevPlayerLoc == Testgame.playerLoc());
}

BOOST_AUTO_TEST_CASE(TestBoxCollision) {
    Sokoban Testgame;
    std::ifstream Inputfile("testcases.lvl");
    Inputfile >> Testgame;
    sf::Vector2u prevPlayerLoc = Testgame.playerLoc();
    Testgame.movePlayer(Direction::Left);
    BOOST_REQUIRE(prevPlayerLoc == Testgame.playerLoc());
    Testgame.movePlayer(Direction::Down);
    prevPlayerLoc = Testgame.playerLoc();
    Testgame.movePlayer(Direction::Left);
    prevPlayerLoc = Testgame.playerLoc();
    Testgame.movePlayer(Direction::Up);
    BOOST_REQUIRE(prevPlayerLoc == Testgame.playerLoc());
}

BOOST_AUTO_TEST_CASE(TestMoreBoxesThanTargets) {
    Sokoban Testgame;
    std::ifstream Inputfile("testcases3.lvl");
    Inputfile >> Testgame;
    BOOST_REQUIRE(Testgame.isWon() == false);
    Testgame.movePlayer(Direction::Down);
    BOOST_REQUIRE(Testgame.isWon() == true);
}

BOOST_AUTO_TEST_CASE(TestMoreTargetsThanBoxes) {
    Sokoban Testgame;
    std::ifstream Inputfile("testcases4.lvl");
    Inputfile >> Testgame;
    BOOST_REQUIRE(Testgame.isWon() == false);
    Testgame.movePlayer(Direction::Left);
    BOOST_REQUIRE(Testgame.isWon() == true);
}

BOOST_AUTO_TEST_CASE(TestMisreadSymbols) {
    Sokoban Testgame;
    std::stringstream input("2 3\n#.@\nAa1\n");
    input >> Testgame;
    std::stringstream output;
    output << Testgame;
    BOOST_REQUIRE(output.str() == input.str());
}
