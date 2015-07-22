#include "FileListWindow.h"

#include "ui_FileListWindow.h"

#include <QFileSystemModel>
#include <QStringListModel>
#include <QDirIterator>
#include <QStringList>

FileListWindow::FileListWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileListWindow),
    m_fileListRoot(FileListRoot::Assets),
    m_fileListModel(new QFileSystemModel()),
    m_samplesListModel(new QStringListModel())
{
    ui->setupUi(this);

    loadSamplesListModel();

    ui->fileListView->setModel(m_fileListModel);
    ui->samplesListView->setModel(m_samplesListModel);

    emit RefreshList();
}

FileListWindow::~FileListWindow()
{
    delete ui;
    delete m_fileListModel;
}

void FileListWindow::SelectAssets()
{
    qDebug("assets");
    m_fileListRoot = FileListRoot::Assets;
    emit RefreshList();
}

void FileListWindow::SelectDocuments()
{
    qDebug("documents");
    m_fileListRoot = FileListRoot::Documents;
    emit RefreshList();
}

void FileListWindow::loadSamplesListModel()
{
    QStringList list;

    QString folder = ":/Assets/";
    QDirIterator it(folder, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        list << it.next().mid(folder.length());
    }

    m_samplesListModel->setStringList(list);
}

void FileListWindow::RefreshList()
{
    qDebug("refresh list");

    QString cwd;

    switch(m_fileListRoot)
    {
    case FileListRoot::Assets:
        ui->aLocationAssets->setChecked(true);
        ui->aLocationDocuments->setChecked(false);
        ui->fileListView->hide();
        ui->samplesListView->show();
        break;
    case FileListRoot::Documents:
    {
        ui->aLocationAssets->setChecked(false);
        ui->aLocationDocuments->setChecked(true);

        ui->fileListView->show();
        ui->samplesListView->hide();

        cwd = QDir::currentPath();
        m_fileListModel->setRootPath(cwd);

        auto root_index = m_fileListModel->index(cwd);
        ui->fileListView->setRootIndex(root_index);
        break;
    }
    }
}

void FileListWindow::on_btnLoad_clicked()
{
    QString filename;

    switch(m_fileListRoot)
    {
    case FileListRoot::Assets:
    {
        auto indices = ui->samplesListView->selectionModel()->selectedIndexes();
        if (indices.count() > 0)
        {
            auto index = indices.first();
            filename = ":/Assets/" + m_samplesListModel->data(index, Qt::DisplayRole).toString();
            emit sourceSelected(filename);
        }
        break;
    }
    case FileListRoot::Documents:
        break;
    }
}
