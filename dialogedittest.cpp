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
#include <QFileDialog>
#include <QStandardPaths>
#include <QSqlQuery>

#include "dialogedittest.h"
#include "ui_dialogedittest.h"

DialogEditTest::DialogEditTest(QString fileTest, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditTest)
{
    ui->setupUi(this);
    setWindowTitle( QCoreApplication::applicationName() );
    setWindowFlags(Qt::Window);

    setModal(true);

    ui->pushButtonAddRow->setText(tr("Añadir"));
    ui->pushButtonRemoveRow->setText(tr("Eliminar"));
    ui->pushButtonSaveAndExit->setText(tr("Guardar y salir"));

    ui->tableView->setStyleSheet("QTableView:item:selected {background-color: #3399FF; color: #FFFFFF}\n"
                                 "QTableView:item:selected:focus {background-color: #3399FF;}");

    fileNameTest = fileTest;

    funConnectBD();
    funShow();
}

DialogEditTest::~DialogEditTest()
{
    delete model;
    delete ui;
}

void DialogEditTest::funConnectBD()
{
    db.removeDatabase("my_connection_name");
    db = QSqlDatabase::addDatabase("QSQLITE", "my_connection_name");
    db.setDatabaseName(fileNameTest);

    if(!db.open()){
        QMessageBox::warning(this, QCoreApplication::applicationName(), tr("Error en la conexión con la db de datos"));
        db.close();
        return;
    }
}

void DialogEditTest::funShow()
{
    model = new QSqlTableModel(nullptr, db);
    model->setTable("words");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Índice"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Inglés"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Español"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Imagen"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Avances"));

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(4);
    funResize();
    ui->tableView->verticalHeader()->hide();

    funCreateButtonsImage();
}

QString DialogEditTest::funGetFileName()
{
    QString folderImage = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Abrir Imagen"), folderImage, tr("Image Files (*.png *.jpg *.bmp)"));
    return fileName;
}

void DialogEditTest::funCreateButtonsImage()
{
    for(int c = 0; c < model->rowCount(); c++){

        QPushButton *button = new QPushButton;
        QPixmap pixmap(QCoreApplication::applicationDirPath() + "/MyEnglishQt.png");
        QIcon icon(pixmap);
        button->setIcon(icon);
        button->setIconSize(pixmap.rect().size());

        QWidget* widget = new QWidget();

        QHBoxLayout* pLayout = new QHBoxLayout(widget);
        pLayout->addWidget(button);
        pLayout->setAlignment(Qt::AlignCenter);

        widget->setLayout(pLayout);

        ui->tableView->setIndexWidget(ui->tableView->model()->index(c, 3), button);

        connect (button, SIGNAL(clicked()), this, SLOT(funSlotButtonsImage()));

    }
}

void DialogEditTest::funSlotButtonsImage()
{
    QString fileName = funGetFileName();
    if(!fileName.isEmpty()){

        QModelIndex index = ui->tableView->selectionModel()->currentIndex();
        int value = model->index(index.row(), 0).data().toInt();

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) return;
        QByteArray byteArray = file.readAll();

        QSqlQuery query(db);
        query.prepare("UPDATE words SET image=:my_image WHERE ind=:my_ind");
        query.bindValue(":my_ind", QString::number(value));
        query.bindValue(":my_image", byteArray);
        query.exec();

        query.clear();
        query.finish();

        model->submitAll();

        funConnectBD();
        funShow();
    }
}

void DialogEditTest::on_pushButtonSaveAndExit_clicked()
{
    //Guardamos todos los cambios.
    model->submitAll();
    DialogEditTest::close();
}

void DialogEditTest::on_DialogEditTest_rejected()
{
   on_pushButtonSaveAndExit_clicked();
}

void DialogEditTest::on_pushButtonAddRow_clicked()
{
    QSqlQuery query( db );
    query.prepare("INSERT INTO words (english, spanish, image, avances) "
                 "VALUES (?, ?, ?, ?)");
    query.addBindValue("");
    query.addBindValue("");
    query.addBindValue("");
    query.addBindValue(0);
    query.exec();

    model->submitAll();

    funConnectBD();
    funShow();
}

void DialogEditTest::on_pushButtonRemoveRow_clicked()
{
    const int row = model->rowCount();
    if( row > 1 ){
        int indSelected = ui->tableView->selectionModel()->currentIndex().row();        
        if( indSelected == -1 ){
            QMessageBox::warning( this, QCoreApplication::applicationName(), tr( "Debe de seleccionar la fila a eliminar" ));
            return;
        } else {
            ui->tableView->selectRow( indSelected );

            QMessageBox msgBox;
            msgBox.setText(tr("¿Eliminar fila seleccionada?"));
            msgBox.setStandardButtons( QMessageBox::Yes | QMessageBox::No );
            msgBox.setDefaultButton( QMessageBox::No );
            int ret = msgBox.exec();
            if( ret == QMessageBox::Yes ){
                QString indToDelete = model->index( indSelected , 0 ).data().toString();

                QSqlQuery query( db );
                query.prepare( "DELETE FROM words WHERE ind = ?" );
                query.addBindValue( indToDelete );
                query.exec();

            } else {
                return;
            }
        }
    } else {
        QMessageBox::warning(this, QCoreApplication::applicationName(), tr("No se puede eliminar la fila seleccionada. Debe de haber al menos una"));
        return;
    }

    model->submitAll();

    funConnectBD();
    funShow();
}

void DialogEditTest::resizeEvent(QResizeEvent *)
{
    funResize();
}

void DialogEditTest::funResize()
{
    ui->tableView->setColumnWidth(1, (this->width() / 2) - 45);
    ui->tableView->setColumnWidth(2, (this->width() / 2) - 45);
    ui->tableView->setColumnWidth(3, 60);
}

