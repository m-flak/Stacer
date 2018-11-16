#include <pcrecpp.h>
#include <QString>
#include <QStringList>
#include "appentry.h"
#include "file_util.h"

AppEntry::AppEntry(QObject *parent) : QObject(parent)
{
   this->pretty_name 	= "";
   this->name	 	= "";
   this->install_prefix = "";
}

AppEntry::AppEntry(const AppEntry& other) : QObject(other.parent())
{
   this->pretty_name 	= other.pretty_name; 
   this->name	 	= other.name;
   this->install_prefix = other.install_prefix;
}

bool AppEntry::operator ==(const AppEntry &B) const
{
    bool a = (this->pretty_name == B.pretty_name);
    bool b = (this->name == B.name);
    bool c = (this->install_prefix == B.install_prefix);
    
    return (a & b & c);
}

bool AppEntry::operator ==(const AppEntry *B) const
{
    bool a = (this->pretty_name == B->pretty_name); 
    bool b = (this->name == B->name);
    bool c = (this->install_prefix == B->install_prefix);
    
    return (a & b & c);
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
    ape.handleLines(dqts, &ns);            //parse desktop file
    QString prefix(desktop_file);
    ape.findPrefix(desktop_file, &prefix); //get prefix from the path
    
    delete dqfile;
    return new AppEntry(ape);
}

qint64 AppEntry::loadAllDesktops(QList<AppEntry*>& list)
{
    qint64            totales  = 0;
    const QStringList allofdem = FileUtil::getDesktopFiles(&totales,true);
    
    qint64 i = 0;
    try
    {
        for (const auto& a = allofdem[i]; i<totales; i++)
        {
            list.append(AppEntry::loadFromDesktop(a));
        }
    }
    catch (...)
    {
        return i;
    }
    
    return totales;
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

void AppEntry::findPrefix(const QString& location, QString *prefix)
{
    int share_index = location.indexOf("share", 0, Qt::CaseInsensitive);
    int diff		= location.size()-share_index;
    
    prefix->chop(diff);
    
    this->install_prefix = *prefix;
}
