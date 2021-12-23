#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "Graphics/graphics_timeline.h"
#include "Audio/project.h"
#include "Audio/JuceIncludes.h"
#include "Utils/projectsaver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void importFile();
    void saveProject();

    void updateTitle();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<Audio::Project> mProject;
    Graphics::Timeline mUiTimeline;
    juce::AudioSourcePlayer mPlayer;
    juce::AudioDeviceManager mDeviceManager;

    QString currentProjectPath = "";
};
#endif // MAINWINDOW_H