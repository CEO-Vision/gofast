// -----------------------------------------------------------------------
// IT Hit WebDAV Ajax Library v5.20.5655.0
// Copyright © 2020 IT Hit LTD. All rights reserved.
// License: https://www.webdavsystem.com/ajax/
// -----------------------------------------------------------------------

/**
 * @typedef {ITHit.WebDAV.Client.WebDavSession} webDavSession
 */

QUnit.module('HierarchyItems.MicrosoftOfficeDiscovery');

/**
 * @class ITHit.WebDAV.Client.Tests.HierarchyItems.MicrosoftOfficeDiscovery
 */
ITHit.DefineClass('ITHit.WebDAV.Client.Tests.HierarchyItems.MicrosoftOfficeDiscovery', null, {}, /** @lends ITHit.WebDAV.Client.Tests.HierarchyItems.MicrosoftOfficeDiscovery */{

	OpenParent: function (test, sPath) {
		QUnit.stop();
		webDavSession.OpenFolderAsync(sPath, null, function(oAsyncResult) {
			QUnit.start();

			test.strictEqual(oAsyncResult.IsSuccess, true, 'Check success of open folder request (PROPFIND) to `' + sPath + '`');

			/** @typedef {ITHit.WebDAV.Client.Folder} oFolder */
			var oFolder = oAsyncResult.Result;

			if (!oFolder) {
				return;
			}

			QUnit.stop();
			oFolder.GetSupportedFeaturesAsync(function(oAsyncResult) {
				QUnit.start();

				test.strictEqual(oAsyncResult.IsSuccess, true, 'Check success of supported features request (OPTIONS) to `' + sPath + '`');

				var sParentPath = ITHit.WebDAV.Client.HierarchyItem.GetFolderParentUri(sPath);
				if (sParentPath !== null) {
					ITHit.WebDAV.Client.Tests.HierarchyItems.MicrosoftOfficeDiscovery.OpenParent(test, sParentPath);
				}
			})
		});
	}

});

QUnitRunner.test('Microsoft Office discovery', function (test) {
	QUnit.stop();
	Helper.Create([
		'Ms/Office/'
	], function() {
		QUnit.start();

		ITHit.WebDAV.Client.Tests.HierarchyItems.MicrosoftOfficeDiscovery.OpenParent(test, Helper.GetAbsolutePath('Ms/Office/'));
	});
});
