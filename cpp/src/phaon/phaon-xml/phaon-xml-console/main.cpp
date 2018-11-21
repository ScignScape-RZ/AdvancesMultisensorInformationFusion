
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phaon-xml/phaon-xml-document.h"

#include "kans.h"

USING_KANS(PhaonXML)


int main(int argc, char* argv[])
{
 Phaon_XML_Document pxd;

 pxd.set_url_from_file( DEFAULT_KPH_FOLDER "/test/xml/t1.xml" );

 pxd.transpile();

 return 0;
}
