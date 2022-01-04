#include "camerascreen.h"
#include "ui_camerascreen.h"

CameraScreen::CameraScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraScreen)
{
    ui->setupUi(this);
}

CameraScreen::~CameraScreen()
{
    delete ui;
}
