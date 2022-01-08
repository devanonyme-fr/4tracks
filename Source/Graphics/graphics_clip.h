#ifndef GRAPHICS_GRAPHICS_CLIP_H
#define GRAPHICS_GRAPHICS_CLIP_H

#include <QtWidgets>
#include <QGraphicsOpacityEffect>
#include <QStyleOption>
#include "Audio/audioclip.h"
#include "Audio/clip.h"
#include "Graphics/elidedlabel.h"
#include "Graphics/audiothumbnail.h"

namespace Graphics {

namespace Ui {
class Clip;
}

class Clip : public QWidget
{
    Q_OBJECT

public:
    explicit Clip(QWidget *parent = nullptr);
    ~Clip();

    void setSelected(bool isSelected);
    bool isSelected() const;

    void setClip(std::shared_ptr<Audio::Clip> clip);

    std::shared_ptr<Audio::Clip> getAudioClip();

    bool shouldMoveClip(QPoint mousePosition) const;

    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *) override;

private:
    Ui::Clip *ui;
    ElidedLabel mLabel;
    std::shared_ptr<Audio::Clip> mClip;

    QGraphicsOpacityEffect *mEffect;

    bool mSelected = false;

    AudioThumbnail mAudioThumbnail;
};


} // namespace Graphics
#endif // GRAPHICS_GRAPHICS_CLIP_H
