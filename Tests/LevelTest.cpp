/**
 * @file LevelTest.cpp
 * @author popov
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <Game.h>
#include <Level.h>
#include <string>
#include <wx/filename.h>


class LevelTest : public ::testing::Test{
protected:

};

TEST_F(LevelTest, LoadLevel1) {
    // Create a path to temporary files
    Game game1;

    Level level(&game1);

    std::wstring filename1 = L"levels/level1.xml";

    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename1))
    {
        wxMessageBox(L"Unable to load Level file");
        return;
    }

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();
    level.XmlLevel(root);

    ASSERT_EQ(level.GetHeight(), 15);
    ASSERT_EQ(level.GetWidth(), 20);
    ASSERT_EQ(level.GetTileHeight(), 48);
    ASSERT_EQ(level.GetTileWidth(), 48);

    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"game"){
            level.XmlGame(child);
        }
        else if(name == L"declarations"){
            auto item = child->GetChildren();
            level.XmlDeclarations(item);
        }
        else if(name == L"items"){
            auto item = child->GetChildren();
            level.XmlItems(item);
        }
    }

    auto items = level.GetItems();

    ASSERT_EQ(items.size(), 84);
}

TEST_F(LevelTest, LoadLevel2) {
    // Create a path to temporary files
    Game game2;

    Level level(&game2);

    std::wstring filename = L"levels/level2.xml";

    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Level file");
        return;
    }

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();
    level.XmlLevel(root);

    ASSERT_EQ(level.GetHeight(), 20);
    ASSERT_EQ(level.GetWidth(), 30);
    ASSERT_EQ(level.GetTileHeight(), 48);
    ASSERT_EQ(level.GetTileWidth(), 48);

    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"game"){
            level.XmlGame(child);
        }
        else if(name == L"declarations"){
            auto item = child->GetChildren();
            level.XmlDeclarations(item);
        }
        else if(name == L"items"){
            auto item = child->GetChildren();
            level.XmlItems(item);
        }
    }

    auto items = level.GetItems();

    ASSERT_EQ(items.size(), 71);
}