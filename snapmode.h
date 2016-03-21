#ifndef __RCSNAPMODE_H__
#define __RCSNAPMODE_H__

#include <QtCore/QString>
#include <QtCore/QPointF>

class GraphicsScene;
class QGraphicsItem;
class QListWidgetItem;
/*!
  RCSnapMode
  base class for snap mode. The prefix of derived classes is RCSM (SnapMode).
 */
class SnapMode
{
public:
    SnapMode();
    ~SnapMode();

    virtual QString getDescription()const{ return m_Description; }
    virtual void setDescription( const QString& sNewDescription);

    virtual QPointF getSnapPoint( GraphicsScene *, const QPointF& not_aligned_pt );
    
    virtual QGraphicsItem* getSign()const{ return m_SnappingSign; }
    /**
       prototype function for setting feedback sign of an aligned point
     */
    virtual void setSign( GraphicsScene*, const QPointF& ){ /*do nothing */}
    virtual void removeSign();
    QListWidgetItem * getListItem()const;
protected:
    QGraphicsItem * m_SnappingSign;  /**< if a derived class needs a feedback sign, it will be stored here */
    QListWidgetItem *m_ListItem; /**< the visible part of a snapmode */
    QString m_Description; /**< this value will be seen in the combobox of snapmodes */    
private:

    
    
};

#endif //__RCSNAPMODE_H__
