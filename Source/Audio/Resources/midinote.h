#ifndef AUDIO_MIDINOTE_H
#define AUDIO_MIDINOTE_H

#include <QtWidgets>
#include "Audio/JuceIncludes.h"

namespace Audio
{

class MidiNote: public QObject
{
Q_OBJECT

public:
    MidiNote(juce::int64 positionInSamples, const juce::MidiMessage &midiMessage);

    [[nodiscard]] juce::int64 getPositionInSamples() const;
    void setPositionInSamples(juce::int64 positionInSamples);

    [[nodiscard]] const juce::MidiMessage &getMidiMessage() const;
    void setMidiMessage(const juce::MidiMessage &midiMessage);

    [[nodiscard]] const QSharedPointer<MidiNote> &getNoteOffObject() const;
    void setNoteOffObject(const QSharedPointer<MidiNote> &noteOffObject);

signals:
    void dataChanged();

private:
    juce::int64 mPositionInSamples = 0;
    juce::MidiMessage mMidiMessage;
    QSharedPointer<MidiNote> mNoteOffObject;
};

}


#endif //AUDIO_MIDINOTE_H
