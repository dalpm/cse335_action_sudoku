/**
 * @file XRay.h
 * @author Owen
 *
 * Class for XRay item
 */

#ifndef PROJECT1_GAMELIB_XRAY_H
#define PROJECT1_GAMELIB_XRAY_H

#include "Item.h"
#include <algorithm>

/**
 * Class for XRay item
 */
class XRay : public Item {
private:
    /// Maximum number of digits that can be put inside the XRay
    int mMaxCapacity = 0;

    /// How many items can be in the XRay
    int mCapacity = 0;

    /// A vector of the content in the XRay
    std::vector<std::shared_ptr<Item>> mXRayContent;

public:
    /// Default constructor (disabled)
    XRay() = delete;

    /**
     * Disabled copy constructor.
     * @param other The XRay object to copy from.
     */
    XRay(const XRay &);

    /// Assignment operator
    void operator=(const XRay &) = delete;

    void XmlLoad(wxXmlNode* node) override;

    XRay(Level *level);

    /// Inside XRay class declaration in XRay.h
    std::shared_ptr<Item> Clone() override;

    void Add(std::shared_ptr<Item> item);

    std::shared_ptr<Item> GetItem(int num);

    void Remove(std::shared_ptr<Item> item);

    bool CheckIfContainsNum(int num);

    bool CheckIfContainsParticularNum(std::shared_ptr<Item> itemToSearch);

    /**
     * Accept an item visitor for interaction.
     *
     * This method is used to accept a visitor object, allowing it to interact with
     * the XRay item, although no specific action is performed in this overridden implementation.
     *
     * @param visitor The visitor object to accept.
     */
    void Accept(ItemVisitor* visitor) override {visitor->XRayVisitor(this); }

    /**
     * Getter function to get the value of xray capacity
     *
     * @return Capacity of XRay items
     */
    int GetCapacity() const {return mCapacity; }

    /**
     * Getter function to get the value of xray capacity
     *
     * @return Capacity of XRay items
     */
    int GetMaxCapacity() const {return mMaxCapacity; }


};

#endif //PROJECT1_GAMELIB_XRAY_H
