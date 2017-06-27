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
    //开奖结果
    void slotWinResultFinished(bool ok, const QString &html, const QString &error);
    //开奖日期
    void slotWinDateFinished(bool ok, const QString &html, const QString &error);

    //开奖结果定时器
    void slotWinReusltTimeout();
    //开奖日期定时器
    void slotWinDateTimeout();
    //播放音乐的定时器
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

    //蜘蛛
    CSpider m_spiderWinResult;
    CSpider m_spiderWinDate;
    //音乐
    Phonon::MediaObject *m_pMediaObject;
    Phonon::AudioOutput *m_pAudioOutput;
    //界面
    QMovie *m_pMovie1;
    QMovie *m_pMovie2;
    //定时器
    QTimer m_updateWinResultTimer;
    QTimer m_updateWinDateTimer;
    QTimer m_playMusicTimer;//播放音乐的定时器
    //次数
    int m_iWinResultTimes;//开奖结果更新次数
    int m_iWinDateTimes;//开奖日期更新次数
    //处理标志
    bool m_bWinResultFinished;
    bool m_bWinDateFinished;
    //保存开奖日期
    QDate m_winDate;

    //网址
    static QString m_strWinResultUrl;//开奖数据
    static QString m_strWinDateUrl;//开奖日期
};

#endif // LHCWINWIDGET_H
