<?php

module_load_include('inc', 'gofast_onlyoffice', 'gofast_onlyoffice_config');
module_load_include('inc', 'gofast_onlyoffice', 'gofast_onlyoffice_common');

/**
 * @deprecated
 */
function servConvGetKey() {
  if (defined('ServiceConverterTenantId'))
    return ServiceConverterTenantId;
  return "Gofast3";
}

/**
 * @deprecated
 */
function servConvGetSKey() {
  if (defined('ServiceConverterKey'))
    return ServiceConverterKey;
  return "ONLYOFFICE";
}

/**
 * @deprecated
 */
function get_mime_type($file) {
  //List of mime types
  $mime_types = array(
    "pdf" => "application/pdf"
    , "exe" => "application/octet-stream"
    , "zip" => "application/zip"
    , "dotx" => "application/vnd.openxmlformats-officedocument.wordprocessingml.template"
    , "docx" => "application/msword"
    , "doc" => "application/msword"
    , "xls" => "application/vnd.ms-excel"
    , "xlsx" => "application/vnd.ms-excel"
    , "ppt" => "application/vnd.ms-powerpoint"
    , "gif" => "image/gif"
    , "png" => "image/png"
    , "jpeg" => "image/jpg"
    , "jpg" => "image/jpg"
    , "mp3" => "audio/mpeg"
    , "wav" => "audio/x-wav"
    , "mpeg" => "video/mpeg"
    , "mpg" => "video/mpeg"
    , "mpe" => "video/mpeg"
    , "mov" => "video/quicktime"
    , "avi" => "video/x-msvideo"
    , "3gp" => "video/3gpp"
    , "css" => "text/css"
    , "jsc" => "application/javascript"
    , "js" => "application/javascript"
    , "php" => "text/html"
    , "htm" => "text/html"
    , "html" => "text/html"
    , "xml" => "text/xml"
    , "txt" => "text/plain"
  );
  $tmp = explode('.', $file);
  $extension = end($tmp);
  return (array_key_exists($extension, $mime_types) ? $mime_types[$extension] : $mime_types["txt"]);
}

/**
 * @deprecated
 */
function GetExternalFileUri($local_uri) {
    $externalUri = '';

    try
    {
        $documentRevisionId = GenerateRevisionId($local_uri);
        if (($fileContents = file_get_contents(str_replace(" ","%20", $local_uri)))===FALSE){
            throw new Exception("Bad Request");
        } else {
            $contentType =  mime_content_type($local_uri);

            $urlToService = generateUrlToStorage('', '', '', '', $documentRevisionId);

            $opts = array('http' => array(
                    'method'  => 'POST',
                    'header'  => "User-Agent: " . $_SERVER['HTTP_USER_AGENT'] . "\r\n" .
                                    "Content-Type: " . $contentType . "\r\n" .
                                    "Content-Length: " . strlen($fileContents) . "\r\n",
                    'content' => $fileContents,
                    'timeout' => DOC_SERV_TIMEOUT
                )
            );

            if (substr($urlToService, 0, strlen("https")) === "https") {
                $opts['ssl'] = array( 'verify_peer'   => FALSE );
            }
 

            $context  = stream_context_create($opts);

            if (($response_data = file_get_contents($urlToService, FALSE, $context))===FALSE){
                throw new Exception ("Could not get an answer");
            } else {
                sendlog("GetExternalUri response_data:" . PHP_EOL . $response_data, "logs/common.log");
                GetResponseUri($response_data, $externalUri);
            }

            sendlog("GetExternalFileUri. externalUri = " . $externalUri, "logs/common.log");
            return $externalUri . "";
        }
    }
    catch (Exception $e)
    {
        sendlog("GetExternalFileUri Exception: " . $e->getMessage(), "logs/common.log");
    }
    return $local_uri;
}

/**
 * @deprecated
 */
function generateUrlToConverter($document_uri, $from_extension, $to_extension, $title, $document_revision_id, $validateKey, $is_async) {
  $urlToConverterParams = array(
    "url" => $document_uri,
    "outputtype" => trim($to_extension, '.'),
    "filetype" => trim($from_extension, '.'),
    "title" => $title,
    "key" => $document_revision_id,
    "vkey" => $validateKey);

  $urlToConverter = DOC_SERV_CONVERTER_URL . "?" . http_build_query($urlToConverterParams);

  if ($is_async)
    $urlToConverter = $urlToConverter . "&async=true";

  return $urlToConverter;
}

/**
 * @deprecated
 */
function generateUrlToStorage($document_uri, $from_extension, $to_extension, $title, $key, $validateKey) {

  return DOC_SERV_STORAGE_URL . "?" . http_build_query(
                  array(
                    "url" => $document_uri,
                    "outputtype" => trim($to_extension, '.'),
                    "filetype" => trim($from_extension, '.'),
                    "title" => $title,
                    "key" => $key,
                    "vkey" => $validateKey));
}

/**
 * Encoding string from object
 *
 * @param object $primary_key     Json of primary key
 * @param string $secret          Secret key for encoding
 *
 * @return Encoding string
 */
function signature_Create($primary_key, $secret) {
  $payload = base64_encode(hash('sha256', ($primary_key . $secret), true)) . "?" . $primary_key;
  $base64Str = base64_encode($payload);

  $ind = 0;
  for ($n = strlen($base64Str); $n > 0; $n--) {
    if ($base64Str[$n - 1] === '=') {
      $ind++;
    }
    else {
      break;
    }
  }
  $base64Str = str_replace(array('+', '/'), array('-', '_'), trim($base64Str, '==')) . $ind;

  return urlencode($base64Str);
}

/**
 * Generate an error code table
 *
 * @param string $errorCode   Error code
 *
 * @return null
 */
function ProcessConvServResponceError($errorCode) {
  $errorMessageTemplate = "Error occurred in the document service: ";
  $errorMessage = '';

  switch ($errorCode) {
    case -8:
      $errorMessage = $errorMessageTemplate . "Error document VKey";
      break;
    case -7:
      $errorMessage = $errorMessageTemplate . "Error document request";
      break;
    case -6:
      $errorMessage = $errorMessageTemplate . "Error database";
      break;
    case -5:
      $errorMessage = $errorMessageTemplate . "Error unexpected guid";
      break;
    case -4:
      $errorMessage = $errorMessageTemplate . "Error download error";
      break;
    case -3:
      $errorMessage = $errorMessageTemplate . "Error convertation error";
      break;
    case -2:
      $errorMessage = $errorMessageTemplate . "Error convertation timeout";
      break;
    case -1:
      $errorMessage = $errorMessageTemplate . "Error convertation unknown";
      break;
    case 0:
      break;
    default:
      $errorMessage = $errorMessageTemplate . "ErrorCode = " . $errorCode;
      break;
  }

  throw new Exception($errorMessage);
}

/**
 * Translation key to a supported form.
 *
 * @param string $expected_key  Expected key
 *
 * @return Supported key
 */
//function GenerateRevisionId($expected_key) {
//  if (strlen($expected_key) > 20)
//    $expected_key = crc32($expected_key);
//  $key = preg_replace("[^0-9-.a-zA-Z_=]", "_", $expected_key);
//  $key = substr($key, 0, min(array(strlen($key), 20)));
//  return $key;
//}

/**
* Translation key to a supported form.
*
* @param string $expected_key  Expected key
*
* @return Supported key
*/
function GenerateRevisionId($expected_key) {
    if (strlen($expected_key) > 20) $expected_key = crc32( $expected_key);
    $key = preg_replace("[^0-9-.a-zA-Z_=]", "_", $expected_key);
    $key = substr($key, 0, min(array(strlen($key), 20)));
    return $key;
}

/**
 * @deprecated
 */
function GenerateValidateKey($document_revision_id, $add_host_for_validate = true) {
  if (empty($document_revision_id))
    return '';

  $document_revision_id = GenerateRevisionId($document_revision_id);

  $keyId = servConvGetKey();

  $primaryKey = NULL;
  $ms = number_format(round(microtime(true) * 1000), 0, '.', '');

  if ($add_host_for_validate) {
    $userIp = getClientIp();

    if (!empty($userIp)) {
      $primaryKey = "{\"expire\":\"\\/Date(" . $ms . ")\\/\",\"key\":\"" . $document_revision_id . "\",\"key_id\":\"" . $keyId . "\",\"user_count\":0,\"ip\":\"" . $userIp . "\"}";
    }
  }

  if ($primaryKey == NULL)
    $primaryKey = "{\"expire\":\"\\/Date(" . $ms . ")\\/\",\"key\":\"" . $document_revision_id . "\",\"key_id\":\"" . $keyId . "\",\"user_count\":0}";

  sendlog("GenerateValidateKey. primaryKey = " . $primaryKey, "logs/common.log");

  return signature_Create($primaryKey, servConvGetSKey());
}

/**
 * @deprecated
 */
function SendRequestToConvertService($document_uri, $from_extension, $to_extension, $document_revision_id, $is_async) {
  if (empty($from_extension)) {
    $path_parts = pathinfo($document_uri);
    $from_extension = $path_parts['extension'];
  }

  $title = basename($document_uri);
  if (empty($title)) {
    $title = guid();
  }

  if (empty($document_revision_id)) {
    $document_revision_id = $document_uri;
  }

  $document_revision_id = GenerateRevisionId($document_revision_id);
  $validateKey = GenerateValidateKey($document_revision_id, false);

  $urlToConverter = generateUrlToConverter($document_uri, $from_extension, $to_extension, $title, $document_revision_id, $validateKey, $is_async);

  $response_xml_data = NULL;
  $countTry = 0;

  $opts = array('http' => array(
      'method' => 'GET',
      'timeout' => DOC_SERV_TIMEOUT
    )
  );

  if (substr($urlToConverter, 0, strlen("https")) === "https") {
    $opts['ssl'] = array('verify_peer' => FALSE);
  }

  $context = stream_context_create($opts);
  while ($countTry < ServiceConverterMaxTry) {
    $countTry = $countTry + 1;
    $response_xml_data = file_get_contents($urlToConverter, FALSE, $context);
    if ($response_xml_data !== false) {
      break;
    }
  }

  if ($countTry == ServiceConverterMaxTry) {
    throw new Exception("Bad Request or timeout error");
  }

  libxml_use_internal_errors(true);
  $data = simplexml_load_string($response_xml_data);
  if (!$data) {
    $exc = "Bad Response. Errors: ";
    foreach (libxml_get_errors() as $error) {
      $exc = $exc . "\t" . $error->message;
    }
    throw new Exception($exc);
  }

  return $data;
}

/**
 * @deprecated
 */
function GetConvertedUri($document_uri, $from_extension, $to_extension, $document_revision_id, $is_async, &$converted_document_uri) {
  $converted_document_uri = "";
  $responceFromConvertService = SendRequestToConvertService($document_uri, $from_extension, $to_extension, $document_revision_id, $is_async);

  $errorElement = $responceFromConvertService->Error;
  if ($errorElement != NULL && $errorElement != "")
    ProcessConvServResponceError($errorElement);

  $isEndConvert = $responceFromConvertService->EndConvert;
  $percent = $responceFromConvertService->Percent . "";

  if ($isEndConvert != NULL && strtolower($isEndConvert) == "true") {
    $converted_document_uri = $responceFromConvertService->FileUrl;
    $percent = 100;
  }
  else if ($percent >= 100)
    $percent = 99;

  return $percent;
}

/**
 * @deprecated
 */
function GetResponseUri($x_document_response, &$response_uri) {
    $response_uri = "";
    $resultPercent = 0;

    libxml_use_internal_errors(true);
    $data = simplexml_load_string($x_document_response);

    if (!$data) {
        $errs = "Invalid answer format. Errors: ";
        foreach(libxml_get_errors() as $error) {
           $errs = $errs . '\t' . $error->message;
        }

        throw new Exception ($errs);
    }

    $errorElement = $data->Error;
    if ($errorElement != NULL && $errorElement != "") ProcessConvServResponceError($data->Error);

    $endConvert = $data->EndConvert;
    if ($endConvert != NULL && $endConvert == "") throw new Exception("Invalid answer format");

    if ($endConvert != NULL && strtolower($endConvert) == true)
    {
        $fileUrl = $data->FileUrl;
        if ($fileUrl == NULL || $fileUrl == "") throw new Exception("Invalid answer format");

        $response_uri = $fileUrl;
        $resultPercent = 100;
    }
    else
    {
        $percent = $data->Percent;

        if ($percent != NULL && $percent != "")
            $resultPercent = $percent;
        if ($resultPercent >= 100)
            $resultPercent = 99;
    }

    return $resultPercent;
}

function gofast_onlyoffice_is_edition_disabled($node){
    $tags = taxonomy_get_term_by_name('NO-COEDITION', 'tags');
    $tid_template = array_keys($tags);


    $node_tags= array();
    foreach($node->field_tags[LANGUAGE_NONE] as $tag){
      $node_tags[] = $tag['tid'];
    }

    if(count(array_intersect($tid_template, $node_tags)) > 0){
        return true;
    }else{
        return false;
    }
}

?>