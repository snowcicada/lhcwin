#ifndef LHCWINWIDGET_H
#define LHCWINWIDGET_H

#include <QtCore>
#include <QtGui>
#include <QtNetwork>
#include <phonon>
#include <QtXml>
#include <cspider.h>

namespace Ui {
class LHCWinWidget;
}

class LHCWinWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit LHCWinWidget(QWidget *parent = 0);
    ~LHCWinWidget();
    
private slots:
    //�������
    void slotWinResultFinished(bool ok, const QString &html, const QString &error);
    //��������
    void slotWinDateFinished(bool ok, const QString &html, const QString &error);

    //���������ʱ��
    void slotWinReusltTimeout();
    //�������ڶ�ʱ��
    void slotWinDateTimeout();
    //�������ֵĶ�ʱ��
    void slotPlayMusicTimeout();

private:
    //func
    void initVariable();
    void initSetupUi();
    void setPowerBoot(bool ok);
    void parseXml(const QString &xml);
    void playNotifyMusic(const QString &music);
    bool isPlayMusic();

    //variable
    Ui::LHCWinWidget *ui;

    //֩��
    CSpider m_spiderWinResult;
    CSpider m_spiderWinDate;
    //����
    Phonon::MediaObject *m_pMediaObject;
    Phonon::AudioOutput *m_pAudioOutput;
    //����
    QMovie *m_pMovie1;
    QMovie *m_pMovie2;
    //��ʱ��
    QTimer m_updateWinResultTimer;
    QTimer m_updateWinDateTimer;
    QTimer m_playMusicTimer;//�������ֵĶ�ʱ��
    //����
    int m_iWinResultTimes;//����������´���
    int m_iWinDateTimes;//�������ڸ��´���
    //�����־
    bool m_bWinResultFinished;
    bool m_bWinDateFinished;
    //���濪������
    QDate m_winDate;

    //��ַ
    static QString m_strWinResultUrl;//��������
    static QString m_strWinDateUrl;//��������
};

#endif // LHCWINWIDGET_H
