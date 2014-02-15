#include "importdialog.h"
#include "ui_importdialog.h"



ImportDialog::ImportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportDialog)
{
    ui->setupUi(this);
    createConnections();
}

ImportDialog::ImportDialog(QList<QUrl> imgFiles, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportDialog)
{
    ui->setupUi(this);
    ui->tree_images->hideColumn(2);
    createConnections();
    mCheckerbrush.setTextureImage(QImage(":/images/checkerboard"));
    ui->graphicsView_preview->setBackgroundBrush(mCheckerbrush);
    ui->graphicsView_preview->setBackgroundRole(QPalette::Dark);
    ui->graphicsView_preview->setScene(&mScene);
    parseUrls(imgFiles);
}

ImportDialog::~ImportDialog()
{
    mImg = NULL; mPixmap = NULL; mCurrentItm = NULL;

    delete mImg; delete mPixmap; delete mCurrentItm;
    delete ui;
}

void ImportDialog::onItemSelectionChanged(QModelIndex index)
{
    if(index.row() != mCurrentIndex.row())
    {
        mCurrentIndex = index;
        mCurrentItm = ui->tree_images->currentItem();

        int type = mCurrentItm->data(1,0) == "Group" ? 1 : 0;
        QString id = mCurrentItm->data(2,0).toString();
        ui->stack_pages->setCurrentIndex(type);

        mImg = new QImage(mTreeItemList.value(id).img);

        mPixmap = new QGraphicsPixmapItem(QPixmap::fromImage(*mImg));

        mScene.setSceneRect(0,0,mImg->width(), mImg->height());
        mScene.clear();
        mScene.addItem(mPixmap);

        QWidget *page = ui->stack_pages->currentWidget();
        QRect origin = page->rect();
        QRect offset = QRect(page->pos().x() - page->width(), page->pos().y(),
                             page->width(), page->height());

        QPropertyAnimation *anim = new QPropertyAnimation(page, "geometry");
        anim->setDuration(200);
        anim->setStartValue(offset);
        anim->setEndValue(origin);
        anim->setEasingCurve(QEasingCurve::OutQuad);

        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void ImportDialog::applySplitOption()
{
    if(ui->radio_split->isChecked())
    {
        QString id = ui->tree_images->currentItem()->data(2,0).toString();
        TreeItem itm = mTreeItemList.value(id);

        itm.matchList = mImgProc.get_matches(itm.contours, 0.1);

        QList<TreeItem> list = mImgProc.split(itm, ui->tree_images->currentItem());

        foreach (TreeItem t, list) {
            mTreeItemList.insert(QUuid::createUuid().toString(), t);
        }
    }

    updateTree();

    if(ui->tree_images->currentItem()->childCount() > 0)
    {
        ui->tree_images->currentItem()->setExpanded(true);
    }
}

void ImportDialog::parseUrls(QList<QUrl> urls)
{
    using namespace std;

    foreach(QUrl url, urls)
    {
        TreeItem treeItem;
        treeItem.path = QDir::toNativeSeparators(url.toLocalFile());
        treeItem.img = QImage(treeItem.path);
        treeItem.contours = mImgProc.findContours(treeItem.path);
        treeItem.name = url.fileName();
        treeItem.itemType = treeItem.contours.size() == 1 ?
                    "Single" : "Group";

        mTreeItemList.insert(QUuid::createUuid().toString(), treeItem);
    }

    updateTree();
}

void ImportDialog::updateTree()
{
    QHashIterator<QString, TreeItem> iter(mTreeItemList);

    while(iter.hasNext())
    {
        iter.next();

        if(!mTreeList.contains(iter.key()))
        {
            createTreeItem(iter.value().name, iter.value().itemType,
                           iter.key(), iter.value().img, iter.value().parent);
        }
    }
}

void ImportDialog::createTreeItem(const QString &name, const QString &type,
                                  const QString &id, const QImage& img, QTreeWidgetItem* parent)
{
    QTreeWidgetItem* tree_itm = new QTreeWidgetItem();

    QIcon ico(QPixmap::fromImage(img));
    tree_itm->setIcon(0, ico);
    tree_itm->setText(0, name);
    tree_itm->setText(1, type);
    tree_itm->setText(2, id);

    mTreeList.append(id);

    if(parent == NULL)
    {
        ui->tree_images->addTopLevelItem(tree_itm);
    }
    else
    {
       parent->addChild(tree_itm);
    }
}

void ImportDialog::createConnections()
{
    connect(ui->tree_images,SIGNAL(clicked(QModelIndex)),
            this,SLOT(onItemSelectionChanged(QModelIndex)));
    connect(ui->btn_apply,SIGNAL(clicked()),this,SLOT(applySplitOption()));
}


