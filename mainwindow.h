#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "spreadsheet.h"
#include "searchdialog.h"
#include "sortdialog.h"
#include "gotocelldialog.h"

class QAction;
class QSettings;

class MainWindow : public QMainWindow
{

Q_OBJECT

public:

    MainWindow(QWidget *wgt = nullptr);
protected:

    virtual void closeEvent(QCloseEvent*) override;

private slots:
    void newFile();
    void openFile();
    bool save();
    bool saveFileAs();
    void search();
    void goToCell();
    void openRecentFile();
    void updateStatusBar();
    void documentModified();
    void about();

private:
    enum {maxRecentFiles = 5};

    SpreadSheet *document;
    SearchDialog *searchDialog;
    SortDialog *sortDialog;
    GoToCellDialog *goToCellDialog;
    QString currentFile;
    QStringList recentFiles;


    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *toolsMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;

    QLabel *positionLabel;
    QLabel *formulaLabel;

    QAction *newAction;
    QAction *openAction;
    QAction *saveFileAction;
    QAction *saveFileAsAction;
    QAction *recentFileActions[maxRecentFiles];
    QAction *separatorAction;
    QAction *exitAction;
    QAction *selectAllAction;
    QAction *showGridAction;
    QAction *copyAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *deleteAction;
    QAction *selectRowAction;
    QAction *selectColumnAction;
    QAction *aboutQtAction;
    QAction *goToCellAction;
    QAction *recalculateAction;
    QAction *autoRecalculateAction;

    QAction *sortAction;
    QAction *searchAction;
    QAction *aboutAction;


    QToolBar *fileBar;
    QToolBar *editBar;

    void createActions();
    void createMenus();
    void createToolBars();
    void createContextMenu();
    void createStatusBar();
    void setCurrentFileName(const QString&);
    void readSettings();
    void saveSettings();

    bool saveFile(const QString&);
    bool loadFile(const QString&);

    bool okToContinue();
    void updateRecentFileActions();


    QString getFileName(const QString&);
};

#endif // MAINWINDOW_H
