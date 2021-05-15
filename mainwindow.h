#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Cabinet.h>
#include <Card.h>
#include <threadmanager.h>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addCabinets();
    void addPCBs();


signals:
    void sendData(char*, int);

private slots:
    void on_pushButton_clicked();
    void handleHealthData(char*, int);


private:
    Ui::MainWindow *ui;
    int iNumberofCabinets;
    int iCabWidth;
    int iCabHeight;
    QHash<int, Cabinet*> cabinetHashTable;
    Card *myCard;
    ThreadManager* myManager;
    char buffer[100];
};
#endif // MAINWINDOW_H
