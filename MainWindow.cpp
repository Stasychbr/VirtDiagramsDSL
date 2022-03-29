#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QGraphicsWidget>
#include <QGraphicsScene>

#include <QFileDialog>
#include <QActionGroup>
#include <QSpinBox>

#include <antlr4-runtime.h>

#include "antlr/MetaGrammar/MetaGrammarParser.h"
#include "antlr/MetaGrammar/MetaGrammarLexer.h"

#include "GraphicsVisitor.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    auto dpiGroup = new QActionGroup(this);
    dpiGroup->addAction(ui->dpi100);
    dpiGroup->addAction(ui->dpi300);
    dpiGroup->addAction(ui->dpi500);
    dpiGroup->setExclusionPolicy(QActionGroup::ExclusionPolicy::Exclusive);

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onOpenAction);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSaveAction);
    connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::onSaveAsAction);
    connect(ui->actionZoom_in, &QAction::triggered, this, &MainWindow::onZoomIn);
    connect(ui->actionZoom_out, &QAction::triggered, this, &MainWindow::onZoomOut);
    connect(dpiGroup, &QActionGroup::triggered, this, &MainWindow::onSetDpi);

    auto scene = new QGraphicsScene(this);
	ui->graphicsView->setScene(scene);

    saveScale = 100.f / this->logicalDpiX();

	proceedGrammar("rules.txt");
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
    scene->clear();
    scene->addItem(widget);
    widget->setMaximumSize(200, 200);
}

void MainWindow::saveImage(QString path)
{
    auto sceneRect = ui->graphicsView->scene()->itemsBoundingRect();
    QPixmap pixmap(saveScale * sceneRect.width(), saveScale * sceneRect.height());
    pixmap.fill();
    QPainter painter(&pixmap);
    ui->graphicsView->scene()->render(&painter);
    if (pixmap.save(path)) {
        qDebug() << "Image is saved";
    }
    else {
        qDebug() << "Error during image save!";
    }
}

void MainWindow::onSaveAction()
{
    saveImage("Semantic Diagram.png");
}

void MainWindow::onSaveAsAction()
{
    QStringList mimeTypeFilters({"image/jpeg", "image/png", "image/svg+xml", "application/pdf"});

    QFileDialog dialog(this);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
//    QVBoxLayout layout(dialog.window());
//    QSpinBox dpiSelect;
//    layout.addWidget(dpiSelect.window());
//    dialog.setLayout(layout.layout());
    if (dialog.exec() == QDialog::Accepted) {
        QString filename = dialog.selectedFiles().first();
        if (!filename.isEmpty()) {
            saveImage(filename);
        }
    }
}

void MainWindow::onSetDpi(QAction* action)
{
    float dpi = 0;
    if (action == ui->dpi100) {
        dpi = 100;
    }
    else if (action == ui->dpi300) {
        dpi = 300;
    }
    else {
        dpi = 500;
    }
    saveScale = dpi / logicalDpiX();
}

void MainWindow::onZoomOut()
{
    if (scaleState > -scaleTimes) {
        ui->graphicsView->scale(1 - scaleFactor, 1 - scaleFactor);
        scaleState--;
    }
}

void MainWindow::onZoomIn()
{
    if (scaleState < scaleTimes) {
        ui->graphicsView->scale(1 + scaleFactor, 1 + scaleFactor);
        scaleState++;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


