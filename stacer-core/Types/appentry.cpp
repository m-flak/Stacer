#include <pcrecpp.h>
#include <QString>
#include "appentry.h"

AppEntry::AppEntry(QObject *parent) : QObject(parent)
{
   this->pretty_name 	= "";
   this->name	 	= "";
}

AppEntry::AppEntry(const AppEntry& other) : QObject(other.parent())
{
   this->pretty_name 	= other.pretty_name; 
   this->name	 	= other.name;
}

AppEntry* AppEntry::loadFromDesktop(const QString &desktop_file)
{
    AppEntry ape;
    bool          ns = false;
    QFile    *dqfile = nullptr;

    if (!QFile::exists(desktop_file))
        return nullptr;

    dqfile = new QFile(desktop_file);
    dqfile->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream dqts(dqfile);
    ape.handleLines(dqts, &ns);

    delete dqfile;
    return new AppEntry(ape);
}

void AppEntry::handleLines(QTextStream& stream, bool* status_null)
{
    QString  cur_line   = stream.readLine();
    std::string buffer;
    *status_null	= cur_line.isNull();

    if (*status_null != false)
        return;

    if (this->pretty_name.isEmpty())
    {
        using namespace pcrecpp;
        RE name_re("^Name=(.*)");
        name_re.FullMatch(cur_line.toStdString(), &buffer);
        pretty_name = QString::fromStdString(buffer);
    }
    else if (this->name.isEmpty())
    {
        using namespace pcrecpp;
        RE exec_re("^Exec=(\\w*)\\s?");
        exec_re.FullMatch(cur_line.toStdString(), &buffer);
        name = QString::fromStdString(buffer);
    }

    handleLines(stream, status_null);
}

