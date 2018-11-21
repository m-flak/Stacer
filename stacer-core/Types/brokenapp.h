#ifndef _BROKENAPP_H_
#define _BROKENAPP_H_

#include <QRunnable>
#include "appentry.h"

#include "stacer-core_global.h"

class STACERCORESHARED_EXPORT BrokenApp : public QRunnable
{
public:
     explicit BrokenApp(AppEntry *app);
     virtual  ~BrokenApp();

     virtual void run();

     bool isBroken() const;
private:
     bool   m_broken;
     bool   *m_ran;
     const AppEntry m_entry;
};

#endif
