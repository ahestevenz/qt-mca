/**
 * @class MainWindow
 *
 * @brief Clase de entorno gráfico
 *
 * Esta clase corresponde al entorno gráfico de la aplicación *qt-mca*
 *
 * Tiene como objetivo realizar el control y mantenimiento del tomógrafo por
 * emisión de positrones AR-PET.
 * Realiza el matenimiento y configuración de varios parámetros del equipo, tales
 * como calibración de los fotomultiplicadores y cabezales, control de temperatura,
 * control de alta tensión y cantidad de cuentas adquiridas en el equipo.
 *
 * @note Utiliza la clase MCAE para la comunicación con el ARPET.
 *
 * @note Clase heredada de QMainWindow
 *
 * @author Ariel Hernández
 *
 * @version $Version
 *
 * Contacto: ahernandez@cae.cnea.gov.ar
 *
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "SetPreferences.h"
#include "SetPMTs.h"
#include "apMCAE.hpp"
#include <QString>

#define MULTIHEAD 1
#define MONOHEAD 0
#define MULTIMODE 1
#define TEMPERATURE 2
#define MONOMODE 0
#define HEAD 0
#define HEADS 6
#define MIN_TEMPERATURE 20
#define COIN_NORMAL 0
#define COIN_AUTOCOINCIDENCE 1
#define COIN_AVANCED 2
#define COIN_CALIB 3

using namespace ap;

/**
    El Namespace Ui contiene los métodos y propiedades del entorno gráfico de la aplicación qt-mca.
*/
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    /**
     * @brief The temp_code enum
     *
     * Definición de enum utilizado para las escalas de temperatura.
     *
     */
    enum temp_code {TOO_HOT,HOT,WARM,NORMAL,ERROR,NO_VALUE};

public:
    explicit MainWindow(QWidget *parent = 0);
    void checkCombosStatus();
    ~MainWindow();

    /* Area de prueba/testing */

private slots:
    /* Slots de sincronización para QCustomPlot */
    void addPMTGraph(int index,  QCustomPlot *graph, QString graph_legend="", bool head=false);
    void titleDoubleClickPMT(QMouseEvent* event);
    void titleDoubleClickHead(QMouseEvent* event);
    void axisLabelDoubleClickPMT(QCPAxis *axis, QCPAxis::SelectablePart part);
    void axisLabelDoubleClickHead(QCPAxis *axis, QCPAxis::SelectablePart part);
    void legendDoubleClickPMT(QCPLegend *legend, QCPAbstractLegendItem *item);
    void legendDoubleClickHead(QCPLegend *legend, QCPAbstractLegendItem *item);
    void removeSelectedGraphPMT();
    void removeSelectedGraphHead();
    void removeAllGraphsPMT();
    void removeAllGraphsHead();
    void contextMenuRequestPMT(QPoint pos);
    void contextMenuRequestHead(QPoint pos);
    void moveLegendPMT();
    void moveLegendHead();
    void mousePressPMT();
    void mousePressHead();
    void mouseWheelPMT();
    void mouseWheelHead();
    void selectionChangedPMT();
    void selectionChangedHead();
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);

    /* Slots de sincronización en el entorno gráfico */
    void setHeadMode(int index, string tab);
    void setAdvanceCoinMode(int index);
    void setHeadModeConfig(int index);
    void setHeadModeGraph(int index);
    void setAdquireMode(int index);
    void setTabMode(int index);
    void syncHeadComboBoxToMCA(int index);
    void syncHeadModeComboBoxToMCA(int index);
    void syncCheckBoxHead1ToMCA(bool check);
    void syncCheckBoxHead2ToMCA(bool check);
    void syncCheckBoxHead3ToMCA(bool check);
    void syncCheckBoxHead4ToMCA(bool check);
    void syncCheckBoxHead5ToMCA(bool check);
    void syncCheckBoxHead6ToMCA(bool check);
    void syncHeadComboBoxToConfig(int index);
    void syncHeadModeComboBoxToConfig(int index);
    void syncCheckBoxHead1ToConfig(bool check);
    void syncCheckBoxHead2ToConfig(bool check);
    void syncCheckBoxHead3ToConfig(bool check);
    void syncCheckBoxHead4ToConfig(bool check);
    void syncCheckBoxHead5ToConfig(bool check);
    void syncCheckBoxHead6ToConfig(bool check);

    /* Buttons */
    int on_pushButton_conectar_clicked();
    void on_pushButton_triple_ventana_clicked();
    void on_pushButton_hv_clicked();
    void on_pushButton_energia_clicked();
    void on_pushButton_posicion_X_clicked();
    void on_pushButton_posicion_Y_clicked();
    void on_pushButton_obtener_ini_clicked();
    void on_pushButton_tiempos_cabezal_clicked();
    void on_pushButton_initialize_clicked();
    void on_pushButton_configure_clicked();
    void on_pushButton_hv_set_clicked();
    void on_pushButton_hv_on_clicked();
    void on_pushButton_hv_off_clicked();
    void on_pushButton_hv_estado_clicked();
    void on_pushButton_adquirir_clicked();
    void on_pushButton_select_pmt_clicked();
    void on_pushButton_hv_configure_clicked();
    void on_pushButton_l_5_clicked();
    void on_pushButton_l_10_clicked();
    void on_pushButton_l_50_clicked();
    void on_pushButton_p_5_clicked();
    void on_pushButton_p_10_clicked();
    void on_pushButton_p_50_clicked();
    void on_pushButton_reset_clicked();
    void on_pushButton_arpet_on_clicked();
    void on_pushButton_arpet_off_clicked();
    void on_actionPreferencias_triggered();
    void on_pushButton_send_terminal_clicked();
    void on_pushButton_flush_terminal_clicked();
    void on_pushButton_clear_terminal_clicked();
    void on_pushButton_stream_configure_mca_terminal_clicked();
    void on_pushButton_stream_configure_psoc_terminal_clicked();

    /* Buttons de prueba/testing */


private:
    QString openConfigurationFile();
    void getPaths();
    int parseConfigurationFile(QString filename);
    QStringList availablePortsName();
    QString getHead(string tab);
    string initHead(int head);
    string initSP3(int head);
    void setCalibrationTables(int head);
    void setInitialConfigurations();
    void setLabelState(bool state, QLabel *label);
    void setTextBrowserState(bool state, QTextBrowser *tbro);
    void SetButtonState(bool state, QPushButton * button, bool disable=false);
    string readString(char delimeter='\r');
    string readBufferString(int buffer_size);
    size_t sendString(string msg, string end);
    void manageHeadCheckBox(string tab, bool show);
    void manageHeadComboBox(string tab, bool show);
    QString getMCA(string tab, string function, bool multimode, string pmt="0");
    QString getMultiMCA(string tab, bool accum=false);
    QString getHeadMCA(string tab, bool accum);
    void setMCAEDataStream(string tab, string function, string pmt, string mca_function, int bytes_mca=0, string hv_value="");
    void setMCAEDataStream(string tab, string function, string pmt, string mca_function, double time);
    void setMCAEDataStream(string tab, string calib_function, QVector<double> table);
    void setMCAEDataStream(string coin_function, string data_one, string data_two, bool time);
    int setPSOCDataStream(string tab, string function, QString psoc_value="");
    void setPMTCustomPlotEnvironment(QList<QString> qlist);
    void setHeadCustomPlotEnvironment();
    void getHeadPlot(QCustomPlot *graph);
    void getMultiplePlot(QCustomPlot *graph);
    QVector<int> getCustomPlotParameters();
    void SetQCustomPlotConfiguration(QCustomPlot *graph);
    void SetQCustomPlotSlots(string title_pmt_str="", string title_head_str="");
    QString setHV(string tab, string hv_value, string pmt);
    QString setCalibTable(string function, QVector<double> table, string msg_compare);
    QString setTime(string tab, double time_value, string pmt);
    int getPMT(QLineEdit *line_edit);
    QString getPSOCAlta(QLineEdit *line_edit);
    void setPMT(int value);
    string getHVValue(QLineEdit *line_edit, int value=0);
    void resetHitsValues();
    void setQListElements();
    void drawTemperatureBoard();
    void setTemperatureBoard(double temp, QLabel *label_pmt, int pmt);
    void clearTemperatureBoard();
    temp_code getTemperatureCode(double temperature);
    QVector<double> getValuesFromFiles(QString filename, bool hv=false);
    void setCoincidenceModeDataStream(string stream);
    string getCoincidenceAdvanceModeDataStream();
    void initCoincidenceMode();
    void setCoincidenceModeWindowTime();
    void getARPETStatus();
    void showMCAEStreamDebugMode(string msg);

private:
    Ui::MainWindow *ui;
    SetPreferences *pref;
    SetPMTs *pmt_select;
    shared_ptr<MCAE> arpet;
    string initfile;
    QList<QComboBox*> heads_coin_table;
    QList<QLabel*> pmt_label_table;
    QList<QLabel*> head_status_table;
    QList<QLabel*> pmt_status_table;
    QList<QLabel*> hv_status_table;
    QList<QLabel*> calib_status_table;
    QList<QString> pmt_selected_list;
    int adquire_mode;
    int bytes_int;
    bool debug, init;
    QString coefenerg, coefT, hvtable, coefx, coefy, coefest;
    QVector<double> hvtable_values, coefenerg_values, coefT_values, coefx_values, coefy_values, coefest_values;
    QVector< QVector<double> > hits_pmt_ui, hits_head_ui;
    QVector< QVector<int> > qcp_pmt_parameters, qcp_head_parameters;
    int  AT, LowLimit;
    QVector<double> channels_ui;
    int pmt_ui_current, pmt_ui_previous;

public:
    /**
     * @brief setDebugMode
     *
     * Configura el valor de _debug_ a partir del menú preferencias.
     *
     * @param mode
     */
    void setDebugMode(bool mode) { debug = mode; }
    /**
     * @brief setPMTSelectedList
     *
     * Configura la lista de PMTs a partir de la selección realizada en el _tab_ "mca".
     *
     * @param list
     */
    void setPMTSelectedList(QList<QString> list) { pmt_selected_list = list; }
    /**
     * @brief getPMTSelectedList
     *
     * Devuelve la lista de PMTs seleccionados configurada en el menú de selección de PMTs.
     *
     * @return pmt_selected_list
     */
    QList<QString> getPMTSelectedList() { return pmt_selected_list; }
    /**
     * @brief setPMTVectorHits
     *
     * Configura el vector de cuentas por PMT.
     *
     * @param hits
     */
    void setPMTVectorHits(QVector< QVector<double> > hits) { hits_pmt_ui = hits; }
    /**
     * @brief getPMTVectorHits
     *
     * Devuelve el vector de cuentas por PMT.
     *
     * @return hits_pmt_ui
     */
    QVector< QVector<double> > getPMTVectorHits( ) { return hits_pmt_ui; }
    /**
     * @brief setHeadVectorHits
     *
     * Configura el vector de cuentas por cabezal.
     *
     * @param hits
     */
    void setHeadVectorHits(QVector< QVector<double> > hits) { hits_head_ui = hits; }
    /**
     * @brief getHeadVectorHits
     *
     * Devuelve el vector de cuentas por cabezal.
     *
     * @return hits_head_ui
     */
    QVector< QVector<double> > getHeadVectorHits( ) { return hits_head_ui; }
    /**
     * @brief setHitsInit
     *
     * Configura el estado del vector de cuentas.
     * @deprecated: Verificar este método.
     *
     * @param status
     */
    void setHitsInit(bool status) { init = status;}
};

#endif // MAINWINDOW_H
