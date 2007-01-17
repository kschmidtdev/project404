buildsite.py

A simple script to put together a static website. It will construct some html files into a "build" directory which will be web-ready.

Okay in more detail - it goes through the sections.txt file which contains pairs of "Section Title", "Section_Body_Filename" and uses that as the body of the page (and the section title), and makes a static html file with sitemenu's contents as the site menu, and includes a reference to stylesheet.css for the page's style sheet.

The purpose of this tool is to be able to build the site content and update it's layout without having to update it for each and every page. 

Currently does no error checking.

Karl Schmidt 2007