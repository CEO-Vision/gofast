<?php
/**
 * @file
 * gofast_features_taxonomy.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function gofast_features_taxonomy_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Email',
    'description' => 'An email file
',
    'format' => 'plain_text',
    'weight' => 15,
    'uuid' => '027878dc-1d6b-421e-81b8-6037e7e0a817',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';eml;msg;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-envelope-o file-mail',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'SVG',
    'description' => 'A SVG file',
    'format' => 'plain_text',
    'weight' => 3,
    'uuid' => '042649a3-4c0f-4af7-b7dc-69f9394157b2',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';svg;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-file-image-o image-svg',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Done',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '1bdfdf50-f460-4600-9662-ff1870d8db29',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'state',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Critical',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '1c1b24ce-f26c-4a82-b78d-9e4c592324bb',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'criticity',
  );
  $terms[] = array(
    'name' => 'Internal Distribution',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '245eb1de-161a-4181-8580-341225c01b82',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'criticity',
  );
  $terms[] = array(
    'name' => 'To Validate',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => '1ce68f6c-068b-4242-bd46-904bbf7eaecc',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'state',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Contract',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 6,
    'uuid' => '1edf6b08-b366-4323-915d-63840ccd74a9',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'category',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Vectorial presentation',
    'description' => 'Vectorial presentation',
    'format' => 'plain_text',
    'weight' => 22,
    'uuid' => '2331133e-656e-4517-ac1a-208592fd84c5',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';odg;pub;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-file-text-o file-odg',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Rejected',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => '26badcce-87b0-4b93-9c90-c66e3df7f27c',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'state',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Awaiting signature',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => '1e3c4721-a787-46bd-8bf7-03929e32ba32',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'state',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );

    $terms[] = array(
    'name' => 'Signed',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => 'd1771148-d81a-4099-824b-a6ce932486c6',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'state',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );

  $terms[] = array(
    'name' => 'Other',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 11,
    'uuid' => '2b50a40d-0751-4a3d-a55e-8cf52d8d87ba',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'category',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Userlist',
    'description' => '<p>Userlist</p>
',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '2d80cdf5-d2f2-492d-a7dc-7e95996fbf81',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';userlist;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-users userlist',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Draft',
    'description' => 'Draft',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => '35ec26c0-10f4-41ed-8373-9e260f9a8c94',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'state',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Private Space',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 9,
    'uuid' => '36d6aaee-75ed-45e2-8f4c-73b8ab539ee3',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';private_space;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-home',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Normal',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 2,
    'uuid' => '374ad1b1-3018-4e45-af72-e2bbba4e8d2f',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'criticity',
  );
  $terms[] = array(
    'name' => 'Report and minutes',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 2,
    'uuid' => '37a2a55a-98c0-4efe-a95e-12446f83698b',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'category',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Text file',
    'description' => 'A Text file with .txt.extension',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => '39860739-843e-46e3-b448-f30dcc153c43',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';txt;sh;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-file-text-o',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Extranet',
    'description' => 'An extranet space',
    'format' => 'plain_text',
    'weight' => 12,
    'uuid' => '404bd087-9928-4d7e-9108-c318cd77c17d',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';extranet;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-globe extranet',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Conference',
    'description' => 'Conference, Visio
',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => '480cc27f-223e-44c8-aa77-fb2d903eab7c',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';conference;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-video-camera',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Spreadsheet Document',
    'description' => 'A Spreadsheet file like Excel
',
    'format' => 'plain_text',
    'weight' => 5,
    'uuid' => '4fa7e52a-8a5a-4b92-82a3-f1382d2559b2',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';xls;xlsx;ods;xlsm;xltm;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-file-excel-o',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Public',
    'description' => 'A public space',
    'format' => 'plain_text',
    'weight' => 4,
    'uuid' => '5342fb2d-9235-4016-98ba-b11e71f701c3',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';public;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-share-alt',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Obsolete',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '592d5a53-1bbe-428c-bfee-67e5111c947b',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'state',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Audio',
    'description' => 'Audio file',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => '5f342b8e-f115-4771-8609-c986d9da98f9',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';mp3;wav;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-file-sound-o',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Picture',
    'description' => 'A Picture file',
    'format' => 'plain_text',
    'weight' => 18,
    'uuid' => '61e912a2-7439-438b-b012-125967a87c6f',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';jpg;jpeg;tiff;png;bmp;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-file-image-o',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Archive',
    'description' => 'An Archive file, like zip
',
    'format' => 'plain_text',
    'weight' => 24,
    'uuid' => '61ea50e8-4511-4ebf-a3bd-f76b2716c9ac',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';zip;bz2;rar;7zip;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-file-archive-o',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Validated',
    'description' => '',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => '6b81ccdf-1c26-4432-a067-daf1504acba7',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'state',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Wiki article',
    'description' => 'A Wiki page',
    'format' => 'plain_text',
    'weight' => 7,
    'uuid' => '6c4054f5-4aef-4994-98d9-2b4b4bc75e8f',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';article;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-newspaper-o',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Invoice',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 8,
    'uuid' => '7028233c-9977-4236-b9cb-247e63a034aa',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'category',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Presentation',
    'description' => 'A Presentation file like PowerPoint',
    'format' => 'plain_text',
    'weight' => 19,
    'uuid' => '7796ea2b-8393-41dc-9fa6-245312411ae8',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';ppt;pptx;odp;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-file-powerpoint-o',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Other',
    'description' => 'Undefined format
',
    'format' => 'plain_text',
    'weight' => 21,
    'uuid' => '78173f22-eebc-443a-bb64-4377596d96f5',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';default;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-file-o file-other',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Organisation',
    'description' => 'Organisation collaborative Space',
    'format' => 'plain_text',
    'weight' => 23,
    'uuid' => '7c400b02-877d-481a-a372-079e1af153aa',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';organisation;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-sitemap',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Application',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 12,
    'uuid' => '8261336c-8340-4b96-bce2-705206bf998b',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'category',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Pre-Archived',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '856899f7-6792-40c3-84d1-4d10e5fd4a2b',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'state',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Presentation',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 9,
    'uuid' => '8745aac2-cbd7-423f-8ec7-65824a08ece7',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'category',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'PDF Image',
    'description' => 'PDF non OCRisé
',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => '892a2640-8d27-495f-a665-5ceaa8e60d59',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';pdf_image;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-file-pdf-o pdf-image',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Confidential Data',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '901358ab-35fc-4eb4-9fbb-d335ea836758',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'criticity',
  );
  $terms[] = array(
    'name' => 'CAO',
    'description' => 'A CAO file, like Solidworks
',
    'format' => 'plain_text',
    'weight' => 14,
    'uuid' => '9177ec36-2b57-4dc6-909d-4f50835162f0',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';sldprt;slddrw;sldasm;step;igs;iges;dxf;dwg;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-file-o file-cao',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Forum',
    'description' => 'A forum
',
    'format' => 'plain_text',
    'weight' => 11,
    'uuid' => '93de18c0-3ddd-4317-8c84-7caa9964dc14',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';forum;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-comments-o',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Outbound (e)mail',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 10,
    'uuid' => 'b17fae5d-373f-4540-bab3-a1402bcfac9c',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'category',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'External Web Page',
    'description' => 'An External Web Page',
    'format' => 'plain_text',
    'weight' => 13,
    'uuid' => 'b326fe3d-1d5c-4044-b79d-dc8f78180fd2',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';external_page;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-globe external-page',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'In Progress',
    'description' => '<p>In Progress</p>
',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'b5dcca31-9dfa-4ea1-b51d-d128ea0a5196',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'state',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Form',
    'description' => 'A form',
    'format' => 'plain_text',
    'weight' => 10,
    'uuid' => 'bd095ec9-988d-43ac-b272-4e63dd6c3d2f',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';webform;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-list-alt file-webform',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Inbound (e)mail',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 4,
    'uuid' => 'c39d5846-6789-4f4d-b66a-029791a0ea03',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'category',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Specification',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 1,
    'uuid' => 'c65ca575-8c89-48c4-a3a8-c41ccd211314',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'category',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Group',
    'description' => 'Group collaborative Space
',
    'format' => 'plain_text',
    'weight' => 16,
    'uuid' => 'c8d39b32-61d6-4263-a2b7-da695b46e133',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';group;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-users',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Low',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 3,
    'uuid' => 'cbc9b096-b075-4a14-95a0-6dc4a5987b2b',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'criticity',
  );
  $terms[] = array(
    'name' => 'PDF',
    'description' => 'A PDF document
',
    'format' => 'plain_text',
    'weight' => 20,
    'uuid' => 'd34bc99c-e961-49de-9db7-cbc47b396938',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';pdf;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-file-pdf-o',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Profil',
    'description' => 'A user profile',
    'format' => 'plain_text',
    'weight' => 8,
    'uuid' => 'd3c55831-8f05-4379-b845-ad213d699654',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';user_profile;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-id-card-o',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Information',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 7,
    'uuid' => 'd654af50-1c14-484c-993a-b523827572fe',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'category',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Visio',
    'description' => 'A Visio file',
    'format' => 'plain_text',
    'weight' => 6,
    'uuid' => 'd68c8b68-45c5-4ff1-afd9-cd6db2f6c4f7',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';vsd;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-file-o file-visio',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Personal Data',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 1,
    'uuid' => 'dc7440e1-3260-429d-826d-6dc7d8554866',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'criticity',
  );
  $terms[] = array(
    'name' => 'Documentation',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 5,
    'uuid' => 'dd5cca08-9592-49a2-b18d-87c8720553ac',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'category',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Video',
    'description' => 'A Video file',
    'format' => 'plain_text',
    'weight' => 1,
    'uuid' => 'dd5e25f3-494c-46a9-b046-5f4c886f2c5a',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';wma;wmv;avi;flv;mp4;webm;mpg;mov;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-file-video-o',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'To Do',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'e35313b5-c593-4fe9-9992-7aae53335e29',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'state',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'HTML',
    'description' => 'An HTML document',
    'format' => 'plain_text',
    'weight' => 17,
    'uuid' => 'f0e01087-7832-4239-ac45-415b81730d8b',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';html;xhtml;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-file-code-o html',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Webform',
    'description' => '<p>Icon for webform</p>
',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => 'f2fcb5a9-451e-47ec-bbe4-0b86ad86867b',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';webform;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-list-alt file-webform',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Procedure',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 3,
    'uuid' => 'f335adf1-03d3-4453-9071-b81ae214f7a5',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'category',
    'field_standard_gf' => array(
      'und' => array(
        0 => array(
          'value' => 1,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Text Document',
    'description' => 'A text document like Word or LibreOffice',
    'format' => 'plain_text',
    'weight' => 2,
    'uuid' => 'f3ab0e3a-939a-4018-8c03-c792cc305cb4',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'format',
    'field_extensions' => array(
      'und' => array(
        0 => array(
          'value' => ';doc;docx;odt;dotx;rtf;',
          'format' => NULL,
        ),
      ),
    ),
    'field_icone' => array(
      'und' => array(
        0 => array(
          'value' => 'fa-file-word-o',
          'format' => NULL,
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'High',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 1,
    'uuid' => 'f9adc91d-c63b-4506-8e29-2c4f568f6b98',
    'language' => 'und',
    'i18n_tsid' => 0,
    'vocabulary_machine_name' => 'criticity',
  );
  return $terms;
}
