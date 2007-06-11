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

#include <kapplication.h>
#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <klocale.h>

#include "kcolordialog.h"

static const char description[] =
	I18N_NOOP("KDE Color Chooser");

static const char version[] = "v1.0.1";

static KCmdLineOptions options[] =
{
   { "print", I18N_NOOP("Print the selected color to stdout"), 0 },
   KCmdLineLastOption
};
	
int main(int argc, char *argv[])
{
  KLocale::setMainCatalog("kdelibs"); 
  KAboutData aboutData( "kcolorchooser", I18N_NOOP("KColorChooser"),
		version, description, KAboutData::License_BSD,
		"(c) 2000, Waldo Bastian");
  aboutData.addAuthor("Waldo Bastian",0, "bastian@kde.org");
  KCmdLineArgs::init( argc, argv, &aboutData );
  KCmdLineArgs::addCmdLineOptions( options );

  KApplication app;
  
  KColorDialog dlg;

  dlg.setColor(Qt::blue); // Just a color

  app.connect(&dlg, SIGNAL(finished()), SLOT(quit()));

  dlg.show();
  app.exec();

  KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
  const  QColor c = dlg.color();
  if ( args->isSet("print") && c.isValid() ) {
      std::cout << c.name().toUtf8().constData() << std::endl;
  }
  args->clear();
}  
