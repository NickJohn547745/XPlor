#ifndef SOUNDVIEWER_H
#define SOUNDVIEWER_H

#include "asset_structs.h"

#include <QWidget>
#include <QMediaPlayer>
#include <QBuffer>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QAudioOutput>

namespace Ui {
class SoundViewer;
}

class SoundViewer : public QWidget
{
    Q_OBJECT

public:
    explicit SoundViewer(QWidget *parent = nullptr);
    ~SoundViewer();

    void SetSound(std::shared_ptr<Sound> aSound);

    void SetOutput(QAudioOutput *aOutput);
private:
    Ui::SoundViewer *ui;
    QMediaPlayer *player;
    QBuffer *buffer;
};

#endif // SOUNDVIEWER_H
