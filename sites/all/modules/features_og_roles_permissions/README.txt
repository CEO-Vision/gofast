Features Organic Groups Roles Permissions
=========================================
Adds support for exporting Organic Group roles with related permissions in
features.

Module and code is based on features_og_roles_permissions
(https://www.drupal.org/project/features_og_roles_permissions).


Installation
============

Download, unpack and enable the module.

Dependencies
------------
* Organic Groups.
* Features.


Usage
=====
Create a new feature. Select from "OG Roles and permissions
(og_roles_permissions)" the Organic Groups Roles you want to export.
The permissions that are enabled for that role will be automatically included in
the feature.

NOTE : Only the default OG roles permissions are exportable, Group specific
       permissions can not be exported.

WARNING : Don't export permissions per OG role in combination with exporting
          permissions using "OG Permissions (og_features_permission)".
          This will result in overridden features.


Supporting organizations
========================
* AMPLEXOR International : Module development & support.
