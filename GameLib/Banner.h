/**
 * @file Banner.h
 * @author Owen
 *
 * Class for banner objects specific
 * to each level/win condition
 */

#ifndef PROJECT1_GAMELIB_BANNER_H
#define PROJECT1_GAMELIB_BANNER_H

#include <string>
#include <memory>

/**
 * Class for banner objects specific
 * to each level/win condition
 */
class Banner
{
private:
    /// Message displayed on banner
    std::string mMessageString;

    /// Title string
    std::string mTitleString;

    /// Indicates whether the banner's time-related functionality is active (true) or not (false).
    bool mBannerShouldDisplay = true;

    /// The elapsed time for the banner, used for time-related operations.
    double mTime = 0;

    /// The Y-coordinate location for the full banner.
    double mYLocFull = 0;

public:
    void DrawLevelIntroBanner(std::shared_ptr<wxGraphicsContext> graphics,int width,int height);

    void DrawGameStatusBanner(std::shared_ptr<wxGraphicsContext> graphics,int width,int height);

    void SetBannerMessage(std::string state);

    void Update(double elapsed);

    void DrawIMFullBanner(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    /**
     * Check if the banner is currently visible.
     *
     * @return True if the banner should be displayed; otherwise, false.
     */
    bool GetBannerVisible() {return mBannerShouldDisplay; }

    /**
     * Reset the banner's display state and timer.
     * This function sets the elapsed time to 0 and allows the banner to be displayed again.
     */
    void ResetBanner() {mTime = 0; mBannerShouldDisplay = true;}

    /**
     * Set the Y-coordinate location for the full banner.
     *
     * @param y The Y-coordinate location to set.
     */
    void SetYLoc(double y) {mYLocFull = y; }

    /**
     * Get the Y-coordinate location of the full banner.
     *
     * @return The Y-coordinate location of the full banner.
     */
    double GetYLoc() {return mYLocFull; }

    /**
     * Compute the x-coordinate for centering an object of the given `textWidth`
     * within a container of `width`.
     *
     * @param width The width of the container.
     * @param textWidth The width of the object to be centered.
     * @return The x-coordinate for centering the object within the container.
     */
    double computeCenteredX(double width, double textWidth) {return (width - textWidth) / 2.0; }

    //    virtual void Accept(Visitor& visitor) override {
    //        visitor.VisitBanner(this);
    //    }
    //
    //    virtual std::unique_ptr<Item> Clone() const override {
    //        return std::make_unique<Banner>(*this);
    //    }
};

#endif //PROJECT1_GAMELIB_BANNER_H
