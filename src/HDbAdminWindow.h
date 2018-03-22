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
