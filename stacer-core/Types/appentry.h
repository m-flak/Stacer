#ifndef APPENTRY_H
#define APPENTRY_H

#include <QObject>
#include <QFile>
#include <QTextStream>

#include "stacer-core_global.h"

class STACERCORESHARED_EXPORT AppEntry : public QObject
{
    Q_OBJECT
protected:
    explicit AppEntry(QObject *parent = nullptr);

    void handleLines(QTextStream& stream, bool* status_null);
public:
    AppEntry(const AppEntry& other);

    static AppEntry* loadFromDesktop(const QString &desktop_file);

    QString pretty_name;
    QString name;

signals:

public slots:
};

#endif // APPENTRY_H
