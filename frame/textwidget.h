/*
 * Copyright (C) 2019 ~ %YEAR% Deepin Technology Co., Ltd.
 *
 * Author:     Renran
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
#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H
#include "drawshape/globaldefine.h"
#include "widgets/cfontcombobox.h"

#include <DWidget>
#include <DComboBox>
#include <DSpinBox>

DWIDGET_USE_NAMESPACE

class TextColorButton;
class SeperatorLine;

class TextWidget : public DWidget
{
    Q_OBJECT
public:
    TextWidget(DWidget *parent = nullptr);
    ~TextWidget();

public slots:
    /**
     * @brief updateTextWidget 更新属性栏
     */
    void updateTextWidget();
    /**
     * @brief updateTextColor　跟新文字颜色
     */
    void updateTextColor();
    /**
     * @brief updateTheme　更新主题
     */
    void updateTheme();
    /**
     * @brief slotFontSizeValueChanged　字体大小改变
     */
    void slotFontSizeValueChanged(int size);

signals:
    /**
     * @brief showColorPanel　显示调色板信号
     * @param drawstatus　颜色状态
     * @param pos　位置
     * @param visible　是否显示
     */
    void showColorPanel(DrawStatus drawstatus, QPoint pos, bool visible = true);
    /**
     * @brief resetColorBtns　重置颜色按钮
     */
    void resetColorBtns();
    /**
     * @brief signalTextAttributeChanged 属性变化信号
     */
    void signalTextAttributeChanged();
    /**
     * @brief signalTextFontFamilyChanged　字体改变信号
     */
    void signalTextFontFamilyChanged();
    /**
     * @brief signalTextFontSizeChanged　字体大小改变信号
     */
    void signalTextFontSizeChanged();

private:
    TextColorButton *m_fillBtn;
    CFontComboBox *m_fontComBox;
    SeperatorLine *m_textSeperatorLine;
    DComboBox *m_fontHeavy; // 字体的重量
    DSpinBox *m_fontSize; // 字体的大小

    QString m_oriFamily;
    bool m_bSelect;

private:
    /**
     * @brief initUI 初始化ＵＩ
     */
    void initUI();
    /**
     * @brief initConnection 初始化连接
     */
    void initConnection();
};

#endif // TEXTWIDGET_H
