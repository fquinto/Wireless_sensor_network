<?php
include("../init.php");

/* Library settings */
define("PCHART_PATH", "../pChart2.1.2/");

include(PCHART_PATH."class/pData.class.php");
include(PCHART_PATH."class/pDraw.class.php");
include(PCHART_PATH."class/pImage.class.php");

$datosSERIE = array();
//__________________________________________________________________________
/*
 * DATA FROM PYTHON (serial port)
 */
/*
$PATH = url_completa('../cgi-bin/lectura_graph_linux.py'); //$PATH=http://127.0.0.1/serie/cgi-bin/lectura_graph_linux.py

for ($i = 0; $i <= 9; $i++) {
    $var= @stripslashes( @join( @file( $PATH ),"" ) );
    $pieces = explode(",", $var);
    $valor = str_replace(array("\r\n", "\n", "\r"), '', $pieces[1]);
    //echo $valor;
    array_push($datosSERIE, $valor);
}
*/
//__________________________________________________________________________
/*
 * DATA FOR TEST
 */
$datosSERIE = array(829,745,713,842,810,812,874,880,874,880);
//__________________________________________________________________________

$myData = new pData();
$myData->addPoints($datosSERIE,"Serie1");
//$myData->setSerieTicks("Serie1",4);
$myData->setSerieDescription("Serie1",GRAPHIC_DATA);
$myData->setSerieOnAxis("Serie1",0);

//$myData->addPoints(array("January","February","March","April","May","June","July","August"),"Absissa");
$myData->addPoints(array("0","1","2","3","4","5","6","7","8","9"),"Absissa");
$myData->setSerieDescription("Absissa","Months"); 
$myData->setAbscissa("Absissa");

$myData->setAxisPosition(0,AXIS_POSITION_LEFT);
$myData->setAxisName(0,GRAPHIC_VALUES);
$myData->setAxisUnit(0," ºC");

/* Will append the "autumn" palette to the current one */
$myData->loadPalette(PCHART_PATH."palettes/navy.color",TRUE);

$myPicture = new pImage(700,330,$myData,TRUE);
$myPicture->drawRectangle(0,0,699,329,array("R"=>0,"G"=>0,"B"=>0));

$myPicture->setShadow(TRUE,array("X"=>1,"Y"=>1,"R"=>50,"G"=>50,"B"=>50,"Alpha"=>20));

$myPicture->setFontProperties(array("FontName"=>PCHART_PATH."fonts/Forgotte.ttf","FontSize"=>14));
$TextSettings = array("Align"=>TEXT_ALIGN_MIDDLEMIDDLE
, "R"=>59, "G"=>59, "B"=>59);
$myPicture->drawText(350,25,GRAPHIC_TITLE,$TextSettings);

$myPicture->setShadow(FALSE);
$myPicture->setGraphArea(50,50,675,290);
$myPicture->setFontProperties(array("R"=>0,"G"=>0,"B"=>0,"FontName"=>PCHART_PATH."fonts/pf_arma_five.ttf","FontSize"=>6));

$Settings = array("Pos"=>SCALE_POS_LEFTRIGHT
, "Mode"=>SCALE_MODE_FLOATING
, "LabelingMethod"=>LABELING_ALL
, "GridR"=>0, "GridG"=>0, "GridB"=>0, "GridAlpha"=>50, "TickR"=>0, "TickG"=>0, "TickB"=>0, "TickAlpha"=>50, "LabelRotation"=>0, "CycleBackground"=>1, "DrawArrows"=>1, "DrawXLines"=>1, "DrawSubTicks"=>1, "SubTickR"=>255, "SubTickG"=>0, "SubTickB"=>0, "SubTickAlpha"=>50, "DrawYLines"=>ALL);
$myPicture->drawScale($Settings);

$myPicture->setShadow(TRUE,array("X"=>1,"Y"=>1,"R"=>50,"G"=>50,"B"=>50,"Alpha"=>10));

$Config = "";
$myPicture->drawSplineChart($Config);

$Config = array("FontR"=>0, "FontG"=>0, "FontB"=>0, "FontName"=>PCHART_PATH."fonts/pf_arma_five.ttf", "FontSize"=>6, "Margin"=>6, "Alpha"=>30, "BoxSize"=>5, "Style"=>LEGEND_NOBORDER
, "Mode"=>LEGEND_HORIZONTAL
);
$myPicture->drawLegend(646,16,$Config);

$myPicture->stroke();
?>