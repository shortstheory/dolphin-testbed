/***************************************************************************
 *   Copyright (C) 2010 by Peter Penz <peter.penz19@gmail.com>             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA            *
 ***************************************************************************/

#include "dolphindockwidget.h"

#include <QStyle>

namespace {
    // Disable the 'Floatable' feature, i.e., the possibility to drag the
    // dock widget out of the main window. This works around problems like
    // https://bugs.kde.org/show_bug.cgi?id=288629
    // https://bugs.kde.org/show_bug.cgi?id=322299
    const QDockWidget::DockWidgetFeatures DefaultDockWidgetFeatures = QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable;
}

 // Empty titlebar for the dock widgets when "Lock Layout" has been activated.
class DolphinDockTitleBar : public QWidget
{
    Q_OBJECT

public:
    DolphinDockTitleBar(QWidget* parent = 0) : QWidget(parent) {}
    virtual ~DolphinDockTitleBar() {}

    virtual QSize minimumSizeHint() const
    {
        const int border = style()->pixelMetric(QStyle::PM_DockWidgetTitleBarButtonMargin);
        return QSize(border, border);
    }

    virtual QSize sizeHint() const
    {
        return minimumSizeHint();
    }
};

DolphinDockWidget::DolphinDockWidget(const QString& title, QWidget* parent, Qt::WindowFlags flags) :
    QDockWidget(title, parent, flags),
    m_locked(false),
    m_dockTitleBar(0)
{
    setFeatures(DefaultDockWidgetFeatures);
}

DolphinDockWidget::DolphinDockWidget(QWidget* parent, Qt::WindowFlags flags) :
    QDockWidget(parent, flags),
    m_locked(false),
    m_dockTitleBar(0)
{
    setFeatures(DefaultDockWidgetFeatures);
}

DolphinDockWidget::~DolphinDockWidget()
{
}

void DolphinDockWidget::setLocked(bool lock)
{
    if (lock != m_locked) {
        m_locked = lock;

        if (lock) {
            if (!m_dockTitleBar) {
                m_dockTitleBar = new DolphinDockTitleBar(this);
            }
            setTitleBarWidget(m_dockTitleBar);
            setFeatures(QDockWidget::NoDockWidgetFeatures);
        } else {
            setTitleBarWidget(0);
            setFeatures(DefaultDockWidgetFeatures);
        }
    }
}

bool DolphinDockWidget::isLocked() const
{
    return m_locked;
}

#include "dolphindockwidget.moc"
