/**
 * @file Sudoku.cpp
 * @author Owen
 */

#include "pch.h"
#include "Sudoku.h"
#include "Game.h"

/**
 * Clone this object
 * @return an allocated copy of this object
 */
std::shared_ptr<Item> Sudoku::Clone()
{
    return std::make_shared<Sudoku>(*this);
}
