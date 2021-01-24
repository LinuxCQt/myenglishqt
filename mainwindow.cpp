/*
  MyEnglishQt Copyright © 2019 Juanra Goti

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDesktopServices>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogedittest.h"
#include "dialogexamen.h"
#include "dialogalfabeto.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QCoreApplication::applicationName());
    setWindowFlags(Qt::Window);

    ui->pushButtonExanGrammar->setText(tr("Examen"));
    ui->pushButtonEditGrammar->setText(tr("Editar"));
    ui->pushButtonAlfabeto->setText(tr("Alfabeto"));
    ui->pushButtonHelp->setText(tr("Información"));
    ui->pushButtonAbout->setText(tr("Acerca de"));
    ui->pushButtonExit->setText(tr("Salir"));

    QString file = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/myenglishqt.db";
    //Si no existe la base de datos, se crea.
    if(!QFile(file).exists())
        funCreateDb(file);
    else
        funConnectBD(file);
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::funConnectBD(QString fileDb)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileDb);

    if(!db.open()){
        QMessageBox::warning(this, QCoreApplication::applicationName(), tr("Error en la conexión con la db de datos"));
        db.close();
        return;
    }
}

void MainWindow::funCreateDb(QString fileDb)
{
    funConnectBD(fileDb);

    QSqlQuery query(db);
    query.exec("CREATE TABLE words ("
               "ind  INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,"
               "english VARCHAR(200),"
               "spanish VARCHAR(200),"
               "image BLOB,"
               "avances INTEGER)"
               );
    //Se crea una base de datos con 1 elemento
    query.prepare("INSERT INTO words (ind, english, spanish, image, avances) "
                 "VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(1);
    query.addBindValue("");
    query.addBindValue("");
    query.addBindValue("");
    query.addBindValue(0);
    query.exec();

    query.clear();
    query.finish();

    on_pushButtonEditGrammar_clicked();
}

void MainWindow::on_pushButtonExanGrammar_clicked()
{
    DialogExamen examen(db);
    examen.exec();
}

void MainWindow::on_pushButtonEditGrammar_clicked()
{
    DialogEditTest edit(db);
    edit.exec();
}

void MainWindow::on_pushButtonAlfabeto_clicked()
{
    DialogAlfabeto alfabeto(this);
    alfabeto.exec();
}

void MainWindow::on_pushButtonExit_clicked()
{
    QCoreApplication::exit();
}

void MainWindow::on_pushButtonAbout_clicked()
{
    QString msg = "MyEnglishQt Copyright © 2019 Juanra Goti\n"

            "Version: " + QCoreApplication::applicationVersion() + "\n"

            "Email: linuxcqt@gmail.com\n\n"

            "This program is free software: you can redistribute it and/or modify "
            "it under the terms of the GNU General Public License as published by "
            "the Free Software Foundation, either version 3 of the License, or "
            "(at your option) any later version.\n\n"

            "This program is distributed in the hope that it will be useful, "
            "but WITHOUT ANY WARRANTY; without even the implied warranty of "
            "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
            "GNU General Public License for more details.\n\n"

            "You should have received a copy of the GNU General Public License "
            "along with this program.  If not, see <http://www.gnu.org/licenses/>.";

    QMessageBox::information(this, QCoreApplication::applicationName(), msg);
}


void MainWindow::on_pushButtonHelp_clicked()
{
    QString fileName = QCoreApplication::applicationDirPath()  + "/MyEnglishQt.pdf";
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}
