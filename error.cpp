#include "error.h"


/*
	constructor /destructor
*/
RCError::RCError()
{
    
}
RCError::RCError(int number, const QString& description )
{
    m_number = number;
    m_description = description;
}
RCError::~RCError()
{

}


void RCError::print()const
{
  //qDebug( "error number %d, error description <%s>", m_number, m_description );
}
