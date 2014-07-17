<?php

function sql_cleanup_drush_command() {
  $items['sql-drop-database'] = array(
    'description' => 'Drop the sites database',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'options' => array(
      'db-su' => 'Account to use when dropping the DB.',
      'db-su-pw' => 'Password for the "db-su" account.',
    ),
  );
  return $items;
}


function drush_sql_cleanup_sql_drop_database() {
  if (!drush_confirm(dt('Do you really want to continue?'))) {
    return drush_user_abort();
  }

  $db_spec = _drush_sql_get_db_spec();

  $sql[] = sprintf('DROP DATABASE %s;', $db_spec['database']);
  $sql[] = 'FLUSH PRIVILEGES;';
  $sql = implode(' ', $sql);

  $db_su = drush_sql_su($db_spec);
  drush_print($sql);

  return _drush_sql_query($sql, $db_su);
}
