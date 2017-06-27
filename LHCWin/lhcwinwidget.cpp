#include "lhcwinwidget.h"
#include "ui_lhcwinwidget.h"
#include <cshengxiao.h>

QString LHCWinWidget::m_strWinResultUrl = "http://www.77190.com/wz/scores1.xml";
QString LHCWinWidget::m_strWinDateUrl = "http://www.64562.com/kj/xqkj.html";

LHCWinWidget::LHCWinWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LHCWinWidget)
{
    ui->setupUi(this);

    initVariable();
    initSetupUi();

    //�״θ���
    m_spiderWinResult.spider(m_strWinResultUrl);
    m_spiderWinDate.spider(m_strWinDateUrl);
}

LHCWinWidget::~LHCWinWidget()
{
    if (m_pMediaObject) {
        delete m_pMediaObject;
        m_pMediaObject = NULL;
    }
    if (m_pAudioOutput) {
        delete m_pAudioOutput;
        m_pAudioOutput = NULL;
    }

    if (m_pMovie1) {
        delete m_pMovie1;
        m_pMovie1 = NULL;
    }
    if (m_pMovie2) {
        delete m_pMovie2;
        m_pMovie2 = NULL;
    }

    delete ui;
}

void LHCWinWidget::slotWinResultFinished(bool ok, const QString &html, const QString &error)
{
    if (ok) {
        ui->labelWinResultState->setText(tr("״̬�����³ɹ�(%1)").arg(m_iWinResultTimes++));

        //����xml
        parseXml(html);

        //to ui
    //    QFile file("c:/lhc.htm");
    //    if (!file.open(QIODevice::Text | QIODevice::Append)) {
    //        return;
    //    }
    //    QString strCurTime = QDateTime::currentDateTime().toString("=>yyyy-MM-dd hh:mm:ss");
    //    strCurTime += "\n" + m_strHtml;
    //    file.write(strCurTime.toAscii().data());
    //    file.close();
    } else {
        ui->labelWinResultState->setText(tr("״̬������ʧ��(%1)��%2").arg(m_iWinResultTimes++).arg(error));
    }
    m_bWinResultFinished = true;
}

void LHCWinWidget::slotWinDateFinished(bool ok, const QString &html, const QString &error)
{
    if (ok) {
        ui->labelWinDateState->setText(tr("״̬�����³ɹ�(%1)").arg(m_iWinDateTimes++));
        QRegExp regExp("<table[\\s\\S]*���ڔ�������[\\s\\S]*��������.*content\">(.*)/(.*)/(.*) \\((.*)\\)</td>");
        regExp.setMinimal(true);
        if (regExp.indexIn(html) != -1) {
            if (regExp.captureCount() == 4) {
/*
1   "10"
2   "11"
3   "2013"
4   "������"
*/
                QString strYear = regExp.cap(3);
                QString strMonth = regExp.cap(2);
                QString strDay = regExp.cap(1);
                QString strWeek = regExp.cap(4);
                ui->labelWinDate->setText(tr("��������:%1��%2��%3�� %4").
                                          arg(strYear).
                                          arg(strMonth).
                                          arg(strDay).
                                          arg(strWeek));
                //���濪������
                m_winDate.setDate(strYear.toInt(), strMonth.toInt(), strDay.toInt());
            }
        }

    } else {
        ui->labelWinDateState->setText(tr("״̬������ʧ��(%1)��%2").arg(m_iWinDateTimes++).arg(error));
    }
    m_bWinDateFinished = true;
}

//���������ʱ��
void LHCWinWidget::slotWinReusltTimeout()
{
    //����ץȡƵ��
    QTime tm = QDateTime::currentDateTime().time();
    int sec;
    if (tm.hour() == 21
            && tm.minute() >= 20
            && tm.minute() <= 50) {
        sec = 7*1000;
    } else {
        sec = 30*1000;
    }
    if (m_updateWinResultTimer.interval() != sec) {
        m_updateWinResultTimer.setInterval(sec);
    }

    //ץȡ��ҳ
    if (m_bWinResultFinished) {
        m_bWinResultFinished = false;
        m_spiderWinResult.spider(m_strWinResultUrl);
    } else {
        //�����ʱ��,�Ǿ͹ر�֮ǰ������,�����ύ
        if (m_spiderWinResult.isTimeout()) {
            m_spiderWinResult.closeReply();
            m_bWinResultFinished = false;
            m_spiderWinResult.spider(m_strWinResultUrl);
        }
    }
}

//�������ڶ�ʱ��
void LHCWinWidget::slotWinDateTimeout()
{
    if (m_bWinDateFinished) {
        m_bWinDateFinished = false;
        m_spiderWinDate.spider(m_strWinDateUrl);
    } else {
        //�����ʱ��,�Ǿ͹ر�֮ǰ������,�����ύ
        if (m_spiderWinDate.isTimeout()) {
            m_spiderWinDate.closeReply();
            m_bWinDateFinished = false;
            m_spiderWinDate.spider(m_strWinDateUrl);
        }
    }
}

//�������ֵĶ�ʱ��
void LHCWinWidget::slotPlayMusicTimeout()
{
    QDateTime dt = QDateTime::currentDateTime();
    QTime tm = dt.time();

    //21:30
    if (tm.hour() == 21
            && tm.minute() >= 30
            && tm.minute() <= 40
            && m_winDate == dt.date()) {
        if (!isPlayMusic()) {
            playNotifyMusic(qApp->applicationDirPath() + "/notify.mp3");
        }
        activateWindow();
        showNormal();
    }
}

void LHCWinWidget::initVariable()
{
    m_pMediaObject = NULL;
    m_pAudioOutput = NULL;
    m_pMovie1 = NULL;
    m_pMovie2 = NULL;
    m_iWinResultTimes = 1;
    m_iWinDateTimes = 1;
    m_bWinResultFinished = true;
    m_bWinDateFinished = true;

    //֩���źŲ�
    connect(&m_spiderWinResult, SIGNAL(signalFinished(bool,QString,QString)),
            this, SLOT(slotWinResultFinished(bool,QString,QString)));
    connect(&m_spiderWinDate, SIGNAL(signalFinished(bool,QString,QString)),
            this, SLOT(slotWinDateFinished(bool,QString,QString)));

    //��������
    connect(&m_updateWinResultTimer, SIGNAL(timeout()), this, SLOT(slotWinReusltTimeout()));
    m_updateWinResultTimer.start(7 * 1000);//7sec

    connect(&m_updateWinDateTimer, SIGNAL(timeout()), this, SLOT(slotWinDateTimeout()));
    m_updateWinDateTimer.start(60 * 1000);//1min

    connect(&m_playMusicTimer, SIGNAL(timeout()), this, SLOT(slotPlayMusicTimeout()));
    m_playMusicTimer.start(10 * 1000);//10���ж�һ��
}

void LHCWinWidget::initSetupUi()
{
    //���ô�������
    setFixedSize(800, 380);
    setWindowIcon(QIcon(":/images/logo.ico"));

    //��ӳ��̬ͼƬ
    m_pMovie1 = new QMovie(":/images/pic2.gif");
    m_pMovie2 = new QMovie(":/images/pic3.gif");
    ui->labelGif1->setMovie(m_pMovie1);
    ui->labelGif2->setMovie(m_pMovie2);
    m_pMovie1->start();
    m_pMovie2->start();

    //��������
    setPowerBoot(true);
}

void LHCWinWidget::setPowerBoot(bool ok)
{
    QSettings reg("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);

    if (ok) {
        reg.setValue("lhcwin", QDir::toNativeSeparators(qApp->applicationFilePath()));
    }
    else {
        reg.setValue("lhcwin", "");
    }
}

void LHCWinWidget::parseXml(const QString &xml)
{
    QDomDocument doc;
    //��ʼ��dom�ĵ�

    doc.setContent(xml);
    QDomNodeList nodeList = doc.elementsByTagName("scores");
    if (nodeList.isEmpty()) {
        return;
    }

    /*��ʼ����,���ܳ��ֵ������
<scores>131,9:32�ֿ�����ף����н���</scores>
<scores>131,�V����...֮�����ϲ� </scores>
<scores>131,��Ͷע��5715��Ԫ�۱�!</scores>
<scores>131,32</scores>
<scores>131,32 13</scores>
<scores>131,32 13 35</scores>
<scores>131,32 13 35 39</scores>
<scores>131,32 13 35 39 42</scores>
<scores>131,32 13 35 39 42 31</scores>
<scores>131,32 13 35 39 42 31 T</scores>
<scores>131,32 13 35 39 42 31 T 16</scores>
    */
    QString strResult = nodeList.item(0).toElement().text();

    //ȥ������Ŀո�
    strResult = strResult.simplified();

    //��������������
    //"130,09 04 14 26 30 42 T 21"
    QStringList strList1 = strResult.split(',');
    if (strList1.size() == 2) {
        ui->labelSeqNum->setText(tr("��%1��").arg(strList1.at(0)));
        QString strCodeResult = strList1.at(1);
        strCodeResult = strCodeResult.simplified();

        //��������ĺ���
        QStringList strList2 = strList1.at(1).split(' ');
        CShengXiao sx;
        if (strList2.contains("T")) {
            //��ʾ��ui
            QStringList strCodeList = strCodeResult.split(' ');
            QString strResult;
            strCodeList.removeAll("T");

            for (int i = 0; i < strCodeList.size()-1; i++) {
                strResult.append(strCodeList.at(i));
                strResult.append(' ');
            }

            //�����붼������ʱ��,����ʾ��������,��ʾͼƬ
            if (strCodeList.size() == 7) {
                int iTeMa = strCodeList.last().toInt();

                //��������
                strResult.append(tr("��%1��").arg(strCodeList.last()));

                //����ͼƬ
                int seq = sx.getSxSeqForAge(iTeMa);
                ui->labelAnimal->setPixmap(QPixmap(tr(":/images/sx/sx%1.jpg").arg(seq)));

                //������ɫ
                Qt::GlobalColor color = sx.getSxColor(iTeMa);
                if (color == Qt::red) {
                    ui->labelResult->setStyleSheet("QLabel {color:red;font-weight:bolder;}");
                } else if (color == Qt::blue) {
                    ui->labelResult->setStyleSheet("QLabel {color:blue;font-weight:bolder;}");
                } else if (color == Qt::green) {
                    ui->labelResult->setStyleSheet("QLabel {color:green;font-weight:bolder;}");
                }
            }
            ui->labelResult->setText(strResult);
        } else {
            ui->labelResult->setText(strCodeResult);
            ui->labelResult->setStyleSheet("QLabel {color:black;font-weight:bolder;}");
            ui->labelAnimal->clear();
        }

        //��¼�������
        int row = ui->listRecord->count();
        if (row >= 1) {
            if (strCodeResult != ui->listRecord->item(row-1)->text()) {
                ui->listRecord->insertItem(row, strCodeResult);
            }
        } else {
            ui->listRecord->insertItem(0, strCodeResult);
        }
        ui->listRecord->scrollToBottom();


    }
}

void LHCWinWidget::playNotifyMusic(const QString &music)
{
    QString strMusic(music);
    if (!QFile::exists(strMusic)) {
        return;
    }

    if (!m_pMediaObject) {
        m_pMediaObject = new Phonon::MediaObject(this);
    }
    if (!m_pAudioOutput) {
        m_pAudioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
        Phonon::createPath(m_pMediaObject, m_pAudioOutput);
    }
    Phonon::MediaSource mediaSource(strMusic);
    m_pMediaObject->setCurrentSource(mediaSource);
    m_pMediaObject->stop();
    m_pMediaObject->seek(0);
    m_pMediaObject->play();
}

bool LHCWinWidget::isPlayMusic()
{
    if (m_pMediaObject) {
        Phonon::State st = m_pMediaObject->state();
        if (Phonon::LoadingState == st
                || Phonon::PlayingState == st
                || Phonon::BufferingState == st) {
            return true;
        }
    }
    return false;
}
