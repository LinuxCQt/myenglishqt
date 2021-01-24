/*
  Alfabeto Copyright © 2019 Juanra Goti

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

#include <QFile>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QTextToSpeech>

#include "dialogalfabeto.h"
#include "ui_dialogalfabeto.h"

DialogAlfabeto::DialogAlfabeto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAlfabeto)
{
    ui->setupUi(this);

    setWindowTitle(QCoreApplication::applicationName());
    setWindowFlags(Qt::Dialog);

    setModal(true);

    ui->pushButtonNex->setText(tr("Siguiente"));
    ui->pushButtonSound->setText(tr("Sonido"));

    funShow();
}

DialogAlfabeto::~DialogAlfabeto()
{
    delete ui;
}

void DialogAlfabeto::funBotones(bool resultado)
{
    QList<QPushButton *> botones = this->findChildren<QPushButton *>();
    for(auto *boton: botones)
        boton->setEnabled(resultado);

    ui->pushButtonNex->setEnabled(true);
    ui->pushButtonSound->setEnabled(true);
}

void DialogAlfabeto::funShow()
{
    funBotones(false);

    //Generamos un número aleatorio entre 1 y 26, las letras del alfabeto, para ver cuál decir
    int indice = QRandomGenerator::global()->bounded(1, 27);
    switch(indice){
        case 1:
           letraCorrecta = "A";
           break;
        case 2:
           letraCorrecta = "B";
           break;
        case 3:
           letraCorrecta = "C";
           break;
        case 4:
           letraCorrecta = "D";
           break;
        case 5:
           letraCorrecta = "E";
           break;
        case 6:
           letraCorrecta = "F";
           break;
        case 7:
           letraCorrecta = "G";
           break;
        case 8:
           letraCorrecta = "H";
           break;
        case 9:
           letraCorrecta = "I";
           break;
        case 10:
           letraCorrecta = "J";
           break;
        case 11:
           letraCorrecta = "K";
           break;
        case 12:
           letraCorrecta = "L";
           break;
        case 13:
           letraCorrecta = "M";
           break;
        case 14:
           letraCorrecta = "N";
           break;
        case 15:
           letraCorrecta = "O";
           break;
        case 16:
           letraCorrecta = "P";
           break;
        case 17:
           letraCorrecta = "Q";
           break;
        case 18:
           letraCorrecta = "R";
           break;
        case 19:
           letraCorrecta = "S";
           break;
        case 20:
           letraCorrecta = "T";
           break;
        case 21:
           letraCorrecta = "U";
           break;
        case 22:
           letraCorrecta = "V";
           break;
        case 23:
           letraCorrecta = "W";
           break;
        case 24:
           letraCorrecta = "X";
           break;
        case 25:
           letraCorrecta = "Y";
           break;
        case 26:
           letraCorrecta = "Z";
           break;
        default:
           letraCorrecta = "A";
           break;
    }
    ui->label->clear();
    //Se acierte o no, se marca la respuesta correcta
    QList<QPushButton *> botones = this->findChildren<QPushButton *>();
    for(auto *boton: botones){
        if(boton->text() == "A" ||
                boton->text() == "H" ||
                boton->text() == "J" ||
                boton->text() == "K" ){
            boton->setStyleSheet("background-color: rgb(170, 255, 127); color: rgb(0, 0, 255)");
        } else if(boton->text() == "B" ||
                boton->text() == "C" ||
                boton->text() == "D" ||
                boton->text() == "E" ||
                boton->text() == "G" ||
                boton->text() == "P" ||
                boton->text() == "T" ||
                boton->text() == "V" ||
                boton->text() == "Z" ){
            boton->setStyleSheet("background-color: rgb(170, 255, 127); color: rgb(0, 85, 0)");
        } else if(boton->text() == "F" ||
                boton->text() == "L" ||
                boton->text() == "M" ||
                boton->text() == "N" ||
                boton->text() == "S" ||
                boton->text() == "X" ){
            boton->setStyleSheet("background-color: rgb(170, 255, 127); color: rgb(170, 85, 0)");
        } else if(boton->text() == "I" ||
                boton->text() == "Y" ){
            boton->setStyleSheet("background-color: rgb(170, 255, 127); color: rgb(0, 170, 255)");
        } else if(boton->text() == "Q" ||
                boton->text() == "U" ||
                boton->text() == "W" ){
            boton->setStyleSheet("background-color: rgb(170, 255, 127); color: rgb(255, 0, 255)");
        } else if(boton->text() == "O" ||
                boton->text() == "R" ){
            boton->setStyleSheet("background-color: rgb(170, 255, 127); color: rgb(255, 0, 0)");
        }
    }
    funSound();

    funBotones(true);
}

void DialogAlfabeto::funComprobar(QString cadLetraPulsada)
{
    funBotones(false);

    if(letraCorrecta == cadLetraPulsada){
        ui->label->setText(tr("Correcto"));
    } else {
        ui->label->setText(tr("Incorrecto"));
    }

    //Se acierte o no, se marca la respuesta correcta
    QList<QPushButton *> botones = this->findChildren<QPushButton *>();
    for(auto *boton: botones){
        if(boton->text() == cadLetraPulsada){
            boton->setStyleSheet("background-color: rgb(255, 0, 0)");
        }

        if(boton->text() == letraCorrecta){
            boton->setStyleSheet("background-color: rgb(255, 255, 0)");
        }
    }
}

void DialogAlfabeto::funSound()
{
    QTextToSpeech *speech = new QTextToSpeech;
    speech->stop();
    speech = new QTextToSpeech();
    speech->setLocale( QLocale( QLocale::English, QLocale::LatinScript, QLocale::UnitedStates ) );
    speech->say( letraCorrecta );
}

void DialogAlfabeto::on_pushButtonA_clicked()
{
    funComprobar("A");
}

void DialogAlfabeto::on_pushButtonB_clicked()
{
    funComprobar("B");
}

void DialogAlfabeto::on_pushButtonC_clicked()
{
    funComprobar("C");
}

void DialogAlfabeto::on_pushButtonD_clicked()
{
    funComprobar("D");
}

void DialogAlfabeto::on_pushButtonE_clicked()
{
    funComprobar("E");
}

void DialogAlfabeto::on_pushButtonF_clicked()
{
    funComprobar("F");
}

void DialogAlfabeto::on_pushButtonG_clicked()
{
    funComprobar("G");
}

void DialogAlfabeto::on_pushButtonH_clicked()
{
    funComprobar("H");
}

void DialogAlfabeto::on_pushButtonI_clicked()
{
    funComprobar("I");
}

void DialogAlfabeto::on_pushButtonJ_clicked()
{
    funComprobar("J");
}

void DialogAlfabeto::on_pushButtonK_clicked()
{
    funComprobar("K");
}

void DialogAlfabeto::on_pushButtonL_clicked()
{
    funComprobar("L");
}

void DialogAlfabeto::on_pushButtonM_clicked()
{
    funComprobar("M");
}

void DialogAlfabeto::on_pushButtonN_clicked()
{
    funComprobar("N");
}

void DialogAlfabeto::on_pushButtonO_clicked()
{
    funComprobar("O");
}

void DialogAlfabeto::on_pushButtonP_clicked()
{
    funComprobar("P");
}

void DialogAlfabeto::on_pushButtonQ_clicked()
{
    funComprobar("Q");
}

void DialogAlfabeto::on_pushButtonR_clicked()
{
    funComprobar("R");
}

void DialogAlfabeto::on_pushButtonS_clicked()
{
    funComprobar("S");
}

void DialogAlfabeto::on_pushButtonT_clicked()
{
    funComprobar("T");
}

void DialogAlfabeto::on_pushButtonU_clicked()
{
    funComprobar("U");
}

void DialogAlfabeto::on_pushButtonV_clicked()
{
    funComprobar("V");
}

void DialogAlfabeto::on_pushButtonW_clicked()
{
    funComprobar("W");
}

void DialogAlfabeto::on_pushButtonX_clicked()
{
    funComprobar("X");
}

void DialogAlfabeto::on_pushButtonY_clicked()
{
    funComprobar("Y");
}

void DialogAlfabeto::on_pushButtonZ_clicked()
{
    funComprobar("Z");
}

void DialogAlfabeto::on_pushButtonNex_clicked()
{
    funShow();
}

void DialogAlfabeto::on_pushButtonSound_clicked()
{
    funSound();
}
