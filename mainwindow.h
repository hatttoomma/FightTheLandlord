
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "card1.h"
#include "progress.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void SetBackground(std::string s);
    void NewGame();
    void RestartGame();
    void addcards(int player);
    void sortcards(int num_card);

    bool endgame();
    void ingame(int game);
    ~MainWindow();


    int activepage;
    int num_games;
    std::string color_of_back;
    card1 *c[54];
    progress pro;
    int decided;
    int flag_calllandlord;
    int starttime_of_call;
    int call[2];

private:
    Ui::MainWindow *ui;

protected:
    void changeEvent(QEvent * event);

signals:
    void end_of_turn(int player,int turn,int game);
private slots:
    void on_Button_Playcard_clicked();
public slots:
    void end_of_play(int player,int turn,int game);
};

#endif // MAINWINDOW_H
