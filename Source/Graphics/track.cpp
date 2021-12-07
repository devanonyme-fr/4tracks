#include "track.h"
#include "ui_track.h"

namespace Graphics {

Track::Track(std::shared_ptr<Audio::AudioTrack> track, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Track),
    mAudioTrack(track)
{
    ui->setupUi(this);

    ui->trackName->setText(mAudioTrack->getName());

    setStyleSheet("#Track { background-color: #BDBDBD; }");
    setFixedHeight(DEFAULT_TRACK_HEIGHT);
}

Track::~Track()
{
    delete ui;
}

void Track::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

}
