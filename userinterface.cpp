#include "dragdropwidget.h"

// Konstruktor: Definiert das UI und die Interaktionen
DragDropWidget::DragDropWidget(QWidget *parent) : QWidget(parent) {
    setAcceptDrops(true); // Ermöglihct das Annehmen von Drag and Drop Ereignissen

    // Hier werden Labels und das Feld in welchem editiert wird erstellt
    infoLabel = new QLabel("Datei hier ablegen", this);
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setVisible(true);

    textEdit = new QTextEdit(this);
    textEdit->setFrameStyle(QFrame::Sunken | QFrame::Panel);
    textEdit->setVisible(false); // editier Feld erstmal unsichtbar

    // Buttons erstellen und mit entsprechenden Funktionen verknüpfen
    buttonBIN = new QPushButton("In binär bearbeiten", this);
    connect(buttonBIN, &QPushButton::clicked, this, &DragDropWidget::onbuttonBINClicked);

    buttonHEX = new QPushButton("In hexadezimal bearbeiten", this);
    connect(buttonHEX, &QPushButton::clicked, this, &DragDropWidget::onbuttonHEXClicked);

    buttonCHAR = new QPushButton("In zeichenweise bearbeiten", this);
    connect(buttonCHAR, &QPushButton::clicked, this, &DragDropWidget::onbuttonCHARClicked);

    buttonSAVE = new QPushButton("Speichern", this);
    connect(buttonSAVE, &QPushButton::clicked, this, &DragDropWidget::onbuttonSAVEClicked);

    // Buttons zu Beginn deaktivieren, da keine Datei geladen wurde
    buttonBIN->setEnabled(false);
    buttonHEX->setEnabled(false);
    buttonCHAR->setEnabled(false);
    buttonSAVE->setEnabled(false);

    // Layout erstellen und Widgets hinzufügen
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(infoLabel, 0, Qt::AlignCenter);
    layout->addWidget(textEdit);
    layout->addWidget(buttonBIN);
    layout->addWidget(buttonHEX);
    layout->addWidget(buttonCHAR);
    layout->addWidget(buttonSAVE);
}

// Start des Drag and Drop Ereignisses
void DragDropWidget::dragEnterEvent(QDragEnterEvent *event) {
    // Überprüfen, ob die übergebenen Daten URLs enthalten
    if (event->mimeData()->hasUrls()) {
        QList<QUrl> urls = event->mimeData()->urls();
        bool containsMusicFiles = false;
        QStringList supportedFormats = {".mp3"};//hier könnte man noch weitere Musikformate eingeben

        // Prüfung ob die Datei das passende Format hat
        for (const QUrl &url : urls) {
            QString path = url.toLocalFile();
            QFileInfo fileInfo(path);
            QString fileExtension = fileInfo.suffix().toLower();

            if (supportedFormats.contains("." + fileExtension)) {
                containsMusicFiles = true;
                infoLabel->setText("Datei: " + fileInfo.fileName() + " - Dateigröße: " + QString::number(fileInfo.size()) + " Bytes");
                break;
            }
        }

        // Wenn das Dateiformat stimmt wird akzeptiert
        if (containsMusicFiles) {
            event->acceptProposedAction();
        }
    }
}

// Behandlung des Drop Ereignisses
void DragDropWidget::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasUrls()) {
        QUrl url = event->mimeData()->urls().first();
        QString filePath = url.toLocalFile();
        originalFileExtension = QFileInfo(filePath).suffix();

        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString fileContent = in.readAll();
            textEdit->setPlainText(fileContent);
            file.close();

            // Buttons aktivieren, da eine Datei geladen wurde
            buttonBIN->setEnabled(true);
            buttonHEX->setEnabled(true);
            buttonCHAR->setEnabled(true);
            buttonSAVE->setEnabled(true);
        } else {
            qInfo() << "Fehler beim Öffnen der Datei";
        }
    }
}

// Funktion zum Speichern des bearbeiteten Textes
void DragDropWidget::onbuttonSAVEClicked() {
    // Überprüfen, ob der Text im aktuellen Modus gültig ist
    if (!isValidTextForCurrentMode()) {
        QMessageBox::warning(this, "Ungültige Eingabe", "Der Text enthält ungültige Zeichen.");
        return;
    }

    // Filtern der Dateien vor dem Speichern
    QString filter = "Text Files (*.txt);;All Files (*)";
    if (!originalFileExtension.isEmpty()) {
        filter = QString("%1 Files (*.%2);;").arg(originalFileExtension.toUpper(), originalFileExtension) + filter;
    }

    // Nutzer kann Dateiname und Speicherort auswählen
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "/home/untitled." + originalFileExtension,
                                                    filter);
    if (fileName.isEmpty())
        return;

    // Text in die ausgewählte Datei schreiben
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close();
    }
}
