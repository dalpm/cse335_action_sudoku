/**
 * @file ImageManager.h
 * @author Doruk Alp Mutlu
 *
 *
 */

#ifndef PROJECT1_GAMELIB_IMAGEMANAGER_H
#define PROJECT1_GAMELIB_IMAGEMANAGER_H

#include <vector>
#include <map>
#include <string>
#include "Item.h"

class Game;
/**
 * The ImageManager class is used to store a collection of items, each representing an image.
 */
class ImageManager
{
private:
    /// Map that associates a string ID with a corresponding image filename (in wide string).
    std::map<std::string, std::wstring> mIDFileNameMap;

    /// Map that associates a filename with its corresponding loaded image (bitmap).
    std::map<std::wstring, std::shared_ptr<wxBitmap>> mFileNameBitmapMap;

    /// Map that associates a string ID with a corresponding image filename (in wide string).
    /// Used for items with more than one image.
    std::map<std::string, std::wstring> mIDExtraFileNameMap;

    /// Map that associates a filename with its corresponding loaded image (bitmap).
    /// Used for items with more than one image.
    std::map<std::wstring, std::shared_ptr<wxBitmap>> mExtraFileNameBitmapMap;

    /// Map that associates a filename with its corresponding loaded image (bitmap).
    /// Used for items with more than one image.
    std::map<std::wstring, std::shared_ptr<wxBitmap>> mSpartyFileNameBitmapMap;

public:
    ImageManager(Game* game);

    void InsertFileName(const std::string& id, const std::wstring& name);

    void InsertBitmap(const std::wstring& name);

    std::shared_ptr<wxBitmap> GetBitmap(const std::string& id);

    /**
     * Utility function to get a pointer to this ImageManager instance.
     *
     * @return A pointer to this ImageManager instance.
     */
    ImageManager* GetIM(){return this;}

    void InsertExtraFileName(const std::string &id, const std::wstring &name);

    void InsertBitmapExtra(const std::wstring &name);

    std::shared_ptr<wxBitmap> GetBitmapExtra(const std::string &id);

    void InsertBitmapSparty(const std::wstring& name);

    std::shared_ptr<wxBitmap> GetBitmapSparty(const std::wstring& name);
};

#endif //PROJECT1_GAMELIB_IMAGEMANAGER_H
