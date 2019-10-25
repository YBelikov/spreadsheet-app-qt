#include "mainwindow.h"
#include <QAction>

MainWindow::MainWindow(QWidget *wgt) : QMainWindow(wgt)
{
    document = new SpreadSheet;
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createContextMenu();
    searchDialog = nullptr;
    readSettings();
}
void MainWindow::createActions(){
    newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create new spreadsheet file"));
    newAction-setIcon(":/images/new.png");
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    openAction = new QAction(tr("&Open..."), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open new spreadsheet file"));
    openAction->setIcon(":/images/open.png");
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));

    saveFileAction = new QAction(tr("Save file"), this);
    saveFileAction->setShortcut(QKeySequence::Save);
    saveFileAction->setStatusTip(tr("Save spreadsheet file"));
    saveFileAction->setIcon(":/images/save.png");
    connect(saveFileAction, SIGNAL(triggered()), this, SLOT(saveFile()));

    saveFileAsAction = new QAction(tr("Save as"), this);
    saveFileAsAction->setShortcut(QKeySequence::SaveAs);
    saveFileAsAction->setStatusTip(tr("Save spreadsheet file as"));
    saveFileAction->setIcon(":/images/saveAs.png");
    connect(saveFileAsAction, SIGNAL(triggered()), this, SLOT(saveFileAs()));

    for(int i = 0; i < maxRecentFiles; ++i){
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
    }

    selectAllAction = new QAction(tr("Select all"), this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setStatusTip(tr("Select all cells in spreadsheet file"));
    selectAllAction->setIcon(":/images/selectAll.png");
    connect(selectAllAction, SIGNAL(triggered()), document, SLOT(selectAll()));

    showGridAction = new QAction(tr("Show grid"), this);
    showGridAction->setCheckable(true);
    showGridAction->setChecked(true);
    showGridAction->setStatusTip(tr("Show or hide grid of spreadsheet document"));
    connect(showGridAction, SIGNAL(toggled(bool)), this, SLOT(showGrid(bool)));

    copyAction = new QAction(tr("Copy"), this);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setIcon(":/images/copy.png");
    copyAction->setStatusTip(tr("Copy information of selected cells in spreadsheet document"));
    connect(copyAction, SIGNAL(triggered()), document, SLOT(copy()));

    cutAction = new QAction(tr("Cut"), this);
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setIcon(":/images/cut.png");
    cutAction->setStatusTip(tr("Cut information of selected cells in spreadsheet document"));

    deleteAction = new QAction(tr("Delete"), this);
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setIcon(":/image/delete.png");
    deleteAction->setStatusTip(tr("Delete information selected cells in spreadsheet document")));
    connect(deleteAction, SIGNAL(triggered()), document, SLOT(delete()));

    sortAction = new QAction(tr("Sort"), this);
    sortAction->setStatusTip(tr("Sort selected cells in spreadsheet document"));
    connect(sortAction, SIGNAL(triggered()), document, SLOT(sort()));

    aboutAction = new QAction(tr("About"), this);
    aboutAction->setShortcut(Qt::Key_F9);
    aboutAction->setStatusTip(tr("Show information about Qt"));
    connect(aboutAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

}
