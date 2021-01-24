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

#include <QMessageBox>

#include "dialogexamen.h"
#include "ui_dialogexamen.h"

DialogExamen::DialogExamen(QString fileTest, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogExamen)
{
    ui->setupUi(this);
    setWindowTitle( QCoreApplication::applicationName() );
    setWindowFlags(Qt::Window);

    setModal(true);    

    ui->pushButtonCheck->setText(tr("Mostrar"));
    ui->pushButtonDificult->setText(tr("Difícil"));
    ui->pushButtonEsay->setText(tr("Fácil"));
    ui->pushButtonSound->setText(tr("Sonido"));
    ui->pushButtonExit->setText(tr("Salir"));

    fileNameTest = fileTest;

    speech = new QTextToSpeech();

    db.removeDatabase("my_connection_name");
    db = QSqlDatabase::addDatabase("QSQLITE", "my_connection_name");
    db.setDatabaseName(fileNameTest);

    if(!db.open()){
        QMessageBox::warning(this, QCoreApplication::applicationName(), tr("Error en la conexión con la base de datos"));
        db.close();
        return;
    }

    query = new QSqlQuery("SELECT * FROM words WHERE avances < 5", db);
    int numRecords = 0;
    while( query->next() )
        numRecords++;

    if ( numRecords == 0 ){
        QMessageBox::warning(this, QCoreApplication::applicationName(), tr("El archivo está vacío o se han estudiado todas sus fichas"));
        return;
    }

    query->seek( 0 );

    funShowFicha();
}

DialogExamen::~DialogExamen()
{
    delete query;
    db.commit();
    db.transaction();
    db.connectionName().clear();
    db.close();
    delete ui;
}

void DialogExamen::funSound()
{
    speech->stop();
    speech = new QTextToSpeech();
    speech->setLocale( QLocale( QLocale::English, QLocale::LatinScript, QLocale::UnitedStates ) );
    speech->say( query->value(1).toByteArray() );
}

void DialogExamen::funShowFicha()
{
    ui->labelAnswerOk->clear();

    QString question;
    question = query->value(1).toString();
    answer = query->value(2).toString();
    ui->labelPalabraWord->setText(question);

    ui->label->clear();
    if( !query->value(3).toByteArray().isEmpty() ){
        QByteArray array = query->value(3).toByteArray();
        QPixmap pixmap;
        pixmap.loadFromData(array);
        pixmap = pixmap.scaled(ui->label->size(), Qt::IgnoreAspectRatio);
        ui->label->setPixmap(pixmap);
    }

    funSound();

    ui->labelAnswerOk->clear();

    ui->pushButtonEsay->setEnabled( false );
    ui->pushButtonDificult->setEnabled( false );
    ui->pushButtonCheck->setEnabled( true );
    ui->pushButtonCheck->setFocus();
}

void DialogExamen::on_pushButtonExit_clicked()
{
    db.close();
    close();
}

void DialogExamen::on_pushButtonCheck_clicked()
{
    ui->labelAnswerOk->setText( answer );

    ui->pushButtonCheck->setEnabled( false );
    ui->pushButtonDificult->setEnabled( true );
    ui->pushButtonEsay->setEnabled( true );
    ui->pushButtonEsay->setFocus();
}

void DialogExamen::funNext()
{
    if( query->next() ) {
        funShowFicha();
    } else {
        QMessageBox::information(this, QCoreApplication::applicationName(), tr("Hemos llegado al final del archivo"));
        DialogExamen::close();
    }
}

void DialogExamen::on_pushButtonSound_clicked()
{
    funSound();
}

void DialogExamen::on_pushButtonDificult_clicked()
{
    funSaveAvances( 0 );
    funNext();
}

void DialogExamen::on_pushButtonEsay_clicked()
{
    funSaveAvances( 1 );
    funNext();
}

void DialogExamen::funSaveAvances( int avancesDificultOrEasy )
{
    //Hay cinco cajas, de 1 a 5. Cada vez que "vemos" la ficha, y la marcamos como fácil, se avanza una caja. Cuando se llegue a la caja cinco se supone que sabemos la ficha
    //después de haberla "visto" 4 veces y haberla marcado esas cuatro veces como fácil. Si, en algún momento del recorrido, marcamos la ficha como difícil, se vuelve a la
    //casilla de salida: Caja 0 para ir a la 1.

    int result, cajaActual = query->value( 4 ).toInt(), indiActual = query->value( 0 ).toInt();

    //Si la ficha se marca como difícil se vuelve a la casilla 0, la casilla de salida
    if( avancesDificultOrEasy == 0 ) {
        result = 0;
    //Si la ficha se marca como fácil, se avanza una casilla: Casilla actual más una
    } else {
        //Cuando se llega a la casilla cinco, la ficha se supone que se sabe y ya no vuelve a presentarse
        if ( cajaActual == 5 || cajaActual > 5 )
            result = 5;
        else
            result = cajaActual + avancesDificultOrEasy;
    }

    //Si se ha llegado a 5 en la palabra actual, se borra de la base de datos. Se supone que ya la sabemos.
    if( result == 5 ){
        QSqlQuery queryLocal( db );
        queryLocal.prepare( "DELETE FROM words WHERE ind =:my_ind" );
        queryLocal.bindValue( ":my_ind", indiActual );
        queryLocal.exec();
        queryLocal.clear();
    } else {
        QSqlQuery queryLocal( db );
        queryLocal.prepare( "UPDATE words SET avances=:my_avances WHERE ind=:my_ind" );
        queryLocal.bindValue( ":my_ind", indiActual );
        queryLocal.bindValue( ":my_avances", result );
        queryLocal.exec();
        queryLocal.clear();
    }

    db.transaction();
    db.commit();
}
