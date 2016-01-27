#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    log_stream = "";
    QObject::connect(this, SIGNAL(consoleUpdated()), this, SLOT(updateConsole()));
    QObject::connect(ui->button_clear, SIGNAL(clicked()), this, SLOT(clearConsole()));
    QObject::connect(ui->button_key, SIGNAL(clicked()), this, SLOT(createProfile()));
    QObject::connect(ui->button_delete, SIGNAL(clicked()), this, SLOT(deleteProfile()));
    QObject::connect(ui->button_import, SIGNAL(clicked()), this, SLOT(importProfile()));
    QObject::connect(ui->button_encrypt, SIGNAL(clicked()), this, SLOT(encryptMessage()));
    QObject::connect(ui->button_decrypt, SIGNAL(clicked()), this, SLOT(decryptMessage()));
    QObject::connect(ui->button_public, SIGNAL(clicked()), this, SLOT(exportPublicKey()));
    QObject::connect(ui->button_public_private, SIGNAL(clicked()), this, SLOT(exportPublicPrivateKeys()));
    QObject::connect(ui->check_console, SIGNAL(toggled(bool)), this, SLOT(showConsole(bool)));
    log_stream += "Welcome to PGP - Pretty Goofy Privacy!\n\nStart by creating your profile, then import the profiles of the ones you want to exchange encrypted messages with";
    consoleUpdated();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createProfile()
{
    if (ui->edit_name->text() != ""){
        log_stream += "\n\nCreating profile " + ui->edit_name->text().toStdString();
        consoleUpdated();
        Profile* profile = new Profile(ui->edit_name->text().toStdString(),ui->slider_key->value());
        profile->createKeys();
        profiles.push_back(profile);
        ui->listWidget->addItem(ui->edit_name->text());
        log_stream += "\nGenerating public key\n";
        log_stream += "Found two prime number P and Q\n";
        log_stream += "P = " + profile->P->number + "\n";
        log_stream += "Q = " + profile->Q->number + "\n";
        log_stream += "N = P x Q = " + profile->N->number + "\n";
        log_stream += "Found a number C prime to M\n";
        log_stream += "C = " + profile->C->number + "\n";
        log_stream += "Generated public key C, N\n";
        log_stream += "Generating private key\n";
        log_stream += "Found a number U such that C × U + M × V = 1\n";
        log_stream += "U = " + profile->U->number + "\n";
        log_stream += "Generated private key U, N\n";
        log_stream += "Profile " + ui->edit_name->text().toStdString() + " created";
        consoleUpdated();
        ui->edit_name->setText("");
    }
    else{
        log_stream += "\n\nEnter a name to create profile";
        consoleUpdated();
    }
}

void MainWindow::deleteProfile()
{
    if (ui->listWidget->count() > 0 && ui->listWidget->currentRow() != -1){
        profiles.erase(profiles.begin()+ui->listWidget->currentRow());
        ui->listWidget->takeItem(ui->listWidget->currentRow());
        log_stream += "\n\nDeleting profile " + ui->edit_name->text().toStdString() + "\n";
        log_stream += "Profile deleted";
        consoleUpdated();
    }
    else{
        log_stream += "\n\nSelect a profile to delete";
        consoleUpdated();
    }
}

void MainWindow::importProfile()
{
    log_stream += "\n\nImporting profile from editor";
    consoleUpdated();
    bool correct = false;
    bool guest = true;
    string split;
    stringstream ss(ui->text_editor->toPlainText().toStdString());
    int i = 0;
    Profile* profile = new Profile();
    while(getline(ss, split,'-')){
        correct = false;
        if (i == 0) profile->name = split;
        else if (i == 1) profile->keySize = atoi(split.c_str());
        else{
            Binary* character = new Binary(split);
            if (character->isBinary()){
                if (i == 2) *profile->publicKey.first = *character;
                else if (i == 3) {
                    *profile->publicKey.second = *character;
                    correct = true;
                }
                else if (i == 4) *profile->privateKey.first = *character;
                else if (i == 5) {
                    *profile->privateKey.second = *character;
                    correct = true;
                    guest = false;
                }
                else break;
            }
            else break;
        }
        i++;
    }
    if (correct){
        profiles.push_back(profile);
        if (guest)
            ui->listWidget->addItem(QString::fromStdString(profile->name + " (Guest)"));
        else ui->listWidget->addItem(QString::fromStdString(profile->name));
        log_stream += "\nFound public key C, N\n";
        log_stream += "C = " + profile->C->number + "\n";
        log_stream += "N = " + profile->C->number + "\n";
        if (profile->privateKey.first->number != "" && profile->privateKey.second->number != ""){
            log_stream += "Found private key U, N\n";
            log_stream += "U = " + profile->U->number + "\n";
            log_stream += "N = " + profile->C->number + "\n";
        }
        log_stream += "Profile " + profile->name + " imported";
        consoleUpdated();
    }
    else{
        log_stream += "\nCannot import profile from editor, correct formats should be\n";
        log_stream += "Name-Key size-Public key C-Public key N\n";
        log_stream += "Name-Key size-Public key C-Public key N-Private key U-Private key N";
        consoleUpdated();
    }
}

void MainWindow::encryptMessage()
{
    if (ui->listWidget->count() > 0 && ui->listWidget->currentRow() != -1){
        log_stream += "\n\nEncrypting message in editor\n";
        consoleUpdated();
        Profile* profile = new Profile(*profiles[ui->listWidget->currentRow()]);
        ui->text_editor->setPlainText(QString::fromStdString(profile->encryptText(ui->text_editor->toPlainText().toStdString())));
        log_stream += "Converting characters in decimal ASCII code\n";
        log_stream += "Calculating modular exponentiation of the results such as:\n";
        log_stream += "Encrypted text = Plain text ^ C % N\n";
        log_stream += "Message encrypted";
        consoleUpdated();
    }
    else{
        log_stream += "\n\nSelect a profile to use for encryption";
        consoleUpdated();
    }
}

void MainWindow::decryptMessage()
{
    if (ui->listWidget->count() > 0 && ui->listWidget->currentRow() != -1){
        log_stream += "\n\nDecrypting message in editor";
        consoleUpdated();
        Profile* profile = new Profile(*profiles[ui->listWidget->currentRow()]);
        if (profile->privateKey.first->number != "" && profile->privateKey.second->number != "")
            ui->text_editor->setPlainText(QString::fromStdString(profile->decryptText(ui->text_editor->toPlainText().toStdString())));
        log_stream += "\nCalculating modular exponentiation of the results such as:\n";
        log_stream += "Decrypted text = Encrypted text ^ U % N\n";
        log_stream += "Converting characters in decimal ASCII code\n";
        log_stream += "Message decrypted";
        consoleUpdated();
    }
    else{
        log_stream += "\n\nSelect a profile to use for decryption";
        consoleUpdated();
    }
}

void MainWindow::exportPublicKey()
{
    if (ui->listWidget->count() > 0 && ui->listWidget->currentRow() != -1){
        Profile* profile = new Profile(*profiles[ui->listWidget->currentRow()]);
        stringstream ss;
        ss << profile->keySize;
        string exported = profile->name + "-" + ss.str() + "-" + profile->publicKey.first->number + "-" + profile->publicKey.second->number;
        ui->text_editor->setPlainText(QString::fromStdString(exported));
        log_stream += "\n\nExporting public key C, N\n";
        log_stream += "C = " + profile->C->number + "\n";
        log_stream += "N = " + profile->C->number + "\n";
        log_stream += "Public key exported";
        consoleUpdated();
    }
    else{
        log_stream += "\n\nSelect a profile to export";
        consoleUpdated();
    }
}

void MainWindow::exportPublicPrivateKeys()
{
    if (ui->listWidget->count() > 0 && ui->listWidget->currentRow() != -1){
        Profile* profile = new Profile(*profiles[ui->listWidget->currentRow()]);
        if (profile->privateKey.first->number != "" && profile->privateKey.second->number != ""){
            stringstream ss;
            ss << profile->keySize;
            string exported = profile->name + "-" + ss.str() + "-" + profile->publicKey.first->number + "-" + profile->publicKey.second->number + "-" + profile->privateKey.first->number + "-" + profile->privateKey.second->number;
            ui->text_editor->setPlainText(QString::fromStdString(exported));
            log_stream += "\n\nExporting public key C, N\n";
            log_stream += "C = " + profile->C->number + "\n";
            log_stream += "N = " + profile->C->number + "\n";
            log_stream += "Exporting private key U, N\n";
            log_stream += "U = " + profile->U->number + "\n";
            log_stream += "N = " + profile->C->number + "\n";
            log_stream += "Public and private keys exported";
            consoleUpdated();
        }
        else{
            log_stream += "\nNo private keys to export";
            consoleUpdated();
            exportPublicKey();
        }
    }
    else{
        log_stream += "\n\nSelect a profile to export";
        consoleUpdated();
    }
}

void MainWindow::showConsole(bool checked)
{
    if (checked){
        ui->text_console->setPlainText(QString::fromStdString(log_stream));
        log_stream += "\n\nConsole enabled";
        consoleUpdated();
    }
    else{
        ui->text_console->setPlainText("");
        log_stream += "\n\nConsole disabled";
        consoleUpdated();
    }
}

void MainWindow::updateConsole()
{
    if (ui->check_console->isChecked()){
        ui->text_console->setPlainText(QString::fromStdString(log_stream));
        ui->text_console->verticalScrollBar()->setValue(ui->text_console->verticalScrollBar()->maximum());
    }
    else{
        ui->text_console->setPlainText("");
    }
}

void MainWindow::clearConsole()
{
    log_stream = "";
    ui->text_console->setPlainText("");
}
