<?php

global $base_url, $conf;

define('WEB_ROOT_URL', $base_url);

define('DOC_SERV_TIMEOUT', '120000');
define('DOC_SERV_STORAGE_URL', 'https://'.$conf['gofast-comm_domain'].'/FileUploader.ashx');
define('DOC_SERV_CONVERTER_URL', 'https://'.$conf['gofast-comm_domain'].'/ConvertService.ashx');
define('DOC_SERV_API_URL', 'https://'.$conf['gofast-comm_domain'].'/web-apps/apps/api/documents/api.js');
define('DOC_SERV_PRELOADER_URL', 'https://'.$conf['gofast-comm_domain'].'/web-apps/apps/api/documents/cache-scripts.html');
define('DOC_SERV_COMMAND_SERVICE', 'https://internal-'.$conf['gofast-comm_domain'].'/coauthoring/CommandService.ashx');

function gofast_onlyoffice_rtl_languages() {
  return array("ar", "he", "fa", "ur");
}

function gofast_onlyoffice_viewable_document_extensions() {
    return array("xlsx", "xlsm", "xls", "ods");
}

function gofast_onlyoffice_comparable_document_extensions() {
  return array("doc", "docx", "odt", "pdf");
}

function gofast_onlyoffice_editable_document_extensions() {
  $editable_extensions = array("docx", "docxf", "dotx", "odt", "xlsx", "ods", "odp", "pptx", "ppsx", "txt", "doc", "ppt", "xls");
  return $editable_extensions;
}

function gofast_onlyoffice_old_ms_extensions() {
  return array("doc", "xls", "ppt", "pps");
}

function gofast_onlyoffice_convertible_document_extensions() {
  return array("doc", "odt", "xls", "ods", "ppt", "pps", "odp", "rtf", "mht", "html", "htm", "epub");
}

/*
 Extensions for which the transformation is manage manually by us
*/
function gofast_manual_previewable_document_extensions() {
  return array("doc", "dot", "ppt", "pps", "xls", "eml", "vsd", "odg", "msg", "dwg");
}

function gofast_onlyoffice_previewable_document_extensions() {
  return array("docx", "dotx", "pptx", "ppsx", "docm");
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

function gofast_onlyoffice_get_onclick_contextual_action($node){
  $cmis_object = gofast_cmis_node_edit_item_get($node);

  $current_mimetype = $cmis_object->properties["cmis:contentStreamMimeType"];
  if(gofast_onlyoffice_is_mimetype_must_convert($current_mimetype)){
    global $base_url;
    return "Gofast.gofast_onlyoffice_show_warning('" . $base_url . "/onlyoffice/editor/" . $node->nid . "',$node->nid,event);";
  }else{
    return "";
  }
}


if (!defined('ServiceConverterMaxTry')) {
  define('ServiceConverterMaxTry', 3);
}
  
