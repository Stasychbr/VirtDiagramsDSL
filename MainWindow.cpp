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
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    initDialogs();


    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onOpenAction);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSaveAction);
    connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::onSaveAsAction);
    connect(ui->actionZoom_in, &QAction::triggered, this, &MainWindow::onZoomIn);
    connect(ui->actionZoom_out, &QAction::triggered, this, &MainWindow::onZoomOut);
    connect(ui->actionSet_DPI, &QAction::triggered, this, &MainWindow::onSetDpi);

    auto scene = new QGraphicsScene(this);
	ui->graphicsView->setScene(scene);

    saveScale = 600.f / logicalDpiX();

//	proceedGrammar("rules.txt");
}

void MainWindow::initDialogs() {
    QStringList mimeTypeFilters({"image/jpeg", "image/png", "image/svg+xml", "application/pdf"});

    saveDialog = new QFileDialog(this);
    saveDialog->setMimeTypeFilters(mimeTypeFilters);
    saveDialog->setAcceptMode(QFileDialog::AcceptSave);

    dpiDialog = new DpiDialog(this);
}

void MainWindow::onOpenAction()
{
    QStringList mimeTypeFilters({"text/plain"});
    QFileDialog dialog(this);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    if (dialog.exec() == QDialog::Accepted) {
        QString filename = dialog.selectedFiles().first();
        if (!filename.isEmpty()) {
            proceedGrammar(filename);
        }
    }
}

void MainWindow::proceedGrammar(QString path)
{
    std::ifstream stream;
    stream.open(path.toStdString());

    antlr4::ANTLRInputStream input(stream);
    MetaGrammarLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    MetaGrammarParser parser(&tokens);

    GraphicsVisitor visitor;
    auto rulesList = parser.ruleList();
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
    pixmap.save("Semantic Diagram.png");
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
//        auto menu = menuBar();
//        menu->
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

MainWindow::~MainWindow()
{
    delete ui;
}
