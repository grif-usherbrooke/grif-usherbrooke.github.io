<?php
include("header.php");



addTerm("group_description", 
			"Le GRIF regroupe les chercheuses et chercheurs de
            l'<a href=\"https://www.usherbrooke.ca\">Université de
            Sherbrooke</a> travaillant dans les domaines liés aux
            aspects théoriques de l'informatique. Les membres du
            GRIF possèdent notamment une expertise en
            algorithmique, en bio-informatique, en méthodes formelles, en informatique
            quantique et en théorie des automates.", 
			
			"The GRIF brings together researchers of the <a
            href=\"https://www.usherbrooke.ca\">Université de
            Sherbrooke</a> working in fields related to the
            theoretical aspects of computer science. The expertise of
            the GRIF includes algorithms, bioinformatics,
            formal methods, quantum computing and automata theory."
			);

			
addTerm("section_members", "Membres", "Members");
addTerm("section_profs", "Professeur·e·s", "Professors");
addTerm("section_profs_associate", "Professeur·e·s associé·e·s", "Affiliated professors");
addTerm("section_postdoc", "Postdoctorant·e·s", "Postdocs");
addTerm("section_phd", "Doctorant·e·s <span style='font-size: 75%'>(Ph.D.)</span>", "Ph.D. students");
addTerm("section_msc", "Étudiant·e·s à la maîtrise <span style='font-size: 75%'>(M.Sc.)</span>", "Master's students");
addTerm("section_alumni", "Ancien·ne·s étudiant·e·s", "Former students");
addTerm("section_seminars", "Séminaires", "Seminars");
addTerm("section_research", "Recherche", "Research");
addTerm("section_teaching", "Enseignement", "Teaching");


//MEMBERS TERMS
addTerm("_supervised_by", 
			"avec ",
			"with ");
addTerm("phd_supervised_by", 
			"doctorat avec ",
			"Ph.D. with ");
addTerm("msc_supervised_by", 
			"maîtrise avec ",
			"Master's with ");
addTerm("phd_intern_supervised_by",
			"stage de doctorat avec ",
			"Ph.D. internship with ");
addTerm("msc_intern_supervised_by",
			"stage de maîtrise avec ",
			"Master's internship with ");
addTerm("info", 
			"informatique",
			"computer science");
addTerm("biochimie", 
			"biochimie",
			"biochemistry");

function student($name, $subject, $degree, $advisor, $webpage="") {
    $name = "<b>" . $name . "</b>";
    
    if ($webpage !== "") {
        $name = "<a href='" . $webpage . "'>" . $name . "</a>";
    }
    
    return ("<li>" . $name . ": " . getTerm($subject) .
            "<span style='font-size: 80%;'> (" .
            getTerm($degree . "_supervised_by") .
            " " . $advisor . ")</li>");
}

//EXPERTISES OF OUR MEMBERS
addTerm("mbeaudry_expertise", 
			"théorie des automates, algèbre, complexité du calcul",
			"automata theory, algebra, computational complexity");
addTerm("mblondin_expertise", 
			"vérification formelle, théorie des automates, <em>model checking</em>, complexité du calcul, logique",
			"formal verification, automata theory, model checking, computational complexity, logic");
addTerm("mfrappier_expertise", 
			"méthodes formelles de spécification, sécurité, gestion du consentement",
			"formal specification, security, consent management");
addTerm("mlafond_expertise", 
			"bio-informatique, algorithmique, théorie des graphes, complexité paramétrée",
			"bioinformatics, algorithms, graph theory, phylogenetics, computational complexity");
addTerm("ouangraoua_expertise", 
			"biologie computationnelle et bio-informatique, algorithmique, phylogénétique, structure des ARN",
			"bioinformatics and computational biology, algorithms, phylogenetics, RNA structure");
addTerm("ntahiri_expertise", 
			"bio-informatique, phylogénétique, classification, <em>clustering</em>, algorithmique",
			"bioinformatics, phylogenetics, classification, clustering, algorithms");
addTerm("dtouchette_expertise", 
			"informatique quantique, théorie de l'information, complexité de la communication",
			"quantum computing, information theory, communication complexity");
			
			
			
//RESEARCH
addTerm("fields_we_cover", 
			"Les activités de recherche du GRIF touchent aux domaines suivants:",
			"The research activities of the GRIF cover the following topics:"
			);
addTerm("funding_sources", 
			"Les membres du GRIF sont financés par plusieurs organismes
			  subventionnaires tels que le Conseil de recherches en
			  sciences naturelles et en génie du Canada (CRSNG) et le
			  Fonds québécois de la recherche sur la nature et les
			  technologies (FRQNT).", 
			"The members of the GRIF are funded by several organizations
			  such as the Research Council of Canada in
			  Natural Sciences and Engineering Canada (NSERC) and the
			  Fonds québécois de la recherche sur la nature et les
			  technologies (FRQNT)."
			  );
			  
			  
addTerm("join_us", 
			"Si vous désirez effectuer un stage de recherche, une
			  maîtrise, un doctorat ou un stage postdoctoral au GRIF,
			  veuillez contacter l'un·e
			  de nos <a href='#membres'>professeur·e·s</a>.", 
			  
			"If you are interested in a research internship or in a master's, Ph.D. or postdoctoral position, please contact one
				of our <a
				href='#membres'>professors</a>."
			);

addTerm("list_of_fields", 
			"<li>algorithmique</li>
            <li>bio-informatique</li>
            <li>biologie computationnelle</li>
            <li>classification</li>
            <li>clustering</li>
            <li>complexité du calcul</li>
            <li>complexité paramétrée</li>
            <li>cryptographie et sécurité</li>
            <li>informatique quantique</li>
            <li>logique</li>
            <li>méthodes formelles</li>
            <li>spécification et raffinement</li>
            <li>théorie des automates</li>
            <li>théorie des graphes</li>
            <li>théorie de l'information</li>
            <li>théorie du calcul</li>
            <li>vérification formelle</li>", 
			
	   "<li>algorithms</li>
	    <li>automata theory</li>
            <li>bioinformatics</li>
            <li>classification</li>
            <li>clustering</li>
            <li>computational biology</li>
            <li>computational complexity</li>
            <li>cryptography and security</li>
			<li>formal methods</li>
			<li>formal verification</li>
			<li>graph theory</li>
            <li>information theory</li>
            <li>logic</li>
			<li>parameterized complexity</li>
			<li>quantum computing</li>
            <li>specification and refinement</li>
            <li>theory of computation</li>
			"
            
		);

//TEACHING
addTerm("courses_offered", 
			"Cours de l'Université de Sherbrooke liés aux domaines du GRIF et enseignés par ses membres:",
			"Courses of the Université de Sherbroke related to the fields of the GRIF and taught (in French) by its members:"
			);
addTerm("courses_from_past", 
			"Autres cours enseignés dans le passé:",
			"Other courses previously taught:"
			);
			
			
			
?>

<!-- Highlights -->
      <section class="wrapper style1" id="intro">
	<div class="container">
          <div id="logos" style="padding-top: 30px"></div>
	  <div class="row gtr-200">
	    <section class="col-12 col-12-narrower">
	      <div style="display: flex; justify-content: space-between; align-items: center; width: 95%; padding-left: 20px">
                <img src="./img/automate.svg" height="110" id="logos" style="max-width: 17.5%;">
                <img src="./img/quantique.svg" height="160" id="logos" style="max-width: 17.5%;">
                <img src="./img/logique.svg" height="75" id="logos" style="max-width: 17.5%;">
                <img src="./img/graphe.svg" height="150" id="logos" style="max-width: 17.5%;">
                <img src="./img/bio.svg" height="100" id="logos" style="max-width: 17.5%;">
	      </div>
	    </section>
          </div>
          <div id="logos" style="padding-top: 50px"></div>
          <div>
            <?= getTerm("group_description") ?>
          </div>
	</div>
      </section>

      <section class="wrapper style1" id="membres">
	<div class="container">
          <header>
            <h2><?= getTerm("section_members") ?></h2>
          </header>
          <h3><?= getTerm("section_profs") ?></h3>
          <ul>
            <li><a href="http://info.usherbrooke.ca/mblondin"><b>Michael
            Blondin</b></a>: 
			<?= getTerm("mblondin_expertise") ?>
			</li>

            <li><a href="http://www.dmi.usherb.ca/~frappier/"><b>Marc
            Frappier</b></a>: 
			<?= getTerm("mfrappier_expertise") ?>
			</li>

            <li><a href="http://info.usherbrooke.ca/mlafond/"><b>Manuel
            Lafond</b></a>: 
			<?= getTerm("mlafond_expertise") ?>
			</li>

            <li><a href="https://cobius.usherbrooke.ca"><b>Aïda
            Ouangraoua</b></a>: 
			<?= getTerm("ouangraoua_expertise") ?>
			</li>

            <li><a href="https://tahirinadia.github.io/"><b>Nadia Tahiri</b></a>: 
			<?= getTerm("ntahiri_expertise") ?>
			</li>

                        <li><a href="https://www.usherbrooke.ca/informatique/nous-joindre/personnel/corps-professoral/professeurs/dave-touchette"><b>Dave Touchette</b></a>: 
			<?= getTerm("dtouchette_expertise") ?>
			</li>
          </ul>

          <h3><?= getTerm("section_profs_associate") ?></h3>
          <ul>
            <li><a href="http://info.usherbrooke.ca/mbeaudry"><b>Martin
    Beaudry</b></a>: Université de Sherbrooke
    (<?= getTerm("mbeaudry_expertise") ?>)
			</li>

            <li><a href="https://fredericgervais.com"><b>Frédéric
                Gervais</b></a>: Université Paris-Est Créteil,
            France</li>
            
            <li><a href="http://lacl.univ-paris12.fr/laleau/"><b>Régine
                Laleau</b></a>: Université Paris-Est Créteil, France</li>

            <li><a href="http://www-public.imtbs-tsp.eu/~mammar_a/"><b>Amel
                                    Mammar</b></a>: Télécom SudParis, France</li>
          </ul>

    
          <h3><?= getTerm("section_postdoc") ?></h3>
          <ul>
            <?= student("Ibrahim Chegrane", "info", "",
                        "Manuel Lafond") ?>
          </ul>
    
          <h3><?= getTerm("section_phd") ?></h3>
          <ul>
            <?= student("Diego de Azevedo Oliveira", "info", "",
                        "Marc Frappier") ?>
            <?= student("Chaymae El Jabri", "info", "",
                        "Marc Frappier") ?>
            <?= student("Safa Jammali", "info", "",
                        "Aïda Ouangraoua") ?>
            <?= student("Aleksandr V. Koshkarov", "info", "",
                        "Nadia Tahiri") ?>              
            <?= student("Lionel Nganyewou Tidjon", "info", "",
                        "Marc Frappier") ?>
            <?= student("Philip Offtermatt", "info", "",
                        "Michael Blondin",
                        "https://p-offtermatt.github.io/") ?>
            <?= student("Anaïs Vannutelli", "biochimie", "",
                        "Aïda Ouangraoua") ?>
            <?= student("Michel-Ange Zamor", "info", "",
                        "Marc Frappier") ?>
          </ul>
    
          <h3><?= getTerm("section_msc") ?></h3>
          <ul>
            <?= student("Fadi Abu Salem", "info", "",
                        "Nadia Tahiri") ?>
            <?= student("Sarah Belhamiti", "biochimie", "",
                        "Aïda Ouangraoua") ?>
            <?= student("Marc-André Bossanyi", "info", "",
                        "Aïda Ouangraoua") ?>
            <?= student("Noé Canva", "info", "",
                        "Michael Blondin") ?>
            <?= student("Olivier Desmarais", "info", "",
                        "Nadia Tahiri") ?>
            <?= student("Ali Fotouhi", "info", "",
                        "Aïda Ouangraoua") ?>
            <?= student("François Ladouceur", "info", "",
                        "Michael Blondin") ?>
            <?= student("Wanlin Li", "info", "",
                        "Nadia Tahiri") ?>
            <?= student("Alitzel Lopez", "info", "",
                        "Manuel Lafond") ?>
            <?= student("Ricardo Andres Pastrana", "info", "",
                        "Manuel Lafond") ?>                     
            <?= student("Philippe-Antoine Plante", "info", "",
                        "Marc Frappier") ?>
            <?= student("Alex Sansfaçon-Buchanan", "info", "",
                        "Michael Blondin") ?>
          </ul>

          <h3><?= getTerm("section_alumni") ?></h3>
          <ul>
            <?= student("Vincent Fély", "info", "msc",
                        "Marc Frappier") ?>
            <?= student("Juliette Fournis d'Albiat", "info", "msc_intern",
                        "Michael Blondin") ?>              
            <?= student("Steve Jeffrey Tueno Fotso", "info", "phd",
                        "Marc Frappier") ?>
            <?= student("Esaie Kuitche", "info", "phd",
                        "Aïda Ouangraoua") ?>
            <?= student("Félix Vigneault", "info", "msc",
                        "Marc Frappier") ?>
          </ul>
        </div>
      </section>

      <section class="wrapper style1" id="seminaires">
	<div class="container">
          <header>
            <h2><?= getTerm("section_seminars") ?></h2>
          </header>
          <ul>
            <?php
              include("seminars.php");
            ?>
          </ul>
        </div>
      </section>

      <section class="wrapper style1" id="recherche">
	<div class="container">
          <header>
            <h2><?= getTerm("section_research") ?></h2>
          </header>
          <?= getTerm("fields_we_cover") ?>
		  <br /><br />

          <ul id="fields">
            <?= getTerm("list_of_fields") ?>
          </ul>

		  
		  <?= getTerm("funding_sources") ?>
		  <br /><br />

		  <?= getTerm("join_us") ?>
          
        </div>
      </section>

    <section class="wrapper style1" id="enseignement">
	<div class="container">
          <header>
            <h2><?= getTerm("section_teaching") ?></h2>
          </header>
		  <?= getTerm("courses_offered") ?>
          <br /><br />

          <ul>
            <li><a href="https://www.usherbrooke.ca/admission/fiches-cours/MAT115/">MAT115
            – Logique et mathématiques discrètes</a></li>

            <li><a href="https://www.usherbrooke.ca/admission/fiches-cours/IFT313/">IFT313
            – Introduction aux langages formels</a></li>

            <li><a href="https://www.usherbrooke.ca/admission/fiches-cours/IFT339/">IFT339
            – Structures de données</a></li>

            <li><a href="https://www.usherbrooke.ca/admission/fiches-cours/IFT436/">IFT436
            – Algorithmes et structures de données</a></li>


            <li><a href="https://www.usherbrooke.ca/admission/fiches-cours/IFT503/">IFT503/IFT711
            – Théorie du calcul</a></li>
            
            <li><a href="https://www.usherbrooke.ca/admission/fiches-cours/IGL501/">IGL501/IGL710 – Méthodes formelles en génie logiciel</a></li>

            <li><a href="https://www.usherbrooke.ca/admission/fiches-cours/IGL752/">IGL502/IGL752
            – Techniques de vérification et de validation</a></li>

<li><a href="https://www.usherbrooke.ca/admission/fiches-cours/IFT606/">IFT606 – Sécurité et cryptographie</a></li>

            <li><a href="https://www.usherbrooke.ca/admission/fiches-cours/BIN702/">BIN702
            – Algorithmes pour la bio-informatique</a></li>

            <li><a href="https://www.usherbrooke.ca/admission/fiches-cours/BIN704/">BIN704
            – Sujets choisis en bio-informatique</a></li>

            <li><a href="https://www.usherbrooke.ca/admission/fiches-cours/BIN710/">BIN710
            – Forage de données pour la bio-informatique</a></li>

            <li><a href="https://www.usherbrooke.ca/admission/fiches-cours/IFT800/">IFT800
            – Algorithmique</a></li>

            <li><a href="https://www.usherbrooke.ca/admission/fiches-cours/IFT814/">IFT814
            – Cryptographie</a></li>
          </ul>

          <?= getTerm("courses_from_past") ?><br /><br />

          <ul>
            <li><a href="https://www.usherbrooke.ca/admission/fiches-cours/IFT767/">IFT767
            – Théorie de la complexité</a></li>

            <li><a href="https://www.usherbrooke.ca/admission/fiches-cours/IFT769/">IFT769
            – Sujets choisis en informatique théorique</a></li>

            <li><a href="https://www.usherbrooke.ca/admission/fiches-cours/IFT781/">IFT781
            – Théorie des automates et des langages formels</a></li>
          </ul>
        </div>
      </section>
	  
	  
<?php
include("footer.php");
?>
	  
