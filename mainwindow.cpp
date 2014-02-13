#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createActions();
}

void MainWindow::createActions()
{
    connect (ui->actionQuit, SIGNAL (triggered()), qApp, SLOT (quit()));
    connect (ui->actionImport, SIGNAL(triggered()), this, SLOT (onImport()));
}

MainWindow::~MainWindow()
{
    mImportDialog = NULL;

    delete mImportDialog;
    delete ui;
}

/* =====================================
 * region: events
 * ===================================*/

void MainWindow::onImport()
{
    QList<QUrl> urls = mFileManager.FileDialog();

    if (urls.count() != 0)
    {
        mImportDialog = new ImportDialog(urls, this);
        mImportDialog->setModal(true);
        mImportDialog->exec();
    }
}
