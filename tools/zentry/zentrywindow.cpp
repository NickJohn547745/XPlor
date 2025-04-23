#include "zentrywindow.h"
#include "compression.h"
#include "qfiledialog.h"

#include <QMessageBox>
#include <QLabel>
#include <QFile>
#include <QVBoxLayout>

ZentryWindow::ZentryWindow(QWidget *parent)
    : QMainWindow{parent} {
    setWindowTitle("Zentry Tool");
    setMinimumSize(250, 150);
    setMaximumSize(250, 150);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    QLabel *dragLabel = new QLabel(this);
    dragLabel->setText("Drop file here...");
    dragLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    dragLabel->setStyleSheet("QLabel {"
                             "  color: white;"
                             "  background-color: grey;"
                             "}"
                             "QLabel::hover "
                             "{"
                             "  background-color: black;"
                             "}");

    setCentralWidget(dragLabel);
}

ZentryWindow::~ZentryWindow() {

}

void ZentryWindow::dragEnterEvent(QDragEnterEvent *event) {
    const QMimeData *mimeData = event->mimeData();
    bool goodDrag = true;
    if (mimeData->hasUrls()) {
        qDebug() << mimeData->urls();
    } else {
        goodDrag = false;
    }
    if (goodDrag) {
        event->acceptProposedAction();
    }
}

void ZentryWindow::dragMoveEvent(QDragMoveEvent *event) {
    Q_UNUSED(event);
}

void ZentryWindow::dragLeaveEvent(QDragLeaveEvent *event) {
    Q_UNUSED(event);
}

void ZentryWindow::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        foreach (const QUrl &url, mimeData->urls()) {
            const QString fileName = url.toString().split('/').last();
            QMessageBox msgBox;
            msgBox.setWindowTitle("Handle File");
            msgBox.setText("Choose how to handle " + fileName);

            QPushButton *compressButton = msgBox.addButton(tr("Compress"), QMessageBox::AcceptRole);
            QPushButton *decompressButton = msgBox.addButton(tr("Decompress"), QMessageBox::RejectRole);
            QPushButton *cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::RejectRole);
            msgBox.exec();

            if ((QPushButton*)msgBox.clickedButton() == compressButton) {
                // Compress
            } else if ((QPushButton*)msgBox.clickedButton() == decompressButton) {
                // Decompress
                QFile compressedFile(url.toLocalFile());
                if (!compressedFile.open(QIODevice::ReadOnly)) {
                    qDebug() << QString("Failed to open %1!").arg(fileName);
                    continue;
                }

                const QByteArray compressedData = compressedFile.readAll();
                QByteArray decompressedData;
                if (compressedData.left(2).toHex() == "7801") {
                    qDebug() << "Detected zlib data! (No Compression/low)";
                    decompressedData = Compression::DecompressZLIB(compressedData);
                } else if (compressedData.left(2).toHex() == "785e") {
                    qDebug() << "Detected zlib data! (Fast Compression)";
                    decompressedData = Compression::DecompressZLIB(compressedData);
                } else if (compressedData.left(2).toHex() == "789c") {
                    qDebug() << "Detected zlib data! (Default Compression)";
                    decompressedData = Compression::DecompressZLIB(compressedData);
                } else if (compressedData.left(2).toHex() == "78da") {
                    qDebug() << "Detected zlib data! (Best Compression)";
                    decompressedData = Compression::DecompressZLIB(compressedData);
                } else {
                    qDebug() << "Invalid zlib header!";
                    continue;
                }

                if (decompressedData.isEmpty()) {
                    qDebug() << "Zlib output was empty!";
                    continue;
                }

                const QString decompressedPath = QFileDialog::getSaveFileName(this, "Choose save name");
                QFile decompressedFile(decompressedPath);
                if (!decompressedFile.open(QIODevice::WriteOnly)) {
                    qDebug() << QString("Failed to open %1!").arg(decompressedPath.split('/').last());
                    continue;
                }
                decompressedFile.write(decompressedData);
                decompressedFile.close();
            } else if ((QPushButton*)msgBox.clickedButton() == cancelButton) {
                // Cancel
            }
        }
    }
}
