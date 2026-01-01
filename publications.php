<?php
include("header.php");

addTerm("pdf_preview", "aperçu pdf", "pdf preview");
addTerm("since", "depuis", "since");

/*This function takes a list of full author names in format 
Tarjan, Robert; Corneil, Derek G;
and returns the same authors in format
R Tarjan, DG Corneil
*/
function parse_authors_string($authors_in)
{
	//parse authors string.  current format = name, surname; name, surname; ...
	//we just keep the initials of the first name(s) and produce a format of the type A Lastname1, B Lastname2, ...
	$authors = explode(";", $authors_in);
	
	$parsed_authors = array();
	for ($i = 0; $i < sizeof($authors); $i++)
	{
		$names = explode(",", $authors[$i]);
		$lastname = $names[0];
		$firstnames = explode(" ", $names[1]);
		$initials = "";
		for ($j = 1; $j < sizeof($firstnames); $j++)
		{
			$initials .= $firstnames[$j][0];
		}
		if (str_replace(" ", "", $lastname) != "")	//prevent empty names
		{
			array_push($parsed_authors, $initials . " " . $lastname);
		}
		
		
	}
	$authorstr = implode(", ", $parsed_authors);
	return $authorstr;
}

function cmp_year($a, $b)
{
    if ($a[6] == $b[6]) {
        return 0;
    }
    
    return ($a[6] > $b[6]) ? -1 : 1;
}

?>

<?php
//TODO: this is the style for the publications.  Ideally move this to a .css file
?>
<style type='text/css'>
#publications .container
{
	max-width:900px;
}

.pub-title, .pub-authors, .pub-where, .pub-where-extra, .pub-links, .pub-notes
{
	display:inline;
}

.pub-where
{
    font-weight: 500;
}

.pub-title
{
	font-style: italic;
}

.pub-notes
{
	font-style:italic;
}


.pub-year-section
{
	font-size: 160%;
    font-weight: bold;
    /*background-color: #fafafa;*/
	border-bottom: 1px solid #888888;
    padding: 8px 4px;
    margin-top: 10px;
	margin-bottom:3px;
}

</style>






<section class="wrapper style1" id="publications">
	<div class="container">
        <header>
        <h2>Publications <span style="font-size: 60%">(<?= getTerm("since") ?> 2012)</span></h2>
        </header>

		<ul class='pub-list'>

			<?php
			
			//handy one-liner that parses a csv file.  
			$papers = array_map('str_getcsv', file('publications.csv'));
			
			array_shift($papers);	//removes first header row
			
			$title_index = 1;
			$author_index = 0;
			$where_index = 2;
			$volume_index = 3;
			$number_index = 4;
			$pages_index = 5;
			$year_index = 6;
			$doi_index = 8;
			$file_index = 9;
			$note_index = 11;
			
			$prev_year = "";

            usort($papers, "cmp_year"); // sort papers by year
			
			foreach ($papers as $paper)
			{
				
				//when we start a new year, make a new division
				if ($paper[$year_index] != $prev_year)	
				{
					?>

					<div class='pub-year-section' id=<?= $paper[$year_index] ?>>
						<?= $paper[$year_index] ?>
					</div>

					<?php
					
					$prev_year = $paper[$year_index];
				}
				
				?>
				
				
				<li>
					<div class='pub-authors'>	
						<?= htmlspecialchars(  parse_authors_string($paper[$author_index])  ) ?>.
					</div>
					<div class='pub-title'>
						&quot;<?= htmlspecialchars($paper[$title_index]) ?>&quot;.
					</div>
					
					<div class='pub-where'>
						<?= $paper[$where_index] ?>,
                    </div>
					<div class='pub-where-extra'>
						<?= ($paper[$volume_index] != "" ? 
								$paper[$volume_index] . ($paper[$number_index] != "" ? " (" . $paper[$number_index] . ")" : "") . "," 
							 : "")
						?>
						<?= ($paper[$pages_index] != "" ? $paper[$pages_index] . "," : "") ?>
						<?= $paper[$year_index] ?>.
						
						
					</div>
					
					<?php
					//if there is a DOI, add a link.  If there is a file, add a link.
					if ($paper[$doi_index] != "" || $paper[$file_index] != "")
					{
					?>
						<div class='pub-links'>
						
							<?php
							
							if ($paper[$doi_index] != "")
							{
								echo("<br>DOI : <a href='https://doi.org/" . $paper[$doi_index] . "' target='_blank'>" . $paper[$doi_index] . "</a> ");
							}
							
							if ($paper[$file_index] != "")
							{
								echo(" (<a href='papers/" . $paper[$file_index] . "' target='_blank'>" . getTerm("pdf_preview") . "</a>)");
							}
							
							
							
							?>
						</div>
					<?php
					}
					
					/*
					//if there's a note (special text) then display it
					if ($paper[$note_index] != "")
					{
					?>
						<div class='pub-notes'>
							<?= $paper[$note_index] ?>
						</div>
					<?php
					}
					*/
					?>
					
					
					
					
				</li>
			<?php
			}
			
			?>
		</ul>
	</div>
</section>


<?php
include("footer.php");
?>
