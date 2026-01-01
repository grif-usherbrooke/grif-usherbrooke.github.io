<?php
$talks = array_map('str_getcsv', file('seminars.csv'));

$speaker_index = 0;
$title_index   = 1;
$date_index    = 2;
$url_index     = 3;
$slides_index  = 4;
$note_index    = 5;

array_shift($talks); //removes first header row

foreach ($talks as $talk)
{
    ?>
    
    <li>
    <?= ($talk[$url_index] != "") ? "<a href='" . $talk[$url_index] . "'>" : "" ?>
    <?= $talk[$date_index] ?><?= ($talk[$url_index] != "") ? "</a>" : "" ?>:
    <?= $talk[$speaker_index] ?> – <em><?= $talk[$title_index] ?></em>
    <?= ($talk[$slides_index] != "") ? "<a href='" . $talk[$slides_index] . "'><i class='icon fa-file-pdf-o' aria-hidden='true'></i></a>" : "" ?>
    <?= ($talk[$note_index] != "") ? "<span style='font-size: 80%;'>(" . $talk[$note_index] . ")</span>" : "" ?>
    </li>
    
    <?php
}
?>
