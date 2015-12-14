#ifndef ABOUT_H
#define ABOUT_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QDialogButtonBox>

class AboutWindow : public QWidget
{
    Q_OBJECT

    public:
        AboutWindow(QWidget *parent = 0);

    private:
        QGridLayout *aboutMainLayout;

        QGroupBox *backAndExitButtonState;
        QHBoxLayout *backAndExitButtonLayout;

        QGroupBox *cihatInfosState;
        QHBoxLayout *cihatInfosLayout;
        QLabel *cihatPictLabel;
        QLabel *cihatInfoText;


        QGroupBox *sefaInfosState;
        QHBoxLayout *sefaInfosLayout;
        QLabel *sefaPictLabel;
        QLabel *sefaInfoText;


        QGroupBox *hakanInfosState;
        QHBoxLayout *hakanInfosLayout;
        QLabel *hakanPictLabel;
        QLabel *hakanInfoText;


        QGroupBox *omerInfosState;
        QHBoxLayout *omerInfosLayout;
        QLabel *omerPictLabel;
        QLabel *omerInfoText;


        QGroupBox *benguInfosState;
        QHBoxLayout *benguInfosLayout;
        QLabel *benguPictLabel;
        QLabel *benguInfoText;


        QGroupBox *melikeInfosState;
        QHBoxLayout *melikeInfosLayout;
        QLabel *melikePictLabel;
        QLabel *melikeInfoText;


};

#endif // ABOUT_H
