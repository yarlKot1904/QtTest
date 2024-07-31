#include "FileModifier.h"

FileModifier::FileModifier(QObject* parent) : QObject(parent) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FileModifier::processFiles);
}

void FileModifier::setInputMask(const QString& mask) {
    qDebug() << "Setting mask:" << mask;
    inputMask = mask;
}

void FileModifier::setDeleteInputFiles(bool deleteInput) {
    qDebug() << "Setting delete:" << deleteInput;
    deleteInputFiles = deleteInput;
}

void FileModifier::setOutputPath(const QString& path) {
    qDebug() << "Setting output directory:" << path;
    outputPath = path;
}

void FileModifier::setOverwriteOutput(bool overwrite) {
    qDebug() << "Setting overwrite:" << overwrite;
    overwriteOutput = overwrite;
}

void FileModifier::setPeriodicity(int ms) {
    qDebug() << "Setting periodicity:" << ms;
    periodicity = ms;
}

void FileModifier::setBinaryValue(const QString& value) {
    qDebug() << "Setting binary hex:" << value;
    binaryValue = QByteArray::fromHex(value.toUtf8());
}

void FileModifier::setRunOnce(bool runOnce) {
    qDebug() << "Setting run once:" << runOnce;
    this->runOnce = runOnce;
}

void FileModifier::start() {
    qDebug() << "Starting";
    if (!QDir(outputPath).exists()) {
        qDebug() << "Output directory does not exist, creating new one:" << outputPath;
        QDir().mkpath(outputPath);
    }
    if (runOnce) {
        processFiles();
    }
    else {
        timer->start(periodicity);
    }
}

void FileModifier::processFiles() {
    qDebug() << "Processing files with mask:" << inputMask;
    QDir dir;
    dir.setNameFilters(QStringList() << inputMask);
    dir.setFilter(QDir::Files);

    foreach(QFileInfo fileInfo, dir.entryInfoList()) {
        if (isFileLocked(fileInfo.filePath())) {
            qDebug() << "File" << fileInfo.filePath() << "is locked, ignoring.";
            continue;
        }

        QFile file(fileInfo.filePath());
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Failed to open file" << fileInfo.filePath();
            continue;
        }

        QByteArray data = file.readAll();
        file.close();

        for (int i = 0; i < data.size(); ++i) {
            data[i] = data[i] ^ binaryValue[i % binaryValue.size()];
        }

        QString outputFilePath = outputPath + "/" + fileInfo.fileName();
        if (!overwriteOutput) {
            int counter = 1;
            while (QFile::exists(outputFilePath)) {
                outputFilePath = outputPath + "/" + QString("%1_%2").arg(fileInfo.baseName()).arg(counter++) + "." + fileInfo.completeSuffix();
            }
        }

        QFile outputFile(outputFilePath);
        if (!outputFile.open(QIODevice::WriteOnly)) {
            qDebug() << "Failed to create output file" << outputFilePath;
            continue;
        }

        outputFile.write(data);
        outputFile.close();

        if (deleteInputFiles) {
            file.remove();
        }
    }
}

bool FileModifier::isFileLocked(const QString& filePath) {
    QFile file(filePath);
    return !file.open(QIODevice::ReadWrite);
}
#include "FileModifier.moc"