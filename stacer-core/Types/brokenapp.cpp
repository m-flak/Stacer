#include <exception>
#include "brokenapp.h"

BrokenApp::BrokenApp(AppEntry *app) :
    m_broken(false), m_ran(nullptr), m_entry(*app)
{

}

BrokenApp::~BrokenApp()
{

}

void BrokenApp::run()
{

    // done checking if broken
    // m_broken == whatever
    m_ran = &m_broken;
}

bool BrokenApp::isBroken() const
{
    if (m_ran == nullptr)
        throw std::exception();
    
    return m_broken;
}
