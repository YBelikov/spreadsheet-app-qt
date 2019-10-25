#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "spreadsheet.h"
#include "searchdialog.h"
#include "sortdialog.h"
class QAction;

class MainWindow : public QMainWindow
{

public:

    MainWindow(QWidget *wgt = nullptr);
protected:
    void closeEvent(QCloseEvent*);

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void find();
    void goToCell();
    void openRecentFile();
    void updateStatusBar();
    void spreadSheetModified();

private:
    enum {maxRecentFiles = 5};

    SpreadSheet *document;
    SearchDialog *searchDialog;
    SortDialog *sortDialog;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *toolsMenu;
    QMenu *optionsMenu;

    QAction *newAction;
    QAction *openAction;
    QAction *saveFileAction;
    QAction *saveFileAsAction;
    QAction *recentFileActions[maxRecentFiles];
    QAction *exitAction;
    QAction *selectAllAction;
    QAction *showGridAction;
    QAction *copyAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *deleteAction;
    QAction *sortAction;
    QAction *searchAction;
    QAction *aboutAction;

    QString currentFile;
    QStringList recentFiles;


    void createActions();
    void createMenus();
    void createToolBars();
    void createContextMenu();
    void createStatusBar();
    void setCurrentFileName(const QString&);
    void readSettings();
    void saveSettings();
    bool openFile(const QString&);
    bool saveFile(const QString&);

    void updateRecentFileActions();

};

#endif // MAINWINDOW_H
