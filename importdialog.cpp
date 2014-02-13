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
    checkerbrush.setTextureImage(QImage(":/images/checkerboard"));
    ui->graphicsView_preview->setBackgroundBrush(checkerbrush);
    ui->graphicsView_preview->setBackgroundRole(QPalette::Dark);
    ui->graphicsView_preview->setScene(&mScene);
    fillTree(imgFiles);
}

ImportDialog::~ImportDialog()
{
    delete ui;
}

void ImportDialog::onItemSelectionChanged(QTreeWidgetItem* itm,int col)
{
    ui->stack_pages->setCurrentIndex(itm->data(1,0) == "Group" ? 1 : 0);
    mImg = new QImage(mTmpList.value(itm->data(2,0).toString()).path);

    mPixmap = new QGraphicsPixmapItem(QPixmap::fromImage(*mImg));

    mScene.setSceneRect(0,0,mImg->width(), mImg->height());
    mScene.clear();
    mScene.addItem(mPixmap);
   // ui->graphicsView_preview->setScene(&mScene);
}

void ImportDialog::fillTree(QList<QUrl> urls)
{
    using namespace std;

    foreach(QUrl url, urls)
    {
        TmpObj tmp = createTmpObj(url);

        mTmpList.insert(tmp.ID,tmp);

        QTreeWidgetItem* tree_itm = new QTreeWidgetItem();
        QIcon ico(tmp.path);
        tree_itm->setIcon(0,ico);
        tree_itm->setText(0, tmp.name);
        tree_itm->setText(1, tmp.contours.size() > 1 ? "Group":"Single");
        tree_itm->setText(2, tmp.ID);

        ui->tree_images->addTopLevelItem(tree_itm);
    }
}

void ImportDialog::createConnections()
{
    connect(ui->tree_images,SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this,SLOT(onItemSelectionChanged(QTreeWidgetItem*,int)));
}

ImportDialog::TmpObj ImportDialog::createTmpObj(QUrl url)
{
    TmpObj tmp;
    tmp.ID = QUuid::createUuid().toString();
    tmp.name = url.fileName();
    tmp.path = url.path();
    tmp.contours = mImgProc.findContours(url.path());

    return tmp;
}
