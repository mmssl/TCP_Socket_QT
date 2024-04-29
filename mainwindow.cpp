#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Tcp_Server = new QTcpServer(); // Inti server obj
    if (Tcp_Server->listen(QHostAddress::AnyIPv4), 43000)
    {
        connect(Tcp_Server, &QTcpServer::newConnection, this, &MainWindow::newConnection);
        ui->statusbar->showMessage("TCP server connected");
    }
    else
    {
        QMessageBox::warning(this, "TCP Server Error", Tcp_Server->errorString());

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readSocket()
{
    // Add code for receiving file from client

    QTcpSocket *socket = reinterpret_cast<QTcpSocket*>(sender());
    QByteArray DataBuffer;
    QDataStream socketstream(socket);
    socketstream.setVersion(QDataStream::Qt_6_7);

    socketstream.startTransaction();
    socketstream >> DataBuffer; // Get data from socket stream or from client socket

    if (socketstream.commitTransaction())
    {
        return;
    }

    // Get file header data like file name and data
    QString HeaderData = DataBuffer.mid(0, 128); // Extract header data

    QString FileName = HeaderData.split(",")[0].split(":")[1];
    QString Fileext = FileName.split(":")[1];
    QString Filesize = HeaderData.split(",")[1].split(":")[1];

    DataBuffer = DataBuffer.mid(128); // Get file data only

    QString SaveFilePath = QCoreApplication::applicationDirPath() + "/" + FileName;
    QFile File(SaveFilePath);
    if (File.open(QIODevice::WriteOnly))
    {
        File.write(DataBuffer);
        File.close();
    }



}

void MainWindow::discardSocket()
{
    // Remove clint from the list when the client is disconnected
    QTcpSocket *socket = reinterpret_cast<QTcpSocket*>(sender());
    int idx = Client_List.indexOf(socket);
    if (idx > -1)
    {
        Client_List.removeAt(idx);
    }
    // refresh client list combobox
    ui->comboBox_list->clear();
    foreach(QTcpSocket *sockettemp, Client_List)
    {
        ui->comboBox_list->addItem(QString::number(sockettemp->socketDescriptor()));
    }
    socket->deleteLater();
}

void MainWindow::newConnection()
{
    while(Tcp_Server->hasPendingConnections())
    {
        // Add new coming TCP client in the server
        AddToSocketList(Tcp_Server->nextPendingConnection());
    }
}

void MainWindow::AddToSocketList(QTcpSocket *socket)
{
    Client_List.append(socket);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::discardSocket);
    ui->textEdit_Message->append("Client is connected to server Socket ID: " + QString::number(socket->socketDescriptor()));
    ui->comboBox_list->addItem(QString::number(socket->socketDescriptor()));

}

void MainWindow::Send_File(QTcpSocket *socket, QString filename)
{
    if (socket)
    {
        if(socket->isOpen())
        {
            QFile filedata(filename);
            if(filedata.open(QIODevice::ReadOnly))
            {
                QFileInfo fileinfo(filedata);
                QString FileNameWithExt(fileinfo.fileName()); // filename info is here

                QDataStream socketstream(socket);
                socketstream.setVersion(QDataStream::Qt_6_7);

                // This code used for sending data
                QByteArray header;
                header.prepend("filename" + FileNameWithExt.toUtf8() + ", filesize: " + QString::number(filedata.size()).toUtf8());
                header.resize(128);

                // Add file data
                QByteArray ByteFileData = filedata.readAll();
                ByteFileData.prepend(header);

                // Write in socket
                socketstream << ByteFileData;
            }
            else
            {
                qDebug() << "File not open";
            }
        }
        else
        {
            qDebug() << "Client Socket not open";
        }
    }
    else
    {
        qDebug() << "Client Socket is invalid";
    }
}

void MainWindow::on_pushButton_send_clicked()
{
    // File Browser
    QString FilePath = QFileDialog::getOpenFileName(this, "Select file ", QCoreApplication::applicationDirPath(), "File");

    // Send file to all connected client
    if (ui->comboBox_type->currentText() == "Broadcast")
    {
        foreach (QTcpSocket *socketTemp, Client_List)
        {
            Send_File(socketTemp, FilePath);
        }
    }
    else if (ui->comboBox_type->currentText() == "Receiver")
    {
        // Send File to selected client
        QString recieverid = ui->comboBox_list->currentText();
        foreach (QTcpSocket *socketTemp, Client_List)
        {
            if (socketTemp->socketDescriptor() == recieverid.toLongLong())
            {
                Send_File(socketTemp, FilePath);
            }
        }
    }
}



