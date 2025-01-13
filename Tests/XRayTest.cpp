/**
 * @file XRayTest.cpp
 * @author Doruk Alp Mutlu
 */
#include <pch.h>
#include "gtest/gtest.h"

#include <Game.h>
#include <Level.h>
#include <Item.h>
#include <XRay.h>
#include <Digit.h>
using namespace std;


TEST(XRayTest, Construct)
{
    Game game;
    Level level(&game);
    XRay xray(&level);
    xray.SetGame(&game);
}

TEST(XRayTest, Add)
{
    Game game;
    Level level(&game);
    XRay xray(&level);
    xray.SetGame(&game);

    auto digit1 = std::make_shared<Digit>(&level);
    auto digit2 = std::make_shared<Digit>(&level);
    auto digit3 = std::make_shared<Digit>(&level);

    xray.Add(digit1);
    ASSERT_EQ(1, xray.GetCapacity()) << L"Adding digit";
    xray.Add(digit2);
    ASSERT_EQ(2, xray.GetCapacity()) << L"Adding digit";
    xray.Add(digit3);
    ASSERT_EQ(3, xray.GetCapacity()) << L"Adding digit";
    xray.Add(digit1);
    ASSERT_EQ(3, xray.GetCapacity()) << L"You cannot add the same digit again";
    xray.Add(digit3);
    ASSERT_EQ(3, xray.GetCapacity()) << L"You cannot add the same digit again";

}
