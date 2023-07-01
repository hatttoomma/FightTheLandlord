
#include "mainwindow.h"
#include "player.h"
#include "randomArray.h"
#include "ui_mainwindow.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //this->setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::Window);
    ui->setupUi(this);
    setWindowTitle("FightTheLandlord");
    ui->stackedWidget->setCurrentIndex(1);
    ui->Button_Playcard->hide();

    connect(ui->Button_Play,&QPushButton::clicked,this,[=](){
        ui->Button_Play->hide();
        ui->Button_Playcard->show();
        ui->pushButton->hide();
        ui->radioButton->hide();
        ui->radioButton_2->hide();
        ui->stackedWidget->setCurrentIndex(0);
        SetBackground();
        NewGame();
    });
    connect(ui->Button_Restart,&QPushButton::clicked,this,[=](){
        for(int i=0;i<54;i++) c[i]->hide();
        NewGame();
    });
    connect(ui->Button_Back,&QPushButton::clicked,this,[=](){
        setStyleSheet("");
        ui->stackedWidget->setCurrentIndex(1);
        ui->Button_Play->show();
        ui->Button_Playcard->hide();
        for (int i = 0; i < 54; ++i) {
            c[i]->hide();
        }
    });
}

void MainWindow::SetBackground(){
    this->setObjectName("mainScreen");
    setStyleSheet("QMainWindow#mainScreen{border-image:url(:/p/backgrounds/background_purple.png);}");
}

void MainWindow::NewGame(){
    generate_array();
    //player Player[3];
    decided=0;
    for (int i = 0; i < 54; ++i) {
        int col=(Myarray[i]-1)/13;
        int p=(Myarray[i]-1)%13;
        if(i<17)
        {
            c[i]=new card1(i,col,p,1);
            Player[0].cards[i]=i;
            c[i]->resize(48,66);
            c[i]->move(18*i+this->x()+this->width()/2-168,500+this->y());
            c[i]->show();
            c[i]->belongto=100;
        }
        else if(i<37&&i>19){
            c[i]=new card1(i,col,p,0);
            Player[2].cards[i-20]=i;
            c[i]->resize(66,48);
            c[i]->move(this->x()+this->width()/2-168-5*(i-20),50+18*(i-20)+this->y());
            c[i]->show();
            c[i]->belongto=2;
        }
        else if(i>36){
            c[i]=new card1(i,col,p,0);
            Player[1].cards[i-37]=i;
            c[i]->resize(66,48);
            c[i]->move(this->x()+this->width()/2+168+5*(i-37),50+18*(i-37)+this->y());
            c[i]->show();
            c[i]->belongto=1;
        }
        else{
            c[i]=new card1(i,col,p,0);
            c[i]->resize(48,66);
            c[i]->move(50*(i-17)+this->x()+this->width()/2-75,250+this->y());
            c[i]->show();
            c[i]->belongto=100;
        }
    }
    int player_firstcall=0;
    flag_calllandlord=0;
    int player_call=(player_firstcall)%3;
    if(!player_call){
        ui->pushButton->show();
        ui->radioButton->show();
        ui->radioButton_2->show();
        QTimer::singleShot(10000,[&](){
            if(decided) return;
            decided=1;
            if(ui->radioButton->isChecked())
            {
                flag_calllandlord=1;
                for(int i=17;i<20;i++){
                    c[i]->emerged=1;
                    c[i]->setStyleSheet(cardpath[c[i]->color][c[i]->point]);
                    Player[0].cards[i]=i;
                    c[i]->belongto=0;
                }
                Player[0].cardNumber=20;
                Player[0].landlord=1;
                QTimer::singleShot(1500,[&](){
                    sortcards(20);
                });
            }
            ui->pushButton->hide();
            ui->radioButton->hide();
            ui->radioButton_2->hide();
            call[0]=call[1]=1;
            for (int j = 0; j < 1&&!flag_calllandlord; ++j) {
                if(call[j]){
                    flag_calllandlord=1;
                    sortcards(17);
                    for(int i=17;i<20;i++){
                        c[i]->emerged=1;
                        c[i]->setStyleSheet(cardpath[c[i]->color][c[i]->point]);
                        Player[j+1].cards[i]=i;
                        c[i]->belongto=j+1;
                    }
                    Player[j+1].cardNumber=20;
                    Player[j+1].landlord=1;
                    QTimer::singleShot(1500,[&](){
                        for(int i=17;i<20;i++){
                            c[i]->emerged=0;
                            c[i]->setStyleSheet("border-image:url(:/p/cards/back.png);");
                            c[i]->resize(66,48);
                            if(j) c[i]->move(this->x()+this->width()/2-168-5*(i),50+18*(i)+this->y());
                            else c[i]->move(this->x()+this->width()/2+168+5*(i),50+18*(i)+this->y());
                        }
                    });
                }
            }
            ingame();
        });
        connect(ui->pushButton,&QPushButton::clicked,this,[&](){
            //cout<<decided<<endl<<ui->radioButton->isChecked()<<endl<<ui->radioButton_2->isChecked()<<endl;
            if(decided||(!ui->radioButton->isChecked()&&!ui->radioButton_2->isChecked())) return;
            decided=1;
            if(ui->radioButton->isChecked())
            {
                flag_calllandlord=1;
                for(int i=17;i<20;i++){
                    c[i]->emerged=1;
                    c[i]->setStyleSheet(cardpath[c[i]->color][c[i]->point]);
                    Player[0].cards[i]=i;
                    c[i]->belongto=0;
                }
                Player[0].cardNumber=20;
                Player[0].landlord=1;
                QTimer::singleShot(1500,[&](){
                    sortcards(20);
                });
            }
            ui->pushButton->hide();
            ui->radioButton->hide();
            ui->radioButton_2->hide();
            call[0]=call[1]=1;
            for (int j = 0; j < 1&&!flag_calllandlord; ++j) {
                if(call[j]){
                    flag_calllandlord=1;
                    sortcards(17);
                    for(int i=17;i<20;i++){
                        c[i]->emerged=1;
                        c[i]->setStyleSheet(cardpath[c[i]->color][c[i]->point]);
                        Player[j+1].cards[i]=i;
                        c[i]->belongto=j+1;
                    }
                    Player[j+1].cardNumber=20;
                    Player[j+1].landlord=1;
                    QTimer::singleShot(1500,[&](){
                        for(int i=17;i<20;i++){
                            c[i]->emerged=0;
                            c[i]->setStyleSheet("border-image:url(:/p/cards/back.png);");
                            c[i]->resize(66,48);
                            if(j) c[i]->move(this->x()+this->width()/2-168-5*(i),50+18*(i)+this->y());
                            else c[i]->move(this->x()+this->width()/2+168+5*(i),50+18*(i)+this->y());
                        }
                    });
                }
            }
            ingame();
        });
    }
}

void MainWindow::sortcards(int num_card){
    sort(Myarray,Myarray+num_card,in_left);
    for(int k=0;k<num_card-1;k++){
        int col=(Myarray[k]-1)/13;
        int p=(Myarray[k]-1)%13;
        c[k]->color=col;
        c[k]->point=p;
        c[k]->belongto=0;
        c[k]->resize(18,66);
        c[k]->setStyleSheet(cardpath_shift[c[k]->color][c[k]->point]);
        c[k]->move(18*k+this->x()+this->width()/2-168,500+this->y());
    }
    int k=num_card-1;
    int col=(Myarray[k]-1)/13;
    int p=(Myarray[k]-1)%13;
    c[k]->color=col;
    c[k]->point=p;
    c[k]->belongto=0;
    c[k]->isend=1;
    c[k]->resize(48,66);
    c[k]->setStyleSheet(cardpath[c[k]->color][c[k]->point]);
    c[k]->move(18*k+this->x()+this->width()/2-168,500+this->y());
}
bool MainWindow::endgame(){
    return Player[0].cardNumber==0||Player[1].cardNumber==0||Player[2].cardNumber==0;
}

void MainWindow::ingame(){
    if(endgame())return;
        Player[0].active=1;
        QString s=QString::number(Player[0].turns);

        ui->label_3->setText(s);
        ui->label_3->show();
        QTimer::singleShot(10000,[&](){
            emit end_of_turn(0,Player[0].turns);
            //player1 play
            //player2 play
            ingame();
        });

    connect(this,&MainWindow::end_of_turn,this,&MainWindow::end_of_play);
}




MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::end_of_play(int player,int turn){
    if(Player[player].active&&Player[player].turns==turn){
        ui->label_3->hide();
        Player[player].turns++;
        Player[player].active=0;
        int card_remain=0;
        int last_card=0;
        for(int j=0;j<Player[player].cardNumber;j++){
            if(!c[j]->picked&&!c[j]->used){
                last_card=j;
                c[j]->move(18*card_remain+this->x()+this->width()/2-168,500+this->y());
                card_remain++;
            }
            else{
                c[j]->used=1;
                c[j]->hide();
            }
        }
        c[last_card]->isend=1;
        for(int j=0;j<Player[player].cardNumber;j++){
            c[j]->reshow();
        }
    }
}

void MainWindow::on_Button_Playcard_clicked()
{
    emit end_of_turn(0,Player[0].turns);
}

