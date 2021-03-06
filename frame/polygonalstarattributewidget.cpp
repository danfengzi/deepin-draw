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
#include "polygonalstarattributewidget.h"

#include <DLabel>
//#include <DFontSizeManager>

#include <QHBoxLayout>
#include <QButtonGroup>
#include <QIntValidator>
#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include <QAction>

#include "widgets/toolbutton.h"
#include "widgets/bigcolorbutton.h"
#include "widgets/bordercolorbutton.h"
#include "widgets/seperatorline.h"
#include "widgets/csidewidthwidget.h"
#include "utils/cvalidator.h"
#include "drawshape/cdrawparamsigleton.h"
#include "frame/cviewmanagement.h"
#include "frame/cgraphicsview.h"

const int BTN_SPACING = 5;
const int SEPARATE_SPACING = 4;
const int TEXT_SIZE = 12;
PolygonalStarAttributeWidget::PolygonalStarAttributeWidget(DWidget *parent)
    : DWidget(parent)
{
    initUI();
    initConnection();
}

PolygonalStarAttributeWidget::~PolygonalStarAttributeWidget()
{

}

void PolygonalStarAttributeWidget::changeButtonTheme()
{
    m_sideWidthWidget->changeButtonTheme();
    m_sepLine->updateTheme();
}

void PolygonalStarAttributeWidget::initUI()
{
    m_fillBtn = new BigColorButton( this);

    QFont ft;
    ft.setPixelSize(TEXT_SIZE);

    m_strokeBtn = new BorderColorButton(this);

    m_sepLine = new SeperatorLine(this);
    DLabel *lwLabel = new DLabel(this);
    lwLabel->setText(tr("Width"));
    QFont ft1;
    ft1.setPixelSize(TEXT_SIZE - 1);
    lwLabel->setFont(ft1);

    m_sideWidthWidget = new CSideWidthWidget(this);


    DLabel *anchorNumLabel = new DLabel(this);
    anchorNumLabel->setText(tr("Points"));
    anchorNumLabel->setFont(ft1);
    m_anchorNumber = new DSpinBox(this);
    m_anchorNumber->setFixedSize(QSize(100, 36));
    m_anchorNumber->setRange(3, 50);

    DLabel *radiusLabel = new DLabel(this);
    radiusLabel->setText(tr("Diameter"));
    radiusLabel->setFont(ft1);
    m_radiusNumber = new DSpinBox(this);
    m_radiusNumber->setRange(0, 100);
    m_radiusNumber->setFixedSize(QSize(100, 36));
    m_radiusNumber->setSuffix("%");

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->addStretch();
    layout->addWidget(m_fillBtn);
    layout->addSpacing(SEPARATE_SPACING);
    layout->addWidget(m_strokeBtn);
    layout->addSpacing(SEPARATE_SPACING);
    layout->addWidget(m_sepLine);
    layout->addSpacing(SEPARATE_SPACING);
    layout->addWidget(lwLabel);
    layout->addWidget(m_sideWidthWidget);
    layout->addSpacing(SEPARATE_SPACING);
    layout->addWidget(anchorNumLabel);
    layout->addWidget(m_anchorNumber);
    layout->addSpacing(SEPARATE_SPACING);
    layout->addWidget(radiusLabel);
    layout->addWidget(m_radiusNumber);

    layout->addStretch();
    setLayout(layout);
}

void PolygonalStarAttributeWidget::initConnection()
{
    connect(m_fillBtn, &BigColorButton::btnCheckStateChanged, this, [ = ](bool show) {
        m_strokeBtn->resetChecked();
        emit showColorPanel(DrawStatus::Fill, getBtnPosition(m_fillBtn), show);

    });
    connect(m_strokeBtn, &BorderColorButton::btnCheckStateChanged, this, [ = ](bool show) {
        m_fillBtn->resetChecked();
        emit showColorPanel(DrawStatus::Stroke,  getBtnPosition(m_strokeBtn), show);
    });

    connect(this, &PolygonalStarAttributeWidget::resetColorBtns, this, [ = ] {
        m_fillBtn->resetChecked();
        m_strokeBtn->resetChecked();
    });


    ///线宽
    connect(m_sideWidthWidget, &CSideWidthWidget::signalSideWidthChange, this, [ = ] () {
        emit signalPolygonalStarAttributeChanged();
    });
    connect(m_sideWidthWidget, &CSideWidthWidget::signalSideWidthMenuShow, this, [ = ] () {
        //隐藏调色板
        showColorPanel(DrawStatus::Stroke, QPoint(), false);
    });

    //锚点数
    connect(m_anchorNumber, SIGNAL(valueChanged(int)), this, SLOT(slotAnchorvalueChanged(int)));

    //半径
    connect(m_radiusNumber, SIGNAL(valueChanged(int)), this, SLOT(slotRadiusvalueChanged(int)));

    // 锚点数
    m_anchorNumber->setValue(5);
    m_radiusNumber->setValue(50);
}

void PolygonalStarAttributeWidget::updatePolygonalStarWidget()
{
    m_fillBtn->updateConfigColor();
    m_strokeBtn->updateConfigColor();
    m_sideWidthWidget->updateSideWidth();

    int anchorNum = CManageViewSigleton::GetInstance()->getCurView()->getDrawParam()->getAnchorNum();

    if (anchorNum != m_anchorNumber->value()) {
        m_anchorNumber->setValue(anchorNum);
    }

    int radiusNum = CManageViewSigleton::GetInstance()->getCurView()->getDrawParam()->getRadiusNum();

    if (radiusNum != m_radiusNumber->value()) {
        m_radiusNumber->setValue(radiusNum);
    }
}

void PolygonalStarAttributeWidget::slotAnchorvalueChanged(int value)
{
    CManageViewSigleton::GetInstance()->getCurView()->getDrawParam()->setAnchorNum(value);
    emit signalPolygonalStarAttributeChanged();
    //隐藏调色板
    showColorPanel(DrawStatus::Stroke, QPoint(), false);
}

void PolygonalStarAttributeWidget::slotRadiusvalueChanged(int value)
{
    CManageViewSigleton::GetInstance()->getCurView()->getDrawParam()->setRadiusNum(value);
    emit signalPolygonalStarAttributeChanged();
    //隐藏调色板
    showColorPanel(DrawStatus::Stroke, QPoint(), false);
}

QPoint PolygonalStarAttributeWidget::getBtnPosition(const DPushButton *btn)
{
    QPoint btnPos = mapToGlobal(btn->pos());
    QPoint pos(btnPos.x() + btn->width() / 2,
               btnPos.y() + btn->height());

    return pos;
}
