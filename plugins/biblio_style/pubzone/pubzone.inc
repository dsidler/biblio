<?php

$plugin = array(
  'title' => t('Pubzone'),
  'description' => t('Pubzone Bulk Import.'),
  'class' => 'BiblioStylePubzone',
  // Indicates this style plugin can import entries.
  'import' => TRUE,
  'options' => array(
    'opening_tag' => '{',
    'closing_tag' => '}',
  ),
  /*'export' => array(
    'bibtex' => array(
      'name' => t('Pubzone'),
      'file extension' => 'bib',
    ),
  ),*/
);
