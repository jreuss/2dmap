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
#include <QDir>
#include <QPropertyAnimation>

#include "imgproc.h"
#include "elementtemplate.h"
#include "elementtemplatemanager.h"
#include "treeitem.h"

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
   void onItemSelectionChanged(QModelIndex);
   void applySplitOption();

private:
    void parseUrls(QList<QUrl> urls);
    void updateTree();
    void createConnections();
    void createTreeItem(const QString& name, const QString &type,
                        const QString& id, const QImage& img, QTreeWidgetItem* parent);

    ElementTemplateManager mTemplateManager;
    QHash<QString, TreeItem> mTreeItemList;
    QList<QString> mTreeList;

    QGraphicsScene mScene;
    QImage *mImg;
    QGraphicsPixmapItem *mPixmap;
    Ui::ImportDialog *ui;
    ImgProc mImgProc;
    QBrush mCheckerbrush;
    QModelIndex mCurrentIndex;
    QTreeWidgetItem *mCurrentItm;
};

#endif // IMPORTDIALOG_H
