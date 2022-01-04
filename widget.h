#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <map>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    QPixmap paintWidget();
    int getScanCourse();
    void drawRadarLight(QPainter *qp);
    void setScanCourse(int redius);
    void drawLadar(QPainter *qp);
    void detectObjects(QPainter *qp);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

protected slots:
    void timerTimeOut();

private:
    Ui::Widget *ui;
    QTimer *timer;
    QPoint point;
    int i_diameter=0;
    int scanCourse;


};

#endif // WIDGET_H
