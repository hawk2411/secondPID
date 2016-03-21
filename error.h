#ifndef __RCERROR_H__
#define __RCERROR_H__

#include <QtCore/QString>

#define ERR_PARAM_NOT_VALID 1
#define ERR_PARENT_NOT_VALID 2
#define ERR_MEMORY 3

class RCError
{
public:
    RCError();
    RCError(int number, const QString& description = "" );
    ~RCError();
    
    inline void setNumber(int number){ m_number = number; }
    inline void setDescription( const QString& str ){ m_description = str; }
    void print()const;
protected:
    
private:
    int m_number;
    QString m_description;
};

#endif //__RCERROR_H__
