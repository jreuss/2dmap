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


         mImg = type == 0 ? new QImage(mTemplateManager.getTemplate(id).imgPath())
                          : new QImage(mGroupList.value(id).path);

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

    }

    updateTree();
}

void ImportDialog::parseUrls(QList<QUrl> urls)
{
    using namespace std;

    foreach(QUrl url, urls)
    {
        QString path = QDir::toNativeSeparators(url.toLocalFile());
        QString id = QUuid::createUuid().toString();
        vector<vector<cv::Point> > contour =
                mImgProc.findContours(path);

        if(contour.size() == 1)
        {
            ElementTemplate tmp(id);
            tmp.setImgPath(path);
            tmp.setContour(contour.front());
            tmp.setName(url.fileName());

            mTemplateManager.addTemplate(id, tmp);
        }
        else
        {
            MatchGroup group;
            group.contours = contour;
            group.matchList = mImgProc.get_matches(group.contours, 0.01);
            group.path = path;
            group.name = url.fileName();

            mGroupList.insert(id, group);
        }
    }

    updateTree();
}

void ImportDialog::updateTree()
{

    QHashIterator<QString, ElementTemplate> templateIter = mTemplateManager.getIterator();

    while(templateIter.hasNext())
    {
        templateIter.next();

        if(!mTreeList.contains(templateIter.key()))
        {
            createTreeItem(templateIter.value().imgPath(), templateIter.value().name(),
                           "Single", templateIter.key());
        }
    }

    QHashIterator<QString, MatchGroup> groupIter(mGroupList);

    while(groupIter.hasNext())
    {
        groupIter.next();

        if(!mTreeList.contains(groupIter.key()))
        {
            createTreeItem(groupIter.value().path, groupIter.value().name,
                           "Group", groupIter.key());
        }
    }
}

void ImportDialog::createTreeItem(const QString &path, const QString &name,
                                  const QString &type, const QString &id)
{
    QTreeWidgetItem* tree_itm = new QTreeWidgetItem();

    QIcon ico(path);
    tree_itm->setIcon(0, ico);
    tree_itm->setText(0, name);
    tree_itm->setText(1, type);
    tree_itm->setText(2, id);

    mTreeList.append(id);
    ui->tree_images->addTopLevelItem(tree_itm);
}

void ImportDialog::createConnections()
{
    connect(ui->tree_images,SIGNAL(clicked(QModelIndex)),
            this,SLOT(onItemSelectionChanged(QModelIndex)));
    connect(ui->btn_apply,SIGNAL(clicked()),this,SLOT(applySplitOption()));
}


