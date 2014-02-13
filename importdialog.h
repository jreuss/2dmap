#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>
#include <QUrl>
#include <QList>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QString>
#include <QUuid>
#include <QHash>
#include <QGraphicsScene>
#include <QImage>
#include <QPixmap>
#include <opencv2/core/core.hpp>
#include <QGraphicsPixmapItem>
#include <QBrush>

#include "imgproc.h"

namespace Ui {
class ImportDialog;
}

class ImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportDialog(QWidget *parent = 0);
    ImportDialog(QList<QUrl> imgFiles, QWidget *parent = 0);

    ~ImportDialog();
public slots:
   void onItemSelectionChanged(QTreeWidgetItem*,int);


private:
    void fillTree(QList<QUrl> urls);
    void createConnections();

    struct TmpObj {
        QString ID, name, path;
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Point> fixture;
    };

    TmpObj createTmpObj(QUrl url);

    QGraphicsScene mScene;
    QImage *mImg;
    QGraphicsPixmapItem *mPixmap;
    Ui::ImportDialog *ui;
    QHash<QString, TmpObj> mTmpList;
    ImgProc mImgProc;
    QBrush checkerbrush;
};

#endif // IMPORTDIALOG_H
