/****************************************************************************
**
** BSD 2-Clause License
**
** Copyright (c) 2018, mikispring
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**
**   * Redistributions of source code must retain the above copyright notice, this
**     list of conditions and the following disclaimer.
**
**   * Redistributions in binary form must reproduce the above copyright notice,
**     this list of conditions and the following disclaimer in the documentation
**     and/or other materials provided with the distribution.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
** DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
** SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
** CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
** OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************/

#include <QFile>
#include <QIODevice>
#include <QDebug>

#include "ui_HDbAdmin.h"

#include "HDbAdminWindow.h"
#include "HttpAdapter.h"
#include "qbase/examples/widgets/itemviews/simpletreemodel/treemodel.h"

HDbAdminWindow::HDbAdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HDbAdmin),
    m_httpAdapter(new HttpAdapter(this))
{
    ui->setupUi(this);

    on_comboBoxHttpRequests_currentIndexChanged();

    connect(m_httpAdapter, &HttpAdapter::httpGetFinished, this, &onhttpGetFinished);
    connect(m_httpAdapter, &HttpAdapter::httpPutFinished, this, &onhttpPutFinished);
    connect(m_httpAdapter, &HttpAdapter::httpPostFinished, this, &onhttpPostFinished);
    connect(m_httpAdapter, &HttpAdapter::httpDeleteFinished, this, &onhttpDeleteFinished);
    connect(m_httpAdapter, &HttpAdapter::httpHeadFinished, this, &onhttpHeadFinished);
    connect(m_httpAdapter, &HttpAdapter::httpCopyFinished, this, &onhttpCopyFinished);
    connect(m_httpAdapter, &HttpAdapter::httpAnyFinished, this, &onhttpAnyFinished);
}

HDbAdminWindow::~HDbAdminWindow()
{
    delete ui;
}

//Select text file based on Combobox options.
void HDbAdminWindow::on_comboBoxHttpRequests_currentIndexChanged()
{
    if(ui->comboBoxHttpRequests->currentIndex() == 0)   // HTTP GET
    {
        setModelFromFile("TreeModelGet.txt");
    }
    else if(ui->comboBoxHttpRequests->currentIndex() == 1)  // HTTP PUT
    {
        setModelFromFile("TreeModelPut.txt");
    }
    else if(ui->comboBoxHttpRequests->currentIndex() == 2)  // HTTP POST
    {
        setModelFromFile("TreeModelPost.txt");
    }
    else if(ui->comboBoxHttpRequests->currentIndex() == 3)  // HTTP DELETE
    {
        setModelFromFile("TreeModelDelete.txt");
    }
    else if(ui->comboBoxHttpRequests->currentIndex() == 4)  // HTTP HEAD
    {
        setModelFromFile("TreeModelHead.txt");
    }
    else if(ui->comboBoxHttpRequests->currentIndex() == 5)  // HTTP COPY
    {
        setModelFromFile("TreeModelCopy.txt");
    }
    else if(ui->comboBoxHttpRequests->currentIndex() == 6)  // HTTP ANY
    {
        setModelFromFile("TreeModelAny.txt");
    }
    else
    {
        qCritical() << "Unknown TreeModel File type." << endl;
    }
}

// Get data from the text file and show in TreeView
void HDbAdminWindow::setModelFromFile(const QString& textFile)
{
    QString resourcefileName(":" + textFile);
    TreeModel *treemodel;

    QFile file(resourcefileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open HTTP API file." << endl;
    }
    else
    {
        qDebug() << "HTTP API file opened." << endl;
        treemodel = new TreeModel(file.readAll(), this);
    }
    file.close();

    ui->treeViewDBStructure->setModel(treemodel);
    ui->treeViewDBStructure->show();
}

void HDbAdminWindow::on_treeViewDBStructure_clicked(const QModelIndex &index)
{
    if(HttpApi == index.column())
    {
        QString api;
        QModelIndex current = index;

        while(current.parent().isValid())
        {
            api = current.data().toString() + api;
            current = current.parent();
        }

        ui->lineEditFromtreeview->setText(api);
    }
}

void HDbAdminWindow::on_pushButtonSubmit_clicked()
{
    if(ui->comboBoxHttpRequests->currentIndex() == 0)   // HTTP GET
    {
        QString url = ui->lineEditUrl->text() + ui->lineEditFromtreeview->text();
        m_httpAdapter->httpGet(url);
    }
    else if(ui->comboBoxHttpRequests->currentIndex() == 1)  // HTTP PUT
    {
        QString url = ui->lineEditUrl->text() + ui->lineEditFromtreeview->text();
        m_httpAdapter->httpPut(url, ui->textEditBody->toPlainText().toUtf8());
    }
    else if(ui->comboBoxHttpRequests->currentIndex() == 2)  // HTTP POST
    {
        QString url = ui->lineEditUrl->text() + ui->lineEditFromtreeview->text();
        m_httpAdapter->httpPost(url, ui->textEditBody->toPlainText().toUtf8());
    }
    else if(ui->comboBoxHttpRequests->currentIndex() == 3)  // HTTP DELETE
    {
        QString url = ui->lineEditUrl->text() + ui->lineEditFromtreeview->text();
        m_httpAdapter->httpDelete(url);
    }
    else if(ui->comboBoxHttpRequests->currentIndex() == 4)  // HTTP HEAD
    {
        QString url = ui->lineEditUrl->text() + ui->lineEditFromtreeview->text();
        m_httpAdapter->httpHead(url);
    }
    else if(ui->comboBoxHttpRequests->currentIndex() == 5)  // HTTP COPY
    {
        QString url = ui->lineEditUrl->text() + ui->lineEditFromtreeview->text();
        m_httpAdapter->httpCopy(url, ui->textEditBody->toPlainText());
    }
    else if(ui->comboBoxHttpRequests->currentIndex() == 6)  // HTTP ANY
    {
        QString url = ui->lineEditUrl->text() + ui->lineEditFromtreeview->text();
        m_httpAdapter->httpAny(url);
    }
    else
    {
        ui->textEditResponse->setText("Unknown Command !!!");
        qCritical() << "Requested an unknown HTTP Method." << endl;
    }
}

void HDbAdminWindow::on_pushButtonReset_clicked()
{
    ui->lineEditUrl->clear();
    ui->lineEditFromtreeview->clear();
    ui->textEditBody->clear();
}

void HDbAdminWindow::onhttpGetFinished(const QJsonDocument &document)
{
    ui->textEditResponse->setText("HTTP GET executed. \n Results: \n");
    ui->textEditResponse->setText(document.toJson());
}

void HDbAdminWindow::onhttpPutFinished(const QJsonDocument &document)
{
    ui->textEditResponse->setText("HTTP PUT executed. \n Results: \n");
    ui->textEditResponse->setText(document.toJson());
}

void HDbAdminWindow::onhttpPostFinished(const QJsonDocument &document)
{
    ui->textEditResponse->setText("HTTP POST executed. \n Results: \n");
    ui->textEditResponse->setText(document.toJson());
}

void HDbAdminWindow::onhttpDeleteFinished(const QJsonDocument &document)
{
    ui->textEditResponse->setText("HTTP DELETE executed. \n Results: \n");
    ui->textEditResponse->setText(document.toJson());
}

void HDbAdminWindow::onhttpHeadFinished(const QJsonDocument &document)
{
    ui->textEditResponse->setText("HTTP HEAD executed. \n Results: \n");
    ui->textEditResponse->setText(document.toJson());
}

void HDbAdminWindow::onhttpCopyFinished(const QJsonDocument &document)
{
    ui->textEditResponse->setText("HTTP COPY executed. \n Results: \n");
    ui->textEditResponse->setText(document.toJson());
}

void HDbAdminWindow::onhttpAnyFinished(const QJsonDocument &document)
{
    ui->textEditResponse->setText("HTTP ANY executed. \n Results: \n");
    ui->textEditResponse->setText(document.toJson());
}
