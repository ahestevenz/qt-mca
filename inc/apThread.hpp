#ifndef APTHREAD_H
#define APTHREAD_H
#include "apMCAE.hpp"
#include <QTimer>
#include <QMutex>
#include <QEventLoop>
#include <QThread>
#include <QDebug>
#include <QObject>
#include "qdatetime.h"

namespace ap {

  class Thread : public QObject
  {
      Q_OBJECT

  public:
      explicit Thread(shared_ptr<MCAE> _arpet, QObject *parent = 0);
      /**
       * @brief Requests the process to start
       *
       * It is thread safe as it uses #mutex to protect access to #_working variable.
       */
      void requestLog();
      /**
       * @brief Requests the process to abort
       *
       * It is thread safe as it uses #mutex to protect access to #_abort variable.
       */
      void abort();
      string getLocalDateAndTime();



  private:
      shared_ptr<MCAE> arpet;
      QList<int> checkedHeads;
      /**
       * @brief Process is aborted when @em true
       */
      bool _abort;
      /**
       * @brief @em true when Worker is doing work
       */
      bool _logging;
      /**
       * @brief Protects access to #_abort
       */
      QMutex mutex;
      /**
       * @brief port_name
       */
      QString port_name;
      bool temp;
      bool rate;
      bool debug;
      int time_sec;
      bool log_finished;
      QString etime;


  signals:
      /**
       * @brief This signal is emitted when the Worker request to Work
       * @sa requestWork()
       */
      void logRequested();      
      /**
       * @brief This signal is emitted when counted value is changed (every sec)
       */
      void sendRatesValues(int index, int rate_low, int rate_med, int rate_high);
      /**
       * @brief sendTempValues
       * @param index
       * @param min
       * @param medium
       * @param max
       */
      void sendTempValues(int index, double min, double medium, double max);
      /**
       * @brief This signal is emitted when process is finished (either by counting 60 sec or being aborted)
       */
      void finished();
      void finishedElapsedTime(bool var);
      void sendErrorCommand();
      void startElapsedTime();
      void sendElapsedTimeString(QString eatime_string);
      void sendFinalElapsedTimeString(QString eatime_string);

  public slots:
      /**
       * @brief Does something
       *
       * Counts 60 sec in this example.
       * Counting is interrupted if #_aborted is set to true.
       */
      void getLogWork();
      void setAbortBool(bool abort) {_abort = abort;}
      void cancelLogging(bool var) { log_finished = var; }
      void receivedFinalElapsedTimeString(QString eatime_string) { etime = eatime_string; }
      void getElapsedTime();

  public:
      /**
       * @brief restoreLoggingVariable
       */
      void restoreLoggingVariable() { log_finished = false; }
      /**
       * @brief cancelLogging
       */
      void setCheckedHeads(QList<int> list) {checkedHeads = list;}
      void setPortName(QString port) {port_name = port;}
      void setRateBool(bool _rate) {rate = _rate;}
      void setTempBool(bool _temp) {temp = _temp;}
      void setDebugMode(bool _debug) {debug = _debug;}
      void setTimeBetweenLogs(int _sec) {time_sec = _sec;}
  };

}

#endif // APTHREAD_H
