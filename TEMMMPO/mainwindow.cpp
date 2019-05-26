#include "mainwindow.h"
#include "ui_mainwindow.h"

#define MINUTE 60*1000

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_Timer = new QTimer();
    m_Timer->setSingleShot(false);

    //ボタンの準備
    connect(ui->pushButton, SIGNAL( clicked() ),this, SLOT( getTempo() ) );
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(theEnd()));

    //定期的に音を鳴らす。
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(soundStart()));

    //音の準備
    m_First=new QSound("://sound/First.wav");
    m_other=new QSound("://sound/Other.wav");
    m_Change=new QSound("://sound/Change.wav");

    //テキストボックスの準備
    ui->lineEdit->setText("");
    ui->lineEdit_5->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}
//文字を入れるやつは死ね。
void MainWindow::getTempo()
{
    //テンポ
    QString strDefaultTempo = ui->lineEdit->text();
    m_DefaultTempo = strDefaultTempo.toShort();
    if(m_DefaultTempo==0)
    {
        ui->lineEdit->setText("120");
        m_DefaultTempo=120;
    }

    //小節
    QString strLoopBar = ui->lineEdit_2->text();
    m_LoopBar = strLoopBar.toShort();
    if(m_LoopBar==0)
    {
        ui->lineEdit_2->setText("4");
        m_LoopBar=4;
    }

    //繰り返し回数
    QString strLoopNum = ui->lineEdit_3->text();
    m_LoopNum = strLoopNum.toShort();
    if(m_LoopNum==0)
    {
        ui->lineEdit_3->setText("4");
        m_LoopNum=16;
    }

    //上昇値
    QString strriseTempo = ui->lineEdit_4->text();
    m_RiseTempo = strriseTempo.toShort();
    if(m_RiseTempo==0)
    {
        ui->lineEdit_4->setText("5");
        m_RiseTempo=5;
    }

    //上限
    QString strlimitTempo = ui->lineEdit_5->text();
    if(strlimitTempo.toShort()==0)
    {
        ui->lineEdit_5->setText("180");
        strlimitTempo="180";
    }
    if(strlimitTempo.toShort()<=m_DefaultTempo)
    {
        ui->lineEdit_5->setText( ui->lineEdit->text() );
    }
    m_LimitTempo =MINUTE/ strlimitTempo.toShort();

    //このタイミングで(最初は)なるよ
    m_NowTempo =MINUTE/ m_DefaultTempo;
    m_Timer->setInterval( m_NowTempo );

    m_LoopBarCount =1;
    m_LoopNumCount =1;

    emit imReady();
    m_Timer->start();
}

void MainWindow::theEnd()
{
    m_Timer->stop();
}

//音を鳴らして数を数える
void MainWindow::soundStart()
{
    playSound();
    setLoopBar();
}

//どれ鳴らすよ
void MainWindow::playSound()
{
    if(m_LoopBarCount==1)
    {
        if(m_LoopNumCount==1)
        {
            m_Change->play();

            //テンポかわったよ
            m_Timer->setInterval( m_NowTempo );
            m_Timer->start();
            return;
        }
        m_First->play();
    }
    else
    {
        m_other->play();
    }
}

//何小節やってんのかね
void MainWindow::setLoopBar()
{
    if(m_LoopBar<=m_LoopBarCount)
    {
        m_LoopBarCount=1;
        resetTempo();
    }
    else
    {
        m_LoopBarCount++;
    }

}

//指定小節やったよ
void MainWindow::resetTempo()
{
    if(m_LoopNum <= m_LoopNumCount)
    {
        m_LoopNumCount = 1;

        //イケてない処理
        if(m_NowTempo< m_LimitTempo)
        {
            m_NowTempo =m_LimitTempo;
        }
        else
        {
            m_DefaultTempo +=m_RiseTempo;
            m_NowTempo =MINUTE/ m_DefaultTempo;
            if(m_NowTempo< m_LimitTempo)
            {
                m_NowTempo =m_LimitTempo;
            }
        }
    }
    else{m_LoopNumCount++;}
}
