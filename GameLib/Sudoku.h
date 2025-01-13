/**
 * @file Sudoku.h
 * @author Owen
 *
 * ???
 */

#ifndef PROJECT1_GAMELIB_SUDOKU_H
#define PROJECT1_GAMELIB_SUDOKU_H

#include "Item.h"

/**
 * The Sudoku class
 */
class Sudoku : public Item {
private:

public:
    /**
     * Accepts an item visitor for interaction.
     *
     * This method allows the provided visitor to interact with
     * the Sparty digit grabber item, although no specific action is performed
     * in this overridden implementation.
     *
     * @param visitor The visitor object to accept.
     */
    void Accept(ItemVisitor* visitor) override {}

    std::shared_ptr<Item>Clone() override;


};

#endif //PROJECT1_GAMELIB_SUDOKU_H
