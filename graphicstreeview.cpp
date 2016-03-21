#include <QtCore/QModelIndex>
#include <QtCore/qvariant.h>
#include <QtGui/QStandardItemModel>

#include "graphicstreeview.h"


/*
	constructor /destructor
*/
GraphicsTreeView::GraphicsTreeView(QWidget * parent)
    :QTreeView(parent)
{
	QStandardItemModel *graphicsItemModel = new QStandardItemModel;

	graphicsItemModel->insertRow(0); //, parent_index);
	graphicsItemModel->insertColumn(0); //, parent_index);

	QModelIndex parent_index= graphicsItemModel->index(0, 0);
	graphicsItemModel->setData(parent_index, "graphic items");
	//QModelIndex parent_index = graphicsItemModel->index(0, 0);
	graphicsItemModel->insertColumn(0, parent_index);

	setModel(graphicsItemModel);

	//connect(m_pGraphicsTreeView, SIGNAL(clicked(QModelIndex)), this, SLOT(clicked(QModelIndex)));

}
GraphicsTreeView::~GraphicsTreeView()
{
	//TODO set model must be deleted
	QAbstractItemModel* currentModel = model();
	delete currentModel;
}

void GraphicsTreeView::on_NewRCGraphicsItem( GraphicsItem* newItem)
{
	QAbstractItemModel* graphicsItemModel = model();
	if( graphicsItemModel != NULL )
	{
		

		QModelIndex parent_index = graphicsItemModel->index(0, 0);

		if( !graphicsItemModel->hasChildren(parent_index) )
		{
			graphicsItemModel->insertRow(0, parent_index );
		}
		else
		{
			graphicsItemModel->insertRow(graphicsItemModel->rowCount(parent_index), parent_index );
		}

		int colCount = graphicsItemModel->columnCount(parent_index);
		int rowCount = graphicsItemModel->rowCount(parent_index);

		QModelIndex last_child_index = parent_index.child(rowCount-1,colCount-1 ); //get the last child
		if( last_child_index.isValid() )
		{

			QString s; s.setNum(rowCount);
			long pointer = (long)newItem;
			QVariant data = qVariantFromValue(pointer);
			graphicsItemModel->setData(last_child_index, data, GraphicsTreeView::MyClassRole);
			graphicsItemModel->setData(last_child_index, qVariantFromValue(newItem->getType()), Qt::DisplayRole);

		}
	}
}

void GraphicsTreeView::on_RemoveRCGraphicsItem( GraphicsItem* removedItem)
{
	qDebug( "ready for remove\n" );
	//ok, eine billige L�sung, sequentielles Suchen im Baum nach item
	QAbstractItemModel* graphicsItemModel = model();
	QModelIndex parent_index = graphicsItemModel->index(0, 0);
	if( !graphicsItemModel->hasChildren(parent_index) )
	{
		return;
	}

	int colCount = graphicsItemModel->columnCount(parent_index);
	int rowCount = graphicsItemModel->rowCount(parent_index);

	for( int i = 0; i < rowCount; i++ )
	{
		QModelIndex index = parent_index.child( i, colCount-1);
		
		QVariant data = index.data(GraphicsTreeView::MyClassRole);
		GraphicsItem* item = (GraphicsItem*)data.value<long>();
		if( item == removedItem )
		{
			graphicsItemModel->removeRow(index.row(), parent_index);
		}
	}
}
