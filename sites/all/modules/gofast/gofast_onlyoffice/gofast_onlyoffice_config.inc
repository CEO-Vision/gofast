<?php

global $base_url, $conf;

define('WEB_ROOT_URL', $base_url);

define('DOC_SERV_TIMEOUT', '120000');
define('DOC_SERV_STORAGE_URL', 'https://'.$conf['gofast-comm_domain'].'/FileUploader.ashx');
define('DOC_SERV_CONVERTER_URL', 'https://'.$conf['gofast-comm_domain'].'/ConvertService.ashx');
define('DOC_SERV_API_URL', 'https://'.$conf['gofast-comm_domain'].'/web-apps/apps/api/documents/api.js');
define('DOC_SERV_PRELOADER_URL', 'https://'.$conf['gofast-comm_domain'].'/web-apps/apps/api/documents/cache-scripts.html');

function gofast_onlyoffice_viewable_document_extensions() {
    return array("xlsx", "xlsm", "xls", "ods");
}

function gofast_onlyoffice_editable_document_extensions() {
  $editable_extensions = array("docx", "doc", "docm", "odt", "xlsx", "xlsm", "xls", "ods", "odp", "csv", "pptx", "ppt", "ppsx", "rtf", "mht", "html", "htm");
  // Disabled for now because onlyoffice is not able to convert from docx (output after edit) to txt
  //$editable_extenstions[] = "txt";
  return $editable_extensions;
}

function gofast_onlyoffice_convertible_document_extensions() {
  return array("doc", "odt", "xls", "ods", "ppt", "pps", "odp", "rtf", "mht", "html", "htm", "epub");
}

function gofast_onlyoffice_spreadsheet_extensions() {
  return array("xls", "xlsx", "xlsm",
  "ods", "csv");
}

function gofast_onlyoffice_presentation_extensions() {
  return array("pps", "ppsx",
  "ppt", "pptx",
  "odp");
}

function gofast_onlyoffice_document_extensions() {
  return array("docx", "doc", "docm", "odt", "rtf", "txt",
  "html", "htm", "mht", "pdf", "djvu",
  "fb2", "epub", "xps");
}


if (!defined('ServiceConverterMaxTry')) {
  define('ServiceConverterMaxTry', 3);
}
  
