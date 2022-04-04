#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QGraphicsWidget>
#include <QGraphicsScene>

#include <QtSvg/QSvgGenerator>
#include <QPrinter>

#include <antlr4-runtime.h>

#include "antlr/MetaGrammar/MetaGrammarParser.h"
#include "antlr/MetaGrammar/MetaGrammarLexer.h"

#include "GraphicsVisitor.h"


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
    ui(new Ui::MainWindow),
    errorListener(new ErrorListener(this))
{
	ui->setupUi(this);
    winName = windowTitle();
    ui->loggerWidget->hide();

    initDialogs();

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onOpenAction);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSaveAction);
    connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::onSaveAsAction);
    connect(ui->actionZoom_in, &QAction::triggered, this, &MainWindow::onZoomIn);
    connect(ui->actionZoom_out, &QAction::triggered, this, &MainWindow::onZoomOut);
    connect(ui->actionSet_DPI, &QAction::triggered, this, &MainWindow::onSetDpi);
    connect(ui->actionShow_logger, &QAction::toggled, this, &MainWindow::onShowLogger);
    connect(errorListener, &ErrorListener::errorOccured, this, &MainWindow::onError);

    auto scene = new QGraphicsScene(this);
	ui->graphicsView->setScene(scene);

    vertScroll = ui->graphicsView->verticalScrollBar();
    vertScroll->installEventFilter(this);

    saveScale = dpiDialog->getDpi() / logicalDpiX();
    ui->actionSet_DPI->setText("Set DPI (" + QString::number(dpiDialog->getDpi()) + ")");

    proceedGrammar(QFileInfo("./VirtDiagramsDSL/rules.txt"));
}

void MainWindow::initDialogs() {
    QStringList saveMimeTypeFilters({"image/jpeg", "image/png", "image/svg+xml", "application/pdf"});
    QStringList openMimeTypeFilters({"text/plain"});

    saveDialog = new QFileDialog(this);
    saveDialog->setMimeTypeFilters(saveMimeTypeFilters);
    saveDialog->setAcceptMode(QFileDialog::AcceptSave);

    openDialog = new QFileDialog(this);
    openDialog->setMimeTypeFilters(openMimeTypeFilters);

    dpiDialog = new DpiDialog(this);
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
    if (obj == vertScroll) {
        if (event->type() == QEvent::Wheel) {
            return true;
        }
    }
    return false;
}

void MainWindow::onOpenAction()
{
    if (openDialog->exec() == QDialog::Accepted) {
        QString filename = openDialog->selectedFiles().first();
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

void MainWindow::proceedGrammar(QFileInfo path)
{
    std::ifstream stream;
    stream.open(path.filePath().toStdString());
    if (!stream.good()) {
        log("Unable to open " + path.filePath());
        ui->actionShow_logger->setChecked(true);
        return;
    }
    antlr4::ANTLRInputStream input(stream);
    MetaGrammarLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    MetaGrammarParser parser(&tokens);

    parser.addErrorListener(errorListener);
    lexer.addErrorListener(errorListener);

    log("Proceeding " + path.baseName() + " file...");

    GraphicsVisitor visitor;
    auto rulesList = parser.ruleList();
    if (parser.getNumberOfSyntaxErrors() > 0 || lexer.getNumberOfSyntaxErrors() > 0) {
        ui->actionShow_logger->setChecked(true);
        return;
    }
    log("Success");

    curFileName = path;
    setWindowTitle(curFileName.baseName());

    auto widget = visitor.visit(rulesList).as<QGraphicsWidget*>();
    auto scene = ui->graphicsView->scene();
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
    QPixmap pixmap(saveScale * sceneRect.width(), saveScale * sceneRect.height());
    pixmap.fill();
    drawImage(&pixmap);
    pixmap.save(curFileName.baseName() + "SVD.png");
}

void MainWindow::onSaveAsAction()
{
    if (saveDialog->exec() == QDialog::Accepted) {
        QString filename = saveDialog->selectedFiles().first();
        if (!filename.isEmpty()) {
            auto type = saveDialog->selectedMimeTypeFilter();
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
                QPixmap pixmap(saveScale * sceneRect.width(), saveScale * sceneRect.height());
                pixmap.fill();
                drawImage(&pixmap);
                pixmap.save(filename);
            }

        }
    }
}

void MainWindow::onSetDpi()
{
    if (dpiDialog->exec() == QDialog::Accepted) {
        saveScale = dpiDialog->getDpi() / logicalDpiX();
        ui->actionSet_DPI->setText("Set DPI (" + QString::number(dpiDialog->getDpi()) + ")");
    }
}

void MainWindow::onZoomOut()
{
    if (scaleState > -scaleTimes) {
        ui->graphicsView->scale(1.f / scaleFactor, 1.f / scaleFactor);
        scaleState--;
    }
}

void MainWindow::onZoomIn()
{
    if (scaleState < scaleTimes) {
        ui->graphicsView->scale(scaleFactor, scaleFactor);
        scaleState++;
    }
}

void MainWindow::onShowLogger(bool checked)
{
    if (checked) {
        ui->loggerWidget->show();
    }
    else {
        ui->loggerWidget->hide();
    }
}

void MainWindow::log(QString msg)
{
    ui->plainTextEdit->appendPlainText(msg);
}

MainWindow::~MainWindow()
{
    delete ui;
}
