# Update

In case you are updating CKEditor in a GoFAST context, you'll need to backup your files first in order to reinsert GoFAST custom development code in the module after the update.

## Pre-update
1. Backup
2. Replace the content of the folder by the content of the .tar.gz of the last release.
3. Go to $BASE_URL/update.php to launch database update (if needed)

## Post-update
1. Restore everything from `/* Custom CKEDITOR autocomplete */` onward in ./css/ckeditor.css
2. In ./ckeditor.config.js, restore the config.extraPlugins and config.filebrowserUploadUrl values
3. In ./includes/ckeditor.utils.js, replace the `Drupal.ckeditorLoadPlugins` method and add the `textarea_id` parameter to each of its calls.