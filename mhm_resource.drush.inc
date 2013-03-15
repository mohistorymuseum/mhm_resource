<?php

/**
 * Implements hook_drush_command().
 */
function mhm_resource_drush_command() {
  $commands['mhm-resource-reconcile'] = array(
    'description' => dt('Checks to see if any resources have been created (nodes) but for whatever reason there a mhm_resource hasn\'t been created'),
    'aliases' => array('mhm-rr'),
    'options' => array(
      'limit' => t('The maximum number of records to process'),
    ),
  );

  return $commands;
}

function drush_mhm_resource_reconcile() {
  $types = array_filter(variable_get('mhm_resource_node_types', array()));

  $query = db_select('node', 'n');
  $query->fields('n', array('nid'));
  $query->leftJoin('mhm_resource', 'r', 'n.nid = r.nid');
  $query->isNull('r.nid');
  $query->condition('n.status', 1);
  $query->condition('n.type', $types, 'IN');
  $result = $query->execute();
  $count = $result->rowCount();
  if($count == 0) {
    return drush_user_abort('No records were found');
  }
  if(!drush_confirm(format_plural($count, 'Found 1 record to process. Continue?', 'Found @count records to process. Continue?', array('@count' => $count)))) {
    return drush_user_abort();
  }
  if($limit = drush_get_option('limit') && $count > 0 && $count > $limit) {
    drush_log(dt('Okay, here we go. Since you set a limit of @limit, but we found @count records, we\'ll stop after @limit', array('@limit' => $limit, '@count' => $count)), 'ok');
  }

  $i = 1;
  foreach($result as $row) {
    $node = node_load($row->nid);
    mhm_resource_node_update($node);
    if($i == $limit) {
      break;
    }
    $i++;
  }

  drush_log('All done!', 'success');
}
