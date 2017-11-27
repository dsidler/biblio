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
    'bundles_info' => array(
      'conference_paper' => array(),
      'journal_article' => array(),
      'demo' => array(),
      'technical_report' => array(),
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
    'bundles_info' => array(
      'conference_paper' => array(),
      'journal_article' => array(),
      'demo' => array(),
      'technical_report' => array(),
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
    'bundles_info' => array(
      'conference_paper' => array(),
      'journal_article' => array(),
      'demo' => array(),
      'technical_report' => array(),
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
      'label' => 'Research Group',
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
    'bundles_info' => array(
      'book' => array(),
      'book_chapter' => array(),
    ),
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
      'book' => array(),
      'book_chapter' => array(),
    )
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
    //Applies to all
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
      'book' => array(),
      'book_chapter' => array(),
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
      'book' => array(),
      'book_chapter' => array(),
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
      /*'workshop_paper' => array(
        'label' => 'Venue',
      ),*/
    ),
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
  $types['book'] = array('name' => 'Book');
  $types['book_chapter'] = array('name' => 'Book Chapter');
  $types['conference_paper'] = array('name' => 'Conference Paper');
  $types['journal_article'] = array('name' => 'Journal Article');
  
  // Types added for Systems Group
  $types['demo'] = array('name' => 'Demo');
  $types['master_thesis'] = array('name' => 'Master Thesis');
  $types['phd_thesis'] = array('name' => 'PhD Thesis');
  $types['technical_report'] = array('name' => 'Technical Report');
  //$types['workshop_paper'] = array('name' => 'Workshop Paper');

  return $types;
}


