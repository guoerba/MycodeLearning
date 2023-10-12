#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void btn_onclick_StopandStart();
    void btn_onclick_Connect();
    void btn_onclick_StyleSheet();
    void btn_onclick_SlotFunction();
private:
    QPushButton *btnStopandStart;
    QPushButton *btnConnect;
    QPushButton *btnSendCommand;
    QPushButton *btnStyleSheet;
    QPushButton *btnSlotFunction;

    bool styleSheetFlag;
    QString oldStyleSheet;
};
#endif // MAINWINDOW_H
