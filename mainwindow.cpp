#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "NetworkCommon.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    iNumberofCabinets = 5;
    iCabWidth = 100;
    iCabHeight = 500;
    addCabinets();
    addPCBs();
    myManager = new ThreadManager(this);
    connect(this, SIGNAL(sendData(char*, int)), myManager->getUdpSender(), SIGNAL(hasDataToSend(char*, int)));
    connect(myManager->getPacketProcessor(), SIGNAL(sigHealthData(char*, int)), this, SLOT(handleHealthData(char*, int)));

}

MainWindow::~MainWindow()
{
    delete myManager;

    for (int i=0;i<iNumberofCabinets;i++)
    {
        Cabinet* cabinetToBeDeleted = cabinetHashTable[i+1];
        if (cabinetToBeDeleted!=NULL)
        {
            delete cabinetToBeDeleted;
        }
    }
    delete ui;
}

void
MainWindow::addCabinets()
{
    Cabinet* tempCab;
    int xpos = 10;
    int id;
    for (int i=0;i<iNumberofCabinets; i++)
    {
        id = i+1;
        tempCab =  new Cabinet(id, iCabWidth,iCabHeight,5, this);
        tempCab->setFillColor(QColor(Qt::lightGray));
        tempCab->setLineColor(QColor(Qt::green));
        tempCab->setNumberOfLevels(3);
        cabinetHashTable[id]=tempCab;
        tempCab->move(xpos,10);
        xpos = xpos + iCabWidth +  10;
        tempCab->show();
    }
}

void
MainWindow::addPCBs()
{
    Cabinet* tempCab;
    int pcbId=1;
    int cardwidth, cardheight;
    int xpos, ypos;
    for (int i=0;i<iNumberofCabinets; i++)
    {
        tempCab = cabinetHashTable[i+1];
        cardwidth =  10;
        cardheight = 120;

        for (int iLevelId =1; iLevelId<=3; iLevelId++)
        {
            xpos = 10;
            ypos = 20;

            tempCab->addPCB(pcbId, iLevelId, cardwidth, cardheight);
            tempCab->movePCB(pcbId, xpos,ypos);

            pcbId=pcbId+1;
            tempCab->addPCB(pcbId, iLevelId, cardwidth, cardheight);
            xpos = xpos + 30;
            tempCab->movePCB(pcbId, xpos,ypos);

            pcbId=pcbId+1;
            tempCab->addPCB(pcbId, iLevelId, cardwidth, cardheight);
            xpos = xpos + 30;
            tempCab->movePCB(pcbId, xpos,ypos);
        }
    }
}


void MainWindow::on_pushButton_clicked()
{
    SamplePacket sp;
    int len;
    QString str =  ui->teID->toPlainText();
    sp.id = str.toInt();
    str = ui->teTemp->toPlainText();
    sp.temp = str.toInt();
    len = sizeof(sp);
    sp.header.category=CAT_SAMPLE;
    sp.header.subitem=SUBCAT_SAMPLE;
    memcpy(buffer, &sp, len);
    emit sendData(buffer, len);
}

void
MainWindow::handleHealthData(char *data, int len)
{
    SamplePacket sp;
    memcpy(&sp, data, len);

    qDebug()<<sp.header.category <<"  "<<sp.header.subitem <<"  "<<sp.id <<"   "<<sp.temp;
}



