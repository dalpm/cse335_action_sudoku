/**
 * @file SpartyTest.cpp
 * @author Doruk Alp Mutlu
 */
#include <pch.h>
#include "gtest/gtest.h"

#include <Game.h>
#include <Level.h>
#include <Item.h>
#include <SpartyFinder.h>
#include <Sparty.h>
using namespace std;

TEST(SpartyTest, Construct){
    Game game;
    Level level(&game);
    Sparty sparty(&level);
    sparty.SetGame(&game);
}

TEST(SpartyTest, Attributes){
    Game game;
    game.LoadFiles();
    game.SetLevel(1);

    SpartyFinder visitor;
    game.Accept(&visitor);
    auto sparty =  visitor.GetSparty();

    ASSERT_EQ(sparty->GetTargetOffsetX(), 72);

    ASSERT_EQ(sparty->GetTargetOffsetY(), 24);
}