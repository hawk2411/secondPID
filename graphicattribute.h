#ifndef __RCGRAPHICATTRIBUTE_H__
#define __RCGRAPHICATTRIBUTE_H__

#include <QtCore/QString>
#include <QtCore/QVariant>

class GraphicAttribute
{
public:
    GraphicAttribute();
    ~GraphicAttribute();

    void setName( const QString& newName){ m_Name = newName;}
    void setDescription( const QString& newDescription){ m_Description = newDescription; }
    void setLabel( const QString& newLabel ){ m_Label = newLabel; }
    void setValue( const QVariant& newValue){ m_Value = newValue; }

    QString getName()const{ return m_Name; }
    QString getDescription()const{ return m_Description;}
    QString getLabel()const{ return m_Label; }
    QVariant getValue()const{ return m_Value; }

protected:

private:
    QString m_Name;
    QString m_Description;
    QString m_Label;
    QVariant m_Value;
};

#endif //__RCGRAPHICATTRIBUTE_H__
