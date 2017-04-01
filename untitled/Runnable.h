#ifndef RUNNABLE_H
#define RUNNABLE_H

class Runnable {
    int ref;

    friend class ThreadPool;
    friend class ThreadPoolPrivate;
    friend class ThreadPoolThread;

public:
    virtual void run() = 0;

    Runnable()
        : ref(0)
    {
    }
    virtual ~Runnable();

    bool autoDelete() const { return ref != -1; }
    void setAutoDelete(bool _autoDelete) { ref = _autoDelete ? 0 : -1; }
};

#endif // RUNNABLE_H
