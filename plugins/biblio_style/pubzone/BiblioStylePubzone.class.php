<?php

/**
 * @file
 * Pubzone style.
 */

class BiblioStylePubzone extends BiblioStyleBase implements BiblioStyleImportInterface {

  /**
   * @inheritdoc
   */
  public function importData($data, $options = array()) {

    $map = $this->getMapping();
    $map = $map['field'];

    // Array of Biblios.
    $biblios = array();

    db_set_active('pubzonedb');
    
    $query = db_select('publication', 'p');
    $query->join('group_publication', 'gp', 'p.publication_id=gp.publication_id');
    $query->join('venue', 'v', 'p.venue_id=v.venue_id');
    //$query->join('attachment', 'a', 'p.pdf_file=a.attachment_id');
    $query->fields('p', array('title', 'year', 'month', 'publication_id', 'type', 'doi_url', 'abstract', 'supervisor'));
    //$query->fields('v', array('name'));
    $query->addField('p', 'venueName', 'venue_name');
    $query->addField('v', 'name', 'booktitle'); //TODO maybe map to booktitle or secondary title
    //$query->fields('a', array('contentType', 'description', 'filename'));
    //$query->addField('a', 'filename', 'pdf');
    $query->condition('gp.group_id', 1);
    $query->condition('p.is_deleted', 0);
    $query->condition('p.isActive', 1);
    $query->orderBy('p.year', 'ASC');
    $query->orderBy('p.month', 'ASC');
    $query->orderBy('p.publication_id', 'ASC');
    //This limits the import to 100
    //$query->range(1,99);

    //TODO keywords
    
    $result = $query->execute();
    db_set_active('default');

    foreach($result as $row) {
      if ($row->type == 'book_chapter') {
        continue;
      }
      //check if title or type is NULL
      if (!$row->type || !$row->title) {
        continue;
      }
      if ($row->type == 'phd_thesis' || $row->type == 'master_thesis') {
        if ($row->venue_name) {
          $row->booktitle = $row->venue_name;
        }
      }
      //Check if venue name is actually book title
      else {
        //Check if booktitle is 'ETH Zurich'
        if ($row->venue_name && substr($row->booktitle, 0, 3) === "ETH") {
          $row->booktitle = $row->venue_name;
          $row->venue_name = NULL;
        }
      }

      $entry = (array) $row;
      //Remove HTML special encoding
      foreach($entry as $k => $v) {
        $entry[$k] =  html_entity_decode($v);
      }

      $biblio_type = $this->getTypeMapping($row->type);
      
      $biblio = biblio_create($biblio_type);
      //Get wrapper
      $wrapper = entity_metadata_wrapper('biblio', $biblio);
      foreach (array_keys($map) as $key) {
        if (in_array($key, array('author', 'editor'))) {
          continue;
        }
        
        //Get property_name
        $property_name = $map[$key]['property'];

        if (!isset($wrapper->{$property_name})) {
          //biblio_create_field($property_name, 'biblio', $biblio_type);
          continue;
        }

        $method = $map[$key]['import_method'];
        $this->{$method}($wrapper, $key, $entry);

      } //foreach $map

      //Add contributors
      $contributors = $this->getPublicationAuthors($row->publication_id);
      $this->importContributors($wrapper, $contributors);


      //Add sections/categories
      $sections = $this->getPublicationSections($row->publication_id);
      $this->importSections($wrapper, $sections);

      //Add attachment
      $attachments = $this->getAttachments($row->publication_id);
      $this->importPDF($wrapper, $attachments);

      //Add keywords
      //TODO this is broken
      $keywords = $this->getPublicationKeywords($row->publication_id);
      if (!empty($keywords)) {
        $this->importKeywordsList($wrapper, $keywords);
      }

      //Add to list
      $biblios['success'][] = $wrapper->value();
    } //foreach $row

    return $biblios;
  }

  /**
   * Get Publication Contributors
   */
  public function getPublicationAuthors($publication_id) {
    db_set_active('pubzonedb');
    
    $query = db_select('author', 'a');
    $query->join('person', 'p', 'a.user_id=p.user_id');
    $query->fields('p', array('first_name', 'last_name'));
    $query->condition('a.publication_id', $publication_id);
    $query->orderBy('a.priority', 'ASC');
    
    $authors = $query->execute();
    db_set_active('default');

    $contributors = array();
    foreach($authors as $author) {
      $contributor_array['firstname'] = html_entity_decode(trim($author->first_name));
      $contributor_array['lastname'] = html_entity_decode(trim($author->last_name));
      $contributor_array['initials'] = '';//($contributor_array['firstname'][0].$contributor_array['lastname'][0]);
      $contributor_array['prefix'] = '';
      $contributor_array['suffix'] = '';

      // Get existing Biblio Contributor object, save it if it doesn't exist.
      $biblio_contributor = biblio_contributor_create($contributor_array);
      $biblio_contributor = BiblioContributorUtility::getBiblioContributor($biblio_contributor);

      $contributors[] = $biblio_contributor;
    }

    return $contributors;
  }

  public function getPublicationSections($publication_id) {
    db_set_active('pubzonedb');
    
    $query = db_select('section_publication', 'sp');
    $query->join('section', 's', 'sp.section_id=s.section_id');
    $query->fields('s', array('section_name'));
    $query->condition('sp.publication_id', $publication_id);
    
    $result = $query->execute();
    db_set_active('default');

    $sections = array();

    foreach($result as $row) {
      $sections[] = $row->section_name;
    }

    return $sections;
  }

  public function getAttachments($publication_id) {
    db_set_active('pubzonedb');

    $query = db_select('attachment', 'a');
    $query->join('publication', 'p', 'p.pdf_file=a.attachment_id');
    //$query->addField('a', 'filename', 'pdf');
    $query->fields('a', array('filename'));
    $query->condition('p.publication_id', $publication_id);

    $result = $query->execute();
    db_set_active('default');

    $attachments = array();
    foreach($result as $row) {
      $attachments[] = $row->filename;
    }

    return $attachments;
  }

  public function getPublicationKeywords($publication_id) {
    db_set_active('pubzonedb');
    
    $query = db_select('keyword', 'k');
    $query->fields('k', array('keyword'));
    $query->condition('k.publication_id', $publication_id);
    
    $result = $query->execute();
    db_set_active('default');

    $keywords = array();

    foreach($result as $row) {
      $keywords[] = $row->keyword;
    }

    return $keywords;
  }

  /**
   * Get Type Mapping
   */
  public function getTypeMapping($type) {
    if ($type == 'tech_report') {
      return 'technical_report';
    } else {
      return $type;
    }
  }

  /**
   * Import keywords.
   *
   * @param EntityMetadataWrapper $wrapper
   *   The wrapped Biblio object.
   * @param $key
   *   The key to import.
   * @param $entry
   *   The data to import from.
   */
  public function importKeywords(EntityMetadataWrapper $wrapper, $key, $entry) {
    if (empty($entry[$key])) {
      return;
    }
    $keywords = str_replace(';', ',', $entry[$key]);
    $this->importKeywordsList($wrapper, explode(',', $keywords));
  }

  /**
   * Import a generic property.
   *
   * @param EntityMetadataWrapper $wrapper
   *   The wrapped Biblio object.
   * @param $key
   *   The key to import.
   * @param $entry
   *   The data to import from.
   */
  public function importGeneric(EntityMetadataWrapper $wrapper, $key, $entry) {
    if (empty($entry[$key])) {
      return;
    }

    $map = $this->getMapping();
    $map = $map['field'];
    $property = $map[$key]['property'];

    // Some BibTex might come we double curly brackets, so strip them out from
    // the beginning and end of the value.
    $value = trim($entry[$key], '{}');

    $wrapper->{$property}->set($value);

  }

  /**
   * Import year.
   *
   * @param EntityMetadataWrapper $wrapper
   *   The wrapped Biblio object.
   * @param $key
   *   The key to import.
   * @param $entry
   *   The data to import from.
   */
  public function importYear(EntityMetadataWrapper $wrapper, $key, $entry) {
    if (empty($entry[$key])) {
      return;
    }
    if (strtolower($entry[$key]) == 'in press') {
      // Biblio is in press, set the Biblio's status to be "In Press" and leave
      // the year empty.
      $wrapper->biblio_status->set('in_press');
      return;
    }

    $this->importGeneric($wrapper, $key, $entry);
  }
  
  /**
   * Import a month.
   *
   * @param EntityMetadataWrapper $wrapper
   *   The wrapped Biblio object.
   * @param $key
   *   The key to import.
   * @param $entry
   *   The data to import from.
   */
  public function importMonth(EntityMetadataWrapper $wrapper, $key, $entry) {
    if (empty($entry[$key])) {
      //Assign default value January
      $entry[$key] = '1';
    }

    $this->importGeneric($wrapper, $key, $entry);


    /*$map = $this->getMapping();
    $map = $map['field'];
    $property = $map[$key]['property'];

    // Some BibTex might come we double curly brackets, so strip them out from
    // the beginning and end of the value.
    $value = trim($entry[$key], '{}');

    $wrapper->{$property}->set($value);*/

  }

  /**
   * Import publisher.
   *
   * @param EntityMetadataWrapper $wrapper
   *   The wrapped Biblio object.
   * @param $key
   *   The key to import.
   * @param $entry
   *   The data to import from.
   */
  public function importPublisher(EntityMetadataWrapper $wrapper, $key, $entry) {
    $types = array(
      'organization',
      'school',
      'institution',
      'publisher',
    );

    foreach ($types as $type) {
      if (!empty($entry[$type])) {
        $value = $entry[$type];
        break;
      }
    }

    if (empty($value)) {
      return;
    }

    $entry[$key] = $value;
    $this->importGeneric($wrapper, $key, $entry);
  }

  /**
   * Import secondary title.
   *
   * @param EntityMetadataWrapper $wrapper
   *   The wrapped Biblio object.
   * @param $key
   *   The key to import.
   * @param $entry
   *   The data to import from.
   */
  public function importSecondaryTitle(EntityMetadataWrapper $wrapper, $key, $entry) {
    $types = array(
      'booktitle',
      'series',
      'journal',
    );

    foreach ($types as $type) {
      if (!empty($entry[$type])) {
        $value = $entry[$type];
        break;
      }
    }

    if (empty($value)) {
      return;
    }

    $months = array('January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December');
    $monthIdx = 0;
    $venue = '';
    foreach($months as $idx => $month) {
      if (($mpos = strpos($value, $month)) !== false) {
        //Check if tail contains venue name, find comma after month
        $vpos = strpos(substr($value, $mpos), ',');
        if ($vpos !== false) {
          $venue = substr($value, $mpos+$vpos);
          //Check for space, commma or year
          $offset = 0;
          while ($venue[$offset] == ' ' || $venue[$offset] == ',' || is_numeric($venue[$offset])) {
            $offset++;
          }
          $venue = substr($venue, $offset);
          if (strpos($venue, 'Proceedings') !== false) {
            $venue = '';
          }
        }
        
        //Find last comma before month
        $cpos = strrpos(substr($value, 0, $mpos), ',');
        //Remove tail containing month
        if ($cpos !== false && $cpos < $mpos) {
          if ($value[$cpos-1] == ' ') {
            $value = substr($value, 0, $cpos-1);
          } else {
            $value = substr($value, 0, $cpos);
          }
        }
        $monthIdx = $idx;
        break;
      }
    }

    //Import month based on text
    //January is default anyway, so we only care for other months
    if ($monthIdx > 0 && $entry['month'] === '0') {
      $entry['month'] = strval($monthIdx+1);
      $this->importMonth($wrapper, 'month', $entry);
    }

    //Import venue based on text
    if (strlen($venue) > 2) {
      $entry['venue_name'] = $venue;
      $this->importVenueName($wrapper, 'venue_name', $entry);
    }

    $entry[$key] = $value;
    $this->importGeneric($wrapper, $key, $entry);
  }

  /**
   * Import tertiary title.
   *
   * @param EntityMetadataWrapper $wrapper
   *   The wrapped Biblio object.
   * @param $key
   *   The key to import.
   * @param $entry
   *   The data to import from.
   */
  public function importTertiaryTitle(EntityMetadataWrapper $wrapper, $key, $entry) {
    if (empty($entry['series']) || empty($entry['booktitle'])) {
      return;
    }

    $entry[$key] = $entry['series'];
    $this->importGeneric($wrapper, $key, $entry);
  }

  /**
   * Import venue name.
   *
   * @param EntityMetadataWrapper $wrapper
   *   The wrapped Biblio object.
   * @param $key
   *   The key to import.
   * @param $entry
   *   The data to import from.
   */
  public function importVenueName(EntityMetadataWrapper $wrapper, $key, $entry) {
    if (empty($entry['venue_name'])) {
      return;
    }

    $types = array(
      'conference_paper',
      'demo',
      'workshop_paper',
    );
    if (!in_array($entry['type'], $types)) {
      return;
    }

    $this->importGeneric($wrapper, $key, $entry);
  }

  /**
   * Import contributors.
   *
   * @param EntityMetadataWrapper $wrapper
   *   The wrapped Biblio object.
   * @param $entry
   *   The data to import from.
   */
  public function importContributors(EntityMetadataWrapper $wrapper, $contributors) {
    /*foreach (array('author', 'editor') as $type) {
      if (empty($entry[$type])) {
        continue;
      }*/

      $biblio = $wrapper->value();

      // Get array of saved contributor objects from string of names.
      //$contributors = BiblioContributorUtility::getBiblioContributorsFromNames($entry[$type]);
      $type = 'author';

      foreach ($contributors as $contributor) {
        // Create contributors field collections without saving them.
        // We do not save the field collections because the whole Biblio object
        // may not be saved if it is duplicate, and in that case we will have
        // field collections without a host. By not saving the field collections
        // here we make sure they will only be saved if and when the whole
        // Biblio is saved.
        $field_collection = entity_create('field_collection_item', array('field_name' => 'contributor_field_collection'));
        $field_collection->setHostEntity('biblio', $biblio);
        $collection_wrapper = entity_metadata_wrapper('field_collection_item', $field_collection);
        $collection_wrapper->biblio_contributor->set($contributor);

        // @todo: Add reference to correct term.
        $term = taxonomy_get_term_by_name(ucfirst($type), 'biblio_roles');
        $term = reset($term);
        $collection_wrapper->biblio_contributor_role->set($term);
      }
    //}
  }

  //They are called section in Pubzone, in Biblio we call them categories
  //TODO potentially could be replaced by importKeywordsList
  public function importSections(EntityMetadataWrapper $wrapper, $sections) {
    if(empty($sections)) {
      return;
    }
    $biblio = $wrapper->value();

    $terms = array();
    foreach ($sections as $section) {
      $term = taxonomy_get_term_by_name($section, 'biblio_categories');
      $term = reset($term);
      $terms[] = $term;
    }
    $wrapper->biblio_category->set($terms);
  }

  public function importSupervisor(EntityMetadataWrapper $wrapper, $key, $entry) {
    if (empty($entry[$key])) {
      return;
    }
    //TODO is this function necessary??
    $this->importGeneric($wrapper, $key, $entry);
  }

  //public function importPDF(EntityMetadataWrapper $wrapper, $key, $entry) {
  public function importPDF(EntityMetadataWrapper $wrapper, $attachments) {
    //Check if there is an attachment
    if (empty($attachments)) {
      return;
    }

    //Check if file exists
    $filename = $attachments[0];//$entry[$key];
    //replace whitespace
    $filename = str_replace(' ', '_', $filename);
    $base = variable_get('file_public_path', conf_path().'/files');
    $path = $base.'/publications/'.$filename;
    if (file_exists($path)) {
      $file = new stdClass();
      $file->uid = 1;
      $file->uri= $path;
      $file->filename = $filename;
      $file->filemime = file_get_mimetype($path);
      $file->filesize = filesize($path);
      $file->status = FILE_STATUS_PERMANENT;
      $file->display = '1';
      //Check if file already saved
      $files = file_load_multiple(array(), array('uri' => $path));
      $efile = reset($files);
      if ($efile == false) {
        file_save($file);
        $wrapper->biblio_pdf->set((array) $file);
      } else {
        $efile->display = '1';
        file_save($efile);
        $wrapper->biblio_pdf->set((array) $efile);
      }
    }
  }

  /**
   * @inheritdoc
   */
  public function render($options = array(), $langcode = NULL) {
    // We clone the biblio, as we might change the values.
    $biblio = clone $this->biblio;
    $wrapper = entity_metadata_wrapper('biblio', $biblio);
    $type = $this->biblio->type;
    dpm($biblio);

    //TODO what is this???
    if ($type == 'thesis' && !empty($wrapper->biblio_type_of_work) && strpos($wrapper->biblio_type_of_work->value(), 'masters') === TRUE) {
      $type = 'mastersthesis';
    }
    //debug
    /*if ($type == 'phd_thesis') {
            dpm($biblio);
    }*/
    $type_info = biblio_get_types_info($type);

    $output = ''; //array();
    $links = '';
    $extras = '';

    $map = $this->getMapping();

    $show_fields = array('title',
                        'author',
                        'secondary_title',
                        'venue_name',
                        'month',
                        'year',
                        'supervisor',
                        'doi_url',
                        'pdf',
                        'slides_pdf',
                        'poster_pdf',
                        'video',
                        'abstract' );

    foreach($show_fields as $field) {
      $info = $map['field'][$field];
      $method = $info['method'];
      $property = $info['property'];

      if (empty($wrapper->{$property})) {
        continue;
      }
      if(!$value = $this->{$method}($wrapper, $property)) {
        continue;
      }
      if ($method == 'formatUrl') {
        $links .= $value;
      } elseif ($property == 'biblio_abstract') {
        $extras = $value;
      } else {
        $output .= $value;
        if ($field == 'venue_name' || $field == 'secondary_title') {
          $output .= ', ';
        }
        if ($field == 'month') {
          $output .= ' ';
        }
      }
    }

    //TODO maybe sort output here
    //$links .= l('<span class="glyphicon glyphicon-tag"></span>', '#', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('pub-cite'))));
    $links .= l('<span class="glyphicon glyphicon-share-alt"></span>', '/publication/'.$biblio->bid, array('html' => TRUE));


    //TODO extras contains abstract
    $output .= '<div class="pub-links">'.$links.'</div>';
    $bibtex = '<pre>'.$biblio->getText('bibtex').'</pre>';
    $output .= '<div class="pub-extras">'.$extras.$bibtex.'</div>';

    $cat = 'data-category="';
    foreach ($wrapper->{'biblio_category'}->value() as $category) {
        $cat .= $category->name . ',';
    }

    $year = $biblio->biblio_year['und'][0]['value'];

    // NOTE: this does not close the div, it must be closed where the rendered text is actually used!
    return '<div class="pub" data-type="' . $type_info['name'] . '" ' . $cat . '" data-year="' . $year . '">'.$output;
  }

  /**
   * Generic format entry.
   *
   * @param EntityMetadataWrapper $wrapper
   *  The wrapper object.
   * @param $key
   *  The property name which holds the value of the field.
   *
   * @return
   *  The value of the property.
   */
  private function formatGeneric(EntityMetadataWrapper $wrapper, $key) {
    return $wrapper->{$key}->value();
  }

  /**
   * Rendering the series property.
   *
   * @param EntityMetadataWrapper $wrapper
   *  The wrapper object.
   * @param $key
   *  The property name which holds the value of the field.
   *
   * @return
   *  The value of the property.
   */
  private function formatSeries(EntityMetadataWrapper $wrapper, $key) {
    //if ($this->biblio->type
    return in_array($this->biblio->type, array('book_chapter','conference_paper')) ? $wrapper->biblio_tertiary_title->value() : $wrapper->biblio_secondary_title->value();
  }

  /**
   * Rendering the organization property.
   *
   * @param EntityMetadataWrapper $wrapper
   *  The wrapper object.
   * @param $key
   *  The property name which holds the value of the field.
   *
   * @return
   *  The value of the property.
   */
  private function formatOrganization(EntityMetadataWrapper $wrapper, $key) {
    return in_array($this->biblio->type, array('book_chapter','conference_paper', 'book')) ? $wrapper->biblio_publisher->value() : NULL;
  }

  /**
   * Rendering the book title property.
   *
   * @param EntityMetadataWrapper $wrapper
   *  The wrapper object.
   * @param $key
   *  The property name which holds the value of the field.
   *
   * @return
   *  The value of the property.
   */
  private function formatBookTitle(EntityMetadataWrapper $wrapper, $key) {
    $title = in_array($this->biblio->type, array('book_chapter','conference_paper')) ? $wrapper->biblio_secondary_title->value() : NULL;
    if ($title === null) {
      return $title;
    } else {
      return '<div class="pub-title">'.$title.'</div>';
    }
  }

  /**
   * Rendering conference title property
   */
  private function formatTitle(EntityMetadataWrapper $wrapper, $key) {
    return '<div class="pub-title"><a href="#">'.$wrapper->{$key}->value().' <span class="glyphicon glyphicon-chevron-down" style="display:inline;"/></span><span class="glyphicon glyphicon-chevron-up" style="display:none;"/></span></a></div>';
  }

  private function formatUrl(EntityMetadataWrapper $wrapper, $key) {
    $icons = array(
      'biblio_url' => 'globe',
      'biblio_pdf' => 'file',
      'biblio_slides_pdf' => 'blackboard',
      'biblio_poster_pdf' => 'picture',
      'biblio_video' => 'film', //or facetime-video
    );
    if ($wrapper->{$key}->value() === NULL) {
      return NULL;
    }
    if ($key == 'biblio_url' || $key == 'biblio_video')
    {
      return l('<span class="glyphicon glyphicon-'.$icons[$key].'"></span>', $wrapper->{$key}->value(), array('html'=>TRUE));
    } else {
      $pdf = $wrapper->{$key}->value();
      if ($pdf) {
        $path = file_create_url($pdf['uri']);
        return l('<span class="glyphicon glyphicon-'.$icons[$key].'"></span>', $path, array('html'=>TRUE));
       }
    }
    return NULL;
  }

  private function formatMonth(EntityMetadataWrapper $wrapper, $key) {
    $months = array('January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December');
    $month = '';
    $idx = $wrapper->{$key}->value();
    if ($idx > 0 && $idx < 13) {
      $month = $months[$idx-1];
    }
    return $month;
  }

  private function formatSupervisor(EntityMetadataWrapper $wrapper, $key) {
    if ($wrapper->{$key}->value()) {
      return '<br>Supervised by: '.$wrapper->{$key}->value();
    }
  }

  /**
   * Rendering the school property.
   *
   * @param EntityMetadataWrapper $wrapper
   *  The wrapper object.
   * @param $key
   *  The property name which holds the value of the field.
   *
   * @return
   *  The value of the property.
   */
  private function formatSchool(EntityMetadataWrapper $wrapper, $key) {
    return $this->biblio->type == 'thesis' ? $wrapper->biblio_publisher->value() : NULL;
  }

  /**
   * Rendering the institution property.
   *
   * @param EntityMetadataWrapper $wrapper
   *  The wrapper object.
   * @param $key
   *  The property name which holds the value of the field.
   *
   * @return
   *  The value of the property.
   */
  private function formatInstitution(EntityMetadataWrapper $wrapper, $key) {
    return $this->biblio->type == 'report' ? $wrapper->biblio_publisher->value() : NULL;
  }

  /**
   * Taxonomy term format entry.
   *
   * @param EntityMetadataWrapper $wrapper
   *  The wrapper object.
   * @param $key
   *  The property name which holds the value of the field.
   *
   * @return String
   *  The value of the property.
   */
  private function formatKeywords($wrapper, $key) {
    if (!$terms = $wrapper->{$key}->value()) {
      return;
    }

    $terms = is_array($terms) ? $terms : array($terms);
    $values = array();
    foreach ($terms as $term) {
      $values[] = $term->name;
    }

    return implode(', ', $values);
  }

  /**
   * Return the value of the publisher property.
   *
   * @param EntityMetadataWrapper $wrapper
   *  The wrapper object.
   * @param $key
   *  The property name which holds the value of the field.
   *
   * @return
   *  The value of the property.
   */
  public function formatPublisher(EntityMetadataWrapper $wrapper, $key) {
    return !in_array($this->biblio->type, array('thesis','report')) ? $wrapper->{$key}->value() : NULL;
  }

  /**
   * Return the value of the entry journal property.
   *
   * @param EntityMetadataWrapper $wrapper
   *  The wrapper object.
   * @param $key
   *  The property name which holds the value of the field.
   *
   * @return
   *  The value of the property.
   */
  public function formatJournal(EntityMetadataWrapper $wrapper, $key) {
    return !in_array($this->biblio->type, array('book','book_chapter', 'conference_paper', 'thesis', 'report')) ? $wrapper->biblio_secondary_title->value() : NULL;
  }

  /**
   * File format entry.
   *
   * @param EntityMetadataWrapper $wrapper
   *  The wrapper object.
   * @param $key
   *  The property name which holds the value of the field.
   *
   * @return string
   *  The value of the property.
   */
  public function formatFiles(EntityMetadataWrapper $wrapper, $key) {
    if ($url = parent::renderEntryFiles($wrapper, $key)) {
      return implode(' , ', $url);
    }
  }

  /**
   * Author contributor format entry.
   *
   * @param EntityMetadataWrapper $wrapper
   *  The wrapper object.
   * @param $key
   *  The property name which holds the value of the field.
   *
   * @return string
   */
  private function formatContributorAuthor(EntityMetadataWrapper $wrapper, $key) {
    return $this->formatContributor($wrapper, $key, 'author');
  }

  /**
   * Editor contributor format entry.
   *
   * @param EntityMetadataWrapper $wrapper
   *  The wrapper object.
   * @param $key
   *  The property name which holds the value of the field.
   *
   * @return string
   *  The contributors name.
   */
  private function formatContributorEditor(EntityMetadataWrapper $wrapper, $key) {
    return $this->formatContributor($wrapper, $key, 'editor');
  }

  /**
   * Helper function to get contributors name.
   *
   * @param EntityMetadataWrapper $wrapper
   *  The wrapper object.
   * @param $key
   *  The property name which holds the value of the field.
   * @param $role
   *
   * @return string
   *  The contributors name.
   */
  private function formatContributor(EntityMetadataWrapper $wrapper, $key, $role) {
    if (!$wrapper->{$key}->value()) {
      return;
    }

    $names = array();
    foreach ($wrapper->{$key} as $sub_wrapper) {
      if (strtolower($sub_wrapper->biblio_contributor_role->label()) != strtolower($role)) {
        continue;
      }

      $contributor = $sub_wrapper->biblio_contributor->value();

      // Add a dot to each letter in initials.
      if (!empty($contributor->initials)) {
        $letters = explode(' ', $contributor->initials);
        foreach ($letters as &$letter) {
          $letter .= '.';
        }
        $contributor->initials = implode(' ', $letters);
      }

      // Get the contributor's full name, which is all non-empty name parts.
      $fields = array('firstname', 'lastname');
      $full_name = array();
      foreach ($fields as $field) {
        if (empty($contributor->{$field})) {
          // No value in field.
          continue;
        }

        // Add the field's value to the full name.
        $full_name[] = $contributor->{$field};
      }

      // Add the full name to the list of contributors.
      $thisname = implode(' ', $full_name);
      $names[] = l($thisname, 'author/'.$contributor->{'cid'}.'/'.$thisname);
    }

    $output = $names[0];
    if (count($names) > 1) {
      $output = implode(', ', array_slice($names, 0, -1));
      $output = $output.', and '.$names[count($names)-1];
    }

    return '<div class="pub-author">'.$output.'</div>';
  }

  /**
   * Mapping of Biblio and BibTeX.
   *
   * - type: Array with the Biblio type as key, and the BibTeX type as the
   *   value.
   * - field: Array with field mapping, keyed by BibTeX name, and the Biblio
   *   field as the value.
   */
  public function getMapping() {
    $return  = array(
      'field' => array(
        'abstract' => array('property' => 'biblio_abstract'),
        'address' => array('property' => 'biblio_place_published'),
        // @todo: Use bilbio_file instead.
        'attachments' => array(
          'property' => 'biblio_image',
          'method' => 'renderEntryFiles'
        ),
        'author' => array(
          'property' => 'contributor_field_collection',
          'method' => 'formatContributorAuthor',
        ),
        'bibtex' => array(
          'property' => 'bibtext',
          'method' => 'formatBibText',
          'use_key' => FALSE,
        ),
        'bibtexCitation' => array('property' => 'biblio_citekey'),
        'booktitle' => array(
          'property' => 'booktitle',
          'method' => 'formatBookTitle',
        ),
        'chapter' => array('property' => 'biblio_section'),
        'doi' => array('property' => 'biblio_doi'),
        'editor' => array(
          'property' => 'contributor_field_collection',
          'method' => 'formatContributorEditor',
        ),
        'edition' => array('property' => 'biblio_edition'),
        // @todo: Special entry types?
        'isbn' => array('property' => 'biblio_isbn'),
        'issn' => array('property' => 'biblio_issn'),
        'institution' => array(
          'property' => 'institution',
          'method' => 'formatInstitution',
        ),
        'journal' => array(
          'property' => 'journal',
          'method' => 'formatJournal',
        ),
        'keywords' => array(
          'property' => 'biblio_keywords',
          'method' => 'formatKeywords',
          'import_method' => 'importKeywords',
        ),
        'month' => array(
          'property' => 'biblio_month',
          'method' => 'formatMonth',
          'import_method' => 'importMonth',
        ),
        'note' => array('property' => 'biblio_notes'),
        'number' => array('property' => 'biblio_number'),
        'organization' => array(
          'property' => 'organization',
          'method' => 'formatOrganization',
        ),
        'pages' => array('property' => 'biblio_pages'),
        'publisher' => array(
          'property' => 'biblio_publisher',
          'import_method' => 'importPublisher',
          'method' => 'formatPublisher'
        ),
        // @todo: Is it ok to have this "fake" keys, or add this as property
        // to the array?
        'school' => array(
          'property' => 'school',
          'method' => 'formatSchool',
        ),
        'series' => array(
          'property' => 'series',
          'method' => 'formatSeries',
        ),
        'secondary_title' => array(
          'property' => 'biblio_secondary_title',
          'import_method' => 'importSecondaryTitle',
        ),
        'title' => array(
          'property' => 'title',
          'method' => 'formatTitle',
        ),
        // Keys used for import.
        'tertiary_title' => array(
          'property' => 'biblio_tertiary_title',
          'import_method' => 'importTertiaryTitle',
        ),
        // @todo: Is this the Biblio URL?
        'doi_url' => array('property' => 'biblio_url', 'method' => 'formatUrl'),
        'pdf' => array('property' => 'biblio_pdf', 'method' => 'formatUrl'),
        'slides_pdf' => array('property' => 'biblio_slides_pdf', 'method' => 'formatUrl'),
        'poster_pdf' => array('property' => 'biblio_poster_pdf', 'method' => 'formatUrl'),
        'video' => array('property' => 'biblio_video', 'method' => 'formatUrl'),
        'volume' => array('property' => 'biblio_volume'),
        'year' => array('property' => 'biblio_year'),
        'supervisor' => array(
          'property' => 'biblio_supervisor',
          'import_method' => 'importSupervisor',
          'method' => 'formatSupervisor',
        ),
        'venue_name' => array('property' => 'biblio_venue', 'import_method' => 'importVenueName'),
      ),
      'type' => array(
        'article' => 'journal_article',
        'book' => 'book',
        'booklet' => 'miscellaneous',
        'conference' => 'conference_paper',
        'inbook' => 'book_chapter',
        'incollection' => 'book_chapter',
        'inproceedings' => 'conference_paper',
        'manual' => 'miscellaneous',
        'mastersthesis' => 'thesis',
        'misc' => 'miscellaneous',
        'phdthesis' => 'thesis',
        'proceedings' => 'conference_proceedings',
        'techreport' => 'report',
        'unpublished' => 'unpublished',
      ),
    );

    // Assign default method to format entry.
    foreach ($return['field'] as $key => $value) {
      $return['field'][$key] += array(
        'method' => 'formatGeneric',
        'import_method' => 'importGeneric',
        'use_key' => TRUE,
      );
    }

    return $return;
  }


  /**
   * This is a translation table for best-effort conversion from Unicode to
   * LaTeX/BibTeX entities. It contains a comprehensive list of substitution
   * strings for Unicode characters, which can be used with the 'T1' font
   * encoding.
   *
   * Uses commands from the 'textcomp' package. Characters that can't be matched
   * are converted to ASCII equivalents.
   *
   * Adopted from 'transtab' by Markus Kuhn (transtab.utf v1.8 2000-10-12
   * 11:01:28+01 mgk25 Exp);
   *
   * see <http://www.cl.cam.ac.uk/~mgk25/unicode.html> for more info about
   * Unicode and transtab.
   */
  private function getTranstab() {

    return array(
      "(?<!\\\\)#" => '$\\#$',
      "(?<!\\\\)%" => "\\%",
      "(?<!\\\\)&" => "\\&",
      "(?<!\\\\)'" => "{\\textquoteright}",
      "(?<!\\\\)`" => "{\\textquoteleft}",
      " " => "~",
      "¡" => "{\\textexclamdown}",
      "¢" => "{\\textcent}",
      "£" => "{\\textsterling}",
      "¥" => "{\\textyen}",
      "¦" => "{\\textbrokenbar}",
      "§" => "{\\textsection}",
      "¨" => "{\\textasciidieresis}",
      "©" => "{\\textcopyright}",
      "ª" => "{\\textordfeminine}",
      "«" => "{\\guillemotleft}",
      "¬" => "{\\textlnot}",
      "­" => "-",
      "®" => "{\\textregistered}",
      "¯" => "{\\textasciimacron}",
      "°" => "{\\textdegree}",
      "±" => "{\\textpm}",
      "²" => "{\\texttwosuperior}",
      "³" => "{\\textthreesuperior}",
      "´" => "{\\textasciiacute}",
      "µ" => "{\\textmu}",
      "¶" => "{\\textparagraph}",
      "·" => "{\\textperiodcentered}",
      "¸" => "{\\c\\ }",
      "¹" => "{\\textonesuperior}",
      "º" => "{\\textordmasculine}",
      "»" => "{\\guillemotright}",
      "¼" => "{\\textonequarter}",
      "½" => "{\\textonehalf}",
      "¾" => "{\\textthreequarters}",
      "¿" => "{\\textquestiondown}",
      "À" => "{\\`A}",
      "Á" => "{\\'A}",
      "Â" => "{\\^A}",
      "Ã" => "{\\~A}",
      "Ä" => "{\\\"A}",
      "Å" => "{\\r A}",
      "Æ" => "{\\AE}",
      "Ç" => "{\\c C}",
      "È" => "{\\`E}",
      "É" => "{\\'E}",
      "Ê" => "{\\^E}",
      "Ë" => "{\\\"E}",
      "Ì" => "{\\`I}",
      "Í" => "{\\'I}",
      "Î" => "{\\^I}",
      "Ï" => "{\\\"I}",
      "Ð" => "{\\DH}",
      "Ñ" => "{\\~N}",
      "Ò" => "{\\`O}",
      "Ó" => "{\\'O}",
      "Ô" => "{\\^O}",
      "Õ" => "{\\~O}",
      "Ö" => "{\\\"O}",
      "×" => "{\\texttimes}",
      "Ø" => "{\\O}",
      "Ù" => "{\\`U}",
      "Ú" => "{\\'U}",
      "Û" => "{\\^U}",
      "Ü" => "{\\\"U}",
      "Ý" => "{\\'Y}",
      "Þ" => "{\\TH}",
      "ß" => "{\\ss}",
      "à" => "{\\`a}",
      "á" => "{\\'a}",
      "â" => "{\\^a}",
      "ã" => "{\\~a}",
      "ä" => "{\\\"a}",
      "å" => "{\\r a}",
      "æ" => "{\\ae}",
      "ç" => "{\\c c}",
      "è" => "{\\`e}",
      "é" => "{\\'e}",
      "ê" => "{\\^e}",
      "ë" => "{\\\"e}",
      "ì" => "{\\`\\i}",
      "í" => "{\\'\\i}",
      "î" => "{\\^\\i}",
      "ï" => "{\\\"\\i}",
      "ð" => "{\\dh}",
      "ñ" => "{\\~n}",
      "ò" => "{\\`o}",
      "ó" => "{\\'o}",
      "ô" => "{\\^o}",
      "õ" => "{\\~o}",
      "ö" => "{\\\"o}",
      "÷" => "{\\textdiv}",
      "ø" => "{\\o}",
      "ù" => "{\\`u}",
      "ú" => "{\\'u}",
      "û" => "{\\^u}",
      "ü" => "{\\\"u}",
      "ý" => "{\\'y}",
      "þ" => "{\\th}",
      "ÿ" => "{\\\"y}",
      "Ā" => "A",
      "ā" => "{\\={a}}",
      "Ă" => "{\\u A}",
      "ă" => "{\\u a}",
      "Ą" => "{\\k A}",
      "ą" => "{\\k a}",
      "Ć" => "{\\'C}",
      "ć" => "{\\'c}",
      "Ĉ" => "Ch",
      "ĉ" => "ch",
      "Ċ" => "C",
      "ċ" => "c",
      "Č" => "{\\v C}",
      "č" => "{\\v c}",
      "Ď" => "{\\v D}",
      "ď" => "{\\v d}",
      "Đ" => "{\\DJ}",
      "đ" => "{\\dj}",
      "Ē" => "E",
      "ē" => "e",
      "Ĕ" => "E",
      "ĕ" => "e",
      "Ė" => "E",
      "ė" => "e",
      "Ę" => "{\\k E}",
      "ę" => "{\\k e}",
      "Ě" => "{\\v E}",
      "ě" => "{\\v e}",
      "Ĝ" => "Gh",
      "ĝ" => "gh",
      "Ğ" => "{\\u G}",
      "ğ" => "{\\u g}",
      "Ġ" => "G",
      "ġ" => "g",
      "Ģ" => "G",
      "ģ" => "g",
      "Ĥ" => "Hh",
      "ĥ" => "hh",
      "Ħ" => "H",
      "ħ" => "h",
      "Ĩ" => "I",
      "ĩ" => "i",
      "Ī" => "I",
      "ī" => "i",
      "Ĭ" => "I",
      "ĭ" => "i",
      "Į" => "I",
      "į" => "i",
      "İ" => "{\\.I}",
      "ı" => "{\\i}",
      "Ĳ" => "IJ",
      "ĳ" => "ij",
      "Ĵ" => "Jh",
      "ĵ" => "jh",
      "Ķ" => "K",
      "ķ" => "k",
      "ĸ" => "k",
      "Ĺ" => "{\\'L}",
      "ĺ" => "{\\'l}",
      "Ļ" => "L",
      "ļ" => "l",
      "Ľ" => "{\\v L}",
      "ľ" => "{\\v l}",
      "Ŀ" => "L·",
      "ŀ" => "l·",
      "Ł" => "{\\L}",
      "ł" => "{\\l}",
      "Ń" => "{\\'N}",
      "ń" => "{\\'n}",
      "Ņ" => "N",
      "ņ" => "n",
      "Ň" => "{\\v N}",
      "ň" => "{\\v n}",
      "ŉ" => "'n",
      "Ŋ" => "{\\NG}",
      "ŋ" => "{\\ng}",
      "Ō" => "O",
      "ō" => "o",
      "Ŏ" => "O",
      "ŏ" => "o",
      "Ő" => "{\\H O}",
      "ő" => "{\\H o}",
      "Œ" => "{\\OE}",
      "œ" => "{\\oe}",
      "Ŕ" => "{\\'R}",
      "ŕ" => "{\\'r}",
      "Ŗ" => "R",
      "ŗ" => "r",
      "Ř" => "{\\v R}",
      "ř" => "{\\v r}",
      "Ś" => "{\\'S}",
      "ś" => "{\\'s}",
      "Ŝ" => "Sh",
      "ŝ" => "sh",
      "Ş" => "{\\c S}",
      "ş" => "{\\c s}",
      "Š" => "{\\v S}",
      "š" => "{\\v s}",
      "Ţ" => "{\\c T}",
      "ţ" => "{\\c t}",
      "Ť" => "{\\v T}",
      "ť" => "{\\v t}",
      "Ŧ" => "T",
      "ŧ" => "t",
      "Ũ" => "U",
      "ũ" => "u",
      "Ū" => "U",
      "ū" => "u",
      "Ŭ" => "U",
      "ŭ" => "u",
      "Ů" => "{\\r U}",
      "ů" => "{\\r u}",
      "Ű" => "{\\H U}",
      "ű" => "{\\H u}",
      "Ų" => "U",
      "ų" => "u",
      "Ŵ" => "W",
      "ŵ" => "w",
      "Ŷ" => "Y",
      "ŷ" => "y",
      "Ÿ" => "{\\\"Y}",
      "Ź" => "{\\'Z}",
      "ź" => "{\\'z}",
      "Ż" => "{\\.Z}",
      "ż" => "{\\.z}",
      "Ž" => "{\\v Z}",
      "ž" => "{\\v z}",
      "ſ" => "s",
      "ƒ" => "{\\textflorin}",
      "Ș" => "S",
      "ș" => "s",
      "Ț" => "T",
      "ț" => "t",
      "ʹ" => "'",
      "ʻ" => "'",
      "ʼ" => "'",
      "ʽ" => "'",
      "ˆ" => "{\\textasciicircum}",
      "ˈ" => "'",
      "ˉ" => "-",
      "ˌ" => ",",
      "ː" => ":",
      "˚" => "o",
      "˜" => "\\~{}",
      "˝" => "{\\textacutedbl}",
      "ʹ" => "'",
      "͵" => ",",
      ";" => ";",
      "Ḃ" => "B",
      "ḃ" => "b",
      "Ḋ" => "D",
      "ḋ" => "d",
      "Ḟ" => "F",
      "ḟ" => "f",
      "Ṁ" => "M",
      "ṁ" => "m",
      "Ṗ" => "P",
      "ṗ" => "p",
      "Ṡ" => "S",
      "ṡ" => "s",
      "Ṫ" => "T",
      "ṫ" => "t",
      "Ẁ" => "W",
      "ẁ" => "w",
      "Ẃ" => "W",
      "ẃ" => "w",
      "Ẅ" => "W",
      "ẅ" => "w",
      "Ỳ" => "Y",
      "ỳ" => "y",
      " " => " ",
      " " => "  ",
      " " => " ",
      " " => "  ",
      " " => " ",
      " " => " ",
      " " => " ",
      " " => " ",
      " " => " ",
      " " => " ",
      "‐" => "-",
      "‑" => "-",
      "‒" => "-",
      "–" => "{\\textendash}",
      "—" => "{\\textemdash}",
      "―" => "--",
      "‖" => "{\\textbardbl}",
      "‗" => "{\\textunderscore}",
      "‘" => "{\\textquoteleft}",
      "’" => "{\\textquoteright}",
      "‚" => "{\\quotesinglbase}",
      "‛" => "'",
      "“" => "{\\textquotedblleft}",
      "”" => "{\\textquotedblright}",
      "„" => "{\\quotedblbase}",
      "‟" => "\"",
      "†" => "{\\textdagger}",
      "‡" => "{\\textdaggerdbl}",
      "•" => "{\\textbullet}",
      "‣" => ">",
      "․" => ".",
      "‥" => "..",
      "…" => "{\\textellipsis}",
      "‧" => "-",
      " " => " ",
      "‰" => "{\\textperthousand}",
      "′" => "'",
      "″" => "\"",
      "‴" => "'''",
      "‵" => "`",
      "‶" => "``",
      "‷" => "```",
      "‹" => "{\\guilsinglleft}",
      "›" => "{\\guilsinglright}",
      "‼" => "!!",
      "‾" => "-",
      "⁃" => "-",
      "⁄" => "{\\textfractionsolidus}",
      "⁈" => "?!",
      "⁉" => "!?",
      "⁊" => "7",
      "⁰" => '$^{0}$',
      "⁴" => '$^{4}$',
      "⁵" => '$^{5}$',
      "⁶" => '$^{6}$',
      "⁷" => '$^{7}$',
      "⁸" => '$^{8}$',
      "⁹" => '$^{9}$',
      "⁺" => '$^{+}$',
      "⁻" => '$^{-}$',
      "⁼" => '$^{=}$',
      "⁽" => '$^{(}$',
      "⁾" => '$^{)}$',
      "ⁿ" => '$^{n}$',
      "₀" => '$_{0}$',
      "₁" => '$_{1}$',
      "₂" => '$_{2}$',
      "₃" => '$_{3}$',
      "₄" => '$_{4}$',
      "₅" => '$_{5}$',
      "₆" => '$_{6}$',
      "₇" => '$_{7}$',
      "₈" => '$_{8}$',
      "₉" => '$_{9}$',
      "₊" => '$_{+}$',
      "₋" => '$_{-}$',
      "₌" => '$_{=}$',
      "₍" => '$_{(}$',
      "₎" => '$_{)}$',
      "€" => "{\\texteuro}",
      "℀" => "a/c",
      "℁" => "a/s",
      "℃" => "{\\textcelsius}",
      "℅" => "c/o",
      "℆" => "c/u",
      "℉" => "F",
      "ℓ" => "l",
      "№" => "{\\textnumero}",
      "℗" => "{\\textcircledP}",
      "℠" => "{\\textservicemark}",
      "℡" => "TEL",
      "™" => "{\\texttrademark}",
      "Ω" => "{\\textohm}",
      "K" => "K",
      "Å" => "A",
      "℮" => "{\\textestimated}",
      "⅓" => " 1/3",
      "⅔" => " 2/3",
      "⅕" => " 1/5",
      "⅖" => " 2/5",
      "⅗" => " 3/5",
      "⅘" => " 4/5",
      "⅙" => " 1/6",
      "⅚" => " 5/6",
      "⅛" => " 1/8",
      "⅜" => " 3/8",
      "⅝" => " 5/8",
      "⅞" => " 7/8",
      "⅟" => " 1/",
      "Ⅰ" => "I",
      "Ⅱ" => "II",
      "Ⅲ" => "III",
      "Ⅳ" => "IV",
      "Ⅴ" => "V",
      "Ⅵ" => "VI",
      "Ⅶ" => "VII",
      "Ⅷ" => "VIII",
      "Ⅸ" => "IX",
      "Ⅹ" => "X",
      "Ⅺ" => "XI",
      "Ⅻ" => "XII",
      "Ⅼ" => "L",
      "Ⅽ" => "C",
      "Ⅾ" => "D",
      "Ⅿ" => "M",
      "ⅰ" => "i",
      "ⅱ" => "ii",
      "ⅲ" => "iii",
      "ⅳ" => "iv",
      "ⅴ" => "v",
      "ⅵ" => "vi",
      "ⅶ" => "vii",
      "ⅷ" => "viii",
      "ⅸ" => "ix",
      "ⅹ" => "x",
      "ⅺ" => "xi",
      "ⅻ" => "xii",
      "ⅼ" => "l",
      "ⅽ" => "c",
      "ⅾ" => "d",
      "ⅿ" => "m",
      "←" => "{\\textleftarrow}",
      "↑" => "{\\textuparrow}",
      "→" => "{\\textrightarrow}",
      "↓" => "{\\textdownarrow}",
      "↔" => "<->",
      "⇐" => "<=",
      "⇒" => "=>",
      "⇔" => "<=>",
      "−" => "-",
      "∕" => "/",
      "∖" => "\\",
      "∗" => "*",
      "∘" => "o",
      "∙" => ".",
      "∞" => '$\\infty$',
      "∣" => "|",
      "∥" => "||",
      "∶" => ":",
      "∼" => "\\~{}",
      "≠" => "/=",
      "≡" => "=",
      "≤" => "<=",
      "≥" => ">=",
      "≪" => "<<",
      "≫" => ">>",
      "⊕" => "(+)",
      "⊖" => "(-)",
      "⊗" => "(x)",
      "⊘" => "(/)",
      "⊢" => "|-",
      "⊣" => "-|",
      "⊦" => "|-",
      "⊧" => "|=",
      "⊨" => "|=",
      "⊩" => "||-",
      "⋅" => ".",
      "⋆" => "*",
      "⋕" => '$\\#$',
      "⋘" => "<<<",
      "⋙" => ">>>",
      "⋯" => "...",
      "〈" => "{\\textlangle}",
      "〉" => "{\\textrangle}",
      "␀" => "NUL",
      "␁" => "SOH",
      "␂" => "STX",
      "␃" => "ETX",
      "␄" => "EOT",
      "␅" => "ENQ",
      "␆" => "ACK",
      "␇" => "BEL",
      "␈" => "BS",
      "␉" => "HT",
      "␊" => "LF",
      "␋" => "VT",
      "␌" => "FF",
      "␍" => "CR",
      "␎" => "SO",
      "␏" => "SI",
      "␐" => "DLE",
      "␑" => "DC1",
      "␒" => "DC2",
      "␓" => "DC3",
      "␔" => "DC4",
      "␕" => "NAK",
      "␖" => "SYN",
      "␗" => "ETB",
      "␘" => "CAN",
      "␙" => "EM",
      "␚" => "SUB",
      "␛" => "ESC",
      "␜" => "FS",
      "␝" => "GS",
      "␞" => "RS",
      "␟" => "US",
      "␠" => "SP",
      "␡" => "DEL",
      "␣" => "{\\textvisiblespace}",
      "␤" => "NL",
      "␥" => "///",
      "␦" => "?",
      "①" => "(1)",
      "②" => "(2)",
      "③" => "(3)",
      "④" => "(4)",
      "⑤" => "(5)",
      "⑥" => "(6)",
      "⑦" => "(7)",
      "⑧" => "(8)",
      "⑨" => "(9)",
      "⑩" => "(10)",
      "⑪" => "(11)",
      "⑫" => "(12)",
      "⑬" => "(13)",
      "⑭" => "(14)",
      "⑮" => "(15)",
      "⑯" => "(16)",
      "⑰" => "(17)",
      "⑱" => "(18)",
      "⑲" => "(19)",
      "⑳" => "(20)",
      "⑴" => "(1)",
      "⑵" => "(2)",
      "⑶" => "(3)",
      "⑷" => "(4)",
      "⑸" => "(5)",
      "⑹" => "(6)",
      "⑺" => "(7)",
      "⑻" => "(8)",
      "⑼" => "(9)",
      "⑽" => "(10)",
      "⑾" => "(11)",
      "⑿" => "(12)",
      "⒀" => "(13)",
      "⒁" => "(14)",
      "⒂" => "(15)",
      "⒃" => "(16)",
      "⒄" => "(17)",
      "⒅" => "(18)",
      "⒆" => "(19)",
      "⒇" => "(20)",
      "⒈" => "1.",
      "⒉" => "2.",
      "⒊" => "3.",
      "⒋" => "4.",
      "⒌" => "5.",
      "⒍" => "6.",
      "⒎" => "7.",
      "⒏" => "8.",
      "⒐" => "9.",
      "⒑" => "10.",
      "⒒" => "11.",
      "⒓" => "12.",
      "⒔" => "13.",
      "⒕" => "14.",
      "⒖" => "15.",
      "⒗" => "16.",
      "⒘" => "17.",
      "⒙" => "18.",
      "⒚" => "19.",
      "⒛" => "20.",
      "⒜" => "(a)",
      "⒝" => "(b)",
      "⒞" => "(c)",
      "⒟" => "(d)",
      "⒠" => "(e)",
      "⒡" => "(f)",
      "⒢" => "(g)",
      "⒣" => "(h)",
      "⒤" => "(i)",
      "⒥" => "(j)",
      "⒦" => "(k)",
      "⒧" => "(l)",
      "⒨" => "(m)",
      "⒩" => "(n)",
      "⒪" => "(o)",
      "⒫" => "(p)",
      "⒬" => "(q)",
      "⒭" => "(r)",
      "⒮" => "(s)",
      "⒯" => "(t)",
      "⒰" => "(u)",
      "⒱" => "(v)",
      "⒲" => "(w)",
      "⒳" => "(x)",
      "⒴" => "(y)",
      "⒵" => "(z)",
      "Ⓐ" => "(A)",
      "Ⓑ" => "(B)",
      "Ⓒ" => "(C)",
      "Ⓓ" => "(D)",
      "Ⓔ" => "(E)",
      "Ⓕ" => "(F)",
      "Ⓖ" => "(G)",
      "Ⓗ" => "(H)",
      "Ⓘ" => "(I)",
      "Ⓙ" => "(J)",
      "Ⓚ" => "(K)",
      "Ⓛ" => "(L)",
      "Ⓜ" => "(M)",
      "Ⓝ" => "(N)",
      "Ⓞ" => "(O)",
      "Ⓟ" => "(P)",
      "Ⓠ" => "(Q)",
      "Ⓡ" => "(R)",
      "Ⓢ" => "(S)",
      "Ⓣ" => "(T)",
      "Ⓤ" => "(U)",
      "Ⓥ" => "(V)",
      "Ⓦ" => "(W)",
      "Ⓧ" => "(X)",
      "Ⓨ" => "(Y)",
      "Ⓩ" => "(Z)",
      "ⓐ" => "(a)",
      "ⓑ" => "(b)",
      "ⓒ" => "(c)",
      "ⓓ" => "(d)",
      "ⓔ" => "(e)",
      "ⓕ" => "(f)",
      "ⓖ" => "(g)",
      "ⓗ" => "(h)",
      "ⓘ" => "(i)",
      "ⓙ" => "(j)",
      "ⓚ" => "(k)",
      "ⓛ" => "(l)",
      "ⓜ" => "(m)",
      "ⓝ" => "(n)",
      "ⓞ" => "(o)",
      "ⓟ" => "(p)",
      "ⓠ" => "(q)",
      "ⓡ" => "(r)",
      "ⓢ" => "(s)",
      "ⓣ" => "(t)",
      "ⓤ" => "(u)",
      "ⓥ" => "(v)",
      "ⓦ" => "(w)",
      "ⓧ" => "(x)",
      "ⓨ" => "(y)",
      "ⓩ" => "(z)",
      "⓪" => "(0)",
      "─" => "-",
      "━" => "=",
      "│" => "|",
      "┃" => "|",
      "┄" => "-",
      "┅" => "=",
      "┆" => "|",
      "┇" => "|",
      "┈" => "-",
      "┉" => "=",
      "┊" => "|",
      "┋" => "|",
      "┌" => "+",
      "┍" => "+",
      "┎" => "+",
      "┏" => "+",
      "┐" => "+",
      "┑" => "+",
      "┒" => "+",
      "┓" => "+",
      "└" => "+",
      "┕" => "+",
      "┖" => "+",
      "┗" => "+",
      "┘" => "+",
      "┙" => "+",
      "┚" => "+",
      "┛" => "+",
      "├" => "+",
      "┝" => "+",
      "┞" => "+",
      "┟" => "+",
      "┠" => "+",
      "┡" => "+",
      "┢" => "+",
      "┣" => "+",
      "┤" => "+",
      "┥" => "+",
      "┦" => "+",
      "┧" => "+",
      "┨" => "+",
      "┩" => "+",
      "┪" => "+",
      "┫" => "+",
      "┬" => "+",
      "┭" => "+",
      "┮" => "+",
      "┯" => "+",
      "┰" => "+",
      "┱" => "+",
      "┲" => "+",
      "┳" => "+",
      "┴" => "+",
      "┵" => "+",
      "┶" => "+",
      "┷" => "+",
      "┸" => "+",
      "┹" => "+",
      "┺" => "+",
      "┻" => "+",
      "┼" => "+",
      "┽" => "+",
      "┾" => "+",
      "┿" => "+",
      "╀" => "+",
      "╁" => "+",
      "╂" => "+",
      "╃" => "+",
      "╄" => "+",
      "╅" => "+",
      "╆" => "+",
      "╇" => "+",
      "╈" => "+",
      "╉" => "+",
      "╊" => "+",
      "╋" => "+",
      "╌" => "-",
      "╍" => "=",
      "╎" => "|",
      "╏" => "|",
      "═" => "=",
      "║" => "|",
      "╒" => "+",
      "╓" => "+",
      "╔" => "+",
      "╕" => "+",
      "╖" => "+",
      "╗" => "+",
      "╘" => "+",
      "╙" => "+",
      "╚" => "+",
      "╛" => "+",
      "╜" => "+",
      "╝" => "+",
      "╞" => "+",
      "╟" => "+",
      "╠" => "+",
      "╡" => "+",
      "╢" => "+",
      "╣" => "+",
      "╤" => "+",
      "╥" => "+",
      "╦" => "+",
      "╧" => "+",
      "╨" => "+",
      "╩" => "+",
      "╪" => "+",
      "╫" => "+",
      "╬" => "+",
      "╭" => "+",
      "╮" => "+",
      "╯" => "+",
      "╰" => "+",
      "╱" => "/",
      "╲" => "\\",
      "╳" => "X",
      "╼" => "-",
      "╽" => "|",
      "╾" => "-",
      "╿" => "|",
      "○" => "o",
      "◦" => "{\\textopenbullet}",
      "★" => "*",
      "☆" => "*",
      "☒" => "X",
      "☓" => "X",
      "☹" => ":-(",
      "☺" => ":-)",
      "☻" => "(-:",
      "♭" => "b",
      "♯" => '$\\#$',
      "✁" => '$\\%<$',
      "✂" => '$\\%<$',
      "✃" => '$\\%<$',
      "✄" => '$\\%<$',
      "✌" => "V",
      "✓" => "v",
      "✔" => "V",
      "✕" => "x",
      "✖" => "x",
      "✗" => "X",
      "✘" => "X",
      "✙" => "+",
      "✚" => "+",
      "✛" => "+",
      "✜" => "+",
      "✝" => "+",
      "✞" => "+",
      "✟" => "+",
      "✠" => "+",
      "✡" => "*",
      "✢" => "+",
      "✣" => "+",
      "✤" => "+",
      "✥" => "+",
      "✦" => "+",
      "✧" => "+",
      "✩" => "*",
      "✪" => "*",
      "✫" => "*",
      "✬" => "*",
      "✭" => "*",
      "✮" => "*",
      "✯" => "*",
      "✰" => "*",
      "✱" => "*",
      "✲" => "*",
      "✳" => "*",
      "✴" => "*",
      "✵" => "*",
      "✶" => "*",
      "✷" => "*",
      "✸" => "*",
      "✹" => "*",
      "✺" => "*",
      "✻" => "*",
      "✼" => "*",
      "✽" => "*",
      "✾" => "*",
      "✿" => "*",
      "❀" => "*",
      "❁" => "*",
      "❂" => "*",
      "❃" => "*",
      "❄" => "*",
      "❅" => "*",
      "❆" => "*",
      "❇" => "*",
      "❈" => "*",
      "❉" => "*",
      "❊" => "*",
      "❋" => "*",
      "ﬀ" => "ff",
      "ﬁ" => "fi",
      "ﬂ" => "fl",
      "ﬃ" => "ffi",
      "ﬄ" => "ffl",
      "ﬅ" => "st",
      "ﬆ" => "st"
    );
  }
}
