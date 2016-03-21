#ifndef __RCGRAPHICSTREEVIEW_H__
#define __RCGRAPHICSTREEVIEW_H__

#include <QTreeView>
#include "graphicsitem.h"

class GraphicsTreeView : public QTreeView
{
	Q_OBJECT
public:
    GraphicsTreeView(QWidget * parent = 0);
    ~GraphicsTreeView();

protected:
private:
	enum TreeViewRoles
	{
		MyClassRole = Qt::UserRole + 1

	};

public slots:
    void on_RemoveRCGraphicsItem( GraphicsItem*);
    void on_NewRCGraphicsItem( GraphicsItem*);
};

#endif //__RCGRAPHICSTREEVIEW_H__
