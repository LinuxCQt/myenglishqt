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

#ifndef DialogExamen_H
#define DialogExamen_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QByteArray>
#include <QTextToSpeech>

namespace Ui {
class DialogExamen;
}

class DialogExamen : public QDialog
{
    Q_OBJECT

    QString fileNameTest;

public:
    explicit DialogExamen(QString fileTest, QWidget *parent = nullptr);
    ~DialogExamen();

private slots:
    void on_pushButtonCheck_clicked();
    void on_pushButtonExit_clicked();
    void on_pushButtonSound_clicked();
    void on_pushButtonDificult_clicked();
    void on_pushButtonEsay_clicked();

private:
    QSqlDatabase db;
    QSqlQuery *query;

    QTextToSpeech *speech;

    QString answer;

    void funSound();
    void funShowFicha();
    void funNext();
    void funSaveAvances( int avancesDificultOrEasy );

    Ui::DialogExamen *ui;
};

#endif // DialogExamen_H
