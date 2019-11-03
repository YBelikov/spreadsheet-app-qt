#include "mainwindow.h"
#include <QAction>
#include <QMenuBar>
#include <QApplication>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QSettings>

MainWindow::MainWindow(QWidget *wgt) : QMainWindow(wgt)
{
    document = new SpreadSheet(this);
    searchDialog = nullptr;
    goToCellDialog = nullptr;

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createContextMenu();
    readSettings();
    setCentralWidget(document);

}

void MainWindow::createActions(){

    newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create new spreadsheet file"));
    newAction->setIcon(QIcon(":/images/new.png"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    openAction = new QAction(tr("&Open..."), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open new spreadsheet file"));
    openAction->setIcon(QIcon(":/images/open.png"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));

    saveFileAction = new QAction(tr("Save file"), this);
    saveFileAction->setShortcut(QKeySequence::Save);
    saveFileAction->setStatusTip(tr("Save spreadsheet file"));
    saveFileAction->setIcon(QIcon(":/images/save.png"));
    connect(saveFileAction, SIGNAL(triggered()), this, SLOT(saveFile()));

    saveFileAsAction = new QAction(tr("Save as"), this);
    saveFileAsAction->setShortcut(QKeySequence::SaveAs);
    saveFileAsAction->setStatusTip(tr("Save spreadsheet file as"));
    saveFileAsAction->setIcon(QIcon(":/images/saveAs.png"));
    connect(saveFileAsAction, SIGNAL(triggered()), this, SLOT(saveFileAs()));

    for(int i = 0; i < maxRecentFiles; ++i){
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
    }
    exitAction = new QAction(tr("Exit"), this);
    exitAction->setStatusTip(tr("Close spreadsheet editor"));
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    selectRowAction = new QAction(tr("&Select row"), this);
    selectRowAction->setStatusTip(tr("Selects choose row"));
    connect(selectRowAction, SIGNAL(triggered()), document, SLOT(selectCurrentRow()));

    selectColumnAction = new QAction(tr("&Select column"));
    selectColumnAction->setStatusTip(tr("Selects choose column"));
    connect(selectColumnAction, SIGNAL(triggered()), document, SLOT(selectCurrentColumn()));

    selectAllAction = new QAction(tr("Select all"), this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setStatusTip(tr("Select all cells in spreadsheet file"));
    selectAllAction->setIcon(QIcon(":/images/selectAll.png"));
    connect(selectAllAction, SIGNAL(triggered()), document, SLOT(selectAll()));

    showGridAction = new QAction(tr("Show grid"), this);
    showGridAction->setCheckable(true);
    showGridAction->setChecked(true);
    showGridAction->setStatusTip(tr("Show or hide grid of spreadsheet document"));
    connect(showGridAction, SIGNAL(toggled(bool)), this, SLOT(showGrid(bool)));

    copyAction = new QAction(tr("Copy"), this);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setIcon(QIcon(":/images/copy.png"));
    copyAction->setStatusTip(tr("Copy information of selected cells in spreadsheet document"));
    connect(copyAction, SIGNAL(triggered()), document, SLOT(copy()));

    pasteAction = new QAction(tr("Paste"), this);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setIcon(QIcon(":/images/paste.png"));
    pasteAction->setStatusTip(tr("Paste text in selected cells"));
    connect(pasteAction, SIGNAL(triggered()), document, SLOT(paste()));

    cutAction = new QAction(tr("Cut"), this);
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setIcon(QIcon(":/images/cut.png"));
    cutAction->setStatusTip(tr("Cut information of selected cells in spreadsheet document"));
    connect(cutAction, SIGNAL(triggered()), document, SLOT(cut()));

    deleteAction = new QAction(tr("Delete"), this);
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setIcon(QIcon(":/image/delete.png"));
    deleteAction->setStatusTip(tr("Delete information selected cells in spreadsheet document"));
    connect(deleteAction, SIGNAL(triggered()), document, SLOT(delete()));

    searchAction = new QAction(tr("Search"), this);
    searchAction->setStatusTip(tr("Search for text in spreadsheet document"));
    searchAction->setShortcut(QKeySequence::Find);
    searchAction->setIcon(QIcon(":/image/search.png"));
    connect(searchAction, SIGNAL(triggered()), this, SLOT(search()));

    sortAction = new QAction(tr("Sort"), this);
    sortAction->setStatusTip(tr("Sort selected cells in spreadsheet document"));
   // connect(sortAction, SIGNAL(triggered()), document, SLOT(sort()));

    goToCellAction = new QAction(tr("Go to cell"), this);
    goToCellAction->setStatusTip(tr("Move to cell"));
    connect(goToCellAction, SIGNAL(triggered()), this, SLOT(goToCell()));

    recalculateAction = new QAction(tr("Recalculate"), this);
    recalculateAction->setStatusTip(tr("Recalculate result of expression in a cell"));
    connect(recalculateAction, SIGNAL(triggered()), document, SLOT(recalculate()));

    autoRecalculateAction = new QAction(tr("Auto recalculate"), this);
    autoRecalculateAction->setStatusTip(tr("Auto recalculate expression in a cell"));
    autoRecalculateAction->setCheckable(true);
    autoRecalculateAction->setChecked(true);
    connect(autoRecalculateAction, SIGNAL(toggled(bool)), document, SLOT(autoRecalculate()));

    aboutAction = new QAction(tr("About"), this);
    aboutAction->setShortcut(Qt::Key_F9);
    aboutAction->setStatusTip(tr("Show information about app"));
    aboutAction->setIcon(QIcon(":/images/about.png"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About Qt"), this);
    aboutQtAction->setStatusTip(tr("Show information about Qt"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(saveFileAsAction);
    separatorAction = fileMenu->addSeparator();
    for(int i = 0; i < maxRecentFiles; ++i){
        fileMenu->addAction(recentFileActions[i]);
    }
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(cutAction);
    editMenu->addAction(deleteAction);

    QMenu *selectSubMenu = editMenu->addMenu(tr("&Select"));
    selectSubMenu->addAction(selectRowAction);
    selectSubMenu->addAction(selectColumnAction);
    selectSubMenu->addAction(selectAllAction);
    editMenu->addSeparator();
    editMenu->addAction(searchAction);
    editMenu->addAction(goToCellAction);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(recalculateAction);
    toolsMenu->addAction(sortAction);

    optionsMenu = menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(showGridAction);
    optionsMenu->addAction(autoRecalculateAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

}

void MainWindow::createToolBars(){
    fileBar = addToolBar(tr("File"));
    fileBar->addAction(openAction);
    fileBar->addAction(saveFileAction);
    fileBar->addAction(saveFileAsAction);

    editBar = addToolBar(tr("Edit"));
    editBar->addAction(copyAction);
    editBar->addAction(cutAction);
    editBar->addAction(pasteAction);
    editBar->addAction(selectAllAction);
    editBar->addAction(deleteAction);
    editBar->addSeparator();
    editBar->addAction(goToCellAction);
    editBar->addAction(searchAction);
}

void MainWindow::createStatusBar(){
    positionLabel = new QLabel("Z 999");
    positionLabel->setAlignment(Qt::AlignCenter);
    positionLabel->setMinimumSize(positionLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);

    statusBar()->addWidget(positionLabel);
    statusBar()->addWidget(formulaLabel, 1);
    connect(document, SIGNAL(positionIsChanged(int, int, int, int)), this, SLOT(updateStatusBar()));
    connect(document, SIGNAL(contentModifiied()), this, SLOT(documentModified()));
    updateStatusBar();
}

void MainWindow::createContextMenu(){
    document->addAction(copyAction);
    document->addAction(cutAction);
    document->addAction(pasteAction);
    document->addAction(deleteAction);
    document->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::updateStatusBar(){
    positionLabel->setText(document->getCurrentPosition());
    formulaLabel->setText(document->getCurrentFormula());
}

void MainWindow::documentModified(){
    setWindowModified(true);
    updateStatusBar();
}

bool MainWindow::okToContinue(){
    if(isWindowModified()){
        QMessageBox *fileNotSavedBox = new QMessageBox(QMessageBox::Warning, tr("Spreadsheet"), tr("File has been modified./n Do you want to save changes"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
                                                       | QMessageBox::Default | QMessageBox::Escape);
        int n = fileNotSavedBox->exec();
        if(n == QMessageBox::Yes) return save();
        else return false;
    }
    return true;
}

void MainWindow::newFile(){
    if(okToContinue()){
        document->clear();
        setCurrentFileName("");
    }
}

void MainWindow::openFile(){

    QString str = QFileDialog::getOpenFileName(this, tr("Open file"), ".", "Spreadsheet document (*.spst)");
   if(!str.isEmpty()){
       loadFile(str);
   }
   return;

}

bool MainWindow::loadFile(const QString& fileName){

    if(!document->readFile(fileName)){
        statusBar()->showMessage(tr("An error occured. Cannot load a file"), 3000);
        return false;
    }
    setCurrentFileName(fileName);
    statusBar()->showMessage(tr("Loading successful"), 3000);
    return true;
}

bool MainWindow::save(){
    if(currentFile.isEmpty()){
        return saveFileAs();
    }
    return saveFile(currentFile);
}



bool MainWindow::saveFileAs(){

    QString saveFileName = QFileDialog::getSaveFileName(this, "Spreadsheet", ".");
    if(!saveFileName.isEmpty()){
        return false;
    }
    return saveFile(saveFileName);
}

bool MainWindow::saveFile(const QString& fileName){
    if(!document->writeFile(fileName)){
        statusBar()->showMessage("Cannot save a file");
        return false;
    }
    statusBar()->showMessage("File saved", 3000);
    setCurrentFileName(fileName);
    return true;
}

void MainWindow::setCurrentFileName(const QString& fileName){

    currentFile = fileName;
    setWindowModified(false);
    QString shownTitle = tr("Unnamed");
    if(!currentFile.isEmpty()){
        shownTitle = getFileName(currentFile);
        recentFiles.removeAll(currentFile);
        recentFiles.prepend(currentFile);
        updateRecentFileActions();
    }
    setWindowTitle(shownTitle);
}

QString MainWindow::getFileName(const QString& fileNameWithPath){
   return QFileInfo(fileNameWithPath).fileName();
}

void MainWindow::updateRecentFileActions(){

    QMutableStringListIterator it(recentFiles);

    while(it.hasNext()){
        if(!QFile::exists(it.next())){
            it.remove();
        }
    }

    for(int i = 0; i < maxRecentFiles; ++i){
        if(i < recentFiles.count()){
            QString file = tr("%1 %2").arg(i + 1).arg(recentFiles[i]);
            recentFileActions[i]->setText(file);
            recentFileActions[i]->setVisible(true);

        }else{
            recentFileActions[i]->setVisible(false);
        }

    }
    separatorAction->setVisible(!recentFiles.isEmpty());
}

void MainWindow::openRecentFile(){
    if(okToContinue()){
        QAction *action = qobject_cast<QAction*>(sender());
        if(action){
            loadFile(action->data().toString());
        }
    }
}



void MainWindow::goToCell(){
    if(!goToCellDialog){
        goToCellDialog = new GoToCellDialog(this);
        connect(goToCellDialog, SIGNAL(goToCell(const QString&)), document, SLOT(goToCell(const QString&)));
    }
    if(goToCellDialog->isHidden()){
        goToCellDialog->show();
    }else{
        goToCellDialog->activateWindow();
    }
}

void MainWindow::closeEvent(QCloseEvent *event){
    if(okToContinue()){
        saveSettings();
        event->accept();
    }else{
        event->ignore();
    }

}

void MainWindow::saveSettings(){

   QSettings settings("Yurii Belikov", "Spreadsheet app");
   settings.setValue("Geometry", geometry());
   settings.setValue("Recent files", recentFiles);
   settings.setValue("Show grid", showGridAction->isChecked());
   settings.setValue("AutoRecalc", autoRecalculateAction->isChecked());

}

void MainWindow::readSettings(){

    QSettings settings("Yurii Belikov", "Spreadsheet app");
    QRect rect = settings.value("Geometry", QRect(200, 200, 400, 400)).toRect();
    move(rect.topLeft());
    resize(rect.size());
    recentFiles = settings.value("Recent files").toStringList();
    updateRecentFileActions();
    bool showGrid = settings.value("Show grid").toBool();
    showGridAction->setChecked(showGrid);
    bool autoRecalc = settings.value("AutoRecalc").toBool();
    autoRecalculateAction->setChecked(autoRecalc);

}


void MainWindow::search(){
    if(!searchDialog){
        searchDialog = new SearchDialog(this);
        connect(searchDialog, SIGNAL(searchNext(const QString&, Qt::CaseSesitivity)), document, SLOT(searchNext(const QString&, Qt::CaseSensitivity)));
        connect(searchDialog, SIGNAL(searchPrevious(const QString&, Qt::CaseSesitivity)), document, SLOT(searchPrevious(const QString&, Qt::CaseSensitivity)));
    }
    if(searchDialog->isHidden()){
        searchDialog->show();
    }else{
        searchDialog->activateWindow();
    }
}


void MainWindow::about(){
    QMessageBox::about(nullptr, "About Spreadsheet app", "Spreadsheet app v1.0\n Made in educative and having fun goal\n");
}

