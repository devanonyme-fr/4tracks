#ifndef GRAPHICS_CLIPSGRID_H
#define GRAPHICS_CLIPSGRID_H

#include "Audio/project.h"
#include "graphics_clip.h"
#include "utils_functions.h"
#include "positionbaroverlay.h"
#include "selectionoverlay.h"
#include "selection.h"

#include <QWidget>
#include <QStyleOption>
#include <QLayout>
#include <QPainter>
#include <QTimer>

namespace Graphics {

class ClipsGrid : public QWidget, public Selection::Callback
{
    Q_OBJECT
public:
    explicit ClipsGrid(std::shared_ptr<Selection> currentSelection, QWidget *parent = nullptr);

    void refreshBpm(double bpm);
    void setProject(std::shared_ptr<Audio::Project> project);

    void refreshClips();

    void refreshZoomLevel(double newZoomLevel);
    double getZoomLevel() const;

    double getDivision() const;

    int roundPosition(int positionInSamples) const;

    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void selectionChanged() override;

public slots:
    void drawPositionBar();

private:
    double mBpm;
    double mZoomLevel = 1.f;
    double mPixelsPerBeat;

    std::shared_ptr<Selection> mCurrentSelection;
    std::shared_ptr<Audio::Project> mProject;

    PositionBarOverlay mPositionBarWidget;
    QTimer mPositionBarTimer;
    SelectionOverlay mSelectionOverlay;

    QVector<std::shared_ptr<Clip>> mClips;
};

} // namespace Graphics

#endif // GRAPHICS_CLIPSGRID_H
