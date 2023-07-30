#ifndef OPERATIONTHREAD_H
#define OPERATIONTHREAD_H
#include <KeyboardHook.h>
#include <KeyCapturer.h>
#include <QThread>
#include <QObject>

class OperationThread : public QThread
{
    Q_OBJECT
public:
    OperationThread();
    void setRuning(bool runing);
protected:
    void run();
private:
    bool runing;
};
#endif // OPERATIONTHREAD_H

