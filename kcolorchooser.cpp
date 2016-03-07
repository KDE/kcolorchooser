/*
This file is part of KDE 

  Copyright (C) 1998-2000 Waldo Bastian (bastian@kde.org)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <iostream>

#include <QApplication>
#include <QClipboard>
#include <QColorDialog>
#include <QCommandLineParser>
#include <QDialogButtonBox>
#include <QMenu>
#include <QMimeData>
#include <QPushButton>
#include <QDebug>

#include <KAboutData>
#include <KLocalizedString>
#include <KHelpMenu>

static const char description[] =
	I18N_NOOP("KDE Color Chooser");

static const char version[] = "v2.0.0";

	
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  KAboutData aboutData("kcolorchooser", i18n("KColorChooser"),
                version, i18n(description), KAboutLicense::BSDL,
                i18n("(c) 2000, Waldo Bastian"));
  aboutData.addAuthor(i18n("Waldo Bastian"), QString(), "bastian@kde.org");
  aboutData.addAuthor(i18n("Hugo Parente Lima"),i18n("KF5 port"), "hugo.pl@gmail.com");
  aboutData.setTranslator(i18nc("NAME OF TRANSLATORS", "Your names"), i18nc("EMAIL OF TRANSLATORS", "Your emails"));
  aboutData.setProductName("kdelibs/kdeui");
  KLocalizedString::setApplicationDomain("kcolorchooser");
  KAboutData::setApplicationData(aboutData);


  QCommandLineParser parser;
  parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
  aboutData.setupCommandLine(&parser);
  QCommandLineOption print("print", i18n("Print the selected color to stdout."));
  parser.addOption(print);
  QCommandLineOption color("color", i18n("Set initially selected color."), "color");
  parser.addOption(color);
  parser.process(app);


  QColorDialog dlg;
  QDialogButtonBox *box = dlg.findChild<QDialogButtonBox*>();
  if (!box)
      return 1;

  box->addButton(QDialogButtonBox::Help);

  KHelpMenu *help = new KHelpMenu(&dlg, aboutData);
  QObject::connect(box, &QDialogButtonBox::helpRequested, [=] () {
      QPushButton *button = box->button(QDialogButtonBox::Help);
      QPoint pos = button->pos();
      pos.ry() += button->height();
      pos = box->mapToGlobal(pos);
      help->menu()->exec(pos);
  });

  if (parser.isSet(color)) {
      dlg.setCurrentColor(QColor(parser.value(color)));
  } else {
      const QMimeData* mimeData = QApplication::clipboard()->mimeData(QClipboard::Clipboard);
      QColor clipboardColor = mimeData->colorData().value<QColor>();
      if (clipboardColor.isValid()) {
          dlg.setCurrentColor(clipboardColor);
      }
  }

  dlg.show();
  app.exec();

  const  QColor c = dlg.currentColor();
  if (parser.isSet(print) && c.isValid()) {
      std::cout << c.name().toUtf8().constData() << std::endl;
  }
}  
