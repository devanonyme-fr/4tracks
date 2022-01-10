#include "audiotrack.h"

#include "QDebug"

namespace Audio {

AudioTrack::AudioTrack(QString name, int index) : mName(name), mIndex(index)
{

}

QString AudioTrack::getName() const
{
    return mName;
}

int AudioTrack::getType() const
{
    if (mClips.size() == 0)
        return ANY_TRACK;

    return mClips.at(0)->getType() == Clip::AUDIO_CLIP ? AUDIO_TRACK : MIDI_TRACK;
}

bool AudioTrack::addClip(std::shared_ptr<Clip> clip)
{
    if (clip->getType() == Clip::AUDIO_CLIP && getType() == AUDIO_TRACK)
    {
        mClips.push_back(clip);
        resizeClipsWhenClipAdded(mClips.size() - 1);
    }
    else if (clip->getType() == Clip::MIDI_CLIP && getType() == MIDI_TRACK)
    {
        mClips.push_back(clip);
        resizeClipsWhenClipAdded(mClips.size() - 1);
    }
    else if (getType() == ANY_TRACK)
        mClips.push_back(clip);
    else
        return false;

    onClipAdded();

    return true;
}

std::vector<std::shared_ptr<Clip>> AudioTrack::getClips()
{
    return mClips;
}

int AudioTrack::getIndex() const
{
    return mIndex;
}

void AudioTrack::setIndex(int newPosition)
{
    mIndex = newPosition;
}

void AudioTrack::setVolume(double newVolume)
{
    mVolume = newVolume;
}

double AudioTrack::getVolume() const
{
    return mVolume;
}

void AudioTrack::setPan(double newPan)
{
    mPan = newPan;
}

double AudioTrack::getPan() const
{
    return mPan;
}

void AudioTrack::resizeClipsWhenClipAdded(int newClipIndex)
{

}

void AudioTrack::setNextReadPosition(juce::int64 newPosition)
{
    mPositionInSamples = newPosition;
    mClipPlaying = nullptr;

    for (auto clip : mClips) {
        if (clip->getPositionInSamples() <= mPositionInSamples && clip->getPositionInSamples() + clip->getLengthInSamples() >= mPositionInSamples) {
            mClipPlaying = clip;
            break;
        }
    }

    if (mClipPlaying != nullptr)
        mClipPlaying->setReadPosition(newPosition);
}

juce::int64 AudioTrack::getNextReadPosition() const
{
    return mPositionInSamples;
}

juce::int64 AudioTrack::getTotalLength() const
{
    int max = 0;
    for (auto clip : mClips) {
        max = juce::jmax(clip->getPositionInSamples() + clip->getLengthInSamples(), max);
    }

    return max;
}

bool AudioTrack::isLooping() const
{
    return false;
}

void AudioTrack::setLooping(bool) {}

void AudioTrack::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    mPositionInSamples = 0;
    if (getType() == AUDIO_TRACK)
    {
        for (auto clip : mClips)
        {
            std::dynamic_pointer_cast<AudioClip>(clip)->prepareToPlay(samplesPerBlockExpected, sampleRate);
        }
    }
}

void AudioTrack::releaseResources()
{}

void AudioTrack::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
{
    if (mClipPlaying == nullptr)
        bufferToFill.clearActiveBufferRegion();


    else {
        if (getType() == AUDIO_TRACK)
        {
            std::dynamic_pointer_cast<AudioClip>(mClipPlaying)->getNextAudioBlock(bufferToFill);
        }

        bufferToFill.buffer->applyGain(mVolume);

        // pan
        if (mPan != 0)
        {
            bufferToFill.buffer->applyGain(0, 0, bufferToFill.buffer->getNumSamples(), 1-mPan);
            bufferToFill.buffer->applyGain(1, 0, bufferToFill.buffer->getNumSamples(), 1+mPan);
        }
    }

    setNextReadPosition(getNextReadPosition() + bufferToFill.numSamples);
}

}
