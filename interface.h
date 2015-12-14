#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QString>
#include <QPushButton>
#include <QScrollBar>
#include <QDialogButtonBox>
#include <QMediaPlayer>
#include <QLabel>
#include <QComboBox>
#include <QCommandLinkButton>
#include <QMessageBox>
#include <QApplication>
#include <QAudioOutput>
#include <QCheckBox>
#include <QToolButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFileInfo>
#include <QMovie>
#include <QGroupBox>
#include <QTimer>
#include <QKeyEvent>
#include <QTabWidget>
#include <QAudioRecorder>
#include <QComboBox>
#include <QPushButton>

#include <iostream>
#include <cv.h>
#include <highgui.h>
#include "rs232.h" 
  
using namespace cv;

enum BAGET_COLOR{

      BLUE, RED
  };

class QLineEdit;

class Interface : public QWidget
{

    Q_OBJECT

    public:
        Interface(QWidget *parent = 0);
	private:
        QTabWidget *tabWidget;
        QPushButton *closeButton;
        
};

class MainWindow : public QWidget
{
  Q_OBJECT

public:
  MainWindow( QWidget *parent = 0 );

  void openFile(const QString &fileName);
  int playBattery();

public slots:
  void showPlayWindow();
  void browse();
  void setDirPath(QString);
  void setVolumeLevel(int);
  void operateBackMusic(bool);
  void open();

private:
  void createButtonsPart();
  void createSettingsPart();
  void createGifPart();
  void createKaraokeSettingsPart();
  void createRecordPart();

  rs  port;
  
  /*--------------------------------*/
  QMediaPlayer *drum_1;
  QMediaPlayer *drum_2;
  QMediaPlayer *pedal;
  QMediaPlayer *ring_1;
  QMediaPlayer *ring_2;

  /*---------MAIN VARIABLES---------*/
  QMediaPlayer *player;
  QMovie *playGif;
  QString currentMusicDirectory;
  /*--------------------------------*/

  /*---------GIF STATE---------*/
  QWidget *GifState;
  QGridLayout *gifLayout;
  QLabel *gifLabel;
  /*--------------------------------*/

  /*---------BUTTON STATE---------*/
  QGroupBox *ButtonState;
  QVBoxLayout *buttonsLayout;
  QToolButton *gamePlayButton;
  //QPushButton *About;
  /*--------------------------------*/

  /*---------RECORD STATE---------*/
  QAudioRecorder *audioRecorder;
  QGroupBox *RecordState;
  QHBoxLayout *recordLayout;
  QToolButton *recStartButton;
  QToolButton *recStopButton;
  QComboBox *directoryComboBox;
  QLabel *directoryLabel;
  QToolButton *browseButton;
  /*--------------------------------*/

  /*---------SETTING STATE---------*/
  QGroupBox *SettingsState;
  QVBoxLayout *settingsLayout;
  QScrollBar *volumeStatusBar;
  QLabel *volumeText;
  QCheckBox *muteBox;
  /*--------------------------------*/

  /*---------KARAOKE STATE---------*/
  QGroupBox *KaraokeState;
  QHBoxLayout *karaokeSettingsLayout;
  QToolButton *openButton;
  QToolButton *playButton;
  QToolButton *pauseButton;
  QToolButton *stopButton;
  /*--------------------------------*/
  
};

#endif // INTERFACE_H
