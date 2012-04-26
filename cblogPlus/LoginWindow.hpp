/*
 * =====================================================================================
 *
 *       Filename:  LoginWindow.hpp
 *
 *    Description:  Login screen to be placed at /login url
 *
 *        Version:  1.0
 *        Created:  06/01/2011 02:43:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef LOGIN_WINDOW_HPP
#define LOGIN_WINDOW_HPP

#include "base/MoreAwesomeTemplate.hpp"
#include "base/ButtonBar.hpp"
#include "base/SessionHandle.hpp"
#include <Wt/WLineEdit>
#include <Wt/WLogger>
#include <string>

namespace Wt {
    class WString;
    class WLabel;
    class WContainerWidget;
    class WPushButton;
}

using Wt::WTemplate;
using Wt::WString;
using Wt::WLabel;
using Wt::WContainerWidget;
using Wt::WPushButton;
using Wt::WLineEdit;

namespace wittyPlus {

class LoginWindow : public base::MoreAwesomeTemplate {
private:
    WLabel* _usernameLabel;
    WLineEdit* _usernameEdit;
    WLabel* _passwordLabel;
    WLineEdit* _passwordEdit;
    base::ButtonBar* _btnBar;
protected:
    void handleOKHit();
    void handleCancelHit();
public:
    LoginWindow(WContainerWidget* parent=0);
    void setFocus() { _usernameEdit->setFocus(); }
};

} // namespace wittyPlus

#endif // LOGIN_WINDOW_HPP
