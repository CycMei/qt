#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QGridLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    isUntitled = true;
    curFile = QString::fromLocal8Bit("未命名.txt");
    setWindowTitle(curFile);

    findDlg = nullptr;


    auto iconName = [](const char *icoNa) ->QString{
        std::string icName(":/icon/");
        return QString((icName +=icoNa).c_str());
    };

    //创建文件菜单
    QString title = QString::fromLocal8Bit("文件(&F)");
    QMenu * menu_F = ui->menuBar->addMenu(title);
    //向文件菜单添加动作
        //新建文件动作
    title = QString::fromLocal8Bit("新建(N)");
    QIcon file_new_Ico(iconName("file_new"));
    QAction *newFileAct = new QAction(file_new_Ico, title, this);
    newFileAct->setShortcut(QKeySequence(tr("Ctrl+N")));
    menu_F->addAction(newFileAct);
    connect(newFileAct, SIGNAL(triggered()), this, SLOT(newFile()));
        //保存动作
    title = QString::fromLocal8Bit("保存(S)");
    QIcon file_save_Ico(iconName("file_save"));
    QAction *saveFileAct = new QAction(file_save_Ico, title, this);
    saveFileAct->setShortcut(QKeySequence(tr("Ctrl+S")));
    menu_F->addAction(saveFileAct);
    connect(saveFileAct, &QAction::triggered, this, &MainWindow::save);
        //另存为动作
    title = QString::fromLocal8Bit("另存为(&A)");
    QIcon file_saveAs_Ico(iconName("file_saveAs"));
    QAction *saveAsFileAct = new QAction(file_saveAs_Ico, title, this);
    saveAsFileAct->setShortcut(QKeySequence(tr("Ctrl+Shift+S")));
    menu_F->addAction(saveAsFileAct);
    connect(saveAsFileAct, SIGNAL(triggered()), this, SLOT(saveAs()));
        //打开文件动作
    title = QString::fromLocal8Bit("打开(&O)");
    QIcon file_open_Icon(iconName("file_open"));
    QAction *fileOpenAct = new QAction(file_open_Icon, title, this);
    fileOpenAct->setShortcut(QKeySequence(tr("Ctrl+O")));
    menu_F->addAction(fileOpenAct);
    connect(fileOpenAct, &QAction::triggered, this, &MainWindow::openFile);
        //分隔符
    QAction *fenGeFu = new QAction(this);
    menu_F->addAction(fenGeFu);

        //关闭
    title = QString::fromLocal8Bit("关闭(&C)");
    QIcon file_close_Icon(iconName("file_close"));
    QAction *fileCloseAct = new QAction(file_close_Icon, title, this);
    menu_F->addAction(fileCloseAct);
    connect(fileCloseAct, &QAction::triggered, this, &MainWindow::closeFile);

        //退出动作
    title = QString::fromLocal8Bit("退出(&X)");
    QIcon file_exit_Icon(iconName("file_exit"));
    QAction *exitFileAct = new QAction(file_exit_Icon, title, this);
    menu_F->addAction(exitFileAct);
    connect(exitFileAct, &QAction::triggered, this, &MainWindow::exitMain);


    //创建编辑菜单
    title = QString::fromLocal8Bit("编辑(&E)");
    QMenu * menu_E = ui->menuBar->addMenu(title);
        //添加撤销
    title = QString::fromLocal8Bit("撤销(&Z)");
    QIcon edit_chexiao_Icon(iconName("edit_cheXiao"));
    QAction *editCheXiaoAct = new QAction(edit_chexiao_Icon, title, this);
    editCheXiaoAct->setShortcut(QKeySequence(tr("Ctrl+Z")));
    menu_E->addAction(editCheXiaoAct);
    connect(editCheXiaoAct, &QAction::triggered, this, &MainWindow::cheXiao);
        //添加剪切
    title = QString::fromLocal8Bit("剪切(&X)");
    QIcon edit_jianqie_Icon(iconName("edit_jianQie"));
    QAction *editJianQieAct = new QAction(edit_jianqie_Icon, title, this);
    editJianQieAct->setShortcut(QKeySequence(tr("Ctrl+X")));
    menu_E->addAction(editJianQieAct);
    connect(editJianQieAct, &QAction::triggered, this, &MainWindow::jianQie);
        //添加复制
    title = QString::fromLocal8Bit("复制(&C)");
    QIcon edit_fuzhi_Icon(iconName("edit_fuZhi"));
    QAction *editFuZhiAct = new QAction(edit_fuzhi_Icon, title, this);
    editFuZhiAct->setShortcut(QKeySequence(tr("Ctrl+C")));
    menu_E->addAction(editFuZhiAct);
    connect(editFuZhiAct, &QAction::triggered, this, &MainWindow::fuZhi);
        //添加粘贴
    title = QString::fromLocal8Bit("粘贴(&C)");
    QIcon edit_zhantie_Icon(iconName("edit_zhanTie"));
    QAction *editZhanTieAct = new QAction(edit_zhantie_Icon, title, this);
    editZhanTieAct->setShortcut(QKeySequence(tr("Ctrl+V")));
    menu_E->addAction(editZhanTieAct);
    connect(editZhanTieAct, &QAction::triggered, this, &MainWindow::zhanTie);
        //添加查找
    title = QString::fromLocal8Bit("查找(&C)");
    QIcon edit_chazhao_Icon(iconName("edit_chaZhao"));
    QAction *editChaZhaoAct = new QAction(edit_chazhao_Icon, title, this);
    editChaZhaoAct->setShortcut(QKeySequence(tr("Ctrl+F")));
    menu_E->addAction(editChaZhaoAct);
    connect(editChaZhaoAct, &QAction::triggered, this, &MainWindow::chaZhao);




    //创建文本编辑区域
    textEdit = new QTextEdit(this);
    mouseEvtBtn = new QPushButton(this);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(textEdit, 0, 0, 1, 3);
    layout->addWidget(mouseEvtBtn, 1, 0, 1, 1);
    ui->centralWidget->setLayout(layout);

    //定时器
    id1 = startTimer(1000);
    id2 = startTimer(2000);
    id3 = startTimer(10000);
    labId1 = new QLabel(this);
    labId2 = new QLabel(this);
    layout->addWidget(labId1, 2, 0, 1, 1);
    layout->addWidget(labId2, 3, 0, 1, 1);



    //临时信息
    ui->statusBar->showMessage(QString::fromLocal8Bit("欢迎！"), 2000);

    //一般信息
    statusLabel = new QLabel;
    statusLabel->setMinimumSize(150, 20);
    statusLabel->setFrameShape(QFrame::WinPanel);
    statusLabel->setFrameShadow(QFrame::Sunken);
    statusLabel->setText(QString::fromLocal8Bit("欢迎！"));
    ui->statusBar->addWidget(statusLabel);

    //永久信息
    permanent = new QLabel;
    permanent->setFrameStyle(QFrame::Box | QFrame::Sunken);
    permanent->setText(tr("<a href=\"http://www.baidu.com\">baidu</a>"));
    permanent->setTextFormat(Qt::RichText);
    permanent->setOpenExternalLinks(true);
    ui->statusBar->addPermanentWidget(permanent);



}


bool MainWindow::maybeSave() {
    if (textEdit->document()->isModified()){
        QMessageBox box;
        box.setWindowTitle(QString::fromLocal8Bit("警告"));
        box.setIcon(QMessageBox::Warning);
        box.setText(curFile + QString::fromLocal8Bit("尚未保存，是否保存"));
        QPushButton *yesBtn = box.addButton(QString::fromLocal8Bit("是(&Y)"),
                                            QMessageBox::YesRole);
        box.addButton(QString::fromLocal8Bit("否(&N)"), QMessageBox::NoRole);
        QPushButton *cancelBtn = box.addButton(QString::fromLocal8Bit("取消"),
                                               QMessageBox::RejectRole);
        box.exec();
        if (box.clickedButton() == yesBtn){
            return save();
        }
        else if (box.clickedButton() == cancelBtn){
            return false;
        }

    }
    return true;
}

void MainWindow::newFile() {
    if (maybeSave()){
        isUntitled = true;
        curFile = QString::fromLocal8Bit("未命名.txt");
        setWindowTitle(curFile);
        textEdit->clear();
        textEdit->setVisible(true);
    }
}

bool MainWindow::save() {
    if (isUntitled){
        return saveAs();
    }
    else{
        return saveFile(curFile);
    }
}


bool MainWindow::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    QString::fromLocal8Bit("另存为"),
                                                    curFile);
    if (fileName.isEmpty()){
        return false;
    }
    return saveFile(fileName);
}

bool MainWindow::saveFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,
                             QString::fromLocal8Bit("多文档编辑器"),
                             QString::fromLocal8Bit("无法写入文件 %1: /n %2")
                             .arg(filePath).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << textEdit->toPlainText();
    QApplication::restoreOverrideCursor();
    textEdit->document()->setModified(false);

    isUntitled = false;
    curFile = QFileInfo(filePath).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}

void MainWindow::openFile() {
    if (maybeSave()){
        QString fileName = QFileDialog::getOpenFileName(this/*,
                                                        QString::fromLocal8Bit("打开文件"),
                                                        curFile*/);
        if (!fileName.isEmpty()){
            textEdit->setVisible(true);
            loadFile(fileName);
        }
    }


}

bool MainWindow::loadFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,
                             QString::fromLocal8Bit("多文档编辑器"),
                             QString::fromLocal8Bit("无法打开文件 %1: /n %2")
                             .arg(filePath).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();
    curFile = QFileInfo(filePath).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}


bool MainWindow::closeFile() {
    if (maybeSave()){
        textEdit->setVisible(false);
        textEdit->clear();
        return true;
    }
    return false;
}

void MainWindow::exitMain() {
    if (closeFile()) {
        qApp->quit();
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    exitMain();
}



void MainWindow::cheXiao(){
    textEdit->undo();
}

void MainWindow::jianQie() {
    textEdit->cut();
}

void MainWindow::fuZhi() {
    textEdit->copy();
}

void MainWindow::zhanTie() {
    textEdit->paste();
}


void MainWindow::chaZhao() {
    if (!findDlg){
        findDlg = new FindDialog(this);
    }
    findDlg->show();
}

void MainWindow::showFindText()
{
    const QString str = findDlg->getLineEditText();
    const bool find = textEdit->find(str, QTextDocument::FindBackward);
    if (!find){
        QMessageBox::warning(this, QString::fromLocal8Bit("查找"),
                             QString::fromLocal8Bit("找不到%1").arg(str));
    }


}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    mouseEvtBtn->setText(tr("(%1, %2)").arg(event->x()).arg(event->y()));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    const unsigned int x = mouseEvtBtn->x();
    const unsigned int y = mouseEvtBtn->y();
    switch (event->key()) {
    case Qt::Key_W:
        mouseEvtBtn->move(x, y - 10);
        break;
    case Qt::Key_S:
        mouseEvtBtn->move(x, y + 10);
        break;
    case Qt::Key_A:
        mouseEvtBtn->move(x - 10, y);
        break;
    case Qt::Key_D:
        mouseEvtBtn->move(x+ 10, y);
        break;
    default:
        break;
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == id1){
        labId1->setText(tr("%1").arg(qrand() % 10));
    }
    else if (event->timerId() == id2){
        labId2->setText(tr("hello world!"));
    }
    else{
        qApp->quit();
    }
}


MainWindow::~MainWindow()
{
    DELETE_PTR(textEdit);
    DELETE_PTR(findDlg);
    DELETE_PTR(statusLabel);
    DELETE_PTR(permanent);

    delete ui;
}
