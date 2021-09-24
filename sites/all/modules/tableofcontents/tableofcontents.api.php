<?php
/**
 * @file
 * This is a listing of how to implement api functions for developers.
 */

/**
 * Example of how to implement _tableofcontents_process_text
 * In this example, this function would be a menu callback.
 */
function youexamplemodule_page() {
  // TOC will be added to the top of the text area
  $text = '[toc]';
  // generate text some how, from a node or manually
  $text .= 'some text of some kind';
  // format is the input format that has TOC enabled
  $format = 'full_html';
  // check the markup of the format
  $output = check_markup($text, $format);
  // process the text of the page to add a TOC
  _tableofcontents_process_text($output);
  // return / print / do what you want with the output
  return $output;
}