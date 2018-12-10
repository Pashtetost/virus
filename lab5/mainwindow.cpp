#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    namefolder = QFileDialog::getExistingDirectory(0, "Выбор директории", "");
    ui->lineEdit->setText(namefolder);

}

void MainWindow::on_pushButton_2_clicked()
{
     QFileInfo info;
    if (namefolder.isEmpty())
    {
        return;
    }
    QDir dir(namefolder);
    QStringList listNameFile = dir.entryList(  QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);
    for(int i = 0; i < listNameFile.length(); i++)
    {
     info.setFile(namefolder+ "/" + listNameFile.at(i));
     qDebug()<<listNameFile.at(i);
     qDebug()<<info.isFile();
     if(info.isSymLink())
     {
         QString nameExe=info.symLinkTarget();
         qDebug()<<nameExe;
         QFileInfo exe(nameExe);
         if (exe.isExecutable() && exe.isHidden())
         {
             QString nameTxt=exe.path() + "/" + exe.completeBaseName() + ".txt";
             QFileInfo txt(nameTxt);
             if(txt.exists()&&txt.isHidden())
             {
                 SetFileAttributes((LPCTSTR)((nameTxt).utf16()), FILE_ATTRIBUTE_NORMAL);
                 QFile(nameExe).remove();
                 QFile(info.absoluteFilePath()).remove();
             }
         }
     }
    }
    dir.refresh();
    listNameFile = dir.entryList(  QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);
    for(int i = 0; i < listNameFile.length(); i++)
    {
        info.setFile(namefolder+ "/" + listNameFile.at(i));
     if (info.isExecutable() && info.isHidden())
     {
         QString nameTxt=info.path() + "/" + info.completeBaseName() + ".txt";
         QFileInfo txt(nameTxt);
         if(txt.exists()&&txt.isHidden())
         {
             SetFileAttributes((LPCTSTR)((nameTxt).utf16()), FILE_ATTRIBUTE_NORMAL);
             QFile(info.absoluteFilePath()).remove();
         }
     }
    }
}
