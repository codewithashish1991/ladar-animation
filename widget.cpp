#include "widget.h"
#include "ui_widget.h"
#include <cmath>
#include <iostream>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

float PI = 3.14159265;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:black");
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(timerTimeOut()));
    timer->start(10);
}

Widget::~Widget()
{
    delete ui;
}

int Widget::getScanCourse(){
    update();
    return scanCourse;
}

void Widget::setScanCourse(int redius){
    scanCourse = redius;
}

void Widget::timerTimeOut(){
    timer->start(10);
    int course = this->scanCourse +1;
    if(course >= 360){
        course = 0;
    }
    this->setScanCourse(course);
    update();
}

void Widget::resizeEvent(QResizeEvent *)
{
    if(this->width() > this->height()){
        point = QPoint((this->width()-this->height())/2+(this->height())/2,this->height()/2);
        i_diameter = this->height()-80;
    }else{
        point = QPoint(this->width()/2,(this->height()-this->width())/2+(this->width()-12)/2);
        i_diameter = this->width()-80;
    }
}


void Widget::drawLadar(QPainter *p_painter){
    p_painter->save();
    QPen circle_pen(QColor(102,204,255), 0.8, Qt::SolidLine);
    QPen line_hide(QColor(0, 0, 0), 3, Qt::SolidLine);

    // creating outer circle:
    p_painter->setPen(circle_pen);
    p_painter->drawEllipse(point.x(), point.y(), 0, 0);
    // creating scale

    for(int i=0; i< 360; i++){
        if (i % 30 ==0){
            p_painter->setPen(circle_pen);
            QPoint p(point.x()-5 + i_diameter * 0.55 * cos(i * PI / 180.0),
                           point.y()+5 - i_diameter *0.55 * sin(i * PI / 180.0));
            p_painter->drawText(p, QString::number(i));
            QLineF scale_line;
            scale_line.setP1(QPointF(point.x(), point.y()));
            scale_line.setAngle(i);
            scale_line.setLength(i_diameter*0.5);
            p_painter->setPen(circle_pen);
            p_painter->drawLine(scale_line);

            QLineF scale_line1;
            scale_line1.setP1(QPointF(point.x(), point.y()));
            scale_line1.setAngle(i);
            scale_line1.setLength(i_diameter*0.47);
            p_painter->setPen(line_hide);
            p_painter->drawLine(scale_line1);
       } else if(i % 10 ==0){
            p_painter->setPen(circle_pen);
            QPoint p(point.x()-5 + i_diameter * 0.55 * cos(i * PI / 180.0),
                           point.y()+5 - i_diameter *0.55 * sin(i * PI / 180.0));
            p_painter->drawText(p, QString::number(i));
            QLineF scale_line;
            scale_line.setP1(QPointF(point.x(), point.y()));
            scale_line.setAngle(i);
            scale_line.setLength(i_diameter*0.5);
            p_painter->setPen(circle_pen);
            p_painter->drawLine(scale_line);

            QLineF scale_line1;
            scale_line1.setP1(QPointF(point.x(), point.y()));
            scale_line1.setAngle(i);
            scale_line1.setLength(i_diameter*0.48);
            p_painter->setPen(line_hide);
            p_painter->drawLine(scale_line1);
       }  else{
            p_painter->setPen(circle_pen);
            QPoint p(point.x()-5 + i_diameter * 0.55 * cos(i * PI / 180.0),
                           point.y()+5 - i_diameter *0.55 * sin(i * PI / 180.0));
            QLineF scale_line;
            scale_line.setP1(QPointF(point.x(), point.y()));
            scale_line.setAngle(i);
            scale_line.setLength(i_diameter*0.5);
            p_painter->setPen(circle_pen);
            p_painter->drawLine(scale_line);

            QLineF scale_line1;
            scale_line1.setP1(QPointF(point.x(), point.y()));
            scale_line1.setAngle(i);
            scale_line1.setLength(i_diameter*0.49);
            p_painter->setPen(line_hide);
            p_painter->drawLine(scale_line1);
       }
    }
    p_painter->setPen(circle_pen);
     // creating inner circle:
    for(int i=1; i<6; i++){
       p_painter->drawEllipse(point.x()-i_diameter*0.2*i/2,point.y()-i_diameter*0.2*i/2,i_diameter*0.2*i,i_diameter*0.2*i);
       if (i !=5){
           p_painter->drawText(point.x()-i_diameter*0.2*6/25,point.y()+i_diameter*0.32*i/3+10, QString::number(i*60) + ' '+ 'n' + 'm');
       }
    }

    // creating horizontal and vertical lines
    p_painter->setPen(circle_pen);
    p_painter->drawLine(point.x(), point.y()-i_diameter/2, point.x(), point.y()+i_diameter/2);//Draw coordinates
    p_painter->drawLine(point.x()-i_diameter/2,point.y(),point.x()+i_diameter/2,point.y());
    p_painter->restore();
}

QJsonArray getDetectedObjectsData(){
    QJsonArray detectedObjs;
    auto obj1 = QJsonObject(
    {
        qMakePair(QString("object_name"), QJsonValue("Ship")),
        qMakePair(QString("course"), QJsonValue(256)),
        qMakePair(QString("distance"), QJsonValue(50))
    });
    detectedObjs.push_back(QJsonValue(obj1));

    auto obj2 = QJsonObject(
    {
        qMakePair(QString("object_name"), QJsonValue("Whale")),
        qMakePair(QString("course"), QJsonValue(170)),
        qMakePair(QString("distance"), QJsonValue(153))
    });
    detectedObjs.push_back(QJsonValue(obj2));

    auto obj4 = QJsonObject(
    {
        qMakePair(QString("object_name"), QJsonValue("IceBurg")),
        qMakePair(QString("course"), QJsonValue(50)),
        qMakePair(QString("distance"), QJsonValue(220))
    });
    detectedObjs.push_back(QJsonValue(obj4));

    auto obj5 = QJsonObject(
    {
        qMakePair(QString("object_name"), QJsonValue("Ship")),
        qMakePair(QString("course"), QJsonValue(306)),
        qMakePair(QString("distance"), QJsonValue(250))
    });
    detectedObjs.push_back(QJsonValue(obj5));
    return detectedObjs;
}

QJsonArray getRadarCrossSectionData(){
    QJsonArray radarCrossSectionData;
    auto radar1 = QJsonObject(
    {
        qMakePair(QString("course"), QJsonValue(40)),
        qMakePair(QString("range"), QJsonValue(30))
    });
    radarCrossSectionData.push_back(QJsonValue(radar1));

    auto radar3 = QJsonObject(
    {
        qMakePair(QString("course"), QJsonValue(130)),
        qMakePair(QString("range"), QJsonValue(30))
    });
    radarCrossSectionData.push_back(QJsonValue(radar3));
    return radarCrossSectionData;
}

QJsonObject receive_radar_data(){
    QJsonArray objectsData = getDetectedObjectsData();
    QJsonArray radarData = getRadarCrossSectionData();
    QJsonObject final_object;
    final_object.insert(QString("object_array"), QJsonValue(objectsData));
    final_object.insert(QString("radar_cross_section"), QJsonValue(radarData));
    return final_object;
}

void Widget::detectObjects(QPainter *qp){
    qp->save();
    // object type, distance, course
    QJsonObject arr = receive_radar_data();
    QJsonArray jsonArray = arr["object_array"].toArray();
    int totalRecord = jsonArray.count();
    // check total object is greater then 0
    if(totalRecord > 0){
        foreach (const QJsonValue & value, jsonArray) {
            // assign values from array in variables.
            QJsonObject obj = value.toObject();
            QString name = obj["object_name"].toString();
            int angle = obj["course"].toInt();
            int distance = obj["distance"].toInt();
            float dis = 0.5/300*distance;

            // check distance is in outer circle area.
            if(distance < 300){
                // set color based on distance.
                if(distance < 60){
                    qp->setPen(QPen(Qt::red, 2, Qt::SolidLine));
                }else if(distance > 180){
                    qp->setPen(QPen(Qt::green, 2, Qt::SolidLine));
                }else{
                    qp->setPen(QPen(Qt::yellow, 2, Qt::SolidLine));
                }
                // draw point
                QPoint p(point.x() + i_diameter*dis * cos(angle * PI / 180.0),
                point.y() - i_diameter*dis * sin(angle * PI / 180.0));
                qp->drawPoint(p);
                // draw circle around point
                qp->drawEllipse(QPointF(p), 4, 4);

                qp->setPen(QPen(QColor(102,204,255), 2, Qt::SolidLine));
                // show object name
                QPoint pt(point.x() + i_diameter*dis * cos(angle * PI / 180.0)+10,
                        point.y() - i_diameter*dis * sin(angle * PI / 180.0)+5);
                qp->drawText(QPointF(pt), name);
            }
        }
    }
    qp->restore();
}


void Widget::drawRadarLight(QPainter *qp){
    qp->save();
    QJsonObject arr = receive_radar_data();
    QJsonArray jsonArray = arr["radar_cross_section"].toArray();
    int totalRecord = jsonArray.count();
    QColor color = QColor(102,204,255);
    color.setAlphaF(0.3);
    // check radar numbers is grater then 0.
    if (totalRecord > 0){
        foreach (const QJsonValue & value, jsonArray) {
            // assign values from array in variables.
            QJsonObject obj = value.toObject();
            int angle = obj["course"].toInt();
            int range = obj["range"].toInt();
            int startAngle = angle;
            // draw light visibility area.
            qp->setPen(QPen(color, 2, Qt::SolidLine));
            qp->setBrush(color);
            qp->drawPie(QRect(point.x()-i_diameter/2, point.y()-i_diameter/2, 1 * i_diameter, 1 * i_diameter), 16* startAngle, 16*range);
        }
    }
    // create dynamic radar
    qp->drawPie(QRect(point.x()-i_diameter/2, point.y()-i_diameter/2, 1 * i_diameter, 1 * i_diameter), 16*this->scanCourse, 16*30);
    qp->restore();
}

QPixmap Widget::paintWidget()
{
    QPixmap pixmap(this->width(),this->height());
    QPainter p_painter(&pixmap);
    p_painter.setRenderHint(QPainter::Antialiasing);
    pixmap.fill(Qt::black);
    this->drawLadar(&p_painter);
    this->detectObjects(&p_painter);
    this->drawRadarLight(&p_painter);
    return pixmap;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter p_painter(this);
         //Anti-aliasing
    p_painter.setRenderHint(QPainter::Antialiasing);

    p_painter.drawPixmap(0,0,this->width(),this->height(),paintWidget());

    QWidget::paintEvent(event);
}
