#include "actionwindows.h"
#include <QHeaderView>

ActionWindows::ActionWindows(QWidget* parent, ThreadController* controller)
               :controller(controller)
{
    this->setParent(parent);
    this->close();
    initIssueWindow();
    initUserWindow();
    initProjectWindow();
    initAddUserToIssue();
}

void ActionWindows::initIssueWindow()
{
    this->issueWindow = new QDockWidget(this->parentWidget());
    issueWindow->setAttribute(Qt::WA_DeleteOnClose, false);
    issueWindow->setWindowTitle("Issue:");
    issueWindow->setFeatures(QDockWidget::AllDockWidgetFeatures);
    issueWindow->setFloating(true);
    auto issueTypeWidget = new QWidget(this->parentWidget());
    issueWindow->setWidget(issueTypeWidget);
    auto addIssueLayout = new QGridLayout();
    issueTypeWidget->setLayout(addIssueLayout);

    issueType = new QComboBox(this);
    auto&& issueMetaEnum = QMetaEnum::fromType<IssueTicket::IssueType>();
    addIssueLayout->addWidget(issueType, 0, 1);
    addIssueLayout->addWidget(new QLabel("Issue type:"),0 ,0, Qt::AlignRight);

    for(int i=0; i<issueMetaEnum.keyCount(); i++)
    {
        issueType->addItem(issueMetaEnum.key(i));
    }
    issueType->setCurrentIndex(-1);

    issueShortDesc = new QTextEdit();
    issueShortDesc->setPlaceholderText("Short Description");
    addIssueLayout->addWidget(issueShortDesc, 2, 0, 2, 4);

    issueDesc = new QTextEdit();
    issueDesc->setPlaceholderText("Full Description");
    addIssueLayout->addWidget(issueDesc, 4, 0, 4, 4);


    issueStatus = new QComboBox(this);
    addIssueLayout->addWidget(issueStatus, 0, 3);
    addIssueLayout->addWidget(new QLabel("Status:"),0 ,2, Qt::AlignRight);


    auto&& statusMetaEnum = QMetaEnum::fromType<IssueTicket::Status>();
    for(int i=0; i<statusMetaEnum.keyCount(); i++)
    {
        issueStatus->addItem(statusMetaEnum.key(i));
    }
    issueStatus->setCurrentIndex(-1);

    issueProjName = new QComboBox(this);
    addIssueLayout->addWidget(issueProjName, 1, 1);
    addIssueLayout->addWidget(new QLabel("Project ID:"),1 ,0, Qt::AlignRight);

    for(auto proj : controller->projects)
        issueProjName->addItem(proj->name());
    issueProjName->setCurrentIndex(-1);

    issueAdd = new QPushButton("Add");
    addIssueLayout->addWidget(issueAdd, 8, 0, 2, 2);
    issueAdd->hide();

    issueAccept = new QPushButton("Accept");
    addIssueLayout->addWidget(issueAccept, 8, 0, 2, 2);
    issueAccept->hide();

    issueDiscard = new QPushButton("Discard");
    addIssueLayout->addWidget(issueDiscard, 8, 2, 2, 2);

    QObject::connect(issueAdd, &QPushButton::clicked, this, [=]
        {
        if(issueShortDesc->toPlainText().length()<1 || issueStatus->currentIndex()==-1 || issueType->currentIndex()==-1)
            infoBox("Please fill out all the required fields.");
        else
        {
            emit controller->addIssue(stringToEnum<IssueTicket::IssueType>(issueType->currentText()),
                                      issueShortDesc->toPlainText(), issueDesc->toPlainText(),
                                      stringToEnum<IssueTicket::Status>(issueStatus->currentText()),
                                      controller->projects.at(issueProjName->currentIndex())->id());
            issueType->setCurrentIndex(-1);
            issueShortDesc->clear();
            issueDesc->clear();
            issueStatus->setCurrentIndex(-1);
            issueProjName->setCurrentIndex(-1);
        }
        });

    QObject::connect(issueDiscard, &QPushButton::clicked, this, [=]
        {
            issueWindow->close();
        });

    QObject::connect(controller, &ThreadController::updateProjects, this, [=]
    {
        int lastIndex = issueProjName->currentIndex();
        issueProjName->clear();
        for(auto proj : controller->projects)
            issueProjName->addItem(proj->name());
        issueProjName->setCurrentIndex(lastIndex);
    });
    issueWindow->close();
}

void ActionWindows::showIssueWindow(IssueTicket* issue)
{
    if(issue)
    {
        for(int i=0; i<issueType->count(); i++)
        {
            if(stringToEnum<IssueTicket::IssueType>(issueType->itemText(i))==issue->type())
            {
                issueType->setCurrentIndex(i);
                break;
            }
        }

        issueShortDesc->setText(issue->shortDescription());
        issueDesc->setText(issue->description());

        for(int i=0; i<issueStatus->count(); i++)
        {
            if(stringToEnum<IssueTicket::Status>(issueStatus->itemText(i))==issue->status())
            {
                issueStatus->setCurrentIndex(i);
                break;
            }
        }

        for(int i=0; i<controller->projects.length(); i++)
        {
            if(controller->projects.at(i)->name() == issue->project())
                issueProjName->setCurrentIndex(i);
        }
        issueAdd->hide();
        issueAccept->show();
        issueAccept->disconnect();
        QObject::connect(issueAccept, &QPushButton::clicked, this, [=]
            {
            if(issueShortDesc->toPlainText().length()<1 || issueStatus->currentIndex()==-1 || issueType->currentIndex()==-1 || issueProjName->currentIndex()==-1)
                infoBox("Please fill out all the required fields.");
            else
            {
                IssueTicket::Status stat = stringToEnum<IssueTicket::Status>(issueStatus->currentText());
                emit controller->editIssue(issue->id(), stringToEnum<IssueTicket::IssueType>(issueType->currentText()),
                                          issueShortDesc->toPlainText(), issueDesc->toPlainText(),stat,
                                          controller->projects.at(issueProjName->currentIndex())->id(),
                                          issue->status()==stat ? issue->dateStatusChanged() : QDateTime::currentDateTime());
                issueWindow->close();
            }
            });
    }
    else
    {
        issueType->setCurrentIndex(-1);
        issueShortDesc->clear();
        issueDesc->clear();
        issueStatus->setCurrentIndex(-1);
        issueProjName->setCurrentIndex(-1);
        issueAdd->show();
        issueAccept->hide();
    }

    issueWindow->setWindowFlag(Qt::WindowStaysOnTopHint);//Windows is retarded and has to be reminded everytime
    issueWindow->show();
    issueWindow->raise();
}

void ActionWindows::initUserWindow()
{
    this->userWindow = new QDockWidget(this->parentWidget());
    userWindow->setAttribute(Qt::WA_DeleteOnClose, false);

    userWindow->setWindowTitle("User:");
    userWindow->setFeatures(QDockWidget::AllDockWidgetFeatures);
    userWindow->setFloating(true);
    auto addUserWidget = new QWidget(this->parentWidget());
    userWindow->setWidget(addUserWidget);
    auto addUserLayout = new QGridLayout();
    addUserWidget->setLayout(addUserLayout);

    userLogin = new QLineEdit();
    userLogin->setPlaceholderText("Login");
    addUserLayout->addWidget(userLogin, 0, 0, 1, 2);

    userName = new QLineEdit();
    userName->setPlaceholderText("Name");
    addUserLayout->addWidget(userName, 0, 2, 1, 2);

    userSurname = new QLineEdit();
    userSurname->setPlaceholderText("Surname");
    addUserLayout->addWidget(userSurname, 2, 2, 1, 2);


    userPosition = new QComboBox(this);
    auto&& positionMetaEnum = QMetaEnum::fromType<User::UserPosition>();
    for(int i=0; i<positionMetaEnum.keyCount(); i++)
    {
        userPosition->addItem(positionMetaEnum.key(i));
    }
    addUserLayout->addWidget(userPosition, 2, 1, Qt::AlignLeft);
    addUserLayout->addWidget(new QLabel("Position:", this),2 ,0, Qt::AlignRight);

    auto&& permissionsMetaEnum = QMetaEnum::fromType<User::UserPermission>();
    addUserLayout->addItem(new QSpacerItem(300,10), 3, 0, 1, 4,Qt::AlignHCenter);
    addUserLayout->addWidget(new QLabel("Permissions:", this),4 ,0, Qt::AlignBottom);
    for(int i=0; i<permissionsMetaEnum.keyCount(); i++)
    {
        auto box = new QCheckBox(permissionsMetaEnum.key(i), this);
        if(i<4)
            addUserLayout->addWidget(box, 5+i, 0, 1, 2, Qt::AlignTop);
        else
            addUserLayout->addWidget(box, 5+i-4, 2, 1, 2, Qt::AlignTop);
        userPermissions.append(box);
    }

    userAdd = new QPushButton("Add");
    addUserLayout->addWidget(userAdd, 9, 0, 2, 2);
    userAdd->hide();

    userAccept = new QPushButton("Accept");
    addUserLayout->addWidget(userAccept, 9, 0, 2, 2);
    userAccept->hide();

    userDiscard = new QPushButton("Discard");
    addUserLayout->addWidget(userDiscard, 9, 2, 2, 2);


    QObject::connect(userAdd, &QPushButton::clicked, this, [=]
        {
        if(userLogin->text().isEmpty() || userName->text().isEmpty() || userSurname->text().isEmpty() || userPosition->currentIndex()==-1)
            infoBox("Please fill out all the required fields.");
        else
        {
            auto&& permissionsMetaEnum = QMetaEnum::fromType<User::UserPermission>();
            User::UserPermissionsFlags flags;
            for(int i=0; i<userPermissions.length(); i++)
            {
                if(userPermissions.at(i)->checkState()==2)
                    flags |= static_cast<User::UserPermission>(permissionsMetaEnum.value(i));
            }
            emit controller->addUser(userLogin->text(), userName->text(), userSurname->text(),
                                     stringToEnum<User::UserPosition>(userPosition->currentText()),
                                     flags);
            userLogin->clear();
            userName->clear();
            userSurname->clear();
            userPosition->setCurrentIndex(-1);
            for(int i=0; i<userPermissions.length(); i++)
            {
                userPermissions.at(i)->setCheckState(Qt::CheckState::Unchecked);
            }
        }
        });
    QObject::connect(userDiscard, &QPushButton::clicked, this, [=]
        {
            userWindow->close();
        });

    userWindow->close();
}

void ActionWindows::showUserWindow(User* user)
{
    if(user)
    {
        userLogin->setText(user->login());
        userLogin->setEnabled(false);
        userName->setText(user->name());
        userSurname->setText(user->surname());

        for(int i=0; i<userPosition->count(); i++)
        {
            if(stringToEnum<User::UserPosition>(userPosition->itemText(i))==user->position())
            {
                userPosition->setCurrentIndex(i);
                break;
            }
        }
        for(int i=0; i<userPermissions.length(); i++)
        {
            auto flags = user->permisions();
            if(flags.testFlag(stringToEnum<User::UserPermission>(userPermissions.at(i)->text())))
                userPermissions.at(i)->setCheckState(Qt::CheckState::Checked);
            else
                userPermissions.at(i)->setCheckState(Qt::CheckState::Unchecked);
        }
        userAdd->hide();
        userAccept->show();

        userAccept->disconnect();
        QObject::connect(userAccept, &QPushButton::clicked, this, [=]
            {
            if(userName->text().length()<1 || userSurname->text().length()<1 || userPosition->currentIndex()==-1)
                infoBox("Please fill out all the required fields.");
            else
            {
                auto&& permissionsMetaEnum = QMetaEnum::fromType<User::UserPermission>();
                User::UserPermissionsFlags flags;
                for(int i=0; i<userPermissions.length(); i++)
                {
                    if(userPermissions.at(i)->checkState()==2)
                        flags |= static_cast<User::UserPermission>(permissionsMetaEnum.value(i));
                }
                emit controller->editUser(user->id(), userName->text(), userSurname->text(),
                                          stringToEnum<User::UserPosition>(userPosition->currentText()),
                                          flags);
                userWindow->close();
            }
            });
    }
    else
    {
        userLogin->clear();
        userLogin->setEnabled(true);
        userName->clear();
        userSurname->clear();
        userPosition->setCurrentIndex(-1);
        for(int i=0; i<userPermissions.length(); i++)
        {
            userPermissions.at(i)->setCheckState(Qt::CheckState::Unchecked);
        }
        userAdd->show();
        userAccept->hide();
    }
    userWindow->setWindowFlag(Qt::WindowStaysOnTopHint);
    userWindow->show();
    userWindow->raise();
}

void ActionWindows::initProjectWindow()
{
    this->projectWindow = new QDockWidget(this->parentWidget());
    projectWindow->setAttribute(Qt::WA_DeleteOnClose, false);

    projectWindow->setWindowTitle("Add Project:");
    projectWindow->setFeatures(QDockWidget::AllDockWidgetFeatures);
    projectWindow->setFloating(true);
    auto addProjectWidget = new QWidget(this->parentWidget());
    projectWindow->setWidget(addProjectWidget);
    auto addProjectLayout = new QGridLayout();
    addProjectWidget->setLayout(addProjectLayout);

    projectName = new QLineEdit(this);
    projectName->setPlaceholderText("Name");
    addProjectLayout->addWidget(projectName, 0, 0, 1, 2);

    projectDesc = new QTextEdit(this);
    projectDesc->setPlaceholderText("Description");
    addProjectLayout->addWidget(projectDesc, 1, 0, 1, 2);

    projectAdd = new QPushButton("Add");
    addProjectLayout->addWidget(projectAdd, 9, 0, 2, 2);
    projectAdd->hide();

    projectAccept = new QPushButton("Accept");
    addProjectLayout->addWidget(projectAccept, 9, 0, 2, 2);
    projectAccept->hide();

    projectDiscard = new QPushButton("Discard");
    addProjectLayout->addWidget(projectDiscard, 9, 2, 2, 2);

    QObject::connect(projectAdd, &QPushButton::clicked, this, [=]
        {
        if(projectDesc->toPlainText().isEmpty() || projectName->text().isEmpty())
            infoBox("Please fill out all the required fields.");
        else
        {
            emit controller->addProject(projectName->text(), projectDesc->toPlainText());
            projectName->clear();
            projectDesc->clear();
        }
        });
    QObject::connect(projectDiscard, &QPushButton::clicked, this, [=]
        {
            projectWindow->close();
        });
    projectWindow->close();

}

void ActionWindows::showProjectWindow(Project* project)
{
    if(project)
    {
        projectName->setText(project->name());
        projectDesc->setText(project->desc());
        projectAdd->hide();
        projectAccept->show();
        projectAccept->disconnect();
        QObject::connect(projectAccept, &QPushButton::clicked, this, [=]
            {
            if(projectName->text().length()<1 || projectDesc->toPlainText().length()<1)
                infoBox("Please fill out all the required fields.");
            else
            {
                emit controller->editProject(project->id(), projectName->text(), projectDesc->toPlainText());
                projectWindow->close();
            }
            });

    }
    else
    {
        projectName->clear();
        projectDesc->clear();
        projectAdd->show();
        projectAccept->hide();
    }
    projectWindow->setWindowFlag(Qt::WindowStaysOnTopHint);
    projectWindow->show();
    projectWindow->raise();
}

void ActionWindows::initAddUserToIssue()
{
    this->addUserToIssue = new QDockWidget(this->parentWidget());
    addUserToIssue->setAttribute(Qt::WA_DeleteOnClose, false);

    addUserToIssue->setWindowTitle("Add/Remove resources:");
    addUserToIssue->setFeatures(QDockWidget::AllDockWidgetFeatures);
    addUserToIssue->setFloating(true);
    auto addUserToIssueWidget = new QWidget(this->parentWidget());
    addUserToIssue->setWidget(addUserToIssueWidget);
    auto addUserToIssueLayout = new QGridLayout();
    addUserToIssueWidget->setLayout(addUserToIssueLayout);
    addUserToIssue->close();

    menagersList = new QTableWidget();
    addUserToIssueLayout->addWidget(menagersList, 1, 0);
    addUserToIssueLayout->addWidget(new QLabel("Menagers"),0,0);
    menagersList->setMinimumSize(100, 100);
    menagersList->setMaximumWidth(100);

    programmersList = new QTableWidget();
    addUserToIssueLayout->addWidget(programmersList, 1, 1);
    addUserToIssueLayout->addWidget(new QLabel("Programmers"),0,1);
    programmersList->setMinimumSize(100, 100);
    programmersList->setMaximumWidth(100);

    testersList = new QTableWidget();
    addUserToIssueLayout->addWidget(testersList, 1, 2);
    addUserToIssueLayout->addWidget(new QLabel("Testers"),0,2);
    testersList->setMinimumSize(100, 100);
    testersList->setMaximumWidth(100);

    addUserToIssueAccept = new QPushButton("Accept");
    addUserToIssueLayout->addWidget(addUserToIssueAccept, 2, 0, 1, 2);

    addUserToIssueDiscard = new QPushButton("Discard");
    addUserToIssueLayout->addWidget(addUserToIssueDiscard, 2, 2, 1, 1);

    QObject::connect(addUserToIssueDiscard, &QPushButton::clicked, this, [=]
        {
            addUserToIssue->close();
        });

    menagersList->setRowCount(100);
    menagersList->setColumnCount(1);
    menagersList->horizontalHeader()->resizeSection(0, menagersList->width());
    menagersList->horizontalHeader()->hide();
    menagersList->verticalHeader()->hide();
    menagersList->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
    programmersList->clearContents();
    programmersList->setRowCount(100);
    programmersList->setColumnCount(1);
    programmersList->horizontalHeader()->resizeSection(0, programmersList->width());
    programmersList->horizontalHeader()->hide();
    programmersList->verticalHeader()->hide();
    programmersList->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
    testersList->clearContents();
    testersList->setRowCount(100);
    testersList->setColumnCount(1);
    testersList->horizontalHeader()->resizeSection(0, testersList->width());
    testersList->horizontalHeader()->hide();
    testersList->verticalHeader()->hide();
    testersList->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);

}

void ActionWindows::showAddUserToIssue(IssueTicket *issue)
{
    menagersList->clearContents();
    menagersChecks.clear();
    testersList->clearContents();
    testersChecks.clear();
    programmersList->clearContents();
    programmersChecks.clear();
    int t=0;
    int p=0;
    int m=0;
    for(auto user : controller->users)
    {
        auto temp = new QCheckBox(user->login());
        switch (user->position()) {
        case User::UserPosition::Tester:
            for(auto test : issue->testers())
            {
                if(test->id()==user->id())
                {
                    temp->setCheckState(Qt::CheckState::Checked);
                    break;
                }
            }
            testersChecks.insert(user, temp);
            testersList->setCellWidget(t,0,temp);
            t++;
            break;
        case User::UserPosition::Programmer:
            for(auto prog : issue->programmers())
            {
                if(prog->id()==user->id())
                {
                    temp->setCheckState(Qt::CheckState::Checked);
                    break;
                }
            }
            programmersChecks.insert(user, temp);
            programmersList->setCellWidget(p,0,temp);
            p++;
            break;
        case User::UserPosition::Manager:
            for(auto men : issue->menagers())
            {
                if(men->id()==user->id())
                {
                    temp->setCheckState(Qt::CheckState::Checked);
                    break;
                }
            }
            menagersChecks.insert(user, temp);
            menagersList->setCellWidget(m,0,temp);
            m++;
            break;
        default:
            break;
        }
    }
    addUserToIssueAccept->disconnect();
    QObject::connect(addUserToIssueAccept, &QPushButton::clicked, this, [=]
        {
            auto temp = issue->testers();
            auto temp1 = issue->programmers();
            auto temp2 = issue->menagers();
            for(auto user : testersChecks.keys())
            {
                bool contains = false;
                for(auto tester : issue->testers())
                    if(tester->id() == user->id())
                    {
                        contains = true;
                        break;
                    }
                if(contains && testersChecks.value(user)->checkState()==0)
                    emit controller->removeUserFromIssue(user->id(), issue->id());
                else if(!contains && testersChecks.value(user)->checkState()==2)
                    emit controller->addUserToIssue(user->id(), issue->id());
            }

            for(auto user : programmersChecks.keys())
            {
                bool contains = false;
                for(auto programmer : issue->programmers())
                    if(programmer->id() == user->id())
                    {
                        contains = true;
                        break;
                    }
                if(contains && programmersChecks.value(user)->checkState()==0)
                    emit controller->removeUserFromIssue(user->id(), issue->id());
                else if(!contains && programmersChecks.value(user)->checkState()==2)
                    emit controller->addUserToIssue(user->id(), issue->id());
            }

            for(auto user : menagersChecks.keys())
            {
                bool contains = false;
                for(auto menager : issue->menagers())
                    if(menager->id() == user->id())
                    {
                        contains = true;
                        break;
                    }
                if(contains && menagersChecks.value(user)->checkState()==0)
                    emit controller->removeUserFromIssue(user->id(), issue->id());
                else if(!contains && menagersChecks.value(user)->checkState()==2)
                    emit controller->addUserToIssue(user->id(), issue->id());
            }

            addUserToIssue->close();
        });

    addUserToIssue->setWindowFlag(Qt::WindowStaysOnTopHint);
    addUserToIssue->show();
    addUserToIssue->raise();
}


