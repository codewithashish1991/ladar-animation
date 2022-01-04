#ifndef CAMERASCREEN_H
#define CAMERASCREEN_H

#include <QDialog>

namespace Ui {
class CameraScreen;
}

class CameraScreen : public QDialog
{
    Q_OBJECT

public:
    explicit CameraScreen(QWidget *parent = 0);
    ~CameraScreen();

private:
    Ui::CameraScreen *ui;
};

#endif // CAMERASCREEN_H
