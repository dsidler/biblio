<?php

/**
 * Implements hook_biblio_fields_info().
 */
function biblio_biblio_fields_info() {
  // Abstract.
  $items['biblio_abstract'] = array(
    'field' => array(
      'cardinality' => '1',
      'entity_types' => array(),
      'field_name' => 'biblio_abstract',
      'module' => 'text',
      'type' => 'text_long',
    ),
    'instance' => array(
      'label' => 'Publication abstract',
      'required' => TRUE,
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => '5',
        ),
        'type' => 'text_textarea',
        'weight' => '4',
      ),
    ),
  );

  // Citekey.
  $items['biblio_citekey'] = array(
    'field' => array(
      'cardinality' => '1',
      'entity_types' => array(),
      'field_name' => 'biblio_citekey',
      'module' => 'text',
      'type' => 'text_long',
    ),
    'instance' => array(
      'label' => 'Publication citation',
      'description' => 'Publication citation.',
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => '5',
        ),
        'type' => 'text_textarea',
        'weight' => '-1',
      ),
    ),
	 'bundles_info' => array(),
  );

  // Image.
  $items['biblio_image'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_image',
      'locked' => '0',
      'module' => 'image',
      'settings' => array(
        'default_image' => 0,
        'uri_scheme' => 'public',
      ),
      'translatable' => '0',
      'type' => 'image',
    ),
    'instance' => array(
      'label' => 'The publication image',
      'description' => 'Image for the biblio',
      'settings' => array(
        'alt_field' => 0,
        'default_image' => 0,
        'file_directory' => '',
        'file_extensions' => 'png gif jpg jpeg',
        'max_filesize' => '',
        'max_resolution' => '',
        'min_resolution' => '',
        'title_field' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'image',
        'settings' => array(
          'preview_image_style' => 'thumbnail',
          'progress_indicator' => 'throbber',
        ),
        'type' => 'image_image',
        'weight' => '-2',
      ),
    ),
    'bundles_info' => array(),
  );

  // PDF file.
  $items['biblio_pdf'] = array(
    'field' => array(
      'field_name' => 'biblio_pdf',
      'type' => 'file',
      'cardinality' => 1,
      'locked' => '0',
      'translatable' => '0',
      'settings' => array(
        'uri_scheme' => 'public',
      ),
    ),
    'instance' => array(
      'label' => 'The publication PDF',
      'description' => 'PDF for the biblio',
      'settings' => array(
        'file_directory' => 'publications',
        'file_extensions' => 'pdf',
        'max_filesize' => '2MB',
        'max_resolution' => '',
        'min_resolution' => '',
        'title_field' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'type' => 'file_generic',
        'weight' => '16',
      ),
    ),
  );

  $items['biblio_slides_pdf'] = array(
    'field' => array(
      'field_name' => 'biblio_slides_pdf',
      'type' => 'file',
      'cardinality' => 1,
      'locked' => '0',
      'translatable' => '0',
      'settings' => array(
        'uri_scheme' => 'public',
      ),
    ),
    'instance' => array(
      'label' => 'Presentation Slides PDF',
      'description' => 'PDF for the presentation slides',
      'settings' => array(
        'file_directory' => 'slides',
        'file_extensions' => 'pdf',
        'max_filesize' => '4MB',
        'max_resolution' => '',
        'min_resolution' => '',
        'title_field' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'type' => 'file_generic',
        'weight' => '17',
      ),
    ),
  );

  $items['biblio_poster_pdf'] = array(
    'field' => array(
      'field_name' => 'biblio_poster_pdf',
      'type' => 'file',
      'cardinality' => 1,
      'locked' => '0',
      'translatable' => '0',
      'settings' => array(
        'uri_scheme' => 'public',
      ),
    ),
    'instance' => array(
      'label' => 'Poster PDF',
      'description' => 'PDF of the poster',
      'settings' => array(
        'file_directory' => 'posters',
        'file_extensions' => 'pdf',
        'max_filesize' => '2MB',
        'max_resolution' => '',
        'min_resolution' => '',
        'title_field' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'type' => 'file_generic',
        'weight' => '18',
      ),
    ),
  );

  $items['biblio_video'] = array(
    'description' => 'Video',
    'field' => array(
      'cardinality' => 1,
      'field_name' => 'biblio_video',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Video',
      'description' => 'URL to a video, e.g. YouTube',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '19',
      ),
    ),
   );

  $items['biblio_category'] = array(
    'field' => array(
      'field_name' => 'biblio_category',
      'type' => 'taxonomy_term_reference',
      'module' => 'taxonomy',
      'active' => 1,
      'cardinality' => FIELD_CARDINALITY_UNLIMITED,
      'settings' => array(
        'allowed_values' => array(
          array(
            'vocabulary' => 'biblio_categories',
            'parent' => 0,
          ),
        ),
      ),
    ),
    'instance' => array(
      'label' => 'Publication Category',
      'settings' => array(
        'allowed_values' => array(
          0 => array(
            'vocabulary' => 'biblio_categories',
            'parent' => 0,
          ),
        ),
      ),
      'widget' => array(
        'type' => 'options_buttons',
        'module' => 'options',
        'active' => 1,
        'weight' => '22',
      ),
    ),
  );

  // Other Numbers.
  $items['biblio_other_number'] = array(
    'field' => array(
      'cardinality' => 1,
      'field_name' => 'biblio_other_number',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'translatable' => '0',
      'type' => 'text',
    ),
    'instance' => array(
      'default_value' => NULL,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
        ),
      ),
      'label' => 'Other Numbers',
      'required' => 0,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
      ),
    ),
    // @todo: Applies to all?
    'bundles_info' => array(),
      /*'artwork' => array(),
      'audiovisual' => array(),
      'book' => array(),
      'book_chapter' => array(),
      'bill' => array(),
      'broadcast' => array(),
      'case' => array(),
      'chart' => array(),
      'classical' => array(),
      'conference_paper' => array(),
      'conference_proceedings' => array(),
      'database' => array(),
      'film' => array(),
      'government_report' => array(),
      'hearing' => array(),
      'journal' => array(),
      'journal_article' => array(),
      'legal_ruling' => array(),
      'magazine_article' => array(),
      'manuscript' => array(),
      'map' => array(),
      'miscellaneous' => array(),
      'miscellaneous_section' => array(),
      'newspaper_article' => array(),
      'patent' => array(),
      'personal' => array(),
      'presentation' => array(),
      'report' => array(),
      'software' => array(),
      'statute' => array(),
      'thesis' => array(),
      'unpublished' => array(),
      'web_article' => array(),
      'web_project_page' => array(),
      'web_service' => array(),
      'website' => array(),
    ),*/
  );

  // Publication year.
  $items['biblio_year'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_year',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'number',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'number_integer',
    ),
    'instance' => array(
      'default_value' => NULL,
      'description' => 'Year in 4 digits, for instance: 2017',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'number',
          'settings' => array(
            'prefix_suffix' => TRUE,
            'scale' => 0,
            'thousand_separator' => ' ',
          ),
          'type' => 'number_integer',
        ),
      ),
      'field_name' => 'biblio_year',
      'label' => 'Year of Publication',
      // We will enforce required only if the Publication status is set to
      // "published".
      'required' => TRUE,
      'settings' => array(
        'max' => '9999',
        'min' => '-9999',
        'prefix' => '',
        'suffix' => '',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'number',
        'settings' => array(),
        'type' => 'number',
        'weight' => '11',
      ),
    ),
  );

  // Publication month.
  $items['biblio_month'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_month',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'number',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'number_integer',
    ),
    'instance' => array(
      'default_value' => NULL,
      'description' => 'Month as a number between 1-12',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'number',
          'settings' => array(
            'prefix_suffix' => TRUE,
            'scale' => 0,
            'thousand_separator' => ' ',
          ),
          'type' => 'number_integer',
        ),
      ),
      'field_name' => 'biblio_month',
      'label' => 'Month of Publication',
      // We will enforce required only if the Publication status is set to
      // "published".
      'required' => TRUE,
      'settings' => array(
        'max' => '12',
        'min' => '1',
        'prefix' => '',
        'suffix' => '',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'number',
        'settings' => array(),
        'type' => 'number',
        'weight' => '10',
      ),
    ),
  );


  // First letter; can be used to store the character we would like to later
  // group the publications.
  $items['biblio_first_letter'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_first_letter',
      'module' => 'text',
      'settings' => array(
        'max_length' => '1',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Publication first letter',
      'description' => 'Hold the character to later the publications can be grouped by.',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '1',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
	 'bundles_info' => array(),
  );

  // Section.
  $items['biblio_section'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_section',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Section',
      'required' => FALSE,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(
      'book_chapter' => array(
        'label' => 'Chapter',
      ),
      /*'bill' => array(
        'label' => 'Code Section',
      ),
      'case' => array(
        'label' => 'Page Cited',
      ),
      'government_report' => array(),
      'journal_article' => array(
        'label' => 'Start Page',
      ),
      'legal_ruling' => array(
        'label' => 'Section Number',
      ),
      'magazine_article' => array(),
      'newspaper_article' => array(),
      'patent' => array(
        'label' => 'International Patent Number',
      ),
      'statute' => array(
        'label' => 'Sections',
      ),*/
    ),
  );

  // Issue.
  $items['biblio_issue'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_issue',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Issue Number',
      'required' => FALSE,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '8',
      ),
    ),
    'bundles_info' => array(
      'journal_article' => array(),
    ),
  );

  // Number of volumes.
  $items['biblio_number_of_volumes'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_number_of_volumes',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Number of Volumes',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(),
      /*'audiovisual' => array(
        'label' => 'Extent of Work',
      ),
      'book_chapter' => array(),
      'book' => array(),
      'case' => array(
        'label' => 'Reporter Abbreviation',
      ),
      'classical' => array(),
      'conference_proceedings' => array(),
      'hearing' => array(),
      'legal_ruling' => array(
        'label' => 'Session Number',
      ),
      'magazine_article' => array(
        'label' => 'Frequency',
      ),
      'manuscript' => array(
        'label' => 'Manuscript Number',
      ),
      'newspaper_article' => array(
        'label' => 'Frequency',
      ),
      'personal' => array(
        'label' => 'Communication Number',
      ),
      'statute' => array(
        'label' => 'Statute Number',
      ),
    ),*/
  );

  // Number.
  $items['biblio_number'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_number',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Series Volume',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '8',
      ),
    ),
    'bundles_info' => array(),
      /*'audiovisual' => array(),
      'book' => array(),
      'book_chapter' => array(),
      'bill' => array(
        'label' => 'Bill Number',
      ),
      'chart' => array(
        'label' => 'Number',
      ),
      'classical' => array(),
      'film' => array(
        'label' => 'Running Time',
      ),
      'hearing' => array(
        'label' => 'Document Number',
      ),
      'legal_ruling' => array(
        'label' => 'Start Page',
      ),
      'magazine_article' => array(
        'label' => 'Issue Number',
      ),
      'manuscript' => array(
        'label' => 'Folio Number',
      ),
      'newspaper_article' => array(
        'label' => 'Start Page',
      ),
      'patent' => array(
        'label' => 'Application Number',
      ),
      'personal' => array(
        'label' => 'Folio Number',
      ),
      'report' => array(
        'label' => 'Document Number',
      ),
      'statute' => array(
        'label' => 'Public Law Number',
      ),
      'unpublished' => array(
        'label' => 'Number',
      ),
      'web_article' => array(
        'label' => 'Access Date',
      ),
    ),*/
  );

  // Pages.
  $items['biblio_pages'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_pages',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Publication pages',
      'description' => 'First & last page numbers of the piece. e.g. 23-25',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '9',
      ),
    ),
    'bundles_info' => array(
      'book' => array(
        'label' => 'Number of Pages',
      ),
      'journal_article' => array(
        'label' => 'Pagination',
      ),
    ),
  );

  // Date.
  /*$items['biblio_date'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_date',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Date Published',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(
      'newspaper_article' => array(
        'label' => 'Issue Date',
      ),
    ),
  );*/

  // Reprint edition.
  /*$items['biblio_reprint_edition'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_reprint_edition',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Reprint Edition',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(
      'book' => array(),
      'book_chapter' => array(),
      'classical' => array(),
      'journal_article' => array(),
      'magazine_article' => array(),
      'newspaper_article' => array(),
    ),
  );*/

  // Call number.
  /*$items['biblio_call_number'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_call_number',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Call number',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    // @todo: Applies to all?
    'bundles_info' => array(
      'artwork' => array(),
      'audiovisual' => array(),
      'book' => array(),
      'book_chapter' => array(),
      'bill' => array(),
      'broadcast' => array(),
      'chart' => array(),
      'classical' => array(),
      'conference_paper' => array(),
      'conference_proceedings' => array(),
      'database' => array(),
      'film' => array(),
      'government_report' => array(),
      'hearing' => array(),
      'journal' => array(),
      'journal_article' => array(),
      'legal_ruling' => array(),
      'magazine_article' => array(),
      'manuscript' => array(),
      'map' => array(),
      'miscellaneous' => array(),
      'miscellaneous_section' => array(),
      'newspaper_article' => array(),
      'patent' => array(),
      'personal' => array(),
      'presentation' => array(),
      'report' => array(),
      'software' => array(),
      'statute' => array(),
      'thesis' => array(),
      'unpublished' => array(),
      'web_article' => array(),
      'web_project_page' => array(),
      'web_service' => array(),
      'website' => array(),
    ),
  );*/

  // ISBN number.
  $items['biblio_isbn'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_isbn',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'ISBN Number',
      'description' => 'International Standard Book Number',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    // @todo: Applies to all?
    'bundles_info' => array(
      /*'artwork' => array(),
      'audiovisual' => array(),*/
      'book' => array(),
      'book_chapter' => array(),
      /*'bill' => array(),
      'broadcast' => array(),
      'case' => array(),
      'chart' => array(),
      'classical' => array(),
      'conference_paper' => array(),
      'conference_proceedings' => array(),
      'database' => array(),
      'film' => array(),
      'government_report' => array(),
      'hearing' => array(),
      'journal' => array(),
      'journal_article' => array(),
      'legal_ruling' => array(),
      'magazine_article' => array(),
      'manuscript' => array(),
      'map' => array(),
      'miscellaneous' => array(),
      'miscellaneous_section' => array(),
      'newspaper_article' => array(),
      'patent' => array(),
      'personal' => array(),
      'presentation' => array(),
      'report' => array(),
      'software' => array(),
      'statute' => array(),
      'thesis' => array(),
      'unpublished' => array(),
      'web_article' => array(),
      'web_project_page' => array(),
      'web_service' => array(),
      'website' => array(),*/
    ),
  );

  // ISSN number.
  $items['biblio_issn'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_issn',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'ISSN Number',
      'description' => 'International Standard Serial Number',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(),
      /*'journal_article' => array(
        'label' => 'ISSN',
      ),
      'legal_ruling' => array(
        'label' => 'Document Number',
      ),
      'magazine_article' => array(
        'label' => 'ISSN',
      ),
      'map' => array(
        'label' => 'ISSN',
      ),
      'miscellaneous' => array(),
      'miscellaneous_section' => array(),
      'newspaper_article' => array(
        'label' => 'ISSN',
      ),
      'patent' => array(
        'label' => 'Patent Number',
      ),
      'report' => array(
        'label' => 'Report Number',
      ),
      'software' => array(
        'label' => 'ISSN',
      ),
      'web_article' => array(
        'label' => 'ISSN',
      ),
    ),*/
  );

  // Accession number
  $items['biblio_accession_number'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_accession_number',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Accession number',
      'description' => '',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    // @todo: Applies to all?
    'bundles_info' => array(),
      /*'artwork' => array(),
      'audiovisual' => array(),*/
      /*'book' => array(),
      'book_chapter' => array(),*/
      /*'bill' => array(),
      'broadcast' => array(),
      'case' => array(),
      'chart' => array(),
      'classical' => array(),
      'conference_paper' => array(),
      'conference_proceedings' => array(),
      'database' => array(),
      'film' => array(),
      'government_report' => array(),
      'hearing' => array(),
      'journal' => array(),
      'journal_article' => array(),
      'legal_ruling' => array(),
      'magazine_article' => array(),
      'manuscript' => array(),
      'manuscript' => array(),
      'map' => array(),
      'miscellaneous' => array(),
      'miscellaneous_section' => array(),
      'newspaper_article' => array(),
      'patent' => array(),
      'personal' => array(),
      'presentation' => array(),
      'report' => array(),
      'software' => array(),
      'statute' => array(),
      'thesis' => array(),
      'unpublished' => array(),
      'web_article' => array(),
      'web_project_page' => array(),
      'web_service' => array(),
      'website' => array(),*/
    //),
  );

  // Keywords.
  $items['biblio_keywords'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_keywords',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Keywords',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '24',
      ),
    ),
  );

  // Notes.
  $items['biblio_notes'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_notes',
      'module' => 'text',
      'type' => 'text_long',
    ),
    'instance' => array(
      'label' => 'Notes',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textarea',
        'weight' => '-3',
      ),
    ),
	 'bundles_info' => array(),
  );

  // Research notes.
  $items['biblio_research_notes'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_research_notes',
      'module' => 'text',
      'type' => 'text_long',
    ),
    'instance' => array(
      'label' => 'Research Notes',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textarea',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(),
  );

  // Translated title.
  $items['biblio_translated_title'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_translated_title',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Translated Title',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(),
  );

  // Summary char; can be used to store the character we would like to later
  // group the publications.
  $items['biblio_summary_char'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_summary_char',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Publication summary character',
      'description' => 'Hold the character to later the publications can be grouped by.',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(),
  );

  // Contributor fields.
  $items['contributor_field_collection'] = array(
    'field' => array(
      'cardinality' => FIELD_CARDINALITY_UNLIMITED,
      'field_name' => 'contributor_field_collection',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'field_collection',
      'settings' => array(
        'hide_blank_items' => 1,
        'path' => '',
      ),
      'translatable' => '0',
      'type' => 'field_collection',
    ),
    'instance' => array(
      'label' => 'Contributors',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'field_collection',
        'settings' => array(),
        'type' => 'field_collection_embed',
        'weight' => '12',
      ),
    ),
  );

  // Reference to contributor role.
  $items['biblio_contributor_role'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_contributor_role',
      'module' => 'entityreference',
      'settings' => array(
        'handler' => 'base',
        'handler_settings' => array(
          'sort' => array(
            'type' => 'none',
          ),
          'target_bundles' => array(
            'biblio_roles' => 'biblio_roles',
          ),
        ),
        'target_type' => 'taxonomy_term',
      ),
      'translatable' => '0',
      'type' => 'entityreference',
    ),
    'instance' => array(
      'label' => 'Contributor role',
      'required' => TRUE,
      'widget' => array(
        'active' => 1,
        'module' => 'entityreference',
        'settings' => array(
          'match_operator' => 'CONTAINS',
          'path' => '',
          'size' => '60',
        ),
        'type' => 'options_select',
        'weight' => '2',
      ),
    ),
  );

  // Reference to a single contributor.
  $items['biblio_contributor'] = array(
    'field' => array(
      'active' => '1',
      'cardinality' => 1,
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'biblio_contributor',
      'module' => 'entityreference',
      'settings' => array(
        'handler' => 'base',
        'handler_settings' => array(
          'sort' => array(
            'type' => 'none',
          ),
          'target_bundles' => array(),
        ),
        'target_type' => 'biblio_contributor',
      ),
      'translatable' => '0',
      'type' => 'entityreference',
    ),
    'instance' => array(
      'label' => 'Contributor reference',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'inline_entity_form',
        'settings' => array(
          'type_settings' => array(
            'allow_existing' => TRUE,
            'match_operator' => 'CONTAINS',
          ),
        ),
        'type' => 'inline_entity_form',
        'weight' => '1',
      ),
    ),
  );

  // Short title.
  $items['biblio_short_title'] = array(
    'description' => 'Short title.',
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_short_title',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Short Title',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(
      /*'artwork' => array(),
      'audiovisual' => array(),*/
      'book' => array(),
      'book_chapter' => array(),
      /*'bill' => array(),
      'case' => array(
        'label' => 'Abbreviated Case Name',
      ),
      'classical' => array(),
      'conference_proceedings' => array(),
      'film' => array(),
      'hearing' => array(),
      'journal_article' => array(),
      'magazine_article' => array(),
      'manuscript' => array(),
      'map' => array(),
      'newspaper_article' => array(),
      'patent' => array(),
      'personal' => array(),
      'report' => array(),
      'software' => array(),
      'statute' => array(),
      'thesis' => array(),
      'unpublished' => array(),
      'web_article' => array(),*/
    )
  );

  // Short title.
  $items['biblio_alternate_title'] = array(
    'description' => 'Alternate Title',
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_alternate_title',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Alternate Title',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(),
      /*'artwork' => array(),
      'audiovisual' => array(),
      'book' => array(
        'label' => 'Abbreviation',
      ),
      'book_chapter' => array(
        'label' => 'Abbreviation',
      ),
      'classical' => array(),
      'film' => array(),
      'hearing' => array(),
      'journal_article' => array(),
      'legal_ruling' => array(
        'label' => 'Abbreviation',
      ),
      'magazine_article' => array(
        'label' => 'Alternate Magazine',
      ),
      'manuscript' => array(
        'label' => 'Abbreviation',
      ),
      'map' => array(),
      'personal' => array(
        'label' => 'Abbreviation',
      ),
      'report' => array(),
      'software' => array(),
      'statute' => array(
        'label' => 'Abbreviation',
      ),
      'unpublished' => array(
        'label' => 'Abbreviation',
      ),
      'web_article' => array(),*/
    //),
  );

  // Type of work.
  $items['biblio_type_of_work'] = array(
    'description' => 'Type of work',
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_type_of_work',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Type of work',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(
      /*'audiovisual' => array(
        'label' => 'Type',
      ),
      'book' => array(),
      'chart' => array(
        'label' => 'Type of Image',
      ),
      'classical' => array(
        'label' => 'Type',
      ),
      'conference_proceedings' => array(),
      'film' => array(
        'label' => 'Medium',
      ),
      'journal_article' => array(
        'label' => 'Type of Article',
      ),
      'legal_ruling' => array(),
      'magazine_article' => array(
        'label' => 'Type of Article',
      ),
      'manuscript' => array(),
      'map' => array(
        'label' => 'Type',
      ),
      'newspaper_article' => array(
        'label' => 'Type of Article',
      ),
      'patent' => array(
        'label' => 'Patent Type',
      ),
      'personal' => array(
        'label' => 'Type',
      ),
      'report' => array(
        'label' => 'Type',
      ),
      'thesis' => array(
        'label' => 'Thesis Type',
      ),
      'unpublished' => array(),
      'web_article' => array(
        'label' => 'Type of Medium',
      ),*/
    ),
  );

  // Biblio URL.
  $items['biblio_url'] = array(
    'description' => 'URL',
    'field' => array(
      'cardinality' => 1,
      'field_name' => 'biblio_url',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'URL',
      'description' => 'DOI URL or any other URL',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '20',
      ),
    ),
    // @todo: Applies to all?
    /*'bundles_info' => array(
      'artwork' => array(),
      'audiovisual' => array(),
      'book' => array(),
      'book_chapter' => array(),
      'bill' => array(),
      'broadcast' => array(),
      'case' => array(),
      'chart' => array(),
      'classical' => array(),
      'conference_paper' => array(),
      'conference_proceedings' => array(),
      'database' => array(),
      'film' => array(),
      'government_report' => array(),
      'hearing' => array(),
      'journal' => array(),
      'journal_article' => array(),
      'legal_ruling' => array(),
      'magazine_article' => array(),
      'manuscript' => array(),
      'map' => array(),
      'miscellaneous' => array(),
      'miscellaneous_section' => array(),
      'newspaper_article' => array(),
      'patent' => array(),
      'personal' => array(),
      'presentation' => array(),
      'report' => array(),
      'software' => array(),
      'statute' => array(),
      'thesis' => array(),
      'unpublished' => array(),
      'web_article' => array(),
      'web_project_page' => array(),
      'web_service' => array(),
      'website' => array(),
    ),*/
  );

  // Biblio volume.
  $items['biblio_volume'] = array(
    'description' => 'URL',
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_volume',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Volume',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '7',
      ),
    ),
    'bundles_info' => array(
      'book' => array(),
      'journal_article' => array(),
    ),
  );

  // Biblio volume.
  $items['biblio_doi'] = array(
    'description' => 'DOI',
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_doi',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'volume',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    // @todo: Applies to all?
    'bundles_info' => array(),
      /*'artwork' => array(),
      'audiovisual' => array(),
      'book' => array(),
      'book_chapter' => array(),
      'bill' => array(),
      'broadcast' => array(),
      'case' => array(),
      'chart' => array(),
      'classical' => array(),
      'conference_paper' => array(),
      'conference_proceedings' => array(),
      'database' => array(),
      'film' => array(),
      'government_report' => array(),
      'hearing' => array(),
      'journal' => array(),
      'journal_article' => array(),
      'legal_ruling' => array(),
      'magazine_article' => array(),
      'manuscript' => array(),
      'map' => array(),
      'miscellaneous' => array(),
      'miscellaneous_section' => array(),
      'newspaper_article' => array(),
      'patent' => array(),
      'personal' => array(),
      'presentation' => array(),
      'report' => array(),
      'software' => array(),
      'statute' => array(),
      'thesis' => array(),
      'unpublished' => array(),
      'web_article' => array(),
      'web_project_page' => array(),
      'web_service' => array(),
      'website' => array(),*/
    //)
  );

  // Biblio place published.
  $items['biblio_place_published'] = array(
    'description' => 'City',
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_place_published',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'City',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(),
      /*'audiovisual' => array(),
      'artwork' => array(),
      'book' => array(),
      'book_chapter' => array(),
      'case' => array(
        'label' => 'Place Published',
      ),
      'chart' => array(),
      'classical' => array(),
      'conference_paper' => array(),
      'conference_proceedings' => array(),
      'film' => array(
        'label' => 'Country',
      ),
      'hearing' => array(),
      'manuscript' => array(),
      'map' => array(),
      'newspaper_article' => array(),
      'patent' => array(),
      'personal' => array(),
      'report' => array(),
      'software' => array(),
      'statute' => array(
        'label' => 'Country',
      ),
      'thesis' => array(),
      'unpublished' => array(),
      'web_article' => array(),*/
    //),
  );

  // Biblio publisher.
  $items['biblio_publisher'] = array(
    'description' => 'Publisher',
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_publisher',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Publisher',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(
      //'artwork' => array(),
      //'audiovisual' => array(),
      'book' => array(),
      'book_chapter' => array(),
      /*'case' => array(
        'label' => 'Court',
      ),
      'chart' => array(),
      'classical' => array(),
      'conference_paper' => array(),
      'conference_proceedings' => array(),
      'database' => array(),
      'film' => array(),
      'government_report' => array(),
      'hearing' => array(),
      'legal_hearing' => array(),
      'manuscript' => array(
        'label' => 'Library/Archive',
      ),
      'map' => array(),
      'patent' => array(
        'label' => 'Assignee',
      ),
      'personal' => array(),
      'report' => array(
        'label' => 'Institution',
      ),
      'software' => array(),
      'thesis' => array(
        'label' => 'University',
      ),
      'unpublished' => array(
        'label' => 'Institution',
      ),
      'web_article' => array(),*/
    ),
  );

  // Biblio edition.
  $items['biblio_edition'] = array(
    'description' => 'Edition',
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_edition',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Edition',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(
      //'audiovisual' => array(),
      'book' => array(),
      'book_chapter' => array(),
      /*'bill' =>array(
        'label' => 'Session',
      ),
      'chart' => array(
        'label' => 'Version',
      ),
      'classical' => array(),
      'conference_proceedings' => array(),
      'government_report' => array(),
      'hearing' => array(
        'label' => 'Session',
      ),
      'legal_ruling' => array(),
      'magazine_article' => array(),
      'newspaper_article' => array(),
      'patent' => array(
        'label' => 'International Patent Classification',
      ),
      'personal' => array(
        'label' => 'Description',
      ),
      'software' => array(
        'label' => 'Version',
      ),
      'statute' => array(
        'label' => 'Session',
      ),
      'web_article' => array(),*/
    ),
  );

  // Biblio secondary title.
  $items['biblio_secondary_title'] = array(
    'description' => 'Secondary title',
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_secondary_title',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Secondary title',
      'required' => TRUE,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '5',
      ),
    ),
    'bundles_info' => array(
      'book' => array(
        'label' => 'Series Title',
      ),
      'book_chapter' => array(
        'label' => 'Book Title',
      ),
      'conference_paper' => array(
        'label' => 'Conference Name',
        'description' => 'Example: Proceedings of the Twelfth European Conference on Computer Systems, EuroSys 2017',
      ),
      'journal_article' => array(
        'label' => 'Journal',
      ),
      'phd_thesis' => array(
        'label' => 'Dissertation Number',
        'description' => 'Format: ETH Zurich, Diss Nr. 1234',
      ),
      'master_thesis' => array(
        'label' => 'Thesis number',
        'description' => 'Format: Systems Group Master\'s Thesis, no. 123; Department of Computer Science, ETH Zurich',
      ),
    ),
  );

  // Biblio tertiary title.
  $items['biblio_tertiary_title'] = array(
    'description' => 'Tertiary title',
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_tertiary_title',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Tertiary title',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(
      'book_chapter' => array(
        'label' => 'Series Title',
      ),
      /*'bill' => array(
        'label' => 'Legislative Body',
      ),
      'chart' => array(
        'label' => 'Name of File',
      ),
      'conference_proceedings' => array(
        'label' => 'Series Title',
      ),
      'government_report' => array(
        'label' => 'Series Title',
      ),
      'hearing' => array(
        'label' => 'Legislative Body',
      ),
      'patent' => array(
        'label' => 'International Title',
      ),*/
    ),
  );


  // Biblio venue
  $items['biblio_venue'] = array(
    'description' => 'Venue',
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_venue',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Venue',
      'description' => 'For US/CA locations: Chicago, IL, USA; All other locations: Lausanne, Switzerland',
      'required' => TRUE,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '6',
      ),
    ),
    'bundles_info' => array(
      'conference_paper' => array(
        'label' => 'Venue',
      ),
      'demo' => array(
        'label' => 'Venue',
      ),
      'workshop_paper' => array(
        'label' => 'Venue',
      ),
    ),
  );

  // Refereed designation.
  $items['biblio_refereed_designation'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_refereed_designation',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Refereed Designation',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    // @todo: Applies to all?
    'bundles_info' => array(),
      /*'artwork' => array(),
      'audiovisual' => array(),
      'book' => array(),
      'book_chapter' => array(),
      'bill' => array(),
      'chart' => array(),
      'classical' => array(),
      'conference_paper' => array(),
      'conference_proceedings' => array(),
      'database' => array(),
      'film' => array(),
      'government_report' => array(),
      'hearing' => array(),
      'journal_article' => array(),
      'legal_ruling' => array(),
      'magazine_article' => array(),
      'manuscript' => array(),
      'map' => array(),
      'newspaper_article' => array(),
      'patent' => array(),
      'personal' => array(),
      'report' => array(),
      'software' => array(),
      'statute' => array(),
      'thesis' => array(),
      'unpublished' => array(),
      'web_article' => array(),*/
    //),
  );

  // Original publication.
  $items['biblio_original_publication'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_original_publication',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Original Publication',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(),
      /*'audiovisual' => array(
        'label' => 'Contents',
      ),
      'book' => array(),
      'book_chapter' => array(),
      'bill' => array(
        'label' => 'History',
      ),
      'case' => array(
        'label' => 'History',
      ),
      'classical' => array(),
      'hearing' => array(
        'label' => 'History',
      ),
      'journal_article' => array(),
      'magazine_article' => array(),
      'newspaper_article' => array(),
      'patent' => array(),
      'report' => array(
        'label' => 'Contents',
      ),
      'software' => array(
        'label' => 'Contents',
      ),
      'statute' => array(
        'label' => 'History',
      ),
      'thesis' => array(),
      'web_article' => array(
        'label' => 'Contents',
      ),*/
    //),
  );

  // Publication status.
  $items['biblio_status'] = array(
    'field' => array(
      'field_name' => 'biblio_status',
      'type' => 'list_text',
      'cardinality' => 1,
      'settings' => array(
        'allowed_values' => array(
          'in_press' => 'In press',
          'submitted' => 'Submitted',
          'published' => 'Published',
        ),
      ),
    ),
    'instance' => array(
      'label' => t('Publication status'),
      'description' => t('Determine the publication status (In press, Submitted, Published, etc\').'),
      'display_label' => TRUE,
      'required' => TRUE,
      'default_value' => array(
        0 => array(
          'value' => 'published',
        ),
      ),
      'widget' => array(
        'module' => 'options',
        'type' => 'options_select',
        'weight' => '26',
        'settings' => array(
          'display_label' => TRUE,
        ),
      ),
    ),
  );

  // Language field.
  $items['biblio_language'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_language',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Language',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
	 'bundles_info' => array(),
  );

  // Custom1.
  /*$items['biblio_custom1'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_custom1',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Custom 1',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(
      'map' => array(
        'label' => 'Scale',
      ),
      'software' => array(
        'label' => 'Computer',
      ),
      'thesis' => array(),
    ),
  );

  // Custom2.
  $items['biblio_custom2'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_custom2',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Custom 1',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(
      'patent' => array(
        'label' => 'Issue Date',
      ),
      'thesis' => array(),
    ),
  );

  // Custom3.
  $items['biblio_custom3'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_custom3',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Custom 1',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(
      'patent' => array(
        'label' => 'Designated States',
      ),
      'thesis' => array(),
    ),
  );

  // Custom4.
  $items['biblio_custom4'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_custom4',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Custom 1',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(
      'patent' => array(
        'label' => 'Attorney/Agent',
      ),
      'thesis' => array(),
    ),
  );

  // Custom5.
  $items['biblio_custom5'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_custom5',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Custom 1',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(
      'patent' => array(
        'label' => 'References',
      ),
      'thesis' => array(),
    ),
  );

  // Custom6.
  $items['biblio_custom6'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_custom6',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Custom 6',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(
      'patent' => array(
        'label' => 'Legal Status',
      ),
      'thesis' => array(),
    ),
  );*/

  // Custom7.
  /*$items['biblio_custom7'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_custom7',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Custom 7',
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '-3',
      ),
    ),
    'bundles_info' => array(
      'thesis' => array(),
		'phd_thesis' => array(),
    ),
  );*/

  $items['biblio_supervisor'] = array(
    'field' => array(
      'cardinality' => '1',
      'field_name' => 'biblio_supervisor',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'type' => 'text',
    ),
    'instance' => array(
      'label' => 'Supervisor of Thesis',
      'description' => 'Example: Prof. Timothy Roscoe',
		  'required' => TRUE,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '14',
      ),
    ),
    'bundles_info' => array(
      'master_thesis' => array(),
		  'phd_thesis' => array(),
    ),
  );

  return $items;
}

/**
 * Implements hook_biblio_types_info().
 */
function biblio_biblio_types_info() {
  /*$types['audiovisual'] = array('name' => 'Audiovisual');
  $types['artwork'] = array('name' => 'Artwork');
  $types['bill'] = array('name' => 'Bill');*/
  $types['book'] = array('name' => 'Book');
  $types['book_chapter'] = array('name' => 'Book Chapter');
  /*$types['broadcast'] = array('name' => 'Broadcast');
  $types['case'] = array('name' => 'Case');
  $types['chart'] = array('name' => 'Chart');
  $types['classical'] = array('name' => 'Classical');*/
  $types['conference_paper'] = array('name' => 'Conference Paper');
  /*$types['conference_proceedings'] = array('name' => 'Conference Proceedings');
  $types['database'] = array('name' => 'Database');
  $types['film'] = array('name' => 'Film');
  $types['government_report'] = array('name' => 'Government Report');
  $types['hearing'] = array('name' => 'Hearing');
  $types['journal'] = array('name' => 'Journal');*/
  $types['journal_article'] = array('name' => 'Journal Article');
  /*$types['legal_ruling'] = array('name' => 'Legal Ruling');
  $types['magazine_article'] = array('name' => 'Magazine Article');
  $types['manuscript'] = array('name' => 'Manuscript');
  $types['map'] = array('name' => 'Map');
  $types['miscellaneous'] = array('name' => 'Miscellaneous');
  $types['miscellaneous_section'] = array('name' => 'Miscellaneous Section');
  $types['newspaper_article'] = array('name' => 'Newspaper Article');
  $types['patent'] = array('name' => 'Patent');
  $types['personal'] = array('name' => 'Personal');
  $types['presentation'] = array('name' => 'Presentation');
  $types['report'] = array('name' => 'Report');
  $types['software'] = array('name' => 'Software');
  $types['statute'] = array('name' => 'Statute');
  $types['thesis'] = array('name' => 'Thesis');
  $types['unpublished'] = array('name' => 'Unpublished');
  $types['web_article'] = array('name' => 'Web Article');
  $types['web_project_page'] = array('name' => 'Web project page');
  $types['web_service'] = array('name' => 'Web service');
  $types['website'] = array('name' => 'Website');*/

  // Types added for Systems Group
  $types['demo'] = array('name' => 'Demo');
  $types['master_thesis'] = array('name' => 'Master Thesis');
  $types['phd_thesis'] = array('name' => 'PhD Thesis');
  $types['technical_report'] = array('name' => 'Technical Report');
  $types['workshop_paper'] = array('name' => 'Workshop Paper');

  return $types;
}


