//
//  UserManager.hpp
//
//  Created by Matthew Sherborne on 22/08/11.
//  Copyright 2011 Slicehost LLC. All rights reserved.
//

#pragma once
#ifndef wittyPlus_UserManager_hpp
#define wittyPlus_UserManager_hpp

#include <Wt/WStackedWidget>
#include "UserList.hpp"
#include "UserEdit.hpp"
#include "model/User.hpp"
#include <Wt/WAnimation>

using Wt::WStackedWidget;
using Wt::WAnimation;
using wittyPlus::model::User;

namespace dbo = Wt::Dbo;

namespace wittyPlus {
    

/// GUI to manage users
class UserManager : public WStackedWidget {
private:
    // Helpers
    WAnimation slide;
    // Fields
    UserList* userList;
    UserEdit* userEdit;
    // Helper funcs
    template <class Widget>
    void createAndAddWidget(Widget*& widget) { addWidget(widget = new Widget()); }
    // Event handlers
    void userChosen(dbo::ptr<User> user) {
        setCurrentIndex(1, slide, true); // Switch to edit view (with a nice slide effect)
        userEdit->setUser(user);
    }
    void userEdited(dbo::ptr<User>) {
        setCurrentIndex(0, slide, true);
        userList->refillUserList();
    }
    void userEditCancelled() { 
        setCurrentIndex(0, slide, true);
        userList->refillUserList();
    }
public:
    UserManager(WContainerWidget* parent=0) :
        WStackedWidget(parent), slide(WAnimation::SlideInFromBottom) 
    {
        createAndAddWidget(userList);
        userList->userChosen().connect(this, &UserManager::userChosen);
        createAndAddWidget(userEdit);
        userEdit->done().connect(this, &UserManager::userEdited);
        userEdit->cancelled().connect(this, &UserManager::userEditCancelled);
    }
};
    
} // namespace wittyPlus


#endif // #define wittyPlus_UserManager_hpp
