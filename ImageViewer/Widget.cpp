#include "Widget.h"
#include "ui_Widget.h"

#include <qmath.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    int width = 512;
    int height = 512;

    unsigned char* pic = new unsigned char[width * height];

    for (int i = 0; i < width * height; i++)
    {
        pic[i] = i % 256;
    }

    QImage img(pic, width, height, QImage::Format_Indexed8);

    QGraphicsScene* scene = new QGraphicsScene();
    QPixmap pixmap = QPixmap::fromImage(img);

    scene->addPixmap(pixmap);

    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->viewport()->installEventFilter(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *target, QEvent *event)
{
    if (target == ui->graphicsView->viewport())
    {
        if (event->type() == QEvent::Wheel)
        {
            QWheelEvent *wheelEvent = static_cast<QWheelEvent *> (event);

            qreal factor = qPow(1.2, wheelEvent->delta() / 240.0);
            ui->graphicsView->scale(factor, factor);
            //ui->graphicsView->rotate(factor);
            //event->accept();
            return true;
        }

    }
    return false;
}
