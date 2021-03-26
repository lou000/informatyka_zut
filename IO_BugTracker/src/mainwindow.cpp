#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    window = new FramelessWindow();
    Queries::initDb("login");
    login();
}

void MainWindow::login()
{
    auto mainwidget = new QWidget(this);
    window->setContent(mainwidget);
    window->setWindowTitle("Login  -  BugTracker");
    auto layout = new QVBoxLayout();
    mainwidget->setLayout(layout);
    auto login = new QLineEdit(mainwidget);
    QFont font = QFont("Verdana");
    font.setPointSize(14);
    login->setMinimumSize(200, 50);
    login->setMaximumSize(300, 50);
    login->setPlaceholderText("Login...");
    login->setFont(font);
    login->setAlignment(Qt::AlignHCenter);
    layout->addWidget(login, 0, Qt::AlignHCenter);
    auto password = new QLineEdit(mainwidget);
    password->setMinimumSize(200, 50);
    password->setMaximumSize(300, 50);
    password->setPlaceholderText("Password...");
    password->setEchoMode(QLineEdit::EchoMode::Password);
    password->setFont(font);
    password->setAlignment(Qt::AlignHCenter);
    layout->addWidget(password, 0, Qt::AlignHCenter);
    auto button = new QPushButton("Sign In", mainwidget);
    layout->addWidget(button, 0, Qt::AlignHCenter);
    button->setShortcut(QKeySequence(Qt::Key_Return));
    button->setMinimumSize(120, 30);

    QObject::connect(button, &QPushButton::clicked, this, [=]
    {
        switch(checkLogin(login->text(), password->text()))
        {
        case MainWindow::Success:
            window->close();
            window->deleteLater();
            window = nullptr;
            init();
            emit show();
            break;
        case MainWindow::Fail:
            infoBox("Wrong credentials. Try again");
            break;
        case MainWindow::ChangePassword:
            mainwidget->close();
            window->hide();
            changePassword(login->text());
            break;
        }
    });
    window->show();
}

void MainWindow::changePassword(const QString &login)
{
    auto mainwidget = new QWidget(this);
    window->setContent(mainwidget);
    auto layout = new QVBoxLayout();
    mainwidget->setLayout(layout);
    QFont font = QFont("Verdana");
    font.setPointSize(14);

    auto text = new QLabel(" This is your first login,\nplease setup a password.");
    text->setFont(font);
    text->setStyleSheet("QLabel { color : grey; }");

    layout->addWidget(text, 0, Qt::AlignHCenter);
    auto password = new QLineEdit(mainwidget);
    password->setMinimumSize(200, 50);
    password->setMaximumSize(300, 50);
    password->setPlaceholderText("Password...");
    password->setEchoMode(QLineEdit::EchoMode::Password);
    password->setFont(font);
    password->setAlignment(Qt::AlignHCenter);
    layout->addWidget(password, 0, Qt::AlignHCenter| Qt::AlignTop);
    auto repeat = new QLineEdit(mainwidget);
    repeat->setMinimumSize(200, 50);
    repeat->setMaximumSize(300, 50);
    repeat->setPlaceholderText("Repeat pass...");
    repeat->setEchoMode(QLineEdit::EchoMode::Password);
    repeat->setFont(font);
    repeat->setAlignment(Qt::AlignHCenter);
    layout->addWidget(repeat, 0, Qt::AlignHCenter| Qt::AlignTop);
    auto button = new QPushButton("Sign In", mainwidget);
    layout->addWidget(button, 0, Qt::AlignHCenter| Qt::AlignTop);
    button->setShortcut(QKeySequence(Qt::Key_Return));
    button->setMinimumSize(120, 30);

    QObject::connect(button, &QPushButton::clicked, this, [=]
    {
        if(password->text()!=repeat->text())
            infoBox("Passwords do not match!");
        else if(password->text().length()<3)
            infoBox("Password is too short.");
        else
        {
            addNewHashAndSalt(login, password->text());
            window->close();
            window->deleteLater();
            window = nullptr;
            init();
            emit show();
        }
    });
    window->show();
}

MainWindow::LoginStatus MainWindow::checkLogin(const QString &login, const QString &password)
{
    auto q = getUserPassword(login);
    q.next();
    QString hash = q.value(0).toString();
    QString salt = q.value(1).toString();
    int count = q.value(2).toInt();

    if((hash.isNull() || salt.isNull()) && count>0)
        return LoginStatus::ChangePassword;

    q.finish();

    QString saltedPass = password + salt;
    hashwrapper *hashinator = new sha512wrapper();
    if(hashinator->getHashFromString(saltedPass.toStdString()) == hash.toStdString())
        return LoginStatus::Success;
    else return LoginStatus::Fail;

}

void MainWindow::addNewHashAndSalt(const QString &login, const QString &password)
{
    hashwrapper *hashinator = new sha512wrapper();
    QString salt = QString::fromStdString(hashinator->getHashFromString(QDateTime::currentDateTime().toString("yyyymmddhhmmsszzz").toStdString()));
    QString saltedPass = password + salt;
    QString hash = QString::fromStdString(hashinator->getHashFromString(saltedPass.toStdString()));
    setUserPassword(login, hash, salt);
}

QSqlQuery MainWindow::getUserPassword(const QString &login)
{

    auto q = Queries::getUserPassword(login);
    if(!q.exec())
    {
        infoBox("SQL Error in getUserPassword query:" + q.lastError().text());
    }
    return q;
}

QSqlQuery MainWindow::setUserPassword(const QString &login, const QString &hash, const QString &salt)
{
    auto q = Queries::setUserPassword(login, hash, salt);
    if(!q.exec())
        infoBox("SQL Error in setUserPassword query:" + q.lastError().text());
    return q;
}

void MainWindow::init()
{
    this->controller = new ThreadController(120000);
    this->mainView = new BugView(controller, this);
    this->aWindows = new ActionWindows(this, controller);

    mainView->setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);
    auto editAction = new QAction("Edit");
    mainView->addAction(editAction);
    auto deleteAction = new QAction("Delete");
    mainView->addAction(deleteAction);
    auto addUserAction = new QAction("Add/Remove recources");
    mainView->addAction(addUserAction);

    auto leftBar = new QDockWidget(this);
    leftBar->setWindowTitle("Actions:");
    leftBar->setMinimumWidth(170);
    leftBar->setFeatures(QDockWidget::NoDockWidgetFeatures);
    auto leftBarWidget = new QWidget();
    leftBar->setWidget(leftBarWidget);
    auto leftBarLayout = new QGridLayout();
    leftBarWidget->setLayout(leftBarLayout);

    auto viewMode = new QComboBox(this);
    viewMode->addItem("Issues");
    viewMode->addItem("Projects");
    viewMode->addItem("Users");
    viewMode->setMinimumHeight(30);
    leftBarLayout->addWidget(new QLabel("Select View:"), 0, 0, 1, 2, Qt::AlignBottom);
    leftBarLayout->addWidget(viewMode, 1, 0, 1, 3);

    auto addProjectButton = new QPushButton("Add Item");
    addProjectButton->setMinimumHeight(50);
    addProjectButton->setMinimumWidth(150);
    leftBarLayout->addWidget(addProjectButton, 4, 0, 1, 2);

    leftBarLayout->addItem(new QSpacerItem(1, 200), 5, 0, 1, 2);

    auto editSelection = new QPushButton("Edit Selection");
    editSelection->setMinimumHeight(50);
    leftBarLayout->addWidget(editSelection, 6, 0, 1, 2);

    auto addResources = new QPushButton("Add/Remove recources");
    addResources->setMinimumHeight(50);
    leftBarLayout->addWidget(addResources, 8, 0, 1, 2);

    auto deleteSelection = new QPushButton("Delete Selection");
    deleteSelection->setMinimumHeight(50);
    leftBarLayout->addWidget(deleteSelection, 7, 0, 1, 2);

    leftBarLayout->addItem(new QSpacerItem(1, 700), 9, 0, 1, 2);


    QObject::connect(viewMode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int v){
        switch (v) {
        case 0:
            mainView->switchMode(BugView::ViewMode::Issue);
            break;
        case 1:
            mainView->switchMode(BugView::ViewMode::Project);
            break;
        case 2:
            mainView->switchMode(BugView::ViewMode::User);
            break;
        default:
            break;
        }
    });

    QObject::connect(controller, SIGNAL(updateIssues()), mainView, SLOT(fillIssues()));
    QObject::connect(controller, SIGNAL(updateUsers()), mainView, SLOT(fillUsers()));
    QObject::connect(controller, SIGNAL(updateProjects()), mainView, SLOT(fillProjects()));

    QObject::connect(addProjectButton, &QPushButton::clicked, aWindows, [=]
    {
        switch (mainView->getMode()) {
        case BugView::ViewMode::Issue:
            aWindows->showIssueWindow();
            break;
        case BugView::ViewMode::Project:
            aWindows->showProjectWindow();
            break;
        case BugView::ViewMode::User:
            aWindows->showUserWindow();
            break;
        default:
            break;
        }
    });

    auto editLambda = [=]
    {
        auto selection = mainView->selectedRanges();
        if(selection.length() == 1 && selection.at(0).rowCount()==1)
        {
            int row = selection.at(0).topRow();
            switch (mainView->getMode()) {
            case BugView::ViewMode::Issue:
                if(row<controller->issues.length())
                    aWindows->showIssueWindow(controller->issues.at(row));
                else
                    aWindows->showIssueWindow();
                break;

            case BugView::ViewMode::Project:
                if(row<controller->projects.length())
                    aWindows->showProjectWindow(controller->projects.at(row));
                else
                    aWindows->showProjectWindow();
                break;

            case BugView::ViewMode::User:
                if(row<controller->users.length())
                    aWindows->showUserWindow(controller->users.at(row));
                else
                    aWindows->showUserWindow();
                break;

            default:
                break;
            }
        }
    };

    QObject::connect(editSelection, &QPushButton::clicked, aWindows, editLambda);
    QObject::connect(editAction, &QAction::triggered, aWindows, editLambda);
    QObject::connect(mainView, &QTableWidget::cellDoubleClicked, aWindows, editLambda);


    auto deleteLambda = [=]
    {
        auto selection = mainView->selectedRanges();
        if(selection.length() == 1 && selection.at(0).rowCount()==1)
        {
            QMessageBox msgBox;
            msgBox.setText("Are you sure you want to delete selected item?");
            msgBox.setInformativeText("This action will be permament.");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::No);
            int ret = msgBox.exec();
            if(ret == QMessageBox::Yes)
            {
            int row = selection.at(0).topRow();
                switch (mainView->getMode()) {
                case BugView::ViewMode::Issue:
                    if(row<controller->issues.length())
                        controller->deleteIssue(controller->issues.at(row)->id());
                    break;
                case BugView::ViewMode::Project:
                    if(row<controller->projects.length())
                        controller->deleteProject(controller->projects.at(row)->id());
                    break;
                case BugView::ViewMode::User:
                    if(row<controller->users.length())
                        controller->deleteUser(controller->users.at(row)->id());
                    break;
                default:
                    break;
                }
            }
        }
    };
    QObject::connect(deleteSelection, &QPushButton::clicked, aWindows, deleteLambda);
    QObject::connect(deleteAction, &QAction::triggered, aWindows, deleteLambda);


    auto addUserToIssueLambda = [=]
    {
        auto selection = mainView->selectedRanges();
        if(selection.length() == 1 && selection.at(0).rowCount()==1)
        {
            int row = selection.at(0).topRow();
            if(mainView->getMode() == BugView::ViewMode::Issue)
                if(row<controller->issues.length())
                    aWindows->showAddUserToIssue(controller->issues.at(row));
        }
    };

    QObject::connect(addUserAction, &QAction::triggered, aWindows, addUserToIssueLambda);
    QObject::connect(addResources, &QPushButton::clicked, aWindows, addUserToIssueLambda);
    QObject::connect(mainView, &BugView::modeChanged, addResources, [=](BugView::ViewMode mode)
    {
        if(mode == BugView::ViewMode::Issue)
            addResources->show();
        else
            addResources->hide();
    });

    setCentralWidget(mainView);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, leftBar);
    setWindowIcon(QIcon());
    this->setFixedSize(QSize(1800, 900));
    this->setContentsMargins(10, 10, 10, 10);
    QScreen* mainScreen = QApplication::screens().at(0);
    emit move((mainScreen->size().width()-this->width()) / 2, (mainScreen->size().height()-this->height()) / 2);
}


