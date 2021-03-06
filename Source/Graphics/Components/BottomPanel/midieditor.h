#ifndef MIDIEDITOR_H
#define MIDIEDITOR_H

#include <QtWidgets>

#include "Audio/Project/project.h"
#include "Constants.h"
#include "Utils/utils.h"
#include "Audio/Clip/midiclip.h"
#include "Graphics/Components/Timeline/divisionsmarker.h"
#include "Audio/Resources/mididata.h"
#include "Audio/Resources/midinote.h"
#include "midinote.h"
#include "Graphics/Managers/selectionmanager.h"

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
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void pixelsPerBeatAmountChanged(double newPixelsPerBeatAmount);

private:
    void setupMidiNotes();

    QSharedPointer<Audio::MidiClip> mClip;
    QVector<QPointer<MidiNote>> mNotes;

    QPoint mClickedPos;
    SelectionManager mCurrentSelection;

    bool mExtendingByTheRight = false;
    bool mExtendingByTheLeft = false;

    double mCurrentPixelsPerBeatAmount{};
};

} // Graphics

#endif //MIDIEDITOR_H
