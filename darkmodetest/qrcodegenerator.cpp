#include "qrcodegenerator.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QBuffer>
#include <qrencode.h>

QPixmap QRCodeGenerator::generateQRCode(const QString &data, int size)
{
    QRcode *qr = QRcode_encodeString(data.toUtf8().constData(), 0, QR_ECLEVEL_L, QR_MODE_8, 1);
    if(!qr) {
        return QPixmap();
    }

    QImage image(qr->width, qr->width, QImage::Format_Mono);
    image.fill(1); // White background

    for(int y = 0; y < qr->width; y++) {
        for(int x = 0; x < qr->width; x++) {
            image.setPixel(x, y, qr->data[y * qr->width + x] & 1 ? 0 : 1);
        }
    }

    QRcode_free(qr);

    // Scale the image to the requested size
    return QPixmap::fromImage(image.scaled(size, size, Qt::KeepAspectRatio));
}

bool QRCodeGenerator::saveQRCodeToDatabase(int patientId, const QByteArray &qrCodeData)
{
    QSqlQuery query;
    query.prepare("UPDATE patients SET qr_code = :qrCode WHERE patient_id = :patientId");
    query.bindValue(":qrCode", qrCodeData);
    query.bindValue(":patientId", patientId);

    return query.exec();
}

QByteArray QRCodeGenerator::loadQRCodeFromDatabase(int patientId)
{
    QSqlQuery query;
    query.prepare("SELECT qr_code FROM patients WHERE patient_id = :patientId");
    query.bindValue(":patientId", patientId);

    if(query.exec() && query.next()) {
        return query.value(0).toByteArray();
    }

    return QByteArray();
}
