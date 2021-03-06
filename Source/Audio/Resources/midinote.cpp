#include "midinote.h"

namespace Audio
{

MidiNote::MidiNote(juce::int64 positionInSamples, const juce::MidiMessage &midiMessage)
    : mPositionInSamples(positionInSamples), mMidiMessage(midiMessage)
{}

juce::int64 MidiNote::getPositionInSamples() const
{
    return mPositionInSamples;
}

void MidiNote::setPositionInSamples(juce::int64 positionInSamples)
{
    mPositionInSamples = positionInSamples;
    emit dataChanged();
}

const juce::MidiMessage &MidiNote::getMidiMessage() const
{
    return mMidiMessage;
}

void MidiNote::setMidiMessage(const juce::MidiMessage &midiMessage)
{
    mMidiMessage = midiMessage;
    emit dataChanged();
}

const QSharedPointer<MidiNote> &MidiNote::getNoteOffObject() const
{
    return mNoteOffObject;
}

void MidiNote::setNoteOffObject(const QSharedPointer<MidiNote> &noteOffObject)
{
    mNoteOffObject = noteOffObject;
    emit dataChanged();
}

}