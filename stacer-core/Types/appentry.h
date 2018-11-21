#ifndef APPENTRY_H
#define APPENTRY_H

#include <QObject>
#include <QFile>
#include <QList>
#include <QTextStream>

#include "stacer-core_global.h"

class STACERCORESHARED_EXPORT AppEntry : public QObject
{
    Q_OBJECT
protected:
    explicit AppEntry(QObject *parent = nullptr);

    void handleLines(QTextStream& stream, bool* status_null);
    void findPrefix(const QString& location, QString *prefix);
public:
    AppEntry(const AppEntry& other);

    static AppEntry* loadFromDesktop(const QString &desktop_file);
    static qint64    loadAllDesktops(QList<AppEntry*>& list);

    QString pretty_name;
    QString name;
    QString install_prefix;

    bool operator ==(const AppEntry &B) const;
    bool operator ==(const AppEntry *B) const;
signals:

public slots:
    void init();
};


#endif // APPENTRY_H
