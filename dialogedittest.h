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

#ifndef DIALOGEDITTEST_H
#define DIALOGEDITTEST_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace Ui {
class DialogEditTest;
}

class DialogEditTest : public QDialog
{
    Q_OBJECT

    QString fileNameTest;

public:
    explicit DialogEditTest(QString fileTest, QWidget *parent = nullptr);
    ~DialogEditTest();

private slots:
    void on_pushButtonSaveAndExit_clicked();
    void on_DialogEditTest_rejected();
    void on_pushButtonAddRow_clicked();
    void on_pushButtonRemoveRow_clicked();
    void resizeEvent(QResizeEvent *e);

    void funSlotButtonsImage();

private:
    QSqlDatabase db;
    QSqlTableModel *model;

    void funShow();
    void funCreateButtonsImage();
    QString funGetFileName();
    void funConnectBD();
    void funResize();

    Ui::DialogEditTest *ui;
};

#endif // DIALOGEDITTEST_H
