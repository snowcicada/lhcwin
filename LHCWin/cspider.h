#ifndef CSPIDER_H
#define CSPIDER_H

#include <QtCore>
#include <QtNetwork>

class CSpider : public QObject
{
    Q_OBJECT
public:
    explicit CSpider(QObject *parent = 0);
    ~CSpider();

    void spider(const QString &url);
    QString lastError();
    bool isTimeout();
    void closeReply();

signals:
    void signalFinished(bool ok, const QString &html, const QString &error);

private slots:
    void slotReadyWrite();
    void slotFinished();
    void slotError(QNetworkReply::NetworkError code);

private:
    //func
    void initVariable();

    //variable
    QNetworkAccessManager m_spider;
    QNetworkReply *m_pReply;
    QString m_strHtml;
    QString m_strLastError;
    uint m_iStartTime;
};

#endif // CSPIDER_H
