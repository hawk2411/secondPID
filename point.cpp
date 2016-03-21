#include <math.h>

#include "error.h"
#include "point.h"


/*
	constructor /destructor
*/
RCPoint::RCPoint()
{
    m_z=0.0;
}

RCPoint::RCPoint( const QPointF& pt )
    :QPointF(pt)
{
    m_z=0.0;
}

RCPoint::RCPoint( const RCPoint& pt )
    :QPointF(dynamic_cast<const QPointF&>(pt) )
{
    m_z=pt.z();
}

RCPoint::RCPoint( qreal x, qreal y, qreal z )
    :QPointF(x, y)
{
    m_z = z;
}

RCPoint::~RCPoint()
{

}

double RCPoint::getLength()const
{
    return sqrt(x() * x() + y() * y() + m_z * m_z);
}

double RCPoint::getDistance( const QPointF& pt )const
{
    double dx = pt.x() - x();
    double dy = pt.y() - y();
    double dz = -m_z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}

double RCPoint::getDistance( const RCPoint& pt )const
{
    double dx = pt.x() - x();
    double dy = pt.y() - y();
    double dz = pt.z() - m_z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}


RCPoint RCPoint::getDirection( const QPointF& pt)const
{
    RCPoint pt1 = operator-(*this, pt); //z is null
    
    double len = pt1.getLength();
    pt1.setX( pt1.x() / len );
    pt1.setY( pt1.y() / len );
    //it's no worth for z
    return pt1;
}

RCPoint RCPoint::getDirection( const RCPoint& pt)const
{
    RCPoint pt1 = operator-(*this, pt);
    pt1.setZ( m_z - pt.z() );

    double len = pt1.getLength();
    pt1.setX( pt1.x() / len );
    pt1.setY( pt1.y() / len );
    pt1.setZ( pt1.z() / len );

    return pt1;
}
bool RCPoint::operator!=( const RCPoint & p1 )const
{
    if( (p1.x() == this->x()) && ( p1.y() == this->y() ) && (p1.z() == this->z() ) )
	return false;

    return true;
}

bool RCPoint::operator!= (const QPointF &p1 )const
{
    if( (m_z == 0.0) && (x() == p1.x()) && (y() == p1.y() ) )
	return false;

    return true;
}
RCPoint & RCPoint::operator*= ( qreal factor )
{
    *this =QPointF::operator*=(factor);
    m_z = m_z * factor;
	
    return *this;
}
RCPoint & RCPoint::operator+= ( const RCPoint & point )
{
    *this = QPointF::operator+=(point);
    m_z += point.z();
    return *this;
}

RCPoint & RCPoint::operator-= ( const RCPoint & point )
{
    *this = QPointF::operator-=(point);
    m_z -= point.z();
    return *this;
}

RCPoint & RCPoint::operator/= (qreal divisor )
{
    if( divisor == 0.0 )
	throw RCError(0, "divison null");
    *this = QPointF::operator/=( divisor );
    m_z /= divisor;

    return *this;
}
qreal RCPoint::operator*(const RCPoint& p1)const
{
    qreal ret_val;
    ret_val = p1.x()*this->x()+p1.y()*this->y()+p1.z()*this->z();
	return ret_val;
}

RCPoint RCPoint::crossProduct(const RCPoint& p1)const
{
    RCPoint result;

    result.setX( this->y()*p1.z() - this->z()*p1.y() );
    result.setY( this->z()*p1.x() - this->x()*p1.z() );
    result.setZ( this->x()*p1.y() - this->y()*p1.x() );

    return result;
}

/*
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
