/**
 * @file Container.h
 * @author Owen
 *
 * Class for item of type container
 */

#ifndef PROJECT1_GAMELIB_CONTAINER_H
#define PROJECT1_GAMELIB_CONTAINER_H

#include <vector>
#include "Item.h"

/**
 * Class for a container item
 */
class Container : public Item
{
private:
    /// Represents the front of the container.
    std::wstring mFrontImageName;

    /// Holds the items within the container.
    std::vector<std::shared_ptr<Item>> mItems;

public:
    /// Default constructor (disabled)
    Container() = delete;

    /**
     * Disabled copy constructor.
     * @param other The XRay object to copy from.
     */
    Container(const Container &);

    /// Assignment operator
    void operator=(const Container &) = delete;

    void XmlLoad(wxXmlNode* node) override;

    Container(Level *level);

    std::shared_ptr<Item> Clone() override;

    void AddDigit(std::shared_ptr<Item>);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<wxBitmap>) override;

    std::shared_ptr<Item> GetItem();

    void Remove(std::shared_ptr<Item> item);

    /**
     * Accept an item visitor for interaction.
     *
     * This method is used to accept a visitor object, allowing it to interact with
     * the Container item, although no specific action is performed in this overridden implementation.
     *
     * @param visitor The visitor object to accept.
     */
    void Accept(ItemVisitor* visitor) override {visitor->ContainerVisitor(this); }

    /**
     * Check if a point (x, y) is within the container's boundaries.
     *
     * This function checks whether a point with the specified x and y coordinates falls
     * within the boundaries of the container.
     *
     * @param x The x-coordinate of the point to check.
     * @param y The y-coordinate of the point to check.
     * @return True if the point is within the container, otherwise false.
     */
    bool HitTest(double x, double y) override;
};

#endif //PROJECT1_GAMELIB_CONTAINER_H
