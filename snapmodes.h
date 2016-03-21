#ifndef __RCSNAPMODES_H__
#define __RCSNAPMODES_H__

#include <QObject>
#include <QHash>
#include <QPointF>


class SnapMode;
class QListWidget;
class GraphicsScene;

/*! hash table keys for snap modes
 */
enum SnapModes
{
    snap_by_grid=1,
    snap_by_line_end,
    snap_by_item
};

typedef QHash<SnapModes, SnapMode*> supported_snapmodeclasses_t;
/*!
   RCSnapModes
   try manage all snap modes in this class. For the first I need a function to get a description for an integer value of a snap mode
*/
class RCSnapModes : public QObject
{
    Q_OBJECT
public:
    /*! 
      gathers all known RCSnapMode 
     */
    RCSnapModes(QWidget *parent);
    ~RCSnapModes();
    
//    QWidget * getWidget()const{ return (QWidget*)m_SnapModeWidget; }
    //void setWidget( QComboBox*);

    //bool fillSnapModes( const supported_snapmodes_t& showSnapModes );
    //RCSnapMode* getUserSelectedSnapMode();
    QPointF getSnapPoint( GraphicsScene *, const QPointF& not_aligned_pt );
    void setSigns();
    void removeSigns()const;
protected:
private:
    supported_snapmodeclasses_t m_snapmodes;
    ///hier werden alle bekannten Snapmodes dargestellt
    QListWidget* m_SnapModeWidget;
    SnapMode * m_current_snapmode;
	//void currentSn
signals:
    void currentSnapModeChanged( SnapMode* );
};

#endif //__RCSNAPMODES_H__
