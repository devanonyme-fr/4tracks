#ifndef GRAPHICS_GRAPHICS_CLIP_H
#define GRAPHICS_GRAPHICS_CLIP_H

#include <QtWidgets>

#include "Audio/Clip/audioclip.h"
#include "Audio/Clip/clip.h"
#include "Audio/Track/track.h"
#include "Graphics/Widgets/elidedlabel.h"
#include "audiothumbnail.h"
#include "Audio/Project/project.h"
#include "Graphics/Managers/selectionmanager.h"
#include "Graphics/Managers/thumbnailmanager.h"

namespace Graphics
{

namespace Ui
{
class Clip;
}

class Clip: public SelectionManager::SelectableObject
{
Q_OBJECT

public:
    explicit Clip(const QSharedPointer<ThumbnailManager> &thumbnailManager, QWidget *parent = nullptr);
    ~Clip() override;

    void setClip(const QSharedPointer<Audio::Clip> &clip);
    QSharedPointer<Audio::Clip> getClip();

    [[nodiscard]] bool shouldMoveClip(QPoint mousePosition) const;

    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *) override;

    void setSelectedState(bool isSelected) override;
    [[nodiscard]] SelectionManager::SelectableObject::Type getType() const override;

private:
    Ui::Clip *ui;
    ElidedLabel mLabel;
    QSharedPointer<Audio::Clip> mClip;
    QSharedPointer<ThumbnailManager> mThumbnailManager;
};

} // namespace Graphics
#endif // GRAPHICS_GRAPHICS_CLIP_H
