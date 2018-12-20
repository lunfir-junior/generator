#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
//#include "Generator.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
//  Generator generator;
  QString file = QCoreApplication::applicationDirPath().append("/schema.yaml");
  QString command = QString("open ").append(file);
//  QStringList statements = generator.generate(file);

//  foreach( auto i, statements )
   qDebug().noquote() << "here";

   QProcess process;
   process.start(command);
   process.waitForFinished(-1);

  a.quit();
   return 0;
}
