#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QAudio>
#include <QSound>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void playSound();
    void setLoopBar();
    void resetTempo();

signals:
   void imReady();

public slots:
    void getTempo();
    void theEnd();
    void soundStart();
    //    void updateTimer();

private:
    Ui::MainWindow *ui;

    short m_DefaultTempo;
    short m_LoopBar;
    short m_LoopNum;
    short m_RiseTempo;
    short m_LimitTempo;
    short m_NowTempo;

    QTimer *m_Timer;

    char m_LoopBarCount;
    char m_LoopNumCount;

    QSound *m_First;
    QSound *m_other;
    QSound *m_Change;

};

#endif // MAINWINDOW_H
