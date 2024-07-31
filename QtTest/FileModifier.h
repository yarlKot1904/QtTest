#pragma once

#include <QObject>
#include <QTimer>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QByteArray>

class FileModifier : public QObject {
    Q_OBJECT

public:
    explicit FileModifier(QObject* parent = nullptr);

    Q_INVOKABLE void setInputMask(const QString& mask);
    Q_INVOKABLE void setDeleteInputFiles(bool deleteInput);
    Q_INVOKABLE void setOutputPath(const QString& path);
    Q_INVOKABLE void setOverwriteOutput(bool overwrite);
    Q_INVOKABLE void setPeriodicity(int ms);
    Q_INVOKABLE void setBinaryValue(const QString& value);
    Q_INVOKABLE void setRunOnce(bool runOnce);
    Q_INVOKABLE void start();

private slots:
    void processFiles();

private:
    bool isFileLocked(const QString& filePath);

    QString inputMask;
    bool deleteInputFiles = false;
    QString outputPath;
    bool overwriteOutput = true;
    int periodicity = 1000;
    QByteArray binaryValue;
    QTimer* timer;
    bool runOnce = false;
};