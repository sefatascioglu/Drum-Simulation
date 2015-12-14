#include "interface.h"

#include <QApplication>
#include <QMediaPlayer>
#include <QtCore/QCoreApplication>
#include <QApplication>
#include <QKeyEvent>

/*--------------------------------------*/
using namespace std;

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
/*-----------------------------------------------------*/

using namespace cv;
using namespace std;

int main( int argc, char *argv[] )
{

	QApplication app( argc, argv );

    Interface bateri;

    bateri.resize(720, 650);
    bateri.move(25, 25);
    bateri.setWindowTitle("Bateri Simulation");
    bateri.show();
    

    return app.exec();

	
}


