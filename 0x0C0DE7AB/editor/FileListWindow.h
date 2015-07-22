#ifndef FILELISTWINDOW_H
#define FILELISTWINDOW_H

#include <QMainWindow>

class QFileSystemModel;
class QStringListModel;

namespace Ui {
class FileListWindow;
}

enum class FileListRoot
{
    Assets,
    Documents
};

class FileListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileListWindow(QWidget *parent = 0);
    ~FileListWindow();

signals:
    void sourceSelected(QString filename);

private slots:
    void on_btnLoad_clicked();

public slots:
    void SelectAssets();
    void SelectDocuments();
    void RefreshList();

private:
    Ui::FileListWindow *ui;

    QFileSystemModel *m_fileListModel;
    QStringListModel *m_samplesListModel;

    FileListRoot m_fileListRoot;
    void loadSamplesListModel();
};

#endif // FILELISTWINDOW_H
