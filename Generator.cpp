#include "Generator.h"

QString Generator::table = QString("CREATE TABLE %1 ( %2 );");
QString Generator::timestamp = QString("ALTER TABLE %1 ADD COLUMN %1_%2 TIMESTAMP DEFAULT NOW();");
QString Generator::procedure = QString("CREATE OR REPLACE FUNCTION update()\nRETURNS TRIGGER AS $$\n BEGIN\n NEW.%1_updated = NOW();\n RETURN NEW;\n END;\n$$ language 'plpgsql';");
QString Generator::trigger = QString("CREATE TRIGGER update_%1_updated BEFORE UPDATE ON %1 FOR EACH ROW EXECUTE PROCEDURE update();\n");

Generator::Generator(QObject *parent) : QObject(parent)
{
    qDebug() << __PRETTY_FUNCTION__;
}

Generator::~Generator()
{
    qDebug() <<__PRETTY_FUNCTION__;
}

QStringList Generator::generate(QString inPath)
{
    QStringList out;
    QMap<QString, QMap<QString, QStringList> > schema = parse(read(inPath));
    qDebug().noquote() << schema;

//    for ( int i = 1; i < len; i += 2 ) {
//    QString prefix = schema.at(i-1);
//    out.append(table.arg(prefix, schema.at(i)));
//    out.append(addTimestamp(prefix, "created"));
//    out.append(addTimestamp(prefix, "updated"));
//    out.append(addFunction(prefix));
//    out.append(addTrigger(prefix));

    return out;
}

QString Generator::read(QString inPath)
{
    QFile file;
    QString out;

    file.setFileName(inPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    out = file.readAll();

    file.close();

    return out;
}

QMap<QString, QMap<QString, QStringList> > Generator::parse(QString inStr)
{
    QMap<QString, QMap<QString, QStringList> > out;

    QJsonDocument document = QJsonDocument::fromJson(inStr.toUtf8());
    QJsonObject object = document.object();
    QVariantMap map = object.toVariantMap();

    foreach (const QString& category, map.keys()) {
        QMap<QString, QStringList> nested;
        QMap<QString, QVariant> description = map.value(category).toMap();
        QMap<QString, QVariant> fields = description.value("fields").toMap();
        QMap<QString, QVariant> relations = description.value("relations").toMap();

        nested.insert("fields", toStringList(fields));
        nested.insert("relations", toStringList(relations));

        out.insert(category, nested);
    }

    return out;
}

QStringList Generator::toStringList(QMap<QString, QVariant> inMap)
{
    QStringList out;

    foreach(const QString& str, inMap.keys()) {
        out.append(str);
        out.append(inMap.value(str).toString());
    }

    return out;
}

QString Generator::addTimestamp(QString inTable, QString inColumn)
{
  return timestamp.arg(inTable, inColumn);
}

QString Generator::addFunction(QString inTable)
{
  return procedure.arg(inTable);
}

QString Generator::addTrigger(QString inTable)
{
  return trigger.arg(inTable);
}
