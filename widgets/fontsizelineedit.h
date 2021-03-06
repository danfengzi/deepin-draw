/*
 * Copyright (C) 2019 ~ %YEAR% Deepin Technology Co., Ltd.
 *
 * Author:     RenRan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef FONTSIZELINEEDIT_H
#define FONTSIZELINEEDIT_H

#include <QLineEdit>
#include <QShortcut>
#include <QKeyEvent>
#include <QDebug>
#include <DWidget>

DWIDGET_USE_NAMESPACE

class FontsizeLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    FontsizeLineEdit(DWidget *parent = 0)
    {
        Q_UNUSED(parent);
    }
    ~FontsizeLineEdit() {}

signals:
    void addSize();
    void reduceSize();

protected:
    void keyPressEvent(QKeyEvent *e)
    {
        if (e->key() == Qt::Key_Up) {
            emit addSize();
        } else if (e->key() == Qt::Key_Down) {
            emit reduceSize();
        } else if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
            emit editingFinished();
        }

        QLineEdit::keyPressEvent(e);
    }

};
#endif // FONTSIZELINEEDIT_H
