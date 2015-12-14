#include "interface.h"
#include "about.h"
#include "rs232.h"

#include <QDebug>
#include <iostream>
#include <cv.h>
#include <highgui.h>

/* Aruco Directories */
#include "aruco/aruco.h"
#include "aruco/cvdrawingutils.h"
#include "aruco/cvdrawingutils.cpp"
#include "aruco/cameraparameters.h"
#include "aruco/cameraparameters.cpp"
#include "aruco/marker.h"
#include "aruco/marker.cpp"
#include "aruco/markerdetector.h"
#include "aruco/markerdetector.cpp"
#include "aruco/subpixelcorner.h"
#include "aruco/subpixelcorner.cpp"
#include "aruco/arucofidmarkers.h"
#include "aruco/arucofidmarkers.cpp"
#include "aruco/ar_omp.h"
#include "aruco/ar_omp.cpp"

using namespace aruco;
using namespace cv;
using namespace std;

CvMemStorage* storage;

Interface::Interface(QWidget *parent)
{
    tabWidget = new QTabWidget;
    tabWidget->addTab(new MainWindow, tr("Main Menu"));
    tabWidget->addTab(new AboutWindow, tr("About Menu"));

    closeButton = new QPushButton("Close",this);
    closeButton->setObjectName(QString::fromUtf8("Close"));
    connect( closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(closeButton);
    setLayout(mainLayout);

    setWindowTitle(tr("Bateri Simulation"));
}

MainWindow::MainWindow( QWidget *parent )
{
    player = new QMediaPlayer;
    playGif = new QMovie(this);
    playGif->setCacheMode(QMovie::CacheAll);

	player->setMedia(QUrl::fromLocalFile("background music/Background Music.mp3"));
    player->setVolume(100);
    player->play();

    createGifPart();
    createButtonsPart();
    createSettingsPart();
    createKaraokeSettingsPart();
    createRecordPart();

    QGridLayout *mainLayout;

    mainLayout = new QGridLayout;

    mainLayout->addWidget(GifState,0,0,2,2);
    mainLayout->addWidget(ButtonState,2,0);
    mainLayout->addWidget(SettingsState,2,1);
    mainLayout->addWidget(RecordState,3,0);
    mainLayout->addWidget(KaraokeState,3,1);
    mainLayout->setRowStretch(1, 1);
    mainLayout->setRowStretch(2, 1);
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(1, 1);
    setLayout(mainLayout);

}

void MainWindow::createButtonsPart()
{
    QSize iconSize(375, 70);

    ButtonState = new QGroupBox(tr("Game Menu"));

    buttonsLayout = new QVBoxLayout;

    gamePlayButton = new QToolButton;
    gamePlayButton->setIcon(QIcon("images/play-button.jpg"));
    gamePlayButton->setIconSize(iconSize);
    gamePlayButton->setToolTip(tr("Stop"));
    connect(gamePlayButton, SIGNAL(clicked()), this, SLOT(showPlayWindow()));


    buttonsLayout->addWidget(gamePlayButton);
    buttonsLayout->addStretch(1);
    ButtonState->setLayout(buttonsLayout);
}

void MainWindow::createSettingsPart()
{

    SettingsState = new QGroupBox(tr("Settings Menu"));

    settingsLayout = new QVBoxLayout;

    volumeStatusBar = new QScrollBar(this);
    volumeStatusBar->setObjectName(QString::fromUtf8("volumeStatusBar"));
    volumeStatusBar->setOrientation(Qt::Horizontal);
    volumeStatusBar->setValue(100);
    connect( volumeStatusBar, SIGNAL(valueChanged(int)), this, SLOT(setVolumeLevel(int)) );

    muteBox = new QCheckBox(this);
    muteBox->setObjectName(QStringLiteral("muteBox"));
    muteBox->setText("Turn of background music");
    connect( muteBox, SIGNAL(toggled(bool)), this, SLOT(operateBackMusic(bool)));


    volumeText = new QLabel(this);
    volumeText->setObjectName(QStringLiteral("volumeText"));
    volumeText->setText("Volume");

    settingsLayout->addWidget(volumeText);
    settingsLayout->addWidget(volumeStatusBar);
    settingsLayout->addWidget(muteBox);
    settingsLayout->addStretch(1);
    SettingsState->setLayout(settingsLayout);
}


void MainWindow::operateBackMusic(bool checkbox)
{
    if(checkbox==true)
        player->pause();
    else
        player->play();

}
void MainWindow::createRecordPart()
{
    QSize iconSize(25, 25);

    RecordState = new QGroupBox(tr("Record Menu"));
    QString recDirDefaultPath = "../";

    recordLayout = new QHBoxLayout(RecordState);

    audioRecorder = new QAudioRecorder;
    audioRecorder->setOutputLocation(QUrl::fromLocalFile(recDirDefaultPath));

    recStartButton = new QToolButton;
    recStartButton->setIcon(QIcon("images/record-button.jpg"));
    recStartButton->setIconSize(iconSize);
    recStartButton->setToolTip(tr("Stop"));
    connect(recStartButton, SIGNAL(clicked()), audioRecorder, SLOT(record()));

    recStopButton = new QToolButton;
    recStopButton->setIcon(QIcon("images/stop-button.jpg"));
    recStopButton->setIconSize(iconSize);
    recStopButton->setToolTip(tr("Stop"));
    connect(recStopButton, SIGNAL(clicked()), audioRecorder, SLOT(stop()));

    directoryComboBox = new QComboBox;
    directoryLabel = new QLabel(tr("In directory:  "));

    browseButton = new QToolButton;
    browseButton->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    browseButton->setIconSize(iconSize);
    connect(browseButton, SIGNAL(clicked()), this, SLOT(browse()));

    directoryComboBox->setEditable(true);
    directoryComboBox->addItem("<Enter recording audio directory path here>");
    connect(directoryComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(setDirPath(QString)));

    recordLayout->addWidget(recStartButton);
    recordLayout->addWidget(recStopButton);
    recordLayout->addWidget(directoryLabel);
    recordLayout->addWidget(directoryComboBox);
    recordLayout->addWidget(browseButton);
    recordLayout->addStretch(1);
    RecordState->setLayout(recordLayout);
}
void MainWindow::setDirPath(QString dirPath)
{
    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/amr");
    audioSettings.setQuality(QMultimedia::HighQuality);

    audioRecorder->setEncodingSettings(audioSettings);

    audioRecorder->setOutputLocation(QUrl::fromLocalFile(dirPath));
}

void MainWindow::browse()
{
    QString recDirPath = QFileDialog::getExistingDirectory(this,
                                    tr("Find Files"), "../");

    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/amr");
    audioSettings.setQuality(QMultimedia::HighQuality);

    audioRecorder->setEncodingSettings(audioSettings);

    audioRecorder->setOutputLocation(QUrl::fromLocalFile(recDirPath));
}

void MainWindow::createKaraokeSettingsPart()
{
    QSize iconSize(25, 25);

    KaraokeState = new QGroupBox(tr("Karaoke Settings"));

    karaokeSettingsLayout = new QHBoxLayout(KaraokeState);

    openButton = new QToolButton;
    openButton->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    openButton->setIconSize(iconSize);
    openButton->setToolTip(tr("Open File"));
    connect(openButton, SIGNAL(clicked()), this, SLOT(open()));

    playButton = new QToolButton;
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    playButton->setIconSize(iconSize);
    playButton->setToolTip(tr("Play"));
    connect(playButton, SIGNAL(clicked()), player, SLOT(play()));

    pauseButton = new QToolButton;
    pauseButton->setCheckable(true);
    pauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    pauseButton->setIconSize(iconSize);
    pauseButton->setToolTip(tr("Pause"));
    connect(pauseButton, SIGNAL(clicked(bool)), player, SLOT(pause()));

    stopButton = new QToolButton;
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    stopButton->setIconSize(iconSize);
    stopButton->setToolTip(tr("Stop"));
    connect(stopButton, SIGNAL(clicked()), player, SLOT(stop()));

    karaokeSettingsLayout->addStretch();
    karaokeSettingsLayout->addWidget(openButton);
    karaokeSettingsLayout->addWidget(playButton);
    karaokeSettingsLayout->addWidget(pauseButton);
    karaokeSettingsLayout->addWidget(stopButton);
    karaokeSettingsLayout->addStretch(1);
    KaraokeState->setLayout(karaokeSettingsLayout);


}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open a Music"),
                              "../",
                              tr("Music Files (*.mp3 *.waw)"));
    if (!fileName.isEmpty())
        openFile(fileName);
}

void MainWindow::openFile(const QString &fileName)
{
    currentMusicDirectory = QFileInfo(fileName).path();

    player->setMedia(QUrl::fromLocalFile(fileName));
    player->setVolume(50);
    player->play();
}

void MainWindow::createGifPart()
{
    GifState =new QWidget(this);
    GifState->setGeometry(QRect(0, 0, 650, 366));

    gifLayout = new QGridLayout(GifState);

    QString gifPath = "gifs/gif-drummer-alexis-von-kraven.gif";

    gifLabel = new QLabel(this);
    gifLabel->setObjectName(QStringLiteral("gifLabel"));
    gifLabel->setScaledContents(true);

    gifLabel->setMovie(playGif);
    playGif->setFileName(gifPath);
    playGif->start();

    gifLayout->addWidget(gifLabel);

}

void MainWindow::setVolumeLevel(int level)
{
    player->setVolume(level);
}

void MainWindow::showPlayWindow()
{
	
	if(port.OpenComport(0,115200)==1)
	{
		QMessageBox *message;
		message = new QMessageBox;
	
		message->setText("Cannot connected device");
		message->show();
	}
	else
	{
		gamePlayButton->setEnabled(false);

		drum_1 = new QMediaPlayer;
		drum_1->setMedia(QUrl::fromLocalFile("sounds/drum_1.mp3"));
		player->setVolume(100);

		drum_2 = new QMediaPlayer;
		drum_2->setMedia(QUrl::fromLocalFile("sounds/drum_2.mp3"));
		player->setVolume(100);

		pedal = new QMediaPlayer;
		pedal->setMedia(QUrl::fromLocalFile("sounds/pedal.mp3"));
		player->setVolume(100);

		ring_1 = new QMediaPlayer;
		ring_1->setMedia(QUrl::fromLocalFile("sounds/ring_1.mp3"));
		player->setVolume(100);

		ring_2 = new QMediaPlayer;
		ring_2->setMedia(QUrl::fromLocalFile("sounds/ring_2.mp3"));
		player->setVolume(100);

		playBattery();
	
	}
}

int MainWindow::playBattery()
{
    VideoCapture cap(1); //capture the video from web cam

    MarkerDetector MDetector;
    vector<Marker> Markers;


    if ( !cap.isOpened() )  // if not success, exit program
    {
            cout << "Cannot open the web cam" << endl;
            return -1;
    }

	Mat image;
    namedWindow("Play Bateri",1);

    while (1) {

       Mat imgOriginal;
       Mat src1,dst;

       src1 = imread("images/drumPic2.jpg");
	   
	   cap >> imgOriginal;
	   
	   if(imgOriginal.empty())
		   continue;

       MDetector.detect(imgOriginal,Markers);
	  
       // for each marker, draw info and its boundaries in the image
       for (unsigned int i=0;i<Markers.size();i++) {

            Point p= Markers[i].getCenter();

            circle(src1,Point(640-p.x,p.y),15, Scalar(0,255,0), -1,8,0);

            if((p.x >460 && p.x < 585)&&(p.y > 300 && p.y < 350)){
				ring_1->play();
				qDebug() << p.x << "  -ring_1--------   "<<p.y<<endl;
				if(Markers[0].id==0){
					for(int i=0;i<3;++i)
						port.SendByte(0,'5');
				}else if(Markers[0].id==977){
					for(int i=0;i<3;++i)
					port.SendByte(0,'4');
				}
            }

            else if((p.x > 340 && p.x < 430)&&(p.y > 245 && p.y < 305 )){
                   if(Markers[0].id==0){
					  for(int i=0;i<3;++i)
						port.SendByte(0,'5');
					drum_1->play();
					qDebug() << p.x << "  -drum_1-------   "<<p.y<<endl;
				}else if(Markers[0].id==977){
					for(int i=0;i<3;++i)
					port.SendByte(0,'4');
				}
            }

            else if((p.x > 208 && p.x < 308)&&(p.y > 237 && p.y < 297 )){
                    drum_2->play();
				if(Markers[0].id==0){
					for(int i=0;i<3;++i)
					port.SendByte(0,'5');
					qDebug() << p.x << "  -drum_2----------   "<<p.y<<endl;
				}else if(Markers[0].id==977){
					for(int i=0;i<3;++i)
					port.SendByte(0,'4');
				}
            }

            else if((p.x > 30 && p.x < 180)&&(p.y > 260 && p.y < 320)){
				ring_2->play();
				qDebug() << p.x << "  -ring_2------   "<<p.y<<endl;
				if(Markers[0].id==0){
					for(int i=0;i<3;++i)
					port.SendByte(0,'5');
				}else if(Markers[0].id==977){
					for(int i=0;i<3;++i)
					port.SendByte(0,'4');
				}
            }
			char readBuffer[10]=" ";
			
			port.PollComport(0,readBuffer,10);
			
			qDebug()<<"----Read------  "<<readBuffer<<endl;
				
			if(readBuffer[0]=='9'){
				pedal->play();
				qDebug()<<"-Pedal------"<<endl;
			
			}
			readBuffer[0]='\0';
			//port.SendByte(0,'6');
            circle(src1,Point(640-p.x,p.y),15, Scalar(0,255,0), -1,8,0);
       }
	   


       addWeighted(imgOriginal, 0.001, src1, 0.9, 0.0, dst);

       putText(dst, "GROUP-8 DRUM MASTER", cvPoint(200,100),
           FONT_HERSHEY_COMPLEX_SMALL, 0.9, cvScalar(150,200,250), 1.2, CV_AA);

       imshow("image", dst);

	   if(waitKey(30) >= 0){
		   port.CloseComport(0);

		   break;
	   } 
    }

	return 0;
}

