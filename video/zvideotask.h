#ifndef ZVIDEOTASK_H
#define ZVIDEOTASK_H

#include <QObject>
#include <QPaintEvent>
#include <QImage>
#include <QtWidgets/QWidget>
#include <QLabel>
#include <QQueue>
#include <QByteArray>
#include <QSemaphore>
#include <QProgressBar>

#include <video/zimgcapthread.h>
#include <video/zimgdisplayer.h>
#include <video/zh264encthread.h>
#include <video/zvideotxthread.h>
#include <video/zvideotxthread_h264.h>
#include "zgblpara.h"
class ZVideoTask : public QObject
{
    Q_OBJECT
public:
    explicit ZVideoTask(QObject *parent = nullptr);
    ~ZVideoTask();
    qint32 ZDoInit();
    qint32 ZStartTask();

    bool ZIsExitCleanup();

    ZImgCapThread* ZGetImgCapThread(qint32 index);

signals:
    void ZSigVideoTaskExited();
private slots:
    void ZSlotSubThreadsFinished();
    void ZSlotChkAllExitFlags();
private:
    ZImgCapThread *m_capThread;//主摄像头
    ZHardEncTxThread *m_encTxThread;//main h264 encoder&tx thread.

private:
    //main capture to h264 encoder queue(fifo).
    QByteArray* m_Cap2EncFIFOMain[FIFO_DEPTH];
    QQueue<QByteArray*> m_Cap2EncFIFOFreeMain;
    QQueue<QByteArray*> m_Cap2EncFIFOUsedMain;
    QMutex m_Cap2EncFIFOMutexMain;
    QWaitCondition m_condCap2EncFIFOFullMain;
    QWaitCondition m_condCap2EncFIFOEmptyMain;
private:
    QTimer *m_timerExit;
};

#endif // ZVIDEOTASK_H
