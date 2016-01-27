#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QScrollBar>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <sstream>
#include "Binary.h"
#include "Profile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    vector<Profile*> profiles;
    string log_stream;

public slots:
    void createProfile();
    void deleteProfile();
    void importProfile();
    void encryptMessage();
    void decryptMessage();
    void exportPublicKey();
    void exportPublicPrivateKeys();
    void showConsole(bool checked);
    void updateConsole();
    void clearConsole();

signals:
    void consoleUpdated();
};

#endif // MAINWINDOW_H
