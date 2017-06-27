#include "cspider.h"

CSpider::CSpider(QObject *parent) :
    QObject(parent)
{
    initVariable();
}

CSpider::~CSpider()
{
    if (m_pReply) {
        m_pReply->deleteLater();
        m_pReply = NULL;
    }
}

void CSpider::spider(const QString &url)
{
    //保存开始时间
    m_iStartTime = QDateTime::currentDateTime().toTime_t();
    m_strHtml.clear();
    m_strLastError.clear();
    m_pReply = m_spider.get(QNetworkRequest(QUrl(url)));
    connect(m_pReply, SIGNAL(readyRead()), this, SLOT(slotReadyWrite()));
    connect(m_pReply, SIGNAL(finished()), this, SLOT(slotFinished()));
//    connect(m_pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
}

QString CSpider::lastError()
{
    return m_strLastError;
}

bool CSpider::isTimeout()
{
    //超时时间20秒
    if (QDateTime::currentDateTime().toTime_t() - m_iStartTime >= 20) {
        return true;
    }
    return false;
}

void CSpider::closeReply()
{
    if (m_pReply) {
        m_pReply->close();
        m_pReply->deleteLater();
        m_pReply = NULL;
    }
}

void CSpider::initVariable()
{
    m_pReply = NULL;
    m_iStartTime = 0;
}

void CSpider::slotReadyWrite()
{
    m_strHtml.append(m_pReply->readAll());
}

void CSpider::slotFinished()
{
    bool ok = false;
    if (m_pReply->error() != QNetworkReply::NoError) {
        m_strLastError = m_pReply->errorString();
        m_strHtml.clear();
        ok = false;
    } else {
        ok = true;
    }

    //通知
    emit signalFinished(ok, m_strHtml, m_strLastError);

    //delete
    m_pReply->deleteLater();
    m_pReply = NULL;
//    qDebug() << "slotFinished";
}

void CSpider::slotError(QNetworkReply::NetworkError code)
{
    qDebug() << "slotError: " << m_pReply->errorString();
}
