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

#ifndef DIALOGALFABETO_H
#define DIALOGALFABETO_H

#include <QDialog>

namespace Ui {
class DialogAlfabeto;
}

class DialogAlfabeto : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAlfabeto(QWidget *parent = nullptr);
    ~DialogAlfabeto();

private slots:
    void on_pushButtonA_clicked();
    void on_pushButtonB_clicked();
    void on_pushButtonC_clicked();
    void on_pushButtonD_clicked();
    void on_pushButtonE_clicked();
    void on_pushButtonF_clicked();
    void on_pushButtonG_clicked();
    void on_pushButtonI_clicked();
    void on_pushButtonH_clicked();
    void on_pushButtonJ_clicked();
    void on_pushButtonK_clicked();
    void on_pushButtonL_clicked();
    void on_pushButtonM_clicked();
    void on_pushButtonN_clicked();
    void on_pushButtonO_clicked();
    void on_pushButtonP_clicked();
    void on_pushButtonQ_clicked();
    void on_pushButtonR_clicked();
    void on_pushButtonS_clicked();
    void on_pushButtonT_clicked();
    void on_pushButtonU_clicked();
    void on_pushButtonV_clicked();
    void on_pushButtonW_clicked();
    void on_pushButtonX_clicked();
    void on_pushButtonY_clicked();
    void on_pushButtonZ_clicked();
    void on_pushButtonNex_clicked();
    void on_pushButtonSound_clicked();

private:
    Ui::DialogAlfabeto *ui;

    QString letraCorrecta;

    void funSound();
    void funComprobar(QString cadLetraPulsada);
    void funBotones(bool resultado);
    void funShow();
};

#endif // DIALOGALFABETO_H
