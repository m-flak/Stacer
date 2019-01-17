#include "sdbus_connection.h"

SDBusConnection::SDBusConnection(QObject *parent) : QObject(parent),
    mDBUS([=] { return sdbusplus::bus::new_default(); }()),
    mAcquired(false)
{

}

SDBusConnection::~SDBusConnection()
{
    this->mDBUS.release();
}

const bool SDBusConnection::busAcquired() const
{
    return mAcquired;
}

void SDBusConnection::acquireBus(const short BusType)
{
    if (BusType == CONTYPE_SYSTEM)
    {
        mDBUS = sdbusplus::bus::new_system();
    }
    else if ((BusType & CONTYPE_USER) ||
                 (BusType & CONTYPE_SESSION))
    {
        mDBUS = sdbusplus::bus::new_user();
    }
    else if (BusType & CONTYPE_DEFAULT)
    {
        mDBUS = sdbusplus::bus::new_default();
    }
    else
    {
       throw QException();
    }
    
    mAcquired = true;
}

void SDBusConnection::waitForBus(const bool doAcquire, const short connType)
{
    if (doAcquire == true)
    {
        acquireBus(connType);
    }
    waitForAcquire<void*()>([this](){
        emit onAcquire();
            return;
    },
    200000);
}
