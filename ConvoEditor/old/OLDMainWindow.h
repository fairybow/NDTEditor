/*#pragma once

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileInfo>
#include <QMainWindow>
#include <QMimeData>
#include <QUrl>

#include "JsonModel.h"
#include "JsonView.h"

// Functions as our Presenter
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr)
        : QMainWindow(parent)
    {
        setAcceptDrops(true);
        setCentralWidget(jsonView_);

        connect
        (
            jsonModel_,
            &JsonModel::loaded,
            this,
            &MainWindow::onJsonModelLoaded_
        );

        connect
        (
            jsonView_,
            &JsonView::roleChangeRequested,
            this,
            [&](const QString& from, const QString& to)
            {
                jsonModel_->replaceRole(from, to);
            }
        );

        connect
        (
            jsonView_,
            &JsonView::roleAddRequested,
            this,
            [&](const QString& role)
            {
                jsonModel_->addRole(role);
            }
        );
    }

protected:
    virtual void dragEnterEvent(QDragEnterEvent* event) override
    {
        // Accept .json file paths
        if (event->mimeData()->hasUrls())
        {
           auto urls = event->mimeData()->urls();

           // We can only open one
           if (!urls.isEmpty())
           {
               QUrl url = urls.at(0);

               if (url.isLocalFile()
                   && QFileInfo(url.toLocalFile()).suffix().toLower() == "json")
               {
                   event->acceptProposedAction();
                   return;
               }
           }
        }

        event->ignore();
    }

    virtual void dropEvent(QDropEvent* event) override
    {
        // We know we have URLs because dragEnterEvent already verified this
        // We also know the first URL has .json extension
        QUrl url = event->mimeData()->urls().at(0);
        auto path = url.toLocalFile();

        if (jsonModel_->load(path))
        {
            setWindowTitle(QFileInfo(path).fileName());
            event->acceptProposedAction();
            activateWindow();

            return;
        }

        // If we get here, loading failed
        event->ignore();
    }

private:
    JsonView* jsonView_ = new JsonView(this);
    JsonModel* jsonModel_ = new JsonModel(this);

private slots:
    void onJsonModelLoaded_()
    {
        // Clear View blocks
        // Create new blocks for each element in the model

        jsonView_->clear();
        jsonView_->initRoles(jsonModel_->roles());

        for (auto& element : jsonModel_->elements())
        {
            jsonView_->add
            (
                element.role,
                element.speech,
                element.eot
            );
        }
    }
};
*/