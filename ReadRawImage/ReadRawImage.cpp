#include "ReadRawImage.h"
#include "ui_ReadRawImage.h"

#include <QFile>
#include <QByteArray>

#include <iostream>

ReadRawImage::ReadRawImage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadRawImage)
{
    ui->setupUi(this);
    QFile file("E:\\temp\\IMG00000000000000000825.3384x2712.Mono12.raw");
    if (!file.open(QIODevice::ReadOnly))
    {
        //TODO
    }
    QByteArray blob = file.readAll();
    std::cout << blob.length() << std::endl;
    const int histogramLength = 65536;
    int histogram[histogramLength];

    //std::cout << sizeof(histogram) / sizeof(int) << std::endl;

    //TODO memset
    for (int i = 0; i < histogramLength; i++)
    {
        histogram[i] = 0;
    }

    // generate histogram
    //for (int i = 0; i < blob.length(); i += 2)
    for (int i = 0; i < blob.length(); i += 2) //blob.length(); i += 2)
    {
        //std::cout << blob.at(i) << std::endl;
        int value = blob.at(i) * 256 + blob.at(i + 1);
        //std::cout << value << std::endl;
        if (value > histogramLength)
        {
            //std::cout << "problem!" << std::endl;
            //histogram[value]++;
        }
        //histogram[blob.at(i)]++;
    }

    // print histogram
    for (int i = 0; i < histogramLength; i++)
    {
        if (histogram[i] != 0)
        {
            std::cout << i << ": " << histogram[i] << std::endl;
        }
    }
}

ReadRawImage::~ReadRawImage()
{
    delete ui;
}
