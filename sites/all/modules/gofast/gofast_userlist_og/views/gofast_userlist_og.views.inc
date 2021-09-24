<?php


/**
 * @file
 * Provides support for the Views module.
 */

/**
 * "OG membership" entity Views definitions.
 */
class GofastUserlistOgMembershipViewsController extends EntityDefaultViewsController {

  /**
   * Override views_data().
   */
  public function views_data() {
    $data = parent::views_data();

    $data['og_membership']['og_userlist_roles'] = array(
      'title' => t('OG userlist roles in group'),
      'help' => t('Show all the roles a userlist belongs to in a group. Requires a relationship to userlists to be present.'),
      // This is a dummy field, so point it to a real field that we need - the
      // group ID
      'real field' => 'gid',
      'field' => array(
        'handler' => 'gofast_userlist_og_handler_field_userlist_roles',
      ),
    );

    $data['og_membership']['gofast_og_userlists_roles'] = array(
      'title' => t('OG UserList Roles from membership'),
      'help' => t('The OG Roles associated with the OG membership for Userlist'),
      // Provide a possible relationship to roles through ulid.
      'relationship' => array(
        'label' => t('OG UserList Roles from OG membership'),
        'handler' => 'gofast_userlist_og_handler_relationship_membership_roles',
        'base' => 'gofast_og_userlists_roles',
        'base field' => 'ulid',
        'relationship field' => 'etid',
      ),
    );

    $data['og_role']['table']['group'] = t('OG user/userlist roles');
    $data['og_role']['table']['join'] = array(
      'gofast_og_userlists_roles' => array(
        'left_field' => 'rid',
        'field' => 'rid',
      ),
      'og_users_roles' => array(
            'left_field' => 'rid',
            'field' => 'rid',
      )
    );

    $data['og_role']['name'] = array(
      'title' => t('Role Name'),
      'help' => t('The OG role name.'),
      'filter' => array(
        'handler' => 'gofast_userlist_og_handler_filter_userlist_roles',
      ),
    );


    $data['gofast_userlists']['gofast_views_handler_field_userlist_og_roles'] = array(
      'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
      'field' => array(
        'title' => t('GoFAST userlist OG roles', array(), array('context' => 'gofast')),
        'help' => t('Display GoFAST (non-technical) userlist OG roles, given a space (OG group) context.', array(), array('context' => 'gofast')),
        'handler' => 'gofast_userlist_og_handler_field_userlist_og_roles',
      )
    );


  $data['og_membership']['gofast_userlist_og_handler_field_member_picture'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'real field' => 'etid',
    'field' => array(
      'title' => t('OG member picture', array(), array('context' => 'gofast')),
      'help' => t('Provide themed member picture.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_userlist_og_handler_field_member_picture',
    )
  );

  $data['og_membership']['gofast_userlist_number_members'] = array(
    'group' => t('Userlist members', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Userlist members', array(), array('context' => 'gofast')),
      'help' => t('Number of members', array(), array('context' => 'gofast')),
      'handler' => 'gofast_userlist_og_handler_field_userlist_directories_userlist_number_members',
    ),
  );

  $data['og_membership']['gofast_userlist_handler_field_userlist_directories_userlist_number_members'] = array(
    'group' => t('Userlist admins', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Userlist admins', array(), array('context' => 'gofast')),
      'help' => t('Number of admins', array(), array('context' => 'gofast')),
      'handler' => 'gofast_userlist_og_handler_field_userlist_directories_userlist_number_admins',
    ),
  );
  return $data;
  }
}
