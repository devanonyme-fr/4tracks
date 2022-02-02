#include "track.h"
#include "ui_track.h"

namespace Graphics
{

Track::Track(QSharedPointer<Audio::Track> track, QWidget *parent)
    :
    QWidget(parent),
    ui(new Ui::Track),
    mAudioTrack(track)
{
    ui->setupUi(this);

    setSelected(false);
    setFixedHeight(DEFAULT_TRACK_HEIGHT);
    setFixedWidth(150);

    setupComponents();
    setupCallbacks();
}

Track::~Track()
{
    delete ui;
}

void Track::setupComponents()
{
    ui->trackName->setText(mAudioTrack->getTrackProperties()->getName());

    ui->volumeSlider->setMinimum(0);
    ui->volumeSlider->setMaximum(200);
    ui->volumeSlider->setValue((int) mAudioTrack->getTrackProperties()->getVolume() * 100);
    ui->volumeSlider->getValueLabel()
        ->setText(QString::number(juce::Decibels::gainToDecibels(double(ui->volumeSlider->value()) / 100), 'g', 2));

    ui->panSlider->setMinimum(-100);
    ui->panSlider->setMaximum(100);
    ui->panSlider->setValue((int) mAudioTrack->getTrackProperties()->getPan() * 100);
    ui->panSlider->getValueLabel()
        ->setText(QString::number(double(ui->panSlider->value()) / 10) + (ui->panSlider->value() > 0 ? "R" : "L"));
}

void Track::setupCallbacks()
{
    connect(mAudioTrack->getTrackProperties().get(), &Audio::TrackProperties::trackNameChanged, [=]()
    {
        ui->trackName->setText(mAudioTrack->getTrackProperties()->getName());
    });

    connect(ui->volumeSlider, &QAbstractSlider::valueChanged, [=]()
    {
        mAudioTrack->getTrackProperties()->setVolume((float) ui->volumeSlider->value() / 100);
        ui->volumeSlider->getValueLabel()
            ->setText(QString::number(juce::Decibels::gainToDecibels(double(ui->volumeSlider->value()) / 100), 'g', 2));
    });

    connect(ui->panSlider, &QAbstractSlider::valueChanged, [=]()
    {
        mAudioTrack->getTrackProperties()->setPan((float) ui->panSlider->value() / 100);
        ui->panSlider->getValueLabel()
            ->setText(QString::number(double(ui->panSlider->value()) / 10) + (ui->panSlider->value() > 0 ? "R" : "L"));
    });
}

void Track::setSelected(bool isSelected)
{
    mSelected = isSelected;

    if (isSelected)
        setStyleSheet(
            "Graphics--Track { background-color: #E4E4E7; } QLabel { padding-left: 2px; color: white; background-color: rgba(34, 197, 94, 50%); }");

    else
        setStyleSheet(
            "Graphics--Track { background-color: #E4E4E7; } QLabel { padding-left: 2px; color: white; background-color: rgba(34, 197, 94, 100%);}");

    repaint();
}

bool Track::isSelected() const
{
    return mSelected;
}

void Track::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Track::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    auto *deleteAction = new QAction("Delete", this);
    menu.addAction(deleteAction);

    if (mAudioTrack->getTrackProperties()->getParentProject()->canRemoveTrack()) {
        connect(deleteAction, &QAction::triggered, [this]()
        {
            mAudioTrack->getTrackProperties()->getParentProject()->removeTrack(mAudioTrack);
        });
    }
    else {
        deleteAction->setEnabled(false);
    }

    menu.exec(event->globalPos());
}

}
