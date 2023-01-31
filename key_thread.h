#ifndef KEY_THREAD_H
#define KEY_THREAD_H

#include <QObject>
#include <QThread>
#include <QTime>
#include <QTimer>

class KEY_THREAD: public QThread
{
    Q_OBJECT
public:
    explicit KEY_THREAD(QObject *parent = 0);
    ~KEY_THREAD();

protected:
    //QThread的虚函数
    //线程处理函数
    //不能直接调用，通过start()间接调用
    void run();
private slots:
};

#endif // PUGIJSON_H