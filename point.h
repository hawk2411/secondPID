
#ifndef __RCPOINT_H__
#define __RCPOINT_H__

#include <QtCore/QPointF>

class RCPoint : public QPointF
{
public:
    RCPoint();
    RCPoint( const QPointF& pt );
    RCPoint( const RCPoint& pt );
    RCPoint( qreal, qreal, qreal );

    ~RCPoint();
    
    void setZ( qreal z){m_z = z;}
    qreal z()const{ return m_z; }

    double getLength()const;

    double getDistance( const QPointF& pt )const;
    double getDistance( const RCPoint& pt )const;

    RCPoint getDirection( const QPointF& pt)const;
    RCPoint getDirection( const RCPoint& pt)const;

    bool operator!= ( const RCPoint & p1 )const; 
    bool operator!= (const QPointF &p1 )const;
    RCPoint & operator*= ( qreal factor );
    RCPoint & operator+= ( const RCPoint & point );
    RCPoint & operator-= ( const RCPoint & point );
    RCPoint & operator/= (qreal divisor );
    qreal operator*(const RCPoint& p1)const;
    RCPoint crossProduct(const RCPoint& p1)const;
/*


QPointF & operator/= ( qreal divisor )
    const QPointF operator* ( const QPointF & point, qreal factor );
    const QPointF operator* ( qreal factor, const QPointF & point );
    const QPointF operator+ ( const QPointF & p1, const QPointF & p2 );
    const QPointF operator- ( const QPointF & p1, const QPointF & p2 );
    const QPointF operator- ( const QPointF & point );
    const QPointF operator/ ( const QPointF & point, qreal divisor );
    QDataStream & operator<< ( QDataStream & stream, const QPointF & point );
    bool operator== ( const QPointF & p1, const QPointF & p2 );
    QDataStream & operator>> ( QDataStream & stream, QPointF & point );
*/
protected:

private:
    qreal m_z;
};

#endif //__RCPOINT_H__
