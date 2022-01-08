#ifndef GRAPHICS_TIMELINE_H
#define GRAPHICS_TIMELINE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QStyleOption>
#include <vector>
#include "track.h"
#include "selection.h"
#include "clipsgrid.h"
#include "../Audio/project.h"
#include "../Audio/clip.h"
#include "utils_functions.h"

namespace Graphics {
    class Timeline;
}

class Graphics::Timeline : public QWidget
{
    Q_OBJECT
public:
    Timeline(QWidget *parent = nullptr);

    void setProject(std::shared_ptr<Audio::Project> project);
    void displayTracks();

    void refreshZoomLevel(double newZoomLevel);
    double getZoomLevel() const;

    void refreshBpm();

    double getDivision() const;

    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:

private:
    std::shared_ptr<Audio::Project> mProject;
    std::unique_ptr<ClipsGrid> mClipsGrid;
    QHBoxLayout mMainLayout;
    QVBoxLayout mTracksLayout;
    QPushButton mAddTrackButton;
    QWidget mTracksWidget;

    QWidget mSpacerWidget;

    std::shared_ptr<Selection> mCurrentSelection;

    std::vector<std::shared_ptr<Track>> mTracks;

    double mZoomLevel = 1.f;
};

#endif // TIMELINE_H
