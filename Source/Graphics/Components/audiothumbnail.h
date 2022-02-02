#ifndef GRAPHICS_AUDIOTHUMBNAIL_H
#define GRAPHICS_AUDIOTHUMBNAIL_H

#include <QtWidgets>
#include "Audio/Clip/audioclip.h"

namespace Graphics
{

class AudioThumbnail
{
public:
    AudioThumbnail();

    void loadThumbnail(const QSharedPointer<Audio::AudioClip> &clip, int sourceSamplesPerThumbnailSample);
    void drawThumbnail(QPainter &p, QRect rect);

private:
    class MinMaxValues;

    std::vector<MinMaxValues> mThumbnailValues;
};

class AudioThumbnail::MinMaxValues
{
public:
    MinMaxValues(float min, float max)
        : mMin(min), mMax(max)
    {};

    [[nodiscard]] float getMinValue() const
    { return mMin; };
    [[nodiscard]] float getMaxValue() const
    { return mMax; };

private:
    float mMin, mMax;
};

} // namespace Graphics

#endif // GRAPHICS_AUDIOTHUMBNAIL_H
