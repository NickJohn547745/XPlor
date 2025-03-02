#include "preferenceeditor.h"
#include "ui_preferenceeditor.h"

PreferenceEditor::PreferenceEditor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PreferenceEditor)
{
    ui->setupUi(this);

    ui->frame_View->show();
    ui->frame_TreeWidget->hide();
    ui->frame_FileEditors->hide();

    connect(ui->listWidget_Categories, &QListWidget::itemSelectionChanged, this, [this]() {
        const QString itemText = ui->listWidget_Categories->selectedItems().first()->text();
        if (itemText == "View") {
            ui->frame_View->show();
            ui->frame_TreeWidget->hide();
            ui->frame_FileEditors->hide();
        } else if (itemText == "Tree Widget") {
            ui->frame_View->hide();
            ui->frame_TreeWidget->show();
            ui->frame_FileEditors->hide();
        } else if (itemText == "File Editors") {
            ui->frame_View->hide();
            ui->frame_TreeWidget->hide();
            ui->frame_FileEditors->show();
        }
    });
}

PreferenceEditor::~PreferenceEditor()
{
    delete ui;
}
