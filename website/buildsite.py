import os, shutil, copy


OUTPUT_DIR = os.getcwd() + "\\builtsite\\"

def writeSectionHTML( sectionTitle, sectionFilename, headTxt, footTxt, sideMenuHTML, subsection = "" ):
    sectionHTMLFilename = sectionFilename.replace("txt", "html" )

    thisSectionPage = open( OUTPUT_DIR + sectionHTMLFilename, "w" )

    thisSectionHeadTxt = headTxt
    for line in thisSectionHeadTxt:
        if "PAGETITLE" in line:
            line = line.replace( "PAGETITLE", sectionTitle )
        elif "SIDEMENU" in line:
            line = line.replace( "SIDEMENU", sideMenuHTML )
        elif "STYLESHEET" in line:
            if subsection:
                line = line.replace( "STYLESHEET", "../stylesheet.css")
            else:
                line = line.replace( "STYLESHEET", "stylesheet.css" )
        if subsection:
            line = line.replace( "\n<a href=\"", "\n<a href=\"../" )
            line = line.replace( "\n<a href=\"../http", "\n<a href=\"http" )
            line = line.replace( subsection + "/", "" )
        thisSectionPage.write( line )

    sectionFile = open( sectionFilename, "r" )
    sectionTxt = sectionFile.readlines()
    sectionFile.close()
                
    for line in sectionTxt:
        thisSectionPage.write( line )
        if not line.startswith( "<" ):
            thisSectionPage.write( "<br/>" )

    thisSectionPage.writelines( footTxt )          
    thisSectionPage.close()

def main():

    if not os.path.exists( OUTPUT_DIR ):
        os.mkdir( OUTPUT_DIR )

    shutil.copy( "stylesheet.css", OUTPUT_DIR + "stylesheet.css" )

    sectionsFile = open( "sections.txt", "r" )

    sections = sectionsFile.readlines()

    sectionsFile.close()

    headFile = open( "head.txt" )

    headTxt = headFile.readlines()

    headFile.close()

    footFile = open( "foot.txt" )
    footTxt = footFile.readlines()
    footFile.close()

    # Build the sidemenu
    sideMenuHTML = "<span class = \"sidemenu\" >\n"

    for sectionLine in sections:
        if sectionLine[0] != "#":
            sectionTitle = sectionLine.split(", ")[0].replace("\"", "")
            sectionDetailTitle = sectionLine.split(", ")[1].replace("\"", "")

            if sectionDetailTitle == "subsection":
                sectionFolder = sectionLine.split(", ")[2].replace("\"", "").strip()
                subsectionFile = open( sectionFolder + "\\sections.txt", "r" )
                subsections = subsectionFile.readlines()
                subsectionFile.close()

                sideMenuHTML += "<ul class=\"sidemenulist\">\n"
                for subsectionLine in subsections:
                    if sectionLine[0] != "#":
                        subSectionTitle = subsectionLine.split(", ")[0].replace("\"", "")
                        subSectionFilename = subsectionLine.split(", ")[1].replace("\"", "").strip()
                        subSectionHTMLFilename = sectionFolder + "/" + subSectionFilename.replace("txt", "html" )
                        sideMenuHTML += "<li><a href=\"" + subSectionHTMLFilename + "\">" + subSectionTitle + "</a></li>\n"
                sideMenuHTML += "</ul>\n"
            elif sectionDetailTitle == "url":
                sideMenuHTML += "<a href=" + sectionLine.split(", ")[2] + ">" + sectionTitle + "</a><br/>\n"
            else:
                sectionFilename = sectionLine.split(", ")[2].replace("\"", "").strip()
                sectionHTMLFilename = sectionFilename.replace("txt", "html" )
                sideMenuHTML += "<a href=\"" + sectionHTMLFilename + "\">" + sectionTitle + "</a><br/>\n"
            
    sideMenuHTML += "</span>\n"

    for sectionLine in sections:
        if sectionLine[0] != "#":
            sectionTitle = sectionLine.split(", ")[1].replace("\"", "")

            if sectionTitle == "subsection":
                sectionFolder = sectionLine.split(", ")[2].replace("\"", "").strip()

                if not os.path.exists( OUTPUT_DIR + sectionFolder ):
                    os.mkdir( OUTPUT_DIR + sectionFolder )

                subsectionFile = open( sectionFolder + "\\sections.txt", "r" )
                subsections = subsectionFile.readlines()
                subsectionFile.close()

                for subsectionLine in subsections:
                    if sectionLine[0] != "#":
                        subSectionTitle = sectionLine.split(", ")[0].replace("\"", "") + ": " + subsectionLine.split(", ")[0].replace("\"", "")
                        subSectionFilename = sectionFolder + "\\" + subsectionLine.split(", ")[1].replace("\"", "").strip()

                        writeSectionHTML( subSectionTitle, subSectionFilename, headTxt, footTxt, sideMenuHTML, sectionFolder )
            elif sectionTitle == "url":
                pass
            else:
                sectionFilename = sectionLine.split(", ")[2].replace("\"", "").strip()
                writeSectionHTML( sectionTitle, sectionFilename, headTxt, footTxt, sideMenuHTML )


    shutil.copy( OUTPUT_DIR + "team.html", OUTPUT_DIR + "index.html" )

if __name__ == "__main__":
    main()
