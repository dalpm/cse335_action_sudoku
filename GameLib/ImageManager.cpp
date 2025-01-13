/**
 * @file ImageManager.cpp
 * @author Doruk Alp Mutlu
 */

#include "pch.h"
#include "ImageManager.h"

/**
 * Constructor for the ImageManager class.
 * Initializes the ImageManager associated with a given game instance.
 *
 * @param game Pointer to the game instance.
 */
ImageManager::ImageManager(Game* game){

}

/**
 * Maps an ID to a filename and then inserts the image (bitmap) associated
 * with that filename into the bitmap map.
 *
 * @param id The ID to associate with the filename.
 * @param name The filename of the image.
 */
void ImageManager::InsertFileName(const std::string& id, const std::wstring& name)
{
    mIDFileNameMap[id] = name;
    InsertBitmap(name);
}


/**
 * Maps an ID to a filename and then inserts the image (bitmap) associated
 * with that filename into the bitmap map.
 * Used for items with more than one image.
 *
 * @param id The ID to associate with the filename.
 * @param name The filename of the image.
 */
void ImageManager::InsertExtraFileName(const std::string& id, const std::wstring& name)
{
    mIDExtraFileNameMap[id] = name;
    InsertBitmapExtra(name);
}

/**
 * Inserts a bitmap into the filename to bitmap map if it doesn't already exist.
 * This method ensures that each image file is only loaded once into memory.
 *
 * @param name The filename of the image to insert.
 */
void ImageManager::InsertBitmap(const std::wstring& name){
    if(mFileNameBitmapMap.find(name) == mFileNameBitmapMap.end()){
        std::shared_ptr<wxBitmap> image = std::make_shared<wxBitmap>("images/" +name, wxBITMAP_TYPE_ANY);
        mFileNameBitmapMap[name] = image;
    }
}

/**
 * Inserts a bitmap into the filename to bitmap map if it doesn't already exist.
 * This method ensures that each image file is only loaded once into memory.
 * Used for items with more than one image.
 *
 * @param name The filename of the image to insert.
 */
void ImageManager::InsertBitmapExtra(const std::wstring& name){
    if(mExtraFileNameBitmapMap.find(name) == mExtraFileNameBitmapMap.end()){
        std::shared_ptr<wxBitmap> image = std::make_shared<wxBitmap>("images/" +name, wxBITMAP_TYPE_ANY);
        mExtraFileNameBitmapMap[name] = image;
    }
}

/**
 * Retrieves a bitmap from the filename to bitmap map using an ID.
 * This method first looks up the filename associated with the ID and
 * then retrieves the corresponding bitmap.
 *
 * @param id The ID associated with the desired image.
 * @return A shared pointer to the corresponding bitmap.
 */
std::shared_ptr<wxBitmap> ImageManager::GetBitmap(const std::string& id){
    auto name = mIDFileNameMap[id];
    return mFileNameBitmapMap[name];
}


/**
 * Retrieves a bitmap from the filename to bitmap map using an ID.
 * This method first looks up the filename associated with the ID and
 * then retrieves the corresponding bitmap.
 * Used for items with more than one image.
 *
 * @param id The ID associated with the desired image.
 * @return A shared pointer to the corresponding bitmap.
 */
std::shared_ptr<wxBitmap> ImageManager::GetBitmapExtra(const std::string& id){
    auto name = mIDExtraFileNameMap[id];
    return mExtraFileNameBitmapMap[name];
}

/**
 * Inserts a bitmap into the filename to bitmap map if it doesn't already exist.
 * This method ensures that each image file is only loaded once into memory.
 * Used for items with more than one image.
 *
 * @param name The filename of the image to insert.
 */
void ImageManager::InsertBitmapSparty(const std::wstring& name){
    if(mSpartyFileNameBitmapMap.find(name) == mSpartyFileNameBitmapMap.end()){
        std::shared_ptr<wxBitmap> image = std::make_shared<wxBitmap>(name, wxBITMAP_TYPE_ANY);
        mSpartyFileNameBitmapMap[name] = image;
    }
}

/**
 * Retrieves a bitmap from the filename to bitmap map using an ID.
 * This method first looks up the filename associated with the ID and
 * then retrieves the corresponding bitmap.
 * Used for items with more than one image.
 *
 * @param name The name associated with the desired image.
 * @return A shared pointer to the corresponding bitmap.
 */
std::shared_ptr<wxBitmap> ImageManager::GetBitmapSparty(const std::wstring& name){
    return mSpartyFileNameBitmapMap[name];
}

