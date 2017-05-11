#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QtGlobal>
#include <QList>
#include <QListWidget>

#define BIN_NUM (8)
#define TOTE_NUM (3)
#define TOTAL_NUM (BIN_NUM + TOTE_NUM)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

private:
    void initItemList();
    void initBinList();
    void init();
    void unselectedAll();
    void addBinContent(int);
    void clearBinContent(int);
    void workForBin(int);

    void save();
    void exit();

    QAction *saveAct;
    QAction *exitAct;

    QList<QListWidget *> binList;
    QList< QList<QString> > workOrder;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
