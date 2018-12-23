#include <QCoreApplication>
#include <QProcess>
#include <QDebug>

#include "Generator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString filePath = QCoreApplication::applicationDirPath().append("/schema.json");

    Generator generator;

    generator.generate(filePath);
//    QString command = QString("python -c 'import sys, yaml, json; json.dump(yaml.load(sys.stdin), sys.stdout, indent=4)' < /Users/lunfir/junior/db1/generator/schema.yaml > /Users/lunfir/junior/db1/generator/schema.json");
//    QString command = QString("open %1.yaml").arg(file);

//    QProcess process;
//    process.start(command);
//    process.waitForFinished(-1);

    a.quit();
    return 0;
}
