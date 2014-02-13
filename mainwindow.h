#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "filemanager.h"
#include "importdialog.h"

#include <QMainWindow>
#include <QDebug>
#include <QUrl>
#include <QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void createActions();

    ~MainWindow();

public slots:
    void onImport();

private:
    Ui::MainWindow *ui;
    FileManager mFileManager;
    ImportDialog *mImportDialog;
};

#endif // MAINWINDOW_H
