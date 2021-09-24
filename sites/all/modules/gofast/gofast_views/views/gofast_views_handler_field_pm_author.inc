<?php

/**
 * @file
 * User Relationships Views integration.
 * Show column with link to change approval status.
 */
class gofast_views_handler_field_pm_author extends views_handler_field_node_link {

    function render($values) {
        $output = '';
        $thread = privatemsg_thread_load($values->pm_index_thread_id);
        $account = $thread['user'];
        if($account) {
            $output .= theme('user_picture', array('account' => $account, 'popup' => FALSE, 'dimensions' => array(
                'width' => '20px',
                'height' => '20px',
            )));
        }

        $output = '<div style="display:inline-flex;">' . $output . '</div>';
        return $output;
    }

}
