// -----------------------------------------------------------------------
// IT Hit WebDAV Ajax Library v5.20.5655.0
// Copyright © 2020 IT Hit LTD. All rights reserved.
// License: https://www.webdavsystem.com/ajax/
// -----------------------------------------------------------------------

/**
 * @typedef {ITHit.WebDAV.Client.WebDavSession} webDavSession
 */

QUnit.module('Upload.CancelUpload');

QUnitRunner.test('Cancel upload on created file', function (test) {
    QUnit.stop();
    Helper.Create([
        'Upload/cancel_file2.txt'
    ], function() {
        QUnit.start();

        QUnit.stop();
        webDavSession.OpenItemAsync(Helper.GetAbsolutePath('Upload/cancel_file2.txt'), null, function(oAsyncResult) {
            QUnit.start();

            /** @typedef {ITHit.WebDAV.Client.Folder} oFolder */
            var oFile = oAsyncResult.Result;

            test.strictEqual(oAsyncResult.IsSuccess, true, 'Check success of open item request');
            test.strictEqual(oFile instanceof ITHit.WebDAV.Client.File, true, 'Check result is instance of File');
            test.strictEqual(oFile.ResumableUpload instanceof ITHit.WebDAV.Client.ResumableUpload, true, 'Check file have link to ResumableUpload instance');

            // Async variant
            QUnit.stop();
            oFile.ResumableUpload.CancelUploadAsync(null, function(oAsyncResult) {
                QUnit.start();

                test.strictEqual(oAsyncResult.IsSuccess, true, 'Check success of cancel upload request');
            });
        });
    });
});
