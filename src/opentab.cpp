#include "opentab.h"
#include <QUuid>

OpenTab::OpenTab() :
    m_widget(NULL),
    m_uuid(QUuid::createUuid().toString()),
    m_text(""),
    m_iconUrl("")
{

}

OpenTab::OpenTab(QWidget* view, const QString& uuid) :
    m_widget(view),
    m_uuid(uuid),
    m_text(""),
    m_iconUrl("")
{
}

OpenTab::OpenTab(const OpenTab &other) :
    m_widget(other.m_widget),
    m_uuid(other.m_uuid),
    m_text(other.m_text),
    m_iconUrl(other.m_iconUrl)
{
}
