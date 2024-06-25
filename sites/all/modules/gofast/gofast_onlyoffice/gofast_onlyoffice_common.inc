<?php

module_load_include('inc', 'gofast_onlyoffice', 'gofast_onlyoffice_config');

function sendlog($msg, $logFileName) {
  file_put_contents("sites/default/files/" . $logFileName, $msg . PHP_EOL);
}

function guid() {
  if (function_exists('com_create_guid')) {
    return com_create_guid();
  }
  else {
    mt_srand((double) microtime() * 10000); //optional for php 4.2.0 and up.
    $charid = strtoupper(md5(uniqid(rand(), true)));
    $hyphen = chr(45); // "-"
    $uuid = chr(123)// "{"
            . substr($charid, 0, 8) . $hyphen
            . substr($charid, 8, 4) . $hyphen
            . substr($charid, 12, 4) . $hyphen
            . substr($charid, 16, 4) . $hyphen
            . substr($charid, 20, 12)
            . chr(125); // "}"
    return $uuid;
  }
}

if (!function_exists('mime_content_type')) {

  function mime_content_type($filename) {

    $mime_types = array(
      'txt' => 'text/plain',
      'htm' => 'text/html',
      'html' => 'text/html',
      'php' => 'text/html',
      'css' => 'text/css',
      'js' => 'application/javascript',
      'json' => 'application/json',
      'xml' => 'application/xml',
      'swf' => 'application/x-shockwave-flash',
      'flv' => 'video/x-flv',
      // images
      'png' => 'image/png',
      'jpe' => 'image/jpeg',
      'jpeg' => 'image/jpeg',
      'jpg' => 'image/jpeg',
      'gif' => 'image/gif',
      'bmp' => 'image/bmp',
      'ico' => 'image/vnd.microsoft.icon',
      'tiff' => 'image/tiff',
      'tif' => 'image/tiff',
      'svg' => 'image/svg+xml',
      'svgz' => 'image/svg+xml',
      // archives
      'zip' => 'application/zip',
      'rar' => 'application/x-rar-compressed',
      'exe' => 'application/x-msdownload',
      'msi' => 'application/x-msdownload',
      'cab' => 'application/vnd.ms-cab-compressed',
      // audio/video
      'mp3' => 'audio/mpeg',
      'qt' => 'video/quicktime',
      'mov' => 'video/quicktime',
      // adobe
      'pdf' => 'application/pdf',
      'psd' => 'image/vnd.adobe.photoshop',
      'ai' => 'application/postscript',
      'eps' => 'application/postscript',
      'ps' => 'application/postscript',
      // ms office
      'doc' => 'application/msword',
      'rtf' => 'application/rtf',
      'xls' => 'application/vnd.ms-excel',
      'ppt' => 'application/vnd.ms-powerpoint',
      // open office
      'odt' => 'application/vnd.oasis.opendocument.text',
      'ods' => 'application/vnd.oasis.opendocument.spreadsheet',
    );

    $ext = strtolower(array_pop(explode('.', $filename)));
    if (array_key_exists($ext, $mime_types)) {
      return $mime_types[$ext];
    }
    elseif (function_exists('finfo_open')) {
      $finfo = finfo_open(FILEINFO_MIME);
      $mimetype = finfo_file($finfo, $filename);
      finfo_close($finfo);
      return $mimetype;
    }
    else {
      return 'application/octet-stream';
    }
  }

}

function getClientIp() {
  $ipaddress = getenv('HTTP_CLIENT_IP')? : // empty
          getenv('HTTP_X_FORWARDED_FOR')? : // empty
                  getenv('HTTP_X_FORWARDED')? : // empty
                          getenv('HTTP_FORWARDED_FOR')? : // empty
                                  getenv('HTTP_FORWARDED')? : // empty
                                          getenv('REMOTE_ADDR')? : // /!\ IMPORTANT : This prints out ::1 because this is running in localhost, it will give the ip v4 when running on web hosting (tested)
                                                  '';

  return $ipaddress;
}

function getCurUserHostAddress($userAddress = NULL) {
  if (is_null($userAddress)) {
    $userAddress = getClientIp();
  }
  return preg_replace("[^0-9a-zA-Z.=]", '_', $userAddress);
}

function getInternalExtension($filename) {
  $ext = strtolower(pathinfo($filename, PATHINFO_EXTENSION));

  if (in_array($ext, gofast_onlyoffice_document_extensions()))
    return ".docx";
  if (in_array($ext, gofast_onlyoffice_spreadsheet_extensions()))
    return ".xlsx";
  if (in_array($ext, gofast_onlyoffice_presentation_extensions()))
    return ".pptx";
  return "";
}

function getDocumentType($filename) {
  $ext = strtolower(pathinfo($filename, PATHINFO_EXTENSION));

  if (in_array($ext, gofast_onlyoffice_document_extensions()))
    return "text";
  if (in_array($ext, gofast_onlyoffice_spreadsheet_extensions()))
    return "spreadsheet";
  if (in_array($ext, gofast_onlyoffice_presentation_extensions()))
    return "presentation";
  return "";
}

function getScheme() {
  return (isset($_SERVER['HTTPS']) && $_SERVER['HTTPS'] !== 'off') ? 'https' : 'http';
}

function getVirtualPath() {
  $storagePath = trim(str_replace(array('/', '\\'), '/', $GLOBALS['STORAGE_PATH']), '/');
  $storagePath = $storagePath != "" ? $storagePath . '/' : "";


  $virtPath = rtrim(WEB_ROOT_URL, '/') . '/' . $storagePath . getCurUserHostAddress() . '/';
  sendlog("getVirtualPath virtPath: " . $virtPath, "logs/common.log");
  return $virtPath;
}

?>