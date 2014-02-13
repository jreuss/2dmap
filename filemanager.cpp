#include "filemanager.h"

FileManager::FileManager()
{
    file_dialog = new QFileDialog;
}

QList<QUrl> FileManager::FileDialog() const
{
    QString selection_filter = "PNG (*.png *.PNG)";
    QString title = "open image(s)";
    QString path = "/home/joachim/Pictures/";

    return file_dialog->getOpenFileUrls(0, title, path, selection_filter);
}

FileManager::~FileManager()
{
    file_dialog = NULL;
    delete file_dialog;
}
