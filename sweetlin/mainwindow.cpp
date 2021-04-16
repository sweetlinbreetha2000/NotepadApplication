#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QFileDialog>
#include<QFontDialog>
#include<QPrinter>
#include<QPrintDialog>
#include<QColorDialog>
#include<QColor>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actioncut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actioncopy_triggered()
{
     ui->textEdit->copy();
}

void MainWindow::on_actionpaste_triggered()
{
     ui->textEdit->paste();
}

void MainWindow::on_actionundo_triggered()
{
     ui->textEdit->undo();
}

void MainWindow::on_actionredo_triggered()
{
   ui->textEdit->redo();
}

void MainWindow::on_actionnew_triggered()
{
    file_path=" ";
    ui->textEdit->setText("");
}

void MainWindow::on_actionopen_triggered()
{
    QString file_name=QFileDialog::getOpenFileName(this,"open the file");
    QFile file(file_name);
    file_path=file_name;
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::warning (this,"..","file not open");
        return;
    }
    QTextStream in(&file);
    QString text=in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionsave_triggered()
{

    QFile file(file_path);
    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning (this,"..","file not open");
        return;
    }
    QTextStream out(&file);
    QString text=ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();

}

void MainWindow::on_actionsave_2_triggered()
{
    QString file_name=QFileDialog::getSaveFileName(this,"open the file");
    QFile file(file_name);
    file_path=file_name;
    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning (this,"..","file not open");
        return;
    }
    QTextStream out(&file);
    QString text=ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();

}

void MainWindow::on_actionquit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionselect_Font_triggered()
{
    bool fontSelected;
    QFont font=QFontDialog::getFont(&fontSelected,this);
    if(fontSelected)
    {
        ui->textEdit->setFont(font);

    }
}

void MainWindow::on_actionbold_triggered()
{
    QTextCharFormat format;
     format.setFontWeight(QFont::Bold);

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.mergeCharFormat(format);

}

void MainWindow::on_actionitlaic_triggered()
{
    ui->textEdit->setFontItalic(true);

}

void MainWindow::on_actionfont_background_color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"choose color");
    if(color.isValid()){
        ui->textEdit->setTextBackgroundColor(color);
    }
}

void MainWindow::on_actionfontcolor_triggered()
{
    QTextCursor cursor( ui->textEdit->textCursor() );

    QTextCharFormat format;

    format.setForeground( QBrush( QColor( "yellow" ) ) );
    cursor.setCharFormat( format );
}

void MainWindow::on_actionprint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("desired printer name");
    QPrintDialog dialog(&printer,this);
    if(dialog.exec() == QDialog::Rejected) return;
    ui->textEdit->print(&printer);


}

void MainWindow::on_actionunderline_triggered()
{
    ui->textEdit->setFontUnderline(true);
}
