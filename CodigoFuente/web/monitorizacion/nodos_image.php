<?php
/* Library settings */
define("PCHART_PATH", "../pChart2.1.2/");

/* pChart library inclusions */
include(PCHART_PATH."class/pData.class.php");
include(PCHART_PATH."class/pDraw.class.php");
include(PCHART_PATH."class/pSpring.class.php");
include(PCHART_PATH."class/pImage.class.php");

/* Create the pChart object */
$myPicture = new pImage(300,300);

/* Create the background */
$myPicture->drawGradientArea(0,0,300,300,DIRECTION_HORIZONTAL,array("StartR"=>217,"StartG"=>250,"StartB"=>116,"EndR"=>181,"EndG"=>209,"EndB"=>27,"Alpha"=>100));
$myPicture->drawGradientArea(0,0,300,20,DIRECTION_VERTICAL,array("StartR"=>0,"StartG"=>0,"StartB"=>0,"EndR"=>50,"EndG"=>50,"EndB"=>50,"Alpha"=>100));
$myPicture->drawRectangle(0,0,299,299,array("R"=>0,"G"=>0,"B"=>0));
$myPicture->setFontProperties(array("FontName"=>PCHART_PATH."fonts/Silkscreen.ttf","FontSize"=>6));
$myPicture->drawText(10,13,"pSpring - Draw spring charts",array("R"=>255,"G"=>255,"B"=>255));


/* Define the charting area & stuff */
$myPicture->setGraphArea(20,20,280,280);
$myPicture->setFontProperties(array("FontName"=>PCHART_PATH."fonts/Forgotte.ttf","FontSize"=>9,"R"=>80,"G"=>80,"B"=>80));
$myPicture->setShadow(TRUE,array("X"=>2,"Y"=>2,"R"=>0,"G"=>0,"B"=>0,"Alpha"=>10));

/* Create the pSpring object */
$SpringChart = new pSpring();

/* Create some nodes and connections */
$SpringChart->addNode(0,array("Shape"=>NODE_SHAPE_SQUARE,"FreeZone"=>60,"Size"=>20,"NodeType"=>NODE_TYPE_CENTRAL));
$SpringChart->addNode(1,array("Connections"=>"0"));
$SpringChart->addNode(2,array("Connections"=>"0"));
$SpringChart->addNode(3,array("Shape"=>NODE_SHAPE_TRIANGLE,"Connections"=>"1"));
$SpringChart->addNode(4,array("Shape"=>NODE_SHAPE_TRIANGLE,"Connections"=>"1"));
$SpringChart->addNode(5,array("Shape"=>NODE_SHAPE_TRIANGLE,"Connections"=>"1"));
$SpringChart->addNode(6,array("Connections"=>"2"));
$SpringChart->addNode(7,array("Connections"=>"2"));
$SpringChart->addNode(8,array("Connections"=>"2"));

/* Define the nodes color */
$SpringChart->setNodesColor(0,array("R"=>215,"G"=>163,"B"=>121,"BorderR"=>166,"BorderG"=>115,"BorderB"=>74));
$SpringChart->setNodesColor(array(1,2),array("R"=>150,"G"=>215,"B"=>121,"Surrounding"=>-30));
$SpringChart->setNodesColor(array(3,4,5),array("R"=>216,"G"=>166,"B"=>14,"Surrounding"=>-30));
$SpringChart->setNodesColor(array(6,7,8),array("R"=>179,"G"=>121,"B"=>215,"Surrounding"=>-30));

/* Customize some relations */
$SpringChart->linkProperties(0,1,array("R"=>255,"G"=>0,"B"=>0,"Ticks"=>2));
$SpringChart->linkProperties(0,2,array("R"=>255,"G"=>0,"B"=>0,"Ticks"=>2));

/* Render the spring chart */
$Result = $SpringChart->drawSpring($myPicture);
//print_r($Result);

/* Render the picture */
//$myPicture->Render("drawspring.png");
$myPicture->stroke();
?>