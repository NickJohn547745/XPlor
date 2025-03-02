#include "soundviewer.h"
#include "ui_soundviewer.h"

SoundViewer::SoundViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SoundViewer)
    , player(new QMediaPlayer())
    , buffer(new QBuffer())
{
    ui->setupUi(this);

    connect(ui->pushButton_Play, &QPushButton::clicked, player, &QMediaPlayer::play);
    connect(ui->pushButton_Pause, &QPushButton::clicked, player, &QMediaPlayer::pause);
    connect(ui->pushButton_Stop, &QPushButton::clicked, this, [this]() {
        if (player->isPlaying()) {
            player->stop();
        }
    });
    connect(ui->pushButton_SkipForward, &QPushButton::clicked, this, [this]() {
        player->setPosition(player->position() + 30);
    });
    connect(ui->pushButton_SkipBack, &QPushButton::clicked, this, [this]() {
        player->setPosition(player->position() - 30);
    });
    connect(player, &QMediaPlayer::positionChanged, player, [this](qint64 position) {
        ui->horizontalSlider->setSliderPosition(position);
        ui->label_Time->setText(QString("%1:%2:%3")
                                    .arg(position / 60000)
                                    .arg((position % 60000) / 1000)
                                    .arg(position % 1000));
    });
    connect(player, &QMediaPlayer::durationChanged, player, [this](qint64 duration) {
        ui->horizontalSlider->setMaximum(duration);
        ui->label_TimeMax->setText(QString("%1:%2:%3")
                                       .arg(duration / 60000)
                                       .arg((duration % 60000) / 1000)
                                       .arg(duration % 1000));
    });
    connect(ui->horizontalSlider, &QSlider::sliderMoved, this, [this](int position) {
        player->setPosition(position);
    });

    for (auto outputDevice : QMediaDevices::audioOutputs()) {
        ui->comboBox_Output->addItem(outputDevice.description());
    }
    connect(ui->comboBox_Output, &QComboBox::currentIndexChanged, this, [this](int index) {
        auto outputDevice = QMediaDevices::audioOutputs()[index];
        QAudioOutput *audioOutput = new QAudioOutput(outputDevice);
        player->setAudioOutput(audioOutput);
    });

    auto outputDevice = QMediaDevices::defaultAudioOutput();
    QAudioOutput *audioOutput = new QAudioOutput(outputDevice);
    player->setAudioOutput(audioOutput);
}

SoundViewer::~SoundViewer()
{
    delete buffer;
    delete player;
    delete ui;
}

void SoundViewer::SetSound(std::shared_ptr<Sound> aSound)
{
    buffer->setData(aSound->data);
    if (!buffer->open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open QBuffer.";
        return;
    }

    ui->groupBox->setTitle(aSound->path);
    player->setSourceDevice(buffer);
}

void SoundViewer::SetOutput(QAudioOutput *aOutput) {
    if (!aOutput) { return; }

    player->setAudioOutput(aOutput);
}
