<?php

require_once(DRUPAL_ROOT .'/sites/all/libraries/SetaPDF/Autoload.php');

define('DEFAULT_STAMP_FONT','' );

define('DEFAULT_STAMP_FONT_SIZE', '12');

define('DEFAULT_STAMP_POSITION', SetaPDF_Stamper::POSITION_RIGHT_BOTTOM);



/**
 *
 * @param type $pdf_node
 * @return type
 */
function gofast_pdf_stamper_get_file($pdf_file){

  $reader = new SetaPDF_Core_Reader_File($pdf_file->filepath);

  $writer = new SetaPDF_Core_Writer_TempFile();

  // Load document by filename
  $document = SetaPDF_Core_Document::load($reader, $writer);

  return $document;
}

/**
 *
 * @param type $pdf_node
 * @param type $stamp_text
 * @param type $stamp_options (showOnPage, position, tranlsateX, translateY)
 */
function gofast_pdf_stamper_apply_stamp($pdf_node, $stamp_text, $stamp_options = array(), $textColor = NULL) {

  $pdf_file = gofast_cmis_item_get_content_publication($pdf_node, GOFAST_CMIS_PUBLICATION_TYPE_PDF);

  //load pdf document
  $document = gofast_pdf_stamper_get_file($pdf_file);

  // Create a stamper instance for the document
  $stamper = new SetaPDF_Stamper($document);

  $font = SetaPDF_Core_Font_Standard_Helvetica::create($document);
  $stamp = new SetaPDF_Stamper_Stamp_Text($font, DEFAULT_STAMP_FONT_SIZE);
  $stamp->setText($stamp_text);
  $stamp->setTextColor(new SetaPDF_Core_DataStructure_Color_Rgb($textColor));
  $stamper->addStamp($stamp, $stamp_options);

  $stamper->stamp();

  // save and send it to the client
  $document->save()->finish();

  $document_writer = $document->getWriter();
  copy($document_writer->getPath(), $pdf_file->filepath);

  gofast_pdf_stamper_savein_alfresco($pdf_node, $pdf_file);

  //purge temp file
  gofast_cmis_purge_published_temp_file($pdf_file->filepath);

}

/**
 *
 * @param type $pdf_node
 * @param type $pdf_file
 * @param type $new_major_version
 */
function gofast_pdf_stamper_savein_alfresco($pdf_node, $pdf_file, $new_major_version = FALSE) {

  gofast_cmis_item_set_content(gofast_cmis_node_get_item_id($pdf_node), file_get_contents($pdf_file->filepath), $pdf_file->filemime, array(), FALSE);

  // Create a comment
  if($new_major_version){
    gofast_cmis_tag_major_version($pdf_node, '');
  }

}
