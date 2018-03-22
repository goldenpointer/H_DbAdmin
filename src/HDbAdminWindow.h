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

#ifndef HDBADMIN_H
#define HDBADMIN_H

#include <QMainWindow>
#include <QSortFilterProxyModel>

namespace Ui
{
    class HDbAdmin;
}

class HttpAdapter;

class HDbAdminWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit HDbAdminWindow(QWidget *parent = nullptr);
        ~HDbAdminWindow();

    private slots:
        void on_comboBoxHttpRequests_currentIndexChanged();
        void on_treeViewDBStructure_clicked(const QModelIndex &index);
        void on_pushButtonSubmit_clicked();
        void on_pushButtonReset_clicked();
        void onhttpGetFinished(const QJsonDocument &document);
        void onhttpPutFinished(const QJsonDocument &document);
        void onhttpPostFinished(const QJsonDocument &document);
        void onhttpDeleteFinished(const QJsonDocument &document);
        void onhttpHeadFinished(const QJsonDocument &document);
        void onhttpCopyFinished(const QJsonDocument &document);
        void onhttpAnyFinished(const QJsonDocument &document);

    private:
        void setModelFromFile(const QString &textFile);

        Ui::HDbAdmin *ui;

        HttpAdapter *m_httpAdapter = nullptr;

        enum TreeColumn : int
        {
            HttpApi = 0,
            Description
        };
};

#endif // HDBADMIN_H
