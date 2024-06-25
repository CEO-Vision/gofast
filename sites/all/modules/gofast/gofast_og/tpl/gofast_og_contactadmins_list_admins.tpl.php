<h1 style="font-size: 19px;"><?php print $warning; ?></h1>
<div class="table-responsive" style="max-height: 400px; overflow-y:scroll">
	<table class="table table-bordered table-striped">
		<thead>
		<tr>
			<th><?php print t('Space', array(), array('context' => 'gofast:gofast_og::contact_admins')); ?></th>
			<th><?php print t('Administrators', array(), array('context' => 'gofast:gofast_og::contact_admins')); ?></th>
			<th><?php print t('Remove', array(), array('context' => 'gofast:gofast_og::contact_admins')); ?></th>
		</tr>
		</thead>
		<tbody>
		<?php foreach ($spaces as $space): ?>
      <?php  $admins = get_all_admin_group($space->nid); ?>
			<tr>
				<td><?php print check_plain($space->title); ?></td>
				<td>
					<?php if (count($admins) > 0): ?>
						<?php foreach ($admins as $uid): ?>
							<?php $admin_user = user_load($uid); ?>
							<div class="admin-info" style="display: flex block; gap: 20px;">
								<div class="admin-avatar"><?php print theme('user_picture', array('account' => $admin_user)); ?></div>
								<div class="admin-name-email">
                    <span style="font-weight: bold; font-size: 14px; text-transform: capitalize;">
                      <?php
                      print check_plain($admin_user->ldap_user_givenname[LANGUAGE_NONE][0]["value"]) . ' '
	                      . check_plain($admin_user->ldap_user_sn[LANGUAGE_NONE][0]["value"]);
                      ?>
                    </span>
									<br/>
									<span><?php print check_plain($admin_user->mail); ?></span>
								</div>
							</div>
						<?php endforeach; ?>
					<?php else: ?>
						<?php print t('No administrators', array(), array('context' => 'gofast:gofast_og::contact_admins')); ?>
					<?php endif; ?>
				</td>
				<td title="<?php print t("Don't send a message to the administrators of this space.", array(), array('context' => 'gofast:gofast_og::contact_admins')); ?>">
            <span onclick="Gofast.og.remove_space_from_contact_admin_modal_form(this, <?php print $space->nid; ?>)">
              <i class="text-danger fa fa-trash fa-lg"></i>
            </span>
				</td>
			</tr>
		<?php endforeach; ?>
		</tbody>
	</table>
</div>
