#ifndef MIDIEDITOR_H
#define MIDIEDITOR_H

#include <QtWidgets>

#include "Audio/Project/project.h"
#include "Constants.h"
#include "Utils/utils_functions.h"
#include "Audio/Clip/midiclip.h"
#include "divisionsmarker.h"
#include "midinote.h"

namespace Graphics
{

class MidiEditor: public QWidget
{
    Q_OBJECT
public:
    explicit MidiEditor(const QSharedPointer<Audio::MidiClip> &clip, QWidget *parent = nullptr);

    [[nodiscard]] double calculatePixelsPerBeatAmount() const;

    void refreshMidiNotes();

    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

signals:
    void pixelsPerBeatAmountChanged(double newPixelsPerBeatAmount);

private:
    QSharedPointer<Audio::MidiClip> mClip;
    QVector<QPointer<MidiNote>> mNotes;

    double mCurrentPixelsPerBeatAmount{};
};

} // Graphics

#endif //MIDIEDITOR_H
