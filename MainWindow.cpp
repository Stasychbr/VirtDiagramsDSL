#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QGraphicsWidget>
#include <QGraphicsScene>
#include <QStatusBar>

#include <QtSvg/QSvgGenerator>
#include <QPrinter>

#include <antlr4-runtime.h>

#include "antlr/MetaGrammar/MetaGrammarParser.h"
#include "antlr/MetaGrammar/MetaGrammarLexer.h"

#include "GraphicsVisitor.h"
#include "ErrorListener.h"
#include "Defines.h"

using namespace GuiMetrics;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_errorListener(new ErrorListener(this))
{
	ui->setupUi(this);

	m_loggerButton = new HighlightableButton(LoggerButton::BackroundColor);
	ui->centralLayout->insertWidget(1, m_loggerButton);
    m_loggerButton->setToolTip("Show logger");
    onLoggerButton(false);

    initDialogs();
    initStatusBar();

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onOpenAction);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSaveAction);
    connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::onSaveAsAction);
    connect(ui->actionZoom_in, &QAction::triggered, this, &MainWindow::onZoomIn);
    connect(ui->actionZoom_out, &QAction::triggered, this, &MainWindow::onZoomOut);
    connect(ui->actionSet_DPI, &QAction::triggered, this, &MainWindow::onSetDpi);
	connect(m_errorListener, &ErrorListener::errorOccured, this, &MainWindow::onError);
    connect(m_loggerButton, &QPushButton::clicked, this, &MainWindow::onLoggerButton);
    connect(ui->actionShow_grammar, &QAction::triggered, this, &MainWindow::showMetaDiagram);

	m_loggerButton->setFont(LoggerButton::TextFont);

    m_vertScroll = ui->graphicsView->verticalScrollBar();
    m_vertScroll->installEventFilter(this);

    m_saveScale = m_dpiDialog->getDpi() / logicalDpiX();
    m_dpiLabel->setText("DPI: " + QString::number(m_dpiDialog->getDpi()));
}

void MainWindow::initStatusBar()
{
    m_filenameLabel = new QLabel(this);
    m_dpiLabel = new QLabel(this);
    statusBar()->addWidget(m_filenameLabel);
    statusBar()->addPermanentWidget(m_dpiLabel);
}

void MainWindow::initDialogs() {
    QStringList saveMimeTypeFilters({"image/jpeg", "image/png", "image/svg+xml", "application/pdf"});
    QStringList openMimeTypeFilters({"text/plain"});

    m_saveDialog = new QFileDialog(this);
    m_saveDialog->setMimeTypeFilters(saveMimeTypeFilters);
    m_saveDialog->setAcceptMode(QFileDialog::AcceptSave);

    m_openDialog = new QFileDialog(this);
    m_openDialog->setMimeTypeFilters(openMimeTypeFilters);

    m_dpiDialog = new DpiDialog(this);
}

void MainWindow::wheelEvent(QWheelEvent *event) {
    static int wheelDelta = 0;
    int curDelta = event->angleDelta().y();
    wheelDelta += curDelta;
    if (wheelDelta >= 120) {
        wheelDelta -= 120;
        onZoomIn();
    }
    else if (wheelDelta <= -120) {
        wheelDelta += 120;
        onZoomOut();
    }
    event->accept();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_vertScroll) {
        if (event->type() == QEvent::Wheel) {
            return true;
        }
    }
    return false;
}

void MainWindow::onOpenAction()
{
    if (m_openDialog->exec() == QDialog::Accepted) {
        QString filename = m_openDialog->selectedFiles().first();
		if (!filename.isEmpty()) {
            proceedGrammar(QFileInfo(filename));
        }
    }
}

void MainWindow::onError(size_t line, size_t charPos, const std::string& msg)
{
     QString message("Error at line ");
     message += QString::number(line);
     message += ":";
     message += QString::number(charPos);
	 log(message + " - " + msg.c_str());
}

void MainWindow::onLoggerButton(bool checked)
{
    m_fLoggerShown = !m_fLoggerShown;
    QString buttonText = m_fLoggerShown ? "»" : "«" ;
    ui->loggerWidget->setHidden(m_fLoggerShown);
	m_loggerButton->setText(buttonText);
    if (m_fLoggerShown) {
        m_loggerButton->setToolTip("Show logger");
    }
    else {
        m_loggerButton->setToolTip("Hide logger");
    }
}

void MainWindow::proceedGrammar(QFileInfo path)
{
    statusBar()->showMessage("Proceeding " + path.fileName());
    QFile file(path.filePath());
    file.open(QIODeviceBase::ReadOnly | QIODeviceBase::Text);
    if (!file.isReadable()) {
        statusBar()->showMessage("Error", 3000);
        log("Unable to open " + path.filePath());
		highlightLoggerButton();
		return;
    }
    QByteArray data = file.readAll();
    antlr4::ANTLRInputStream input(data.constData(), data.length());
    MetaGrammarLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    MetaGrammarParser parser(&tokens);

    parser.addErrorListener(m_errorListener);
    lexer.addErrorListener(m_errorListener);

    log("Proceeding " + path.fileName() + " file...");

    GraphicsVisitor visitor;
    auto rulesList = parser.ruleList();
    if (parser.getNumberOfSyntaxErrors() > 0 || lexer.getNumberOfSyntaxErrors() > 0) {
        statusBar()->showMessage("Error", 3000);
		highlightLoggerButton();
        return;
    }
    statusBar()->showMessage("Success", 3000);
    log("Success");
    m_filenameLabel->setText(path.absoluteFilePath());

    m_curFileName = path;

	auto currScene = ui->graphicsView->scene();
	delete currScene;

	auto scene = new QGraphicsScene(this);
	ui->graphicsView->setScene(scene);

    auto widget = visitor.visit(rulesList).as<QGraphicsWidget*>();
    scene->addItem(widget);
}

void MainWindow::drawImage(QPaintDevice* paintDevice)
{
    QPainter painter;
    painter.begin(paintDevice);
    painter.setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->scene()->render(&painter);
    painter.end();
}

void MainWindow::onSaveAction()
{
    auto sceneRect = ui->graphicsView->scene()->itemsBoundingRect();
    QPixmap pixmap(m_saveScale * sceneRect.width(), m_saveScale * sceneRect.height());
    pixmap.fill();
    drawImage(&pixmap);
	pixmap.save(m_curFileName.baseName() + "Diagram.png");
    statusBar()->showMessage("Saved " + m_curFileName.baseName() + "Diagram.png", 3000);
}

void MainWindow::onSaveAsAction()
{
    if (m_saveDialog->exec() == QDialog::Accepted) {
        QString filename = m_saveDialog->selectedFiles().first();
        if (!filename.isEmpty()) {
            auto type = m_saveDialog->selectedMimeTypeFilter();
            auto sceneRect = ui->graphicsView->scene()->itemsBoundingRect();
            if (type == "image/svg+xml") {
                QSvgGenerator generator;
                generator.setFileName(filename);
                generator.setSize({qCeil(sceneRect.width()), qCeil(sceneRect.height())});
                generator.setViewBox(sceneRect);
                generator.setDescription("Just a Virt's semantic diagram");
                generator.setTitle("Semantic Diagram");
                drawImage(&generator);
            }
            else if (type == "application/pdf") {
                QPrinter printer;
                printer.setOutputFileName(filename);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPageSize(QPageSize({sceneRect.width(), sceneRect.height()}, QPageSize::Millimeter, QString(), QPageSize::ExactMatch));
                drawImage(&printer);
            }
            else {
                QPixmap pixmap(m_saveScale * sceneRect.width(), m_saveScale * sceneRect.height());
                auto color = type == "image/png" ? Qt::transparent : Qt::white;
                pixmap.fill(color);
                drawImage(&pixmap);
                pixmap.save(filename);
            }
            statusBar()->showMessage("Saved " + filename, 3000);
        }
    }
}

void MainWindow::onSetDpi()
{
    if (m_dpiDialog->exec() == QDialog::Accepted) {
        m_saveScale = m_dpiDialog->getDpi() / logicalDpiX();
        m_dpiLabel->setText("DPI: " + QString::number(m_dpiDialog->getDpi()));
    }
}

void MainWindow::onZoomOut()
{
    if (m_scaleState > -scaleTimes) {
        ui->graphicsView->scale(1.f / scaleFactor, 1.f / scaleFactor);
        m_scaleState--;
    }
}

void MainWindow::onZoomIn()
{
    if (m_scaleState < scaleTimes) {
        ui->graphicsView->scale(scaleFactor, scaleFactor);
        m_scaleState++;
    }
}

void MainWindow::log(QString msg)
{
	ui->loggerOutput->appendPlainText(msg);
}

void MainWindow::showMetaDiagram() {
    proceedGrammar(QFileInfo(":/basic_grammars/meta_grammar.txt"));
}

void MainWindow::highlightLoggerButton()
{
	m_loggerButton->highlight(LoggerButton::HighlightColor,
							  LoggerButton::HighlightDuration);
}

MainWindow::~MainWindow()
{
    delete ui;
}
