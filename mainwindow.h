#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <QModelIndex>
#include "snapmodes.h"


namespace Ui
{
    class MainWindowClass;
}
class GraphicsView;
class GraphicsTreeView;
class GraphicsScene;
class QStandardItemModel;
class GraphicsItem;
class RCSnapModes;
class QLabel;



/*! \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 \subsection todo_sec Todo
 Weiter mit der Klasse RCSMLineEnd. Vielleicht sollte sie jedoch RCSMNodeEnd heißen, da nicht nur an Linienenden gesnapped wird, sondern auch an Kanten eines Rechtecks oder eines eckigen Polygons. Der Prototyp steht schon, was fehlt ist eine Eintragung in RCSnapModes und natürlich die Implementierung von getAlignedPoint.

 \subsection finished_sec Finished
 Die Klasse RCSnapModes muss ausgebaut werden. Im Konstruktor müssen alle unterstützende RCSnapMode Klassen kreiert und in den Vector oder noch besser in eine Map eingebaut werden. 
Die RCGraphicsItemCreator Klassen müssen an diese Änderung angepasst werden.

\subsection snapmodes_sec SnapModes
 MainWindow erstellt RCSnapModes. In RCSnapModes wird eine QListWidget erstellt und in bool fillSnapModes gefüllt. RCSnapModes erstellt alle verfügbare RCSnapMode Klassen und speichert sie ein Array. Die ComboBox wird von MainWindow in ToolBar eigefügt. Das CreationItem fragt bei der Scene mit getAlignedPoint nach. Dir RCGraphicsScene hat als Member m_SnapModes und die wiederum hat eine Funktion namens: getAlignedPoint.
 *  
 * etc...
 \htmlinclude notes.html
**/



/*! MainWindow
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
       initialize all member and visible widgets
     */
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindowClass* getUI(){return m_ui;}
private:
    //private members
    Ui::MainWindowClass *m_ui;
    QLabel m_orthCoordinate;
    QLabel m_polarCoordinate;
    GraphicsView *m_pGraphicsView; /**< overwrites the default behavior of QGraphicsView */
    GraphicsTreeView *m_pGraphicsTreeView; /**< overwrites the default behavior of QTreeView */
    GraphicsScene *m_pScene; /**< overwrites the default behavior of QGraphicsScene */
    
    //private functions
    long synchronizeToolBar( QToolBar * pToSynchronize, QAction * pTriggered );
    //protected members
protected:
    //QAction *m_snapshots_action; /**< repesents a combobox which is visible in the toolbar if selection of different snap modes is useful*/
    

private slots:
    void on_actionAddLine_triggered();
    void on_actionSelectGraphObject_triggered();
    void on_actionAddCircle_triggered();
    void on_actionAddRectangle_triggered();
    void on_actionScalePlus_triggered();
    void on_actionScaleMinus_triggered();
    void on_actionAddText_triggered();
	//void clicked( const QModelIndex& index);
//    void on_currentIndexChanged(int);

public slots:
    void on_showCoordinate( const QPointF& pt );
};

#endif // MAINWINDOW_H
