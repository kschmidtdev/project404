import os, shutil, copy

OUTPUT_DIR = os.getcwd() + "\\builtsite\\"

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

for sectionLine in sections:
    sectionTitle = sectionLine.split(", ")[0].replace("\"", "")
    sectionFilename = sectionLine.split(", ")[1].replace("\"", "").strip()

    thisSectionPage = open( OUTPUT_DIR + sectionFilename.replace("txt", "html" ), "w" )

    thisSectionHeadTxt = headTxt
    for line in thisSectionHeadTxt:
        if "PAGETITLE" in line:
            line = line.replace( "PAGETITLE", sectionTitle )

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
