<!DOCTYPE HTML>
<!--
    Arcana by HTML5 UP
    html5up.net | @ajlkn
    Free for personal and commercial use under the CCA 3.0 license (html5up.net/license)
-->

<?php

/*
LANGUAGE DEFINITIONS START HERE

We begin by including languages.php, which defines the functions addTerm and getTerm.  These are respectively used to 
add and get a multilingual term.  It also defines setCurrentLang, which can take "fr" or "en" as a parameter.
*/
include("languages.php");

$langget = $_GET['lang'];

if (isset($langget) && ($langget == "fr" || $langget == "en")) {
    setCurrentLang($langget);
}
else { // Detect language (a bit hackish, ignores order and weight)
    $browserlang   = preg_split("/[;,]/",
                                strtolower($_SERVER['HTTP_ACCEPT_LANGUAGE']));
    $browserfrench = in_array("fr-ca", $browserlang) ||
                     in_array("fr", $browserlang);

	setCurrentLang($browserfrench ? "fr" : "en");
}

/*
Then we define our multilingual terms.  When we add a term, it becomes available in the current language later on.
For instance, if we call
	addTerm("term_id", "francais", "english");
and later on call 
	getTerm("term_id");
the return value will be "francais" if the current lang is "fr", and "english" if the current lang is "en"
*/

addTerm("site_title", 
        "GRIF – Groupe de recherche en informatique fondamentale de l'Université de Sherbrooke", 
        "GRIF – Research group on fundamental computer science of the Université de Sherbrooke" );


addTerm("menu_home", "Accueil", "Home");
addTerm("menu_members", "Membres", "Members");
addTerm("menu_seminars", "Séminaires", "Seminars");
addTerm("menu_research", "Recherche", "Research");
addTerm("menu_teaching", "Enseignement", "Teaching");
addTerm("menu_publications", "Publications", "Publications");

								   
?>

<html>
  <head>
    <title>
      <?= getTerm("site_title") ?>
    </title>
    <meta charset="UTF-8" />
	<?php
	header('Content-Type: text/html; charset=UTF-8');
	?>
    <meta name="viewport" content="width=device-width, initial-scale=1, user-scalable=no" />

    <meta name="description" lang="fr" content="GRIF – Groupe de recherche en informatique fondamentale de l'Université de Sherbrooke">
    <meta name="description" lang="en" content="GRIF – Research group on the foundations of computer science of the Université de Sherbrooke">

    <meta name="keywords" lang="fr" content="GRIF, Martin Beaudry, Michael Blondin, Marc Frappier, Manuel Lafond,
Aïda Ouangraoua, Dave Touchette, Université de Sherbrooke,
informatique, informatique fondamentale, algorithmique,
bio-informatique, biologie computationnelle, complexité du calcul,
complexité paramétrée, cryptographie, sécurité, informatique
quantique, logique, méthodes formelles, spécification, raffinement,
théorie des automates, théorie des graphes, théorie de l'information,
théorie du calcul, vérification formelle">

    <meta name="keywords" lang="en" content="GRIF, Martin Beaudry, Michael Blondin, Marc Frappier, Manuel Lafond,
Aïda Ouangraoua, Dave Touchette, Université de Sherbrooke, University
of Sherbrooke, computer science, foundations of computer science,
algorithms, automata theory, bioinformatics, computational biology,
computational complexity, cryptography, security, formal methods,
formal verification, graph theory, information theory, logic,
parameterized complexity, quantum computing, specification,
refinement, theory of computation">

    <link rel="stylesheet" href="assets/css/main.css" />
    <link rel="stylesheet" href="https://code.cdn.mozilla.net/fonts/fira.css">
    <link rel="icon" href="favicon.ico"">
  </head>
  <body class="is-preload">
    <div id="page-wrapper">
	
	  <div style="position: absolute; right: 20px; top: 5px;">
		<?php
		$lang = getCurrentLang();
        $url  = strtok($_SERVER["REQUEST_URI"], '?');

		if ($lang == "fr")
		{
		?>
			<b>FR</b> / <a href='<?= $url ?>?lang=en'>EN</a>
		<?php
		}
		else
		{
		?>
			<a href='<?= $url ?>?lang=fr'>FR</a> / <b>EN</b>
		<?php
		}
		
		?>
	  </div>
	
      <!-- Header -->
      <div id="header">

	<!-- Logo -->
	<h1>
          <a href="" id="logo">
            <?= getTerm("site_title") ?>
          </a>
        </h1>

		
	<?php
	$curpage = basename($_SERVER['PHP_SELF']);
	$is_publications = (strpos($curpage, "publications.php") !== false);
    $url_decoration = "?lang=" . getCurrentLang();
    ?>

	<!-- Nav -->
	<nav id="nav">
	  <ul>
	  
	    <li <?= ($is_publications ? "" : "class='current'") ?>><a href="index.php<?= $url_decoration ?>"><?= getTerm("menu_home") ?></a></li>
	    <li><a href="index.php<?= $url_decoration ?>#membres"><?= getTerm("menu_members") ?></a></li>
	    <li><a href="index.php<?= $url_decoration ?>#seminaires"><?= getTerm("menu_seminars") ?></a></li>
	    <li><a href="index.php<?= $url_decoration ?>#recherche"><?= getTerm("menu_research") ?></a></li>
		<li <?= ($is_publications ? "class='current'" : "") ?>><a href="publications.php<?= $url_decoration ?>"><?= getTerm("menu_publications") ?></a></li>
	    <li><a href="index.php<?= $url_decoration ?>#enseignement"><?= getTerm("menu_teaching") ?></a></li>
        <li id="langhide">
        <?
		$lang = getCurrentLang();
		if ($lang == "fr")
		{
		?>
			<a href='index.php?lang=en'>English version</a>
		<?
		}
		else
		{
		?>
			<a href='index.php?lang=fr'>Version française</a>
		<?
		}
        ?>
        </li>
	  </ul>
	</nav>
      </div>
