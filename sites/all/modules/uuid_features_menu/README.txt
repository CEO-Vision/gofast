CONTENTS OF THIS FILE 
---------------------  
* Introduction  
* Requirements  
* Installation  
* Configuration  
* Maintainers

INTRODUCTION 
------------ 
UUID Features Menu module adds Features support for
menu items using UUIDs instead of default mlid identifier. Each menu item
receives UUID hash and can be transferred with Features without using mlids. 
For core entity types (Nodes, Users, Taxonomy) this module will export 
menu items paths like 'node/[UUID]' which will be translated into 
normal "node/[NID]" when enabling Feature on target instance.

* For a full description of the module, visit the project page:
https://drupal.org/sandbox/ioskevich/2163429 
* To submit bug reports and feature suggestions, or to track changes:     
https://drupal.org/project/issues/2163429

REQUIREMENTS
------------ 
This module requires the following modules:  
* Core Menu module  
* Features (https://drupal.org/project/features)  
* UUID
(https://drupal.org/project/uuid)

INSTALLATION 
------------  
* Install as you would normally install a contributed
drupal module. See:  https://drupal.org/documentation/install/modules-
themes/modules-7 for further information.

CONFIGURATION 
------------- 
The module will add Features "Menu links (UUID)" component to the standard 
Features UI where you will be able to select menu itmes with UUID support you 
would like to export with your Feature.

NOTE: Because of Postgres doesn't currently have built-in UUID functions
you have to be attentive during the process of generating of UUIDs for
menu links.

Drush integration isn't implemented yet.


MAINTAINERS 
----------- 
Original development done by:  
* J. Rao (jrao): https://drupal.org/user/623328

Current maintainer:  
* Vitaly Ioskevich (ioskevich): https://drupal.org/user/85913

This project has been sponsored by:  
* DrupalSquad (https://drupal.org/node/1738596)  
DrupalSquad provides expert Drupal maintenance and development on-demand.

Through our easy-to-use ticketing system (http://drupalsquad.com), we can 
handle any size assignment, no matter how small (or large). Estimates are 
always free and 100% guaranteed. A joint venture of Warecorp and 
New Amsterdam Ideas, DrupalSquad is a global team with offices in Seattle, 
Minneapolis, New York and Minsk. Whether you’re an agency looking for a 
technology partner, a development shop looking to expand your engineering 
capacity, or just need help with your website, DrupalSquad is here for you.
