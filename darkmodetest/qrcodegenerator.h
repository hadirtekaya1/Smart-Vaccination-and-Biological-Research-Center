#ifndef QRCODEGENERATOR_H
#define QRCODEGENERATOR_H

#include <QPixmap>
#include <QString>

class QRCodeGenerator
{
public:
    QRCodeGenerator();
    static QPixmap generateQRCode(const QString &data, int size = 200);
    static bool saveQRCodeToDatabase(int patientId, const QByteArray &qrCodeData);
    static QByteArray loadQRCodeFromDatabase(int patientId);
};

#endif // QRCODEGENERATOR_H
