/**
 * @file Level.cpp
 * @author mdoru
 */

#include "pch.h"
#include "Level.h"

#include <string>
#include <sstream>

#include "Game.h"
#include "Container.h"
#include "Digit.h"
#include "Given.h"
#include "Sparty.h"
#include "XRay.h"
#include "Background.h"
#include "VisitContainer.h"

/**
 * Load item declarations from XML data.
 * @param node The XML node containing item declarations.
 */
void Level::XmlDeclarations(wxXmlNode *node){
    for(; node; node=node->GetNext()){
        std::shared_ptr<Item> item;
        auto name_item = node->GetName();
        std::string id = node->GetAttribute(L"id").ToStdString();

        if (name_item == L"given"){
            item = std::make_shared<Given>(this);
        }
        else if(name_item == L"digit"){
            item = std::make_shared<Digit>(this);
        }
        else if(name_item == L"sparty"){
            item = std::make_shared<Sparty>(this);
        }
        else if(name_item == L"background"){
            item = std::make_shared<Background>(this);
        }
        else if(name_item == L"xray"){
            item = std::make_shared<XRay>(this);
        }
        else if(name_item == L"container"){
            item = std::make_shared<Container>(this);
            auto container_node = node->GetChildren();
            for (;container_node; container_node=container_node->GetNext()){
                auto item_digit = std::make_shared<Digit>(this);
                std::string ct_id = container_node->GetAttribute(L"id").ToStdString();
                item_digit->XmlLoad(container_node);
                mMapDeclarations[ct_id] = item_digit;
            }
        }
        if (item != nullptr)
        {
            item->XmlLoad(node);
            mMapDeclarations[id] = item;
        }
    }
}

/**
 * Load game items from XML data.
 * @param node The XML node containing game items.
 */
void Level::XmlItems(wxXmlNode *node){
    for(; node; node=node->GetNext()){
        auto name_item = node->GetName();
        std::string id = node->GetAttribute(L"id").ToStdString();
        auto item = mMapDeclarations[id];
        double col, row;
        node->GetAttribute(L"col", L"0").ToDouble(&col);
        node->GetAttribute(L"row", L"0").ToDouble(&row);
        item->SetRow(row);
        item->SetColumn(col);

        std::shared_ptr<Item> item_to_add = item->Clone();


        mLevelItems.push_back(item_to_add);

        if (name_item == L"container"){
            VisitContainer visitor;
            item_to_add->Accept(&visitor);
            auto container = visitor.GetContainer();
            auto container_node = node->GetChildren();
            for(;container_node; container_node = container_node->GetNext()){
                std::string ct_id = container_node->GetAttribute(L"id").ToStdString();
                auto ct_item = mMapDeclarations[ct_id];
                std::shared_ptr<Item> ct_item_to_add = ct_item->Clone();

                double ct_col, ct_row;
                container_node->GetAttribute(L"col", L"0").ToDouble(&ct_col);
                container_node->GetAttribute(L"row", L"0").ToDouble(&ct_row);
                ct_item_to_add->SetRow(ct_row);
                ct_item_to_add->SetColumn(ct_col);

                mImageManager->InsertFileName(ct_item_to_add->GetID() ,ct_item_to_add->GetImage());

                container->AddDigit(ct_item_to_add);
            }
        }
    }

}


void Level::XmlLevel(wxXmlNode *node){
    long w, h, tw, th;
    node->GetAttribute(L"width", L"0").ToLong(&w);
    node->GetAttribute(L"height", L"0").ToLong(&h);
    node->GetAttribute(L"tilewidth", L"0").ToLong(&tw);
    node->GetAttribute(L"tileheight", L"0").ToLong(&th);

    mLevelWidth = (int) w;
    mLevelHeight = (int) h;
    mLevelTileWidth = (int) tw;
    mLevelTileHeight = (int) th;
}

void Level::XmlGame(wxXmlNode *node) {
    // Load starting coordinates from XML attributes
    long startCol, startRow;
    node->GetAttribute(L"col", L"0").ToLong(&startCol);
    node->GetAttribute(L"row", L"0").ToLong(&startRow);
    mStartCol = (int) startCol;
    mStartRow = (int) startRow;

    std::string game_sol = std::string(node->GetChildren()->GetContent());
    std::stringstream numstream;
    numstream << game_sol;
    int num;

    // Dynamically determine matrix dimensions
    int dimension = std::sqrt(std::count(game_sol.begin(), game_sol.end(), ' ')+ 1);

    for (int i = 0; i < dimension; ++i) {
        std::vector<int> sub_vec;
        for (int j = 0; j < dimension; ++j) {
            numstream >> num;
            sub_vec.push_back(num);
        }
        mSolution.push_back(sub_vec);
    }
}


/**
 * The constructor for the Level class.
 *
 * @param game Pointer to the game instance associated with this level.
 */
Level::Level(Game* game) {
    mGame = game;
    mImageManager = mGame->GetIM();
}


