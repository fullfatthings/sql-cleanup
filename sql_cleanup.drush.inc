<?php

/**
 * Implements hook_drush_command().
 */
function sql_cleanup_drush_command() {
  $items['sql-drop-database'] = array(
    'description' => 'Drop the sites database',
    'bootstrap' => DRUSH_BOOTSTRAP_NONE,
    'options' => array(
      'db-su' => 'Account to use when dropping the DB.',
      'db-su-pw' => 'Password for the "db-su" account.',
    ),
  );
  $items['sql-create-database'] = array(
    'description' => 'Create the sites database without any grants, unlike core drush.',
    'bootstrap' => DRUSH_BOOTSTRAP_NONE,
    'options' => array(
      'db-su' => 'Account to use when dropping the DB.',
      'db-su-pw' => 'Password for the "db-su" account.',
    ),
  );
  return $items;
}


/**
 * SQL Drop Database command callback.
 */
function drush_sql_cleanup_sql_drop_database() {
  if (!drush_confirm(dt('Do you really want to continue?'))) {
    return drush_user_abort();
  }

  drush_sql_bootstrap_further();
  $db = drush_sql_get_class();
  $db_spec = $db->db_spec();
  $dbname = $db_spec['database'];

  $sql[] = sprintf('DROP DATABASE %s;', $db_spec['database']);
  $sql[] = 'FLUSH PRIVILEGES;';
  $sql = implode(' ', $sql);

  $db->su();
  return $db->query($sql);
}


/**
 * SQL Create Database command callback.
 */
function drush_sql_cleanup_sql_create_database() {
  if (!drush_confirm(dt('Do you really want to continue?'))) {
    return drush_user_abort();
  }

  drush_sql_bootstrap_further();
  $db = drush_sql_get_class();
  $db_spec = $db->db_spec();
  $dbname = $db_spec['database'];

  $sql[] = sprintf('DROP DATABASE IF EXISTS %s;', $db_spec['database']);
  $sql[] = sprintf('CREATE DATABASE %s /*!40100 DEFAULT CHARACTER SET utf8 */;', $db_spec['database']);
  $sql = implode(' ', $sql);

  $db->su();
  return $db->query($sql);
}
