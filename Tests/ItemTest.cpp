/**
 * @file ItemTest.cpp
 * @author popov
 */

#include <pch.h>
#include "gtest/gtest.h"

#include <Game.h>
#include <Level.h>
#include <Item.h>
#include <ItemVisitor.h>
using namespace std;

class ItemMock : public Item {
public:
    ItemMock(Level *level) : Item(level) {}

    virtual void Accept(ItemVisitor* visitor){}

    virtual std::shared_ptr<Item> Clone(){return std::make_shared<ItemMock>(*this);}
};

TEST(ItemTest, Construct) {
    Game game;
    Level level(&game);
    ItemMock item(&level);
}

TEST(ItemTest, HitTest){
    Game game;
    Level level(&game);
    ItemMock item(&level);

    game.LoadFiles();
    game.SetLevel(1);

    item.SetColumn(4);
    item.SetRow(3);
    item.SetGame(&game);

    ASSERT_EQ(item.GetColumn(), 4);

    ASSERT_EQ(item.GetRow(), 3);

    item.SetDisplayProperties();

    ASSERT_FALSE(item.HitTest(3.0, 4.0)) << L"testing when Sparty is at the top of the digit";

    ASSERT_TRUE(item.HitTest(3.0, 3.5)) << L"testing when Sparty is at an acceptable height from the digit";

    ASSERT_TRUE(item.HitTest(3.0, 2.5)) << L"testing when Sparty is at an acceptable height from the digit";

    ASSERT_FALSE(item.HitTest(2.0, 3.0)) << L"testing when Sparty is too left of the digit";

    ASSERT_TRUE(item.HitTest(2.75, 3.0)) << L"testing when Sparty is close enough to the digit";

    ASSERT_FALSE(item.HitTest(2.25, 3.0)) << L"testing when Sparty is close enough but at the other side of the digit";
}