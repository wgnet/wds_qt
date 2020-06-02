/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef PatternistSDK_TreeItem_H
#define PatternistSDK_TreeItem_H

#include <QObject>

#include "Global.h"

QT_BEGIN_NAMESPACE

class QVariant;
template<typename T> class QList;
template<typename T> class QPointer;

namespace QPatternistSDK
{
    /**
     * @short TreeItem is a node in a hierachial structure and is used together
     * with TreeModel.
     *
     * TreeItem is abstract base class. Instances of sub-classes of TreeItem
     * can be used with TreeModel in order to use hierarchial data in Qt's
     * model/view framework.
     *
     * TreeItem is a QObject in order to be able to be used with QPointer.
     *
     * @author Frans Englich <frans.englich@nokia.com>
     * @see TreeModel
     * @ingroup PatternistSDK
     */
    class Q_PATTERNISTSDK_EXPORT TreeItem : public QObject
    {
        Q_OBJECT
    public:
        typedef QList<QPointer<TreeItem> > List;

        virtual ~TreeItem() {}
        virtual void appendChild(TreeItem *item) = 0;
        virtual TreeItem *child(const unsigned int row) const = 0;
        virtual unsigned int childCount() const = 0;
        virtual TreeItem *parent() const = 0;

        virtual TreeItem::List children() const = 0;
        virtual int columnCount() const = 0;

        /**
         * Determines the position among the children of
         * this TreeItem's parent. This is done by introspecting the result
         * of children().
         */
        int row() const;

        virtual QVariant data(const Qt::ItemDataRole role, int column) const = 0;

        static QPair<int,int> executeRange;
        static int executions;

    Q_SIGNALS:
        /**
         * Emitted whenever this item changed. This is used for keeping
         * views in synchronization with the item model which houses
         * this item.
         *
         * @param item the item which changed. That is, this TreeItem.
         */
        void changed(TreeItem *item);
    };
}

QT_END_NAMESPACE

#endif
// vim: et:ts=4:sw=4:sts=4
