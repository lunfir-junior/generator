#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMap>
#include <QMapIterator>
#include <QDebug>

class Generator : public QObject
{
    Q_OBJECT
public:
    explicit Generator(QObject *parent = nullptr);
    virtual ~Generator();

    QStringList generate(QString inPath);

private:
    static QString table;
    static QString timestamp;
    static QString procedure;
    static QString trigger;

    QString read(QString inPath);
    QMap< QString, QMap<QString, QStringList> > parse(QString inStr);
    QStringList toStringList(QMap<QString, QVariant> inMap);

    QString addTimestamp(QString inTable, QString inColumn);
    QString addFunction(QString inTable);
    QString addTrigger(QString inTable);

signals:

public slots:
};

#endif // GENERATOR_H
