<?php
$out = null;
$res = null;

$params = ["mg", "hg", "wg", "ma", "ha", "wa", "mb", "hb", "wb"];


$cmd = "../CentralizedFateClassifier/CentralizedFateClassifier -m triangleviewer ";

for ($i = 0; $i < count($params); $i++)
{
	if (!is_numeric($_GET[$params[$i]]))
	{
		echo("parameter error " . $params[$i]);
		exit();
	}
	
	
	$cmd .= " " . $_GET[$params[$i]];
}

echo("cmd=" . $cmd . "\n");

exec($cmd, $out, $res);


for ($i = 0; $i < count($out); $i++)
{
	echo($out[$i] . "\n");
}

?>