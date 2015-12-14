#include "about.h"
#include <QLabel>
//#include "ui_newwindow.h"


AboutWindow::AboutWindow(QWidget *parent)
{
    QString cihatPictPath = "F:/Qt/Tools/QtCreator/bin/Proje/about images/cihat.jpg";
    QString sefaPictPath = "F:/Qt/Tools/QtCreator/bin/Proje/about images/sefa.jpg";
    QString hakanPictPath = "F:/Qt/Tools/QtCreator/bin/Proje/about images/hakan.jpg";
    QString omerPictPath = "F:/Qt/Tools/QtCreator/bin/Proje/about images/omer.jpg";
    QString melikePictPath = "F:/Qt/Tools/QtCreator/bin/Proje/about images/melike.jpg";
    QString benguPictPath = "F:/Qt/Tools/QtCreator/bin/Proje/about images/bengu.jpg";


    /*----------------------------------------------------------------------------------------*/
    cihatInfosState = new QGroupBox(tr("Member 1"));
    cihatInfosLayout = new QHBoxLayout(this);

    cihatPictLabel = new QLabel(this);
    cihatPictLabel->setObjectName(QStringLiteral("cihatPictLabel"));
    cihatPictLabel->setPixmap(QPixmap(cihatPictPath));

    cihatInfoText=new QLabel(this);
    cihatInfoText->setText("<INTERFACE - SOFTWARE>   \n      M. Cihat OZDENOGLU  \n            091044008  \n                4.SINIF");
    //cihatInfoText->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    cihatInfosLayout->addWidget(cihatPictLabel);
    cihatInfosLayout->addWidget(cihatInfoText);
    cihatInfosLayout->addStretch(1);
    cihatInfosState->setLayout(cihatInfosLayout);

    /*----------------------------------------------------------------------------------------*/
    sefaInfosState = new QGroupBox(tr("Member 2"));
    sefaInfosLayout = new QHBoxLayout(this);

    sefaPictLabel = new QLabel(this);
    sefaPictLabel->setObjectName(QStringLiteral("sefaPictLabel"));
    sefaPictLabel->setPixmap(QPixmap(sefaPictPath));

    sefaInfoText=new QLabel(this);
    sefaInfoText->setText("<HARDWARE - SOFTWARE>  \n         Sefa TASCIOGLU  \n             101044005  \n                 4.SINIF");
    //sefaInfoText->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    sefaInfosLayout->addWidget(sefaPictLabel);
    sefaInfosLayout->addWidget(sefaInfoText);
    sefaInfosLayout->addStretch(1);
    sefaInfosState->setLayout(sefaInfosLayout);
    /*----------------------------------------------------------------------------------------*/
    hakanInfosState = new QGroupBox(tr("Member 4"));
    hakanInfosLayout = new QHBoxLayout(this);

    hakanPictLabel = new QLabel(this);
    hakanPictLabel->setObjectName(QStringLiteral("hakanPictLabel"));
    hakanPictLabel->setPixmap(QPixmap(hakanPictPath));

    hakanInfoText=new QLabel(this);
    hakanInfoText->setText("<HARDWARE - SOFTWARE>  \n         Hakan DEGIRMEN  \n            101044057  \n                 4.SINIF");
    //hakanInfoText->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    hakanInfosLayout->addWidget(hakanPictLabel);
    hakanInfosLayout->addWidget(hakanInfoText);
    hakanInfosLayout->addStretch(1);
    hakanInfosState->setLayout(hakanInfosLayout);
    /*----------------------------------------------------------------------------------------*/
    omerInfosState = new QGroupBox(tr("Member 3"));
    omerInfosLayout = new QHBoxLayout(this);

    omerPictLabel = new QLabel(this);
    omerPictLabel->setObjectName(QStringLiteral("omerPictLabel"));
    omerPictLabel->setPixmap(QPixmap(omerPictPath));

    omerInfoText=new QLabel(this);
    omerInfoText->setText("<INTERFACE - SOFTWARE>  \n     Omer COSKUNCELEBI  \n             101044057  \n                 3.SINIF");
    //omerInfoText->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    omerInfosLayout->addWidget(omerPictLabel);
    omerInfosLayout->addWidget(omerInfoText);
    omerInfosLayout->addStretch(1);
    omerInfosState->setLayout(omerInfosLayout);
    /*----------------------------------------------------------------------------------------*/
    benguInfosState = new QGroupBox(tr("Member 6"));
    benguInfosLayout = new QHBoxLayout(this);

    benguPictLabel = new QLabel(this);
    benguPictLabel->setObjectName(QStringLiteral("benguPictLabel"));
    benguPictLabel->setPixmap(QPixmap(benguPictPath));

    benguInfoText=new QLabel(this);
    benguInfoText->setText("<HARDWARE - SOFTWARE>  \n           Bengu ALAN  \n           101044043  \n               4.SINIF");
    //benguInfoText->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    benguInfosLayout->addWidget(benguPictLabel);
    benguInfosLayout->addWidget(benguInfoText);
    benguInfosLayout->addStretch(1);
    benguInfosState->setLayout(benguInfosLayout);
    /*----------------------------------------------------------------------------------------*/
    melikeInfosState = new QGroupBox(tr("Member 5"));
    melikeInfosLayout = new QHBoxLayout(this);

    melikePictLabel = new QLabel(this);
    melikePictLabel->setObjectName(QStringLiteral("melikePictLabel"));
    melikePictLabel->setPixmap(QPixmap(melikePictPath));

    melikeInfoText=new QLabel(this);
    melikeInfoText->setText("<INTERFACE - HARDWARE>  \n            Melike SEZER  \n             101044005  \n                4.SINIF");
    //melikeInfoText->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    melikeInfosLayout->addWidget(melikePictLabel);
    melikeInfosLayout->addWidget(melikeInfoText);
    melikeInfosLayout->addStretch(1);
    melikeInfosState->setLayout(melikeInfosLayout);
    /*----------------------------------------------------------------------------------------*/

    aboutMainLayout = new QGridLayout;


    aboutMainLayout->addWidget(cihatInfosState,0,0,1,1);
    aboutMainLayout->addWidget(sefaInfosState,0,1,1,1);
    aboutMainLayout->addWidget(omerInfosState,1,0,1,1);
    aboutMainLayout->addWidget(hakanInfosState,1,1,1,1);
    aboutMainLayout->addWidget(melikeInfosState,2,0,1,1);
    aboutMainLayout->addWidget(benguInfosState,2,1,1,1);
    setLayout(aboutMainLayout);
}
