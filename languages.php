<?php
/*
Here we setup an associative array of multilingual terms. 
The key is the id of the term, and the value is another array that has one entry for "en" and "fr".  
These entries are the text to be displayed for the different languages.
*/

$lang_terms = array();
$cur_lang = "fr";	//set this to "en" for English

function setCurrentLang($lang)
{
	global $cur_lang;
	$cur_lang = $lang;
}


function getCurrentLang()
{
	global $cur_lang;
	return $cur_lang;
}

function addTerm($term_key, $fr_text, $en_text)
{
	global $lang_terms;
	$lang_terms[$term_key] = array( "fr" => $fr_text, "en" => $en_text );
}

function getTerm($term_key)
{
	global $lang_terms;
	global $cur_lang;
	return $lang_terms[$term_key][$cur_lang];
}

?>
