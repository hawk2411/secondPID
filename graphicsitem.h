#ifndef __RCGRAPHICSITEM_H__
#define __RCGRAPHICSITEM_H__

#include <QMetaType>
#include <QGraphicsItem>
#include <QUuid>

#include "global_defs.h"
#include "smgridaligned.h"


/** Basisklasse für alle Klassen, die Prototypen für's Berechnen der Schnappunkten liefern.
 * 
 * 
 */
class Snap
{
public:
    Snap(){ m_snapDistance = DEF_SNAP_WIDTH; }

    void setSnapDistance( qreal newSnapDistance){ m_snapDistance = newSnapDistance; }
    qreal getSnapDisctance()const{ return m_snapDistance; }
protected:
    qreal m_snapDistance; /*!< wie nah darf der Zeichencursor an einer Kante sein, damit er einrastet.*/
    
};
/*! \brief Prototyp Klasse für das Berechnen von Schnappunkten
 *
 * Alle RCGraphicsItem oder davon abgeleiteten Klassen sollten, wenn sie das Einschnappen an Kanten oder an Mittelpunkten der Linien anbieten wollen, von dieser Klasse ableiten.
 */
class EdgeSnap : public Snap
{
public:
    /*! \brief wird von RCSMLineEnde aufgerufen
     *
     * Diese Funktion muss von ableitenden Klassen implementiert werden.
     * \param [in] ptIn QPointF die Position des Zeichencursors
     * \param [out] ptOut QPointF die Schnappposition
     * \return true falls eine Schnappposition gefunden wird, sonst false.
     */
    virtual bool getNearestEdgePoint(const QPointF& ptIn, QPointF& ptOut )const=0; 
};

/** \brief Prototypklasse fürs Berechnen von Schnapppunkten an Linien 
 * 
 * Alle RCGraphicsItem oder davon abgeleiteten Klassen sollten, wenn sie das Einschnappen an Linien anbieten wollen, von dieser Klasse ableiten.
 * 
 */
class LineSnap : public Snap
{
public:
    /** 
     * 
     * 
     * @param ptIn Position des Zeichencursors
     * @param ptOut Positions des Snappunktes, gültig nur wenn die Funktion true liefert
     * 
     * @return true wenn eine Linie innerhalb der Snapdistanz sich befindet
     */
    virtual bool getNearestLinePoint(const QPointF& ptIn, QPointF& ptOut)const=0;
};

/*! \brief base class for all rc graphic item.
 *
 * this class itself derived from QGraphicsItem and provides some expedient 
 * functions for my program
 */
class GraphicsItem : public QGraphicsItem
{
public:
    GraphicsItem(QGraphicsItem * parent = 0, QGraphicsScene * scene = 0 );
    ~GraphicsItem();

    //overloaded functions
    
    //void contextMenuEvent(QGraphicsSceneContextMenuEvent *event)=0;
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
    ///derived from QGraphicsItem
    bool collidesWithPath ( const QPainterPath & path, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape ) const;
    
    //member access functions
	virtual QString getType()const{ return m_sType; }
    
	virtual mouse_points_t getCenterNodes()const;
    /**in base class returns a empty vector. the points are necessary for snapping on nodes
     *
     *the derived classes should override this function returning their required snapping points
     */
    virtual mouse_points_t getNodes()const;
   
    //protected members
protected:
	QString		m_sType;	//< apparently required for GUI labels and so.
	QUuid		m_id;		
    
private:
    
};

struct VariantType
{
    QString sText;
    GraphicsItem * pPointer;
};

Q_DECLARE_METATYPE(VariantType);
#endif //__RCGRAPHICSITEM_H__
