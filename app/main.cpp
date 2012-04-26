/** \file main.cpp
* Copyright (C) 2006 Wim Dumon, Koen Deforche
* See the LICENSE file for terms of use.
* \b compiles with \code g++ -I/usr/local/wt/include -o hello.wt main.cpp -L/usr/local/wt/lib -lwthttp -lwt \endcode
*then run with 
*\code  ./hello.wt  --docroot . --http-address 0.0.0.0 --http-port 8080 \endcode
* open your browser on http://localhost:8080/ ctrl+C on console use to lunch app to stop srv \n
* \n
* this complete documentation is followed by autor version and date tags\n
* \author Lyase.d Wim Dumon Koen Deforche 
* \version 0.1
* \date 25 april 2012 
**/
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
using namespace Wt;

/*! \class HelloApplication
   * \brief A simple hello world application class which demonstrates how to react
     * to events, read input, and give feed-back.
   *  more documentation of the class
   */
// simple definition of a HelloApplication 
class HelloApplication : public WApplication
{
    public:
        /**
 * \fn HelloApplication(const WEnvironment& env)
 * \brief Constructor Fonction
 *
 * \param &env* The env argument contains information about the new session, and
 * the initial request. It must be passed to the WApplication
 * constructor so it is typically also an argument for your custom
 * application constructor.
 * \return STR_NO_ERR si aucune erreur, STR_EMPTY_ERR sinon.
 */
          HelloApplication(const WEnvironment& env);

    private:
            WLineEdit *nameEdit_;
              WText *greeting_;

                void greet();
};

HelloApplication::HelloApplication(const WEnvironment& env)
      : WApplication(env)
{
      setTitle("Hello world");                               // application title

        root()->addWidget(new WText("Your name, please ? "));  // show some text
          nameEdit_ = new WLineEdit(root());                     // allow text input
            nameEdit_->setFocus();                                 // give focus

              WPushButton *b = new WPushButton("Greet me.", root()); // create a button
                b->setMargin(5, Left);                        // add 5 pixels margin 

                  root()->addWidget(new WBreak());                       // insert a line break

                    greeting_ = new WText(root());                         // empty text
  /*
   * Connect signals with slots
   *
   * - simple Wt-way
   */
  b->clicked().connect(this, &HelloApplication::greet);

  /*
   * - using an arbitrary function object (binding values with boost::bind())
   */
  nameEdit_->enterPressed().connect
    (boost::bind(&HelloApplication::greet, this));

  /*
   * - using a c++0x lambda:
   */
  // b->clicked().connect(std::bind([=]() { 
  //       greeting_->setText("Hello there, " + nameEdit_->text());
  // }));
}
void HelloApplication::greet()
{
      /*
            * Update the text, using text input into the nameEdit_ field.
               */
      greeting_->setText("Hello there, " + nameEdit_->text());
}

WApplication *createApplication(const WEnvironment& env)
{
      /*
            * You could read information from the environment to decide whether
               * the user has permission to start a new application
                  */
      return new HelloApplication(env);
}
int main(int argc, char **argv)
{
      /*
            * Your main method may set up some shared resources, but should then
               * start the server application (FastCGI or httpd) that starts listening
                  * for requests, and handles all of the application life cycles.
                     *
                        * The last argument to WRun specifies the function that will instantiate
                           * new application objects. That function is executed when a new user surfs
                              * to the Wt application, and after the library has negotiated browser
                                 * support. The function should return a newly instantiated application
                                    * object.
                                       */
      return WRun(argc, argv, &createApplication);
}
