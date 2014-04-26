#include "mainwindow.h"
#include "pic.h"
#include <QtGui>
#include <algorithm>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    int width = 600;
    int height = 500;

    //Pic test = Pic(width, height);
    //test.initPic(4);
    //test.setPixelValue(width/2, height/2, 0);
    //test.markLine(2, 0);
    //test.markLine(100, 122);
    //test.markColumn(200, 0);
    //test.markColumn(500, 10);

    /*QVector <QRgb> colorTable;
    for (int i = 0; i < 256; i++) {
        QRgb rgb
    }*/

    /*QImage *image = new QImage(, height, QImage::Format_Indexed8);
    uchar* bits = image->bits();
    //QVector<QRgb> colorTable = image->colorTable();

    srand(12);
    for (int i = 0; i < width * height; i++) {
        bits[i] = rand() % 256;
    }*/

    //QImage image(test.getPixels(), test.getWidth(), test.getHeight(), QImage::Format_Indexed8);
    QImage *image = new QImage(width, height, QImage::Format_Indexed8);
    //Pic test()
    /*unsigned char* imageBits = image->bits();
    for (unsigned int i = 0; i < height * width; i++) {
        imageBits[i] = i % 256;
    }*/
    Pic test(image->bits(), image->width(), image->height());
    //test.generarteStripes(stripeWidth, offset, stripeType, invert)
    test.generarteStripes(50,  10, 1, false);
    test.spread();

    /*
    bool test_bool;
    if (1 % 2 == 1) {
        test_bool = true;
    }
    else {
        test_bool = false;
    }
    std::cout << test_bool << std::endl;
    */

    //test.generarteStripes(30, true, true);
    //test.initPic(3);
    //test.spread();

    //test.initPic(3);
    //test.fillRect(10, 20, 30, 50, 100);
    //test.drawRect(10, 20, 30, 50, 128);
    //test.fillRect(100, 100, 200, 300, 100);
    //test.drawLine(300,300,300,300,255);
    //test.drawLine(10,10,200,100,255);
    //test.markPoint(10, 20, 255);
    //test.markPoint(30, 50, 255);
    //test.markPoint(0, 0, 255);
    //test.

    //uchar* bitsOfImage = image->bits();
    //bitsOfImage = (uchar*) test2.getPixels();
    // das geht nicht so, wie ich dachte.

    // Colortable erstellen für Graustufen
    QVector<QRgb> grayscales;
    for (int i=0; i<256; ++i) {
        grayscales.push_back(qRgb(i,i,i));
    }
    // colortable dem graustufen bild zuweisen
    image->setColorTable(grayscales);
    QVector<unsigned char> vector;
    //qsort(vector.begin(), vect);
    qSort(vector);



    /*for (int x=0; x<width; ++x) {
        for (int y=0; y<height; ++y) {
            //image.setPixel(x,y, rand() % 256);
            bits[y*width+x] = rand() %256;
        }
    }*/

    // Pixel von QImage holen und mit Index manipulieren:
    /*uchar* bits = image.bits();
    for (int i = 0; i < width * height; i++) {
        bits[i] = rand() % 256;
        //bits[i] = 255;
    }*/


    QLabel *imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    imageLabel->setPixmap(QPixmap::fromImage(*image));
    //imageLabel->setPixmap();

    // Vergrößerung - leider geglättet
    //imageLabel->resize(4 * imageLabel->pixmap()->size());

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(scrollArea);

    setCentralWidget(scrollArea);

    setWindowTitle(tr("IPBasic"));
    resize(width, height);
}

MainWindow::~MainWindow()
{

}
