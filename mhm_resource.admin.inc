<?php

/**
 * Config form callback.
 */
function mhm_resource_config_form($form, &$form_state) {
  $form['mhm_resource_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Resource Node Types'),
    '#description' => t('Only selected node types will be treated as resources'),
    '#options' => node_type_get_names(),
    '#default_value' => variable_get('mhm_resource_node_types', array()),
  );

  $form['mhm_resource_namespace_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Namespace ID'),
    '#default_value' => variable_get('mhm_resource_namespace_id', NULL),
    '#required' => TRUE,
  );

  $form['mhm_resource_consumer_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Consumer Key'),
    '#description' => t('Enter the consumer key from MHM Resource'),
    '#default_value' => variable_get('mhm_resource_consumer_key', NULL),
    '#required' => TRUE,
  );

  $form['mhm_resource_consumer_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Consumer Secret'),
    '#description' => t('Enter the consumer secret from MHM Resource'),
    '#default_value' => variable_get('mhm_resource_consumer_secret', NULL),
    '#required' => TRUE,
  );

  $form['urls'] = array(
    '#type' => 'fieldset',
    '#title' => t('URLs'),
  );

  $form['urls']['mhm_resource_oauth_url'] = array(
    '#type' => 'textfield',
    '#title' => t('OAuth URL'),
    '#default_value' => variable_get('mhm_resource_oauth_url', NULL),
    '#required' => TRUE,
  );

  $form['urls']['mhm_resource_rest_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Rest Endpoint URL'),
    '#description' => t('Enter the rest endpoint URL'),
    '#default_value' => variable_get('mhm_resource_rest_url', NULL),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Implements hook_form_FORMID_validate().
 */
function mhm_resource_config_form_validate($form, &$form_state) {
  $oauth_url = &$form_state['values']['mhm_resource_oauth_url'];
  if(substr($oauth_url, -1, 1) !== '/') {
    $oauth_url .= '/';
  }

  $rest_url = &$form_state['values']['mhm_resource_rest_url'];
  if(substr($rest_url, -1, 1) !== '/') {
    $rest_url .= '/';
  }
}
