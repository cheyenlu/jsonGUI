#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonDocument>

void MainWindow::initItemList()
{
    QString path = QCoreApplication::applicationDirPath();
    path.append("/classes.txt");
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Can't find the classes file";
    }
    else{
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QListWidgetItem *item = new QListWidgetItem(line);
            ui->candidateList->addItem(item);
        }
        file.close();
    }
}

void MainWindow::initBinList()
{
    binList.append(ui->binList0);
    binList.append(ui->binList1);
    binList.append(ui->binList2);
    binList.append(ui->binList3);
    binList.append(ui->binList4);
    binList.append(ui->binList5);
    binList.append(ui->binList6);
    binList.append(ui->binList7);
    binList.append(ui->binList8);
    binList.append(ui->binList9);
    binList.append(ui->binList10);
}

void MainWindow::init()
{
    //menu
    ui->menuBar->setVisible(true);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    QMenu *fileMenu = ui->menuBar->addMenu(tr("&File"));
    fileMenu->addAction(saveAct);
    fileMenu->addAction(exitAct);

    //init
    initItemList();
    initBinList();
    //create 8 elements in work order
    for(int i = 0; i < BIN_NUM; i++){
        QList<QString> *s = new QList<QString>();
        workOrder.append(*s);
    }
    //bind button and callback
    connect(ui->binAdd0, &QPushButton::clicked, [=](){ this->addBinContent(0); });
    connect(ui->binAdd1, &QPushButton::clicked, [=](){ this->addBinContent(1); });
    connect(ui->binAdd2, &QPushButton::clicked, [=](){ this->addBinContent(2); });
    connect(ui->binAdd3, &QPushButton::clicked, [=](){ this->addBinContent(3); });
    connect(ui->binAdd4, &QPushButton::clicked, [=](){ this->addBinContent(4); });
    connect(ui->binAdd5, &QPushButton::clicked, [=](){ this->addBinContent(5); });
    connect(ui->binAdd6, &QPushButton::clicked, [=](){ this->addBinContent(6); });
    connect(ui->binAdd7, &QPushButton::clicked, [=](){ this->addBinContent(7); });
    connect(ui->binAdd8, &QPushButton::clicked, [=](){ this->addBinContent(8); });
    connect(ui->binAdd9, &QPushButton::clicked, [=](){ this->addBinContent(9); });
    connect(ui->binAdd10, &QPushButton::clicked, [=](){ this->addBinContent(10); });

    connect(ui->binClear0, &QPushButton::clicked, [=](){ this->clearBinContent(0); });
    connect(ui->binClear1, &QPushButton::clicked, [=](){ this->clearBinContent(1); });
    connect(ui->binClear2, &QPushButton::clicked, [=](){ this->clearBinContent(2); });
    connect(ui->binClear3, &QPushButton::clicked, [=](){ this->clearBinContent(3); });
    connect(ui->binClear4, &QPushButton::clicked, [=](){ this->clearBinContent(4); });
    connect(ui->binClear5, &QPushButton::clicked, [=](){ this->clearBinContent(5); });
    connect(ui->binClear6, &QPushButton::clicked, [=](){ this->clearBinContent(6); });
    connect(ui->binClear7, &QPushButton::clicked, [=](){ this->clearBinContent(7); });
    connect(ui->binClear8, &QPushButton::clicked, [=](){ this->clearBinContent(8); });
    connect(ui->binClear9, &QPushButton::clicked, [=](){ this->clearBinContent(9); });
    connect(ui->binClear10, &QPushButton::clicked, [=](){ this->clearBinContent(10); });

    connect(ui->binWork0, &QPushButton::clicked, [=](){ this->workForBin(0); });
    connect(ui->binWork1, &QPushButton::clicked, [=](){ this->workForBin(1); });
    connect(ui->binWork2, &QPushButton::clicked, [=](){ this->workForBin(2); });
    connect(ui->binWork3, &QPushButton::clicked, [=](){ this->workForBin(3); });
    connect(ui->binWork4, &QPushButton::clicked, [=](){ this->workForBin(4); });
    connect(ui->binWork5, &QPushButton::clicked, [=](){ this->workForBin(5); });
    connect(ui->binWork6, &QPushButton::clicked, [=](){ this->workForBin(6); });
    connect(ui->binWork7, &QPushButton::clicked, [=](){ this->workForBin(7); });
}

void MainWindow::unselectedAll()
{
    ui->candidateList->clearSelection();
    for(int i = 0; i < TOTAL_NUM; i++){
        binList[i]->clearSelection();
    }
}

void MainWindow::addBinContent(int binNumber)
{
    foreach(QListWidgetItem* item, ui->candidateList->selectedItems()){
        //item->setBackground(Qt::red);
        QListWidgetItem *newItem = new QListWidgetItem(*item);
        binList[binNumber]->addItem(newItem);
    }
    unselectedAll();
}

void MainWindow::clearBinContent(int binNumber)
{
    unselectedAll();
    binList[binNumber]->clear();
}

void MainWindow::workForBin(int binNumber)
{
    workOrder[binNumber].clear();
    for(int i = 0; i < binList[binNumber]->count(); i++){
        binList[binNumber]->item(i)->setBackground(Qt::white);
    }

    foreach(QListWidgetItem* item, binList[binNumber]->selectedItems()){
        item->setBackground(Qt::red);
        workOrder[binNumber].append(item->text());
    }
    unselectedAll();
    //qDebug() << workOrder[binNumber].size();
}

void MainWindow::exit()
{
    close();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // set window to the center of screen
    ui->setupUi(this);
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());

    //setup UI
    ui->setupUi(this);

    //initialization
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::save()
{
    //qDebug() << "save file";
    QString fileName = QFileDialog::getSaveFileName(this,
           tr("Save JSON file"), "",
           tr("JSON (*.json);;All Files (*)"));

    if (fileName.isEmpty())
            return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        QJsonObject jsonObject, jsonBinContents, jsonToteContents;
        QJsonArray jsonWorkOrder;
        QJsonArray contentArray[TOTAL_NUM];
        QJsonArray workArray[BIN_NUM];

        for(int idx = 0; idx < TOTAL_NUM; idx++){
            for(int itemNum = 0; itemNum < binList[idx]->count(); itemNum++){
                QJsonValue value(binList[idx]->item(itemNum)->text());
                //qDebug() << value.toString();
                contentArray[idx].append(value);
            }
        }

        for(int idx = 0; idx < BIN_NUM; idx++){
            for(int itemNum = 0; itemNum < workOrder[idx].count(); itemNum++){
                QJsonValue value(workOrder[idx][itemNum]);
                workArray[idx].append(value);
            }
        }

        QList<QString> nameList = {"bin_A", "bin_B", "bin_C", "bin_D", "bin_E", "bin_F", "bin_G", "bin_H", "tote_1", "tote_2", "tote_3"};
        //bin content
        for(int i = 0; i < BIN_NUM; i++){
            jsonBinContents[nameList[i]] = contentArray[i];
        }
        //tote content
        for(int i = BIN_NUM; i < TOTAL_NUM; i++){
            jsonToteContents[nameList[i]] = contentArray[i];
        }
        QJsonObject works;
        for(int i = 0; i < BIN_NUM; i++){
            works.insert("bin", QJsonValue(nameList[i]));
            works.insert("items", workArray[i]);
            jsonWorkOrder.append(works);
        }

        jsonObject["bin_contents"] = jsonBinContents;
        jsonObject["tote_contents"] = jsonToteContents;
        jsonObject["work_order"] = jsonWorkOrder;
        QJsonDocument JsonDocument(jsonObject);
        file.write(JsonDocument.toJson());
        file.close();
    }
}
