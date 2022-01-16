#include "clip.h"

namespace Audio
{

Clip::Clip(std::weak_ptr<Track> parentTrack)
    : mParentTrack(parentTrack)
{

}

void Clip::setName(QString name)
{
    mName = name;
}

QString Clip::getName() const
{
    return mName;
}

QString Clip::getSourceFilePath() const
{
    return mSourceFilePath;
}

int Clip::getPositionInSamples() const
{
    return mPositionInSamples;
}

void Clip::setClipPositionInSamples(int newPosition)
{
    mPositionInSamples = newPosition;
    clipMoved();
}

int Clip::getLengthInSamples() const
{
    return mLengthInSamples;
}

void Clip::setReadPosition(int newPosition)
{
    mNextReadPosition = newPosition;
    nextReadPositionChanged();
}

int Clip::getReadPosition() const
{
    return mNextReadPosition;
}

std::weak_ptr<Track> Clip::getParentTrack()
{
    return mParentTrack;
}

}
