#ifndef SDBUS_CONNECTION_H
#define SDBUS_CONNECTION_H

#include <unistd.h>
#include <QException>
#include <QObject>
#include <sdbusplus/bus.hpp>
#include <sdbusplus/sdbus.hpp>
#include "stacer-core_global.h"

#define CONTYPE_SYSTEM 0
#define CONTYPE_NONE   2
#define CONTYPE_USER 16
#define CONTYPE_SESSION 32
#define CONTYPE_DEFAULT 64


using SDBus = sdbusplus::bus::bus;

class STACERCORESHARED_EXPORT SDBusConnection : public QObject
{
    Q_OBJECT
public:
    explicit SDBusConnection(QObject *parent = nullptr);
    virtual ~SDBusConnection();

    const bool busAcquired() const;

    template <class R, typename T=typename R::result_type>
    void waitForAcquire(T wfaCallback, qint64 microseconds) const {
        waitForAcquire(microseconds);
        wfaCallback();
        
    }
    
protected:
    virtual void waitForAcquire(qint64 microseconds) const{
        while(!busAcquired()) {
            usleep(microseconds);
        }
    }
    
signals:
    void onAcquire();

public slots:
    virtual void acquireBus(const short BusType);
    virtual void waitForBus(const bool doAcquire=false, const short connType=CONTYPE_USER);
    
private:
    volatile bool  mAcquired;
    SDBus mDBUS;
};

#endif // SDBUS_CONNECTION_H
