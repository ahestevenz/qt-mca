#include "inc/MainWindow.h"
#include "ui_MainWindow.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    TimeOut(1000),
    bytes_int(CHANNELS*6+16),
    channels_ui(CHANNELS),
    hits_ui(CHANNELS),
    debug(false),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->maximumSize());    
    SetInitialConfigurations();    
}

MainWindow::~MainWindow()
{
    arpet->portDisconnect();    
    delete ui;
    delete pref;
}

void MainWindow::SetInitialConfigurations()
{
    arpet = shared_ptr<MCAE>(new MCAE(TimeOut));
    pref = new SetPreferences(this);

    manageHeadCheckBox("config",false);
    manageHeadCheckBox("mca",false);
    setAdquireMode(ui->comboBox_adquire_mode->currentIndex());

    ui->lineEdit_pmt->setValidator( new QIntValidator(1, PMTs, this) );
    ui->lineEdit_pmt_terminal->setValidator( new QIntValidator(1, PMTs, this) );
    ui->lineEdit_hv_value->setValidator( new QIntValidator(0, MAX_HV_VALUE, this) );
    ui->lineEdit_pmt_hv_terminal->setValidator( new QIntValidator(0, MAX_HV_VALUE, this) );
    ui->lineEdit_alta->setValidator( new QIntValidator(MIN_HIGH_HV_VOLTAGE, MAX_HIGH_HV_VOLTAGE, this) );
    ui->lineEdit_psoc_hv_terminal->setValidator( new QIntValidator(MIN_HIGH_HV_VOLTAGE, MAX_HIGH_HV_VOLTAGE, this) );
    ui->tabWidget_general->setCurrentWidget(ui->config);
    ui->comboBox_port->addItems(availablePortsName());
    getPMTLabelNames();

    resetHitsValues();
}

void MainWindow::checkCombosStatus()
{
     QObject::connect(ui->comboBox_head_mode_select_graph ,SIGNAL(currentIndexChanged (int)),this,SLOT(setHeadModeGraph(int)));
     QObject::connect(ui->comboBox_head_mode_select_config ,SIGNAL(currentIndexChanged (int)),this,SLOT(setHeadModeConfig(int)));
     QObject::connect(ui->comboBox_adquire_mode ,SIGNAL(currentIndexChanged (int)),this,SLOT(setAdquireMode(int)));
     QObject::connect(ui->tabWidget_mca ,SIGNAL(currentChanged(int)),this,SLOT(setTabMode(int)));
     QObject::connect(ui->comboBox_head_mode_select_config ,SIGNAL(currentIndexChanged (int)),this,SLOT(syncHeadModeComboBoxToMCA(int)));
     QObject::connect(ui->comboBox_head_select_config ,SIGNAL(currentIndexChanged (int)),this,SLOT(syncHeadComboBoxToMCA(int)));
     QObject::connect(ui->comboBox_head_mode_select_graph ,SIGNAL(currentIndexChanged (int)),this,SLOT(syncHeadModeComboBoxToConfig(int)));
     QObject::connect(ui->comboBox_head_select_graph ,SIGNAL(currentIndexChanged (int)),this,SLOT(syncHeadComboBoxToConfig(int)));
     QObject::connect(ui->checkBox_mca_1 ,SIGNAL(toggled(bool)),this,SLOT(syncCheckBoxHead1ToConfig(bool)));
     QObject::connect(ui->checkBox_mca_2 ,SIGNAL(toggled(bool)),this,SLOT(syncCheckBoxHead2ToConfig(bool)));
     QObject::connect(ui->checkBox_mca_3 ,SIGNAL(toggled(bool)),this,SLOT(syncCheckBoxHead3ToConfig(bool)));
     QObject::connect(ui->checkBox_mca_4 ,SIGNAL(toggled(bool)),this,SLOT(syncCheckBoxHead4ToConfig(bool)));
     QObject::connect(ui->checkBox_mca_5 ,SIGNAL(toggled(bool)),this,SLOT(syncCheckBoxHead5ToConfig(bool)));
     QObject::connect(ui->checkBox_mca_6 ,SIGNAL(toggled(bool)),this,SLOT(syncCheckBoxHead6ToConfig(bool)));
     QObject::connect(ui->checkBox_c_1 ,SIGNAL(toggled(bool)),this,SLOT(syncCheckBoxHead1ToMCA(bool)));
     QObject::connect(ui->checkBox_c_2 ,SIGNAL(toggled(bool)),this,SLOT(syncCheckBoxHead2ToMCA(bool)));
     QObject::connect(ui->checkBox_c_3 ,SIGNAL(toggled(bool)),this,SLOT(syncCheckBoxHead3ToMCA(bool)));
     QObject::connect(ui->checkBox_c_4 ,SIGNAL(toggled(bool)),this,SLOT(syncCheckBoxHead4ToMCA(bool)));
     QObject::connect(ui->checkBox_c_5 ,SIGNAL(toggled(bool)),this,SLOT(syncCheckBoxHead5ToMCA(bool)));
     QObject::connect(ui->checkBox_c_6 ,SIGNAL(toggled(bool)),this,SLOT(syncCheckBoxHead6ToMCA(bool)));
}

void MainWindow::getPMTLabelNames()
{
    pmt_label_table.push_back(ui->label_pmt_01);
    pmt_label_table.push_back(ui->label_pmt_02);
    pmt_label_table.push_back(ui->label_pmt_03);
    pmt_label_table.push_back(ui->label_pmt_04);
    pmt_label_table.push_back(ui->label_pmt_05);
    pmt_label_table.push_back(ui->label_pmt_06);
    pmt_label_table.push_back(ui->label_pmt_07);
    pmt_label_table.push_back(ui->label_pmt_08);
    pmt_label_table.push_back(ui->label_pmt_09);
    pmt_label_table.push_back(ui->label_pmt_10);
    pmt_label_table.push_back(ui->label_pmt_11);
    pmt_label_table.push_back(ui->label_pmt_12);
    pmt_label_table.push_back(ui->label_pmt_13);
    pmt_label_table.push_back(ui->label_pmt_14);
    pmt_label_table.push_back(ui->label_pmt_15);
    pmt_label_table.push_back(ui->label_pmt_16);
    pmt_label_table.push_back(ui->label_pmt_17);
    pmt_label_table.push_back(ui->label_pmt_18);
    pmt_label_table.push_back(ui->label_pmt_19);
    pmt_label_table.push_back(ui->label_pmt_20);
    pmt_label_table.push_back(ui->label_pmt_21);
    pmt_label_table.push_back(ui->label_pmt_22);
    pmt_label_table.push_back(ui->label_pmt_23);
    pmt_label_table.push_back(ui->label_pmt_24);
    pmt_label_table.push_back(ui->label_pmt_25);
    pmt_label_table.push_back(ui->label_pmt_26);
    pmt_label_table.push_back(ui->label_pmt_27);
    pmt_label_table.push_back(ui->label_pmt_28);
    pmt_label_table.push_back(ui->label_pmt_29);
    pmt_label_table.push_back(ui->label_pmt_30);
    pmt_label_table.push_back(ui->label_pmt_31);
    pmt_label_table.push_back(ui->label_pmt_32);
    pmt_label_table.push_back(ui->label_pmt_33);
    pmt_label_table.push_back(ui->label_pmt_34);
    pmt_label_table.push_back(ui->label_pmt_35);
    pmt_label_table.push_back(ui->label_pmt_36);
    pmt_label_table.push_back(ui->label_pmt_37);
    pmt_label_table.push_back(ui->label_pmt_38);
    pmt_label_table.push_back(ui->label_pmt_39);
    pmt_label_table.push_back(ui->label_pmt_40);
    pmt_label_table.push_back(ui->label_pmt_41);
    pmt_label_table.push_back(ui->label_pmt_42);
    pmt_label_table.push_back(ui->label_pmt_43);
    pmt_label_table.push_back(ui->label_pmt_44);
    pmt_label_table.push_back(ui->label_pmt_45);
    pmt_label_table.push_back(ui->label_pmt_46);
    pmt_label_table.push_back(ui->label_pmt_47);
    pmt_label_table.push_back(ui->label_pmt_48);

    pmt_status_table.push_back(ui->label_pmt_estado_1);
    pmt_status_table.push_back(ui->label_pmt_estado_2);
    pmt_status_table.push_back(ui->label_pmt_estado_3);
    pmt_status_table.push_back(ui->label_pmt_estado_4);
    pmt_status_table.push_back(ui->label_pmt_estado_5);
    pmt_status_table.push_back(ui->label_pmt_estado_6);

    hv_status_table.push_back(ui->label_hv_estado_1);
    hv_status_table.push_back(ui->label_hv_estado_2);
    hv_status_table.push_back(ui->label_hv_estado_3);
    hv_status_table.push_back(ui->label_hv_estado_4);
    hv_status_table.push_back(ui->label_hv_estado_5);
    hv_status_table.push_back(ui->label_hv_estado_6);

    head_status_table.push_back(ui->label_cabezal_estado_1);
    head_status_table.push_back(ui->label_cabezal_estado_2);
    head_status_table.push_back(ui->label_cabezal_estado_3);
    head_status_table.push_back(ui->label_cabezal_estado_4);
    head_status_table.push_back(ui->label_cabezal_estado_5);
    head_status_table.push_back(ui->label_cabezal_estado_6);
}

/* Menu: Preferencias */

void MainWindow::on_actionPreferencias_triggered()
{
    int ret = pref->exec();
    bool debug_console=pref->GetDegugConsoleValue();

    if(ret == QDialog::Accepted)
    {
        setDebugMode(debug_console);
    }
}

void MainWindow::showMCAEStreamDebugMode(string msg)
{
    cout<< "Trama recibida: "<< msg << " | Trama enviada: "<< arpet->getTrama_MCAE()<<endl;
}

/* Pestaña: "Configuración" */

void MainWindow::on_pushButton_arpet_on_clicked()
{
    string msg;
    try
    {
        SendString(arpet->getAP_ON(),arpet->getEnd_MCA());
        sleep(1);
        SendString(arpet->getAP_ON(),arpet->getEnd_MCA());
        msg = ReadString();
    }
    catch(Exceptions & ex)
    {
        QMessageBox::critical(this,tr("Atención"),tr((string("Hubo un inconveniente al intentar encender el equipo. Revise la conexión. Error: ")+string(ex.excdesc)).c_str()));
    }
    setLabelState(!arpet->verifyMCAEStream(msg,arpet->getAnsAP_ON()),ui->label_arpet_power_supply);
}

void MainWindow::on_pushButton_arpet_off_clicked()
{
    string msg;
    try
    {
        SendString(arpet->getAP_OFF(),arpet->getEnd_MCA());
        msg = ReadString();
    }
    catch(Exceptions & ex)
    {
        QMessageBox::critical(this,tr("Atención"),tr((string("Hubo un inconveniente al intentar apagar el equipo. Revise la conexión. Error: ")+string(ex.excdesc)).c_str()));
    }
    setLabelState(arpet->verifyMCAEStream(msg,arpet->getAnsAP_OFF()),ui->label_arpet_power_supply,true);
}

void MainWindow::on_pushButton_triple_ventana_clicked()
{
    QString fileName = openConfigurationFile();
    ui->textBrowser_triple_ventana->setText(fileName);
}

void MainWindow::on_pushButton_hv_clicked()
{
    QString fileName = openConfigurationFile();
    ui->textBrowser_hv->setText(fileName);
}

void MainWindow::on_pushButton_energia_clicked()
{
    QString fileName = openConfigurationFile();
    ui->textBrowser_energia->setText(fileName);
}


void MainWindow::on_pushButton_posicion_X_clicked()
{
    QString fileName = openConfigurationFile();
    ui->textBrowser_posicion_X->setText(fileName);
}

void MainWindow::on_pushButton_posicion_Y_clicked()
{
    QString fileName = openConfigurationFile();
    ui->textBrowser_posicion_Y->setText(fileName);
}

void MainWindow::on_pushButton_tiempos_cabezal_clicked()
{
    QString fileName = openConfigurationFile();
    ui->textBrowser_tiempos_cabezal->setText(fileName);
}

void MainWindow::on_pushButton_obtener_rutas_clicked()
{
    getPaths();
}

int MainWindow::on_pushButton_conectar_clicked()
{

    if(arpet->isPortOpen())
    {
        ui->pushButton_conectar->setText("Conectar");
        arpet->portDisconnect();
    }
    else
    {
        ui->pushButton_conectar->setText("Desconectar");
        try{
            QString port_name=ui->comboBox_port->currentText();
            arpet->portConnect(port_name.toStdString().c_str());
            QMessageBox::information(this,tr("Información"),tr("Conectado al puerto: ") + port_name);
        }
        catch(boost::system::system_error e)
            {
            QMessageBox::critical(this,tr("Error"),tr("No se puede acceder al puerto serie. Revise la conexión USB. Error: ")+tr(e.what()));;
            return MCAE::FAILED;
        }
    }

    return MCAE::OK;
}

void MainWindow::on_pushButton_head_init_clicked()
{
   int head_index=getHead("config").toInt();   
   /* Incialización del cabezal */
   setMCAEDataStream("config", arpet->getFunCHead(), arpet->getBrCst(), arpet->getInit_MCA());   
   string msg_head;
   try
   {
       SendString(arpet->getTrama_MCAE(),arpet->getEnd_MCA());
       msg_head = ReadString();
   }
   catch(Exceptions & ex)
   {
       QMessageBox::critical(this,tr("Atención"),tr((string("No se puede/n inicializar el/los cabezal/es seleccionado/s. Revise la conexión al equipo. Error: ")+string(ex.excdesc)).c_str()));
   }
   setLabelState(!arpet->verifyMCAEStream(msg_head,arpet->getAnsHeadInit()),head_status_table[head_index-1]);

   /* Inicialización de las Spartans 3*/
   setMCAEDataStream("config", arpet->getFunCSP3(), arpet->getBrCst(), arpet->getInit_MCA());  
   string msg_pmts;
   try
   {
       SendString(arpet->getTrama_MCAE(),arpet->getEnd_MCA());
       msg_pmts = ReadString();
   }
   catch(Exceptions & ex)
   {
       QMessageBox::critical(this,tr("Atención"),tr((string("No se pueden inicializar los PMT en el/los cabezal/es seleccionado/s. Revise la conexión al equipo. Error: ")+string(ex.excdesc)).c_str()));
   }
   setLabelState(!arpet->verifyMCAEStream(msg_pmts,arpet->getAnsMultiInit()),pmt_status_table[head_index-1]);

   ui->label_config_init->setText("Recepción del Cabezal: "+QString::fromStdString(msg_head)+"\nRecepción de los PMTs: "+QString::fromStdString(msg_pmts));
}

void MainWindow::on_pushButton_configurar_clicked()
{
    coefenerg_values=getValuesFromFiles(coefenerg,false);
    hvtable_values=getValuesFromFiles(hvtable,true);
    coefx_values=getValuesFromFiles(coefx,false);
    coefy_values=getValuesFromFiles(coefy,false);
    coefT_values=getValuesFromFiles(coefT,false);
    coefest_values=getValuesFromFiles(coefest,false);

    QString q_msg;
    try
    {
        for(int pmt = 0; pmt < PMTs; pmt++)
        {
            QString hv=QString::number(hvtable_values[pmt]);
            q_msg = setHV("config",hv.toStdString(), QString::number(pmt+1).toStdString());
            if(debug)
            {
                cout<<"================================"<<endl;
                cout<<"PMT: "<< QString::number(pmt+1).toStdString() <<endl;
                showMCAEStreamDebugMode(q_msg.toStdString());
                cout<<"Valor de HV: "<< hv.toStdString() <<endl;
                cout<<"================================"<<endl;
            }
        }

    }
    catch( Exceptions & ex )
    {
        QMessageBox::critical(this,tr("Atención"),tr((string("No se puede configurar el valor de HV. Revise la conexión al equipo. Error: ")+string(ex.excdesc)).c_str()));
    }
}

void MainWindow::on_pushButton_hv_set_clicked()
{
    string msg;    
    QString psoc_alta = getPSOCAlta(ui->lineEdit_alta);
    int head_index=setPSOCDataStream("config",arpet->getPSOC_SET(),psoc_alta);
    try
    {
        SendString(arpet->getTrama_MCAE(),arpet->getEnd_PSOC());
        msg = ReadString();
        hv_status_table[head_index-1]->setText(psoc_alta);
    }
    catch(Exceptions & ex)
    {
        QMessageBox::critical(this,tr("Atención"),tr((string("No se puede acceder a la placa de alta tensión. Revise la conexión al equipo. Error: ")+string(ex.excdesc)).c_str()));
    }

    ui->label_psoc_estado_datos->setText(QString::fromStdString(msg));
    if (debug) showMCAEStreamDebugMode(msg);
}

void MainWindow::on_pushButton_hv_on_clicked()
{
    string msg;
    int head_index=setPSOCDataStream("config",arpet->getPSOC_ON());
    try
    {
        SendString(arpet->getTrama_MCAE(),arpet->getEnd_PSOC());
        msg = ReadString();
        setLabelState(!arpet->verifyMCAEStream(msg,arpet->getPSOC_ANS()), hv_status_table[head_index-1]);
    }
    catch(Exceptions & ex)
    {
        QMessageBox::critical(this,tr("Atención"),tr((string("No se puede acceder a la placa de alta tensión. Revise la conexión al equipo. Error: ")+string(ex.excdesc)).c_str()));
    }

    ui->label_psoc_estado_datos->setText(QString::fromStdString(msg));
    if (debug) showMCAEStreamDebugMode(msg);
}

void MainWindow::on_pushButton_hv_off_clicked()
{
    string msg;
    int head_index=setPSOCDataStream("config",arpet->getPSOC_OFF());
    try
    {
        SendString(arpet->getTrama_MCAE(),arpet->getEnd_PSOC());
        msg = ReadString();
        setLabelState(arpet->verifyMCAEStream(msg,arpet->getPSOC_ANS()), hv_status_table[head_index-1],true);
    }
    catch(Exceptions & ex)
    {
        QMessageBox::critical(this,tr("Atención"),tr((string("No se puede acceder a la placa de alta tensión. Revise la conexión al equipo. Error: ")+string(ex.excdesc)).c_str()));
    }

    ui->label_psoc_estado_datos->setText(QString::fromStdString(msg));
    if (debug) showMCAEStreamDebugMode(msg);
}

void MainWindow::on_pushButton_hv_estado_clicked()
{
    string msg;
    setPSOCDataStream("config",arpet->getPSOC_STA());
    try
    {
        SendString(arpet->getTrama_MCAE(),arpet->getEnd_PSOC());
        msg = ReadString();

    }
    catch(Exceptions & ex)
    {
        QMessageBox::critical(this,tr("Atención"),tr((string("No se puede acceder a la placa de alta tensión. Revise la conexión al equipo. Error: ")+string(ex.excdesc)).c_str()));
    }

    ui->label_psoc_estado_datos->setText(QString::fromStdString(msg));
    if (debug) showMCAEStreamDebugMode(msg);
}

void MainWindow::setHeadModeConfig(int index)
{
    setHeadMode(index,"config");
}


/* Pestaña: "MCA" */

MainWindow::temp_code MainWindow::getTemperatureCode(double temperature)
{
    if (temperature<20) return ERROR;
    if (temperature>=20 && temperature<49) return NORMAL;
    if (temperature>=49 && temperature<56) return WARM;
    if (temperature>=56 && temperature<60) return HOT;
    if (temperature>=60) return TOO_HOT;
    else return NO_VALUE;
}

void MainWindow::setTemperatureBoard(double temp, QLabel *label_pmt, int pmt)
{
    QPalette palette_temperature;
    palette_temperature.setColor(QPalette::Background,Qt::black);

    switch (getTemperatureCode(temp)) {
    case ERROR:
        palette_temperature.setColor(QPalette::Background,Qt::lightGray);
        break;
    case NORMAL:
        palette_temperature.setColor(QPalette::Background,Qt::green);
        break;
    case WARM:
        palette_temperature.setColor(QPalette::Background,Qt::yellow);
        break;
    case HOT:
        palette_temperature.setColor(QPalette::Background,QColor::fromRgb(255,140,0)); // Naranja en RGB = 255,140,0
        break;
    case TOO_HOT:
        palette_temperature.setColor(QPalette::Background,Qt::red);
        break;
    default:
        break;
    }
    QString label_text="<span style='font-weight:600;'>"+QString::number(pmt)+"<br></span><span style='font-size:18pt; font-weight:600;'>"+QString::number(round(temp))+"</span>";
    label_pmt->setPalette(palette_temperature);
    label_pmt->setText(label_text);
}

void MainWindow::drawTemperatureBoard()
{
    double temp;
    QVector<double> temp_vec;
    temp_vec.fill(0);

    try
    {
        for(int pmt = 0; pmt < PMTs; pmt++)
        {
            setMCAEDataStream("mca", arpet->getFunCSP3(), QString::number(pmt+1).toStdString(), arpet->getTemp_MCA());
            SendString(arpet->getTrama_MCAE(),arpet->getEnd_MCA());
            string msg = ReadString();
            temp=arpet->getPMTTemperature(msg);
            temp_vec.push_back(temp);
            if(debug)
            {
                cout<<"================================"<<endl;
                cout<<"PMT: "<< QString::number(pmt+1).toStdString() <<endl;
                showMCAEStreamDebugMode(msg);
                cout<<"Valor de temperatura: "<<temp<<"°C"<<endl;
                cout<<"================================"<<endl;
            }
            setTemperatureBoard(temp,pmt_label_table[pmt],pmt+1);
        }
    }
    catch( Exceptions & ex )
    {
         QMessageBox::critical(this,tr("Atención"),tr((string("Imposible obtener los valores de temperatura. Revise la conexión al equipo. Error: ")+string(ex.excdesc)).c_str()));
    }

    double mean = std::accumulate(temp_vec.begin(), temp_vec.end(), .0) / temp_vec.size();
    double t_max = *max_element(temp_vec.begin(),temp_vec.end());
    double t_min = *min_element(temp_vec.begin(),temp_vec.end());

    if(debug)
    {
        cout<<"================================"<<endl;
        cout<<"Temperaturas"<<endl;
        cout<<"Media: "<< mean <<"°C"<<endl;
        cout<<"Máxima: "<<t_max<<"°C"<<endl;
        cout<<"Mínima: "<<t_min<<"°C"<<endl;
        cout<<"================================"<<endl;
    }

    ui->label_title_output->setText("Temperatura");
    ui->label_data_output->setText("Media: "+QString::number(mean)+"°C"+"\nMáxima: "+QString::number(t_max)+"°C"+"\nMínima: "+QString::number(t_min)+"°C");
}


void MainWindow::clearTemperatureBoard()
{
    QPalette palette_temperature;
    palette_temperature.setColor(QPalette::Background,Qt::transparent);
    for(int pmt = 0; pmt < PMTs; pmt++)
       {
          pmt_label_table[pmt]->setPalette(palette_temperature);
          pmt_label_table[pmt]->setText(QString::number(pmt+1));
       }
}

void MainWindow::on_pushButton_adquirir_clicked()
{
    QString q_msg;
    bool accum=true;
    if (!(ui->checkBox_accum->isChecked())) accum=false;

    switch (adquire_mode) {
    case MONOMODE:
        q_msg = getMCA("mca",arpet->getFunCSP3());
        getPlot(accum, ui->specPMTs);        
        break;
    case MULTIMODE:
        q_msg = getMCA("mca",arpet->getFunCHead());
        getPlot(accum, ui->specHead);        
        break;
    case TEMPERATURE:
        drawTemperatureBoard();
        break;
    default:
        break;
    }

    ui->label_received->setText(q_msg);    
}

void MainWindow::on_pushButton_reset_clicked()
{
    switch (adquire_mode) {
    case MONOMODE:
        resetHitsValues();
        break;
    case MULTIMODE:
        resetHitsValues();
        break;
    case TEMPERATURE:
        clearTemperatureBoard();
        break;
    default:
        break;
    }
}


void MainWindow::on_pushButton_hv_configure_clicked()
{
    QString q_msg;
    try
    {
        q_msg =setHV("mca",getHVValue(ui->lineEdit_hv_value),QString::number(getPMT(ui->lineEdit_pmt)).toStdString());
    }
    catch (Exceptions ex)
    {
        QMessageBox::critical(this,tr("Atención"),tr((string("No se puede configurar el valor de HV. Revise la conexión al equipo. Error: ")+string(ex.excdesc)).c_str()));
    }
    ui->label_received->setText(q_msg);
    if (debug) showMCAEStreamDebugMode(q_msg.toStdString());
}

void MainWindow::on_pushButton_l_5_clicked()
{
    QString q_msg;
    try
    {
        q_msg = setHV("mca",getHVValue(ui->lineEdit_hv_value,-5),QString::number(getPMT(ui->lineEdit_pmt)).toStdString());
    }
    catch (Exceptions ex)
    {
        QMessageBox::critical(this,tr("Atención"),tr((string("No se puede configurar el valor de HV. Revise la conexión al equipo. Error: ")+string(ex.excdesc)).c_str()));
    }
    ui->label_received->setText(q_msg);
    if (debug) showMCAEStreamDebugMode(q_msg.toStdString());
}

void MainWindow::on_pushButton_l_10_clicked()
{
    QString q_msg;
    try
    {
        q_msg = setHV("mca",getHVValue(ui->lineEdit_hv_value,-10),QString::number(getPMT(ui->lineEdit_pmt)).toStdString());
    }
    catch (Exceptions ex)
    {
        QMessageBox::critical(this,tr("Atención"),tr((string("No se puede configurar el valor de HV. Revise la conexión al equipo. Error: ")+string(ex.excdesc)).c_str()));
    }
    ui->label_received->setText(q_msg);
    if (debug) showMCAEStreamDebugMode(q_msg.toStdString());
}

void MainWindow::on_pushButton_l_50_clicked()
{
    QString q_msg;
    try
    {
        q_msg = setHV("mca",getHVValue(ui->lineEdit_hv_value,-50),QString::number(getPMT(ui->lineEdit_pmt)).toStdString());
    }
    catch (Exceptions ex)
    {
        QMessageBox::critical(this,tr("Atención"),tr((string("No se puede configurar el valor de HV. Revise la conexión al equipo. Error: ")+string(ex.excdesc)).c_str()));
    }
    ui->label_received->setText(q_msg);
    if (debug) showMCAEStreamDebugMode(q_msg.toStdString());
}

void MainWindow::on_pushButton_p_5_clicked()
{
    QString q_msg;
    try
    {
        q_msg = setHV("mca",getHVValue(ui->lineEdit_hv_value,5),QString::number(getPMT(ui->lineEdit_pmt)).toStdString());
    }
    catch (Exceptions ex)
    {
        QMessageBox::critical(this,tr("Atención"),tr((string("No se puede configurar el valor de HV. Revise la conexión al equipo. Error: ")+string(ex.excdesc)).c_str()));
    }
    ui->label_received->setText(q_msg);
    if (debug) showMCAEStreamDebugMode(q_msg.toStdString());
}

void MainWindow::on_pushButton_p_10_clicked()
{
    QString q_msg;
    try
    {
        q_msg = setHV("mca",getHVValue(ui->lineEdit_hv_value,10),QString::number(getPMT(ui->lineEdit_pmt)).toStdString());
    }
    catch (Exceptions ex)
    {
        QMessageBox::critical(this,tr("Atención"),tr((string("No se puede configurar el valor de HV. Revise la conexión al equipo. Error: ")+string(ex.excdesc)).c_str()));
    }
    ui->label_received->setText(q_msg);
    if (debug) showMCAEStreamDebugMode(q_msg.toStdString());
}

void MainWindow::on_pushButton_p_50_clicked()
{
    QString q_msg;
    try
    {
        q_msg = setHV("mca",getHVValue(ui->lineEdit_hv_value,50),QString::number(getPMT(ui->lineEdit_pmt)).toStdString());
    }
    catch (Exceptions ex)
    {
        QMessageBox::critical(this,tr("Atención"),tr((string("No se puede configurar el valor de HV. Revise la conexión al equipo. Error: ")+string(ex.excdesc)).c_str()));
    }
    ui->label_received->setText(q_msg);
    if (debug) showMCAEStreamDebugMode(q_msg.toStdString());
}


void MainWindow::on_pushButton_decrease_clicked()
{
    QString pmt=ui->lineEdit_pmt->text();
    if (pmt.toInt()>1)
    {
        int pmt_decrease=pmt.toInt()-1;
        ui->lineEdit_pmt->setText(QString::number(pmt_decrease));
    }
}

void MainWindow::on_pushButton_increase_clicked()
{
    QString pmt=ui->lineEdit_pmt->text();
    if (pmt.toInt()<PMTs)
    {
        int pmt_increase=pmt.toInt()+1;
        ui->lineEdit_pmt->setText(QString::number(pmt_increase));
    }
}

void MainWindow::setHeadModeGraph(int index)
{
    setHeadMode(index,"mca");
}

void MainWindow::setAdquireMode(int index)
{
    adquire_mode=index;
    switch (adquire_mode) {
    case MONOMODE:
        ui->frame_PMT->show();
        ui->frame_HV->show();
        ui->frame_MCA->show();        
        ui->tabWidget_mca->setCurrentWidget(ui->tab_esp_1);
        break;
    case MULTIMODE:
        ui->frame_PMT->hide();
        ui->frame_HV->hide();        
        ui->frame_MCA->show();
        ui->tabWidget_mca->setCurrentWidget(ui->tab_esp_2);
        break;
    case TEMPERATURE:
        ui->frame_PMT->hide();
        ui->frame_HV->hide();
        ui->tabWidget_mca->setCurrentWidget(ui->tab_esp_3);
        ui->frame_MCA->hide();        
    default:
        break;
    }
}

void MainWindow::setTabMode(int index)
{
    adquire_mode=index;
    ui->comboBox_adquire_mode->setCurrentIndex(adquire_mode);
}

QString MainWindow::getMCA(string tab, string function)
{
    pmt_ui_current=getPMT(ui->lineEdit_pmt);
    if (pmt_ui_current!=pmt_ui_previous) resetHitsValues();
    pmt_ui_previous=pmt_ui_current;
    setMCAEDataStream(tab, function, QString::number(pmt_ui_current).toStdString(), arpet->getData_MCA(),bytes_int);    
    string msg, msg_data;
    try
    {
        SendString(arpet->getTrama_MCAE(),arpet->getEnd_MCA());
        msg = ReadString();
        msg_data = ReadBufferString(bytes_int);
    }
    catch(Exceptions & ex)
    {
        QMessageBox::critical(this,tr("Atención"),tr((string("No se pueden obtener los valores de MCA. Revise la conexión al equipo. Error: ")+string(ex.excdesc)).c_str()));
    }
    arpet->getMCASplitData(msg_data, CHANNELS);

    long long time_mca;
    int frame, HV_pmt, offset, var;

    frame=arpet->getFrameMCA();
    time_mca=arpet->getTimeMCA();
    HV_pmt=arpet->getHVMCA();
    offset=arpet->getOffSetMCA();
    var=arpet->getVarMCA();

    ui->label_title_output->setText("MCA Extended");
    ui->label_data_output->setText("Frame: "+QString::number(frame)+"\nVarianza: "+QString::number(var)+"\nOffset ADC: "+QString::number(offset)+"\nTiempo (useg):\n"+QString::number(time_mca));

    if(debug)
    {
        cout<<"================================"<<endl;
        cout<<"Datos extraídos por MCA"<<endl;
        cout<<"Frame: "<< frame <<endl;
        cout<<"Varianza (unidades cuadráticas de ADC): "<< var <<endl;
        cout<<"Offset (unidades de ADC): "<< offset <<endl;
        cout<<"Tiempo de adquisición (medido en microsegundos): "<< time_mca <<endl;
        cout<<"Valor de HV: "<<HV_pmt<<endl;
        showMCAEStreamDebugMode(msg);
        cout<<"================================"<<endl;
    }


    return QString::fromStdString(msg);
}

QString MainWindow::setHV(string tab, string hv_value, string pmt)
{
    setMCAEDataStream(tab, arpet->getFunCSP3(), pmt, arpet->getSetHV_MCA(),0, hv_value);
    string msg;
    try
    {
        SendString(arpet->getTrama_MCAE(),arpet->getEnd_MCA());
        msg = ReadString();
    }
    catch(Exceptions & ex)
    {
        Exceptions exception_hv(ex.excdesc);
        throw exception_hv;
    }
    resetHitsValues();

    return QString::fromStdString(msg);
}


int MainWindow::getPMT(QLineEdit *line_edit)
{
   QString pmt=line_edit->text();
   switch (adquire_mode) {
     case MONOMODE:
       if(pmt.isEmpty() || pmt.toInt()==0)
       {
           pmt=QString::number(1);
           line_edit->setText(pmt);
       }
       break;
      case MULTIMODE:
       line_edit->setText(0);
       break;
      default:
       break;
   }

   return line_edit->text().toInt();
}

QString MainWindow::getPSOCAlta(QLineEdit *line_edit)
{
    QString psoc_value=line_edit->text();
    if(psoc_value.isEmpty() || psoc_value.toInt()<MIN_HIGH_HV_VOLTAGE)
    {
            psoc_value=QString::number(MIN_HIGH_HV_VOLTAGE);
            line_edit->setText(psoc_value);
    }

    return line_edit->text();
}

void MainWindow::setPMT(int value)
{
     ui->lineEdit_pmt->setText(QString::number(value));
}

string MainWindow::getHVValue(QLineEdit *line_edit, int value)
{
    int hv_value_int;
    if (line_edit->text().isEmpty()) hv_value_int=0;
    if (value==0) hv_value_int=line_edit->text().toInt();
    else  hv_value_int=line_edit->text().toInt() + value;
    if (hv_value_int<0) hv_value_int=0;
    line_edit->setText(QString::number(hv_value_int));

    return QString::number(hv_value_int).toStdString();
}

void MainWindow::setMCAEDataStream(string tab, string function, string pmt, string mca_function, int bytes_mca, string hv_value)
{
  arpet->setHeader_MCAE(arpet->getHead_MCAE() + getHead(tab).toStdString() + function);
  arpet->setMCAEStream(pmt, bytes_mca, mca_function, hv_value);
}

int MainWindow::setPSOCDataStream(string tab, string function, QString psoc_value)
{
    QString head=getHead(tab);
    int head_index=head.toInt();
    arpet->setHeader_MCAE(arpet->getHead_MCAE() + head.toStdString() + arpet->getFunCPSOC());
    arpet->setPSOCEStream(function, psoc_value.toStdString());

    return head_index;
}

void MainWindow::resetHitsValues()
{
    hits_ui.fill(0);
}

void MainWindow::getPlot(bool accum, QCustomPlot *graph)
{
    /* Datos del gráfico */    
    if (!accum){
        resetHitsValues();
    }
    channels_ui = arpet->getChannels();
    transform(hits_ui.begin(), hits_ui.end(), arpet->getHitsMCA().begin(), hits_ui.begin(), plus<double>());

    /* Se genera los ejes */
    double c_max = *max_element(hits_ui.begin(),hits_ui.end());
    double c_min =0;
    if (c_max==0) {c_max=1; c_min=-1;}

    if (debug)
    {
        cout<<"================================"<<endl;
        cout<<"Máximo número de cuentas: "<<c_max<<endl;
        cout<<"Cantidad de canales: "<<CHANNELS<<endl;
        cout<<"Rango en el gráfico: "<<endl;
        cout<<"De: "<<c_min<<" a "<<c_max*1.25 <<endl;
        cout<<"================================"<<endl;
    }

    graph->addGraph();
    graph->graph(0)->setData(channels_ui, hits_ui);
    graph->xAxis2->setVisible(true);
    graph->xAxis2->setTickLabels(true);
    graph->yAxis2->setVisible(true);
    graph->yAxis2->setTickLabels(true);
    graph->xAxis->setLabel("Canales");
    graph->yAxis->setLabel("Cuentas");

    /* Rangos y grafico */
    graph->xAxis->setRange(0, CHANNELS);
    graph->yAxis->setRange(c_min, c_max*1.25);
    graph->replot();
}

/* Métodos generales del entorno gráfico */

void MainWindow::getARPETStatus()
{
    setMCAEDataStream("config", arpet->getFunCHead(), arpet->getBrCst(), arpet->getInit_MCA());    
    string msg_head;
    try
    {
        SendString(arpet->getTrama_MCAE(),arpet->getEnd_MCA());
        msg_head = ReadString();
    }
    catch(Exceptions & ex)
    {
        QMessageBox::critical(this,tr("Atención"),tr((string("No se puede obtener el estado del equipo. Revise la conexión. Error: ")+string(ex.excdesc)).c_str()));
    }
    setLabelState(!arpet->verifyMCAEStream(msg_head,arpet->getAnsHeadInit()),ui->label_arpet_power_supply);
}

QVector<double> MainWindow::getValuesFromFiles(QString filename, bool hv)
{
    QVector<double> values;
    QRegExp rx("(\\t)");
    QFile inputFile(filename);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        if(hv)
        {
            while (!in.atEnd())
            {
                QString line = in.readLine();
                QStringList fields = line.split(rx);
                QString q_hv=fields.at(1);
                values.push_back(q_hv.toDouble());
            }
        }
        else
        {
            while (!in.atEnd())
            {
                QString line = in.readLine();
                values.push_back(line.toDouble());
            }
        }
        inputFile.close();
    }

    return values;
}

/**
 * @brief MainWindow::parseConfigurationFile
 * @param filename
 * @return
 */
int MainWindow::parseConfigurationFile(QString filename)
{
    QFile configfile(filename);
    if (!configfile.open(QIODevice::ReadOnly)) {
        filename=openConfigurationFile();
        configfile.setFileName(filename);
        if (!configfile.open(QIODevice::ReadOnly)){
            if(debug) qDebug() << "No se puede abrir el archivo de configuración. Error: " << configfile.errorString();
            QMessageBox::critical(this,tr("Atención"),tr("No se puede abrir el archivo de configuración."));
            return MCAE::FILE_NOT_FOUND;
        }
    }

    QSettings settings(filename, QSettings::IniFormat);

    /* Parameters */
    AT = settings.value("SetUp/AT", "US").toInt();
    LowLimit = settings.value("SetUp/LowLimit", "US").toInt();

    /* Paths to the configuration files */

    QString head= getHead("config");
    QString root=settings.value("Paths/root", "US").toString();

    coefenerg = root+settings.value("Cabezal"+head+"/coefenerg", "US").toString();
    hvtable = root+settings.value("Cabezal"+head+"/hvtable", "US").toString();
    coefx = root+settings.value("Cabezal"+head+"/coefx", "US").toString();
    coefy = root+settings.value("Cabezal"+head+"/coefy", "US").toString();
    coefest = root+settings.value("Cabezal"+head+"/coefest", "US").toString();
    coefT = root+settings.value("Cabezal"+head+"/coefT", "US").toString();

    configfile.close();

    return MCAE::OK;
}

/**
 * @brief MainWindow::openConfigurationFile
 * @return
 */
QString MainWindow::openConfigurationFile()
{
    QString root="/media/arpet/pet/calibraciones/03-info/cabezales";
    QString filename = QFileDialog::getOpenFileName(this, tr("Abrir archivo de configuración"),
                                                    root,
                                                    tr("Configuración (*.ini);;Texto (*.txt)"));
    return filename;
}

/**
 * @brief MainWindow::getPaths
 */
void MainWindow::getPaths()
{
    string initfile="/media/arpet/pet/calibraciones/03-info/cabezales/ConfigINI/config_cabs_linux.ini";
    QString filename=QString::fromStdString(initfile);
    parseConfigurationFile(filename);

    ui->textBrowser_triple_ventana->setText(coefest);
    ui->textBrowser_hv->setText(hvtable);
    ui->textBrowser_energia->setText(coefenerg);
    ui->textBrowser_posicion_X->setText(coefx);
    ui->textBrowser_posicion_Y->setText(coefy);
    ui->textBrowser_tiempos_cabezal->setText(coefT);

    ui->lineEdit_alta->setText(QString::number(AT));
    ui->lineEdit_limiteinferior->setText(QString::number(LowLimit));
}

/**
 * @brief MainWindow::SetLabelState
 * @param state
 * @param label
 */
void MainWindow::setLabelState(bool state, QLabel *label, bool power_off)
{
    QPalette palette;

    if (!state && !power_off)
    {
        palette.setColor(QPalette::Background,Qt::green);
        label->setPalette(palette);
    }
    else if(state)
    {
        palette.setColor(QPalette::Background,Qt::red);
        label->setPalette(palette);
    }
    else
    {
        palette.setColor(QPalette::Background,Qt::gray);
        label->setPalette(palette);
    }

    return;
}


/**
 * @brief MainWindow::availablePortsName
 * @return
 */
QStringList MainWindow::availablePortsName()
{

    QStringList portsName;

    QDir dir("/dev/");
    QStringList filters;

    filters << "ttyUSB*";
    dir.setNameFilters(filters);
    dir.setFilter(QDir::Files | QDir::System);
    QFileInfoList list = dir.entryInfoList();

    for (int i=0; i< list.size(); i++)
    {
        portsName.append(list.at(i).canonicalFilePath ());
    }

    return portsName;
}

QString MainWindow::getHead(string tab)
{
    QString head;
    if (tab=="mca")
    {
        if (ui->comboBox_head_mode_select_graph->currentIndex()==MONOHEAD)
        {
           head=ui->comboBox_head_select_graph->currentText();
        }
    }
    else if (tab=="config")
    {
        if (ui->comboBox_head_mode_select_config->currentIndex()==MONOHEAD)
        {
           head=ui->comboBox_head_select_config->currentText();
        }
    }
    else if (tab=="terminal")
    {
       head=ui->comboBox_head_select_terminal->currentText();
    }
    else head="";

    return head;
}

string MainWindow::ReadString(char delimeter)
{
    string msg;
    try{
         arpet->portReadString(&msg,delimeter);
    }
    catch( Exceptions & ex ){
         Exceptions exception_stop(ex.excdesc);
         throw exception_stop;
    }
    return msg;
}

string MainWindow::ReadBufferString(int buffer_size)
{
    string msg;
    try{
         arpet->portReadBufferString(&msg,buffer_size);
    }
    catch( Exceptions & ex ){
         Exceptions exception_stop(ex.excdesc);
         throw exception_stop;
    }
    return msg;
}

size_t MainWindow::SendString(string msg, string end)
{
    arpet->portFlush();
    size_t bytes_transfered = 0;

    try{
        string sended=msg + end;
        bytes_transfered = arpet->portWrite(&sended);
    }
    catch(boost::system::system_error e){
        Exceptions exception_serial_port((string("No se puede acceder al puerto serie. Error: ")+string(e.what())).c_str());
        throw exception_serial_port;
    }

    return bytes_transfered;
}

void MainWindow::manageHeadCheckBox(string tab, bool show)
{
    if (tab=="config")
    {
        if (show) ui->frame_multihead_config->show();
        else ui->frame_multihead_config->hide();
    }
    else if(tab=="mca")
    {
        if (show) ui->frame_multihead_graph->show();
        else ui->frame_multihead_graph->hide();
    }
    else return;
}

void MainWindow::manageHeadComboBox(string tab, bool show)
{
    if (tab=="config"){
        if (show) ui->comboBox_head_select_config->show();
        else ui->comboBox_head_select_config->hide();
    }
    else if(tab=="mca")
    {
        if (show) ui->comboBox_head_select_graph->show();
        else ui->comboBox_head_select_graph->hide();
    }
    else return;
}


void MainWindow::setHeadMode(int index, string tab)
{
    switch (index) {
    case MONOHEAD:
        manageHeadComboBox(tab, true);
        manageHeadCheckBox(tab, false);
        break;
    case MULTIHEAD:
        manageHeadComboBox(tab, false);
        manageHeadCheckBox(tab, true);
        break;
    default:
        break;
    }
}

void MainWindow::syncHeadModeComboBoxToConfig(int index)
{
    getPaths();
    ui->comboBox_head_mode_select_config->setCurrentIndex(index);
}

void MainWindow::syncHeadComboBoxToConfig(int index)
{
    getPaths();
    ui->comboBox_head_select_config->setCurrentIndex(index);
}

void MainWindow::syncHeadModeComboBoxToMCA(int index)
{
    getPaths();
    ui->comboBox_head_mode_select_graph->setCurrentIndex(index);
}

void MainWindow::syncHeadComboBoxToMCA(int index)
{
    getPaths();
    ui->comboBox_head_select_graph->setCurrentIndex(index);
}

void MainWindow::syncCheckBoxHead1ToConfig(bool check)
{
    ui->checkBox_c_1->setChecked(check);
}

void MainWindow::syncCheckBoxHead2ToConfig(bool check)
{
    ui->checkBox_c_2->setChecked(check);
}

void MainWindow::syncCheckBoxHead3ToConfig(bool check)
{
    ui->checkBox_c_3->setChecked(check);
}

void MainWindow::syncCheckBoxHead4ToConfig(bool check)
{
    ui->checkBox_c_4->setChecked(check);
}

void MainWindow::syncCheckBoxHead5ToConfig(bool check)
{
    ui->checkBox_c_5->setChecked(check);
}

void MainWindow::syncCheckBoxHead6ToConfig(bool check)
{
    ui->checkBox_c_6->setChecked(check);
}

void MainWindow::syncCheckBoxHead1ToMCA(bool check)
{
    ui->checkBox_mca_1->setChecked(check);
}

void MainWindow::syncCheckBoxHead2ToMCA(bool check)
{
    ui->checkBox_mca_2->setChecked(check);
}

void MainWindow::syncCheckBoxHead3ToMCA(bool check)
{
    ui->checkBox_mca_3->setChecked(check);
}

void MainWindow::syncCheckBoxHead4ToMCA(bool check)
{
    ui->checkBox_mca_4->setChecked(check);
}

void MainWindow::syncCheckBoxHead5ToMCA(bool check)
{
    ui->checkBox_mca_5->setChecked(check);
}

void MainWindow::syncCheckBoxHead6ToMCA(bool check)
{
    ui->checkBox_mca_6->setChecked(check);
}

/* Terminal */

void MainWindow::on_pushButton_send_terminal_clicked()
{
    QString sended = ui->lineEdit_terminal->text();
    size_t bytes;
    string msg;
    string end_stream=arpet->getEnd_MCA();

    if(ui->checkBox_end_terminal->isChecked()) end_stream=arpet->getEnd_PSOC();

    try
    {
        bytes = SendString(sended.toStdString(),end_stream);
        msg = ReadString();
    }
    catch(Exceptions & ex)
    {
        QMessageBox::critical(this,tr("Atención"),tr(ex.excdesc));
    }

    QString q_msg=QString::fromStdString(msg);
    QString q_bytes=QString::number(bytes);
    ui->label_size_terminal->setText(q_bytes);
    ui->label_received_terminal->setText(q_msg);
}

void MainWindow::on_pushButton_flush_terminal_clicked()
{
    arpet->portFlush();
}

void MainWindow::on_pushButton_clear_terminal_clicked()
{
    ui->lineEdit_terminal->clear();
}


void MainWindow::on_pushButton_stream_configure_mca_terminal_clicked()
{
    string mca_function, function, hv_value;
    int bytes_mca;
    switch (ui->comboBox_mca_function_terminal->currentIndex())
    {
        case 0:
            mca_function=arpet->getInit_MCA();
            hv_value="";
            bytes_mca=0;
            break;
        case 1:
            mca_function=arpet->getData_MCA();
            hv_value="";
            bytes_mca=bytes_int;
            break;
        case 2:
            mca_function=arpet->getSetHV_MCA();
            hv_value=getHVValue(ui->lineEdit_pmt_hv_terminal);
            bytes_mca=0;
            break;
        case 3:
            mca_function=arpet->getTemp_MCA();
            hv_value="";
            bytes_mca=0;
            break;
        default:
            break;
    }

    switch (ui->comboBox_func_terminal->currentIndex())
    {
        case 0:
            function=arpet->getFunCHead();
            break;
        case 1:
            function=arpet->getFunCSP3();
            break;
        default:
            break;
    }

    int pmt=getPMT(ui->lineEdit_pmt_terminal);
    setMCAEDataStream("terminal", function, QString::number(pmt).toStdString(), mca_function, bytes_mca, hv_value);
    ui->lineEdit_terminal->setText(QString::fromStdString(arpet->getTrama_MCAE()));

}

void MainWindow::on_pushButton_stream_configure_psoc_terminal_clicked()
{
    QString psoc_alta;
   switch (ui->comboBox_psoc_function_terminal->currentIndex())
    {
        case 0:            
            setPSOCDataStream("terminal",arpet->getPSOC_ON());
            break;
        case 1:
            setPSOCDataStream("terminal",arpet->getPSOC_OFF());
            break;
        case 2:
            psoc_alta = getPSOCAlta(ui->lineEdit_psoc_hv_terminal);
            setPSOCDataStream("terminal",arpet->getPSOC_SET(),psoc_alta);
            break;
        case 3:
            setPSOCDataStream("terminal",arpet->getPSOC_STA());
            break;
        default:
            break;
    }
    ui->lineEdit_terminal->setText(QString::fromStdString(arpet->getTrama_MCAE()));
}
