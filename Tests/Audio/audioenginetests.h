#include "gtest/gtest.h"

#include "Audio/Project/project.h"
#include "Audio/Utils/audiofileloader.h"

class TrackTests: public ::testing::Test
{
public:
    void SetUp() override;
    void TearDown() override;

    QSharedPointer<Audio::Track> mTrackToTest;
    QScopedPointer<Audio::Project> mProjectToTest;
};

class ProjectTests: public ::testing::Test
{
public:
    void SetUp() override;
    void TearDown() override;

    QSharedPointer<Audio::Project> mProjectToTest;
};

class AudioFileLoaderTests: public ::testing::Test
{
public:
    void SetUp() override;
    void TearDown() override;

    QScopedPointer<Audio::AudioFileLoader> mFileLoader;
};